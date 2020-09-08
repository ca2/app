#include "framework.h"





CLASS_DECL_AQUA DWORD get_last_error()
{

   return GetLastError();

}


CLASS_DECL_AQUA void set_last_error(DWORD dw)
{

   SetLastError(dw);

}





