// Created by camilo on 2022-11-03 17:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "last_error_exception.h"


#include "acme/_operating_system.h"


last_error_exception::last_error_exception(DWORD dwLastError, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails) :
   exception(error_win32, pszMessage, pszDetails)
{

   m_errorcodea.add(::windows::last_error_error_code(dwLastError));

}


namespace windows
{


   CLASS_DECL_ACME void throw_last_error(DWORD dwLastError)
   {

      throw ::last_error_exception(dwLastError);

   }


   CLASS_DECL_ACME void throw_last_error()
   {

      auto dwLastError = ::GetLastError();

      throw_last_error(dwLastError);

   }


} // namespace windows



