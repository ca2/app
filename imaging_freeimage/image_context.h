#pragma once


#include "aura/graphics/image/image_context.h"


#include <FreeImage.h>


namespace imaging_freeimage
{


   class CLASS_DECL_IMAGING_FREEIMAGE image_context :
      virtual public ::image_context
   {
   public:


      image_context();
      ~image_context() override;


      virtual void _load_image(::image::image *pimageParam, const ::payload & payloadFile, const image::load_options & loadoptions) override;

      virtual void _load_image(::image::image *pimage, ::pointer<image_frame_array>& pframea, memory & memory) override;
      virtual void save_image(memory & memory, ::image::image *pimage, const ::save_image * psaveimage) override;
      //void load_svg(::image::image *pimage, memory & memory) override;

      //virtual void _load_image(::particle * pparticle, image_frame_array * pimageframea, const ::memory & memory);


   };


   CLASS_DECL_IMAGING_FREEIMAGE FIBITMAP * freeimage_from_image(const ::image::image *pimage);
   CLASS_DECL_IMAGING_FREEIMAGE bool image_from_freeimage(::image::image *pimage, FIBITMAP * pfibitmap);


} // namespace imaging_freeimage



