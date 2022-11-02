// Created by camilo on 2022-09-26 18:33 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/primitive/string/string.h"
#include "debug.h"


namespace windows
{


   CLASS_DECL_ACME string last_error_message()
   {

      DWORD dwLastError = ::GetLastError();

      return last_error_message(dwLastError);

   }


   CLASS_DECL_ACME string last_error_message(::u32 dwError)
   {

      wchar_t * pszError;

      FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (LPWSTR)&pszError, 0, nullptr);

      string strError(pszError);

      ::LocalFree(pszError);

      return strError;

   }


} // namespace windows



