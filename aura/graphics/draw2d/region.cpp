#include "framework.h"
#include "region.h"
#include "acme/exception/interface_only.h"
#include "acme/primitive/geometry2d/item.h"


namespace draw2d
{


   region::region()
   {

      //m_eregion         = e_region_none;
      //m_lppoints        = nullptr;
      //m_lppolycounts    = nullptr;

   }


   region::region(const region & region)
   {

      //m_lppolycounts    = nullptr;
      //m_lppoints        = nullptr;
      //m_eregion         = e_region_none;

      m_pitem = region.m_pitem->clone();

   }


   region::~region()
   {

      destroy();

   }


   void region::destroy()
   {

      m_pitem.release();
      //::acme::adel(m_lppoints);
      //::acme::adel(m_lppolycounts);
      //m_pregion1.release();
      //m_pregion2.release();

      //return ::success;

   }

   //bool region::create_rectangle(const ::rectangle_i32 & rectangle)
   //{

   //   if(m_eregion != e_region_none)
   //   {

   //      destroy();

   //   }

   //   m_eregion = e_region_rect;

   //   auto pitem = __new(rectangle_item);

   //   pitem->m_rectangle = rectangle;

   //   m_pitem = pitem;

   //   return true;

   //}


   //bool region::create_ellipse(const ::rectangle_i32 & rectangle)
   //{

   //   if(m_eregion != e_region_none)
   //   {

   //      destroy();

   //   }

   //   m_eregion = e_region_ellipse;

   //   auto pitem = __new(ellipse_item);

   //   pitem->m_rectangle = rectangle;

   //   m_pitem = pitem;

   //   return true;

   //}


   //bool region::create_polygon(const ::point_f64 * ppoints, i32 nCount, ::draw2d::enum_fill_mode efillmode)
   //{

   //   if(m_eregion != e_region_none)
   //   {

   //      destroy();

   //   }

   //   m_eregion = e_region_polygon;

   //   auto pitem = __new(polygon_item);

   //   pitem->m_polygon.set_size(nCount);

   //   memcpy(pitem->m_polygon.data(), ppoints, pitem->m_polygon.get_size_in_bytes());

   //   pitem->m_efillmode = efillmode;

   //   m_pitem = pitem;

   //   return true;

   //}


   //bool region::create_polygon(const polygon& polygon, ::draw2d::enum_fill_mode efillmode)
   //{

   //   return create_polygon(polygon.data(), (::i32) polygon.size(), efillmode);

   //}


   //bool region::create_polygon(const ::point_i32 * ppoints, i32 nCount, ::draw2d::enum_fill_mode efillmode)
   //{

   //   if(m_eregion != e_region_none)
   //   {

   //      destroy();

   //   }

   //   m_eregion = e_region_polygon;

   //   auto pitem = __new(polygon_item);

   //   pitem->m_polygon.set_size(nCount);

   //   for (::i32 i = 0; i < nCount; i++)
   //   {

   //      auto& p = pitem->m_polygon[i];

   //      p = (const ::point_i32&)ppoints[i];

   //   }

   //   pitem->m_efillmode = efillmode;

   //   m_pitem = pitem;

   //   return true;

   //}


   //bool region::create_poly_polygon(const ::point_f64 * ppoints, const i32 * ppolycounts, i32 nCount, ::draw2d::enum_fill_mode efillmode)
   //{

   //   if(m_eregion != e_region_none)
   //   {

   //      destroy();

   //   }

   //   m_eregion = e_region_polygon;

   //   auto pitem = __new(poly_polygon_item);

   //   pitem->m_polygona.set_size(nCount);

   //   for (::index i = 0; i < nCount; i++)
   //   {

   //      pitem->m_polygona[i] = __new(polygon);

   //      pitem->m_polygona[i]->set_size(ppolycounts[i]);

   //      for (::index j = 0; j < ppolycounts[i]; j++)
   //      {

   //         pitem->m_polygona[i]->element_at(j).x() = ppoints->x();
   //         pitem->m_polygona[i]->element_at(j).y() = ppoints->y();

   //         ppoints++;

   //      }

   //   }

   //   pitem->m_efillmode = efillmode;

   //   m_pitem = pitem;

   //   return true;

   //}


   //bool region::create_poly_polygon(const ::point_i32 * ppoints, const i32 * ppolycounts,i32 nCount,::draw2d::enum_fill_mode efillmode)
   //{

   //   if(m_eregion != e_region_none)
   //   {

   //      destroy();

   //   }

   //   m_eregion = e_region_poly_polygon;

   //   auto pitem = __new(poly_polygon_item);

   //   pitem->m_polygona.set_size(nCount);

   //   for (::index i = 0; i < nCount; i++)
   //   {

   //      pitem->m_polygona[i] = __new(polygon);

   //      pitem->m_polygona[i]->set_size(ppolycounts[i]);

   //      for (::index j = 0; j < ppolycounts[i]; j++)
   //      {

   //         pitem->m_polygona[i]->element_at(j).x() = ppoints->x();
   //         pitem->m_polygona[i]->element_at(j).y() = ppoints->y();

   //         ppoints++;

   //      }

   //   }

   //   pitem->m_efillmode = efillmode;

   //   m_pitem = pitem;

   //   return true;

   //}


   //bool region::combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, enum_combine ecombine, ::draw2d::graphics * pgraphics)
   //{

   //   ::pointer<::draw2d::region>pregion1 = (::draw2d::region *) prgn1;

   //   ::pointer<::draw2d::region>pregion2 = (::draw2d::region *) prgn2;

   //   if(m_eregion != e_region_none)
   //   {

   //      destroy();

   //   }

   //   m_eregion = e_region_combine;

   //   auto pitem = __new(combine_item);

   //   pitem->m_pregion1 = pregion1;

   //   pitem->m_pregion2 = pregion2;

   //   pitem->m_ecombine  = ecombine;

   //   m_pitem = pitem;

   //   return true;

   //}


   region & region::operator = (const ::draw2d::region & regionSrc)
   {

      if(this == &regionSrc)
         return *this;

      //if(m_eregion != e_region_none)
      //{

      //   destroy();

      //}


      if (!regionSrc.m_pitem)
      {

         m_pitem.release();

      }
      else
      {

         m_pitem = regionSrc.m_pitem->clone();

      }

      return *this;

      //m_eregion = regionSrc.m_eregion;

      //switch(m_eregion)
      //{
      //case e_region_none:
      //   return *this;
      //case e_region_rect:
      //case e_region_ellipse:
      //   m_pitem = regionSrc.m_pitem->clone();
      //   return *this;
      //case e_region_polygon:
      //   m_pitem = regionSrc.m_pitem->clone();
      //   return *this;
      //case e_region_poly_polygon:
      //{
      //   m_pitem = regionSrc.m_pitem->clone();
      //}
      //return *this;
      //case e_region_round_rect:
      //   m_pitem = regionSrc.m_pitem->clone();
      //   return *this;
      //case e_region_combine:
      //   m_pitem = regionSrc.m_pitem->clone();
      //   return *this;
      //default:
      //   throw ::interface_only();
      //};
      //return *this;

   }


   bool region::get_bounding_box(::rectangle_i32 & rectangle, ::draw2d::graphics * pgraphics)
   {

      throw ::interface_only();

      return false;

   }


   bool region::contains(const ::point_f64 & point, ::draw2d::graphics * pgraphics)
   {

      return internal_contains(point);

   }


   bool region::translate(const ::point_i32 & point, ::draw2d::graphics * pgraphics)
   {

      set_modified();

      if (m_pitem)
      {

         m_pitem->translate(point);

      }

      return true;

   }


   bool region::contains(const ::point_i32 & point, ::draw2d::graphics * pgraphics)
   {

      return contains(point_f64(point));

   }


   void region::expand_bounding_box(::rectangle_i32 & rectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_f64 rectangleMaxBounding;

      expand_bounding_box(rectangleMaxBounding);

      rectangle = rectangleMaxBounding;

   }


   //void region::expand_bounding_box(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::rectangle_f64 rectangle;

   //   max_bounding_box_rect(rectangle);

   //   copy(prectangle, rectangle);


   //}


   //void region::max_bounding_box_oval(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::rectangle_f64 rectangle;

   //   max_bounding_box_oval(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_polygon(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::rectangle_f64 rectangle;

   //   max_bounding_box_polygon(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_poly_polygon(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::rectangle_f64 rectangle;

   //   max_bounding_box_poly_polygon(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_combine(::rectangle_i32 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::rectangle_f64 rectangle;

   //   max_bounding_box_combine(rectangle);

   //   copy(prectangle, rectangle);

   //}


   void region::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {

      if (m_pitem)
      {

         m_pitem->expand_bounding_box(rectangle);

      }

   }


   //void region::max_bounding_box_rect(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if (m_pitem)
   //   {

   //      m_pitem->max_bounding_box_rect(prectangle, pgraphics);

   //   }

   //}


   //void region::max_bounding_box_oval(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if (m_pitem)
   //   {

   //      m_pitem->max_bounding_box_rect(prectangle, pgraphics);

   //   }


   //}


   //void region::max_bounding_box_polygon(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if(m_nCount <= 0)
   //   {

   //      return;
   //      
   //   }

   //   for(int i = 0; i < m_nCount; i++)
   //   {

   //      prectangle->left = minimum(prectangle->left,m_lppoints[i].x());

   //      prectangle->right = maximum(prectangle->right,m_lppoints[i].x());

   //      prectangle->top = minimum(prectangle->left,m_lppoints[i].y());

   //      prectangle->bottom = maximum(prectangle->right,m_lppoints[i].y());

   //   }

   //}


   //void region::max_bounding_box_poly_polygon(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   i32 n = 0;

   //   for(i32 i = 0; i < m_nCount; i++)
   //   {

   //      i32 iCount = m_lppolycounts[i];

   //      for(int j = 0; j < iCount; j++,n++)
   //      {

   //         prectangle->left = minimum(prectangle->left,m_lppoints[n].x());

   //         prectangle->right = maximum(prectangle->right,m_lppoints[n].x());

   //         prectangle->top = minimum(prectangle->left,m_lppoints[n].y());

   //         prectangle->bottom = maximum(prectangle->right,m_lppoints[n].y());

   //      }

   //   }

   //}


   //void region::max_bounding_box_combine(::rectangle_f64 * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   m_pregion1->expand_bounding_box(prectangle);

   //   m_pregion2->expand_bounding_box(prectangle);

   //}


   bool region::internal_contains(const ::point_f64 & point)
   {

      if (m_pitem)
      {

         return m_pitem->contains(point);

      }

      return false;

   }


   //bool region::internal_rectangle_contains(const ::point_f64 & point)
   //{

   //   return point.x() >= m_x1 && point.y() >= m_y1 && point.x() <= m_x2 && point.y() <= m_y2;

   //}


   //bool region::internal_oval_contains(const ::point_f64 & point)
   //{

   //   double centerx    = (m_x2 + m_x1) / 2.0;
   //   double centery    = (m_y2 + m_y1) / 2.0;

   //   double rx    = fabs(m_x2 - m_x1) / 2.0;
   //   double ry    = fabs(m_y2 - m_y1) / 2.0;

   //   if (rx == 0.0 || ry == 0.0)
   //   {

   //      return false;

   //   }
   //
   //   double x = point.x();

   //   double y = point.y();
   //   
   //   double Δx = x - centerx;
   //   
   //   double Δy = y - centery;
   //   
   //   if(rx == ry)
   //   {
   //      
   //      double r = rx;
   //      
   //      double square_distance = (Δx * Δx) + (Δy * Δy);
   //      
   //      double square_boundary = (r * r);
   //      
   //      return square_distance <= square_boundary;
   //            
   //   }
   //   else
   //   {

   //      double normal_distance = ((Δx * Δx) / (rx * rx) + (Δy * Δy) / (ry * ry));
   //      
   //      return normal_distance <= 1.0;
   //      
   //   }

   //}


   //bool region::internal_polygon_contains(const ::point_f64 & point)
   //{

   //   if (m_nCount <= 0)
   //   {

   //      return false;

   //   }

   //   if (::polygon_contains_point(m_lppoints, m_nCount, point))
   //   {

   //      return true;

   //   }

   //   return false;

   //}


   //bool region::internal_poly_polygon_contains(const ::point_f64 & point)
   //{

   //   i32 n = 0;

   //   for(i32 i = 0; i < m_nCount; i++)
   //   {

   //      i32 iCount = m_lppolycounts[i];

   //      if (::polygon_contains_point(&m_lppoints[n], iCount, point))
   //      {

   //         return true;

   //      }

   //      n += iCount;

   //   }

   //   return false;

   //}


   //bool region::internal_combine_contains(const ::point_f64 & point)
   //{

   //   if(m_ecombine == e_combine_add)
   //   {

   //      if (m_pregion1->internal_contains(point))
   //      {

   //         return true;

   //      }

   //      if (m_pregion2->internal_contains(point))
   //      {

   //         return true;

   //      }

   //      return false;

   //   }
   //   else if(m_ecombine == e_combine_exclude)
   //   {

   //      if (m_pregion2->internal_contains(point))
   //      {

   //         return false;

   //      }

   //      if (m_pregion1->internal_contains(point))
   //      {

   //         return true;

   //      }

   //      return false;

   //   }
   //   else if(m_ecombine == e_combine_intersect)
   //   {
   //      
   //      if(m_pregion1->internal_contains(point))
   //      {

   //         if (m_pregion2->internal_contains(point))
   //         {

   //            return true;

   //         }

   //      }

   //      return false;

   //   }
   //   else if(m_ecombine == e_combine_xor)
   //   {
   //      
   //      if(m_pregion1->internal_contains(point))
   //      {

   //         if (m_pregion2->internal_contains(point))
   //         {

   //            return false;

   //         }
   //         else
   //         {

   //            return true;

   //         }

   //      }
   //      else if(m_pregion2->internal_contains(point))
   //      {

   //         return true;

   //      }
   //      else
   //      {

   //         return false;

   //      }

   //   }
   //   else
   //   {

   //      return false;

   //   }

   //}


   bool region::internal_contains(const ::point_i32 & point)
   {

      return internal_contains(point_f64(point));

   }


   //bool region::internal_rectangle_contains(const ::point_i32 & point)
   //{

   //   return internal_rectangle_contains(point_f64(point));

   //}


   //bool region::internal_oval_contains(const ::point_i32 & point)
   //{

   //   return internal_oval_contains(point_f64(point));

   //}


   //bool region::internal_polygon_contains(const ::point_i32 & point)
   //{

   //   return internal_polygon_contains(point_f64(point));

   //}


   //bool region::internal_poly_polygon_contains(const ::point_i32 & point)
   //{

   //   return internal_poly_polygon_contains(point_f64(point));

   //}


   //bool region::internal_combine_contains(const ::point_i32 & point)
   //{

   //   return internal_combine_contains(point_f64(point));

   //}


} // namespace draw2d



