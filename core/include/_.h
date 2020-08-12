/////////////////////////////////////////////////////////////////////////////////////////
//
//  ca2
//
//  ca2 is an all-purpose multi-platform framework and set of libraries
//  written in C++ language to help developers create great apps for users.
//
//  ca2/C++/C/Assembly/Huffman Machine/Hardware/Universe/Multiverse stack
//
//

#pragma once


namespace user
{


   class tree;


} // namespace user


//#include "core/compress/compress.h"

//#include "core/multimedia/_c.h"

#include "core/user/user/_const.h"

#include "core/user/experience/_const.h"

#include "aura/const/_const.h"

#include "aura/primitive/primitive/_memory.h"

#include "core/user/user/_const.h"

#include "core/user/user/_const_key.h"




namespace core
{

   class user;

} // namespace core


namespace html
{


   class html;


} // namespace html


namespace audio
{


   class plugin;



} // namespace audio


#define Usr(pobject) (*Sess(pobject).user()->m_pcoreuser)
#define User (Usr(get_context()))



CLASS_DECL_CORE bool __node_core_pre_init();
CLASS_DECL_CORE bool __node_core_pos_init();

CLASS_DECL_CORE bool __node_core_pre_term();
CLASS_DECL_CORE bool __node_core_pos_term();



//CLASS_DECL_CORE ::core::user * get_context_user();
//CLASS_DECL_CORE inline ::core::user * get_context_user(::object * pobject);
//CLASS_DECL_CORE inline ::core::user * get_context_user(::aura::application * papp);


#include "aura/xml/exportable.h"


#include "aura/xml/importable.h"



//#include "aura/common.h"


#if defined(LINUX)

#include "aura/os/ansios/_.h"

#elif defined(_UWP)
//
//#include "aura/os/_UWP/_UWP.h"
//#include "aura/os/_UWP/_UWP_user_impl.h"
//
#elif defined(MACOS)
//
//#include "aura/os/ansios/ansios.h"
//#include "aura/os/macos/macos.h"
//
#elif defined(ANDROID)
//
//#include "aura/os/ansios/ansios.h"
//#include "aura/os/android/android.h"
//
#elif defined(WINDOWS_DESKTOP)
//
//#include "aura/os/windows/windows.h"
//
#elif defined(APPLE_IOS)
//
//#include "aura/os/ansios/ansios.h"
//#include "aura/os/ios/ios.h"
////#include "aura/os/ios/ios_windowing.h"
//
#elif defined(SOLARIS)
//
//#include "aura/os/ansios/ansios.h"
//#include "aura/os/solaris/solaris_user_impl.h"
//
#else
//
//#error "not implemented!!"
//
#endif


#include "core/user/simple/message_box.h"

#include "core/user.h"

#include "core/net/_.h"



#include "core/os/text.h"

#ifdef ANDROID

#include "core/os/android/_os_local.h"

#endif

//#include "core/database/database/_.h"

#include "core/user/_.h"

//#include "core/multimedia/_.h"

#include "core/os/process.h"

#include "core/geoip/geoip.h"

class ftpfs;

namespace fs
{

   class remote_native;
   class fs;
   class data;

}

class ifs;

//#include "axis/programming/javascript/javascript.h"

#include "core/filesystem/fs/_fs.h"

//#include "core/database/sqlitedb/_.h"

//#include "core/database/simpledb/_.h"

#include "core/html/html_lite/_.h"

#include "core/user/experience/_.h"

#include "core/filesystem/userfs/_.h"

#include "core/filesystem/filemanager/_.h"

#include "core/user/userex/_.h"

#include "core/filesystem/filehandler/_.h"

//#include "core/game/_.h"

#include "core/platform/user.h"

//#include "core/multimedia/audio/speaker.h"

//#include "core/multimedia/audio.h"

//#include "core/multimedia/multimedia.h"

//#include "core/gpu/gpu/_.h"


#include "core/os/chronometer.h"



#include "core/math/_math.h"


// C++ Includes
#include "core/os/_.h"

// C++ Includes
#include "core/node/_.h"


#include "core/scripting/javascript/javascript.h"


#include "core/compress/compress.h"


#include "core/user/_.h"


#include "core/filesystem/_impl.h"


#include "core/net/_impl.h"


///#include "core/database/database/_impl.h"


#include "core/os/_impl.h"



