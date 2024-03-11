// From connector.h by camilo on 2024-03-11 02:24 <3ThomasBorregaardSorensen!!
#pragma once


#include "in_place_edit.h"


namespace nanoui
{


   class CLASS_DECL_NANOUI in_place_edit_array :
      virtual public ::pointer_array < in_place_edit >
   {
   public:


      in_place_edit_array();
      ~in_place_edit_array() override;


      ::pointer < in_place_edit > hit_test_label(const ::point_f32& point, in_place_edit_mapper * pmapper) const;


   };


} // namespace RedDotLogics_PixelPerfectPro



