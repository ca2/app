#include "framework.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/_operating_system.h"


#include "_c.h"

#ifdef _UWP

#include <Psapi.h>

#endif


#include "framework.h"


WCHAR * wrap_dup_w(const WCHAR * pwsz, const WCHAR * pwszPrefix = nullptr, const WCHAR * pwszSuffix = nullptr)
{

   auto len = wcslen(pwsz);

   if (!len)
   {

      return wcsdup(L"");

   }

   auto prefix_len = ::is_set(pwszPrefix) ? wcslen(pwszPrefix) : 0;

   auto suffix_len = ::is_set(pwszSuffix) ? wcslen(pwszSuffix) : 0;

   auto buffer_len = len + prefix_len + suffix_len;

   WCHAR * pwszResult = (WCHAR *)malloc((buffer_len + 1) * sizeof(WCHAR));

   pwszResult[0] = L'\0';

   if (prefix_len)
   {

      wcscat(pwszResult, pwszPrefix);

   }

   wcscat(pwszResult, pwsz);

   if (suffix_len)
   {

      wcscat(pwszResult, pwszSuffix);

   }

   return pwszResult;

}


WCHAR * module_debug_wcsdup(hinstance hinstance, const WCHAR * pwszPrefix = nullptr, const WCHAR * pwszSuffix = nullptr)
{

   auto prefix_len = ::is_set(pwszPrefix) ? wcslen(pwszPrefix) : 0;

   auto suffix_len = ::is_set(pwszSuffix) ? wcslen(pwszSuffix) : 0;

   auto module_len = MAX_PATH * 4;

   auto buffer_len = module_len * 2 + prefix_len + suffix_len + 16;

   WCHAR * pwsz = (WCHAR *)malloc((buffer_len + 1) * sizeof(WCHAR));

   try
   {

      pwsz[0] = L'\'';

      ::GetModuleFileNameW((HINSTANCE)hinstance, pwsz + 1, module_len);

      auto name = wcsrchr(pwsz, '\\');

      if (name)
      {

         memmove(pwsz + 1, name + 1, module_len * sizeof(WCHAR));

      }

      wcscat(pwsz, L"\'");

      if (prefix_len)
      {

         wcscat(pwsz, pwszPrefix);

      }
      else
      {

         wcscat(pwsz, L"");

      }

      wcscat(pwsz, L"\'");

      ::GetModuleFileNameW((HINSTANCE)hinstance, &pwsz[wcslen(pwsz)], (::u32)module_len);

      wcscat(pwsz, L"\'");

      if (suffix_len)
      {

         wcscat(pwsz, pwszSuffix);

      }

   }
   catch (...)
   {

   }

   return pwsz;

}


// void module_debug_box_w(const ::e_message_box & emessagebox, hinstance hinstance, const WCHAR * pwszCaption, WCHAR * pwszSuffix = nullptr)
// {

//    WCHAR * pwsz = nullptr;

//    WCHAR * pwszPrefix = wrap_dup_w(pwszCaption, L"\n\n", L"\n\n");

//    try
//    {

//       auto pwsz = module_debug_wcsdup(hinstance, pwszPrefix, pwszSuffix);

//       try
//       {

//          xxxshow_error_message(string(pwsz), string(pwszCaption), emessagebox);
//          //FUNCTION_DEBUGBOXW(pwsz, pwszCaption, iFlags);

//       }
//       catch (...)
//       {

//       }

//       ::free(pwsz);

//    }
//    catch (...)
//    {

//    }

//    ::free(pwszPrefix);

// }


void module_output_debug_string_w(hinstance hinstance, const WCHAR * pwszPrefix = nullptr, const WCHAR * pwszSuffix = nullptr)
{

   auto pwsz = module_debug_wcsdup(hinstance, pwszPrefix, pwszSuffix);

   try
   {

      ::OutputDebugStringW(pwsz);

   }
   catch (...)
   {

   }

   ::free(pwsz);

}



#ifndef CUBE


//CLASS_DECL_ACME void defer_initialize_callstack();


//#ifdef _UWP
//[MTAThread]
//#endif
//int_bool CLASS_DECL_ACME _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, LPVOID pReserved, int iLibMainDebugBox, const lib_main_int & intDelayMs)
//int_bool CLASS_DECL_ACME _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, LPVOID pReserved, int iLibMainDebugBox)
int_bool CLASS_DECL_ACME _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, LPVOID pReserved)
{

   __UNREFERENCED_PARAMETER(pReserved);

   //if (iLibMainDebugBox & e_library_main_any)
   //{

   //   //module_debug_box_w(e_message_box_icon_information, hinstance, L"_001DefaultDllMain");

   //}

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      auto psystem = ::get_system();

      if (psystem)
      {

         auto pnode = psystem->acmenode();

         if (pnode)
         {

            pnode->m_bUpdateCallstack = true;

            //pnode->defer_initialize_callstack();

         }

      }

      //if (iLibMainDebugBox & e_library_main_process_attach)
      //{

      //   //module_debug_box_w(e_message_box_icon_information, hinstance, L"_001DefaultDllMain process attach");

      //}
      //else
      //{

      //   auto millisecond = intDelayMs.m_timeProcessAttach.integral_millisecond();

      //   if (millisecond > 0_ms)
      //   {

      //      ::preempt(millisecond);

      //   }

      //}

   }

   if (dwReason == DLL_PROCESS_DETACH)
   {

      //if (iLibMainDebugBox & e_library_main_process_attach)
      //{

      //   //module_debug_box_w(e_message_box_icon_information, hinstance, L"_001DefaultDllMain process detach");

      //}
      //else
      //{

      //   auto millisecond = intDelayMs.m_timeProcessDetach.integral_millisecond();

      //   if (millisecond > 0_ms)
      //   {

      //      ::preempt(millisecond);

      //   }

      //}

   }

   if (dwReason == DLL_THREAD_ATTACH)
   {

      //if (iLibMainDebugBox & e_library_main_thread_attach)
      //{

      //   //module_debug_box_w(e_message_box_icon_information, hinstance, L"_001DefaultDllMain thread attach");

      //}
      //else
      //{

      //   auto millisecond = intDelayMs.m_timeThreadAttach.integral_millisecond();

      //   if (millisecond > 0_ms)
      //   {

      //      ::preempt(millisecond);

      //   }

      //}

   }

   if (dwReason == DLL_THREAD_DETACH)
   {

      //if (iLibMainDebugBox & e_library_main_thread_detach)
      //{

      //   //module_debug_box_w(e_message_box_icon_information, hinstance, L"_001DefaultDllMain thread detach");

      //}
      //else
      //{

      //   auto millisecond = intDelayMs.m_timeThreadDetach.integral_millisecond();

      //   if (millisecond > 0_ms)
      //   {

      //      ::preempt(millisecond);

      //   }

      //}

   }

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      module_output_debug_string_w(hinstance, L": initializing library ", L"\n");

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      module_output_debug_string_w(hinstance, L": finalizing library ", L"\n");

   }

   return 1;   // ok

}

#endif




