/////////////////////////////////////////////////////////////////////////////////////////
//
//  ca2
//
//  ca2 is an all-purpose multi-platform framework and set of libraries written in 
//  C++ language with the aim to help developers create awesome apps for users.
//
//  ca2/.../base/axis/aura/C++/C/Assembly/Huffman Machine/Hardware/Universe/Multiverse stack
//
//


#pragma once

#undef System
#undef Session
#undef Application
#undef Usr

#define System (*get_context_system()->m_pbasesystem)
#define Session (*get_context_session()->m_pbasesession)
#define Application (*get_app()->m_pbaseapplication)
#define Usr(pobject) (*Sess(pobject).user()->m_pbaseuser)


#include "base/user/experience/_const.h"


#include "base/user/user/_.h"


#include "base/user/experience/_.h"


#include "aura/platform/application_menu.h"


#include "aura/user/form_callback.h"


#include "base/platform/application.h"
#include "base/platform/session.h"
#include "base/platform/system.h"


#include "base/user/_.h"


#include "base/platform/_impl.h"






