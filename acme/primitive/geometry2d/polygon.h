#pragma once


//#include "_collection.h"
//#include "_geometry2d.h"
#include "point_array.h"


template < primitive_number NUMBER >
class polygon_type :
   virtual public point_array_base < NUMBER >
{
public:


   //using POLYGON_BASE_TYPE = point_array_base < NUMBER >;
   //using POINT_BASE_TYPE = POINT_TYPE;
   using UNIT_TYPE = NUMBER;
   //using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   //using RECTANGLE_TYPE = typename POINT_TYPE::RECTANGLE_TYPE;
   //using RECTANGLE_BASE_TYPE = typename RECTANGLE_TYPE::RECTANGLE_BASE_TYPE;


   bool                          m_bDirty;
   bool                          m_bDirtyBoundingRect;
   ::rectangle_type < NUMBER >   m_rectangleBounding;


   polygon_type();
   polygon_type(const polygon_type & polygon_i32);
   polygon_type(polygon_type&& polygon_i32);
   ~polygon_type();

   void set_rect(const ::rectangle_type < NUMBER > & rectangle);


   void check_dirty()
   {

      if (m_bDirty)
      {
         m_bDirty = false;
         m_bDirtyBoundingRect = true;

      }

   }

   const ::rectangle_type < NUMBER > & bounding_rect() const;

   bool overlaps(const polygon_type & polygon_i32) const;

   polygon_type convex_intersection(const polygon_type & polygon) const;

   // sort clockwise
   void sort();

   bool bounding_rectangle_contains(const ::point_type < NUMBER > & point) const;
   
   bool contains(const ::point_type < NUMBER > & point) const
   {
    
      return point_array_base < NUMBER >::polygon_contains_winding(point);
    
   }

   bool contains_alternate(const ::point_type < NUMBER > & point) const
   {

      return point_array_base < NUMBER >::polygon_contains_alternate(point);

   }

   polygon_type& operator = (const polygon_type& polygon_i32);
   polygon_type& operator = (polygon_type&& polygon_i32);



};

template < primitive_number NUMBER >
inline polygon_type < NUMBER >::polygon_type(const polygon_type& polygon) :
point_array_base < NUMBER >(polygon)
{

}

template < primitive_number NUMBER >
inline polygon_type < NUMBER >::polygon_type(polygon_type&& polygon) :
   point_array_base < NUMBER >(::transfer(polygon))
{
   
   m_bDirty = polygon.m_bDirty;
   m_bDirtyBoundingRect = polygon.m_bDirtyBoundingRect;
   m_rectangleBounding = polygon.m_rectangleBounding;

}

template < primitive_number NUMBER >
inline bool polygon_type < NUMBER >::bounding_rectangle_contains(const ::point_type < NUMBER > & point) const
{

   return this->bounding_rect().contains(point);

}


inline double atan(const point_f64 & point, double x, double y)
{

   return ::atan2(point.y() - y, point.x() - x);

}

//https://www.swtestacademy.com/intersection-convex-polygons-algorithm/
// Sinan Oz is an experienced IT professional who has a big passion on software science and algorithms since he attended International Olympiads in Informatics in his early ages.He finished Istanbul Technical University Computer Engineering Department.He worked at Garanti Technology, one of the biggest technology centres in the country for about 5 years.After that, he started Kariyer.net and takes some serious projects as a Lead Architect and he promoted as a Software Development Manager.Currently, he is working at Movie Star Planet Kopenhagen office as a Senior Backend Game Developer.
template < primitive_number NUMBER >
void polygon_type < NUMBER >::sort()
{
   
   UNIT_TYPE x = 0;
   UNIT_TYPE y = 0;
   
   for (auto & point : *this)
   {
      x += point.x();
      y += point.y();
   }
   
   x /= this->get_count();
   y /= this->get_count();

   this->predicate_sort([x, y](auto & point1, auto & point2) { return atan(point1, x, y) >= atan(point2, x, y); });
   
}


template < primitive_number NUMBER >
polygon_type < NUMBER > & polygon_type < NUMBER >::operator = (const polygon_type& polygon)
{

   if (&polygon != this)
   {

      point_array_base < NUMBER >::operator = (polygon);
      m_bDirty = polygon.m_bDirty;
      m_bDirtyBoundingRect = polygon.m_bDirtyBoundingRect;
      m_rectangleBounding = polygon.m_rectangleBounding;

   }

   return *this;

}


template < primitive_number NUMBER >
polygon_type < NUMBER > & polygon_type < NUMBER >::operator = (polygon_type&& polygon)
{

   if (&polygon != this)
   {

      point_array_base < NUMBER >::operator = (::transfer(polygon));
      m_bDirty = polygon.m_bDirty;
      m_bDirtyBoundingRect = polygon.m_bDirtyBoundingRect;
      if(!m_bDirtyBoundingRect)
      {
         m_rectangleBounding = polygon.m_rectangleBounding;
      }

   }

   return *this;

}


inline bool line_intersection(point_f64 & point, const point_f64 & pt1, const point_f64 & pt2, const point_f64 & pt3, const point_f64 & pt4);


//https://rbrundritt.wordpress.com/2008/10/20/approximate-points-of-intersection-of-two-line-segments/
//latlong1 and latlong2 represent two coordinates that make up the bounded box
//latlong3 is a point_i32 that we are checking to see is inside the box
inline bool inBoundedBox(const point_f64 & pt1, const point_f64 & pt2, const point_f64 & pt3)
{

   double dSpan = 0.01;

   if (pt1.x() < pt2.x())
   {

      if (!(pt1.x() - dSpan <= pt3.x() && pt3.x() <= pt2.x() + dSpan))
      {

         return false;

      }

   }
   else
   {

      if (!(pt2.x() - dSpan <= pt3.x() && pt3.x() <= pt1.x() + dSpan))
      {

         return false;

      }

   }

   if (pt1.y() < pt2.y())
   {

      if (!(pt1.y() - dSpan <= pt3.y() && pt3.y() <= pt2.y() + dSpan))
      {

         return false;

      }

   }
   else
   {

      if (!(pt2.y() - dSpan <= pt3.y() && pt3.y() <= pt1.y() + dSpan))
      {

         return false;

      }

   }

   return true;

}

inline bool inBoundedBox1(const point_f64 & pt1, const point_f64 & pt2, const point_f64 & pt3)
{

   if (pt1.x() < pt2.x())
   {

      if (!(pt1.x() <= pt3.x() && pt3.x() <= pt2.x()))
      {

         return false;

      }

   }
   else
   {

      if (!(pt2.x() <= pt3.x() && pt3.x() <= pt1.x()))
      {

         return false;

      }

   }

   if (pt1.y() < pt2.y())
   {

      if (!(pt1.y() <= pt3.y() && pt3.y() <= pt2.y()))
      {

         return false;

      }

   }
   else
   {

      if (!(pt2.y() <= pt3.y() && pt3.y() <= pt1.y()))
      {

         return false;

      }

   }

   return true;

}


//https://rbrundritt.wordpress.com/2008/10/20/approximate-points-of-intersection-of-two-line-segments/
inline bool line_intersection(point_f64 & point, const point_f64 & pt1, const point_f64 & pt2, const point_f64 & pt3, const point_f64 & pt4)
{

   //Line segment 1 (point1, point2)
   double A1 = pt2.x() - pt1.x();
   double B1 = pt1.y() - pt2.y();
   double C1 = A1 * pt1.y() + B1 * pt1.x();

   //Line segment 2 (p3,  p4)
   double A2 = pt4.x() - pt3.x();
   double B2 = pt3.y() - pt4.y();
   double C2 = A2 * pt3.y() + B2 * pt3.x();

   double determinant = A1 * B2 - A2 * B1;

   if (determinant != 0.0)
   {

      point.y() = (B2 * C1 - B1 * C2) / determinant;

      point.x() = (A1 * C2 - A2 * C1) / determinant;

      return inBoundedBox(pt1, pt2, point) && inBoundedBox(pt3, pt4, point);

   }

   // lines are parallel;
   return false;

}


inline void get_intersection_points(point_f64_array & pa, const point_f64 & point1, const point_f64 & point2, const point_f64_array & paPolygon)
{

   point_f64 point;

   for (iptr i = 0; i < paPolygon.get_count(); i++)
   {

      if (line_intersection(point, point1, point2, i % paPolygon, (i + 1) % paPolygon))
      {

         pa.tolerance_add_unique(0.001, point);

      }

   }

}


template < primitive_number NUMBER >
polygon_type < NUMBER >::polygon_type()
{

   m_bDirty = false;

   m_bDirtyBoundingRect = false;

}


template < primitive_number NUMBER >
polygon_type < NUMBER >::~polygon_type()
{

}


template < primitive_number NUMBER >
void polygon_type < NUMBER >::set_rect(const ::rectangle_type < NUMBER > & rectangle)
{

   m_rectangleBounding = rectangle;

   this->set_size(4);

   this->element_at(0) = m_rectangleBounding.top_left();
   this->element_at(1) = m_rectangleBounding.top_right();
   this->element_at(2) = m_rectangleBounding.bottom_right();
   this->element_at(3) = m_rectangleBounding.bottom_left();

   m_bDirty = false;
   m_bDirtyBoundingRect = false;

}


template < primitive_number NUMBER >
const ::rectangle_type < NUMBER > & polygon_type < NUMBER >::bounding_rect() const
{

   ((polygon_type *)this)->check_dirty();

   if (m_bDirtyBoundingRect && this->has_elements())
   {

      ((polygon_type *)this)->m_bDirtyBoundingRect = false;
      
      ::get_bounding_box(((polygon_type *)this)->m_rectangleBounding, *this);

//      ((polygon_base *)this)->m_rectangleBounding.left = this->element_at(0).x();
//      ((polygon_base *)this)->m_rectangleBounding.top = this->element_at(0).y();
//      ((polygon_base *)this)->m_rectangleBounding.right = this->element_at(0).x();
//      ((polygon_base *)this)->m_rectangleBounding.bottom = this->element_at(0).y();
//
//      for (index i = 1; i < this->get_count(); i++)
//      {
//
//         ((polygon_base *)this)->m_rectangleBounding.left = minimum(m_rectangleBounding.left, this->element_at(i).x());
//         ((polygon_base *)this)->m_rectangleBounding.right = maximum(m_rectangleBounding.right, this->element_at(i).x());
//         ((polygon_base *)this)->m_rectangleBounding.top = minimum(m_rectangleBounding.top, this->element_at(i).y());
//         ((polygon_base *)this)->m_rectangleBounding.bottom = maximum(m_rectangleBounding.bottom, this->element_at(i).y());

//      }

   }

   return m_rectangleBounding;

}


template < primitive_number NUMBER >
bool polygon_type < NUMBER >::overlaps(const polygon_type & polygon) const
{

   if (this->get_count() >= 3 && polygon.get_count() >= 3)
   {

      auto & r1 = bounding_rect();

      auto & r2 = polygon.bounding_rect();

      if (!r1.intersects(r2))
      {

         return false;

      }

      ::count c1 = this->get_count();

      ::count c2 = polygon.get_count();

      for (int i = 0; i < c1; i++)
      {

         if (polygon.contains(this->element_at(i)))
         {

            return true;

         }

      }

      for (int i = 0; i < c2; i++)
      {

         if (this->contains(polygon[i]))
         {

            return true;

         }

      }

      point_f64 point;

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


template < primitive_number NUMBER >
polygon_type < NUMBER > polygon_type < NUMBER >::convex_intersection(const polygon_type & polygon_i32) const
{

   ::count c1 = this->get_count();

   ::count c2 = polygon_i32.get_count();

   polygon_type polygonResult;

   if (c1 >= 3 && c2 >= 3)
   {

      //Add  the corners of poly1 which are inside poly2
      for (int i = 0; i < c1; i++)
      {

         if (polygon_i32.polygon_contains(this->element_at(i)))
         {

            polygonResult.tolerance_add_unique(0.001, this->element_at(i));

         }

      }

      for (int i = 0; i < c2; i++)
      {

         if (this->polygon_contains(polygon_i32[i]))
         {

            polygonResult.tolerance_add_unique(0.001, polygon_i32[i]);

         }

      }

      for (int i = 0; i < this->get_count(); i++)
      {

         get_intersection_points(polygonResult, i % *this, (i + 1) % *this, polygon_i32);

      }

      polygonResult.sort();

      polygonResult.m_bDirty = polygonResult.has_elements();

   }

   return polygonResult;

}


template < primitive_number NUMBER >
class poly_polygon_type :
   public ::pointer_array < ::polygon_type < NUMBER > >
{
public:
   
   
   using UNIT_TYPE = NUMBER;
   
   
   using ::pointer_array < ::polygon_type < NUMBER > >::pointer_array;
   
   
   void expand_bounding_box(::point_type < UNIT_TYPE > & top_left, ::point_type < UNIT_TYPE > & bottom_right)
   {
      
      for(auto & ppolygon : *this)
      {
         
         ppolygon->expand_bounding_box(top_left, bottom_right);
         
      }
      
   }
   
   
};



