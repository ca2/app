#pragma once


#define SECURITY_WIN32



//string get_error_message(unsigned int dwError);

::platform::application *     ios_instantiate_application(::apex::application * pappSystem, const ::scoped_string & scopedstrId);


#define NULL_REF(class) (*((class *) nullptr))

#define IOS_THREAD(pthread) (dynamic_cast < ::ios::thread * > (dynamic_cast < ::thread * >(pthread)))


CLASS_DECL_APEX void __trace_message(const char * lpszPrefix, ::message::message * pmessage);
CLASS_DECL_APEX void __trace_message(const char * lpszPrefix, MESSAGE * lpmsg);

//#include "implementation.h"
//#include "directory_system.h"
//#include "file_system.h"
//#include "directory_context.h"
//#include "file_context.h"
//#include "file.h"
//#include "factory_exchange.h"
//#include "thread.h"
//#include "os_context.h"
//#include "ip_enum.h"
//#include "shell.h"
//#include "file_os_watcher.h"
//#include "host_interaction.h"


//#include "application.h"


//#include "printer.h"
//#include "file_set.h"
//#include "window_draw.h"
//#include "window.h"
//#include "port_forward.h"
//#include "copydesk.h"
//#include "crypto.h"


// int_bool PeekMessage(
// MESSAGE * lpMsg,
// oswindow hWnd,
// unsigned int wMsgFilterMin,
// unsigned int wMsgFilterMax,
// unsigned int wRemoveMsg);

// int_bool GetMessage(
// MESSAGE * lpMsg,
// oswindow hWnd,
// unsigned int wMsgFilterMin,
// unsigned int wMsgFilterMax);



int CLASS_DECL_APEX __ios_main(int argc, char * argv[]);


//CLASS_DECL_APEX void vfxThrowFileException(::particle * pparticle, const ::e_status & estatus, int lOsError, const char * lpszFileName = nullptr);
//
//CLASS_DECL_APEX ::file::exception * get_FileException(::particle * pparticle, const ::e_status & estatus, int lOsError, const char * lpszFileName = nullptr);

//
//
//namespace ios
//{
//
//
//   class thread;
//
//   class IOS
//   {
//      int function();
//   };
//
//
//
//} // namespace ios
//


