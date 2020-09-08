#pragma once


namespace plane
{

   class session;
   class system;
   //class cube;


} // namespace plane


class form_data;



//namespace install
//{
//
//   class install;
//
//} // namespace install
//

namespace message
{


   class mouse;


} // namespace message


namespace hotplugin
{

   class host;
   class plugin;

}

namespace user
{


   class elemental;
   class interaction;
   class interaction_impl;
   class interaction_child;
   class user;
   class copydesk;
   class create_struct;
   class window_draw;
   class control_event;
   class form_control;
   class style;


} // namespace user




typedef __pointer(::user::interaction_impl) window_pointer;


#define SYSTEM_TYPE ::acme::system
#define SESSION_TYPE ::acme::session
#define APP_TYPE ::acme::application

#undef Sys
#define Sys(pobject) (*(::get_context_system(pobject))->cast < SYSTEM_TYPE >())

#undef Sess
#define Sess(pobject) (*(::get_context_session(pobject))->cast < SESSION_TYPE >())

#undef App
#define App(pobject) (*(::get_context_application(pobject))->cast < APP_TYPE >())








CLASS_DECL_ACME bool axis_init();
CLASS_DECL_ACME bool axis_term();

CLASS_DECL_ACME bool __node_axis_pre_init();
CLASS_DECL_ACME bool __node_axis_pos_init();

CLASS_DECL_ACME bool __node_axis_pre_term();
CLASS_DECL_ACME bool __node_axis_pos_term();


#include "acme/filesystem/filesystem.h"


#include "acme/acme/geoip/geoip.h"


//#if defined(LINUX)
//
//#include "acme/acme/os/ansios/ansios.h"
//
//#elif defined(_UWP)
//
//#include "acme/os/_UWP/_UWP.h"
//
//#elif defined(MACOS)
//
//#include "acme/acme/os/ansios/ansios.h"
//#include "acme/acme/os/macos/macos.h"
//
//#elif defined(ANDROID)
//
//#include "acme/os/ansios/ansios.h"
//#include "acme/os/android/android.h"
//
//#elif defined(WINDOWS)
//
//#include "acme/os/windows/windows.h"
//
//#elif defined(APPLE_IOS)
//
//#include "acme/os/ansios/ansios.h"
//#include "acme/os/ios/ios.h"
////#include "acme/os/ios/ios_windowing.h"
//
//#elif defined(SOLARIS)
//
//#include "acme/os/ansios/ansios.h"
//#include "acme/os/solaris/solaris_user_impl.h"
//
//#else
//
//#error "not implemented!!"
//
//#endif



#if defined(_UWP)

#include "app/acme/acme/os/_UWP/_UWP_sockets.h"

#endif


class ftpfs;

namespace fs
{

   class remote_native;
   class fs;
   class data;

}

class ifs;

//#include "acme/programming/javascript/javascript.h"

#include "acme/filesystem/fs/_fs.h"

//#include "acme/acme/account/account.h"



//#include "acme/user/user/user_enum.h"

//#include "acme/user/user/user_key_enum.h"

//#include "acme/user/user/user_keyboard_layout.h"

//#include "acme/user/user/user_keyboard.h"

#include "acme/user/user.h"


#include "acme/database/database/_.h"

#include "acme/database/sqlitedb/_.h"

#include "acme/database/simpledb/_.h"

#include "acme/acme/application.h"


#include "acme/acme/session.h"

//#include "acme/filesystem/filesystem/application_file.h"
//
//#include "acme/filesystem/filesystem/application_dir.h"
//
//#include "acme/filesystem/filesystem/system_file.h"
//
//#include "acme/filesystem/filesystem/system_dir.h"

#include "acme/graphics/_.h"

#include "acme/acme/system.h"

#include "acme/acme/static_start.h"

#include "app/acme/acme/node/_.h"

#include "acme/primitive/data/data_tree_item.h"

#include "acme/primitive/data/data_tree.h"

#include "acme/primitive/data/data_simple_item.h"

#include "acme/html_lite/_.h"

//#include "acme/database/database/database.h"

//#include "acme/database/sqlitedb/sqlitedb.h"

//#include "acme/database/simpledb/simpledb.h"


#include "acme/acme/acme/_impl.h"


#include "acme/database/database/_impl.h"

