#pragma once


namespace graphics
{


   class CLASS_DECL_AURA buffer :
      virtual public object
   {
   public:



      ::windowing::window * m_pimpl;
      oswindow                      m_oswindow;



      buffer(::particle * pparticle);
      virtual ~buffer();


      virtual void initialize(::windowing::window * pimpl);


      //virtual void create_window_graphics_x(const ::size & size, int iStride = -1);
      //virtual void destroy_window_graphics_x();

      //virtual void create_bufferx(const ::size & size, int iStride = -1);
      //virtual void destroy_bufferx();

      virtual bool round_swap_key_buffers();

      virtual bool update_window();

      virtual ::size window_size();

      //virtual bool is_buffer_okx();

      virtual ::draw2d::graphics * on_begin_draw(synchronization ** ppsync);
      virtual void on_end_draw();


   };




} // namespace graphics



