#pragma once


namespace imaging_freeimage
{


   class CLASS_DECL_IMAGING_FREEIMAGE context_image :
      virtual public ::context_image
   {
   public:


      context_image();
      ~context_image() override;


      virtual ::e_status _load_image(::image * pimageParam, const ::payload & payloadFile, const image::load_options & loadoptions) override;

      virtual ::e_status _load_image(::image * pimage, __pointer(image_frame_array) & pframea, memory & memory) override;
      virtual ::e_status save_image(memory & memory, const ::image * pimage, const ::save_image * psaveimage) override;
      //::e_status load_svg(::image * pimage, memory & memory) override;

      //virtual ::e_status _load_image(::object * pobject, image_frame_array * pimageframea, const ::memory & memory);


   };


} // namespace imaging_freeimage



