// Create by camilo on 2024-03-11 03:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "in_place_edit_mapper.h"


namespace nanoui
{


   ::f32_point in_place_edit_mapper::inner_to_outer(const ::f32_point& point, in_place_edit*)
   {

      return point;

   }
   
   
   ::f32_point in_place_edit_mapper::outer_to_inner(const ::f32_point& point, in_place_edit*)
   {

      return point;

   }


   ::f32_rectangle in_place_edit_mapper::inner_to_outer(const ::f32_rectangle& rectangle, in_place_edit* pinplaceedit)
   {
      
      auto top_left = rectangle.top_left();

      auto bottom_right = rectangle.bottom_right();

      ::f32_rectangle rectangleOuter;

      rectangleOuter.top_left() = inner_to_outer(top_left, pinplaceedit);

      rectangleOuter.bottom_right() = inner_to_outer(bottom_right, pinplaceedit);

      return rectangleOuter;

   }


} // namespace nanoui



