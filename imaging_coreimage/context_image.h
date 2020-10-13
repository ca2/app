#pragma once


namespace coreimage_imaging
{


   class CLASS_DECL_COREIMAGE_IMAGING context_image :
      virtual public ::context_image
   {
   public:


      context_image();
      virtual ~context_image();

      virtual ::estatus _load_image(::image * pimageParam, const var & varFile, bool bSync, bool bCreateHelperMaps) override;

      virtual ::estatus _load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory) override;
      virtual ::estatus save_image(memory & memory, const ::image * pimage, const ::save_image * psaveimage = nullptr) override;

      virtual HCURSOR CreateAlphaCursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot) override;
      //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
      virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot) override;

      //virtual ::estatus _load_image(::object * pobject, image_frame_array * pimageframea, const ::memory & memory);
      //virtual int_bool window_set_mouse_cursor(oswindow window, HCURSOR hcursor) override;

   };


} // namespace coreimage_imaging



