#pragma once


namespace graphics
{


   class CLASS_DECL_AURA double_buffer :
      virtual public graphics
   {
   public:


      int                           m_iGoodStride;
      ::image_pointer               m_imageaBuffer[2];
      ::mutex                       m_mutexa[2];


      bool                          m_bDibIsHostingBuffer;


      int                           m_iCurrentBuffer;


      double_buffer();
      virtual ~double_buffer();


      virtual ::estatus initialize_graphics_graphics(::user::interaction_impl * pimpl) override;


      virtual bool round_swap_key_buffers() override;

      // sync_lock buffer sync first...
      virtual sync * get_buffer_sync() override;
      virtual ::image_pointer & get_buffer_image() override;

      // sync_lock screen sync first...
      virtual sync * get_screen_sync() override;
      virtual ::image_pointer & get_screen_image() override;


      using graphics::update_window;
      virtual bool update_window() override;

      virtual sync * get_draw_lock() override;
      virtual ::draw2d::graphics * on_begin_draw() override;


      virtual void destroy_buffer();


   };


} // namespace graphics



