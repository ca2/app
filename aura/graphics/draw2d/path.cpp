#include "framework.h"
#include "path.h"
//#include "aura/graphics/write_text/_.h"
#include "aura/graphics/draw2d/graphics.h"
#include "acme/primitive/geometry2d/_collection_enhanced.h"
#include "acme/primitive/geometry2d/shape_array.h"
#include "aura/graphics/write_text/_shape.h"
#include "path_shape.h"
#include "acme/primitive/geometry2d/_defer_shape.h"


point_f64 arc_point(double dAngle, size_f64 sizeRadius)
{

   double ab = sizeRadius.cx * sizeRadius.cy;

   point_f64 p;

   double cosAngle = cos(dAngle);

   double sinAngle = sin(dAngle);

   double m = cosAngle * sizeRadius.cy;

   double n = sinAngle * sizeRadius.cx;

   double q = sqrt(m * m + n * n);

   //if (dAngle > g_dPi / 2.0 && dAngle < g_dPi * 3.0 / 2.0)
   //{

   //   p.x = ab * cosAngle / q;

   //   p.y = ab * sinAngle / q;

   //}
   //else
   //{

      p.x = ab * cosAngle / q;

      p.y = ab * sinAngle / q;

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


   bool path::get_bounding_rectangle(::rectangle_f64 & rectangle) const
   {

      rectangle_f64 r;

      bool bGotAny = false;

      if (m_pshapea)
      {

         for (auto & pshape : *m_pshapea)
         {

            if (pshape->expand_bounding_rect(r))
            {

               bGotAny = true;

            }

         }

      }

      if (!bGotAny)
      {

         return false;

      }

      copy(&rectangle, &r);

      return true;

   }


   bool path::has_current_point()
   {

      return m_bHasPoint;

   }


   point_f64 path::get_current_point()
   {

      if(!m_bHasPoint)
      {

         throw ::exception(error_wrong_state, "there is no current point");

      }

      return m_pointEnd;

   }


   bool path::is_empty()
   {

      if (!m_pshapea)
      {

         return true;

      }

      return m_pshapea->is_empty();

   }


   bool path::set_current_point(const ::point_f64 & point)
   {

      m_pointEnd = point;

      m_bHasPoint = true;

      return true;

   }


   bool path::add_rectangle(const ::rectangle_f64& rectangle, const ::angle& angleRotationCenter)
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


   bool path::add_rectangle(const ::rectangle_f64& rectangleParam)
   {

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add_shape(rectangleParam);

      return true;

   }


   bool path::add_ellipse(const ::ellipse_f64 & ellipseParam)
   {

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add_shape(ellipseParam);

      return true;

   }


   bool path::add_rectangle(const ::rectangle_f64& rectangle, const ::point_f64& point, const ::angle& angleRotationCenter)
   {

      ::polygon_f64 polygon_i32;

      polygon_i32.set_size(4);

      polygon_i32[0].x = rectangle.left;
      polygon_i32[0].y = rectangle.top;

      polygon_i32[1].x = rectangle.right;
      polygon_i32[1].y = rectangle.top;

      polygon_i32[2].x = rectangle.right;
      polygon_i32[2].y = rectangle.bottom;

      polygon_i32[3].x = rectangle.left;
      polygon_i32[3].y = rectangle.bottom;

      polygon_i32.rotate(angleRotationCenter, point);

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add_shape(polygon_i32);

      return true;

   }


   bool path::varc(const ::point_f64 & point, double h, const ::angle& angle)
   {

      if (fabs(angle) <= 0.00001 || fabs(h) <= 0.001)
      {
         return false;
      }

      auto parc = __new(arc_shape< path >);

      ::arc& arc = parc->m_shape;

      ::angle t = 90_degrees - angle;
      double x = point.x;
      double y = point.y;
      arc.m_pointCenter.y = point.y + h/2.0;
      double b = point.y - arc.m_pointCenter.y / sin(t);
      double a = sqrt((b*b*x*x) / (y*y - b *b));

      arc.m_sizeRadius.cx = a;
      arc.m_sizeRadius.cy = b;
      arc.m_pointCenter.x = point.x - a * cos(t);
      arc.m_angleBeg = t;
      arc.m_angleExt = -90_degrees;
      arc.m_angleEnd2 = t - 90_degrees;
      arc.m_angleRotation = 0.0;
      ///arc.m_dAngle = (arc.m_angleEnd - arc.m_angleBeg) * g_dPi / 180.0;
      arc.m_pointBegin = arc.m_pointCenter + arc_point(arc.m_angleBeg, arc.m_sizeRadius);
      arc.m_pointEnd = arc.m_pointCenter + arc_point(arc.m_angleEnd2, arc.m_sizeRadius);

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add(parc);

      m_bHasPoint = true;

      m_pointBegin = arc.m_pointBegin;

      m_pointEnd = arc.m_pointEnd;

      set_modified();

      return true;

   }


   bool path::harc(const ::point_f64 & point, double w, const ::angle& angle)
   {


      if (fabs(angle) <= 0.00001 || fabs(w) <= 0.001)
      {

         return false;

      }

      auto parc = __new(arc_shape < path >);

      ::arc& arc = parc->m_shape;

      ::angle t = angle + 90_degrees;
      arc.m_pointBegin.x = point.x + w / 2.0;
      double a = (point.x - arc.m_pointBegin.x) / cos(t);
      double x = point.x - arc.m_pointBegin.x;
      double b = 0;
      //double y = b * b  *w / (4.0* tan(dAngle));
      double y = 0;
      b = sqrt((a*a*y*y) / (a*a-x *x));

      arc.m_sizeRadius.cx = a;
      arc.m_sizeRadius.cy = b;
      arc.m_pointCenter.y = point.y - b * sin(t);
      arc.m_angleBeg = t;
      arc.m_angleEnd2 = fmod(180_degrees - arc.m_angleBeg, 360_degrees);
      arc.m_angleExt = arc.m_angleEnd2 - arc.m_angleBeg;
      arc.m_angleRotation = arc.m_angleEnd2 - arc.m_angleBeg;

      arc.m_pointBegin = arc.m_pointCenter + arc_point(arc.m_angleBeg, arc.m_sizeRadius);
      arc.m_pointEnd = arc.m_pointCenter + arc_point(arc.m_angleEnd2, arc.m_sizeRadius);

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add_item(parc);

      m_bHasPoint = true;

      m_pointBegin = arc.m_pointBegin;

      m_pointEnd = arc.m_pointEnd;

      set_modified();

      return true;

   }


   bool path::add_arc(const ::rectangle_f64 & rectangle, const ::angle & angleBeg, const ::angle& angleExt)
   {

      if (rectangle.width() <= 0 || rectangle.height() <= 0)
      {

         return true;

      }

      auto parc = __new(arc_shape< ::draw2d::path>);

      ::arc& arc = parc->m_shape;

      arc.m_pointCenter.x   = (rectangle.right + rectangle.left) / 2.0;
      arc.m_pointCenter.y   = (rectangle.bottom + rectangle.top) / 2.0;
      arc.m_sizeRadius.cx   = fabs(rectangle.right - rectangle.left) / 2.0;
      arc.m_sizeRadius.cy   = fabs(rectangle.bottom - rectangle.top) / 2.0;
      arc.m_angleBeg        = angleBeg;
      arc.m_angleExt        = angleExt;
      arc.m_angleEnd2       = angleBeg + angleExt;
      arc.m_angleRotation   = 0_degrees;
      arc.m_pointBegin        = arc.m_pointCenter + arc_point(arc.m_angleBeg, arc.m_sizeRadius);
      arc.m_pointEnd        = arc.m_pointCenter + arc_point(arc.m_angleEnd2, arc.m_sizeRadius);

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add(parc);

      m_bHasPoint = true;

      m_pointBegin = arc.m_pointBegin;

      m_pointEnd = arc.m_pointEnd;

      set_modified();

      return true;

   }


   bool path::begin_figure()
   {

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add_shape(e_shape_begin_figure);

      m_bHasPoint = false;

      set_modified();

      return true;

   }


   bool path::close_figure()
   {

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add_shape(e_shape_close_figure);

      set_modified();

      return true;

   }


   bool path::end_figure()
   {

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add_shape(e_shape_end_figure);

      set_modified();

      return true;

   }


   bool path::add_text_out(const ::point_f64 & point, const ::string & strText,::write_text::font_pointer pfont)
   {

      auto ptextout = __new(text_out_shape < path >);

      auto& textout = ptextout->m_shape;

      ptextout->m_pholdee = this;

      textout.m_strText     = strText;
      textout.m_pfont       = pfont;
      textout.m_point       = point;

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add_item(ptextout);

      return true;

   }


   bool path::add_draw_text(const string& strText, const ::rectangle_f64& rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext , ::write_text::font_pointer pfont)
   {

      auto pdrawtext = __new(draw_text_shape < path >);

      auto & drawtext = pdrawtext->m_shape;

      pdrawtext->m_pholdee = this;

      drawtext.m_strText            = strText;
      drawtext.m_pfont              = pfont;


      drawtext.m_rectangle          = rectangle;
      drawtext.m_ealign             = ealign;
      drawtext.m_edrawtext          = edrawtext;

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add(pdrawtext);

      return true;

   }


   bool path::add_line(const point_f64 & p1, const point_f64 & p2)
   {

      auto pline = __new(line_shape< path>);

      pline->m_pholdee = this;

      ::line & line = pline->m_shape;

      line.m_p1 = p1;

      line.m_p2 = p2;

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add(pline);

      m_pointBegin = line.m_p1;

      m_pointEnd = line.m_p2;

      return true;

   }


   bool path::add_line(const point_f64 & point)
   {

      auto pline = __new(line_shape < path >);

      pline->m_pholdee = this;

      ::line & line = pline->m_shape;

      line.m_p1 = m_pointEnd;

      line.m_p2 = point;

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add(pline);

      m_pointBegin = line.m_p1;

      m_pointEnd = line.m_p2;

      return true;

   }


 
   bool path::add_polygon(const ::point_f64 * ppoint, ::count nCount)
   {

      auto ppolygon = __new(polygon_shape < path >);

      ppolygon->m_pholdee = this;

      ppolygon->m_shape.set_size(nCount);

      memcpy(ppolygon->m_shape.get_data(), ppoint, ppolygon->m_shape.get_size_in_bytes());

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add(ppolygon);

      return true;

   }


   bool path::add_lines(const ::point_f64 * ppoint, ::count nCount)
   {

      auto plines = __new(lines_shape < path >);

      plines->m_pholdee = this;

      plines->m_shape.set_size(nCount);

      memcpy(plines->m_shape.get_data(), ppoint, plines->m_shape.get_size_in_bytes());

      if (!m_pshapea)
      {

         m_pshapea = __new(shape_array < path>());

      }

      m_pshapea->add(plines);

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
   // Purpose:     Defines a Rounded rectangle_i32 and places it in the GraphicsPath
   //
   // Parameters:  path.m_ppath		- [out] pointer to GraphicsPath that will recieve the
   //									path data
   //				rectangle_i32			- [in]	Rect that defines the round rectangle_i32 boundaries
   //				iDiameter			- [in]	diameter of the rounded corners (2*radius)
   //
   // Returns:     None
   //
   
   
   //bool path::do_round_rect_corner(const ::rectangle_f64& rectangleCorner, const ::rectangle_f64& rectangleRect, i32 iDiameter, const ::e_border & eborder, int iCorner, bool& bOn)
   //{

   //   switch (iCorner % 4)
   //   {
   //   case 0:
   //   {
   //      if ((eborder & e_border_top_left))
   //      {

   //         if ((eborder & e_border_top_left) == e_border_top_left)
   //         {

   //            add_arc(::rectangle_i32(rectangleCorner.top_left(), ::size_i32(iDiameter, iDiameter)), 180_degrees, 90_degrees);

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

   //            add_arc(::rectangle_i32(rectangleCorner.top_right(), ::size_i32(iDiameter, iDiameter)), 270_degrees, 90_degrees);

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

   //            add_arc(::rectangle_i32(rectangleCorner.bottom_right(), ::size_i32(iDiameter, iDiameter)), 0_degrees, 90_degrees);

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

   //            add_arc(::rectangle_i32(rectangleCorner.bottom_left(), ::size_i32(iDiameter, iDiameter)), 90_degrees, 90_degrees);

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


   bool path::do_round_rectangle_corner(const ::rectangle_f64& rectangleCorner, const ::rectangle_f64& rectangleRect, double dDiameter, const ::e_border & eborder, int iCorner, bool& bOn)
   {

      switch (iCorner % 4)
      {
      case 0:
      {
         if ((eborder & e_border_top_left))
         {

            if ((eborder & e_border_top_left) == e_border_top_left)
            {

               add_arc(::rectangle_f64(rectangleCorner.top_left(), ::size_f64(dDiameter, dDiameter)), 180_degrees, 90_degrees);

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

               add_arc(::rectangle_f64(rectangleCorner.top_right(), ::size_f64(dDiameter, dDiameter)), 270_degrees, 90_degrees);

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

               add_arc(::rectangle_f64(rectangleCorner.bottom_right(), ::size_f64(dDiameter, dDiameter)), 0_degree, 90_degree);

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

               add_arc(::rectangle_f64(rectangleCorner.bottom_left(), ::size_f64(dDiameter, dDiameter)), 90_degrees, 90_degrees);

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


   //bool path::clock_corner(const ::rectangle_i32& rectangleCorner, i32 iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   if (iDiameter == 0)
   //   {

   //      iDiameter = 1;

   //   }

   //   switch (eborder)
   //   {
   //   case e_border_top_left:
   //      add_arc(::rectangle_i32(rectangleCorner.top_left(), ::size_i32(iDiameter, iDiameter)), 180_degree, 90_degree);
   //      return true;
   //   case e_border_top_right:
   //      add_arc(::rectangle_i32(rectangleCorner.top_right() - ::size_i32(iDiameter, 0), ::size_i32(iDiameter, iDiameter)), 270_degree, 90_degree);
   //      return true;
   //   case e_border_bottom_right:
   //      add_arc(::rectangle_i32(rectangleCorner.bottom_right() - ::size_i32(iDiameter, iDiameter), ::size_i32(iDiameter, iDiameter)), 0_degree, 90_degree);
   //      return true;
   //   case e_border_bottom_left:
   //      add_arc(::rectangle_i32(rectangleCorner.bottom_left() - ::size_i32(0, iDiameter), ::size_i32(iDiameter, iDiameter)), 90_degree, 90_degree);
   //      return true;
   //   default:
   //      return false;
   //   }

   //}


   //bool path::counter_corner(const ::rectangle_i32& rectangleCorner, i32 iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   if (iDiameter == 0)
   //   {

   //      iDiameter = 1;

   //   }

   //   switch (eborder)
   //   {
   //   case e_border_top_left:
   //      add_arc(::rectangle_i32(rectangleCorner.top_left(), ::size_i32(iDiameter, iDiameter)), 270_degree, -90_degree);
   //      return true;
   //   case e_border_top_right:
   //      add_arc(::rectangle_i32(rectangleCorner.top_right() - ::size_i32(iDiameter, 0), ::size_i32(iDiameter, iDiameter)), 0_degree, -90_degree);
   //      return true;
   //   case e_border_bottom_right:
   //      add_arc(::rectangle_i32(rectangleCorner.bottom_right() - ::size_i32(iDiameter, iDiameter), ::size_i32(iDiameter, iDiameter)), 90_degree, -90_degree);
   //      return true;
   //   case e_border_bottom_left:
   //      add_arc(::rectangle_i32(rectangleCorner.bottom_left() - ::size_i32(0, iDiameter), ::size_i32(iDiameter, iDiameter)), 180_degree, -90_degree);
   //      return true;
   //   default:
   //      return false;
   //   }

   //}


   bool path::_set_create(::draw2d::graphics* pgraphics)
   {

      if (!m_pshapea)
      {

         return true;

      }

      for (auto& pmatter : *m_pshapea)
      {

         if (!_set(pgraphics, pmatter))
         {

            return false;

         }

      }

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ___shape < path > * pshape)
   {

      auto eshape = pshape->eshape();

      switch (eshape)
      {
      case e_shape_begin_figure:
         return _set(pgraphics, e_shape_begin_figure);
      case e_shape_close_figure:
         return _set(pgraphics, e_shape_close_figure);
      case e_shape_end_figure:
         return _set(pgraphics, e_shape_end_figure);
      case e_shape_arc:
         return _set(pgraphics, pshape->shape < ::arc>());
      //case e_shape_line:
      //   return  _set(pgraphics, pshape->shape < ::line>());
      case e_shape_line:
         return  _set(pgraphics, pshape->shape < ::line>());
      case e_shape_lines:
         return _set(pgraphics, pshape->shape < ::lines>());
      case e_shape_rectangle:
         return _set(pgraphics, pshape->shape < ::rectangle_f64>());
      case e_shape_ellipse:
         return _set(pgraphics, pshape->shape < ::ellipse_f64>());
      case e_shape_polygon:
         return _set(pgraphics, pshape->shape < ::polygon_f64>());
      case e_shape_draw_text:
         m_estatus = success;
         return _set(pgraphics, pshape->shape < ::write_text::draw_text>());
      case e_shape_text_out:
         m_estatus = success;
         return _set(pgraphics, pshape->shape < ::write_text::text_out>());
      default:
         throw "unexpected simple os graphics matter type";
      }

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const enum_shape& eshape)
   {

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const::arc & arc)
   {

      throw ::interface_only();

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::line & line)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::line & line)
   {

      throw ::interface_only();

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const::lines& lines)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const::lines & lines)
   {

      throw ::interface_only();

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::rectangle_i32 & rectangle)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool path::_set(::draw2d::graphics * pgraphics, const ::rectangle_f64 & rectangle)
   {

      throw ::interface_only();

      return false;

   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::ellipse_f64 & ellipse)
   {

      throw ::interface_only();

      return false;

   }
   

   //bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_i32& polygon_i32)
   //{

   //   throw ::interface_only();

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_f64& polygon_f64)
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


   bool path::clock_corner(const ::rectangle_f64& rectangleCorner, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case e_border_top_left:
         add_arc(::rectangle_f64(rectangleCorner.top_left(), ::size_f64(dDiameter, dDiameter)), 180_degree, 90_degree);
         return true;
      case e_border_top_right:
         add_arc(::rectangle_f64(rectangleCorner.top_right() - ::size_f64(dDiameter, 0), ::size_f64(dDiameter, dDiameter)), 270_degree, 90_degree);
         return true;
      case e_border_bottom_right:
         add_arc(::rectangle_f64(rectangleCorner.bottom_right() - ::size_f64(dDiameter, dDiameter), ::size_f64(dDiameter, dDiameter)), 0_degree, 90_degree);
         return true;
      case e_border_bottom_left:
         add_arc(::rectangle_f64(rectangleCorner.bottom_left() - ::size_f64(0, dDiameter), ::size_f64(dDiameter, dDiameter)), 90_degree, 90_degree);
         return true;
      default:
         return false;
      }

   }


   bool path::counter_corner(const ::rectangle_f64& rectangleCorner, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case e_border_top_left:
         add_arc(::rectangle_f64(rectangleCorner.top_left(), ::size_f64(dDiameter, dDiameter)), 270_degree, -90_degree);
         return true;
      case e_border_top_right:
         add_arc(::rectangle_f64(rectangleCorner.top_right() - ::size_f64(dDiameter, 0), ::size_f64(dDiameter, dDiameter)), 0_degree, -90_degree);
         return true;
      case e_border_bottom_right:
         add_arc(::rectangle_f64(rectangleCorner.bottom_right() - ::size_f64(dDiameter, dDiameter), ::size_f64(dDiameter, dDiameter)), 90_degree, -90_degree);
         return true;
      case e_border_bottom_left:
         add_arc(::rectangle_f64(rectangleCorner.bottom_left() - ::size_f64(0, dDiameter), ::size_f64(dDiameter, dDiameter)), 180_degree, -90_degree);
         return true;
      default:
         return false;
      }

   }


   //bool path::add_round_rect(const ::rectangle_i32 & rectangle, i32 iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   // diameter can't exceed width or height
   //   if (iDiameter > rectangle.width())	iDiameter = (i32)rectangle.width();
   //   if (iDiameter > rectangle.height())	iDiameter = (i32)rectangle.height();

   //   ::rectangle_i32 rectangleRect(rectangle);

   //   rectangleRect.deflate(0, 0, 1, 1);

   //   ::size_i32 size(iDiameter, iDiameter);

   //   ::rectangle_i32 rectangleCorner(rectangleRect);

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

   void path::add_round_rectangle(const ::rectangle_f64& rectangle, double dRadius, const ::e_border & eborder)
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

      ::rectangle_f64 rectangleRect(rectangle);

      rectangleRect.deflate(0, 0, 1.0, 1.0);

      ::size_f64 size(dDiameter, dDiameter);

      ::rectangle_f64 rectangleCorner(rectangleRect);

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


   bool path::add_round_top_left(const ::rectangle_f64 & rectangleParam, double iDiameter, const ::e_border & eborder)
   {

      ::rectangle_i32 rectangle(rectangleParam);

      // diameter can't exceed width or height
      if (iDiameter > rectangle.width())	iDiameter = rectangle.width();
      if (iDiameter > rectangle.height())	iDiameter = rectangle.height();

      // define a corner
      auto Corner = rectangle_f64_dimension(rectangle.left, rectangle.top, iDiameter, iDiameter);

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
      Corner.left += (rectangle.width() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 270, 90);

      // bottom right
      Corner.top += (rectangle.height() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner,   0, 90);

      // bottom left
      Corner.left -= (rectangle.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 135, 45);

      add_line(rectangle.left, rectangle.top + rectangle.height() - iDiameter / 2, rectangle.left, rectangle.top + iDiameter / 2);


      Corner.top -= (rectangle.height() - iDiameter - 1);
      Corner.bottom = Corner.top + iDiameter2;
      add_arc(Corner, 180, 90);

      add_line(rectangle.left + iDiameter / 2, rectangle.top, rectangle.left + rectangle.width() - iDiameter / 2, rectangle.top);

      Corner.left += (rectangle.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 270, 45);


      // end path
      //path.m_ppath->CloseFigure();

      return true;

   }



   bool path::add_round_bottom_right(const ::rectangle_f64 & rectangle, double iDiameter, const ::e_border & eborder)
   {
      // diameter can't exceed width or height
      if (iDiameter > rectangle.width())	iDiameter = rectangle.width();
      if (iDiameter > rectangle.height())	iDiameter = rectangle.height();

      // define a corner
      auto Corner = rectangle_f64_dimension(rectangle.left, rectangle.top, iDiameter, iDiameter);

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
      Corner.left += (rectangle.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 315, 45);

      add_line(rectangle.left + rectangle.width(), rectangle.top + iDiameter / 2, rectangle.left + rectangle.width(), rectangle.top + rectangle.height() - iDiameter / 2);

      // bottom right
      Corner.top += (rectangle.height() - iDiameter - 1);
      Corner.bottom = Corner.top + iDiameter2;
      add_arc(Corner, 0_degrees, 90_degrees);

      add_line(rectangle.left + iDiameter / 2, rectangle.top + rectangle.height(), rectangle.left + rectangle.width() - iDiameter / 2, rectangle.top + rectangle.height());

      // bottom left
      Corner.left -= (rectangle.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 90_degrees, 45_degrees);




      //Corner.Y -= (rectangle.height() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 180, 90);



      //Corner.X += (rectangle.width() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 275, 45);


      // end path
      //path.m_ppath->CloseFigure();

      return true;

   }


   bool path::contains(::draw2d::graphics_pointer & pgraphics, const point_f64& point)
   {

      if (!m_pshapea)
      {

         return false;

      }

      int iFill = 0;

      for (auto& pmatter : *m_pshapea)
      {

         if (pmatter->contains(point))
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


   bool path::add_arc_label(const ::rectangle_f64 & rectangleParam)
   {

      ::rectangle_f64 rectangle;
      ::rectangle_f64 r2;

      {

         rectangle.left = rectangleParam.left;

         rectangle.top = rectangleParam.top;

         rectangle.right = rectangleParam.left + rectangleParam.height();

         rectangle.bottom = rectangleParam.bottom;

         add_arc(rectangle,90_degree,180_degree);

      }

      {

         r2.left = rectangle.left + rectangle.height() / 2.0;

         r2.top = rectangle.top;

         r2.right = rectangle.right - rectangle.height() / 2.0;

         r2.bottom = rectangle.bottom;

         //add_line(r2.right, r2.top);

      }

      {

         rectangle.right = rectangleParam.right;

         rectangle.top = rectangleParam.top;

         rectangle.left = rectangleParam.right - rectangleParam.height();

         rectangle.bottom = rectangleParam.bottom;

         add_arc(rectangle,-90_degree,180_degree);

      }

      {

         add_line(r2.left,r2.bottom);

      }

      return true;

   }


   path & path::operator = (const path & path)
   {

      if (this != &path)
      {

         if(!m_pshapea)
         {

            m_pshapea = __new(shape_array <class path>());

         }

         m_pshapea->erase_all();

         for (auto & pshape : *path.m_pshapea)
         {

            m_pshapea->add(::clone(pshape));

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






