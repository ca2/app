#pragma once


namespace coreimage_imaging
{


   class CLASS_DECL_COREIMAGE_IMAGING imaging :
      virtual public ::imaging
   {
   public:


      imaging();
      virtual ~imaging();

      virtual ::estatus _load_image(::context * pcontext, ::image * pimageParam, const var & varFile, bool bSync, bool bCreateHelperMaps) override;

      virtual ::estatus _load_image(::image * pimage, __pointer(image_frame_array) & pframea, ::memory_pointer pmemory) override;
      virtual ::estatus save_image(memory & memory, const ::image * pimage, ::save_image * psaveimage) override;

      virtual HCURSOR CreateAlphaCursor(oswindow oswindow, const image * pimage, int xHotSpot, int yHotSpot) override;
      virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
      virtual void set_cursor_image(const image * pimage, int xHotSpot, int yHotSpot) override;

      //virtual ::estatus _load_image(::object * pobject, image_frame_array * pimageframea, const ::memory & memory);
      virtual WINBOOL window_set_mouse_cursor(oswindow window, HCURSOR hcursor) override;

   };


} // namespace coreimage_imaging



