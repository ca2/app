#include "framework.h"
#include "_android.h"


window_android::window_android()
{

   //m_cairoSource = nullptr;
   //m_cairosurfaceSource = nullptr;

}


window_android::~window_android()
{

}


bool window_android::update_buffer(const ::size_i32 & size,int iStrideParam)
{

   destroy_buffer();


   synchronous_lock synchronouslock(this->synchronization());

   //if(m_cairoSource != nullptr)
   //{
   //   cairo_destroy(m_cairoSource);

   //}

   //if(m_cairosurfaceSource != nullptr)
   //{

   //   cairo_surface_destroy(m_cairosurfaceSource);

   //}

   //i32 iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cxParam);

   i32 iStride = iStrideParam;

   //m_mem.set_size(iStride * cyParam);

   //m_cairosurfaceSource = cairo_image_surface_create_for_data((unsigned char *) m_mem.get_data(), CAIRO_FORMAT_ARGB32, cxParam, cyParam, iStride);

   //m_cairoSource = cairo_create(m_cairosurfaceSource);

   if (!::graphics::buffer::update_buffer(size, iStride))
   {

      return false;

   }

   return true;

}


void window_android::destroy_buffer()
{

   ::graphics::buffer::destroy_buffer();


}


bool window_android::update_screen(::image * pimage)
{

   ::copy_colorref((color32_t *)m_mem.get_data(), pimage->get_size(), m_size.cx(), pimage->get_data(), pimage->scan_size());

   return true;

}



