//
//  mm_graphics.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 21/05/20.
//

#include "_mm.h"



::f64 pixels_to_points(::f64 d)
{
   
   
   
   return d / [[UIScreen mainScreen] scale];

}


::f64 points_to_pixels(::f64 d)
{
   
   return d * [[UIScreen mainScreen] scale];

}


::f64 status_bar_height()
{
    CGSize statusBarSize = [[UIApplication sharedApplication] statusBarFrame].size;
    return min(statusBarSize.width, statusBarSize.height);
}
