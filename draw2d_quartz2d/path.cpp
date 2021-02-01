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
   
   
   bool path::internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode)
   {
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   bool path::internal_close(bool bClose)
   {
      
      if(bClose)
      {
         
         CGPathCloseSubpath(m_path);
         
      }
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   bool path::internal_add_arc(const ::rectangle_f64 & rectangle, double dBeg, double dEnd, bool bClockwise)
   {
      
      CGFloat d1 = rectangle.right - rectangle.left;
      
      if(d1 <= 0)
         return true;
      
      CGFloat d2 = rectangle.bottom - rectangle.top;
      
      if(d2 <= 0)
         return true;
      
      CGFloat x = (rectangle.right + rectangle.left) / 2.0;
   
      CGFloat y = (rectangle.bottom + rectangle.top) / 2.0;
   
      if(d1 == d2)
      {
         
         CGPathAddArc(m_path, nullptr, x, y, d1/2.0, dBeg, dEnd, bClockwise ? 1 : 0);

      }
      else
      {
      
         CGAffineTransform t = CGAffineTransformMakeScale(1.0, d2 / d1);
      
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
         
      }
      
      return true;
      
   }
   
   
   bool path::internal_add_line(int x1, int y1, int x2, int y2)
   {
      
      x1+= m_pointOffset.x;
      y1+= m_pointOffset.y;
      x2+= m_pointOffset.x;
      y2+= m_pointOffset.y;


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
      
      x+= m_pointOffset.x;
      y+= m_pointOffset.y;

      
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

   bool path::internal_add_text_out(int x, int y, const string & strText, ::draw2d::font_pointer spfont, ::draw2d_quartz2d::graphics * p)
   {
      
      x+= m_pointOffset.x;
      y+= m_pointOffset.y;

      
      CGContextSaveGState(p->m_pdc);
      
      p->internal_show_text(spfont,nullptr,nullptr, x, y, 0, DT_TOPLEFT, strText, kCGTextInvisible);
      
      CGPathAddPath(m_path, nullptr, CGContextCopyPath(p->m_pdc));

      CGContextSaveGState(p->m_pdc);

      return true;
      
   }
   
   bool path::internal_add_move(int x, int y)
   {
      
      x+= m_pointOffset.x;
      y+= m_pointOffset.y;
      
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
   
   
   bool path::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {
      
      m_path = CGPathCreateMutable();
      
      //for(i32 i = 0; i < m_elementa.get_count(); i++)
      //{
         
         _set_create(pgraphics);
         
      //}
      
      m_osdata[0] = m_path;
      
      return true;
      
   }

   
//   bool path::set(const ::draw2d::path::matter & e)
//   {
//
//      switch(e.m_etype)
//      {
//         case ::draw2d::path::matter::type_move:
//            set(e.u.m_move);
//            break;
//         case ::draw2d::path::matter::type_arc:
//            set(e.u.m_arc);
//            break;
//         case ::draw2d::path::matter::type_line:
//            set(e.u.m_line);
//            break;
//         case ::draw2d::path::matter::e_type_string:
////            set(e.m_stringpath);
//            break;
//         case ::draw2d::path::matter::type_end:
//            internal_end_figure(e.u.m_end.m_bClose);
//            break;
//         default:
//            __throw(::exception::exception("unexpected simple os graphics matter type"));
//      }
//
//      return false;
//
//   }
   
   
   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::begin * pbegin)
   {

      return true;
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::arc * parc)
   {
   
      ::rectangle_f64 rectangle_i32;
      
      rectangle.left = parc->m_pointCenter.x - parc->m_sizeRadius.cx;
      rectangle.right = parc->m_pointCenter.x + parc->m_sizeRadius.cx;
      rectangle.top = parc->m_pointCenter.y - parc->m_sizeRadius.cy;
      rectangle.bottom = parc->m_pointCenter.y + parc->m_sizeRadius.cy;
      
      
      rectangle.offset(m_pointOffset);
      
      return internal_add_arc(rectangle, parc->m_angleBeg.radian(), parc->m_angleEnd.radian(), parc->m_angleEnd < parc->m_angleBeg);
      
   }
   
   
//   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::move & move)
//   {
//
//      return internal_add_move(move.m_x, move.m_y);
//
//   }
   
   
   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::rectangle_i32 * prectangle)
   {
   
      CGRect r;
      
      r.origin.x = prectangle->m_rectangle.left;
      r.origin.y = prectangle->m_rectangle.top;
      r.size.width = prectangle->m_rectangle.width();
      r.size.height = prectangle->m_rectangle.height();
      
      r.origin.x += m_pointOffset.x;
      r.origin.y += m_pointOffset.y;
      
      CGPathAddRect(m_path, nullptr, r);
                    
      return true;
      
   }
                    

   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::lines * plines)
   {
   
      ::array < CGPoint > points;
      
      ::papaya::array::__copy(points, plines->m_pointa);
      
      for(auto & point : points)
      {
         
         point.x += m_pointOffset.x;
         point.y += m_pointOffset.y;
         
      }
      
      CGPathAddLines(m_path, nullptr, points.get_data(), points.get_count());
                    
      return true;
      
   }
                    

   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::polygon_i32 * ppolygon)
   {

      ::array < CGPoint > points;
      
      ::papaya::array::__copy(points, ppolygon->m_pointa);
      
      for(auto & point : points)
      {
         
         point.x += m_pointOffset.x;
         point.y += m_pointOffset.y;
         
      }
      
      CGPathAddLines(m_path, nullptr, points.get_data(), points.get_count());

      CGPathCloseSubpath(m_path);
      
      return true;
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::line * pline)
   {
      
      if(pline->m_pointBeg != m_pointBeg)
      {
         
         internal_add_line(pline->m_pointBeg.x, pline->m_pointBeg.y);
         
      }
      
      return internal_add_line(pline->m_pointEnd.x, pline->m_pointEnd.y);
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::text_out * ptextout)
   {
      
      return false;
      
   }
   

   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::draw_text * pdrawtext)
   {
      
      return false;
      
   }
   

   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::close * pclose)
   {

      CGPathCloseSubpath(m_path);
      
      return true;
   
   }



   bool path::contains(::draw2d::graphics_pointer & pgraphics, const ::point_f64 & point)
   {
    
      CGMutablePathRef ppath = get_os_data <CGMutablePathRef>(pgraphics);
      
      if(::is_null(ppath))
      {
         
         return false;
         
      }
      
      return CGPathContainsPoint(ppath, nullptr,CGPointMake(point.x, point.y), false);
      
   }


   
} // namespace metrowin




