#include "framework.h"


#ifndef CUBE


#ifdef UNIVERSAL_WINDOWS
[MTAThread]
#endif
int_bool WINAPI DllMain(HINSTANCE hInstance, ::u32 dwReason, LPVOID lpReserved)
{

   return _001DefaultDllMain(hInstance, dwReason, lpReserved);

}


#endif



