#pragma once


#include "aura/graphics/draw2d/context_image.h"


namespace imaging_freeimage
{


   class CLASS_DECL_IMAGING_FREEIMAGE context_image :
      virtual public ::context_image
   {
   public:


      context_image();
      ~context_image() override;


      virtual void _load_image(::image * pimageParam, const ::payload & payloadFile, const image::load_options & loadoptions) override;

      virtual void _load_image(::image * pimage, __pointer(image_frame_array) & pframea, memory & memory) override;
      virtual void save_image(memory & memory, const ::image * pimage, const ::save_image * psaveimage) override;
      //void load_svg(::image * pimage, memory & memory) override;

      //virtual void _load_image(::object * pobject, image_frame_array * pimageframea, const ::memory & memory);


   };


} // namespace imaging_freeimage



