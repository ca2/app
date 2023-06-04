// From geometry2d/align.h by camilo on 2022-10-19 23:25 <3ThomasBorregaardSørensen!!
#pragma once


enum enum_orientation
{

   e_orientation_horizontal = 0,
   e_orientation_vertical = 1,
   e_orientation_z = 2,
   e_orientation_w = 3,

};


constexpr ::index index_of(enum_orientation eorientation)
{

   return (::index) eorientation;

}


constexpr enum_orientation orthogonal2_of(enum_orientation eorientation)
{

   return eorientation == e_orientation_horizontal ? e_orientation_vertical : e_orientation_horizontal;

}

constexpr ::index orthogonal2_index_of(enum_orientation eorientation)
{

   return eorientation == e_orientation_horizontal ? 1 : 0;

}



enum enum_align
{

   e_align_none = 0,
   e_align_left = 1,
   e_align_top = 2,
   e_align_bottom = 4,
   e_align_right = 8,
   e_align_vertical_center = 16,
   e_align_horizontal_center = 32,
   e_align_horizontal = e_align_left | e_align_right | e_align_horizontal_center,
   e_align_vertical = e_align_bottom | e_align_top | e_align_vertical_center,
   e_align_top_left = e_align_top | e_align_left,
   e_align_top_right = e_align_top | e_align_right,
   e_align_bottom_left = e_align_bottom | e_align_left,
   e_align_bottom_right = e_align_bottom | e_align_right,
   e_align_top_center = e_align_top | e_align_horizontal_center,
   e_align_bottom_center = e_align_bottom | e_align_horizontal_center,
   e_align_left_center = e_align_left | e_align_vertical_center,
   e_align_right_center = e_align_right | e_align_vertical_center,
   e_align_center = e_align_horizontal_center | e_align_vertical_center,
   e_align_bottom_right_bias = e_align_center | e_align_bottom_right,

};


namespace design
{


   enum enum_fit
   {


      e_fit_width = -1,
      e_fit_match = 0,
      e_fit_height = 1,


   };


   enum enum_match
   {

      e_match_width = -1,
      e_match_none = 0,
      e_match_height = 1,

   };


} // namespace design



