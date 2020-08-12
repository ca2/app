//
//  macos_mm.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once


#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import <CoreGraphics/CoreGraphics.h>

template < typename T >
bool is_null(const T * pv)
{
   
   return ((unsigned long) pv) < sizeof(T);
   
}

#include "ios_m.h"


//#include "NSObject+DDExtensions.h"
//#include "DDInvocationGrabber.h"


#include "ios_windowing.h"
//#include "ios_mm_window.h"
//#include "ios_window_boot.h"
//#include "ios_mm_window_frame_view.h"
