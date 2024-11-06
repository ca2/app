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


      void get_text_extent(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, ::double_size_array & sizea);

      void get_text_extent(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, double_size & size);

      //void get_text_extent(::draw2d::graphics_pointer & pgraphics, const ::string & pcwsz, character_count iCount, int_size & size);


      void text_out(::draw2d::graphics_pointer & pgraphics, int x, int y, const ::scoped_string & scopedstr, double_size & s);


      //void FillSolidRect(HDC hdc, const ::i64_rectangle * prectangle, ::color::color clr);

      //void FillSolidRect(HDC hdc, const ::int_rectangle & rectangle, ::color::color clr);

      //void FillSolidRect(HDC hdc, int x, int y, int cx, int cy, ::color::color clr);

      //static int _FindPrefixV1(const unichar * pcsz);


   };


} // namespace draw2d



