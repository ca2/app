#ifndef BASE_SOLARIS_WINDOW_XLIB_H
#define BASE_SOLARIS_WINDOW_XLIB_H


#pragma once


class CLASS_DECL_APEX window_xlib :
   public window_graphics
{
public:


   oswindow                      m_window;
   device_context *              m_pdc;
   memory           m_mem;
   int_size                          m_size;
   int                           m_iScan;
/*   XImage *                      m_pimage;


   window_xlib();
   virtual ~window_xlib();

   virtual void create(oswindow window, long long cx, long long cy, int iStride = -1);
   virtual void destroy();

   virtual void update_window(oswindow window, color32_t * pOsBitmapData, const ::int_rectangle * lpcrect, int iStride = -1);

};


#endif // BASE_SOLARIS_WINDOW_XLIB_H



