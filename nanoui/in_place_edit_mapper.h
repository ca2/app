// Created by camilo on 2024-03-11 03:53 <3ThomasBorregaardSorensen!!
#pragma once


namespace nanoui
{


   class in_place_edit;


   class CLASS_DECL_NANOUI in_place_edit_mapper
   {
   public:

      virtual ::float_point inner_to_outer(const ::float_point& point, in_place_edit*);
      virtual ::float_point outer_to_inner(const ::float_point& point, in_place_edit*);


      virtual ::float_rectangle inner_to_outer(const ::float_rectangle& rectangle, in_place_edit*);

    
   };



} // namespace nanoui




