//
//  shape.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "framework.h"


bool ___shape::expand_bounding_rect(RECTANGLE_F64* prectangle) const
{

   rectangle_f64 r;

   if (!get_bounding_rect(&r))
   {

      return false;

   }

   expand_rect(prectangle, r);

   return true;

}


bool ___shape::expand_bounding_rect(RECTANGLE_I32* prectangle) const
{

   rectangle_f64 r;

   if (!expand_bounding_rect(&r))
   {

      return false;

   }

   expand_rect(prectangle, r);

   return true;

}


bool ___shape::get_bounding_rect(RECTANGLE_F64* prectangle) const
{

   ::null_rect(prectangle);

   return false;

}


bool ___shape::get_bounding_rect(RECTANGLE_I32* prectangle) const
{

   ::null_rect(prectangle);

   return false;

}


bool ___shape::contains(const ::point_f64& point) const
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectangle_f64 r;

   if (!get_bounding_rect(r))
   {

      return false;

   }

   return r.contains(point);

}