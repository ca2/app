// Created by camilo on 2022-06-25 09:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "region.h"
#include "region_shape.h"
#include "acme/primitive/geometry2d/_enhanced.h"
#include "acme/primitive/geometry2d/_collection_enhanced.h"
#include "acme/primitive/geometry2d/_defer_shape.h"


namespace draw2d
{

   void region::item::translate(const ::point_i32 & point)
   {


   }
   void region::item::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {


   }

   bool region::item::internal_contains(const ::point_f64 & p)
   {

      return false;

   }



   void region::rectangle_item::translate(const ::point_i32 & point)
   {

      m_rectangle.offset(point);

   }


   void region::rectangle_item::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {

      ::expand_bounding_box(rectangle, (::point_f64 *)&m_rectangle, 2);

   }


   bool region::rectangle_item::internal_contains(const ::point_f64 & p)
   {

      return m_rectangle.contains(p);

   }


   void region::ellipse_item::translate(const ::point_i32 & point)
   {

      m_rectangle.offset(point);

   }



   void region::ellipse_item::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {

      ::expand_bounding_box(rectangle, (::point_f64 *)&m_rectangle, 2);

   }


   bool region::ellipse_item::internal_contains(const ::point_f64 & p)
   {

      auto center = m_rectangle.center();

      auto radius = m_rectangle.size() / 2.0;

      if (radius.is_empty())
      {

         return false;

      }

      double x = p.x();

      double y = p.y();

      double Δx = x - center.x();

      double Δy = y - center.y();

      if (radius.cx() == radius.cy())
      {

         double r = radius.cx();

         double square_distance = (Δx * Δx) + (Δy * Δy);

         double square_boundary = (r * r);

         return square_distance <= square_boundary;

      }
      else
      {

         double normal_distance = ((Δx * Δx) / (radius.cx() * radius.cx()) + (Δy * Δy) / (radius.cx() * radius.cy()));

         return normal_distance <= 1.0;

      }

   }

   void region::polygon_item::translate(const ::point_i32 & point)
   {

      for (auto & pointVertex : m_polygon)
      {

         pointVertex += point;

      }

   }


   void region::polygon_item::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {

      ::expand_bounding_box(rectangle, m_polygon.data(), m_polygon.get_size());

   }


   bool region::polygon_item::internal_contains(const ::point_f64 & p)
   {

      return m_polygon.contains(p);

   }


   void region::poly_polygon_item::translate(const ::point_i32 & point)
   {

      for (auto & ppolygon : m_polygona)
      {

         for (auto & pointVertex : *ppolygon)
         {

            pointVertex += point;

         }

      }

   }


   void region::poly_polygon_item::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {

      for (auto & ppolygon : m_polygona)
      {

         for (auto & pointVertex : *ppolygon)
         {

            ::expand_bounding_box(rectangle, pointVertex);

         }

      }

   }


   bool region::poly_polygon_item::internal_contains(const ::point_f64 & p)
   {

      for (auto & ppolygon : m_polygona)
      {

         if (ppolygon->contains(p))
         {

            return true;

         }

      }

      return false;

   }


   void region::combine_item::translate(const ::point_i32 & point)
   {

      m_pregion1->translate(point);
      m_pregion2->translate(point);

   }


   void region::combine_item::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {
      // "fake" implementation

      m_pregion1->expand_bounding_box(rectangle, pgraphics);
      m_pregion2->expand_bounding_box(rectangle, pgraphics);

   }


   bool region::combine_item::internal_contains(const ::point_f64 & point)
   {

      if (m_ecombine == e_combine_add)
      {

         if (m_pregion1->internal_contains(point))
         {

            return true;

         }

         if (m_pregion2->internal_contains(point))
         {

            return true;

         }

         return false;

      }
      else if (m_ecombine == e_combine_exclude)
      {

         if (m_pregion2->internal_contains(point))
         {

            return false;

         }

         if (m_pregion1->internal_contains(point))
         {

            return true;

         }

         return false;

      }
      else if (m_ecombine == e_combine_intersect)
      {

         if (m_pregion1->internal_contains(point))
         {

            if (m_pregion2->internal_contains(point))
            {

               return true;

            }

         }

         return false;

      }
      else if (m_ecombine == e_combine_xor)
      {

         if (m_pregion1->internal_contains(point))
         {

            if (m_pregion2->internal_contains(point))
            {

               return false;

            }
            else
            {

               return true;

            }

         }
         else if (m_pregion2->internal_contains(point))
         {

            return true;

         }
         else
         {

            return false;

         }

      }
      else
      {

         return false;

      }

   }



   void region::round_rectangle_item::translate(const ::point_i32 & point)
   {

      m_rectangle.offset(point);

   }

   void region::round_rectangle_item::expand_bounding_box(::rectangle_f64 & rectangle, ::draw2d::graphics * pgraphics)
   {

      ::expand_bounding_box(rectangle, (::point_f64 *)&m_rectangle, 2);

   }


   bool region::round_rectangle_item::internal_contains(const ::point_f64 & point)
   {

      // "fake" implementation

      return m_rectangle.contains(point);

   }


} // namespace draw2d



