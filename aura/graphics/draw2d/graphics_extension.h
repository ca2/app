#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA graphics_extension :
      virtual public ::object
   {
   public:


      graphics_extension();
      virtual ~graphics_extension();


      void get_text_extent(::draw2d::graphics_pointer & pgraphics, const char * pcwsz, ::size_array & sizea);

      void get_text_extent(::draw2d::graphics_pointer & pgraphics, const char * pcwsz, size_i32 & size);

      void get_text_extent(::draw2d::graphics_pointer & pgraphics, const char * pcwsz, strsize iCount, size_i32 & size);


      bool text_out(::draw2d::graphics_pointer & pgraphics, i32 x, i32 y, const char * pcwsz, strsize iCount,size_i32 & s);


      //void FillSolidRect(HDC hdc, const RECTANGLE_I64 * prectangle, ::color::color clr);

      //void FillSolidRect(HDC hdc, const ::rectangle_i32 & rectangle, ::color::color clr);

      //void FillSolidRect(HDC hdc, i32 x, i32 y, i32 cx, i32 cy, ::color::color clr);

      //static i32 _FindPrefixV1(const unichar * pcsz);


   };


} // namespace draw2d



