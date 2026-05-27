#pragma once


#include "acme/_operating_system.h"


#include "aura/graphics/write_text/font.h"

namespace typeface_freetype
{


   class CLASS_DECL_TYPEFACE_FREETYPE font : 
      virtual public ::write_text::font
   {
   public:

      
      //HDC                           m_hdcFont;
      //HFONT                         m_hfont;
      //GLuint	                     m_baseFont;				// Base Display List For The Font Set

//#ifdef WINDOWS
//      GLYPHMETRICSFLOAT             m_gmf[256];	// Storage For Information About Our Outline Font Characters
//#endif
//
      // settings
      //const ::u32 SCR_WIDTH = 800;
      //const ::u32 SCR_HEIGHT = 600;

      ::pointer < face > m_pface;
     
      font();
      ~font() override;


      void construct(const ::write_text::font & pfontParam);

      
      // void dump(dump_context & dumpcontext) const override;


      void create(::draw2d::graphics* pgraphics, ::i8 iCreate) override;
      void destroy() override;


   };


} // namespace typeface_freetype



