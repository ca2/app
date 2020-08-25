#include "framework.h"





CLASS_DECL_AURA DWORD get_last_error()
{

   return GetLastError();

}


CLASS_DECL_AURA void set_last_error(DWORD dw)
{

   SetLastError(dw);

}





