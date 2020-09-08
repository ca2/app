#include "framework.h"


namespace aqua
{


#ifdef WINDOWS


   CLASS_DECL_AQUA i32 get_errno()
   {
      i32 nErrNo;
      C_RUNTIME_ERROR_CHECK(::_get_errno(&nErrNo));
      return nErrNo;
   }

   CLASS_DECL_AQUA void set_errno(i32 _Value)
   {
      C_RUNTIME_ERROR_CHECK(::_set_errno(_Value));
   }


#else


   CLASS_DECL_AQUA i32 get_errno()
   {
      return errno;
   }

   CLASS_DECL_AQUA void set_errno(i32 _Value)
   {
      errno = _Value;
   }


#endif


} // namespace aqua




