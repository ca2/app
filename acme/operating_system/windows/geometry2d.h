//
// Created by camilo on 2026-02-10 23:52 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/prototype/geometry2d/rectangle.h"


namespace windows
{


   inline RECT as_RECT(const ::int_rectangle & rectangle)
   {

      if (rectangle.is_empty())
      {

         return {0, 0, 0, 0};

      }

      RECT r{rectangle.left, rectangle.top, rectangle.right, rectangle.bottom};

      return r;

   }


} // namespace windows


