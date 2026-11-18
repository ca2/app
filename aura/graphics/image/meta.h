#pragma once

//meta
//orto
//para


#include "acme/graphics/image/pixmap.h"
#include "acme/filesystem/filesystem/path.h"


#include "aura/graphics/draw2d/bitmap.h"


#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


#include "aura/graphics/image/extension.h"


#include "aura/graphics/image/dynamic.h"
#include "aura/graphics/image/alpha_statistics.h"


// #define IMAGE_IMAGE_META_TRANSFER(a) \
// ::image::image_meta(::transfer(a)), \
// PARTICLE_TRANSFER(a)
//
// //PIXMAP_TRANSFER(a)


namespace image
{


   enum enum_image_derivation
   {

      e_image_derivation_none,
      e_image_derivation_stretched,

   };


   class CLASS_DECL_AURA image_meta :
      virtual public ::particle
   {
   public:


      bool                                      m_bGraphicsWasAcquiredAfterLastMap;
      bool                                      m_bWasMappedAfterLastGraphicsAcquisition;
      /// This flag is an optimization hint.
      /// It is not much literal.
      bool                                      m_bHintCpuBackingEnabled;
      ::i32_size                                m_size;
      ::i32_size                                m_sizeRaw;
      ::i32_point                               m_point;
      ::i32                                     m_iScan;
      ::image_pixmap_lease *                    m_pimagepixmaplease;
      ::draw2d::graphics_lease *                m_pgraphicslease;
      ::pointer<::draw2d::bitmap>               m_pdraw2dbitmap;
      ::pixmap_pointer                          m_ppixmapOwned;
      ::draw2d::graphics_pointer                m_pgraphicsOwned;
      //::draw2d::graphics_pointer              m_pgraphics2;
      ::f64                                     m_dSpeed;
      ::f64                                     m_dIsotropicRate;
      //::i32_size                              m_sizeAlloc;
      //i32_point                                 m_point;
      ::f64                                    m_dSizeScaler;
      //::draw2d::enum_alpha_mode               m_ealphamode;
      bool                                      m_bOwn;
      ::image::enum_mipmap                      m_emipmap;
      ::collection::index                       m_iFrame;
      ::pointer < ::image::image_frame >        m_pimageframeSource;
      ::i32                                     m_iExifOrientation;
      bool                                      m_bCreateHelperMaps;
      ::pointer<::image::image_extension>       m_pextension;
      image_dynamic                             m_dynamic;
      bool                                      m_bImageGraphics;
      ::image::alpha_statistics_cache          m_alphastatisticscache;
      /// Original file or URI that supplied these pixels, when loaded from a path.
      ::file::path                              m_pathImageSource;
      /// Immediate input size for a derived image.
      ::i32_size                                m_sizeImageSource;
      enum_image_derivation                     m_eImageDerivation = e_image_derivation_none;


      image_meta()
      {

         //m_uImageFlags = DEFAULT_CREATE_IMAGE_FLAGS;
         m_bHintCpuBackingEnabled = true;
         m_iScan = -1;
         m_bWasMappedAfterLastGraphicsAcquisition  = false;
         m_bGraphicsWasAcquiredAfterLastMap = false;
         m_pimagepixmaplease = nullptr;
         m_pgraphicslease = nullptr;
         m_dSpeed = 1.0;
         m_dIsotropicRate = 1.0;
         m_dSizeScaler = 1.0;
         m_bImageGraphics = false;
         //m_ealphamode = ::draw2d::e_alpha_mode_blend;
         m_bOwn = true;
         m_emipmap = ::image::e_mipmap_none;
         m_iFrame = 0;
         m_bCreateHelperMaps = false;
         m_pdraw2dbitmap = nullptr;
         m_iExifOrientation = 0;
         m_sizeImageSource = {};
         //m_pgraphics = nullptr;

      }

      // image_meta(image_meta && imagemeta) :
      //    PARTICLE_TRANSFER(imagemeta),
      //    m_bGraphicsWasAcquiredAfterLastMap(imagemeta.m_bGraphicsWasAcquiredAfterLastMap),
      //    m_size(imagemeta.m_size),
      //    m_sizeRaw(imagemeta.m_sizeRaw),
      //    m_point(imagemeta.m_point),
      //    m_iScan(imagemeta.m_iScan),
      //    m_pimagepixmaplease(nullptr),
      //    m_pgraphicslease(nullptr),
      //    m_pdraw2dbitmap(::transfer(imagemeta.m_pdraw2dbitmap)),
      //    m_ppixmapOwned(::transfer(imagemeta.m_ppixmapOwned)),
      //    m_pgraphicsOwned(::transfer(imagemeta.m_pgraphicsOwned)),
      //    m_dSpeed(::transfer(imagemeta.m_dSpeed)),
      //    m_dIsotropicRate(::transfer(imagemeta.m_dIsotropicRate)),
      //    m_dSizeScaler(::transfer(imagemeta.m_dSizeScaler)),
      //    m_bOwn(::transfer(imagemeta.m_bOwn)),
      //    m_emipmap(::transfer(imagemeta.m_emipmap)),
      //    m_iFrame(::transfer(imagemeta.m_iFrame)),
      //    m_iExifOrientation(::transfer(imagemeta.m_iExifOrientation)),
      //    m_bCreateHelperMaps(::transfer(imagemeta.m_bCreateHelperMaps)),
      //    m_pextension(::transfer(imagemeta.m_pextension)),
      //    m_dynamic(::transfer(imagemeta.m_dynamic))
      // {
      //
      //    if (imagemeta.m_pimagepixmaplease)
      //    {
      //
      //       throw ::exception(error_wrong_state);
      //
      //    }
      //
      //    if (imagemeta.m_pgraphicslease)
      //    {
      //
      //       throw ::exception(error_wrong_state);
      //
      //    }
      //
      //    imagemeta.m_pimagepixmaplease = nullptr;
      //    imagemeta.m_pgraphicslease = nullptr;
      //    imagemeta.m_dSpeed = 0.;
      //    imagemeta.m_dIsotropicRate = 0.;
      //    imagemeta.m_dSizeScaler = 0.;
      //    imagemeta.m_bOwn = false;
      //    imagemeta.m_emipmap = e_mipmap_none;
      //    imagemeta.m_iFrame = 0;
      //    imagemeta.m_iExifOrientation = 0;
      //    imagemeta.m_bCreateHelperMaps = false;
      //
      // }

      ~image_meta();


      //inline ::pointer<::image::image_frame_array>frames();

      virtual void set_exif_orientation(::i32 iExifOrientation);

      void set_image_source_path(const ::file::path & path);
      void set_stretched_from(const image_meta & imagemetaSource);
      ::string image_debug_provenance() const;


      inline image_frame_array * frames() { return m_pextension ? m_pextension->m_pframea : nullptr; }

      ::i32_size size() const {return m_size;}
      ::i32_size raw_size() const {return m_sizeRaw.is_empty() ? this->size() : m_sizeRaw;}
      ::i32 area() const {return this->size().area();}
      ::i32 width() const {return this->size().width();}
      ::i32 height() const {return this->size().height();}
      ::i32 minimum_scan() const {return this->size().width() * 4;}
      ::i32 scan() const {return m_iScan >= this->minimum_scan() ? m_iScan:this->minimum_scan();}
      ::i32 scan_in_pixels() const {return this->scan() / 4; }
      ::i32 scan_area_in_bytes() const {return this->scan() * height();}
      ::i32 scan_area_in_pixels() const {return this->scan_in_pixels() * height();}

   };


} // namespace image
