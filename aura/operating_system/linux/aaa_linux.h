#pragma once


#include "apex/operating_system/linux/_linux.h"


////#include "aura/user/user/_component.h"


string get_error_message(::u32 dwError);

::pointer<::aura::application>    linux_instantiate_application(::pointer<::aura::application>appSystem, const ::string & pszId);

//
//
//namespace linux
//{
//
//
////   class thread;
//
////   class linux
////   {
////      i32 function();
////   };
//
//
//
//} // namespace linux
//


CLASS_DECL_AURA MESSAGE * __get_current_message();


//CLASS_DECL_AURA ::pointer<::aura::application> __get_app();
//CLASS_DECL_AURA ::pointer<::user::primitive>__get_main_window();
////CLASS_DECL_AURA HINSTANCE CLASS_DECL_AURA ::auraacmesystem()->m_hInstance;
//CLASS_DECL_AURA const char * __get_app_name();







//#include "interaction_impl.h"


CLASS_DECL_AURA void AfxProcessWndProcException(::exception*, ::message::message * pmessage);

CLASS_DECL_AURA void __cdecl __pre_translate_message(::message::message * pmessage);

int_bool mq_peek_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);

int_bool mq_get_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

i32 CLASS_DECL_AURA __linux_main(i32 argc, char * argv[]);

//CLASS_DECL_AURA void vfxThrowFileException(::particle * pparticle, const ::e_status & estatus, ::i32 lOsError, const ::string & pszFileName = nullptr);

CLASS_DECL_AURA void os_shell_initialize();

CLASS_DECL_AURA MESSAGE * __get_current_message();

//CLASS_DECL_AURA ::pointer<::aura::application> __get_app();

CLASS_DECL_AURA ::pointer<::user::primitive>__get_main_window();

CLASS_DECL_AURA const char * __get_app_name();



#include "factory_exchange.h"





#include "_user.h"

//#include "desktop_file.h"
#include "x11.h"



