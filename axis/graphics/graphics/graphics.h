#pragma once


namespace graphics
{


   class CLASS_DECL_AURA graphics :
      virtual public ::object
   {
   public:


      ::user::interaction_impl *    m_pimpl;
      ::oswindow                    m_oswindow;
      bool                          m_bNewBuffer;


      graphics();
      virtual ~graphics();


      virtual ::estatus initialize_graphics_graphics(::user::interaction_impl * pimpl);
      virtual void finalize();

      virtual bool round_swap_key_buffers();

      virtual bool update_window();

      virtual bool update_window(::image * pimage);

      virtual ::size window_size();

      virtual i64 _001GetTopLeftWeightedOpaqueArea(LPCRECT lpcrect);

      virtual sync * get_draw_lock();
      virtual ::draw2d::graphics * on_begin_draw();

      virtual void on_end_draw();

      virtual bool create_buffer(const ::size & size, int iStrideParam = -1);


      virtual ::image_pointer & get_buffer_image();
      virtual sync * get_buffer_sync();
      virtual ::image_pointer & get_screen_image();
      virtual sync * get_screen_sync();


   };


} // namespace graphics



