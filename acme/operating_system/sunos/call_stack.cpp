#include "platform.h"
#include "acme/operating_system/ansi/call_stack.h"
#include "acme/exception/call_stack.h"

#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ucontext.h>


namespace
{

   struct stack_capture
   {

      void ** m_stack;
      ::i32   m_capacity;
      ::i32   m_count;

   };


   int capture_stack_frame(uintptr_t program_counter, int signal_number, void * user_data)
   {

      (void)signal_number;

      auto pstackcapture = static_cast < stack_capture * > (user_data);

      if (pstackcapture->m_count >= pstackcapture->m_capacity)
      {

         return 1;

      }

      pstackcapture->m_stack[pstackcapture->m_count++] = reinterpret_cast < void * > (program_counter);

      return 0;

   }


   ::i32 capture_stack(void ** stack, ::i32 capacity)
   {

      ucontext_t context = {};

      if (::getcontext(&context) != 0)
      {

         return 0;

      }

      stack_capture stackcapture{ stack, capacity, 0 };

      ::walkcontext(&context, &capture_stack_frame, &stackcapture);

      return stackcapture.m_count;

   }

}


void call_stack::capture(::i32 iSkip, void * caller_address, ::i32 iCount)
{

   ::free((void *)m_pszCallStack);
   m_pszCallStack = nullptr;
   m_caller_address = caller_address;
   m_u32Hash = 0;
   m_iCount = 0;

   if (iCount == 0)
   {

      return;

   }

   auto frames = capture_stack(m_stack, TRACE_MAX_STACK_FRAMES);
   // getcontext() captures this helper and its caller, so skip both internal frames by default.
   auto internalFrames = frames < 2 ? frames : 2;
   auto skip = iSkip < 0 ? internalFrames : (iSkip >= frames - internalFrames ? frames : iSkip + internalFrames);
   // A supplied caller address selects the start when present in this stack.
   if (caller_address)
   {

      for (int i = skip; i < frames; ++i)
      {

         if (m_stack[i] == caller_address)
         {

            skip = i;
            break;

         }

      }

   }

   auto count = frames - skip;
   if (iCount >= 0 && count > iCount)
   {

      count = iCount;

   }

   for (int i = 0; i < count; ++i)
   {

      m_stack[i] = m_stack[i + skip];
      auto address = (uintptr_t)m_stack[i];
      // Fold every byte so the hash includes all bits of a 64-bit program counter.
      for (size_t byte = 0; byte < sizeof(address); ++byte)
      {

         m_u32Hash = m_u32Hash * 33 + (address & 0xff);
         address >>= 8;

      }

   }

   m_iCount = count;

}


::i32 call_stack::_prepare_trace(const_char_pointer pszFormat)
{

   // Match the Windows backend's module + offset representation.
   ::i32 size = 64;
   for (::i32 i = 0; i < m_iCount; ++i)
   {

      Dl_info info = {};
      const char * path = "(unknown)";
      m_modulea[i] = nullptr;
      if (::dladdr(m_stack[i], &info))
      {

         m_modulea[i] = info.dli_fbase;
         if (info.dli_fname && *info.dli_fname)
         {

            path = info.dli_fname;

         }

      }

      ::snprintf(m_szaModulePath[i], MODULE_BUF_SIZE, "%s", path);
      m_u32ModulePathLength[i] = ::strlen(m_szaModulePath[i]);
      size += m_u32ModulePathLength[i] + 64;

   }

   return size;

}


const_char_pointer call_stack::_trace(::i32 iSize, const_char_pointer pszFormat)
{

   if (iSize <= 0)
   {

      return nullptr;

   }

   auto trace = (char *)::malloc(iSize);
   if (!trace)
   {

      return nullptr;

   }

   trace[0] = '\0';
   auto written = ::snprintf(trace, iSize, "Stack hash: 0x%08x\n", (unsigned int)m_u32Hash);
   size_t used = written < 0 ? 0 : (size_t)written;
   for (::i32 i = 0; i < m_iCount && used < (size_t)iSize; ++i)
   {

      auto offset = (uintptr_t)m_stack[i] - (uintptr_t)m_modulea[i];
      written = ::snprintf(trace + used, iSize - used, "%02d:%s+0x%016llx\n",
         i, m_szaModulePath[i], (unsigned long long)offset);
      if (written < 0)
      {

         break;

      }

      used += (size_t)written;

   }

   return trace;

}


string get_callstack(::particle * pparticle, const_char_pointer pszFormat, ::i32 iSkip, void * caller_address, ::i32 iCount)
{

   void * stack[64];
   auto frames = capture_stack(stack, 64);

   return _ansi_stack_trace(pparticle, stack, frames, pszFormat, iSkip);

}
