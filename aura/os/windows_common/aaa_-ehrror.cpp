#include "framework.h"





CLASS_DECL_AURA ::u32 get_last_error()
{

   return GetLastError();

}


CLASS_DECL_AURA void set_last_error(::u32 dw)
{

   SetLastError(dw);

}





