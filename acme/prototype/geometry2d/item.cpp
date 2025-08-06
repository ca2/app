// From aura/graphics/draw2d/region_item by camilo on 2023-05-26 14:21 <3ThomasBorregaardSorensen!!
// Created by camilo on 2022-06-25 09:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "item.h"
#include "region.h"
//#include "region_shape.h"
//#include "acme/prototype/geometry2d/_enhanced.h"
//#include "acme/prototype/geometry2d/_collection_enhanced.h"
//#include "acme/prototype/geometry2d/_defer_shape.h"


namespace geometry2d
{


   item::item()
   {


   }


   item::~item()
   {



   }


   ::draw2d::enum_item item::type() const 
   {
      
      return ::draw2d::e_item_none; 
   
   }


   void item::translate(const ::double_point & point)
   {


   }


   bool item::contains(const ::double_point & point)
   {

      return false;

   }


   void item::expand_bounding_box(::double_rectangle & rectangle)
   {


   }


   begin_figure_item::begin_figure_item()
   {


   }


   begin_figure_item::~begin_figure_item()
   {


   }


   ::draw2d::enum_item begin_figure_item::type() const 
   {
      
      return ::draw2d::e_item_begin_figure; 
   
   }


   close_figure_item::close_figure_item()
   {


   }


   close_figure_item::~close_figure_item()
   {


   }


   ::draw2d::enum_item close_figure_item::type() const 
   {
      
      return ::draw2d::e_item_close_figure; 
   
   }


   end_figure_item::end_figure_item()
   {


   }


   end_figure_item::~end_figure_item()
   {



   }


   ::draw2d::enum_item end_figure_item::type() const
   {

      return ::draw2d::e_item_end_figure;

   }

   intersect_clip_item::intersect_clip_item()
   {


   }


   intersect_clip_item::~intersect_clip_item()
   {


   }

   ::draw2d::enum_item intersect_clip_item::type() const
   {

      return ::draw2d::e_item_intersect_clip;

   }


//
   //void item::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //}


   //::draw2d::enum_item rectangle_item::type() const 
   //{
   //   
   //   return ::draw2d::e_item_rectangle; 
   //
   //}


   //void rectangle_item::translate(const ::int_point & point)
   //{

   //   m_rectangle.offset(point);

   //}



   //bool rectangle_item::contains(const ::double_point & p)
   //{

   //   return m_rectangle.contains(p);

   //}



   //void rectangle_item::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //   ::expand_bounding_box(rectangle, m_rectangle);

   //}

   //void rectangle_item::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //   rectangle.left() = ::minimum(m_rectangle.left(), rectangle.left());
   //   rectangle.top() = ::minimum(m_rectangle.top(), rectangle.top());
   //   rectangle.right() = ::minimum(m_rectangle.right(), rectangle.right());
   //   rectangle.bottom() = ::minimum(m_rectangle.bottom(), rectangle.bottom());

   //}


   //::draw2d::enum_item ellipse_item::type() const 
   //{
   //   
   //   return ::draw2d::e_item_ellipse;
   //
   //}


   //void ellipse_item::translate(const ::int_point & point)
   //{

   //   m_ellipse.offset(point);

   //}


   ////void ellipse_item::expand_bounding_box(::double_rectangle & rectangle)
   ////{

   ////   ::expand_bounding_box(rectangle, (::double_point *)&m_ellipse, 2);

   ////}


   //bool ellipse_item::contains(const ::double_point & p)
   //{

   //   auto center = m_ellipse.center();

   //   auto radius = m_ellipse.size() / 2.0;

   //   if (radius.is_empty())
   //   {

   //      return false;

   //   }

   //   double x = p.x();

   //   double y = p.y();

   //   double Δx = x - center.x();

   //   double Δy = y - center.y();

   //   if (radius.cx() == radius.cy())
   //   {

   //      double r = radius.cx();

   //      double square_distance = (Δx * Δx) + (Δy * Δy);

   //      double square_boundary = (r * r);

   //      return square_distance <= square_boundary;

   //   }
   //   else
   //   {

   //      double normal_distance = ((Δx * Δx) / (radius.cx() * radius.cx()) + (Δy * Δy) / (radius.cx() * radius.cy()));

   //      return normal_distance <= 1.0;

   //   }

   //}


   //void ellipse_item::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //   ::expand_bounding_box(rectangle, m_ellipse);/* rectangleleft = ::minimum(m_rectangle.left(), rectangle.left());
   //   rectangle.top() = ::minimum(m_rectangle.top(), rectangle.top());
   //   rectangle.right() = ::minimum(m_rectangle.right(), rectangle.right());
   //   rectangle.bottom() = ::minimum(m_rectangle.bottom(), rectangle.bottom());*/

   //}


   //::draw2d::enum_item arc_item::type() const
   //{
   //   
   //   return ::draw2d::e_item_arc; 
   //
   //}


   //void arc_item::translate(const ::int_point & point)
   //{

   //   m_arc.offset(point);

   //}


   ////void arc_item::expand_bounding_box(::double_rectangle & rectangle)
   ////{

   ////   //::expand_bounding_box(rectangle, (::double_point *)&m_rectangle, 2);

   ////   ::expand_bounding_box(rectangle, m_arc);

   ////}


   //bool arc_item::contains(const ::double_point & p)
   //{

   //   //return m_rectangle.contains(p);
   //   throw ::exception(error_not_implemented);

   //}


   //void arc_item::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //   ::expand_bounding_box(rectangle, m_arc);
   //   //rectangle.left() = ::minimum(m_rectangle.left(), rectangle.left());
   //   //rectangle.top() = ::minimum(m_rectangle.top(), rectangle.top());
   //   //rectangle.right() = ::minimum(m_rectangle.right(), rectangle.right());
   //   //rectangle.bottom() = ::minimum(m_rectangle.bottom(), rectangle.bottom());

   //}

   polygon_item::polygon_item()
   {


   }


   polygon_item::~polygon_item()
   {


   }





   ::draw2d::enum_item polygon_item::type() const 
   {
      
      return ::draw2d::e_item_polygon; 
   
   }


   void polygon_item::translate(const ::double_point & point)
   {

      m_polygon.offset(point);

   }


   //void polygon_item::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //   ::expand_bounding_box(rectangle, m_polygon.data(), m_polygon.get_size());

   //}


   bool polygon_item::contains(const ::double_point & p)
   {

      if (m_efillmode == ::draw2d::e_fill_mode_winding)
      {

         return m_polygon.contains(p);

      }
      else
      {

         return m_polygon.contains_alternate(p);

      }

   }


   void polygon_item::expand_bounding_box(::double_rectangle & rectangle)
   {

      m_polygon.expand_bounding_box(rectangle.top_left(), rectangle.bottom_right());

   }



   
   //::draw2d::enum_item poly_polygon_item::type() const 
   //{
   //   
   //   return ::draw2d::e_item_poly_polygon; 
   //
   //}

   poly_polygon_item::poly_polygon_item()
   {


   }


   poly_polygon_item::~poly_polygon_item()
   {


   }

   void poly_polygon_item::translate(const ::double_point & point)
   {

      for (auto & ppolygon : m_polypolygon)
      {

         ppolygon->offset(point);
         //{

         //   pointVertex += point;

         //}

      }

   }

   
   bool poly_polygon_item::contains(const ::double_point & point)
   {

      for (auto & ppolygon : m_polypolygon)
      {

         if (m_efillmode == ::draw2d::e_fill_mode_winding)
         {

            if (ppolygon->contains(point))
            {

               return true;

            }

         }
         else if (m_efillmode == ::draw2d::e_fill_mode_alternate)
         {

            if (ppolygon->contains_alternate(point))
            {

               return true;

            }

         }
         else
         {

            throw ::exception(error_wrong_state, "poly_polygon_item::contains not expected fill mode");

         }

      }
   
      return false;

   }

   //   }

   //}


   void poly_polygon_item::expand_bounding_box(::double_rectangle & rectangle)
   {

      m_polypolygon.expand_bounding_box(rectangle.top_left(), rectangle.bottom_right());

   }


   //void poly_polygon_item::expand_bounding_box(::double_rectangle & rectangle)
   //{

   //   ::expand_bounding_box(rectangle, m_polypolygon);

   //}

   combine_item::combine_item()
   {


   }


   combine_item::~combine_item()
   {


   }


   ::draw2d::enum_item combine_item::type() const 
   {
      
      return ::draw2d::e_item_combine; 
   
   }


   void combine_item::translate(const ::double_point & point)
   {

      m_pregion1->translate(point);
      m_pregion2->translate(point);

   }


   void combine_item::expand_bounding_box(::double_rectangle & rectangle)
   {
      // "fake" implementation

      m_pregion1->expand_bounding_box(rectangle);
      m_pregion2->expand_bounding_box(rectangle);

   }


   bool combine_item::contains(const ::double_point & point)
   {

      if (m_ecombine == ::draw2d::e_combine_add)
      {

         if (m_pregion1->contains(point))
         {

            return true;

         }

         if (m_pregion2->contains(point))
         {

            return true;

         }

         return false;

      }
      else if (m_ecombine == ::draw2d::e_combine_exclude)
      {

         if (m_pregion2->contains(point))
         {

            return false;

         }

         if (m_pregion1->contains(point))
         {

            return true;

         }

         return false;

      }
      else if (m_ecombine == ::draw2d::e_combine_intersect)
      {

         if (m_pregion1->contains(point))
         {

            if (m_pregion2->contains(point))
            {

               return true;

            }

         }

         return false;

      }
      else if (m_ecombine == ::draw2d::e_combine_xor)
      {

         if (m_pregion1->contains(point))
         {

            if (m_pregion2->contains(point))
            {

               return false;

            }
            else
            {

               return true;

            }

         }
         else if (m_pregion2->contains(point))
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


   void round_rectangle_item::translate(const ::double_point & point)
   {

      m_rectangle.offset(point);

   }


   void round_rectangle_item::expand_bounding_box(::double_rectangle & rectangle)
   {

      m_rectangle.expand_bounding_box(rectangle.top_left(), rectangle.bottom_right());

   }


   bool round_rectangle_item::contains(const ::double_point & point)
   {

      // "fake" implementation

      return m_rectangle.contains(point);

   }


   ::subparticle_pointer combine_item::clone()
   {

      auto pitem = __allocate combine_item();

      pitem->m_pregion1 = m_pregion1->clone();

      pitem->m_pregion2 = m_pregion2->clone();

      pitem->m_ecombine = m_ecombine;

      return pitem;

   }



} // namespace geometry2d



