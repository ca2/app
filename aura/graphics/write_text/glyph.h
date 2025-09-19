// From draw2d component by camilo on 2022-08-28 16:57 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/geometry2d/_collection.h"


namespace write_text
{


   class CLASS_DECL_AURA glyph
   {
   public:


      unsigned int   m_ui;

      array <int_point_array_base > m_pointsets;
//
//#ifdef WINDOWS_DESKTOP
//
//      GLYPHMETRICS   m_gm;
//
//#endif


      glyph();
      virtual ~glyph();


      void DrawGlyph(::draw2d::graphics_pointer & pgraphics, bool bFill, double dRateX, ::int_point * ppointoffset);


//#ifdef WINDOWS_DESKTOP
//
//      void Initialize(LPTTPOLYGONHEADER pph, unsigned int cbSize, int iFontHiHeight);
//
//
//#endif

      void GetGlyphRect(int x, int y, ::int_rectangle * prectangle);


      void clear();

      glyph & operator = (const glyph & glyph);

      bool operator <= (const glyph & glyph) const;


   };


} // namespace write_text



