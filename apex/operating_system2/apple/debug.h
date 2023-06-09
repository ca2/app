//
//  apple_debug.hpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 06/01/18.
//
#pragma once


#undef DEBUG
#ifdef MACOS
#include <Carbon/Carbon.h>
#endif


void throw_ns_exception();

string apple_error_string(OSStatus status);

string apple_error_description(OSStatus status);

