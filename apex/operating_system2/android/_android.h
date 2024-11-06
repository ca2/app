#pragma once


//CLASS_DECL_APEX void os_shell_initialize();


//#include "apex/operating_system/ansios/ansios.h"


//string get_error_message(unsigned int dwError);

//::application* win_instantiate_application(::apex::application* pappSystem, const ::scoped_string & scopedstrId);


#include "android1.h"
#include "implementation.h"
#include "factory_exchange.h"
#include "thread.h"
//#include "os_context.h"

//#include "directory_system.h"
//#include "file_system.h"
//
//#include "directory_context.h"
//#include "file_context.h"

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
   unsigned int wMsgFilterMin,
   unsigned int wMsgFilterMax,
   unsigned int wRemoveMsg);

int_bool GetMessage(
   MESSAGE * lpMsg,
   oswindow hWnd,
   unsigned int wMsgFilterMin,
   unsigned int wMsgFilterMax);



int CLASS_DECL_APEX __android_main(int argc, char* argv[]);


CLASS_DECL_APEX void vfxThrowFileException(::object* pparticle, const ::e_status & estatus, int lOsError, const char* lpszFileName = nullptr);


#include "internal.h"



