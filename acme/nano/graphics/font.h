//
// Created by camilo on 31/01/2022 14:43 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "object.h"

namespace nano
{
   
   namespace graphics
   {
      

      class CLASS_DECL_ACME font :
         virtual public ::nano::graphics::object
      {
      public:


         ::pointer < font_family >     m_pfontfamily;
         ::f32                         m_fFontSize;
         bool                          m_bPixelSize;
         bool                          m_bBold;
         bool                          m_bItalic;
         bool                          m_bUnderline;


         font();
         ~font();


         virtual void create_point_font(font_family * pfontfamily, ::f64 fPointSize, bool bBold = false, bool bItalic = false, bool bUnderline = false);
         virtual void create_pixel_font(font_family * pfontfamily, ::f64 fPixelSize, bool bBold = false, bool bItalic = false, bool bUnderline = false);




      };


   } // namespace graphics


} // namespace nano



