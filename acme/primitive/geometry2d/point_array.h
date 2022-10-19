#pragma once


inline bool tolerance_is_equal(double tolerance, double d1, double d2)
{
   return ::abs(d1 - d2) <= tolerance;
}


template < typename POINT_TYPE >
class point_array_base :
   virtual public comparable_array < POINT_TYPE >
{
public:


   using POINT_BASE_TYPE = typename POINT_TYPE::POINT_BASE_TYPE;
   using UNIT_TYPE = typename POINT_TYPE::UNIT_TYPE;
   using SIZE_TYPE = typename POINT_TYPE::SIZE_TYPE;
   using RECTANGLE_TYPE = typename POINT_TYPE::RECTANGLE_TYPE;
   using RECTANGLE_BASE_TYPE = typename RECTANGLE_TYPE::RECTANGLE_BASE_TYPE;


   inline point_array_base() : comparable_array < POINT_TYPE >() {}
   template < std::size_t n >
   inline point_array_base(const POINT_TYPE p[n]) : comparable_array < POINT_TYPE >(p, n){ }
   inline point_array_base(point_array_base && pointset) : comparable_array < POINT_TYPE >(::move(pointset)) { }
   inline point_array_base(const point_array_base & pointset) { operator=(pointset); }
   virtual ~point_array_base() { }


   operator POINT_BASE_TYPE * () { return this->get_data(); }

   void offset(UNIT_TYPE x, UNIT_TYPE y);
   void offset(POINT_TYPE point) { offset(point.x, point.y); }

   void rotate(double dAngle);

   void rotate(double dAngle, POINT_TYPE pointCenter);

   void get_bounding_rectangle(RECTANGLE_BASE_TYPE & rectangle) const;

   bool polygon_contains(const POINT_TYPE & point) const;

   inline index add(UNIT_TYPE x, UNIT_TYPE y) { return comparable_array < POINT_TYPE >::add(POINT_TYPE(x, y)); }
   inline index add(const POINT_TYPE & point) { return comparable_array < POINT_TYPE >::add(POINT_TYPE(point)); }
   inline point_array_base & operator =(const point_array_base & pointset) { this->copy(pointset); return *this; }

   inline index tolerance_add_unique(UNIT_TYPE tolerance, const POINT_TYPE & pointAdd)
   {

      for (auto & point : *this)
      {

         if (tolerance_is_equal(tolerance, point.x, pointAdd.x) && tolerance_is_equal(tolerance, point.y, pointAdd.y))
         {

            /// 'p' is "tolerance"-equal to an existing point_i32 'p' in '*this' array,
            /// so don't add it.

            return -1;

         }

      }

      return comparable_array < POINT_TYPE >::add(pointAdd);

   }

   //virtual void xml_import(::xml::input_tree & xmlif);
   //virtual void xml_export(::xml::output_tree & xmlof);


   ::count add_unique_range(const POINT_TYPE & pBeg, const POINT_TYPE & pointEnd, const SIZE_TYPE & s = e_unit_size);
   //https://www.geeksforgeeks.org/area-of-a-polygon_i32-with-given-n-ordered-vertices/
      // (X[i], Y[i]) are coordinates of i'th point.

   UNIT_TYPE polygon_area()
   {

      UNIT_TYPE area = (UNIT_TYPE) 0;

      int n = (int) this->get_count();

      // Calculate value of shoelace formula
      int j = n - 1;

      for (int i = 0; i < n; i++)
      {

         area += (this->element_at(j).x + this->element_at(i).x)
               * (this->element_at(j).y - this->element_at(i).y);

         j = i;  // j is previous vertex to i

      }

      return area / 2;

   }

};




template < typename POINT_TYPE >
void point_array_base < POINT_TYPE >::offset(UNIT_TYPE x, UNIT_TYPE y)
{
   for (i32 i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).x += x;
      this->element_at(i).y += y;
   }
}


template < typename POINT_TYPE >
void point_array_base < POINT_TYPE >::rotate(double dAngle)
{

   UNIT_TYPE x;
   UNIT_TYPE y;
   double dCos = ::cos(dAngle);
   double dSin = ::sin(dAngle);

   for (i32 i = 0; i < this->get_count(); i++)
   {
      x = this->element_at(i).x;
      y = this->element_at(i).y;
      this->element_at(i).x = (::i32)(x * dCos - y * dSin);
      this->element_at(i).y = (::i32)(x * dSin + y * dCos);
   }

}





template < typename POINT_TYPE >
void point_array_base < POINT_TYPE >::get_bounding_rectangle(RECTANGLE_BASE_TYPE & prectangle) const
{

   ::get_bounding_rectangle(rectangle, this->get_data(), this->get_count());

}



template < typename POINT_TYPE >
void point_array_base < POINT_TYPE >::rotate(double dAngle, POINT_TYPE pointCenter)
{

   UNIT_TYPE x;
   UNIT_TYPE y;
   double dCos = cos(dAngle);
   double dSin = sin(dAngle);

   for (i32 i = 0; i < this->get_count(); i++)
   {
      this->element_at(i) -= pointCenter;
      x = this->element_at(i).x;
      y = this->element_at(i).y;
      this->element_at(i).x = (::i32)(x * dCos - y * dSin);
      this->element_at(i).y = (::i32)(x * dSin + y * dCos);
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
https://stackoverflow.com/questions/217578/how-can-i-determine-whether-a-2d-point_i32-is-within-a-polygon_i32
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
//bool polygon_contains_point(const POINT_TYPE * ppointa, ::count c, const POINT_TYPE & point)
//{
//   int i, j, c = 0;
//   for (i = 0, j = nvert - 1; i < nvert; j = i++)
//   {
//      if (((ppointa[i].y > point.y) != (ppointa[j].y > point.y)) &&
//         (point.x < (ppointa[j].x - ppointa[i].x) * (point.y - ppointa[i].y) / (ppointa[j].y - ppointa[i].y) + ppointa[i].x))
//         c = !c;
//   }
//   return c;
//}

template < typename POINT_TYPE >
bool point_array_base < POINT_TYPE >::polygon_contains(const POINT_TYPE & point) const
{

   return ::polygon_contains_point( this->get_data(), (int)this->get_size(), point);

}


template < typename POINT_TYPE >
::count point_array_base < POINT_TYPE >::add_unique_range(const POINT_TYPE & pointBeg, const POINT_TYPE & pointEnd, const SIZE_TYPE & size)
{

   typename POINT_TYPE::TYPE x1 = pointBeg.x;

   typename POINT_TYPE::TYPE x2 = pointEnd.x;

   typename POINT_TYPE::TYPE y1 = pointBeg.y;

   typename POINT_TYPE::TYPE y2 = pointEnd.y;

   __sort(x1, x2);

   __sort(y1, y2);

   ::count c = 0;

   for (typename POINT_TYPE::TYPE x = x1; x <= x2; x += size.cx)
   {

      for (typename POINT_TYPE::TYPE y = y1; y <= y2; y += size.cy)
      {

         if (this->add_unique(POINT_TYPE(x, y)))
         {

            c++;

         }

      }

   }

   return c;

}











using point_i32_array = point_array_base < point_i32 >;
using point_i64_array = point_array_base < point_i64 >;
using point_f64_array = point_array_base < point_f64 >;





