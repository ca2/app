#pragma once


#include "acme/primitive/geometry/sequence.h"


template < primitive_number NUMBER >
class point_type :
   public sequence_type < NUMBER, 2 >
{
public:


   using UNIT_TYPE = NUMBER;
   //using SIZE_TYPE = size_type < NUMBER >;
   //using RECTANGLE_TYPE = rectangle_type < NUMBER >;

   
   ///using sequence_type < NUMBER, 2 >::sequence_type;
   
   
   point_type() {}
   point_type(no_initialize_t) : sequence_type < NUMBER, 2 >(no_initialize_t{}) {}
   //point_type(::std::nullptr_t) : sequence_type < NUMBER, 2 >(nullptr) {}

//   sequence_type(const sequence_type&) = default;

//   template <primitive_number T,
//      std::enable_if_t<T::SIZE == SIZE &&
//      std::is_same_v<typename T::COORDINATE, COORDINATE>, int> = 0>
   point_type(UNIT_TYPE n)
   {
   
      this->set_all(n);
      
   }
   
   point_type(NUMBER x, NUMBER y)
   {
      this->m_coordinatea[0] = x;
      this->m_coordinatea[1] = y;
   }
   
   template < primitive_number NUMBER1 >
   point_type(const sequence_type < NUMBER1, 2 > & sequence) :
      sequence_type < UNIT_TYPE, 2 >(sequence)
   {
      
   }
   

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


//   point_type() noexcept { this->x() = (UNIT_TYPE)0; this->y() = (UNIT_TYPE)0; }
//   point_type(enum_no_initialize) noexcept {  }
//   point_type(::std::nullptr_t) noexcept { this->x() = (UNIT_TYPE)0; this->y() = (UNIT_TYPE)0; }
//   point_type(UNIT_TYPE x, UNIT_TYPE y) noexcept { this->x() = x; this->y() = y; }
//   ///point_type(const ::lparam& lparam) noexcept : point_type(lparam.x(), lparam.y()) {}
//   //point_type(const ::u32 u) noexcept : point_type((UNIT_TYPE) u32_x(u), (UNIT_TYPE)u32_y(u)) {}
//   //point_type(const ::u64 u) noexcept : point_type((UNIT_TYPE)u64_x(u), (UNIT_TYPE)u64_y(u)) {}
//   //point_type(const SIZE_TYPE & size) noexcept : point_type(size.cx(), size.cy()) {}
//
//
////   template < raw_primitive_point POINT >
////   point_type(const POINT & point)
////   {
////
////      this->x() = (UNIT_TYPE) point.x();
////      this->y() = (UNIT_TYPE) point.y()
////
////   }
//
//
//   point_type(const sequence_type < UNIT_TYPE, 2 > & sequence)
//   {
//
//      this->x() = sequence.a();
//      this->y() = sequence.b();
//
//   }
//
//
////   template < primitive_size SIZE >
////   point_type(const SIZE & size)
////   {
////
////      this->x() = (UNIT_TYPE) size.cx();
////      this->y() = (UNIT_TYPE) size.cy();
////
////   }
//
//
//   ///point_type(const ::sequence_type < NUMBER, 2 > & point) noexcept { this->x() = (UNIT_TYPE) point.x(); this->y() = (UNIT_TYPE) point.y(); }
//
////   template < primitive_size SIZE >
//  // point_type(const SIZE & size) noexcept { ::copy(*this, size); }
//
//#ifdef WINDOWS
//   //rectangle_type(const Gdiplus::Rect& t) noexcept : { ::copy(this, &t); }
//   //rectangle_type(const Gdiplus::RectF& t) noexcept : { ::copy(this, &t); }
//   //rectangle_type(const Gdiplus::Rect* p) noexcept : { ::copy(this, p); }
//   //rectangle_type(const Gdiplus::RectF* p) noexcept : { ::copy(this, p); }
//#endif
//#ifdef __APPLE__
////   point_type(const CGPoint & point) noexcept : point_type(point.x(), point.y()){}
////   point_type(const CGPoint * ppoint) noexcept : point_type(ppoint->x(), ppoint->y()){}
//#endif
   
   constexpr const UNIT_TYPE & x() const {return this->a();}
   UNIT_TYPE & x() {return this->a();}
   constexpr const UNIT_TYPE & y() const {return this->b();}
   UNIT_TYPE & y() {return this->b();}

//   template < raw_primitive_point RAW_PRIMITIVE_POINT >
//   inline point_type& operator = (const RAW_PRIMITIVE_POINT& point) { this->x() = (UNIT_TYPE)point.x(); this->y() = (UNIT_TYPE)point.y(); return *this; }

   
//   template < primitive_size PRIMITIVE_SIZE >
//   inline point_type & operator = (const PRIMITIVE_SIZE  & point) { this->x() = (UNIT_TYPE) point.x(); this->y() = (UNIT_TYPE)point.y(); return *this; }

   
   inline point_type & operator = (const ::point_type < UNIT_TYPE > & point) { this->x() = point.x(); this->y() = point.y(); return *this; }

   //operator POINT_BASE_TYPE*() noexcept { return this; }
   //operator const POINT_BASE_TYPE*() const noexcept { return this; }
   //operator ::lparam() const { return lparam(); }

   ::u32 u32() const noexcept { return __u32(this->x(), this->y()); }
   ::u64 u64() const noexcept { return __u64(this->x(), this->y()); }
   //::lparam lparam() const noexcept { return { this->x(), this->y() }; }

   point_type& Null() { this->x() = (UNIT_TYPE)0; this->y() = (UNIT_TYPE) 0;  return *this; }


   point_type & offset(UNIT_TYPE xOffset, UNIT_TYPE yOffset) noexcept { this->x() += xOffset; this->y() += yOffset; return *this; }
   point_type & offset(const sequence_type < UNIT_TYPE, 2 > & sequence) noexcept { this->x() += sequence.a(); this->y() += sequence.b(); return *this; }
//   point_type & offset(const SIZE_TYPE& size) noexcept { this->x() += size.cx(); this->y() += size.cy(); return *this; }
   point_type & set(UNIT_TYPE x, UNIT_TYPE y) noexcept { this->x() = x; this->y() = y; return *this; }



//   inline UNIT_TYPE get_dimension(enum_orientation eorientation) const noexcept { return get_dimension(eorientation, this->x(), this->y()); }
//   inline UNIT_TYPE get_orthogonal_dimension(enum_orientation eorientation) const noexcept { return get_normal_dimension(eorientation, this->x(), this->y()); }
//   inline UNIT_TYPE get_orthogonal(enum_orientation eorientation)const noexcept { return get_orthogonal_dimension(eorientation); }
//   inline UNIT_TYPE get_normal_dimension(enum_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }
//   inline UNIT_TYPE get_normal(enum_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }


//   inline UNIT_TYPE set_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept;
//   inline UNIT_TYPE set_orthogonal_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept;
//   inline UNIT_TYPE set_orthogonal(enum_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation,l); }
//   inline UNIT_TYPE set_normal_dimension(enum_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation,l); }
//   inline UNIT_TYPE set_normal(enum_orientation eorientation, UNIT_TYPE l) noexcept { return set_orthogonal_dimension(eorientation,l); }

   template < primitive_point POINT >
   double distance(const POINT& point) const { auto s = *this - point; return sqrt((double) (s.cx() * s.cx() + s.cy() * s.cy())); }

   template < primitive_point POINT >
   point_type mid(const POINT& point) const
   {
      return { (UNIT_TYPE)((this->x() + point.x()) / (UNIT_TYPE)2), (UNIT_TYPE)((this->y() + point.y()) / (UNIT_TYPE)2) };
   }


   template < primitive_point POINT >
   inline bool operator==(const POINT & point) const noexcept { return (this->x() == (UNIT_TYPE) point.x() && this->y() == (UNIT_TYPE) point.y()); }

   //template < primitive_point POINT >
   //inline bool operator!=(const POINT & point) const noexcept { return (this->x() != (UNIT_TYPE) point.x() || this->y() != (UNIT_TYPE) point.y()); }


   inline bool operator==(::std::nullptr_t) const noexcept { return ::is_null(this); }
   //inline bool operator!=(::std::nullptr_t) const noexcept { return !::is_null(this); }

   template < primitive_number NUMBER1 >
   point_type < largest_number < UNIT_TYPE, NUMBER1 > > operator *(NUMBER1 n) const
   {
      point_type < largest_number < UNIT_TYPE, NUMBER1 > > result;
      result[0] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[0] * n);
      result[1] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[1] * n);
      return result;
   }


   template < primitive_number NUMBER1 >
   point_type < largest_number < UNIT_TYPE, NUMBER1 > > operator /(NUMBER1 n) const
   {
      point_type < largest_number < UNIT_TYPE, NUMBER1 > > result;
      result[0] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[0] / n);
      result[1] = (largest_number < UNIT_TYPE, NUMBER1 >) (this->m_coordinatea[1] / n);
      return result;
   }

   
   template < primitive_size SIZE >
   inline point_type& operator +=(const SIZE& size) noexcept { this->x() = (UNIT_TYPE) (this->x() + size.cx()); this->y() = (UNIT_TYPE)(this->y() + size.cy()); return *this; }

   template < primitive_size SIZE >
   inline point_type& operator -=(const SIZE& size) noexcept { this->x() = (UNIT_TYPE)(this->x() - size.cx()); this->y() = (UNIT_TYPE)(this->y() - size.cy()); return *this; }

   template < primitive_point POINT >
   inline point_type& operator +=(const POINT& point) noexcept { this->x() = (UNIT_TYPE)(this->x() + point.x()); this->y() = (UNIT_TYPE)(this->y() + point.y()); return *this; }

   template < primitive_point POINT >
   inline point_type& operator -=(const POINT& point) noexcept { this->x() = (UNIT_TYPE)(this->x() - point.x()); this->y() = (UNIT_TYPE)(this->y() - point.y()); return *this; }

   template < primitive_number NUMBER1 >
   inline point_type < largest_number < UNIT_TYPE, NUMBER1 > > operator+(const sequence_type < NUMBER1, 2 > & sequence) const noexcept { return point_type < largest_number < UNIT_TYPE, NUMBER1 > >(this->x() + sequence.a(), this->y() + sequence.b()); }

//   template < primitive_point POINT >
//   inline point_type operator+(const POINT & point) const noexcept { return point_type(this->x() + point.x(), this->y() + point.y()); }


   template < primitive_number NUMBER1 >
   inline point_type < largest_number < UNIT_TYPE, NUMBER1 > > operator-(const sequence_type < NUMBER1, 2 > & sequence) const noexcept { return point_type < largest_number < UNIT_TYPE, NUMBER1 > >(this->x() - sequence.a(), this->y() - sequence.b()); }

   inline point_type operator-() const noexcept { return point_type(-this->x(), -this->y()); }
   inline point_type operator+() const noexcept { return point_type(this->x(), this->y()); }
   //inline point_type operator+(const point_type& point) const noexcept { return point_type(this->x() + point.x(), this->y() + point.y()); }
   //inline SIZE_TYPE operator-(const point_type& point) const noexcept { return SIZE_TYPE(this->x() - point.x(), this->y() - point.y()); }

//   inline RECTANGLE_TYPE operator+(const RECTANGLE_TYPE & rectangle) const noexcept { return RECTANGLE_TYPE(rectangle) + *this; }
//   inline RECTANGLE_TYPE operator-(const RECTANGLE_TYPE & rectangle) const noexcept { return RECTANGLE_TYPE(rectangle) - *this; }


//   inline point_type& operator+=(const SHIFT_I32& shift) noexcept { this->x() = (UNIT_TYPE)(this->x() + shift.Δx); this->y() = (UNIT_TYPE)(this->y() + shift.Δy); return *this; }
//   inline point_type& operator-=(const SHIFT_I32& shift) noexcept { this->x() = (UNIT_TYPE)(this->x() - shift.Δx); this->y() = (UNIT_TYPE)(this->y() - shift.Δy); return *this; }
//
//   inline point_type operator+(const SHIFT_I32& shift) noexcept { return { (UNIT_TYPE)(this->x() + shift.Δx), (UNIT_TYPE)(this->y() + shift.Δy) }; }
//   inline point_type operator-(const SHIFT_I32& shift) noexcept { return { (UNIT_TYPE)(this->x() - shift.Δx), (UNIT_TYPE)(this->y() - shift.Δy) }; }



//   void x_constraint(const RECTANGLE_TYPE& rectangle) noexcept
//   {
//
//      if (this->x() < rectangle.left)
//      {
//
//         this->x() = rectangle.left;
//
//      }
//      else if (this->x() > rectangle.right)
//      {
//
//         this->x() = rectangle.right;
//
//      }
//
//   }
//
//   void y_constraint(const RECTANGLE_TYPE& rectangle) noexcept
//   {
//
//      if (this->y() < rectangle.top)
//      {
//
//         this->y() = rectangle.top;
//
//      }
//      else if (this->y() > rectangle.bottom)
//      {
//
//         this->y() = rectangle.bottom;
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

      auto d = this->y() - point.y();

      if (d < 0) return true;

      if (d > 0) return false;

      return this->x() < point.x();

   }


   bool is_null() const
   {

      return this->x() == 0 && this->y() == 0;

   }
   
   
   template < primitive_point POINT >
   void expand_bounding_box(POINT & top_left, POINT & bottom_right) const
   {
      
      expand_minimum_maximum(top_left.x(), bottom_right.x(), this->x());
      
      expand_minimum_maximum(top_left.y(), bottom_right.y(), this->y());
      
   }
   
   
   template < primitive_point POINT >
   static void expand_bounding_box(POINT & top_left, POINT & bottom_right, const point_type * ppoint, ::count count)
   {

      while(count > 0)
      {
         
         ppoint->expand_bounding_box(top_left, bottom_right);
         
         count--;
         
         ppoint++;

      }

   }

   
};





//inline auto u32_point_i32(const ::lparam & lparam) noexcept { return ::point_i32(lparam.x(), lparam.y()); }
inline auto u32_point_i32(const ::u32 u) noexcept { return ::point_i32((::i32)u32_x(u), (::i32)u32_y(u)); }
inline auto u64_point_i32(const ::u64 u) noexcept { return ::point_i32((::i32)u64_x(u), (::i32)u64_y(u)); }


//inline auto u32_point_i64(const ::lparam & lparam) noexcept { return ::point_i64(lparam.x(), lparam.y()); }
inline auto u32_point_i64(const ::u32 u) noexcept { return ::point_i64((i64)u32_x(u), (i64)u32_y(u)); }
inline auto u64_point_i64(const ::u64 u) noexcept { return ::point_i64((i64)u64_x(u), (i64)u64_y(u)); }


//inline auto __point_f32(const ::lparam & lparam) noexcept { return ::point_f32((float)lparam.x(), (float)lparam.y()); }
inline auto __point_f32(const ::u32 u) noexcept { return ::point_f32((float)u32_x(u), (float)u32_y(u)); }
inline auto __point_f32(const ::u64 u) noexcept { return ::point_f32((float)u64_x(u), (float)u64_y(u)); }


//inline auto __point_f64(const ::lparam & lparam) noexcept { return ::point_f64(lparam.x(), lparam.y()); }
inline auto __point_f64(const ::u32 u) noexcept { return ::point_f64((double)u32_x(u), (double)u32_y(u)); }
inline auto __point_f64(const ::u64 u) noexcept { return ::point_f64((double)u64_x(u), (double)u64_y(u)); }


inline bool is_same(const ::point_f64& p1, const ::point_f64& p2, double dTolerance)
{

   return is_same(p1.x(), p2.x(), dTolerance) && is_same(p1.y(), p2.y(), dTolerance);

}


inline bool is_different(const ::point_f64& p1, const ::point_f64& p2, double dTolerance)
{

   return !is_same(p1, p2, dTolerance);

}


template < primitive_number NUMBER1, primitive_number NUMBER2 >
inline ::size_type < largest_number < NUMBER1, NUMBER2 > > operator -(const ::point_type < NUMBER1 > & point1, const ::point_type < NUMBER2 > & point2) noexcept
{
   
   return ::size_type < largest_number < NUMBER1, NUMBER2 > >((largest_number < NUMBER1, NUMBER2 >) (point1.x() - point2.x()),
                                                              (largest_number < NUMBER1, NUMBER2 >)(point1.y() - point2.y()));
   
}
