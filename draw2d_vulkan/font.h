#pragma once


#include "acme/_operating_system.h"


#include "aura/graphics/write_text/font.h"


namespace draw2d_vulkan
{


   class CLASS_DECL_DRAW2D_VULKAN font : 
      virtual public ::write_text::font
   {
   public:

      
      HDC                           m_hdcFont;
      HFONT                         m_hfont;
//      VKuint	                     m_baseFont;				// Base Display List For The Font Set
//
//#ifdef WINDOWS
//      VKYPHMETRICSFLOAT             m_gmf[256];	// Storage For Information About Our Outline Font Characters
//#endif



      font();
      ~font() override;


      void construct(const ::write_text::font & pfontParam);

      
      // void dump(dump_context & dumpcontext) const override;


      void create(::draw2d::graphics* pgraphics, char iCreate) override;
      void destroy() override;


   };


} // namespace draw2d_vulkan



