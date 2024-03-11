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


} // namespace nanoui



