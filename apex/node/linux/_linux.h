#pragma once


//#include "apex/node/ansios/ansios.h"


string get_error_message(DWORD dwError);

__pointer(::apex::application)     linux_instantiate_application(__pointer(::apex::application) pappSystem, const char * pszId);



#pragma once


namespace linux
{


//   class thread;

   class linux
   {
      i32 function();
   };



} // namespace linux



CLASS_DECL_APEX MESSAGE * __get_current_message();


CLASS_DECL_APEX __pointer(::apex::application)  __get_app();
CLASS_DECL_APEX __pointer(::user::primitive) __get_main_window();
//CLASS_DECL_APEX HINSTANCE CLASS_DECL_APEX System.m_hInstance;
CLASS_DECL_APEX const char * __get_app_name();





#include "thread.h"
#include "os_context.h"

#define NULL_REF(class) (*((class *) nullptr))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))

//#include "shell.h"
//#include "shell_linux.h"


//#include "interaction_impl.h"


CLASS_DECL_APEX void AfxProcessWndProcException(::exception::exception*, ::message::message * pmessage);

CLASS_DECL_APEX void __cdecl __pre_translate_message(::message::message * pmessage);

WINBOOL mq_peek_message(LPMESSAGE pMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

WINBOOL mq_get_message(LPMESSAGE pMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);

i32 CLASS_DECL_APEX __linux_main(i32 argc, char * argv[]);

CLASS_DECL_APEX void vfxThrowFileException(::object * pobject, const ::estatus & estatus, LONG lOsError, const char * pszFileName = nullptr);

#include "internal.h"

CLASS_DECL_APEX ::estatus os_shell_initialize();

CLASS_DECL_APEX MESSAGE * __get_current_message();

CLASS_DECL_APEX __pointer(::apex::application)  __get_app();

CLASS_DECL_APEX __pointer(::user::primitive) __get_main_window();

CLASS_DECL_APEX const char * __get_app_name();


#include "dir_system.h"
#include "dir_context.h"
#include "file_system.h"
#include "file_context.h"


#include "factory_exchange.h"



