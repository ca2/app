//
//  macos_mm.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once

#include "aura/include/_no_templates.h"

#import <Foundation/Foundation.h>

#ifdef MACOS

#import <AppKit/AppKit.h>

#endif

#ifdef APPLE_IOS

#import <UIKit/UIKit.h>

#endif

//#ifdef MACOS
//
////#include "aura/os/macos/mm_oswindow.h"
////#include "aura/os/macos/windowing.h"
//
//#elif defined(APPLE_IOS)
//
//#include "aura/operating_system/ios/mm_oswindow.h"
//#include "aura/operating_system/ios/windowing.h"
//
//#else
//
//#error "Not implemented... (not MACOS, not APPLE_IOS, but __APPLE__ ?)"
//
//#endif


#undef _

#define _(str) (__ns_get_text(str))

NSString * __ns_get_text(NSString * str);
NSString * __ns_get_text(const ::string & psz);



