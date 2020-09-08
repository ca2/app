#pragma once


class CLASS_DECL_BASE window_gdi :
   public window_graphics
{
public:


   HBITMAP                       m_hbitmap;
   HBITMAP                       m_hbitmapOld;
   BITMAPINFO                    m_bitmapinfo;
   COLORREF *                    m_pcolorref;
   HDC                           m_hdc;
   HWND                          m_hwnd;
   HDC                           m_hdcScreen;
   bool                          m_bOwnDC;

   ::image_pointer              m_spimageBuffer;


   window_gdi(::generic * pobject);
   virtual ~window_gdi();

   virtual void create_window_graphics(oswindow interaction_impl, i64 cx, i64 cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window();
   virtual void update_window(COLORREF * pcolorref,int cxParam,int cyParam,int iStride = -1);


   ::draw2d::graphics * on_begin_draw();


};
