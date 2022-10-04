//
//  _apple.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/02/20.
//

#pragma once


#include <CoreGraphics/CoreGraphics.h>


#include "_apple_no_templates.h"



#if defined(__APPLE__)


CFDataRef get_os_cf_data(const memory_base & memory, memsize pos = 0, memsize size = -1);
void set_os_cf_data(memory_base & memory, CFDataRef data, memsize pos = 0, memsize size = -1);


#endif


string apple_error_string(OSStatus status);

string apple_error_description(OSStatus status);



