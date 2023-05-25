//
//  screen.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 29/11/2022.
//  14:07
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"


#include "acme/_operating_system.h"


#include <CoreGraphics/CoreGraphics.h>


void screen_coordinates_aware_copy(CGRect & rectTarget, const ::rectangle_i32 & rectSource)
{

   CGRect rectWorkspace = mm_get_screen_cgrect();

   rectTarget.origin.x()       = rectSource.left;
   rectTarget.origin.y()       = rectWorkspace.size.height - rectSource.bottom;
   rectTarget.size.width     = rectSource.right - rectSource.left;
   rectTarget.size.height    = rectSource.bottom - rectSource.top;

}


void screen_coordinates_aware_copy(::rectangle_i32 & rectTarget, const CGRect & rectSource)
{

   CGRect rectWorkspace = mm_get_screen_cgrect();

   rectTarget.left        = rectSource.origin.x();
   rectTarget.bottom      = rectWorkspace.size.height - rectSource.origin.y();
   rectTarget.right       = rectTarget.left + rectSource.size.width;
   rectTarget.top         = rectTarget.bottom - rectSource.size.height;

}



