#include "framework.h"
#include "path.h"
#include "acme/exception/interface_only.h"
//#include "aura/graphics/write_text/_.h"
#include "aura/graphics/draw2d/graphics.h"
//#include "acme/prototype/geometry2d/_collection_enhanced.h"
//#include "acme/prototype/geometry2d/shape_array.h"
#include "acme/prototype/geometry2d/item.h"
#include "aura/graphics/write_text/draw_text.h"
#include "acme/prototype/geometry2d/_defer_item.h"
#include "aura/graphics/write_text/_defer_geometry2d_item.h"
#include "path_shape.h"
//#include "acme/prototype/geometry2d/_defer_shape.h"


double_point arc_point(double dAngle, double_size sizeRadius)
{

   double ab = sizeRadius.cx() * sizeRadius.cy();

   double_point p;

   double cosAngle = cos(dAngle);

   double sinAngle = sin(dAngle);

   double m = cosAngle * sizeRadius.cy();

   double n = sinAngle * sizeRadius.cx();

   double q = sqrt(m * m + n * n);

   //if (dAngle > g_dPi / 2.0 && dAngle < g_dPi * 3.0 / 2.0)
   //{

   //   p.x() = ab * cosAngle / q;

   //   p.y() = ab * sinAngle / q;

   //}
   //else
   //{

      p.x() = ab * cosAngle / q;

      p.y() = ab * sinAngle / q;

//   }

   return p;

}


namespace draw2d
{


   path::path()
   {
      
      m_bPersistent              = false;
      m_efillmode                = ::draw2d::e_fill_mode_winding;
      m_bHasPoint                = false;
      m_bUseGeometryRealization  = true;

   }


   path::~path()
   {

   }


   void path::set_fill_mode(::draw2d::enum_fill_mode efillmode)
   {

      m_efillmode = efillmode;

   }


   ::draw2d::enum_fill_mode path::get_fill_mode()
   {

      return m_efillmode;

   }


   bool path::get_bounding_box(::double_rectangle & rectangle) const
   {

      if (m_itema.is_empty())
      {

         return false;

      }

      double_rectangle r;

      //bool bGotAny = false;

      //if (m_pshapea)
      //{

         for (auto & pitem : m_itema)
         {

            pitem->expand_bounding_box(r);
            //{

            //   bGotAny = true;

            //}

         }

      //}

      //if (!bGotAny)
      //{

      //   return false;

      //}

      rectangle = r;

      return true;

   }


   void path::destroy()
   {

      m_itema.clear();
      m_ppathoptimization.release();

      ::draw2d::object::destroy();

   }


   bool path::has_current_point()
   {

      return m_bHasPoint;

   }


   double_point path::get_current_point()
   {

      if(!m_bHasPoint)
      {

         throw ::exception(error_wrong_state, "there is no current point");

      }

      return m_pointEnd;

   }


   bool path::is_empty()
   {

      //if (!m_pshapea)
      //{

      //   return true;

      //}

      return m_itema.is_empty();

   }


   bool path::set_current_point(const ::double_point & point)
   {

      m_pointEnd = point;

      m_bHasPoint = true;

      return true;

   }


   bool path::add_rectangle(const ::double_rectangle& rectangle, const ::angle_double & angleRotationCenter)
   {

      if (angleRotationCenter == 0)
      {

         return add_rectangle(rectangle);

      }
      else
      {

         return add_rectangle(rectangle, rectangle.center(), angleRotationCenter);

      }

   }


   bool path::add_rectangle(const ::double_rectangle& rectangle)
   {

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      auto pitem = __create_new < ::geometry2d::rectangle_item >();

      pitem->m_item = rectangle;

      m_itema.add(pitem);

      return true;

   }


   bool path::add_ellipse(const ::double_ellipse & ellipse)
   {

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add_shape(ellipseParam);

      auto pitem = __create_new < ::geometry2d::ellipse_item >();

      pitem->m_item = ellipse;

      m_itema.add(pitem);

      return true;

   }


   bool path::add_rectangle(const ::double_rectangle& rectangle, const ::double_point& point, const ::angle_double & angleRotationCenter)
   {

      ::double_polygon polygon;

      polygon.set_size(4);

      polygon[0].x() = rectangle.left();
      polygon[0].y() = rectangle.top();

      polygon[1].x() = rectangle.right();
      polygon[1].y() = rectangle.top();

      polygon[2].x() = rectangle.right();
      polygon[2].y() = rectangle.bottom();

      polygon[3].x() = rectangle.left();
      polygon[3].y() = rectangle.bottom();

      polygon.rotate(angleRotationCenter, point);

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add_shape(int_polygon);

      auto pitem = __create_new < ::geometry2d::polygon_item >();

      pitem->m_polygon = polygon;

      m_itema.add(pitem);

      return true;

   }


//   bool path::varc(const ::double_point & point, double h, const ::angle_double & angle)
//   {
//
//      if (fabs(angle) <= 0.00001 || fabs(h) <= 0.001)
//      {
//         return false;
//      }
//
//      auto pitem = __create_new < ::geometry2d::arc_item >();
//
//      //pitem->m_rectangle = rectangle;
//
//      //auto parc = __allocate arc_double_shape< path > ();
//
//      auto & arc = pitem->m_item;
//
//      auto t = 90_degrees - angle;
//
//      double x = point.x();
//      double y = point.y();
//      //arc.m_pointCenter.y() = point.y() + h/2.0;
//      arc.left() = x;
//      arc.top() = y;
//      double b = point.y() - arc.m_pointCenter.y() / sin(t);
//      double a = sqrt((b*b*x*x) / (y*y - b *b));
//
//      arc.m_sizeRadius.cx() = a;
//      arc.m_sizeRadius.cy() = b;
//      arc.m_pointCenter.x() = point.x() - a * cos(t);
//      arc.m_angleBeg = t;
//      arc.m_angleExt = -90_degrees;
//      arc.m_angleEnd2 = t - 90_degrees;
//      arc.m_angleRotation = 0.0;
//      ///arc.m_dAngle = (arc.m_angleEnd - arc.m_angleBeg) * g_dPi / 180.0;
//      arc.m_pointBegin = arc.m_pointCenter + arc_point(arc.m_angleBeg, arc.m_sizeRadius);
//      arc.m_pointEnd = arc.m_pointCenter + arc_point(arc.m_angleEnd2, arc.m_sizeRadius);
//
//      //if (!m_pshapea)
//      //{
//
//      //   m_pshapea = __allocate shape_array < path> ();
//
//      //}
//
//      //m_pshapea->add(parc);
//
//      m_itema.add(pitem);
//
//      m_bHasPoint = true;
//
//      m_pointBegin = arc.m_pointBegin;
//
//      m_pointEnd = arc.m_pointEnd;
//
//      set_modified();
//
//      return true;
//
//   }
//
//
//   bool path::harc(const ::double_point & point, double w, const ::angle_double & angle)
//   {
//
//
//      if (fabs(angle) <= 0.00001 || fabs(w) <= 0.001)
//      {
//
//         return false;
//
//      }
//
//      auto pitem = __create_new<::geometry2d::arc_item>();
//
//      auto & arc = pitem->m_item;
//
//      auto t = angle + 90_degrees;
//      arc.m_pointBegin.x() = point.x() + w / 2.0;
//      double a = (point.x() - arc.m_pointBegin.x()) / cos(t);
//      double x = point.x() - arc.m_pointBegin.x();
//      double b = 0;
//      //double y = b * b  *w / (4.0* tan(dAngle));
//      double y = 0;
//      b = sqrt((a*a*y*y) / (a*a-x *x));
//
//      arc.m_sizeRadius.cx() = a;
//      arc.m_sizeRadius.cy() = b;
//      arc.m_pointCenter.y() = point.y() - b * sin(t);
//      arc.m_angleBeg = t;
//      arc.m_angleEnd2 = fmod(180_degrees - arc.m_angleBeg, 360_degrees);
//      arc.m_angleExt = arc.m_angleEnd2 - arc.m_angleBeg;
//      arc.m_angleRotation = arc.m_angleEnd2 - arc.m_angleBeg;
//
//      arc.m_pointBegin = arc.m_pointCenter + arc_point(arc.m_angleBeg, arc.m_sizeRadius);
//      arc.m_pointEnd = arc.m_pointCenter + arc_point(arc.m_angleEnd2, arc.m_sizeRadius);
//
//      //if (!m_pshapea)
//      //{
//
//      //   m_pshapea = __allocate shape_array < path> ();
//
//      //}
//
//      //m_pshapea->add_item(parc);
//      m_itema.add(pitem);
//
//      m_bHasPoint = true;
//
//      m_pointBegin = arc.m_pointBegin;
//
//      m_pointEnd = arc.m_pointEnd;
//
//      set_modified();
//
//      return true;
//
//   }


   bool path::add_arc(const ::double_rectangle & rectangle, const ::angle_double & angleBeg, const ::angle_double & angleExt)
   {

      if (rectangle.width() <= 0 || rectangle.height() <= 0)
      {

         return true;

      }

      auto pitem = __create_new < ::geometry2d::arc_item >();

      auto & arc = pitem->m_item;

      arc.set(rectangle);
      
      arc.m_angleBeg        = angleBeg;
      arc.m_angleExt        = angleExt;
      arc.m_angleEnd2       = angleBeg + angleExt;
      arc.m_angleRotation   = 0_degrees;
      arc.m_pointBegin      = arc.center() + arc_point(arc.m_angleBeg, arc.radius());
      arc.m_pointEnd        = arc.center() + arc_point(arc.m_angleEnd2, arc.radius());

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add(parc);

      m_itema.add(pitem);

      m_bHasPoint = true;

      m_pointBegin = arc.m_pointBegin;

      m_pointEnd = arc.m_pointEnd;

      set_modified();

      return true;

   }


   bool path::begin_figure()
   {

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      m_itema.add(__create_new<::geometry2d::begin_figure_item>());

      //m_pshapea->add_shape(e_shape_begin_figure);

      m_bHasPoint = false;

      set_modified();

      return true;

   }


   bool path::close_figure()
   {

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      // m_pshapea->add_shape(e_shape_close_figure);

      m_itema.add(__create_new<::geometry2d::close_figure_item>());

      set_modified();

      return true;

   }


   bool path::end_figure()
   {

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add_shape(e_shape_end_figure);

      m_itema.add(__create_new<::geometry2d::end_figure_item>());

      set_modified();

      return true;

   }


   bool path::add_text_out(const ::double_point & point, const ::string & strText,::write_text::font_pointer pfont)
   {

      auto pitem = __create_new < ::geometry2d::text_out_item >();

      auto& textout = pitem->m_item;

      //ptextout->m_pholdee = this;

      textout.m_strText     = strText;
      textout.m_pfont       = pfont;
      textout.m_point       = point;

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add_item(ptextout);

      m_itema.add(pitem);

      return true;

   }


   bool path::add_draw_text(const string& strText, const ::double_rectangle& rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext , ::write_text::font_pointer pfont)
   {

      auto pitem = __create_new < ::geometry2d::draw_text_item >();

      auto & drawtext = pitem->m_item;

      //pdrawtext->m_pholdee = this;

      drawtext.m_strText            = strText;
      drawtext.m_pfont              = pfont;


      drawtext.m_rectangle          = rectangle;
      drawtext.m_ealign             = ealign;
      drawtext.m_edrawtext          = edrawtext;

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add(pdrawtext);

      m_itema.add(pitem);

      return true;

   }


   bool path::add_line(const double_point & p1, const double_point & p2)
   {

      //auto pline = __allocate double_line_shape< path> ();

      auto pitem = __create_new < ::geometry2d::line_item >();

      //pline->m_pholdee = this;

      auto & line = pitem->m_item;

      line.m_p1 = p1;

      line.m_p2 = p2;

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add(pline);

      m_itema.add(pitem);

      m_pointBegin = line.m_p1;

      m_pointEnd = line.m_p2;

      return true;

   }


   bool path::add_line(const double_point & point)
   {

      //auto pline = __allocate double_line_shape < path > ();

      auto pitem = __create_new < ::geometry2d::line_item >();

      //pline->m_pholdee = this;

      auto & line = pitem->m_item;

      line.m_p1 = m_pointEnd;

      line.m_p2 = point;

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add(pline);

      m_itema.add(pitem);

      m_pointBegin = line.m_p1;

      m_pointEnd = line.m_p2;

      return true;

   }


 
   bool path::add_polygon(const ::double_point * ppoint, ::collection::count nCount)
   {

      auto pitem = __create_new < ::geometry2d::polygon_item >();

      //ppolygon->m_pholdee = this;

      pitem->m_polygon.set_size(nCount);

      memory_copy(pitem->m_polygon.data(), ppoint, pitem->m_polygon.get_size_in_bytes());

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add(ppolygon);

      m_itema.add(pitem);

      return true;

   }


   bool path::add_lines(const ::double_point * ppoint, ::collection::count nCount)
   {

      //auto plines = __allocate lines_double_shape < path > ();

      auto pitem = __create_new < ::geometry2d::lines_item >();

      //plines->m_pholdee = this;

      pitem->m_item.set_size(nCount);

      memory_copy(pitem->m_item.data(), ppoint, pitem->m_item.get_size_in_bytes());

      //if (!m_pshapea)
      //{

      //   m_pshapea = __allocate shape_array < path> ();

      //}

      //m_pshapea->add(plines);

      m_itema.add(pitem);

      return true;

   }


   void * path::detach()
   {

      throw ::interface_only();

      return nullptr;

   }





   //
   // CRoundRect.h : Version 1.0 - see article at CodeProject.com
   //
   // Author:  Darren Sessions
   //
   //
   // Description:
   //     CRoundRect Draws or Fills rounded rectangles for GDI+.  It was implemented
   //	   to overcome the asymmetric issues associated with GDI+ round rectangles
   //
   // History
   //     Version 1.0 - 2008 June 24
   //     - Initial public release
   //
   // License:
   //     This software is released under the Code Project Open License (CPOL),
   //     which may be found here:  http://www.codeproject.com/info/eula.aspx
   //     You are free to use this software in any way you like, except that you
   //     may not sell this source code.
   //
   //     This software is provided "as is" with no expressed or implied warranty.
   //     I accept no liability for any damage or loss of business that this
   //     software may cause.
   //
   ///////////////////////////////////////////////////////////////////////////////

   //=============================================================================
   //
   // get_round_rect()
   //
   // Purpose:     Defines a Rounded int_rectangle and places it in the GraphicsPath
   //
   // Parameters:  path.m_ppath		- [out] pointer to GraphicsPath that will recieve the
   //									path data
   //				int_rectangle			- [in]	Rect that defines the round int_rectangle boundaries
   //				iDiameter			- [in]	diameter of the rounded corners (2*radius)
   //
   // Returns:     None
   //
   
   
   //bool path::do_round_rect_corner(const ::double_rectangle& rectangleCorner, const ::double_rectangle& rectangleRect, int iDiameter, const ::e_border & eborder, int iCorner, bool& bOn)
   //{

   //   switch (iCorner % 4)
   //   {
   //   case 0:
   //   {
   //      if ((eborder & e_border_top_left))
   //      {

   //         if ((eborder & e_border_top_left) == e_border_top_left)
   //         {

   //            add_arc(::int_rectangle(rectangleCorner.top_left(), ::int_size(iDiameter, iDiameter)), 180_degrees, 90_degrees);

   //            bOn = true;

   //         }
   //         else if(bOn)
   //         {

   //            add_line(rectangleRect.top_left());

   //            bOn = false;

   //         }
   //         else
   //         {

   //            set_current_point(rectangleRect.top_left());

   //            bOn = true;

   //         }

   //      }
   //      else
   //      {

   //         bOn = false;

   //      }

   //   }
   //   break;
   //   case 1:
   //   {
   //      if ((eborder & e_border_top_right))
   //      {

   //         if ((eborder & e_border_top_right) == e_border_top_right)
   //         {

   //            add_arc(::int_rectangle(rectangleCorner.top_right(), ::int_size(iDiameter, iDiameter)), 270_degrees, 90_degrees);

   //            bOn = true;

   //         }
   //         else if(bOn)
   //         {

   //            add_line(rectangleRect.top_right());

   //            bOn = false;

   //         }
   //         else
   //         {

   //            set_current_point(rectangleRect.top_right());

   //            bOn = true;

   //         }

   //      }
   //      else
   //      {

   //         bOn = false;

   //      }

   //   }
   //   break;
   //   case 2:
   //   {

   //      if ((eborder & e_border_bottom_right))
   //      {

   //         if ((eborder & e_border_bottom_right) == e_border_bottom_right)
   //         {

   //            add_arc(::int_rectangle(rectangleCorner.bottom_right(), ::int_size(iDiameter, iDiameter)), 0_degrees, 90_degrees);

   //            bOn = true;

   //         }
   //         else if (bOn)
   //         {

   //            add_line(rectangleRect.bottom_right());

   //            bOn = false;

   //         }
   //         else
   //         {

   //            set_current_point(rectangleRect.bottom_right());

   //            bOn = true;

   //         }

   //      }
   //      else
   //      {

   //         bOn = false;

   //      }
   //   }
   //   break;
   //   case 3:
   //   {
   //      if ((eborder & e_border_bottom_left))
   //      {

   //         if ((eborder & e_border_bottom_left) == e_border_bottom_left)
   //         {

   //            add_arc(::int_rectangle(rectangleCorner.bottom_left(), ::int_size(iDiameter, iDiameter)), 90_degrees, 90_degrees);

   //            bOn = true;

   //         }
   //         else if(bOn)
   //         {

   //            add_line(rectangleRect.bottom_left());

   //            bOn = false;

   //         }
   //         else
   //         {

   //            set_current_point(rectangleRect.bottom_left());

   //            bOn = true;

   //         }

   //      }
   //      else
   //      {

   //         bOn = false;

   //      }

   //   }
   //   break;

   //   default:
   //   {
   //      ASSERT(false);
   //      return false;
   //   }

   //   };

   //   return true;

   //}


   bool path::do_round_rectangle_corner(const ::double_rectangle& rectangleCorner, const ::double_rectangle& rectangleRect, double dDiameter, const ::e_border & eborder, int iCorner, bool& bOn)
   {

      switch (iCorner % 4)
      {
      case 0:
      {
         if ((eborder & e_border_top_left))
         {

            if ((eborder & e_border_top_left) == e_border_top_left)
            {

               add_arc(::double_rectangle(rectangleCorner.top_left(), ::double_size(dDiameter, dDiameter)), 180_degrees, 90_degrees);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectangleRect.top_left());

               bOn = false;

            }
            else
            {

               set_current_point(rectangleRect.top_left());

               bOn = true;

            }

         }
         else
         {

            bOn = false;

         }

      }
      break;
      case 1:
      {
         if ((eborder & e_border_top_right))
         {

            if ((eborder & e_border_top_right) == e_border_top_right)
            {

               add_arc(::double_rectangle(rectangleCorner.top_right(), ::double_size(dDiameter, dDiameter)), 270_degrees, 90_degrees);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectangleRect.top_right());

               bOn = false;

            }
            else
            {

               set_current_point(rectangleRect.top_right());

               bOn = true;

            }

         }
         else
         {

            bOn = false;

         }

      }
      break;
      case 2:
      {

         if ((eborder & e_border_bottom_right))
         {

            if ((eborder & e_border_bottom_right) == e_border_bottom_right)
            {

               add_arc(::double_rectangle(rectangleCorner.bottom_right(), ::double_size(dDiameter, dDiameter)), 0_degree, 90_degree);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectangleRect.bottom_right());

               bOn = false;

            }
            else
            {

               set_current_point(rectangleRect.bottom_right());

               bOn = true;

            }

         }
         else
         {

            bOn = false;

         }
      }
      break;
      case 3:
      {
         if ((eborder & e_border_bottom_left))
         {

            if ((eborder & e_border_bottom_left) == e_border_bottom_left)
            {

               add_arc(::double_rectangle(rectangleCorner.bottom_left(), ::double_size(dDiameter, dDiameter)), 90_degrees, 90_degrees);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectangleRect.bottom_left());

               bOn = false;

            }
            else
            {

               set_current_point(rectangleRect.bottom_left());

               bOn = true;

            }

         }
         else
         {

            bOn = false;

         }

      }
      break;

      default:
      {

         ASSERT(false);

         return false;

      }

      };

      return true;

   }


   //bool path::clock_corner(const ::int_rectangle& rectangleCorner, int iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   if (iDiameter == 0)
   //   {

   //      iDiameter = 1;

   //   }

   //   switch (eborder)
   //   {
   //   case e_border_top_left:
   //      add_arc(::int_rectangle(rectangleCorner.top_left(), ::int_size(iDiameter, iDiameter)), 180_degree, 90_degree);
   //      return true;
   //   case e_border_top_right:
   //      add_arc(::int_rectangle(rectangleCorner.top_right() - ::int_size(iDiameter, 0), ::int_size(iDiameter, iDiameter)), 270_degree, 90_degree);
   //      return true;
   //   case e_border_bottom_right:
   //      add_arc(::int_rectangle(rectangleCorner.bottom_right() - ::int_size(iDiameter, iDiameter), ::int_size(iDiameter, iDiameter)), 0_degree, 90_degree);
   //      return true;
   //   case e_border_bottom_left:
   //      add_arc(::int_rectangle(rectangleCorner.bottom_left() - ::int_size(0, iDiameter), ::int_size(iDiameter, iDiameter)), 90_degree, 90_degree);
   //      return true;
   //   default:
   //      return false;
   //   }

   //}


   //bool path::counter_corner(const ::int_rectangle& rectangleCorner, int iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   if (iDiameter == 0)
   //   {

   //      iDiameter = 1;

   //   }

   //   switch (eborder)
   //   {
   //   case e_border_top_left:
   //      add_arc(::int_rectangle(rectangleCorner.top_left(), ::int_size(iDiameter, iDiameter)), 270_degree, -90_degree);
   //      return true;
   //   case e_border_top_right:
   //      add_arc(::int_rectangle(rectangleCorner.top_right() - ::int_size(iDiameter, 0), ::int_size(iDiameter, iDiameter)), 0_degree, -90_degree);
   //      return true;
   //   case e_border_bottom_right:
   //      add_arc(::int_rectangle(rectangleCorner.bottom_right() - ::int_size(iDiameter, iDiameter), ::int_size(iDiameter, iDiameter)), 90_degree, -90_degree);
   //      return true;
   //   case e_border_bottom_left:
   //      add_arc(::int_rectangle(rectangleCorner.bottom_left() - ::int_size(0, iDiameter), ::int_size(iDiameter, iDiameter)), 180_degree, -90_degree);
   //      return true;
   //   default:
   //      return false;
   //   }

   //}


   bool path::_set_create(::draw2d::graphics* pgraphics)
   {

      //if (!m_pshapea)
      //{

      //   return true;

      //}

      //for (auto& pmatter : *m_pshapea)
      for (auto & pitem : m_itema)
      {

         if (!_set(pgraphics, pitem))
         {

            return false;

         }

      }

      return true;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, ___shape < path > * pshape)
   //{

   //   auto eshape = pshape->eshape();

   //   switch (eshape)
   //   {
   //   case e_shape_begin_figure:
   //      return _set(pgraphics, e_shape_begin_figure);
   //   case e_shape_close_figure:
   //      return _set(pgraphics, e_shape_close_figure);
   //   case e_shape_end_figure:
   //      return _set(pgraphics, e_shape_end_figure);
   //   case e_shape_arc:
   //      return _set(pgraphics, pshape->shape < ::arc_double>());
   //   //case e_shape_line:
   //   //   return  _set(pgraphics, pshape->shape < ::line>());
   //   case e_shape_line:
   //      return  _set(pgraphics, pshape->shape < ::double_line>());
   //   case e_shape_lines:
   //      return _set(pgraphics, pshape->shape < ::lines_double>());
   //   case e_shape_rectangle:
   //      return _set(pgraphics, pshape->shape < ::double_rectangle>());
   //   case e_shape_ellipse:
   //      return _set(pgraphics, pshape->shape < ::double_ellipse>());
   //   case e_shape_polygon:
   //      return _set(pgraphics, pshape->shape < ::double_polygon>());
   //   case e_shape_draw_text:
   //      m_estatus = success;
   //      return _set(pgraphics, pshape->shape < ::write_text::draw_text>());
   //   case e_shape_text_out:
   //      m_estatus = success;
   //      return _set(pgraphics, pshape->shape < ::write_text::text_out>());
   //   default:
   //      throw "unexpected simple os graphics matter type";
   //   }

   //   return false;

   //}


   bool path::_set(::draw2d::graphics * pgraphics, ::geometry2d::item * pitem)
   {

      auto eitem = pitem->type();

      switch (eitem)
      {
      case e_item_begin_figure:
         return _set(pgraphics, e_item_begin_figure);
      case e_item_close_figure:
         return _set(pgraphics, e_item_close_figure);
      case e_item_end_figure:
         return _set(pgraphics, e_item_end_figure);
      case e_item_arc:
         return _set(pgraphics, pitem->cast < ::geometry2d::arc_item >()->m_item);
         //case e_shape_line:
         //   return  _set(pgraphics, pshape->shape < ::line>());
      case e_item_line:
         return  _set(pgraphics, pitem->cast < ::geometry2d::line_item >()->m_item);
      case e_item_lines:
         return _set(pgraphics, pitem->cast < ::geometry2d::lines_item >()->m_item);
      case e_item_rectangle:
         return _set(pgraphics, pitem->cast < ::geometry2d::rectangle_item >()->m_item);
      case e_item_ellipse:
         return _set(pgraphics, pitem->cast < ::geometry2d::ellipse_item >()->m_item);
      case e_item_polygon:
         return _set(pgraphics, pitem->cast < ::geometry2d::polygon_item >()->m_polygon);
      case e_item_poly_polygon:
         return _set(pgraphics, pitem->cast < ::geometry2d::poly_polygon_item >()->m_polypolygon);
      case e_item_draw_text:
         m_estatus = success;
         return _set(pgraphics, pitem->cast < ::geometry2d::draw_text_item >()->m_item);
      case e_item_text_out:
         m_estatus = success;
         return _set(pgraphics, pitem->cast < ::geometry2d::text_out_item >()->m_item);
      default:
         throw "unexpected simple os graphics matter type";
      }

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const enum_item& eitem)
   {

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::arc_double & arc)
   {

      throw ::interface_only();

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::line & line)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::double_line & line)
   {

      throw ::interface_only();

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const::lines& lines)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const::lines_double & lines)
   {

      throw ::interface_only();

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::int_rectangle & rectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool path::_set(::draw2d::graphics * pgraphics, const ::double_rectangle & rectangle)
   {

      throw ::interface_only();

      return false;

   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::double_ellipse & ellipse)
   {

      throw ::interface_only();

      return false;

   }
   

   //bool path::_set(::draw2d::graphics* pgraphics, const ::int_polygon& int_polygon)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::double_polygon& polygon)
   {

      throw ::interface_only();

      return false;

   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::double_poly_polygon & polypolygon)
   {

      throw ::interface_only();

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::write_text::text_out & textout)
   {

      throw ::interface_only();

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::write_text::draw_text& drawtext)
   {

      throw ::interface_only();

      return false;

   }


   bool path::clock_corner(const ::double_rectangle& rectangleCorner, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case e_border_top_left:
         add_arc(::double_rectangle(rectangleCorner.top_left(), ::double_size(dDiameter, dDiameter)), 180_degree, 90_degree);
         return true;
      case e_border_top_right:
         add_arc(::double_rectangle(rectangleCorner.top_right() - ::double_size(dDiameter, 0), ::double_size(dDiameter, dDiameter)), 270_degree, 90_degree);
         return true;
      case e_border_bottom_right:
         add_arc(::double_rectangle(rectangleCorner.bottom_right() - ::double_size(dDiameter, dDiameter), ::double_size(dDiameter, dDiameter)), 0_degree, 90_degree);
         return true;
      case e_border_bottom_left:
         add_arc(::double_rectangle(rectangleCorner.bottom_left() - ::double_size(0, dDiameter), ::double_size(dDiameter, dDiameter)), 90_degree, 90_degree);
         return true;
      default:
         return false;
      }

   }


   bool path::counter_corner(const ::double_rectangle& rectangleCorner, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case e_border_top_left:
         add_arc(::double_rectangle(rectangleCorner.top_left(), ::double_size(dDiameter, dDiameter)), 270_degree, -90_degree);
         return true;
      case e_border_top_right:
         add_arc(::double_rectangle(rectangleCorner.top_right() - ::double_size(dDiameter, 0), ::double_size(dDiameter, dDiameter)), 0_degree, -90_degree);
         return true;
      case e_border_bottom_right:
         add_arc(::double_rectangle(rectangleCorner.bottom_right() - ::double_size(dDiameter, dDiameter), ::double_size(dDiameter, dDiameter)), 90_degree, -90_degree);
         return true;
      case e_border_bottom_left:
         add_arc(::double_rectangle(rectangleCorner.bottom_left() - ::double_size(0, dDiameter), ::double_size(dDiameter, dDiameter)), 180_degree, -90_degree);
         return true;
      default:
         return false;
      }

   }


   //bool path::add_round_rect(const ::int_rectangle & rectangle, int iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   // diameter can't exceed width or height
   //   if (iDiameter > rectangle.width())	iDiameter = (int)rectangle.width();
   //   if (iDiameter > rectangle.height())	iDiameter = (int)rectangle.height();

   //   ::int_rectangle rectangleRect(rectangle);

   //   rectangleRect.deflate(0, 0, 1, 1);

   //   ::int_size size(iDiameter, iDiameter);

   //   ::int_rectangle rectangleCorner(rectangleRect);

   //   rectangleCorner.deflate(0, 0, iDiameter, iDiameter);

   //   bool bOn = false;

   //   int iCount = 0;

   //   if (eborder & e_border_all)
   //   {

   //      //begin_figure(true, ::draw2d::e_fill_mode_winding);

   //      //begin_figure();

   //      int iEmptyBorder;

   //      if (!(eborder & e_border_right))
   //      {

   //         iEmptyBorder = 1;

   //      }
   //      else if(!(eborder & e_border_bottom))
   //      {

   //         iEmptyBorder = 2;

   //      }
   //      else if(!(eborder & e_border_left))
   //      {

   //         iEmptyBorder = 3;

   //      }
   //      else
   //      {

   //         iEmptyBorder = 0;

   //      }

   //      for(int iShift = 0; iShift < 4; iShift++)
   //      {

   //         int iCorner = iEmptyBorder + iShift + 1;

   //         do_round_rect_corner(rectangleCorner, rectangleRect, iDiameter, eborder, iCorner, bOn);

   //      }

   //      //end_figure(bOn);

   //      close_figure();

   //      return true;

   //   }


   //   return false;

   //}

   void path::add_round_rectangle(const ::double_rectangle& rectangle, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      // diameter can't exceed width or height
      //if (dDiameter > rectangle.width())	dDiameter = (double)rectangle.width();
      //if (dDiameter > rectangle.height()) dDiameter = (double)rectangle.height();
      if (dDiameter > rectangle.width() || dDiameter > rectangle.height())
      {

         throw exception(error_bad_argument, "diameter of round rect should be greater or equal than any of its dimensions.");

      }

      if (dDiameter <= 0.)
      {

         add_rectangle(rectangle);

         return;

      }

      ::double_rectangle rectangleRect(rectangle);

      rectangleRect.deflate(0, 0, 1.0, 1.0);

      ::double_size size(dDiameter, dDiameter);

      ::double_rectangle rectangleCorner(rectangleRect);

      rectangleCorner.deflate(0, 0, dDiameter, dDiameter);

      bool bOn = false;

      int iCount = 0;

      if (eborder & e_border_all)
      {

         //begin_figure(true, ::draw2d::e_fill_mode_winding);

         begin_figure();

         int iEmptyBorder;

         if (!(eborder & e_border_right))
         {

            iEmptyBorder = 1;

         }
         else if (!(eborder & e_border_bottom))
         {

            iEmptyBorder = 2;

         }
         else if (!(eborder & e_border_left))
         {

            iEmptyBorder = 3;

         }
         else
         {

            iEmptyBorder = 0;

         }

         for (int iShift = 0; iShift < 4; iShift++)
         {

            int iCorner = iEmptyBorder + iShift + 1;

            do_round_rectangle_corner(rectangleCorner, rectangleRect, dDiameter, eborder, iCorner, bOn);

         }

         close_figure();

         return;

      }

      //return false;

   }


   bool path::add_round_top_left(const ::double_rectangle & rectangleParam, double iDiameter, const ::e_border & eborder)
   {

      ::int_rectangle rectangle(rectangleParam);

      // diameter can't exceed width or height
      if (iDiameter > rectangle.width())	iDiameter = rectangle.width();
      if (iDiameter > rectangle.height())	iDiameter = rectangle.height();

      // define a corner
      auto Corner = double_rectangle_dimension(rectangle.left(), rectangle.top(), iDiameter, iDiameter);

      // begin path
      //path.m_ppath->Reset();


      // top left
      //   path.m_ppath->AddArc(Corner, 180, 90);

      // tweak needed for radius of 10 (iDiameter of 20)
      double iDiameter2 = iDiameter;
      
      //if (iDiameter % 2 == 0)
      //{
      //   iDiameter2++;
      //   //Corner.Height += 1;
      //   //rectangle.height() -=1; //rectangle.height() -= 1;
      //}

      // top right
      Corner.left() += (rectangle.width() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 270, 90);

      // bottom right
      Corner.top() += (rectangle.height() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner,   0, 90);

      // bottom left
      Corner.left() -= (rectangle.width() - iDiameter - 1);
      Corner.right() = Corner.left() + iDiameter2;
      add_arc(Corner, 135_degree, 45_degree);

      add_line(rectangle.left(), rectangle.top() + rectangle.height() - iDiameter / 2, rectangle.left(), rectangle.top() + iDiameter / 2);


      Corner.top() -= (rectangle.height() - iDiameter - 1);
      Corner.bottom() = Corner.top() + iDiameter2;
      add_arc(Corner, 180_degree, 90_degree);

      add_line(rectangle.left() + iDiameter / 2, rectangle.top(), rectangle.left() + rectangle.width() - iDiameter / 2, rectangle.top());

      Corner.left() += (rectangle.width() - iDiameter - 1);
      Corner.right() = Corner.left() + iDiameter2;
      add_arc(Corner, 270_degree, 45_degree);


      // end path
      //path.m_ppath->CloseFigure();

      return true;

   }



   bool path::add_round_bottom_right(const ::double_rectangle & rectangle, double iDiameter, const ::e_border & eborder)
   {
      // diameter can't exceed width or height
      if (iDiameter > rectangle.width())	iDiameter = rectangle.width();
      if (iDiameter > rectangle.height())	iDiameter = rectangle.height();

      // define a corner
      auto Corner = double_rectangle_dimension(rectangle.left(), rectangle.top(), iDiameter, iDiameter);

      // begin path
      //path.m_ppath->Reset();


      // top left
      //   path.m_ppath->AddArc(Corner, 180, 90);

      // tweak needed for radius of 10 (iDiameter of 20)
      double iDiameter2 = iDiameter;
      //if (iDiameter % 2 == 0)
      //{
      //   iDiameter2++;
      //   //Corner.Height += 1;
      //   //rectangle.height() -=1; //rectangle.height() -= 1;
      //}

      // top right
      Corner.left() += (rectangle.width() - iDiameter - 1);
      Corner.right() = Corner.left() + iDiameter2;
      add_arc(Corner, 315_degree, 45_degree);

      add_line(rectangle.left() + rectangle.width(), rectangle.top() + iDiameter / 2, rectangle.left() + rectangle.width(), rectangle.top() + rectangle.height() - iDiameter / 2);

      // bottom right
      Corner.top() += (rectangle.height() - iDiameter - 1);
      Corner.bottom() = Corner.top() + iDiameter2;
      add_arc(Corner, 0_degrees, 90_degrees);

      add_line(rectangle.left() + iDiameter / 2, rectangle.top() + rectangle.height(), rectangle.left() + rectangle.width() - iDiameter / 2, rectangle.top() + rectangle.height());

      // bottom left
      Corner.left() -= (rectangle.width() - iDiameter - 1);
      Corner.right() = Corner.left() + iDiameter2;
      add_arc(Corner, 90_degrees, 45_degrees);




      //Corner.Y -= (rectangle.height() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 180, 90);



      //Corner.X += (rectangle.width() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 275, 45);


      // end path
      //path.m_ppath->CloseFigure();

      return true;

   }


   bool path::contains(::draw2d::graphics_pointer & pgraphics, const double_point& point)
   {

      //if (!m_pshapea)
      //{

      //   return false;

      //}

      int iFill = 0;

      for (auto& pitem : m_itema)
      {

         if (pitem->contains(point))
         {

            if (m_efillmode == ::draw2d::e_fill_mode_winding)
            {

               return true;

            }
            else
            {

               iFill++;

            }

         }

      }

      return (iFill % 2) == 1;

   }


   bool path::add_arc_label(const ::double_rectangle & rectangleParam)
   {

      ::double_rectangle rectangle;
      ::double_rectangle r2;

      {

         rectangle.left() = rectangleParam.left();

         rectangle.top() = rectangleParam.top();

         rectangle.right() = rectangleParam.left() + rectangleParam.height();

         rectangle.bottom() = rectangleParam.bottom();

         add_arc(rectangle,90_degree,180_degree);

      }

      {

         r2.left() = rectangle.left() + rectangle.height() / 2.0;

         r2.top() = rectangle.top();

         r2.right() = rectangle.right() - rectangle.height() / 2.0;

         r2.bottom() = rectangle.bottom();

         //add_line(r2.right(), r2.top());

      }

      {

         rectangle.right() = rectangleParam.right();

         rectangle.top() = rectangleParam.top();

         rectangle.left() = rectangleParam.right() - rectangleParam.height();

         rectangle.bottom() = rectangleParam.bottom();

         add_arc(rectangle,-90_degree,180_degree);

      }

      {

         add_line(r2.left(),r2.bottom());

      }

      return true;

   }


   path & path::operator = (const path & path)
   {

      if (this != &path)
      {

         //if(!m_pshapea)
         //{

         //   m_pshapea = __allocate shape_array <class path> ();

         //}

         // m_pshapea->erase_all();

         m_itema.clear();

         for (auto & pitem : path.m_itema)
         {

            m_itema.add(pitem->clone());

         }

         m_bHasPoint = path.m_bHasPoint;
         m_pointBegin = path.m_pointBegin;
         m_pointEnd = path.m_pointEnd;
         m_efillmode = path.m_efillmode;
         m_pointOffset = path.m_pointOffset;

      }

      return *this;
   }


} // namespace draw2d



