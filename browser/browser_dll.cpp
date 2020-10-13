#include "framework.h"


#ifndef CUBE


#ifdef _UWP
[MTAThread]
#endif
int_bool WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{

   return _001DefaultDllMain(hInstance, dwReason, lpReserved);

}


#endif



