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


      virtual ::e_status initialize_graphics_graphics(::user::interaction_impl * pimpl) override;


      virtual bool buffer_lock_round_swap_key_buffers() override;

      // sync_lock buffer sync first...
      virtual sync * get_buffer_sync() override;
      virtual ::image_pointer & get_buffer_image() override;

      // sync_lock screen sync first...
      virtual sync * get_screen_sync() override;
      virtual ::image_pointer & get_screen_image() override;

      virtual ::index get_buffer_index() const;
      virtual ::index get_screen_index() const;

      using graphics::update_window;
      virtual bool update_window() override;

      virtual sync * get_draw_lock() override;
      virtual ::draw2d::graphics * on_begin_draw() override;


      virtual void destroy_buffer() override;


   };


} // namespace graphics



