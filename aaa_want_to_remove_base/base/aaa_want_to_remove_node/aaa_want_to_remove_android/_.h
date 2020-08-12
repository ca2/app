#pragma once


#include "aura/node/android/_.h"


string get_error_message(DWORD dwError);

::aura::application *     win_instantiate_application(::aura::application * pappSystem, const char * pszId);

#include "android1.h"
#include "android_implementation.h"
#include "android_factory_exchange.h"


CLASS_DECL_BASE void __cdecl __pre_translate_message(::message::message * pmessage);



WINBOOL PeekMessage(
LPMESSAGE lpMsg,
oswindow hWnd,
UINT wMsgFilterMin,
UINT wMsgFilterMax,
UINT wRemoveMsg);

WINBOOL GetMessage(
LPMESSAGE lpMsg,
oswindow hWnd,
UINT wMsgFilterMin,
UINT wMsgFilterMax);



i32 CLASS_DECL_BASE __android_main(i32 argc, char * argv[]);


//CLASS_DECL_BASE void vfxThrowFileException(::object * pobject, i32 cause, LONG lOsError, const char * lpszFileName = nullptr);


//#include "android_internal.h"




