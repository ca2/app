#pragma once

#define SECURITY_WIN32

#undef User

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>


#include "exception.h"


//namespace universal_windows
//{
//
//   ref class directx_framework_impact;
//
//} // namespace universal_windows



//string get_error_message(unsigned int dwError);


/////////////////////////////////////////////////////////////////////////////
// Global implementation helpers

// window creation hooking
//CLASS_DECL_ACME void hook_window_create(::user::interaction * pWnd);
//CLASS_DECL_ACME bool unhook_window_create();
//CLASS_DECL_ACME void reset_message_cache();


//#include "command.h"
//#include "implementation.h"
//#include "_UWP_folder_watch.h"
#include "factory_exchange.h"
//#include "uac_tools.h"
//#include "thread.h"
#include "file.h"
#include "native_buffer.h" // soon, from axis library 2015-07-17 20:06 Livecoding(.tv)
//#include "stdio_file.h"
//#include "os.h"


//#include "directory_system.h"
//#include "file_system.h"


//#include "directory_context.h"
//#include "file_context.h"


#define NULL_REF(class) (*((class *) nullptr))


#define WIN_THREAD(pthread) (dynamic_cast < ::UNIVERSAL_WINDOWS::thread * > (dynamic_cast < ::thread * >(pthread)))


//CLASS_DECL_ACME void __trace_message(const ::scoped_string & scopedstrPrefix, ::message::message * pmessage);

//CLASS_DECL_ACME void __trace_message(const ::scoped_string & scopedstrPrefix, MESSAGE * lpmsg);


//CLASS_DECL_ACME void __cdecl __pre_translate_message(::message::message * pmessage);

//#include "tts_speaker.h"

//#include "application.h"





