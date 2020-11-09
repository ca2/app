#pragma once


#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


string get_error_message(DWORD dwError);

__pointer(::aura::application)     linux_instantiate_application(__pointer(::aura::application) pappSystem, const char * pszId);



namespace linux
{


//   class thread;

   class linux
   {
      i32 function();
   };



} // namespace linux



CLASS_DECL_AURA MESSAGE * __get_current_message();


CLASS_DECL_AURA __pointer(::aura::application)  __get_app();
CLASS_DECL_AURA __pointer(::user::primitive) __get_main_window();
//CLASS_DECL_AURA HINSTANCE CLASS_DECL_AURA System.m_hInstance;
CLASS_DECL_AURA const char * __get_app_name();







#include "interaction_impl.h"


CLASS_DECL_AURA void AfxProcessWndProcException(::exception::exception*, ::message::message * pmessage);

CLASS_DECL_AURA void __cdecl __pre_translate_message(::message::message * pmessage);

int_bool mq_peek_message(LPMESSAGE pMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

int_bool mq_get_message(LPMESSAGE pMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);

i32 CLASS_DECL_AURA __linux_main(i32 argc, char * argv[]);

CLASS_DECL_AURA void vfxThrowFileException(::object * pobject, const ::estatus & estatus, LONG lOsError, const char * pszFileName = nullptr);

CLASS_DECL_AURA ::estatus os_shell_initialize();

CLASS_DECL_AURA MESSAGE * __get_current_message();

CLASS_DECL_AURA __pointer(::aura::application)  __get_app();

CLASS_DECL_AURA __pointer(::user::primitive) __get_main_window();

CLASS_DECL_AURA const char * __get_app_name();



#include "copydesk.h"


#include "factory_exchange.h"



