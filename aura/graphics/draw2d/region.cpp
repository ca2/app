#include "framework.h"


namespace draw2d
{


   region::region()
   {

      m_eregion         = e_region_none;
      m_lppoints        = nullptr;
      m_lppolycounts    = nullptr;

   }


   region::region(const region & region)
   {

      m_lppolycounts    = nullptr;
      m_lppoints        = nullptr;
      m_eregion         = e_region_none;

      operator = (region);

   }


   region::~region()
   {

      destroy();

   }


   ::e_status region::destroy()
   {

      ::acme::adel(m_lppoints);
      ::acme::adel(m_lppolycounts);
      m_pregion1.release();
      m_pregion2.release();

      return ::success;

   }


   bool region::create_rectangle(const ::rectangle_i32 & rectangle)
   {

      if(m_eregion != e_region_none)
      {

         destroy();

      }

      m_eregion = e_region_rect;

      m_x1 = rectangle.left;

      m_y1 = rectangle.top;

      m_x2 = rectangle.right;

      m_y2 = rectangle.bottom;

      return true;

   }


   bool region::create_ellipse(const ::rectangle_i32 & rectangle)
   {

      if(m_eregion != e_region_none)
      {

         destroy();

      }

      m_eregion = e_region_ellipse;

      m_x1 = rectangle.left;

      m_y1 = rectangle.top;

      m_x2 = rectangle.right;

      m_y2 = rectangle.bottom;

      return true;

   }


   bool region::create_polygon(const POINT_F64 * ppoints, i32 nCount, ::draw2d::enum_fill_mode efillmode)
   {

      if(m_eregion != e_region_none)
      {

         destroy();

      }

      m_eregion = e_region_polygon;

      m_nCount = nCount;
      ::acme::del(m_lppoints);
      m_lppoints = new ::point_f64[m_nCount];
      ::memcpy_dup(m_lppoints, ppoints, sizeof(POINT_F64) * m_nCount);

      m_efillmode = efillmode;

      return true;
   }


   bool region::create_polygon(const POINT_I32 * ppoints, i32 nCount, ::draw2d::enum_fill_mode efillmode)
   {

      if(m_eregion != e_region_none)
      {

         destroy();

      }

      m_eregion = e_region_polygon;

      m_nCount = nCount;

      m_lppoints = new ::point_f64[m_nCount];

      for(index i = 0; i < m_nCount; i++)
      {

         m_lppoints[i].x = (double) ppoints[i].x;

         m_lppoints[i].y = (double) ppoints[i].y;

      }

      m_efillmode = efillmode;

      return true;

   }


   bool region::create_poly_polygon(const POINT_F64 * ppoints, const i32 * ppolycounts, i32 nCount, ::draw2d::enum_fill_mode efillmode)
   {

      if(m_eregion != e_region_none)
      {

         destroy();

      }

      m_eregion = e_region_polygon;

      m_nCount = nCount;

      m_lppolycounts = new int[m_nCount];

      ::memcpy_dup(m_lppolycounts, ppolycounts, sizeof(int) * m_nCount);

      i32 iTotalCount = 0;

      for(i32 i = 0; i < nCount; i++)
      {

         iTotalCount += m_lppolycounts[i];

      }

      m_lppoints = new ::point_f64[iTotalCount];

      ::memcpy_dup(m_lppoints, ppoints, sizeof(POINT_F64) * iTotalCount);

      m_efillmode = efillmode;

      return true;

   }


   bool region::create_poly_polygon(const POINT_I32 * ppoints, const i32 * ppolycounts,i32 nCount,::draw2d::enum_fill_mode efillmode)
   {

      if(m_eregion != e_region_none)
      {

         destroy();

      }

      m_eregion = e_region_poly_polygon;

      m_nCount = nCount;

      m_lppolycounts = new int[m_nCount];

      ::memcpy_dup(m_lppolycounts,ppolycounts,sizeof(int)* m_nCount);

      i32 iTotalCount = 0;

      for(i32 i = 0; i < nCount; i++)
      {

         iTotalCount += m_lppolycounts[i];

      }

      m_lppoints = new ::point_f64[iTotalCount];

      for(i32 i = 0; i < iTotalCount; i++)
      {

         m_lppoints[i].x = ppoints[i].x;

         m_lppoints[i].y = ppoints[i].y;

      }

      m_efillmode = efillmode;

      return true;

   }


   bool region::combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, enum_combine ecombine, ::draw2d::graphics * pgraphics)
   {

      __pointer(::draw2d::region) pregion1 = (::draw2d::region *) prgn1;

      __pointer(::draw2d::region) pregion2 = (::draw2d::region *) prgn2;

      if(m_eregion != e_region_none)
      {

         destroy();

      }

      m_eregion = e_region_combine;

      m_pregion1 = pregion1;

      m_pregion2 = pregion2;

      m_ecombine  = ecombine;

      return true;

   }

   region & region::operator = (const ::draw2d::region & regionSrc)
   {

      if(this == &regionSrc)
         return *this;

      if(m_eregion != e_region_none)
      {

         destroy();

      }

      m_eregion = regionSrc.m_eregion;

      switch(m_eregion)
      {
      case e_region_none:
         return *this;
      case e_region_rect:
      case e_region_ellipse:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         return *this;
      case e_region_polygon:
         m_nCount = regionSrc.m_nCount;
         m_lppoints = new ::point_f64[m_nCount];
         ::memcpy_dup(m_lppoints, regionSrc.m_lppoints, sizeof(POINT_F64) * m_nCount);
         m_efillmode = regionSrc.m_efillmode;
         return *this;
      case e_region_poly_polygon:
      {
         m_nCount = regionSrc.m_nCount;
         m_lppolycounts = new int[m_nCount];
         ::memcpy_dup(m_lppolycounts, regionSrc.m_lppolycounts, sizeof(int) * m_nCount);
         i32 iTotalCount = 0;
         for(i32 i = 0; i < m_nCount; i++)
         {
            iTotalCount += m_lppolycounts[i];
         }
         m_lppoints = new ::point_f64[iTotalCount];
         ::memcpy_dup(m_lppoints, regionSrc.m_lppoints, sizeof(POINT_F64) * iTotalCount);
         m_efillmode = regionSrc.m_efillmode;
      }
      return *this;
      case e_region_round_rect:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         m_x3 = regionSrc.m_x3;
         m_y3 = regionSrc.m_y3;
         return *this;
      case e_region_combine:
         m_pregion1 = new ::draw2d::region(*regionSrc.m_pregion1);
         m_pregion2 = new ::draw2d::region(*regionSrc.m_pregion2);
         m_ecombine = regionSrc.m_ecombine;
         return *this;
      default:
         throw interface_only_exception();
      };
      return *this;

   }


   bool region::get_bounding_box(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics)
   {

      throw ::interface_only_exception();

      return false;

   }


   bool region::contains(const POINT_F64 & point, ::draw2d::graphics * pgraphics)
   {

      return internal_contains(point);

   }


   bool region::translate(const POINT_I32 & point, ::draw2d::graphics * pgraphics)
   {

      set_modified();

      switch(m_eregion)
      {
      case e_region_none:
         return false;
      case e_region_round_rect:
         m_x3 += point.x;
         m_y3 += point.y;
      case e_region_rect:
      case e_region_ellipse:
         m_x1 += point.x;
         m_y1 += point.y;
         m_x2 += point.x;
         m_y2 += point.y;
         return true;
      case e_region_polygon:
         for(i32 i = 0; i < m_nCount; i++)
         {
            m_lppoints[i].x += point.x;
            m_lppoints[i].y += point.y;
         }
         return true;
      case e_region_poly_polygon:
      {
         i32 iTotalCount = 0;
         for(i32 i = 0; i < m_nCount; i++)
         {
            iTotalCount += m_lppolycounts[i];
         }
         for(i32 i = 0; i < iTotalCount; i++)
         {
            m_lppoints[i].x += point.x;
            m_lppoints[i].y += point.y;
         }
      }
      return true;
      case e_region_combine:
      {
         bool bOk1 = m_pregion1->translate(point);
         bool bOk2 = m_pregion2->translate(point);
         return bOk1 && bOk2;
      }
      default:
         throw interface_only_exception();
      };
      return false;

   }


   bool region::contains(const POINT_I32 & point, ::draw2d::graphics * pgraphics)
   {

      return contains(point_f64(point));

   }


   void region::max_bounding_box(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_f64 rectangle;

      max_bounding_box(rectangle);

      __copy(prectangle, rectangle);

   }


   void region::max_bounding_box_rect(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_f64 rectangle;

      max_bounding_box_rect(rectangle);

      __copy(prectangle, rectangle);


   }


   void region::max_bounding_box_oval(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_f64 rectangle;

      max_bounding_box_oval(rectangle);

      __copy(prectangle, rectangle);

   }


   void region::max_bounding_box_polygon(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_f64 rectangle;

      max_bounding_box_polygon(rectangle);

      __copy(prectangle, rectangle);

   }


   void region::max_bounding_box_poly_polygon(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_f64 rectangle;

      max_bounding_box_poly_polygon(rectangle);

      __copy(prectangle, rectangle);

   }


   void region::max_bounding_box_combine(RECTANGLE_I32 * prectangle, ::draw2d::graphics * pgraphics)
   {

      ::rectangle_f64 rectangle;

      max_bounding_box_combine(rectangle);

      __copy(prectangle, rectangle);

   }


   void region::max_bounding_box(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      switch(m_eregion)
      {
      case e_region_none:
         return;
      case e_region_rect:
         return max_bounding_box_rect(prectangle);

      case e_region_ellipse:
         return max_bounding_box_oval(prectangle);

      case e_region_polygon:
         return max_bounding_box_polygon(prectangle);

      case e_region_poly_polygon:
         return max_bounding_box_poly_polygon(prectangle);

      case e_region_combine:
         return max_bounding_box_combine(prectangle);

      default:
         throw interface_only_exception();
      }

   }


   void region::max_bounding_box_rect(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      prectangle->left = minimum(prectangle->left,m_x1);

      prectangle->right = maximum(prectangle->right,m_x2);

      prectangle->top = minimum(prectangle->left,m_y1);

      prectangle->bottom = maximum(prectangle->right,m_y2);

   }


   void region::max_bounding_box_oval(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      prectangle->left = minimum(prectangle->left,m_x1);

      prectangle->right = maximum(prectangle->right,m_x2);

      prectangle->top = minimum(prectangle->left,m_y1);

      prectangle->bottom = maximum(prectangle->right,m_y2);

   }


   void region::max_bounding_box_polygon(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      if(m_nCount <= 0)
      {

         return;
         
      }

      for(int i = 0; i < m_nCount; i++)
      {

         prectangle->left = minimum(prectangle->left,m_lppoints[i].x);

         prectangle->right = maximum(prectangle->right,m_lppoints[i].x);

         prectangle->top = minimum(prectangle->left,m_lppoints[i].y);

         prectangle->bottom = maximum(prectangle->right,m_lppoints[i].y);

      }

   }


   void region::max_bounding_box_poly_polygon(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      i32 n = 0;

      for(i32 i = 0; i < m_nCount; i++)
      {

         i32 iCount = m_lppolycounts[i];

         for(int j = 0; j < iCount; j++,n++)
         {

            prectangle->left = minimum(prectangle->left,m_lppoints[n].x);

            prectangle->right = maximum(prectangle->right,m_lppoints[n].x);

            prectangle->top = minimum(prectangle->left,m_lppoints[n].y);

            prectangle->bottom = maximum(prectangle->right,m_lppoints[n].y);

         }

      }

   }


   void region::max_bounding_box_combine(RECTANGLE_F64 * prectangle, ::draw2d::graphics * pgraphics)
   {

      m_pregion1->max_bounding_box(prectangle);

      m_pregion2->max_bounding_box(prectangle);

   }


   bool region::internal_contains(const POINT_F64 & point)
   {

      switch(m_eregion)
      {
      case e_region_none:
         return false;
      case e_region_rect:
         return internal_rectangle_contains(point);

      case e_region_ellipse:
         return internal_oval_contains(point);

      case e_region_polygon:
         return internal_polygon_contains(point);

      case e_region_poly_polygon:
         return internal_poly_polygon_contains(point);

      case e_region_combine:
         return internal_combine_contains(point);

      default:
         throw interface_only_exception();
      }

      return false;

   }


   bool region::internal_rectangle_contains(const POINT_F64 & point)
   {

      return point.x >= m_x1 && point.y >= m_y1 && point.x <= m_x2 && point.y <= m_y2;

   }


   bool region::internal_oval_contains(const POINT_F64 & point)
   {

      double centerx    = (m_x2 + m_x1) / 2.0;
      double centery    = (m_y2 + m_y1) / 2.0;

      double rx    = fabs(m_x2 - m_x1) / 2.0;
      double ry    = fabs(m_y2 - m_y1) / 2.0;

      if (rx == 0.0 || ry == 0.0)
      {

         return false;

      }
   
      double x = point.x;

      double y = point.y;
      
      double dx = x - centerx;
      
      double dy = y - centery;
      
      if(rx == ry)
      {
         
         double r = rx;
         
         double square_distance = (dx * dx) + (dy * dy);
         
         double square_boundary = (r * r);
         
         return square_distance <= square_boundary;
               
      }
      else
      {

         double normal_distance = ((dx * dx) / (rx * rx) + (dy * dy) / (ry * ry));
         
         return normal_distance <= 1.0;
         
      }

   }


   bool region::internal_polygon_contains(const POINT_F64 & point)
   {

      if (m_nCount <= 0)
      {

         return false;

      }

      if (::polygon_contains_point(m_lppoints, m_nCount, point))
      {

         return true;

      }

      return false;

   }


   bool region::internal_poly_polygon_contains(const POINT_F64 & point)
   {

      i32 n = 0;

      for(i32 i = 0; i < m_nCount; i++)
      {

         i32 iCount = m_lppolycounts[i];

         if (::polygon_contains_point(&m_lppoints[n], iCount, point))
         {

            return true;

         }

         n += iCount;

      }

      return false;

   }


   bool region::internal_combine_contains(const POINT_F64 & point)
   {

      if(m_ecombine == e_combine_add)
      {

         if (m_pregion1->internal_contains(point))
         {

            return true;

         }

         if (m_pregion2->internal_contains(point))
         {

            return true;

         }

         return false;

      }
      else if(m_ecombine == e_combine_exclude)
      {

         if (m_pregion2->internal_contains(point))
         {

            return false;

         }

         if (m_pregion1->internal_contains(point))
         {

            return true;

         }

         return false;

      }
      else if(m_ecombine == e_combine_intersect)
      {
         
         if(m_pregion1->internal_contains(point))
         {

            if (m_pregion2->internal_contains(point))
            {

               return true;

            }

         }

         return false;

      }
      else if(m_ecombine == e_combine_xor)
      {
         
         if(m_pregion1->internal_contains(point))
         {

            if (m_pregion2->internal_contains(point))
            {

               return false;

            }
            else
            {

               return true;

            }

         }
         else if(m_pregion2->internal_contains(point))
         {

            return true;

         }
         else
         {

            return false;

         }

      }
      else
      {

         return false;

      }

   }


   bool region::internal_contains(const POINT_I32 & point)
   {

      return internal_contains(point_f64(point));

   }


   bool region::internal_rectangle_contains(const POINT_I32 & point)
   {

      return internal_rectangle_contains(point_f64(point));

   }


   bool region::internal_oval_contains(const POINT_I32 & point)
   {

      return internal_oval_contains(point_f64(point));

   }


   bool region::internal_polygon_contains(const POINT_I32 & point)
   {

      return internal_polygon_contains(point_f64(point));

   }


   bool region::internal_poly_polygon_contains(const POINT_I32 & point)
   {

      return internal_poly_polygon_contains(point_f64(point));

   }


   bool region::internal_combine_contains(const POINT_I32 & point)
   {

      return internal_combine_contains(point_f64(point));

   }


} // namespace draw2d



