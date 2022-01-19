#pragma once

//
//#if !BROAD_PRECOMPILED_HEADER
//#include "acme/user/_user.h"
//#endif


string get_error_message(::u32 dwError);

//__pointer(::acme::application)     linux_instantiate_application(__pointer(::acme::application) pappSystem, const char * pszId);



namespace linux
{


//   class thread;

   class linux
   {
      i32 function();
   };



} // namespace linux



CLASS_DECL_ACME MESSAGE * __get_current_message();


//CLASS_DECL_ACME __pointer(::acme::application)  __get_app();
//CLASS_DECL_ACME __pointer(::user::primitive) __get_main_window();
//CLASS_DECL_ACME HINSTANCE CLASS_DECL_ACME ::acme::get_system()->m_hInstance;
CLASS_DECL_ACME const char * __get_app_name();





#include "thread.h"
//#include "os_context.h"

#define NULL_REF(class) (*((class *) nullptr))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))


CLASS_DECL_ACME void AfxProcessWndProcException(::exception*, ::message::message * pmessage);

CLASS_DECL_ACME void __cdecl __pre_translate_message(::message::message * pmessage);

int_bool mq_peek_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);

void mq_get_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

i32 CLASS_DECL_ACME __linux_main(i32 argc, char * argv[]);

CLASS_DECL_ACME void vfxThrowFileException(::matter * pobject, const ::e_status & estatus, ::i32 lOsError, const char * pszFileName = nullptr);

#include "internal.h"

CLASS_DECL_ACME void os_shell_initialize();

CLASS_DECL_ACME MESSAGE * __get_current_message();

//CLASS_DECL_ACME __pointer(::acme::application)  __get_app();

//CLASS_DECL_ACME __pointer(::user::primitive) __get_main_window();

CLASS_DECL_ACME const char * __get_app_name();


//#include "dir_system.h"
//#include "dir_context.h"
//#include "file_system.h"
//#include "file_context.h"


//#include "copydesk.h"


#include "factory_exchange.h"



