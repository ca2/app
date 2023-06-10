#pragma once

//meta
//orto
//para


#include "pixmap.h"


#include "aura/graphics/draw2d/bitmap.h"


#include "aura/graphics/draw2d/graphics.h"


#include "extension.h"


#include "dynamic.h"


class CLASS_DECL_AURA image_meta :
   public ::pixmap
{
public:


   ::pointer<::draw2d::bitmap>      m_pbitmap;
   ::pointer<::draw2d::graphics>    m_pgraphics;
   double                           m_dSpeed;
   double                           m_dIsotropicRate;
   ::size_i32                       m_sizeAlloc;
   point_i32                        m_point;
   double                           m_dFontFactor;
   //::draw2d::enum_alpha_mode        m_ealphamode;
   bool                             m_bOwn;
   ::draw2d::enum_mipmap               m_emipmap;
   index                            m_iFrame;
   int                              m_iExifOrientation;
   bool                             m_bCreateHelperMaps;
   ::pointer<::image_extension>    m_pextension;
   image_dynamic                    m_dynamic;


   image_meta() :
      m_sizeAlloc(0, 0),
      m_point(0, 0)
   {

      //m_uImageFlags = DEFAULT_CREATE_IMAGE_FLAGS;
      m_dSpeed = 1.0;
      m_dIsotropicRate = 1.0;
      m_dFontFactor = 1.0;
      //m_ealphamode = ::draw2d::e_alpha_mode_blend;
      m_bOwn = true;
      m_emipmap = ::draw2d::e_mipmap_none;
      m_iFrame = 0;
      m_bCreateHelperMaps = false;
      m_pbitmap = nullptr;
      //m_pgraphics = nullptr;

   }


   ~image_meta();


   //inline ::pointer<::image_frame_array>frames();




   inline image_frame_array * frames() { return m_pextension ? m_pextension->m_pframea : nullptr; }

};



