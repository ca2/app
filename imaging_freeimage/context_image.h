#pragma once


#include "aura/graphics/image/context_image.h"


#include <FreeImage/FreeImage.h>


namespace imaging_freeimage
{


   class CLASS_DECL_IMAGING_FREEIMAGE context_image :
      virtual public ::context_image
   {
   public:


      context_image();
      ~context_image() override;


      virtual void _load_image(::image * pimageParam, const ::payload & payloadFile, const image::load_options & loadoptions) override;

      virtual void _load_image(::image * pimage, ::pointer<image_frame_array>& pframea, memory & memory) override;
      virtual void save_image(memory & memory, ::image * pimage, const ::save_image * psaveimage) override;
      //void load_svg(::image * pimage, memory & memory) override;

      //virtual void _load_image(::particle * pparticle, image_frame_array * pimageframea, const ::memory & memory);


   };


   CLASS_DECL_IMAGING_FREEIMAGE FIBITMAP * freeimage_from_image(const ::image * pimage);
   CLASS_DECL_IMAGING_FREEIMAGE bool image_from_freeimage(::image * pimage, FIBITMAP * pfibitmap);


} // namespace imaging_freeimage



