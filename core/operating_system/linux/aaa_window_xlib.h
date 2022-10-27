#pragma once
//#include <X11/extensions/Xrender.h>

//#include "app/base/graphics/graphics_window_buffer.h"
namespace xlib
{


   class CLASS_DECL_CORE buffer :
      virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer
   {
   public:


      //::pointer < ::mutex >                         m_pmutexPixmap;
      //pixmap                        m_pixmap;
      GC                            m_gc;
      //memory                        m_mem;
      //XImage *                      m_pimage;
      //bool                          m_bMapped;
      ::rectangle                        m_rectangleLast;
      //::image_pointer                         m_pimage;


      buffer();
      virtual ~buffer();


      virtual void initialize_graphics_graphics(::user::interaction_impl * pimpl) override;
      virtual void destroy() override;


      virtual bool create_os_buffer(const ::size & size, int iStride = -1);
      virtual void destroy_os_buffer();

//      virtual bool create_os_buffer(::image::image * pimage);
//      virtual void destroy_os_buffer(::image::image * pimage);

      virtual bool update_window() override;
      virtual bool update_window(::image * pimage) override;


      virtual bool round_swap_key_buffers() override;

      //void update_window();

      ::draw2d::graphics * on_begin_draw() override;


   };


} // namespace xlib



