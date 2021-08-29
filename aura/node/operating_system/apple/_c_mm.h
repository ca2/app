//
//  apple.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//
#pragma once

// C and Objective-C include

#ifdef __OBJC__
//#include "acme/node/operating_system/apple/NSObject+DDExtensions.h"
//#include "acme/node/operating_system/apple/DDInvocationGrabber.h"

char * ns_string(NSString * str);

#endif
//
//CGRect mm_get_workspace_rect();


void copy(CGRect * prectTarget, const RECTANGLE_I32 * prectSource);
void copy(RECTANGLE_I32 * prectTarget, const CGRect * prectSource);
void copy(CGRect * prectTarget, const RECTANGLE_F64 * prectSource);
void copy(RECTANGLE_F64 * prectTarget, const CGRect * prectSource);
void window_copy(CGRect * prectTarget, const RECTANGLE_I32 * prectSource);
void window_copy(RECTANGLE_I32 * prectTarget, const CGRect * prectSource);

#ifdef MM

void copy(NSRect & rectangle, const RECTANGLE_I32 * lpcrect);
void copy(RECTANGLE_I32 * lprect, const NSRect & rectangleSource);
void window_copy(NSRect & rectangle, const RECTANGLE_I32 * lpcrect);
void window_copy(RECTANGLE_I32 * lprect, const NSRect & rectangleSource);

#endif


#include "graphics.h"
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
