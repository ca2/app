// From connector.cpp by camilo on 2024-03-11 02:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "in_place_edit.h"
#include "in_place_edit_array.h"
#include "in_place_edit_mapper.h"


namespace nanoui
{


   in_place_edit_array::in_place_edit_array()
   {


   }


   in_place_edit_array::~in_place_edit_array()
   {


   }


   ::pointer < in_place_edit > in_place_edit_array::hit_test_label(const ::point_f32& point, in_place_edit_mapper* pmapper) const
   {

      for (auto& pinplaceedit : *this)
      {

         auto pointInternal = pmapper->outer_to_inner(point, pinplaceedit);

         if (pinplaceedit->m_rectangleInternal.contains(pointInternal))
         {

            return pinplaceedit;

         }

      }

      return {};

   }


} // namespace RedDotLogics_PixelPerfectPro



