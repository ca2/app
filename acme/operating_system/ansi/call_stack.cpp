//
//  callstack.cpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Soerensen on 14/02/22.
//  15:33
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "platform.h"

#if !defined(WINDOWS)


#include "call_stack.h"
#include "acme/exception/call_stack.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform_platform.h"
#include "acme/platform/system.h"
#if !defined(__HAIKU__)
#include <execinfo.h>
#else
#include <unwind.h>
#include <dlfcn.h>
#include <stdint.h>
#endif
#include <cxxabi.h>
#if defined(__HAIKU__)
struct haiku_call_stack_capture
{
   void **stack;
   ::i32 capacity;
   ::i32 count;
};

static _Unwind_Reason_Code haiku_call_stack_capture_frame(
   _Unwind_Context *context, void *argument)
{
   auto &capture = *static_cast<haiku_call_stack_capture *>(argument);
   auto address = _Unwind_GetIP(context);
   if (!address || capture.count >= capture.capacity)
      return _URC_END_OF_STACK;
   capture.stack[capture.count++] = reinterpret_cast<void *>(address);
   return _URC_NO_REASON;
}
#endif
#if defined(__SUNOS__)
#include <dlfcn.h>
#include <stdint.h>
#include <spawn.h>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <elf.h>
#include "acme/prototype/collection/string_array.h"
extern char **environ;

static long long sunos_call_stack_milliseconds()
{
   struct timespec now = {};
   if (clock_gettime(CLOCK_MONOTONIC, &now) != 0) return 0;
   return (long long)now.tv_sec * 1000 + now.tv_nsec / 1000000;
}

// No shell, bounded output, and one shared deadline for the entire stack.
static string sunos_call_stack_addr2line(char **arguments, long long deadline)
{
   int output[2];
   if (pipe(output) != 0) return {};
   for (int i = 0; i < 2; ++i)
   {
      if (output[i] <= STDERR_FILENO)
      {
         auto replacement = fcntl(output[i], F_DUPFD, 3);
         if (replacement < 0) { close(output[0]); close(output[1]); return {}; }
         close(output[i]);
         output[i] = replacement;
      }
      if (fcntl(output[i], F_SETFD, FD_CLOEXEC) != 0)
      { close(output[0]); close(output[1]); return {}; }
   }
   posix_spawn_file_actions_t actions;
   if (posix_spawn_file_actions_init(&actions) != 0)
   { close(output[0]); close(output[1]); return {}; }
   int actionError = posix_spawn_file_actions_adddup2(&actions, output[1], STDOUT_FILENO);
   if (!actionError) actionError = posix_spawn_file_actions_addclose(&actions, output[0]);
   if (!actionError) actionError = posix_spawn_file_actions_addclose(&actions, output[1]);
   if (!actionError) actionError = posix_spawn_file_actions_addopen(&actions, STDERR_FILENO, "/dev/null", O_WRONLY, 0);
   pid_t child = -1;
   int result = actionError ? actionError : posix_spawnp(&child, "addr2line", &actions, nullptr, arguments, environ);
   posix_spawn_file_actions_destroy(&actions);
   close(output[1]);
   if (result != 0) { close(output[0]); return {}; }
   struct child_scope
   {
      pid_t pid;
      int descriptor;
      ~child_scope()
      {
         if (pid > 0)
         {
            kill(pid, SIGKILL);
            while (waitpid(pid, nullptr, 0) < 0 && errno == EINTR) {}
         }
         close(descriptor);
      }
   } childGuard { child, output[0] };
   if (fcntl(output[0], F_SETFL, O_NONBLOCK) != 0) return {};

   string text;
   bool completed = false;
   int status = 0;
   for (;;)
   {
      auto now = sunos_call_stack_milliseconds();
      if (!now || now >= deadline) break;
      char buffer[4096];
      ssize_t count;
      while ((count = read(output[0], buffer, sizeof(buffer))) > 0)
      {
         if (text.size() + count > 131072) break;
         text.append(buffer, (memsize)count);
      }
      if (text.size() >= 131072 || count > 0) break;
      auto waited = waitpid(child, &status, WNOHANG);
      if (waited == child)
      {
         childGuard.pid = -1;
         // Drain bytes written between the preceding read and child exit.
         while ((count = read(output[0], buffer, sizeof(buffer))) > 0)
         {
            if (text.size() + count > 131072) return {};
            text.append(buffer, (memsize)count);
         }
         completed = true;
         break;
      }
      if (waited < 0 && errno == ECHILD) { childGuard.pid = -1; break; }
      if (waited < 0 && errno != EINTR) break;
      struct pollfd descriptor = { output[0], POLLIN, 0 };
      auto remaining = deadline - sunos_call_stack_milliseconds();
      if (remaining > 0) poll(&descriptor, 1, (int)minimum(remaining, 20LL));
   }
   if (!completed || !WIFEXITED(status) || WEXITSTATUS(status) != 0) return {};
   return text;
}

static bool sunos_call_stack_fixed_executable(const char *path)
{
   auto fd = open(path, O_RDONLY);
   if (fd < 0) return false;
   // e_type has the same offset for ELF32 and ELF64 on native SunOS.
   unsigned char header[18] = {};
   auto count = read(fd, header, sizeof(header));
   close(fd);
   if (count != sizeof(header) || header[0] != 0x7f || header[1] != 'E' || header[2] != 'L' || header[3] != 'F') return false;
   auto type = header[EI_DATA] == ELFDATA2MSB
      ? (header[16] << 8) | header[17] : header[16] | (header[17] << 8);
   return type == ET_EXEC;
}

static string_array_base sunos_call_stack_source_lines(void *const *stack, int frames, int skip)
{
   string_array_base lines;
   lines.set_size(frames);
   static thread_local bool resolving = false;
   if (resolving) return lines;
   struct resolving_scope
   {
      bool &flag;
      resolving_scope(bool &value) : flag(value) { flag = true; }
      ~resolving_scope() { flag = false; }
   } scope(resolving);
   auto start = sunos_call_stack_milliseconds();
   if (!start) return lines;
   const auto deadline = start + 2000;
   string_array_base modules;
   for (int i = skip; i < frames; ++i)
   {
      Dl_info info = {};
      if (stack[i] && dladdr(stack[i], &info) && info.dli_fname && *info.dli_fname)
         modules.add_unique(info.dli_fname);
   }
   for (auto &module : modules)
   {
      if (sunos_call_stack_milliseconds() >= deadline) break;
      char addresses[96][32];
      int frameIndices[96];
      char *arguments[100];
      arguments[0] = (char *)"addr2line";
      arguments[1] = (char *)"-e";
      arguments[2] = (char *)module.c_str();
      int count = 0;
      bool fixed = sunos_call_stack_fixed_executable(module.c_str());
      for (int i = skip; i < frames && count < 96; ++i)
      {
         Dl_info info = {};
         if (!stack[i] || !dladdr(stack[i], &info) || !info.dli_fname || module != info.dli_fname) continue;
         uintptr_t pc = (uintptr_t)stack[i];
         if (!fixed) pc -= (uintptr_t)info.dli_fbase;
         // Captured PCs are return addresses; select the calling instruction.
         if (pc) --pc;
         snprintf(addresses[count], sizeof(addresses[count]), "0x%llx", (unsigned long long)pc);
         frameIndices[count] = i;
         arguments[3 + count] = addresses[count];
         ++count;
      }
      arguments[3 + count] = nullptr;
      auto output = sunos_call_stack_addr2line(arguments, deadline);
      string_array_base resolved;
      resolved.add_lines(output);
      for (int i = 0; i < count && i < resolved.size(); ++i)
      {
         resolved[i].trim();
         if (resolved[i].has_character() && !resolved[i].begins("??"))
            lines[frameIndices[i]] = resolved[i];
      }
   }
   return lines;
}
#endif


//#define __USE_BFD


#if defined(__APPLE__)
#define DISABLE_BACKTRACE 0

void apple_backtrace_symbol_parse(string & strSymbolName, string & strAddress, char_pointer pmessage, void * address);

#elif defined(FREEBSD)
#define DISABLE_BACKTRACE 0
void freebsd_backtrace_symbol_parse(::particle * pparticle, string & strSymbolName, string & strModule, string & strAddress, char_pointer pmessage, void * address);

#elif defined(__HAIKU__)
#define DISABLE_BACKTRACE 0

#elif defined(OPENBSD)
#define DISABLE_BACKTRACE 1
void openbsd_backtrace_symbol_parse(::particle * pparticle, string & strSymbolName, string & strModule, string & strAddress, char_pointer pmessage, void * address);

#else
#define DISABLE_BACKTRACE 0
void backtrace_symbol_parse(string &strSymbolName, string &strAddress, char_pointer pmessage, void *address);

#endif


#if !defined(__ANDROID__)

string _ansi_stack_trace(::particle * pparticle, void *const *ppui, ::i32 frames, const_char_pointer pszFormat, ::i32 iSkip, bool bWithinSignalHandler)
{

#if DISABLE_BACKTRACE

   return "";

#else

   ::string strCallstack;

#if defined(__HAIKU__)
   if (!ppui || frames <= 0) return strCallstack;
   for (::i32 i = maximum(iSkip, 0); i < frames; ++i)
   {
      if (!ppui[i]) break;
      Dl_info info = {};
      ::string symbol = "<unknown>";
      const bool resolved = ::dladdr(ppui[i], &info) != 0;
      if (resolved && info.dli_sname)
      {
         int status = -1;
         ::acme::malloc<char_pointer> demangled(
            abi::__cxa_demangle(info.dli_sname, nullptr, nullptr, &status));
         symbol = status == 0 && demangled.get() ? demangled.get() : info.dli_sname;
      }
      const auto offset = resolved && info.dli_saddr
         ? (uintptr_t)ppui[i] - (uintptr_t)info.dli_saddr : 0;
      ::string line;
      line.formatf("%02d : %p : %s + 0x%llx (%s)\n",
         frames - i - 1, ppui[i], symbol.c_str(), (unsigned long long)offset,
         resolved && info.dli_fname ? info.dli_fname : "<unknown module>");
      strCallstack += line;
   }
   return strCallstack;
#elif defined(__SUNOS__)
   // OpenIndiana's backtrace_symbols text does not use the Linux syntax
   // expected by backtrace_symbol_parse. Resolve the captured PCs directly.
   if (!ppui || frames <= 0)
   {
      return strCallstack;
   }

   bWithinSignalHandler = bWithinSignalHandler || call_stack_within_signal_handler();
   string_array_base sourceLines;
   if (!bWithinSignalHandler)
   {
      try { sourceLines = sunos_call_stack_source_lines(ppui, frames, maximum(iSkip, 0)); }
      catch (...) { /* Source lookup must never replace the original exception. */ }
   }

   for (::i32 i = maximum(iSkip, 0); i < frames; ++i)
   {
      if (!ppui[i])
      {
         break;
      }
      Dl_info info = {};
      ::string strLine;
      ::string strSymbolName = "<unknown>";
      if (::dladdr(ppui[i], &info))
      {
         if (info.dli_sname && *info.dli_sname)
         {
            int status = -1;
            ::acme::malloc<char_pointer> demangled(
               abi::__cxa_demangle(info.dli_sname, nullptr, nullptr, &status));
            strSymbolName = status == 0 && demangled.get()
               ? demangled.get() : info.dli_sname;
         }

         const auto moduleOffset = (uintptr_t)ppui[i] - (uintptr_t)info.dli_fbase;
         const auto symbolOffset = info.dli_saddr
            ? (uintptr_t)ppui[i] - (uintptr_t)info.dli_saddr : 0;
         strLine.formatf("%02d : %p : %s + 0x%llx (%s + 0x%llx)\n",
            frames - i - 1, ppui[i], strSymbolName.c_str(),
            (unsigned long long)symbolOffset,
            info.dli_fname ? info.dli_fname : "<unknown module>",
            (unsigned long long)moduleOffset);
      }
      else
      {
         strLine.formatf("%02d : %p : <unresolved>\n", frames - i - 1, ppui[i]);
      }
      strCallstack += strLine;
      if (!bWithinSignalHandler && i < sourceLines.size() && sourceLines[i].has_character())
         strCallstack += "    " + sourceLines[i] + "\n";
   }

   return strCallstack;
#else

   ::acme::malloc<char_pointer *> messages(::backtrace_symbols(ppui, frames));

   //::i8 szN[24];

   //*_strS = '\0';

   //::i8 syscom[1024];

   //const_char_pointer func;
   //const_char_pointer file;
   //::u32 iLine;

   auto ppMessages = messages.get();

   ::i32 i = 0;

   for (; i < frames && *ppMessages != nullptr; ++i, ppMessages++)
   {

      if(i < iSkip)
      {

         continue;

      }

      //printf("backtrace %s\n", *ppMessages);
#ifdef __USE_BFD

      if(resolve_addr_file_func_line(((void **)ppui)[i], &file, &func, iLine))
            {


               ansi_concatenate(_strS, file);
               ansi_concatenate(_strS, ":");
               ansi_from_u64(szN, iLine, 10);
               ansi_concatenate(_strS, szN);
               ansi_concatenate(_strS, ":1: warning: ");

            }
#endif // __USE_BFD

      auto pmessage = *ppMessages;




      //printf("%s", pmessage);

      string strSymbolName;

      string strAddress;

      string strLine;

#if defined(__APPLE__)
      
      apple_backtrace_symbol_parse(strSymbolName, strAddress, pmessage, ppui[i]);

      strLine.formatf("%02d : %s : %s\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str());

#elif defined(FREEBSD)

      string strModule;

      freebsd_backtrace_symbol_parse(pparticle, strSymbolName, strModule, strAddress, pmessage, ppui[i]);

      strLine.formatf("%02d : %s : %s (%s)\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str(), strModule.c_str());

#elif defined(OPENBSD)

      string strModule;

      openbsd_backtrace_symbol_parse(pparticle, strSymbolName, strModule, strAddress, pmessage, ppui[i]);

      strLine.formatf("%02d : %s : %s (%s)\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str(), strModule.c_str());

#else
      
      backtrace_symbol_parse(strSymbolName, strAddress, pmessage, ppui[i]);
      
      strLine.formatf("%02d : %s : %s\n", frames - i - 1, strAddress.c_str(), strSymbolName.c_str());

#endif

      strCallstack += strLine;

   }

   return strCallstack;

#endif // __SUNOS__

#endif

}


#endif


namespace platform
{


   void node::defer_update_call_stack()
   {


   }

#if !defined(__ANDROID__)

   void node::get_call_stack_frames(void ** stack, ::i32 & frame_count)
   {

#if DISABLE_BACKTRACE
      frame_count = 0;
#else

#if defined(FREEBSD) || defined(OPENBSD)
      const ::i32 iMaximumFramesToCapture = 32;
#else
      const ::i32 iMaximumFramesToCapture = 96;
#endif
      
      ::i32 iFrameCount = minimum(frame_count, iMaximumFramesToCapture);

#if defined(__HAIKU__)
      if (!stack || iFrameCount <= 0)
      {
         frame_count = 0;
         return;
      }
      haiku_call_stack_capture capture { stack, iFrameCount, 0 };
      ::_Unwind_Backtrace(haiku_call_stack_capture_frame, &capture);
      auto frames = capture.count;
#else
      auto frames = ::backtrace(stack, iFrameCount);
#endif
      
      frame_count = frames;
#endif

   }

#endif

   ::i32 node::get_call_stack_default_frame_count()
   {
      
   #if defined(FREEBSD) || defined(OPENBSD)
         const ::i32 iMaximumFramesToCapture = 32;
   #else
         const ::i32 iMaximumFramesToCapture = 96;
   #endif
      
      return iMaximumFramesToCapture;
      
   }


   string node::get_call_stack_trace(const ::scoped_string & scopedstrFormat, ::i32 iSkip, void * caller_address, ::i32 iCount)
   {
      
      return _get_call_stack_trace(scopedstrFormat, iSkip, caller_address, iCount);
      
   }


   string node::get_call_stack_trace(void ** stack, ::i32 frame_count, const ::scoped_string &scopedstrFormat, ::i32 iSkip, void *caller_address, ::i32 iCount)
   {

      return _get_call_stack_trace(stack, minimum_non_negative(frame_count, iCount), scopedstrFormat, iSkip, caller_address);

   }

#if !defined(ANDROID)


    critical_section g_criticalsectionCallStack;


    string node::_get_call_stack_trace(void ** stack, ::i32 frame_count, const ::scoped_string & strFormat, ::i32 iSkip, void *caller_address, ::i32 iCount)
    {

       //auto psynchronization = ::system()->synchronization();

       //_synchronous_lock sl(psynchronization, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

       critical_section_lock criticalsectionlock(&g_criticalsectionCallStack);

#if defined(FREEBSD) || defined(OPENBSD)
       const ::i32 iMaximumFramesToCapture = 32;
#else
       const ::i32 iMaximumFramesToCapture = 96;
#endif

       string str = _ansi_stack_trace(this, stack, minimum_non_negative(frame_count, iMaximumFramesToCapture), strFormat, maximum(iSkip, 0), call_stack_within_signal_handler());

       return str;

    }



#endif

} // namespace acme



#endif
