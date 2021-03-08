/////////////////////////////////////////////////////////////////////////////////////////
//
//  ca2
//
//  ca2 is an all-purpose multi-platform framework and set of libraries written in
//  C++ language with the aim to help developers create awesome apps for users.
//
//  ca2/./aura/C++/C/Assembly/Huffman Machine/Hardware/Universe/Multiverse stack
//
//
//
//
//  c(s)t(s)<tb(s)!!
//




#pragma once



//#undef System
//#undef Sess
//#undef App
//
//
//#define System (::get_context_system()->m_pbredsystem)
//#define Sess(pcontextsession) (pcontextsession->m_pabredsession)
//#define App(playered) (*::get_context_application(playered)->m_pbredapplication)


#define __spin_namespace bred // back bone / four-letter "spin*" namespace name


namespace bred
{


   class system;
   class session;
   class application;


   inline system * get_system() { return ::bred::get_system()->layer(LAYERED_BRED); }


} // namespace bred

#include "bred/platform/application.h"


#include "bred/platform/session.h"


#include "bred/platform/system.h"



