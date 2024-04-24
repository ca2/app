#include "framework.h"
#include "acme/exception/runtime_check.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include <errno.h>


namespace acme
{


#ifdef WINDOWS


   CLASS_DECL_ACME i32 get_errno()
   {

      i32 nErrNo;

      errno_t iErrNo = ::_get_errno(&nErrNo);

      if (iErrNo)
      {

         throw ::runtime_check_exception(error_failed, { c_error_number(iErrNo) }, "get_errno (error getting error)");

      }

      return nErrNo;
   }


   CLASS_DECL_ACME void set_errno(i32 _Value)
   {

      errno_t iErrNo = ::_set_errno(_Value);

      if (iErrNo)
      {

         throw ::runtime_check_exception(error_failed, { c_error_number(iErrNo) }, "set_errno (error setting error)");

      }

   }


#else


   CLASS_DECL_ACME i32 get_errno()
   {

      return errno;

   }


   CLASS_DECL_ACME void set_errno(i32 _Value)
   {

      errno = _Value;

   }


#endif


} // namespace acme




