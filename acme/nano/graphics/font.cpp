//
// Created by camilo on 31/01/2022 15:23 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "font.h"
#include "font_family.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"

namespace nano
{

   namespace graphics
   {

      font::font()
      {

         m_fFontSize = 12.0f;
         m_bPixelSize = false;
         m_bBold = false;
         m_bUnderline = false;

      }


      font::~font() {}


      void font::create_point_font(font_family * pfontfamily, ::f64 fPointSize, bool bBold, bool bItalic, bool bUnderline)
      {

         m_pfontfamily = pfontfamily;
         m_fFontSize = (::f32)fPointSize;
         m_bPixelSize = false;
         m_bBold = bBold;
         m_bItalic = bItalic;
         m_bUnderline = bUnderline;
         //throw ::interface_only();

         //::pointer<::nano::graphics::font>pwritetextfont(e_create, pparticle, nullptr);

         // pwritetextfont->m_iFontSize = iPoint;
         // pwritetextfont->m_strFontName = pparticle->node()->font_name(efont);
         // pwritetextfont->m_bBold = bBold;

         //  return pwritetextfont;
      }


      
      void font::create_pixel_font(font_family * pfontfamily, ::f64 fPixelSize, bool bBold, bool bItalic, bool bUnderline)
      {

         m_pfontfamily = pfontfamily;
         m_fFontSize = (::f32) fPixelSize;
         m_bPixelSize = true;
         m_bBold = bBold;
         m_bItalic = bItalic;
         m_bUnderline = bUnderline;
//         throw ::interface_only();

         //::pointer<::nano::graphics::font>pwritetextfont(e_create, pparticle, nullptr);

         // pwritetextfont->m_iFontSize = iPoint;
         // pwritetextfont->m_strFontName = pparticle->node()->font_name(efont);
         // pwritetextfont->m_bBold = bBold;

         //  return pwritetextfont;
      }

   } // namespace graphics


} // namespace nano
