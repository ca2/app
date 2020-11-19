#include "framework.h"
#include <X11/Xft/Xft.h>
#include <math.h>

HDC CreateCompatibleDC(HDC hdc);

array < XChar2b > utf8toXChar2b(const char *input, int inlen);

namespace draw2d_xlib
{


   graphics::graphics(::layered * pobjectContext) :
      ::object(pobject),
      ::draw2d::graphics(pobject)
      //,     m_ui(pobject)
   {

      mutex()                = new ::mutex(pobject);

      m_bPrinting       = FALSE;
      m_pimageAlphaBlend  = nullptr;
      m_pdc             = nullptr;
      /*      m_hdc             = nullptr;
            m_ppath           = nullptr;
            m_ppathPaint      = nullptr;
            */
      m_etextrenderinghint  = ::draw2d::text_rendering_hint_anti_alias_grid_fit;

      m_pfont.create(this);
      m_pfont->m_strFontFamilyName = FONT_SANS;
      m_pfont->m_dFontSize = 12.0;


      m_nStretchBltMode = e_interpolation_mode_high_quality_bicubic;

   }

//   graphics::graphics() //:
////      m_ui(nullptr)
//   {
//
//      m_bPrinting       = FALSE;
//      m_pdc             = nullptr;
///*      m_pgraphics       = nullptr;
//      m_hdc             = nullptr;
//      m_ppath           = nullptr;
//      m_ppathPaint      = nullptr;*/
//      m_etextrenderinghint  = ::draw2d::text_rendering_hint_anti_alias_grid_fit;
//
//
//      m_nStretchBltMode = e_interpolation_mode_high_quality_bicubic;
//
//   }


   void graphics::assert_valid() const
   {
      object::assert_valid();
   }

   void graphics::dump(dump_context & dumpcontext) const
   {
      object::dump(dumpcontext);

//      dumpcontext << "get_handle1() = " << get_handle1();
      //    dumpcontext << "\nm_hAttribDC = " << get_handle2();
      //  dumpcontext << "\nm_bPrinting = " << m_bPrinting;

      dumpcontext << "\n";
   }


   graphics::~graphics()
   {

//      sync_lock ml(&xlib_mutex());

      /*      HDC hdc = Detach();

            if(hdc != nullptr)
            {
               bool bDeleted = ::DeleteDC(hdc) != FALSE;
               if(!bDeleted)
               {
                  TRACE("Failed to delete GDI device context");
               }
            }*/

      if(m_pdc != nullptr)
      {
//	if(m_pdc ==  xlib_keep::g_xlib)
         //{
         //    printf("123");

         //}
         //    xlib_destroy(m_pdc);
         m_pdc = nullptr;
      }

      /*      if(m_ppath != nullptr)
            {
               delete m_ppath;
               m_ppath = nullptr;
            }

            if(m_ppathPaint != nullptr)
            {
               delete m_ppathPaint;
               m_ppathPaint = nullptr;
            }*/

   }


   /*   __pointer(::user::user::interaction_impl) graphics::GetWindow() const
      {
         ASSERT(get_handle1() != nullptr); return ::win::user::interaction_impl::from_handle(::WindowFromDC(get_handle1()));
      }
   */

   bool graphics::IsPrinting() const
   {
      return m_bPrinting;
   }

   bool graphics::CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      __throw(not_supported_exception());
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
   }

   bool graphics::CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      __throw(not_supported_exception());
      //return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
   }

   bool graphics::CreateCompatibleDC(::image * pimage)
   {

      //sync_lock ml(&xlib_mutex());

      if(m_pdc != nullptr)
      {
//	if(m_pdc ==  xlib_keep::g_xlib)
         //{
         ///    printf("123");

         //}

         DeleteDC();

         m_pdc = nullptr;

      }

      if(pgraphics == nullptr)
      {

//         xlib_surface_t * psurface = xlib_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);

//         if(psurface == nullptr)
         //          return false;

         //     m_pdc = xlib_create(psurface);

//if(psurface == xlib_keep::g_xlibsurface)
//{
         // printf("123");
//}         xlib_surface_destroy(psurface);


         m_pbitmap.create(this);

         m_pbitmap->CreateCompatibleBitmap(this, 256, 256);

         SelectObject(m_pbitmap);

         return m_pdc != nullptr;

      }
      else
      {

         m_pdc = ::CreateCompatibleDC((HDC) pgraphics->get_os_data());

         /*       xlib_surface_t * psurface = xlib_get_target((xlib_t *) pgraphics->get_os_data());

                if(xlib_surface_status(psurface) != CAIRO_STATUS_SUCCESS)
                   return false;

                xlib_surface_t * psurfaceNew = xlib_surface_create_similar(psurface, xlib_surface_get_content(psurface), 1, 1);

                if(psurfaceNew == nullptr)
                   return false;
         if(psurfaceNew == xlib_keep::g_xlibsurface)
         {
         //   printf("123");
         }
                m_pdc = xlib_create(psurfaceNew);

                xlib_surface_destroy(psurfaceNew);*/

         return m_pdc != nullptr;

      }
      /*
            HDC hdc = nullptr;

            if(pgraphics == nullptr)
            {
               hdc = ::CreateCompatibleDC(nullptr);
            }
            else
            {
               hdc = ::CreateCompatibleDC((HDC)(dynamic_cast<::win::graphics * >(pgraphics))->get_handle1());
            }

            if(!Attach(hdc))
            {
               ::DeleteDC(hdc);
               return FALSE;
            }
            */

      return true;

   }


   i32 graphics::ExcludeUpdateRgn(::window * pWnd)
   {

//       ASSERT(get_handle1() != nullptr);
//       return ::ExcludeUpdateRgn(get_handle1(), WIN_WINDOW(pWnd)->get_handle());
      __throw(not_implemented());
      return 0;

   }


   i32 graphics::GetDevicecaps(i32 nIndex) const
   {
      /*      ASSERT(get_handle2() != nullptr);
            return ::GetDevicecaps(get_handle2(), nIndex);*/
      __throw(not_implemented());
      return 0;
   }

   point graphics::GetBrushOrg() const
   {
      /*      ASSERT(get_handle1() != nullptr);
            ::point point;
            VERIFY(::GetBrushOrgEx(get_handle1(), &point));
            return point;*/
      __throw(not_implemented());
      return ::point();

   }

   point graphics::SetBrushOrg(i32 x, i32 y)
   {
      /*      ASSERT(get_handle1() != nullptr);
            ::point point;
            VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));
            return point;*/
      __throw(not_implemented());
      return ::point();

   }

   point graphics::SetBrushOrg(const ::point & point)
   {
      /*      ASSERT(get_handle1() != nullptr);
            VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
            return point;*/
      __throw(not_implemented());
      return ::point();

   }

   i32 graphics::EnumObjects(i32 nObjectType, i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      /*      ASSERT(get_handle2() != nullptr);
            return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData);*/
      __throw(not_implemented());
      return 0;

   }

   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap * pbitmapParam)
   {

      if(pbitmapParam == nullptr)
         return nullptr;

      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (pbitmapParam);

      if(pbitmap == nullptr)
         return nullptr;

      /*      if(get_handle1() == nullptr)
               return nullptr;
            if(pbitmap == nullptr)
               return nullptr;
            return dynamic_cast < ::draw2d::bitmap* > (SelectGdiObject(get_context_application(), get_handle1(), pbitmap->get_os_data()));*/
      if(m_pdc != nullptr)
      {

         DeleteDC();

      }

      //m_pdc = xlib_create((xlib_surface_t *) pbitmap->get_os_data());

      m_pdc                = new device_context();

//      m_pdc->m_pdisplay    = pbitmap->m_ui.m_window->display();

      m_pdc->m_pixmap      = pbitmap->m_pixmap;

      m_pdc->m_drawable    = m_pdc->m_pixmap;

      ::XGCValues values;

      values.background    = 1;

      values.fill_rule     = WindingRule;

      m_pdc->m_gc          = ::XCreateGC(m_pdc->m_pdisplay, m_pdc->m_drawable, GCBackground | GCFillRule, &values);

      set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

      m_pbitmap = pbitmap;

      return m_pbitmap;
   }


   ::draw2d_xlib::object* graphics::SelectObject(draw2d_xlib::object* pObject)
   {
      /*      ASSERT(get_handle1() != nullptr);
         if(pObject == nullptr)
            return nullptr;
         return SelectGdiObject(get_context_application(), get_handle1(), pObject->get_os_data()); */
      return nullptr;
   }

   /*   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for nullptr handles
      {

         ::u32 uType = GetObjectType(hObject);

         if(uiType == OBJ_BITMAP)
         {

            HBITMAP hbitmap = (HBITMAP) hObject;

            if(m_pbitmap.is_null())
               m_pbitmap.create(get_object());

            if(m_pbitmap.is_null())
               return nullptr;

            (dynamic_cast < ::win::bitmap * > (m_pbitmap.m_p))->m_pbitmap = new Gdiplus::Bitmap(hbitmap, nullptr);

            if(m_pgraphics != nullptr)
            {
               delete m_pgraphics;
            }

            m_pgraphics = new Gdiplus::Graphics((Gdiplus::Bitmap *) m_pbitmap->get_os_data());

            set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

            return hbitmap;

         }

         //*ASSERT(get_handle1() == get_handle2()); // ASSERT a simple graphics object
         //return (hObject != nullptr) ? ::SelectObject(get_handle1(), hObject) : nullptr; */
   /*    return nullptr;
    }*/

   color32_t graphics::GetNearestColor(color32_t crColor) const
   {
      //__throw(not_implemented());
      return crColor;
//      return ::GetNearestColor(get_handle2(), crColor);
   }

   ::u32 graphics::RealizePalette()
   {
//      return ::RealizePalette(get_handle1());
      return 0;
   }

   void graphics::UpdateColors()
   {
      //::UpdateColors(get_handle1());

   }

   i32 graphics::GetPolyFillMode() const
   {
      //return ::GetPolyFillMode(get_handle2());
//      return xlib_get_fill_rule(m_pdc) == CAIRO_FILL_RULE_WINDING ? ::draw2d::fill_mode_winding : ::draw2d::fill_mode_alternate;
      return ::draw2d::fill_mode_winding;
   }

   i32 graphics::GetROP2() const
   {
      //return ::GetROP2(get_handle2());
      return 0;
   }

   i32 graphics::GetStretchBltMode() const
   {
      //return ::GetStretchBltMode(get_handle2());
      return 0;
   }

   i32 graphics::GetMapMode() const
   {
      //return ::GetMapMode(get_handle2());
      return 0;
   }

   i32 graphics::GetGraphicsMode() const
   {
      //return ::GetGraphicsMode(get_handle2());
      return 0;
   }

   bool graphics::GetWorldTransform(XFORM* pXform) const
   {

      //return ::GetWorldTransform(get_handle2(),pXform) != FALSE;
      return 0;

   }

   size graphics::GetViewportExt() const
   {
      /*::size size;
      ::GetViewportExtEx(get_handle2(), &size);
      return size;*/

      return ::size(0, 0);
   }

   point graphics::GetWindowOrg() const
   {
      /*::point point;
      ::GetWindowOrgEx(get_handle2(), &point);
      return point;*/
      return ::point();
   }

   size graphics::GetWindowExt() const
   {
      /*::size size;
      ::GetWindowExtEx(get_handle2(), &size);
      return size;*/
      return ::size(0, 0);
   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(const ::point & point)
   {

      m_pdc->m_point = point;

      return m_pdc->m_point;

   }


   size graphics::SetViewportExt(const ::size & size)
   {
      //return SetViewportExt(size.cx, size.cy);
      return ::size(0, 0);
   }

   point graphics::SetWindowOrg(const ::point & point)
   {
      //return SetWindowOrg(point.x, point.y);
      return ::point();
   }

   size graphics::SetWindowExt(const ::size & size)
   {
      //return SetWindowExt(size.cx, size.cy);
      return ::size(0, 0);
   }

   void graphics::DPtoLP(POINT32 * lpPoints, i32 nCount) const
   {
      //::DPtoLP(get_handle2(), lpPoints, nCount);
   }

   void graphics::DPtoLP(RECT32 * prect) const
   {
      //::DPtoLP(get_handle2(), (POINT32 *)rect, 2);
   }

   void graphics::LPtoDP(POINT32 * lpPoints, i32 nCount) const
   {
      //::LPtoDP(get_handle2(), lpPoints, nCount);
   }

   void graphics::LPtoDP(RECT32 * prect) const
   {
      //::LPtoDP(get_handle2(), (POINT32 *)rect, 2);
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      __throw(not_implemented());
      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != FALSE;
      return false;

   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight)
   {

//      return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != FALSE;
      __throw(not_implemented());
      return false;

   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      //    ASSERT(get_handle1() != nullptr);

//      return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != FALSE;
      __throw(not_implemented());
      return false;


   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

//      ASSERT(get_handle1() != nullptr);

      //    return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != FALSE;
      __throw(not_implemented());
      return false;

   }

   bool graphics::PtVisible(i32 x, i32 y) const
   {

      //    ASSERT(get_handle1() != nullptr);

//      return ::PtVisible(get_handle1(), x, y) != FALSE;
      __throw(not_implemented());
      return false;

   }

   bool graphics::PtVisible(const ::point & point) const
   {

//      ASSERT(get_handle1() != nullptr);

//      return PtVisible(point.x, point.y);

      __throw(not_implemented());
      return false;

   }

   bool graphics::RectVisible(const ::rect & rect) const
   {

//      ASSERT(get_handle1() != nullptr);

//      return ::RectVisible(get_handle1(), rect) != FALSE;

      __throw(not_implemented());
      return false;

   }

   point graphics::GetCurrentPosition() const
   {
//      ASSERT(get_handle2() != nullptr);
//      ::point point;
//      VERIFY(::GetCurrentPositionEx(get_handle2(), &point));
//      return point;
      __throw(not_implemented());
      return ::point();

   }

   bool graphics::Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {

      double centerx    = (x2 + x1) / 2.0;
      double centery    = (y2 + y1) / 2.0;

      double radiusx    = abs(x2 - x1) / 2.0;
      double radiusy    = abs(y2 - y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;

      double start      = atan2(y3 - centery, x3 - centerx);
      double end        = atan2(y4 - centery, x4 - centerx);


      /*      xlib_keep keep(m_pdc);

            xlib_translate(m_pdc, centerx, centery);

            xlib_scale(m_pdc, radiusx, radiusy);

            xlib_arc(m_pdc, 0.0, 0.0, 1.0, start, end);*/

      return true;

   }

   bool graphics::Arc(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd)
   {

      return Arc(
             rect.left,
             rect.top,
             rect.right,
             rect.bottom,
             ptStart.x,
             ptStart.y,
             ptEnd.x,
             ptEnd.y);

   }

   bool graphics::Polyline(const POINT32* lpPoints, i32 nCount)
   {

      /*ASSERT(get_handle1() != nullptr);

      return ::Polyline(get_handle1(), lpPoints, nCount) != FALSE;*/

      __throw(not_implemented());
      return false;

   }

   void graphics::FillRect(const ::rect & rect, ::draw2d::brush* pBrush)
   {

      set(pBrush);

      XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
                     rect.left + m_pdc->m_pointOffset.x, rect.top + m_pdc.m_pointOffset.y,
                     width(rect), height(rect));
//      __throw(not_implemented());
      //    return;

//      ASSERT(get_handle1() != nullptr); ::FillRect(get_handle1(), rect, (HBRUSH)pBrush->get_os_data());

   }
   void graphics::FrameRect(const ::rect & rect, ::draw2d::brush* pBrush)
   {

      __throw(not_implemented());
      return;

//       ASSERT(get_handle1() != nullptr); ::FrameRect(get_handle1(), rect, (HBRUSH)pBrush->get_os_data());

   }


   bool graphics::DrawRect(const ::rect & rect, ::draw2d::pen * ppen)
   {

      return DrawRect(rect.left, rect.top, rect.right, rect.bottom, ppen);

   }


   bool graphics::DrawRect(int x1, int y1, int x2, int y2, ::draw2d::pen * ppen)
   {

      set(ppen);

      XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
                     x1 + m_pdc->m_pointOffset.x, y1 + m_pdc.m_pointOffset.y,
                     x2 - x1 - 1, y2 - y1 -1);

      return true;

   }


   void graphics::InvertRect(const ::rect & rect)
   {

      __throw(not_implemented());
      return;

//      ASSERT(get_handle1() != nullptr); ::InvertRect(get_handle1(), rect);

   }

   bool graphics::DrawIcon(i32 x, i32 y, ::draw2d::icon * picon)
   {

      __throw(not_implemented());
      return false;


      //    ASSERT(get_handle1() != nullptr);

      //  if(picon == nullptr)
      //   return false;

//      return ::DrawIcon(get_handle1(), x, y, (HICON) picon->m_picon) != FALSE;

   }

   bool graphics::DrawIcon(const ::point & point, ::draw2d::icon * picon)
   {

      __throw(not_implemented());
      return false;
      /*      ASSERT(get_handle1() != nullptr);

            if(picon == nullptr)
               return false;

            return ::DrawIcon(get_handle1(), point.x, point.y, (HICON) picon->m_picon) != FALSE;*/

   }

   bool graphics::DrawIcon(i32 x, i32 y, ::draw2d::icon * picon, i32 cx, i32 cy, ::u32 istepIfAniCur, HBRUSH hbrFlickerFreeDraw, ::u32 diFlags)
   {


#ifdef WINDOWS

      try
      {

         if(picon == nullptr)
            return FALSE;

         if(m_pdc == nullptr)
            return FALSE;

         if(cx <= 0 || cx <= 0)
            return false;


         bool bOk = FALSE;

         BITMAPINFO info;
         color32_t * pcolorref;

         ZeroMemory(&info, sizeof (BITMAPINFO));

         info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
         info.bmiHeader.biWidth         = cx;
         info.bmiHeader.biHeight        = - cy;
         info.bmiHeader.biPlanes        = 1;
         info.bmiHeader.biBitCount      = 32;
         info.bmiHeader.biCompression   = BI_RGB;
         info.bmiHeader.biSizeImage     = cx * cy * 4;

         HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pcolorref, nullptr, 0);

         HDC hdc = ::CreateCompatibleDC(nullptr);

         HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         if(::DrawIconEx(hdc, 0, 0, (HICON) picon->m_picon, cx, cy, istepIfAniCur, nullptr, DI_IMAGE | DI_MASK))
         {

            ::SelectObject(hdc, hbitmapOld);

            try
            {

               //Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (byte *) pcolorref);

               ::draw2d::bitmap_pointer b(e_create);

               b->CreateBitmap(this, cx, cy, 1, 32, pcolorref, cx * sizeof(color32_t));

               xlib_surface_t * psurface = (xlib_surface_t *) b->get_os_data();

               if(psurface == nullptr)
                  return false;

               xlib_pattern_t * ppattern = xlib_pattern_create_for_surface(psurface);

               if(ppattern == nullptr)
                  return false;

               xlib_matrix_t matrix;

               xlib_matrix_t matrixOld;

               xlib_keep keep(m_pdc);

               xlib_translate(m_pdc, x, y);

               xlib_pattern_get_matrix(ppattern, &matrixOld);

               xlib_matrix_init_translate(&matrix, 0, 0);

               xlib_pattern_set_matrix(ppattern, &matrix);

               xlib_rectangle(m_pdc, 0, 0, cx, cy);

               xlib_clip(m_pdc);

               xlib_set_source(m_pdc, ppattern);

               xlib_paint(m_pdc);

               xlib_pattern_set_matrix(ppattern, &matrixOld);

               xlib_pattern_destroy(ppattern);
            }
            catch(...)
            {
            }

         }

         ::DeleteDC(hdc);

         ::DeleteObject(hbitmap);

         return bOk;

      }
      catch(...)
      {
      }

#endif

      return false;
   }

//   bool graphics::DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      __throw(not_implemented());
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hBitmap, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;
//
//   }
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      __throw(not_implemented());
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;
//
//   }
//
//   /*   bool graphics::DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags, HBRUSH hBrush)
//      {
//
//         __throw(not_implemented());
//         return false;
//   //      ASSERT(get_handle1() != nullptr);
//   //      return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;
//
//      }
//
//
//      bool graphics::DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags, ::draw2d::brush* pBrush)
//      {
//
//         __throw(not_implemented());
//         return false;
//   //      ASSERT(get_handle1() != nullptr);
//   //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;
//
//      }*/
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, const char * lpszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, HBRUSH hBrush)
//   {
//
//      __throw(not_implemented());
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawState(get_handle1(), hBrush,  nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;
//
//   }
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, const char * lpszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, ::draw2d::brush* pBrush)
//   {
//
//      __throw(not_implemented());
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;
//
//   }

//   /*
//
//      bool graphics::DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, ::u32 nFlags, HBRUSH hBrush)
//      {
//
//         __throw(not_implemented());
//         return false;
//
//   //      ASSERT(get_handle1() != nullptr);
//   //      return ::DrawState(get_handle1(), hBrush, lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;
//
//      }
//
//      bool graphics::DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush)
//      {
//
//         __throw(not_implemented());
//         return false;
//
//   //      ASSERT(get_handle1() != nullptr);
//   //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;
//
//      }
//
//   */
//
//   bool graphics::DrawEdge(RECT32 * prect, ::u32 nEdge, ::u32 nFlags)
//   {
//
//      __throw(not_implemented());
//      return false;
//
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawEdge(get_handle1(), rect, nEdge, nFlags) != FALSE;
//
//   }
//
//   bool graphics::DrawFrameControl(RECT32 * prect, ::u32 nType, ::u32 nState)
//   {
//
//      __throw(not_implemented());
//      return false;
////      ASSERT(get_handle1() != nullptr);
////      return ::DrawFrameControl(get_handle1(), rect, nType, nState) != FALSE;
//
//   }

   bool graphics::Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {
      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
   }

   bool graphics::Chord(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd)
   {

      __throw(not_implemented());
      return false;

      //ASSERT(get_handle1() != nullptr);
      //return ::Chord(get_handle1(), rect.left, rect.top, rect.right, rect.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != FALSE;

   }

   void graphics::DrawFocusRect(const ::rect & rect)
   {

      __throw(not_implemented());

      //ASSERT(get_handle1() != nullptr); ::DrawFocusRect(get_handle1(), rect);

   }

   bool graphics::DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      ::XDrawArc(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1, 0, 360 * 64);

      /*      double centerx    = (x2 + x1) / 2.0;
            double centery    = (y2 + y1) / 2.0;

            double radiusx    = abs(x2 - x1) / 2.0;
            double radiusy    = abs(y2 - y1) / 2.0;

            if(radiusx == 0.0 || radiusy == 0.0)
               return false;

            xlib_keep keep(m_pdc);

            xlib_new_sub_path(m_pdc);

            xlib_translate(m_pdc, centerx, centery);

            xlib_scale(m_pdc, radiusx, radiusy);

            xlib_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

            keep.pulse();

            set(m_ppen);

            xlib_stroke(m_pdc);*/

      return true;

   }

   bool graphics::DrawEllipse(rect lprect)
   {

      return DrawEllipse(lprect->left, lprect->top, lprect->right, lprect->bottom);

      /*return ::Ellipse(get_handle1(), rect.left, rect.top,
      rect.right, rect.bottom); */


   }

   bool graphics::FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      ::XFillArc(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1, 0, 360 * 64);

      /*double centerx    = (x2 + x1) / 2.0;

      double centery    = (y2 + y1) / 2.0;

      double radiusx    = abs(x2 - x1) / 2.0;

      double radiusy    = abs(y2 - y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;


      xlib_keep keep(m_pdc);

      xlib_new_sub_path(m_pdc);

      xlib_translate(m_pdc, centerx, centery);

      xlib_scale(m_pdc, radiusx, radiusy);

      xlib_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      keep.restore();

      fill();*/


      return true;

   }


   bool graphics::FillEllipse(const ::rect & rect)
   {

      /*return ::Ellipse(get_handle1(), rect.left, rect.top,
      rect.right, rect.bottom); */

      return FillEllipse(rect.left, rect.top, rect.right, rect.bottom);

   }

   bool graphics::Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {

      __throw(not_implemented());
      return false;

      /*      ASSERT(get_handle1() != nullptr);
            return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;*/

   }

   bool graphics::Pie(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd)
   {

      __throw(not_implemented());
      return false;


      /*      ASSERT(get_handle1() != nullptr);
            return ::Pie(get_handle1(), rect.left, rect.top, rect.right, rect.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != FALSE;*/

   }

   bool graphics::fill_polygon(const POINTD * pa, i32 iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(i32 i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      //set(m_ppen);

      set(m_pbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      delete xpa;

      return true;

   }

   bool graphics::fill_polygon(const POINT32* pa, i32 iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(i32 i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      //set(m_ppen);

      set(m_pbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::draw_polygon(const POINTD * pa, i32 iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(i32 i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      set(m_ppen);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::draw_polygon(const POINT32* pa, i32 iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(i32 i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      set(m_ppen);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::Polygon(const POINT32* pa, i32 iCount)
   {

      if(iCount <= 0)
         return true;

      XPoint * xpa = new XPoint[iCount];

      for(i32 i = 0; i < iCount; i++)
      {

         xpa[i].x = pa[i].x + m_pdc->m_pointOffset.x;
         xpa[i].y = pa[i].y + m_pdc->m_pointOffset.y;

      }

      set(m_ppen);

      set(m_pbrush);

      XFillPolygon(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, Complex, CoordModeOrigin);

      XDrawLines(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, xpa, iCount, CoordModeOrigin);

      delete xpa;

      return true;

   }


   bool graphics::PolyPolygon(const POINT32* lpPoints, const ::i32* lpPolyCounts, i32 nCount)
   {

      __throw(not_implemented());
      return false;
      //   ASSERT(get_handle1() != nullptr); return ::PolyPolygon(get_handle1(), lpPoints, lpPolyCounts, nCount) != FALSE;

   }

   bool graphics::Rectangle(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      /*      Gdiplus::RectF rectf((Gdiplus::REAL) x1, (Gdiplus::REAL) y1, (Gdiplus::REAL) (x2 - x1), (Gdiplus::REAL) (y2 - y1));

            bool bOk1 = m_pgraphics->FillRectangle(gdiplus_brush(), rectf) == Gdiplus::Status::Ok;

            bool bOk2 = m_pgraphics->DrawRectangle(gdiplus_pen(), rectf) == Gdiplus::Status::Ok;

            return bOk1 && bOk2;*/

      set(m_pbrush);

      ::XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1 + m_pdc->m_pointOffset.x, y1 + m_pdc.m_pointOffset.y, x2 - x1, y2 - y1);

      set(m_ppen);

      ::XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1 + m_pdc->m_pointOffset.x, y1 + m_pdc.m_pointOffset.y, x2 - x1 - 1, y2 - y1 - 1);

      return true;




   }

   bool graphics::Rectangle(const ::rect & rect)
   {

      return Rectangle(rect.left, rect.top, rect.right, rect.bottom);

   }

   bool graphics::DrawRectangle(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      set(m_ppen);

      set(m_pbrush);

      ::XDrawRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1);

      return true;

   }

   bool graphics::DrawRectangle(const ::rect & rect)
   {

      return DrawRectangle(rect.left, rect.top, rect.right, rect.bottom);

   }

   bool graphics::FillRectangle(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      set(m_ppen);

      set(m_pbrush);

      ::XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x1, y1, x2 - x1, y2 - y1);

      return true;

   }

   bool graphics::FillRectangle(const ::rect & rect)
   {

      return FillRectangle(rect.left, rect.top, rect.right, rect.bottom);

   }

   bool graphics::RoundRect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::RoundRect(get_handle1(), x1, y1, x2, y2, x3, y3) != FALSE;

   }

   bool graphics::RoundRect(const ::rect & rect, const ::point & point)
   {

      //ASSERT(get_handle1() != nullptr);
      //return ::RoundRect(get_handle1(), rect.left, rect.top, rect.right, rect.bottom, point.x, point.y) != FALSE;
      __throw(not_implemented());
      return false;


   }

   bool graphics::PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight)
   {

//      ASSERT(get_handle1() != nullptr);
//      return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != FALSE;

      __throw(not_implemented());
      return false;


   }


   bool graphics::BitBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc)
   {

      //sync_lock ml(&xlib_mutex());

      if(m_pimageAlphaBlend->is_set())
      {
         __throw(not_implemented());

         /*::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


         ::image_pointer pimageWork = nullptr;
         ::image_pointer pimageWork2 = nullptr;
         //         ::image_pointer pimageWork3 = nullptr;
         ::image_pointer pimageWork4 = nullptr;


         ::point pointSrc(xSrc, ySrc);
         ::point ptDest(x, y);
         ::size size(nWidth, nHeight);



         ::image_pointer pimage;
         if(imageWork == nullptr)
         {
            pimage = create_image(get_object());
            imageWork = pimage;
         }
         if(imageWork == nullptr)
            return false;
         if(!imageWork = create_image(size))
            return false;

         imageWork.Fill(0, 0, 0, 0);

         imageWork.get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         if(!imageWork.from(::point(), pgraphicsSrc, pointSrc, size))
            return false;




         ::image_pointer pimage2;
         if(imageWork2 == nullptr)
         {
            pimage2 = create_image(get_object());
            imageWork2 = pimage2;
         }


         ::image_pointer pimage4;
         if(imageWork4 == nullptr)
         {
            image4 = create_image(get_object());
            imageWork4 = image4;
         }
         if(imageWork4 == nullptr)
            return false;
         if(!imageWork4 = create_image(size))
            return false;


         imageWork4.Fill(255, 0, 0, 0);

         imageWork4.get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         imageWork4.from(point(max(0, m_pointAlphaBlend.x - x), max(0, m_pointAlphaBlend.y - y)),
            m_pimageAlphaBlend->get_graphics(), point(max(0, x - m_pointAlphaBlend.x), max(0, y - m_pointAlphaBlend.y)),
                               ::size(max(0, m_pimageAlphaBlend->width() - max(0, x - m_pointAlphaBlend.x)), max(0, m_pimageAlphaBlend->height() - max(0, y - m_pointAlphaBlend.y))));

         imageWork.channel_multiply(::color::channel_alpha, imageWork4);

         /*imageWork.get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

         imageWork.from(point(max(0, m_pointAlphaBlend.x - x), max(0, m_pointAlphaBlend.y - y)),
            m_pimageAlphaBlend->get_graphics(), point(max(0, x - m_pointAlphaBlend.x), max(0, y - m_pointAlphaBlend.y)),
                               ::size(max(0, size.cx - max(0, x - m_pointAlphaBlend.x)), max(0, size.cy - max(0, y - m_pointAlphaBlend.y))));*/

         //keeper < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);

         /*Gdiplus::CompositingMode mode = m_pgraphics->GetCompositingMode();

         //m_pgraphics->SetCompositingMode(Gdiplus::CompositingModeSourceOver);

         bool bOk = m_pgraphics->DrawImage(
            (Gdiplus::Bitmap *) imageWork.get_graphics()->get_current_bitmap()->get_os_data(),
            x, y , 0, 0, nWidth, nHeight, Gdiplus::UnitPixel) == Gdiplus::Status::Ok;


         m_pgraphics->SetCompositingMode(mode);

         return bOk;

         //return System.imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), ::point());
         */

      }


      try
      {

         if(pgraphicsSrc == nullptr)
            return false;

         if(nWidth <= 0 || nHeight <= 0)
            return false;

         ::draw2d_xlib::graphics * psrc = dynamic_cast < ::draw2d_xlib::graphics * > (pgraphicsSrc);

         if(psrc == nullptr)
            return false;

         if(psrc->m_pbitmap.is_null())
            return false;

         XCopyArea(m_pdc->m_pdisplay, psrc->m_pdc->m_drawable, m_pdc->m_drawable, m_pdc->m_gc,
                   xSrc + m_pdc->m_pointOffset.x,
                   ySrc + m_pdc->m_pointOffset.y,
                   nWidth,
                   nHeight,
                   x + m_pdc->m_pointOffset.x,
                   y + m_pdc->m_pointOffset.y);

         return true;

      }
      catch(...)
      {

         return false;

      }

      //return ::BitBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc);

   }


   bool graphics::StretchBlt(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight)
   {

      return false;

      /*      sync_lock ml(&xlib_mutex());

            if(pgraphicsSrc == nullptr)
               return false;

            if(nSrcWidth <= 0 || nSrcHeight <= 0 || nDstWidth <= 0 || nDstHeight <= 0)
               return false;

               if(pgraphicsSrc == nullptr)
                  return false;

               xlib_surface_t * psurface = xlib_get_target((xlib_t *) pgraphicsSrc->get_os_data());

               if(psurface == nullptr)
                  return false;

               xlib_pattern_t * ppattern = xlib_pattern_create_for_surface(psurface);

               if(ppattern == nullptr)
                  return false;

               xlib_matrix_t matrix;

               xlib_matrix_t matrixOld;

               xlib_pattern_get_matrix(ppattern, &matrixOld);

               xlib_keep keep(m_pdc);

               xlib_translate(m_pdc, xDst, yDst);

               xlib_matrix_init_translate(&matrix, -xSrc, -ySrc);

               xlib_matrix_scale(&matrix, (double) nSrcWidth / (double) nDstWidth, (double) nSrcHeight / (double) nDstHeight);

               xlib_pattern_set_matrix(ppattern, &matrix);

               xlib_rectangle(m_pdc, 0, 0, nDstWidth, nDstHeight);

               xlib_clip(m_pdc);

               xlib_set_source(m_pdc, ppattern);

               if(m_nStretchBltMode == 0)
               {
                  xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_NEAREST);
               }
               else if(m_nStretchBltMode == e_interpolation_mode_high_quality_bicubic)
               {
                  xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_GOOD);
               }
               else
               {
                  xlib_pattern_set_filter(xlib_get_source(m_pdc), CAIRO_FILTER_FAST);
               }

               xlib_paint(m_pdc);

               xlib_pattern_set_matrix(ppattern, &matrixOld);

               xlib_pattern_destroy(ppattern);


            return true;*/

      //return ::StretchBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight);

   }


   color32_t graphics::GetPixel(i32 x, i32 y) const
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetPixel(get_handle1(), x, y);

   }

   color32_t graphics::GetPixel(const ::point & point) const
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetPixel(get_handle1(), point.x, point.y);

   }

   color32_t graphics::SetPixel(i32 x, i32 y, color32_t crColor)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetPixel(get_handle1(), x, y, crColor);

   }

   color32_t graphics::SetPixel(const ::point & point, color32_t crColor)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetPixel(get_handle1(), point.x, point.y, crColor);

   }

//   bool graphics::FloodFill(i32 x, i32 y, color32_t crColor)
//   {
//
//      __throw(not_implemented());
//      return false;
//
////      ASSERT(get_handle1() != nullptr);
////      return ::FloodFill(get_handle1(), x, y, crColor) != FALSE;
//
//   }
//
//   bool graphics::ExtFloodFill(i32 x, i32 y, color32_t crColor, ::u32 nFillType)
//   {
//
//      __throw(not_implemented());
//      return false;
//
////      ASSERT(get_handle1() != nullptr);
////      return ::ExtFloodFill(get_handle1(), x, y, crColor, nFillType) != FALSE;
//
//   }


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   bool graphics::text_out(i32 x, i32 y, const string & str)
   {

      if(m_pimageAlphaBlend->is_set())
      {
         __throw(not_implemented());
         //if(GetBkMode() == TRANSPARENT)
         /*         {
                  //   return TRUE;
                     ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
                     ::rect rectText(::point(x, y), GetTextExtent(str));
                     if(rectIntersect.intersect(rectIntersect, rectText))
                     {
                        /* p::image_pointer pimage0(get_object());
                        image0 = create_image(rectText.size());
                        image0.Fill(0, 0, 0, 0);
                        image0.get_graphics()->SetTextColor(ARGB(255, 255, 255, 255));
                        image0.get_graphics()->SelectObject(&get_current_font());
                        image0.get_graphics()->SetBkMode(TRANSPARENT);
                        image0.get_graphics()->text_out(0, 0, str);
                        image0.ToAlpha(0);*/
         /* p::image_pointer pimage1(get_object());
                      pimage1 = create_image(rectText.size());
                      pimage1->Fill(0, 0, 0, 0);
         //               pimage1->get_graphics()->set_color(m_crColor);
                      pimage1->get_graphics()->SelectObject(&get_current_font());
                      pimage1->get_graphics()->SetBkMode(TRANSPARENT);
                      pimage1->get_graphics()->text_out(0, 0, str);
                      //pimage1->channel_from(::color::channel_alpha, image0);
                      ::image_pointer pimage2(get_object());
                      pimage2 = create_image(rectText.size());
                      pimage2->Fill(255, 0, 0, 0);
                      pimage2->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
                      pimage2->from(point(max(0, m_pointAlphaBlend.x - x), max(0, m_pointAlphaBlend.y - y)),
                         m_pimageAlphaBlend->get_graphics(), point(max(0, x - m_pointAlphaBlend.x), max(0, y - m_pointAlphaBlend.y)),
                         size(max(0, m_pimageAlphaBlend->width()-max(0, x - m_pointAlphaBlend.x)),
                               max(0, m_pimageAlphaBlend->height()-max(0, y - m_pointAlphaBlend.y))));
                      pimage1->channel_multiply(::color::channel_alpha, pimage2);
                      /* p::image_pointer pimage3(get_object());
                      pimage1->mult_alpha(image3);*/

         /*           keeper < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);

                    return System.imaging().true_blend(this, ::point(x, y), rectText.size(), pimage1->get_graphics(), ::point());

                    /*BLENDFUNCTION bf;
                    bf.BlendOp     = AC_SRC_OVER;
                    bf.BlendFlags  = 0;
                    bf.SourceConstantAlpha = 0xFF;
                    bf.AlphaFormat = AC_SRC_ALPHA;
                    return ::AlphaBlend(get_handle1(), x, y,
                       rectText.width(), rectText.height(), WIN_HDC(pimage1->get_graphics()), 0, 0, rectText.width(),
                       rectText.height(), bf) != FALSE; */
         //      }
         // }
      }

      //ASSERT(get_handle1() != nullptr);
      //wstring wstr = ::str::international::utf8_to_unicode(str);
      return text_out(x, y, str, (i32) str.get_length());

   } // call virtual

   bool graphics::text_out(double x, double y, const string & str)
   {
      if(m_pimageAlphaBlend->is_set())
      {
//         if(GetBkMode() == TRANSPARENT)
         {
            //   return TRUE;
            ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
            ::rect rectText(point((i64) x, (i64) y), GetTextExtent(str));
            if(rectIntersect.intersect(rectIntersect, rectText))
            {
               ::image_pointer pimage0;
               image0 = create_image(rectText.size());
               ::draw2d::brush_pointer brush(e_create_new, this,ARGB(255, 255, 255, 255));
               image0.get_graphics()->SelectObject(get_current_font());
               image0.get_graphics()->SelectObject(brush);
               image0.get_graphics()->text_out(0, 0, str);
               image0.ToAlpha(0);
               ::image_pointer pimage1;
               pimage1 = create_image(rectText.size());
               brush->create_solid(m_pbrush->m_color);
               pimage1->get_graphics()->SelectObject(get_current_font());
               pimage1->get_graphics()->text_out(0, 0, str);
               pimage1->channel_from(::color::channel_alpha, image0);
               ::image_pointer pimage2;
               pimage2 = create_image(rectText.size());
               pimage2->Fill(255, 0, 0, 0);
               pimage2->from(point((i64) max(0, m_pointAlphaBlend.x - x), (i64) max(0, m_pointAlphaBlend.y - y)),
                           m_pimageAlphaBlend->get_graphics(), point((i64) max(0, x - m_pointAlphaBlend.x), (i64) max(0, y - m_pointAlphaBlend.y)), rectText.size());
               pimage1->channel_multiply(::color::channel_alpha, pimage2->m_p);
               /* p::image_pointer pimage3(get_object());
               pimage1->mult_alpha(image3);*/

               keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);

               return BitBlt((i32) x, (i32) y, rectText.width(), rectText.height(), pimage1->get_graphics(), 0, 0);

               /*BLENDFUNCTION bf;
               bf.BlendOp     = AC_SRC_OVER;
               bf.BlendFlags  = 0;
               bf.SourceConstantAlpha = 0xFF;
               bf.AlphaFormat = AC_SRC_ALPHA;
               return ::AlphaBlend(get_handle1(), x, y,
                  rectText.width(), rectText.height(), WIN_HDC(pimage1->get_graphics()), 0, 0, rectText.width(),
                  rectText.height(), bf) != FALSE; */
            }
         }
      }

      //ASSERT(get_handle1() != nullptr);
      //wstring wstr = ::str::international::utf8_to_unicode(str);
      return text_out(x, y, str, (i32) str.get_length());

   } // call virtual

   bool graphics::ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect, const char * lpszString, ::u32 nCount, LPINT lpDxWidths)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::ExtTextOut(get_handle1(), x, y, nOptions, rect, lpszString, nCount, lpDxWidths) != FALSE;

   }

   bool graphics::ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect, const string & str, LPINT lpDxWidths)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::ExtTextOut(get_handle1(), x, y, nOptions, rect, str, (::u32)str.get_length(), lpDxWidths) != FALSE;

   }

   size graphics::TabbedTextOut(i32 x, i32 y, const char * lpszString, i32 nCount, i32 nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   {

      __throw(not_implemented());
      return ::size(0, 0);

//      ASSERT(get_handle1() != nullptr);
//      return ::TabbedTextOut(get_handle1(), x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);

   }

   size graphics::TabbedTextOut(i32 x, i32 y, const string & str, i32 nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin)
   {

      __throw(not_implemented());
      return ::size(0, 0);

//      ASSERT(get_handle1() != nullptr);
//      return ::TabbedTextOut(get_handle1(), x, y, str, (i32)str.get_length(), nTabPositions, lpnTabStopPositions, nTabOrigin);

   }


   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions) const
   {

      __throw(not_implemented());
      return ::size(0, 0);

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTabbedTextExtent(get_handle2(), lpszString, (i32) nCount, nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions) const
   {

      __throw(not_implemented());
      return ::size(0, 0);

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTabbedTextExtent(get_handle2(), str, (i32) str.get_length(), nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions) const
   {

      __throw(not_implemented());
      return ::size(0, 0);

//      ASSERT(get_handle1() != nullptr);
//      return ::GetTabbedTextExtent(get_handle1(), lpszString, (i32) nCount, nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetOutputTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions) const
   {

      __throw(not_implemented());
      return ::size(0, 0);

//      ASSERT(get_handle1() != nullptr);
//      return ::GetTabbedTextExtent(get_handle1(), str, (i32) str.get_length(), nTabPositions, lpnTabStopPositions);

   }

   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount,i32 x, i32 y, i32 nWidth, i32 nHeight)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != FALSE;

   }

   ::u32 graphics::GetTextAlign() const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTextAlign(get_handle2());

   }

   i32 graphics::GetTextFace(i32 nCount, char * lpszFacename) const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTextFace(get_handle2(), nCount, lpszFacename);

   }

   i32 graphics::GetTextFace(string & rString) const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      i32 nResult = ::GetTextFace(get_handle2(), 256, rString.GetBuffer(256)); rString.ReleaseBuffer();
//      return nResult;

   }

   bool graphics::get_text_metrics(::draw2d::text_metric * lpMetrics) const
   {
      //ASSERT(get_handle2() != nullptr); return ::GetTextMetrics(get_handle2(), lpMetrics);

      /*
      str = L"123AWZwmc";
      Gdiplus::RectF rect;
      Gdiplus::RectF rect2;
      Gdiplus::PointF origin(0, 0);
      m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_font->get_os_data(), origin, &rect);

      wstr = L"123AWZwmcpQçg";
      m_pgraphics->MeasureString(wstr.m_pwsz, -1, (Gdiplus::Font *) m_font->get_os_data(), origin, &rect2);*/

      string str1;
      str1 = L"WM123AWZwmciItf";
      string str2;
      str2 = L"WWÜ123AWZwmcpQçgÁiItf";

      size sz1 = GetTextExtent(str1);
      size sz2 = GetTextExtent(str2);

      lpMetrics->tmAveCharWidth = sz2.cx / (double) str2.get_length();
      lpMetrics->tmAscent = sz1.cy;
      lpMetrics->tmDescent = sz2.cy - sz1.cy;


      //retry_single_lock slGdiplus(&System.s_mutexGdiplus, millis(1), millis(1));

      /*((::draw2d_xlib::graphics *) this)->set(m_pfont);

      // Get the font from GC.
      ::XFontStruct *font = ::XQueryFont(m_pdc->m_pdisplay, ::XGContextFromGC(m_pdc->m_gc));

      // Compute and return the line height.
      if(nullptr == font)
      {

         return false;
      }

      lpMetrics->tmAscent              = (::i32) font->max_bounds.ascent;
      lpMetrics->tmDescent             = (::i32) font->max_bounds.descent;
      lpMetrics->tmHeight              = (::i32) font->ascent + font->descent;*/

      lpMetrics->tmInternalLeading     = (::i32) lpMetrics->tmAscent + lpMetrics->tmDescent - lpMetrics->tmHeight;
      lpMetrics->tmExternalLeading     = (::i32) (lpMetrics->tmHeight * 0.25);

//      lpMetrics->tmAveCharWidth        = (::i32) (font->max_bounds.width + font->min_bounds.width) / 2; // fast calculation

      //::XFreeFontInfo(nullptr, font, 0);

      return true;

   }


   bool graphics::get_output_text_metrics(::draw2d::text_metric * lpMetrics) const
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetTextMetrics(get_handle1(), lpMetrics) != FALSE;

   }


   i32 graphics::GetTextCharacterExtra() const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetTextCharacterExtra(get_handle2());

   }

   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != FALSE;

   }

   bool graphics::GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer) const
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != FALSE;

   }

   u32 graphics::GetFontLanguageInfo() const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetFontLanguageInfo(get_handle1());

   }

   /*

      u32 graphics::GetCharacterPlacement(const char * lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const
      {

         __throw(not_implemented());
         return 0;

   //      ASSERT(get_handle1() != nullptr);
   //      return ::GetCharacterPlacement(get_handle1(), lpString, nCount, nMaxExtent, lpResults, dwFlags);

      }

      u32 graphics::GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const
      {

         __throw(not_implemented());
         return 0;

   //      ASSERT(get_handle1() != nullptr);
   //      return ::GetCharacterPlacement(get_handle1(), (const char *)str, (i32) str.get_length(), nMaxExtent, lpResults, dwFlags);

      }

   */

   size graphics::GetAspectRatioFilter() const
   {

      __throw(not_implemented());
      return size(0, 0);

//      ASSERT(get_handle2() != nullptr);
//      ::size size;
//      VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
//      return size;

   }


   bool graphics::ScrollDC(i32 dx, i32 dy, rect lpRectScroll, const ::rect & rectClip, ::draw2d::region* pRgnUpdate, LPRECT32 lpRectUpdate)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::ScrollDC(get_handle1(), dx, dy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != FALSE;

   }

   // Printer Escape Functions
   i32 graphics::Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData)
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);

   }

   // graphics 3.1 Specific functions
   ::u32 graphics::SetBoundsRect(::rect rectBounds, ::u32 flags)
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetBoundsRect(get_handle1(), rectBounds, flags);

   }

   ::u32 graphics::GetBoundsRect(LPRECT32 rectBounds, ::u32 flags)
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetBoundsRect(get_handle2(), rectBounds, flags);

   }

   /*

      bool graphics::ResetDC(const DEVMODE* lpDevMode)
      {

         __throw(not_implemented());
         return false;

   //    ASSERT(get_handle2() != nullptr);
   //    return ::ResetDC(get_handle2(), lpDevMode) != nullptr;

      }

      ::u32 graphics::GetOutlineTextMetrics(::u32 cbData, LPOUTLINETEXTMETRICW lpotm) const
      {

         __throw(not_implemented());
         return 0;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetOutlineTextMetrics(get_handle2(), cbData, lpotm);

      }

      bool graphics::GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABC lpabc) const
      {

         __throw(not_implemented());
         return false;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetCharABCWidths(get_handle2(), nFirstChar, nLastChar, lpabc) != FALSE;

      }

   */

   u32 graphics::GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetFontData(get_handle2(), dwTable, dwOffset, lpData, cbData);

   }

   /*

      i32 graphics::GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const
      {

         __throw(not_implemented());
         return 0;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetKerningPairs(get_handle2(), nPairs, lpkrnpair);

      }

      u32 graphics::GetGlyphOutline(::u32 nChar, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPGLYPHMETRICS lpgm, u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const
      {

         __throw(not_implemented());
         return 0;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetGlyphOutline(get_handle2(), nChar, nFormat, lpgm, cbBuffer, lpBuffer, lpmat2);

      }

   */

   /*

      // ::user::object handling functions
      i32 graphics::StartDoc(LPDOCINFO lpDocInfo)
      {

         __throw(not_implemented());
         return 0;

   //      ASSERT(get_handle1() != nullptr);
   //      return ::StartDoc(get_handle1(), lpDocInfo);

      }

   */

   i32 graphics::StartPage()
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::StartPage(get_handle1());

   }

   i32 graphics::EndPage()
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::EndPage(get_handle1());

   }

   i32 graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32))
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetAbortProc(get_handle1(), (ABORTPROC)lpfn);

   }

   i32 graphics::AbortDoc()
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::AbortDoc(get_handle1());

   }

   i32 graphics::EndDoc()
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::EndDoc(get_handle1());

   }

   bool graphics::MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != FALSE;

   }

   bool graphics::PlgBlt(POINT32 * lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::PlgBlt(get_handle1(), lpPoint, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.get_os_data(), xMask, yMask) != FALSE;

   }

   bool graphics::SetPixelV(i32 x, i32 y, color32_t crColor)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetPixelV(get_handle1(), x, y, crColor) != FALSE;

   }

   bool graphics::SetPixelV(const ::point & point, color32_t crColor)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != FALSE;

   }

   bool graphics::AngleArc(i32 x, i32 y, i32 nRadius, float fStartAngle, float fSweepAngle)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != FALSE;

   }

   bool graphics::ArcTo(const ::rect & rect, const ::point & pointStart, const ::point & pointEnd)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ArcTo(rect.left, rect.top, rect.right, rect.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

   }

   i32 graphics::GetArcDirection() const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetArcDirection(get_handle2());

   }

   bool graphics::PolyPolyline(const POINT32* lpPoints, const u32* lpPolyPoints, i32 nCount)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::PolyPolyline(get_handle1(), lpPoints, lpPolyPoints, nCount) != FALSE;

   }

   /*

      bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const
      {

         __throw(not_implemented());
         return false;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;

      }

   */

   ::draw2d::pen_pointer graphics::get_current_pen() const
   {

      return m_ppen;

   }

   ::draw2d::brush_pointer graphics::get_current_brush() const
   {

      return m_pbrush;

   }

   ::draw2d::palette_pointer graphics::get_current_palette() const
   {

      return (::draw2d::palette *)nullptr;

   }

   ::draw2d::font_pointer graphics::get_current_font() const
   {

      return m_pfont;

   }


   ::draw2d::bitmap_pointer graphics::get_current_bitmap() const
   {

      return m_pbitmap;

   }

   bool graphics::PolyBezier(const POINT32* lpPoints, i32 nCount)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::PolyBezier(get_handle1(), lpPoints, nCount) != FALSE;

   }

   i32 graphics::DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData)
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);

   }

   i32 graphics::Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData,  i32 nOutputSize, char * lpszOutputData)
   {

      __throw(not_implemented());
      return 0;

//       ASSERT(get_handle1() != nullptr);
//       return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);

   }

   /*

      bool graphics::GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABCFLOAT lpABCF) const
      {

         __throw(not_implemented());
         return false;

   //      ASSERT(get_handle2() != nullptr);
   //      return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != FALSE;

      }

   */

   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, float* lpFloatBuffer) const
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle2() != nullptr);
//      return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != FALSE;

   }

   bool graphics::AbortPath()
   {

      __throw(not_implemented());
      return false;

      /*
            if(m_ppath != nullptr)
            {
               delete m_ppath;
               m_ppath = nullptr;
            }
            return true;
      */

   }

   bool graphics::BeginPath()
   {

      __throw(not_implemented());
      return false;

      /*
            if(m_ppath != nullptr)
               delete m_ppath;

            m_ppath = new Gdiplus::GraphicsPath;

            return m_ppath != nullptr;
      */

   }

   bool graphics::CloseFigure()
   {

      __throw(not_implemented());
      return false;

      /*
            ASSERT(m_ppath != nullptr);
            return m_ppath->CloseFigure() == Gdiplus::Status::Ok;
      */
   }

   bool graphics::EndPath()
   {

      __throw(not_implemented());
      return false;

      /*
            if(m_ppath == nullptr)
               return FALSE;

            m_ppathPaint   = m_ppath;
            m_ppath        = nullptr;

            return true;
      */
   }

   bool graphics::FillPath()
   {

      __throw(not_implemented());
      return false;

//      return m_pgraphics->FillPath(gdiplus_brush(), m_ppath) == Gdiplus::Status::Ok;

   }

   bool graphics::FlattenPath()
   {

      __throw(not_implemented());
      return false;

//      return m_ppath->Flatten() == Gdiplus::Status::Ok;

   }

   float graphics::GetMiterLimit() const
   {

      __throw(not_implemented());
      return 0.f;

//      ASSERT(get_handle1() != nullptr);
//      float fMiterLimit;
//      VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
//      return fMiterLimit;

   }

   i32 graphics::GetPath(POINT32 * lpPoints, byte * lpTypes, i32 nCount) const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetPath(get_handle1(), lpPoints, lpTypes, nCount);

   }

   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetMiterLimit(get_handle1(), fMiterLimit, nullptr) != FALSE;

   }

   bool graphics::StrokeAndFillPath()
   {

      __throw(not_implemented());
      return false;

//      bool bOk1 = m_pgraphics->FillPath(gdiplus_brush(), m_ppathPaint) == Gdiplus::Status::Ok;

//      bool bOk2 = m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

//      return bOk1 && bOk2;

   }

   bool graphics::StrokePath()
   {

      __throw(not_implemented());
      return false;

//      return m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

   }

   bool graphics::WidenPath()
   {

      __throw(not_implemented());
      return false;

//      return m_ppath->Widen(gdiplus_pen()) == Gdiplus::Status::Ok;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      if(!set(ppath))
         return false;

      return draw();

   }

   bool graphics::fill_path(::draw2d::path * ppath)
   {

      if(!set(ppath))
         return false;

      return fill();

   }


   bool graphics::AddMetaFileComment(::u32 nDataSize, const byte* pCommentData)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GdiComment(get_handle1(), nDataSize, pCommentData) != FALSE;

   }


   /*bool CALLBACK metacallback(
      EmfPlusRecordType recordType,
      u32 flags,
      u32 dataSize,
      const unsigned char* pStr,
      void* callbackData)
   {
      // Play only EmfPlusRecordTypeFillEllipse records.
      if (recordType == EmfPlusRecordTypeFillEllipse)
      {
      // Explicitly cast callbackData as a metafile pointer, and use it to call
      // the PlayRecord method.
      static_cast < Metafile* > (callbackData)->PlayRecord(recordType, flags, dataSize, pStr);
      }
      return TRUE;
   }

   VOID Example_EnumerateMetafile9(HDC hdc)
   {
      Graphics graphics(hdc);
      // Create a Metafile object from an existing disk metafile.
      Metafile* pMeta = new Metafile(L"SampleMetafile.emf", hdc);
      {
         // Fill a rectangle and an ellipse in pMeta.
         Graphics metaGraphics(pMeta);
         metaGraphics.FillRectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
     metaGraphics.FillEllipse(&SolidBrush(Color(255, 255, 0, 0)), 100, 0, 200, 100);
      }
      // Enumerate pMeta to the destination rectangle, passing pMeta as the CALLBACK data.
      graphics.EnumerateMetafile(
      pMeta,
      Rect(0, 0, 300, 50),
      metacallback,
      pMeta);
      // Draw pMeta as an pimage->
      graphics.DrawImage(pMeta, Point(0, 150));
      delete pMeta;;
   }*/

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, rect lpBounds)
   {

      __throw(not_implemented());
      return false;


      /*      Gdiplus::RectF rect((Gdiplus::REAL) lpBounds->left, (Gdiplus::REAL) lpBounds->top, (Gdiplus::REAL) width(lpBounds), (Gdiplus::REAL) height(lpBounds));

            Gdiplus::Metafile* pMeta = new Gdiplus::Metafile(hEnhMF, false);

            //m_pgraphcis->EnumerateMetafile(pMeta, rect, metacallback, PMETAHEADER);

            bool bOk = m_pgraphics->DrawImage(pMeta, rect) == Gdiplus::Status::Ok;

            delete pMeta;

            return bOk ? TRUE : FALSE;*/
      //return ::PlayEnhMetaFile(get_handle1(), hEnhMF, lpBounds);

   }

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

// Thank you
// Jiju George T
// Web Developer
// India India
// Member

   bool graphics::alpha_blend(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate)
   {

      return this->BitBlt(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc);

      //sync_lock ml(&xlib_mutex());

      if(m_pimageAlphaBlend->is_set())
      {

         __throw(not_implemented());

         /*
                  ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


                  ::image_pointer pimageWork = nullptr;
                  ::image_pointer pimageWork2 = nullptr;
         //         ::image_pointer pimageWork3 = nullptr;
                  ::image_pointer pimageWork4 = nullptr;


                  ::point pointSrc(xSrc, ySrc);
                  ::point ptDest(xDest, yDest);
                  ::size size(nDestWidth, nDestHeight);



                  ::image_pointer pimage;
                  if(imageWork == nullptr)
                  {
                     pimage = create_image(get_object());
                     imageWork = pimage;
                  }
                  if(imageWork == nullptr)
                     return false;
                  if(!imageWork = create_image(size))
                     return false;
                  if(!imageWork.from(::point(), pgraphicsSrc, pointSrc, size))
                     return false;




                  ::image_pointer pimage2;
                  if(imageWork2 == nullptr)
                  {
                     pimage2 = create_image(get_object());
                     imageWork2 = pimage2;
                  }


                  ::image_pointer pimage4;
                  if(imageWork4 == nullptr)
                  {
                     image4 = create_image(get_object());
                     imageWork4 = image4;
                  }
                  if(imageWork4 == nullptr)
                     return false;
                  if(!imageWork4 = create_image(size))
                     return false;


                  imageWork4.Fill(255, 0, 0, 0);

                  imageWork4.from(point(max(0, m_pointAlphaBlend.x - xDest), max(0, m_pointAlphaBlend.y - yDest)),
                     m_pimageAlphaBlend->get_graphics(), point(max(0, xDest - m_pointAlphaBlend.x), max(0, yDest - m_pointAlphaBlend.y)), size);

                  imageWork.channel_multiply(::color::channel_alpha, imageWork4);


                  keeper < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


                  return System.imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), pointSrc);

         */
      }

      /*if(pgraphicsSrc == nullptr)
         return false;


      if(nSrcWidth == 0 || nSrcHeight == 0 || nDstWidth == 0 || nDstHeight == 0)
         return false;

      xlib_pattern_t * ppattern = xlib_get_source((xlib_t *) pgraphicsSrc->get_os_data());

      if(ppattern == nullptr)
         return false;

      if(xlib_pattern_status(ppattern) != CAIRO_STATUS_SUCCESS)
         return false;

      if(m_pdc == nullptr)
         return false;

      xlib_keep keep(m_pdc);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_translate(m_pdc, xDst, yDst);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_scale(m_pdc, (double) nDstWidth / (double) nSrcWidth, (double) nDstHeight / (double) nSrcHeight);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_set_source(m_pdc, ppattern);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_paint_with_alpha(m_pdc, dRate);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;

      xlib_pattern_destroy(ppattern);

      if(xlib_status(m_pdc) != CAIRO_STATUS_SUCCESS)
         return false;*/

      return true;

   }


   /*bool graphics::alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
      ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, BLENDFUNCTION blend)
   {

      __throw(not_implemented());
      //if(get_handle1() == nullptr)
        // return false;


      if(m_pimageAlphaBlend->is_set())
      {


         ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());


         ::image_pointer pimageWork = nullptr;
         ::image_pointer pimageWork2 = nullptr;
   //         ::image_pointer pimageWork3 = nullptr;
         ::image_pointer pimageWork4 = nullptr;


         ::point pointSrc(xSrc, ySrc);
         ::point ptDest(xDest, yDest);
         ::size size(nDestWidth, nDestHeight);



         ::image_pointer pimage;
         if(imageWork == nullptr)
         {
            pimage = create_image(get_object());
            imageWork = pimage;
         }
         if(imageWork == nullptr)
            return false;
         if(!imageWork = create_image(size))
            return false;
         if(!imageWork.from(::point(), pgraphicsSrc, pointSrc, size))
            return false;




         ::image_pointer pimage2;
         if(imageWork2 == nullptr)
         {
            pimage2 = create_image(get_object());
            imageWork2 = pimage2;
         }


         ::image_pointer pimage4;
         if(imageWork4 == nullptr)
         {
            image4 = create_image(get_object());
            imageWork4 = image4;
         }
         if(imageWork4 == nullptr)
            return false;
         if(!imageWork4 = create_image(size))
            return false;


         imageWork4.Fill(255, 0, 0, 0);

         imageWork4.from(point(max(0, m_pointAlphaBlend.x - xDest), max(0, m_pointAlphaBlend.y - yDest)),
            m_pimageAlphaBlend->get_graphics(), point(max(0, xDest - m_pointAlphaBlend.x), max(0, yDest - m_pointAlphaBlend.y)), size);

         imageWork.channel_multiply(::color::channel_alpha, imageWork4);


         keeper < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);


         return System.imaging().true_blend(this, ptDest, size, imageWork.get_graphics(), pointSrc);


      }

      return ::AlphaBlend(get_handle1(), xDest, yDest,
         nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
         nSrcHeight, blend) != FALSE;
   }*/


   bool graphics::TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, ::u32 crTransparent)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::TransparentBlt(get_handle1(), xDest, yDest, nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent) != FALSE;

   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, ULONG nVertices, void * pMesh, ULONG nMeshElements, u32 dwMode)
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GradientFill(get_handle1(), pVertices, nVertices, pMesh, nMeshElements, dwMode) != FALSE;

   }

#if (_WIN32_WINNT >= 0x0500)

   // Always Inline. Functions only in Win98/Win2K or later


   color32_t graphics::GetDCBrushColor() const
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetDCBrushColor(get_handle1());

   }

   color32_t graphics::SetDCBrushColor(color32_t crColor)
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetDCBrushColor(get_handle1(), crColor);

   }

   color32_t graphics::GetDCPenColor() const
   {

      __throw(not_implemented());
      return 0;

//       ASSERT(get_handle1() != nullptr);
//       return ::GetDCPenColor(get_handle1());
   }

   color32_t graphics::SetDCPenColor(color32_t crColor)
   {

      __throw(not_implemented());
      return 0;

//      ASSERT(get_handle1() != nullptr);
//      return ::SetDCPenColor(get_handle1(), crColor);

   }

#endif

#if (_WIN32_WINNT >= 0x0500)

   bool graphics::GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC lpabc) const
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetCharABCWidthsI(get_handle1(), giFirst, cgi, pgi, lpabc) != FALSE;

   }

   bool graphics::GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPINT lpBuffer) const
   {

      __throw(not_implemented());
      return false;

//      ASSERT(get_handle1() != nullptr);
//      return ::GetCharWidthI(get_handle1(), giFirst, cgi, pgi, lpBuffer) != FALSE;

   }

#endif

#if (_WIN32_WINNT >= 0x0500)

   bool graphics::GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE32 LPSIZE32) const
   {

      __throw(not_implemented());
      return false;

//      ENSURE(LPSIZE32 != nullptr);
//      ASSERT(get_handle1() != nullptr);
//      return ::GetTextExtentExPointI(get_handle1(), pgiIn, cgi, nMaxExtent, lpnFit, alpDx, LPSIZE32) != FALSE;

   }


   bool graphics::GetTextExtentPointI(LPWORD pgiIn, i32 cgi, LPSIZE32 LPSIZE32) const
   {

      __throw(not_implemented());
      return false;

//      ENSURE(LPSIZE32 != nullptr);
//      ASSERT(get_handle1() != nullptr);
//      return ::GetTextExtentPointI(get_handle1(), pgiIn, cgi, LPSIZE32) != FALSE;

   }


#endif


   /////////////////////////////////////////////////////////////////////////////
   // More coordinate transforms (in separate file to avoid transitive refs)

#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE32 LPSIZE32) const
   {

      __throw(not_implemented());

      /*
            ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE32)));

            i32 nMapMode;
            if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC && nMapMode != MM_TEXT)
            {
               // when using a constrained ::collection::map mode, ::collection::map against physical inch
               ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
               DPtoLP(LPSIZE32);
               ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
            }
            else
            {
               // ::collection::map against logical inch for non-constrained mapping modes
               i32 cxPerInch, cyPerInch;
               if (this != nullptr)
               {
                  ASSERT_VALID(this);
                  ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
                  cxPerInch = GetDevicecaps(LOGPIXELSX);
                  cyPerInch = GetDevicecaps(LOGPIXELSY);
               }
               else
               {
      //            cxPerInch = afxData.cxPixelsPerInch;
        //          cyPerInch = afxData.cyPixelsPerInch;
               }
               ASSERT(cxPerInch != 0 && cyPerInch != 0);
               LPSIZE32->cx = MulDiv(LPSIZE32->cx, HIMETRIC_INCH, cxPerInch);
               LPSIZE32->cy = MulDiv(LPSIZE32->cy, HIMETRIC_INCH, cyPerInch);
            }

      */

   }

   void graphics::HIMETRICtoDP(LPSIZE32 LPSIZE32) const
   {

      __throw(not_implemented());

      /*      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE32)));

            i32 nMapMode;
            if (this != nullptr && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
               nMapMode != MM_TEXT)
            {
               // when using a constrained ::collection::map mode, ::collection::map against physical inch
               ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
               LPtoDP(LPSIZE32);
               ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
            }
            else
            {
               // ::collection::map against logical inch for non-constrained mapping modes
               i32 cxPerInch, cyPerInch;
               if (this != nullptr)
               {
                  ASSERT_VALID(this);
                  ASSERT(get_handle1() != nullptr);  // no HDC attached or created?
                  cxPerInch = GetDevicecaps(LOGPIXELSX);
                  cyPerInch = GetDevicecaps(LOGPIXELSY);
               }
               else
               {
      //            cxPerInch = afxData.cxPixelsPerInch;
        //          cyPerInch = afxData.cyPixelsPerInch;
               }
               ASSERT(cxPerInch != 0 && cyPerInch != 0);
               LPSIZE32->cx = MulDiv(LPSIZE32->cx, cxPerInch, HIMETRIC_INCH);
               LPSIZE32->cy = MulDiv(LPSIZE32->cy, cyPerInch, HIMETRIC_INCH);
            }

      */

   }

   void graphics::LPtoHIMETRIC(LPSIZE32 LPSIZE32) const
   {
      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE32)));

      LPtoDP(LPSIZE32);
      DPtoHIMETRIC(LPSIZE32);
   }

   void graphics::HIMETRICtoLP(LPSIZE32 LPSIZE32) const
   {
      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE32)));

      HIMETRICtoDP(LPSIZE32);
      DPtoLP(LPSIZE32);
   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* PASCAL graphics::GetHalftoneBrush(::layered * pobjectContext)
   {
      /*      ::aura::LockGlobals(CRIT_HALFTONEBRUSH);
            if (gen_HalftoneBrush == nullptr)
            {
               ::u16 grayPattern[8];
               for (i32 i = 0; i < 8; i++)
                  grayPattern[i] = (::u16)(0x5555 << (i & 1));
               HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
               if (grayBitmap != nullptr)
               {
                  gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
                  ::DeleteObject(grayBitmap);
               }
            }
            if (!gen_WingdixTerm)
               gen_WingdixTerm = (char)!atexit(&__win_gdi_x_term);
            ::aura::UnlockGlobals(CRIT_HALFTONEBRUSH);

      //      return ::win::brush::from_handle(papp, gen_HalftoneBrush);*/
      return nullptr;
   }

   void graphics::DrawDragRect(const ::rect & rect, const ::size & size, const ::rect & rectLast, const ::size & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {

      __throw(not_implemented());

      /*
            ASSERT(__is_valid_address(rect, sizeof(RECT32), FALSE));
            ASSERT(lpRectLast == nullptr ||
               __is_valid_address(lpRectLast, sizeof(RECT32), FALSE));

            // first, determine the update region and select it
            ::draw2d::region rgnNew;
            ::draw2d::region rgnOutside, rgnInside;
            rgnOutside.CreateRectRgnIndirect(rect);
            const ::rect & rect = *rect;
            rect.inflate(-size.cx, -size.cy);
            rect.intersect(rect, rect);
            rgnInside.CreateRectRgnIndirect(rect);
            rgnNew.CreateRectRgn(0, 0, 0, 0);
            rgnNew.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

            ::draw2d::brush* pBrushOld = nullptr;
            if (pBrush == nullptr)
            {
               pBrush = graphics::GetHalftoneBrush(get_object());
            }

            ENSURE(pBrush);

            if (pBrushLast == nullptr)
            {
               pBrushLast = pBrush;
            }

            ::draw2d::region rgnLast, rgnUpdate;
            if (lpRectLast != nullptr)
            {
               // find difference between new region and old region
               rgnLast.CreateRectRgn(0, 0, 0, 0);
               rgnOutside.SetRectRgn(lpRectLast);
               rect = *lpRectLast;
               rect.inflate(-sizeLast.cx, -sizeLast.cy);
               rect.intersect(rect, lpRectLast);
               rgnInside.SetRectRgn(rect);
               rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

               // only diff them if brushes are the same
               if (pBrush->get_os_data() == pBrushLast->get_os_data())
               {
                  rgnUpdate.CreateRectRgn(0, 0, 0, 0);
                  rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
               }
            }
            if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != nullptr)
            {
               // brushes are different -- erase old region first
               SelectClipRgn(&rgnLast);
               GetClipBox(&rect);
               pBrushOld = SelectObject(pBrushLast);
               PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);
               SelectObject(pBrushOld);
               pBrushOld = nullptr;
            }

            // draw into the update/new region
            SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
            GetClipBox(&rect);
            pBrushOld = SelectObject(pBrush);
            PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);

            // cleanup DC
            if (pBrushOld != nullptr)
               SelectObject(pBrushOld);
            SelectClipRgn(nullptr);

      */

   }

   /*void graphics::FillSolidRect(const ::rect & rect, color32_t clr)
   {
      ::SetBkColor(get_handle1(), clr);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, rect, nullptr, 0, nullptr);
   }*/

   void graphics::FillSolidRect(const RECT64 * rect, color32_t clr)
   {
      ::rect rect32;
      __copy(rect32, rect);
      FillSolidRect(rect32, clr);
   }


   /*

   void graphics::FillSolidRect(i32 x, i32 y, i32 cx, i32 cy, color32_t clr)
   {
      ::SetBkColor(get_handle1(), clr);
      ::rect rect(x, y, x + cx, y + cy);
      ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, &rect, nullptr, 0, nullptr);
   }

   */

   void graphics::Draw3dRect(const ::rect & rect,
                             color32_t clrTopLeft, color32_t clrBottomRight)
   {
      Draw3dRect(rect.left, rect.top, rect.right - rect.left,
                 rect.bottom - rect.top, clrTopLeft, clrBottomRight);
   }

   void graphics::Draw3dRect(i32 x, i32 y, i32 cx, i32 cy,
                             color32_t clrTopLeft, color32_t clrBottomRight)
   {
      FillSolidRect(x, y, cx - 1, 1, clrTopLeft);
      FillSolidRect(x, y, 1, cy - 1, clrTopLeft);
      FillSolidRect(x + cx - 1, y, 1, cy, clrBottomRight);
      FillSolidRect(x, y + cy - 1, cx, 1, clrBottomRight);
   }





   //::draw2d::graphics * PASCAL ::win::graphics::from_handle(HDC hDC)
   //{
   //hdc_map* pMap = afxMapHDC(TRUE); //create ::collection::map if not exist
   //ASSERT(pMap != nullptr);
//      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)pMap->from_handle(hDC);
   //    ASSERT(pgraphics == nullptr || (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() == hDC);
   //  return pgraphics;
   // return nullptr;
   //}

   /*

      bool graphics::Attach(HDC hdc)
      {

         if(hdc == nullptr)
            return false;

         if(m_hdc == hdc)
         {

            if(m_pgraphics != nullptr)
               return true;

         }

         if(hdc != nullptr)
         {

            m_pgraphics = new ::Gdiplus::Graphics(hdc);

            set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

            m_hdc = hdc;

         }

         return m_pgraphics != nullptr;

         /*ASSERT(get_handle1() == nullptr);      // only attach once, detach on destroy
         ASSERT(get_handle2() == nullptr);    // only attach to an is_empty DC

         if (hDC == nullptr)
         {
            return FALSE;
         }
         // remember early to avoid leak
         set_handle1(hDC);
         hdc_map* pMap = afxMapHDC(TRUE); // create ::collection::map if not exist
         ASSERT(pMap != nullptr);
         pMap->set_permanent(get_handle1(), this);

         SetAttribDC(get_handle1());     // Default to same as output
         return TRUE;*/
//   }

   /* HDC graphics::Detach()
    {

       if(m_hdc == nullptr)
          return nullptr;

       if(m_pgraphics == nullptr)
          return nullptr;

       delete m_pgraphics;
       m_pgraphics = nullptr;

       HDC hdc = m_hdc;
       m_hdc = nullptr;

       return hdc;

    }
   */

   bool graphics::DeleteDC()
   {

      //sync_lock ml(&xlib_mutex());

      m_pbitmap.release();

      if(m_pdc == nullptr)
         return true;

      XFreeGC(m_pdc->m_pdisplay, m_pdc->m_gc);

      delete m_pdc;

      m_pdc = nullptr;

      return true;

   }


   /*

      void graphics::SetAttribDC(HDC hDC)  // Set the Attribute DC
      {
   //      set_handle2(hDC);
      }

      void graphics::SetOutputDC(HDC hDC)  // Set the Output DC
      {
   #ifdef _DEBUG
   /*      hdc_map* pMap = afxMapHDC();
         if (pMap != nullptr && pMap->lookup_permanent(get_handle1()) == this)
         {
            TRACE(::aura::trace::category_AppMsg, 0, "cannot Set Output hDC on Attached graphics.\n");
            ASSERT(FALSE);
         }*/
//#endif
   //    set_handle1(hDC);
   //}
   /*
      void graphics::ReleaseAttribDC()     // Release the Attribute DC
      {
   //      set_handle2(nullptr);
      }

      void graphics::ReleaseOutputDC()     // Release the Output DC
      {
   #ifdef _DEBUG
   /*      hdc_map* pMap = afxMapHDC();
         if (pMap != nullptr && pMap->lookup_permanent(get_handle1()) == this)
         {
            TRACE(::aura::trace::category_AppMsg, 0, "cannot Release Output hDC on Attached graphics.\n");
            ASSERT(FALSE);
         }*/
//#endif
   //set_handle1(nullptr);
   //

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   i32 graphics::StartDoc(const char * lpszDocName)
   {

      __throw(not_implemented());
      return 0;

      /*
            DOCINFO di;
            __memset(&di, 0, sizeof(DOCINFO));
            di.cbSize = sizeof(DOCINFO);
            di.lpszDocName = lpszDocName;
            return StartDoc(&di);
      */

   }

   i32 graphics::SaveDC()
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = 0;
            if(get_handle2() != nullptr)
               nRetVal = ::SaveDC(get_handle2());
            if(get_handle1() != nullptr && get_handle1() != get_handle2() && ::SaveDC(get_handle1()) != 0)
               nRetVal = -1;   // -1 is the only valid restore value for complex DCs
            return nRetVal;
      */

   }

   bool graphics::RestoreDC(i32 nSavedDC)
   {

      __throw(not_implemented());
      return false;

      /*
            bool bRetVal = TRUE;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               bRetVal = ::RestoreDC(get_handle1(), nSavedDC) != FALSE;
            if(get_handle2() != nullptr)
               bRetVal = (bRetVal && ::RestoreDC(get_handle2(), nSavedDC) != FALSE);
            return bRetVal;
      */

   }

//   object* PASCAL graphics::SelectGdiObject(::object * pobject, HDC hDC, HGDIOBJ h)
   // {
//      return ::win::object::from_handle(papp, ::SelectObject(hDC, h));
   //}

   ::draw2d::object* graphics::SelectStockObject(i32 nIndex)
   {
      /*      HGDIOBJ hObject = ::GetStockObject(nIndex);
            HGDIOBJ hOldObj = nullptr;
            ASSERT(hObject != nullptr);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               hOldObj = ::SelectObject(get_handle1(), hObject);
            if(get_handle2() != nullptr)
               hOldObj = ::SelectObject(get_handle2(), hObject);
            return ::win::object::from_handle(get_context_application(), hOldObj);*/

      return nullptr;
   }

   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* ppen)
   {
      /*HGDIOBJ hOldObj = nullptr;
      if(pPen == nullptr)
         return nullptr;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         hOldObj = ::SelectObject(get_handle1(), pPen->get_os_data());
      if(get_handle2() != nullptr)
         hOldObj = ::SelectObject(get_handle2(), pPen->get_os_data());
      return dynamic_cast < pen * > (::win::object::from_handle(get_context_application(), hOldObj));*/
      m_ppen = ppen;
      return m_ppen;
   }

   ::draw2d::brush* graphics::SelectObject(::draw2d::brush* pbrush)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pBrush == nullptr)
               return nullptr;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               hOldObj = ::SelectObject(get_handle1(), pBrush->get_os_data());
            if(get_handle2() != nullptr)
               hOldObj = ::SelectObject(get_handle2(), pBrush->get_os_data());
            return dynamic_cast < ::draw2d::brush * > (::win::object::from_handle(get_context_application(), hOldObj));*/
      m_pbrush = pbrush;
      return m_pbrush;

   }

   ::draw2d::font* graphics::SelectObject(::draw2d::font* pfont)
   {
      /*      HGDIOBJ hOldObj = nullptr;
            if(pFont == nullptr)
               return nullptr;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               hOldObj = ::SelectObject(get_handle1(), pFont->get_os_data());
            if(get_handle2() != nullptr)
               hOldObj = ::SelectObject(get_handle2(), pFont->get_os_data());
            return dynamic_cast < ::draw2d::font * > (::win::object::from_handle(get_context_application(), hOldObj));*/

      /*ASSERT(pFont != nullptr);

      if(pFont == nullptr)
         return nullptr;

      m_fontxyz = *pFont;
      return m_pfont;*/

      if(!select_font(pfont))
         return nullptr;

      return m_pfont;

   }

   i32 graphics::SelectObject(::draw2d::region* pRgn)
   {

      __throw(not_implemented());
      return false;

      /*
            i32 nRetVal = GDI_ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = (i32)(iptr)::SelectObject(get_handle1(), (HGDIOBJ) pRgn->get_os_data());
            if(get_handle2() != nullptr)
               nRetVal = (i32)(iptr)::SelectObject(get_handle2(), (HGDIOBJ) pRgn->get_os_data());
            return nRetVal;
      */

   }

   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {
      return nullptr;
//      return dynamic_cast < ::draw2d::palette * > (::win::object::from_handle(get_context_application(), ::SelectPalette(get_handle1(), (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }


   i32 graphics::SetPolyFillMode(i32 nPolyFillMode)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
            if(get_handle2() != nullptr)
               nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
            return nRetVal;
      */

   }

   i32 graphics::SetROP2(i32 nDrawMode)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetROP2(get_handle1(), nDrawMode);
            if(get_handle2() != nullptr)
               nRetVal = ::SetROP2(get_handle2(), nDrawMode);
            return nRetVal;
      */

   }

   i32 graphics::set_interpolation_mode(i32 nStretchMode)
   {

      //__throw(not_implemented());
//      return 0;

      m_nStretchBltMode = nStretchMode;
      return 1;

      /*i32 nRetVal = 0;
      if(get_handle1() != nullptr && get_handle1() != get_handle2())
         nRetVal = ::set_interpolation_mode(get_handle1(), nStretchMode);
      if(get_handle2() != nullptr)
         nRetVal = ::set_interpolation_mode(get_handle2(), nStretchMode);
      return nRetVal;*/
   }


   i32 graphics::SetGraphicsMode(i32 iMode)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
            {
               nRetVal = ::SetGraphicsMode(get_handle1(), iMode);
            }
            if(get_handle2() != nullptr)
            {
               nRetVal = ::SetGraphicsMode(get_handle2(), iMode);
            }
            return nRetVal;
      */

   }

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      __throw(not_implemented());
      return false;

      /*
            bool nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
            {
               nRetVal = ::SetWorldTransform(get_handle1(), pXform) != FALSE;
            }
            if(get_handle2() != nullptr)
            {
               nRetVal = ::SetWorldTransform(get_handle2(), pXform) != FALSE;
            }
            return nRetVal;
      */

   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform,u32 iMode)
   {

      __throw(not_implemented());
      return false;


      /*
            bool nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
            {
               nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != FALSE;
            }
            if(get_handle2() != nullptr)
            {
               nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != FALSE;
            }
            return nRetVal;
      */

   }

   i32 graphics::SetMapMode(i32 nMapMode)
   {

      //__throw(not_implemented());
      return 0;


      /*
            i32 nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetMapMode(get_handle1(), nMapMode);
            if(get_handle2() != nullptr)
               nRetVal = ::SetMapMode(get_handle2(), nMapMode);
            return nRetVal;
      */

   }


   point graphics::GetViewportOrg() const
   {

      return m_pdc->m_pointOffset;

   }


   point graphics::SetViewportOrg(i32 x, i32 y)
   {

      m_pdc->m_pointOffset.x = x;

      m_pdc->m_pointOffset.y = y;

      return m_pdc->m_pointOffset;

   }


   point graphics::OffsetViewportOrg(i32 nWidth, i32 nHeight)
   {

      m_pdc->m_pointOffset.x += nWidth;

      m_pdc->m_pointOffset.y += nHeight;

      return m_pdc->m_pointOffset;

   }

   size graphics::SetViewportExt(i32 x, i32 y)
   {

      __throw(not_implemented());
      return ::size(0, 0);

      /*
            size size(0, 0);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::SetViewportExtEx(get_handle1(), x, y, &size);
            if(get_handle2() != nullptr)
               ::SetViewportExtEx(get_handle2(), x, y, &size);
            return size;
      */
   }

   size graphics::ScaleViewportExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom)
   {

      __throw(not_implemented());
      return ::size(0, 0);

      /*
            size size(0, 0);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::ScaleViewportExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
            if(get_handle2() != nullptr)
               ::ScaleViewportExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
            return size;
      */

   }

   point graphics::SetWindowOrg(i32 x, i32 y)
   {

      __throw(not_implemented());
      return ::point();

      /*
            ::point point;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::SetWindowOrgEx(get_handle1(), x, y, &point);
            if(get_handle2() != nullptr)
               ::SetWindowOrgEx(get_handle2(), x, y, &point);
            return point;
      */
   }

   point graphics::OffsetWindowOrg(i32 nWidth, i32 nHeight)
   {

      __throw(not_implemented());
      return ::point();

      /*
            ::point point;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
            if(get_handle2() != nullptr)
               ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
            return point;
      */

   }

   size graphics::SetWindowExt(i32 x, i32 y)
   {

      __throw(not_implemented());
      return ::size(0, 0);

      /*
            size size(0, 0);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::SetWindowExtEx(get_handle1(), x, y, &size);
            if(get_handle2() != nullptr)
               ::SetWindowExtEx(get_handle2(), x, y, &size);
            return size;
      */

   }

   size graphics::ScaleWindowExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom)
   {

      __throw(not_implemented());
      return ::size(0, 0);

      /*
            size size(0, 0);
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
            if(get_handle2() != nullptr)
               ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
            return size;
      */

   }

   i32 graphics::GetClipBox(RECT32 * prect) const
   {

      //__throw(not_implemented());
      return 0;

      /*      return ::GetClipBox(get_handle1(), rect);*/
   }

   i32 graphics::SelectClipRgn(::draw2d::region * pregion)
   {

      /*sync_lock ml(&xlib_mutex());
      if(pregion == nullptr)
      {

         xlib_reset_clip(m_pdc);

      }
      else
      {

         if(m_spregion.is_null())
            m_spregion.create(e_create);

         *m_spregion.m_p = *pregion;

         //xlib_clip(m_pdc);

      }*/

      return 0;

      /*
            i32 nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SelectClipRgn(get_handle1(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            if(get_handle2() != nullptr)
               nRetVal = ::SelectClipRgn(get_handle2(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
            return nRetVal;
      */

   }

   i32 graphics::ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
            if(get_handle2() != nullptr)
               nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
            return nRetVal;
      */

   }

   i32 graphics::ExcludeClipRect(const ::rect & rect)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::ExcludeClipRect(get_handle1(), rect.left, rect.top,
               rect.right, rect.bottom);
            if(get_handle2() != nullptr)
               nRetVal = ::ExcludeClipRect(get_handle2(), rect.left, rect.top,
               rect.right, rect.bottom);
            return nRetVal;
      */

   }

   i32 graphics::IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
            if(get_handle2() != nullptr)
               nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
            return nRetVal;
      */

   }

   i32 graphics::IntersectClipRect(const ::rect & rect)
   {

      __throw(not_implemented());
      return 0;

      /*      i32 nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::IntersectClipRect(get_handle1(), rect.left, rect.top, rect.right, rect.bottom);
            if(get_handle2() != nullptr)
               nRetVal = ::IntersectClipRect(get_handle2(), rect.left, rect.top, rect.right, rect.bottom);
            return nRetVal;
      */

   }

   i32 graphics::OffsetClipRgn(i32 x, i32 y)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::OffsetClipRgn(get_handle1(), x, y);
            if(get_handle2() != nullptr)
               nRetVal = ::OffsetClipRgn(get_handle2(), x, y);
            return nRetVal;
      */

   }

   i32 graphics::OffsetClipRgn(const ::size & size)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
            if(get_handle2() != nullptr)
               nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
            return nRetVal;
      */
   }


   point graphics::MoveTo(i32 x, i32 y)
   {

      m_pdc->m_point.x = x;

      m_pdc->m_point.y = y;

      return m_pdc->m_point;

   }


   pointd graphics::MoveTo(double x, double y)
   {

      m_pdc->m_point.x = x;

      m_pdc->m_point.y = y;

      return pointd(x, y);

   }

   ::u32 graphics::SetTextAlign(::u32 nFlags)
   {

      __throw(not_implemented());
      return 0;

      /*
            ::u32 nRetVal = GDI_ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               ::SetTextAlign(get_handle1(), nFlags);
            if(get_handle2() != nullptr)
               nRetVal = ::SetTextAlign(get_handle2(), nFlags);
            return nRetVal;
      */

   }

   i32 graphics::SetTextJustification(i32 nBreakExtra, i32 nBreakCount)
   {

      __throw(not_implemented());
      return 0;

      /*
            i32 nRetVal = 0;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
            if(get_handle2() != nullptr)
               nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
            return nRetVal;
      */

   }

   i32 graphics::SetTextCharacterExtra(i32 nCharExtra)
   {

      __throw(not_implemented());
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            i32 nRetVal = 0x8000000;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
            if(get_handle2() != nullptr)
               nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
            return nRetVal;
      */

   }

   u32 graphics::SetMapperFlags(u32 dwFlag)
   {

      __throw(not_implemented());
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            u32 dwRetVal = GDI_ERROR;
            if(get_handle1() != nullptr && get_handle1() != get_handle2())
               dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
            if(get_handle2() != nullptr)
               dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
            return dwRetVal;
      */

   }

//   typedef u32 (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
//   typedef u32 (CALLBACK* __GDISETLAYOUTPROC)(HDC, u32);

   u32 graphics::GetLayout() const
   {

      __throw(not_implemented());
      return 0;

      /*
            HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
            ASSERT(hInst != nullptr);
            u32 dwGetLayout = LAYOUT_LTR;
            __GDIGETLAYOUTPROC pfn;
            pfn = (__GDIGETLAYOUTPROC) GetProcaddress(hInst, "GetLayout");
            // if they API is available, just call it. If it is not
            // available, indicate an error.
            if (pfn != nullptr)
               dwGetLayout = (*pfn)(get_handle1());
            else
            {
               dwGetLayout = GDI_ERROR;
               set_last_error(ERROR_caLL_NOT_IMPLEMENTED);
            }
            return dwGetLayout;
      */

   }

   u32 graphics::SetLayout(u32 dwSetLayout)
   {

      __throw(not_implemented());
      return 0;

      /*
            HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
            ASSERT(hInst != nullptr);
            u32 dwGetLayout = LAYOUT_LTR;
            __GDISETLAYOUTPROC pfn;
            pfn = (__GDISETLAYOUTPROC) GetProcaddress(hInst, "SetLayout");
            // If the API is availalbe, just call it. If it's not available,
            // setting anything other than LAYOUT_LTR is an error.
            if (pfn != nullptr)
               dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
            else if (dwSetLayout != LAYOUT_LTR)
            {
               dwGetLayout = GDI_ERROR;
               set_last_error(ERROR_caLL_NOT_IMPLEMENTED);
            }
            return dwGetLayout;
      */

   }
   /*
   void window::_001ScreenToClient(RECT32 * prect)
   {
   ASSERT(::IsWindow(get_handle1()));
   ::_001ScreenToClient(get_handle1(), (POINT32 *)rect);
   ::_001ScreenToClient(get_handle1(), ((POINT32 *)rect)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rect::swap_left_right(rect);
   }

   void window::_001ClientToScreen(RECT32 * prect)
   {
   ASSERT(::IsWindow(get_handle1()));
   ::_001ClientToScreen(get_handle1(), (POINT32 *)rect);
   ::_001ClientToScreen(get_handle1(), ((POINT32 *)rect)+1);
   if (GetExStyle() & WS_EX_LAYOUTRTL)
   rect::swap_left_right(rect);
   }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {

      __throw(not_implemented());
      return false;

      /*
            ASSERT(get_handle1() != nullptr);
            bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
            if (get_handle1() != get_handle2())
            {
               ::point point;
               VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
               VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
            }
            return bResult;
      */

   }

   i32 graphics::SetArcDirection(i32 nArcDirection)
   {


      __throw(not_implemented());
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            i32 nResult = 0;
            if (get_handle1() != get_handle2())
               nResult = ::SetArcDirection(get_handle1(), nArcDirection);
            if (get_handle2() != nullptr)
               nResult = ::SetArcDirection(get_handle2(), nArcDirection);
            return nResult;
      */

   }

   bool graphics::PolyDraw(const POINT32* lpPoints, const byte* lpTypes, i32 nCount)
   {

      __throw(not_implemented());
      return false;

      /*
            ASSERT(get_handle1() != nullptr);
            bool bResult = ::PolyDraw(get_handle1(), lpPoints, lpTypes, nCount) != FALSE;
            if (get_handle1() != get_handle2())
            {
               ::point point;
               VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
               VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
            }
            return bResult;
      */

   }

   bool graphics::PolylineTo(const POINT32* lpPoints, i32 nCount)
   {

      __throw(not_implemented());
      return false;

      /*
            ASSERT(get_handle1() != nullptr);
            bool bResult = ::PolylineTo(get_handle1(), lpPoints, nCount) != FALSE;
            if (get_handle1() != get_handle2())
            {
               ::point point;
               VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
               VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
            }
            return bResult;
      */

   }

   /*
      bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
      {

         __throw(not_implemented());
         return false;

   /*
         ASSERT(get_handle1() != nullptr);
         bool bResult = FALSE;
         if (get_handle1() != get_handle2())
            bResult = ::SetColorAdjustment(get_handle1(), lpColorAdjust) != FALSE;
         if (get_handle2() != nullptr)
            bResult = ::SetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;
         return bResult;
   */

//   }

   bool graphics::PolyBezierTo(const POINT32* lpPoints, i32 nCount)
   {

      __throw(not_implemented());
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            bool bResult = ::PolyBezierTo(get_handle1(), lpPoints, nCount) != FALSE;
            if (get_handle1() != get_handle2())
            {
               ::point point;
               VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
               VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
            }
            return bResult;
      */

   }

   bool graphics::SelectClipPath(i32 nMode)
   {

      __throw(not_implemented());
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);

            // output DC always holds the current path
            if (!::SelectClipPath(get_handle1(), nMode))
               return FALSE;

            // transfer clipping region into the attribute DC
            bool bResult = TRUE;
            if (get_handle1() != get_handle2())
            {
               HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
               if (::GetClipRgn(get_handle1(), hRgn) < 0 || !::SelectClipRgn(get_handle2(), hRgn))
               {
                  TRACE(::aura::trace::category_AppMsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
                  bResult = FALSE;
               }
               ::DeleteObject(hRgn);
            }
            return bResult;
      */

   }

   i32 graphics::SelectClipRgn(::draw2d::region* pRgn, i32 nMode)
   {

      __throw(not_implemented());
      return 0;

      /*      ASSERT(get_handle1() != nullptr);
            i32 nRetVal = ERROR;
            if (get_handle1() != get_handle2())
               nRetVal = ::ExtSelectClipRgn(get_handle1(), (HRGN)pRgn->get_os_data(), nMode);
            if (get_handle2() != nullptr)
               nRetVal = ::ExtSelectClipRgn(get_handle2(), (HRGN)pRgn->get_os_data(), nMode);
            return nRetVal;
      */

   }

   /////////////////////////////////////////////////////////////////////////////
   // Special handling for metafile playback
   /*
      i32 CALLBACK __enum_meta_file_procedure(HDC hDC,
         HANDLETABLE* pHandleTable, METARECORD* pMetaRec, i32 nHandles, LPARAM lParam)
      {
         ::draw2d::graphics * pgraphics = (::draw2d::graphics *)lParam;
         ASSERT_VALID(pgraphics);

         switch (pMetaRec->rdFunction)
         {
            // these records have effects different for each graphics derived class
         case META_SETMAPMODE:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetMapMode((i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETWINDOWEXT:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetWindowExt(
               (i32)(short)pMetaRec->rdParm[1], (i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETWINDOWORG:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetWindowOrg(
               (i32)(short)pMetaRec->rdParm[1], (i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETVIEWPORTEXT:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetViewportExt(
               (i32)(short)pMetaRec->rdParm[1], (i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETVIEWPORTORG:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetViewportOrg(
               (i32)(short)pMetaRec->rdParm[1], (i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_ScaLEWINDOWEXT:
            (dynamic_cast<::win::graphics * >(pgraphics))->ScaleWindowExt(
               (i32)(short)pMetaRec->rdParm[3], (i32)(short)pMetaRec->rdParm[2],
               (i32)(short)pMetaRec->rdParm[1], (i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_ScaLEVIEWPORTEXT:
            (dynamic_cast<::win::graphics * >(pgraphics))->ScaleViewportExt(
               (i32)(short)pMetaRec->rdParm[3], (i32)(short)pMetaRec->rdParm[2],
               (i32)(short)pMetaRec->rdParm[1], (i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_OFFSETVIEWPORTORG:
            (dynamic_cast<::win::graphics * >(pgraphics))->OffsetViewportOrg(
               (i32)(short)pMetaRec->rdParm[1], (i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_SAVEDC:
            (dynamic_cast<::win::graphics * >(pgraphics))->SaveDC();
            break;
         case META_RESTOREDC:
            (dynamic_cast<::win::graphics * >(pgraphics))->RestoreDC((i32)(short)pMetaRec->rdParm[0]);
            break;
         case META_SETBKCOLOR:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetBkColor(*(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
            break;
         case META_SETTEXTCOLOR:
            (dynamic_cast<::win::graphics * >(pgraphics))->SetTextColor(*(UNALIGNED color32_t*)&pMetaRec->rdParm[0]);
            break;

            // need to watch out for SelectObject(HFONT), for custom font mapping
         case META_SELECTOBJECT:
            {
               HGDIOBJ hObject = pHandleTable->objectHandle[pMetaRec->rdParm[0]];
               ::u32 nObjType = GetObjectType(hObject);
               if (nObjType == 0)
               {
                  // object type is unknown, determine if it is a font
                  HFONT hStockFont = (HFONT)::GetStockObject(SYSTEM_FONT);
                  HFONT hFontOld = (HFONT)::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hStockFont);
                  HGDIOBJ hObjOld = ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hObject);
                  if (hObjOld == hStockFont)
                  {
                     // got the stock object back, so must be selecting a font
                     __throw(not_implemented());
   //                  (dynamic_cast<::win::graphics * >(pgraphics))->SelectObject(::win::font::from_handle(pgraphics->get_context_application(), (HFONT)hObject));
                     break;  // don't play the default record
                  }
                  else
                  {
                     // didn't get the stock object back, so restore everything
                     ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hFontOld);
                     ::SelectObject((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1(), hObjOld);
                  }
                  // and fall through to PlayMetaFileRecord...
               }
               else if (nObjType == OBJ_FONT)
               {
                  // play back as graphics::SelectObject(::draw2d::font*)
   //               (dynamic_cast<::win::graphics * >(pgraphics))->SelectObject(::win::font::from_handle(pgraphics->get_context_application(), (HFONT)hObject));
                  __throw(not_implemented());
                  break;  // don't play the default record
               }
            }
            // fall through...

         default:
            ::PlayMetaFileRecord(hDC, pHandleTable, pMetaRec, nHandles);
            break;
         }

         return 1;
      }*/

   /*

      bool graphics::PlayMetaFile(HMETAFILE hMF)
      {

         __throw(not_implemented());
         return false;

   /*
         if (::GetDevicecaps(get_handle1(), TECHNOLOGY) == DT_METAFILE)
         {
            // playing metafile in metafile, just use aura windows API
            return ::PlayMetaFile(get_handle1(), hMF) != FALSE;
         }

         // for special playback, lParam == pgraphics
         return ::EnumMetaFile(get_handle1(), hMF, __enum_meta_file_procedure, (LPARAM)this) != FALSE;
   */

//   }

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE32 LPSIZE32) const
   {

      __throw(not_implemented());
      return;

      /*
            ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE32)));

            size sizeWinExt = GetWindowExt();
            size sizeVpExt = GetViewportExt();
            LPSIZE32->cx = MulDiv(LPSIZE32->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
            LPSIZE32->cy = MulDiv(LPSIZE32->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
      */

   }

   void graphics::DPtoLP(LPSIZE32 LPSIZE32) const
   {

      __throw(not_implemented());
      return;

      /*
            ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE32)));

            size sizeWinExt = GetWindowExt();
            size sizeVpExt = GetViewportExt();
            LPSIZE32->cx = MulDiv(LPSIZE32->cx, abs(sizeWinExt.cx), abs(sizeVpExt.cx));
            LPSIZE32->cy = MulDiv(LPSIZE32->cy, abs(sizeWinExt.cy), abs(sizeVpExt.cy));
      */

   }



   i32 graphics::draw_text(const char * lpszString, i32 nCount, RECT32 * prect, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {
      /*if(get_handle1() == nullptr)
         return -1;
      // these flags would modify the string
      ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
      ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
      wstring wstr = ::str::international::utf8_to_unicode(string(lpszString, nCount));
      return ::DrawTextW(get_handle1(), wstr, (i32) wcslen(wstr), rect, nFormat); */

      return draw_text(string(lpszString, nCount), rect, nFormat);

   }


   i32 graphics::draw_text(const string & str, RECT32 * prect, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      //sync_lock ml(&xlib_mutex());

      if(m_pfont.is_null())
         return 0;

      set(m_pfont);

      /*      XGCValues v;

            XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

            if(v.font == -1)
               return 0;*/

      int h = compute_line_height();

      size sz = GetTextExtent(str);

      xlib_keep keep(this);

      double dx;

      double dy;

      if(nFormat & e_align_right)
      {
         dx = rect.right - rect.left - sz.cx;
      }
      else if(nFormat & e_align_horizontal_center)
      {
         dx = ((rect.right - rect.left) - (sz.cx)) / 2.0;
      }
      else
      {
         dx = 0.;
      }

      if(nFormat & e_align_bottom)
      {
         dy = rect.bottom - rect.top - sz.cy;
      }
      else if(nFormat & e_align_vertical_center)
      {
         dy = ((rect.bottom - rect.top) - (sz.cy)) / 2.0;
      }
      else
      {
         dy = 0.;
      }

      /*      array < XChar2b > xa = utf8toXChar2b(str);

            ::XDrawString16(
               m_pdc->m_pdisplay,
               m_pdc->m_drawable,
               m_pdc->m_gc,
               rect.left + dx + m_pdc->m_pointOffset.x,
               rect.top + h + dy + m_pdc->m_pointOffset.y,
               xa.get_data(),
               xa.get_count());*/

      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_pbitmap.m_p);

      if(pbitmap == nullptr)
         return false;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) m_pfont.m_p);

      if(pfont == nullptr)
         return false;

      XftDraw * pdraw = XftDrawCreateAlpha (m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_iDepth);

      XRenderColor c;

      c.red = colorref_get_r_value(m_pbrush->m_color) * 255;
      c.green = colorref_get_g_value(m_pbrush->m_color) * 255;
      c.blue = colorref_get_b_value(m_pbrush->m_color) * 255;
      c.alpha = colorref_get_a_value(m_pbrush->m_color) * 255;

      XftColor ftc;
//      XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

      XftDrawStringUtf8(pdraw, &ftc, pfont->m_pft,
                        rect.left + dx + m_pdc->m_pointOffset.x,
                        rect.top + h + dy + m_pdc->m_pointOffset.y, (const FcChar8 *) (const char *) str);

//      XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &ftc);

      XftDrawDestroy(pdraw);

      return true;

   }

   i32 graphics::draw_text_ex(char * lpszString, i32 nCount, RECT32 * prect, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   {

      __throw(not_implemented());
      return 0 ;

      /*
            if(get_handle1() == nullptr)
               return -1;
            // these flags would modify the string
            ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
            ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
            wstring wstr = ::str::international::utf8_to_unicode(string(lpszString, nCount));
            return ::DrawTextExW(get_handle1(), const_cast<unichar *>((const unichar *)wstr), (i32)wcslen(wstr), rect, nFormat, lpDTParams);
      */
   }

   i32 graphics::draw_text_ex(const string & str, RECT32 * prect, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   {

      __throw(not_implemented());
      return 0;

      /*
            ASSERT(get_handle1() != nullptr);
            // these flags would modify the string
            ASSERT((nFormat & (DT_END_ELLIPSIS | DT_MODIFYSTRING)) != (DT_END_ELLIPSIS | DT_MODIFYSTRING));
            ASSERT((nFormat & (DT_PATH_ELLIPSIS | DT_MODIFYSTRING)) != (DT_PATH_ELLIPSIS | DT_MODIFYSTRING));
            wstring wstr = ::str::international::utf8_to_unicode(str);
            return ::DrawTextExW(get_handle1(), const_cast<unichar *>((const unichar *)wstr), (i32)wcslen(wstr), rect, nFormat, lpDTParams);
      */

   }

   /**
    * Computes the text rectangle.
    * \return C::u322dRectangle.
    */
   size graphics::GetTextExtent(const char * lpszString, strsize nCount, i32 iIndex) const
   {

      sync_lock ml(&xlib_mutex());

      //int direction = 0, fontAscent = 0, fontDescent = 0;

      if(m_pfont.is_null())
         return size(0, 0);

      ((graphics *) this)->set(m_pfont);

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) m_pfont.m_p);

      if(pfont == nullptr)
         return size(0, 0);

      XGlyphInfo extents;

      ·zero(extents);

//      wstring wstr(lpszString, nCount);

      XftTextExtentsUtf8 (m_pdc->m_pdisplay, pfont->m_pft, (const FcChar8 *) (const char *) lpszString, nCount, &extents);

      //XGCValues v;

      //XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

      //if(v.font == -1)
      // return size(0, 0);

      //array < XChar2b > x = utf8toXChar2b(&lpszString[iIndex], nCount - iIndex);

      //::XCharStruct charStruct;

      //::XQueryTextExtents16(m_pdc->m_pdisplay, ::XGContextFromGC(m_pdc->m_gc), x.get_data(), x.get_count(), &direction, &fontAscent, &fontDescent, &charStruct);

      //return ::size(charStruct.rbearing - charStruct.lbearing, fontAscent + fontDescent);

      return size(extents.width, extents.height);

   }


   size graphics::GetTextExtent(const char * lpszString, strsize nCount) const
   {

      return GetTextExtent(lpszString, nCount, 0);

   }


   size graphics::GetTextExtent(const string & str) const
   {

      return GetTextExtent(str);

   }


   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount) const
   {

      __throw(not_implemented());
      return ::size(0, 0);

      /*
            ASSERT(get_handle1() != nullptr);
            ::size size;
            string str(lpszString, nCount);
            wstring wstr = ::str::international::utf8_to_unicode(str);
            VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (i32)wstr.get_length(), &size));
            return size;
      */

   }

   size graphics::GetOutputTextExtent(const string & str) const
   {

      __throw(not_implemented());
      return ::size(0, 0);

      /*
            ASSERT(get_handle1() != nullptr);
            ::size size;
            wstring wstr = ::str::international::utf8_to_unicode(str);
            VERIFY(::GetTextExtentPoint32W(get_handle1(), wstr, (i32)wstr.get_length(), &size));
            return size;
      */
   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, i32 iIndex) const
   {

      sync_lock ml(&xlib_mutex());

      ::size  sz = GetTextExtent(lpszString, nCount, iIndex);

      size.cx = sz.cx;

      size.cy = sz.cy;

      return true;

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount) const
   {

      return GetTextExtent(size, lpszString, nCount, 0);

   }


   bool graphics::GetTextExtent(sized & size, const string & str) const
   {

      return GetTextExtent(size, str, 0);

   }



   /*

      /////////////////////////////////////////////////////////////////////////////
      // Helper DCs


      void CClientDC::assert_valid() const
      {
         graphics::assert_valid();
         ASSERT(m_hWnd == nullptr || ::IsWindow(m_hWnd));
      }

      void CClientDC::dump(dump_context & dumpcontext) const
      {
         graphics::dump(dumpcontext);

         dumpcontext << "get_handle1() = " << m_hWnd;
         dumpcontext << "\n";
      }


      CClientDC::CClientDC(window * pWnd)
      {
         ASSERT(pWnd == nullptr || ::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

         if (!Attach(::GetDC(m_hWnd = WIN_WINDOW(pWnd)->GetSafeHwnd())))
            __throw(resource_exception());
      }

      CClientDC::~CClientDC()
      {
         ASSERT(get_handle1() != nullptr);
         ::ReleaseDC(m_hWnd, Detach());
      }


      void CWindowDC::assert_valid() const
      {
         graphics::assert_valid();
         ASSERT(m_hWnd == nullptr || ::IsWindow(m_hWnd));
      }

      void CWindowDC::dump(dump_context & dumpcontext) const
      {
         graphics::dump(dumpcontext);

         dumpcontext << "get_handle1() = " << m_hWnd;
         dumpcontext << "\n";
      }


      CWindowDC::CWindowDC(window * pWnd)
      {
         ASSERT(pWnd == nullptr || ::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

         if (!Attach(::GetWindowDC(m_hWnd = WIN_WINDOW(pWnd)->GetSafeHwnd())))
            __throw(resource_exception());
      }

      CWindowDC::~CWindowDC()
      {
         ASSERT(get_handle1() != nullptr);
         ::ReleaseDC(m_hWnd, Detach());
      }


      void CPaintDC::assert_valid() const
      {
         graphics::assert_valid();
         ASSERT(::IsWindow(m_hWnd));
      }

      void CPaintDC::dump(dump_context & dumpcontext) const
      {
         graphics::dump(dumpcontext);

         dumpcontext << "get_handle1() = " << m_hWnd;
         dumpcontext << "\nm_ps.hdc = " << m_ps.hdc;
         dumpcontext << "\nm_ps.fErase = " << m_ps.fErase;
         dumpcontext << "\nm_ps.rcPaint = " << (rect)m_ps.rcPaint;

         dumpcontext << "\n";
      }


      CPaintDC::CPaintDC(window * pWnd)
      {
         ASSERT_VALID(pWnd);
         ASSERT(::IsWindow(WIN_WINDOW(pWnd)->get_handle1()));

         if (!Attach(::BeginPaint(m_hWnd = WIN_WINDOW(pWnd)->get_handle1(), &m_ps)))
            __throw(resource_exception());
      }

      CPaintDC::~CPaintDC()
      {
         ASSERT(get_handle1() != nullptr);
         ASSERT(::IsWindow(m_hWnd));

         ::EndPaint(m_hWnd, &m_ps);
         Detach();
      }

   */







   // IMPLEMENT_DYNAMIC(resource_exception, ::exception::exception)
   //resource_exception _simpleResourceException(FALSE, __IDS_RESOURCE_EXCEPTION);

   // IMPLEMENT_DYNAMIC(user_exception, ::exception::exception)
   //user_exception _simpleUserException(FALSE, __IDS_USER_EXCEPTION);

   // IMPLEMENT_DYNCREATE(pgraphics, object)
   // IMPLEMENT_DYNAMIC(CClientDC, graphics)
   // IMPLEMENT_DYNAMIC(CWindowDC, graphics)
   // IMPLEMENT_DYNAMIC(CPaintDC, graphics)
   // IMPLEMENT_DYNCREATE(object, object)

   // IMPLEMENT_DYNAMIC(pen, object)
   // IMPLEMENT_DYNAMIC(::draw2d::brush, object)
   // IMPLEMENT_DYNAMIC(::draw2d::font, object)
   // IMPLEMENT_DYNAMIC(::draw2d::bitmap, object)
   // IMPLEMENT_DYNAMIC(::draw2d::palette, object)
   // IMPLEMENT_DYNAMIC(::draw2d::region, object)


   void graphics::FillSolidRect(const ::rect & rect, color32_t clr)
   {

      FillSolidRect(rect.left, rect.top, width(rect), height(rect), clr);

   }


   void graphics::FillSolidRect(i32 x, i32 y, i32 cx, i32 cy, color32_t clr)
   {

      if(cx <= 0 || cy <= 0)
         return;

      sync_lock ml(&xlib_mutex());

      set_os_color(clr);

      XFillRectangle(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc, x, y, cx, cy);

   }


   bool graphics::text_out(i32 x, i32 y, const char * lpszString, i32 nCount)
   {

      sync_lock ml(&xlib_mutex());

      if(m_pfont.is_null())
         return false;

      set(m_pfont);

      /*      XGCValues v;

            XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

            if(v.font == -1)
               return false;*/

      int h = compute_line_height();

      /*set(m_pbrush);

      array < XChar2b > xa = utf8toXChar2b(lpszString, nCount);

      ::XDrawString16(
         m_pdc->m_pdisplay,
         m_pdc->m_drawable,
         m_pdc->m_gc,
         x + m_pdc->m_pointOffset.x,
         h + y + m_pdc->m_pointOffset.y,
         xa.get_data(),
         xa.get_count());*/


      ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_pbitmap.m_p);

      if(pbitmap == nullptr)
         return false;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) m_pfont.m_p);

      if(pfont == nullptr)
         return false;

      XftDraw * pdraw = XftDrawCreateAlpha (m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_iDepth);

      XRenderColor c;

      c.red = colorref_get_r_value(m_pbrush->m_color) * 255;
      c.green = colorref_get_g_value(m_pbrush->m_color) * 255;
      c.blue = colorref_get_b_value(m_pbrush->m_color) * 255;
      c.alpha = 0xffff;

      XftColor ftc;
//      XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

//      wstring wstr(lpszString, nCount);

      XftDrawStringUtf8(pdraw, &ftc, pfont->m_pft,
                        x + m_pdc->m_pointOffset.x,
                        y + h + m_pdc->m_pointOffset.y, (const FcChar8 *) (const char *) lpszString, nCount);

//      XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &ftc);

      XftDrawDestroy(pdraw);


      return true;

   }


   bool graphics::text_out(double x, double y, const char * lpszString, i32 nCount)
   {

      return text_out(i32(x), i32(y), lpszString, nCount);

   }



   bool graphics::LineTo(double x, double y)
   {

      sync_lock ml(&xlib_mutex());

      set(m_ppen);

      XDrawLine(m_pdc->m_pdisplay, m_pdc->m_drawable, m_pdc->m_gc,
                m_pdc->m_point.x + m_pdc.m_pointOffset.x,
                m_pdc->m_point.y + m_pdc.m_pointOffset.y,
                x + m_pdc->m_pointOffset.x,
                y + m_pdc->m_pointOffset.y);

      m_pdc->m_point.x = x;

      m_pdc->m_point.y = y;

      return true;

   }


   void graphics::set_alpha_mode(::draw2d::enum_alpha_mode ealphamode)
   {

      sync_lock ml(&xlib_mutex());

      try
      {

         if(m_pdc == nullptr)
            return;

         /*
                  ::draw2d::graphics::set_alpha_mode(ealphamode);
                  if(m_ealphamode == ::draw2d::alpha_mode_blend)
                  {
                     xlib_set_operator(m_pdc, CAIRO_OPERATOR_OVER);
                  }
                  else if(m_ealphamode == ::draw2d::alpha_mode_set)
                  {
                     xlib_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);
                  }
         */
      }
      catch(...)
      {
         return;
      }

   }


   void graphics::set_text_rendering_hint(::draw2d::e_text_rendering_hint_hint etextrendering)
   {
      m_etextrenderinghint = etextrendering;

   }


   void * graphics::get_os_data() const
   {

      return (void *) m_pdc;

   }


   /*   HDC graphics::get_handle() const
      {
         return m_hdc;
      }

      HDC graphics::get_handle1() const
      {
         return get_handle();
      }

      HDC graphics::get_handle2() const
      {
         return get_handle();
      }*/

   bool graphics::attach(void * pdata)
   {

      if(m_pdc != nullptr)
      {
         /*	if(m_pdc ==  xlib_keep::g_xlib)
         	{
         //         printf("123");

         	}

                  xlib_destroy(m_pdc);*/

      }

      m_pdc = (device_context *) pdata;

      return true;

   }

   /*
      Gdiplus::Font * graphics::gdiplus_font()
      {
         if(m_pfont.is_null())
         {
            m_pfont.create(get_object());
            m_pfont->operator=(m_fontxyz);
         }
         else if(!m_pfont->m_bUpdated)
         {
            m_pfont->m_bUpdated = true;
            m_pfont->operator=(m_fontxyz);
         }
         return (Gdiplus::Font *) m_pfont->get_os_data();
      }

      Gdiplus::Brush * graphics::gdiplus_brush()
      {
         if(m_pbrush.is_null())
         {
            m_pbrush.create(get_object());
            m_pbrush->operator=(m_brushxyz);
         }
         else if(!m_pbrush->m_bUpdated)
         {
            m_pbrush->m_bUpdated = true;
            m_pbrush->operator=(m_brushxyz);
         }
         return (Gdiplus::Brush *) m_pbrush->get_os_data();
      }

      Gdiplus::Pen * graphics::gdiplus_pen()
      {
         if(m_ppen.is_null())
         {
            m_ppen.create(get_object());
            m_ppen->operator=(m_penxyz);
         }
         else if(!m_ppen->m_bUpdated)
         {
            m_ppen->m_bUpdated = true;
            m_ppen->operator=(m_penxyz);
         }
         return (Gdiplus::Pen *) m_ppen->get_os_data();
      }*/


//   ::aura::enum_fill_mode graphics::gdiplus_get_fill_mode()
   // {
//      return ::draw2d::fill_mode_winding;
   // }

   /*void xlib_image_surface_blur( xlib_surface_t* surface, double radius )
   {
       // Steve Hanov, 2009
       // Released into the public domain.

       // get width, height
       i32 width = xlib_image_surface_get_width( surface );
       i32 height = xlib_image_surface_get_height( surface );
       unsigned char* dst = (unsigned char*)malloc(width*height*4);
       unsigned* precalc =
           (unsigned*)malloc(width*height*sizeof(unsigned));
       unsigned char* src = xlib_image_surface_get_data( surface );
       double mul=1.f/((radius*2)*(radius*2));
       i32 channel;

       // The number of times to perform the averaging. According to wikipedia,
       // three iterations is good enough to pass for a gaussian.
       const i32 MAX_ITERATIONS = 3;
       i32 iteration;

       ::memcpy_dup( dst, src, width*height*4 );

       for ( iteration = 0; iteration < MAX_ITERATIONS; iteration++ ) {
           for( channel = 0; channel < 4; channel++ ) {
               i32 x,y;

               // precomputation step.
               unsigned char* pix = src;
               unsigned* pre = precalc;

               pix += channel;
               for (y=0;y<height;y++) {
                   for (x=0;x<width;x++) {
                       i32 tot=pix[0];
                       if (x>0) tot+=pre[-1];
                       if (y>0) tot+=pre[-width];
                       if (x>0 && y>0) tot-=pre[-width-1];
                       *pre++=tot;
                       pix += 4;
                   }
               }

               // blur step.
               pix = dst + (i32)radius * width * 4 + (i32)radius * 4 + channel;
               for (y=(i32) radius;y<height-radius;y++) {
                   for (x=(i32) radius;x<width-radius;x++) {
                       i32 l = (i32) (x < radius ? 0 : x - radius);
                       i32 t = (i32) (y < radius ? 0 : y - radius);
                       i32 rect = (i32) (x + radius >= width ? width - 1 : x + radius);
                       i32 b = (i32) (y + radius >= height ? height - 1 : y + radius);
                       i32 tot = precalc[rect+b*width] + precalc[l+t*width] -
                           precalc[l+b*width] - precalc[rect+t*width];
                       *pix=(unsigned char)(tot*mul);
                       pix += 4;
                   }
                   pix += (i32)radius * 2 * 4;
               }
           }
           ::memcpy_dup( src, dst, width*height*4 );
       }

       free( dst );
       free( precalc );
   }*/


   bool graphics::blur(bool bExpand, double dRadius, const ::rect & rect)
   {

      /*      xlib_pattern_t * ppattern = xlib_get_source(m_pdc);

            if(ppattern == nullptr)
               return false;

            xlib_surface_t * psurfaceSrc = nullptr;

            xlib_pattern_get_surface(ppattern, &psurfaceSrc);*/

      /*

      xlib_surface_t * psurface = xlib_surface_create_for_rectangle(psurfaceSrc, rect.left, rect.top, width(rect), height(rect));

      xlib_image_surface_blur(psurface, dRadius);

      */

      return true;

   }


   double graphics::get_dpix() const
   {

//      return m_pgraphics->GetDpiX();
      return 72.0;

   }


   bool graphics::set(const ::draw2d::brush * pbrushParam)
   {

      if(pbrushParam == nullptr)
         return false;

      ::draw2d_xlib::brush * pbrush = dynamic_cast < ::draw2d_xlib::brush * > ((::draw2d::brush *) pbrushParam);

      if(pbrush == nullptr)
         return false;

      if(pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
      {

         //xlib_pattern_t * ppattern = xlib_pattern_create_linear(pbrush->m_point1.x, pbrush.m_point1.y, pbrush.m_point2.x, pbrush.m_point2.y);

         //xlib_pattern_add_color_stop_rgba(ppattern, 0., colorref_get_r_value(pbrush->m_color1) / 255.0, colorref_get_g_value(pbrush->m_color1) / 255.0, colorref_get_b_value(pbrush->m_color1) / 255.0, colorref_get_a_value(pbrush->m_color1) / 255.0);

         //xlib_pattern_add_color_stop_rgba(ppattern, 1., colorref_get_r_value(pbrush->m_color2) / 255.0, colorref_get_g_value(pbrush->m_color2) / 255.0, colorref_get_b_value(pbrush->m_color2) / 255.0, colorref_get_a_value(pbrush->m_color2) / 255.0);

         //xlib_set_source(m_pdc, ppattern);

         //xlib_pattern_destroy(ppattern);

         //pbrush->get_os_data();

         pbrush->m_color.create(
         m_pdc->m_pdisplay,
         m_pdc->m_iScreen,
         (colorref_get_r_value(pbrush->m_color1) + colorref_get_r_value(pbrush->m_color2)) / 2,
         (colorref_get_g_value(pbrush->m_color1) + colorref_get_g_value(pbrush->m_color2)) / 2,
         (colorref_get_b_value(pbrush->m_color1) + colorref_get_b_value(pbrush->m_color2)) / 2,
         (colorref_get_a_value(pbrush->m_color1) + colorref_get_a_value(pbrush->m_color2)) / 2);

         XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, pbrush->m_color.m_color.pixel);

      }
      else
      {

         //pbrush->get_os_data();

         pbrush->m_color.create(
         m_pdc->m_pdisplay,
         m_pdc->m_iScreen,
         colorref_get_r_value(pbrush->m_color),
         colorref_get_g_value(pbrush->m_color),
         colorref_get_b_value(pbrush->m_color),
         colorref_get_a_value(pbrush->m_color));

         XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, pbrush->m_color.m_color.pixel);

      }

      return true;

   }


   bool graphics::set(const ::draw2d::pen * ppenParam)
   {

      if(ppenParam == nullptr)
         return false;

      ::draw2d_xlib::pen * ppen = dynamic_cast < ::draw2d_xlib::pen * > ((::draw2d::pen *) ppenParam);

      if(ppen == nullptr)
         return false;

      ppen->m_color.create(
      m_pdc->m_pdisplay,
      m_pdc->m_iScreen,
      colorref_get_r_value(ppen->m_color),
      colorref_get_g_value(ppen->m_color),
      colorref_get_b_value(ppen->m_color),
      colorref_get_a_value(ppen->m_color));

      XSetForeground(m_pdc->m_pdisplay, m_pdc->m_gc, ppen->m_color.m_color.pixel);

      XSetLineAttributes(m_pdc->m_pdisplay, m_pdc->m_gc, ppen->m_dWidth, LineSolid, CapNotLast, JoinMiter);

      return true;

   }


   bool graphics::set(const ::draw2d::font * pfontParam)
   {

      if(pfontParam == nullptr)
         return false;

      string strFont;

      ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) pfontParam);

      if(pfont == nullptr)
         return false;

      int iPoint = pfont->m_dFontSize;

      /*if(pfont->m_pfont != nullptr)
      {

         XFreeFont(pfont->m_pdisplay, pfont->m_pfont);

         pfont->m_pfont = nullptr;

      }*/

      if(pfont->m_pft != nullptr)
      {

         XftFontClose(pfont->m_pdisplay, pfont->m_pft);

         pfont->m_pft = nullptr;

      }


      //strFont.Format("-*-helvetica-*-rect-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);

      char ** szMissing;
      int i;
      char * szmf;

      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                                  XFT_FAMILY, XftTypeString, FONT_SANS,
                                  pfont->m_eunitFontSize == ::draw2d::unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                                  nullptr);

      //pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft != nullptr)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

//      strFont.Format("-*-sans-*-rect-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);
      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                                  XFT_FAMILY, XftTypeString, "sans",
                                  pfont->m_eunitFontSize == ::draw2d::unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                                  nullptr);

//      pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft != nullptr)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

      //    strFont.Format("-*-fixed-*-rect-*-*-%d-*-*-*-*-*-iso10646-1", iPoint);

      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                                  XFT_FAMILY, XftTypeString, "sans",
                                  pfont->m_eunitFontSize == ::draw2d::unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                                  nullptr);
//      pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);


      if (pfont->m_pft != nullptr)
         goto ok;

      fprintf (stderr, "unable to load font %s: using fixed\n", strFont.c_str());

//      strFont = "fixed";
      pfont->m_pft = XftFontOpen (m_pdc->m_pdisplay, m_pdc->m_iScreen,
                                  XFT_FAMILY, XftTypeString, "charter",
                                  pfont->m_eunitFontSize == ::draw2d::unit_point ? XFT_SIZE : XFT_PIXEL_SIZE, XftTypeDouble, pfont->m_dFontSize,
                                  nullptr);

      //    pfont->m_pfont = XLoadQueryFont(m_pdc->m_pdisplay, strFont);

      if (pfont->m_pft == nullptr)
         return false;

ok:

      pfont->m_pdisplay = m_pdc->m_pdisplay;

      //XSetFont (m_pdc->m_pdisplay, m_pdc->m_gc, pfont->m_pfont->fid);

      return true;

   }


   bool graphics::fill_and_draw()
   {

      /*bool bPen = m_ppen->m_etype != ::draw2d::e_pen_null;

      xlib_keep keep(this);

      if(m_pbrush->m_etype != ::draw2d::brush::e_type_null)
      {

         set(m_pbrush);

         set_alpha_mode(m_ealphamode);

         if(bPen)
         {

            xlib_fill_preserve(m_pdc);

         }
         else
         {

            xlib_fill(m_pdc);

         }

      }

      keep.pulse();

      if(bPen)
      {

         set(m_ppen);

         set_alpha_mode(m_ealphamode);

         xlib_stroke(m_pdc);


      }*/

      return false;

   }


   bool graphics::fill(::draw2d::brush * pbrush)
   {

      /*if(pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::e_type_null)
         return true;

      xlib_keep keep(m_pdc);

      set(pbrush);

      xlib_fill(m_pdc);*/

      return false;

   }


   bool graphics::draw(::draw2d::pen * ppen)
   {

      /*if(ppen == nullptr || ppen->m_etype == ::draw2d::e_pen_null)
         return true;

      xlib_keep keep(m_pdc);

      set(ppen);

      xlib_stroke(m_pdc);*/

      return false;

   }


   bool graphics::set(const ::draw2d::path * ppathParam)
   {

      /*xlib_keep keep(m_pdc);

      xlib_new_sub_path(m_pdc);

      ::draw2d_xlib::path * ppath = dynamic_cast < ::draw2d_xlib::path * > ((::draw2d::path *) ppathParam);

      for(i32 i = 0; i < ppath->m_elementa.get_count(); i++)
      {

         set(ppath->m_elementa[i]);

      }

      if(ppath->m_efillmode == ::draw2d::fill_mode_alternate)
      {

         xlib_set_fill_rule(m_pdc, CAIRO_FILL_RULE_EVEN_ODD);

      }
      else
      {

         xlib_set_fill_rule(m_pdc, CAIRO_FILL_RULE_WINDING);

      }*/

      return false;

   }


   bool graphics::set(const ::draw2d_xlib::path::matter & e)
   {

      /*      switch(e.m_etype)
            {
            case ::draw2d::path::matter::type_arc:
               set(e.m_arc);
               break;
            case ::draw2d::path::matter::type_line:
               set(e.m_line);
               break;
            case ::draw2d::path::matter::type_move:
               set(e.m_move);
               break;
            case ::draw2d::path::matter::type_end:
               {

                  if(e.m_end.m_bClose)
                  {
                  xlib_close_path(m_pdc);
                  }
               }
               break;
            default:
               __throw(::exception::exception("unexpected simple os graphics matter type"));
            }*/

      return false;

   }

   bool graphics::set(const ::draw2d_xlib::path::arc & a)
   {

      /*      xlib_keep keep(m_pdc);

            xlib_translate(m_pdc, a.m_xCenter, a.m_yCenter);

            xlib_scale(m_pdc, 1.0, a.m_dRadiusY / a.m_dRadiusX);

            xlib_arc(m_pdc, 0.0, 0.0, a.m_dRadiusX, a.m_dAngle1, a.m_dAngle2);*/

      return true;

   }

   bool graphics::set(const ::draw2d_xlib::path::line & l)
   {

      /*if(!xlib_has_current_point(m_pdc))
      {

         xlib_move_to(m_pdc, l.m_x + 0.5, l.m_y + 0.5);

      }
      else
      {

         xlib_line_to(m_pdc, l.m_x + 0.5, l.m_y + 0.5);

      }*/

      return true;

   }


   bool graphics::set(const ::draw2d_xlib::path::move & p)
   {

      //xlib_move_to(m_pdc, p.m_x + 0.5, p.m_y + 0.5);

      return true;

   }



   bool graphics::fill()
   {

      return fill(m_pbrush);


   }

   bool graphics::draw()
   {

      return draw(m_ppen);

   }

   void * graphics::detach()
   {

      device_context * p = m_pdc;

      m_pdc = nullptr;

      return p;
   }

   bool graphics::set_os_color(color32_t cr)
   {

      //xlib_set_source_rgba(m_pdc, colorref_get_r_value(cr) / 255.0, colorref_get_g_value(cr) / 255.0, colorref_get_b_value(cr) / 255.0, colorref_get_a_value(cr) / 255.0);

      return true;

   }




   /**
    * Computes text line height.
    * \return Text line height.
    */
   unsigned int graphics::compute_line_height()
   {

      size sz = GetTextExtent(L"Ac");
      return sz.cy;
      /*
            ::draw2d_xlib::bitmap * pbitmap = dynamic_cast < ::draw2d_xlib::bitmap * > (m_pbitmap.m_p);

            if(pbitmap == nullptr)
               return false;

            ::draw2d_xlib::font * pfont = dynamic_cast < ::draw2d_xlib::font * > ((::draw2d::font *) m_pfont.m_p);

            if(pfont == nullptr)
               return false;

            XftDraw * pdraw = XftDrawCreate (m_pdc->m_pdisplay, m_pdc->m_drawable, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap);

            XRenderColor c;

            c.red = colorref_get_r_value(m_pbrush->m_color);
            c.green = colorref_get_g_value(m_pbrush->m_color);
            c.blue = colorref_get_b_value(m_pbrush->m_color);
            c.alpha = colorref_get_a_value(m_pbrush->m_color);

            XftColor ftc;
            XftColorAllocValue(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &c, &ftc);

            XftDrawString8(pdraw, &ftc, pfont->m_pft,
            rect.left + dx + m_pdc->m_pointOffset.x,
            rect.top + h + dy + m_pdc->m_pointOffset.y, (FcChar8 *) (const char *) str);

            XftColorFree(m_pdc->m_pdisplay, pbitmap->m_ui.m_window->draw2d(), pbitmap->m_ui.m_window->m_colormap, &ftc);

            XftDrawDestroy(pdraw);*/

      /*      if(m_pfont.is_null())
               return 0;

            set(m_pfont);

            XGCValues v;

            XGetGCValues(m_pdc->m_pdisplay, m_pdc->m_gc, GCFont, &v);

            if(v.font == -1)
               return 0;

            ::draw2d_xlib::font * pfont = m_pfont.cast < ::draw2d_xlib::font >();

            if(pfont == nullptr)
               return 0;

            return pfont->m_pfont->max_bounds.ascent + pfont->m_pfont->max_bounds.descent;*/


   }

} // namespace draw2d_xlib








array < XChar2b > utf8toXChar2b(const char *input, int inlen)
{

   array < XChar2b > output_r;

   int j, k;

   for(j = 0, k = 0; j < inlen; j++)
   {

      unsigned char c = input[j];

      if (c < 128)
      {
         output_r.element_at_grow(k).byte1 = 0;
         output_r.element_at_grow(k).byte2 = c;
         k++;
      }
      else if (c < 0xC0)
      {
         /* we're inside a character we don't know  */
         continue;
      }
      else switch(c & 0xF0)
         {
         case 0xC0:
         case 0xD0: /* two bytes 5+6 = 11 bits */
            if (inlen < j + 1)
            {
               return output_r;
            }
            output_r.element_at_grow(k).byte1 = (c & 0x1C) >> 2;
            j++;
            output_r.element_at_grow(k).byte2 = ((c & 0x3) << 6) + (input[j] & 0x3F);
            k++;
            break;
         case 0xE0: /* three bytes 4+6+6 = 16 bits */
            if (inlen < j + 2)
            {
               return output_r;
            }
            j++;
            output_r.element_at_grow(k).byte1 = ((c & 0xF) << 4) + ((input[j] & 0x3C) >> 2);
            c = input[j];
            j++;
            output_r.element_at_grow(k).byte2 = ((c & 0x3) << 6) + (input[j] & 0x3F);
            k++;
            break;
         case 0xFF:
            /* the character uses more than 16 bits */
            continue;
         }

   }

   return output_r;

}

