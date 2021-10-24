#pragma once


namespace universal_windows
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

      comptr<ID2D1DeviceContext>      m_pd2d1devicecontext;
      directx_framework_view  ^        m_pframeworkview;

      ::draw2d::graphics_pointer       m_pdraw2dgraphics;


      buffer();
      virtual ~buffer();


      virtual ::e_status initialize_graphics_graphics(::user::interaction_impl* pimpl) override;


      virtual bool create_buffer(const ::size_i32& size, int iStride = -1);
      virtual void destroy_buffer();
      virtual bool update_window();


      virtual bool update_window(::image* pimage);


      virtual ::draw2d::graphics* on_begin_draw() override;

      virtual void on_end_draw();


      bool create_os_buffer(const ::size_i32& size, int iStride = -1);
      void destroy_os_buffer();


      virtual bool buffer_lock_round_swap_key_buffers() override;


   };


} // namespace universal_windows



