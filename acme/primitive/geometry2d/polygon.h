#pragma once


template < typename POINT_TYPE >
class polygon_base :
   virtual public point_array_base < POINT_TYPE >
{
public:

   using POLYGON_BASE_TYPE = point_array_base < POINT_TYPE >;
   using POINT_BASE_TYPE = typename POINT_TYPE::POINT_BASE_TYPE;
   using UNIT_TYPE = typename POINT_TYPE::UNIT_TYPE;
   using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   using RECT_TYPE = typename POINT_TYPE::RECT_TYPE;
   using RECT_BASE_TYPE = typename RECT_TYPE::RECT_BASE_TYPE;


   bool                 m_bDirty;

   bool                 m_bDirtyBoundingRect;
   RECT_TYPE            m_rectBounding;


   polygon_base();
   polygon_base(const polygon_base & polygon);
   polygon_base(polygon_base&& polygon);
   ~polygon_base();

   void set_rect(const RECT_TYPE & rect);


   void check_dirty()
   {

      if (m_bDirty)
      {
         m_bDirty = false;
         m_bDirtyBoundingRect = true;

      }

   }

   const RECT_TYPE & bounding_rect() const;

   bool overlaps(const polygon_base & polygon) const;

   polygon_base convex_intersection(const polygon_base & polygon) const;

   // sort clockwise
   void sort();

   bool bounding_rect_contains(const POINT_TYPE & point) const;

   polygon_base& operator = (const polygon_base& polygon);
   polygon_base& operator = (polygon_base&& polygon);


};

template < typename POINT_TYPE >
inline polygon_base < POINT_TYPE >::polygon_base(const polygon_base& polygon)
{
   operator = (polygon);

}

template < typename POINT_TYPE >
inline polygon_base < POINT_TYPE >::polygon_base(polygon_base&& polygon) :
   point_array_base < POINT_TYPE >(::move(polygon))
{
   
   m_bDirty = polygon.m_bDirty;
   m_bDirtyBoundingRect = polygon.m_bDirtyBoundingRect;
   m_rectBounding = polygon.m_rectBounding;

}

template < typename POINT_TYPE >
inline bool polygon_base < POINT_TYPE >::bounding_rect_contains(const POINT_TYPE & point) const
{

   return this->bounding_rect().contains(point);

}


inline double atan(const pointd & point, double x, double y)
{

   return ::atan2(point.y - y, point.x - x);

}




//https://www.swtestacademy.com/intersection-convex-polygons-algorithm/
// Sinan Oz is an experienced IT professional who has a big passion on software science and algorithms since he attended International Olympiads in Informatics in his early ages.He finished Istanbul Technical University Computer Engineering Department.He worked at Garanti Technology, one of the biggest technology centres in the country for about 5 years.After that, he started Kariyer.net and takes some serious projects as a Lead Architect and he promoted as a Software Development Manager.Currently, he is working at Movie Star Planet Kopenhagen office as a Senior Backend Game Developer.
template < typename POINT_TYPE >
void polygon_base < POINT_TYPE >::sort()
{
   UNIT_TYPE x = 0;
   UNIT_TYPE y = 0;
   for (auto & point : *this)
   {
      x += point.x;
      y += point.y;
   }
   x /= this->get_count();
   y /= this->get_count();

   this->pred_sort([x, y](auto & point1, auto & point2) { return atan(point1, x, y) >= atan(point2, x, y); });
}


template < typename POINT_TYPE >
polygon_base<POINT_TYPE> & polygon_base < POINT_TYPE >::operator = (const polygon_base& polygon)
{

   if (&polygon != this)
   {

      point_array_base < POINT_TYPE >::operator = (polygon);
      m_bDirty = polygon.m_bDirty;
      m_bDirtyBoundingRect = polygon.m_bDirtyBoundingRect;
      m_rectBounding = polygon.m_rectBounding;

   }

   return *this;

}

template < typename POINT_TYPE >
polygon_base<POINT_TYPE>& polygon_base < POINT_TYPE >::operator = (polygon_base&& polygon)
{

   if (&polygon != this)
   {

      point_array_base < POINT_TYPE >::operator = (::move(polygon));
      m_bDirty = polygon.m_bDirty;
      m_bDirtyBoundingRect = polygon.m_bDirtyBoundingRect;
      m_rectBounding = polygon.m_rectBounding;

   }

   return *this;

}

inline bool line_intersection(pointd & point, const pointd & pt1, const pointd & pt2, const pointd & pt3, const pointd & pt4);




//https://rbrundritt.wordpress.com/2008/10/20/approximate-points-of-intersection-of-two-line-segments/
//latlong1 and latlong2 represent two coordinates that make up the bounded box
//latlong3 is a point that we are checking to see is inside the box
inline bool inBoundedBox(const pointd & pt1, const pointd & pt2, const pointd & pt3)
{

   double dSpan = 0.01;

   if (pt1.x < pt2.x)
   {

      if (!(pt1.x - dSpan <= pt3.x && pt3.x <= pt2.x + dSpan))
      {

         return false;

      }

   }
   else
   {

      if (!(pt2.x - dSpan <= pt3.x && pt3.x <= pt1.x + dSpan))
      {

         return false;

      }

   }

   if (pt1.y < pt2.y)
   {

      if (!(pt1.y - dSpan <= pt3.y && pt3.y <= pt2.y + dSpan))
      {

         return false;

      }

   }
   else
   {

      if (!(pt2.y - dSpan <= pt3.y && pt3.y <= pt1.y + dSpan))
      {

         return false;

      }

   }

   return true;

}

inline bool inBoundedBox1(const pointd & pt1, const pointd & pt2, const pointd & pt3)
{

   if (pt1.x < pt2.x)
   {

      if (!(pt1.x <= pt3.x && pt3.x <= pt2.x))
      {

         return false;

      }

   }
   else
   {

      if (!(pt2.x <= pt3.x && pt3.x <= pt1.x))
      {

         return false;

      }

   }

   if (pt1.y < pt2.y)
   {

      if (!(pt1.y <= pt3.y && pt3.y <= pt2.y))
      {

         return false;

      }

   }
   else
   {

      if (!(pt2.y <= pt3.y && pt3.y <= pt1.y))
      {

         return false;

      }

   }

   return true;

}


//https://rbrundritt.wordpress.com/2008/10/20/approximate-points-of-intersection-of-two-line-segments/
inline bool line_intersection(pointd & point, const pointd & pt1, const pointd & pt2, const pointd & pt3, const pointd & pt4)
{

   //Line segment 1 (point1, point2)
   double A1 = pt2.x - pt1.x;
   double B1 = pt1.y - pt2.y;
   double C1 = A1 * pt1.y + B1 * pt1.x;

   //Line segment 2 (p3,  p4)
   double A2 = pt4.x - pt3.x;
   double B2 = pt3.y - pt4.y;
   double C2 = A2 * pt3.y + B2 * pt3.x;

   double determinant = A1 * B2 - A2 * B1;

   if (determinant != 0.0)
   {

      point.y = (B2 * C1 - B1 * C2) / determinant;

      point.x = (A1 * C2 - A2 * C1) / determinant;

      return inBoundedBox(pt1, pt2, point) && inBoundedBox(pt3, pt4, point);

   }

   // lines are parallel;
   return false;

}


inline void get_intersection_points(pointd_array & pa, const pointd & point1, const pointd & point2, const pointd_array & paPolygon)
{

   pointd point;

   for (iptr i = 0; i < paPolygon.get_count(); i++)
   {

      if (line_intersection(point, point1, point2, i % paPolygon, (i + 1) % paPolygon))
      {

         pa.tolerance_add_unique(0.001, point);

      }

   }

}


template < typename POINT_TYPE >
polygon_base < POINT_TYPE >::polygon_base()
{

   m_bDirty = false;

   m_bDirtyBoundingRect = false;

}


template < typename POINT_TYPE >
polygon_base < POINT_TYPE >::~polygon_base()

{

}


template < typename POINT_TYPE >
void polygon_base < POINT_TYPE >::set_rect(const RECT_TYPE & rect)
{

   m_rectBounding = rect;

   this->set_size(4);

   this->element_at(0) = m_rectBounding.top_left();
   this->element_at(1) = m_rectBounding.top_right();
   this->element_at(2) = m_rectBounding.bottom_right();
   this->element_at(3) = m_rectBounding.bottom_left();

   m_bDirty = false;
   m_bDirtyBoundingRect = false;

}


template < typename POINT_TYPE >
const typename polygon_base < POINT_TYPE >::RECT_TYPE & polygon_base < POINT_TYPE >::bounding_rect() const
{

   ((polygon_base *)this)->check_dirty();

   if (m_bDirtyBoundingRect && this->has_elements())
   {

      ((polygon_base *)this)->m_bDirtyBoundingRect = false;

      ((polygon_base *)this)->m_rectBounding.left = this->element_at(0).x;
      ((polygon_base *)this)->m_rectBounding.top = this->element_at(0).y;
      ((polygon_base *)this)->m_rectBounding.right = this->element_at(0).x;
      ((polygon_base *)this)->m_rectBounding.bottom = this->element_at(0).y;

      for (index i = 1; i < this->get_count(); i++)
      {

         ((polygon_base *)this)->m_rectBounding.left = min(m_rectBounding.left, this->element_at(i).x);
         ((polygon_base *)this)->m_rectBounding.right = max(m_rectBounding.right, this->element_at(i).x);
         ((polygon_base *)this)->m_rectBounding.top = min(m_rectBounding.top, this->element_at(i).y);
         ((polygon_base *)this)->m_rectBounding.bottom = max(m_rectBounding.bottom, this->element_at(i).y);

      }

   }

   return m_rectBounding;

}


template < typename POINT_TYPE >
bool polygon_base < POINT_TYPE >::overlaps(const polygon_base & polygon) const
{

   if (this->get_count() >= 3 && polygon.get_count() >= 3)
   {

      const rectd & r1 = bounding_rect();

      const rectd & r2 = polygon.bounding_rect();

      if (!r1.intersects(r2))
      {

         return false;

      }

      ::count c1 = this->get_count();

      ::count c2 = polygon.get_count();


      for (int i = 0; i < c1; i++)
      {

         if (polygon.polygon_contains(this->element_at(i)))
         {

            return true;

         }

      }

      for (int i = 0; i < c2; i++)
      {

         if (this->polygon_contains(polygon[i]))
         {

            return true;

         }

      }


      pointd point;

      for (int i = 0; i < c1; i++)
      {

         for (int k = 0; k < c2; k++)
         {

            if (line_intersection(point, this->element_at(i), this->element_at((i + 1) % c1), polygon[k], polygon[(k + 1) % c2]))
            {

               return true;

            }

         }

      }

   }

   return false;

}



template < typename POINT_TYPE >
polygon_base < POINT_TYPE > polygon_base < POINT_TYPE >::convex_intersection(const polygon_base & polygon) const
{

   ::count c1 = this->get_count();

   ::count c2 = polygon.get_count();

   polygon_base polygonResult;

   if (c1 >= 3 && c2 >= 3)
   {

      //Add  the corners of poly1 which are inside poly2
      for (int i = 0; i < c1; i++)
      {

         if (polygon.polygon_contains(this->element_at(i)))
         {

            polygonResult.tolerance_add_unique(0.001, this->element_at(i));

         }

      }

      for (int i = 0; i < c2; i++)
      {

         if (this->polygon_contains(polygon[i]))
         {

            polygonResult.tolerance_add_unique(0.001, polygon[i]);

         }

      }

      for (int i = 0; i < this->get_count(); i++)
      {

         get_intersection_points(polygonResult, i % *this, (i + 1) % *this, polygon);

      }

      polygonResult.sort();

      polygonResult.m_bDirty = polygonResult.has_elements();

   }

   return polygonResult;

}



using polygon = polygon_base < point >;
using polygon64 = polygon_base < point64 >;
using polygonf = polygon_base < pointf >;
using polygond = polygon_base < pointd >;
