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


   bool path::element::expand_bounding_rect(RECTD* prect) const
   {

      rectd r;

      if (!get_bounding_rect(&r))
      {

         return false;

      }

      expand_rect(prect, r);

      return true;

   }


   bool path::element::expand_bounding_rect(RECT* prect) const
   {

      rectd r;

      if (!expand_bounding_rect(&r))
      {

         return false;

      }

      expand_rect(prect, r);

      return true;

   }


   bool path::element::get_bounding_rect(RECTD* prect) const
   {

      ::null_rect(prect);

      return false;

   }


   bool path::element::get_bounding_rect(RECT* prect) const
   {

      ::null_rect(prect);

      return false;

   }


   bool path::element::contains(const ::pointd& point) const
   {

      // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

      ::rectd r;

      if (!get_bounding_rect(r))
      {

         return false;

      }

      return r.contains(point);

   }


   bool path::arc::get_bounding_rect(RECTD* prectd) const
   {

      // BUG SS (STILL SIMPLE) m_dRotationAngle ignored

      prectd->left = m_pointCenter.x - m_sizeRadius.cx;
      prectd->right = m_pointCenter.x + m_sizeRadius.cx;
      prectd->top = m_pointCenter.y - m_sizeRadius.cy;
      prectd->bottom = m_pointCenter.y + m_sizeRadius.cy;

      return true;

   }



   bool path::arc::contains(const ::pointd & point) const
   {

      // BUG SS (STILL SIMPLE) using bounding box HAHA LOL ROFL

      return path::element::contains(point);

   }


   bool path::rect::get_bounding_rect(RECTD* prect) const
   {

      __copy(prect, m_rect);

      return true;

   }


   bool path::rect::contains(const ::pointd& point) const
   {

      return m_rect.contains(point);

   }


   bool path::lines::get_bounding_rect(RECTD* prect) const
   {

      m_pointa.get_bounding_rect(prect);

      return true;

   }


   bool path::lines::contains(const ::pointd& point) const
   {

      return m_pointa.polygon_contains(point);

   }



   bool path::polygon::get_bounding_rect(RECTD* prect) const
   {

      m_pointa.get_bounding_rect(prect);

      return true;

   }


   bool path::polygon::contains(const ::pointd& point) const
   {

      return m_pointa.polygon_contains(point);

   }


   bool path::line::get_bounding_rect(RECTD* prect) const
   {

      prect->left = MIN(m_pointBeg.x, m_pointEnd.x);
      prect->right = MAX(m_pointBeg.x, m_pointEnd.x);
      prect->top = MIN(m_pointBeg.y, m_pointEnd.y);
      prect->bottom = MAX(m_pointBeg.y, m_pointEnd.y);

      return true;

   }

   //bool path::line::contains(const ::pointd& point) const
   //{

   //   return false;

   //}


   bool path::text_out::get_bounding_rect(RECTD* prect) const
   {

      //__copy(prect, m_rect);

      return true;

   }


   bool path::text_out::contains(const ::pointd& point) const
   {

      return path::element::contains(point);

   }


   bool path::draw_text::get_bounding_rect(RECTD* prect) const
   {

      __copy(prect, m_rect);

      return true;

   }



   bool path::draw_text::contains(const ::pointd& point) const
   {

      return path::element::contains(point);

   }


   //path::text::text()
   //{

   //}


   //path::text::text(const text& text)
   //{

   //   operator = (text);

   //}


   //path::text::~text()
   //{

   //}


   //path::text& path::text::operator = (const text& text)
   //{

   //   if (this == &text)
   //   {

   //      return *this;

   //   }

   //   m_point        = text.m_point;
   //   m_rect         = text.m_rect;
   //   m_strText      = text.m_strText;
   //   m_pfont        = text.m_pfont;

   //   return *this;

   //}


   path::element::element()
   {

      m_etype = type_none;

   }


   path::element::~element()
   {


   }


   path::path()
   {

      //m_bFill        = false;
      m_efillmode    = ::draw2d::fill_mode_winding;
      m_bHasPoint    = false;

   }


   path::~path()
   {

   }


   void path::set_fill_mode(::draw2d::e_fill_mode efillmode)
   {

      m_efillmode = efillmode;

   }


   ::draw2d::e_fill_mode path::get_fill_mode()
   {

      return m_efillmode;

   }



   bool path::get_bounding_rect(RECTD* prect) const
   {

      rectd r;

      bool bGotAny = false;

      for(auto & pelement : m_elementa)
      {

         if (pelement->expand_bounding_rect(r))
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


   bool path::get_bounding_rect(RECT* prect) const
   {

      ::rect r;

      bool bGotAny = false;

      for (auto& pelement : m_elementa)
      {

         if (pelement->expand_bounding_rect(r))
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

   //   m_elementa.add(prect);

   //   return true;

   //}


   bool path::add_rect(const ::rectd& rectParam)
   {

      auto prect = __new(rect);

      __copy(prect->m_rect, rectParam);

      m_elementa.add(prect);

      return true;

   }


   //bool path::add_rect(const ::rect& rect, const ::point & point, const ::angle& angleRotationCenter)
   //{

   //   auto ppolygon = __new(polygon);

   //   ppolygon->m_pointa.set_size(4);

   //   ppolygon->m_pointa[0].x = rect.left;
   //   ppolygon->m_pointa[0].y = rect.top;

   //   ppolygon->m_pointa[1].x = rect.right;
   //   ppolygon->m_pointa[1].y = rect.top;

   //   ppolygon->m_pointa[2].x = rect.right;
   //   ppolygon->m_pointa[2].y = rect.bottom;

   //   ppolygon->m_pointa[3].x = rect.left;
   //   ppolygon->m_pointa[3].y = rect.bottom;

   //   ppolygon->m_pointa.rotate(angleRotationCenter, point);

   //   m_elementa.add(ppolygon);

   //   return true;

   //}


   bool path::add_rect(const ::rectd& rect, const ::pointd& point, const ::angle& angleRotationCenter)
   {

      auto ppolygon = __new(polygon);

      ppolygon->m_pointa.set_size(4);

      ppolygon->m_pointa[0].x = rect.left;
      ppolygon->m_pointa[0].y = rect.top;

      ppolygon->m_pointa[1].x = rect.right;
      ppolygon->m_pointa[1].y = rect.top;

      ppolygon->m_pointa[2].x = rect.right;
      ppolygon->m_pointa[2].y = rect.bottom;

      ppolygon->m_pointa[3].x = rect.left;
      ppolygon->m_pointa[3].y = rect.bottom;

      ppolygon->m_pointa.rotate(angleRotationCenter, point);

      m_elementa.add(ppolygon);

      return true;

   }


   //bool path::add_arc(const ::rect & rect, const ::angle & angleBeg, const ::angle& angleSweep)
   //{

   //   if (rect.width() <= 0 || rect.height() <= 0)
   //   {

   //      return true;

   //   }

   //   auto parc = __new(arc);

   //   auto& arc = *parc;

   //   arc.m_pointCenter.x  = ((double) rect.right + (double) rect.left) / 2.0;
   //   arc.m_pointCenter.y  = ((double) rect.bottom + (double) rect.top) / 2.0;
   //   arc.m_sizeRadius.cx  = (double) rect.right - parc->m_pointCenter.x;
   //   arc.m_sizeRadius.cy  = (double) rect.bottom - parc->m_pointCenter.y;
   //   arc.m_angleBeg       = angleBeg;
   //   arc.m_angleEnd       = angleBeg + angleSweep;
   //   arc.m_angleRotation  = 0.0;
   //   arc.m_pointBeg       = parc->m_pointCenter + arc_point(parc->m_angleBeg, parc->m_sizeRadius);
   //   arc.m_pointEnd       = parc->m_pointCenter + arc_point(parc->m_angleEnd, parc->m_sizeRadius);


   //   m_elementa.add(parc);

   //   m_bHasPoint = true;

   //   m_pointBeg = parc->m_pointBeg;

   //   m_pointEnd = parc->m_pointEnd;

   //   set_modified();

   //   return true;

   //}



   bool path::varc(const ::pointd & point, double h, const ::angle& angle)
   {

      if (fabs(angle) <= 0.00001 || fabs(h) <= 0.001)
      {
         return false;
      }

      auto parc = __new(arc);

      ::angle t = 90_degrees - angle;
      double x = point.x;
      double y = point.y;
      parc->m_pointCenter.y = point.y + h/2.0;
      double b = point.y - parc->m_pointCenter.y / sin(t);
      double a = sqrt((b*b*x*x) / (y*y - b *b));

      parc->m_sizeRadius.cx = a;
      parc->m_sizeRadius.cy = b;
      parc->m_pointCenter.x = point.x - a * cos(t);
      parc->m_angleBeg = t;
      parc->m_angleEnd = t - 90_degrees;
      parc->m_angleRotation = 0.0;
      ///parc->m_dAngle = (parc->m_angleEnd - parc->m_angleBeg) * g_dPi / 180.0;
      parc->m_pointBeg = parc->m_pointCenter + arc_point(parc->m_angleBeg, parc->m_sizeRadius);
      parc->m_pointEnd = parc->m_pointCenter + arc_point(parc->m_angleEnd, parc->m_sizeRadius);

      //parc->m_pointBeg.x = parc->m_pointCenter.x + parc->m_dRadiusX * cos(parc->m_angleBeg);
      //parc->m_pointBeg.y = parc->m_pointCenter.y +parc->m_dRadiusY * sin(parc->m_angleBeg);
      //parc->m_pointEnd.x = parc->m_pointCenter.x + parc->m_dRadiusX * cos(parc->m_angleEnd);
      //parc->m_pointEnd.y = parc->m_pointCenter.y + parc->m_dRadiusY * sin(parc->m_angleEnd);

      m_elementa.add(parc);

      m_bHasPoint = true;

      m_pointBeg = parc->m_pointBeg;

      m_pointEnd = parc->m_pointEnd;

      set_modified();

      return true;

   }


   bool path::harc(const ::pointd & point, double w, const ::angle& angle)
   {


      if (fabs(angle) <= 0.00001 || fabs(w) <= 0.001)
      {

         return false;

      }

      auto parc = __new(arc);

      ::angle t = angle + 90_degrees;
      parc->m_pointBeg.x = point.x + w / 2.0;
      double a = (point.x - parc->m_pointBeg.x) / cos(t);
      double x = point.x - parc->m_pointBeg.x;
      double b = 0;
      //double y = b * b  *w / (4.0* tan(dAngle));
      double y = 0;
      b = sqrt((a*a*y*y) / (a*a-x *x));

      parc->m_sizeRadius.cx = a;
      parc->m_sizeRadius.cy = b;
      parc->m_pointCenter.y = point.y - b * sin(t);
      parc->m_angleBeg = t;
      parc->m_angleEnd = fmod(180_degrees - parc->m_angleBeg, 360_degrees);
      parc->m_angleRotation = parc->m_angleEnd - parc->m_angleBeg;

      parc->m_pointBeg = parc->m_pointCenter + arc_point(parc->m_angleBeg, parc->m_sizeRadius);
      parc->m_pointEnd = parc->m_pointCenter + arc_point(parc->m_angleEnd, parc->m_sizeRadius);

      m_elementa.add(parc);

      m_bHasPoint = true;

      m_pointBeg = parc->m_pointBeg;

      m_pointEnd = parc->m_pointEnd;

      set_modified();

      return true;

   }


   bool path::add_arc(const ::rectd & rect, const ::angle & angleBeg, const ::angle& angleSweep)
   {

      if (rect.width() <= 0 || rect.height() <= 0)
      {

         return true;

      }

      auto parc = __new(arc);

      parc->m_pointCenter.x   = (rect.right + rect.left) / 2.0;
      parc->m_pointCenter.y   = (rect.bottom + rect.top) / 2.0;
      parc->m_sizeRadius.cx   = fabs(rect.right - rect.left) / 2.0;
      parc->m_sizeRadius.cy   = fabs(rect.bottom - rect.top) / 2.0;
      parc->m_angleBeg        = angleBeg;
      parc->m_angleEnd        = angleBeg + angleSweep;
      parc->m_angleRotation   = 0_degrees;
      parc->m_pointBeg        = parc->m_pointCenter + arc_point(parc->m_angleBeg, parc->m_sizeRadius);
      parc->m_pointEnd        = parc->m_pointCenter + arc_point(parc->m_angleEnd, parc->m_sizeRadius);

      m_elementa.add(parc);

      m_bHasPoint = true;

      m_pointBeg = parc->m_pointBeg;

      m_pointEnd = parc->m_pointEnd;

      set_modified();

      return true;

   }


   //bool path::add_move(double x, double y)
   //{

   //   __pointer(element) pelement;

   //   pelement = __new(element);

   //   pelement->m_etype               = element::type_move;
   //   pelement->u.m_move.m_x          = x;
   //   pelement->u.m_move.m_y          = y;

   //   m_elementa.add(pelement);

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

   //   m_elementa.add(pline);

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

      auto pbegin = __new(begin);

      m_elementa.add(pbegin);

      m_bHasPoint = false;

      set_modified();

      return true;

   }


   bool path::close_figure()
   {

      auto pend = __new(close);

      m_elementa.add(pend);

      set_modified();

      return true;

   }


   bool path::add_text_out(const ::pointd & point, const string & strText,::draw2d::font_pointer pfont)
   {

      auto ptextout = __new(text_out);

      ptextout->m_strText     = strText;
      ptextout->m_pfont       = pfont;
      ptextout->m_point       = point;

      m_elementa.add(ptextout);

      return true;

   }


   bool path::add_draw_text(const string & strText, const ::rectd & rect, int iDrawTextFlags, ::draw2d::font_pointer pfont)
   {

      auto pdrawtext = __new(draw_text);

      pdrawtext->m_strText          = strText;
      pdrawtext->m_pfont            = pfont;

      pdrawtext->m_rect             = rect;
      pdrawtext->m_iDrawTextFlags   = iDrawTextFlags;
      //pdrawtext->m_crForeground     = crForeground;

      m_elementa.add(pdrawtext);

      return true;

   }


   bool path::add_line(const pointd & pointBeg, const pointd & pointEnd)
   {

      auto pline = __new(line);

      pline->m_pointBeg = pointBeg;

      pline->m_pointEnd = pointEnd;

      m_elementa.add(pline);

      m_pointBeg = pline->m_pointBeg;

      m_pointEnd = pline->m_pointEnd;

      return true;

   }


   bool path::add_line(const pointd & point)
   {

      auto pline = __new(line);

      pline->m_pointBeg = m_pointEnd;

      pline->m_pointEnd = point;

      m_elementa.add(pline);

      m_pointBeg = pline->m_pointBeg;

      m_pointEnd = pline->m_pointEnd;

      return true;

   }


   bool path::add_polygon(const POINT* ppoint, ::count nCount)
   {

      auto ppolygon = __new(polygon);

      for (i32 i = 0; i < nCount; i++)
      {

         ppolygon->m_pointa.add(pointd(ppoint[i].x, ppoint[i].y));

      }

      m_elementa.add(ppolygon);

      return true;

   }


   bool path::add_polygon(const POINTD* ppoint, ::count nCount)
   {

      auto plines = __new(lines);

      plines->m_pointa.set_size(nCount);

      memcpy(plines->m_pointa.get_data(), ppoint, plines->m_pointa.get_size_in_bytes());

      m_elementa.add(plines);

      return true;

   }



   bool path::add_lines(const POINT * ppoint, ::count nCount)
   {

      auto plines = __new(lines);

      for (i32 i = 0; i < nCount; i++)
      {

         plines->m_pointa.add(pointd(ppoint[i].x, ppoint[i].y));

      }

      m_elementa.add(plines);

      return true;

   }


   bool path::add_lines(const POINTD * ppoint, ::count nCount)
   {

      auto plines = __new(lines);

      plines->m_pointa.set_size(nCount);

      memcpy(plines->m_pointa.get_data(), ppoint, plines->m_pointa.get_size_in_bytes());

      m_elementa.add(plines);

      return true;

   }


   void * path::detach()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


//   void path::get_bounding_rect(RECT * prect)
//
//   {
//
//      prect->right     = 0x80000000;
//
//      prect->left      = 0x7fffffff;
//
//      prect->bottom    = 0x80000000;
//
//      prect->top       = 0x7fffffff;
//
//
//
//      for(int i = 0; i < m_elementa.get_count(); i++)
//      {
//
//         get_bounding_rect(prect, m_elementa(i));
//
//
//      }
//
//   }
//
//   void path::get_bounding_rect(RECT * prect, element & element)
//
//   {
//
//      switch(element.m_etype)
//      {
//      case ::draw2d::path::element::type_arc:
//         get_bounding_rect(prect, element.u.m_arc);
//
//         break;
//      case ::draw2d::path::element::type_line:
//         get_bounding_rect(prect, element.u.m_line);
//
//         break;
//      case ::draw2d::path::element::type_move:
//         get_bounding_rect(prect, element.u.m_move);
//
//         break;
//      case ::draw2d::path::element::type_rect:
//         get_bounding_rect(prect,element.u.m_rect);
//
//         break;
//      case ::draw2d::path::element::type_string:
//         get_bounding_rect(prect,element.m_stringpath);
//
//         break;
//      case ::draw2d::path::element::type_end:
//      {
//
//      }
//      break;
//      default:
//         __throw(::exception::exception("unexpected simple os graphics element type"));
//      }
//
//
//
//
//   }
//
//   void path::get_bounding_rect(RECT * prect,rect & rect)
//
//   {
//
//      prect->left = (LONG) rect.m_x;
//
//      prect->top = (LONG)rect.m_y;
//
//      prect->right= (LONG)(rect.m_x + rect.m_cx);
//
//      prect->bottom = (LONG)(rect.m_y + rect.m_cy);
//
//
//   }
//
//   void path::get_bounding_rect(RECT * prect, arc & a)
//
//   {
//
//      ::rect rect;
//
//      rect.left         = (LONG) (a.m_pointCenter.x - a.m_sizeRadius.cx);
//
//      rect.right        = (LONG) (a.m_pointCenter.x + a.m_sizeRadius.cx);
//
//      rect.top          = (LONG) (a.m_pointCenter.y - a.m_sizeRadius.cy);
//
//      rect.bottom       = (LONG) (a.m_pointCenter.y + a.m_sizeRadius.cy);
//
//      ::point point1;
//
//      ::point point2;
//
//      prect->left   = (LONG) MIN(a.m_pointCenter.x, prect->left);
//
//      prect->top    = (LONG) MIN(a.m_pointCenter.y, prect->top);
//
//      prect->right  = (LONG) MAX(a.m_pointCenter.x, prect->right);
//
//      prect->bottom = (LONG) MAX(a.m_pointCenter.y, prect->bottom);
//
//
////      double pelement = a.m_dRadiusY / a.m_dRadiusX;
//
//      double f1 = a.m_angleBeg;
//
//      double f2 = a.m_angleEnd;
//
//      point1.x          = (LONG) (a.m_pointCenter.x + a.m_sizeRadius.cx * cos(f1));
//
//      point1.y          = (LONG) (a.m_pointCenter.y - a.m_sizeRadius.cy * sin(f1));
//
//      point2.x          = (LONG) (a.m_pointCenter.x + a.m_sizeRadius.cx * cos(f2));
//
//      point2.y          = (LONG) (a.m_pointCenter.y - a.m_sizeRadius.cy * sin(f2));
//
//      prect->left   = (LONG) MIN(point1.x, prect->left);
//
//
//      prect->top    = (LONG) MIN(point1.y, prect->top);
//
//
//      prect->right  = (LONG) MAX(point1.x, prect->right);
//
//
//      prect->bottom = (LONG) MAX(point1.y, prect->bottom);
//
//
//      prect->left   = (LONG) MIN(point2.x, prect->left);
//
//
//      prect->top    = (LONG) MIN(point2.y, prect->top);
//
//
//      prect->right  = (LONG) MAX(point2.x, prect->right);
//
//
//      prect->bottom = (LONG) MAX(point2.y, prect->bottom);
//
//
//      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
//      {
//
//         prect->left   = (LONG) MIN(rect.right, prect->left);
//
//
//         prect->right  = (LONG) MAX(rect.right, prect->right);
//
//
//      }
//
//      f1 -= System.math().GetPi() / 2.0;
//
//      f2 -= System.math().GetPi() / 2.0;
//
//      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
//      {
//
//         prect->top    = (LONG) MIN(rect.top, prect->top);
//
//
//         prect->bottom = (LONG) MAX(rect.top, prect->bottom);
//
//
//      }
//
//      f1 -= System.math().GetPi() / 2.0;
//
//      f2 -= System.math().GetPi() / 2.0;
//
//      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
//      {
//
//         prect->left   = (LONG) MIN(rect.left, prect->left);
//
//
//         prect->right  = (LONG) MAX(rect.left, prect->right);
//
//
//      }
//
//      f1 -= System.math().GetPi() / 2.0;
//
//      f2 -= System.math().GetPi() / 2.0;
//
//      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
//      {
//
//         prect->top    = (LONG) MIN(rect.bottom, prect->top);
//
//
//         prect->bottom = (LONG) MAX(rect.bottom, prect->bottom);
//
//
//      }
//
//   }
//
   //void path::get_bounding_rect(RECT * prect, move & m)

   //{

   //   prect->left   = (LONG) MIN(m.m_x, prect->left);


   //   prect->top    = (LONG) MIN(m.m_y, prect->top);


   //   prect->right  = (LONG) MAX(m.m_x, prect->right);


   //   prect->bottom = (LONG) MAX(m.m_y, prect->bottom);


   //}


   //void path::get_bounding_rect(RECT * prect, line & l)

   //{

   //   prect->left   = (LONG) MIN(l.m_x, prect->left);


   //   prect->top    = (LONG) MIN(l.m_y, prect->top);


   //   prect->right  = (LONG) MAX(l.m_x, prect->right);


   //   prect->bottom = (LONG) MAX(l.m_y, prect->bottom);


   //}

   //void path::get_bounding_rect(RECT * prect,string_path & point)

   //{


   //}



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
   bool path::do_round_rect_corner(const ::rect& rectCorner, const ::rect& rectRect, i32 iDiameter, eborder eborder, int iCorner, bool& bOn)
   {

      switch (iCorner % 4)
      {
      case 0:
      {
         if ((eborder & border_top_left))
         {

            if ((eborder & border_top_left) == border_top_left)
            {

               add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 180_degrees, 90_degrees);

               bOn = true;

            }
            else if(bOn)
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
         if ((eborder & border_top_right))
         {

            if ((eborder & border_top_right) == border_top_right)
            {

               add_arc(::rect(rectCorner.top_right(), ::size(iDiameter, iDiameter)), 270_degrees, 90_degrees);

               bOn = true;

            }
            else if(bOn)
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

         if ((eborder & border_bottom_right))
         {

            if ((eborder & border_bottom_right) == border_bottom_right)
            {

               add_arc(::rect(rectCorner.bottom_right(), ::size(iDiameter, iDiameter)), 0_degrees, 90_degrees);

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
         if ((eborder & border_bottom_left))
         {

            if ((eborder & border_bottom_left) == border_bottom_left)
            {

               add_arc(::rect(rectCorner.bottom_left(), ::size(iDiameter, iDiameter)), 90_degrees, 90_degrees);

               bOn = true;

            }
            else if(bOn)
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


   bool path::do_round_rect_corner(const ::rectd& rectCorner, const ::rectd& rectRect, double dDiameter, eborder eborder, int iCorner, bool& bOn)
   {

      switch (iCorner % 4)
      {
      case 0:
      {
         if ((eborder & border_top_left))
         {

            if ((eborder & border_top_left) == border_top_left)
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
         if ((eborder & border_top_right))
         {

            if ((eborder & border_top_right) == border_top_right)
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

         if ((eborder & border_bottom_right))
         {

            if ((eborder & border_bottom_right) == border_bottom_right)
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
         if ((eborder & border_bottom_left))
         {

            if ((eborder & border_bottom_left) == border_bottom_left)
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


   bool path::clock_corner(const ::rect& rectCorner, i32 iRadius, eborder eborder)
   {

      int iDiameter = iRadius * 2;

      if (iDiameter == 0)
      {

         iDiameter = 1;

      }

      switch (eborder)
      {
      case border_top_left:
         add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 180_degree, 90_degree);
         return true;
      case border_top_right:
         add_arc(::rect(rectCorner.top_right() - ::size(iDiameter, 0), ::size(iDiameter, iDiameter)), 270_degree, 90_degree);
         return true;
      case border_bottom_right:
         add_arc(::rect(rectCorner.bottom_right() - ::size(iDiameter, iDiameter), ::size(iDiameter, iDiameter)), 0_degree, 90_degree);
         return true;
      case border_bottom_left:
         add_arc(::rect(rectCorner.bottom_left() - ::size(0, iDiameter), ::size(iDiameter, iDiameter)), 90_degree, 90_degree);
         return true;
      default:
         return false;
      }

   }


   bool path::counter_corner(const ::rect& rectCorner, i32 iRadius, eborder eborder)
   {

      int iDiameter = iRadius * 2;

      if (iDiameter == 0)
      {

         iDiameter = 1;

      }

      switch (eborder)
      {
      case border_top_left:
         add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 270_degree, -90_degree);
         return true;
      case border_top_right:
         add_arc(::rect(rectCorner.top_right() - ::size(iDiameter, 0), ::size(iDiameter, iDiameter)), 0_degree, -90_degree);
         return true;
      case border_bottom_right:
         add_arc(::rect(rectCorner.bottom_right() - ::size(iDiameter, iDiameter), ::size(iDiameter, iDiameter)), 90_degree, -90_degree);
         return true;
      case border_bottom_left:
         add_arc(::rect(rectCorner.bottom_left() - ::size(0, iDiameter), ::size(iDiameter, iDiameter)), 180_degree, -90_degree);
         return true;
      default:
         return false;
      }

   }


   bool path::_set_create(::draw2d::graphics* pgraphics)
   {

      for (auto& pelement : m_elementa)
      {

         if (!_set(pgraphics, pelement))
         {

            return false;

         }

      }

      return true;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::element * pelement)
   {

      switch (pelement->m_etype)
      {
      case ::draw2d::path::type_begin:
         return _set(pgraphics, dynamic_cast <begin*>(pelement));
      case ::draw2d::path::type_arc:
         return _set(pgraphics, dynamic_cast <arc*>(pelement));
      case ::draw2d::path::type_rect:
         return _set(pgraphics, dynamic_cast <rect*>(pelement));
      case ::draw2d::path::type_line:
         return  _set(pgraphics, dynamic_cast <line*>(pelement));
      case ::draw2d::path::type_lines:
         return _set(pgraphics, dynamic_cast <lines*>(pelement));
      case ::draw2d::path::type_polygon:
         return _set(pgraphics, dynamic_cast <polygon*>(pelement));
      case ::draw2d::path::type_text_out:
         return _set(pgraphics, dynamic_cast <text_out*>(pelement));
      case ::draw2d::path::type_draw_text:
         return _set(pgraphics, dynamic_cast <draw_text*>(pelement));
      case ::draw2d::path::type_close:
         return _set(pgraphics, dynamic_cast <close*>(pelement));

      default:
         throw "unexpected simple os graphics element type";
      }

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::begin* pbegin)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::arc* parc)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::rect* prect)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::line* pline)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::lines* plines)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::polygon* pline)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::text_out* ptextout)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::draw_text* pdrawtext)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::_set(::draw2d::graphics* pgraphics, ::draw2d::path::close* pclose)
   {

      __throw(interface_only_exception);

      return false;

   }


   bool path::clock_corner(const ::rectd& rectCorner, double dRadius, eborder eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case border_top_left:
         add_arc(::rectd(rectCorner.top_left(), ::sized(dDiameter, dDiameter)), 180_degree, 90_degree);
         return true;
      case border_top_right:
         add_arc(::rectd(rectCorner.top_right() - ::sized(dDiameter, 0), ::sized(dDiameter, dDiameter)), 270_degree, 90_degree);
         return true;
      case border_bottom_right:
         add_arc(::rectd(rectCorner.bottom_right() - ::sized(dDiameter, dDiameter), ::sized(dDiameter, dDiameter)), 0_degree, 90_degree);
         return true;
      case border_bottom_left:
         add_arc(::rectd(rectCorner.bottom_left() - ::sized(0, dDiameter), ::sized(dDiameter, dDiameter)), 90_degree, 90_degree);
         return true;
      default:
         return false;
      }

   }


   bool path::counter_corner(const ::rectd& rectCorner, double dRadius, eborder eborder)
   {

      double dDiameter = dRadius * 2.0;

      switch (eborder)
      {
      case border_top_left:
         add_arc(::rectd(rectCorner.top_left(), ::sized(dDiameter, dDiameter)), 270_degree, -90_degree);
         return true;
      case border_top_right:
         add_arc(::rectd(rectCorner.top_right() - ::sized(dDiameter, 0), ::sized(dDiameter, dDiameter)), 0_degree, -90_degree);
         return true;
      case border_bottom_right:
         add_arc(::rectd(rectCorner.bottom_right() - ::sized(dDiameter, dDiameter), ::sized(dDiameter, dDiameter)), 90_degree, -90_degree);
         return true;
      case border_bottom_left:
         add_arc(::rectd(rectCorner.bottom_left() - ::sized(0, dDiameter), ::sized(dDiameter, dDiameter)), 180_degree, -90_degree);
         return true;
      default:
         return false;
      }

   }


   bool path::add_round_rect(const ::rect & rect, i32 iRadius, eborder eborder)
   {

      int iDiameter = iRadius * 2;

      // diameter can't exceed width or height
      if (iDiameter > rect.width())	iDiameter = (i32)rect.width();
      if (iDiameter > rect.height())	iDiameter = (i32)rect.height();

      ::rect rectRect(rect);

      rectRect.deflate(0, 0, 1, 1);

      ::size size(iDiameter, iDiameter);

      ::rect rectCorner(rectRect);

      rectCorner.deflate(0, 0, iDiameter, iDiameter);

      bool bOn = false;

      int iCount = 0;

      if (eborder & border_all)
      {

         //begin_figure(true, ::draw2d::fill_mode_winding);

         //begin_figure();

         int iEmptyBorder;

         if (!(eborder & border_right))
         {

            iEmptyBorder = 1;

         }
         else if(!(eborder & border_bottom))
         {

            iEmptyBorder = 2;

         }
         else if(!(eborder & border_left))
         {

            iEmptyBorder = 3;

         }
         else
         {

            iEmptyBorder = 0;

         }

         for(int iShift = 0; iShift < 4; iShift++)
         {

            int iCorner = iEmptyBorder + iShift + 1;

            do_round_rect_corner(rectCorner, rectRect, iDiameter, eborder, iCorner, bOn);

         }

         //end_figure(bOn);

         close_figure();

         return true;

      }


      return false;

   }

   bool path::add_round_rect(const ::rectd& rect, double dRadius, eborder eborder)
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

      if (eborder & border_all)
      {

         //begin_figure(true, ::draw2d::fill_mode_winding);

         begin_figure();

         int iEmptyBorder;

         if (!(eborder & border_right))
         {

            iEmptyBorder = 1;

         }
         else if (!(eborder & border_bottom))
         {

            iEmptyBorder = 2;

         }
         else if (!(eborder & border_left))
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


   bool path::add_round_top_left(const ::rect & rectParam, i32 iDiameter, eborder eborder)
   {

      ::rect rect(rectParam);

      // diameter can't exceed width or height
      if (iDiameter > rect.width())	iDiameter = rect.width();
      if (iDiameter > rect.height())	iDiameter = rect.height();

      // define a corner
      ::rect Corner(rect_dim(rect.left, rect.top, iDiameter, iDiameter));

      // begin path
      //path.m_ppath->Reset();


      // top left
      //   path.m_ppath->AddArc(Corner, 180, 90);

      // tweak needed for radius of 10 (iDiameter of 20)
      i32 iDiameter2 = iDiameter;
      if (iDiameter % 2 == 0)
      {
         iDiameter2++;
         //Corner.Height += 1;
         //rect.height() -=1; //rect.height() -= 1;
      }

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



   bool path::add_round_bottom_right(const ::rect & rect, i32 iDiameter, eborder eborder)
   {
      // diameter can't exceed width or height
      if (iDiameter > rect.width())	iDiameter = rect.width();
      if (iDiameter > rect.height())	iDiameter = rect.height();

      // define a corner
      ::rect Corner(rect_dim(rect.left, rect.top, iDiameter, iDiameter));

      // begin path
      //path.m_ppath->Reset();


      // top left
      //   path.m_ppath->AddArc(Corner, 180, 90);

      // tweak needed for radius of 10 (iDiameter of 20)
      i32 iDiameter2 = iDiameter;
      if (iDiameter % 2 == 0)
      {
         iDiameter2++;
         //Corner.Height += 1;
         //rect.height() -=1; //rect.height() -= 1;
      }

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

      for (auto& pelement : m_elementa)
      {

         if (pelement->contains(point))
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


         add_arc(rect,90,180);

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


         add_arc(rect,-90,180);

      }

      {

         add_line(r2.left,r2.bottom);

      }

      return true;

   }


} // namespace draw2d






