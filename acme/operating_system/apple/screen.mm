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


CGRect g_rectScreen;


void mm_on_update_screen()
{
   
   g_rectScreen = [ [ NSScreen mainScreen ] frame];
   
}


CGRect mm_get_screen_cgrect()
{
   
   mm_on_update_screen();

   return g_rectScreen;

}


::rectangle_i32 get_main_screen_rectangle()
{
   
   ::rectangle_i32 rectangle{};
   
   screen_coordinates_aware_copy(rectangle, g_rectScreen);
   
   return rectangle;
   
}
