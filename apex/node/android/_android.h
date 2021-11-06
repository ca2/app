#pragma once


CLASS_DECL_APEX::e_status os_shell_initialize();


//#include "apex/node/ansios/ansios.h"


string get_error_message(::u32 dwError);

::application* win_instantiate_application(::application* pappSystem, const char* pszId);


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

//#include "shell.h"

//#include "host_interaction.h"

//CLASS_DECL_APEX void __trace_message(const char * lpszPrefix, ::message::message * pmessage);
//CLASS_DECL_APEX void __trace_message(const char * lpszPrefix, MESSAGE * lpmsg);

CLASS_DECL_APEX void __cdecl __pre_translate_message(::message::message* pmessage);


#include "application.h"



int_bool PeekMessage(
   MESSAGE * lpMsg,
   oswindow hWnd,
   ::u32 wMsgFilterMin,
   ::u32 wMsgFilterMax,
   ::u32 wRemoveMsg);

int_bool GetMessage(
   MESSAGE * lpMsg,
   oswindow hWnd,
   ::u32 wMsgFilterMin,
   ::u32 wMsgFilterMax);



i32 CLASS_DECL_APEX __android_main(i32 argc, char* argv[]);


CLASS_DECL_APEX void vfxThrowFileException(::object* pobject, const ::e_status& estatus, ::i32 lOsError, const char* lpszFileName = nullptr);


#include "internal.h"



