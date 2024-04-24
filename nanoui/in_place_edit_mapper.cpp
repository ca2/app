// Create by camilo on 2024-03-11 03:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "in_place_edit_mapper.h"


namespace nanoui
{


   ::point_f32 in_place_edit_mapper::inner_to_outer(const ::point_f32& point, in_place_edit*)
   {

      return point;

   }
   
   
   ::point_f32 in_place_edit_mapper::outer_to_inner(const ::point_f32& point, in_place_edit*)
   {

      return point;

   }


   ::rectangle_f32 in_place_edit_mapper::inner_to_outer(const ::rectangle_f32& rectangle, in_place_edit* pinplaceedit)
   {
      
      auto top_left = rectangle.top_left();

      auto bottom_right = rectangle.bottom_right();

      ::rectangle_f32 rectangleOuter;

      rectangleOuter.top_left() = inner_to_outer(top_left, pinplaceedit);

      rectangleOuter.bottom_right() = inner_to_outer(bottom_right, pinplaceedit);

      return rectangleOuter;

   }


} // namespace nanoui



