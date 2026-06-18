// From draw2d component by camilo on 2022-08-28 16:57 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/geometry2d/_collection.h"


namespace write_text
{


   class CLASS_DECL_AURA glyph :
      virtual public ::subparticle
   {
   public:


      ::u32   m_u32;

      array_base <i32_point_array_base > m_pointsets;
//
//#ifdef WINDOWS_DESKTOP
//
//      GLYPHMETRICS   m_gm;
//
//#endif


      glyph();
      ~glyph() override;


      void DrawGlyph(::draw2d::graphics_pointer & pgraphics, bool bFill, ::f64 dRateX, ::i32_point * ppointoffset);


//#ifdef WINDOWS_DESKTOP
//
//      void Initialize(LPTTPOLYGONHEADER pph, ::u32 cbSize, ::i32 iFontHiHeight);
//
//
//#endif

      void GetGlyphRect(::i32 x, ::i32 y, ::i32_rectangle * prectangle);


      void clear();

      glyph & operator = (const glyph & glyph);

      bool operator <= (const glyph & glyph) const;


   };


} // namespace write_text



