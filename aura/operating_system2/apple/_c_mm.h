//
//  apple.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 21/07/17.
//
//
#pragma once

// C and Objective-C include

#ifdef __OBJC__
//#include "acme/operating_system/apple/NSObject+DDExtensions.h"
//#include "acme/operating_system/apple/DDInvocationGrabber.h"

char * __strdup(NSString * str);

#endif
//
//CGRect mm_get_workspace_rect();


#include <CoreGraphics/CoreGraphics.h>


void copy(CGRect * prectTarget, const ::rectangle_i32 * prectSource);
void copy(::rectangle_i32 * prectTarget, const CGRect * prectSource);
void copy(CGRect * prectTarget, const ::rectangle_f64 * prectSource);
void copy(::rectangle_f64 * prectTarget, const CGRect * prectSource);
void screen_coordinates_aware_copy(CGRect * prectTarget, const ::rectangle_i32 * prectSource);
void screen_coordinates_aware_copy(::rectangle_i32 * prectTarget, const CGRect * prectSource);

#ifdef MM

void copy(NSRect & rectangle, const ::rectangle_i32 * lpcrect);
void copy(::rectangle_i32 * lprect, const NSRect & rectangleSource);
void screen_coordinates_aware_copy(NSRect & rectangle, const ::rectangle_i32 * lpcrect);
void screen_coordinates_aware_copy(::rectangle_i32 * lprect, const NSRect & rectangleSource);

#endif


//#include "graphics.h"
#include "ns_exception.h"
#include "time.h"
//
//void ns_launch_app(const ::string & psz, const ::string &* argv, int iFlags);
//bool ns_open_file(const ::string & psz);
//void ns_main_async(dispatch_block_t block);
//
//void apple_on_open_file(const ::string &* psza, int iCount, const ::string & pszExtra);
//void apple_accumulate_on_open_file(const ::string &* psza, int iCount, const ::string & pszExtra);
//void apple_on_new_file();
//
//
//void aura_application_main(int argc, char *argv[], const ::string & pszCommandLine);
//
//
//
//int is_window(oswindow window);
//
////void ns_main_sync(dispatch_block_t block, unsigned int uiMillis = -1);
////void ns_main_async(dispatch_block_t block);
//
