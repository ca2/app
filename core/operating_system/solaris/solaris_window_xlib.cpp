#include "framework.h"


window_xlib::window_xlib()
{

   m_window = nullptr;

   m_pdc = nullptr;

/*   m_pimage = nullptr;

}


window_xlib::~window_xlib()
{

}


HDC GetDC(oswindow window);


void window_xlib::create(oswindow window, i64 cxParam, i64 cyParam, int iStrideParam)
{

   if(cxParam <= 0 || cyParam <= 0)
      return;

   destroy();

   single_lock synchronouslock(&user_synchronization(), true);

   m_window = window;

   m_size.cx = cxParam;

   m_size.cy = cyParam;

   //if(iStrideParam < 0 || iStrideParam < (m_size.cx * sizeof(color32_t)))
   {

      m_iScan = m_size.cx * sizeof(color32_t);

   }
   /*else
   {

      m_iScan = ((iStrideParam + sizeof(color32_t) - 1) & ~sizeof(color32_t));

   }*/

   m_mem.set_size(cyParam * m_iScan);

/*   m_pimage = XCreateImage(window->display(), window->draw2d(), window->m_iDepth, ZPixmap, 0, (char *) m_mem->get_data(), cxParam, cyParam, sizeof(color32_t) * 8, m_iScan);

   m_pdc = memory_new device_context();

   XGCValues gcvalues;

   m_pdc->m_gc = XCreateGC(window->display(), window->window(), 0, &gcvalues);

   window_graphics::create(window, cxParam, cyParam, m_iScan);

}






void window_xlib::destroy()
{

   window_graphics::destroy();


}


void window_xlib::update_window(oswindow window, color32_t * pOsBitmapData, const ::rectangle_i32 * lpcrect, int iStride)
{

   single_lock synchronouslock(&user_synchronization());

   if(m_pdc == nullptr)
      return;

   if(m_window == nullptr)
      return;

/*   if(m_pimage == nullptr)
      return;

   if(pOsBitmapData == nullptr)
      return;

   if(m_size.area() <= 0)
      return;


   //memory_set(pOsBitmapData, 0x44, minimum(iStride * 16, iStride * m_size.cy));

   copy_colorref((color32_t *) m_mem.get_data(), pOsBitmapData, iStride);



   try
   {

/*      XPutImage(m_window->display(), m_window->window(), m_pdc->m_gc, m_pimage, 0, 0, 0, 0, m_size.cx, m_size.cy);

   }
   catch(...)
   {


   }

}



