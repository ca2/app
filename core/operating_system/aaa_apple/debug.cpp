//
//  apple_debug.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 06/01/18.
//

#include "debug.h"

void throw_ns_exception()
{
   
   throw ::exception(ns_exception());
   
}


char * mm_error_string(OSStatus status);

char * mm_error_description(OSStatus status);


string apple_error_string(OSStatus status)
{
   
   return string_from_strdup(mm_error_string(status));
   
}


string apple_error_description(OSStatus status)
{
   
   return string_from_strdup(mm_error_description(status));
   
}


