#include "framework.h"


namespace draw2d
{


   region::region()
   {

      m_etype           = type_none;
      m_lppoints        = nullptr;
      m_lppolycounts    = nullptr;

   }


   region::region(const region & region)
   {

      m_lppolycounts    = nullptr;
      m_lppoints        = nullptr;
      m_etype           = type_none;

      operator = (region);

   }


   region::~region()
   {

      destroy();

   }


   void region::finalize()
   {

      ::aura::adel(m_lppoints);
      ::aura::adel(m_lppolycounts);
      m_pregion1.release();
      m_pregion2.release();

      //e_type etype = m_etype;

      //m_etype = type_none;

      //switch(etype)
      //{
      //case type_none:
      //   return false;
      //case type_rect:
      //   return true;
      //case type_oval:
      //   return true;
      //case type_polygon:
      //   ::aura::adel(m_lppoints);
      //   return true;
      //case type_poly_polygon:
      //   ::aura::adel(m_lppoints);
      //   ::aura::adel(m_lppolycounts);
      //   return true;
      //case type_round_rect:
      //   return true;
      //case type_combine:
      //   m_pregion1.release();
      //   m_pregion2.release();
      //   return true;
      //default:
      //   ::exception::throw_not_implemented();
      //};

   }


   /*bool region::CreateRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      m_pointa.remove_all();

      m_pointa.add(pointd(x1, y1));
      m_pointa.add(pointd(x2, y2));

      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::create_rect(const ::rect & rect)

   {

      m_pointa.remove_all();

      m_pointa.add(pointd(rect.left, rect.top));

      m_pointa.add(pointd(rect.right, rect.bottom));


      m_etype = type_rect;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateEllipticRgn(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      m_pointa.remove_all();

      m_pointa.add(pointd(x1, y1));
      m_pointa.add(pointd(x2, y2));

      m_etype = type_elliptic;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateEllipticRgnIndirect(const ::rect & rect)

   {

      m_pointa.remove_all();

      m_pointa.add(pointd(rect.left, rect.top));

      m_pointa.add(pointd(rect.right, rect.bottom));


      m_etype = type_elliptic;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreatePolygonRgn(LPPOINT pPoints, i32 nCount, i32 nMode)

   {

      m_pointa.remove_all();

      for(i32 i = 0; i < nCount; i++)
      {
         m_pointa.add(pointd(pPoints[i].x, lpPoints[i].y));

      }

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreatePolyPolygonRgn(LPPOINT pPoints, LPINT lpPolyCounts, i32 nCount, i32 nPolyFillMode)

   {

      m_pointa.remove_all();
      m_iaCount.remove_all();

      i32 n = 0;

      for(i32 i = 0; i < nCount; i++)
      {
         m_iaCount.add(pPolyCounts[i]);

         for(i32 j = 0; j < pPolyCounts[i]; j++)

         {
            m_pointa.add(pointd(pPoints[n].x, lpPoints[n].y));

            n++;
         }
      }

      m_etype = type_poly_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateRoundRectRgn(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3)
   {

      m_pointa.remove_all();
      m_iaCount.remove_all();

      m_pointa.add(pointd(x1, y1));
      m_pointa.add(pointd(x2, y2));
      m_pointa.add(pointd(x3, y3));

      m_etype = type_polygon;

      m_bUpdated = false;

      return TRUE;

   }

   bool region::CreateFromPath(::image * pimage)
   {
      UNREFERENCED_PARAMETER(pgraphics);
      ::exception::throw_interface_only();
   }

   #ifdef WINDOWS

   bool region::CreateFromData(const XFORM* pXForm, i32 nCount, const RGNDATA* pRgnData)

   {
      UNREFERENCED_PARAMETER(pXForm);

      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(pRgnData);
      ::exception::throw_interface_only();
   }

   i32 region::GetRegionData(LPRGNDATA pRgnData, i32 nDataSize) const

   {
      UNREFERENCED_PARAMETER(pRgnData);

      UNREFERENCED_PARAMETER(nDataSize);
      ::exception::throw_interface_only();
   }

   #endif

   void region::SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      ::exception::throw_interface_only();
   }

   void region::SetRectRgn(const ::rect & rect)

   {
      UNREFERENCED_PARAMETER(prect);

      ::exception::throw_interface_only();
   }

   i32 region::CombineRgn(const region* pRgn1, const region* pRgn2, i32 nCombineMode)
   {
      UNREFERENCED_PARAMETER(pRgn1);
      UNREFERENCED_PARAMETER(pRgn2);
      UNREFERENCED_PARAMETER(nCombineMode);
      ::exception::throw_interface_only();
   }

   i32 region::CopyRgn(const region* pRgnSrc)
   {
      UNREFERENCED_PARAMETER(pRgnSrc);
      ::exception::throw_interface_only();
   }

   bool region::EqualRgn(const region* pRgn) const
   {
      UNREFERENCED_PARAMETER(pRgn);
      ::exception::throw_interface_only();
   }

   i32 region::OffsetRgn(i32 x, i32 y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      ::exception::throw_interface_only();
   }

   i32 region::OffsetRgn(const ::point & point)
   {
      UNREFERENCED_PARAMETER(point);
      ::exception::throw_interface_only();
   }

   i32 region::GetRgnBox(RECT * prect) const

   {
      UNREFERENCED_PARAMETER(prect);

      ::exception::throw_interface_only();
   }

   i32 region::GetRgnBox(rect64 * prect) const

   {
      ::rect rect;
      i32 iRgn = GetRgnBox(rect);
      *prect = rect;

      return iRgn;
   }

   bool region::PtInRegion(i32 x, i32 y) const
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      ::exception::throw_interface_only();
   }

   bool region::PtInRegion(const ::point & point) const
   {
      UNREFERENCED_PARAMETER(point);
      ::exception::throw_interface_only();
   }

   bool region::RectInRegion(const ::rect & rect) const

   {
      UNREFERENCED_PARAMETER(prect);

      ::exception::throw_interface_only();
   }
   */


   //bool region::create_rect(i32 x1, i32 y1, i32 x2, i32 y2)
   //{

   //   if(m_etype != type_none)
   //   {

   //      destroy();

   //   }

   //   m_etype = type_rect;

   //   m_x1 = x1;
   //   m_y1 = y1;
   //   m_x2 = x2;
   //   m_y2 = y2;

   //   return true;


   //}

   bool region::create_rect(const ::rect & rect)

   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_rect;

      m_x1 = rect.left;

      m_y1 = rect.top;

      m_x2 = rect.right;

      m_y2 = rect.bottom;


      return true;


   }

   /*bool region::create_oval(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_oval;

      m_x1 = x1;
      m_y1 = y1;
      m_x2 = x2;
      m_y2 = y2;

      return true;

   }*/

   bool region::create_oval(const ::rect & rect)

   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_oval;

      m_x1 = rect.left;

      m_y1 = rect.top;

      m_x2 = rect.right;

      m_y2 = rect.bottom;


      return true;

   }


   bool region::create_polygon(const POINTD * ppoints, i32 nCount, ::draw2d::e_fill_mode efillmode)

   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_polygon;

      m_nCount = nCount;
      ::aura::del(m_lppoints);
      m_lppoints = new POINTD[m_nCount];
      ::memcpy_dup(m_lppoints, ppoints, sizeof(POINTD) * m_nCount);

      m_efillmode = efillmode;

      return true;
   }


   bool region::create_polygon(const POINT * ppoints, i32 nCount, ::draw2d::e_fill_mode efillmode)

   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_polygon;

      m_nCount = nCount;

      m_lppoints = new POINTD[m_nCount];

      for(index i = 0; i < m_nCount; i++)
      {

         m_lppoints[i].x = (double) ppoints[i].x;


         m_lppoints[i].y = (double) ppoints[i].y;


      }

      m_efillmode = efillmode;

      return true;

   }


   bool region::create_poly_polygon(const POINTD * ppoints, const i32 * ppolycounts, i32 nCount, ::draw2d::e_fill_mode efillmode)

   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_poly_polygon;

      m_nCount = nCount;

      m_lppolycounts = new INT[m_nCount];

      ::memcpy_dup(m_lppolycounts, ppolycounts, sizeof(INT) * m_nCount);


      i32 iTotalCount = 0;

      for(i32 i = 0; i < nCount; i++)
      {

         iTotalCount += m_lppolycounts[i];

      }

      m_lppoints = new POINTD[iTotalCount];

      ::memcpy_dup(m_lppoints, ppoints, sizeof(POINTD) * iTotalCount);


      m_efillmode = efillmode;

      return true;

   }


   bool region::create_poly_polygon(const POINT * ppoints, const i32 * ppolycounts,i32 nCount,::draw2d::e_fill_mode efillmode)

   {

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_poly_polygon;

      m_nCount = nCount;

      m_lppolycounts = new INT[m_nCount];

      ::memcpy_dup(m_lppolycounts,ppolycounts,sizeof(INT)* m_nCount);


      i32 iTotalCount = 0;

      for(i32 i = 0; i < nCount; i++)
      {

         iTotalCount += m_lppolycounts[i];

      }

      m_lppoints = new POINTD[iTotalCount];

      for(i32 i = 0; i < iTotalCount; i++)
      {

         m_lppoints[i].x = ppoints[i].x;


         m_lppoints[i].y = ppoints[i].y;


      }

      m_efillmode = efillmode;

      return true;

   }


   //virtual bool add_round_rect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3);
//      virtual bool add_path(::draw2d::path * ppath);

//      virtual void SetRectRgn(i32 x1, i32 y1, i32 x2, i32 y2);
//      virtual void SetRectRgn(const ::rect & rect);

   
   bool region::combine(const ::draw2d::region * prgn1, const ::draw2d::region * prgn2, e_combine ecombine, ::draw2d::graphics * pgraphics)
   {

      __pointer(::draw2d::region) pregion1 = (::draw2d::region *) prgn1;

      __pointer(::draw2d::region) pregion2 = (::draw2d::region *) prgn2;

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = type_combine;

      m_pregion1 = pregion1;

      m_pregion2 = pregion2;

      m_ecombine  = ecombine;

      return true;

   }

   region & region::operator = (const ::draw2d::region & regionSrc)
   {

      if(this == &regionSrc)
         return *this;

      if(m_etype != type_none)
      {

         destroy();

      }

      m_etype = regionSrc.m_etype;

      switch(m_etype)
      {
      case type_none:
         return *this;
      case type_rect:
      case type_oval:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         return *this;
      case type_polygon:
         m_nCount = regionSrc.m_nCount;
         m_lppoints = new POINTD[m_nCount];
         ::memcpy_dup(m_lppoints, regionSrc.m_lppoints, sizeof(POINTD) * m_nCount);
         m_efillmode = regionSrc.m_efillmode;
         return *this;
      case type_poly_polygon:
      {
         m_nCount = regionSrc.m_nCount;
         m_lppolycounts = new INT[m_nCount];
         ::memcpy_dup(m_lppolycounts, regionSrc.m_lppolycounts, sizeof(INT) * m_nCount);
         i32 iTotalCount = 0;
         for(i32 i = 0; i < m_nCount; i++)
         {
            iTotalCount += m_lppolycounts[i];
         }
         m_lppoints = new POINTD[iTotalCount];
         ::memcpy_dup(m_lppoints, regionSrc.m_lppoints, sizeof(POINTD) * iTotalCount);
         m_efillmode = regionSrc.m_efillmode;
      }
      return *this;
      case type_round_rect:
         m_x1 = regionSrc.m_x1;
         m_y1 = regionSrc.m_y1;
         m_x2 = regionSrc.m_x2;
         m_y2 = regionSrc.m_y2;
         m_x3 = regionSrc.m_x3;
         m_y3 = regionSrc.m_y3;
         return *this;
      case type_combine:
         m_pregion1 = new ::draw2d::region(*regionSrc.m_pregion1);
         m_pregion2 = new ::draw2d::region(*regionSrc.m_pregion2);
         m_ecombine = regionSrc.m_ecombine;
         return *this;
      default:
         ::exception::throw_not_implemented();
      };
      return *this;

   }


   bool region::get_bounding_box(RECT * prect, ::draw2d::graphics * pgraphics)
   {

      ::exception::throw_interface_only();

      return false;

   }


   bool region::contains(const POINTD & point, ::draw2d::graphics * pgraphics)
   {

      return internal_contains(point);

   }


   bool region::translate(const POINT & point, ::draw2d::graphics * pgraphics)
   {

      set_modified();

      switch(m_etype)
      {
      case type_none:
         return false;
      case type_round_rect:
         m_x3 += point.x;
         m_y3 += point.y;
      case type_rect:
      case type_oval:
         m_x1 += point.x;
         m_y1 += point.y;
         m_x2 += point.x;
         m_y2 += point.y;
         return true;
      case type_polygon:
         for(i32 i = 0; i < m_nCount; i++)
         {
            m_lppoints[i].x += point.x;
            m_lppoints[i].y += point.y;
         }
         return true;
      case type_poly_polygon:
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
      case type_combine:
      {
         bool bOk1 = m_pregion1->translate(point);
         bool bOk2 = m_pregion2->translate(point);
         return bOk1 && bOk2;
      }
      default:
         ::exception::throw_not_implemented();
      };
      return false;

   }


   bool region::contains(const POINT & point, ::draw2d::graphics * pgraphics)
   {

      return contains(pointd(point));

   }


   void region::max_bounding_box(RECT * prect, ::draw2d::graphics * pgraphics)
   {

      ::rectd rect;

      max_bounding_box(rect);

      __copy(prect,rect);

   }


   void region::max_bounding_box_rect(RECT * prect, ::draw2d::graphics * pgraphics)
   {

      ::rectd rect;

      max_bounding_box_rect(rect);

      __copy(prect,rect);


   }


   void region::max_bounding_box_oval(RECT * prect, ::draw2d::graphics * pgraphics)
   {

      ::rectd rect;

      max_bounding_box_oval(rect);

      __copy(prect,rect);


   }


   void region::max_bounding_box_polygon(RECT * prect, ::draw2d::graphics * pgraphics)
   {

      ::rectd rect;

      max_bounding_box_polygon(rect);

      __copy(prect,rect);

   }


   void region::max_bounding_box_poly_polygon(RECT * prect, ::draw2d::graphics * pgraphics)
   {

      ::rectd rect;

      max_bounding_box_poly_polygon(rect);

      __copy(prect,rect);


   }


   void region::max_bounding_box_combine(RECT * prect, ::draw2d::graphics * pgraphics)
   {

      ::rectd rect;

      max_bounding_box_combine(rect);

      __copy(prect,rect);


   }


   void region::max_bounding_box(RECTD * prect, ::draw2d::graphics * pgraphics)
   {

      switch(m_etype)
      {
      case type_none:
         return;
      case type_rect:
         return max_bounding_box_rect(prect);

      case type_oval:
         return max_bounding_box_oval(prect);

      case type_polygon:
         return max_bounding_box_polygon(prect);

      case type_poly_polygon:
         return max_bounding_box_poly_polygon(prect);

      case type_combine:
         return max_bounding_box_combine(prect);

      default:
         ::exception::throw_not_implemented();
      }

   }


   void region::max_bounding_box_rect(RECTD * prect, ::draw2d::graphics * pgraphics)
   {

      prect->left = MIN(prect->left,m_x1);

      prect->right = MAX(prect->right,m_x2);

      prect->top = MIN(prect->left,m_y1);

      prect->bottom = MAX(prect->right,m_y2);

   }


   void region::max_bounding_box_oval(RECTD * prect, ::draw2d::graphics * pgraphics)
   {

      prect->left = MIN(prect->left,m_x1);

      prect->right = MAX(prect->right,m_x2);

      prect->top = MIN(prect->left,m_y1);

      prect->bottom = MAX(prect->right,m_y2);

   }


   void region::max_bounding_box_polygon(RECTD * prect, ::draw2d::graphics * pgraphics)
   {

      if(m_nCount <= 0)
         return;

      for(int i = 0; i < m_nCount; i++)
      {

         prect->left = MIN(prect->left,m_lppoints[i].x);

         prect->right = MAX(prect->right,m_lppoints[i].x);

         prect->top = MIN(prect->left,m_lppoints[i].y);

         prect->bottom = MAX(prect->right,m_lppoints[i].y);


      }

   }


   void region::max_bounding_box_poly_polygon(RECTD * prect, ::draw2d::graphics * pgraphics)
   {

      i32 n = 0;

      for(i32 i = 0; i < m_nCount; i++)
      {

         i32 iCount = m_lppolycounts[i];

         for(int j = 0; j < iCount; j++,n++)
         {

            prect->left = MIN(prect->left,m_lppoints[n].x);

            prect->right = MAX(prect->right,m_lppoints[n].x);

            prect->top = MIN(prect->left,m_lppoints[n].y);

            prect->bottom = MAX(prect->right,m_lppoints[n].y);


         }

      }

   }


   void region::max_bounding_box_combine(RECTD * prect, ::draw2d::graphics * pgraphics)
   {

      m_pregion1->max_bounding_box(prect);

      m_pregion2->max_bounding_box(prect);

   }


   bool region::internal_contains(const POINTD & point)
   {

      switch(m_etype)
      {
      case type_none:
         return false;
      case type_rect:
         return internal_rect_contains(point);

      case type_oval:
         return internal_oval_contains(point);

      case type_polygon:
         return internal_polygon_contains(point);

      case type_poly_polygon:
         return internal_poly_polygon_contains(point);

      case type_combine:
         return internal_combine_contains(point);

      default:
         ::exception::throw_not_implemented();
      }

      return false;

   }


   bool region::internal_rect_contains(const POINTD & point)
   {

      return point.x >= m_x1 && point.y >= m_y1 && point.x <= m_x2 && point.y <= m_y2;

   }


   bool region::internal_oval_contains(const POINTD & point)
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


   bool region::internal_polygon_contains(const POINTD & point)
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


   bool region::internal_poly_polygon_contains(const POINTD & point)
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


   bool region::internal_combine_contains(const POINTD & point)
   {

      if(m_ecombine == ::draw2d::region::combine_add)
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
      else if(m_ecombine == ::draw2d::region::combine_exclude)
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
      else if(m_ecombine == ::draw2d::region::combine_intersect)
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
      else if(m_ecombine == ::draw2d::region::combine_xor)
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


   bool region::internal_contains(const POINT & point)
   {

      return internal_contains(pointd(point));

   }


   bool region::internal_rect_contains(const POINT & point)
   {

      return internal_rect_contains(pointd(point));

   }


   bool region::internal_oval_contains(const POINT & point)
   {

      return internal_oval_contains(pointd(point));

   }


   bool region::internal_polygon_contains(const POINT & point)
   {

      return internal_polygon_contains(pointd(point));

   }


   bool region::internal_poly_polygon_contains(const POINT & point)
   {

      return internal_poly_polygon_contains(pointd(point));

   }


   bool region::internal_combine_contains(const POINT & point)
   {

      return internal_combine_contains(pointd(point));

   }


} // namespace draw2d



