#pragma once


CLASS_DECL_AURA void os_shell_initialize();


//#include "aura/node/ansios/ansios.h"


string get_error_message(::u32 dwError);

::aura::application* win_instantiate_application(::aura::application* pappSystem, const ::string & pszId);


#include "buffer.h"
#include "window_android.h"
//#include "factory_exchange.h"
//#include "thread.h"
//#include "os_context.h"

//#include "dir_system.h"
//#include "file_system.h"

//#include "dir_context.h"
//#include "file_context.h"

//#define ANDROID_THREAD(pthread) (dynamic_cast < ::android::thread * > (dynamic_cast < ::thread * >(pthread)))

//#include "shell.h"

//s#include "host_interaction.h"

//CLASS_DECL_AURA void __trace_message(const ::string & lpszPrefix, ::message::message * pmessage);
//CLASS_DECL_AURA void __trace_message(const ::string & lpszPrefix, MESSAGE * lpmsg);

//CLASS_DECL_AURA void __cdecl __pre_translate_message(::message::message* pmessage);


#include "application.h"

//
//
//int_bool PeekMessage(
//   MESSAGE * lpMsg,
//   oswindow hWnd,
//   ::u32 wMsgFilterMin,
//   ::u32 wMsgFilterMax,
//   ::u32 wRemoveMsg);
//
//int_bool GetMessage(
//   MESSAGE * lpMsg,
//   oswindow hWnd,
//   ::u32 wMsgFilterMin,
//   ::u32 wMsgFilterMax);



i32 CLASS_DECL_AURA __android_main(i32 argc, char* argv[]);


//CLASS_DECL_AURA void vfxThrowFileException(::object* pobject, const ::e_status & estatus, ::i32 lOsError, const ::string & lpszFileName = nullptr);


//#include "internal.h"


//#include "interaction_impl.h"



