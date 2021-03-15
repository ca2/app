#include "framework.h"


namespace draw2d_xlib
{


   region::region(::context_object * pcontextobject) :
      ::object(pobject)
   {

   }


   region::~region()
   {

   }



   /*   region::operator HRGN() const
      {
         return (HRGN)(this == nullptr ? nullptr : get_os_data());
      }
      region* PASCAL region::from_handle(::object * pobject, HRGN hRgn)
      {
         return dynamic_cast < region * > (::win::object::from_handle(papp, hRgn));
      }
      int_bool region::CreateRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
      { return Attach(::CreateRectRgn(x1, y1, x2, y2)); }
      int_bool region::CreateRectRgnIndirect(const ::rectangle_i32 & rectangle)
      { return Attach(::CreateRectRgnIndirect(rectangle)); }
      int_bool region::CreateEllipticRgn(i32 x1, i32 y1, i32 x2, i32 y2)
      { return Attach(::CreateEllipticRgn(x1, y1, x2, y2)); }
      int_bool region::CreateEllipticRgnIndirect(const ::rectangle_i32 & rectangle)
      { return Attach(::CreateEllipticRgnIndirect(rectangle)); }
      int_bool region::CreatePolygonRgn(POINT_I32 * lpPoints, i32 nCount, i32 nMode)
      { return Attach(::CreatePolygonRgn(lpPoints, nCount, nMode)); }
      int_bool region::CreatePolyPolygonRgn(POINT_I32 * lpPoints, LPINT lpPolyCounts, i32 nCount, i32 nPolyFillMode)
      { return Attach(::CreatePolyPolygonRgn(lpPoints, lpPolyCounts, nCount, nPolyFillMode)); }
      int_bool region::CreateRoundRectRgn(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3)
      { return Attach(::CreateRoundRectRgn(x1, y1, x2, y2, x3, y3)); }
      int_bool region::CreateFromPath(::image * pimage)
      { ASSERT(pgraphics != nullptr); return Attach(::PathToRegion((dynamic_cast<::win::graphics * >(pgraphics))->get_handle1())); }
      int_bool region::CreateFromData(const XFORM* lpXForm, i32 nCount, const RGNDATA* pRgnData)
      { return Attach(::ExtCreateRegion(lpXForm, nCount, pRgnData)); }
      i32 region::GetRegionData(LPRGNDATA lpRgnData, i32 nDataSize) const
      { ASSERT(get_os_data() != nullptr); return (i32)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData); }
      void region::SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
      { ASSERT(get_os_data() != nullptr); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2); }

      void region::SetRectRgn(const ::rectangle_i32 & rectangle)
      {
         ::SetRectRgn((HRGN)get_os_data(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
      }

      i32 region::CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, i32 nCombineMode)
      { ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(),
      (HRGN)pRgn2->get_os_data(), nCombineMode); }
      i32 region::CopyRgn(const ::draw2d::region* pRgnSrc)
      { ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), nullptr, RGN_COPY); }
      int_bool region::EqualRgn(const ::draw2d::region* pRgn) const
      { ASSERT(get_os_data() != nullptr); return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()); }
      i32 region::OffsetRgn(i32 x, i32 y)
      { ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), x, y); }
      i32 region::OffsetRgn(const ::point_i32 & point)
      { ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y); }
      i32 region::GetRgnBox(RECTANGLE_I32 * prectangle) const
      { ASSERT(get_os_data() != nullptr); return ::GetRgnBox((HRGN)get_os_data(), rectangle); }
      int_bool region::PtInRegion(i32 x, i32 y) const
      { ASSERT(get_os_data() != nullptr); return ::PtInRegion((HRGN)get_os_data(), x, y); }
      int_bool region::PtInRegion(const ::point_i32 & point) const
      { ASSERT(get_os_data() != nullptr); return ::PtInRegion((HRGN)get_os_data(), point.x, point.y); }
      int_bool region::RectInRegion(const ::rectangle_i32 & rectangle) const
      { ASSERT(get_os_data() != nullptr); return ::RectInRegion((HRGN)get_os_data(), rectangle); }*/

   /*   bool region::get(xlib_t * pgraphics)
      {

         xlib_set_source_rgba(pgraphics, 0.0, 0.0, 0.0, 0.0);

         xlib_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);

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
            __throw(error_not_implemented);
         }

         return false;

      }

      bool region::get_rect(xlib_t * pgraphics)
      {

         xlib_rectangle(pgraphics, m_x1, m_y1, m_x2, m_y2);

         xlib_fill(pgraphics);

         return true;

      }

      bool region::get_oval(xlib_t * pgraphics)
      {

         double centerx    = (m_x2 + m_x1) / 2.0;
         double centery    = (m_y2 + m_y1) / 2.0;

         double radiusx    = abs(m_x2 - m_x1) / 2.0;
         double radiusy    = abs(m_y2 - m_y1) / 2.0;

         if(radiusx == 0.0 || radiusy == 0.0)
            return false;

         xlib_translate(pgraphics, centerx, centery);

         xlib_scale(pgraphics, radiusx, radiusy);

         xlib_arc(pgraphics, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

         xlib_fill(pgraphics);

         xlib_scale(pgraphics, 1.0 / radiusx, 1.0 / radiusy);

         xlib_translate(pgraphics, -centerx,  -centery);

         return true;

      }

      bool region::get_polygon(xlib_t * pgraphics)
      {

         if(m_nCount <= 0)
            return true;


         xlib_move_to(pgraphics, m_lppoints[0].x, m_lppoints[0].y);

         for(i32 i = 1; i < m_nCount; i++)
         {

            xlib_line_to(pgraphics, m_lppoints[i].x, m_lppoints[i].y);

         }
         xlib_fill(pgraphics);

         return true;

      }

      bool region::get_poly_polygon(xlib_t * pgraphics)
      {

         i32 n = 0;

         for(i32 i = 0; i < m_nCount; i++)
         {
            i32 jCount = m_lppolycounts[i];
            if(jCount > 0)
            {
               xlib_move_to(pgraphics, m_lppoints[n].x, m_lppoints[n].y);
               n++;
               for(i32 j = 1; i < jCount; j++)
               {
                  xlib_line_to(pgraphics, m_lppoints[n].x, m_lppoints[n].y);
                  n++;
               }
            }

         }
         xlib_fill(pgraphics);

         return true;

      }

      bool region::get_combine(xlib_t * pgraphics)
      {

         xlib_push_group( graphics);

         dynamic_cast < ::draw2d_xlib::region * >(m_pregion1)->get( graphics);

         xlib_pop_group_to_source(pgraphics);

         xlib_paint(pgraphics);

         xlib_push_group(pgraphics);

         dynamic_cast < ::draw2d_xlib::region * >(m_pregion2)->get( graphics);

         xlib_pop_group_to_source(pgraphics);

         if(m_ecombine == ::draw2d::region::combine_add)
         {
            xlib_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);
         }
         else if(m_ecombine == ::draw2d::region::combine_exclude)
         {
            xlib_set_operator(pgraphics, CAIRO_OPERATOR_CLEAR);
         }
         else if(m_ecombine == ::draw2d::region::combine_intersect)
         {
            xlib_set_operator(pgraphics, CAIRO_OPERATOR_IN);
         }
         else
         {
            xlib_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);
         }

         xlib_paint(pgraphics);

         return true;

      }


      void * region::get_os_data() const
      {

         if(m_bUpdated)
            return (void *) this;

         ((region *) this)->m_bUpdated = true;

         return (void *) this;

      }*/

} // namespace draw2d_xlib



