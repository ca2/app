//
//  screen.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 29/11/2022.
//  14:07
//  Copyright (c) 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"


#include "acme/_operating_system.h"


#include "acme/prototype/geometry2d/rectangle.h"


#include <CoreGraphics/CoreGraphics.h>


void screen_coordinates_aware_copy(CGRect & rectTarget, const ::int_rectangle & rectSource)
{

   CGRect rectWorkspace = mm_get_screen_cgrect();

   cast_copy(rectTarget.origin.x, rectSource.left());
   cast_copy(rectTarget.origin.y, rectWorkspace.size.height - rectSource.bottom());
   cast_copy(rectTarget.size.width, rectSource.right() - rectSource.left());
   cast_copy(rectTarget.size.height, rectSource.bottom() - rectSource.top());

}


void screen_coordinates_aware_copy(::int_rectangle & rectTarget, const CGRect & rectSource)
{

   CGRect rectWorkspace = mm_get_screen_cgrect();

   cast_copy(rectTarget.left(), rectSource.origin.x);
   cast_copy(rectTarget.bottom(), rectWorkspace.size.height - rectSource.origin.y);
   cast_copy(rectTarget.right(), rectTarget.left() + rectSource.size.width);
   cast_copy(rectTarget.top(), rectTarget.bottom() - rectSource.size.height);

}


// void copy(CGRect & rectTarget, const ::int_rectangle & rectSource)
// {

//    rectTarget.origin.x       = rectSource.left();
//    rectTarget.origin.y       = rectSource.top();
//    rectTarget.size.width     = rectSource.right() - rectSource.left();
//    rectTarget.size.height    = rectSource.bottom() - rectSource.top();

// }


// void copy(::int_rectangle & rectTarget, const CGRect & rectSource)
// {

//    rectTarget.left()        = rectSource.origin.x;
//    rectTarget.top()         = rectSource.origin.y;
//    rectTarget.right()       = rectTarget.left() + rectSource.size.width;
//    rectTarget.bottom()      = rectTarget.top() + rectSource.size.height;

// }



