#pragma once


#include "acme/prototype/geometry/sequence.h"




template < prototype_number NUMBER >
class point_type :
   public sequence_type < NUMBER, 2 >
{
public:


   using UNIT_TYPE = NUMBER;
   //using SIZE_TYPE = size_type < NUMBER >;
   //using RECTANGLE_TYPE = rectangle_type < NUMBER >;

   
   ///using sequence_type < NUMBER, 2 >::sequence_type;
   
   
   constexpr point_type() {}
   point_type(no_initialize_t) : sequence_type < NUMBER, 2 >(no_initialize_t{}) {}



   consteval point2_t semantic_t() const { return {}; }

   //point_type(nullptr_t) : sequence_type < NUMBER, 2 >(nullptr) {}

//   sequence_type(const sequence_type&) = default;

//   template <prototype_number T,
//      std::enable_if_t<T::SIZE == SIZE &&
//      std::is_same_v<typename T::COORDINATE, COORDINATE>, int> = 0>
   template < prototype_number A >
   constexpr point_type(A a)
   {
   
      this->set_all(a);
      
   }
   
   template < prototype_number X, prototype_number Y >
   constexpr point_type(X x, Y y)
   {
      this->m_coordinatea[0] = (UNIT_TYPE) x;
      this->m_coordinatea[1] = (UNIT_TYPE) y;
   }
   
   template < prototype_number NUMBER1 >
   constexpr point_type(const sequence_type < NUMBER1, 2 > & sequence) :
      sequence_type < UNIT_TYPE, 2 >(sequence)
   {
      
   }
   

   constexpr point_type(const lparam & lparam);


//   sequence_type(COORDINATE s) {
//      for (size_t i = 0; i < SIZE; ++i)
//         m_coordinatea[i] = s;
//   }


//   void set_all(COORDINATE coordinate)
//   {
//
//      for (size_t i = 0; i < SIZE; ++i)
//      {
//
//         m_coordinatea[i] = coordinate;
//
//      }
//
//   }


//   point_type() noexcept { this->x = (UNIT_TYPE)0; this->y = (UNIT_TYPE)0; }
//   point_type(no_initialize_t) noexcept {  }
//   point_type(nullptr_t) noexcept { this->x = (UNIT_TYPE)0; this->y = (UNIT_TYPE)0; }
//   point_type(UNIT_TYPE x, UNIT_TYPE y) noexcept { this->x = x; this->y = y; }
//   ///point_type(const ::lparam& lparam) noexcept : point_type(lparam.x, lparam.y) {}
//   //point_type(const unsigned int u) noexcept : point_type((UNIT_TYPE) u32_x(u), (UNIT_TYPE)u32_y(u)) {}
//   //point_type(const unsigned long long u) noexcept : point_type((UNIT_TYPE)u64_x(u), (UNIT_TYPE)u64_y(u)) {}
//   //point_type(const SIZE_TYPE & size) noexcept : point_type(size.cx, size.cy) {}
//
//
////   template < raw_primitive_point POINT >
////   point_type(const POINT & point)
////   {
////
////      this->x = (UNIT_TYPE) point.x;
////      this->y = (UNIT_TYPE) point.y
////
////   }
//
//
//   point_type(const sequence_type < UNIT_TYPE, 2 > & sequence)
//   {
//
//      this->x = sequence.x;
//      this->y = sequence.y;
//
//   }
//
//
////   template < prototype_size SIZE >
////   point_type(const SIZE & size)
////   {
////
////      this->x = (UNIT_TYPE) size.cx;
////      this->y = (UNIT_TYPE) size.cy;
////
////   }
//
//
//   ///point_type(const ::sequence_type < NUMBER, 2 > & point) noexcept { this->x = (UNIT_TYPE) point.x; this->y = (UNIT_TYPE) point.y; }
//
////   template < prototype_size SIZE >
//  // point_type(const SIZE & size) noexcept { ::copy(*this, size); }
//
//#ifdef WINDOWS
//   //rectangle_type(const Gdiplus::Rect& t) noexcept : { ::copy(this, &t); }
//   //rectangle_type(const Gdiplus::RectF& t) noexcept : { ::copy(this, &t); }
//   //rectangle_type(const Gdiplus::Rect* p) noexcept : { ::copy(this, p); }
//   //rectangle_type(const Gdiplus::RectF* p) noexcept : { ::copy(this, p); }
//#endif
//#ifdef __APPLE__
////   point_type(const CGPoint & point) noexcept : point_type(point.x, point.y){}
////   point_type(const CGPoint * ppoint) noexcept : point_type(ppoint->x, ppoint->y){}
//#endif
   
   //constexpr const UNIT_TYPE & x() const {return this->x;}
   //UNIT_TYPE & x() {return this->x;}
   //constexpr const UNIT_TYPE & y() const {return this->y;}
   //UNIT_TYPE & y() {return this->y;}

//   template < raw_primitive_point RAW_PRIMITIVE_POINT >
//   inline point_type& operator = (const RAW_PRIMITIVE_POINT& point) { this->x = (UNIT_TYPE)point.x; this->y = (UNIT_TYPE)point.y; return *this; }

   
//   template < prototype_size PRIMITIVE_SIZE >
//   inline point_type & operator = (const PRIMITIVE_SIZE  & point) { this->x = (UNIT_TYPE) point.x; this->y = (UNIT_TYPE)point.y; return *this; }
   //template < prototype_number E >
   constexpr bool is_same_by(UNIT_TYPE e, const point_type & p) const
   {

      return ::std::abs(this->x - p.x) < ::std::abs(e)
         && ::std::abs(this->y - p.y) < ::std::abs(e);

   }

   
   inline point_type & operator = (const ::point_type < UNIT_TYPE > & point) { this->x = point.x; this->y = point.y; return *this; }

   //operator POINT_BASE_TYPE*() noexcept { return this; }
   //operator const POINT_BASE_TYPE*() const noexcept { return this; }
   //operator ::lparam() const { return lparam(); }

   unsigned int as_unsigned_int() const noexcept { return as_unsigned_int(this->x, this->y); }
   unsigned long long as_unsigned_long_long() const noexcept { return as_unsigned_long_long(this->x, this->y); }
   //::lparam lparam() const noexcept { return { this->x, this->y }; }

   point_type& Null() { this->x = (UNIT_TYPE)0; this->y = (UNIT_TYPE) 0;  return *this; }


   point_type & offset(UNIT_TYPE xOffset, UNIT_TYPE yOffset) noexcept { this->x += xOffset; this->y += yOffset; return *this; }
   point_type & offset(const sequence_type < UNIT_TYPE, 2 > & sequence) noexcept { this->x += sequence.x; this->y += sequence.y; return *this; }
//   point_type & offset(const SIZE_TYPE& size) noexcept { this->x += size.cx; this->y += size.cy; return *this; }
   point_type & set(UNIT_TYPE x, UNIT_TYPE y) noexcept { this->x = x; this->y = y; return *this; }



//   inline UNIT_TYPE get_dimension(enum_orientation eorientation) const noexcept { return get_dimension(eorientation, this->x, this->y); }
//   inline UNIT_TYPE get_orthogonal_dimension(enum_orientation eorientation) const noexcept { return get_normal_dimension(eorientation, this->x, this->y); }
//   inline UNIT_TYPE get_orthogonal(enum_orientation eorientation)const noexcept { return get_orthogonal_dimension(eorientation); }
//   inline UNIT_TYPE get_normal_dimension(enum_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }
//   inline UNIT_TYPE get_normal(enum_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }


//   inline UNIT_TYPE set_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept;
//   inline UNIT_TYPE set_orthogonal_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept;
//   inline UNIT_TYPE set_orthogonal(enum_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation,l); }
//   inline UNIT_TYPE set_normal_dimension(enum_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation,l); }
//   inline UNIT_TYPE set_normal(enum_orientation eorientation, UNIT_TYPE l) noexcept { return set_orthogonal_dimension(eorientation,l); }

   template < prototype_point POINT >
   double distance(const POINT& point) const { auto s = *this - point; return sqrt((double) (s.cx * s.cx + s.cy * s.cy)); }

   template < prototype_point POINT >
   point_type mid(const POINT& point) const
   {
      return { (UNIT_TYPE)((this->x + point.x) / (UNIT_TYPE)2), (UNIT_TYPE)((this->y + point.y) / (UNIT_TYPE)2) };
   }


   template < prototype_point POINT >
   inline bool operator==(const POINT & point) const noexcept { return (this->x == (UNIT_TYPE) point.x && this->y == (UNIT_TYPE) point.y); }

   //template < prototype_point POINT >
   //inline bool operator!=(const POINT & point) const noexcept { return (this->x != (UNIT_TYPE) point.x || this->y != (UNIT_TYPE) point.y); }


   inline bool operator==(nullptr_t) const noexcept { return ::is_null(this); }
   //inline bool operator!=(nullptr_t) const noexcept { return !::is_null(this); }

   template < prototype_number NUMBER1 >
   point_type < largest_number < UNIT_TYPE, NUMBER1 > > operator *(NUMBER1 n) const
   {
      point_type < largest_number < UNIT_TYPE, NUMBER1 > > result;
      result[0] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[0] * n);
      result[1] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[1] * n);
      return result;
   }


   template < prototype_number NUMBER1 >
   point_type < largest_number < UNIT_TYPE, NUMBER1 > > operator /(NUMBER1 n) const
   {
      point_type < largest_number < UNIT_TYPE, NUMBER1 > > result;
      result[0] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[0] / n);
      result[1] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[1] / n);
      return result;
   }

   
   template < prototype_size SIZE >
   inline point_type& operator +=(const SIZE& size) noexcept { this->x = (UNIT_TYPE) (this->x + size.cx); this->y = (UNIT_TYPE)(this->y + size.cy); return *this; }

   template < prototype_size SIZE >
   inline point_type& operator -=(const SIZE& size) noexcept { this->x = (UNIT_TYPE)(this->x - size.cx); this->y = (UNIT_TYPE)(this->y - size.cy); return *this; }

   template < prototype_point POINT >
   inline point_type& operator +=(const POINT& point) noexcept { this->x = (UNIT_TYPE)(this->x + point.x); this->y = (UNIT_TYPE)(this->y + point.y); return *this; }

   template < prototype_point POINT >
   inline point_type& operator -=(const POINT& point) noexcept { this->x = (UNIT_TYPE)(this->x - point.x); this->y = (UNIT_TYPE)(this->y - point.y); return *this; }

   template < prototype_number NUMBER1 >
   inline point_type < largest_number < UNIT_TYPE, NUMBER1 > > operator +(const sequence_type < NUMBER1, 2 > & sequence) const noexcept { return point_type < largest_number < UNIT_TYPE, NUMBER1 > >(this->x + sequence.x, this->y + sequence.y); }

//   template < prototype_point POINT >
//   inline point_type operator +(const POINT & point) const noexcept { return point_type(this->x + point.x, this->y + point.y); }


   template < prototype_number NUMBER1 >
   inline point_type < largest_number < UNIT_TYPE, NUMBER1 > > operator-(const sequence_type < NUMBER1, 2 > & sequence) const noexcept { return point_type < largest_number < UNIT_TYPE, NUMBER1 > >(this->x - sequence.x, this->y - sequence.y); }

   inline point_type operator-() const noexcept { return point_type(-this->x, -this->y); }
   inline point_type operator +() const noexcept { return point_type(this->x, this->y); }
   //inline point_type operator +(const point_type& point) const noexcept { return point_type(this->x + point.x, this->y + point.y); }
   //inline SIZE_TYPE operator-(const point_type& point) const noexcept { return SIZE_TYPE(this->x - point.x, this->y - point.y); }

//   inline RECTANGLE_TYPE operator +(const RECTANGLE_TYPE & rectangle) const noexcept { return RECTANGLE_TYPE(rectangle) + *this; }
//   inline RECTANGLE_TYPE operator-(const RECTANGLE_TYPE & rectangle) const noexcept { return RECTANGLE_TYPE(rectangle) - *this; }


//   inline point_type& operator +=(const SHIFT_I32& shift) noexcept { this->x = (UNIT_TYPE)(this->x + shift.Δx); this->y = (UNIT_TYPE)(this->y + shift.Δy); return *this; }
//   inline point_type& operator-=(const SHIFT_I32& shift) noexcept { this->x = (UNIT_TYPE)(this->x - shift.Δx); this->y = (UNIT_TYPE)(this->y - shift.Δy); return *this; }
//
//   inline point_type operator +(const SHIFT_I32& shift) noexcept { return { (UNIT_TYPE)(this->x + shift.Δx), (UNIT_TYPE)(this->y + shift.Δy) }; }
//   inline point_type operator-(const SHIFT_I32& shift) noexcept { return { (UNIT_TYPE)(this->x - shift.Δx), (UNIT_TYPE)(this->y - shift.Δy) }; }



//   void x_constraint(const RECTANGLE_TYPE& rectangle) noexcept
//   {
//
//      if (this->x < rectangle.left)
//      {
//
//         this->x = rectangle.left;
//
//      }
//      else if (this->x > rectangle.right)
//      {
//
//         this->x = rectangle.right;
//
//      }
//
//   }
//
//   void y_constraint(const RECTANGLE_TYPE& rectangle) noexcept
//   {
//
//      if (this->y < rectangle.top)
//      {
//
//         this->y = rectangle.top;
//
//      }
//      else if (this->y > rectangle.bottom)
//      {
//
//         this->y = rectangle.bottom;
//
//      }
//
//   }
//
//   void constraint(const RECTANGLE_TYPE & rectangle) noexcept
//   {
//
//      x_constraint(rectangle);
//
//      y_constraint(rectangle);
//
//   }



   inline bool operator < (const point_type& point) const noexcept
   {

      auto d = this->y - point.y;

      if (d < 0) return true;

      if (d > 0) return false;

      return this->x < point.x;

   }


   bool is_null() const
   {

      return this->x == 0 && this->y == 0;

   }
   
   
   template < prototype_point POINT >
   void expand_bounding_box(POINT & top_left, POINT & bottom_right) const
   {
      
      expand_minimum_maximum(top_left.x, bottom_right.x, this->x);
      
      expand_minimum_maximum(top_left.y, bottom_right.y, this->y);
      
   }
   
   
   template < prototype_point POINT >
   static void expand_bounding_box(POINT & top_left, POINT & bottom_right, const point_type * ppoint, ::collection::count count)
   {

      while(count > 0)
      {
         
         ppoint->expand_bounding_box(top_left, bottom_right);
         
         count--;
         
         ppoint++;

      }

   }

   
};





//inline auto as_int_point(const ::lparam & lparam) noexcept { return ::int_point(lparam.x, lparam.y); }
inline auto as_int_point(const unsigned int u) noexcept { return ::int_point((int)u32_x(u), (int)u32_y(u)); }
inline auto as_int_point(const unsigned long long u) noexcept { return ::int_point((int)u64_x(u), (int)u64_y(u)); }


//inline auto as_long_long_point(const ::lparam & lparam) noexcept { return ::long_long_point(lparam.x, lparam.y); }
inline auto as_long_long_point(const unsigned int u) noexcept { return ::long_long_point((long long)u32_x(u), (long long)u32_y(u)); }
inline auto as_long_long_point(const unsigned long long u) noexcept { return ::long_long_point((long long)u64_x(u), (long long)u64_y(u)); }


//inline auto as_float_point(const ::lparam & lparam) noexcept { return ::float_point((float)lparam.x, (float)lparam.y); }
inline auto as_float_point(const unsigned int u) noexcept { return ::float_point((float)u32_x(u), (float)u32_y(u)); }
inline auto as_float_point(const unsigned long long u) noexcept { return ::float_point((float)u64_x(u), (float)u64_y(u)); }


//inline auto as_double_point(const ::lparam & lparam) noexcept { return ::double_point(lparam.x, lparam.y); }
inline auto as_double_point(const unsigned int u) noexcept { return ::double_point((double)u32_x(u), (double)u32_y(u)); }
inline auto as_double_point(const unsigned long long u) noexcept { return ::double_point((double)u64_x(u), (double)u64_y(u)); }


inline bool is_almost_equal(const ::double_point& p1, const ::double_point& p2, double dTolerance)
{

   return is_almost_equal(p1.x, p2.x, dTolerance) && is_almost_equal(p1.y, p2.y, dTolerance);

}


inline bool is_different(const ::double_point& p1, const ::double_point& p2, double dTolerance)
{

   return !is_almost_equal(p1, p2, dTolerance);

}


template < prototype_number NUMBER1, prototype_number NUMBER2 >
inline ::size_type < largest_number < NUMBER1, NUMBER2 > > operator -(const ::point_type < NUMBER1 > & point1, const ::point_type < NUMBER2 > & point2) noexcept
{
   
   return ::size_type < largest_number < NUMBER1, NUMBER2 > >((largest_number < NUMBER1, NUMBER2 >) (point1.x - point2.x),
                                                              (largest_number < NUMBER1, NUMBER2 >)(point1.y - point2.y));
   
}





#include "acme/platform/lparam.h"


template < prototype_number NUMBER >
constexpr point_type<NUMBER>::point_type(const lparam &lparam) : sequence_type<UNIT_TYPE, 2>(lparam.x(), lparam.y())
{


}


template < prototype_point POINT >
constexpr lparam::lparam(const POINT & point) : lparam((int)point.x, (int)point.y)
{


}


constexpr ::int_point lparam::point() const
{

   return {(int)this->x(), (int)this->y()};

}



