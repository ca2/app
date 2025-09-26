#pragma once


#include "aura/graphics/image/context.h"


#if defined(USE_PORT_FREEIMAGE)
#include <port_freeimage/FreeImage.h>
#else
#include <FreeImage.h>
#endif


namespace imaging_freeimage
{


   class CLASS_DECL_IMAGING_FREEIMAGE image_context :
      virtual public ::image::image_context
   {
   public:


      image_context();
      ~image_context() override;


      void _load_image(::image::image *pimageParam, const ::payload & payloadFile, const image::load_options & loadoptions) override;

      void _load_image(::image::image *pimage, ::pointer<::image::image_frame_array>& pframea, memory & memory) override;
      void save_image(memory & memory, ::image::image *pimage, const ::image::encoding_options & encodingoptions) override;
      //void load_svg(::image::image *pimage, memory & memory) override;

      //virtual void _load_image(::particle * pparticle, image_frame_array * pimageframea, const ::memory & memory);


   };


   CLASS_DECL_IMAGING_FREEIMAGE FIBITMAP * freeimage_from_image(const ::image::image *pimage);
   CLASS_DECL_IMAGING_FREEIMAGE bool image_from_freeimage(::image::image *pimage, FIBITMAP * pfibitmap);


} // namespace imaging_freeimage



