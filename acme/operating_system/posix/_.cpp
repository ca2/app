// Created by camilo on 2023-03-16 20:08 <3ThomasBorregaardSorensen!!
#include "framework.h"


[[noreturn]] CLASS_DECL_ACME void throw_errno_exception(const ::scoped_string & scopedstr, int iErrNo)
{

   if (iErrNo == 0)
   {

      iErrNo = errno;

   } 

   auto estatus = errno_status(iErrNo);

   auto errorcode = errno_error_code(iErrNo);

   throw ::exception(estatus, { errorcode }, scopedstr);

}



