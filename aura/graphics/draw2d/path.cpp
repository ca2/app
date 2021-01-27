#include "framework.h"



pointd arc_point(double dAngle, sized sizeRadius)
{

   double ab = sizeRadius.cx * sizeRadius.cy;

   pointd p;

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


   //bool path::matter::expand_bounding_rect(RECTD* prect) const
   //{

   //   rectd r;

   //   if (!get_bounding_rect(&r))
   //   {

   //      return false;

   //   }

   //   expand_rect(prect, r);

   //   return true;

   //}


   //bool path::matter::expand_bounding_rect(RECT32* prect) const
   //{

   //   rectd r;

   //   if (!expand_bounding_rect(&r))
   //   {

   //      return false;

   //   }

   //   expand_rect(prect, r);

   //   return true;

   //}


   //bool path::matter::get_bounding_rect(RECTD* prect) const
   //{

   //   ::null_rect(prect);

   //   return false;

   //}


   //bool path::matter::get_bounding_rect(RECT32* prect) const
   //{

   //   ::null_rect(prect);

   //   return false;

   //}


   //bool path::matter::contains(const ::pointd& point) const
   //{

   //   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   //   ::rectd r;

   //   if (!get_bounding_rect(r))
   //   {

   //      return false;

   //   }

   //   return r.contains(point);

   //}


   //bool path::arc::get_bounding_rect(RECTD* prectd) const
   //{

   //   // BUG SS (STILL SIMPLE) m_dRotationAngle ignored

   //   prectd->left = m_pointCenter.x - m_sizeRadius.cx;
   //   prectd->right = m_pointCenter.x + m_sizeRadius.cx;
   //   prectd->top = m_pointCenter.y - m_sizeRadius.cy;
   //   prectd->bottom = m_pointCenter.y + m_sizeRadius.cy;

   //   return true;

   //}



   //bool path::arc::contains(const ::pointd & point) const
   //{

   //   // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

   //   return path::matter::contains(point);

   //}


   //bool path::rect::get_bounding_rect(RECTD* prect) const
   //{

   //   __copy(prect, m_rect);

   //   return true;

   //}


   //bool path::rect::contains(const ::pointd& point) const
   //{

   //   return m_rect.contains(point);

   //}


   //bool path::lines::get_bounding_rect(RECTD* prect) const
   //{

   //   m_pointa.get_bounding_rect(prect);

   //   return true;

   //}


   //bool path::lines::contains(const ::pointd& point) const
   //{

   //   return m_pointa.polygon_contains(point);

   //}



   //bool path::polygon::get_bounding_rect(RECTD* prect) const
   //{

   //   m_pointa.get_bounding_rect(prect);

   //   return true;

   //}


   //bool path::polygon::contains(const ::pointd& point) const
   //{

   //   return m_pointa.polygon_contains(point);

   //}


   //bool path::line::get_bounding_rect(RECTD* prect) const
   //{

   //   prect->left = min(m_pointBeg.x, m_pointEnd.x);
   //   prect->right = max(m_pointBeg.x, m_pointEnd.x);
   //   prect->top = min(m_pointBeg.y, m_pointEnd.y);
   //   prect->bottom = max(m_pointBeg.y, m_pointEnd.y);

   //   return true;

   //}

   ////bool path::line::contains(const ::pointd& point) const
   ////{

   ////   return false;

   ////}


   //bool path::text_out::get_bounding_rect(RECTD* prect) const
   //{

   //   //__copy(prect, m_rect);

   //   return true;

   //}


   //bool path::text_out::contains(const ::pointd& point) const
   //{

   //   return path::matter::contains(point);

   //}


   //bool path::draw_text::get_bounding_rect(RECTD* prect) const
   //{

   //   __copy(prect, m_rect);

   //   return true;

   //}



   //bool path::draw_text::contains(const ::pointd& point) const
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
   ////   m_rect         = text.m_rect;
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


   bool path::get_bounding_rect(::rectd * prect) const
   {

      rectd r;

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

      __copy(prect, r);

      return true;

   }


   //bool path::get_bounding_rect(RECT32* prect) const
   //{

   //   ::rect r;

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

   //   __copy(prect, r);

   //   return true;

   //}


   bool path::has_current_point()
   {

      return m_bHasPoint;

   }


   pointd path::get_current_point()
   {

      if(!m_bHasPoint)
         __throw(::exception::exception("there is no point"));

      return m_pointEnd;

   }


   //bool path::set_current_point(i32 x, i32 y)
   //{

   //   m_pointEnd.x = x;

   //   m_pointEnd.y = y;

   //   m_bHasPoint = true;

   //   return true;

   //}


   bool path::set_current_point(const ::pointd & point)
   {

      m_pointEnd = point;

      m_bHasPoint = true;

      return true;

   }


   //bool path::add_rect(const ::rect& rect, const ::angle& angleRotationCenter)
   //{

   //   if (angleRotationCenter == 0)
   //   {

   //      return add_rect(rect);

   //   }
   //   else
   //   {

   //      return add_rect(rect, rect.center(), angleRotationCenter);

   //   }

   //}


   bool path::add_rect(const ::rectd& rect, const ::angle& angleRotationCenter)
   {

      if (angleRotationCenter == 0)
      {

         return add_rect(rect);

      }
      else
      {

         return add_rect(rect, rect.center(), angleRotationCenter);

      }

   }


   //bool path::add_rect(const ::rect& rectParam)
   //{

   //   auto prect = __new(rect);

   //   __copy(prect->m_rect, rectParam);

   //   m_shapea.add(prect);

   //   return true;

   //}


   bool path::add_rect(const ::rectd& rectParam)
   {

      m_shapea.add_shape(rectParam);

      return true;

   }


   bool path::add_rect(const ::rectd& rect, const ::pointd& point, const ::angle& angleRotationCenter)
   {

      ::polygond polygon;

      polygon.set_size(4);

      polygon[0].x = rect.left;
      polygon[0].y = rect.top;

      polygon[1].x = rect.right;
      polygon[1].y = rect.top;

      polygon[2].x = rect.right;
      polygon[2].y = rect.bottom;

      polygon[3].x = rect.left;
      polygon[3].y = rect.bottom;

      polygon.rotate(angleRotationCenter, point);

      m_shapea.add_shape(polygon);

      return true;

   }




   bool path::varc(const ::pointd & point, double h, const ::angle& angle)
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
      arc.m_pointBeg = arc.m_pointCenter + arc_point(arc.m_angleBeg, arc.m_sizeRadius);
      arc.m_pointEnd = arc.m_pointCenter + arc_point(arc.m_angleEnd2, arc.m_sizeRadius);

      //arc.m_pointBeg.x = arc.m_pointCenter.x + arc.m_dRadiusX * cos(arc.m_angleBeg);
      //arc.m_pointBeg.y = arc.m_pointCenter.y +arc.m_dRadiusY * sin(arc.m_angleBeg);
      //arc.m_pointEnd.x = arc.m_pointCenter.x + arc.m_dRadiusX * cos(arc.m_angleEnd);
      //arc.m_pointEnd.y = arc.m_pointCenter.y + arc.m_dRadiusY * sin(arc.m_angleEnd);

      m_shapea.add(parc);

      m_bHasPoint = true;

      m_pointBeg = arc.m_pointBeg;

      m_pointEnd = arc.m_pointEnd;

      set_modified();

      return true;

   }


   bool path::harc(const ::pointd & point, double w, const ::angle& angle)
   {


      if (fabs(angle) <= 0.00001 || fabs(w) <= 0.001)
      {

         return false;

      }

      auto parc = __new(arc_shape);

      ::arc& arc = parc->m_shape;

      ::angle t = angle + 90_degrees;
      arc.m_pointBeg.x = point.x + w / 2.0;
      double a = (point.x - arc.m_pointBeg.x) / cos(t);
      double x = point.x - arc.m_pointBeg.x;
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

      arc.m_pointBeg = arc.m_pointCenter + arc_point(arc.m_angleBeg, arc.m_sizeRadius);
      arc.m_pointEnd = arc.m_pointCenter + arc_point(arc.m_angleEnd2, arc.m_sizeRadius);

      m_shapea.add_item(parc);

      m_bHasPoint = true;

      m_pointBeg = arc.m_pointBeg;

      m_pointEnd = arc.m_pointEnd;

      set_modified();

      return true;

   }


   bool path::add_arc(const ::rectd & rect, const ::angle & angleBeg, const ::angle& angleExt)
   {

      if (rect.width() <= 0 || rect.height() <= 0)
      {

         return true;

      }

      auto parc = __new(arc_shape);

      ::arc& arc = parc->m_shape;

      arc.m_pointCenter.x   = (rect.right + rect.left) / 2.0;
      arc.m_pointCenter.y   = (rect.bottom + rect.top) / 2.0;
      arc.m_sizeRadius.cx   = fabs(rect.right - rect.left) / 2.0;
      arc.m_sizeRadius.cy   = fabs(rect.bottom - rect.top) / 2.0;
      arc.m_angleBeg        = angleBeg;
      arc.m_angleExt        = angleExt;
      arc.m_angleEnd2       = angleBeg + angleExt;
      arc.m_angleRotation   = 0_degrees;
      arc.m_pointBeg        = arc.m_pointCenter + arc_point(arc.m_angleBeg, arc.m_sizeRadius);
      arc.m_pointEnd        = arc.m_pointCenter + arc_point(arc.m_angleEnd2, arc.m_sizeRadius);

      m_shapea.add(parc);

      m_bHasPoint = true;

      m_pointBeg = arc.m_pointBeg;

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

   //   return add_line(m_pointEnd, pointd(x, y));

   //}


   //bool path::add_line(i32 x, i32 y)
   //{

   //   return add_line((double)x,(double)y);

   //}


   //bool path::add_line(double x,double y,double x2,double y2)
   //{

   //   auto pline = __new(line);

   //   pline->m_pointBeg.x = x;

   //   pline->m_pointBeg.y = y;

   //   pline->m_pointEnd.x = x2;

   //   pline->m_pointEnd.y = y2;

   //   m_shapea.add(pline);

   //   m_bHasPoint = true;

   //   m_pointBeg = pline->m_pointBeg;

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


   bool path::add_text_out(const ::pointd & point, const string & strText,::draw2d::font_pointer pfont)
   {

      auto ptextout = __new(text_out_shape);

      auto& textout = ptextout->m_shape;

      textout.m_strText     = strText;
      textout.m_pfont       = pfont;
      textout.m_point       = point;

      m_shapea.add_item(ptextout);

      return true;

   }


   bool path::add_draw_text(const string& strText, const ::rectd& rect, const ::e_align & ealign, const ::e_draw_text & edrawtext , ::draw2d::font_pointer pfont)
   {

      auto pdrawtext = __new(draw_text_shape);

      ::draw_text & drawtext = pdrawtext->m_shape;

      drawtext.m_strText          = strText;
      drawtext.m_pfont            = pfont;

      drawtext.m_rect             = rect;
      drawtext.m_ealign = ealign;
      drawtext.m_edrawtext   = edrawtext;


      m_shapea.add(pdrawtext);

      return true;

   }


   bool path::add_line(const pointd & p1, const pointd & p2)
   {

      auto pline = __new(lined_shape);

      ::lined& line = pline->m_shape;

      line.m_p1 = p1;

      line.m_p2 = p2;

      m_shapea.add(pline);

      m_pointBeg = line.m_p1;

      m_pointEnd = line.m_p2;

      return true;

   }


   bool path::add_line(const pointd & point)
   {

      auto pline = __new(lined_shape);

      ::lined& line = pline->m_shape;

      line.m_p1 = m_pointEnd;

      line.m_p2 = point;

      m_shapea.add(pline);

      m_pointBeg = line.m_p1;

      m_pointEnd = line.m_p2;

      return true;

   }


   //bool path::add_polygon(const POINT32* ppoint, ::count nCount)
   //{

   //   auto ppolygon = __new(polygon_shape);

   //   for (i32 i = 0; i < nCount; i++)
   //   {

   //      ppolygon->m_shape.add(pointd(ppoint[i].x, ppoint[i].y));

   //   }

   //   m_shapea.add_item(ppolygon);

   //   return true;

   //}


   bool path::add_polygon(const ::pointd * ppoint, ::count nCount)
   {

      auto ppolygon = __new(polygond_shape);

      ppolygon->m_shape.set_size(nCount);

      memcpy(ppolygon->m_shape.get_data(), ppoint, ppolygon->m_shape.get_size_in_bytes());

      m_shapea.add(ppolygon);

      return true;

   }



   //bool path::add_lines(const POINT32 * ppoint, ::count nCount)
   //{

   //   auto plines = __new(lines_shape);

   //   plines->m_shape.set_size(nCount);

   //   memcpy(plines->m_shape.get_data(), ppoint, plines->m_shape.get_size_in_bytes());

   //   m_shapea.add(plines);

   //   return true;

   //}


   bool path::add_lines(const ::pointd * ppoint, ::count nCount)
   {

      auto plines = __new(linesd_shape);

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
   // Purpose:     Defines a Rounded rectangle and places it in the GraphicsPath
   //
   // Parameters:  path.m_ppath		- [out] pointer to GraphicsPath that will recieve the
   //									path data
   //				rect			- [in]	Rect that defines the round rectangle boundaries
   //				iDiameter			- [in]	diameter of the rounded corners (2*radius)
   //
   // Returns:     None
   //
   
   
   //bool path::do_round_rect_corner(const ::rectd& rectCorner, const ::rectd& rectRect, i32 iDiameter, const ::e_border & eborder, int iCorner, bool& bOn)
   //{

   //   switch (iCorner % 4)
   //   {
   //   case 0:
   //   {
   //      if ((eborder & e_border_top_left))
   //      {

   //         if ((eborder & e_border_top_left) == e_border_top_left)
   //         {

   //            add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 180_degrees, 90_degrees);

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

   //            add_arc(::rect(rectCorner.top_right(), ::size(iDiameter, iDiameter)), 270_degrees, 90_degrees);

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

   //            add_arc(::rect(rectCorner.bottom_right(), ::size(iDiameter, iDiameter)), 0_degrees, 90_degrees);

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

   //            add_arc(::rect(rectCorner.bottom_left(), ::size(iDiameter, iDiameter)), 90_degrees, 90_degrees);

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
   //      ASSERT(FALSE);
   //      return false;
   //   }

   //   };

   //   return true;

   //}


   bool path::do_round_rect_corner(const ::rectd& rectCorner, const ::rectd& rectRect, double dDiameter, const ::e_border & eborder, int iCorner, bool& bOn)
   {

      switch (iCorner % 4)
      {
      case 0:
      {
         if ((eborder & e_border_top_left))
         {

            if ((eborder & e_border_top_left) == e_border_top_left)
            {

               add_arc(::rectd(rectCorner.top_left(), ::sized(dDiameter, dDiameter)), 180_degrees, 90_degrees);

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

               add_arc(::rectd(rectCorner.top_right(), ::sized(dDiameter, dDiameter)), 270_degrees, 90_degrees);

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

               add_arc(::rectd(rectCorner.bottom_right(), ::sized(dDiameter, dDiameter)), 0_degree, 90_degree);

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

               add_arc(::rectd(rectCorner.bottom_left(), ::sized(dDiameter, dDiameter)), 90_degrees, 90_degrees);

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
         ASSERT(FALSE);
         return false;
      }

      };

      return true;

   }


   //bool path::clock_corner(const ::rect& rectCorner, i32 iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   if (iDiameter == 0)
   //   {

   //      iDiameter = 1;

   //   }

   //   switch (eborder)
   //   {
   //   case e_border_top_left:
   //      add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 180_degree, 90_degree);
   //      return true;
   //   case e_border_top_right:
   //      add_arc(::rect(rectCorner.top_right() - ::size(iDiameter, 0), ::size(iDiameter, iDiameter)), 270_degree, 90_degree);
   //      return true;
   //   case e_border_bottom_right:
   //      add_arc(::rect(rectCorner.bottom_right() - ::size(iDiameter, iDiameter), ::size(iDiameter, iDiameter)), 0_degree, 90_degree);
   //      return true;
   //   case e_border_bottom_left:
   //      add_arc(::rect(rectCorner.bottom_left() - ::size(0, iDiameter), ::size(iDiameter, iDiameter)), 90_degree, 90_degree);
   //      return true;
   //   default:
   //      return false;
   //   }

   //}


   //bool path::counter_corner(const ::rect& rectCorner, i32 iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   if (iDiameter == 0)
   //   {

   //      iDiameter = 1;

   //   }

   //   switch (eborder)
   //   {
   //   case e_border_top_left:
   //      add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 270_degree, -90_degree);
   //      return true;
   //   case e_border_top_right:
   //      add_arc(::rect(rectCorner.top_right() - ::size(iDiameter, 0), ::size(iDiameter, iDiameter)), 0_degree, -90_degree);
   //      return true;
   //   case e_border_bottom_right:
   //      add_arc(::rect(rectCorner.bottom_right() - ::size(iDiameter, iDiameter), ::size(iDiameter, iDiameter)), 90_degree, -90_degree);
   //      return true;
   //   case e_border_bottom_left:
   //      add_arc(::rect(rectCorner.bottom_left() - ::size(0, iDiameter), ::size(iDiameter, iDiameter)), 180_degree, -90_degree);
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
      case e_shape_lined:
         return  _set(pgraphics, pshape->shape < ::lined>());
      //case e_shape_lines:
      //   return _set(pgraphics, pshape->shape < ::lines>());
      case e_shape_linesd:
         return _set(pgraphics, pshape->shape < ::linesd>());
      //case e_shape_rect:
      //   return _set(pgraphics, pshape->shape < ::rect>());
      case e_shape_rectd:
         return _set(pgraphics, pshape->shape < ::rectd>());
      //case e_shape_polygon:
      //   return _set(pgraphics, pshape->shape < ::polygon>());
      case e_shape_polygond:
         return _set(pgraphics, pshape->shape < ::polygond>());
      case e_shape_draw_text:
         return _set(pgraphics, pshape->shape < ::draw_text>());
      case e_shape_text_out:
         return _set(pgraphics, pshape->shape < ::text_out>());
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

      __throw(interface_only_exception);

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::line & line)
   //{

   //   __throw(interface_only_exception);

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const::lined& line)
   {

      __throw(interface_only_exception);

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const::lines& lines)
   //{

   //   __throw(interface_only_exception);

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const::linesd& lines)
   {

      __throw(interface_only_exception);

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::rect & rect)
   //{

   //   __throw(interface_only_exception);

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::rectd & rect)
   {

      __throw(interface_only_exception);

      return false;

   }


   //bool path::_set(::draw2d::graphics* pgraphics, const ::polygon& polygon)
   //{

   //   __throw(interface_only_exception);

   //   return false;

   //}


   bool path::_set(::draw2d::graphics* pgraphics, const ::polygond& polygond)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::text_out & textout)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, const ::draw_text& drawtext)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::clock_corner(const ::rectd& rectCorner, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case e_border_top_left:
         add_arc(::rectd(rectCorner.top_left(), ::sized(dDiameter, dDiameter)), 180_degree, 90_degree);
         return true;
      case e_border_top_right:
         add_arc(::rectd(rectCorner.top_right() - ::sized(dDiameter, 0), ::sized(dDiameter, dDiameter)), 270_degree, 90_degree);
         return true;
      case e_border_bottom_right:
         add_arc(::rectd(rectCorner.bottom_right() - ::sized(dDiameter, dDiameter), ::sized(dDiameter, dDiameter)), 0_degree, 90_degree);
         return true;
      case e_border_bottom_left:
         add_arc(::rectd(rectCorner.bottom_left() - ::sized(0, dDiameter), ::sized(dDiameter, dDiameter)), 90_degree, 90_degree);
         return true;
      default:
         return false;
      }

   }


   bool path::counter_corner(const ::rectd& rectCorner, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case e_border_top_left:
         add_arc(::rectd(rectCorner.top_left(), ::sized(dDiameter, dDiameter)), 270_degree, -90_degree);
         return true;
      case e_border_top_right:
         add_arc(::rectd(rectCorner.top_right() - ::sized(dDiameter, 0), ::sized(dDiameter, dDiameter)), 0_degree, -90_degree);
         return true;
      case e_border_bottom_right:
         add_arc(::rectd(rectCorner.bottom_right() - ::sized(dDiameter, dDiameter), ::sized(dDiameter, dDiameter)), 90_degree, -90_degree);
         return true;
      case e_border_bottom_left:
         add_arc(::rectd(rectCorner.bottom_left() - ::sized(0, dDiameter), ::sized(dDiameter, dDiameter)), 180_degree, -90_degree);
         return true;
      default:
         return false;
      }

   }


   //bool path::add_round_rect(const ::rect & rect, i32 iRadius, const ::e_border & eborder)
   //{

   //   int iDiameter = iRadius * 2;

   //   // diameter can't exceed width or height
   //   if (iDiameter > rect.width())	iDiameter = (i32)rect.width();
   //   if (iDiameter > rect.height())	iDiameter = (i32)rect.height();

   //   ::rect rectRect(rect);

   //   rectRect.deflate(0, 0, 1, 1);

   //   ::size size(iDiameter, iDiameter);

   //   ::rect rectCorner(rectRect);

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

   bool path::add_round_rect(const ::rectd& rect, double dRadius, const ::e_border & eborder)
   {

      double dDiameter = dRadius * 2.0;

      // diameter can't exceed width or height
      if (dDiameter > rect.width())	dDiameter = (double)rect.width();
      if (dDiameter > rect.height()) dDiameter = (double)rect.height();

      ::rectd rectRect(rect);

      rectRect.deflate(0, 0, 1.0, 1.0);

      ::sized size(dDiameter, dDiameter);

      ::rectd rectCorner(rectRect);

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


   bool path::add_round_top_left(const ::rectd & rectParam, double iDiameter, const ::e_border & eborder)
   {

      ::rect rect(rectParam);

      // diameter can't exceed width or height
      if (iDiameter > rect.width())	iDiameter = rect.width();
      if (iDiameter > rect.height())	iDiameter = rect.height();

      // define a corner
      auto Corner = rectd_dim(rect.left, rect.top, iDiameter, iDiameter);

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
      //   //rect.height() -=1; //rect.height() -= 1;
      //}

      // top right
      Corner.left += (rect.width() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 270, 90);

      // bottom right
      Corner.top += (rect.height() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner,   0, 90);

      // bottom left
      Corner.left -= (rect.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 135, 45);

      add_line(rect.left, rect.top + rect.height() - iDiameter / 2, rect.left, rect.top + iDiameter / 2);


      Corner.top -= (rect.height() - iDiameter - 1);
      Corner.bottom = Corner.top + iDiameter2;
      add_arc(Corner, 180, 90);

      add_line(rect.left + iDiameter / 2, rect.top, rect.left + rect.width() - iDiameter / 2, rect.top);

      Corner.left += (rect.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 270, 45);


      // end path
      //path.m_ppath->CloseFigure();

      return true;

   }



   bool path::add_round_bottom_right(const ::rectd & rect, double iDiameter, const ::e_border & eborder)
   {
      // diameter can't exceed width or height
      if (iDiameter > rect.width())	iDiameter = rect.width();
      if (iDiameter > rect.height())	iDiameter = rect.height();

      // define a corner
      auto Corner = rectd_dim(rect.left, rect.top, iDiameter, iDiameter);

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
      //   //rect.height() -=1; //rect.height() -= 1;
      //}

      // top right
      Corner.left += (rect.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 315, 45);

      add_line(rect.left + rect.width(), rect.top + iDiameter / 2, rect.left + rect.width(), rect.top + rect.height() - iDiameter / 2);

      // bottom right
      Corner.top += (rect.height() - iDiameter - 1);
      Corner.bottom = Corner.top + iDiameter2;
      add_arc(Corner, 0_degrees, 90_degrees);

      add_line(rect.left + iDiameter / 2, rect.top + rect.height(), rect.left + rect.width() - iDiameter / 2, rect.top + rect.height());

      // bottom left
      Corner.left -= (rect.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 90_degrees, 45_degrees);




      //Corner.Y -= (rect.height() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 180, 90);



      //Corner.X += (rect.width() - iDiameter - 1);
      //path.m_ppath->AddArc(Corner, 275, 45);


      // end path
      //path.m_ppath->CloseFigure();

      return true;

   }

   bool path::contains(::draw2d::graphics_pointer & pgraphics, const pointd& point)
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


   bool path::add_arc_label(const ::rectd & rectParam)
   {

      ::rectd rect;
      ::rectd r2;

      {

         rect.left = rectParam.left;

         rect.top = rectParam.top;

         rect.right = rectParam.left + rectParam.height();

         rect.bottom = rectParam.bottom;

         add_arc(rect,90_degree,180_degree);

      }

      {

         r2.left = rect.left + rect.height() / 2.0;

         r2.top = rect.top;

         r2.right = rect.right - rect.height() / 2.0;

         r2.bottom = rect.bottom;

         add_line(r2.right, r2.top);

      }

      {

         rect.right = rectParam.right;

         rect.top = rectParam.top;

         rect.left = rectParam.right - rectParam.height();

         rect.bottom = rectParam.bottom;

         add_arc(rect,-90_degree,180_degree);

      }

      {

         add_line(r2.left,r2.bottom);

      }

      return true;

   }


} // namespace draw2d






