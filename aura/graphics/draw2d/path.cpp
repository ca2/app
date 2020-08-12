#include "framework.h"


//#include "draw2d.h"
//#include <math.h>


static double g_dPi = atan(1.0) * 4.0;


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




   path::string_path::string_path()
   {
      m_x = 0;
      m_y = 0;
   }

   path::string_path::string_path(const string_path & stringpath)
   {

      operator = (stringpath);

   }

   path::string_path::~string_path()
   {
   }

   path::string_path & path::string_path::operator = (const string_path & stringpath)
   {

      if(this == &stringpath)
         return *this;

      m_x            = stringpath.m_x;
      m_y            = stringpath.m_y;
      m_strText      = stringpath.m_strText;
      m_pfont       = stringpath.m_pfont;

      return *this;

   }


   path::element::element()
   {

      m_etype = type_none;

   }

   path::element::element(const element & pelement)
   {

      operator = (pelement);

   }

   path::element::~element()
   {



   }

   path::element & path::element::operator = (const element & element)
   {

      if (this == &element)
      {

         return *this;

      }

      m_etype = element.m_etype;

      if(m_etype == type_string)
      {
         m_stringpath = element.m_stringpath;
      }
      else
      {
         u = element.u;
      }

      return *this;

   }


   path::path()
   {

      m_bFill        = false;
      m_efillmode    = ::draw2d::fill_mode_winding;
      m_bHasPoint    = false;

   }


   path::~path()
   {

   }


   bool path::has_current_point()
   {

      return m_bHasPoint;

   }

   pointd path::last_point()
   {

      if(!m_bHasPoint)
         __throw(::exception::exception("there is no point"));

      return m_point;

   }



   bool path::add_arc(const ::rect & rect, double dStart, double dAngle)
   {

      if (rect.width() <= 0 || rect.height() <= 0)
      {

         return true;

      }

      __pointer(element) pelement;

      pelement = __new(element);

      pelement->m_etype                   = element::type_arc;

      auto& arc = pelement->u.m_arc;
      arc.m_pointCenter.x   = ((double) rect.right + (double) rect.left) / 2.0;
      arc.m_pointCenter.y   = ((double) rect.bottom + (double) rect.top) / 2.0;
      arc.m_sizeRadius.cx   = (double) rect.right - pelement->u.m_arc.m_pointCenter.x;
      arc.m_sizeRadius.cy   = (double) rect.bottom - pelement->u.m_arc.m_pointCenter.y;
      arc.m_dAngle1         = dStart * g_dPi / 180.0;
      arc.m_dAngle          = dAngle * g_dPi / 180.0;
      arc.m_dAngle2         = pelement->u.m_arc.m_dAngle1 + pelement->u.m_arc.m_dAngle;
      arc.m_pointStart      = pointd(pelement->u.m_arc.m_pointCenter)+arc_point(pelement->u.m_arc.m_dAngle1, pelement->u.m_arc.m_sizeRadius);
      arc.m_pointEnd        = pointd(pelement->u.m_arc.m_pointCenter)+arc_point(pelement->u.m_arc.m_dAngle2, pelement->u.m_arc.m_sizeRadius);


      if(m_bHasPoint)
      {

         m_pointStart = pelement->u.m_arc.m_pointStart;


      }

      m_elementa.add(pelement);

      m_bHasPoint = true;
      m_point.x = (LONG)pelement->u.m_arc.m_pointEnd.x;
      m_point.y = (LONG)pelement->u.m_arc.m_pointEnd.y;

      set_modified();

      return true;

   }



   bool path::varc(const ::point & point, double h, double dAngle)
   {

      if (fabs(dAngle) <= 0.00001 || fabs(h) <= 0.001)
      {
         return false;
      }

      dAngle *= g_dPi / 180.0;

      __pointer(element) pelement;

      pelement = __new(element);
      double t = g_dPi / 2.0 - dAngle;
      double x = point.x;
      double y = point.y;
      pelement->u.m_arc.m_pointCenter.y = point.y + h/2.0;
      double b = point.y - pelement->u.m_arc.m_pointCenter.y / sin(t);
      double a = sqrt((b*b*x*x) / (y*y - b *b));

      pelement->u.m_arc.m_sizeRadius.cx = a;
      pelement->u.m_arc.m_sizeRadius.cy = b;
      pelement->m_etype = element::type_arc;
      pelement->u.m_arc.m_pointCenter.x = point.x - a * cos(t);
      pelement->u.m_arc.m_dAngle1 = t * g_dPi / 180.0;
      pelement->u.m_arc.m_dAngle2 = pelement->u.m_arc.m_dAngle1 / 2.0 - 90.0;
      pelement->u.m_arc.m_dAngle = (pelement->u.m_arc.m_dAngle2 - pelement->u.m_arc.m_dAngle1) * g_dPi / 180.0;
      pelement->u.m_arc.m_pointStart = pointd(pelement->u.m_arc.m_pointCenter) + arc_point(pelement->u.m_arc.m_dAngle1, pelement->u.m_arc.m_sizeRadius);
      pelement->u.m_arc.m_pointEnd = pointd(pelement->u.m_arc.m_pointCenter) + arc_point(pelement->u.m_arc.m_dAngle2, pelement->u.m_arc.m_sizeRadius);

      //pelement->u.m_arc.m_pointStart.x = pelement->u.m_arc.m_pointCenter.x + pelement->u.m_arc.m_dRadiusX * cos(pelement->u.m_arc.m_dAngle1);
      //pelement->u.m_arc.m_pointStart.y = pelement->u.m_arc.m_pointCenter.y +pelement->u.m_arc.m_dRadiusY * sin(pelement->u.m_arc.m_dAngle1);
      //pelement->u.m_arc.m_pointEnd.x = pelement->u.m_arc.m_pointCenter.x + pelement->u.m_arc.m_dRadiusX * cos(pelement->u.m_arc.m_dAngle2);
      //pelement->u.m_arc.m_pointEnd.y = pelement->u.m_arc.m_pointCenter.y + pelement->u.m_arc.m_dRadiusY * sin(pelement->u.m_arc.m_dAngle2);

      m_elementa.add(pelement);

      m_bHasPoint = true;
      m_point.x = (LONG)pelement->u.m_arc.m_pointEnd.x;
      m_point.y = (LONG)pelement->u.m_arc.m_pointEnd.y;

      set_modified();

      return true;

   }


   bool path::harc(const ::point & point, double w, double dAngle)
   {


      if (fabs(dAngle) <= 0.00001 || fabs(w) <= 0.001)
      {
         return false;
      }

      dAngle *= g_dPi / 180.0;

      __pointer(element) pelement;

      pelement = __new(element);
      double t = dAngle + g_dPi / 2.0;
      pelement->u.m_arc.m_pointStart.x = point.x + w / 2.0;
      double a = (point.x - pelement->u.m_arc.m_pointStart.x) / cos(t);
      double x = point.x - pelement->u.m_arc.m_pointStart.x;
      double b = 0;
      //double y = b * b  *w / (4.0* tan(dAngle));
      double y = 0;
      b = sqrt((a*a*y*y) / (a*a-x *x));

      pelement->u.m_arc.m_sizeRadius.cx = a;
      pelement->u.m_arc.m_sizeRadius.cy = b;
      pelement->m_etype = element::type_arc;
      pelement->u.m_arc.m_pointCenter.y = point.y - b * sin(t);
      pelement->u.m_arc.m_dAngle1 = t;
      pelement->u.m_arc.m_dAngle2 = fmod(g_dPi - pelement->u.m_arc.m_dAngle1, g_dPi);
      pelement->u.m_arc.m_dAngle = pelement->u.m_arc.m_dAngle2 - pelement->u.m_arc.m_dAngle1;

      pelement->u.m_arc.m_pointStart = pointd(pelement->u.m_arc.m_pointCenter) + arc_point(pelement->u.m_arc.m_dAngle1, pelement->u.m_arc.m_sizeRadius);
      pelement->u.m_arc.m_pointEnd = pointd(pelement->u.m_arc.m_pointCenter) + arc_point(pelement->u.m_arc.m_dAngle2, pelement->u.m_arc.m_sizeRadius);

      m_elementa.add(pelement);

      m_bHasPoint = true;
      m_point.x = (LONG)pelement->u.m_arc.m_pointEnd.x;
      m_point.y = (LONG)pelement->u.m_arc.m_pointEnd.y;

      set_modified();

      return true;

   }


   bool path::add_arc(const ::rectd & rect,double dStart,double dAngle)
   {

      if (rect.width() <= 0 || rect.height() <= 0)
      {

         return true;

      }

      __pointer(element) pelement;

      pelement = __new(element);

      pelement->m_etype               = element::type_arc;
      pelement->u.m_arc.m_pointCenter.x     = (rect.right + rect.left) / 2.0;
      pelement->u.m_arc.m_pointCenter.y     = (rect.bottom + rect.top) / 2.0;
      pelement->u.m_arc.m_sizeRadius.cx    = fabs(rect.right - rect.left) / 2.0;
      pelement->u.m_arc.m_sizeRadius.cy = fabs(rect.bottom - rect.top) / 2.0;
      pelement->u.m_arc.m_dAngle1     = dStart * g_dPi / 180.0;
      pelement->u.m_arc.m_dAngle      = dAngle * g_dPi / 180.0;
      pelement->u.m_arc.m_dAngle2     = pelement->u.m_arc.m_dAngle1 + pelement->u.m_arc.m_dAngle;
      pelement->u.m_arc.m_pointStart = pointd(pelement->u.m_arc.m_pointCenter) + arc_point(pelement->u.m_arc.m_dAngle1, pelement->u.m_arc.m_sizeRadius);
      pelement->u.m_arc.m_pointEnd = pointd(pelement->u.m_arc.m_pointCenter) + arc_point(pelement->u.m_arc.m_dAngle2, pelement->u.m_arc.m_sizeRadius);

      m_elementa.add(pelement);

      m_bHasPoint = true;
      m_point.x = pelement->u.m_arc.m_pointEnd.x;
      m_point.y = pelement->u.m_arc.m_pointEnd.y;

      set_modified();

      return true;

   }


   bool path::add_move(i32 x,i32 y)
   {

      return add_move((double)x,(double)y);

   }


   bool path::add_move(double x, double y)
   {

      __pointer(element) pelement;

      pelement = __new(element);

      pelement->m_etype               = element::type_move;
      pelement->u.m_move.m_x          = x;
      pelement->u.m_move.m_y          = y;

      m_elementa.add(pelement);

      m_bHasPoint = true;
      m_point.x = x;
      m_point.y = y;

      set_modified();

      return true;

   }


   bool path::add_line(double x,double y)
   {

      if(!has_current_point())
      {
         return add_move(x,y);
      }

      __pointer(element) pelement;

      pelement = __new(element);

      pelement->m_etype               = element::type_line;
      pelement->u.m_line.m_x          = x;
      pelement->u.m_line.m_y          = y;

      m_elementa.add(pelement);

      m_bHasPoint = true;
      m_point.x = x;
      m_point.y = y;

      set_modified();

      return true;

   }


   bool path::add_line(i32 x, i32 y)
   {

      return add_line((double)x,(double)y);

   }


   bool path::add_line(double x,double y,double x2,double y2)
   {

      bool bOk1 = add_line(x,y);

      bool bOk2 = add_line(x2,y2);

      return bOk1 && bOk2;

   }


   bool path::add_line(i32 x,i32 y,i32 x2,i32 y2)
   {

      bool bOk1 = add_line(x, y);

      bool bOk2 = add_line(x2, y2);

      return bOk1 && bOk2;

   }


   bool path::begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
   {

      m_bFill = bFill;

      m_efillmode = efillmode;

      m_bHasPoint = false;

      set_modified();

      return true;

   }


   bool path::end_figure(bool bClose)
   {


      __pointer(element) pelement;

      pelement = __new(element);

      pelement->m_etype               = element::type_end;

      pelement->u.m_end.m_bClose      = bClose;

      m_elementa.add(pelement);

      set_modified();

      return true;

   }


   bool path::add_string(i32 x,i32 y,const string & strText,::draw2d::font_pointer spfont)
   {

      __pointer(element) pelement;

      pelement = __new(element);

      pelement->m_etype                     = element::type_string;
      pelement->m_stringpath.m_x            = x;
      pelement->m_stringpath.m_y            = y;
      pelement->m_stringpath.m_strText      = strText;
      pelement->m_stringpath.m_pfont       = spfont;

      m_elementa.add(pelement);

      return true;

   }


   bool path::add_string(const string & strText, const ::rect & rect, int iDrawTextFlags, ::draw2d::font_pointer spfont, COLORREF crForeground)

   {

      __pointer(element) pelement;

      pelement = __new(element);

      pelement->m_etype = element::type_draw_text;
      pelement->m_stringpath.m_rect = rect;

      pelement->m_stringpath.m_strText = strText;
      pelement->m_stringpath.m_pfont = spfont;
      pelement->m_stringpath.m_iDrawTextFlags = iDrawTextFlags;
      pelement->m_stringpath.m_crForeground = crForeground;

      m_elementa.add(pelement);

      return true;

   }


   bool path::add_rect(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      __pointer(element) pelement;

      pelement = __new(element);

      pelement->m_etype               = element::type_rect;

      pelement->u.m_rect.m_x = x1;
      pelement->u.m_rect.m_y = y1;
      pelement->u.m_rect.m_cx = x2-x1;
      pelement->u.m_rect.m_cy = y2-y1;

      m_elementa.add(pelement);

      set_modified();

      return true;

   }


   bool path::add_rect(const ::rect & rect)

   {

      return add_rect(rect.left,rect.top,rect.right,rect.bottom);


   }



   bool path::add_line(const point & point1, const point & point2)
   {

      return add_line(point1.x, point1.y, point2.x, point2.y);

   }


   bool path::add_line(pointd point)
   {

      return add_line(point.x,point.y);

   }


   bool path::add_lines(const POINT * ppoint, ::count nCount)

   {

      bool bOk = true;

      for(i32 i = 0; i < nCount; i++)
      {

         if (!add_line(ppoint[i].x, ppoint[i].y))
         {

            bOk = false;

         }

      }

      return bOk;

   }


   bool path::add_lines(const POINTD * ppoint, ::count nCount)

   {

      bool bOk = true;

      for(i32 i = 0; i < nCount; i++)
      {

         if(!add_line(ppoint[i]))

            bOk = false;
      }

      return bOk;

   }

   bool path::add_move(pointd point)
   {

      return add_move(point.x,point.y);

   }

   void * path::detach()
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   void path::get_bounding_rect(RECT * prect)

   {

      prect->right     = 0x80000000;

      prect->left      = 0x7fffffff;

      prect->bottom    = 0x80000000;

      prect->top       = 0x7fffffff;



      for(int i = 0; i < m_elementa.get_count(); i++)
      {

         get_bounding_rect(prect, m_elementa(i));


      }

   }

   void path::get_bounding_rect(RECT * prect, element & element)

   {

      switch(element.m_etype)
      {
      case ::draw2d::path::element::type_arc:
         get_bounding_rect(prect, element.u.m_arc);

         break;
      case ::draw2d::path::element::type_line:
         get_bounding_rect(prect, element.u.m_line);

         break;
      case ::draw2d::path::element::type_move:
         get_bounding_rect(prect, element.u.m_move);

         break;
      case ::draw2d::path::element::type_rect:
         get_bounding_rect(prect,element.u.m_rect);

         break;
      case ::draw2d::path::element::type_string:
         get_bounding_rect(prect,element.m_stringpath);

         break;
      case ::draw2d::path::element::type_end:
      {

      }
      break;
      default:
         __throw(::exception::exception("unexpected simple os graphics element type"));
      }




   }

   void path::get_bounding_rect(RECT * prect,rect & rect)

   {

      prect->left = (LONG) rect.m_x;

      prect->top = (LONG)rect.m_y;

      prect->right= (LONG)(rect.m_x + rect.m_cx);

      prect->bottom = (LONG)(rect.m_y + rect.m_cy);


   }

   void path::get_bounding_rect(RECT * prect, arc & a)

   {

      ::rect rect;

      rect.left         = (LONG) (a.m_pointCenter.x - a.m_sizeRadius.cx);

      rect.right        = (LONG) (a.m_pointCenter.x + a.m_sizeRadius.cx);

      rect.top          = (LONG) (a.m_pointCenter.y - a.m_sizeRadius.cy);

      rect.bottom       = (LONG) (a.m_pointCenter.y + a.m_sizeRadius.cy);

      ::point point1;

      ::point point2;

      prect->left   = (LONG) MIN(a.m_pointCenter.x, prect->left);

      prect->top    = (LONG) MIN(a.m_pointCenter.y, prect->top);

      prect->right  = (LONG) MAX(a.m_pointCenter.x, prect->right);

      prect->bottom = (LONG) MAX(a.m_pointCenter.y, prect->bottom);


//      double pelement = a.m_dRadiusY / a.m_dRadiusX;

      double f1 = a.m_dAngle1;

      double f2 = a.m_dAngle2;

      point1.x          = (LONG) (a.m_pointCenter.x + a.m_sizeRadius.cx * cos(f1));

      point1.y          = (LONG) (a.m_pointCenter.y - a.m_sizeRadius.cy * sin(f1));

      point2.x          = (LONG) (a.m_pointCenter.x + a.m_sizeRadius.cx * cos(f2));

      point2.y          = (LONG) (a.m_pointCenter.y - a.m_sizeRadius.cy * sin(f2));

      prect->left   = (LONG) MIN(point1.x, prect->left);


      prect->top    = (LONG) MIN(point1.y, prect->top);


      prect->right  = (LONG) MAX(point1.x, prect->right);


      prect->bottom = (LONG) MAX(point1.y, prect->bottom);


      prect->left   = (LONG) MIN(point2.x, prect->left);


      prect->top    = (LONG) MIN(point2.y, prect->top);


      prect->right  = (LONG) MAX(point2.x, prect->right);


      prect->bottom = (LONG) MAX(point2.y, prect->bottom);


      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
      {

         prect->left   = (LONG) MIN(rect.right, prect->left);


         prect->right  = (LONG) MAX(rect.right, prect->right);


      }

      f1 -= System.math().GetPi() / 2.0;

      f2 -= System.math().GetPi() / 2.0;

      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
      {

         prect->top    = (LONG) MIN(rect.top, prect->top);


         prect->bottom = (LONG) MAX(rect.top, prect->bottom);


      }

      f1 -= System.math().GetPi() / 2.0;

      f2 -= System.math().GetPi() / 2.0;

      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
      {

         prect->left   = (LONG) MIN(rect.left, prect->left);


         prect->right  = (LONG) MAX(rect.left, prect->right);


      }

      f1 -= System.math().GetPi() / 2.0;

      f2 -= System.math().GetPi() / 2.0;

      if((f1 >= 0 && f2 <= f1) || (f1 <= 0 && f2 >= 0))
      {

         prect->top    = (LONG) MIN(rect.bottom, prect->top);


         prect->bottom = (LONG) MAX(rect.bottom, prect->bottom);


      }

   }

   void path::get_bounding_rect(RECT * prect, move & m)

   {

      prect->left   = (LONG) MIN(m.m_x, prect->left);


      prect->top    = (LONG) MIN(m.m_y, prect->top);


      prect->right  = (LONG) MAX(m.m_x, prect->right);


      prect->bottom = (LONG) MAX(m.m_y, prect->bottom);


   }


   void path::get_bounding_rect(RECT * prect, line & l)

   {

      prect->left   = (LONG) MIN(l.m_x, prect->left);


      prect->top    = (LONG) MIN(l.m_y, prect->top);


      prect->right  = (LONG) MAX(l.m_x, prect->right);


      prect->bottom = (LONG) MAX(l.m_y, prect->bottom);


   }

   void path::get_bounding_rect(RECT * prect,string_path & point)

   {


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

               add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 180, 90);

               bOn = true;

            }
            else if(bOn)
            {

               add_line(rectRect.top_left());

               bOn = false;

            }
            else
            {

               add_move(rectRect.top_left());

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

               add_arc(::rect(rectCorner.top_right(), ::size(iDiameter, iDiameter)), 270, 90);

               bOn = true;

            }
            else if(bOn)
            {

               add_line(rectRect.top_right());

               bOn = false;

            }
            else
            {

               add_move(rectRect.top_right());

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

               add_arc(::rect(rectCorner.bottom_right(), ::size(iDiameter, iDiameter)), 0, 90);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.bottom_right());

               bOn = false;

            }
            else
            {

               add_move(rectRect.bottom_right());
               
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

               add_arc(::rect(rectCorner.bottom_left(), ::size(iDiameter, iDiameter)), 90, 90);

               bOn = true;

            }
            else if(bOn)
            {

               add_line(rectRect.bottom_left());

               bOn = false;

            }
            else
            {

               add_move(rectRect.bottom_left());

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

               add_arc(::rectd(rectCorner.top_left(), ::sized(dDiameter, dDiameter)), 180, 90);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.top_left());

               bOn = false;

            }
            else
            {

               add_move(rectRect.top_left());

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

               add_arc(::rectd(rectCorner.top_right(), ::sized(dDiameter, dDiameter)), 270, 90);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.top_right());

               bOn = false;

            }
            else
            {

               add_move(rectRect.top_right());

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

               add_arc(::rectd(rectCorner.bottom_right(), ::sized(dDiameter, dDiameter)), 0, 90);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.bottom_right());

               bOn = false;

            }
            else
            {

               add_move(rectRect.bottom_right());

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

               add_arc(::rectd(rectCorner.bottom_left(), ::sized(dDiameter, dDiameter)), 90, 90);

               bOn = true;

            }
            else if (bOn)
            {

               add_line(rectRect.bottom_left());

               bOn = false;

            }
            else
            {

               add_move(rectRect.bottom_left());

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
         add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 180, 90);
         return true;
      case border_top_right:
         add_arc(::rect(rectCorner.top_right() - ::size(iDiameter, 0), ::size(iDiameter, iDiameter)), 270, 90);
         return true;
      case border_bottom_right:
         add_arc(::rect(rectCorner.bottom_right() - ::size(iDiameter, iDiameter), ::size(iDiameter, iDiameter)), 0, 90);
         return true;
      case border_bottom_left:
         add_arc(::rect(rectCorner.bottom_left() - ::size(0, iDiameter), ::size(iDiameter, iDiameter)), 90, 90);
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
         add_arc(::rect(rectCorner.top_left(), ::size(iDiameter, iDiameter)), 270, -90);
         return true;
      case border_top_right:
         add_arc(::rect(rectCorner.top_right() - ::size(iDiameter, 0), ::size(iDiameter, iDiameter)), 0, -90);
         return true;
      case border_bottom_right:
         add_arc(::rect(rectCorner.bottom_right() - ::size(iDiameter, iDiameter), ::size(iDiameter, iDiameter)), 90, -90);
         return true;
      case border_bottom_left:
         add_arc(::rect(rectCorner.bottom_left() - ::size(0, iDiameter), ::size(iDiameter, iDiameter)), 180, -90);
         return true;
      default:
         return false;
      }

   }


bool path::clock_corner(const ::rectd& rectCorner, double dRadius, eborder eborder)
{

   double dDiameter = dRadius * 2.0;

   switch (eborder)
   {
   case border_top_left:
      add_arc(::rectd(rectCorner.top_left(), ::sized(dDiameter, dDiameter)), 180, 90);
      return true;
   case border_top_right:
      add_arc(::rectd(rectCorner.top_right() - ::sized(dDiameter, 0), ::sized(dDiameter, dDiameter)), 270, 90);
      return true;
   case border_bottom_right:
      add_arc(::rectd(rectCorner.bottom_right() - ::sized(dDiameter, dDiameter), ::sized(dDiameter, dDiameter)), 0, 90);
      return true;
   case border_bottom_left:
      add_arc(::rectd(rectCorner.bottom_left() - ::sized(0, dDiameter), ::sized(dDiameter, dDiameter)), 90, 90);
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
      add_arc(::rectd(rectCorner.top_left(), ::sized(dDiameter, dDiameter)), 270, -90);
      return true;
   case border_top_right:
      add_arc(::rectd(rectCorner.top_right() - ::sized(dDiameter, 0), ::sized(dDiameter, dDiameter)), 0, -90);
      return true;
   case border_bottom_right:
      add_arc(::rectd(rectCorner.bottom_right() - ::sized(dDiameter, dDiameter), ::sized(dDiameter, dDiameter)), 90, -90);
      return true;
   case border_bottom_left:
      add_arc(::rectd(rectCorner.bottom_left() - ::sized(0, dDiameter), ::sized(dDiameter, dDiameter)), 180, -90);
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

         begin_figure(true, ::draw2d::fill_mode_winding);

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

         end_figure(bOn);

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

         begin_figure(true, ::draw2d::fill_mode_winding);

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

         end_figure(bOn);

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
      add_arc(Corner, 0, 90);

      add_line(rect.left + iDiameter / 2, rect.top + rect.height(), rect.left + rect.width() - iDiameter / 2, rect.top + rect.height());

      // bottom left
      Corner.left -= (rect.width() - iDiameter - 1);
      Corner.right = Corner.left + iDiameter2;
      add_arc(Corner, 90, 45);




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

      __throw(interface_only_exception);

      return false;

   }

   bool path::add_arc_label(const ::rect & rectParam)

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






