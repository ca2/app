#pragma once


#include "acme/prototype/geometry2d/size_array.h"
////#include "acme/prototype/prototype/object.h"


namespace draw2d
{


   class CLASS_DECL_AURA graphics_extension :
      virtual public ::object
   {
   public:


      graphics_extension();
      ~graphics_extension() override;


      void get_text_extent(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, ::f64_size_array & sizea);

      void get_text_extent(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, ::f64_size & size);

      //void get_text_extent(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstrcwsz, character_count iCount, i32_size & size);


      void text_out(::draw2d::graphics_pointer & pgraphics, ::i32 x, ::i32 y, const ::scoped_string & scopedstr, ::f64_size & s);


      //void FillSolidRect(HDC hdc, const ::i64_rectangle * prectangle, ::color::color clr);

      //void FillSolidRect(HDC hdc, const ::i32_rectangle & rectangle, ::color::color clr);

      //void FillSolidRect(HDC hdc, ::i32 x, ::i32 y, ::i32 cx, ::i32 cy, ::color::color clr);

      //static ::i32 _FindPrefixV1(const wide_character * pcsz);


   };


} // namespace draw2d



