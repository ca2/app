#pragma once


#include "acme/_operating_system.h"


#include "bred/gpu/font.h"

namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL font : 
      virtual public ::gpu::font
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
      //const unsigned int SCR_WIDTH = 800;
      //const unsigned int SCR_HEIGHT = 600;

      ::pointer < face > m_pface;
     
      font();
      ~font() override;


      void construct(const ::write_text::font & pfontParam);

      
      // void dump(dump_context & dumpcontext) const override;


      void update(::draw2d::graphics * pdraw2dgraphics) override;
      void destroy() override;


   };


} // namespace draw2d_opengl



