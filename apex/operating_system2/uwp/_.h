#pragma once


#define SECURITY_WIN32


#undef User


#include <shlobj.h>
#include <Security.h>
#include <shlobj.h>


//string get_error_message(::u32 dwError);



#include "factory_exchange.h"
#include "thread.h"
#include "directory_system.h"
#include "file_system.h"
#include "directory_context.h"
#include "file_context.h"


#define NULL_REF(class) (*((class *) nullptr))


#define WIN_THREAD(pthread) (dynamic_cast < ::UNIVERSAL_WINDOWS::thread * > (dynamic_cast < ::thread * >(pthread)))


//CLASS_DECL_APEX void __trace_message(const ::scoped_string & scopedstrPrefix, ::message::message * pmessage);

//CLASS_DECL_APEX void __trace_message(const ::scoped_string & scopedstrPrefix, MESSAGE * lpmsg);


//CLASS_DECL_APEX void __cdecl __pre_translate_message(::message::message * pmessage);

//#include "tts_speaker.h"

#include "application.h"





