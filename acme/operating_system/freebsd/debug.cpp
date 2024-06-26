#include "framework.h"
//#include "acme/platform/static_start.h"
//#include "acme/platform/static_start_internal.h"
#include "acme/platform/acme.h"

#include "acme/operating_system/ansi/_pthread.h"
#undef USE_MISC



//#include <stdbool.h
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>

int gdb_check();


i32 __node_is_debugger_attached()
{

   return gdb_check();

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

static void*
test_trace(void* ignored)
{
#ifdef FREEBSD
   // This is a guess
   return (void *)(iptr)(int)ptrace(PT_TRACE_ME, 0, nullptr, 0);
#else
   return (void*)ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);
#endif
}


i32
gdb_check(void)
{

   pthread_attr_t attr;
   void* result;
   pthread_t thread;

   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   if (pthread_create(&thread, &attr, test_trace, nullptr) != 0)
   {
      pthread_attr_destroy(&attr);
      return false;
   }
   pthread_attr_destroy(&attr);
   if (pthread_join(thread, &result) != 0)
   {
      return false;
   }

   return result != nullptr;
}



//
//  macos_debug.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2013-09-17.
//
//

//
//  macos_debug.cpp
//  ca
//
//  Created by Lion User on 26/05/2012.
//  Copyright (c) 2012 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
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


void output_debug_string(const scoped_string & scopedstrFormat)
{

   //if(::acme::g_bOutputDebugString)
   {

//      if(scopedstrFormat == "font_list")
//      {
//
//         output_debug_string("a");
//
//      }

      auto pszBegin = scopedstrFormat.m_begin;

      auto pszEnd = scopedstrFormat.m_end;

      fwrite(pszBegin, 1, scopedstrFormat.size(), stdout);

      //fflush(stdout);

   }

}


void output_debug_string(const ::wide_character * pOutputString)
{

   //if(::acme::g_bOutputDebugString)
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



void output_debug_string_flush()
{

   if (::platform::get()->m_bOutputDebugString)
   {

      fflush(stdout);

   }

}




