#include "framework.h"



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


   //bool path::matter::expand_bounding_rect(RECTANGLE_F64* prectangle) const
   //{

   //   rectangle_f64 r;

   //   if (!get_bounding_rectangle(&r))
   //   {

   //      return false;

   //   }

   //   expand_rect(prectangle, r);

   //   return true;

   //}


   //bool path::matter::expand_bounding_rect(RECTANGLE_I32* prectangle) const
   //{

   //   rectangle_f64 r;

   //   if (!expand_bounding_rect(&r))
   //   {

   //      return false;

   //   }

   //   expand_rect(prectangle, r);

   //   return true;

   //}


   //bool path::matter::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
   //{

   //   ::null_rect(prectangle);

   //   return false;

   //}


   //bool path::matter::get_bounding_rectangle(RECTANGLE_I32* prectangle) const
   //{

   //   ::null_rect(prectangle);

   //   return false;

   //}


   //bool path::matter::contains(const ::point_f64& point) const
   //{

   //   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   //   ::rectangle_f64 r;

   //   if (!get_bounding_rectangle(r))
   //   {

   //      return false;

   //   }

   //   return r.contains(point);

   //}


   //bool path::arc::get_bounding_rectangle(RECTANGLE_F64* prectd) const
   //{

   //   // BUG SS (STILL SIMPLE) m_dRotationAngle ignored

   //   prectd->left = m_pointCenter.x - m_sizeRadius.cx;
   //   prectd->right = m_pointCenter.x + m_sizeRadius.cx;
   //   prectd->top = m_pointCenter.y - m_sizeRadius.cy;
   //   prectd->bottom = m_pointCenter.y + m_sizeRadius.cy;

   //   return true;

   //}



   //bool path::arc::contains(const ::point_f64 & point) const
   //{

   //   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   //   return path::matter::contains(point);

   //}


   //bool path::rectangle_i32::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
   //{

   //   __copy(prectangle, m_rectangle);

   //   return true;

   //}


   //bool path::rectangle_i32::contains(const ::point_f64& point) const
   //{

   //   return m_rectangle.contains(point);

   //}


   //bool path::lines::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
   //{

   //   m_pointa.get_bounding_rectangle(prectangle);

   //   return true;

   //}


   //bool path::lines::contains(const ::point_f64& point) const
   //{

   //   return m_pointa.polygon_contains(point);

   //}



   //bool path::polygon_i32::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
   //{

   //   m_pointa.get_bounding_rectangle(prectangle);

   //   return true;

   //}


   //bool path::polygon_i32::contains(const ::point_f64& point) const
   //{

   //   return m_pointa.polygon_contains(point);

   //}


   //bool path::line::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
   //{

   //   prectangle->left = minimum(m_pointBegin.x, m_pointEnd.x);
   //   prectangle->right = maximum(m_pointBegin.x, m_pointEnd.x);
   //   prectangle->top = minimum(m_pointBegin.y, m_pointEnd.y);
   //   prectangle->bottom = maximum(m_pointBegin.y, m_pointEnd.y);

   //   return true;

   //}

   ////bool path::line::contains(const ::point_f64& point) const
   ////{

   ////   return false;

   ////}


   //bool path::text_out::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
   //{

   //   //__copy(prectangle, m_rectangle);

   //   return true;

   //}


   //bool path::text_out::contains(const ::point_f64& point) const
   //{

   //   return path::matter::contains(point);

   //}


   //bool path::draw_text::get_bounding_rectangle(RECTANGLE_F64* prectangle) const
   //{

   //   __copy(prectangle, m_rectangle);

   //   return true;

   //}



   //bool path::draw_text::contains(const ::point_f64& point) const
   //{

   //   return path::matter::contains(point);

   //}


   ////path::text::text()
   ////{

   ////}


   ////path::text::text(const text& text)
   ////{

   ////   operator = (text);

   ////}


   ////path::text::~text()
   ////{

   ////}


   ////path::text& path::text::operator = (const text& text)
   ////{

   ////   if (this == &text)
   ////   {

   ////      return *this;

   ////   }

   ////   m_point        = text.m_point;
   ////   m_rectangle         = text.m_rectangle;
   ////   m_strText      = text.m_strText;
   ////   m_pfont        = text.m_pfont;

   ////   return *this;

   ////}


   //path::matter::matter()
   //{

   //   m_etype = type_none;

   //}


   //path::matter::~matter()
   //{


   //}


   path::path()
   {

      //m_bFill        = false;
      m_efillmode    = ::draw2d::fill_mode_winding;
      m_bHasPoint    = false;

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


   bool path::get_bounding_rectangle(::rectangle_f64 * prectangle) const
   {

      rectangle_f64 r;

      bool bGotAny = false;

      for(auto & pmatter : m_shapea)
      {

         if (pmatter->expand_bounding_rect(r))
         {

            bGotAny = true;

         }

      }

      if (!bGotAny)
      {

         return false;

      }

      __copy(prectangle, r);

      return true;

   }


   //bool path::get_bounding_rectangle(RECTANGLE_I32* prectangle) const
   //{

   //   ::rectangle_i32 r;

   //   bool bGotAny = false;

   //   for (auto& pmatter : m_shapea)
   //   {

   //      if (pmatter->expand_bounding_rect(r))
   //      {

   //         bGotAny = true;

   //      }

   //   }

   //   if (!bGotAny)
   //   {

   //      return false;

   //   }

   //   __copy(prectangle, r);

   //   return true;

   //}


   bool path::has_current_point()
   {

      return m_bHasPoint;

   }


   point_f64 path::get_current_point()
   {

      if(!m_bHasPoint)
      {

         __throw(::exception::exception("there is no point_i32"));

      }

      return m_pointEnd;

   }


   //bool path::set_current_point(i32 x, i32 y)
   //{

   //   m_pointEnd.x = x;

   //   m_pointEnd.y = y;

   //   m_bHasPoint = true;

   //   return true;

   //}


   bool path::set_current_point(const ::point_f64 & point)
   {

      m_pointEnd = point;

      m_bHasPoint = true;

      return true;

   }


   bool path::add_rect(const ::rectangle_f64& rectangle, const ::angle& angleRotationCenter)
   {

      if (angleRotationCenter == 0)
      {

         return add_rect(rectangle);

      }
      else
      {

         return add_rect(rectangle, rectangle.center(), angleRotationCenter);

      }

   }


   //bool path::add_rect(const ::rectangle_i32& rectParam)
   //{

   //   auto prectangle = __new(rectangle);

   //   __copy(prectangle->m_rectangle, rectParam);

   //   m_shapea.add(prectangle);

   //   return true;

   //}


   bool path::add_rect(const ::rectangle_f64& rectParam)
   {

      m_shapea.add_shape(rectParam);

      return true;

   }


   bool path::add_rect(const ::rectangle_f64& rectangle, const ::point_f64& point, const ::angle& angleRotationCenter)
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

      m_shapea.add_shape(polygon_i32);

      return true;

   }




   bool path::varc(const ::point_f64 & point, double h, const ::angle& angle)
   {

      if (fabs(angle) <= 0.00001 || fabs(h) <= 0.001)
      {
         return false;
      }

      auto parc = __new(arc_shape);

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

      //arc.m_pointBegin.x = arc.m_pointCenter.x + arc.m_dRadiusX * cos(arc.m_angleBeg);
      //arc.m_pointBegin.y = arc.m_pointCenter.y +arc.m_dRadiusY * sin(arc.m_angleBeg);
      //arc.m_pointEnd.x = arc.m_pointCenter.x + arc.m_dRadiusX * cos(arc.m_angleEnd);
      //arc.m_pointEnd.y = arc.m_pointCenter.y + arc.m_dRadiusY * sin(arc.m_angleEnd);

      m_shapea.add(parc);

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

      auto parc = __new(arc_shape);

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

      m_shapea.add_item(parc);

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

      auto parc = __new(arc_shape);

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

      m_shapea.add(parc);

      m_bHasPoint = true;

      m_pointBegin = arc.m_pointBegin;

      m_pointEnd = arc.m_pointEnd;

      set_modified();

      return true;

   }


   //bool path::add_move(double x, double y)
   //{

   //   __pointer(matter) pmatter;

   //   pmatter = __new(matter);

   //   pmatter->m_etype               = matter::type_move;
   //   pmatter->u.m_move.m_x          = x;
   //   pmatter->u.m_move.m_y          = y;

   //   m_shapea.add(pmatter);

   //   m_bHasPoint = true;
   //   m_point.x = x;
   //   m_point.y = y;

   //   set_modified();

   //   return true;

   //}


   //bool path::add_line(double x,double y)
   //{

   //   if(!has_current_point())
   //   {
   //
   //      return set_current_point(x,y);

   //   }

   //   return add_line(m_pointEnd, point_f64(x, y));

   //}


   //bool path::add_line(i32 x, i32 y)
   //{

   //   return add_line((double)x,(double)y);

   //}


   //bool path::add_line(double x,double y,double x2,double y2)
   //{

   //   auto pline = __new(line);

   //   pline->m_pointBegin.x = x;

   //   pline->m_pointBegin.y = y;

   //   pline->m_pointEnd.x = x2;

   //   pline->m_pointEnd.y = y2;

   //   m_shapea.add(pline);

   //   m_bHasPoint = true;

   //   m_pointBegin = pline->m_pointBegin;

   //   m_pointEnd = pline->m_pointEnd;

   //   set_modified();

   //   return true;

   //}


   //bool path::add_line(i32 x,i32 y,i32 x2,i32 y2)
   //{

   //   return add_line((double) x, (double)y, (double) x2, (double) y2);

   //}


   bool path::begin_figure()
   {

      m_shapea.add_shape(e_shape_begin_figure);

      m_bHasPoint = false;

      set_modified();

      return true;

   }


   bool path::close_figure()
   {

      m_shapea.add_shape(e_shape_close_figure);

      set_modified();

      return true;

   }


   bool path::add_text_out(const ::point_f64 & point, const ::string & strText,::write_text::font_pointer pfont)
   {

      auto ptextout = __new(::write_text::text_out_shape);

      auto& textout = ptextout->m_shape;

      textout.m_strText     = strText;
      textout.m_pfont       = pfont;
      textout.m_point       = point;

      m_shapea.add_item(ptextout);

      return true;

   }


   bool path::add_draw_text(const string& strText, const ::rectangle_f64& rectangle, const ::e_align & ealign, const ::e_draw_text & edrawtext , ::write_text::font_pointer pfont)
   {

      auto pdrawtext = __new(::write_text::draw_text_shape);

      auto & drawtext = pdrawtext->m_shape;


      drawtext.m_strText            = strText;
      drawtext.m_pfont              = pfont;


      drawtext.m_rectangle          = rectangle;
      drawtext.m_ealign             = ealign;
      drawtext.m_edrawtext          = edrawtext;

      m_shapea.add(pdrawtext);

      return true;

   }


   bool path::add_line(const point_f64 & p1, const point_f64 & p2)
   {

      auto pline = __new(line_shape);

      ::line & line = pline->m_shape;

      line.m_p1 = p1;

      line.m_p2 = p2;

      m_shapea.add(pline);

      m_pointBegin = line.m_p1;

      m_pointEnd = line.m_p2;

      return true;

   }


   bool path::add_line(const point_f64 & point)
   {

      auto pline = __new(line_shape);

      ::line & line = pline->m_shape;

      line.m_p1 = m_pointEnd;

      line.m_p2 = point;

      m_shapea.add(pline);

      m_pointBegin = line.m_p1;

      m_pointEnd = line.m_p2;

      return true;

   }


   //bool path::add_polygon(const POINT_I32* ppoint, ::count nCount)
   //{

   //   auto ppolygon = __new(polygon_shape);

   //   for (i32 i = 0; i < nCount; i++)
   //   {

   //      ppolygon->m_shape.add(point_f64(ppoint[i].x, ppoint[i].y));

   //   }

   //   m_shapea.add_item(ppolygon);

   //   return true;

   //}


   bool path::add_polygon(const ::point_f64 * ppoint, ::count nCount)
   {

      auto ppolygon = __new(polygon_shape);

      ppolygon->m_shape.set_size(nCount);

      memcpy(ppolygon->m_shape.get_data(), ppoint, ppolygon->m_shape.get_size_in_bytes());

      m_shapea.add(ppolygon);

      return true;

   }



   //bool path::add_lines(const POINT_I32 * ppoint, ::count nCount)
   //{

   //   auto plines = __new(lines_shape);

   //   plines->m_shape.set_size(nCount);

   //   memcpy(plines->m_shape.get_data(), ppoint, plines->m_shape.get_size_in_bytes());

   //   m_shapea.add(plines);

   //   return true;

   //}


   bool path::add_lines(const ::point_f64 * ppoint, ::count nCount)
   {

      auto plines = __new(lines_shape);

      plines->m_shape.set_size(nCount);

      memcpy(plines->m_shape.get_data(), ppoint, plines->m_shape.get_size_in_bytes());

      m_shapea.add(plines);

      return true;

   }


   void * path::detach()
   {

      ::exception::throw_interface_only();

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
   
   
   //bool path::do_round_rect_corner(const ::rectangle_f64& rectCorner, const ::rectangle_f64& rectRect, i32 iDiameter, const ::e_border & eborder, int iCorner, bool& bOn)
   //{

   //   switch (iCorner % 4)
   //   {
   //   case 0:
   //   {
   //      if ((eborder & e_border_top_left))
   //      {

   //         if ((eborder & e_border_top_left) == e_border_top_left)
   //         {

   //            add_arc(::rectangle_i32(rectCorner.top_left(), ::size_i32(iDiameter, iDiameter)), 180_degrees, 90_degrees);

   //            bOn = true;

   //         }
   //         else if(bOn)
   //         {

   //            add_line(rectRect.top_left());

   //            bOn = false;

   //         }
   //         else
   //         {

   //            set_current_point(rectRect.top_left());

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

   //            add_arc(::rectangle_i32(rectCorner.top_right(), ::size_i32(iDiameter, iDiameter)), 270_degrees, 90_degrees);

   //            bOn = true;

   //         }
   //         else if(bOn)
   //         {

   //            add_line(rectRect.top_right());

   //            bOn = false;

   //         }
   //         else
   //         {

   //            set_current_point(rectRect.top_right());

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

   //            add_arc(::rectangle_i32(rectCorner.bottom_right(), ::size_i32(iDiameter, iDiameter)), 0_degrees, 90_degrees);

   //            bOn = true;

   //         }
   //         else if (bOn)
   //         {

   //            add_line(rectRect.bottom_right());

   //            bOn = false;

   //         }
   //         else
   //         {

   //            set_current_point(rectRect.bottom_right());

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

   //            add_arc(::rectangle_i32(rectCorner.bottom_left(), ::size_i32(iDiameter, iDiameter)), 90_degrees, 90_degrees);

   //            bOn = true;

   //         }
   //         else if(bOn)
   //         {

   //            add_line(rectRect.bottom_left());

   //            bOn = false;

   //         }
   //         else
   //         {

   //            set_current_point(rectRect.bottom_left());

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


   bool path::do_round_rect_corner(const ::rectangle_f64& rectCorner, const ::rectangle_f64& rectRect, double dDiameter, const ::e_border & eborder, int iCorner, bool& bOn)
   {

      switch (iCorner % 4)
      {
      case 0:
      {
         if ((eborder & e_border_top_left))
         {

            if ((eborder & e_border_top_left) == e_border_top_left)
            {

               add_arc(::rectangle_f64(rectCorner.top_left(), ::size_f64(dDiameter, dDiameter)), 180_degrees, 90_degrees);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.top_left());

               bOn = false;

            }
            else
            {

               set_current_point(rectRect.top_left());

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

               add_arc(::rectangle_f64(rectCorner.top_right(), ::size_f64(dDiameter, dDiameter)), 270_degrees, 90_degrees);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.top_right());

               bOn = false;

            }
            else
            {

               set_current_point(rectRect.top_right());

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

               add_arc(::rectangle_f64(rectCorner.bottom_right(), ::size_f64(dDiameter, dDiameter)), 0_degree, 90_degree);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.bottom_right());

               bOn = false;

            }
            else
            {

               set_current_point(rectRect.bottom_right());

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

               add_arc(::rectangle_f64(rectCorner.bottom_left(), ::size_f64(dDiameter, dDiameter)), 90_degrees, 90_degrees);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.bottom_left());

               bOn = false;

            }
            else
            {

               set_current_point(rectRect.bottom_left());

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


   //bool path::clock_corner(const ::rectangle_i32& rectCorner, i32 iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   if (iDiameter == 0)
   //   {

   //      iDiameter = 1;

   //   }

   //   switch (eborder)
   //   {
   //   case e_border_top_left:
   //      add_arc(::rectangle_i32(rectCorner.top_left(), ::size_i32(iDiameter, iDiameter)), 180_degree, 90_degree);
   //      return true;
   //   case e_border_top_right:
   //      add_arc(::rectangle_i32(rectCorner.top_right() - ::size_i32(iDiameter, 0), ::size_i32(iDiameter, iDiameter)), 270_degree, 90_degree);
   //      return true;
   //   case e_border_bottom_right:
   //      add_arc(::rectangle_i32(rectCorner.bottom_right() - ::size_i32(iDiameter, iDiameter), ::size_i32(iDiameter, iDiameter)), 0_degree, 90_degree);
   //      return true;
   //   case e_border_bottom_left:
   //      add_arc(::rectangle_i32(rectCorner.bottom_left() - ::size_i32(0, iDiameter), ::size_i32(iDiameter, iDiameter)), 90_degree, 90_degree);
   //      return true;
   //   default:
   //      return false;
   //   }

   //}


   //bool path::counter_corner(const ::rectangle_i32& rectCorner, i32 iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   if (iDiameter == 0)
   //   {

   //      iDiameter = 1;

   //   }

   //   switch (eborder)
   //   {
   //   case e_border_top_left:
   //      add_arc(::rectangle_i32(rectCorner.top_left(), ::size_i32(iDiameter, iDiameter)), 270_degree, -90_degree);
   //      return true;
   //   case e_border_top_right:
   //      add_arc(::rectangle_i32(rectCorner.top_right() - ::size_i32(iDiameter, 0), ::size_i32(iDiameter, iDiameter)), 0_degree, -90_degree);
   //      return true;
   //   case e_border_bottom_right:
   //      add_arc(::rectangle_i32(rectCorner.bottom_right() - ::size_i32(iDiameter, iDiameter), ::size_i32(iDiameter, iDiameter)), 90_degree, -90_degree);
   //      return true;
   //   case e_border_bottom_left:
   //      add_arc(::rectangle_i32(rectCorner.bottom_left() - ::size_i32(0, iDiameter), ::size_i32(iDiameter, iDiameter)), 180_degree, -90_degree);
   //      return true;
   //   default:
   //      return false;
   //   }

   //}


   bool path::_set_create(::draw2d::graphics* pgraphics)
   {

      for (auto& pmatter : m_shapea)
      {

         if (!_set(pgraphics, pmatter))
         {

            return false;

         }

      }

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ___shape * pshape)
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
      case e_shape_polygon:
         return _set(pgraphics, pshape->shape < ::polygon_f64>());
      case e_shape_draw_text:
         return _set(pgraphics, pshape->shape < ::write_text::draw_text>());
      case e_shape_text_out:
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

      __throw(error_interface_only);

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::line & line)
   //{

   //   __throw(error_interface_only);

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::line & line)
   {

      __throw(error_interface_only);

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const::lines& lines)
   //{

   //   __throw(error_interface_only);

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const::lines & lines)
   {

      __throw(error_interface_only);

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::rectangle_i32 & rectangle)
   //{

   //   __throw(error_interface_only);

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::rectangle_f64 & rectangle)
   {

      __throw(error_interface_only);

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_i32& polygon_i32)
   //{

   //   __throw(error_interface_only);

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygon_f64& polygon_f64)
   {

      __throw(error_interface_only);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::write_text::text_out & textout)
   {

      __throw(error_interface_only);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::write_text::draw_text& drawtext)
   {

      __throw(error_interface_only);

      return false;

   }


   bool path::clock_corner(const ::rectangle_f64& rectCorner, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case e_border_top_left:
         add_arc(::rectangle_f64(rectCorner.top_left(), ::size_f64(dDiameter, dDiameter)), 180_degree, 90_degree);
         return true;
      case e_border_top_right:
         add_arc(::rectangle_f64(rectCorner.top_right() - ::size_f64(dDiameter, 0), ::size_f64(dDiameter, dDiameter)), 270_degree, 90_degree);
         return true;
      case e_border_bottom_right:
         add_arc(::rectangle_f64(rectCorner.bottom_right() - ::size_f64(dDiameter, dDiameter), ::size_f64(dDiameter, dDiameter)), 0_degree, 90_degree);
         return true;
      case e_border_bottom_left:
         add_arc(::rectangle_f64(rectCorner.bottom_left() - ::size_f64(0, dDiameter), ::size_f64(dDiameter, dDiameter)), 90_degree, 90_degree);
         return true;
      default:
         return false;
      }

   }


   bool path::counter_corner(const ::rectangle_f64& rectCorner, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case e_border_top_left:
         add_arc(::rectangle_f64(rectCorner.top_left(), ::size_f64(dDiameter, dDiameter)), 270_degree, -90_degree);
         return true;
      case e_border_top_right:
         add_arc(::rectangle_f64(rectCorner.top_right() - ::size_f64(dDiameter, 0), ::size_f64(dDiameter, dDiameter)), 0_degree, -90_degree);
         return true;
      case e_border_bottom_right:
         add_arc(::rectangle_f64(rectCorner.bottom_right() - ::size_f64(dDiameter, dDiameter), ::size_f64(dDiameter, dDiameter)), 90_degree, -90_degree);
         return true;
      case e_border_bottom_left:
         add_arc(::rectangle_f64(rectCorner.bottom_left() - ::size_f64(0, dDiameter), ::size_f64(dDiameter, dDiameter)), 180_degree, -90_degree);
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

   //   ::rectangle_i32 rectRect(rectangle);

   //   rectRect.deflate(0, 0, 1, 1);

   //   ::size_i32 size(iDiameter, iDiameter);

   //   ::rectangle_i32 rectCorner(rectRect);

   //   rectCorner.deflate(0, 0, iDiameter, iDiameter);

   //   bool bOn = false;

   //   int iCount = 0;

   //   if (eborder & e_border_all)
   //   {

   //      //begin_figure(true, ::draw2d::fill_mode_winding);

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

   //         do_round_rect_corner(rectCorner, rectRect, iDiameter, eborder, iCorner, bOn);

   //      }

   //      //end_figure(bOn);

   //      close_figure();

   //      return true;

   //   }


   //   return false;

   //}

   bool path::add_round_rect(const ::rectangle_f64& rectangle, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      // diameter can't exceed width or height
      if (dDiameter > rectangle.width())	dDiameter = (double)rectangle.width();
      if (dDiameter > rectangle.height()) dDiameter = (double)rectangle.height();

      ::rectangle_f64 rectRect(rectangle);

      rectRect.deflate(0, 0, 1.0, 1.0);

      ::size_f64 size(dDiameter, dDiameter);

      ::rectangle_f64 rectCorner(rectRect);

      rectCorner.deflate(0, 0, dDiameter, dDiameter);

      bool bOn = false;

      int iCount = 0;

      if (eborder & e_border_all)
      {

         //begin_figure(true, ::draw2d::fill_mode_winding);

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

            do_round_rect_corner(rectCorner, rectRect, dDiameter, eborder, iCorner, bOn);

         }

         close_figure();

         return true;

      }


      return false;

   }


   bool path::add_round_top_left(const ::rectangle_f64 & rectParam, double iDiameter, const ::e_border & eborder)
   {

      ::rectangle_i32 rectangle(rectParam);

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

      int iFill = 0;

      for (auto& pmatter : m_shapea)
      {

         if (pmatter->contains(point))
         {

            if (m_efillmode == ::draw2d::fill_mode_winding)
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


   bool path::add_arc_label(const ::rectangle_f64 & rectParam)
   {

      ::rectangle_f64 rectangle;
      ::rectangle_f64 r2;

      {

         rectangle.left = rectParam.left;

         rectangle.top = rectParam.top;

         rectangle.right = rectParam.left + rectParam.height();

         rectangle.bottom = rectParam.bottom;

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

         rectangle.right = rectParam.right;

         rectangle.top = rectParam.top;

         rectangle.left = rectParam.right - rectParam.height();

         rectangle.bottom = rectParam.bottom;

         add_arc(rectangle,-90_degree,180_degree);

      }

      {

         add_line(r2.left,r2.bottom);

      }

      return true;

   }


} // namespace draw2d






