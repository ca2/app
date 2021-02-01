#pragma once


#define SECURITY_WIN32



//#include "acme/node/ansios/_.h"
////#define CLASS_DECL_ACME

//struct plane_system
//{
//
//   ::plane::system *    m_psystem;
//
//   plane_system(const char * pszId);
//
//   UIWindow * init_part_2ex(CGRect rectangle_i32);
//
//   void begin();
//
//};


string get_error_message(::u32 dwError);

::acme::application *     ios_instantiate_application(::acme::application * pappSystem, const char * pszId);


#define NULL_REF(class) (*((class *) nullptr))

#define IOS_THREAD(pthread) (dynamic_cast < ::ios::thread * > (dynamic_cast < ::thread * >(pthread)))


//CLASS_DECL_ACME void __trace_message(const char * lpszPrefix, ::message::message * pmessage);
//CLASS_DECL_ACME void __trace_message(const char * lpszPrefix, MESSAGE * lpmsg);

#include "implementation.h"
#include "dir_system.h"
#include "file_system.h"
#include "dir_context.h"
#include "file_context.h"
#include "file.h"
#include "factory_exchange.h"
#include "thread.h"
#include "os_context.h"
#include "ip_enum.h"
#include "shell.h"
#include "file_os_watcher.h"
#include "host_interaction.h"


#include "application.h"


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
// ::u32 wMsgFilterMin,
// ::u32 wMsgFilterMax,
// ::u32 wRemoveMsg);

// int_bool GetMessage(
// MESSAGE * lpMsg,
// oswindow hWnd,
// ::u32 wMsgFilterMin,
// ::u32 wMsgFilterMax);



i32 CLASS_DECL_ACME __ios_main(i32 argc, char * argv[]);


CLASS_DECL_ACME void vfxThrowFileException(::matter * pobject, const ::e_status & estatus, ::i32 lOsError, const char * lpszFileName = nullptr);

CLASS_DECL_ACME ::file::exception * get_FileException(::matter * pobject, const ::e_status & estatus, ::i32 lOsError, const char * lpszFileName = nullptr);



namespace ios
{


   class thread;

   class IOS
   {
      i32 function();
   };



} // namespace ios


///#include "ios_plane_system.h"


#include "interaction_impl.h"



