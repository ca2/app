#pragma once

//meta
//orto
//para


#include "acme/graphics/image/pixmap.h"


#include "aura/graphics/draw2d/bitmap.h"


#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


#include "aura/graphics/image/extension.h"


#include "aura/graphics/image/dynamic.h"


#define IMAGE_IMAGE_META_TRANSFER(a) \
::image::image_meta(::transfer(a)), \
PIXMAP_TRANSFER(a)


namespace image
{


   class CLASS_DECL_AURA image_meta :
      virtual public ::pixmap
   {
   public:


      ::pointer<::draw2d::bitmap>               m_pbitmap;
      //::draw2d::graphics_pointer              m_pgraphics2;
      ::draw2d::graphics_pointer                m_pgraphicsOwned;
      ::f64                                    m_dSpeed;
      ::f64                                    m_dIsotropicRate;
      //::i32_size                                m_sizeAlloc;
      //i32_point                                 m_point;
      ::f64                                    m_dSizeScaler;
      //::draw2d::enum_alpha_mode               m_ealphamode;
      bool                                      m_bOwn;
      ::image::enum_mipmap                      m_emipmap;
      ::collection::index                       m_iFrame;
      ::i32                                       m_iExifOrientation;
      bool                                      m_bCreateHelperMaps;
      ::pointer<::image::image_extension>       m_pextension;
      image_dynamic                             m_dynamic;


      image_meta()
      {

         //m_uImageFlags = DEFAULT_CREATE_IMAGE_FLAGS;
         m_dSpeed = 1.0;
         m_dIsotropicRate = 1.0;
         m_dSizeScaler = 1.0;
         //m_ealphamode = ::draw2d::e_alpha_mode_blend;
         m_bOwn = true;
         m_emipmap = ::image::e_mipmap_none;
         m_iFrame = 0;
         m_bCreateHelperMaps = false;
         m_pbitmap = nullptr;
         m_iExifOrientation = 0;
         //m_pgraphics = nullptr;

      }

      image_meta(image_meta && imagemeta) :
         PIXMAP_TRANSFER(imagemeta),
         m_pbitmap(::transfer(imagemeta.m_pbitmap)),
         m_pgraphicsOwned(::transfer(imagemeta.m_pgraphicsOwned)),
         m_dSpeed(::transfer(imagemeta.m_dSpeed)),
         m_dIsotropicRate(::transfer(imagemeta.m_dIsotropicRate)),
         m_dSizeScaler(::transfer(imagemeta.m_dSizeScaler)),
         m_bOwn(::transfer(imagemeta.m_bOwn)),
         m_emipmap(::transfer(imagemeta.m_emipmap)),
         m_iFrame(::transfer(imagemeta.m_iFrame)),
         m_iExifOrientation(::transfer(imagemeta.m_iExifOrientation)),
         m_bCreateHelperMaps(::transfer(imagemeta.m_bCreateHelperMaps)),
         m_pextension(::transfer(imagemeta.m_pextension)),
         m_dynamic(::transfer(imagemeta.m_dynamic))
      {

         imagemeta.m_dSpeed = 0.;
         imagemeta.m_dIsotropicRate = 0.;
         imagemeta.m_dSizeScaler = 0.;
         imagemeta.m_bOwn = false;
         imagemeta.m_emipmap = e_mipmap_none;
         imagemeta.m_iFrame = 0;
         imagemeta.m_iExifOrientation = 0;
         imagemeta.m_bCreateHelperMaps = false;

      }

      ~image_meta();


      //inline ::pointer<::image::image_frame_array>frames();

      void set_exif_orientation(::i32 iExifOrientation) override;


      inline image_frame_array * frames() { return m_pextension ? m_pextension->m_pframea : nullptr; }

   };
} // namespace image


