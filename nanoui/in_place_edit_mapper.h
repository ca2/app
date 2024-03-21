// Created by camilo on 2024-03-11 03:53 <3ThomasBorregaardSorensen!!
#pragma once


namespace nanoui
{


   class in_place_edit;


   class CLASS_DECL_NANOUI in_place_edit_mapper
   {
   public:

      virtual ::point_f32 inner_to_outer(const ::point_f32& point, in_place_edit*);
      virtual ::point_f32 outer_to_inner(const ::point_f32& point, in_place_edit*);


      virtual ::rectangle_f32 inner_to_outer(const ::rectangle_f32& rectangle, in_place_edit*);

    
   };



} // namespace nanoui




