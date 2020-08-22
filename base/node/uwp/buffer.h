#pragma once


namespace uwp
{


   class CLASS_DECL_AURA buffer :
      //virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer
   {
   public:


      //class os_buffer :
      //   virtual public ::object
      //{
      //public:


      //   os_buffer();
      //   virtual ~os_buffer();


      //   ::pixmap                      m_pixmap;
      //   HBITMAP                       m_hbitmap;
      //   HBITMAP                       m_hbitmapOld;
      //   HDC                           m_hdc;


      //   void destroy_buffer();


      //};


      directx_application  ^           m_directxapplication;

      ::draw2d::graphics_pointer       m_pdraw2dgraphics;


      buffer();
      virtual ~buffer();


      virtual ::estatus initialize_graphics_graphics(::user::interaction_impl* pimpl) override;


      virtual bool create_buffer(const ::size& size, int iStride = -1);
      virtual void destroy_buffer();
      virtual bool update_window();


      virtual bool update_window(::image* pimage);


      virtual ::draw2d::graphics* on_begin_draw() override;

      virtual void on_end_draw();


      bool create_os_buffer(const ::size& size, int iStride = -1);
      void destroy_os_buffer();


      virtual bool round_swap_key_buffers() override;


   };


} // namespace uwp



