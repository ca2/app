//
//  apple_debug.hpp
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 06/01/18.
//
#pragma once


#undef DEBUG
#include <Carbon/Carbon.h>


void throw_ns_exception();

string apple_error_string(OSStatus status);

string apple_error_description(OSStatus status);

