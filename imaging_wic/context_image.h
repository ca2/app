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


         ::payload                        m_varFile;
         ::image_pointer                  m_pimage;
         __pointer(context_image)         m_pcontextimage;


         load_image(context_image* pcontextimage);
         virtual ~load_image();


         virtual ::e_status run() override;


         virtual void on_os_load_image(memory_pointer pmemory);


      };


      __composite(handler_manager)        m_pmanagerImageLoad;


      context_image();
      virtual ~context_image();


      virtual ::e_status initialize(::object * pobject) override;


      //virtual ::e_status _load_image(::context_image * pcontextimage, ::image * pimageParam, const ::payload & varFile, bool bSync, bool bCreateHelperMaps) override;
      virtual ::e_status _load_image(image* pimage, const ::payload& varFile, bool bSync = true, bool bCreateHelperMaps = false);

      virtual ::e_status _load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory);
      virtual ::e_status save_image(memory & memory, const ::image * pimage, const ::save_image * psaveimage) override;

      //virtual ::e_status _load_image(::image* pimage, const ::payload& varFile, bool bSync, bool bCreateHelperMaps);


      //virtual ::e_status _load_image(::image* pimage, __pointer(image_frame_array)& pframea, ::memory_pointer pmemory);
      //virtual ::e_status save_image(memory& memory, const ::image* pimage, ::save_image* psaveimage);


      //virtual ::e_status load_cursor(::draw2d::cursor* pcursor, ::file::path path, bool bSync, bool bCache = true) override;

      //virtual ::e_status load_svg(::image* pimage, ::memory_pointer pmemory);


#ifdef _UWP
      virtual bool _desk_to_image(::image* pimage);
      virtual bool _desk_has_image();
      virtual bool _image_to_desk(const ::image* pimage);
#endif


      virtual bool _save_image(::file::file* pfile, const ::image* pimage, const ::save_image* psaveimage);


   };


} // namespace imaging_wic



