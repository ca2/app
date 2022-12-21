#pragma once


CLASS_DECL_ACME void os_shell_initialize();


//#include "acme/node/ansios/ansios.h"


string get_error_message(::u32 dwError);

//::acme::application* win_instantiate_application(::acme::application* pappSystem, const ::scoped_string & scopedstrId);


#include "android1.h"
#include "implementation.h"
#include "factory_exchange.h"
#include "thread.h"
//#include "os_context.h"

//#include "dir_system.h"
//#include "file_system.h"

//#include "dir_context.h"
//#include "file_context.h"

//#define ANDROID_THREAD(pthread) (dynamic_cast < ::android::thread * > (dynamic_cast < ::thread * >(pthread)))

//#include "shell.h"

//#include "host_interaction.h"

//CLASS_DECL_ACME void __trace_message(const char * lpszPrefix, ::message::message * pmessage);
//CLASS_DECL_ACME void __trace_message(const char * lpszPrefix, MESSAGE * lpmsg);

CLASS_DECL_ACME void __cdecl __pre_translate_message(::message::message* pmessage);


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



i32 CLASS_DECL_ACME __android_main(i32 argc, char* argv[]);


CLASS_DECL_ACME void vfxThrowFileException(::particle * pparticle, const ::e_status & estatus, ::i32 lOsError, const char* lpszFileName = nullptr);


#include "internal.h"



