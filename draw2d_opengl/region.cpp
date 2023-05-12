#include "framework.h"
#include "_opengl.h"
#include "region.h"


namespace draw2d_opengl
{

   //region::region(const region & rectangle) :
   //   ::draw2d::region(rectangle)
   //{
   //   //m_pregion = nullptr;
   //   m_bUpdated = false;
   //}


   region::region()
   { 
      
      /*m_pregion = nullptr;*/
      //m_bUpdated = false;

   }

   region::~region()
   {
      
      //if(m_pregion != nullptr)
      //{
      //   delete m_pregion;
      //   m_pregion = nullptr;
      //}

   }

/*
   i32 region::GetRegionData(LPRGNDATA lpRgnData, i32 nDataSize) const
   { ASSERT(get_os_data() != nullptr); return (i32)::GetRegionData((HRGN)get_os_data(), nDataSize, lpRgnData); }
   void region::SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
   { ASSERT(get_os_data() != nullptr); ::SetRectRgn((HRGN)get_os_data(), x1, y1, x2, y2); }
   
   void region::SetRectRgn(const ::rectangle_i32 & rectangle)
   { 
      ::SetRectRgn((HRGN)get_os_data(), rectangle.left, rectangle.top, rectangle.right, rectangle.bottom); 
   }

   i32 region::CombineRgn(const ::draw2d::region* pRgn1, const ::draw2d::region* pRgn2, i32 nCombineMode)
   { ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgn1->get_os_data(),
   (HRGN)pRgn2->get_os_data(), nCombineMode); }
   i32 region::CopyRgn(const ::draw2d::region* pRgnSrc)
   { ASSERT(get_os_data() != nullptr); return ::CombineRgn((HRGN)get_os_data(), (HRGN)pRgnSrc->get_os_data(), nullptr, RGN_COPY); }

   bool region::EqualRgn(const ::draw2d::region* pRgn) const
   {
      
      ASSERT(get_os_data() != nullptr); 
      
      return ::EqualRgn((HRGN)get_os_data(), (HRGN)pRgn->get_os_data()) != false;

   }

   i32 region::OffsetRgn(i32 x, i32 y)
   { ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), x, y); }
   i32 region::OffsetRgn(const ::point_i32 & point)
   { ASSERT(get_os_data() != nullptr); return ::OffsetRgn((HRGN)get_os_data(), point.x, point.y); }

   */
   bool region::get_bounding_box(RECTANGLE_I32 * lprect) const
   {

      //((region *)this)->defer_update();

      //plusplus::rectangle_i32 rectangle_i32;

      //((region *) this)->m_pregion->GetBounds(&rectangle, &plusplus::Graphics((HDC) nullptr));


      //lprect->left = rectangle.X;
      //lprect->top = rectangle.Y;
      //lprect->right = rectangle.X + rectangle.Width;
      //lprect->bottom = rectangle.Y + rectangle.Height;
      
      return true;

   }
   /*
   bool region::PtInRegion(i32 x, i32 y) const
   { 

      plusplus::PointF point_f32((plusplus::REAL) x, (plusplus::REAL) y);
      
      ASSERT(get_os_data() != nullptr); //return ::PtInRegion((HRGN)get_os_data(), x, y); 

      return m_pregion->IsVisible(point_f32)  != false;
   
   }
   */
   bool region::contains(const ::point_i32 & point) const
   { 

    /*  ((region *) (this))->defer_update();

      plusplus::PointF point_f32((plusplus::REAL) point.x, (plusplus::REAL) point.y);
      
      ASSERT(get_os_data() != nullptr);

      return m_pregion->IsVisible(point_f32)  != false;
*/
      return true;
   }
   /*
   bool region::rectInRegion(const ::rectangle_i32 & rectangle) const
   { 
      //ASSERT(get_os_data() != nullptr); return ::rectInRegion((HRGN)get_os_data(), rectangle); 

      plusplus::rectF rectangle_f32((plusplus::REAL) rectangle.left, (plusplus::REAL) rectangle.top, (plusplus::REAL) (rectangle.right - rectangle.left), (plusplus::REAL) (rectangle.bottom - rectangle.top));
      
      ASSERT(get_os_data() != nullptr); //return ::PtInRegion((HRGN)get_os_data(), x, y); 

      return m_pregion->IsVisible(rectangle_f32)  != false;

   }
   */

   void * region::get_os_data() const
   {

      //((region *) this)->defer_update();

      //return m_pregion;

      return nullptr;

   }


   void region::defer_update()
   {
      
      //if(m_pregion == nullptr || !m_bUpdated)
      //{

      //   if(m_pregion != nullptr)
      //   {
      //      delete m_pregion;
      //   }

      //   m_pregion = get();

      //}

   }


   void region::destroy()
   {

      /*if(m_pregion != nullptr)
      {

         delete m_pregion;

         m_pregion = nullptr;

      }*/

      return ::draw2d::region::destroy();

   }

   //plusplus::Region * region::get()
   //{
   //   
   //   //switch(m_etype)
   //   //{
   //   //case type_none:
   //   //   return memory_new plusplus::Region();
   //   //case type_rect:
   //   //   return get_rect();
   //   //case type_oval:
   //   //   return get_oval();
   //   //case type_polygon:
   //   //   return get_polygon();
   //   //case type_poly_polygon:
   //   //   return get_polygon();
   //   //case type_combine:
   //   //   return get_combine();
   //   //default:
   //   //   throw ::interface_only();
   //   //}

   //   return nullptr;

   //}

   //plusplus::Region * region::get_rect()
   //{

   //   plusplus::GraphicsPath path;

   //   plusplus::rectF rectangle_i32;

   //   rectangle.X      = (plusplus::REAL) m_x1;
   //   rectangle.Y      = (plusplus::REAL) m_y1;
   //   rectangle.Width  = (plusplus::REAL) (m_x2 - m_x1);
   //   rectangle.Height = (plusplus::REAL) (m_y2 - m_y1);

   //   path.AddRectangle(rectangle);

   //   return memory_new plusplus::Region(&path);
   //      
   //}

   //plusplus::Region * region::get_oval()
   //{
   //   
   //   plusplus::GraphicsPath path;

   //   path.AddEllipse((::i32) m_x1, (::i32) m_y1, (::i32) (m_x2 - m_x1), (::i32) (m_y2 - m_y1));

   //   return memory_new plusplus::Region(&path);

   //}

   //plusplus::Region * region::get_polygon()
   //{

   //   plusplus::GraphicsPath path;

   //   array < plusplus::PointF > pa;

   //   for(i32 i = 0; i < m_nCount; i++)
   //   {
   //      pa.add(plusplus::PointF((plusplus::REAL) m_lppoints[i].x, (plusplus::REAL) m_lppoints[i].y));
   //   }

   //   if(m_efillmode == ::draw2d::e_fill_mode_alternate)
   //   {
   //      path.SetFillMode(plusplus::FillModeAlternate);
   //   }
   //   else
   //   {
   //      path.SetFillMode(plusplus::FillModeWinding);
   //   }

   //   path.AddPolygon(pa.get_data(), (i32) pa.get_count());

   //   return memory_new plusplus::Region(&path);

   //}

   //plusplus::Region * region::get_poly_polygon()
   //{
   //   plusplus::GraphicsPath path;

   //   array < plusplus::PointF > pa;

   //   if(m_efillmode == ::draw2d::e_fill_mode_alternate)
   //   {
   //      path.SetFillMode(plusplus::FillModeAlternate);
   //   }
   //   else
   //   {
   //      path.SetFillMode(plusplus::FillModeWinding);
   //   }

   //   i32 n = 0;

   //   for(i32 i = 0; i < m_nCount; i++)
   //   {
   //      i32 jCount = m_lppolycounts[i];
   //      pa.erase_all();
   //      for(i32 j = 0; j < jCount; j++)
   //      {
   //         pa.add(plusplus::PointF((plusplus::REAL) m_lppoints[n].x, (plusplus::REAL) m_lppoints[n].y));
   //         n++;
   //      }
   //      path.AddPolygon(pa.get_data(), (i32) pa.get_count());
   //      path.CloseFigure();
   //   }

   //   return memory_new plusplus::Region(&path);

   //}

   //plusplus::Region * region::get_combine()
   //{

   //   plusplus::Region * pregion = ((plusplus::Region *) m_pregion1->get_os_data())->Clone();
   //   plusplus::Region * pregionOp = (plusplus::Region *) m_pregion2->get_os_data();

   //   if(m_ecombine == combine_add)
   //   {
   //      pregion->Union(pregionOp);
   //   }
   //   else if(m_ecombine == combine_exclude)
   //   {
   //      pregion->Exclude(pregionOp);
   //   }
   //   else if(m_ecombine == combine_intersect)
   //   {
   //      pregion->Intersect(pregionOp);
   //   }
   //   else
   //   {
   //      pregion->Union(pregionOp);
   //   }
   //   
   //   return pregion;

   //}

} // namespace draw2d_opengl
