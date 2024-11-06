// Created by camilo on 2023-06-29 19:24 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "rectangle_array.h"


CLASS_DECL_ACME ::int_rectangle_array get_top_left_oriented_damaged_areas_by_resizing(const ::int_rectangle & rectangleNew, const ::int_rectangle & rectangleOld, bool bOnlyGrowing)
{

   auto rectangleBefore = rectangleOld;

   rectangleBefore.move_to({ 0, 0 });

   auto rectangleAfter = rectangleNew;

   rectangleAfter.move_to({ 0, 0 });

   if (!bOnlyGrowing && rectangleBefore.contains(rectangleAfter))
   {

      return {};

   }

   int_rectangle_array rectanglea;

   {

      // Right
      auto rectangleRight = rectangleAfter;
      rectangleRight.left() = rectangleBefore.right();
      rectangleRight.bottom() = ::minimum(rectangleBefore.bottom(), rectangleAfter.bottom());

      if (!bOnlyGrowing)
      {

         rectangleRight.normalize();

      }

      if (rectangleRight.is_set())
      {

         rectanglea.add(rectangleRight);

      }

   }

   {

      // Bottom
      auto rectangleBottom = rectangleAfter;
      rectangleBottom.top() = rectangleBefore.bottom();

      if (!bOnlyGrowing)
      {

         rectangleBottom.normalize();

      }

      if (rectangleBottom.is_set())
      {

         rectanglea.add(rectangleBottom);

      }

   }

   return ::transfer(rectanglea);

}



