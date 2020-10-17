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


   class matter;
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


#define SYSTEM_TYPE ::axis::system
#define SESSION_TYPE ::axis::session
#define APP_TYPE ::axis::application

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


#include "axis/filesystem/filesystem.h"


#include "axis/axis/geoip/geoip.h"


//#if defined(LINUX)
//
//#include "axis/axis/os/ansios/ansios.h"
//
//#elif defined(_UWP)
//
//#include "axis/os/_UWP/_UWP.h"
//
//#elif defined(MACOS)
//
//#include "axis/axis/os/ansios/ansios.h"
//#include "axis/axis/os/macos/macos.h"
//
//#elif defined(ANDROID)
//
//#include "axis/os/ansios/ansios.h"
//#include "axis/os/android/android.h"
//
//#elif defined(WINDOWS)
//
//#include "axis/os/windows/windows.h"
//
//#elif defined(APPLE_IOS)
//
//#include "axis/os/ansios/ansios.h"
//#include "axis/os/ios/ios.h"
////#include "axis/os/ios/ios_windowing.h"
//
//#elif defined(SOLARIS)
//
//#include "axis/os/ansios/ansios.h"
//#include "axis/os/solaris/solaris_user_impl.h"
//
//#else
//
//#error "not implemented!!"
//
//#endif



#if defined(_UWP)

#include "app/axis/axis/os/_UWP/_UWP_sockets.h"

#endif


class ftpfs;

namespace fs
{

   class remote_native;
   class fs;
   class data;

}

class ifs;

//#include "axis/programming/javascript/javascript.h"

#include "axis/filesystem/fs/_fs.h"

//#include "axis/axis/account/account.h"



//#include "axis/user/user/user_enum.h"

//#include "axis/user/user/user_key_enum.h"

//#include "axis/user/user/user_keyboard_layout.h"

//#include "axis/user/user/user_keyboard.h"

#include "axis/user/user.h"


#include "axis/database/database/_.h"

#include "axis/database/sqlitedb/_.h"

#include "axis/database/simpledb/_.h"

#include "axis/axis/application.h"


#include "axis/axis/session.h"

//#include "axis/filesystem/filesystem/application_file.h"
//
//#include "axis/filesystem/filesystem/application_dir.h"
//
//#include "axis/filesystem/filesystem/system_file.h"
//
//#include "axis/filesystem/filesystem/system_dir.h"

#include "acme/graphics/_.h"

#include "axis/axis/system.h"

#include "axis/axis/static_start.h"

#include "app/axis/axis/node/_.h"

#include "acme/primitive/data/data_tree_item.h"

#include "acme/primitive/data/data_tree.h"

#include "acme/primitive/data/data_simple_item.h"

#include "axis/html_lite/_.h"

//#include "axis/database/database/database.h"

//#include "axis/database/sqlitedb/sqlitedb.h"

//#include "axis/database/simpledb/simpledb.h"


#include "axis/axis/axis/_impl.h"


#include "axis/database/database/_impl.h"

