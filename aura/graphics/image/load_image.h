// Enhanced by camilo on 2026-07-21 00:30 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// Created by camilo on 2021-08-24 23:40 <3ThomasBS_!!
#pragma once



//#include "acme/prototype/prototype/payload.h"
class load_image_interface;

namespace image
{


   class CLASS_DECL_AURA load_image :
      virtual public ::particle
   {
   public:


      ::payload                                          m_payload;
      ::pointer<::load_image_interface>                  m_ploadimageinterface;
      //::image::image_pointer                             m_pimage2;
      ::pixmap_pointer                                   m_ppixmap;
      ::pointer<::image::image_context>                  m_pimagecontext;
      ::function < void(::pixmap *) >                    m_functionLoaded;
      ::i32_size                                         m_sizePreferred;
      bool                                               m_bCreateHelperMaps = false;


      //load_image(::image::image_context * pimagecontext);
      load_image();
      ~load_image() override;


      virtual void initialize_load_image(::image::image_context *pimagecontext, ::pixmap * ppixmap);


      virtual image32_t * defer_image32(const ::i32_size &size, ::i32 * piScan = nullptr);

      
      virtual void on_load_image(const image32_t *pimage32, const ::i32_size &size, int iScan);


      virtual void on_image_loaded(const ::e_status &estatus);


      virtual void nanosvg(char_pointer pszXml, ::i32 iRedLower, ::f64 dDpi = 0.);

      
      //virtual void create_nanosvg(char_pointer pszXml, ::i32 iRedLower, ::i32 width, ::i32 height);


      void run() override;


   };



} // namespace image


