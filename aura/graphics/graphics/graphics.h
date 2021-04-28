#pragma once


namespace graphics
{


   class CLASS_DECL_AURA graphics :
      virtual public ::object
   {
   public:


      __pointer(::user::interaction_impl)    m_pimpl;
      __pointer(::windowing::window)         m_pwindow;
      bool                                   m_bNewBuffer;


      graphics();
      virtual ~graphics();


      virtual ::e_status initialize_graphics_graphics(::user::interaction_impl * pimpl);
      virtual ::e_status finalize();

      virtual void destroy_buffer();

      virtual bool buffer_lock_round_swap_key_buffers();

      virtual bool update_window();

      virtual bool update_window(::image * pimage);

      virtual ::size_i32 window_size();

      virtual i64 _001GetTopLeftWeightedOpaqueArea(const RECTANGLE_I32 * lpcrect);

      virtual synchronization_object * get_draw_lock();
      virtual ::draw2d::graphics * on_begin_draw();

      virtual void on_end_draw();

      virtual bool update_buffer(const ::size_i32 & size, int iStrideParam = -1);


      virtual ::image_pointer & get_buffer_image();
      virtual synchronization_object * get_buffer_sync();
      virtual ::image_pointer & get_screen_image();
      virtual synchronization_object * get_screen_sync();



   };


} // namespace graphics



