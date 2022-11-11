// From draw2d component by camilo on 2022-08-28 16:57 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/geometry2d/_collection.h"


namespace write_text
{


   class CLASS_DECL_AURA glyph
   {
   public:


      ::u32   m_ui;

      array <point_i32_array, point_i32_array &> m_pointsets;
//
//#ifdef WINDOWS_DESKTOP
//
//      GLYPHMETRICS   m_gm;
//
//#endif


      glyph();
      virtual ~glyph();


      void DrawGlyph(::draw2d::graphics_pointer & pgraphics, bool bFill, double dRateX, POINT_I32 * ppointoffset);


//#ifdef WINDOWS_DESKTOP
//
//      void Initialize(LPTTPOLYGONHEADER pph, u32 cbSize, i32 iFontHiHeight);
//
//
//#endif

      void GetGlyphRect(i32 x, i32 y, RECTANGLE_I32 * prectangle);


      void clear();

      glyph & operator = (const glyph & glyph);

      bool operator <= (const glyph & glyph) const;


   };


} // namespace write_text



