#pragma once


//#include "apex/operating_system/ansios/ansios.h"


string get_error_message(::u32 dwError);

::pointer<::apex::application>    linux_instantiate_application(::pointer<::apex::application>appSystem, const scoped_string & strId);



//#pragma once
//
//
//namespace linux
//{
//
//
////   class thread;
//
//   class linux
//   {
//      i32 function();
//   };
//
//
//
//} // namespace linux



CLASS_DECL_APEX MESSAGE * __get_current_message();


CLASS_DECL_APEX ::pointer<::apex::application> __get_app();
CLASS_DECL_APEX ::pointer<::user::primitive>__get_main_window();
//CLASS_DECL_APEX HINSTANCE CLASS_DECL_APEX ::apexacmesystem()->m_hInstance;
CLASS_DECL_APEX const char * __get_app_name();





#include "parallelization.h"
//#include "os_context.h"

#define NULL_REF(class) (*((class *) nullptr))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))


CLASS_DECL_APEX void AfxProcessWndProcException(::exception*, ::message::message * pmessage);

CLASS_DECL_APEX void __cdecl __pre_translate_message(::message::message * pmessage);

int_bool mq_peek_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);

int_bool mq_get_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

i32 CLASS_DECL_APEX __linux_main(i32 argc, char * argv[]);

CLASS_DECL_APEX void vfxThrowFileException(::particle * pparticle, const ::e_status & estatus, ::i32 lOsError, const scoped_string & strFileName = nullptr);

#include "internal.h"

CLASS_DECL_APEX void os_shell_initialize();

CLASS_DECL_APEX MESSAGE * __get_current_message();

CLASS_DECL_APEX ::pointer<::apex::application> __get_app();

CLASS_DECL_APEX ::pointer<::user::primitive>__get_main_window();

CLASS_DECL_APEX const char * __get_app_name();


//#include "dir_system.h"
//#include "dir_context.h"
//#include "file_system.h"
//#include "file_context.h"
//#include "inteprocess_channel.h"

#include "factory_exchange.h"



