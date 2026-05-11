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

      array_base <int_poi32_array_base > m_pointsets;
//
//#ifdef WINDOWS_DESKTOP
//
//      GLYPHMETRICS   m_gm;
//
//#endif


      glyph();
      ~glyph() override;


      void DrawGlyph(::draw2d::graphics_pointer & pgraphics, bool bFill, double dRateX, ::i32_point * ppointoffset);


//#ifdef WINDOWS_DESKTOP
//
//      void Initialize(LPTTPOLYGONHEADER pph, ::u32 cbSize, int iFontHiHeight);
//
//
//#endif

      void GetGlyphRect(int x, int y, ::i32_rectangle * prectangle);


      void clear();

      glyph & operator = (const glyph & glyph);

      bool operator <= (const glyph & glyph) const;


   };


} // namespace write_text



