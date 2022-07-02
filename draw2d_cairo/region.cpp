#include "framework.h"
#include <math.h>


namespace draw2d_cairo
{


   region::region()
   {

      m_pthis = this;

      m_pcairo = nullptr;

      m_psurface = nullptr;

   }


   region::~region()
   {

   }


   bool region::is_simple_positive_region()
   {

      switch(m_eregion)
      {
      case ::draw2d::e_region_none:

         return true;

      case ::draw2d::e_region_rect:

         return true;

      case ::draw2d::e_region_ellipse:

         return true;

      case ::draw2d::e_region_polygon:

         return true;

      case ::draw2d::e_region_poly_polygon:

         return false;

      case ::draw2d::e_region_combine:

         return false;

      default:

         throw ::interface_only();

      }

      return true;

   }


   bool region::_mask(cairo_t * pgraphics, double dOpacity, enum_mask emask)
   {

      synchronous_lock ml(cairo_mutex());

      if(m_pcairo != nullptr)
      {

         cairo_destroy(m_pcairo);

         m_pcairo = nullptr;

      }

      if(m_psurface != nullptr)
      {

         cairo_surface_destroy(m_psurface);

         m_psurface = nullptr;

      }

      m_rectangleBoundingBoxInternal = rectangle_i32(0, 0, 0, 0);

      max_bounding_box(m_rectangleBoundingBoxInternal);

      m_psurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, m_rectangleBoundingBoxInternal.width(), m_rectangleBoundingBoxInternal.height());

      if(m_psurface == nullptr)
      {

         return false;

      }

      m_pcairo = cairo_create(m_psurface);

      cairo_set_antialias(m_pcairo, CAIRO_ANTIALIAS_BEST);

      int x = m_rectangleBoundingBoxInternal.left;

      int y = m_rectangleBoundingBoxInternal.top;

      cairo_translate(m_pcairo, -x, -y);

      cairo_push_group(m_pcairo);

      _mask(m_pcairo);

      cairo_pop_group_to_source(m_pcairo);

      cairo_rectangle(m_pcairo, 0, 0, m_rectangleBoundingBoxInternal.width(), m_rectangleBoundingBoxInternal.height());

      cairo_fill(m_pcairo);

      cairo_mask_surface(pgraphics, m_psurface, m_rectangleBoundingBoxInternal.left, m_rectangleBoundingBoxInternal.top);

      cairo_destroy(m_pcairo);

      m_pcairo = nullptr;

      cairo_surface_destroy(m_psurface);

      m_psurface = nullptr;

      return true;

   }


   bool region::_mask(cairo_t * pgraphics)
   {

      switch(m_eregion)
      {
      case ::draw2d::e_region_none:

         break;

      case ::draw2d::e_region_rect:

         mask_rect(pgraphics);

         cairo_set_source_rgba(pgraphics, 0.0, 0.0, 0.0, 1.0);

         cairo_fill(pgraphics);

         break;

      case ::draw2d::e_region_ellipse:

         mask_oval(pgraphics);

         cairo_set_source_rgba(pgraphics, 0.0, 0.0, 0.0, 1.0);

         cairo_fill(pgraphics);

         break;

      case ::draw2d::e_region_polygon:

         mask_polygon(pgraphics);

         cairo_set_source_rgba(pgraphics, 0.0, 0.0, 0.0, 1.0);

         cairo_fill(pgraphics);

         break;

      case ::draw2d::e_region_poly_polygon:

         mask_polygon(pgraphics);

         cairo_set_source_rgba(pgraphics, 0.0, 0.0, 0.0, 1.0);

         cairo_fill(pgraphics);

         break;

      case ::draw2d::e_region_combine:

         mask_combine(pgraphics);

         cairo_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);

         cairo_paint(pgraphics);

         break;

      default:

         throw ::interface_only();

      }

      return true;

   }


   bool region::mask_fill(cairo_t * pdc)
   {

      return _mask(pdc, 0.0, e_mask_fill);

   }


   bool region::mask_paint(cairo_t * pdc)
   {

      return _mask(pdc, 0.0, e_mask_paint);

   }


   bool region::mask_paint_with_alpha(cairo_t * pdc, double dOpacity)
   {

      return _mask(pdc, dOpacity, e_mask_paint_with_alpha);

   }


   bool region::mask_rect(cairo_t * pgraphics)
   {

      synchronous_lock ml(cairo_mutex());

      __pointer(rectangle_item) pitem = m_pitem;

      cairo_rectangle(
         pgraphics, 
         pitem->m_rectangle.left,
         pitem->m_rectangle.top, 
         pitem->m_rectangle.width(), 
         pitem->m_rectangle.height());

      return true;

   }


   bool region::mask_oval(cairo_t * pgraphics)
   {

      synchronous_lock ml(cairo_mutex());

      __pointer(ellipse_item) pitem = m_pitem;

      auto center = pitem->m_rectangle.center();

      auto size = pitem->m_rectangle.size();

      double centerx    = center.x;

      double centery    = center.y;

      double radiusx    = fabs(size.cx) / 2.0;

      double radiusy    = fabs(size.cy) / 2.0;

      if(radiusx == 0.0 || radiusy == 0.0)
      {

         return false;

      }

      cairo_keep k(pgraphics);

      cairo_translate(pgraphics, centerx, centery);

      cairo_scale(pgraphics, radiusx, radiusy);

      cairo_arc(pgraphics, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      return true;

   }


   bool region::mask_polygon(cairo_t * pgraphics)
   {

      synchronous_lock ml(cairo_mutex());

      __pointer(polygon_item) pitem = m_pitem;

      if(pitem->m_polygon.is_empty())
      {

         return true;

      }

      cairo_move_to(pgraphics, pitem->m_polygon[0].x, pitem->m_polygon[0].y);

      for(i32 i = 1; i < pitem->m_polygon.size(); i++)
      {

         cairo_line_to(pgraphics, pitem->m_polygon[i].x, pitem->m_polygon[i].y);

      }

      return true;

   }


   bool region::mask_poly_polygon(cairo_t * pgraphics)
   {

      synchronous_lock ml(cairo_mutex());

      __pointer(poly_polygon_item) pitem = m_pitem;

      if (pitem->m_polygona.is_empty())
      {

         return true;

      }

      i32 n = 0;

      for(i32 i = 0; i < pitem->m_polygona.size(); i++)
      {

         auto ppolygon = pitem->m_polygona[i];

         if(ppolygon && ppolygon->has_element())
         {

            auto & polygon = *ppolygon;

            cairo_move_to(pgraphics, polygon[n].x, polygon[n].y);

            n++;

            for(i32 j = 1; j < polygon.size(); j++)
            {

               cairo_line_to(pgraphics, polygon[n].x, polygon[n].y);

               n++;

            }

         }

      }

      return true;

   }


   bool region::mask_combine(cairo_t * pgraphics)
   {

      synchronous_lock ml(cairo_mutex());

      cairo_push_group(pgraphics);

      __pointer(combine_item) pitem = m_pitem;

      pitem->m_pregion1.cast < ::draw2d_cairo::region >()->_mask(pgraphics);

      if(pitem->m_ecombine == ::draw2d::e_combine_add)
      {

         cairo_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);

      }
      else if(pitem->m_ecombine == ::draw2d::e_combine_exclude)
      {

         cairo_set_operator(pgraphics, CAIRO_OPERATOR_CLEAR);

      }
      else if(pitem->m_ecombine == ::draw2d::e_combine_intersect)
      {

         cairo_set_operator(pgraphics, CAIRO_OPERATOR_IN);

      }
      else
      {

         cairo_set_operator(pgraphics, CAIRO_OPERATOR_SOURCE);

      }

      pitem->m_pregion2.cast < ::draw2d_cairo::region >()->_mask(pgraphics);

      cairo_pop_group_to_source(pgraphics);

      return true;

   }


   bool region::clip(cairo_t * pgraphics)
   {

      synchronous_lock ml(cairo_mutex());

      _mask(pgraphics);

      cairo_clip(pgraphics);

      return true;

   }


   //bool region::clip_rect(cairo_t * pgraphics)
   //{

   //   synchronous_lock ml(cairo_mutex());

   //   cairo_rectangle(pgraphics, m_x1, m_y1, m_x2, m_y2);

   //   cairo_clip(pgraphics);

   //   return true;

   //}


   //bool region::clip_oval(cairo_t * pgraphics)
   //{

   //   synchronous_lock ml(cairo_mutex());

   //   double centerx    = (m_x2 + m_x1) / 2.0;

   //   double centery    = (m_y2 + m_y1) / 2.0;

   //   double radiusx    = fabs(m_x2 - m_x1) / 2.0;

   //   double radiusy    = fabs(m_y2 - m_y1) / 2.0;

   //   if(radiusx == 0.0 || radiusy == 0.0)
   //   {

   //      return false;

   //   }

   //   cairo_translate(pgraphics, centerx, centery);

   //   cairo_scale(pgraphics, radiusx, radiusy);

   //   cairo_arc(pgraphics, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

   //   cairo_clip(pgraphics);

   //   cairo_scale(pgraphics, 1.0 / radiusx, 1.0 / radiusy);

   //   cairo_translate(pgraphics, -centerx, -centery);

   //   return true;

   //}


   //bool region::clip_polygon(cairo_t * pgraphics)
   //{

   //   synchronous_lock ml(cairo_mutex());

   //   if(m_nCount <= 0)
   //   {

   //      return true;

   //   }

   //   cairo_move_to(pgraphics, m_lppoints[0].x, m_lppoints[0].y);

   //   for(i32 i = 1; i < m_nCount; i++)
   //   {

   //      cairo_line_to(pgraphics, m_lppoints[i].x, m_lppoints[i].y);

   //   }

   //   cairo_clip(pgraphics);

   //   return true;

   //}


   bool region::create(::draw2d::graphics * pgraphics)
   {

      m_osdata[0] = this;

      return true;

   }


   void region::destroy_os_data()
   {

      if (m_psurface != nullptr)
      {

         cairo_surface_destroy(m_psurface);

         m_psurface = nullptr;

      }

      if (m_pcairo != nullptr)
      {

         cairo_destroy(m_pcairo);

         m_pcairo = nullptr;

      }

      //return ::success;

   }


   void region::destroy()
   {

      //auto estatus = 
      
      ::draw2d::region::destroy();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


} // namespace draw2d_cairo



