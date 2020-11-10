#pragma once


//#include "aura/node/ansios/ansios.h"


string get_error_message(::u32 dwError);

__pointer(::aura::application)     linux_instantiate_application(__pointer(::aura::application) pappSystem, const char * pszId);



#pragma once


namespace linux
{


//   class thread;

   class linux
   {
      i32 function();
   };



} // namespace linux



CLASS_DECL_CORE MESSAGE * __get_current_message();


CLASS_DECL_CORE __pointer(::aura::application)  __get_app();
CLASS_DECL_CORE __pointer(::user::primitive) __get_main_window();
//CLASS_DECL_CORE HINSTANCE CLASS_DECL_CORE System.m_hInstance;
CLASS_DECL_CORE const char * __get_app_name();





#include "thread.h"
#include "os_context.h"

#define NULL_REF(class) (*((class *) nullptr))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))

#include "shell.h"


#include "interaction_impl.h"


CLASS_DECL_CORE void AfxProcessWndProcException(::exception::exception*, ::message::message * pmessage);

CLASS_DECL_CORE void __cdecl __pre_translate_message(::message::message * pmessage);

int_bool mq_peek_message(LPMESSAGE pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);

int_bool mq_get_message(LPMESSAGE pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

i32 CLASS_DECL_CORE __linux_main(i32 argc, char * argv[]);

CLASS_DECL_CORE void vfxThrowFileException(::object * pobject, const ::estatus & estatus, ::i32 lOsError, const char * pszFileName = nullptr);

#include "internal.h"

CLASS_DECL_CORE ::estatus os_shell_initialize();

CLASS_DECL_CORE MESSAGE * __get_current_message();

CLASS_DECL_CORE __pointer(::aura::application)  __get_app();

CLASS_DECL_CORE __pointer(::user::primitive) __get_main_window();

CLASS_DECL_CORE const char * __get_app_name();


#include "dir_system.h"
#include "dir_context.h"
#include "file_system.h"
#include "file_context.h"


#include "factory_exchange.h"



