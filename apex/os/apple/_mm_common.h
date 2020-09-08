//
//  macos_mm.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once

#include "apex/include/_no_templates.h"

#import <Foundation/Foundation.h>

#ifdef MACOS

#import <AppKit/AppKit.h>

#endif

#ifdef APPLE_IOS

#import <UIKit/UIKit.h>

#endif

#ifdef MACOS

#include "apex/os/macos/mm_oswindow.h"
#include "apex/os/macos/windowing.h"

#elif defined(APPLE_IOS)

#include "apex/os/ios/mm_oswindow.h"
#include "apex/os/ios/windowing.h"

#else

#error "Not implemented... (not MACOS, not APPLE_IOS, but APPLEOS ?)"

#endif


#undef _

#define _(str) (__ns_get_text(str))

NSString * __ns_get_text(NSString * str);
NSString * __ns_get_text(const char * psz);



