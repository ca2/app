#pragma once



//string get_error_message(::u32 dwError);

//::pointer<::acid::application>    linux_instantiate_application(::pointer<::acid::application>appSystem, const ::scoped_string & scopedstrId);



namespace linux
{


//   class thread;

   class linux
   {
      i32 function();
   };



} // namespace linux



CLASS_DECL_ACID MESSAGE * __get_current_message();


//CLASS_DECL_ACID ::pointer<::acid::application> __get_app();
//CLASS_DECL_ACID ::pointer<::user::primitive>__get_main_window();
//CLASS_DECL_ACID HINSTANCE CLASS_DECL_ACID ::aceacesystem()->m_hInstance;
CLASS_DECL_ACID const char * __get_app_name();





#include "thread.h"
//#include "os_context.h"

#define NULL_REF(class) (*((class *) nullptr))

#define LNX_THREAD(pthread) (dynamic_cast < ::linux::thread * > (dynamic_cast < ::thread * >(pthread)))


//CLASS_DECL_ACID void ::windows_definition::ProcessWndProcException(::exception*, ::message::message * pmessage);

//CLASS_DECL_ACID void __cdecl __pre_translate_message(::message::message * pmessage);

//int_bool mq_peek_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax, ::u32 wRemoveMsg);

//int_bool mq_get_message(MESSAGE * pMsg, oswindow hWnd, ::u32 wMsgFilterMin, ::u32 wMsgFilterMax);

//i32 CLASS_DECL_ACID __linux_main(i32 argc, char * argv[]);

//CLASS_DECL_ACID void vfxThrowFileException(::particle * pparticle, const ::e_status & estatus, ::i32 lOsError, const ::file::path & path = nullptr);

#include "internal.h"

//CLASS_DECL_ACID void os_shell_initialize();

//CLASS_DECL_ACID MESSAGE * __get_current_message();

//CLASS_DECL_ACID ::pointer<::acid::application> __get_app();

//CLASS_DECL_ACID ::pointer<::user::primitive>__get_main_window();

CLASS_DECL_ACID const char * __get_app_name();


//#include "dir_system.h"
//#include "dir_context.h"
//#include "file_system.h"
//#include "file_context.h"


//#include "copydesk.h"


#include "factory_exchange.h"



