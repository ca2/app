#pragma once


#include "_function.h"
//#include "bounding_box.h"


//#include "_concept.h"


//#include "acme/prototype/collection/array.h"
////#include "acme/prototype/collection/comparable_eq_array.h"
////#include "acme/prototype/collection/comparable_array.h"


inline bool tolerance_is_equal(double tolerance, double d1, double d2)
{
   return ::abs(d1 - d2) <= tolerance;
}


template < primitive_number NUMBER >
class point_array_base :
   virtual public ::array < ::point_type < NUMBER > >
{
public:


   //using POINT_BASE_TYPE = POINT_TYPE;
   using UNIT_TYPE = NUMBER;
   //using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   //using RECTANGLE_TYPE = typename POINT_TYPE::RECTANGLE_TYPE;
   //using RECTANGLE_BASE_TYPE = typename RECTANGLE_TYPE::RECTANGLE_BASE_TYPE;


   inline point_array_base() : ::array < ::point_type < NUMBER > >() {}
   template < std::size_t n >
   inline point_array_base(const ::point_type < NUMBER > p[n]) : ::array < ::point_type < NUMBER > >(p, n){ }
   inline point_array_base(point_array_base && pointset) : ::array < ::point_type < NUMBER > >(::transfer(pointset)) { }
   inline point_array_base(const point_array_base & pointset) { operator=(pointset); }
   ~point_array_base() override { }


   //operator ::point_type < UNIT_TYPE > * () { return this->get_data(); }

   void offset(UNIT_TYPE x, UNIT_TYPE y);
   void offset(::point_type < UNIT_TYPE > point) { offset(point.x(), point.y()); }

   void rotate(double dAngle);

   void rotate(double dAngle, ::point_type < UNIT_TYPE > pointCenter);

   void expand_bounding_box(::point_type < UNIT_TYPE > & top_left, ::point_type < UNIT_TYPE > & bottom_right) const;

   bool get_bounding_box(::point_type < UNIT_TYPE > & top_left, ::point_type < UNIT_TYPE > & bottom_right) const;

   bool polygon_contains_winding(const ::point_type < UNIT_TYPE > & point) const;
   bool polygon_contains_alternate(const ::point_type < UNIT_TYPE > & point) const;

   inline ::collection::index add(UNIT_TYPE x, UNIT_TYPE y) { return ::array < ::point_type < NUMBER > >::add({x, y}); }
   inline ::collection::index add(const ::point_type < NUMBER > & point) { return ::array < ::point_type < NUMBER > >::add(point); }
   inline point_array_base & operator =(const point_array_base & pointset) { this->copy(pointset); return *this; }

   inline ::collection::index tolerance_add_unique(UNIT_TYPE tolerance, const ::point_type < NUMBER > & pointAdd)
   {

      for (auto & point : *this)
      {

         if (tolerance_is_equal(tolerance, point.x(), pointAdd.x()) && tolerance_is_equal(tolerance, point.y(), pointAdd.y()))
         {

            /// 'p' is "tolerance"-equal to an existing int_point 'p' in '*this' array,
            /// so don't add it.

            return -1;

         }

      }

      return ::array < ::point_type < NUMBER > >::add(pointAdd);

   }

   //virtual void xml_import(::xml::input_tree & xmlif);
   //virtual void xml_export(::xml::output_tree & xmlof);


   ::collection::count add_unique_range(const ::point_type < NUMBER > & pBeg, const ::point_type < NUMBER > & pointEnd, const ::size_type < NUMBER > & s = e_unit_size);
   //https://www.geeksforgeeks.org/area-of-a-int_polygon-with-given-n-ordered-vertices/
      // (X[i], Y[i]) are coordinates of i'th point.

   UNIT_TYPE polygon_area()
   {

      UNIT_TYPE area = (UNIT_TYPE) 0;

      int n = (int) this->get_count();

      // Calculate value of shoelace formula
      int j = n - 1;

      for (int i = 0; i < n; i++)
      {

         area += (this->element_at(j).x() + this->element_at(i).x())
               * (this->element_at(j).y() - this->element_at(i).y());

         j = i;  // j is previous vertex to i

      }

      return area / 2;

   }


   auto points_beyond_right(UNIT_TYPE x) const
   {

      return ::transfer(container_predicate_get(*this, [x](const ::point_type < NUMBER > & p) {return p.x() > x; }));

   }

   
   auto points_beyond_left(UNIT_TYPE x) const
   {

      return ::transfer(container_predicate_get(*this, [x](const ::point_type < NUMBER > & p) {return p.x() < x; }));

   }


   auto points_beyond_top(UNIT_TYPE y) const
   {

      return ::transfer(container_predicate_get(*this, [y](const ::point_type < NUMBER > & p) {return p.y() < y; }));

   }


   auto points_beyond_bottom(UNIT_TYPE y) const
   {

      return ::transfer(container_predicate_get(*this, [y](const ::point_type < NUMBER > & p) {return p.y() > y; }));

   }


   auto points_beyond_right() const
   {

      return this->points_beyond_right(this->first().x());

   }


   auto points_beyond_left() const
   {

      return this->points_beyond_left(this->first().x());

   }


   auto points_beyond_top() const
   {

      return this->points_beyond_top(this->first().y());

   }


   auto points_beyond_bottom() const
   {

      return this->points_beyond_bottom(this->first().y());

   }


};


   


template < primitive_number NUMBER >
void point_array_base < NUMBER >::offset(UNIT_TYPE x, UNIT_TYPE y)
{
   for (int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).x() += x;
      this->element_at(i).y() += y;
   }
}


template < primitive_number NUMBER >
void point_array_base < NUMBER >::rotate(double dAngle)
{

   UNIT_TYPE x;
   UNIT_TYPE y;
   double dCos = ::cos(dAngle);
   double dSin = ::sin(dAngle);

   for (int i = 0; i < this->get_count(); i++)
   {
      x = this->element_at(i).x();
      y = this->element_at(i).y();
      this->element_at(i).x() = (int)(x * dCos - y * dSin);
      this->element_at(i).y() = (int)(x * dSin + y * dCos);
   }

}




//
//template < typename POINT_TYPE >
//void point_array_base < POINT_TYPE >::get_bounding_box(RECTANGLE_BASE_TYPE & rectangle) const
//{
//
//   ::get_bounding_box(rectangle, this->get_data(), this->get_count());
//
//}



template < primitive_number NUMBER >
void point_array_base < NUMBER >::rotate(double dAngle, ::point_type < NUMBER > pointCenter)
{

   UNIT_TYPE x;
   UNIT_TYPE y;
   double dCos = cos(dAngle);
   double dSin = sin(dAngle);

   for (int i = 0; i < this->get_count(); i++)
   {
      this->element_at(i) -= pointCenter;
      x = this->element_at(i).x();
      y = this->element_at(i).y();
      this->element_at(i).x() = (int)(x * dCos - y * dSin);
      this->element_at(i).y() = (int)(x * dSin + y * dCos);
      this->element_at(i) += pointCenter;
   }

}


//template < typename POINT_TYPE >
//::xml::input_tree & operator >> (::xml::input_tree & xmlif, point_array_base < POINT_TYPE > & pointa);
//
//template < typename POINT_TYPE >
//::xml::output_tree & operator << (::xml::output_tree & xmlof, point_array_base < POINT_TYPE > & pointa);

/*
http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-int_point-is-within-a-int_polygon
int pnpoly(int nvert, float * vertx, float * verty, float testx, float testy)
{
   int i, j, c = 0;
   for (i = 0, j = nvert - 1; i < nvert; j = i++) {
      if (((verty[i] > testy) != (verty[j] > testy)) &&
         (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
         c = !c;
   }
   return c;
}
*/
//template < typename POINT_TYPE >
//bool polygon_contains_point(const POINT_TYPE * ppointa, ::collection::count c, const POINT_TYPE & point)
//{
//   int i, j, c = 0;
//   for (i = 0, j = nvert - 1; i < nvert; j = i++)
//   {
//      if (((ppointa[i].y() > point.y()) != (ppointa[j].y() > point.y())) &&
//         (point.x() < (ppointa[j].x() - ppointa[i].x()) * (point.y() - ppointa[i].y()) / (ppointa[j].y() - ppointa[i].y()) + ppointa[i].x()))
//         c = !c;
//   }
//   return c;
//}

template < primitive_number NUMBER >
bool point_array_base < NUMBER >::polygon_contains_winding(const ::point_type < NUMBER > & point) const
{

   return ::polygon_contains_winding( this->data(), (int)this->size(), point);

}


template < primitive_number NUMBER >
bool point_array_base < NUMBER >::polygon_contains_alternate(const ::point_type < NUMBER > & point) const
{

   return ::polygon_contains_alternate(this->data(), (int)this->size(), point, true);

}


template < primitive_number NUMBER >
::collection::count point_array_base < NUMBER >::add_unique_range(const ::point_type < NUMBER > & pointBeg, const ::point_type < NUMBER > & pointEnd, const ::size_type < NUMBER > & size)
{

   auto x1 = pointBeg.x();

   auto x2 = pointEnd.x();

   auto y1 = pointBeg.y();

   auto y2 = pointEnd.y();

   __sort(x1, x2);

   __sort(y1, y2);

   ::collection::count c = 0;

   for (auto x = x1; x <= x2; x += size.cx())
   {

      for (auto y = y1; y <= y2; y += size.cy())
      {

         if (this->add_unique(POINT_TYPE(x, y)))
         {

            c++;

         }

      }

   }

   return c;

}


template < primitive_number NUMBER >
void point_array_base < NUMBER >::expand_bounding_box(::point_type < UNIT_TYPE > & top_left, ::point_type < UNIT_TYPE > & bottom_right) const
{

   ::point_type < NUMBER > ::expand_bounding_box(top_left, bottom_right, this->data(), this->size());
   
}


template < primitive_number NUMBER >
bool point_array_base < NUMBER >::get_bounding_box(::point_type < UNIT_TYPE > & top_left, ::point_type < UNIT_TYPE > & bottom_right) const
{
   
   if(this->is_empty())
   {
      
      return false;
      
   }
   
   top_left = this->first();
   
   bottom_right = this->first();
   
   this->expand_bounding_box(top_left, bottom_right, this->element_at[1], this->count() - 1);
   
   return true;
   
}













