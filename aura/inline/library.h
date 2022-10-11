#pragma once


#include "acme/operating_system.h"


#ifndef CUBE


#ifdef WINDOWS


#include "aura/operating_system/windows_common/_c.h"


#ifndef LIBRARY_MAIN_DEBUG_BOX

#define LIBRARY_MAIN_DEBUG_BOX e_library_main_none

#endif


#ifndef LIBRARY_MAIN_INT_DELAY_MS

#define LIBRARY_MAIN_INT_DELAY_MS {}

#endif


//#ifdef _UWP
//[MTAThread]
//#endif


BOOL WINAPI DllMain(HINSTANCE hinstance, ::u32 dwReason, LPVOID pReserved)
{

   return _001DefaultDllMain(hinstance, dwReason, pReserved, LIBRARY_MAIN_DEBUG_BOX, LIBRARY_MAIN_INT_DELAY_MS);

}


#endif


#endif


#if !defined(__APPLE__)


#if !defined(CUBE)


#include "acme/asset/new.cpp"


#endif


#endif



