//
// Created by camilo on 31/01/2022 15:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "font.h"
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

         throw ::interface_only();

         //::pointer<::nano::graphics::font>pfont(e_create, pparticle, nullptr);

         // pfont->m_iFontSize = iPoint;
         // pfont->m_strFontName = pparticle->node()->font_name(efont);
         // pfont->m_bBold = bBold;

         //  return pfont;
      }


      
      void font::create_pixel_font(font_family * pfontfamily, ::f64 fPixelSize, bool bBold, bool bItalic, bool bUnderline)
      {

         throw ::interface_only();

         //::pointer<::nano::graphics::font>pfont(e_create, pparticle, nullptr);

         // pfont->m_iFontSize = iPoint;
         // pfont->m_strFontName = pparticle->node()->font_name(efont);
         // pfont->m_bBold = bBold;

         //  return pfont;
      }

   } // namespace graphics


} // namespace nano
