#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/platform/static_start.h"
//#include <math.h>

#define IMAGE_OK(pimpl) (::is_set(pimpl) && pimpl->area() > 0)

#include "nanosvg/nanosvg.h"

CLASS_DECL_AURA image_array * g_pimagea = nullptr;

namespace draw2d
{


   bool word_break(::draw2d::graphics * pgraphics, const string & strSource, const rect & rectParam, string &str1, string & str2, int iEll);


   strsize _EncodeV033(string & str);


   graphics::graphics()
   {

      //m_puserstyle = nullptr;

      //m_bLayoutModified = false;

      m_bOutline = false;

      defer_create_mutex();

      m_puserinteraction         = nullptr;
      m_bPat                     = false;
      m_bStoreThumbnails         = true;
      m_pdrawcontext             = nullptr;
      m_dFontFactor              = 1.0;

   }


   graphics::~graphics()
   {

   }


   bool graphics::prefer_mapped_image_on_mix()
   {

      return false;

   }


   ::apex::str_context * graphics::str_context()
   {
      return m_pstrcontext;
   }

   ::aura::draw_context * graphics::draw_context()
   {
      return m_pdrawcontext;
   }

   bool graphics::is_set()
   {
      return get_os_data() != 0;
   }


   //void *  graphics::get_os_data(int i) const
   //{

   //   return 0;

   //}


   //void graphics::release_os_data_ex(int i, void * p)
   //{

   //}


   bool graphics::attach(void * pdata)
   {



      return false;

   }


   void * graphics::detach()
   {



      return nullptr;

   }


#ifdef WINDOWS_DESKTOP


   bool graphics::attach_hdc(HDC hdc)
   {

      ::exception::throw_not_implemented();

      return false;

   }


   HDC graphics::detach_hdc()
   {

      ::exception::throw_not_implemented();

      return nullptr;

   }


   bool graphics::AttachPrinter(HDC hdc)
   {

      ::exception::throw_not_implemented();

      return false;

   }


   HDC graphics::DetachPrinter()
   {

      ::exception::throw_not_implemented();

      return nullptr;

   }

#endif


   oswindow graphics::get_window_handle() const
   {

      if (!m_puserinteraction)
      {

         return nullptr;

      }

      oswindow oswindow = m_puserinteraction->get_safe_handle();

      if (!oswindow)
      {

         return nullptr;

      }

      return oswindow;

   }


   bool graphics::IsPrinting()
   {



      return false;

   }


   void graphics::thread_select()
   {


   }




   bool graphics::CreateDC(const char * pszDriverName,  const char * pszDeviceName, const char * pszOutput, const void * pInitData)

   {

      UNREFERENCED_PARAMETER(pszDriverName);

      UNREFERENCED_PARAMETER(pszDeviceName);

      UNREFERENCED_PARAMETER(pszOutput);

      UNREFERENCED_PARAMETER(pInitData);



      return false;

   }


   bool graphics::CreateIC(const char * pszDriverName,  const char * pszDeviceName, const char * pszOutput, const void * pInitData)

   {

      UNREFERENCED_PARAMETER(pszDriverName);

      UNREFERENCED_PARAMETER(pszDeviceName);

      UNREFERENCED_PARAMETER(pszOutput);

      UNREFERENCED_PARAMETER(pInitData);



      return false;

   }


   bool graphics::create_memory_graphics()
   {

      if (!CreateCompatibleDC(nullptr))
      {

         return false;

      }

      return true;

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);



      return false;

   }

   bool graphics::CreateWindowDC(oswindow wnd)
   {

      UNREFERENCED_PARAMETER(wnd);



      return false;

   }


   /*   i32 graphics::ExcludeUpdateRgn(::user::interaction_impl * pwindow)
      {
         UNREFERENCED_PARAMETER(pwindow);

      }
      */

   i32 graphics::GetDeviceCaps(i32 nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);


      return -1;

   }

   point graphics::GetBrushOrg()
   {



      return nullptr;

   }


   bool graphics::set_font(::user::interaction* pinteraction, ::user::eelement eelement, ::user::estate estate)
   {

      auto pstyle = pinteraction->get_style(m_puserstyle);

      auto pfont = pinteraction->get_font(pstyle, eelement, estate);

      return set(pfont);

   }


   bool graphics::set_text_color(color color)
   {

      ::draw2d::brush_pointer brush(e_create);

      if (brush.is_null())
      {

         return false;

      }

      brush->create_solid(color);

      return set(brush) != FALSE;

   }


   point graphics::SetBrushOrg(i32 x, i32 y)
   {

      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);


      return nullptr;

   }

   point graphics::SetBrushOrg(const ::point & point)
   {
      UNREFERENCED_PARAMETER(point);



      return nullptr;

   }

/*
   i32 graphics::EnumObjects(i32 nObjectType, i32 (CALLBACK* pfn)(LPVOID, LPARAM), LPARAM pData)

   {
      UNREFERENCED_PARAMETER(nObjectType);
      UNREFERENCED_PARAMETER(pfn);

      UNREFERENCED_PARAMETER(pData);



      return -1;

   }
   */


   ::e_status graphics::set(::draw2d::bitmap* pbitmap)
   {

      if (::is_null(pbitmap))
      {

         return ::error_failed;

      }

      m_pbitmap = pbitmap;

      return ::error_failed;

   }


   ::e_status graphics::set(::draw2d::font * pfont)
   {

      if (::is_null(pfont))
      {

         return ::error_failed;

      }

      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods

      m_pfont = pfont;

      return ::success;

   }


   ::e_status graphics::set(::draw2d::pen * ppen)
   {

      if (::is_null(ppen))
      {

         return ::error_failed;

      }

      m_ppen = ppen;

      return ::success;

   }


   ::e_status graphics::set(::draw2d::brush* pbrush)
   {

      if (::is_null(pbrush))
      {

         return ::error_failed;

      }

      m_pbrush = pbrush;

      return ::success;

   }


   ::e_status graphics::set(::draw2d::region* pregion)
   {

      if (::is_null(pregion))
      {

         return ::error_failed;

      }

      m_pregion = pregion;

      return ::success;

   }


   //color32_t graphics::GetNearestColor(const ::color & colorColor)
   //{

   //   UNREFERENCED_PARAMETER(crColor);

   //   return 0;

   //}


   //::u32 graphics::RealizePalette()
   //{


   //   return -1;

   //}

   //void graphics::UpdateColors()
   //{




   //}


   i32 graphics::GetPolyFillMode()
   {



      return -1;

   }


   i32 graphics::GetROP2()
   {



      return -1;

   }


   i32 graphics::GetStretchBltMode()
   {



      return -1;

   }


   i32 graphics::GetMapMode()
   {



      return -1;

   }


   i32 graphics::GetGraphicsMode()
   {



      return -1;

   }


#ifdef WINDOWS

   bool graphics::GetWorldTransform(XFORM* pXform)
   {
      UNREFERENCED_PARAMETER(pXform);


      return false;

   }

#endif


   point graphics::GetViewportOrg()
   {

      return ::point((::i32)m_matrixViewport.c1, (::i32) m_matrixViewport.c2);

   }


   size graphics::GetViewportExt()
   {



      return ::size(0, 0);

   }


   point graphics::GetWindowOrg()
   {



      return nullptr;

   }


   size graphics::GetWindowExt()
   {



      return ::size(0, 0);

   }


   point graphics::SetViewportOrg(const ::point & point)
   {

      return SetViewportOrg(point.x, point.y);

   }


   size graphics::SetViewportExt(const ::size & size)
   {

      UNREFERENCED_PARAMETER(size);



      return ::size(0, 0);

   }


   point graphics::SetWindowOrg(const ::point & point)
   {

      UNREFERENCED_PARAMETER(point);



      return nullptr;

   }


   size graphics::SetWindowExt(const ::size & size)
   {

      UNREFERENCED_PARAMETER(size);



      return ::size(0, 0);

   }


   void graphics::DPtoLP(POINT32 * ppoints, count nCount)

   {

      UNREFERENCED_PARAMETER(ppoints);


      UNREFERENCED_PARAMETER(nCount);



   }


   void graphics::DPtoLP(RECT32 * rect)

   {
      UNREFERENCED_PARAMETER(rect);


   }

   void graphics::LPtoDP(POINT32 * ppoints, count nCount)

   {
      UNREFERENCED_PARAMETER(ppoints);

      UNREFERENCED_PARAMETER(nCount);

   }

   void graphics::LPtoDP(RECT32 * rect)

   {
      UNREFERENCED_PARAMETER(rect);


   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);


      return false;
   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);

      return false;
   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);

      return false;

   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);

      return false;
   }

//   bool graphics::PtVisible(i32 x, i32 y)
//   {
//      UNREFERENCED_PARAMETER(x);
//      UNREFERENCED_PARAMETER(y);
//
//
//      return false;
//   }
//
//   bool graphics::PtVisible(const ::point & point)
//   {
//      UNREFERENCED_PARAMETER(point);
//
//
//      return false;
//   }


//   bool graphics::RectVisible(const ::rect & rect)
//   {
//
//      UNREFERENCED_PARAMETER(rect);
//
//
//
//      return false;
//   }


   pointd graphics::current_position()
   {

      return m_point;

   }


   bool graphics::move_to(const ::point & point)

   {

      return move_to(pointd(point));


   }


   bool graphics::move_to(const pointd & point)

   {

      m_point = point;


      return true;

   }


   bool graphics::line_to(const ::point & point)

   {

      return line_to(pointd(point));


   }


   bool graphics::line_to(const pointd & point)
   {

      return line_to(::point(point));

   }


   bool graphics::draw_line(const point & point1, const point & point2)
   {

      return draw_line(point1, point2, m_ppen);

   }


   bool graphics::draw_line(const point & point1, const point & point2, ::draw2d::pen * ppen)
   {

      return draw_line(pointd(point1), pointd(point2), ppen);

   }


   bool graphics::draw_line(const pointd & point1, const pointd & point2)
   {

      return draw_line(point1, point2, m_ppen);

   }


   bool graphics::draw_line(const pointd & point1, const pointd & point2, ::draw2d::pen * ppen)
   {

      return draw_line(point(point1), point(point2), ppen);

   }


   bool graphics::rectangle(const rect & rect)
   {

      return rectangle(rectd(rect));

   }


   bool graphics::rectangle(const rectd & rect)
   {

      return rectangle(::rect(rect));

   }


   bool graphics::draw_rect(const ::rect & rect)
   {

      return draw_rect(rectd(rect), m_ppen);

   }


   bool graphics::draw_rect(const rectd & rect)
   {

      return draw_rect(::rect(rect), m_ppen);

   }


   bool graphics::draw_rect(const ::rect & rect, ::draw2d::pen * ppen)
   {

      return draw_rect(rectd(rect), ppen);

   }


   bool graphics::draw_rect(const rectd & rect, ::draw2d::pen * ppen)
   {

      return draw_rect(::rect(rect), ppen);

   }


   bool graphics::fill_rect(const ::rect & rect)
   {

      return fill_rect(rect, m_pbrush);

   }


   bool graphics::fill_rect(const rectd & rect)
   {

      return fill_rect(rect, m_pbrush);

   }


   bool graphics::fill_rect(const ::rect & rect, ::draw2d::brush * pbrush)
   {

      return fill_rect(rectd(rect), pbrush);

   }


   bool graphics::fill_rect(const rectd & rect, ::draw2d::brush * pbrush)
   {

      return fill_rect(::rect(rect), pbrush);

   }


   bool graphics::Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {

      int x = (x1 + x2)/2;

      int y = (y1 + y2)/2;

      return Arc(x1, y1, x2 - x1, y2 - y1, atan2(x3 - x, y3 - y), atan2(x4 - x, y4 - y));

   }


   bool graphics::Arc(const ::rect & rect, const point & pointStart, const point & pointEnd)
   {

      return Arc(rect.left, rect.top, rect.width(), rect.height(), pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);

   }


   bool graphics::Arc(i32 x1, i32 y1, i32 w, i32 h, angle start, angle extends)
   {

//      ::point pointCenter;
//
//      pointCenter.x = x1 + w / 2;
//      pointCenter.y = y1 + h / 2;
//
//      double dx = w / 2.0;
//      double dy = h / 2.0;
//
//      double startx = (cos(start * System.math().GetPi() / 180.0) * dx) + pointCenter.x;
//      double starty = (sin(start * System.math().GetPi() / 180.0) * dy) + pointCenter.y;
//
//      double endx = (cos((start + extends) * System.math().GetPi() / 180.0) * dx) + pointCenter.x;
//      double endy = (sin((start + extends) * System.math().GetPi() / 180.0) * dy) + pointCenter.y;

      return Arc((double)x1, (double)y1, (double)w, (double)h, start, extends);

   }


   bool graphics::Arc(const ::rect & rect, angle start, angle extends)
   {

      return Arc(rect.left, rect.top, rect.width(), rect.height(), start, extends);

   }



   bool graphics::Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      double x = (x1 + x2)/2.0;

      double y = (y1 + y2)/2.0;;

      return Arc(x1, y1, x2 - x1, y2 - y1, atan2(x3 - x, y3 - y), atan2(x4 - x, y4 - y));

   }


   bool graphics::Arc(const rectd & rect, const pointd & pointStart, const pointd& pointEnd)
   {

      return Arc(rect.left, rect.top, rect.width(), rect.height(), pointStart.x, pointStart.y, pointEnd.x, pointEnd.y);

   }


   bool graphics::Arc(double x1, double y1, double w, double h, angle start, angle extends)
   {

      pointd pointCenter;

      pointCenter.x = x1 + w / 2.0;
      pointCenter.y = y1 + h / 2.0;

      double dx = w / 2.0;
      double dy = h / 2.0;

      double startx = cos(start.radian()) * dx + pointCenter.x;
      double starty = sin(start.radian()) * dy + pointCenter.y;

      double endx = cos(start.radian() + extends.radian()) * dx + pointCenter.x;
      double endy = sin(start.radian() + extends.radian()) * dy + pointCenter.y;

      return Arc(x1, y1, x1 + w, y1 + h, startx, starty, endx, endy);

   }


   bool graphics::Arc(const ::rectd & rect, angle start, angle extends)
   {

      return Arc(rect.left, rect.top, rect.right, rect.bottom, start, extends);

   }


   bool graphics::Polyline(const POINT32 * ppoints, count nCount)
   {

      UNREFERENCED_PARAMETER(ppoints);

      UNREFERENCED_PARAMETER(nCount);



      return false;

   }


   void graphics::frame_rect(const ::rect & rect, ::draw2d::brush * pbrush)

   {

      UNREFERENCED_PARAMETER(rect);


      UNREFERENCED_PARAMETER(pbrush);



   }


   void graphics::invert_rect(const ::rect & rect)

   {

      UNREFERENCED_PARAMETER(rect);




   }


   bool graphics::draw(const ::rect & rectDst, icon * picon)
   {

      return draw(rectDst, picon->get_image(rectDst.size()));

   }




//
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, HBITMAP hBitmap, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      UNREFERENCED_PARAMETER(point);
//      UNREFERENCED_PARAMETER(size);
//      UNREFERENCED_PARAMETER(hBitmap);
//      UNREFERENCED_PARAMETER(nFlags);
//      UNREFERENCED_PARAMETER(hBrush);
//
//
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, ::draw2d::bitmap* pBitmap, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      UNREFERENCED_PARAMETER(point);
//      UNREFERENCED_PARAMETER(size);
//      UNREFERENCED_PARAMETER(pBitmap);
//      UNREFERENCED_PARAMETER(nFlags);
//      UNREFERENCED_PARAMETER(pBrush);
//
//
//      return false;
//   }
//
//#ifdef WINDOWS
//
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      UNREFERENCED_PARAMETER(point);
//      UNREFERENCED_PARAMETER(size);
//      UNREFERENCED_PARAMETER(hIcon);
//      UNREFERENCED_PARAMETER(nFlags);
//      UNREFERENCED_PARAMETER(hBrush);
//
//
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, HICON hIcon, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      UNREFERENCED_PARAMETER(point);
//      UNREFERENCED_PARAMETER(size);
//      UNREFERENCED_PARAMETER(hIcon);
//      UNREFERENCED_PARAMETER(nFlags);
//      UNREFERENCED_PARAMETER(pBrush);
//
//
//      return false;
//
//   }
//
//#endif


//   bool graphics::DrawState(const ::point & point, const ::size & size, const char * pszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen)
//   {
//
//      UNREFERENCED_PARAMETER(point);
//      UNREFERENCED_PARAMETER(size);
//      UNREFERENCED_PARAMETER(pszText);
//
//      UNREFERENCED_PARAMETER(nFlags);
//      UNREFERENCED_PARAMETER(bPrefixText);
//      UNREFERENCED_PARAMETER(nTextLen);
//      UNREFERENCED_PARAMETER(hBrush);
//
//
//      return false;
//
//   }


//   bool graphics::DrawState(const ::point & point, const ::size & size, const char * pszText, ::u32 nFlags, bool bPrefixText, i32 nTextLen, ::draw2d::brush* pBrush)
//   {
//
//      UNREFERENCED_PARAMETER(point);
//      UNREFERENCED_PARAMETER(size);
//      UNREFERENCED_PARAMETER(pszText);
//
//      UNREFERENCED_PARAMETER(nFlags);
//      UNREFERENCED_PARAMETER(bPrefixText);
//      UNREFERENCED_PARAMETER(nTextLen);
//      UNREFERENCED_PARAMETER(pBrush);
//
//
//      return false;
//
//
//   }
//
//
//#ifdef WINDOWS_DESKTOP
//
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC pDrawProc, LPARAM lData, ::u32 nFlags, HBRUSH hBrush)
//   {
//
//      UNREFERENCED_PARAMETER(point);
//      UNREFERENCED_PARAMETER(size);
//      UNREFERENCED_PARAMETER(pDrawProc);
//
//      UNREFERENCED_PARAMETER(lData);
//      UNREFERENCED_PARAMETER(nFlags);
//      UNREFERENCED_PARAMETER(hBrush);
//
//
//      return false;
//
//   }
//
//
//   bool graphics::DrawState(const ::point & point, const ::size & size, DRAWSTATEPROC pDrawProc, LPARAM lData, ::u32 nFlags, ::draw2d::brush* pBrush)
//   {
//
//      UNREFERENCED_PARAMETER(point);
//      UNREFERENCED_PARAMETER(size);
//      UNREFERENCED_PARAMETER(pDrawProc);
//
//      UNREFERENCED_PARAMETER(lData);
//      UNREFERENCED_PARAMETER(nFlags);
//      UNREFERENCED_PARAMETER(pBrush);
//
//
//      return false;
//
//   }
//
//
//#endif


//   bool graphics::DrawEdge(const rect & rect, ::u32 nEdge, ::u32 nFlags)
//   {
//
//      UNREFERENCED_PARAMETER(rect);
//      UNREFERENCED_PARAMETER(nEdge);
//      UNREFERENCED_PARAMETER(nFlags);
//
//
//      return false;
//
//   }
//
//
//   bool graphics::DrawFrameControl(const rect & rect, ::u32 nType, ::u32 nState)
//   {
//
//      UNREFERENCED_PARAMETER(rect);
//      UNREFERENCED_PARAMETER(nType);
//      UNREFERENCED_PARAMETER(nState);
//
//
//
//      return false;
//
//   }


   bool graphics::Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {

      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);



      return false;

   }


   bool graphics::Chord(const rect & rect, const point & pointStart, const point & pointEnd)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(pointStart);
      UNREFERENCED_PARAMETER(pointEnd);



      return false;

   }


   void graphics::DrawFocusRect(const rect & rect)
   {

      UNREFERENCED_PARAMETER(rect);



   }


   //bool graphics::ellipse(i32 x1, i32 y1, i32 x2, i32 y2)
   //{

   //   bool bFill = fill_ellipse(x1, y1, x2, y2);

   //   bool bDraw = draw_ellipse(x1, y1, x2, y2);

   //   return bFill && bDraw;

   //}


   bool graphics::ellipse(const rectd &  rect)
   {

      auto ealphamode = m_ealphamode;

      set_alpha_mode(alpha_mode_blend);

      bool bFill = fill_ellipse(rect);

      bool bDraw = draw_ellipse(rect);

      set_alpha_mode(ealphamode);

      return bFill && bDraw;

   }


   //bool graphics::draw_ellipse(i32 x1, i32 y1, i32 x2, i32 y2)
   //{

   //   ::rectd rect(x1, y1, x2, y2);

   //   return draw_ellipse(rect);

   //}


   //bool graphics::draw_ellipse(const rect & rect)
   //{

   //   return draw_ellipse((double)rect.left, (double)rect.top, (double)rect.right,(double) rect.bottom);

   //}


   //bool graphics::fill_ellipse(i32 x1, i32 y1, i32 x2, i32 y2)
   //{

   //   ::rectd rect(x1, y1, x2, y2);

   //   return FillEllipse(rect);

   //}


   //bool graphics::fill_ellipse(const rectd &  rect)
   //{

   //   return FillEllipse((double)rect.left, (double)rect.top, (double)rect.right,(double) rect.bottom);

   //}


   bool graphics::ellipse(double x1, double y1, double x2, double y2)
   {

      bool bFill = fill_ellipse(x1, y1, x2, y2);

      bool bDraw = draw_ellipse(x1, y1, x2, y2);

      return bFill && bDraw;

   }


   //bool graphics::Ellipse(const ::rectd & rect)
   //{

   //   bool bFill = FillEllipse(rect);

   //   bool bDraw = draw_ellipse(rect);

   //   return bFill && bDraw;

   //}


   bool graphics::draw_ellipse(double x1, double y1, double x2, double y2)
   {

      ::rectd rect(x1, y1, x2, y2);

      return draw_ellipse(rect);

   }


   bool graphics::draw_ellipse(const ::rectd & rect)
   {

      return draw_ellipse(rect.left, rect.top, rect.right, rect.bottom);

//      return true;

   }


   bool graphics::fill_ellipse(double x1, double y1, double x2, double y2)
   {

      ::rectd rect(x1, y1, x2, y2);

      return fill_ellipse(rect);

   }


   bool graphics::fill_ellipse(const ::rectd & rect)
   {

      UNREFERENCED_PARAMETER(rect);



      return false;

   }


   bool graphics::Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {

      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);



      return false;

   }


   bool graphics::Pie(const rect & rect, const point & pointStart, const point & pointEnd)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(pointStart);
      UNREFERENCED_PARAMETER(pointEnd);



      return false;

   }


   bool graphics::fill_polygon(const POINTD * ppoints, count nCount)

   {

      point_array pointa;

      ::papaya::array::copy_points(pointa, ppoints, nCount);


      return draw_polygon(pointa.get_data(), pointa.get_count());

   }


   bool graphics::draw_polygon(const POINTD * ppoints, count nCount)

   {

      point_array pointa;

      ::papaya::array::copy_points(pointa, ppoints, nCount);


      return draw_polygon(pointa.get_data(), pointa.get_count());

   }


   bool graphics::fill_polygon(const POINT32 * ppoints, count nCount)

   {

      pointd_array pointa;

      ::papaya::array::copy_points(pointa, ppoints, nCount);


      return fill_polygon(pointa.get_data(), pointa.get_count());

   }


   bool graphics::draw_polygon(const POINT32 * ppoints, count nCount)

   {

      pointd_array pointa;

      ::papaya::array::copy_points(pointa, ppoints, nCount);


      return draw_polygon(pointa.get_data(), pointa.get_count());

   }


   bool graphics::polygon(const POINT32 * ppoints, count nCount)
   {

      bool bOk1 = fill_polygon(ppoints, nCount);

      bool bOk2 = draw_polygon(ppoints, nCount);

      return bOk1 && bOk2;

   }


   bool graphics::polygon(const POINTD * ppoints, count nCount)
   {

      bool bOk1 = fill_polygon(ppoints, nCount);

      bool bOk2 = draw_polygon(ppoints, nCount);

      return bOk1 && bOk2;

   }


   bool graphics::poly_polygon(const POINT32 * ppoints, const i32 * pPolyCounts, count nCount)
   {

      bool bOk1 = fill_poly_polygon(ppoints, pPolyCounts, nCount);

      bool bOk2 = draw_poly_polygon(ppoints, pPolyCounts, nCount);

      return bOk1 && bOk2;

   }

   bool graphics::poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount)
   {

      bool bOk1 = fill_poly_polygon(ppoints, pPolyCounts, nCount);

      bool bOk2 = draw_poly_polygon(ppoints, pPolyCounts, nCount);

      return bOk1 && bOk2;

   }


   bool graphics::draw_poly_polygon(const POINT32 * ppoints, const i32 * pPolyCounts, count nCount)
   {

      bool bOk = true;

      for(int i = 0; i < nCount; i++)
      {

         if (!draw_polygon(ppoints, *pPolyCounts))
         {

            bOk = false;

         }

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      return bOk;

   }


   bool graphics::draw_poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount)
   {

      bool bOk = true;

      for (int i = 0; i < nCount; i++)
      {

         if (!draw_polygon(ppoints, *pPolyCounts))
         {

            bOk = false;

         }

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      return bOk;

   }


   bool graphics::fill_poly_polygon(const POINT32 * ppoints, const i32 * pPolyCounts, count nCount)
   {

      bool bOk = true;

      for (int i = 0; i < nCount; i++)
      {

         if (!fill_polygon(ppoints, *pPolyCounts))
         {

            bOk = false;

         }

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      return bOk;

   }


   bool graphics::fill_poly_polygon(const POINTD * ppoints, const i32 * pPolyCounts, count nCount)
   {

      bool bOk = true;

      for (int i = 0; i < nCount; i++)
      {

         if (!fill_polygon(ppoints, *pPolyCounts))
         {

            bOk = false;

         }

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      return bOk;

   }


   bool graphics::round_rect(const ::rect & rect, const point & point)
   {

      return round_rect(::rectd(rect), ::pointd(point));

   }


   bool graphics::round_rect(const rectd & rect, const pointd & point)
   {

      return round_rect(::rect(rect), ::point(point));

   }

   
   bool graphics::draw(const ::point & point, cursor * pcursor)
   {
   
      set_alpha_mode(::draw2d::alpha_mode_blend);

      ::point pointDst(point - pcursor->m_szHotspotOffset);

      auto pimage = pcursor->m_pimage;

      return draw(::rect(pointDst, pimage->size()), pimage->g());

   }


   //bool graphics::PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight)
   //{

   //   UNREFERENCED_PARAMETER(x);
   //   UNREFERENCED_PARAMETER(y);
   //   UNREFERENCED_PARAMETER(nWidth);
   //   UNREFERENCED_PARAMETER(nHeight);

   //   return false;

   //}


   //bool graphics::draw_image(const ::rect & rect, ::image * pimage, const ::point & point)
   //{

   //   pimage->defer_update_image();

   //   return draw(rect, pimage->g(), point);

   //}

   
   bool graphics::draw_at(const ::point & pointDst, ::image * pimage)
   {

      return draw(::rect(pointDst, pimage->get_size()), pimage->g());

   }


   bool graphics::draw_at(const ::point & pointDst, ::image_frame * pframe)
   {

      return draw_at(pointDst, pframe->m_pimage);

   }


   bool graphics::draw_at(const ::point & pointDst, ::draw2d::graphics * pgraphics)
   {

      return draw_at(pointDst, pgraphics->m_pimage);

   }


   bool graphics::draw(::image * pimage, const ::point & pointSrc)
   {

      return draw(::rect(::point(), pimage->get_size() - pointSrc), pimage, pointSrc);

   }


   bool graphics::draw(::image_frame * pframe, const ::point & pointSrc)
   {

      return draw(pframe->m_pimage, pointSrc);

   }


   bool graphics::draw(::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc)
   {

      return draw(pgraphicsSrc->m_pimage, pointSrc);

   }

   
   bool graphics::draw(const ::rect & rectDst, ::image * pimage, const ::point & pointSrc)
   {

      return draw(rectDst, pimage->g(), pointSrc);

   }


   bool graphics::draw(const ::rect & rectDst, ::image_frame * pframe, const ::point & pointSrc)
   {

      return draw(rectDst, pframe->m_pimage, pointSrc);

   }


   bool graphics::draw(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc)
   {

      if (::is_null(pgraphicsSrc))
      {

         return false;

      }

      if (draw_blend(rectDst, pgraphicsSrc, pointSrc))
      {

         return true;

      }

      if (draw_raw(rectDst, pgraphicsSrc, pointSrc))
      {

         return true;

      }

      return false;

   }


   bool graphics::draw_raw(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc)
   {

      return false;

   }


   bool graphics::draw_blend(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc)
   {

      return false;

   }


   bool graphics::stretch_raw(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc)
   {

      return false;

   }


   bool graphics::stretch_blend(const ::rect & rectDstParam, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrcParam)
   {

      //::rect rectDst(rectDstParam);

      //::rect rectSrc(rectSrcParam);

      //if (m_pimageAlphaBlend)
      //{

      //   if (rectDst.left < 0)
      //   {

      //      rectSrc.left -= rectDst.left;

      //      rect.right += rect.left;

      //      rect.left = 0;

      //   }

      //   if (rect.top < 0)
      //   {

      //      point.y -= rect.top;

      //      rect.bottom += rect.top;

      //      rect.top = 0;

      //   }

      //   ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->get_size());

      //   if (rectIntersect.intersect(rectIntersect, rect))
      //   {

      //      // The following commented out code does not work well when there is clipping
      //      // and some calculations are not precise
      //      //if (m_pimage != nullptr && pgraphicsSrc->m_pimage != nullptr)
      //      //{

      //      //   const ::point & pointOff = GetViewportOrg();

      //      //   x += pointOff.x;

      //      //   y += pointOff.y;

      //      //   return m_ppimage->blend(::point(x, y), pgraphicsSrc->m_pimage, ::point(xSrc, ySrc), m_pimageAlphaBlend, point(m_pointAlphaBlend.x - x, m_pointAlphaBlend.y - y), rectBlt.size());

      //      //}
      //      //else
      //      {

      //         ::image_pointer pimage1;
      //         //#ifdef _UWP
      //         //               g_pimagea.add(pimage1);
      //         //#endif

      //         pimage1 = create_image(rect.size());

      //         pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      //         if (!pimage1->from(nullptr, pgraphicsSrc, point, rect.size()))
      //            return false;

      //         pimage1->blend(::point(), m_pimageAlphaBlend,
      //            {
      //               (int)max(0, rect.left - m_pointAlphaBlend.x),
      //               (int)max(0, rect.top - m_pointAlphaBlend.y)
      //            }, rect.size());

      //         draw_image(rect, pimage1->get_graphics());

      //      }

      //      return true;

      //   }



      //}

      return false;

   }


   //bool graphics::draw_image(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc)
   //{

   //   if(pgraphicsSrc == nullptr)
   //   {

   //      return false;

   //   }

   //   ::image_pointer pimage = pgraphicsSrc->m_pimage;

   //   if(pimage->is_null())
   //   {

   //      return false;

   //   }

   //   ::rect rectSrc(nullptr, pimage->get_size());

   //   return draw_image(rectDst, pgraphicsSrc, rectSrc);

   //}


   bool graphics::stretch(const ::rect & rectDst, ::image * pimage, const ::rect & rectSrc)
   {

      return stretch(rectDst, pimage->g(), rectSrc.is_null() ? pimage->rect() : rectSrc);

   }


   bool graphics::stretch(const ::rect & rectDst, ::image_frame * pframe, const ::rect & rectSrc)
   {

      return stretch(rectDst, pframe->m_pimage, rectSrc);

   }


   bool graphics::stretch(const ::rect & rectDst, ::draw2d::graphics * pgraphicsSrc, const ::rect & rectSrc)
   {

      if (stretch_blend(rectDst, pgraphicsSrc, rectSrc))
      {

         return true;

      }

      if (stretch_raw(rectDst, pgraphicsSrc, rectSrc))
      {

         return true;

      }

      return false;

   }


   //bool graphics::StretchBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight)
   //{

   //   if (StretchBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight))
   //   {

   //      return true;

   //   }

   //   if (StretchBltRaw(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight))
   //   {

   //      return true;

   //   }

   //   return false;

   //}


   //bool graphics::StretchBlt(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight)
   //{

   //   if (StretchBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight))
   //   {

   //      return true;

   //   }

   //   if (StretchBltRaw(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight))
   //   {

   //      return true;

   //   }

   //   return false;

   //}


   //bool graphics::StretchBltAlphaBlend(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight)
   //{

   //   return StretchBltAlphaBlend(
   //          (double)xDst,
   //          (double)yDst,
   //          (double)nDstWidth,
   //          (double)nDstHeight,
   //          pgraphicsSrc,
   //          xSrc,
   //          ySrc,
   //          nSrcWidth,
   //          nSrcHeight);

   //}


   //bool graphics::StretchBltAlphaBlend(double xDst, double yDst, double nDstWidth, double nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight)
   //{

   //   if (m_pimageAlphaBlend->is_ok())
   //   {



   //      ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->get_size());

   //      ::rect rectBlt(point((::i32)xDst, (::i32)yDst), size((::i32)nDstWidth, (::i32)nDstHeight));

   //      if (rectIntersect.intersect(rectIntersect, rectBlt))
   //      {

   //         ::point pointSrc(xSrc, ySrc);
   //         ::point pointDst((::i32)xDst, (::i32)yDst);
   //         ::size sizeSrc(nSrcWidth, nSrcHeight);
   //         ::size sizeDst((::i32)nDstWidth, (::i32)nDstHeight);

   //         //::image_pointer pimage1 = create_image(sizeDst);

   //         //if (!pimage1)
   //         //{

   //         //   return false;

   //         //}

   //         //if (!pimage1->g()->StretchBltRaw(0.0, 0.0, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight))
   //         //{

   //         //   return false;

   //         //}

   //         //::image_pointer pimage2 = create_image(sizeDst);

   //         //if (!pimage2)
   //         //{

   //         //   return false;

   //         //}

   //         //pimage2->fill(255, 0, 0, 0);

   //         //pimage2->from(point((::i32)max(0, m_pointAlphaBlend.x - xDst), (::i32)max(0, m_pointAlphaBlend.y - yDst)),
   //         //            m_pimageAlphaBlend->g(), point((::i32)max(0, xDst - m_pointAlphaBlend.x), (::i32)max(0, yDst - m_pointAlphaBlend.y)), sizeDst);

   //         //pimage1->channel_multiply(::color::channel_alpha, pimage2);

   //         //BitBltRaw(pointDst.x, pointDst.y, sizeDst.cx, sizeDst.cy, pimage1->get_graphics(), pointSrc.x, pointSrc.y);

   //         auto pimage1 = create_image({::size(nSrcWidth,  nSrcHeight)});

   //         pimage1->g()->set_alpha_mode(::draw2d::alpha_mode_set);

   //         pimage1->from(nullptr, pgraphicsSrc, ::point(xSrc, ySrc), ::size(nSrcWidth, nSrcHeight));

   //         pimage1->blend2(::point(), m_pimageAlphaBlend, ::point((::i32)(xDst-m_pointAlphaBlend.x), (::i32)(yDst-m_pointAlphaBlend.y)), ::size(nSrcWidth, nSrcHeight), 255);

   //         StretchBltRaw(xDst, yDst, nDstWidth, nDstHeight, pimage1->g(), 0, 0, nSrcWidth, nSrcHeight);

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   //bool graphics::StretchBltRaw(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight)
   //{

   //   return StretchBltRaw(
   //          (double)xDst,
   //          (double)yDst,
   //          (double)nDstWidth,
   //          (double)nDstHeight,
   //          pgraphicsSrc,
   //          xSrc,
   //          ySrc,
   //          nSrcWidth,
   //          nSrcHeight);

   //}


   //bool graphics::StretchBltRaw(double x, double y, double nWidth, double nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight)
   //{

   //   return false;

   //}


   ::color graphics::GetPixel(i32 x, i32 y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);

      return 0;
   }


   ::color graphics::GetPixel(const ::point & point)
   {

      UNREFERENCED_PARAMETER(point);

      return 0;

   }


   ::color graphics::SetPixel(i32 x, i32 y, const ::color & color)
   {

      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(color);

      return 0;

   }


   ::color graphics::SetPixel(const ::point & point, const ::color& color)
   {

      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(color);

      return 0;

   }


   ::color graphics::blend_pixel(const ::point& point, const ::color& color)
   {

      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(color);

      return 0;

   }


//   bool graphics::FloodFill(i32 x, i32 y, const ::color& color)
//   {
//
//      UNREFERENCED_PARAMETER(x);
//      UNREFERENCED_PARAMETER(y);
//      UNREFERENCED_PARAMETER(color);
//
//      return false;
//
//   }
//
//
//   bool graphics::ExtFloodFill(i32 x, i32 y, const ::color& color, ::u32 nFillType)
//   {
//
//      UNREFERENCED_PARAMETER(x);
//      UNREFERENCED_PARAMETER(y);
//      UNREFERENCED_PARAMETER(color);
//      UNREFERENCED_PARAMETER(nFillType);
//
//      return false;
//
//   }


   bool graphics::text_out(i32 x, i32 y, const char * pszString, strsize nCount)
   {

      return text_out((double)x, (double)y, pszString, nCount);


   }


   bool graphics::text_out(i32 x, i32 y, const string & str)
   {

      return text_out((double) x, (double) y, str);

   }


   bool graphics::text_out(double x, double y, const char* pszString, strsize nCount)
   {

      return text_out(x, y, string(pszString, nCount));

   }


   bool graphics::text_out(double x, double y, const string & str)
   {

      if (m_pimageAlphaBlend)
      {

         if (TextOutAlphaBlend(x, y, str))
         {

            return true;

         }

      }

      if (TextOutRaw(x, y, str))
      {

         return true;

      }

      return false;

   }


   bool graphics::TextOutRaw(double x, double y, const string & str)
   {

      return false;

   }


   bool graphics::TextOutAlphaBlend(double x, double y, const string &str)
   {

      ASSERT(m_pimageAlphaBlend->is_ok());
      ASSERT(str.has_char());

      single_lock sl(mutex());

      // "Reference" implementation for TextOutAlphaBlend

      ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->get_size());

      const ::size & size = ::size(GetTextExtent(str));


      //size.cx = size.cx * 110 / 100;

      //size.cy = size.cy * 110 / 100;

      ::rect rectText(point((::i32)x, (::i32)y), size);

      if (rectIntersect.intersect(rectIntersect, rectText))
      {

         ::image_pointer pimage1;
//#ifdef _UWP
//            g_pimagea.add(pimage1);
//#endif

         pimage1 = create_image(rectText.size());

         pimage1->get_graphics()->set(get_current_font());

         pimage1->get_graphics()->set(get_current_brush());

         pimage1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

         pimage1->get_graphics()->text_out(0, 0, str);

         pimage1->blend(nullptr, m_pimageAlphaBlend, point((int)max(0, x - m_pointAlphaBlend.x), (int)max(0, y - m_pointAlphaBlend.y)), rectText.size());

         stretch({ {(int)x, (int)y}, rectText.size() }, pimage1->get_graphics());

         return true;

      }

      return false;

   }


   bool graphics::ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect, const char * pszString, strsize nCount, i32 * pDxWidths)
   {

      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(pszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(pDxWidths);


      return false;
   }

   bool graphics::ExtTextOut(i32 x, i32 y, ::u32 nOptions, const ::rect & rect, const string & str, i32 * pDxWidths)

   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(pDxWidths);


      return false;
   }

   size graphics::TabbedTextOut(i32 x, i32 y, const char * pszString, strsize nCount, count nTabPositions, i32 * pnTabStopPositions, int nTabOrigin)

   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(pszString);

      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(pnTabStopPositions);
      UNREFERENCED_PARAMETER(nTabOrigin);


      return size(0, 0);
   }

   size graphics::TabbedTextOut(i32 x, i32 y, const string & str, count nTabPositions, i32 * pnTabStopPositions, int nTabOrigin)

   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(pnTabStopPositions);

      UNREFERENCED_PARAMETER(nTabOrigin);

      return size(0, 0);
   }

   size graphics::GetTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, i32 * pnTabStopPositions)

   {
      UNREFERENCED_PARAMETER(pszString);

      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(pnTabStopPositions);


      return size(0, 0);
   }


   size graphics::GetTabbedTextExtent(const string & str, count nTabPositions, i32 * pnTabStopPositions)

   {

      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(pnTabStopPositions);



      return size(0, 0);

   }


   size graphics::GetOutputTabbedTextExtent(const char * pszString, strsize nCount, count nTabPositions, i32 * pnTabStopPositions)
   {

      UNREFERENCED_PARAMETER(pszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(pnTabStopPositions);



      return size(0, 0);

   }


   size graphics::GetOutputTabbedTextExtent(const string & str, count nTabPositions, i32 * pnTabStopPositions)

   {

      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(pnTabStopPositions);



      return size(0, 0);

   }


//   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* pfnOutput)(HDC, LPARAM, i32), LPARAM pData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight)
//   {
//
//      UNREFERENCED_PARAMETER(pBrush);
//      UNREFERENCED_PARAMETER(pfnOutput);
//      UNREFERENCED_PARAMETER(pData);
//      UNREFERENCED_PARAMETER(nCount);
//      UNREFERENCED_PARAMETER(x);
//      UNREFERENCED_PARAMETER(y);
//      UNREFERENCED_PARAMETER(nWidth);
//      UNREFERENCED_PARAMETER(nHeight);
//
//      return false;
//   }

   ::u32 graphics::GetTextAlign()
   {

      return -1;
   }

   i32 graphics::GetTextFace(count nCount, char * pszFacename)

   {
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(pszFacename);


      return -1;
   }

   i32 graphics::GetTextFace(string & rString)
   {
      UNREFERENCED_PARAMETER(rString);

      return -1;
   }


   text_metric graphics::get_text_metrics()
   {

      text_metric metrics;

      get_text_metrics(&metrics);

      return metrics;

   }


   bool graphics::get_text_metrics(text_metric * pMetrics)
   {

      UNREFERENCED_PARAMETER(pMetrics);

      return false;

   }


   bool graphics::get_output_text_metrics(text_metric * pMetrics)
   {

      UNREFERENCED_PARAMETER(pMetrics);

      return false;

   }


   // ::draw2d::graphics_pointer 3.1 Specific functions
   ::u32 graphics::SetBoundsRect(const rect &  pRectBounds, ::u32 flags)
   {

      UNREFERENCED_PARAMETER(pRectBounds);

      UNREFERENCED_PARAMETER(flags);

      return -1;

   }


   ::u32 graphics::GetBoundsRect(RECT32 * pRectBounds, ::u32 flags)
   {

      UNREFERENCED_PARAMETER(pRectBounds);

      UNREFERENCED_PARAMETER(flags);

      return -1;

   }


#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(SOLARIS)


   bool graphics::ResetDC(const DEVMODE* pDevMode)
   {

      UNREFERENCED_PARAMETER(pDevMode);

      return false;

   }


#endif


#ifdef WINDOWS_DESKTOP


   // ::user::document handling functions
   i32 graphics::StartDoc(LPDOCINFO pDocInfo)

   {
      UNREFERENCED_PARAMETER(pDocInfo);


      return -1;
   }


#endif


   i32 graphics::StartPage()
   {

      return -1;
   }

   i32 graphics::EndPage()
   {

      return -1;
   }

//   i32 graphics::SetAbortProc(bool (CALLBACK* pfn)(HDC, i32))
//
//   {
//      UNREFERENCED_PARAMETER(pfn);
//
//
//      return -1;
//   }

   i32 graphics::AbortDoc()
   {

      return -1;
   }

   i32 graphics::EndDoc()
   {

      return -1;
   }

//   bool graphics::MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
//                          i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask)
//   {
//      UNREFERENCED_PARAMETER(x);
//      UNREFERENCED_PARAMETER(y);
//      UNREFERENCED_PARAMETER(nWidth);
//      UNREFERENCED_PARAMETER(nHeight);
//      UNREFERENCED_PARAMETER(pgraphicsSrc);
//      UNREFERENCED_PARAMETER(xSrc);
//      UNREFERENCED_PARAMETER(ySrc);
//      UNREFERENCED_PARAMETER(maskBitmap);
//      UNREFERENCED_PARAMETER(xMask);
//      UNREFERENCED_PARAMETER(yMask);
//      UNREFERENCED_PARAMETER(dwRop);
//
//
//      return false;
//   }
//   bool graphics::PlgBlt(POINT32 * pPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
//
//                         i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask)
//   {
//      UNREFERENCED_PARAMETER(pPoint);
//
//      UNREFERENCED_PARAMETER(pgraphicsSrc);
//      UNREFERENCED_PARAMETER(xSrc);
//      UNREFERENCED_PARAMETER(ySrc);
//      UNREFERENCED_PARAMETER(nWidth);
//      UNREFERENCED_PARAMETER(nHeight);
//      UNREFERENCED_PARAMETER(maskBitmap);
//      UNREFERENCED_PARAMETER(xMask);
//      UNREFERENCED_PARAMETER(yMask);
//      UNREFERENCED_PARAMETER(ySrc);
//
//      return false;
//   }


   bool graphics::SetPixelV(i32 x, i32 y, const ::color& color)
   {

      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(color);

      return false;

   }


   bool graphics::SetPixelV(const ::point & point, const ::color& color)
   {

      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(color);

      return false;

   }


   bool graphics::AngleArc(i32 x, i32 y, i32 nRadius, angle fStartAngle, angle fSweepAngle)
   {

      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nRadius);
      UNREFERENCED_PARAMETER(fStartAngle);
      UNREFERENCED_PARAMETER(fSweepAngle);

      return false;

   }


   bool graphics::ArcTo(const ::rect & rect, const point & pointStart, const point & pointEnd)
   {

      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(pointStart);
      UNREFERENCED_PARAMETER(pointEnd);

      return false;

   }


   i32 graphics::GetArcDirection()
   {

      return -1;
   }


   bool graphics::PolyPolyline(const POINT32 * ppoints, const ::i32 * pPolyPoints, count nCount)


   {

      UNREFERENCED_PARAMETER(ppoints);

      UNREFERENCED_PARAMETER(pPolyPoints);

      UNREFERENCED_PARAMETER(nCount);


      return false;

   }


//#ifdef WINDOWS_DESKTOP
//
//   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT pColorAdjust)
//
//   {
//      UNREFERENCED_PARAMETER(pColorAdjust);
//
//
//      return false;
//   }
//
//#endif
//

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

      return nullptr;

   }


   ::draw2d::font * graphics::get_current_font()
   {

      return m_pfont;

   }


   ::draw2d::bitmap * graphics::get_current_bitmap()
   {

      return m_pbitmap;

   }


   bool graphics::PolyBezier(const POINT32 * ppoints, count nCount)

   {

      UNREFERENCED_PARAMETER(ppoints);

      UNREFERENCED_PARAMETER(nCount);



      return false;

   }


//   i32 graphics::DrawEscape(i32 nEscape, i32 nInputSize, const char * pszInputData)
//
//   {
//      UNREFERENCED_PARAMETER(nEscape);
//      UNREFERENCED_PARAMETER(nInputSize);
//      UNREFERENCED_PARAMETER(pszInputData);
//
//
//      return -1;
//   }
//
//   i32 graphics::Escape(i32 nEscape, i32 nInputSize, const char * pszInputData, i32 nOutputSize, char * pszOutputData)
//
//   {
//      UNREFERENCED_PARAMETER(nEscape);
//      UNREFERENCED_PARAMETER(nInputSize);
//      UNREFERENCED_PARAMETER(pszInputData);
//
//      UNREFERENCED_PARAMETER(nOutputSize);
//      UNREFERENCED_PARAMETER(pszOutputData);
//
//
//      return -1;
//   }
//
//#ifdef WINDOWS_DESKTOP
//
//   bool graphics::GetCharABCWidths(::u32 nFirstChar, ::u32 nLastChar, LPABCFLOAT pABCF)
//
//   {
//      UNREFERENCED_PARAMETER(nFirstChar);
//      UNREFERENCED_PARAMETER(nLastChar);
//      UNREFERENCED_PARAMETER(pABCF);
//
//
//      return false;
//   }
//
//#endif
//
//   bool graphics::GetCharWidth(::u32 nFirstChar, ::u32 nLastChar, float * pFloatBuffer)
//
//   {
//      UNREFERENCED_PARAMETER(nFirstChar);
//      UNREFERENCED_PARAMETER(nLastChar);
//      UNREFERENCED_PARAMETER(pFloatBuffer);
//
//
//      return false;
//   }


   bool graphics::abort_path()
   {



      return false;

   }


   bool graphics::begin_path()
   {



      return false;

   }


   bool graphics::close_figure()
   {



      return false;

   }


   bool graphics::end_path()
   {



      return false;

   }


   bool graphics::fill_path()
   {



      return false;

   }


   bool graphics::flatten_path()
   {



      return false;

   }


   float graphics::GetMiterLimit()
   {



      return false;

   }


   i32 graphics::GetPath(POINT32 * ppoints, byte * pTypes, count nCount)


   {

      UNREFERENCED_PARAMETER(ppoints);

      UNREFERENCED_PARAMETER(pTypes);

      UNREFERENCED_PARAMETER(nCount);



      return false;

   }


   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      UNREFERENCED_PARAMETER(fMiterLimit);



      return false;

   }


   bool graphics::stroke_and_fill_path()
   {



      return false;

   }


   bool graphics::stroke_path()
   {



      return false;

   }


   bool graphics::widen_path()
   {



      return false;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {



      return false;

   }


   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {



      return false;

   }


   bool graphics::fill_path(::draw2d::path * ppath)
   {



      return false;

   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {



      return false;

   }


   bool graphics::path(::draw2d::path * ppath)
   {

      bool bOk1 = fill_path(ppath);

      bool bOk2 = draw_path(ppath);

      return bOk1 && bOk2;

   }


   bool graphics::AddMetaFileComment(::u32 nDataSize, const byte* pCommentData)
   {
      UNREFERENCED_PARAMETER(nDataSize);
      UNREFERENCED_PARAMETER(pCommentData);

      return false;
   }

#ifdef WINDOWS

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const rect &  pBounds)

   {
      UNREFERENCED_PARAMETER(hEnhMF);
      UNREFERENCED_PARAMETER(pBounds);


      return false;
   }

#endif

//   bool graphics::TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
//                                 ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, ::u32 crTransparent)
//   {
//      UNREFERENCED_PARAMETER(xDest);
//      UNREFERENCED_PARAMETER(yDest);
//      UNREFERENCED_PARAMETER(nDestWidth);
//      UNREFERENCED_PARAMETER(nDestHeight);
//      UNREFERENCED_PARAMETER(pgraphicsSrc);
//      UNREFERENCED_PARAMETER(xSrc);
//      UNREFERENCED_PARAMETER(ySrc);
//      UNREFERENCED_PARAMETER(nSrcWidth);
//      UNREFERENCED_PARAMETER(nSrcHeight);
//      UNREFERENCED_PARAMETER(crTransparent);
//
//      return false;
//   }

//   bool graphics::GradientFill(TRIVERTEX* pVertices, WINULONG nVertices, void * pMesh, WINULONG nMeshElements, u32 dwMode)
//   {
//      UNREFERENCED_PARAMETER(pVertices);
//      UNREFERENCED_PARAMETER(nVertices);
//      UNREFERENCED_PARAMETER(pMesh);
//      UNREFERENCED_PARAMETER(nMeshElements);
//      UNREFERENCED_PARAMETER(dwMode);
//
//      return false;
//   }

//#ifdef WINDOWS
//
//   color32_t graphics::GetDCBrushColor()
//   {
//
//      return 0;
//   }
//
//
//   //::color graphics::SetDCBrushColor(const ::color& color)
//   //{
//
//   //   UNREFERENCED_PARAMETER(color);
//
//   //   return 0;
//
//   //}
//
//
//   color32_t graphics::GetDCPenColor()
//   {
//
//      return 0;
//   }
//
//   color32_t graphics::SetDCPenColor(const ::color & colorColor)
//   {
//      UNREFERENCED_PARAMETER(crColor);
//
//      return 0;
//   }

//#ifndef _UWP
//
//   bool graphics::GetCharABCWidthsI(::u32 giFirst, ::u32 cgi, LPWORD pgi, LPABC pabc)
//
//   {
//      UNREFERENCED_PARAMETER(giFirst);
//      UNREFERENCED_PARAMETER(cgi);
//      UNREFERENCED_PARAMETER(pgi);
//      UNREFERENCED_PARAMETER(pabc);
//
//
//      return false;
//   }
//
//   bool graphics::GetCharWidthI(::u32 giFirst, ::u32 cgi, LPWORD pgi, i32 * pBuffer)
//
//   {
//      UNREFERENCED_PARAMETER(giFirst);
//      UNREFERENCED_PARAMETER(cgi);
//      UNREFERENCED_PARAMETER(pgi);
//      UNREFERENCED_PARAMETER(pBuffer);
//
//
//      return false;
//   }
//
//#endif
//
//   bool graphics::GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, i32 * pnFit, i32 * alpDx, LPSIZE32 pSize)
//
//
//   {
//      UNREFERENCED_PARAMETER(pgiIn);
//      UNREFERENCED_PARAMETER(cgi);
//      UNREFERENCED_PARAMETER(nMaxExtent);
//      UNREFERENCED_PARAMETER(pnFit);
//
//      UNREFERENCED_PARAMETER(alpDx);
//      UNREFERENCED_PARAMETER(pSize);
//
//
//      return false;
//   }
//
//   bool graphics::GetTextExtentPointI(LPWORD pgiIn, i32 cgi, LPSIZE32 pSize)
//
//   {
//      UNREFERENCED_PARAMETER(pgiIn);
//      UNREFERENCED_PARAMETER(cgi);
//      UNREFERENCED_PARAMETER(pSize);
//
//
//      return false;
//   }
//
//#endif

   void graphics::DPtoHIMETRIC(LPSIZE32 pSize)

   {
      UNREFERENCED_PARAMETER(pSize);


   }

   void graphics::HIMETRICtoDP(LPSIZE32 pSize)

   {
      UNREFERENCED_PARAMETER(pSize);


   }

   void graphics::LPtoHIMETRIC(LPSIZE32 pSize)

   {
      UNREFERENCED_PARAMETER(pSize);


   }

   void graphics::HIMETRICtoLP(LPSIZE32 pSize)

   {
      UNREFERENCED_PARAMETER(pSize);


   }

   ::draw2d::brush * graphics::GetHalftoneBrush()
   {

      return nullptr;
   }

   //// top of windows implementation

   //void graphics::DrawDragRect(const ::rect & rect, const ::size & size, const rect & rectLast, const size & sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   //{

   //   UNREFERENCED_PARAMETER(rect);
   //   UNREFERENCED_PARAMETER(size);
   //   UNREFERENCED_PARAMETER(rectLast);
   //   UNREFERENCED_PARAMETER(sizeLast);
   //   UNREFERENCED_PARAMETER(pBrush);
   //   UNREFERENCED_PARAMETER(pBrushLast);
   //
   //

   //}


   void graphics::fill_rect(const ::rect & rect, const ::color & color)
   {

      fill_rect(rectd(rect), color);

   }


   void graphics::fill_rect(const rectd & rect, const ::color& color)
   {

      fill_rect(::rect(rect), color);

   }


   void graphics::draw_3drect(const ::rect & rect, const ::color & colorTopLeft, const ::color & colorBottomRight, const ::e_border & eborder)
   {

      draw_3drect(rectd(rect), colorTopLeft, colorBottomRight, eborder);


   }


   void graphics::draw_3drect(const rectd & rect, const ::color & colorTopLeft, const ::color & colorBottomRight, const ::e_border & eborder)
   {

      draw_3drect(::rect(rect), colorTopLeft, colorBottomRight, eborder);

   }


   void graphics::draw_rect(const ::rect & rect, const ::color & color, const ::e_border & eborder)
   {

      return draw_3drect(rect, color, color, eborder);

   }


   void graphics::draw_rect(const rectd & rect, const ::color & color, const ::e_border & eborder)
   {

      return draw_3drect(rect, color, color, eborder);

   }


   void graphics::assert_valid() const
   {



   }


   void graphics::dump(dump_context & dumpcontext) const
   {

      UNREFERENCED_PARAMETER(dumpcontext);



   }


   bool graphics::DeleteDC()
   {



      return false;

   }


   i32 graphics::StartDoc(const char * pszDocName)

   {

      UNREFERENCED_PARAMETER(pszDocName);




      return -1;

   }


   i32 graphics::SaveDC()
   {

      return -1;
   }


   bool graphics::RestoreDC(i32)
   {

      return false;

   }


   ::draw2d::object* graphics::set_stock_object(i32)
   {

      return nullptr;

   }





   //::draw2d::palette* graphics::SelectPalette(::draw2d::palette *, bool)
   //{

   //   return nullptr;

   //}


   i32 graphics::SetPolyFillMode(i32 nPolyFillMode)
   {

      UNREFERENCED_PARAMETER(nPolyFillMode);

      return -1;

   }


   i32 graphics::SetROP2(i32 nDrawMode)
   {

      UNREFERENCED_PARAMETER(nDrawMode);

      return -1;

   }


//   i32 graphics::set_interpolation_mode(i32 nStretchMode)
//   {
//
//      UNREFERENCED_PARAMETER(nStretchMode);
//
//      return -1;
//
//   }


   i32 graphics::SetGraphicsMode(i32 iMode)
   {

      UNREFERENCED_PARAMETER(iMode);

      return -1;

   }


#ifdef WINDOWS

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      UNREFERENCED_PARAMETER(pXform);

      return false;

   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform, u32 iMode)
   {

      UNREFERENCED_PARAMETER(pXform);
      UNREFERENCED_PARAMETER(iMode);

      return false;

   }

#endif

   i32 graphics::SetMapMode(i32 nMapMode)
   {

      UNREFERENCED_PARAMETER(nMapMode);

      return -1;

   }


   point graphics::SetViewportOrg(i32 x, i32 y)
   {

      m_matrixViewport.c1 = x;

      m_matrixViewport.c2 = y;

      update_matrix();

      return ::point((::i32)m_matrixViewport.c1, (::i32)m_matrixViewport.c2);

   }


   void graphics::get_viewport_scale(::draw2d::matrix & matrix)
   {

      matrix = ::draw2d::matrix();

      matrix.a1 = m_matrixViewport.a1;

      matrix.b2 = m_matrixViewport.b2;

   }


   point graphics::OffsetViewportOrg(i32 nWidth, i32 nHeight)
   {

      m_matrixViewport.c1 += nWidth;

      m_matrixViewport.c2 += nHeight;

      update_matrix();

      return point((::i32)m_matrixViewport.c1, (::i32)m_matrixViewport.c2);

   }


   size graphics::SetViewportExt(i32 x, i32 y)
   {

      UNREFERENCED_PARAMETER(x);

      UNREFERENCED_PARAMETER(y);

      return size(0, 0);

   }


   size graphics::ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom)
   {

      m_matrixViewport.a1 *= xNum / xDenom;

      m_matrixViewport.b2 *= yNum / yDenom;

      update_matrix();

      return size(0, 0);

   }


   point graphics::SetWindowOrg(i32 x, i32 y)
   {

      UNREFERENCED_PARAMETER(x);

      UNREFERENCED_PARAMETER(y);

      return nullptr;

   }


   point graphics::OffsetWindowOrg(i32 nWidth, i32 nHeight)
   {

      UNREFERENCED_PARAMETER(nWidth);

      UNREFERENCED_PARAMETER(nHeight);

      return nullptr;

   }


   size graphics::SetWindowExt(i32 x, i32 y)
   {

      UNREFERENCED_PARAMETER(x);

      UNREFERENCED_PARAMETER(y);


      return size(0, 0);

   }


   size graphics::ScaleWindowExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom)
   {

      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);


      return size(0, 0);

   }


   i32 graphics::GetClipBox(RECT32 * rect)
   {

      UNREFERENCED_PARAMETER(rect);

      return -1;

   }


   i32 graphics::GetClipBox(rect64 * prect)
   {

      ::rect rect;

      i32 iClip = GetClipBox(rect);

      ::copy_rect(prect, &rect);

      return iClip;

   }


//   i32 graphics::ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
//   {
//
//      UNREFERENCED_PARAMETER(x1);
//      UNREFERENCED_PARAMETER(y1);
//      UNREFERENCED_PARAMETER(x2);
//      UNREFERENCED_PARAMETER(y2);
//
//      return -1;
//
//   }
//
//
//   i32 graphics::ExcludeClipRect(const ::rect & rect)
//   {
//
//      UNREFERENCED_PARAMETER(rect);
//
//
//
//      return -1;
//
//   }
//
//
//   i32 graphics::IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
//   {
//
//      ::rect rect;
//
//      rect.left = x1;
//      rect.top = y1;
//      rect.right = x2;
//      rect.bottom = y2;
//
//      return IntersectClipRect(rect);
//
//   }
//
//
//   i32 graphics::IntersectClipRect(const ::rect & rectParam)
//   {
//
//      ::draw2d::region_pointer pregion(e_create);
//
//      pregion->create_rect(rectParam);
//
//      if(m_pregion)
//      {
//
//         auto pregionOld = m_pregion;
//
//         __construct(m_pregion);
//
//         m_pregion->combine(pregionOld, pregion, ::draw2d::e_combine_intersect, this);
//
//      }
//      else
//      {
//
//         m_pregion = pregion;
//
//      }
//
//      //m_pregion->defer_update(this, 0);
//
//      on_apply_clip_region();
//
//      return 0;
//
//   }
//
//
//   i32 graphics::OffsetClipRgn(i32 x, i32 y)
//   {
//
//      if(m_pregion)
//      {
//
//         m_pregion->m_pointOffset += ::size(x, y);
//
//         m_pregion->set_modified();
//
//         on_apply_clip_region();
//
//      }
//
//      return 0;
//
//   }
//
//
//   i32 graphics::OffsetClipRgn(const ::size & size)
//   {
//
//      return OffsetClipRgn(size.cx, size.cy);
//
//   }


   void graphics::on_apply_clip_region()
   {

   }


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
//   i32 graphics::OffsetClipRgn(i32 x, i32 y)
//   {
//
//      UNREFERENCED_PARAMETER(x);
//      UNREFERENCED_PARAMETER(y);
//
//
//
//      return -1;
//
//   }


//   i32 graphics::OffsetClipRgn(const ::size & size)
//   {
//
//      UNREFERENCED_PARAMETER(size);
//
//
//
//      return -1;
//
//   }


   ::u32 graphics::SetTextAlign(::u32 nFlags)
   {
      UNREFERENCED_PARAMETER(nFlags);

      return -1;
   }

   //i32 graphics::SetTextJustification(i32 nBreakExtra, i32 nBreakCount)
   //{
   //   UNREFERENCED_PARAMETER(nBreakExtra);
   //   UNREFERENCED_PARAMETER(nBreakCount);

   //   return -1;
   //}

   //i32 graphics::SetTextCharacterExtra(i32 nCharExtra)
   //{
   //   UNREFERENCED_PARAMETER(nCharExtra);

   //   return -1;
   //}

   //u32 graphics::SetMapperFlags(u32 dwFlag)
   //{
   //   UNREFERENCED_PARAMETER(dwFlag);

   //   return -1;
   //}

   u32 graphics::GetLayout()
   {

      return -1;
   }

   u32 graphics::SetLayout(u32 dwSetLayout)
   {
      UNREFERENCED_PARAMETER(dwSetLayout);

      return -1;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);

      return false;
   }

   i32 graphics::SetArcDirection(i32 nArcDirection)
   {
      UNREFERENCED_PARAMETER(nArcDirection);

      return -1;
   }

   bool graphics::PolyDraw(const POINT32 * ppoints, const byte* pTypes, count nCount)


   {
      UNREFERENCED_PARAMETER(ppoints);

      UNREFERENCED_PARAMETER(pTypes);

      UNREFERENCED_PARAMETER(nCount);

      return false;
   }

   bool graphics::PolylineTo(const POINT32 * ppoints, count nCount)

   {
      UNREFERENCED_PARAMETER(ppoints);

      UNREFERENCED_PARAMETER(nCount);

      return false;
   }


//#ifdef WINDOWS_DESKTOP
//
//
//   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* pColorAdjust)
//
//   {
//
//      UNREFERENCED_PARAMETER(pColorAdjust);
//
//
//      return false;
//
//   }
//
//
//#endif


   bool graphics::PolyBezierTo(const POINT32 * ppoints, count nCount)

   {
      UNREFERENCED_PARAMETER(ppoints);

      UNREFERENCED_PARAMETER(nCount);

      return false;
   }


   bool graphics::SelectClipPath(i32 nMode)
   {

      UNREFERENCED_PARAMETER(nMode);

      return false;

   }


   ::e_status graphics::reset_clip()
   {
   
      return ::success;
   
   }


   ::e_status graphics::add_shapes(const shape_array & shapea)
   {
      
      for(auto & pshape : shapea)
      {
         
         _add_shape(pshape);
         
      }

      return ::success;

   }


   ::e_status graphics::_add_shape(___shape * pshape)
   {
   
      switch(pshape->eshape())
      {
      case e_shape_none:
         return ::success_none;
      case e_shape_intersect_clip:
         return _intersect_clip();
      case e_shape_rect:
         return _add_shape(pshape->shape < ::rect >());
      case e_shape_rectd:
         return _add_shape(pshape->shape < ::rectd >());
      case e_shape_oval:
         return _add_shape(pshape->shape < ::oval >());
      case e_shape_ovald:
         return _add_shape(pshape->shape < ::ovald >());
      case e_shape_polygon:
         return _add_shape(pshape->shape < ::polygon >());
      case e_shape_polygond:
         return _add_shape(pshape->shape < ::polygond >());
      default:
         break;
            
      }

      return error_not_implemented;
      
   }


   ::e_status graphics::_intersect_clip()
   {

      __throw(interface_only_exception);

      return error_interface_only;

   }


   ::e_status graphics::_add_shape(const ::rect & rect)
   {
   
      __throw(interface_only_exception);
   
      return error_interface_only;
   
   }


   ::e_status graphics::_add_shape(const ::rectd & rect)
   {
   
      __throw(interface_only_exception);
   
      return error_interface_only;
   
   }


   ::e_status graphics::_add_shape(const ::oval & oval)
   {
   
      __throw(interface_only_exception);
   
      return error_interface_only;
   
   }


   ::e_status graphics::_add_shape(const ::ovald & oval)
   {
   
      __throw(interface_only_exception);
   
      return error_interface_only;
   
   }


   ::e_status graphics::_add_shape(const ::polygon & polygon)
   {
   
      __throw(interface_only_exception);
   
      return error_interface_only;
   
   }


   ::e_status graphics::_add_shape(const ::polygond & polygon)
   {

      __throw(interface_only_exception);

      return error_interface_only;

   }


   ::e_status graphics::intersect_clip(const ::rect & rect)
   {
   
      auto estatus = _add_shape(rect);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      estatus = _intersect_clip();
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
   
   }


   ::e_status graphics::intersect_clip(const ::rectd & rect)
   {
   
      auto estatus = _add_shape(rect);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      estatus = _intersect_clip();
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
   
   }


   ::e_status graphics::intersect_clip(const ::oval & oval)
   {
   
      auto estatus = _add_shape(oval);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      estatus = _intersect_clip();
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
   
   }


   ::e_status graphics::intersect_clip(const ::ovald & oval)
   {
   
      auto estatus = _add_shape(oval);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      estatus = _intersect_clip();
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
   
   }


   ::e_status graphics::intersect_clip(const ::polygon & polygon)
   {
   
      auto estatus = _add_shape(polygon);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      estatus = _intersect_clip();
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
   
   }


   ::e_status graphics::intersect_clip(const ::polygond & polygon)
   {

      auto estatus = _add_shape(polygon);
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      estatus = _intersect_clip();
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;

   }




//   i32 graphics::SelectClipRgn(::draw2d::region * pregion, enum_combine ecombine)
//   {
//
//      if(pregion != nullptr)
//      {
//
//         auto pregionOld = m_pregion;
//
//         __construct(m_pregion);
//
//         m_pregion->combine(pregionOld, pregion, ecombine);
//
//         m_pregion = pregion;
//
//      }
//
//      on_apply_clip_region();
//
//      return 0;
//
//   }


#ifdef WINDOWS

   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {
      UNREFERENCED_PARAMETER(hMF);

      return false;
   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE32 pSize)

   {
      UNREFERENCED_PARAMETER(pSize);


   }


   void graphics::DPtoLP(LPSIZE32 pSize)

   {

      UNREFERENCED_PARAMETER(pSize);




   }


   ::count graphics::get_character_extent(double_array & daLeft, double_array & daRight, const string & str, strsize iStart, strsize iCount)
   {

      daLeft.remove_all();

      daRight.remove_all();

      if (str.length() <= 0)
      {

         return 0;

      }

      if (iCount == 0)
      {

         return 0;

      }

      if (iStart < 0)
      {

         iStart = 0;

      }

      if (iStart > str.get_length())
      {

         return 0;

      }

      if (iCount < 0)
      {

         iCount = str.get_length() - iStart;

      }

      if (iStart + iCount > str.get_length())
      {

         iCount = str.get_length() - iStart;

         if (iCount <= 0)
         {

            return 0;

         }

      }

      iCount++;

      strsize iRange = 0;

      strsize iAsciiCharCount = 0;

      strsize iLen;

      const char * pszStart = str;

      const char * psz = pszStart;

      double dLeft = 0.0;

      while (*psz && iRange < iStart + iCount)
      {

         const char * pszNext = ::str::utf8_inc(psz);

         if (pszNext == nullptr)
         {

            break;

         }

         iLen = pszNext - psz;

         iAsciiCharCount += iLen;

         daLeft.add(dLeft);

         dLeft = GetTextExtent(str, iAsciiCharCount).cx;

         daRight.add(dLeft);

         iRange++;

         if (*pszNext == '\0')
         {

            break;

         }

         psz = pszNext;

      }

      return daLeft.get_size();

   }


   sized graphics::GetTextBegin(const char * pszString, strsize nCount, strsize iIndex)
   {

      return GetTextExtent(pszString, nCount, iIndex);

   }


   sized graphics::GetTextExtent(const char * pszString, strsize nCount, strsize iIndex)

   {

      return GetTextExtent(pszString, iIndex);


   }


   sized graphics::GetTextExtent(const char * pszString, strsize nCount)
   {

      return GetTextExtent(string(pszString, nCount));

   }


   sized graphics::GetTextExtent(const string & str)
   {
      
      ::sized size;

      if (!GetTextExtent(size, str, str.get_length()))
      {

         return nullptr;

      }

      return size;

   }


   bool graphics::GetTextExtent(sized & size, const char * pszString, strsize nCount, strsize iIndex)

   {

      ::sized sz = GetTextExtent(string(pszString), nCount, iIndex);


      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   bool graphics::GetTextExtent(sized & size, const char * pszString, strsize nCount)

   {

      ::sized sz = GetTextExtent(string(pszString), nCount);


      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   bool graphics::GetTextExtent(sized & size, const string & str)
   {

      ::sized sz = GetTextExtent(str);

      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   size graphics::GetOutputTextExtent(const char * pszString, strsize nCount)

   {
      UNREFERENCED_PARAMETER(pszString);

      UNREFERENCED_PARAMETER(nCount);

      return size(0, 0);
   }

   size graphics::GetOutputTextExtent(const string & str)
   {
      UNREFERENCED_PARAMETER(str);

      return size(0, 0);
   }


   bool graphics::draw_text(const string & str, const rect & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      ::rectd rect(rectParam);

      return _001DrawText(str, rect, ealign, edrawtext, false);

   }



   bool graphics::draw_text(const string & strParam, const ::rectd & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      ::rectd rect(rectParam);

      return _001DrawText(strParam, rect, ealign, edrawtext, false);

   }


   bool graphics::_001DrawText(const string & strParam, rectd & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, bool bMeasure)
   {

      string str(strParam);

      sized size = GetTextExtent(str);

      double dx;

      double dy;

      if(ealign & e_align_right)
      {

         dx = rectParam.right - rectParam.left - size.cx;

      }
      else if(ealign & e_align_horizontal_center)
      {

         dx = ((rectParam.right - rectParam.left) - (size.cx)) / 2.0;

      }
      else
      {

         dx = 0.;

      }

      if(ealign & e_align_bottom)
      {

         dy = rectParam.bottom - rectParam.top - size.cy;

      }
      else if(ealign & e_align_vertical_center)
      {

         dy = ((rectParam.bottom - rectParam.top) - (size.cy)) / 2.0;

      }
      else
      {

         dy = 0.;

      }

      if(edrawtext & e_draw_text_expand_tabs)
      {

         str.replace("\t", "        ");

      }
      else
      {

         str.replace("\t", "");

      }

      if(edrawtext & e_draw_text_single_line)
      {

         str.replace("\rect", "");

         str.replace("\n", "");

         text_out(rectParam.left + dx, rectParam.top + dy, str);

      }
      else
      {

         auto size = GetTextExtent(str);

         string_array stra;

         stra.add_lines(str);

         int offsety = 0;

         for(auto & str : stra)
         {

            auto size1 = GetTextExtent(str);

            text_out(rectParam.left + dx, rectParam.top + dy + offsety, str);

            offsety += (i32) size1.cy;

         }

      }

      return 1;

   }


#ifndef _UWP


   bool graphics::draw_text_ex(const string & str, const rect & rect, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(rect);

      UNREFERENCED_PARAMETER(ealign);
      UNREFERENCED_PARAMETER(edrawtext);

      return false;

   }


   bool graphics::draw_text_ex(const string & str, const rectd & rect, const ::e_align & ealign, const ::e_draw_text & edrawtext)
   {

      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(rect);
      UNREFERENCED_PARAMETER(ealign);
      UNREFERENCED_PARAMETER(edrawtext);

      return false;

   }


#endif


   //bool graphics::from(const ::point & pointDst, const ::size & size, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc)
   //{

   //   return BitBlt(pointDst.x, pointDst.y, size.cx, size.cy, pgraphicsSrc, pointSrc.x, pointSrc.y) != FALSE;

   //}


   //bool graphics::from(const ::size & size, ::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc)
   //{

   //   return from(nullptr, size, pgraphicsSrc, pointSrc);

   //}


   //bool graphics::from(const ::size & size, ::draw2d::graphics * pgraphicsSrc)
   //{

   //   return from(size, pgraphicsSrc, nullptr);

   //}


   bool graphics::alpha_blend(const ::point & pointDst, const ::size & sizeDst,::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc, size szSrc, double dOpacity)
   {

      return alpha_blend(pointDst.x, pointDst.y, sizeDst.cx, sizeDst.cy, pgraphicsSrc, pointSrc.x, pointSrc.y, szSrc.cx, szSrc.cy, dOpacity);

   }


   bool graphics::alpha_blend(const ::point & pointDst, const ::size & size,::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc, double dOpacity)
   {

      return alpha_blend(pointDst, size, pgraphicsSrc, pointSrc, size, dOpacity);

   }


   bool graphics::alpha_blend(const ::point & pointDst, const ::size & size,::draw2d::graphics * pgraphicsSrc, double dOpacity)
   {

      return alpha_blend(pointDst, size, pgraphicsSrc, nullptr, dOpacity);

   }


   bool graphics::alpha_blend(const ::rect & rect, ::draw2d::graphics * pgraphicsSrc, double dOpacity)
   {

      return alpha_blend(rect.top_left(), rect.size(), pgraphicsSrc, dOpacity);

   }


   bool graphics::alpha_blend(const ::size & size,::draw2d::graphics * pgraphicsSrc, const ::point & pointSrc, double dOpacity)
   {

      return alpha_blend(nullptr, size, pgraphicsSrc, pointSrc, dOpacity);

   }


   bool graphics::alpha_blend(const ::size & size,::draw2d::graphics * pgraphicsSrc, double dOpacity)
   {

      return alpha_blend(size, pgraphicsSrc, nullptr, dOpacity);

   }


   bool graphics::alpha_blend(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity)
   {

      if (dOpacity == 1.0)
      {

         if (nSrcHeight == nDstHeight && nSrcWidth == nDstWidth)
         {

            return draw(::rect_dim(xDst, yDst, nDstWidth, nDstHeight), pgraphicsSrc, { xSrc, ySrc });

         }
         else
         {

            return stretch(
               ::rect_dim(xDst, yDst, nDstWidth, nDstHeight),
               pgraphicsSrc, 
               ::rect_dim(xSrc, ySrc, nSrcWidth, nSrcHeight)
            );

         }

      }

      if (alpha_blendAlphaBlend(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight, dOpacity))
      {

         return true;

      }

      if (alpha_blendRaw(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight, dOpacity))
      {

         return true;

      }

      return false;

   }


   bool graphics::alpha_blend(const ::point & pointDst, const ::size & sizeDst, ::image * pimage, const ::point & pointSrc, size szSrc, double dOpacity)
   {

      return alpha_blend(pointDst.x, pointDst.y, sizeDst.cx, sizeDst.cy, pimage, pointSrc.x, pointSrc.y, szSrc.cx, szSrc.cy, dOpacity);

   }


   bool graphics::alpha_blend(const ::point & pointDst, const ::size & size, ::image * pimage, const ::point & pointSrc, double dOpacity)
   {

      return alpha_blend(pointDst, size, pimage, pointSrc, size, dOpacity);

   }


   bool graphics::alpha_blend(const ::point & pointDst, const ::size & size, ::image * pimage, double dOpacity)
   {

      return alpha_blend(pointDst, size, pimage, nullptr, dOpacity);

   }


   bool graphics::alpha_blend(const ::rect & rect, ::image * pimage, double dOpacity)
   {

      return alpha_blend(rect.top_left(), rect.size(), pimage, dOpacity);

   }


   bool graphics::alpha_blend(const ::size & size, ::image * pimage, const ::point & pointSrc, double dOpacity)
   {

      return alpha_blend(nullptr, size, pimage, pointSrc, dOpacity);

   }


   bool graphics::alpha_blend(const ::size & size, ::image * pimage, double dOpacity)
   {

      return alpha_blend(size, pimage, nullptr, dOpacity);

   }


   bool graphics::alpha_blend(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::image * pimage, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity)
   {

      if (dOpacity == 1.0)
      {

         if (nSrcHeight == nDstHeight && nSrcWidth == nDstWidth)
         {

            return draw(::rect(xDst, yDst, nDstWidth, nDstHeight), pimage, {xSrc, ySrc});

         }
         else
         {

            pimage->defer_update_image();

            return stretch(
               ::rect_dim(xDst, yDst, nDstWidth, nDstHeight),
               pimage->g(),
               ::rect_dim(xSrc, ySrc, nSrcWidth, nSrcHeight)
               );

         }

      }

      pimage->defer_update_image();

      if (alpha_blendAlphaBlend(xDst, yDst, nDstWidth, nDstHeight, pimage->g(), xSrc, ySrc, nSrcWidth, nSrcHeight, dOpacity))
      {

         return true;

      }

      if (alpha_blendRaw(xDst, yDst, nDstWidth, nDstHeight, pimage->g(), xSrc, ySrc, nSrcWidth, nSrcHeight, dOpacity))
      {

         return true;

      }

      return false;

   }






   bool graphics::alpha_blendRaw(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate)
   {

      return false;

   }


   bool graphics::alpha_blendAlphaBlend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate)
   {

      if (m_pimageAlphaBlend->is_ok())
      {

         ::rect rectIntersect(m_pointAlphaBlend, m_pimageAlphaBlend->size());

         ::rect rectBlt(point((::i32)xDest, (::i32)yDest), size(nDestWidth, nDestHeight));

         if (rectIntersect.intersect(rectIntersect, rectBlt))
         {

            ::point pointSrc(xSrc, ySrc);

            ::point pointDst(xDest, yDest);

            ::size size(nDestWidth, nDestHeight);

            ::image_pointer pimage1 = create_image(size);

            if (!pimage1)
            {

               return false;

            }

            if (!pimage1->draw(size, pgraphicsSrc->m_pimage, pointSrc))
            {

               return false;

            }

            ::image_pointer pimage2 = create_image(size);

            if (!pimage2)
            {

               return false;

            }

            pimage2->fill(255, 0, 0, 0);

            pimage2->g()->draw({ point(max(0, m_pointAlphaBlend.x - xDest), max(0, m_pointAlphaBlend.y - yDest)), size },
                        m_pimageAlphaBlend->get_graphics(),
               point(max(0, xDest - m_pointAlphaBlend.x), max(0, yDest - m_pointAlphaBlend.y)));

            pimage1->channel_multiply(::color::channel_alpha, pimage2);

            stretch({ pointDst, size }, pimage1->g(), { pointSrc, size });

            return true;

         }

      }

      return false;

   }


   bool graphics::set_alpha_mode(enum_alpha_mode ealphamode)
   {

      m_ealphamode = ealphamode;

      return true;

   }


   bool graphics::set_smooth_mode(e_smooth_mode esmoothmode)
   {

      m_esmoothmode = esmoothmode;

      return true;

   }


   bool graphics::set_interpolation_mode(enum_interpolation_mode einterpolationmode)
   {

      m_einterpolationmode = einterpolationmode;

      return true;

   }


   bool graphics::set_compositing_quality(e_compositing_quality ecompositingquality)
   {

      m_ecompositingquality = ecompositingquality;

      return true;

   }



   bool graphics::set_text_rendering_hint(e_text_rendering_hint etextrenderinghint)
   {

      m_etextrenderinghint = etextrenderinghint;

      return true;

   }


   bool graphics::blur(bool bExpand, double dRadius, const ::rect & rect)
   {



      return false;

   }


   bool graphics::set_solid_pen(double dWidth, const ::color & color)
   {

      if(m_ppen.is_null())
      {

         m_ppen.create();

      }

      m_ppen->create_solid(dWidth, color);

      return true;

   }


   //memory_graphics::memory_graphics(enum_create) :
   //   graphics_pointer(e_create)
   //{

   //   m_p->CreateCompatibleDC(nullptr);

   //}


   //memory_graphics::~memory_graphics()
   //{

   //}


   double graphics::get_dpix()
   {

      return 96.0;

   }


   double graphics::get_dpiy()
   {

      return 96.0;

   }


   bool graphics::flush()
   {

      return true;

   }


   bool graphics::sync_flush()
   {

      return flush();

   }


   ::size graphics::get_size()
   {

      if (::is_null(m_pimage))
      {

         return ::size();

      }

      return m_pimage->get_size();

   }


   //=============================================================================
   //
   // draw_round_rect()
   //
   // Purpose:     Draws a rounded rectangle with a solid pen
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          rect        - [in]   Rect that defines the round rectangle boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //          width    - [in]  width of the border
   //
   // Returns:     None
   //
   bool graphics::draw_round_rect(const ::rect & rect, ::draw2d::pen * ppen, i32 radius, const ::e_border & eborder)
   {

      if (eborder & e_border_all)
      {

         ::draw2d::path_pointer path(e_create);

         if (path->add_round_rect(rect, radius, eborder))
         {

            draw_path(path, ppen);

         }

      }

      return true;

   }


   //=============================================================================
   //
   // draw_round_rect()
   //
   // Purpose:     Draws a rounded rectangle with a solid pen
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          rect        - [in]   Rect that defines the round rectangle boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //          width    - [in]  width of the border
   //
   // Returns:     None
   //
   bool graphics::draw_round_rect(const ::rect & rectParam, const ::color & color, i32 radius, i32 width, const ::e_border & eborder)
   {

      ::rect rect(rectParam);

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, color);

      draw_round_rect(rect, pen, radius);

      for (i32 i = 1; i<width; i++)
      {

         rect.inflate(1, 0);

         draw_round_rect(rect, pen, radius);

         //rect.inflate(0, 1);

         //draw_round_rect(rect, pen, dia / 2);

      }

      return true;

   }


   //bool graphics::draw_round_top_left(const ::rect & rect, ::draw2d::pen  * ppen, i32 radius, const ::e_border & eborder)
   //{

   //   ::draw2d::path_pointer path(e_create);

   //   //path->begin_figure(false, ::draw2d::fill_mode_winding);

   //   path->begin_figure();

   //   path->add_round_top_left(rect, 2 * radius);

   //   path->close_figure();

   //   draw_path(path, ppen);

   //   return true;

   //}


   //bool graphics::draw_round_top_left(const ::rect & rectParam, const ::color & color, i32 radius, i32 width, const ::e_border & eborder)
   //{

   //   ::rect rect(rectParam);

   //   i32 dia = 2 * radius;

   //   ::draw2d::pen_pointer pen(e_create);

   //   pen->create_solid(1.0, color);

   //   draw_round_top_left(rect, pen, radius);


   //   for (i32 i = 1; i<width; i++)
   //   {
   //      dia++;

   //      // left stroke
   //      rect.deflate(1, 0);

   //      draw_round_top_left(rect, pen, dia / 2);

   //      // up stroke
   //      rect.deflate(0, 1);

   //      draw_round_top_left(rect, pen, dia / 2);

   //   }

   //   return true;

   //}


   //bool graphics::draw_round_bottom_right(const ::rect & rect, ::draw2d::pen  * ppen, i32 radius, const ::e_border & eborder)
   //{

   //   ::draw2d::path_pointer path(e_create);

   //   //path->begin_figure(false, ::draw2d::fill_mode_winding);

   //   path->begin_figure();

   //   path->add_round_bottom_right(rect, 2 * radius);

   //   //path->end_figure(false);

   //   path->close_figure();

   //   draw_path(path, ppen);

   //   return true;

   //}


   //bool graphics::draw_round_bottom_right(const ::rect & rectParam, const ::color & color, i32 radius, i32 width, const ::e_border & eborder)
   //{

   //   ::rect rect(rectParam);

   //   i32 dia = 2 * radius;

   //   ::draw2d::pen_pointer pen(e_create);

   //   pen->create_solid(1.0, color);

   //   draw_round_bottom_right(rect, pen, radius);

   //   for (i32 i = 1; i<width; i++)
   //   {

   //      dia++;

   //      // left stroke
   //      rect.deflate(1, 0);

   //      draw_round_bottom_right(rect, pen, dia / 2);

   //      // up stroke
   //      rect.deflate(0, 1);

   //      draw_round_bottom_right(rect, pen, dia / 2);

   //   }

   //   return true;

   //}

   //=============================================================================
   //
   // fill_round_rect()
   //
   // Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
   //          first then fills in the rectangle.
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          rect        - [in]   Rect that defines the round rectangle boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //
   // Returns:     None
   //
   bool graphics::fill_round_rect(const ::rect & rect, const ::color & color, i32 radius)
   {

      ::draw2d::brush_pointer br(e_create);

      br->create_solid(color);

      return fill_round_rect(rect, br.m_p, radius);

   }

   //=============================================================================
   //
   // fill_round_rect()
   //
   // Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
   //          first then fills in the rectangle.
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          pBrush      - [in]  pointer to a Brush
   //          rect        - [in]   Rect that defines the round rectangle boundaries
   //          color    - [in]   Color value for the border (needed in case the
   //                         brush is a type other than solid)
   //          radius      - [in]  radius of the rounded corner
   //
   // Returns:     None
   //
   bool graphics::fill_round_rect(const ::rect & rect, ::draw2d::brush * pbr, i32 radius)
   {

      ::draw2d::path_pointer path(e_create);

      //path->begin_figure(true, ::draw2d::fill_mode_winding);

      path->begin_figure();

      path->add_round_rect(rect, 2 * radius);

      //path->end_figure(true);

      path->close_figure();

      fill_path(path, pbr);

      return true;

   }


   bool graphics::round_rect(const ::rect & rect, i32 radius)
   {

      bool bOk1 = fill_round_rect(rect, m_pbrush.m_p, radius);

      bool bOk2 = draw_round_rect(rect, m_ppen, radius);

      return bOk1 && bOk2;

   }


   i32 graphics::_DrawText(const string& strArg, const rect & rectParam, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::draw2d::font * pfontUnderline)
   {

      string strParam(strArg);

      strParam = ::str::q_valid(strParam);

      if (strParam.is_empty())
      {

         return -1;

      }

      if (!m_pfont)
      {

         return -1;

      }

      text_metric tm2;

      get_text_metrics(&tm2);

      double dLineSpacing = tm2.get_line_spacing();

      ::draw2d::graphics * pgraphics = this;

      wstring wstr = ::str::international::utf8_to_unicode(strParam);

      string str(strParam);

      string str2;

      ::rect rectClip(rectParam);

      if (rectClip.area() <= 0)
      {

         return 0;

      }

      sized sz;

      sz.cx = 0;

      sz.cy = 0;

      strsize iUnderline = -1;

      if(!(edrawtext & e_draw_text_no_prefix))
      {

         iUnderline = _EncodeV033(str);

      }

      strsize iLen = str.get_length();

      bool bLastLine = false;

      if((edrawtext & e_draw_text_word_break) != 0)
      {

         bLastLine = !word_break(pgraphics, str, rectClip, str, str2, (edrawtext & e_draw_text_end_ellipsis));

         sz = pgraphics->GetTextExtent(str);

      }
      else if ((edrawtext & e_draw_text_end_ellipsis) != 0)
      {

         sz = pgraphics->GetTextExtent(str, (i32)iLen);

         if (sz.cx > rectClip.width())
         {

            const char * pszStart = str;

            const char * psz = pszStart;

            string strLastSample = "...";

            string strSample;

            while (true)
            {

               psz = ::str::utf8_inc(psz);

               strSample = string(pszStart, psz - pszStart) + "...";

               sz = pgraphics->GetTextExtent(strSample);

               if (sz.cx > rectClip.width())
               {

                  str = strLastSample;

                  break;

               }

               strLastSample = strSample;

            }

         }

      }
      else
      {

         sz = pgraphics->GetTextExtent(str);

         if (sz.cx > rectClip.width())
         {

            strsize i = iLen;

            if (i < 0)
            {

               i = 0;

            }

            char * psz = str.get_string_buffer(max(0, i));

            while (i > 0)
            {

               sz = pgraphics->GetTextExtent(str, (i32)i);

               if ((int) sz.cx > rectClip.width())
               {

                  i = ::str::uni_dec(str, &((const char *)str)[i]) - ((const char *)str);

                  if (i <= 0)
                  {

                     break;

                  }

               }
               else
               {

                  break;

               }

            }

            psz[i] = L'\0';

            str.release_string_buffer();
         }

      }

      if (str.is_empty())
      {

         return 0;

      }

      ::draw2d::font_pointer fontUnderline;

      if (iUnderline >= 0)
      {

         if (pfontUnderline == nullptr)
         {

            fontUnderline.create();

            pfontUnderline = fontUnderline;

            fontUnderline ->operator=(*pgraphics->get_current_font());

            fontUnderline->set_bold();

         }

      }

      ::rect rect;

      rect.left = 0;
      rect.top = 0;
      rect.right = (::i32) sz.cx;
      rect.bottom = dLineSpacing;

      //::e_align ealign;

      //if (ealig & e_align_bottom)
      //{
      //   
      //   ealign |= ::e_align_bottom;

      //}
      //else if (uiFormat & e_align_vertical_center)
      //{
      //   
      //   ealign |= ::e_align_vertical_center;

      //}
      //else
      //{
      //   
      //   ealign |= ::e_align_top;

      //}

      //if (uiFormat & e_align_right)
      //{
      //   
      //   ealign |= ::e_align_right;

      //}
      //else if (uiFormat & e_align_horizontal_center)
      //{

      //   ealign |= ::e_align_horizontal_center;

      //}
      //else
      //{

      //   ealign |= ::e_align_left;

      //}

      rect.Align(ealign, rectParam);

      if (iUnderline >= 0 && iUnderline < str.get_length())
      {

         pgraphics->text_out(rect.left, rect.top, str, (i32)min(iUnderline, str.get_length()));
         /*::TextOutU(
         (HDC)pgraphics->get_os_data(),
         rect.left,
         rect.top,
         str,
         min(iUnderline, str.get_length()));*/
         if (iUnderline <= str.get_length())
         {
            pgraphics->set(pfontUnderline);
            /*::GetTextExtentPoint32U(
            (HDC)pgraphics->get_os_data(),
            str,
            iUnderline,
            &sz);*/
            sz = pgraphics->GetTextExtent(str, (i32)iUnderline);
            char wch = str[iUnderline];
            /*::TextOutU(
            (HDC)pgraphics->get_os_data(),
            rect.left + sz.cx,
            rect.top,
            &wch,
            1);*/
            pgraphics->text_out(rect.left + sz.cx, (double) rect.top, &wch, 1);
            if (iUnderline + 1 <= str.get_length())
            {
               sz = pgraphics->GetTextExtent(str, (i32)(iUnderline + 1));
               /*::GetTextExtentPoint32U(
               (HDC)pgraphics->get_os_data(),
               str,
               iUnderline + 1,
               &sz);*/
               strsize iCount = str.get_length() - iUnderline - 1;
               pgraphics->text_out(rect.left + sz.cx, (double)rect.top, str.Right(iCount), (i32)iCount);
               /*::TextOutU(
               (HDC)pgraphics->get_os_data(),
               rect.left + sz.cx,
               rect.top,
               str.Right(iCount),
               iCount);*/
            }

         }

      }
      else
      {

         pgraphics->text_out(rect.left, rect.top, str);

      }

      if (!bLastLine && str2.get_length() > 0)
      {

         rectClip.top += dLineSpacing;

         _DrawText(str2, rectClip, ealign, edrawtext);

      }

      return 1;

   }


   bool word_break(::draw2d::graphics * pgraphics, const string & strSource, const rect & rectParam, string &str1, string & str2, int iEll)
   {

      ::rect rect(rectParam);

      string str;

      ::rect rectClip(rect);

      const char * pszSource = strSource;


      strsize len = strSource.get_length();

      const char * pszEnd = pszSource + len;


//      index iFind = str.find(L' ');

      const char * pszStart = ::str::utf8_inc(pszSource);


      size sz;

      const char * pszSpaceStart = nullptr;

      const char * pszSpaceEnd = nullptr;


      const char * psz = pszStart;


      const char * pszPrevious = pszSource;


      string strChar;

      int iNewY;

      bool bLastLine = false;

      bool bEnd = false;

      int y = rect.top;

      while(psz <= pszEnd)

      {

         sz = pgraphics->GetTextExtent(pszSource, psz - pszSource);


         iNewY = y + sz.cy;

         if(iNewY + sz.cy > rect.bottom)
         {

            bLastLine = true;


            str = strSource;

            strsize iLen = str.length();

            sz = pgraphics->GetTextExtent(str,(i32)iLen);


            if(sz.cx > rectClip.width())
            {

               strsize iSampleLen = strSource.get_length();

               while(iSampleLen > 0)
               {

                  iSampleLen--;

                  str = strSource.Left(iSampleLen) + "...";

                  sz = pgraphics->GetTextExtent(str);

                  if(sz.cx < rectClip.width())
                  {

                     break;

                  }

               }

            }

            str1 = str;

            rect.top = y;

            return false;


         }

         if(::str::ch::is_space_char(pszPrevious))

         {
            pszSpaceStart       = pszPrevious;

            do
            {
               pszSpaceEnd      = psz;

               if(!::str::ch::is_space_char(psz))

               {
                  break;
               }
               pszPrevious      = psz;

               psz              = ::str::utf8_inc(psz);

            }
            while(psz != nullptr);

         }

         if (sz.cx > rectClip.width())
         {

            if(psz == pszStart)

            {
               pszEnd = pszStart;

               break;
            }

            if(pszSpaceStart != nullptr)

            {
               // "legit" word break, i.meaning., found mid space in text and split there, instead of slicing a full word in a single-character (above) or the maximum-unclipped (below).
               psz = pszSpaceStart;

               pszEnd = pszSpaceEnd;

               break;
            }

            psz = ::str::uni_dec(pszSource, psz);

            pszEnd = psz;


            break;

         }

         pszPrevious = psz;

         psz = ::str::utf8_inc(psz);


         if(bEnd)
            break;
         else
            bEnd = psz >= pszEnd;


      }

      str1 = string(pszSource, psz - pszSource);


      str2 = string(pszEnd);


      rect.top = y;

      return true;

   }


   strsize _EncodeV033(string & str)
   {
      strsize iStart = 0;
      strsize iIndex;
      strsize iLen = str.get_length();
      while (true)
      {
         iIndex = str.find(L'&', iStart);
         if (iIndex < 0)
            break;
         if (iIndex + 1 >= iLen)
            break;
         if (str[iIndex + 1] == L'&')
         {
            iIndex++;
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
         }
         else
         {
            // Found !
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
            return iIndex;
         }

         if (iIndex >= str.get_length())
            break;
      }
      // Not Found
      return -1;
   }




   bool graphics::draw_stock_icon(const rectd & rectParam, e_stock_icon eicon)
   {

      ::rectd rect(rectParam);

      if(eicon == stock_icon_close)
      {

         rect.deflate(rect.width() / 7.0, rect.height() / 7.0);

         m_ppen->m_dWidth *= 2.0;
         m_ppen->set_modified();
         move_to(rect.top_left());
         line_to(rect.bottom_right());
         move_to(rect.bottom_left());
         line_to(rect.top_right());

      }
      else if(eicon == stock_icon_zoom)
      {

         rect.deflate(0, rect.height() / 7.0);

         draw_rect(rect);

         //m_ppen->m_elinecapBeg = ::draw2d::e_line_cap_flat;
         //m_ppen->m_elinecapEnd = ::draw2d::e_line_cap_flat;
         //move_to(rect.top_left() + ::size(0,(::i32) (pen->m_dWidth/2.0)));
         //line_to(rect.top_right() + ::size(0,(::i32)(pen->m_dWidth / 2.0)));
         //move_to(rect.top_left() + ::size(0,(::i32)(pen->m_dWidth)));
         //line_to(rect.top_right() + ::size(0,(::i32)(pen->m_dWidth)));
         //move_to(rect.top_left() + ::size(0,(::i32)(pen->m_dWidth *3.0 / 2.0)));
         //line_to(rect.top_right() + ::size(0,(::i32)(pen->m_dWidth *3.0 / 2.0)));
         //move_to(rect.top_left() + ::size(0,(::i32)(pen->m_dWidth*2.0)));
         //line_to(rect.top_right() + ::size(0,(::i32)(pen->m_dWidth*2.0)));

      }
      else if(eicon == stock_icon_restore)
      {

         rect.deflate(0, rect.height() / 7.0);

         ::rectd rect1(rect);

         rect1.deflate(0, 0, rect.width() / 3.0, rect.height() / 3.0);

         ::rectd rect2(rect1);

         rect2.Align(e_align_bottom_right, rect);

         draw_rect(rect2);

         m_ppen->m_elinecapBeg = ::draw2d::e_line_cap_flat;
         m_ppen->m_elinecapEnd = ::draw2d::e_line_cap_flat;
         move_to(rect2.top_left() + ::sized(0.,(m_ppen->m_dWidth / 2.0)));
         line_to(rect2.top_right() + ::sized(0.,(m_ppen->m_dWidth / 2.0)));
         move_to(rect2.top_left() + ::sized(0.,(m_ppen->m_dWidth)));
         line_to(rect2.top_right() + ::sized(0.,(m_ppen->m_dWidth)));


         move_to(rect1.top_left());
         line_to(rect1.top_right());
         move_to(rect1.top_left() + ::sized(0.,(m_ppen->m_dWidth / 2.0)));
         line_to(rect1.top_right() + ::sized(0.,(m_ppen->m_dWidth / 2.0)));
         move_to(rect1.top_left() + ::sized(0.,(m_ppen->m_dWidth)));
         line_to(rect1.top_right() + ::sized(0.,(m_ppen->m_dWidth)));



         m_ppen->m_elinecapBeg = ::draw2d::e_line_cap_square;
         m_ppen->m_elinecapEnd = ::draw2d::e_line_cap_square;
         m_ppen->set_modified();

         move_to(rect1.top_left() + ::sized(0,(m_ppen->m_dWidth)));
         line_to(rect1.bottom_left());
         line_to(rect2.bottom_left());

         move_to(rect1.top_right() + ::sized(0,(m_ppen->m_dWidth)));
         line_to(pointd(rect1.right,(int)(rect2.top - (m_ppen->m_dWidth))));

      }
      else if(eicon == stock_icon_iconify)
      {


         rect.deflate(0, rect.height() / 7.0);


         move_to(rect.bottom_left() - ::size(0,(::i32)(m_ppen->m_dWidth*2.0)));
         line_to(rect.bottom_right() - ::size(0,(::i32)(m_ppen->m_dWidth*2.0)));
         move_to(rect.bottom_left() - ::size(0,(::i32)(m_ppen->m_dWidth*3.0 / 2.0)));
         line_to(rect.bottom_right() - ::size(0,(::i32)(m_ppen->m_dWidth*3.0 / 2.0)));
         move_to(rect.bottom_left() - ::size(0,(::i32)(m_ppen->m_dWidth)));
         line_to(rect.bottom_right() - ::size(0,(::i32)(m_ppen->m_dWidth)));
         move_to(rect.bottom_left() - ::size(0,(::i32)(m_ppen->m_dWidth / 2.0)));
         line_to(rect.bottom_right() - ::size(0,(::i32)(m_ppen->m_dWidth / 2.0)));
         move_to(rect.bottom_left());
         line_to(rect.bottom_right());

      }
      else if(eicon == stock_icon_transparent_frame)
      {

      }
      else if(eicon == stock_icon_dock)
      {

         rect.deflate(rect.height() / 8.0, rect.height() / 8.0);

         draw_ellipse(rect);

         ::rect rect1(rect);

         rect1.deflate((i32)(m_ppen->m_dWidth / 2.0),(i32)(m_ppen->m_dWidth / 2.0));

         draw_ellipse(rect1);

         ::rect rect2(rect);

         rect2.deflate((i32)(m_ppen->m_dWidth),(i32)(m_ppen->m_dWidth));

         draw_ellipse(rect2);

      }
      else if (eicon == stock_icon_notify)
      {

         rect.deflate(rect.height() / 2.0, rect.height() / 2.0);

         draw_ellipse(rect);

         ::rect rect1(rect);

         rect1.deflate((i32)(m_ppen->m_dWidth / 2.0), (i32)(m_ppen->m_dWidth / 2.0));

         draw_ellipse(rect1);

         ::rect rect2(rect);

         rect2.deflate((i32)(m_ppen->m_dWidth), (i32)(m_ppen->m_dWidth));

         draw_ellipse(rect2);

      }
      else if (eicon == stock_icon_level_up)
      {

         rect.deflate(rect.height() / 3.0, rect.height() / 3.0);

         pointd_array pointa;

         pointa.add(rect.bottom_left());

         pointa.add(rect.bottom_right());

         pointa.add((rect.right + rect.left) / 2.0, rect.top);

         polygon(pointa);

      }
      else if (eicon == stock_icon_level_down)
      {

         rect.deflate(rect.height() / 3.0, rect.height() / 3.0);

         pointd_array pointa;

         pointa.add(rect.top_left());

         pointa.add(rect.top_right());

         pointa.add((rect.right + rect.left) / 2.0, rect.bottom);

         polygon(pointa);

      }
      else
      {

         ::exception::throw_not_implemented();

      }

      return true;

   }


   void graphics::debug()
   {
   }


   bool graphics::draw_error_line(i32 x1, i32 h, i32 x2, i32 iStyle)
   {

      int iR = m_ppen->m_color.m_iR;
      int iG = m_ppen->m_color.m_iG;
      int iB = m_ppen->m_color.m_iB;
      int iA = m_ppen->m_color.m_iA;

      if(iStyle == 0)
      {

         draw_line(x1, h, x2, h);

      }
      else
      {

         ::image_pointer pimage;

         double w = x2 - x1 + 1;

         auto estatus = __construct(pimage);

         if (!estatus)
         {

            return estatus;

         }

         estatus = pimage->create({ (i32)w, 6 });

         if (!estatus || pimage->area() <= 0)
         {

            return estatus;

         }

         pimage->fill(0, 0, 0, 0);

         double dStep = 0.125;
         double dPeriod = 7.0;
         double dTint;
         double dHalfH = 1.33;
         double dHSpan = 0.7;
         double dH = 2.5;
         double dCurl = 2.3;
         double dBaseTint = 2.0;
         double dCircleX;
         double dCircleY;

         pimage->map();

         auto colorref = pimage->colorref();

         auto scan = pimage->scan_size();

         auto wscan = scan / sizeof(color32_t);

         for (double dx = 0; dx < w; dx += dStep)
         {
            dCircleX = fmod(dx, (double)(dPeriod));
            double dSign = dCircleX < (dPeriod / 2.0) ? 1.0 : -1.0;
            dCircleX -= dPeriod / 2.0;
            dTint = dBaseTint * 0.51;
            dCircleY = dSign * sqrt(dPeriod * dPeriod / 4.0 - dCircleX * dCircleX) * 0.05;
            {
               double dy = (sin((double)dx * 2.0 * 3.1415 / dPeriod) - fmod(dx, (double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               ;
               dy = (dy * dHalfH + dH - dHSpan);
               int x = (int)round(dx);
               int y = (int)round(dy);
               if (x < 0 || y < 0 || x >= pimage->width() || y >= pimage->height())
               {
               }
               else
               {
                  int A = (colorref[x + wscan * y] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(dy), 1.0);
                  double fx = 1.0 - fmod(fabs(dx), 1.0);
                  A = (int)(A + ((fx * fy) * 255.0 * dStep * dTint));
                  A = min(A, 255);
                  colorref[x + wscan * y] = ARGB((A * iA) / 255, iB, iG, iR);
               }
            }
            dTint = dBaseTint * 0.51;
            {
               double dy = (sin((double)dx * 2.0 * 3.1415 / dPeriod) - fmod(dx, (double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               dy = (dy * dHalfH + dH + dHSpan);
               int x = (int)round(dx);
               int y = (int)round(dy);
               if (x < 0 || y < 0 || x >= pimage->width() || y >= pimage->height())
               {
               }
               else
               {
                  int A = (colorref[x + wscan * y] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(dy), 1.0);
                  double fx = 1.0 - fmod(fabs(dx), 1.0);
                  A = (int)(A + ((fx * fy) * 255.0 * dStep * dTint));
                  A = min(A, 255);
                  colorref[x + wscan * y] = ARGB((A * iA) / 255, iB, iG, iR);
               }

            }

            dTint = dBaseTint * 2.3;

            {
               double dy = (sin((double)dx * 2.0 * 3.1415 / dPeriod) - fmod(dx, (double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               dy = (dy * dHalfH + dH);
               int x = (int)round(dx);
               int y = (int)round(dy);
               if (x < 0 || y < 0 || x >= pimage->width() || y >= pimage->height())
               {
               }
               else
               {
                  int A = (colorref[x + wscan] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(dy), 1.0);
                  double fx = 1.0 - fmod(fabs(dx), 1.0);
                  A = (int)(A + ((fx * fy) * 255.0 * dStep * dTint));
                  A = min(A, 255);
                  colorref[x + wscan * y] = ARGB((A * iA) / 255, iB, iG, iR);

               }

            }

         }

         set_alpha_mode(::draw2d::alpha_mode_blend);

         draw({::point(x1, h), pimage->size() }, pimage->get_graphics());

      }

      return true;

   }


   void graphics::draw_ca2_with_border2(int x, int y, int z, int bOut, int bIn, const ::color & colorBk, const ::color & color, const ::color & colorOut, const ::color & colorIn)
   {

      draw_ca2(x + bIn + bOut, y + bIn + bOut, z, colorBk, color);

      draw_ca2_border2(x, y, z, bOut, bIn, colorBk, color, colorOut, colorIn);

   }


   void graphics::draw_ca2_with_border(int x, int y, int z, int b, const ::color & colorBk, const ::color & color, const ::color & colorBorder)
   {

      draw_ca2(x + b, y + b, z, colorBk, color);

      int w = z / 19;

      if (w < 1)
      {

         w = 1;

      }

      z = w * 19;

      rect rect(x + b, y + b, x + b + z, y + b + z);

      ::draw2d::pen_pointer point(e_create);

      point->create_solid(1.0, colorBorder);

      for(int i = 0; i < b; i++)
      {

         rect.inflate(1,1);

         draw_rect(rect, point);

      }

   }


   ::file::path graphics::get_font_path(const string & strName, int iWeight, bool bItalic)
   {

      cslock sl(::aura::g_pcsFont);

      string strFontName(strName);

      strFontName.make_lower();

      string strPath = (*::aura::g_pmapFontFaceName)[strFontName][iWeight * 10 + (bItalic ? 1 : 0)];

      return strPath;

   }



   void graphics::draw_ca2(int x, int y, int z, const ::color & colorBk, const ::color & color)
   {

      ::draw2d::brush_pointer b(e_create);

      // black rectangle

      int w = z / 19;

      if(w < 1)
         w = 1;

      z = w * 19;

      b->create_solid(colorBk);

      rect rect(x, y, x + z, y + z);

      fill_rect(rect, b);

      // bottom line

      b->create_solid(color);

      rect.top += w * 13;
      rect.bottom -= w;


      // c

      rect.left += w;
      rect.right = rect.left + w * 5;

      ::rect rect2(rect);

      // c vertical

      rect2.right = rect2.left + w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.bottom = rect2.top + w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.top = rect2.bottom - w;

      fill_rect(rect2, b);








      // a

      rect.left += w * 6;
      rect.right = rect.left + w * 5;

      rect2 = rect;

      rect2.bottom = rect2.top + w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.top = rect2.bottom - w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.right = rect2.left + w * 2;
      rect2.top += w * 2;
      rect2.bottom = rect2.top + w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.left += w * 5 / 2;
      rect2.right = rect2.left + w;
      rect2.top += w * 2;
      rect2.bottom = rect2.top + w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.left = rect2.right - w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.right = rect2.left + w;
      rect2.top += w * 2;

      fill_rect(rect2, b);





      // 2

      rect.left += w * 6;
      rect.right = rect.left + w * 5;

      rect2 = rect;

      rect2.bottom = rect2.top + w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.top = rect2.bottom - w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.top += w * 2;
      rect2.bottom = rect2.top + w;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.right = rect2.left + w;
      rect2.top += w * 2;

      fill_rect(rect2, b);

      rect2 = rect;

      rect2.left = rect2.right - w;
      rect2.bottom -= w * 2;

      fill_rect(rect2, b);

   }


   void graphics::draw_ca2_border2(int x, int y, int z, int bOut, int bIn, const ::color & colorBk, const ::color & color, const ::color & colorOut, const ::color & colorIn)
   {
      int w = z / 19;

      if(w < 1)
         w = 1;

      z = w * 19;


      rect rect(x + bIn + bOut, y + bIn + bOut, x + bIn + bOut + z - 1, y + bIn + bOut + z - 1);

      ::draw2d::pen_pointer point(e_create);

      point->create_solid(1.0, colorIn);

      for(int i = 0; i < bIn; i++)
      {

         rect.inflate(1,1);

         draw_rect(rect, point);

      }

      point->create_solid(1.0, colorOut);

      for(int i = 0; i < bOut; i++)
      {

         rect.inflate(1,1);

         draw_rect(rect, point);

      }

   }


   void graphics::enum_fonts(::draw2d::font_enum_item_array & itema)
   {

      UNREFERENCED_PARAMETER(itema);



   }


   void graphics::sorted_fonts(::draw2d::font_enum_item_array & itema)
   {

      enum_fonts(itema);

      ::sort::array::pred_sort(itema, [&](auto & a, auto & b)
      {

         return a->m_strName < b->m_strName;

      });

   }


   float graphics::nanosvg_distPtSeg(float x, float y, float px, float py, float qx, float qy)
   {

      float pqx, pqy, dx, dy, d, t;
      pqx = qx - px;
      pqy = qy - py;
      dx = x - px;
      dy = y - py;
      d = pqx*pqx + pqy*pqy;
      t = pqx*dx + pqy*dy;
      if (d > 0) t /= d;
      if (t < 0) t = 0;
      else if (t > 1) t = 1;
      dx = px + t*pqx - x;
      dy = py + t*pqy - y;
      return dx*dx + dy*dy;

   }


   void graphics::nanosvg_cubicBez(float x1, float y1, float x2, float y2,
                                   float x3, float y3, float x4, float y4,
                                   float tol, int level)
   {
      float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
      float d;

      if (level > 12) return;

      x12 = (x1 + x2)*0.5f;
      y12 = (y1 + y2)*0.5f;
      x23 = (x2 + x3)*0.5f;
      y23 = (y2 + y3)*0.5f;
      x34 = (x3 + x4)*0.5f;
      y34 = (y3 + y4)*0.5f;
      x123 = (x12 + x23)*0.5f;
      y123 = (y12 + y23)*0.5f;
      x234 = (x23 + x34)*0.5f;
      y234 = (y23 + y34)*0.5f;
      x1234 = (x123 + x234)*0.5f;
      y1234 = (y123 + y234)*0.5f;

      d = nanosvg_distPtSeg(x1234, y1234, x1, y1, x4, y4);
      if (d > tol*tol)
      {
         nanosvg_cubicBez(x1, y1, x12, y12, x123, y123, x1234, y1234, tol, level + 1);
         nanosvg_cubicBez(x1234, y1234, x234, y234, x34, y34, x4, y4, tol, level + 1);
      }
      else
      {

         line_to(pointd(x4, y4));

      }

   }


   void graphics::nanosvg_drawPath(float* pts, int npts, char closed, float tol, const ::color & color)
   {

      int i;

      begin_path();

      move_to(pointd(pts[0], pts[1]));

      for (i = 0; i < npts - 1; i += 3)
      {

         float* point = &pts[i * 2];

         nanosvg_cubicBez(point[0], point[1], point[2], point[3], point[4], point[5], point[6], point[7], tol, 0);

      }

      if (closed)
      {

         move_to(pointd(pts[0], pts[1]));

      }

      end_path();

   }


   void graphics::nanosvg_drawControlPts(float* pts, int npts)
   {

      int i;

      // Control lines
      //glColor4ubv(lineColor);
      //glBegin(GL_LINES);
      begin_path();

      for (i = 0; i < npts - 1; i += 3)
      {

         float* point = &pts[i * 2];

         move_to(::point((::i32) point[0], (::i32)point[1]));
         line_to(::point((::i32)point[2], (::i32)point[3]));
         line_to(::point((::i32)point[4], (::i32)point[5]));
         line_to(::point((::i32)point[6], (::i32)point[7]));

      }

      end_path();


      // Points
      //glPointSize(6.0f);
      //glColor4ubv(lineColor);

      //glBegin(GL_POINTS);
      //glVertex2f(pts[0], pts[1]);
      //for (i = 0; i < npts - 1; i += 3) {
      // float* point = &pts[i * 2];
      //glVertex2f(point[6], point[7]);
      //}
      //glEnd();

      // Points
      //glPointSize(3.0f);

      //glBegin(GL_POINTS);
      //glColor4ubv(bgColor);
      //glVertex2f(pts[0], pts[1]);
      //for (i = 0; i < npts - 1; i += 3) {
      //   float* point = &pts[i * 2];
      //   glColor4ubv(lineColor);
      //   glVertex2f(point[2], point[3]);
      //   glVertex2f(point[4], point[5]);
      //   glColor4ubv(bgColor);
      //   glVertex2f(point[6], point[7]);
      //}
      //glEnd();

   }


   void graphics::nanosvg_drawframe(NSVGimage* pnsvgimage, int x, int y, int width, int height)
   {

      float view[4], cx, cy, hw, hh, aspect, px;

      NSVGshape* shape;

      NSVGpath* path;

      //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      //glfwGetFramebufferSize(window, &width, &height);

      //glViewport(0, 0, width, height);

      int n=SaveDC();

      OffsetViewportOrg(x, y);

      //glClearColor(220.0f / 255.0f, 220.0f / 255.0f, 220.0f / 255.0f, 1.0f);
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //glDisable(GL_TEXTURE_2D);
      //glMatrixMode(GL_PROJECTION);
      //glLoadIdentity();

      // Fit view to bounds
      cx = pnsvgimage->width * 0.5f;
      cy = pnsvgimage->height * 0.5f;
      hw = pnsvgimage->width * 0.5f;
      hh = pnsvgimage->height * 0.5f;

      if (width / hw < height / hh)
      {
         aspect = (float)height / (float)width;
         view[0] = cx - hw * 1.2f;
         view[2] = cx + hw * 1.2f;
         view[1] = cy - hw * 1.2f * aspect;
         view[3] = cy + hw * 1.2f * aspect;
      }
      else
      {
         aspect = (float)width / (float)height;
         view[0] = cx - hh * 1.2f * aspect;
         view[2] = cx + hh * 1.2f * aspect;
         view[1] = cy - hh * 1.2f;
         view[3] = cy + hh * 1.2f;
      }
      // Size of one pixel.
      px = (view[2] - view[1]) / (float)width;

      //glOrtho(view[0], view[2], view[3], view[1], -1, 1);

      //glMatrixMode(GL_MODELVIEW);
      //glLoadIdentity();
      //glDisable(GL_DEPTH_TEST);
      //glColor4ub(255, 255, 255, 255);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      // Draw bounds
      //glColor4ub(0, 0, 0, 64);
      //glBegin(GL_LINE_LOOP);
      //glVertex2f(0, 0);
      //glVertex2f(pnsvgimage->width, 0);
      //glVertex2f(pnsvgimage->width, pnsvgimage->height);
      //glVertex2f(0, pnsvgimage->height);
      //glEnd();

      ::draw2d::pen_pointer pen(e_create);

      pen->create_solid(1.0, ARGB(255, 0, 128, 0));

      set(pen);

      for (shape = pnsvgimage->shapes; shape != nullptr; shape = shape->next)
      {

         for (path = shape->paths; path != nullptr; path = path->next)
         {

            nanosvg_drawPath(path->pts, path->npts, path->closed, px / 3.0f, ARGB(255, 0, 128, 0));

//            nanosvg_drawControlPts(path->pts, path->npts);

         }

      }

      //glfwSwapBuffers(window);

      RestoreDC(n);

   }

   //void graphics::nanosvg_resizecb(int width, int height)
   //{
   //   // Update and render
   //   NSVG_NOTUSED(width);
   //   NSVG_NOTUSED(height);
   //   //drawframe(window);
   //}


   bool graphics::nanosvg(string str, int x, int y, int w, int h)
   {

      struct NSVGimage* pnsvgimage;

      pnsvgimage = nsvgParse((char *) (const char *) str, "px", 96);

      nanosvg_drawframe(pnsvgimage, x, y, w, h);

      nsvgDelete(pnsvgimage);

      return true;

   }



   bool graphics::is_valid_update_window_thread()
   {

      return true;

   }


   void graphics::on_begin_draw(oswindow wnd, const size & sz)
   {

   }

   void graphics::on_end_draw(oswindow wnd)
   {


   }

   savedc::savedc(graphics * pgraphics)
   {
      m_pgraphics = pgraphics;
      try
      {
         if (m_pgraphics != nullptr)
         {
            m_iSavedDC = m_pgraphics->SaveDC();
            m_matrixViewport = pgraphics->m_matrixViewport;
            m_matrixTransform = pgraphics->m_matrixTransform;
         }
      }
      catch (...)
      {

      }
   }
   savedc::~savedc()
   {
      try
      {
         if (m_pgraphics != nullptr)
         {
            m_pgraphics->RestoreDC(m_iSavedDC);
            m_pgraphics->m_matrixViewport = m_matrixViewport;
            m_pgraphics->m_matrixTransform = m_matrixTransform;
         }
      }
      catch (...)
      {

      }

   }

   bool graphics::_get(matrix & matrix)
   {

      return false;

   }


   bool graphics::_set(const matrix & matrix)
   {

      return false;

   }


   bool graphics::get(matrix & matrix)
   {

      matrix = m_matrixTransform;

      return true;

   }


   bool graphics::set(const matrix & matrix)
   {

      m_matrixTransform = matrix;

      update_matrix();

      return true;

   }


   bool graphics::update_matrix()
   {

      matrix matrixViewport;

      matrix matrixViewportScale;

      matrix matrixViewportTranslate;

      matrixViewportScale.a1 = m_matrixViewport.a1;

      matrixViewportScale.b2 = m_matrixViewport.b2;

      matrixViewportTranslate.c1 = m_matrixViewport.c1;

      matrixViewportTranslate.c2 = m_matrixViewport.c2;

      matrix matrix = matrixViewportScale * m_matrixTransform * matrixViewportTranslate;

      if (!_set(matrix))
      {

         return false;

      }

      return true;

   }


   bool graphics::append(const matrix & matrix)
   {

      m_matrixTransform.append(matrix);

      update_matrix();

      return true;

   }


   bool graphics::prepend(const matrix & matrix)
   {

      m_matrixTransform.prepend(matrix);

      update_matrix();

      return true;

   }

   void graphics::draw_rect_side(const ::rect& rect, enum_border eborder)
   {

      if (eborder & e_border_top)
      {

         move_to(rect.top_left());

         line_to(rect.top_right());

      }

      if (eborder & e_border_right)
      {

         move_to(rect.top_right());

         line_to(rect.bottom_right());

      }

      if (eborder & e_border_bottom)
      {

         move_to(rect.bottom_right());

         line_to(rect.bottom_left());

      }

      if (eborder & e_border_left)
      {

         move_to(rect.bottom_left());

         line_to(rect.top_left());

      }

   }


   void graphics::draw_border(const ::rect & rectParam, const ::color & color, int iWidth)
   {

      ::rect rect(rectParam);

      rect.inflate(iWidth + 1, iWidth + 1);

      __pointer(pen) point = m_ppen;

      pen_pointer point1(e_create);

      point1->create_solid(iWidth, color);

      point1->m_epenalign = e_pen_align_inset;

      set(point1);

      draw_rect(rect);

      set(point);

   }


   ::e_status graphics::clear_current_point()
   {

      __throw(todo);

      return ::success_none;

   }


   ::draw2d::graphics_pointer create_graphics()
   {

      auto pgraphics = __create< graphics>();

      return ::move(pgraphics);

   }


   ::draw2d::graphics_pointer create_memory_graphics()
   {

      auto pgraphics = create_graphics();

      if (!pgraphics)
      {

         return nullptr;

      }

      if (!pgraphics->create_memory_graphics())
      {

         return nullptr;

      }

      return pgraphics;

   }


} // namespace draw2d



