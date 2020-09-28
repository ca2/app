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



#undef Sys
#undef Sess
#undef App


#define Sys(playered) (*::get_context_system(playered)->m_paquasystem)
#define Sess(playered) (*::get_context_session(playered)->m_paquasession)
#define App(playered) (*::get_context_application(playered)->m_paquaapplication)


#define Au(playered) (*(::get_context_audio(playered)))
#define Audio (Au(get_context()))

#define Mm(playered) (*(::get_context_multimedia(playered)))
#define Multimedia (Mm(get_context()))


#define __spin_namespace aqua // back bone / four-letter "spin*" namespace name




namespace audio
{


   class plugin;


} // namespace audio


namespace multimedia
{


   class decoder;


} // namespace multimedia


#include "aqua/multimedia/_c.h"


#include "aqua/user/controller.h"


#include "aqua/multimedia/_.h"




#include "aqua/platform/application.h"


#include "aqua/platform/session.h"


#include "aqua/platform/system.h"



