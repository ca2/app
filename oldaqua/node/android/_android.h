#pragma once


CLASS_DECL_AQUA::estatus os_shell_initialize();


//#include "aqua/node/ansios/ansios.h"


string get_error_message(DWORD dwError);

::aqua::application* win_instantiate_application(::aqua::application* pappSystem, const char* pszId);


#include "android1.h"
#include "implementation.h"
#include "factory_exchange.h"
#include "thread.h"
#include "os_context.h"

#include "dir_system.h"
#include "file_system.h"

#include "dir_context.h"
#include "file_context.h"

//#define ANDROID_THREAD(pthread) (dynamic_cast < ::android::thread * > (dynamic_cast < ::thread * >(pthread)))

#include "shell.h"

#include "host_interaction.h"

//CLASS_DECL_AQUA void __trace_message(const char * lpszPrefix, ::message::message * pmessage);
//CLASS_DECL_AQUA void __trace_message(const char * lpszPrefix, LPMESSAGE lpmsg);

CLASS_DECL_AQUA void __cdecl __pre_translate_message(::message::message* pmessage);


#include "application.h"



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



i32 CLASS_DECL_AQUA __android_main(i32 argc, char* argv[]);


CLASS_DECL_AQUA void vfxThrowFileException(::object* pobject, const ::estatus& estatus, LONG lOsError, const char* lpszFileName = nullptr);


#include "internal.h"


#include "interaction_impl.h"




