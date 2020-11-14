#include "framework.h"
#include <math.h>
#include <memory.h>
#include <CoreFoundation/CFDictionary.h>


unsigned long apple_get_fonts(char *** p);
double nsfont_get_ctweight(int iWeight);


namespace draw2d_quartz2d
{


   void __copy(CGAffineTransform & affine, const ::draw2d::matrix & m)
   {

      affine.a = m.a1;
      affine.b = m.a2;
      affine.c = m.b1;
      affine.d = m.b2;
      affine.tx = m.c1;
      affine.ty = m.c2;

   }


   void __copy(::draw2d::matrix & m, const CGAffineTransform & affine)
   {

      m.a1 = affine.a;
      m.a2 = affine.b;
      m.b1 = affine.c;
      m.b2 = affine.d;
      m.c1 = affine.tx;
      m.c2 = affine.ty;

   }


   graphics::graphics()
   {
      
      m_iType = -1;
      defer_create_mutex();

      m_iSaveDC         = 0;
      m_bPrinting       = FALSE;
      //m_pimageimplAlphaBlend  = nullptr;
      m_etextrenderinghint  = ::draw2d::text_rendering_hint_anti_alias_grid_fit;
      m_bOwnDC          = true;
      m_pdc             = nullptr;
      m_layer           = nullptr;

   }


   void graphics::assert_valid() const
   {

      ::draw2d::graphics::assert_valid();

   }


   void graphics::dump(dump_context & dumpcontext) const
   {

      ::draw2d::graphics::dump(dumpcontext);

      dumpcontext << "\n";

   }


   graphics::~graphics()
   {

      DeleteDC();

   }


   bool graphics::IsPrinting()
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


   CGContextRef MyCreateBitmapContext(int cx, int cy)
   {

      CGContextRef    context = nullptr;

      int             size;

      int             scan;

      scan                 = (cx * 4);

      size                 = (scan * cy);

      CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();

      context              = CGBitmapContextCreate(nullptr, cx, cy, 8, scan, colorspace, kCGImageAlphaPremultipliedLast);

      CGColorSpaceRelease(colorspace);

      if(context== nullptr)
      {

         return nullptr;

      }

      return context;

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      DeleteDC();

      m_pdc             = nullptr;

      CGContextRef cg   = nullptr;

      if(pgraphics == nullptr || pgraphics->get_os_data() == nullptr)
      {

         cg = MyCreateBitmapContext(1, 1);

      }
      else
      {

         cg = (CGContextRef) pgraphics->get_os_data();

      }

      CGSize size;

      size.width = 1;

      size.height = 1;

      m_layer = CGLayerCreateWithContext(cg, size, nullptr);

      if(m_layer != nullptr)
      {

         m_pdc = CGLayerGetContext(m_layer);

      }

      if(m_pdc == nullptr)
      {

         CGLayerRelease(m_layer);

         m_layer = nullptr;

      }

      if(pgraphics == nullptr || pgraphics->get_os_data() == nullptr)
      {

         CGContextRelease(cg);

      }

      if(m_layer == nullptr)
      {

         CGContextRelease(cg);

         return false;

      }

//      if(m_pdc != nullptr)
//      {
//
//         m_affine = CGContextGetCTM(m_pdc);
//
//      }

      m_bOwnDC = true;

      return true;

   }


   i32 graphics::GetDeviceCaps(i32 nIndex)
   {
      /*      ASSERT(get_handle2() != nullptr);
       return ::GetDeviceCaps(get_handle2(), nIndex);*/
      __throw(not_implemented());
      return 0;

   }


   point graphics::GetBrushOrg()
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


   ::estatus graphics::set(::draw2d::bitmap * pbitmap)
   {


      if(m_iType != -1)
      {

         //TRACE("occluding device context?!!?");

      }

      __pointer(::draw2d_quartz2d::bitmap) pbitmapQuartz = pbitmap;

      if(pbitmapQuartz.is_set())
      {

         DeleteDC();

         attach(pbitmapQuartz->m_pdc);

         m_bOwnDC = false;

         m_pbitmap = pbitmap;

      }

      return ::success;

   }

//   color32_t graphics::GetNearestColor(color32_t crColor)
//   {
//      //__throw(not_implemented());
//      return crColor;
//      //      return ::GetNearestColor(get_handle2(), crColor);
//   }
//
//   ::u32 graphics::RealizePalette()
//   {
//      //      return ::RealizePalette(get_handle1());
//      return 0;
//   }
//
//   void graphics::UpdateColors()
//   {
//      //::UpdateColors(get_handle1());
//
//   }
//
////   color32_t graphics::GetBkColor()
////   {
////      //return ::GetBkColor(get_handle2());
////      return 0;
////   }
////
////   i32 graphics::GetBkMode()
////   {
////      //return ::GetBkMode(get_handle2());
////      return 0;
////   }

   i32 graphics::GetPolyFillMode()
   {
      //return ::GetPolyFillMode(get_handle2());
//      return cairo_get_fill_rule(m_pdc) == CAIRO_FILL_RULE_WINDING ? ::ca2::fill_mode_winding : ::ca2::fill_mode_alternate;
      return 0;
   }

   i32 graphics::GetROP2()
   {
      //return ::GetROP2(get_handle2());
      return 0;
   }

   i32 graphics::GetStretchBltMode()
   {
      //return ::GetStretchBltMode(get_handle2());
      return 0;
   }

   i32 graphics::GetMapMode()
   {
      //return ::GetMapMode(get_handle2());
      return 0;
   }

   i32 graphics::GetGraphicsMode()
   {
      //return ::GetGraphicsMode(get_handle2());
      return 0;
   }

//   bool graphics::GetWorldTransform(XFORM* pXform)
//   {
//
//      //return ::GetWorldTransform(get_handle2(),pXform) != FALSE;
//      return 0;
//
//   }

   size graphics::GetViewportExt()
   {
      /*::size size;
       ::GetViewportExtEx(get_handle2(), &size);
       return size;*/

      return ::size(0, 0);
   }

   point graphics::GetWindowOrg()
   {
      /*::point point;
       ::GetWindowOrgEx(get_handle2(), &point);
       return point;*/
      return ::point();
   }

   size graphics::GetWindowExt()
   {
      /*::size size;
       ::GetWindowExtEx(get_handle2(), &size);
       return size;*/
      return ::size(0, 0);
   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(const ::point & point)
   {

      return SetViewportOrg(point.x, point.y);

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

//   void graphics::DPtoLP(POINT32 * lpPoints, i32 nCount)
//   {
//      //::DPtoLP(get_handle2(), lpPoints, nCount);
//   }

   void graphics::DPtoLP(RECT32 * prect)
   {
      //::DPtoLP(get_handle2(), (POINT32 *)rect, 2);
   }

//   void graphics::LPtoDP(POINT32 * lpPoints, i32 nCount)
//   {
//      //::LPtoDP(get_handle2(), lpPoints, nCount);
//   }

   void graphics::LPtoDP(RECT32 * prect)
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

//   bool graphics::PtVisible(i32 x, i32 y)
//   {
//
//      //    ASSERT(get_handle1() != nullptr);
//
//      //      return ::PtVisible(get_handle1(), x, y) != FALSE;
//      __throw(not_implemented());
//      return false;
//
//   }

//   bool graphics::PtVisible(const ::point & point)
//   {
//
//      //      ASSERT(get_handle1() != nullptr);
//
//      //      return PtVisible(point.x, point.y);
//
//      __throw(not_implemented());
//      return false;
//
//   }

//   bool graphics::RectVisible(const ::rect & rect)
//   {
//
//      //      ASSERT(get_handle1() != nullptr);
//
//      //      return ::RectVisible(get_handle1(), rect) != FALSE;
//
//      __throw(not_implemented());
//      return false;
//
//   }


   pointd graphics::current_position()
   {

      return m_point;

   }


//   bool graphics::Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
//   {
//
//      return ::draw2d::graphics::Arc((double)x1, (double)y1, (double)x2, (double)y2, (double)x3, (double)y3, (double)x4, (double)y4);
//
//   }


//   bool graphics::Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
//   {
//
//      return ::draw2d::graphics::Arc((i32) x1, (i32) y1, (i32) x2, (i32) y2, (i32) x3, (i32) y3, (i32) x4, (i32) y4);
//
//   }


//   bool graphics::Arc(i32 x1, i32 y1, i32 w, i32 h, double start, double extends)
//   {
//
//      return Arc((double) x1, (double)y1, (double) w, (double) h, start, extends);
//
//   }


   bool graphics::Arc(double x, double y, double w, double h, angle start, angle extends)
   {

      double end = start + extends;

      CGContextSaveGState(m_pdc);

      CGContextTranslateCTM(m_pdc, x + w/2.0, y + h/2.0);

      CGContextScaleCTM(m_pdc, w/2.0, h/2.0);

      CGContextAddArc(m_pdc, 0.f, 0.f, 1.0f, start * 3.1415 / 180.0, end * 3.1415 / 180.0, extends < 0.0);

      CGContextRestoreGState(m_pdc);

      return _draw();

   }


   bool graphics::Polyline(const POINT32* lpPoints, count nCount)
   {

      if(nCount < 2)
      {
         
         return false;
         
      }

      CGContextBeginPath(m_pdc);

      set_polygon(lpPoints, nCount);

      if(!_draw())
      {

         return false;
         
      }

      return true;

   }


   bool graphics::fill_rect(const ::rectd & rectParam, ::draw2d::brush * pbrush)
   {

      CGRect rect;
      
      __copy(rect, rectParam);
      
      CGContextBeginPath(m_pdc);
      
      CGContextAddRect(m_pdc, rect);
      
      return _fill(pbrush);

   }


   bool graphics::fill_rect(const ::rectd & rect)
   {

      return fill_rect(rect, m_pbrush);
      
   }
   
   
   void graphics::frame_rect(const ::rect & rectParam, ::draw2d::brush* pBrush)
   {

      CGRect rect;

      __copy(rect, rectParam);

      CGContextBeginPath(m_pdc);

      CGContextAddRect(m_pdc, rect);

      _draw(pBrush);

   }


   bool graphics::draw_rect(const ::rectd & rectParam, ::draw2d::pen* ppen)
   {

      CGRect rect;
      
      __copy(rect, rectParam);
      
      CGContextBeginPath(m_pdc);
      
      CGContextAddRect(m_pdc, rect);
      
      return _draw(ppen);

   }


   bool graphics::draw_rect(const ::rectd & rect)
   {

      return draw_rect(rect, m_ppen);

   }
   
  
   void graphics::invert_rect(const ::rect & rect)
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

      return false;

      /*      try
       {

       if(picon == nullptr)
       return FALSE;

       if(m_pgraphics == nullptr)
       return FALSE;

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

       HBITMAP hbitmap = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **) &pcolorref, nullptr, nullptr);

       HDC hdc = ::CreateCompatibleDC(nullptr);

       HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

       if(::DrawIconEx(hdc, 0, 0, (HICON) picon->m_picon, cx, cy, istepIfAniCur, nullptr, DI_IMAGE | DI_MASK))
       {

       ::SelectObject(hdc, hbitmapOld);

       try
       {

       Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (byte *) pcolorref);

       bOk = m_pgraphics->DrawImage(&b, x, y, 0, 0, cx, cy, Gdiplus::UnitPixel) == Gdiplus::Ok;

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
       return FALSE;
       }
       */
      //return ::DrawIconEx(get_handle1(), x, y, picon->m_hicon, cx, cy, istepIfAniCur, hbrFlickerFreeDraw, diFlags);

   }

//   bool graphics::DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      __throw(not_implemented());
//      return false;
//      //      ASSERT(get_handle1() != nullptr);
//      //      return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hBitmap, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;
//
//   }

//   bool graphics::DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      __throw(not_implemented());
//      return false;
//      //      ASSERT(get_handle1() != nullptr);
//      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)pBitmap->get_os_data(), 0, point.x, point.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;
//
//   }

   /*
   bool graphics::DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags, HBRUSH hBrush)
   {

      __throw(not_implemented());
      return false;
      //      ASSERT(get_handle1() != nullptr);
      //      return ::DrawState(get_handle1(), hBrush, nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }


   bool graphics::DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags, ::draw2d::brush* pBrush)
   {

      __throw(not_implemented());
      return false;
      //      ASSERT(get_handle1() != nullptr);
      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)hIcon, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }*/

//   bool graphics::DrawState(const ::point & point, const ::size & size, const char * lpszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, HBRUSH hBrush)
//   {
//
//      __throw(not_implemented());
//      return false;
//      //      ASSERT(get_handle1() != nullptr);
//      //      return ::DrawState(get_handle1(), hBrush,  nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;
//
//   }
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, const char * lpszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, ::draw2d::brush* pBrush)
//   {
//
//      __throw(not_implemented());
//      return false;
//      //      ASSERT(get_handle1() != nullptr);
//      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), nullptr, (LPARAM)lpszText, (WPARAM)nTextLen, point.x, point.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;
//
//   }

   /*

    bool graphics::DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, ::u32 nFlags, HBRUSH hBrush)
    {

    __throw(not_implemented());
    return false;

    //      ASSERT(get_handle1() != nullptr);
    //      return ::DrawState(get_handle1(), hBrush, lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;

    }

    bool graphics::DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC lpDrawProc, LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush)
    {

    __throw(not_implemented());
    return false;

    //      ASSERT(get_handle1() != nullptr);
    //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), lpDrawProc, lData, 0, point.x, point.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;

    }

    */

   bool graphics::DrawEdge(RECT32 * prect, ::u32 nEdge, ::u32 nFlags)
   {

      __throw(not_implemented());
      return false;

      //      ASSERT(get_handle1() != nullptr);
      //      return ::DrawEdge(get_handle1(), rect, nEdge, nFlags) != FALSE;

   }

   bool graphics::DrawFrameControl(RECT32 * prect, ::u32 nType, ::u32 nState)
   {

      __throw(not_implemented());
      return false;
      //      ASSERT(get_handle1() != nullptr);
      //      return ::DrawFrameControl(get_handle1(), rect, nType, nState) != FALSE;

   }

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

   }


   void graphics::DrawFocusRect(const ::rect & rect)
   {

      __throw(not_implemented());

      //ASSERT(get_handle1() != nullptr); ::DrawFocusRect(get_handle1(), rect);

   }
   
//
//   bool graphics::DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2)
//   {
//
////      double centerx    = (x2 + x1) / 2.0;
////      double centery    = (y2 + y1) / 2.0;
////
////      double radiusx    = abs(x2 - x1) / 2.0;
////      double radiusy    = abs(y2 - y1) / 2.0;
////
////      if(radiusx == 0.0 || radiusy == 0.0)
////         return false;
////
////      cairo_translate(m_pdc, centerx, centery);
////
////      cairo_scale(m_pdc, radiusx, radiusy);
////
////      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
////
////      draw();
////
////      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
////
////      cairo_translate(m_pdc, -centerx,  -centery);
//
//      CGRect rect;
//
//      rect.origin.x     = x1;
//      rect.origin.y     = y1;
//      rect.size.width   = x2 - x1;
//      rect.size.height  = y2 - y1;
//
//      set(m_ppen);
//
//      CGContextStrokeEllipseInRect(m_pdc, rect);
//
//      return true;
//
//   }
//
//
//   bool graphics::DrawEllipse(const ::rect & rect)
//   {
//
//
//      return DrawEllipse(rect.left, rect.top, rect.right, rect.bottom);
//
//
//      /*return ::Ellipse(get_handle1(), rect.left, rect.top,
//       rect.right, rect.bottom); */
//
//   }
//
//
//   bool graphics::FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2)
//   {
//
////      double centerx    = (x2 + x1) / 2.0;
////
////      double centery    = (y2 + y1) / 2.0;
////
////      double radiusx    = abs(x2 - x1) / 2.0;
////
////      double radiusy    = abs(y2 - y1) / 2.0;
////
////      if(radiusx == 0.0 || radiusy == 0.0)
////         return false;
////
////      cairo_translate(m_pdc, centerx, centery);
////
////      cairo_scale(m_pdc, radiusx, radiusy);
////
////      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
////
////      fill();
////
////      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
////
////      cairo_translate(m_pdc, -centerx,  -centery);
//
//      CGRect rect;
//
//      rect.origin.x     = x1;
//      rect.origin.y     = y1;
//      rect.size.width   = x2 - x1;
//      rect.size.height  = y2 - y1;
//
//      //set(m_pbrush);
//
//      CGContextAddEllipseInRect(m_pdc, rect);
//
//      return fill();
//
//   }
//
//
//   bool graphics::FillEllipse(const ::rect & rect)
//   {
//
//      /*return ::Ellipse(get_handle1(), rect.left, rect.top,
//       rect.right, rect.bottom); */
//
//      return FillEllipse(rect.left, rect.top, rect.right, rect.bottom);
//
//   }

//   bool graphics::draw_ellipse(double x1, double y1, double x2, double y2)
//   {
//
//      CGRect rect;
//
//      rect.origin.x     = x1;
//      rect.origin.y     = y1;
//      rect.size.width   = x2 - x1;
//      rect.size.height  = y2 - y1;
//
//      set(m_ppen);
//
//      CGContextStrokeEllipseInRect(m_pdc, rect);
//
//      return true;
//
//   }


   bool graphics::draw_ellipse(const ::rectd & rectParam)
   {
      
      CGRect rect;

      __copy(rect, rectParam);

      _set(m_ppen);

      CGContextStrokeEllipseInRect(m_pdc, rect);
      
      return true;

   }


//   bool graphics::FillEllipse(double x1, double y1, double x2, double y2)
//   {
//
//      CGRect rect;
//
//      rect.origin.x     = x1;
//      rect.origin.y     = y1;
//      rect.size.width   = x2 - x1;
//      rect.size.height  = y2 - y1;
//
//      CGContextAddEllipseInRect(m_pdc, rect);
//
//      return fill();
//
//   }


   bool graphics::fill_ellipse(const ::rectd & rectParam)
   {

       
     CGRect rect;

     __copy(rect, rectParam);

     CGContextAddEllipseInRect(m_pdc, rect);

     return _fill();

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
       return ::Pie(get_handle1(), rect.left, rect.top, rect.right, rect.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y) != FALSE;*/

   }

   bool graphics::set_polygon(const POINTD * p, count c)
   {

      CGContextMoveToPoint(m_pdc, p[0].x, p[0].y);

      for(i32 i = 1; i < c; i++)
      {

         CGContextAddLineToPoint(m_pdc, p[i].x, p[i].y);

      }

      return true;

   }


   bool graphics::set_polygon(const POINT32 * p, count c)
   {

      CGContextMoveToPoint(m_pdc, p[0].x, p[0].y);

      for(i32 i = 1; i < c; i++)
      {

         CGContextAddLineToPoint(m_pdc, p[i].x, p[i].y);

      }

      return true;

   }


   bool graphics::fill_polygon(const POINTD * pa, count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      CGContextBeginPath(m_pdc);

      set_polygon(pa, nCount);

      CGContextClosePath(m_pdc);

      _fill();

      return true;

   }

   bool graphics::fill_polygon(const POINT32* pa, count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      CGContextBeginPath(m_pdc);

      set_polygon(pa, nCount);

      CGContextClosePath(m_pdc);

      _fill();

      return true;

   }


   bool graphics::draw_polygon(const POINTD * pa, count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      CGContextBeginPath(m_pdc);

      set_polygon(pa, nCount);

      CGContextClosePath(m_pdc);

      _draw();

      return true;

   }


   bool graphics::draw_polygon(const POINT32* pa, count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      CGContextBeginPath(m_pdc);

      set_polygon(pa, nCount);

      CGContextClosePath(m_pdc);

      _draw();

      return true;

   }


   bool graphics::polygon(const POINTD * pa, count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      CGContextBeginPath(m_pdc);

      set_polygon(pa, nCount);

      CGContextClosePath(m_pdc);

      return _fill_and_draw();

   }



   bool graphics::rectangle(const ::rectd & rectParam)
   {

      CGRect rect;
      
      __copy(rect, rectParam);
      
      CGContextBeginPath(m_pdc);
      
      CGContextAddRect(m_pdc, rect);
      
      return _fill_and_draw();

   }


   bool graphics::round_rect(const ::rectd & rect, const ::pointd & point)
   {

      return ::draw2d::graphics::round_rect(rect, point);
      
   }
   

   bool graphics::PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::u32 dwRop)
   {

      //      ASSERT(get_handle1() != nullptr);
      //      return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != FALSE;

      __throw(not_implemented());
      return false;


   }


   bool graphics::BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, ::u32 dwRop)
   {

      sync_lock sl(mutex());

      try
      {

         if(pgraphicsSrc == nullptr)
         {

            return false;

         }

         sync_lock slSrc(pgraphicsSrc->mutex());

         if(pgraphicsSrc->get_os_data() == nullptr)
         {

            return false;

         }

         __pointer(::draw2d_quartz2d::image) imageSrc = pgraphicsSrc->m_pimage;

         __pointer(::draw2d::graphics) imageGraphics;

         if(imageSrc.is_set())
         {

            imageGraphics = imageSrc->g();

         }
         else
         {

            TRACE("imageSrc nullptr");


         }

         CGContextRef pdcSrc = (CGContextRef) pgraphicsSrc->get_os_data();

         CGImageRef pimage = CGBitmapContextCreateImage(pdcSrc);

         if(pimage == nullptr)
         {

            return false;

         }

         size_t SrcW = CGImageGetWidth(pimage);

         size_t SrcH = CGImageGetHeight(pimage);

         CGRect rect;

         rect.origin.x = x;
         rect.origin.y = y;
         rect.size.width = nWidth;
         rect.size.height = nHeight;

         CGRect rectSub;

         if(::comparison::gt(xSrc, SrcW))
         {

            CGImageRelease(pimage);

            return true;

         }

         if(::comparison::gt(ySrc, SrcH))
         {

            CGImageRelease(pimage);

            return true;

         }

         rectSub.origin.x = 0;
         rectSub.origin.y = 0;
         rectSub.size.width = SrcW;
         rectSub.size.height = SrcH;

         if(m_pregion.is_null())
         {

            if(xSrc == 0 && ySrc == 0 && nWidth == SrcW && nHeight == SrcH)
            {

               CGContextDrawImage(m_pdc, rect, pimage);

            }
            else
            {

               CGContextSaveGState(m_pdc);

               CGContextClipToRect(m_pdc, rect);

               rect.origin.x -= xSrc;
               rect.origin.y -= ySrc;
               rect.size.width = SrcW;
               rect.size.height =  SrcH;

               CGContextDrawImage(m_pdc, rect, pimage);

               CGContextRestoreGState(m_pdc);

            }

         }
         else
         {

            CGContextSaveGState(m_pdc);

            _clip(m_pregion);

            if(xSrc == 0 && ySrc == 0 && nWidth == SrcW && nHeight == SrcH )
            {

            }
            else
            {

               CGContextClipToRect(m_pdc, rect);

               rect.origin.x -= xSrc;
               rect.origin.y -= ySrc;
               rect.size.width = SrcW;
               rect.size.height =  SrcH;

            }

            if(rect.origin.x < 0)
            {
               rect.size.width += rect.origin.x;
               rect.origin.x = 0;
            }
            if(rect.origin.y < 0)
            {
               rect.size.height += rect.origin.y;
               rect.origin.y = 0;
            }

            CGContextDrawImage(m_pdc, rect, pimage);

            CGContextRestoreGState(m_pdc);

         }


         CGImageRelease(pimage);

         //CGContextRestoreGState(pdcSrc);

         return true;

      }
      catch(...)
      {

         return false;

      }

   }


   bool graphics::StretchBltRaw(double xDst, double yDst, double nDstWidth, double nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, ::u32 dwRop)
   {

      if(nDstWidth <= 0 || nDstHeight <= 0 || nSrcWidth <= 0 || nSrcHeight <= 0)
      {

         return false;

      }


      try
      {

         if(pgraphicsSrc == nullptr)
         {

            return false;

         }

         if(pgraphicsSrc->get_os_data() == nullptr)
         {

            return false;

         }

         CGImageRef pimage = CGBitmapContextCreateImage((CGContextRef) pgraphicsSrc->get_os_data());

         if(pimage == nullptr)
         {

            return false;

         }

         size_t SrcW = CGImageGetWidth(pimage);

         size_t SrcH = CGImageGetHeight(pimage);

         CGRect rect;

         rect.origin.x = xDst;
         rect.origin.y = yDst;
         rect.size.width = nDstWidth;
         rect.size.height = nDstHeight;

         if(xSrc == 0 && ySrc == 0 && SrcW == nSrcWidth && SrcH == nSrcHeight)
         {

            CGContextDrawImage(m_pdc, rect, pimage);

         }
         else
         {

            CGRect rectSub;

            rectSub.origin.x = xSrc;
            rectSub.origin.y = ySrc;
            rectSub.size.width = nSrcWidth;
            rectSub.size.height = nSrcHeight;

            CGImageRef imageSub = CGImageCreateWithImageInRect(pimage, rectSub);

            if(imageSub != nullptr)
            {

               CGContextDrawImage(m_pdc, rect, imageSub);

               CGImageRelease(imageSub);

            }

         }

         CGImageRelease(pimage);

         return true;

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   ::color graphics::GetPixel(i32 x, i32 y)
   {

      __throw(not_implemented());
      return false;

      //      ASSERT(get_handle1() != nullptr);
      //      return ::GetPixel(get_handle1(), x, y);

   }


   ::color graphics::GetPixel(const ::point & point)
   {

      __throw(not_implemented());

      return false;

   }


   ::color graphics::SetPixel(i32 x, i32 y, const ::color & color)
   {

      __throw(not_implemented());

      return ::color();

   }


   ::color graphics::SetPixel(const ::point & point, const ::color & color)
   {

      __throw(not_implemented());

      return ::color();

   }

//
//   bool graphics::FloodFill(i32 x, i32 y, color32_t crColor)
//   {
//
//      __throw(not_implemented());
//
//      return false;
//
//   }
//
//
//   bool graphics::ExtFloodFill(i32 x, i32 y, color32_t crColor, ::u32 nFillType)
//   {
//
//      __throw(not_implemented());
//
//      return false;
//
//   }


   bool graphics::BitBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop)
   {

      if (m_pimageAlphaBlend->is_set())
      {

         ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         auto rectBlt = rect_dim(x, y, nWidth, nHeight);

         if (rectIntersect.intersect(rectIntersect, rectBlt))
         {

            auto pimage1 = create_image(rectBlt.size());

            pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

            if (!pimage1->from(::point(), pgraphicsSrc, ::point(xSrc, ySrc), rectBlt.size()))
            {

               return false;

            }

            pimage1->blend(::point(), m_pimageAlphaBlend, point((int)max(0, x - m_pointAlphaBlend.x), (int)max(0, y - m_pointAlphaBlend.y)), rectBlt.size());

            set_alpha_mode(::draw2d::alpha_mode_blend);

            BitBltRaw(x, y, nWidth, nHeight, pimage1->get_graphics(), 0, 0, dwRop);

            return true;

         }

      }

      return false;

   }


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   bool graphics::text_out(i32 x, i32 y, const string & str)
   {

      if (m_pimageAlphaBlend->is_set())
      {

         ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         auto rectText = ::rect(::point(x, y), ::size(GetTextExtent(str)));

         if (rectIntersect.intersect(rectIntersect, rectText))
         {

            rectText.bottom = rectText.top + rectText.height() * 2;

            auto pimage1 = create_image(rectText.size());
            
            pimage1->fill(0, 0, 0, 0);
            pimage1->get_graphics()->set(get_current_font());
            pimage1->get_graphics()->set(get_current_brush());
            pimage1->get_graphics()->text_out(0, 0, str);

            pimage1->blend(::point(), m_pimageAlphaBlend, point((int)max(0, x - m_pointAlphaBlend.x), (int)max(0, y - m_pointAlphaBlend.y)), rectText.size());

            set_alpha_mode(::draw2d::alpha_mode_blend);

            BitBltRaw((int)x, (int)y, rectText.width(), rectText.height(), pimage1->get_graphics(), 0, 0);

         }
         
         return true;

      }
      
      if(TextOutRaw(x, y, str))
      {
       
         return true;
         
      }
      
      return false;

   }


   bool graphics::text_out(double x, double y, const string & str)
   {

      if(m_pimageAlphaBlend->is_set())
      {

         ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
         
         auto rectText = ::rect(point((i32) x, (i32) y), ::size(GetTextExtent(str)));
         
         if(rectIntersect.intersect(rectIntersect, rectText))
         {

            return true;

//               ::image_pointer pimage0;
//               image0 = create_image(rectText.size());
//               image0.get_graphics()->set_text_color(RGB(255, 255, 255));
//               image0.get_graphics()->SelectObject(get_current_font());
//
//               image0.get_graphics()->text_out(0, 0, str);
//
//               image0.ToAlpha(0);
//               ::image_pointer pimage1;
//               pimage1 = create_image(rectText.size());
//               pimage1->get_graphics()->set_text_color(m_pbrush->m_color);
//               pimage1->get_graphics()->SelectObject(get_current_font());
//
//               pimage1->get_graphics()->text_out(0, 0, str);
//
//               pimage1->channel_from(::color::channel_alpha, image0);
//               ::image_pointer pimage2;
//               pimage2 = create_image(rectText.size());
//               pimage2->Fill(255, 0, 0, 0);
//               pimage2->from(point((i64) max(0, m_pointAlphaBlend.x - x), (i64) max(0, m_pointAlphaBlend.y - y)),
//                          m_pimageAlphaBlend->get_graphics(), point((i64) max(0, x - m_pointAlphaBlend.x), (i64) max(0, y - m_pointAlphaBlend.y)), rectText.size());
//               pimage1->channel_multiply(::color::channel_alpha, pimage2);
//               /* p::image_pointer pimage3(get_object());
//                pimage1->mult_alpha(image3);*/
//
//               keep < image > keep(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);
//
//               return BitBlt(point((i64) x, (i64) y), rectText.size(), pimage1->get_graphics(), ::point());

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

      //ASSERT(get_handle1() != nullptr);
      //wstring wstr = ::str::international::utf8_to_unicode(str);
      return text_out(x, y, str, (i32) str.get_length());

   } // call virtual


   bool graphics::ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rectd & rect, const char * lpszString, ::u32 nCount, int * lpDxWidths)
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


   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(not_implemented());
      return ::size(0, 0);

      //      ASSERT(get_handle2() != nullptr);
      //      return ::GetTabbedTextExtent(get_handle2(), lpszString, (i32) nCount, nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(not_implemented());
      return ::size(0, 0);

      //      ASSERT(get_handle2() != nullptr);
      //      return ::GetTabbedTextExtent(get_handle2(), str, (i32) str.get_length(), nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, i32 nTabPositions, LPINT lpnTabStopPositions)
   {

      __throw(not_implemented());
      return ::size(0, 0);

      //      ASSERT(get_handle1() != nullptr);
      //      return ::GetTabbedTextExtent(get_handle1(), lpszString, (i32) nCount, nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetOutputTabbedTextExtent(const string & str, i32 nTabPositions, LPINT lpnTabStopPositions)
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

   ::u32 graphics::GetTextAlign()
   {

      __throw(not_implemented());
      return 0;

      //      ASSERT(get_handle2() != nullptr);
      //      return ::GetTextAlign(get_handle2());

   }

   i32 graphics::GetTextFace(i32 nCount, char * lpszFacename)
   {

      __throw(not_implemented());
      return 0;

      //      ASSERT(get_handle2() != nullptr);
      //      return ::GetTextFace(get_handle2(), nCount, lpszFacename);

   }

   i32 graphics::GetTextFace(string & rString)
   {

      __throw(not_implemented());
      return 0;

   }

   
   bool graphics::get_text_metrics(::draw2d::text_metric * pmetric)
   {

      if(!m_pfont)
      {
       
         return false;
         
      }
      
      CTFontRef pfont = (CTFontRef) m_pfont->get_os_data(this);

      if(pfont == nullptr)
      {
       
         return false;
         
      }

      string str(L"123AWZwmc123AWZwmcpQg");

      array < CFTypeRef > pkeys;
      
      array < CFTypeRef > pvals;
      
      array < CFTypeRef > cfrel;
      
      array < CGColorRef > crrel;
      
      pkeys.add(kCTFontAttributeName);
      
      pvals.add(pfont);
      
      if(m_pfont->m_bUnderline)
      {
         
         int iUnderlineStyle = kCTUnderlineStyleSingle;
         
         CFNumberRef num = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &iUnderlineStyle);
         
         cfrel.add(num);
         
         pkeys.add(kCTUnderlineStyleAttributeName);
         
         pvals.add(num);
         
      }
      
      CFDictionaryRef attributes = CFDictionaryCreate(
                                                      kCFAllocatorDefault,
                                                      pkeys.get_data(),
                                                      pvals.get_data(),
                                                      pkeys.get_size(),
                                                      &kCFTypeDictionaryKeyCallBacks,
                                                      &kCFTypeDictionaryValueCallBacks);
         
      CFStringRef string = CFStringCreateWithCString(nullptr, str, kCFStringEncodingUTF8);
      

      CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
      
      CTLineRef line = CTLineCreateWithAttributedString(attrString);
      //... contribution https://delphiscience.wordpress.com/2013/01/06/getting-text-metrics-in-firemonkey/
      CFRelease(string);
      
      //CFRelease(attributes);
      
      CGFloat ascent;
      CGFloat descent;
      CGFloat leading;
      
//      double width = CTLineGetTypographicBounds(line, &ascent,  &descent, &leading);
            CTLineGetTypographicBounds(line, &ascent,  &descent, &leading);
      CFRelease(line);
      
      pmetric->tmAscent = ascent;
      pmetric->tmDescent = descent;
      pmetric->tmInternalLeading = leading;
      pmetric->tmHeight = ascent + descent + leading;
      pmetric->tmExternalLeading = leading;
      //CapHeight := CTFontGetCapHeight(LFontRef);
      //XHeight := CTFontGetXHeight(LFontRef);
      //CFRelease(LFontRef);
//
//      CGFloat ascent, descent, leading, width;
//
//      const_cast < graphics * > (this)->internal_show_text(0, 0, 0, DT_TOPLEFT, str, (int) str.get_length(), kCGTextInvisible, false, &ascent, &descent, &leading, &width);
//
//      lpMetrics->tmAscent              = ascent;
//      lpMetrics->tmDescent             = descent;
//
//      pmetric->tmAveCharWidth        = (::i32) (width * (m_pfont.is_null() ? 1.0 : m_pfont->m_dFontWidth) / (double) str.get_length());

      return true;

   }


   bool graphics::get_output_text_metrics(::draw2d::text_metric * lpMetrics)
   {

      __throw(not_implemented());
      return false;

      //      ASSERT(get_handle1() != nullptr);
      //      return ::GetTextMetrics(get_handle1(), lpMetrics) != FALSE;

   }


//   i32 graphics::GetTextCharacterExtra()
//   {
//
//      __throw(not_implemented());
//      return 0;
//
//      //      ASSERT(get_handle2() != nullptr);
//      //      return ::GetTextCharacterExtra(get_handle2());
//
//   }
//
//   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer)
//   {
//
//      __throw(not_implemented());
//      return false;
//
//      //      ASSERT(get_handle2() != nullptr);
//      //      return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != FALSE;
//
//   }
//
//   bool graphics::GetOutputCharWidth(::u32 nFirstChar, ::u32 nLastChar, LPINT lpBuffer)
//   {
//
//      __throw(not_implemented());
//      return false;
//
//      //      ASSERT(get_handle1() != nullptr);
//      //      return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != FALSE;
//
//   }
//
//
//   ::u32 graphics::GetFontLanguageInfo()
//   {
//
//      __throw(not_implemented());
//
//      return 0;
//
//   }


   /*

    ::u32 graphics::GetCharacterPlacement(const char * lpString, i32 nCount, i32 nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags)
    {

    __throw(not_implemented());
    return 0;

    //      ASSERT(get_handle1() != nullptr);
    //      return ::GetCharacterPlacement(get_handle1(), lpString, nCount, nMaxExtent, lpResults, dwFlags);

    }

    ::u32 graphics::GetCharacterPlacement(string & str, i32 nMaxExtent, LPGCP_RESULTS lpResults, ::u32 dwFlags)
    {

    __throw(not_implemented());
    return 0;

    //      ASSERT(get_handle1() != nullptr);
    //      return ::GetCharacterPlacement(get_handle1(), (const char *)str, (i32) str.get_length(), nMaxExtent, lpResults, dwFlags);

    }

    */

//   size graphics::GetAspectRatioFilter()
//   {
//
//      __throw(not_implemented());
//      return size(0, 0);
//
//      //      ASSERT(get_handle2() != nullptr);
//      //      ::size size;
//      //      VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
//      //      return size;
//
//   }
//
//
////   bool graphics::ScrollDC(i32 dx, i32 dy, const ::rect & rectScroll, const ::rect & rectClip, ::draw2d::region* pRgnUpdate, LPRECT32 rectUpdate)
////   {
////
////      __throw(not_implemented());
////      return false;
////
////      //      ASSERT(get_handle1() != nullptr);
////      //      return ::ScrollDC(get_handle1(), dx, dy, rectScroll, rectClip, (HRGN)pRgnUpdate->get_os_data(), rectUpdate) != FALSE;
////
////   }
////
////
////   // Printer Escape Functions
////   i32 graphics::Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData)
////   {
////
////      __throw(not_implemented());
////      return 0;
////
////      //      ASSERT(get_handle1() != nullptr);
////      //      return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);
////
////   }

   // graphics 3.1 Specific functions
   ::u32 graphics::SetBoundsRect(const ::rect & rectBounds, ::u32 flags)
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

   }


//   ::u32 graphics::GetFontData(::u32 dwTable, ::u32 dwOffset, LPVOID lpData, ::u32 cbData)
//   {
//
//      __throw(not_implemented());
//
//      return 0;
//
//   }


   i32 graphics::StartPage()
   {

      __throw(not_implemented());

      return 0;

   }


   i32 graphics::EndPage()
   {

      __throw(not_implemented());

      return 0;

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

   bool graphics::MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask, ::u32 dwRop)
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

   bool graphics::SetPixelV(i32 x, i32 y, const ::color & color)
   {

      __throw(not_implemented());
      return false;

      //      ASSERT(get_handle1() != nullptr);
      //      return ::SetPixelV(get_handle1(), x, y, crColor) != FALSE;

   }

   bool graphics::SetPixelV(const ::point & point, const ::color & color)
   {

      __throw(not_implemented());
      return false;

      //      ASSERT(get_handle1() != nullptr);
      //      return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != FALSE;

   }

   bool graphics::AngleArc(i32 x, i32 y, i32 nRadius, angle fStartAngle, angle fSweepAngle)
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
      //      return ArcTo(rect.left, rect.top, rect.right, rect.bottom, pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);

   }

   i32 graphics::GetArcDirection()
   {

      __throw(not_implemented());
      return 0;

      //      ASSERT(get_handle2() != nullptr);
      //      return ::GetArcDirection(get_handle2());

   }

   bool graphics::PolyPolyline(const POINT32* lpPoints, const ::u32* lpPolyPoints, i32 nCount)
   {

      __throw(not_implemented());
      return false;

      //      ASSERT(get_handle1() != nullptr);
      //      return ::PolyPolyline(get_handle1(), lpPoints, lpPolyPoints, nCount) != FALSE;

   }

   /*

    bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust)
    {

    __throw(not_implemented());
    return false;

    //      ASSERT(get_handle2() != nullptr);
    //      return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;

    }

    */

   ::draw2d::pen * graphics::get_current_pen()
   {

      return m_ppen;

   }

   ::draw2d::brush * graphics::get_current_brush()
   {

      return m_pbrush;

   }

   ::draw2d::palette * graphics::get_current_palette()
   {

      return (::draw2d::palette *)nullptr;

   }


   ::draw2d::font * graphics::get_current_font()
   {

      return m_pfont;

   }


   ::draw2d::bitmap * graphics::get_current_bitmap()
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

//   i32 graphics::DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData)
//   {
//
//      __throw(not_implemented());
//      return 0;
//
//      //      ASSERT(get_handle1() != nullptr);
//      //      return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);
//
//   }
//
//   i32 graphics::Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData,  i32 nOutputSize, char * lpszOutputData)
//   {
//
//      __throw(not_implemented());
//      return 0;
//
//      //       ASSERT(get_handle1() != nullptr);
//      //       return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);
//
//   }

   /*

    bool graphics::GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABCFLOAT lpABCF)
    {

    __throw(not_implemented());
    return false;

    //      ASSERT(get_handle2() != nullptr);
    //      return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != FALSE;

    }

    */

//   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, float* lpFloatBuffer)
//   {
//
//      __throw(not_implemented());
//      return false;
//
//      //      ASSERT(get_handle2() != nullptr);
//      //      return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != FALSE;
//
//   }

   bool graphics::abort_path()
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

   bool graphics::begin_path()
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

   bool graphics::close_figure()
   {

      __throw(not_implemented());
      return false;

      /*
       ASSERT(m_ppath != nullptr);
       return m_ppath->CloseFigure() == Gdiplus::Status::Ok;
       */
   }

   bool graphics::end_path()
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

   bool graphics::fill_path()
   {

      __throw(not_implemented());
      return false;

      //      return m_pgraphics->FillPath(gdiplus_brush(), m_ppath) == Gdiplus::Status::Ok;

   }

   bool graphics::flatten_path()
   {

      __throw(not_implemented());
      return false;

      //      return m_ppath->Flatten() == Gdiplus::Status::Ok;

   }

   float graphics::GetMiterLimit()
   {

      __throw(not_implemented());
      return 0.f;

      //      ASSERT(get_handle1() != nullptr);
      //      float fMiterLimit;
      //      VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
      //      return fMiterLimit;

   }

   i32 graphics::GetPath(POINT32 * lpPoints, LPBYTE lpTypes, i32 nCount)
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

   bool graphics::stroke_and_fill_path()
   {

      __throw(not_implemented());
      return false;

      //      bool bOk1 = m_pgraphics->FillPath(gdiplus_brush(), m_ppathPaint) == Gdiplus::Status::Ok;

      //      bool bOk2 = m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

      //      return bOk1 && bOk2;

   }

   bool graphics::stroke_path()
   {

      __throw(not_implemented());
      return false;

      //      return m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

   }

   bool graphics::widen_path()
   {

      __throw(not_implemented());
      return false;

      //      return m_ppath->Widen(gdiplus_pen()) == Gdiplus::Status::Ok;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

 //     if(!_set(ppath))
   //      return false;
      
      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_pdc, path);

      _draw();

      _draw_inline(ppath, m_ppen);

      return true;

   }

   bool graphics::fill_path(::draw2d::path * ppath)
   {

      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_pdc, path);

      _fill();

      _fill_inline(ppath, m_pbrush);

      return true;

   }


   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_pdc, path);

      _draw(ppen);

      _draw_inline(ppath, ppen);

      return true;
      
   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      auto path = ppath->template get_os_data < CGMutablePathRef >(this);
      
      CGContextAddPath(m_pdc, path);

      _fill(pbrush);

      _fill_inline(ppath, pbrush);

      return true;

   }


//   bool graphics::draw_inline_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
//   {
//
//      if(!_set(ppath))
//         return false;
//
//      return _draw(ppen);
//
//   }
//
//
//   bool graphics::fill_inline_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
//   {
//
//      if(!_set(ppath))
//         return false;
//
//      return _fill(pbrush);
//
//   }


   bool graphics::AddMetaFileComment(::u32 nDataSize, const byte* pCommentData)
   {

      __throw(not_implemented());
      return false;

      //      ASSERT(get_handle1() != nullptr);
      //      return ::GdiComment(get_handle1(), nDataSize, pCommentData) != FALSE;

   }


   /*bool CALLBACK metaCallback(
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
    // Enumerate pMeta to the destination rectangle, passing pMeta as the callback data.
    graphics.EnumerateMetafile(
    pMeta,
    Rect(0, 0, 300, 50),
    metaCallback,
    pMeta);
    // Draw pMeta as an pimage->
    graphics.DrawImage(pMeta, Point(0, 150));
    delete pMeta;;
    }*/

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const ::rect & rectBounds)
   {

      __throw(not_implemented());
      return false;


      /*      Gdiplus::RectF rect((Gdiplus::REAL) lpBounds->left, (Gdiplus::REAL) lpBounds->top, (Gdiplus::REAL) width(lpBounds), (Gdiplus::REAL) height(lpBounds));

       Gdiplus::Metafile* pMeta = new Gdiplus::Metafile(hEnhMF, false);

       //m_pgraphcis->EnumerateMetafile(pMeta, rect, metaCallback, PMETAHEADER);

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

   bool graphics::alpha_blendRaw(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate)
   {

//      if(m_pimageAlphaBlend->is_set())
//      {
//
//
//         ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());
//
//
//         ::image_pointer pimageWork = nullptr;
//         ::image_pointer pimageWork2 = nullptr;
//         //         ::image_pointer pimageWork3 = nullptr;
//         ::image_pointer pimageWork4 = nullptr;
//
//
//         class const ::point & pointSrc(xSrc, ySrc);
//         ::point pointDest(xDst, yDst);
//         ::size size(nDstWidth, nDstHeight);
//
//
//
//         ::image_pointer pimage;
//         if(imageWork == nullptr)
//         {
//            pimage->create(this);
//            imageWork = pimage;
//         }
//         if(imageWork == nullptr)
//            return false;
//         if(!imageWork = create_image(size))
//            return false;
//         if(!imageWork.from(::point(), pgraphicsSrc, pointSrc, size))
//            return false;
//
//
//
//
//         ::image_pointer pimage2;
//         if(imageWork2 == nullptr)
//         {
//            pimage2->create(this);
//            imageWork2 = pimage2;
//         }
//
//
//         ::image_pointer pimage4;
//         if(imageWork4 == nullptr)
//         {
//            image4.create(this);
//            imageWork4 = image4;
//         }
//         if(imageWork4 == nullptr)
//            return false;
//         if(!imageWork4 = create_image(size))
//            return false;
//
//
//         imageWork4.Fill(255, 0, 0, 0);
//
//         imageWork4.from(point(max(0, m_pointAlphaBlend.x - xDst), max(0, m_pointAlphaBlend.y - yDst)),
//                         m_pimageAlphaBlend->get_graphics(), point(max(0, xDst - m_pointAlphaBlend.x), max(0, yDst - m_pointAlphaBlend.y)), size);
//
//         imageWork.channel_multiply(::color::channel_alpha, imageWork4);
//
//
//         ::keep < image > keep2(&m_pimageAlphaBlend, nullptr, m_pimageAlphaBlend, true);
//
//
//         return BitBlt(pointDest.x, ptDest.y, size.cx, size.cy, imageWork.get_graphics(), pointSrc.x, pointSrc.y);
//
//
//      }


      CGContextSetAlpha(m_pdc, (CGFloat) dRate);
      StretchBltRaw(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight);
      CGContextSetAlpha(m_pdc, (CGFloat) 1.f);

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


    class const ::point & pointSrc(xSrc, ySrc);
    ::point pointDest(xDest, yDest);
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


    return System.imaging().true_blend(this, pointDest, size, imageWork.get_graphics(), pointSrc);


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

   bool graphics::GradientFill(TRIVERTEX* pVertices, WINULONG nVertices, void * pMesh, WINULONG nMeshElements, ::u32 dwMode)
   {

      __throw(not_implemented());
      return false;

   }


#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE32 LPSIZE32)
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
       cxPerInch = GetDeviceCaps(LOGPIXELSX);
       cyPerInch = GetDeviceCaps(LOGPIXELSY);
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

   void graphics::HIMETRICtoDP(LPSIZE32 LPSIZE32)
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
       cxPerInch = GetDeviceCaps(LOGPIXELSX);
       cyPerInch = GetDeviceCaps(LOGPIXELSY);
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

   void graphics::LPtoHIMETRIC(LPSIZE32 LPSIZE32)
   {
      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE32)));

      LPtoDP(LPSIZE32);
      DPtoHIMETRIC(LPSIZE32);
   }

   void graphics::HIMETRICtoLP(LPSIZE32 LPSIZE32)
   {
      ASSERT(__is_valid_address(LPSIZE32, sizeof(SIZE32)));

      HIMETRICtoDP(LPSIZE32);
      DPtoLP(LPSIZE32);
   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* PASCAL graphics::GetHalftoneBrush(::base::application * papp)
   {
      /*      ::ca2::LockGlobals(CRIT_HALFTONEBRUSH);
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
       ::ca2::UnlockGlobals(CRIT_HALFTONEBRUSH);

       //      return ::win::brush::from_handle(papp, gen_HalftoneBrush);*/
      return nullptr;
   }

//   void graphics::DrawDragRect(const ::rect & rect, const ::size & size, const ::rect & rectLast, const ::size & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
//   {
//
//      __throw(not_implemented());
//
//      /*
//       ASSERT(__is_valid_address(rect, sizeof(RECT32), FALSE));
//       ASSERT(rectLast == nullptr ||
//       __is_valid_address(rectLast, sizeof(RECT32), FALSE));
//
//       // first, determine the update region and select it
//       ::draw2d::region rgnNew;
//       ::draw2d::region rgnOutside, rgnInside;
//       rgnOutside.CreateRectRgnIndirect(rect);
//       const ::rect & rect = *rect;
//       rect.inflate(-size.cx, -size.cy);
//       rect.intersect(rect, rect);
//       rgnInside.CreateRectRgnIndirect(rect);
//       rgnNew.CreateRectRgn(0, 0, 0, 0);
//       rgnNew.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);
//
//       ::draw2d::brush* pBrushOld = nullptr;
//       if (pBrush == nullptr)
//       {
//       pBrush = graphics::GetHalftoneBrush(get_object());
//       }
//
//       ENSURE(pBrush);
//
//       if (pBrushLast == nullptr)
//       {
//       pBrushLast = pBrush;
//       }
//
//       ::draw2d::region rgnLast, rgnUpdate;
//       if (rectLast != nullptr)
//       {
//       // find difference between new region and old region
//       rgnLast.CreateRectRgn(0, 0, 0, 0);
//       rgnOutside.SetRectRgn(rectLast);
//       rect = *rectLast;
//       rect.inflate(-sizeLast.cx, -sizeLast.cy);
//       rect.intersect(rect, rectLast);
//       rgnInside.SetRectRgn(rect);
//       rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);
//
//       // only diff them if brushes are the same
//       if (pBrush->get_os_data() == pBrushLast->get_os_data())
//       {
//       rgnUpdate.CreateRectRgn(0, 0, 0, 0);
//       rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
//       }
//       }
//       if (pBrush->get_os_data() != pBrushLast->get_os_data() && rectLast != nullptr)
//       {
//       // brushes are different -- erase old region first
//       SelectClipRgn(&rgnLast);
//       GetClipBox(&rect);
//       pBrushOld = SelectObject(pBrushLast);
//       PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);
//       SelectObject(pBrushOld);
//       pBrushOld = nullptr;
//       }
//
//       // draw into the update/new region
//       SelectClipRgn(rgnUpdate.get_os_data() != nullptr ? &rgnUpdate : &rgnNew);
//       GetClipBox(&rect);
//       pBrushOld = SelectObject(pBrush);
//       PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);
//
//       // cleanup DC
//       if (pBrushOld != nullptr)
//       SelectObject(pBrushOld);
//       SelectClipRgn(nullptr);
//
//       */
//
//   }

   /*void graphics::FillSolidRect(const ::rect & rect, const ::color & color)
    {
    ::SetBkColor(get_handle1(), clr);
    ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, rect, nullptr, 0, nullptr);
    }*/


   void graphics::draw_3drect(const ::rectd & rect, const ::color & colorTopLeft, const ::color & colorBottomRight, eborder eborder)
   {
      ::i32 x = rect.left;
      ::i32 y = rect.top;
      ::i32 cx = width(rect);
      ::i32 cy = height(rect);
      if(eborder & border_top)
      fill_solid_rect_dim(x, y, cx - 1, 1, colorTopLeft);
      
      if(eborder & border_left)
      fill_solid_rect_dim(x, y, 1, cy - 1, colorTopLeft);
      
      if(eborder &border_right)
      fill_solid_rect_dim(x + cx - 1, y, 1, cy, colorBottomRight);
      
      if(eborder & border_bottom)
      fill_solid_rect_dim(x, y + cy - 1, cx, 1, colorBottomRight);
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

    ASSERT(get_handle1() == nullptr);      // only attach once, detach on destroy
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

      if(m_layer != nullptr)
      {

         //CGLayerRelease(m_layer);

         m_layer = nullptr;

         if(m_bOwnDC)
         {

            CGContextRelease(m_pdc);

         }

         m_pdc = nullptr;

      }
      else
      {

         m_pdc = nullptr;

         m_layer = nullptr;

      }

      m_pimage = nullptr;

      m_etextrenderinghint  = ::draw2d::text_rendering_hint_anti_alias_grid_fit;

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
          hdc_map* pMap = afxMapHDC();
    if (pMap != nullptr && pMap->lookup_permanent(get_handle1()) == this)
    {
    TRACE(::ca2::trace::category_AppMsg, 0, "Cannot Set Output hDC on Attached graphics.\n");
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
          hdc_map* pMap = afxMapHDC();
    if (pMap != nullptr && pMap->lookup_permanent(get_handle1()) == this)
    {
    TRACE(::ca2::trace::category_AppMsg, 0, "Cannot Release Output hDC on Attached graphics.\n");
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


      CGContextSaveGState(m_pdc);

      m_iSaveDC++;


      return m_iSaveDC;

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

      bool bRestored = false;

      while(m_iSaveDC >= max(1, nSavedDC))
      {

         CGContextRestoreGState(m_pdc);

         m_iSaveDC--;

         bRestored = true;

      }



      return bRestored;

      /*
       bool bRetVal = TRUE;
       if(get_handle1() != nullptr && get_handle1() != get_handle2())
       bRetVal = ::RestoreDC(get_handle1(), nSavedDC) != FALSE;
       if(get_handle2() != nullptr)
       bRetVal = (bRetVal && ::RestoreDC(get_handle2(), nSavedDC) != FALSE);
       return bRetVal;
       */

   }

   //   ::draw2d::object* PASCAL graphics::SelectGdiObject(::base::application * papp, HDC hDC, HGDIOBJ h)
   // {
   //      return ::win::object::from_handle(papp, ::SelectObject(hDC, h));
   //}


//   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
//   {
//      return nullptr;
//      //      return dynamic_cast < ::draw2d::palette * > (::win::object::from_handle(get_context_application(), ::SelectPalette(get_handle1(), (HPALETTE)pPalette->get_os_data(), bForceBackground)));
//   }
//
//   color32_t graphics::SetBkColor(color32_t crColor)
//   {
//
////      __throw(not_implemented());
//      return 0;
//
//
//      /*
//       color32_t crRetVal = CLR_INVALID;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       crRetVal = ::SetBkColor(get_handle1(), crColor);
//       if(get_handle2() != nullptr)
//       crRetVal = ::SetBkColor(get_handle2(), crColor);
//       return crRetVal;
//       */
//
//   }

   i32 graphics::SetBkMode(i32 nBkMode)
   {

      return 0;

      /*      i32 nRetVal = 0;
       if(get_handle1() != nullptr && get_handle1() != get_handle2())
       nRetVal = ::SetBkMode(get_handle1(), nBkMode);
       if(get_handle2() != nullptr)
       nRetVal = ::SetBkMode(get_handle2(), nBkMode);
       return nRetVal;*/
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

//      __throw(not_implemented());
      //return 0;


      if(nStretchMode == 0)
      {

         CGContextSetInterpolationQuality(m_pdc, kCGInterpolationDefault);

      }
      else if(nStretchMode == e_interpolation_mode_high_quality_bicubic)
      {

         CGContextSetInterpolationQuality(m_pdc, kCGInterpolationHigh);

      }
      else
      {

         CGContextSetInterpolationQuality(m_pdc,kCGInterpolationLow);

      }

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

   bool graphics::ModifyWorldTransform(const XFORM* pXform,::u32 iMode)
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

      __throw(not_implemented());
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

   point graphics::GetViewportOrg()
   {

//      sync_lock sl(mutex());

//      CGAffineTransform affine = CGContextGetCTM(m_pdc);

//      return point(affine.tx, affine.ty);

      return ::draw2d::graphics::GetViewportOrg();

   }


   bool graphics::_get(::draw2d::matrix & matrix)
   {

      sync_lock sl(mutex());

      CGAffineTransform affine = CGContextGetCTM(m_pdc);

      __copy(matrix, affine);

      return true;

   }


   bool graphics::_set(const ::draw2d::matrix & matrix)
   {

      sync_lock sl(mutex());

      CGAffineTransform affine = CGContextGetCTM(m_pdc);

      CGAffineTransform affineInverted;

      affineInverted = CGAffineTransformInvert(affine);

      CGContextConcatCTM(m_pdc, affineInverted);

      CGAffineTransform affineSet;

      __copy(affineSet, matrix);

      CGContextConcatCTM(m_pdc, affineSet);

      return true;

   }


   point graphics::SetViewportOrg(i32 x, i32 y)
   {

      point pt =GetViewportOrg();
      
      pt.x = x - pt.x;
      pt.y = y - pt.y;
      
      return OffsetViewportOrg(pt.x, pt.y);
      



   }


   point graphics::OffsetViewportOrg(i32 nWidth, i32 nHeight)
   {

//      CGAffineTransform affine = CGContextGetCTM(m_pdc);
//
//      if(nWidth != 0 || nHeight != 0)
//      {
//
//         CGContextTranslateCTM(m_pdc, nWidth, nHeight);
//
//      }
//
//      return point(affine.tx, affine.ty);
      return ::draw2d::graphics::OffsetViewportOrg(nWidth, nHeight);

   }


   ::estatus graphics::clear_current_point()
   {
   
      return ::success;
   
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


   size graphics::ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom)
   {

      return ::draw2d::graphics::ScaleViewportExt(xNum, xDenom, yNum, yDenom);

   }


   point graphics::SetWindowOrg(i32 x, i32 y)
   {

      __throw(not_implemented());
      return ::point();

      /*
       const ::point & ::point();
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
       const ::point & ::point();
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

   i32 graphics::GetClipBox(RECT32 * prect)
   {

      CGRect rect =CGContextGetClipBoundingBox (m_pdc);
      
      prect->left = rect.origin.x;
      prect->top = rect.origin.y;
      prect->right = prect->left + rect.size.width;
      prect->bottom = prect->top + rect.size.height;

      return 0;

      /*      return ::GetClipBox(get_handle1(), rect);*/
   }

//   i32 graphics::SelectClipRgn(::draw2d::region * pregion)
//   {
//
//      if(pregion == nullptr)
//      {
//
//         m_pregion.release();
//
//      }
//      else
//      {
//
//         m_pregion = pregion;
//
//         //cairo_clip(m_pdc);
//
//      }
//
//      return 0;
//
//      /*
//       i32 nRetVal = ERROR;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       nRetVal = ::SelectClipRgn(get_handle1(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
//       if(get_handle2() != nullptr)
//       nRetVal = ::SelectClipRgn(get_handle2(), pRgn == nullptr ? nullptr : (HRGN) pRgn->get_os_data());
//       return nRetVal;
//       */
//
//   }


//   i32 graphics::ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
//   {
//
//      __throw(not_implemented);
//
//      return 0;
//
//   }


//   i32 graphics::ExcludeClipRect(const ::rect & rect)
//   {
//
//      __throw(not_implemented());
//      
//      return 0;
//
//   }


//   i32 graphics::IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
//   {
//
//      __throw(not_implemented());
//      return 0;
//
//      /*
//       i32 nRetVal = ERROR;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
//       if(get_handle2() != nullptr)
//       nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
//       return nRetVal;
//       */
//
//   }

//   i32 graphics::IntersectClipRect(const ::rect & rectParam)
//   {
//
//      //__throw(not_implemented());
//      CGRect rect;
//
//      __copy(rect, rectParam);
//
////      rect.origin.x     = rect.left;
////      rect.origin.y     = rect.top;
////      rect.size.width   = rect.right - rect.left;
////      rect.size.height  = rect.bottom - rect.top;
//      CGContextAddRect(m_pdc, rect);
//
//      ::draw2d::region_pointer pregion;
//
//      pregion->create_rect(rectParam);
//
//
//      if(m_pregion)
//      {
//
//         auto pregionOld = m_pregion;
//
//         __construct(m_pregion);
//
//         m_pregion->combine(pregionOld, pregion, ::draw2d::region::combine_intersect, this);
//
//         CGContextClip(m_pdc);
//
//      }
//      else
//      {
//
//         m_pregion = pregion;
//
//      }
//
//      m_pregionClip->defer_update(this, 0);
//
//      __add_path(m_pregionClip);
//
//      CGContextClip(m_pdc);
//
//      return 0;
//
//      /*      i32 nRetVal = ERROR;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       nRetVal = ::IntersectClipRect(get_handle1(), rect.left, rect.top, rect.right, rect.bottom);
//       if(get_handle2() != nullptr)
//       nRetVal = ::IntersectClipRect(get_handle2(), rect.left, rect.top, rect.right, rect.bottom);
//       return nRetVal;
//       */
//
//   }
//
//   i32 graphics::OffsetClipRgn(i32 x, i32 y)
//   {
//
//      if(m_pregionClip)
//      {
//
//         m_pregionClip->m_pointOffset += ::size(x, y);
//
//         m_pregionClip->set_modified();
//
//         _add_path(m_pregionClip);
//
//         CGContextClip(m_pdc);
//
//      }
//
//      //__throw(not_implemented());
//      return 0;
//
//      /*
//       i32 nRetVal = ERROR;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       nRetVal = ::OffsetClipRgn(get_handle1(), x, y);
//       if(get_handle2() != nullptr)
//       nRetVal = ::OffsetClipRgn(get_handle2(), x, y);
//       return nRetVal;
//       */
//
//   }
//
//   i32 graphics::OffsetClipRgn(const ::size & size)
//   {
//
//      __throw(not_implemented());
//      return 0;
//
//      /*
//       i32 nRetVal = ERROR;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
//       if(get_handle2() != nullptr)
//       nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
//       return nRetVal;
//       */
//   }

   /*point graphics::MoveTo(i32 x, i32 y)
    {
    const ::point & ::point();
    if(get_handle1() != nullptr && get_handle1() != get_handle2())
    ::MoveToEx(get_handle1(), x, y, &point);
    if(get_handle2() != nullptr)
    ::MoveToEx(get_handle2(), x, y, &point);
    return point;
    }*/

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


//   i32 graphics::SetTextJustification(i32 nBreakExtra, i32 nBreakCount)
//   {
//
//      __throw(not_implemented());
//      return 0;
//
//      /*
//       i32 nRetVal = 0;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
//       if(get_handle2() != nullptr)
//       nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
//       return nRetVal;
//       */
//
//   }
//
//   i32 graphics::SetTextCharacterExtra(i32 nCharExtra)
//   {
//
//      __throw(not_implemented());
//      return 0;
//
//      /*
//       ASSERT(get_handle1() != nullptr);
//       i32 nRetVal = 0x8000000;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
//       if(get_handle2() != nullptr)
//       nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
//       return nRetVal;
//       */
//
//   }
//
//   ::u32 graphics::SetMapperFlags(::u32 dwFlag)
//   {
//
//      __throw(not_implemented());
//      return 0;
//
//      /*
//       ASSERT(get_handle1() != nullptr);
//       ::u32 dwRetVal = GDI_ERROR;
//       if(get_handle1() != nullptr && get_handle1() != get_handle2())
//       dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
//       if(get_handle2() != nullptr)
//       dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
//       return dwRetVal;
//       */
//
//   }
//
//   //   typedef ::u32 (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
//   //   typedef ::u32 (CALLBACK* __GDISETLAYOUTPROC)(HDC, ::u32);

   ::u32 graphics::GetLayout()
   {

      __throw(not_implemented());
      return 0;

      /*
       HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
       ASSERT(hInst != nullptr);
       ::u32 dwGetLayout = LAYOUT_LTR;
       __GDIGETLAYOUTPROC pfn;
       pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
       // if they API is available, just call it. If it is not
       // available, indicate an error.
       if (pfn != nullptr)
       dwGetLayout = (*pfn)(get_handle1());
       else
       {
       dwGetLayout = GDI_ERROR;
       set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
       }
       return dwGetLayout;
       */

   }

   ::u32 graphics::SetLayout(::u32 dwSetLayout)
   {

      __throw(not_implemented());
      return 0;

      /*
       HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
       ASSERT(hInst != nullptr);
       ::u32 dwGetLayout = LAYOUT_LTR;
       __GDISETLAYOUTPROC pfn;
       pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
       // If the API is availalbe, just call it. If it's not available,
       // setting anything other than LAYOUT_LTR is an error.
       if (pfn != nullptr)
       dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
       else if (dwSetLayout != LAYOUT_LTR)
       {
       dwGetLayout = GDI_ERROR;
       set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
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

//   bool graphics::ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
//   {
//
//      __throw(not_implemented());
//      return false;
//
//      /*
//       ASSERT(get_handle1() != nullptr);
//       bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
//       if (get_handle1() != get_handle2())
//       {
//       ::point point;
//       VERIFY(::GetCurrentPositionEx(get_handle1(), &point));
//       VERIFY(::MoveToEx(get_handle2(), point.x, point.y, nullptr));
//       }
//       return bResult;
//       */
//
//   }

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


   ::estatus graphics::reset_clip()
   {
   
      CGContextResetClip(m_pdc);
      
      return ::success;
   
   }


   ::estatus graphics::_intersect_clip()
   {
      
      CGContextClip(m_pdc);
      
      return ::success;
      
   }


   ::estatus graphics::_add_shape(const ::rect & rect)
   {
   
      CGRect r;
      
      __copy(r, rect);
   
      CGContextAddRect(m_pdc, r);
      
      return ::success;
      
   }


   ::estatus graphics::_add_shape(const ::rectd & rect)
   {
   
      CGRect r;
         
      __copy(r, rect);
      
      CGContextAddRect(m_pdc, r);
         
      return ::success;
      
   }


   ::estatus graphics::_add_shape(const ::oval & oval)
   {
   
      CGRect r;
      
      __copy(r, oval);
   
      CGContextAddEllipseInRect(m_pdc, r);
      
      return ::success;
      
   }


   ::estatus graphics::_add_shape(const ::ovald & oval)
   {
   
      CGRect r;
      
      __copy(r, oval);
   
      CGContextAddEllipseInRect(m_pdc, r);
      
      return ::success;
      
   }


   ::estatus graphics::_add_shape(const ::polygon & polygon)
   {
   
      CGContextBeginPath(m_pdc);
   
      set_polygon(polygon.get_data(), polygon.get_count());
      
      CGContextClosePath(m_pdc);
      
      return ::success;
      
   }


   ::estatus graphics::_add_shape(const ::polygond & polygon)
   {

      CGContextBeginPath(m_pdc);
      
      set_polygon(polygon.get_data(), polygon.get_count());
         
      CGContextClosePath(m_pdc);
         
      return ::success;
      
   }



//   void graphics::on_apply_clip_region()
//   {
//
//      CGContextResetClip(m_pdc);
//
//      if(m_pregion)
//      {
//
//         _clip(m_pregion);
//
//      }
//
//   }


   void graphics::LPtoDP(LPSIZE32 LPSIZE32)
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

   void graphics::DPtoLP(LPSIZE32 LPSIZE32)
   {

      __throw(not_implemented());
      return;

   }



   i32 graphics::draw_text(const char * lpszString, i32 nCount, const ::rectd & rect, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      return draw_text(string(lpszString, nCount), rect, nFormat);

   }


   bool graphics::draw_text(const string & str, const ::rect & rect, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      ::draw2d::graphics::draw_text(str, rect, nFormat);

      return 1;

   }


   i32 graphics::draw_text_ex(char * lpszString, i32 nCount, const ::rectd & rect, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   {

      __throw(not_implemented());

      return 0;

   }


   bool graphics::draw_text_ex(const string & str, const ::rectd & rect, const ::e_align & ealign, const ::e_draw_text & edrawtext, LPDRAWTEXTPARAMS lpDTParams)
   {

      __throw(not_implemented());
      return 0;

   }


   sized graphics::GetTextExtent(const char * lpszString, strsize nCount, i32 iIndex)
   {

      sized sz;

      if (!GetTextExtent(sz, lpszString, nCount, iIndex))
         return ::size(0, 0);

      return size((int) sz.cx, (int) sz.cy);

   }


   sized graphics::GetTextExtent(const char * lpszString, strsize nCount)
   {

      ::sized sized;

      if(!GetTextExtent(sized, lpszString, nCount, (int) nCount))
      {
         
         return ::size(0, 0);
         
      }

      return ::size(sized.cx, sized.cy);

   }


   sized graphics::GetTextExtent(const string & str)
   {

      ::sized size;

      if(!GetTextExtent(size, str, (int)str.get_length()))
      {
         
         return ::size(0, 0);
         
      }

      return size;

   }


   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount)
   {

      __throw(not_implemented());
      return ::size(0, 0);

   }


   size graphics::GetOutputTextExtent(const string & str)
   {

      __throw(not_implemented());
      return ::size(0, 0);

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, i32 iIndex)
   {

      sync_lock sl(mutex());

      CGFloat ascent, descent, leading, width;

      string_array stra;

      stra.add_lines(string(lpszString, min(iIndex, nCount), 0));

      size.cy = 0;

      size.cx = 0;

      for(auto str : stra)
      {

         const_cast < graphics * > (this)->internal_show_text(0, 0, 0, DT_TOPLEFT, str, kCGTextInvisible, false, &ascent, &descent, &leading, &width);

         size.cy += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            size.cy += descent;
//
//         }

         size.cx = max(size.cx, width);

      }

      return true;

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount)
   {

      return GetTextExtent(size, lpszString, nCount, (i32) nCount);

   }


   bool graphics::GetTextExtent(sized & size, const string & str)
   {

      return GetTextExtent(size, str);

   }


   void graphics::fill_rect(const ::rectd & rectParam, const ::color & color)
   {

      CGRect rect;

      __copy(rect, rectParam);

      internal_set_fill_color(color);

      CGContextFillRect(m_pdc, rect);

   }


   bool graphics::text_out(i32 x, i32 y, const char * lpszString, strsize nCount)
   {

      return TextOutRaw(double(x), double(y), string(lpszString, nCount));

   }


   bool graphics::TextOutRaw(double x, double y, const string & str)
   {

      return internal_show_text(x, y, 0, DT_TOPLEFT, str, kCGTextFill);

   }


   bool graphics::internal_show_text(double x, double y, double wAlign, const ::e_align & ealign, const ::e_draw_text & edrawtext, const string & str, CGTextDrawingMode emode, bool bDraw, CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth, ::draw2d::pen * ppen, ::draw2d::brush * pbrush, ::draw2d::font * pfont)
   {

      if(pfont == nullptr)
      {
         
         if(m_pfont.is_null())
         {

            m_pfont.create();

            m_pfont->create_pixel_font(FONT_SANS, 16.0);

         }
         
         pfont = m_pfont;
         
      }

      if(pbrush == nullptr)
      {
         
         pbrush = m_pbrush;
         
      }

      if(ppen == nullptr)
      {
         
         ppen = m_ppen;
         
      }

      return internal_show_text(pfont, pbrush, ppen, x, y, wAlign, nFormat, str, emode, bDraw, pascent,pdescent, pleading, pwidth);

   }


   bool graphics::draw_line(const ::pointd & p1, const ::pointd & p2, ::draw2d::pen * ppen)
   {

      CGContextBeginPath(m_pdc);

      CGContextMoveToPoint(m_pdc, p1.x, p1.y);

      CGContextAddLineToPoint(m_pdc, p2.x, p2.y);

      _draw(ppen);

      m_point = p2;

      return true;

   }


   bool graphics::line_to(const ::pointd & point)
   {

      CGContextBeginPath(m_pdc);

      CGContextMoveToPoint(m_pdc, m_point.x, m_point.y);

      CGContextAddLineToPoint(m_pdc, point.x, point.y);

      _draw();

      m_point = point;

      return true;

   }


   bool graphics::set_alpha_mode(::draw2d::e_alpha_mode ealphamode)
   {

      try
      {

         if(m_pdc == nullptr)
         {

            return false;

         }

         ::draw2d::graphics::set_alpha_mode(ealphamode);

         if(m_ealphamode == ::draw2d::alpha_mode_blend)
         {

            CGContextSetBlendMode(m_pdc, kCGBlendModeNormal);

         }
         else if(m_ealphamode == ::draw2d::alpha_mode_set)
         {

            CGContextSetBlendMode(m_pdc, kCGBlendModeCopy);

         }

      }
      catch(...)
      {

      }

      return true;

   }


   bool graphics::set_text_rendering_hint(::draw2d::e_text_rendering_hint etextrenderinghint)
   {

      return ::draw2d::graphics::set_text_rendering_hint(etextrenderinghint);

   }


//   void * graphics::get_os_data() const
//   {
//
//      return (void *) m_pdc;
//
//   }


   bool graphics::attach(void * pdata)
   {

      m_iType = 10;

      m_pdc = (CGContextRef) pdata;

      m_bOwnDC = false;
      
      m_osdata[0] = (void *) m_pdc;

      return true;

   }


   void * graphics::detach()
   {

      CGContextRef pgraphics = m_pdc;

      m_pdc = nullptr;

      return pgraphics;

   }


   bool graphics::blur(bool bExpand, double dRadius, const ::rect & rect)
   {

//      cairo_pattern_t * ppattern = cairo_get_source(m_pdc);
//
//      if(ppattern == nullptr)
//         return false;
//
//      cairo_surface_t * psurfaceSrc = nullptr;
//
//      cairo_pattern_get_surface(ppattern, &psurfaceSrc);
//
//      cairo_surface_t * psurface = cairo_surface_create_for_rectangle(psurfaceSrc, rect.left, rect.top, width(rect), height(rect));
//
//      cairo_image_surface_blur(psurface, dRadius);

      return true;

   }


   double graphics::get_dpix()
   {

      //      return m_pgraphics->GetDpiX();
      return 72.0;

   }


   bool graphics::_clip(::draw2d::region * pregion, bool bEO)
   {

      if(pregion == nullptr)
      {

         return true;

      }

      if(pregion->m_eregion == ::draw2d::e_region_combine)
      {

         if(pregion->m_ecombine == ::draw2d::e_combine_intersect)
         {

            _clip(pregion->m_pregion1);

            CGContextEOClip(m_pdc);

            _add_path(pregion->m_pregion2);

            CGContextEOClip(m_pdc);

         }
         else if(pregion->m_ecombine == ::draw2d::e_combine_add)
         {

            _clip(pregion->m_pregion1);

            CGContextClip(m_pdc);

            _add_path(pregion->m_pregion2);

            CGContextClip(m_pdc);

         }
         
      }
      else if(pregion->m_eregion == ::draw2d::e_region_rect)
      {

         CGRect rect;

         rect.origin.x = pregion->m_x1;
         rect.origin.y = pregion->m_y1;
         rect.size.width = pregion->m_x2 - pregion->m_x1;
         rect.size.height = pregion->m_y2 - pregion->m_y1;
         
         CGContextAddRect (m_pdc, rect);

      }
      else if(pregion->m_eregion == ::draw2d::e_region_polygon)
      {

         CGContextBeginPath (m_pdc);

         set_polygon(pregion->m_lppoints, pregion->m_nCount);

         CGContextClosePath (m_pdc);

      }
      else if(pregion->m_eregion == ::draw2d::e_region_oval)
      {

         CGRect rect;

         rect.origin.x = pregion->m_x1;
         rect.origin.y = pregion->m_y1;
         rect.size.width = pregion->m_x2 - pregion->m_x1;
         rect.size.height = pregion->m_y2 - pregion->m_y1;

         CGContextAddEllipseInRect(m_pdc, rect);

      }

      if(bEO)
      {
         
         CGContextEOClip(m_pdc);
         
      }
      else
      {
         
         CGContextClip(m_pdc);
         
      }

      return true;

   }


   bool graphics::_add_path(::draw2d::region * pregion)
   {

      if(pregion == nullptr)
         return true;

      if(pregion->m_eregion == ::draw2d::e_region_rect)
      {

         CGRect rect;

         rect.origin.x = pregion->m_x1;
         rect.origin.y = pregion->m_y1;
         rect.size.width = pregion->m_x2 - pregion->m_x1;
         rect.size.height = pregion->m_y2 - pregion->m_y1;

         CGContextAddRect (m_pdc, rect);

      }
      else if(pregion->m_eregion == ::draw2d::e_region_polygon)
      {

         CGContextBeginPath (m_pdc);

         set_polygon(pregion->m_lppoints, pregion->m_nCount);

         CGContextClosePath (m_pdc);

      }
      else if(pregion->m_eregion == ::draw2d::e_region_oval)
      {

         CGRect rect;

         rect.origin.x = pregion->m_x1;
         rect.origin.y = pregion->m_y1;
         rect.size.width = pregion->m_x2 - pregion->m_x1;
         rect.size.height = pregion->m_y2 - pregion->m_y1;


         CGContextAddEllipseInRect(m_pdc, rect);

      }
      else if(pregion->m_eregion == ::draw2d::e_region_combine)
      {
         
         if(pregion->m_ecombine == ::draw2d::e_combine_intersect)
         {

            _add_path(pregion->m_pregion1);
            
            CGContextEOClip(m_pdc);
         
            _add_path(pregion->m_pregion2);
            
            CGContextEOClip(m_pdc);

         }
         else if(pregion->m_ecombine == ::draw2d::e_combine_add)
         {

            _add_path(pregion->m_pregion1);
            
            CGContextClip(m_pdc);
         
            _add_path(pregion->m_pregion2);
            
            CGContextClip(m_pdc);

         }

      }

      return true;

   }


   bool graphics::_set(::draw2d::brush * pbrush)
   {

//      cairo_set_source_rgba(m_pdc, colorref_get_r_value(pbrush->m_color) / 255.0, colorref_get_g_value(pbrush->m_color) / 255.0, colorref_get_b_value(pbrush->m_color) / 255.0, colorref_get_a_value(pbrush->m_color) / 255.0);

      if(pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
         return false;

      CGContextSetRGBFillColor(m_pdc, pbrush->m_color.dr(), pbrush->m_color.dg(), pbrush->m_color.db(), pbrush->m_color.da());

      return true;

   }


   bool graphics::_set(::draw2d::pen * ppen)
   {

      if(ppen == nullptr)
      {
         
         return false;
         
      }

      if(ppen->m_etype == ::draw2d::e_pen_brush && ppen->m_pbrush)
      {

         if(ppen->m_pbrush->m_etype == ::draw2d::brush::type_solid)
         {

            CGContextSetRGBStrokeColor(m_pdc, ppen->m_pbrush->m_color.dr(), ppen->m_pbrush->m_color.dg(), ppen->m_pbrush->m_color.db(), ppen->m_pbrush->m_color.da());

         }

      }
      else
      {

         CGContextSetRGBStrokeColor(m_pdc, ppen->m_color.dr(), ppen->m_color.dg(), ppen->m_color.db(), ppen->m_color.da());

      }

      CGContextSetLineWidth(m_pdc, ppen->m_dWidth);

      return true;

   }


   bool graphics::_set_pen(::draw2d::brush * pbrush, double dWidth)
   {

      if(pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::e_type_null)
      {

         return false;

      }

      CGContextSetRGBStrokeColor(m_pdc, pbrush->m_color.dr(), pbrush->m_color.dg(), pbrush->m_color.db(), pbrush->m_color.da());

      CGContextSetLineWidth(m_pdc, dWidth);

      return true;

   }


   bool graphics::_fill_and_draw()
   {

      _fill(m_pbrush);

      _draw(m_ppen);

      return true;

   }


   bool graphics::_fill(::draw2d::brush * pbrush)
   {

      CGContextRef pgraphics = m_pdc;

      CGContextSaveGState(pgraphics);

      bool bOk = false;

      try
      {

         bOk = _fill(pbrush, true);

      }
      catch (...)
      {

      }

      CGContextRestoreGState(pgraphics);

      return bOk;

   }


   bool graphics::_fill(::draw2d::brush * pbrush, bool bContextClip)
   {

      if(pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::e_type_null)
         return true;

      CGContextRef pgraphics = m_pdc;

      if(pbrush->m_etype == ::draw2d::brush::type_radial_gradient_color)
      {
         
         pbrush->defer_update(this, 0);

         if(bContextClip)
         {

            CGContextClip(pgraphics);

         }

         _clip(m_pregion);

         CGPoint myStartPoint, myEndPoint;

         CGContextTranslateCTM(pgraphics, pbrush->m_point.x, pbrush->m_point.y);

         CGContextScaleCTM(pgraphics, pbrush->m_size.cx, pbrush->m_size.cy);

         myStartPoint.x = 0;

         myStartPoint.y = 0;

         myEndPoint.x = 0;

         myEndPoint.y = 0;

         CGContextDrawRadialGradient(pgraphics, (CGGradientRef) pbrush->m_osdata[0], myStartPoint, 0, myEndPoint, 1.0f, kCGGradientDrawsBeforeStartLocation);

      }
      else if(pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
      {
         
         pbrush->defer_update(this, 0);

         if(bContextClip)
         {

            CGContextClip(pgraphics);

         }

         _clip(m_pregion);

         CGPoint myStartPoint, myEndPoint;

         myStartPoint.x = pbrush->m_point1.x;

         myStartPoint.y = pbrush->m_point1.y;

         myEndPoint.x = pbrush->m_point2.x;

         myEndPoint.y = pbrush->m_point2.y;

         CGContextDrawLinearGradient(pgraphics, (CGGradientRef) pbrush->m_osdata[0], myStartPoint, myEndPoint, 0);

      }
      else if(pbrush->m_etype == ::draw2d::brush::type_pattern)
      {

         if(bContextClip)
         {

            CGContextClip(pgraphics);

         }

         _clip(m_pregion);

         __keep(m_bPat);

         CGRect rect = CGContextGetClipBoundingBox(pgraphics);

         BitBlt(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height, pbrush->m_pimage->g(), 0,0, 0);

         //CGContextRestoreGState(pgraphics);

      }
      else
      {

         if(pbrush->m_osdata[0])
         {
            
            if(m_pregion.is_null())
            {

               CGContextSetFillColorWithColor(pgraphics, (CGColorRef) pbrush->m_osdata[0]);

               CGContextFillPath(pgraphics);

            }
            else
            {

               CGContextSetFillColorWithColor(pgraphics, (CGColorRef) pbrush->m_osdata[0]);

               if(bContextClip)
               {

                  CGContextClip(pgraphics);

               }

               _clip(m_pregion);

               CGContextAddRect(pgraphics, CGContextGetClipBoundingBox(pgraphics));

               CGContextFillPath(pgraphics);

            }
            
         }
         else
         {
            
            if(m_pregion.is_null())
            {

               internal_set_fill_color(pbrush->m_color);

               CGContextFillPath(pgraphics);

            }
            else
            {

               internal_set_fill_color(pbrush->m_color);

               if(bContextClip)
               {

                  CGContextClip(pgraphics);

               }

               _clip(m_pregion);

               CGContextAddRect(pgraphics, CGContextGetClipBoundingBox(pgraphics));

               CGContextFillPath(pgraphics);

            }
            
         }

      }

      return true;

   }


   bool graphics::_draw(::draw2d::pen * ppen)
   {

      if(ppen == nullptr || ppen->m_etype == ::draw2d::e_pen_null)
         return true;

      //if(ppen->m_etype == ::draw2d::e_pen_solid)
      {


         CGContextSaveGState(m_pdc);

         _set(ppen);

         if(ppen->m_etype == ::draw2d::e_pen_brush && ppen->m_pbrush.is_set()
               && (ppen->m_pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color
                   || ppen->m_pbrush->m_etype == ::draw2d::brush::type_radial_gradient_color
                   || ppen->m_pbrush->m_etype == ::draw2d::brush::type_pattern)
           )
         {

            CGContextReplacePathWithStrokedPath(m_pdc);

            // Turn the fillable path in to a clipping region.
//            CGContextClip(m_pdc);

            _fill(ppen->m_pbrush);

         }
         else
         {

            CGContextStrokePath(m_pdc);

         }

         CGContextRestoreGState(m_pdc);

      }

      return true;

   }


   bool graphics::_draw(::draw2d::brush * pbrush)
   {

      if(pbrush == nullptr || pbrush->m_etype == ::draw2d::brush::e_type_null)
         return true;

      //if(ppen->m_etype == ::draw2d::e_pen_solid)
      {


         CGContextSaveGState(m_pdc);

         _set(pbrush);

         if(pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color
               || pbrush->m_etype == ::draw2d::brush::type_radial_gradient_color
               || pbrush->m_etype == ::draw2d::brush::type_pattern)

         {

            CGContextReplacePathWithStrokedPath(m_pdc);

            // Turn the fillable path in to a clipping region.
            //CGContextClip(m_pdc);

            _fill(pbrush);

         }
         else
         {

            CGContextStrokePath(m_pdc);

         }

         CGContextRestoreGState(m_pdc);

      }

      return true;

   }


//   bool graphics::_set(::draw2d::path * ppathParam)
//   {
//
//      if(ppathParam == nullptr)
//      {
//
//         return false;
//
//      }
//
//      if(m_pdc == nullptr)
//      {
//
//         return false;
//
//      }
//
//      CGMutablePathRef path = (CGMutablePathRef) ppathParam->get_os_data(this);
//
//      if(path == nullptr)
//      {
//
//         return false;
//
//      }
//
//      CGContextBeginPath(m_pdc);
//
//      CGContextAddPath(m_pdc, path);
//
//      return true;
//
//   }


   bool graphics::_draw_inline(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      for(auto & pmatter : ppath->m_elementa)
      {
         
         if(pmatter->m_etype == path::type_text_out)
         {

            _draw_inline(pmatter.cast < path::text_out >(), ppen);
            
         }
         else if(pmatter->m_etype == path::type_draw_text)
         {

            _draw_inline(pmatter.cast < path::draw_text >(), ppen);
            
         }

      }

      return true;

   }


   bool graphics::_fill_inline(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      for(auto & pmatter : ppath->m_elementa)
      {
         
         if(pmatter->m_etype == path::type_text_out)
         {

            _fill_inline(pmatter.cast < path::text_out >(), pbrush);
            
         }
         else if(pmatter->m_etype == path::type_draw_text)
         {

            _fill_inline(pmatter.cast < path::draw_text >(), pbrush);
            
         }

      }

      return true;

   }



//   bool graphics::_set(::draw2d_quartz2d::path::matter * pmatter)
//   {
//
//      switch(pmatter->m_etype)
//      {
//      case ::draw2d::path::type_begin:
//         return _set(dynamic_cast < path::begin *>(pmatter));
//      case ::draw2d::path::type_arc:
//         return _set(dynamic_cast < path::arc *>(pmatter));
//      case ::draw2d::path::type_rect:
//         return _set(dynamic_cast < path::rect *>(pmatter));
//      case ::draw2d::path::type_line:
//         return _set(dynamic_cast < path::line *>(pmatter));
//      case ::draw2d::path::type_lines:
//         return _set(dynamic_cast < path::lines *>(pmatter));
//      case ::draw2d::path::type_polygon:
//         return _set(dynamic_cast < path::polygon *>(pmatter));
//      case ::draw2d::path::type_text_out:
//         break;
//      case ::draw2d::path::type_close:
//         return _set(dynamic_cast < path::close *>(pmatter));
//      default:
//         break;
//      }
//
//      return false;
//
//   }


   bool graphics::_draw_inline(::draw2d_quartz2d::path::matter * pmatter, ::draw2d::pen * ppen)
   {

      switch(pmatter->m_etype)
      {
      case ::draw2d::path::type_text_out:
         _draw_inline(dynamic_cast < path::text_out * >(pmatter), ppen);
         break;
      default:
         break;
      }

      return false;

   }


   bool graphics::_fill_inline(::draw2d_quartz2d::path::matter * pmatter, ::draw2d::brush * pbrush)
   {

      switch(pmatter->m_etype)
      {
      case ::draw2d::path::type_text_out:
         _fill_inline(dynamic_cast < path::text_out * >(pmatter), pbrush);
         break;
      default:
         break;
      }

      return false;

   }

//   bool graphics::_set(const ::draw2d_quartz2d::path::arc & a)
//   {
//
////      cairo_translate(m_pdc, a.m_xCenter, a.m_yCenter);
////
////      cairo_scale(m_pdc, 1.0, a.m_dRadiusY / a.m_dRadiusX);
////
////      cairo_arc(m_pdc, 0.0, 0.0, a.m_dRadiusX, a.m_dAngle1, a.m_dAngle2);
////
////      cairo_scale(m_pdc, 1.0, a.m_dRadiusX / a.m_dRadiusY);
////
////      cairo_translate(m_pdc, -a.m_xCenter, -a.m_yCenter);
//
//      return true;
//
//   }
//
//   bool graphics::set(const ::draw2d_quartz2d::path::line & l)
//   {
//
////      if(!cairo_has_current_point(m_pdc))
////      {
////
////         cairo_move_to(m_pdc, l.m_x, l.m_y);
////
////      }
////      else
////      {
////
////         cairo_line_to(m_pdc, l.m_x, l.m_y);
////
////      }
//
//      return true;
//
//   }
//
//
//   bool graphics::set(const ::draw2d_quartz2d::path::move & p)
//   {
//
////      cairo_move_to(m_pdc, p.m_x, p.m_y);
//
//
//      return true;
//
//   }
//
//   bool graphics::set(const ::draw2d_quartz2d::path::string_path & stringpath)
//   {
//      return true;
//
//   }


   bool graphics::_draw_inline(::draw2d::path::text_out * ptextout, ::draw2d::pen * ppen)
   {

      string str(ptextout->m_strText);

      sync_lock ml(mutex());

      double dx;

      double dy;

      dx = 0.;

      dy = 0.;

      str.replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(ptextout->m_point.x + dx,ptextout->m_point.y + dy + offsety, 0, DT_TOPLEFT, str, kCGTextStroke, true, &ascent, &descent, &leading, &width, ppen, nullptr, ptextout->m_pfont);

         offsety += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }

      }

      return true;

   }


   bool graphics::_fill_inline(::draw2d_quartz2d::path::text_out * ptextout, ::draw2d::brush * pbrush)
   {

      string str(ptextout->m_strText);

      sync_lock ml(mutex());

      double dx;

      double dy;

      dx = 0.;

      dy = 0.;

      str.replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(ptextout->m_point.x + dx, ptextout->m_point.y + dy + offsety, 0, DT_TOPLEFT,  str, kCGTextFill, true, &ascent, &descent, &leading, &width, nullptr, pbrush, ptextout->m_pfont);

         offsety += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }

      }

      return true;

   }


   bool graphics::_draw_inline(::draw2d::path::draw_text * pdrawtext, ::draw2d::pen * ppen)
   {

      string str(pdrawtext->m_strText);

      sync_lock ml(mutex());

      double dx;

      double dy;

      dx = 0.;

      dy = 0.;

      str.replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(pdrawtext->m_rect.left + dx,pdrawtext->m_rect.top + dy + offsety, 0, DT_TOPLEFT, str, kCGTextStroke, true, &ascent, &descent, &leading, &width, ppen, nullptr, pdrawtext->m_pfont);

         offsety += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }

      }

      return true;

   }


   bool graphics::_fill_inline(::draw2d::path::draw_text * pdrawtext, ::draw2d::brush * pbrush)
   {

      string str(pdrawtext->m_strText);

      sync_lock ml(mutex());

      double dx;

      double dy;

      dx = 0.;

      dy = 0.;

      str.replace("\t", "        ");

      string_array stra;

      stra.add_lines(str);

      int offsety = 0;

      CGFloat ascent, descent, leading, width;

      for(auto str : stra)
      {

         internal_show_text(pdrawtext->m_rect.left + dx, pdrawtext->m_rect.top + dy + offsety, 0, DT_TOPLEFT,  str, kCGTextFill, true, &ascent, &descent, &leading, &width, nullptr, pbrush, pdrawtext->m_pfont);

         offsety += ascent + descent + leading;

//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }

      }

      return true;

   }



   bool graphics::_fill()
   {

      return _fill(m_pbrush);

   }


   bool graphics::_draw()
   {

      return _draw(m_ppen);

   }

   void graphics::internal_set_fill_color(const ::color & color)
   {

      CGContextSetRGBFillColor(m_pdc, color.dr(), color.dg(), color.db(), color.da());

   }


   void graphics::enum_fonts(::draw2d::font_enum_item_array & itema)
   {

      char ** p;

      unsigned long c = apple_get_fonts(&p);

      if(c > 0)
      {

         for(unsigned long u = 0; u < c; u++)
         {

            itema.add(__new(::draw2d::font_enum_item(p[u], p[u])));

            free(p[u]);

         }

         free(p);

      }

   }


   bool graphics::draw_text(const string & strParam,const ::rectd & rect, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      string str(strParam);

      sync_lock ml(mutex());

      //double dx;

      //double dy;


      if(nFormat & DT_EXPANDTABS)
      {

         str.replace("\t", "        ");

      }
      else
      {

         str.replace("\t", "");

      }


      double y;

      if(nFormat & e_align_bottom)
      {

         y = rect.bottom;

      }
      else if(nFormat & e_align_vertical_center)
      {

         y = rect.top + ::height(rect) / 2.0;

      }
      else
      {

         y = rect.top;

      }



      if(nFormat & DT_SINGLELINE)
      {

         str.replace("\rect\n", " ");

         str.replace("\n", " ");

         str.replace("\rect", " ");

         internal_show_text(
         rect.left,
         y,
         ::width(rect),
         nFormat,
         str,
         kCGTextFill,
         true,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         nullptr,
         m_pbrush,
         m_pfont);

      }
      else
      {

         string_array stra;

         stra.add_lines(str);

         //CGFloat ascent, descent, leading, width;

         CGFloat ascent, descent, leading;

         if(!(nFormat & e_align_bottom) && ! (nFormat & e_align_vertical_center))
         {

            for(auto str : stra)
            {

               internal_show_text(
               rect.left,
               y,
               ::width(rect),
               nFormat,
               str,
               kCGTextFill,
               true,
               &ascent,
               &descent,
               &leading,
               nullptr,
               nullptr,
               m_pbrush,
               m_pfont);

               y += ascent + descent + leading;

//               if(leading <= 0)
//               {
//
//                  y += descent;
//
//               }

            }

         }
         else if(nFormat & e_align_bottom)
         {

            for(auto str : stra)
            {

               internal_show_text(
               rect.left,
               y,
               ::width(rect),
               nFormat,
               str,
               kCGTextFill,
               true,
               &ascent,
               &descent,
               &leading,
               nullptr,
               nullptr,
               m_pbrush,
               m_pfont);

               y -= ascent + descent + leading;

//                  if(leading <= 0)
//                  {
//
//                     y -= descent;
//
//                  }

            }

         }
         else if(nFormat & e_align_vertical_center)
         {

            rectd rectUpper(rect);

            rectd rectLower(rect);

            rectUpper.bottom = y;

            rectLower.top = y;

            if(stra.get_count() % 2 == 1)
            {

               internal_show_text(
               rect.left,
               y,
               ::width(rect),
               nFormat,
               stra[stra.get_middle_index()],
               kCGTextFill,
               true,
               &ascent,
               &descent,
               &leading,
               nullptr,
               nullptr,
               m_pbrush,
               m_pfont);

               double dy = ascent + descent + leading;

//                  if(leading <= 0)
//                  {
//
//                     dy += descent;
//
//                  }

               rectUpper.bottom -= dy/2.0;

               rectLower.top += dy/2.0;

            }

            if(stra.get_count() >= 2)
            {

               draw_text(
               stra.implode("\n", 0, stra.get_middle_index() + 1),
               rectUpper,
               (nFormat & ~e_align_vertical_center) | e_align_bottom);

               draw_text(
               stra.implode("\n", stra.get_middle_index() + 1),
               rectLower,
               (nFormat & ~e_align_vertical_center) | e_align_top);

            }

         }

      }

      return 1;

   }


   bool graphics::internal_show_text(::draw2d::font_pointer spfont,::draw2d::brush_pointer spbrush,::draw2d::pen_pointer sppen, double x, double y, double wAlign, const ::e_align & ealign, const ::e_draw_text & edrawtext, const string & str, CGTextDrawingMode emode, bool bDraw, CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth)
   {

      sync_lock sl(mutex());

      //CGContextRef pgraphics = m_pdc;

      if(str == "GB18030 Bitmap")
      {
         
         ::output_debug_string("GB18030 Bitmap");
         
      }

      //__pointer(::draw2d_quartz2d::font) f = spfont;
      
      if(!spfont)
      {
         
         return false;
         
      }

      if(str.trimmed().is_empty())
      {

         return true;

      }
      
      CTFontRef pfont = (CTFontRef) spfont->get_os_data(this);

      if(pfont == nullptr)
      {
         
         return false;
         
      }

      bool bFill = false;

      bool bStroke = false;

      color32_t crFill;

      color32_t crStroke;

      ::draw2d::brush * pbrush = nullptr;

      //bool bCacheLine = false;

      if(bDraw)
      {

         if(emode == kCGTextFill || emode == kCGTextFillStroke)
         {

            if(spbrush.is_set() &&
                  (spbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color
                   || spbrush->m_etype == ::draw2d::brush::type_radial_gradient_color
                   || spbrush->m_etype == ::draw2d::brush::type_pattern))
            {

               pbrush = spbrush;

               emode = kCGTextClip;

            }
            else
            {

               bFill = true;

               crFill = spbrush.is_null() ? ARGB(255, 0, 0, 0) : spbrush->m_color.operator unsigned int();

            }

         }

         if(emode == kCGTextStroke|| emode == kCGTextFillStroke)
         {

            bStroke = true;

            crStroke = sppen.is_null() ? ARGB(255, 0, 0, 0) : sppen->m_color.operator color32_t();

         }

      }

      if(!bDraw)
      {

//         auto passoc = f->m_mapMetrics.plookup(str);
//
//         if(passoc != nullptr)
//         {
//
//            ::draw2d_quartz2d::font::metrics & m = passoc->element2();
//
//            m.get(pascent, pdescent, pleading, pwidth);
//
//            return true;
//
//         }

      }
      else if(ansi_scan(str, "0123456789") == nullptr)
      {

//         auto passoc = f->m_mapMetrics.plookup(str);
//
//         if(passoc != nullptr)
//         {
//
//            ::draw2d_quartz2d::font::metrics & m = passoc->element2();
//
//            CTLineRef line = m.m_map[emode][crFill][crStroke];
//
//            if(line != nullptr)
//            {
//
//               m.align(x, y, wAlign, nFormat);
//
//               CGContextSaveGState(pgraphics);
//
//               internal_draw_text(emode, x, y + m.ascent, line, pbrush);
//
//               CGContextRestoreGState(pgraphics);
//
//               m.get(pascent, pdescent, pleading, pwidth);
//
//               return true;
//
//            }
//
//         }

      }

//      ::draw2d_quartz2d::font::metrics & m = f->m_mapMetrics[str];

      CFStringRef stringI = CFStringCreateWithCString(nullptr, str, kCFStringEncodingUTF8);

      if(stringI == nullptr)
      {

         return false;

      }

      CFStringRef string = CFStringCreateMutableCopy(nullptr, 0, stringI);

      if(stringI == nullptr)
      {

         CFRelease(stringI);

         return false;

      }

      //CGContextSaveGState(pgraphics);

      array < CFTypeRef > pkeys;
      
      array < CFTypeRef > pvals;
      
      array < CFTypeRef > cfrel;
      
      array < CGColorRef > crrel;
      
      pkeys.add(kCTFontAttributeName);

      pvals.add(pfont);

      if(spfont->m_bUnderline)
      {

         int iUnderlineStyle = kCTUnderlineStyleSingle;

         CFNumberRef num = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &iUnderlineStyle);

         cfrel.add(num);

         pkeys.add(kCTUnderlineStyleAttributeName);

         pvals.add(num);

      }

      if(emode != kCGTextInvisible && bDraw)
      {

         CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();

         CGFloat components[4];

         if(bFill)
         {

            components[0] = colorref_get_r_value(crFill) / 255.f;
            components[1] = colorref_get_g_value(crFill) / 255.f;
            components[2] = colorref_get_b_value(crFill) / 255.f;
            components[3] = colorref_get_a_value(crFill) / 255.f;

            pkeys.add(kCTForegroundColorAttributeName);
            pvals.add(CGColorCreate(rgbColorSpace, components));
            crrel.add((CGColorRef)pvals.last());

         }

         if(bStroke)
         {

            double dStroke = sppen.is_null() ? 3.0 : sppen->m_dWidth * 100.0 / spfont->m_dFontSize;

            pkeys.add(kCTStrokeWidthAttributeName);
            pvals.add(CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &dStroke));
            cfrel.add(pvals.last());

            components[0] = colorref_get_r_value(crStroke) / 255.f;
            components[1] = colorref_get_g_value(crStroke) / 255.f;
            components[2] = colorref_get_b_value(crStroke) / 255.f;
            components[3] = colorref_get_a_value(crStroke) / 255.f;

            pkeys.add(kCTStrokeColorAttributeName);
            pvals.add(CGColorCreate(rgbColorSpace, components));
            crrel.add((CGColorRef)pvals.last());

         }

         CGColorSpaceRelease(rgbColorSpace);

      }

      
      CFDictionaryRef attributes = CFDictionaryCreate(
                                   kCFAllocatorDefault,
                                   pkeys.get_data(),
                                   pvals.get_data(),
                                   pkeys.get_size(),
                                   &kCFTypeDictionaryKeyCallBacks,
                                   &kCFTypeDictionaryValueCallBacks);

      CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);

      CTLineRef line = CTLineCreateWithAttributedString(attrString);

      CFRelease(string);

      CFRelease(stringI);

      CFRelease(attributes);
      
      CGFloat width;
      
      CGFloat ascent;
      
      CGFloat descent;
      
      CGFloat leading;
      
      width = CTLineGetTypographicBounds(line, &ascent,  &descent, &leading);
                  
      if(bDraw)
      {

         if(nFormat & e_align_right)
         {
            


            x += wAlign - width;
   
         }
         else if(nFormat & e_align_horizontal_center)
         {
   
  
            x += (wAlign - width) / 2.0;
   
         }
   
         if(nFormat & ({ e_align_bottom, e_align_vertical_center }))
         {
   
    

            double cy = -(ascent + descent + leading);
   
            if(leading <= 0)
            {
   
               cy -= descent;
   
            }
   
            if(nFormat & e_align_vertical_center)
            {
   
               cy /= 2.0;
   
            }
   
            y += cy;
   
         }
         
         internal_draw_text(emode, x, y + ascent, line, pbrush);

      }

      if(line)
      {

         CFRelease(line);

      }

      for(index i = 0; i < cfrel.count(); i++)
      {

         CFRelease(cfrel[i]);

      }

      for(index i = 0; i < crrel.count(); i++)
      {

         CGColorRelease(crrel[i]);

      }

      if(pascent)
      {
      
         *pascent = ascent;
         
      }
      
      if(pdescent)
      {
      
         *pdescent = descent;
         
      }
      
      if(pleading)
      {
      
         *pleading = leading;
         
      }
      
      if(pwidth)
      {

         *pwidth = width;
         
      }

      return true;

   }


   void graphics::internal_draw_text(CGTextDrawingMode emode, double x, double y, CTLineRef line, ::draw2d::brush * pbrush)
   {

      sync_lock sl(mutex());
      
      CGContextRef pgraphics = m_pdc;

      // CGContextSetTextMatrix(pgraphics, CGAffineTransformScale(CGAffineTransformMakeTranslation(x, y), 1.f, -1.f));
      //CGContextTranslateCTM(pgraphics, x, y);
      //CGContextScaleCTM(pgraphics, 1.0, -1.0);

      //CGContextSetTextMatrix(pgraphics, CGAffineTransformIdentity);
      CGContextSetTextMatrix(pgraphics, CGAffineTransformScale(CGAffineTransformMakeTranslation(x, y), 1.f, -1.f));
      //CGContextTranslateCTM(pgraphics, x, y);
      //CGContextScaleCTM(pgraphics, 1.0, -1.0);
      // CGContextSetTextMatrix(pgraphics, CGAffineTransformScale(CGAffineTransformMakeTranslation(x, y), 1.f, -1.f));
      
      CGContextSetTextDrawingMode(pgraphics, emode);

      CTLineDraw(line, pgraphics);

      //CGContextScaleCTM(pgraphics, 1.0, -1.0);
      //CGContextTranslateCTM(pgraphics, -x, -y);

      if(pbrush != nullptr)
      {
 
         _fill(pbrush, false);

      }

   }


} // namespace draw2d_quartz2d






CGContextRef CGContextCreate(CGSize size)
{

   CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();

   CGContextRef ctx = CGBitmapContextCreate(nil, size.width, size.height, 8, size.width * (CGColorSpaceGetNumberOfComponents(space) + 1), space, kCGImageAlphaPremultipliedLast);

   CGColorSpaceRelease(space);

   return ctx;

}


