#include "platform.h"
//#include "acme/platform/static_start.h"
//#include "acme/platform/static_start_internal.h"
#include "acme/platform/acme.h"

#include "acme/operating_system/ansi/_pthread.h"
#undef USE_MISC



//#include <stdbool.h
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

::i32 gdb_check();


::i32 __node_is_debugger_attached()
{

   return gdb_check();

}



// Inspect tracing state without changing it. PT_TRACE_ME makes this process
// traced by its parent and can lead to SIGCHLD termination or an orphaned
// traced process when ordinary build commands create child processes.
::i32 gdb_check(void)
{
   struct kinfo_proc2 info = {};
   size_t size = sizeof(info);
   int mib[] = {CTL_KERN, KERN_PROC2, KERN_PROC_PID, (int)getpid(),
                (int)sizeof(info), 1};
   if (::sysctl(mib, 6, &info, &size, nullptr, 0) == -1 || size != sizeof(info))
      return false;

   return (info.p_flag & P_TRACED) != 0;
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
//char_pointer pBuffer,
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


// void output_debug_string(const scoped_string & scopedstrFormat)
// {

//    //if(::acme::g_bOutputDebugString)
//    {

//       if(scopedstrFormat == "font_list")
//       {

//          output_debug_string("a");

//       }

//       printf("%s", ::string(scopedstrFormat).c_str());

//       //fflush(stdout);

//    }

// }


// void output_debug_string(const ::wide_character * pOutputString)
// {

//    //if(::acme::g_bOutputDebugString)
//    {

//       output_debug_string(string(pOutputString));

//    }

// }


////CLASS_DECL_BERG extern fixed_alloc_array * g_pfixedallocaWstring;
//
////CLASS_DECL_BERG fixed_alloc_array * new_wstring_manager();
//
//void CLASS_DECL_ACME __cdecl _ca2_purecall()
//{
//    throw ::exception(::exception());
//}


//void __cdecl _null_se_translator(::u32 uiCode, EXCEPTION_POINTERS * ppointers);
//
//
//
//void __cdecl _null_se_translator(::u32 uiCode, EXCEPTION_POINTERS * ppointers)
//{
//   __UNREFERENCED_PARAMETER(uiCode);
//   __UNREFERENCED_PARAMETER(ppointers);
//}



// void output_debug_string_flush()
// {

//    if (::platform::get()->m_bOutputDebugString)
//    {

//       fflush(stdout);

//    }

// }




