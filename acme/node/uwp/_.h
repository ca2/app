#pragma once

#define SECURITY_WIN32

#undef User

#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>


#include "exception.h"


//namespace uwp
//{
//
//   ref class directx_framework_view;
//
//} // namespace uwp



string get_error_message(::u32 dwError);


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


//#include "dir_system.h"
//#include "file_system.h"


//#include "dir_context.h"
//#include "file_context.h"


#define NULL_REF(class) (*((class *) nullptr))


#define WIN_THREAD(pthread) (dynamic_cast < ::_UWP::thread * > (dynamic_cast < ::thread * >(pthread)))


//CLASS_DECL_ACME void __trace_message(const char * pszPrefix, ::message::message * pmessage);

//CLASS_DECL_ACME void __trace_message(const char * pszPrefix, LPMESSAGE lpmsg);


//CLASS_DECL_ACME void __cdecl __pre_translate_message(::message::message * pmessage);

//#include "tts_speaker.h"

//#include "application.h"





