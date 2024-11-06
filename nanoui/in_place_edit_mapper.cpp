// Create by camilo on 2024-03-11 03:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "in_place_edit_mapper.h"


namespace nanoui
{


   ::float_point in_place_edit_mapper::inner_to_outer(const ::float_point& point, in_place_edit*)
   {

      return point;

   }
   
   
   ::float_point in_place_edit_mapper::outer_to_inner(const ::float_point& point, in_place_edit*)
   {

      return point;

   }


   ::float_rectangle in_place_edit_mapper::inner_to_outer(const ::float_rectangle& rectangle, in_place_edit* pinplaceedit)
   {
      
      auto top_left = rectangle.top_left();

      auto bottom_right = rectangle.bottom_right();

      ::float_rectangle rectangleOuter;

      rectangleOuter.top_left() = inner_to_outer(top_left, pinplaceedit);

      rectangleOuter.bottom_right() = inner_to_outer(bottom_right, pinplaceedit);

      return rectangleOuter;

   }


} // namespace nanoui



