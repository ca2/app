// Created by camilo on 2024-03-11 03:53 <3ThomasBorregaardSorensen!!
#pragma once


namespace nanoui
{


   class in_place_edit;


   class CLASS_DECL_NANOUI in_place_edit_mapper
   {
   public:

      virtual ::f32_point inner_to_outer(const ::f32_point& point, in_place_edit*);
      virtual ::f32_point outer_to_inner(const ::f32_point& point, in_place_edit*);


      virtual ::f32_rectangle inner_to_outer(const ::f32_rectangle& rectangle, in_place_edit*);

    
   };



} // namespace nanoui




