// Created by camilo on 2023-03-16 20:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/operating_system/shared_posix/c_error_number.h"


#ifdef FREEBSD
#include <string.h>
#endif


[[noreturn]] CLASS_DECL_ACME void throw_errno_exception(const ::scoped_string & scopedstr, c_error_number cerrornumber)
{

   if (cerrornumber == 0)
   {

      cerrornumber.set_last_errno_status();

   } 

   auto estatus = cerrornumber.estatus();

   auto errorcode = cerrornumber.error_code();

   throw ::exception(estatus, { errorcode }, scopedstr);

}


::string errno_error_message(::i32 iError)
{

   return strerror(iError);

}



