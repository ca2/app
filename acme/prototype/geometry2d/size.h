#pragma once


#include "_function.h"
#include "acme/prototype/geometry/sequence.h"


template < primitive_number NUMBER >
class size_type :
   public sequence_type < NUMBER, 2 >
{
public:


//   NUMBER   cx;
  // NUMBER   cy;


   //using SIZE_BASE_TYPE = BASE_TYPE;
   using UNIT_TYPE = NUMBER;
   //using POINT_TYPE = point_type < NUMBER >;
   //using RECTANGLE_TYPE = rectangle_type < NUMBER >;

   
   
   
   size_type() {}
   size_type(no_initialize_t) : sequence_type < NUMBER, 2 >(no_initialize_t{}) {}
   //size_type(nullptr_t) : sequence_type < NUMBER, 2 >(nullptr) {}

//   sequence_type(const sequence_type&) = default;

//   template <primitive_number T,
//      std::enable_if_t<T::SIZE == SIZE &&
//      std::is_same_v<typename T::COORDINATE, COORDINATE>, int> = 0>
//   sequence_type(const T & a) {
//      for (size_t i = 0; i < SIZE; ++i)
//         m_coordinatea[i] = (COORDINATE)a[i];
//   }
   
   template < primitive_number C >
   size_type(C c)
   {
   
      this->set_all(c);
      
   }

   template < primitive_number CX, primitive_number CY >
   size_type(CX cx, CY cy)
   {
      this->m_coordinatea[0] = (UNIT_TYPE) cx;
      this->m_coordinatea[1] = (UNIT_TYPE) cy;
   }
   
   template < primitive_number NUMBER1 >
   size_type(const sequence_type < NUMBER1, 2 > & sequence) :
      sequence_type < UNIT_TYPE, 2 >(sequence)
   {
      
   }
   

   
   
   
   //using sequence_type < NUMBER, 2 >::sequence_type;

   //size_type() noexcept { this->cx() = UNIT_TYPE{}; this->cy() = UNIT_TYPE{}; }
   //size_type(no_initialize_t) noexcept {}
   //size_type(nullptr_t) noexcept { this->cx() = UNIT_TYPE{}; this->cy() = UNIT_TYPE{}; }
   //size_type(UNIT_TYPE cx, UNIT_TYPE cy) noexcept { this->cx() = cx; this->cy() = cy; }
//   template < primitive_number NUMBER_TYPE >
//   size_type(NUMBER_TYPE n) noexcept { this->cx() = (UNIT_TYPE) n; this->cy() = (UNIT_TYPE) n; }
   //size_type(unsigned int u) noexcept { this->cx() = (UNIT_TYPE) u; this->cy() = (UNIT_TYPE) u; }
   //size_type(long long i) noexcept { this->cx() = (UNIT_TYPE) i; this->cy() = (UNIT_TYPE) i; }
   //size_type(unsigned long long u) noexcept { this->cx() = (UNIT_TYPE) u; this->cy() = (UNIT_TYPE) u; }
   //size_type(float f) noexcept { this->cx() = (UNIT_TYPE) f; this->cy() = (UNIT_TYPE) f; }
   //size_type(double d) noexcept { this->cx() = (UNIT_TYPE) d; this->cy() = (UNIT_TYPE) d; }
//   explicit size_type(const lparam & lparam) noexcept : size_type(lparam.x(), lparam.y()) {}
   //template < primitive_point POINT >
//   size_type(const sequence_type < UNIT_TYPE, 2 > & sequence) noexcept { this->cx() = sequence.a(); this->cy() = sequence.b(); }
//   template < primitive_rectangle RECTANGLE >
//   size_type(const RECTANGLE & rectangle) noexcept { this->cx() = (UNIT_TYPE)::width(rectangle); this->cy() = (UNIT_TYPE)::height(rectangle); }
//   template < primitive_size SIZE >
//   size_type(const SIZE & size) noexcept : size_type((UNIT_TYPE)size.cx(), (UNIT_TYPE)size.cy()) {}
   //size_type(const ::long_long_size& size) noexcept : size_type((UNIT_TYPE)size.cx(), (UNIT_TYPE)size.cy()) {}
   //size_type(const ::float_size& size) noexcept : size_type((UNIT_TYPE)size.cx(), (UNIT_TYPE)size.cy()) {}
   //size_type(const ::double_size& size) noexcept : size_type((UNIT_TYPE)size.cx(), (UNIT_TYPE)size.cy()) {}
   //size_type(const ::int_size* psize) noexcept : size_type(*psize) {}
   //size_type(const ::long_long_size* psize) noexcept : size_type(*psize) {}
   //size_type(const ::float_size* psize) noexcept : size_type(*psize) {}
   //size_type(const ::double_size* psize) noexcept : size_type(*psize) {}
//#ifdef __APPLE__
////   size_type(const CGSize& size) noexcept : size_type((UNIT_TYPE)size.width, (UNIT_TYPE)size.height) {}
////   size_type(const CGSize *psize) noexcept : size_type(*psize) {}
//#endif


   //operator ::int_size* () noexcept { return this; }
   //operator const ::int_size* () const noexcept { return this; }
   //operator bool () const noexcept { return is_set(); }

   constexpr const NUMBER & cx() const { return this->a(); }
   constexpr const NUMBER & cy() const { return this->b(); }
   NUMBER & cx() { return this->a(); }
   NUMBER & cy() { return this->b(); }

   size_type& Null() { this->cx() = (UNIT_TYPE)0; this->cy() = (UNIT_TYPE)0; return *this; }

   template < primitive_point POINT >
   POINT operator+(const POINT& point1) const noexcept { POINT point(point1); ::offset(point, this->cx(), this->cy()); return point; }
   template < primitive_point POINT >
   POINT operator-(const POINT & point1) const noexcept { POINT point(this->cx(), this->cy()); ::offset(point, -point1.x(), -point1.y()); return point;   }

//   RECTANGLE_TYPE operator+(const RECTANGLE_TYPE& rect1) const noexcept { RECTANGLE_TYPE rectangle(rect1); ::offset(rectangle, this->cx(), this->cy()); return rectangle; }
//   RECTANGLE_TYPE operator-(const RECTANGLE_TYPE& rect1) const noexcept { RECTANGLE_TYPE rectangle(rect1); ::offset(rectangle, -this->cx(), -this->cy()); return rectangle; }

   UNIT_TYPE area() const noexcept { return ::area(this->cx(), this->cy()); }
   inline bool is_empty() const noexcept { return this->cx() <= 0 || this->cy() <= 0; }
   inline bool is_set() const noexcept { return !is_empty(); }
   inline bool has_area() const noexcept { return is_set(); }


   unsigned int as_unsigned_int() const noexcept { return as_unsigned_int(this->cx(), this->cy()); }
   unsigned long long as_unsigned_long_long() const noexcept { return as_unsigned_long_long(this->cx(), this->cy()); }
   class lparam lparam() const noexcept { return make_unsigned_int(this->cx(), this->cy()); }

   inline UNIT_TYPE width() const noexcept { return this->cx(); }
   inline UNIT_TYPE height() const noexcept { return this->cy(); }

//   inline UNIT_TYPE get_minimum_dimension() const noexcept { return ::minimum(this->cx(), this->cy()); }
//   inline UNIT_TYPE get_maximum_dimension() const noexcept { return ::maximum(this->cx(), this->cy()); }

//   inline UNIT_TYPE get_dimension(enum_orientation eorientation) const noexcept { return ::get_dimension(eorientation, this->cx(), this->cy()); }
//   inline UNIT_TYPE get_orthogonal_dimension(enum_orientation eorientation) const noexcept { return ::get_normal_dimension(eorientation, this->cx(), this->cy()); }
//   inline UNIT_TYPE get_orthogonal(enum_orientation eorientation)const noexcept { return get_orthogonal_dimension(eorientation); }
//   inline UNIT_TYPE get_normal_dimension(enum_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }
//   inline UNIT_TYPE get_normal(enum_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }
//
//   inline UNIT_TYPE set_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept { if (eorientation == e_orientation_horizontal) this->cx() = l; else if (eorientation == e_orientation_vertical) this->cy() = l; return l; }
//   inline UNIT_TYPE set_orthogonal_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept { if(eorientation == e_orientation_horizontal) this->cy() = l; else if (eorientation == e_orientation_vertical) this->cx() = l; return l;}
//   inline UNIT_TYPE set_orthogonal(enum_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation, l); }
//   inline UNIT_TYPE set_normal_dimension(enum_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation, l); }
//   inline UNIT_TYPE set_normal(enum_orientation eorientation, UNIT_TYPE l) noexcept { return set_orthogonal_dimension(eorientation, l); }

   inline void set(UNIT_TYPE c) noexcept { this->cx() = this->cy() = c; }
   inline void set(UNIT_TYPE cx, UNIT_TYPE cy) noexcept { this->cx() = cx; this->cy() = cy; }

   inline UNIT_TYPE minimum() const {return sequence_type <UNIT_TYPE, 2>::minimum();}
   inline UNIT_TYPE maximum() const {return sequence_type <UNIT_TYPE, 2>::maximum();}
   inline size_type minimum(const size_type & s)const noexcept { return size_type(::minimum(this->cx(), s.cx()), ::minimum(this->cy(), s.cy())); }
   inline size_type maximum(const size_type& s)const noexcept { return size_type(::maximum(this->cx(), s.cx()), ::maximum(this->cy(), s.cy())); }

   inline size_type & ensure_at_most(const size_type & s) noexcept { this->cx() = ::minimum(this->cx(), s.cx()); this->cy() = ::minimum(this->cy(), s.cy()); return *this; }
   inline size_type & ensure_at_least(const size_type & s) noexcept { this->cx() = ::maximum(this->cx(), s.cx()); this->cy() = ::maximum(this->cy(), s.cy()); return *this; }

   inline static size_type unit_size() { return size_type(1, 1); }

   inline size_type aspect_width(UNIT_TYPE w) { return size_type(w, w * this->cy() / this->cx()); }
   inline size_type aspect_height(UNIT_TYPE h) { return size_type(h * this->cx() / this->cy(), h); }
   inline ::design::enum_fit get_fit(size_type s) { return (::design::enum_fit) ::numeric::sign(s.cx() *this->cy() - s.cy() * this->cx()); }
   inline size_type fit(size_type s)
   {
      if (get_fit(s) == ::design::e_fit_height) return aspect_height(s.cy()); else return aspect_width(s.cx());
   }
   inline ::design::enum_match get_expand(size_type s) { return (::design::enum_match)(-(int)get_fit(s)); }
   inline size_type expand(size_type s)
   {
      if (get_expand(s) == ::design::e_match_height) return aspect_height(s.cy()); else return aspect_width(s.cx());
   }

   inline size_type & operator =(const size_type & size) noexcept { this->cx() = size.cx(); this->cy() = size.cy(); return *this; }

   template < primitive_size SIZE > 
   inline size_type & operator+=(const SIZE & size) noexcept { this->cx() += size.cx(); this->cy() += size.cy(); return *this; }

   template < primitive_size SIZE >
   inline size_type & operator-=(const SIZE & size) noexcept { this->cx() -= size.cx(); this->cy() -= size.cy(); return *this; }

//   template < primitive_point POINT >
//   inline size_type & operator+=(const POINT & point) noexcept { this->cx() += point.x(); this->cy() += point.y(); return *this; }

   template < primitive_number NUMBER1 >
   inline size_type & operator +=(const sequence_type < NUMBER1, 2 > & sequence) noexcept { this->cx() = (UNIT_TYPE) (this->cx() + sequence.a()); this->cy() = (UNIT_TYPE) (this->cy() + sequence.b()); return *this; }

   template < primitive_number NUMBER1 >
   inline size_type & operator -=(const sequence_type < NUMBER1, 2 > & sequence) noexcept { this->cx() = (UNIT_TYPE) (this->cx() - sequence.a()); this->cy() = (UNIT_TYPE) (this->cy() - sequence.b()); return *this; }

//   template < primitive_point POINT >
//   inline size_type & operator-=(const POINT & point) noexcept { this->cx() -= point.x(); this->cy() -= point.y(); return *this; }

   template < primitive_number NUMBER1 >
   inline size_type & operator +=(NUMBER1 n) noexcept { this->cx() = UNIT_TYPE(this->cx() + n); this->cy() = UNIT_TYPE(this->cy() + n); return *this; }

   template < primitive_number NUMBER1 >
   inline size_type & operator -=(NUMBER1 n) noexcept { this->cx() = UNIT_TYPE(this->cx() - n); this->cy() = UNIT_TYPE(this->cy() - n); return *this; }

   template < primitive_number NUMBER1 >
   inline size_type & operator *=(NUMBER1 n) noexcept { this->cx() = UNIT_TYPE(this->cx() * n); this->cy() = UNIT_TYPE(this->cy() * n); return *this; }

   template < primitive_number NUMBER1 >
   inline size_type & operator /=(NUMBER1 n) noexcept { this->cx() = UNIT_TYPE(this->cx() / n); this->cy() = UNIT_TYPE(this->cy() / n); return *this; }

   inline void set_size(UNIT_TYPE cx, UNIT_TYPE cy) noexcept {this->cx() = cx; this->cy() = cy; }
   inline void set_size(const size_type & size_type) noexcept { set_size(size_type.cx(), size_type.cy()); }

   template < primitive_number NUMBER1 >
   inline size_type < largest_number < UNIT_TYPE, NUMBER1 > > operator +(const sequence_type < NUMBER1, 2 > & sequence) const noexcept { return size_type < largest_number < UNIT_TYPE, NUMBER1 > > ((largest_number < UNIT_TYPE, NUMBER1 >) (this->cx() + sequence.a()), (largest_number < UNIT_TYPE, NUMBER1 >) (this->cy() + sequence.b())); }

   template < primitive_number NUMBER1 >
   inline size_type < largest_number < UNIT_TYPE, NUMBER1 > > operator -(const sequence_type < NUMBER1, 2 > & sequence) const noexcept { return size_type < largest_number < UNIT_TYPE, NUMBER1 > > ((largest_number < UNIT_TYPE, NUMBER1 >) (this->cx() - sequence.a()), (largest_number < UNIT_TYPE, NUMBER1 >) (this->cy() - sequence.b())); }

   inline size_type operator-() const noexcept { return size_type(-this->cx(), -this->cy()); }

//#ifdef WINDOWS
//   inline size_type operator /(int i) const noexcept { return size_type((UNIT_TYPE)(this->cx() / i), (UNIT_TYPE)(this->cy() / i)); }
//#endif
   
   template < primitive_number NUMBER1 >
   inline size_type < largest_number < UNIT_TYPE, NUMBER1 > > operator /(NUMBER1 l) const noexcept { return size_type < largest_number < UNIT_TYPE, NUMBER1 > >((largest_number < UNIT_TYPE, NUMBER1 >)(this->cx() / l), (largest_number < UNIT_TYPE, NUMBER1 >)(this->cy() / l)); }
//   inline size_type operator /(long long i) const noexcept { return size_type((UNIT_TYPE)(this->cx() / i), (UNIT_TYPE)(this->cy() / i)); }
//   inline size_type operator /(float f) const noexcept { return size_type((UNIT_TYPE)(this->cx() / f), (UNIT_TYPE)(this->cy() / f)); }
//   inline size_type operator /(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx() / d), (UNIT_TYPE)(this->cy() / d)); }
   template < primitive_number NUMBER1 >
   inline size_type < largest_number < UNIT_TYPE, NUMBER1 > > operator /(const sequence_type <NUMBER1, 2> & sequence) const { return size_type < largest_number < UNIT_TYPE, NUMBER1 > >((largest_number < UNIT_TYPE, NUMBER1 >)(this->cx() / sequence.a()), (largest_number < UNIT_TYPE, NUMBER1 >)(this->cy() / sequence.b())); }

   template < primitive_number NUMBER1 >
   inline size_type < largest_number < UNIT_TYPE, NUMBER1 > > operator *(NUMBER1 d) const noexcept { return size_type < largest_number < UNIT_TYPE, NUMBER1 > >((largest_number < UNIT_TYPE, NUMBER1 >)(this->cx() * d), (largest_number < UNIT_TYPE, NUMBER1 >)(this->cy() * d)); }

   //inline size_type operator +(int i) const noexcept { return size_type(this->cx() + i, this->cy() + i); }
   template < primitive_number NUMBER1 >
   inline size_type<largest_number < UNIT_TYPE, NUMBER1 >> operator +(NUMBER1 d) const noexcept { return size_type < largest_number < UNIT_TYPE, NUMBER1 > >((largest_number < UNIT_TYPE, NUMBER1 >)(this->cx() + d), (largest_number < UNIT_TYPE, NUMBER1 >)(this->cy() + d)); }

//   inline size_type operator -(int i) const noexcept { return size_type(this->cx() - i, this->cy() - i); }
   template < primitive_number NUMBER1 >
   inline size_type < largest_number < UNIT_TYPE, NUMBER1 > > operator -(NUMBER1 d) const noexcept { return size_type < largest_number < UNIT_TYPE, NUMBER1 > >((largest_number < UNIT_TYPE, NUMBER1 >)(this->cx() - d), (largest_number < UNIT_TYPE, NUMBER1 >)(this->cy() - d)); }


   template < primitive_number NUMBER1 >
   inline size_type < largest_number < UNIT_TYPE, NUMBER1 > > half_away(const size_type < NUMBER1 >& size) { return size_type < largest_number < UNIT_TYPE, NUMBER1 > >((this->cx() - size.cx()) / (largest_number < UNIT_TYPE, NUMBER1 >) 2, (this->cy() - size.cy()) / (largest_number < UNIT_TYPE, NUMBER1 >) 2); }

//   inline bool operator ==(nullptr_t) const noexcept { return ::is_null(this); }
//   inline bool operator !=(nullptr_t) const noexcept { return !operator==(nullptr); }

   inline bool operator == (const size_type & size) const noexcept { return this->cx() == size.cx() && this->cy() == size.cy(); }
//   inline bool operator != (const size_type & size) const noexcept { return !operator ==(size); }

//   inline bool operator == (const RECTANGLE_TYPE & rectangle) const noexcept { return this->cx() == rectangle.width() && this->cy() == rectangle.height(); }
   //inline bool operator != (const RECTANGLE_TYPE & rectangle) const noexcept { return !operator ==(rectangle); }

   inline bool operator >= (const size_type & size) const noexcept
   {
   
      return this->cx() >= size.cx() && this->cy() >= size.cy();

   }

   
   inline bool operator > (const size_type & size) const noexcept
   {
   
      return *this >= size && *this != size;

   }

   
   inline bool operator <= (const size_type & size) const noexcept
   {
   
      return this->cx() <= size.cx() && this->cy() <= size.cy();

   }

   
   inline bool operator < (const size_type & size) const noexcept
   {
   
      return *this <= size && *this != size;

   }
//   inline ::std::strong_ordering operator <=> (const RECTANGLE_TYPE & rectangle) const noexcept { return this->operator <=> (rectangle.size()); }
   //inline bool operator >= (const RECTANGLE_TYPE & rectangle) const noexcept { return this->operator >= (rectangle.size()); }
   //inline bool operator < (const RECTANGLE_TYPE & rectangle) const noexcept { return this->operator < (rectangle.size()); }
   //inline bool operator <= (const RECTANGLE_TYPE & rectangle) const noexcept { return this->operator <= (rectangle.size()); }

   inline bool any_gt (const size_type & size) const noexcept { return this->cx() > size.cx() || this->cy() > size.cy(); }
   inline bool any_ge (const size_type & size) const noexcept { return this->cx() >= size.cx() || this->cy() >= size.cy(); }
   inline bool any_lt (const size_type & size) const noexcept { return this->cx() < size.cx() || this->cy() < size.cy(); }
   inline bool any_le (const size_type & size) const noexcept { return this->cx() <= size.cx() || this->cy() <= size.cy(); }

//   inline bool any_gt (const RECTANGLE_TYPE & rectangle) const noexcept { return this->any_gt(rectangle.size()); }
//   inline bool any_ge (const RECTANGLE_TYPE & rectangle) const noexcept { return this->any_ge(rectangle.size()); }
//   inline bool any_lt (const RECTANGLE_TYPE & rectangle) const noexcept { return this->any_lt(rectangle.size()); }
//   inline bool any_le (const RECTANGLE_TYPE & rectangle) const noexcept { return this->any_le(rectangle.size()); }


   constexpr operator hash32() const
   {

      return ::hash32(this->cx()) + ::hash32(this->cy());

   }

};


template < primitive_size SIZE >
inline auto abs(const SIZE & size) noexcept { return SIZE(abs(size.cx()), abs(size.cy())); }
//inline auto abs(const ::long_long_size& size) noexcept { return ::long_long_size(abs(size.cx()), abs(size.cy())); }
//inline auto abs(const ::float_size& size) noexcept { return ::float_size(abs(size.cx()), abs(size.cy())); }
//inline auto abs(const ::double_size& size) noexcept { return ::double_size(abs(size.cx()), abs(size.cy())); }


