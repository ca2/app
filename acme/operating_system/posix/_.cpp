// Created by camilo on 2023-03-16 20:08 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/operating_system/shared_posix/c_errno.h"


#if defined(FREEBSD) || defined(OPENBSD)
#include <string.h>
#endif


[[noreturn]] CLASS_DECL_ACME void throw_errno_exception(const ::scoped_string & scopedstr, c_errno cerrno)
{

   if (cerrno == 0)
   {

      cerrno.set_last_errno_status();

   } 

   auto estatus = cerrno.estatus();

   auto errorcode = cerrno.error_code();

   throw ::exception(estatus, { errorcode }, scopedstr);

}
