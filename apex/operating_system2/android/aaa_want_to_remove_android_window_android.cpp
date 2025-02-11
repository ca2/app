#include "framework.h"


window_android::window_android()
{

   //m_cairoSource = nullptr;
   //m_cairosurfaceSource = nullptr;

}


window_android::~window_android()
{

}


void window_android::create(oswindow interaction_impl, long long cxParam, long long cyParam, int iStrideParam)
{

   destroy();


   synchronous_lock synchronouslock(&user_synchronization());

   //if(m_cairoSource != nullptr)
   //{
   //   cairo_destroy(m_cairoSource);

   //}

   //if(m_cairosurfaceSource != nullptr)
   //{

   //   cairo_surface_destroy(m_cairosurfaceSource);

   //}

   //int iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cxParam);

   int iStride = iStrideParam;

   //m_mem.set_size(iStride * cyParam);

   //m_cairosurfaceSource = cairo_image_surface_create_for_data((unsigned char *) m_mem.get_data(), CAIRO_FORMAT_ARGB32, cxParam, cyParam, iStride);

   //m_cairoSource = cairo_create(m_cairosurfaceSource);

   window_graphics::create(interaction_impl, cxParam, cyParam, iStride);

}





void window_android::destroy()
{

   window_graphics::destroy();


}


void window_android::update_window(oswindow interaction_impl, color32_t * pOsBitmapData, const ::double_rectangle & rectangle, int iStride)
{


   copy_image32((color32_t *) m_mem.get_data(), pOsBitmapData, iStride);


}



