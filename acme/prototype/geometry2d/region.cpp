// From aura/graphics/draw2d/region by camilo on 2023-05-26 13:55 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "ellipse.h"
#include "item.h"
#include "region.h"
#include "acme/exception/interface_only.h"
#include "_defer_item.h"


namespace geometry2d
{



   region::region()
   {

      //m_eregion = ::draw2d::e_region_none;
      //m_lppoints        = nullptr;
      //m_lppolycounts    = nullptr;

   }


   region::region(const region & region)
   {

      //m_lppolycounts    = nullptr;
      //m_lppoints        = nullptr;
      //m_eregion = ::draw2d::e_region_none;

      m_pitem = region.m_pitem->clone();

   }


   region::~region()
   {

      destroy();

   }

   //void region::destroy()
   //{

   //   m_pitem.release();
   //   //::acme::adel(m_lppoints);
   //   //::acme::adel(m_lppolycounts);
   //   //m_pregion1.release();
   //   //m_pregion2.release();

   //   //return ::success;

   //}


   bool region::create_rectangle(const ::double_rectangle & rectangle)
   {

      if (m_pitem)
      {

         destroy();

      }

      //m_eregion = ::draw2d::e_region_rect;

      auto pitem = __create_new < rectangle_item >();

      pitem->m_item = rectangle;

      m_pitem = pitem;

      return true;

   }


   bool region::create_ellipse(const ::double_ellipse & ellipse)
   {

      if (m_pitem)
      {

         destroy();

      }

      //m_eregion = ::draw2d::e_region_ellipse;

      auto pitem = __create_new < ellipse_item >();

      pitem->m_item = ellipse;

      m_pitem = pitem;

      return true;

   }


   bool region::create_polygon(const ::double_point * ppoints, int nCount, ::draw2d::enum_fill_mode efillmode)
   {

      //if (m_eregion != ::draw2d::e_region_none)
      if (m_pitem)
      {

         destroy();

      }

      //m_eregion = ::draw2d::e_region_polygon;

      auto pitem = __create_new < polygon_item >();

      pitem->m_polygon.set_size(nCount);

      memory_copy(pitem->m_polygon.data(), ppoints, pitem->m_polygon.get_size_in_bytes());

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;

   }




   bool region::create_polygon(const double_polygon & polygon, ::draw2d::enum_fill_mode efillmode)
   {

      return create_polygon(polygon.data(), (int)polygon.size(), efillmode);

   }


   bool region::create_polygon(const ::int_point * ppoints, int nCount, ::draw2d::enum_fill_mode efillmode)
   {

      //if (m_eregion != ::draw2d::e_region_none)
      //if(m_pitem)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_polygon;

      auto pitem = __create_new < polygon_item>();

      pitem->m_polygon.set_size(nCount);

      for (int i = 0; i < nCount; i++)
      {

         auto & p = pitem->m_polygon[i];

         p = (const ::int_point &)ppoints[i];

      }

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;


   }



   bool region::create_poly_polygon(const ::double_point * ppoints, const int * ppolycounts, int nCount, ::draw2d::enum_fill_mode efillmode)
   {

      //if (m_eregion != ::draw2d::e_region_none)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_polygon;

      auto pitem = __create_new < poly_polygon_item >();

      pitem->m_polypolygon.set_size(nCount);

      for (::collection::index i = 0; i < nCount; i++)
      {

         pitem->m_polypolygon[i] = __allocate double_polygon();

         pitem->m_polypolygon[i]->set_size(ppolycounts[i]);

         for (::collection::index j = 0; j < ppolycounts[i]; j++)
         {

            pitem->m_polypolygon[i]->element_at(j).x() = ppoints->x();

            pitem->m_polypolygon[i]->element_at(j).y() = ppoints->y();

            ppoints++;

         }

      }

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;

   }



   bool region::create_poly_polygon(const ::int_point * ppoints, const int * ppolycounts, int nCount, ::draw2d::enum_fill_mode efillmode)
   {

      //if (m_eregion != ::draw2d::e_region_none)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_poly_polygon;

      auto pitem = __create_new < poly_polygon_item >();

      pitem->m_polypolygon.set_size(nCount);

      for (::collection::index i = 0; i < nCount; i++)
      {

         pitem->m_polypolygon[i] = __allocate double_polygon();

         pitem->m_polypolygon[i]->set_size(ppolycounts[i]);

         for (::collection::index j = 0; j < ppolycounts[i]; j++)
         {

            pitem->m_polypolygon[i]->element_at(j).x() = ppoints->x();

            pitem->m_polypolygon[i]->element_at(j).y() = ppoints->y();

            ppoints++;

         }

      }

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;

   }


   bool region::create_poly_polygon(const ::double_poly_polygon & polypolygon, ::draw2d::enum_fill_mode efillmode)
   {

      ////if (m_eregion != ::draw2d::e_region_none)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_poly_polygon;

      auto pitem = __create_new < poly_polygon_item >();

      pitem->m_polypolygon = polypolygon;

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;

   }


   bool region::combine(const ::geometry2d::region * prgn1, const ::geometry2d::region * prgn2, ::draw2d::enum_combine ecombine)
   {

      ::pointer<::geometry2d::region>pregion1 = (::geometry2d::region *)prgn1;

      ::pointer<::geometry2d::region>pregion2 = (::geometry2d::region *)prgn2;

      //if (m_eregion != ::draw2d::e_region_none)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_combine;

      auto pitem = __create_new < combine_item >();

      pitem->m_pregion1 = pregion1;

      pitem->m_pregion2 = pregion2;

      pitem->m_ecombine = ecombine;

      m_pitem = pitem;

      return true;

   }




   region & region::operator = (const ::geometry2d::region & regionSrc)
   {

      if (this == &regionSrc)
      {

         return *this;

      }

      if (!regionSrc.m_pitem)
      {

         m_pitem.release();

      }
      else
      {

         m_pitem = m_pitem->clone();

      }

      //if (m_eregion != ::draw2d::e_region_none)
      //{

      //   destroy();

      //}

      //auto eitem = regionSrc.type();

      //switch (eitem)
      //{
      //case ::draw2d::e_item_none:
      //   return *this;
      //case ::draw2d::e_item_rectangle:
      //case ::draw2d::e_region_ellipse:
      //   m_pitem = regionSrc.m_pitem->clone();
      //   return *this;
      //case ::draw2d::e_region_polygon:
      //   m_pitem = regionSrc.m_pitem->clone();
      //   return *this;
      //case ::draw2d::e_region_poly_polygon:
      //{
      //   m_pitem = regionSrc.m_pitem->clone();
      //}
      //return *this;
      //case ::draw2d::e_region_round_rect:
      //   m_pitem = regionSrc.m_pitem->clone();
      //   return *this;
      //case ::draw2d::e_region_combine:
      //   m_pitem = regionSrc.m_pitem->clone();
      //   return *this;
      //default:
      //   throw ::interface_only();
      //};
      return *this;

   }


   bool region::get_bounding_box(::double_rectangle & rectangle)
   {

      if (!m_pitem)
      {

         return false;

      }

      rectangle.maximum_minimum();

      expand_bounding_box(rectangle);

      return true;

   }


   void region::expand_bounding_box(::double_rectangle & rectangle)
   {

      if (!m_pitem)
      {

         return;

      }

      m_pitem->expand_bounding_box(rectangle);

      //throw ::interface_only();

      //return true;

   }


   bool region::contains(const ::double_point & point)
   {
      
      if(!m_pitem)
      {
         
         return false;
         
      }

      auto bContains = m_pitem->contains(point);
      
      if(!bContains)
      {
         
         return false;
         
      }
      
      return true;

   }



   bool region::translate(const ::double_point & point)
   {

      //set_modified();

      if (m_pitem)
      {

         m_pitem->translate(point);

      }

      return true;

   }


   //bool region::contains(const ::double_point & point)
   //{

   //   return internal_contains(point);

   //}


   //void region::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //   ::double_rectangle rectangleMaxBounding;

   //   expand_bounding_box(rectangleMaxBounding);

   //   rectangle = rectangleMaxBounding;

   //}


   //void region::expand_bounding_box(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::double_rectangle rectangle;

   //   max_bounding_box_rect(rectangle);

   //   copy(prectangle, rectangle);


   //}


   //void region::max_bounding_box_oval(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::double_rectangle rectangle;

   //   max_bounding_box_oval(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_polygon(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::double_rectangle rectangle;

   //   max_bounding_box_polygon(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_poly_polygon(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::double_rectangle rectangle;

   //   max_bounding_box_poly_polygon(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_combine(::int_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::double_rectangle rectangle;

   //   max_bounding_box_combine(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //   if (m_pitem)
   //   {

   //      m_pitem->expand_bounding_box(rectangle);

   //   }

   //}


   //void region::max_bounding_box_rect(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if (m_pitem)
   //   {

   //      m_pitem->max_bounding_box_rect(prectangle, pgraphics);

   //   }

   //}


   //void region::max_bounding_box_oval(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if (m_pitem)
   //   {

   //      m_pitem->max_bounding_box_rect(prectangle, pgraphics);

   //   }


   //}


   //void region::max_bounding_box_polygon(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if(m_nCount <= 0)
   //   {

   //      return;
   //      
   //   }

   //   for(int i = 0; i < m_nCount; i++)
   //   {

   //      prectangle->left() = minimum(prectangle->left(),m_lppoints[i].x());

   //      prectangle->right() = maximum(prectangle->right(),m_lppoints[i].x());

   //      prectangle->top() = minimum(prectangle->left(),m_lppoints[i].y());

   //      prectangle->bottom() = maximum(prectangle->right(),m_lppoints[i].y());

   //   }

   //}


   //void region::max_bounding_box_poly_polygon(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   int n = 0;

   //   for(int i = 0; i < m_nCount; i++)
   //   {

   //      int iCount = m_lppolycounts[i];

   //      for(int j = 0; j < iCount; j++,n++)
   //      {

   //         prectangle->left() = minimum(prectangle->left(),m_lppoints[n].x());

   //         prectangle->right() = maximum(prectangle->right(),m_lppoints[n].x());

   //         prectangle->top() = minimum(prectangle->left(),m_lppoints[n].y());

   //         prectangle->bottom() = maximum(prectangle->right(),m_lppoints[n].y());

   //      }

   //   }

   //}


   //void region::max_bounding_box_combine(::double_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   m_pregion1->expand_bounding_box(prectangle);

   //   m_pregion2->expand_bounding_box(prectangle);

   //}


   bool region::internal_contains(const ::double_point & point)
   {

      if (m_pitem)
      {

         return m_pitem->contains(point);

      }

      return false;

   }


   //bool region::internal_rectangle_contains(const ::double_point & point)
   //{

   //   return point.x() >= m_x1 && point.y() >= m_y1 && point.x() <= m_x2 && point.y() <= m_y2;

   //}


   //bool region::internal_oval_contains(const ::double_point & point)
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


   //bool region::internal_polygon_contains(const ::double_point & point)
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


   //bool region::internal_poly_polygon_contains(const ::double_point & point)
   //{

   //   int n = 0;

   //   for(int i = 0; i < m_nCount; i++)
   //   {

   //      int iCount = m_lppolycounts[i];

   //      if (::polygon_contains_point(&m_lppoints[n], iCount, point))
   //      {

   //         return true;

   //      }

   //      n += iCount;

   //   }

   //   return false;

   //}


   //bool region::internal_combine_contains(const ::double_point & point)
   //{

   //   if(m_ecombine == e_combine_add)
   //   {

   //      if (m_pregion1->contains(point))
   //      {

   //         return true;

   //      }

   //      if (m_pregion2->contains(point))
   //      {

   //         return true;

   //      }

   //      return false;

   //   }
   //   else if(m_ecombine == e_combine_exclude)
   //   {

   //      if (m_pregion2->contains(point))
   //      {

   //         return false;

   //      }

   //      if (m_pregion1->contains(point))
   //      {

   //         return true;

   //      }

   //      return false;

   //   }
   //   else if(m_ecombine == e_combine_intersect)
   //   {
   //      
   //      if(m_pregion1->contains(point))
   //      {

   //         if (m_pregion2->contains(point))
   //         {

   //            return true;

   //         }

   //      }

   //      return false;

   //   }
   //   else if(m_ecombine == e_combine_xor)
   //   {
   //      
   //      if(m_pregion1->contains(point))
   //      {

   //         if (m_pregion2->contains(point))
   //         {

   //            return false;

   //         }
   //         else
   //         {

   //            return true;

   //         }

   //      }
   //      else if(m_pregion2->contains(point))
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


   //bool region::contains(const ::int_point & point)
   //{

   //   return internal_contains(double_point(point));

   //}


   //bool region::internal_rectangle_contains(const ::int_point & point)
   //{

   //   return internal_rectangle_contains(double_point(point));

   //}


   //bool region::internal_oval_contains(const ::int_point & point)
   //{

   //   return internal_oval_contains(double_point(point));

   //}


   //bool region::internal_polygon_contains(const ::int_point & point)
   //{

   //   return internal_polygon_contains(double_point(point));

   //}


   //bool region::internal_poly_polygon_contains(const ::int_point & point)
   //{

   //   return internal_poly_polygon_contains(double_point(point));

   //}


   //bool region::internal_combine_contains(const ::int_point & point)
   //{

   //   return internal_combine_contains(double_point(point));

   //}



} // namespace geometry2d



