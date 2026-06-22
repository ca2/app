#pragma once


//CLASS_DECL_ACME void os_shell_initialize();


//#include "acme/node/ansios/ansios.h"


//string get_error_message(::u32 dwError);

//::platform::application* win_instantiate_application(::platform::application* pappSystem, const ::scoped_string & scopedstrId);


#include "android1.h"
#include "implementation.h"
#include "factory_exchange.h"
#include "thread.h"
#include "acme/operating_system/window.h"
//#include "os_context.h"

//#include "directory_system.h"
//#include "file_system.h"

//#include "directory_context.h"
//#include "file_context.h"

//#define ANDROID_THREAD(pthread) (dynamic_cast < ::android::thread * > (dynamic_cast < ::thread * >(pthread)))

//#include "shell.h"

//#include "host_interaction.h"

//CLASS_DECL_ACME void __trace_message(const_char_pointer pszPrefix, ::message::message * pmessage);
//CLASS_DECL_ACME void __trace_message(const_char_pointer pszPrefix, MESSAGE * lpmsg);

CLASS_DECL_ACME void __cdecl __pre_translate_message(::message::message* pmessage);


#include "application.h"



::i32_bool PeekMessage(
   MESSAGE * lpMsg,
   const ::operating_system::window & operatingsystemwindow,
   ::u32 wMsgFilterMin,
   ::u32 wMsgFilterMax,
   ::u32 wRemoveMsg);

::i32_bool GetMessage(
   MESSAGE * lpMsg,
   const ::operating_system::window & operatingsystemwindow,
   ::u32 wMsgFilterMin,
   ::u32 wMsgFilterMax);



::i32 CLASS_DECL_ACME __android_main(::i32 argc, char_pointer argv[]);


CLASS_DECL_ACME void vfxThrowFileException(::particle * pparticle, const ::e_status & estatus, ::i32 lOsError, const_char_pointer pszFileName = nullptr);


#include "internal.h"



