#include "framework.h"
#include "_.h"
#include "buffer.h"
#include "aura/os/android/window_android.h"
//#include <native_window.h>

namespace android
{


   buffer::buffer()
   {

      //m_cairoSource = nullptr;
      //m_cairosurfaceSource = nullptr;

   }


   buffer::~buffer()
   {
      
      destroy_buffer();

   }


   bool buffer::create_buffer(const ::size & size, int iStrideParam)
   {

      destroy_buffer();

      synchronous_lock synchronouslock(this->synchronization());

      int w;

      int h;

      //w = ANativeWindow_getWidth(m_pimpl->m_oswindow->m_engine.app->window);

      //h = ANativeWindow_getHeight(m_pimpl->m_oswindow->m_engine.app->window);

      //ANativeWindow_setBuffersGeometry(m_pimpl->m_oswindow->m_engine.app->window, w, h, WINDOW_FORMAT_RGBA_8888);

      //::graphics::buffer::create_buffer(size, w * 4);

      return false;

   }





   void buffer::destroy_buffer()
   {

      ::graphics::double_buffer::destroy_buffer();


   }


   bool buffer::update_window(::image * pimage)
   {

      //ANativeWindow_Buffer buffer;

      //ARect r;

      //rectangle.left = 0;
      //rectangle.top = 0;
      //rectangle.right = pimage->width();
      //rectangle.bottom = pimage->height();

      //__zero(buffer);

      //ANativeWindow_lock(m_pimpl->m_oswindow->m_engine.app->window, &buffer, rectangle);

      ///**
      //* Unlock the window's drawing surface after previously locking it,
      //* posting the memory_new buffer to the display.
      //*/


      //::copy_colorref(pimage->width(), pimage->height(), (color32_t *)buffer.bits, pimage->width() * sizeof(color32_t), pimage->get_data(), pimage->scan_size());

      //ANativeWindow_unlockAndPost(m_pimpl->m_oswindow->m_engine.app->window);

      return true;

   }


} // namespace android




