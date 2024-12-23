//
//  screen.m
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/2022.
//  14:11
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"


#include "acme/_operating_system.h"


#import <Foundation/Foundation.h>
#if defined(MACOS)
#import <Cocoa/Cocoa.h>
#elif defined(APPLE_IOS)
#import <UIKit/UIKit.h>
#else
#error "todo"
#endif
#include "acme/prototype/geometry2d/rectangle.h"


CGRect g_rectScreen;


void mm_on_update_screen()
{
   
#ifdef APPLE_IOS

   g_rectScreen = [ [ UIScreen mainScreen ] nativeBounds];

#else
   
   g_rectScreen = [ [ NSScreen mainScreen ] frame];
   
#endif
   
}


CGRect mm_get_screen_cgrect()
{
   
   mm_on_update_screen();

   return g_rectScreen;

}


::int_rectangle get_main_screen_rectangle()
{
   
   ::int_rectangle rectangle{};
   
   screen_coordinates_aware_copy(rectangle, g_rectScreen);
   
   return rectangle;
   
}



