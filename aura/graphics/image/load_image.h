// Enhanced by camilo on 2026-07-21 00:30 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// Created by camilo on 2021-08-24 23:40 <3ThomasBS_!!
#pragma once


#include "acme/graphics/image/pixmap_lease.h"
#include "aura/graphics/image/load_options.h"
//class load_image_interface;


namespace image
{


   class CLASS_DECL_AURA load_image :
      virtual public ::particle
   {
   public:


      ::image::load_options                              m_loadoptions;
      ::pointer<::image::image_context>                  m_pimagecontext;
      ::payload                                          m_payload;
      ::i32                                              m_iRedLower = 0;
      ::i32_size                                         m_sizePreferred;
      bool                                               m_bCreateHelperMaps = false;
      //::pointer<::load_image_interface>                  m_ploadimageinterface;
      //::image::image_pointer                             m_pimage2;
      //::pixmap_pointer                                   m_ppixmap;
      ::pointer <::image::image_frame_array>             m_pimageframearray;
      ::function < void(::image::load_image *) >         m_functionLoaded;


      //load_image(::image::image_context * pimagecontext);
      load_image();
      ~load_image() override;


      virtual void initialize_load_image(::image::image_context *pimagecontext, ::pixmap * ppixmapCallback);
      virtual void initialize_load_image(::image::image_context *pimagecontext, const ::function < void(::image::load_image *) > & functionLoaded);


      virtual pixmap * allocate_pixmap();
      virtual pixmap * create_pixmap(const ::i32_size & size, ::i32 iScan = 0);
      virtual pixmap * create_pixmap_from_data(const ::i32_size & size, const image32_t * pimage32, ::i32 iScan = 0);

      
      virtual void nanosvg(const ::block & blockXml, ::f64 dDpi = 0.);

      
      //virtual void create_nanosvg(char_pointer pszXml, ::i32 iRedLower, ::i32 width, ::i32 height);


      void run() override;


      virtual void on_load_image(const ::i32_size &size, const image32_t *pimage32, int iScan);


      virtual void on_image_loaded(const ::e_status &estatus);


   };



} // namespace image


