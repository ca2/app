#pragma once


#define SECURITY_WIN32


#undef User


#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>


string get_error_message(::u32 dwError);



#include "factory_exchange.h"
#include "thread.h"
#include "dir_system.h"
#include "file_system.h"
#include "dir_context.h"
#include "file_context.h"


#define NULL_REF(class) (*((class *) nullptr))


#define WIN_THREAD(pthread) (dynamic_cast < ::_UWP::thread * > (dynamic_cast < ::thread * >(pthread)))


//CLASS_DECL_APEX void __trace_message(const char * pszPrefix, ::message::message * pmessage);

//CLASS_DECL_APEX void __trace_message(const char * pszPrefix, MESSAGE * lpmsg);


//CLASS_DECL_APEX void __cdecl __pre_translate_message(::message::message * pmessage);

//#include "tts_speaker.h"

#include "application.h"





