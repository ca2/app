#pragma once


//#include "aqua/node/ansios/ansios.h"


string get_error_message(DWORD dwError);

__pointer(::aqua::application)     linux_instantiate_application(__pointer(::aqua::application) pappSystem, const char * pszId);



#pragma once


namespace linux
{


//   class thread;

   class linux
   {
      i32 function();
   };



} // namespace linux



CLASS_DECL_AQUA MESSAGE * __get_current_message();


CLASS_DECL_AQUA __pointer(::aqua::application)  __get_app();
CLASS_DECL_AQUA __pointer(::user::primitive) __get_main_window();
//CLASS_DECL_AQUA HINSTANCE CLASS_DECL_AQUA System.m_hInstance;
CLASS_DECL_AQUA const char * __get_app_name();





#include "thread.h"
#include "os_context.h"

#define NULL_REF(class) (*((class *) nullptr))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))

#include "shell.h"
#include "shell_linux.h"


#include "interaction_impl.h"


CLASS_DECL_AQUA void AfxProcessWndProcException(::exception::exception*, ::message::message * pmessage);

CLASS_DECL_AQUA void __cdecl __pre_translate_message(::message::message * pmessage);

WINBOOL mq_peek_message(LPMESSAGE pMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

WINBOOL mq_get_message(LPMESSAGE pMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);

i32 CLASS_DECL_AQUA __linux_main(i32 argc, char * argv[]);

CLASS_DECL_AQUA void vfxThrowFileException(::object * pobject, const ::estatus & estatus, LONG lOsError, const char * pszFileName = nullptr);

#include "internal.h"

CLASS_DECL_AQUA ::estatus os_shell_initialize();

CLASS_DECL_AQUA MESSAGE * __get_current_message();

CLASS_DECL_AQUA __pointer(::aqua::application)  __get_app();

CLASS_DECL_AQUA __pointer(::user::primitive) __get_main_window();

CLASS_DECL_AQUA const char * __get_app_name();


#include "dir_system.h"
#include "dir_context.h"
#include "file_system.h"
#include "file_context.h"


#include "factory_exchange.h"



