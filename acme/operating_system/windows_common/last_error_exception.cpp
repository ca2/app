// Created by camilo on 2022-11-03 17:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "last_error_exception.h"


#include "acme/_operating_system.h"


namespace windows
{

    last_error_exception::last_error_exception(const last_error & lasterror, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrDetails) :
       exception(error_win32, scopedstrMessage, scopedstrDetails)
    {

       m_errorcodea.add(::windows::last_error_error_code(lasterror));

    }


   CLASS_DECL_ACME void throw_last_error_exception(const last_error & lasterror)
   {

      throw last_error_exception(lasterror);

   }


   CLASS_DECL_ACME void throw_last_error_exception()
   {

      auto lasterror = ::windows::get_last_error();

      throw_last_error_exception(lasterror);

   }


} // namespace windows



