#include "framework.h"


namespace draw2d_quartz2d
{


   region::region()
   {

   }


   region::~region()
   {

   }

//   void * region::get_os_data() const
//   {
//      defer_update();
//
//      return m_path;
//
//
//   }

   void region::destroy()
   {

      if(m_path != nullptr)
      {

         CGPathRelease(m_path);

         m_path = nullptr;

      }

   }


   bool region::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

      m_path = CGPathCreateMutable();

      if(m_etype == ::draw2d::region::type_rect)
      {

         CGRect rect;

         rect.origin.x = m_x1;
         rect.origin.y = m_y1;
         rect.size.width = m_x2 - m_x1;
         rect.size.height = m_y2 - m_y1;

         CGPathAddRect (m_path, nullptr, rect);

      }
      else if(m_etype == ::draw2d::region::type_polygon)
      {

         CGPathMoveToPoint(m_path, nullptr, m_lppoints[0].x, m_lppoints[0].y);

         for(i32 i = 1; i < m_nCount; i++)
         {

            CGPathAddLineToPoint(m_path, nullptr, m_lppoints[i].x, m_lppoints[i].y);

         }

      }
      else if(m_etype == ::draw2d::region::type_oval)
      {

         CGRect rect;

         rect.origin.x = m_x1;
         rect.origin.y = m_y1;
         rect.size.width = m_x2 - m_x1;
         rect.size.height = m_y2 - m_y1;


         CGPathAddEllipseInRect(m_path, nullptr, rect);

      }
      else if(m_etype == ::draw2d::region::type_combine)
      {

         __throw(::exception::exception("not supported"));

      }

      CGPathCloseSubpath(m_path);

      return true;

   }

   /*   region::operator HRGN() const
    {
    return (HRGN)(this == nullptr ? nullptr : get_os_data());
    }
    region* PASCAL region::from_handle(::base::application * papp, HRGN hRgn)
    {
    return dynamic_cast < region * > (::win::object::from_handle(papp, hRgn));
    }
    WINBOOL region::CreateRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
    { return Attach(::CreateRectRgn(x1, y1, x2, y2)); }
    WINBOOL region::CreateRectRgnIndirect(const ::rect & rect)
    { return Attach(::CreateRectRgnIndirect(rect)); }
    WINBOOL region::CreateEllipticRgn(i32 x1, i32 y1, i32 x2, i32 y2)
    { return Attach(::CreateEllipticRgn(x1, y1, x2, y2)); }
    WINBOOL region::CreateEllipticRgnIndirect(const ::rect & rect)
    { return Attach(::CreateEllipticRgnIndirect(rect)); }
    WINBOOL region::CreatePolygonRgn(LPPOINT lpPoints, i32 nCount, i32 nMode)
    { return Attach(::CreatePolygonRgn(lpPoints, nCount, nMode)); }
    WINBOOL region::CreatePolyPolygonRgn(LPPOINT lpPoints, LPINT lpPolyCounts, i32 nCount, i32 nPolyFillMode)
    { return Attach(::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, nPolyFillMode)); }
    WINBOOL region::CreateRoundRectRgn(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3)
    { return Attach(::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3)); }
    WINBOOL region::CreateFromPath(::image * pimage)
    { ASSERT(pgraphics != nullptr); return Attach(::PathToRegion((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1())); }
    WINBOOL region::CreateFromData(const XFORM* lpXForm, i32 nCount, const RGNDATA* pRgnData)
    { return Attach(::ExtCreateRegion(lpXForm, nCount, pRgnData)); }
    i32 region::GetRegionData(LPRGNDATA lpRgnData, i32 nDataSize) const
    { ASSERT(get_os_data() != nullptr); return (i32)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData); }
    void region::SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
    { ASSERT(get_os_data() != nullptr); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2); }

    void region::SetRectRgn(const ::rect & rect)
    {
    ::SetRectRgn((HRGN)get_os_data(), rect.left, rect.top, rect.right, rect.bottom);
    }

    i32 region::CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, i32 nCombineMode)
    { ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(),
    (HRGN)pRgn2->get_os_data(), nCombineMode); }
    i32 region::CopyRgn(const ::draw2d::region* pRgnSrc)
    { ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), nullptr, RGN_COPY); }
    WINBOOL region::EqualRgn(const ::draw2d::region* pRgn) const
    { ASSERT(get_os_data() != nullptr); return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()); }
    i32 region::OffsetRgn(i32 x, i32 y)
    { ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), x, y); }
    i32 region::OffsetRgn(const ::point & point)
    { ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y); }
    i32 region::GetRgnBox(RECT * prect) const
    { ASSERT(get_os_data() != nullptr); return ::GetRgnBox((HRGN)get_os_data(), rect); }
    WINBOOL region::PtInRegion(i32 x, i32 y) const
    { ASSERT(get_os_data() != nullptr); return ::PtInRegion((HRGN)get_os_data(), x, y); }
    WINBOOL region::PtInRegion(const ::point & point) const
    { ASSERT(get_os_data() != nullptr); return ::PtInRegion((HRGN)get_os_data(), point.x, point.y); }
    WINBOOL region::RectInRegion(const ::rect & rect) const
    { ASSERT(get_os_data() != nullptr); return ::RectInRegion((HRGN)get_os_data(), rect); }*/

   /*

   bool region::get(cairo_t * pgraphics)
   {

      cairo_set_source_rgba(pgraphics, 0.0, 0.0, 0.0, 0.0);

      cairo_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);

      switch(m_etype)
      {
         case type_none:
            return true;
         case type_rect:
            return get_rect(pgraphics);
         case type_oval:
            return get_oval(pgraphics);
         case type_polygon:
            return get_polygon(pgraphics);
         case type_poly_polygon:
            return get_polygon(pgraphics);
         case type_combine:
            return get_combine(pgraphics);
         default:
            __throw(not_implemented());
      }

      return false;

   }

   bool region::get_rect(cairo_t * pgraphics)
   {

      cairo_rectangle(pgraphics, m_x1, m_y1, m_x2, m_y2);

      cairo_fill(pgraphics);

      return true;

   }

   bool region::get_oval(cairo_t * pgraphics)
   {

      double centerx    = (m_x2 + m_x1) / 2.0;
      double centery    = (m_y2 + m_y1) / 2.0;

      double radiusx    = abs(m_x2 - m_x1) / 2.0;
      double radiusy    = abs(m_y2 - m_y1) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
         return false;

      cairo_translate(pgraphics, centerx, centery);

      cairo_scale(pgraphics, radiusx, radiusy);

      cairo_arc(pgraphics, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      cairo_fill(pgraphics);

      cairo_scale(pgraphics, 1.0 / radiusx, 1.0 / radiusy);

      cairo_translate(pgraphics, -centerx,  -centery);

      return true;

   }

   bool region::get_polygon(cairo_t * pgraphics)
   {

      if(m_nCount <= 0)
         return true;


      cairo_move_to(pgraphics, m_lppoints[0].x, m_lppoints[0].y);

      for(i32 i = 1; i < m_nCount; i++)
      {

         cairo_line_to(pgraphics, m_lppoints[i].x, m_lppoints[i].y);

      }
      cairo_fill(pgraphics);

      return true;

   }

   bool region::get_poly_polygon(cairo_t * pgraphics)
   {

      i32 n;

      for(i32 i = 0; i < m_nCount; i++)
      {
         i32 jCount = m_lppolycounts[i];
         if(jCount > 0)
         {
            cairo_move_to(pgraphics, m_lppoints[n].x, m_lppoints[n].y);
            n++;
            for(i32 j = 1; i < jCount; j++)
            {
               cairo_line_to(pgraphics, m_lppoints[n].x, m_lppoints[n].y);
               n++;
            }
         }

      }
      cairo_fill(pgraphics);

      return true;

   }

   bool region::get_combine(cairo_t * pgraphics)
   {

      cairo_push_group( graphics);

      dynamic_cast < ::lnx::region * >(m_pregion1)->get( graphics);

      cairo_pop_group_to_source(pgraphics);

      cairo_paint(pgraphics);

      cairo_push_group(pgraphics);

      dynamic_cast < ::lnx::region * >(m_pregion2)->get( graphics);

      cairo_pop_group_to_source(pgraphics);

      if(m_ecombine == ::draw2d::region::combine_add)
      {
         cairo_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);
      }
      else if(m_ecombine == ::draw2d::region::combine_exclude)
      {
         cairo_set_operator(pgraphics, CAIRO_OPERATOR_CLEAR);
      }
      else if(m_ecombine == ::draw2d::region::combine_intersect)
      {
         cairo_set_operator(pgraphics, CAIRO_OPERATOR_IN);
      }
      else
      {
         cairo_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);
      }

      cairo_paint(pgraphics);

   }

   */



   void * region::detach()
   {

      void * ppath = m_path;

      m_path = nullptr;

      return ppath;

   }

} // namespace draw2d_quartz2d



