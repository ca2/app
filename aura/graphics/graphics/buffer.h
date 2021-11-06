#pragma once



namespace graphics
{


   class CLASS_DECL_AURA buffer :
      virtual public graphics
   {
   public:


      int                           m_iGoodStride;
      ::image_pointer               m_pimageBuffer;

      bool                          m_bDibIsHostingBuffer;


      buffer();
      virtual ~buffer();


      virtual synchronization_object * get_draw_lock() override;
      ::draw2d::graphics * on_begin_draw() override;
      virtual bool update_window() override;
      virtual bool buffer_lock_round_swap_key_buffers() override;


      virtual bool update_buffer(const ::size_i32 & size, int iStride = -1) override;
      virtual void destroy_buffer() override;
      inline ::size_i32 buffer_size() { return m_pimageBuffer->get_size(); }


      virtual bool update_window(::image * pimage) override;
      virtual bool is_buffer_ok();
      ::image_pointer & get_buffer();

      virtual ::image_pointer & get_screen_image() override;
      virtual synchronization_object * get_screen_sync() override;


   };


} // namespace graphics



