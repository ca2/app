#pragma once


#ifndef CUBE


#ifdef WINDOWS


#include "aura/os/windows_common/_c.h"


#ifndef LIB_MAIN_DEBUG_BOX

#define LIB_MAIN_DEBUG_BOX lib_main_none

#endif


#ifndef LIB_MAIN_INT_DELAY_MS

#define LIB_MAIN_INT_DELAY_MS {}

#endif


#ifdef _UWP
[MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hinstance, ::u32 dwReason, LPVOID pReserved)
{

   return _001DefaultDllMain(hinstance, dwReason, pReserved, LIB_MAIN_DEBUG_BOX, LIB_MAIN_INT_DELAY_MS);

}


#endif


#endif


#if !defined(__APPLE__)


//#if !defined(CUBE)


#include "acme/asset/new.cpp"


//#endif


#endif



