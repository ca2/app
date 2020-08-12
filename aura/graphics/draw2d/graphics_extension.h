#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA graphics_extension :
      virtual public ::object
   {
   public:


      graphics_extension();
      virtual ~graphics_extension();


      void GetTextExtent(::draw2d::graphics_pointer & pgraphics, const char * pcwsz, ::size_array & sizea);

      void GetTextExtent(::draw2d::graphics_pointer & pgraphics, const char * pcwsz, size & size);

      void GetTextExtent(::draw2d::graphics_pointer & pgraphics, const char * pcwsz, strsize iCount, size & size);


      bool text_out(::draw2d::graphics_pointer & pgraphics, i32 x, i32 y, const char * pcwsz, strsize iCount,size & s);


      //void FillSolidRect(HDC hdc, const RECT64 * prect, COLORREF clr);

      //void FillSolidRect(HDC hdc, const ::rect & rect, COLORREF clr);

      //void FillSolidRect(HDC hdc, i32 x, i32 y, i32 cx, i32 cy, COLORREF clr);

      //static i32 _FindPrefixV1(const unichar * pcsz);


   };


} // namespace draw2d



