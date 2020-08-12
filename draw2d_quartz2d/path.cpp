#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   path::path()
   {
      
      m_path = nullptr;
      
      m_bBegin = true;
      
   }
   
   
   path::~path()
   {
      
      
   }
   
   
   bool path::internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode)
   {
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   bool path::internal_end_figure(bool bClose)
   {
      
      if(bClose)
      {
         
         CGPathCloseSubpath(m_path);
         
      }
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   bool path::internal_add_arc(const ::rect & rect, double dBeg, double dEnd, bool bClockwise)
   {
      
      CGFloat d1 = rect.right - rect.left;
      
      if(d1 <= 0)
         return true;
      
      CGFloat d2 = rect.bottom - rect.top;
      
      if(d2 <= 0)
         return true;
      
      CGAffineTransform t = CGAffineTransformMakeScale(1.0, d2 / d1);
      
      CGFloat x = (rect.right + rect.left) / 2.0;
      
      CGFloat y = (rect.bottom + rect.top) / 2.0;
      
//      CGFloat x1 = x + d1 * cos(dBeg);
//      
//      CGFloat y1 = y + d1 * sin(dBeg);
      
//      if(CGPathIsEmpty(m_path))
//      {
//
//         internal_add_move(x1, y1);
//
//      }
      
      CGPathAddArc(m_path, &t, x, y, d1/2.0, dBeg, dEnd, bClockwise ? 1 : 0);
      
      return true;
      
   }
   
   
   bool path::internal_add_line(int x1, int y1, int x2, int y2)
   {

      if(CGPathIsEmpty(m_path))
      {
         
         internal_add_move(x1, y1);
         
      }
      else
      {
      
         CGPathAddLineToPoint(m_path, nullptr, x1, y1);
         
      }

      CGPathAddLineToPoint(m_path, nullptr, x2, y2);
      
      return true;
      
   }
   
   
   bool path::internal_add_line(int x, int y)
   {
      
      if(CGPathIsEmpty(m_path))
      {
         
         internal_add_move(x, y);
         
      }
      else
      {
         
         CGPathAddLineToPoint(m_path, nullptr, x, y);
         
      }
      
      return true;
      
   }

   bool path::internal_add_string_path(int x, int y, const string & strText, ::draw2d::font_pointer spfont, ::draw2d_quartz2d::graphics * p)
   {
      
      CGContextSaveGState(p->m_pdc);
      
      p->internal_show_text(spfont,nullptr,nullptr, x, y, 0, DT_TOPLEFT, strText, kCGTextInvisible);
      
      CGPathAddPath(m_path, nullptr, CGContextCopyPath(p->m_pdc));

      CGContextSaveGState(p->m_pdc);

      return true;
      
   }
   
   bool path::internal_add_move(int x, int y)
   {

      CGPathMoveToPoint(m_path, nullptr, x, y);
      
      m_bBegin = false;
      
      return true;
      
   }
   
   
   
   void * path::detach()
   {
      
      void * ppath = m_path;
      
      m_path = nullptr;
      m_osdata[0] = nullptr;
      
      return ppath;
      
   }
   
   
//   void * path::get_os_data() const
//   {
//
//      defer_update();
//
//      return m_path;
//
//
//   }
   
   void path::destroy()
   {
      
      if(m_path != nullptr)
      {
         
         CGPathRelease(m_path);
         
         m_path = nullptr;
         
      }
      
      //return true;
      
   }
   
   
   bool path::create(::draw2d::graphics * pgraphics)
   {
      
      m_path = CGPathCreateMutable();
      
      for(i32 i = 0; i < m_elementa.get_count(); i++)
      {
         
         set(m_elementa(i));
         
      }
      
      m_osdata[0] = m_path;
      
      return true;
      
   }

   
   bool path::set(const ::draw2d::path::element & e)
   {
      
      switch(e.m_etype)
      {
         case ::draw2d::path::element::type_move:
            set(e.u.m_move);
            break;
         case ::draw2d::path::element::type_arc:
            set(e.u.m_arc);
            break;
         case ::draw2d::path::element::type_line:
            set(e.u.m_line);
            break;
         case ::draw2d::path::element::type_string:
//            set(e.m_stringpath);
            break;
         case ::draw2d::path::element::type_end:
            internal_end_figure(e.u.m_end.m_bClose);
            break;
         default:
            __throw(::exception::exception("unexpected simple os graphics element type"));
      }
      
      return false;
      
   }
   
   
   bool path::set(const ::draw2d::path::arc & arc)
   {
   
      ::rect rect;
      rect.left = arc.m_pointCenter.x - arc.m_sizeRadius.cx;
      rect.right = arc.m_pointCenter.x + arc.m_sizeRadius.cx;
      rect.top = arc.m_pointCenter.y - arc.m_sizeRadius.cy;
      rect.bottom = arc.m_pointCenter.y + arc.m_sizeRadius.cy;
      
      return internal_add_arc(rect, arc.m_dAngle1, arc.m_dAngle2, arc.m_dAngle < 0.0);
      
   }
   
   
   bool path::set(const ::draw2d::path::move & move)
   {
      
      return internal_add_move(move.m_x, move.m_y);
      
   }
   
   bool path::set(const ::draw2d::path::line & line)
   {
      
      return internal_add_line(line.m_x, line.m_y);
      
   }

   bool path::set(const ::draw2d::path::string_path & stringpath)
   {
      
      return false;
      //return //internal_add_string_path(stringpath.m_x, stringpath.m_y, stringpath.m_strText, stringpath.m_pfont);
      
   }
   

   bool path::contains(::draw2d::graphics_pointer & pgraphics, const ::pointd & point)
   {
    
      CGMutablePathRef ppath = get_os_data <CGMutablePathRef>(pgraphics);
      
      if(::is_null(ppath))
      {
         
         return false;
         
      }
      
      return CGPathContainsPoint(ppath, nullptr,CGPointMake(point.x, point.y), false);
      
   }


   
} // namespace metrowin




