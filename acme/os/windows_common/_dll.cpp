#include "framework.h"
#include "_c.h"

#ifdef _UWP

#include <Psapi.h>

#endif


#include "framework.h"


WCHAR* wrap_dup_w(const WCHAR* pwsz, const WCHAR* pwszPrefix = nullptr, const WCHAR* pwszSuffix = nullptr)
{

   auto len = wcslen(pwsz);

   if (!len)
   {

      return wcsdup(L"");

   }

   auto prefix_len = ::is_set(pwszPrefix) ? wcslen(pwszPrefix) : 0;

   auto suffix_len = ::is_set(pwszSuffix) ? wcslen(pwszSuffix) : 0;

   auto buffer_len = len + prefix_len + suffix_len;

   WCHAR* pwszResult = (WCHAR*)malloc((buffer_len + 1) * sizeof(WCHAR));

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


WCHAR* module_debug_wcsdup(HINSTANCE hinstance, WCHAR* pwszPrefix = nullptr, WCHAR* pwszSuffix = nullptr)
{

   auto prefix_len = ::is_set(pwszPrefix) ? wcslen(pwszPrefix) : 0;

   auto suffix_len = ::is_set(pwszSuffix) ? wcslen(pwszSuffix) : 0;

   auto module_len = MAX_PATH * 4;

   auto buffer_len = module_len * 2 + prefix_len + suffix_len + 16;

   WCHAR* pwsz = (WCHAR*)malloc((buffer_len + 1) * sizeof(WCHAR));

   try
   {

      pwsz[0] = L'\'';

      ::GetModuleFileNameW(hinstance, pwsz + 1, module_len);

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

      ::GetModuleFileNameW(hinstance, &pwsz[wcslen(pwsz)], (::u32)module_len);

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


void module_debug_box_w(::i32 iFlags, HINSTANCE hinstance, WCHAR* pwszCaption, WCHAR* pwszSuffix = nullptr)
{

   WCHAR* pwsz = nullptr;

   WCHAR* pwszPrefix = wrap_dup_w(pwszCaption, L"\n\n", L"\n\n");

   try
   {

      auto pwsz = module_debug_wcsdup(hinstance, pwszPrefix, pwszSuffix);

      try
      {

         os_message_box(string(pwsz), string(pwszCaption), iFlags);
         //FUNCTION_DEBUGBOXW(pwsz, pwszCaption, iFlags);

      }
      catch (...)
      {

      }

      ::free(pwsz);

   }
   catch (...)
   {

   }

   ::free(pwszPrefix);

}


void module_output_debug_string_w(HINSTANCE hinstance, WCHAR* pwszPrefix = nullptr, WCHAR* pwszSuffix = nullptr)
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


#ifdef _UWP
[MTAThread]
#endif
int_bool CLASS_DECL_ACME _001DefaultDllMain(HINSTANCE hinstance, ::u32 dwReason, LPVOID pReserved, int iLibMainDebugBox, const lib_main_int& intDelayMs)
{

   UNREFERENCED_PARAMETER(pReserved);

   if (iLibMainDebugBox & lib_main_any)
   {

      module_debug_box_w(MB_ICONINFORMATION, hinstance, L"_001DefaultDllMain");

   }

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      if (iLibMainDebugBox & lib_main_process_attach)
      {

         module_debug_box_w(MB_ICONINFORMATION, hinstance, L"_001DefaultDllMain process attach");

      }
      else if (intDelayMs.m_millisProcessAttach.m_iMilliseconds)
      {

         ::sleep(intDelayMs.m_millisProcessAttach);

      }

   }

   if (dwReason == DLL_PROCESS_DETACH)
   {

      if (iLibMainDebugBox & lib_main_process_detach)
      {

         module_debug_box_w(MB_ICONINFORMATION, hinstance, L"_001DefaultDllMain process detach");

      }
      else if (intDelayMs.m_millisProcessDetach.m_iMilliseconds)
      {

         ::sleep(intDelayMs.m_millisProcessDetach);

      }

   }

   if (dwReason == DLL_THREAD_ATTACH)
   {

      if (iLibMainDebugBox & lib_main_thread_attach)
      {

         module_debug_box_w(MB_ICONINFORMATION, hinstance, L"_001DefaultDllMain thread attach");

      }
      else if (intDelayMs.m_millisThreadAttach.m_iMilliseconds)
      {

         ::sleep(intDelayMs.m_millisThreadAttach);

      }

   }

   if (dwReason == DLL_THREAD_DETACH)
   {

      if (iLibMainDebugBox & lib_main_thread_detach)
      {

         module_debug_box_w(MB_ICONINFORMATION, hinstance, L"_001DefaultDllMain thread detach");

      }
      else if (intDelayMs.m_millisThreadDetach.m_iMilliseconds)
      {

         ::sleep(intDelayMs.m_millisThreadDetach);

      }

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



