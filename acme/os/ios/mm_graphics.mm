//
//  mm_graphics.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 21/05/20.
//

#include "_mm.h"



double pixels_to_points(double d)
{
   
   
   
   return d / [[UIScreen mainScreen] scale];

}


double points_to_pixels(double d)
{
   
   return d * [[UIScreen mainScreen] scale];

}


double status_bar_height()
{
    CGSize statusBarSize = [[UIApplication sharedApplication] statusBarFrame].size;
    return MIN(statusBarSize.width, statusBarSize.height);
}
