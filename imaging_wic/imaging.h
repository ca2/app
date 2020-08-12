#pragma once


namespace imaging_wic
{


   class CLASS_DECL_IMAGING_WIC imaging :
      virtual public ::imaging
   {
   public:


      class CLASS_DECL_IMAGING_WIC load_image :
         virtual public ::object
      {
      public:


         var                  m_varFile;
         ::image_pointer      m_pimage;


         virtual ::estatus run() override;


         virtual void on_os_load_image(memory_pointer pmemory);


      };

      handler_manager                     m_managerImageLoad;


      imaging();
      virtual ~imaging();

      virtual ::estatus _load_image(::context * pcontext, ::image * pimageParam, const var & varFile, bool bSync, bool bCreateHelperMaps) override;

      virtual ::estatus _load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory);
      virtual ::estatus save_image(memory & memory, const ::image * pimage, ::save_image * psaveimage);

#ifdef _UWP
      virtual bool _desk_to_image(::image* pimage) override;
      virtual bool _desk_has_image() override;
      virtual bool _image_to_desk(const ::image* pimage) override;
#endif

   };


} // namespace imaging_wic



