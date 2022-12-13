#include "framework.h"
#include "acme/platform/acme.h"


#include "acme/operating_system/ansi/_pthread.h"
#undef USE_MISC



//#include <stdbool.h
#include <sys/ptrace.h>
#include <sys/wait.h>


int gdb_check();


class ::time g_timeLastDebuggerAttachedCheck;
::i32 g_iLastIsDebuggerAttached;
::i32 g_iLastIsDebuggerAttachedOptimizedCount;


namespace acme
{


   extern class acme * g_p;


} // namespace acme


i32 __node_is_debugger_attached()
{

   critical_section_lock lock(::acme::g_p->globals_critical_section());

   if(g_timeLastDebuggerAttachedCheck.elapsed() > 300_ms)
   {

      g_iLastIsDebuggerAttached = gdb_check();

      g_timeLastDebuggerAttachedCheck.elapsed();

   }
   else
   {

      printf("\nOptimized times %d", g_iLastIsDebuggerAttachedOptimizedCount++);

   }

   return g_iLastIsDebuggerAttached;


}



#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

// https://stackoverflow.com/questions/3596781/how-to-detect-if-the-current-process-is-being-run-by-gdb
// https://stackoverflow.com/users/63550/peter-mortensen
// https://stackoverflow.com/users/75501/sam-liao

int gdb_check()
{
   char buf[4096];

   const int status_fd = ::open("/proc/self/status", O_RDONLY);
   if (status_fd == -1)
      return false;

   const ssize_t num_read = ::read(status_fd, buf, sizeof(buf) - 1);
   ::close(status_fd);

   if (num_read <= 0)
      return false;

   buf[num_read] = '\0';
   constexpr char tracerPidString[] = "TracerPid:";
   const auto tracer_pid_ptr = ::strstr(buf, tracerPidString);
   if (!tracer_pid_ptr)
      return false;

   for (const char* characterPtr = tracer_pid_ptr + sizeof(tracerPidString) - 1; characterPtr <= buf + num_read; ++characterPtr)
   {
      if (::character_isspace(*characterPtr))
         continue;
      else
      {
         int iDebuggerAttached = ::isdigit(*characterPtr) != 0 && *characterPtr != '0';

         return iDebuggerAttached;
      }
   }

   return false;
}


/*
i32 gdb_check()
{
  i32 pid = fork();
  i32 status;
  i32 res;

  if (pid == -1)
    {
      perror("fork");
      return -1;
    }

  if (pid == 0)
    {
      i32 ppid = getppid();

      // Child
      if (ptrace(PTRACE_ATTACH, ppid, nullptr, nullptr) == 0)
        {
          // Wait for the parent to stop and continue it
          waitpid(ppid, nullptr, 0);
          ptrace(PTRACE_CONT, nullptr, nullptr);

          // Detach
          ptrace(PTRACE_DETACH, getppid(), nullptr, nullptr);

          // We were the tracers, so gdb is not present
          res = 0;
        }
      else
        {
  // Trace failed so gdb is present
          res = 1;
        }
      exit(res);
    }
  else
    {
      waitpid(pid, &status, 0);
      res = WEXITSTATUS(status);
    }
  return res;
}
*/

//
//
//static void*
//test_trace(void* ignored)
//{
//   return (void*)ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
//}
//
//i32
//gdb_check(void)
//{
//
//   pthread_attr_t attr;
//   void* result;
//   pthread_t thread;
//
//   pthread_attr_init(&attr);
//   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
//   if (pthread_create(&thread, &attr, test_trace, nullptr) != 0)
//   {
//      pthread_attr_destroy(&attr);
//      return false;
//   }
//   pthread_attr_destroy(&attr);
//   if (pthread_join(thread, &result) != 0)
//   {
//      return false;
//   }
//
//   return result != nullptr;
//}
//
//
//
////
////  macos_debug.cpp
////  acme
////
////  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2013-09-17.
////
////
//
////
////  macos_debug.cpp
////  ca
////
////  Created by Lion User on 26/05/2012.
////  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
////
//







//::u32
//WINAPI
//FormatMessage(
//::u32 dwFlags,
//const void * pSource,
//
//::u32 dwMessageId,
//::u32 dwLanguageId,
//char * pBuffer,
//
//::u32 nSize,
//va_list *Arguments
//)
//{
//
//
//   return 0;
//
//
//}


void output_debug_string(const char * pOutputString)
{

   if(::acme::g_p->m_bOutputDebugString)
   {

      if(strstr(pOutputString, "font_list"))
      {

         printf("a");

      }

      printf("%s", pOutputString);

      fflush(stdout);

   }

}


void output_debug_string(const ::wide_character * pOutputString)
{

   if(::acme::g_p->m_bOutputDebugString)
   {

      output_debug_string(string(pOutputString));

   }

}


////CLASS_DECL_BASE extern fixed_alloc_array * g_pfixedallocaWstring;
//
////CLASS_DECL_BASE fixed_alloc_array * new_wstring_manager();
//
//void CLASS_DECL_ACME __cdecl _ca2_purecall()
//{
//    throw ::exception(::exception());
//}


//void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers);
//
//
//
//void __cdecl _null_se_translator(u32 uiCode, EXCEPTION_POINTERS * ppointers)
//{
//   __UNREFERENCED_PARAMETER(uiCode);
//   __UNREFERENCED_PARAMETER(ppointers);
//}
