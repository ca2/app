// Created by camilo on 2022-06-25 09:18 <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "aura/graphics/draw2d/_component.h"
#include "region_shape.h"
#include "_defer.h"


namespace draw2d
{

   void region::item::translate(const POINT_I32 & point)
   {


   }
   void region::item::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {


   }

   bool region::item::internal_contains(const POINT_F64 & p)
   {

      return false;

   }



   void region::rectangle_item::translate(const POINT_I32 & point)
   {

      m_rectangle.offset(point);

   }

   void region::rectangle_item::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::max_bounding_box(prectangle, (POINT_F64 *)&m_rectangle, 2);

   }

   bool region::rectangle_item::internal_contains(const POINT_F64 & p)
   {

      return m_rectangle.contains(p);

   }


   void region::ellipse_item::translate(const POINT_I32 & point)
   {

      m_rectangle.offset(point);

   }



   void region::ellipse_item::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::max_bounding_box(prectangle, (POINT_F64 *)&m_rectangle, 2);

   }


   bool region::ellipse_item::internal_contains(const POINT_F64 & p)
   {

      auto center = m_rectangle.center();

      auto radius = m_rectangle.size() / 2.0;

      if (radius.is_empty())
      {

         return false;

      }

      double x = p.x;

      double y = p.y;

      double dx = x - center.x;

      double dy = y - center.y;

      if (radius.cx == radius.cy)
      {

         double r = radius.cx;

         double square_distance = (dx * dx) + (dy * dy);

         double square_boundary = (r * r);

         return square_distance <= square_boundary;

      }
      else
      {

         double normal_distance = ((dx * dx) / (radius.cx * radius.cx) + (dy * dy) / (radius.cx * radius.cy));

         return normal_distance <= 1.0;

      }

   }

   void region::polygon_item::translate(const POINT_I32 & point)
   {

      for (auto & pointVertex : m_polygon)
      {

         pointVertex += point;

      }

   }

   void region::polygon_item::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::max_bounding_box(prectangle, m_polygon.get_data(), m_polygon.get_size());

   }

   bool region::polygon_item::internal_contains(const POINT_F64 & p)
   {

      return m_polygon.contains(p);

   }


   void region::poly_polygon_item::translate(const POINT_I32 & point)
   {

      for (auto & ppolygon : m_polygona)
      {

         for (auto & pointVertex : *ppolygon)
         {

            pointVertex += point;

         }

      }

   }


   void region::poly_polygon_item::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      for (auto & ppolygon : m_polygona)
      {

         for (auto & pointVertex : *ppolygon)
         {

            ::max_bounding_box(prectangle, pointVertex);

         }

      }

   }


   bool region::poly_polygon_item::internal_contains(const POINT_F64 & p)
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


   void region::combine_item::translate(const POINT_I32 & point)
   {

      m_pregion1->translate(point);
      m_pregion2->translate(point);

   }

   void region::combine_item::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {
      // "fake" implementation

      m_pregion1->max_bounding_box(prectangle, pgraphics);
      m_pregion2->max_bounding_box(prectangle, pgraphics);

   }
   bool region::combine_item::internal_contains(const POINT_F64 & point)
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



   void region::round_rectangle_item::translate(const POINT_I32 & point)
   {

      m_rectangle.offset(point);

   }

   void region::round_rectangle_item::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::max_bounding_box(prectangle, (POINT_F64 *)&m_rectangle, 2);

   }


   bool region::round_rectangle_item::internal_contains(const POINT_F64 & point)
   {

      // "fake" implementation

      return m_rectangle.contains(point);

   }



} // namespace draw2d



