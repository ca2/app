/////////////////////////////////////////////////////////////////////////////////////////
//
//  ca2
//
//  ca2 is an all-purpose multi-platform framework and set of libraries written in
//  C++ language with the aim to help developers create awesome apps for users.
//
//  ca2/../axis/aura/C++/C/Assembly/Huffman Machine/Hardware/Universe/Multiverse stack
//
//
//
//
//  c(s)t(s)<tb(s)!!
//


#pragma once


#undef Sys
#undef Sess
#undef App


#define Sys(pobject) (*pobject->get_context_system()->m_paxissystem)
#define Sess(pobject) (*pobject->get_context_session()->m_paxissession)
#define App(pobject) (*pobject->get_app()->m_paxisapplication)


// C-includes
#include "axis/os/_c.h"

#include "axis/account/_.h"



#if defined(LINUX)

#include "axis/os/ansios/_.h"

#elif defined(_UWP)
//
//#include "axis/os/_UWP/_UWP.h"
//#include "axis/os/_UWP/_UWP_user_impl.h"
//
#elif defined(MACOS)
//
//#include "axis/os/ansios/ansios.h"
//#include "axis/os/macos/macos.h"
//
#elif defined(ANDROID)
//
//#include "axis/os/ansios/ansios.h"
//#include "axis/os/android/android.h"
//
#elif defined(WINDOWS_DESKTOP)
//
//#include "axis/os/windows/windows.h"
//
#elif defined(APPLE_IOS)
//
//#include "axis/os/ansios/ansios.h"
//#include "axis/os/ios/ios.h"
////#include "axis/os/ios/ios_windowing.h"
//
#elif defined(SOLARIS)
//
//#include "axis/os/ansios/ansios.h"
//#include "axis/os/solaris/solaris_user_impl.h"
//
#else
//
//#error "not implemented!!"
//
#endif

#include "axis/net/_.h"


#include "axis/platform/openweather_city.h"

#include "axis/math/_.h"

#include "axis/database/database/_.h"

#include "axis/database/simpledb/_.h"

#include "axis/platform/geo_department.h"

#include "axis/platform/application.h"

#include "axis/account/_account.h"

#include "axis/platform/session.h"

#include "axis/net/email_department.h"

#include "axis/html/html/_.h"

#include "axis/platform/system.h"

#define new AURA_NEW




// C++ Includes
#include "axis/os/_.h"
#include "axis/node/_.h"



#include "axis/compress/compress.h"






#include "axis/platform/_impl.h"






#include "axis/net/_impl.h"



#include "axis/database/database/_impl.h"


#include "axis/os/_impl.h"


