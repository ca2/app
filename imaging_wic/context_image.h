#pragma once


namespace imaging_wic
{


   class CLASS_DECL_IMAGING_WIC context_image :
      virtual public ::context_image
   {
   public:


      class CLASS_DECL_IMAGING_WIC load_image :
         virtual public ::object
      {
      public:


         var                        m_varFile;
         ::image_pointer            m_pimage;
         __pointer(context_image)   m_pcontextimage;


         load_image(context_image* pcontextimage);


         virtual ::estatus run() override;


         virtual void on_os_load_image(memory_pointer pmemory);


      };


      __pointer(handler_manager)       m_pmanagerImageLoad;


      context_image();
      virtual ~context_image();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      //virtual ::estatus _load_image(::context_image * pcontextimage, ::image * pimageParam, const var & varFile, bool bSync, bool bCreateHelperMaps) override;
      virtual ::estatus _load_image(image* pimage, const ::var& varFile, bool bSync = true, bool bCreateHelperMaps = false);

      virtual ::estatus _load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory);
      virtual ::estatus save_image(memory & memory, const ::image * pimage, ::save_image * psaveimage);

      //virtual ::estatus _load_image(::image* pimage, const var& varFile, bool bSync, bool bCreateHelperMaps);


      //virtual ::estatus _load_image(::image* pimage, __pointer(image_frame_array)& pframea, ::memory_pointer pmemory);
      //virtual ::estatus save_image(memory& memory, const ::image* pimage, ::save_image* psaveimage);


      //virtual ::estatus load_cursor(::draw2d::cursor* pcursor, ::file::path path, bool bSync, bool bCache = true) override;

      //virtual ::estatus load_svg(::image* pimage, ::memory_pointer pmemory);




   };


} // namespace imaging_wic



