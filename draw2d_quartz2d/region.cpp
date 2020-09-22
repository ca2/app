#include "framework.h"


namespace draw2d_quartz2d
{


   region::region()
   {

   }


   region::~region()
   {

   }


   void region::destroy()
   {

      if(m_path != nullptr)
      {

         CGPathRelease(m_path);

         m_path = nullptr;

      }

   }


   bool region::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

      m_path = CGPathCreateMutable();

      if(m_eregion == ::draw2d::e_region_rect)
      {

         CGRect rect;

         rect.origin.x = m_x1;
         rect.origin.y = m_y1;
         rect.size.width = m_x2 - m_x1;
         rect.size.height = m_y2 - m_y1;
         
         CGPathAddRect (m_path, nullptr, rect);

      }
      else if(m_eregion == ::draw2d::e_region_polygon)
      {

         CGPathMoveToPoint(m_path, nullptr, m_lppoints[0].x, m_lppoints[0].y);

         for(i32 i = 1; i < m_nCount; i++)
         {

            CGPathAddLineToPoint(m_path, nullptr, m_lppoints[i].x, m_lppoints[i].y);

         }

      }
      else if(m_eregion == ::draw2d::e_region_oval)
      {

         CGRect rect;

         rect.origin.x = m_x1;
         rect.origin.y = m_y1;
         rect.size.width = m_x2 - m_x1;
         rect.size.height = m_y2 - m_y1;

         CGPathAddEllipseInRect(m_path, nullptr, rect);

      }
      else if(m_eregion == ::draw2d::e_region_combine)
      {

         __throw(::exception::exception("not supported"));

      }

      CGPathCloseSubpath(m_path);
      
      CGAffineTransform transformTranslation = CGAffineTransformMakeTranslation(m_pointOffset.x, m_pointOffset.y);
      
      m_path = CGPathCreateMutableCopyByTransformingPath(m_path, &transformTranslation);

      return true;

   }


   void * region::detach()
   {

      void * ppath = m_path;

      m_path = nullptr;

      return ppath;

   }


} // namespace draw2d_quartz2d



