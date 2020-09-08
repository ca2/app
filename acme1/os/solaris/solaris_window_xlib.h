#ifndef BASE_SOLARIS_WINDOW_XLIB_H
#define BASE_SOLARIS_WINDOW_XLIB_H


#pragma once


class CLASS_DECL_ACME window_xlib :
   public window_graphics
{
public:


   oswindow                      m_window;
   device_context *              m_pdc;
   memory           m_mem;
   size                          m_size;
   int                           m_iScan;
/*   XImage *                      m_pimage;


   window_xlib();
   virtual ~window_xlib();

   virtual void create(oswindow window, i64 cx, i64 cy, int iStride = -1);
   virtual void destroy();

   virtual void update_window(oswindow window, COLORREF * pOsBitmapData, LPCRECT lpcrect, int iStride = -1);

};


#endif // BASE_SOLARIS_WINDOW_XLIB_H



