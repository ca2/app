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


   bool region::create_rectangle(const ::f64_rectangle & rectangle)
   {

      if (m_pitem)
      {

         destroy();

      }

      //m_eregion = ::draw2d::e_region_rect;

      auto pitem = create_newø < rectangle_item >();

      pitem->m_item = rectangle;

      m_pitem = pitem;

      return true;

   }


   bool region::create_ellipse(const ::f64_ellipse & ellipse)
   {

      if (m_pitem)
      {

         destroy();

      }

      //m_eregion = ::draw2d::e_region_ellipse;

      auto pitem = create_newø < ellipse_item >();

      pitem->m_item = ellipse;

      m_pitem = pitem;

      return true;

   }


   bool region::create_polygon(const ::f64_point * ppoints, ::i32 nCount, ::draw2d::enum_fill_mode efillmode)
   {

      //if (m_eregion != ::draw2d::e_region_none)
      if (m_pitem)
      {

         destroy();

      }

      //m_eregion = ::draw2d::e_region_polygon;

      auto pitem = create_newø < polygon_item >();

      pitem->m_polygon.set_size(nCount);

      memory_copy(pitem->m_polygon.data(), ppoints, pitem->m_polygon.get_size_in_bytes());

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;

   }




   bool region::create_polygon(const f64_polygon & polygon, ::draw2d::enum_fill_mode efillmode)
   {

      return create_polygon(polygon.data(), (::i32)polygon.size(), efillmode);

   }


   bool region::create_polygon(const ::i32_point * ppoints, ::i32 nCount, ::draw2d::enum_fill_mode efillmode)
   {

      //if (m_eregion != ::draw2d::e_region_none)
      //if(m_pitem)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_polygon;

      auto pitem = create_newø < polygon_item>();

      pitem->m_polygon.set_size(nCount);

      for (::i32 i = 0; i < nCount; i++)
      {

         auto & p = pitem->m_polygon[i];

         p = (const ::i32_point &)ppoints[i];

      }

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;


   }



   bool region::create_poly_polygon(const ::f64_point * ppoints, const ::i32 * ppolycounts, ::i32 nCount, ::draw2d::enum_fill_mode efillmode)
   {

      //if (m_eregion != ::draw2d::e_region_none)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_polygon;

      auto pitem = create_newø < poly_polygon_item >();

      pitem->m_polypolygon.set_size(nCount);

      for (::collection::index i = 0; i < nCount; i++)
      {

         pitem->m_polypolygon[i] = allocateø array_particle< f64_polygon >();

         pitem->m_polypolygon[i]->set_size(ppolycounts[i]);

         for (::collection::index j = 0; j < ppolycounts[i]; j++)
         {

            pitem->m_polypolygon[i]->element_at(j).x = ppoints->x;

            pitem->m_polypolygon[i]->element_at(j).y = ppoints->y;

            ppoints++;

         }

      }

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;

   }



   bool region::create_poly_polygon(const ::i32_point * ppoints, const ::i32 * ppolycounts, ::i32 nCount, ::draw2d::enum_fill_mode efillmode)
   {

      //if (m_eregion != ::draw2d::e_region_none)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_poly_polygon;

      auto pitem = create_newø < poly_polygon_item >();

      pitem->m_polypolygon.set_size(nCount);

      for (::collection::index i = 0; i < nCount; i++)
      {

         pitem->m_polypolygon[i] = allocateø f64_polygon();

         pitem->m_polypolygon[i]->set_size(ppolycounts[i]);

         for (::collection::index j = 0; j < ppolycounts[i]; j++)
         {

            pitem->m_polypolygon[i]->element_at(j).x = ppoints->x;

            pitem->m_polypolygon[i]->element_at(j).y = ppoints->y;

            ppoints++;

         }

      }

      pitem->m_efillmode = efillmode;

      m_pitem = pitem;

      return true;

   }


   bool region::create_poly_polygon(const ::f64_poly_polygon & polypolygon, ::draw2d::enum_fill_mode efillmode)
   {

      ////if (m_eregion != ::draw2d::e_region_none)
      //{

      //   destroy();

      //}

      //m_eregion = ::draw2d::e_region_poly_polygon;

      auto pitem = create_newø < poly_polygon_item >();

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

      auto pitem = create_newø < combine_item >();

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


   bool region::get_bounding_box(::f64_rectangle & rectangle)
   {

      if (!m_pitem)
      {

         return false;

      }

      rectangle.maximum_minimum();

      expand_bounding_box(rectangle);

      return true;

   }


   void region::expand_bounding_box(::f64_rectangle & rectangle)
   {

      if (!m_pitem)
      {

         return;

      }

      m_pitem->expand_bounding_box(rectangle);

      //throw ::interface_only();

      //return true;

   }


   bool region::contains(const ::f64_point & point)
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



   bool region::translate(const ::f64_point & point)
   {

      //set_modified();

      if (m_pitem)
      {

         m_pitem->translate(point);

      }

      return true;

   }


   //bool region::contains(const ::f64_point & point)
   //{

   //   return internal_contains(point);

   //}


   //void region::expand_bounding_box(::f64_rectangle & rectangle)
   //{

   //   ::f64_rectangle rectangleMaxBounding;

   //   expand_bounding_box(rectangleMaxBounding);

   //   rectangle = rectangleMaxBounding;

   //}


   //void region::expand_bounding_box(::i32_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::f64_rectangle rectangle;

   //   max_bounding_box_rect(rectangle);

   //   copy(prectangle, rectangle);


   //}


   //void region::max_bounding_box_oval(::i32_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::f64_rectangle rectangle;

   //   max_bounding_box_oval(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_polygon(::i32_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::f64_rectangle rectangle;

   //   max_bounding_box_polygon(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_poly_polygon(::i32_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::f64_rectangle rectangle;

   //   max_bounding_box_poly_polygon(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::max_bounding_box_combine(::i32_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::f64_rectangle rectangle;

   //   max_bounding_box_combine(rectangle);

   //   copy(prectangle, rectangle);

   //}


   //void region::expand_bounding_box(::f64_rectangle & rectangle)
   //{

   //   if (m_pitem)
   //   {

   //      m_pitem->expand_bounding_box(rectangle);

   //   }

   //}


   //void region::max_bounding_box_rect(::f64_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if (m_pitem)
   //   {

   //      m_pitem->max_bounding_box_rect(prectangle, pgraphics);

   //   }

   //}


   //void region::max_bounding_box_oval(::f64_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if (m_pitem)
   //   {

   //      m_pitem->max_bounding_box_rect(prectangle, pgraphics);

   //   }


   //}


   //void region::max_bounding_box_polygon(::f64_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   if(m_nCount <= 0)
   //   {

   //      return;
   //      
   //   }

   //   for(::i32 i = 0; i < m_nCount; i++)
   //   {

   //      prectangle->left = minimum(prectangle->left,m_lppoints[i].x);

   //      prectangle->right = maximum(prectangle->right,m_lppoints[i].x);

   //      prectangle->top = minimum(prectangle->left,m_lppoints[i].y);

   //      prectangle->bottom = maximum(prectangle->right,m_lppoints[i].y);

   //   }

   //}


   //void region::max_bounding_box_poly_polygon(::f64_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   ::i32 n = 0;

   //   for(::i32 i = 0; i < m_nCount; i++)
   //   {

   //      ::i32 iCount = m_lppolycounts[i];

   //      for(::i32 j = 0; j < iCount; j++,n++)
   //      {

   //         prectangle->left = minimum(prectangle->left,m_lppoints[n].x);

   //         prectangle->right = maximum(prectangle->right,m_lppoints[n].x);

   //         prectangle->top = minimum(prectangle->left,m_lppoints[n].y);

   //         prectangle->bottom = maximum(prectangle->right,m_lppoints[n].y);

   //      }

   //   }

   //}


   //void region::max_bounding_box_combine(::f64_rectangle * prectangle, ::draw2d::graphics * pgraphics)
   //{

   //   m_pregion1->expand_bounding_box(prectangle);

   //   m_pregion2->expand_bounding_box(prectangle);

   //}


   bool region::internal_contains(const ::f64_point & point)
   {

      if (m_pitem)
      {

         return m_pitem->contains(point);

      }

      return false;

   }


   //bool region::internal_rectangle_contains(const ::f64_point & point)
   //{

   //   return point.x >= m_x1 && point.y >= m_y1 && point.x <= m_x2 && point.y <= m_y2;

   //}


   //bool region::internal_oval_contains(const ::f64_point & point)
   //{

   //   ::f64 centerx    = (m_x2 + m_x1) / 2.0;
   //   ::f64 centery    = (m_y2 + m_y1) / 2.0;

   //   ::f64 rx    = fabs(m_x2 - m_x1) / 2.0;
   //   ::f64 ry    = fabs(m_y2 - m_y1) / 2.0;

   //   if (rx == 0.0 || ry == 0.0)
   //   {

   //      return false;

   //   }
   //
   //   ::f64 x = point.x;

   //   ::f64 y = point.y;
   //   
   //   ::f64 Δx = x - centerx;
   //   
   //   ::f64 Δy = y - centery;
   //   
   //   if(rx == ry)
   //   {
   //      
   //      ::f64 r = rx;
   //      
   //      ::f64 square_distance = (Δx * Δx) + (Δy * Δy);
   //      
   //      ::f64 square_boundary = (r * r);
   //      
   //      return square_distance <= square_boundary;
   //            
   //   }
   //   else
   //   {

   //      ::f64 normal_distance = ((Δx * Δx) / (rx * rx) + (Δy * Δy) / (ry * ry));
   //      
   //      return normal_distance <= 1.0;
   //      
   //   }

   //}


   //bool region::internal_polygon_contains(const ::f64_point & point)
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


   //bool region::internal_poly_polygon_contains(const ::f64_point & point)
   //{

   //   ::i32 n = 0;

   //   for(::i32 i = 0; i < m_nCount; i++)
   //   {

   //      ::i32 iCount = m_lppolycounts[i];

   //      if (::polygon_contains_point(&m_lppoints[n], iCount, point))
   //      {

   //         return true;

   //      }

   //      n += iCount;

   //   }

   //   return false;

   //}


   //bool region::internal_combine_contains(const ::f64_point & point)
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


   //bool region::contains(const ::i32_point & point)
   //{

   //   return internal_contains(::f64_point(point));

   //}


   //bool region::internal_rectangle_contains(const ::i32_point & point)
   //{

   //   return internal_rectangle_contains(::f64_point(point));

   //}


   //bool region::internal_oval_contains(const ::i32_point & point)
   //{

   //   return internal_oval_contains(::f64_point(point));

   //}


   //bool region::internal_polygon_contains(const ::i32_point & point)
   //{

   //   return internal_polygon_contains(::f64_point(point));

   //}


   //bool region::internal_poly_polygon_contains(const ::i32_point & point)
   //{

   //   return internal_poly_polygon_contains(::f64_point(point));

   //}


   //bool region::internal_combine_contains(const ::i32_point & point)
   //{

   //   return internal_combine_contains(::f64_point(point));

   //}



} // namespace geometry2d



