#include "framework.h"





CLASS_DECL_ACME DWORD get_last_error()
{

   return GetLastError();

}


CLASS_DECL_ACME void set_last_error(DWORD dw)
{

   SetLastError(dw);

}





