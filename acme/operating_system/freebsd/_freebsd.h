#pragma once



//string get_error_message(::u32 dwError);

//::pointer<::platform::application>    linux_instantiate_application(::pointer<::platform::application>appSystem, const ::scoped_string & scopedstrId);



namespace linux
{


//   class thread;

   class linux
   {
      i32 function();
   };



} // namespace linux



CLASS_DECL_ACME MESSAGE * __get_current_message();


//CLASS_DECL_ACME ::pointer<::platform::application> __get_app();
//CLASS_DECL_ACME ::pointer<::user::interaction_base>__get_main_window();
//CLASS_DECL_ACME HINSTANCE CLASS_DECL_ACME ::acmeacmesystem()->m_hInstance;
CLASS_DECL_ACME const char * __get_app_name();





#include "thread.h"
//#include "os_context.h"

#define NULL_REF(class) (*((class *) nullptr))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))


//CLASS_DECL_ACME void ::windows_definition::ProcessWndProcException(::exception*, ::message::message * pmessage);

//CLASS_DECL_ACME void __cdecl __pre_translate_message(::message::message * pmessage);

//int_bool mq_peek_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);

//int_bool mq_get_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

//i32 CLASS_DECL_ACME __linux_main(i32 argc, char * argv[]);

//CLASS_DECL_ACME void vfxThrowFileException(::particle * pparticle, const ::e_status & estatus, int lOsError, const ::file::path & path = nullptr);

#include "internal.h"

//CLASS_DECL_ACME void os_shell_initialize();

//CLASS_DECL_ACME MESSAGE * __get_current_message();

//CLASS_DECL_ACME ::pointer<::platform::application> __get_app();

//CLASS_DECL_ACME ::pointer<::user::interaction_base>__get_main_window();

CLASS_DECL_ACME const char * __get_app_name();


//#include "directory_system.h"
//#include "directory_context.h"
//#include "file_system.h"
//#include "file_context.h"


//#include "copydesk.h"


#include "factory_exchange.h"



