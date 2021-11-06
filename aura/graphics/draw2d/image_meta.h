#pragma once

//meta
//orto
//para


class CLASS_DECL_AURA image_meta :
   public ::pixmap
{
public:


   ::draw2d::bitmap_pointer         m_pbitmap;
   ::draw2d::graphics_pointer       m_pgraphics;
   double                           m_dSpeed;
   double                           m_dIsotropicRate;
   ::size_i32                       m_sizeAlloc;
   point_i32                        m_point;
   double                           m_dFontFactor;
   ::draw2d::enum_alpha_mode        m_ealphamode;
   bool                             m_bOwn;
   ::draw2d::e_mipmap               m_emipmap;
   index                            m_iFrame;
   int                              m_iExifOrientation;
   bool                             m_bCreateHelperMaps;
   __pointer(::image_extension)     m_pextension;
   image_dynamic                    m_dynamic;


   image_meta() :
      m_sizeAlloc(0, 0),
      m_point(0, 0)
   {

      //m_uImageFlags = DEFAULT_CREATE_IMAGE_FLAGS;
      m_dSpeed = 1.0;
      m_dIsotropicRate = 1.0;
      m_dFontFactor = 1.0;
      m_ealphamode = ::draw2d::e_alpha_mode_blend;
      m_bOwn = true;
      m_emipmap = ::draw2d::mipmap_none;
      m_iFrame = 0;
      m_bCreateHelperMaps = false;

   }


   ~image_meta()
   {

   }


   inline __pointer(::image_frame_array) frames();


};



