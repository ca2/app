//
//  os_windowing.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 10/12/17.
//
#pragma once


#if defined UNIVERSAL_WINDOWS && defined(__cplusplus_winrt)

// class CLASS_DECL_APEX os_system_window
// {
// public:

//    //bool                                         m_bWindowSizeChange;

   

//    ::apex::system_window ^                      m_pwindow;

//    os_system_window();

// };

#elif defined(APPLE_IOS)

// class os_system_window
// {
// public:

//    ::pointer<::user::interaction>                     m_puserinteraction;

// };

#elif defined(ANDROID)

// class os_system_window
// {
// public:

//    ::pointer<::user::interaction>                     m_puserinteraction;

//    oswindow                                     m_oswindow;

//    os_system_window();
//    ~os_system_window();

// };

#else

// class os_system_window;

#endif


//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow);

#ifdef APPLE_IOS

#include "ios/ios_window.h"

#endif

