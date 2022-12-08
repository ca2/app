

#ifndef _WINDOWS_

#include "acme/_operating_system.h"

#endif


#ifndef CUBE


#ifdef WINDOWS


//#ifndef LIBRARY_MAIN_DEBUG_BOX
//
//#define LIBRARY_MAIN_DEBUG_BOX e_library_main_none
//
//#endif

//
//#ifndef LIBRARY_MAIN_INT_DELAY_MS
//
//#define LIBRARY_MAIN_INT_DELAY_MS {}
//
//#endif


int_bool CLASS_DECL_ACME _001DefaultDllMain(hinstance hinstance, ::u32 dwReason, LPVOID pReserved);


BOOL WINAPI DllMain(HINSTANCE hinstance, ::u32 dwReason, LPVOID pReserved)
{

   //return _001DefaultDllMain(hinstance, dwReason, pReserved, LIBRARY_MAIN_DEBUG_BOX, LIBRARY_MAIN_INT_DELAY_MS);
   return _001DefaultDllMain(hinstance, dwReason, pReserved);

}


#endif


#endif


#if !defined(__APPLE__)


#if !defined(CUBE)


#include "acme/memory/_new.inl"


#endif


#endif



