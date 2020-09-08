#include "framework.h"





CLASS_DECL_APEX DWORD get_last_error()
{

   return GetLastError();

}


CLASS_DECL_APEX void set_last_error(DWORD dw)
{

   SetLastError(dw);

}





