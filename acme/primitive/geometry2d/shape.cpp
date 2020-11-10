//
//  shape.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/20.
//  Copyright © 2020 Camilo Sasuke Tsumanuma. All rights reserved.
//

#include "framework.h"


bool ___shape::expand_bounding_rect(RECTD* prect) const
{

   rectd r;

   if (!get_bounding_rect(&r))
   {

      return false;

   }

   expand_rect(prect, r);

   return true;

}


bool ___shape::expand_bounding_rect(RECT32* prect) const
{

   rectd r;

   if (!expand_bounding_rect(&r))
   {

      return false;

   }

   expand_rect(prect, r);

   return true;

}


bool ___shape::get_bounding_rect(RECTD* prect) const
{

   ::null_rect(prect);

   return false;

}


bool ___shape::get_bounding_rect(RECT32* prect) const
{

   ::null_rect(prect);

   return false;

}


bool ___shape::contains(const ::pointd& point) const
{

   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   ::rectd r;

   if (!get_bounding_rect(r))
   {

      return false;

   }

   return r.contains(point);

}