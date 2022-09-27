// Created by camilo on 2022-09-26 18:33 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "_api.h"


::string get_command_line()
{

   return ::GetCommandLineW();

}


namespace windows
{


   CLASS_DECL_ACME string get_last_error_string()
   {

      DWORD dwLastError = ::GetLastError();

      return get_error_string(dwLastError);

   }


   CLASS_DECL_ACME string get_error_string(DWORD dwError)
   {

      wchar_t * pszError;

      FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, dwError, 0, (LPWSTR)&pszError, 0, nullptr);

      string strError(pszError);

      ::LocalFree(pszError);

      return strError;

   }


} // namespace windows



