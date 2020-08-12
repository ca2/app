#pragma once


namespace imaging_freeimage
{


   class CLASS_DECL_IMAGING_FREEIMAGE imaging :
      virtual public ::imaging
   {
   public:


      imaging();
      virtual ~imaging();

      virtual ::estatus _load_image(::context * pcontext, ::image * pimageParam, const var & varFile, bool bSync, bool bCreateHelperMaps) override;

      virtual ::estatus _load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory) override;
      virtual ::estatus save_image(memory & memory, const ::image * pimage, ::save_image * psaveimage) override;


      //virtual ::estatus _load_image(::object * pobject, image_frame_array * pimageframea, const ::memory & memory);


   };


} // namespace imaging_freeimage



