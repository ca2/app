#pragma once


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECTANGLE_BASE_TYPE >
class size_type :
   public BASE_TYPE
{
public:


   using SIZE_BASE_TYPE = BASE_TYPE;
   using UNIT_TYPE = decltype(SIZE_BASE_TYPE::cx);
   using POINT_TYPE = point_type < POINT_BASE_TYPE, SIZE_BASE_TYPE, RECTANGLE_BASE_TYPE >;
   using RECTANGLE_TYPE = rectangle_type < RECTANGLE_BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE >;


   size_type() noexcept { this->cx = 0; this->cy = 0; }
   size_type(enum_no_initialize) noexcept {}
   size_type(::std::nullptr_t) noexcept { this->cx = 0; this->cy = 0; }
   size_type(UNIT_TYPE cx, UNIT_TYPE cy) noexcept { this->cx = cx; this->cy = cy; }
   size_type(::i32 i) noexcept { this->cx = (UNIT_TYPE) i; this->cy = (UNIT_TYPE) i; }
   size_type(::u32 u) noexcept { this->cx = (UNIT_TYPE) u; this->cy = (UNIT_TYPE) u; }
   size_type(::i64 i) noexcept { this->cx = (UNIT_TYPE) i; this->cy = (UNIT_TYPE) i; }
   size_type(::u64 u) noexcept { this->cx = (UNIT_TYPE) u; this->cy = (UNIT_TYPE) u; }
   size_type(float f) noexcept { this->cx = (UNIT_TYPE) f; this->cy = (UNIT_TYPE) f; }
   size_type(double d) noexcept { this->cx = (UNIT_TYPE) d; this->cy = (UNIT_TYPE) d; }
   size_type(const lparam & lparam) noexcept : size_type(lparam.x(), lparam.y()) {}
   template < primitive_point POINT >
   size_type(const POINT & point) noexcept { this->cx = (UNIT_TYPE)point.x; this->cy = (UNIT_TYPE)point.y; }
   template < primitive_rectangle RECTANGLE >
   size_type(const RECTANGLE & rectangle) noexcept { this->cx = (UNIT_TYPE)::width(rectangle); this->cy = (UNIT_TYPE)::height(rectangle); }
   size_type(const SIZE_I32& size) noexcept : size_type((UNIT_TYPE)size.cx, (UNIT_TYPE)size.cy) {}
   size_type(const SIZE_I64& size) noexcept : size_type((UNIT_TYPE)size.cx, (UNIT_TYPE)size.cy) {}
   size_type(const SIZE_F32& size) noexcept : size_type((UNIT_TYPE)size.cx, (UNIT_TYPE)size.cy) {}
   size_type(const SIZE_F64& size) noexcept : size_type((UNIT_TYPE)size.cx, (UNIT_TYPE)size.cy) {}
   size_type(const SIZE_I32* psize) noexcept : size_type(*psize) {}
   size_type(const SIZE_I64* psize) noexcept : size_type(*psize) {}
   size_type(const SIZE_F32* psize) noexcept : size_type(*psize) {}
   size_type(const SIZE_F64* psize) noexcept : size_type(*psize) {}
#ifdef __APPLE__
//   size_type(const CGSize& size) noexcept : size_type((UNIT_TYPE)size.width, (UNIT_TYPE)size.height) {}
//   size_type(const CGSize *psize) noexcept : size_type(*psize) {}
#endif


   operator SIZE_I32* () noexcept { return this; }
   operator const SIZE_I32* () const noexcept { return this; }
   operator bool () const noexcept { return is_set(); }


   size_type& Null() { this->cx = (UNIT_TYPE)0; this->cy = (UNIT_TYPE)0; return *this; }

   POINT_TYPE operator+(const POINT_TYPE& point1) const noexcept { POINT_TYPE point(point1); ::offset_point(&point, this->cx, this->cy); return point; }
   template < primitive_point POINT >
   POINT_TYPE operator-(const POINT & point1) const noexcept { POINT_TYPE point(this->cx, this->cy); ::offset_point(&point, -point1.x, -point1.y); return point;   }

   RECTANGLE_TYPE operator+(const RECTANGLE_TYPE& rect1) const noexcept { RECTANGLE_TYPE rectangle(rect1); ::offset_rect(&rectangle, this->cx, this->cy); return rectangle; }
   RECTANGLE_TYPE operator-(const RECTANGLE_TYPE& rect1) const noexcept { RECTANGLE_TYPE rectangle(rect1); ::offset_rect(&rectangle, -this->cx, -this->cy); return rectangle; }

   UNIT_TYPE area() const noexcept { return ::rect_area(this->cx, this->cy); }
   inline bool is_empty() const noexcept { return this->cx <= 0 || this->cy <= 0; }
   inline bool is_set() const noexcept { return !is_empty(); }
   inline bool has_area() const noexcept { return is_set(); }


   ::u32          u32() const noexcept { return __u32(this->cx, this->cy); }
   ::u64          u64() const noexcept { return __u64(this->cx, this->cy); }
   class lparam   lparam() const noexcept { return __MAKE_LPARAM(this->cx, this->cy); }

   inline UNIT_TYPE width() const noexcept { return this->cx; }
   inline UNIT_TYPE height() const noexcept { return this->cy; }

   inline UNIT_TYPE get_minimum_dimension() const noexcept { return ::minimum(this->cx, this->cy); }
   inline UNIT_TYPE get_maximum_dimension() const noexcept { return ::maximum(this->cx, this->cy); }

   inline UNIT_TYPE get_dimension(enum_orientation eorientation) const noexcept { return ::get_dimension(eorientation, this->cx, this->cy); }
   inline UNIT_TYPE get_orthogonal_dimension(enum_orientation eorientation) const noexcept { return ::get_normal_dimension(eorientation, this->cx, this->cy); }
   inline UNIT_TYPE get_orthogonal(enum_orientation eorientation)const noexcept { return get_orthogonal_dimension(eorientation); }
   inline UNIT_TYPE get_normal_dimension(enum_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }
   inline UNIT_TYPE get_normal(enum_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }

   inline UNIT_TYPE set_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept { if (eorientation == e_orientation_horizontal) this->cx = l; else if (eorientation == e_orientation_vertical) this->cy = l; return l; }
   inline UNIT_TYPE set_orthogonal_dimension(enum_orientation eorientation, UNIT_TYPE l) noexcept { if(eorientation == e_orientation_horizontal) this->cy = l; else if (eorientation == e_orientation_vertical) this->cx = l; return l;}
   inline UNIT_TYPE set_orthogonal(enum_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation, l); }
   inline UNIT_TYPE set_normal_dimension(enum_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation, l); }
   inline UNIT_TYPE set_normal(enum_orientation eorientation, UNIT_TYPE l) noexcept { return set_orthogonal_dimension(eorientation, l); }

   inline void set(UNIT_TYPE c) noexcept { this->cx = this->cy = c; }
   inline void set(UNIT_TYPE cx, UNIT_TYPE cy) noexcept { this->cx = cx; this->cy = cy; }

   inline size_type minimum(const size_type & s)const noexcept { return size_type(::minimum(this->cx, s.cx), ::minimum(this->cy, s.cy)); }
   inline size_type maximum(const size_type& s)const noexcept { return size_type(::maximum(this->cx, s.cx), ::maximum(this->cy, s.cy)); }

   inline size_type & ensure_at_most(const size_type & s) noexcept { this->cx = ::minimum(this->cx, s.cx); this->cy = ::minimum(this->cy, s.cy); return *this; }
   inline size_type & ensure_at_least(const size_type & s) noexcept { this->cx = ::maximum(this->cx, s.cx); this->cy = ::maximum(this->cy, s.cy); return *this; }

   inline static size_type unit_size() { return size_type(1, 1); }

   inline size_type aspect_width(UNIT_TYPE w) { return size_type(w, w * this->cy / this->cx); }
   inline size_type aspect_height(UNIT_TYPE h) { return size_type(h * this->cx / this->cy, h); }
   inline ::design::e_fit get_fit(size_type s) { return (::design::e_fit) ::papaya::sgn(s.cx *this->cy - s.cy * this->cx); }
   inline size_type fit(size_type s)
   {
      if (get_fit(s) == ::design::fit_height) return aspect_height(s.cy); else return aspect_width(s.cx);
   }
   inline ::design::e_match get_expand(size_type s) { return (::design::e_match)(-(int)get_fit(s)); }
   inline size_type expand(size_type s)
   {
      if (get_expand(s) == ::design::match_height) return aspect_height(s.cy); else return aspect_width(s.cx);
   }

   inline size_type & operator=(const size_type & size) noexcept { this->cx = size.cx; this->cy = size.cy; return *this; }

   template < primitive_size SIZE > 
   inline size_type & operator+=(const SIZE & size) noexcept { this->cx += size.cx; this->cy += size.cy; return *this; }

   template < primitive_size SIZE >
   inline size_type & operator-=(const SIZE & size) noexcept { this->cx -= size.cx; this->cy -= size.cy; return *this; }

   template < primitive_point POINT >
   inline size_type & operator+=(const POINT & point) noexcept { this->cx += point.x; this->cy += point.y; return *this; }

   template < primitive_point POINT >
   inline size_type & operator-=(const POINT & point) noexcept { this->cx -= point.x; this->cy -= point.y; return *this; }

   template < primitive_number NUMBER >
   inline size_type & operator+=(NUMBER n) noexcept { this->cx = UNIT_TYPE(this->cx + n); this->cy = UNIT_TYPE(this->cy + n); return *this; }

   template < primitive_number NUMBER >
   inline size_type & operator-=(NUMBER n) noexcept { this->cx = UNIT_TYPE(this->cx - n); this->cy = UNIT_TYPE(this->cy - n); return *this; }

   template < primitive_number NUMBER >
   inline size_type & operator*=(NUMBER n) noexcept { this->cx = UNIT_TYPE(this->cx * n); this->cy = UNIT_TYPE(this->cy * n); return *this; }

   template < primitive_number NUMBER >
   inline size_type & operator/=(NUMBER n) noexcept { this->cx = UNIT_TYPE(this->cx / n); this->cy = UNIT_TYPE(this->cy / n); return *this; }

   inline void set_size(UNIT_TYPE cx, UNIT_TYPE cy) noexcept {this->cx = cx; this->cy = cy; }
   inline void set_size(const size_type & size_type) noexcept { set_size(size_type.cx, size_type.cy); }

   template < primitive_size SIZE >
   inline size_type operator+(const SIZE & size) const noexcept { return size_type((UNIT_TYPE) (this->cx + size.cx), (UNIT_TYPE) (this->cy + size.cy)); }
   template < primitive_size SIZE >
   inline size_type operator-(const SIZE & size) const noexcept { return size_type((UNIT_TYPE) (this->cx - size.cx), (UNIT_TYPE) (this->cy - size.cy)); }

   inline size_type operator-() const noexcept { return size_type(-this->cx, -this->cy); }

//#ifdef WINDOWS
//   inline size_type operator /(int i) const noexcept { return size_type((UNIT_TYPE)(this->cx / i), (UNIT_TYPE)(this->cy / i)); }
//#endif
   inline size_type operator /(i32 l) const noexcept { return size_type((UNIT_TYPE)(this->cx / l), (UNIT_TYPE)(this->cy / l)); }
   inline size_type operator /(i64 i) const noexcept { return size_type((UNIT_TYPE)(this->cx / i), (UNIT_TYPE)(this->cy / i)); }
   inline size_type operator /(float f) const noexcept { return size_type((UNIT_TYPE)(this->cx / f), (UNIT_TYPE)(this->cy / f)); }
   inline size_type operator /(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx / d), (UNIT_TYPE)(this->cy / d)); }

   inline size_type operator *(int i) const noexcept { return size_type(this->cx * i, this->cy * i); }
   inline size_type operator *(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx * d), (UNIT_TYPE)(this->cy * d)); }

   inline size_type operator +(int i) const noexcept { return size_type(this->cx + i, this->cy + i); }
   inline size_type operator +(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx + d), (UNIT_TYPE)(this->cy + d)); }

   inline size_type operator -(int i) const noexcept { return size_type(this->cx - i, this->cy - i); }
   inline size_type operator -(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx - d), (UNIT_TYPE)(this->cy - d)); }


   inline size_type half_away(const size_type& size) { return size_type((this->cx - size.cx) / (UNIT_TYPE) 2, (this->cy - size.cy) / (UNIT_TYPE)2); }

   inline bool operator==(::std::nullptr_t) const noexcept { return ::is_size_null(this); }
   inline bool operator!=(::std::nullptr_t) const noexcept { return !operator==(nullptr); }

   inline bool operator == (const size_type & size) const noexcept { return this->cx == size.cx && this->cy == size.cy; }
   inline bool operator != (const size_type & size) const noexcept { return !operator ==(size); }

   inline bool operator == (const RECTANGLE_TYPE & rectangle) const noexcept { return this->cx == rectangle.width() && this->cy == rectangle.height(); }
   inline bool operator != (const RECTANGLE_TYPE & rectangle) const noexcept { return !operator ==(rectangle); }

   inline bool operator > (const size_type & size) const noexcept { return this->cx > size.cx && this->cy > size.cy; }
   inline bool operator >= (const size_type & size) const noexcept { return this->cx >= size.cx && this->cy >= size.cy; }
   inline bool operator < (const size_type & size) const noexcept { return this->cx < size.cx && this->cy < size.cy; }
   inline bool operator <= (const size_type & size) const noexcept { return this->cx <= size.cx && this->cy <= size.cy; }

   inline bool operator > (const RECTANGLE_TYPE & rectangle) const noexcept { return this->operator > (rectangle.size()); }
   inline bool operator >= (const RECTANGLE_TYPE & rectangle) const noexcept { return this->operator >= (rectangle.size()); }
   inline bool operator < (const RECTANGLE_TYPE & rectangle) const noexcept { return this->operator < (rectangle.size()); }
   inline bool operator <= (const RECTANGLE_TYPE & rectangle) const noexcept { return this->operator <= (rectangle.size()); }

   inline bool any_gt (const size_type & size) const noexcept { return this->cx > size.cx || this->cy > size.cy; }
   inline bool any_ge (const size_type & size) const noexcept { return this->cx >= size.cx || this->cy >= size.cy; }
   inline bool any_lt (const size_type & size) const noexcept { return this->cx < size.cx || this->cy < size.cy; }
   inline bool any_le (const size_type & size) const noexcept { return this->cx <= size.cx || this->cy <= size.cy; }

   inline bool any_gt (const RECTANGLE_TYPE & rectangle) const noexcept { return this->any_gt(rectangle.size()); }
   inline bool any_ge (const RECTANGLE_TYPE & rectangle) const noexcept { return this->any_ge(rectangle.size()); }
   inline bool any_lt (const RECTANGLE_TYPE & rectangle) const noexcept { return this->any_lt(rectangle.size()); }
   inline bool any_le (const RECTANGLE_TYPE & rectangle) const noexcept { return this->any_le(rectangle.size()); }

};




inline auto abs(const ::size_i32& size) noexcept { return ::size_i32(abs(size.cx), abs(size.cy)); }
inline auto abs(const ::size_i64& size) noexcept { return ::size_i64(abs(size.cx), abs(size.cy)); }
inline auto abs(const ::size_f32& size) noexcept { return ::size_f32(abs(size.cx), abs(size.cy)); }
inline auto abs(const ::size_f64& size) noexcept { return ::size_f64(abs(size.cx), abs(size.cy)); }


