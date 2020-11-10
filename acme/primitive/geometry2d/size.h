#pragma once


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename RECT_BASE_TYPE >
class size_type :
   public BASE_TYPE
{
public:


   using SIZE_BASE_TYPE = BASE_TYPE;
   using UNIT_TYPE = decltype(SIZE_BASE_TYPE::cx);
   using POINT_TYPE = point_type < POINT_BASE_TYPE, SIZE_BASE_TYPE, RECT_BASE_TYPE >;
   using RECT_TYPE = rect_type < RECT_BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE >;


   size_type() noexcept { this->cx = 0; this->cy = 0; }
   size_type(e_no_init) noexcept {}
   size_type(::std::nullptr_t) noexcept { this->cx = 0; this->cy = 0; }
   size_type(UNIT_TYPE cx, UNIT_TYPE cy) noexcept { this->cx = cx; this->cy = cy; }
   size_type(::u32 u) noexcept : size_type(__u32xy(u)) {}
   size_type(::u64 u) noexcept : size_type(__u64xy(u)) {}
   size_type(const POINT_TYPE& point) noexcept;
   size_type(const RECT_TYPE& rect) noexcept;
   size_type(const SIZE32& size) noexcept : size_type((UNIT_TYPE)size.cx, (UNIT_TYPE)size.cy) {}
   size_type(const SIZE64& size) noexcept : size_type((UNIT_TYPE)size.cx, (UNIT_TYPE)size.cy) {}
   size_type(const SIZEF& size) noexcept : size_type((UNIT_TYPE)size.cx, (UNIT_TYPE)size.cy) {}
   size_type(const SIZED& size) noexcept : size_type((UNIT_TYPE)size.cx, (UNIT_TYPE)size.cy) {}
   size_type(const SIZE32* psize) noexcept : size_type(*psize) {}
   size_type(const SIZE64* psize) noexcept : size_type(*psize) {}
   size_type(const SIZEF* psize) noexcept : size_type(*psize) {}
   size_type(const SIZED* psize) noexcept : size_type(*psize) {}
#ifdef APPLEOS
   size_type(const CGSize& size) noexcept : size_type((UNIT_TYPE)size.width, (UNIT_TYPE)size.height) {}
   size_type(const CGSize *psize) noexcept : size_type(*psize) {}
#endif


   operator SIZE32* () noexcept { return this; }
   operator const SIZE32* () const noexcept { return this; }
   operator bool () const noexcept { return is_set(); }


   size_type& Null() { this->cx = (UNIT_TYPE)0; this->cy = (UNIT_TYPE)0; return *this; }

   POINT_TYPE operator+(const POINT_TYPE& point1) const noexcept { POINT_TYPE point(point1); ::offset_point(&point, this->cx, this->cy); return point; }
   POINT_TYPE operator-(const POINT_TYPE& point1) const noexcept { POINT_TYPE point(this->cx, this->cy); ::offset_point(&point, -point1.x, -point1.y); return point;   }

   RECT_TYPE operator+(const RECT_TYPE& rect1) const noexcept { RECT_TYPE rect(rect1); ::offset_rect(&rect, this->cx, this->cy); return rect; }
   RECT_TYPE operator-(const RECT_TYPE& rect1) const noexcept { RECT_TYPE rect(rect1); ::offset_rect(&rect, -this->cx, -this->cy); return rect; }

   UNIT_TYPE area() const noexcept { return ::rect_area(this->cx, this->cy); }
   inline bool is_empty() const noexcept { return this->cx <= 0 || this->cy <= 0; }
   inline bool is_set() const noexcept { return !is_empty(); }


   ::u32    u32() const noexcept { return __u32(this->cx, this->cy); }
   ::u64    u64() const noexcept { return __u64(this->cx, this->cy); }
   LPARAM    lparam() const noexcept { return MAKELPARAM(this->cx, this->cy); }

   inline UNIT_TYPE width() const noexcept { return this->cx; }
   inline UNIT_TYPE height() const noexcept { return this->cy; }

   inline UNIT_TYPE get_minimum_dimension() const noexcept { return ::min(this->cx, this->cy); }
   inline UNIT_TYPE get_maximum_dimension() const noexcept { return ::max(this->cx, this->cy); }

   inline UNIT_TYPE get_dimension(e_orientation eorientation) const noexcept { return ::get_dimension(eorientation, this->cx, this->cy); }
   inline UNIT_TYPE get_orthogonal_dimension(e_orientation eorientation) const noexcept { return ::get_normal_dimension(eorientation, this->cx, this->cy); }
   inline UNIT_TYPE get_orthogonal(e_orientation eorientation)const noexcept { return get_orthogonal_dimension(eorientation); }
   inline UNIT_TYPE get_normal_dimension(e_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }
   inline UNIT_TYPE get_normal(e_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }

   inline UNIT_TYPE set_dimension(e_orientation eorientation, UNIT_TYPE l) noexcept { if (eorientation == orientation_horizontal) this->cx = l; else if (eorientation == orientation_vertical) this->cy = l; return l; }
   inline UNIT_TYPE set_orthogonal_dimension(e_orientation eorientation, UNIT_TYPE l) noexcept { if(eorientation == orientation_horizontal) this->cy = l; else if (eorientation == orientation_vertical) this->cx = l; return l;}
   inline UNIT_TYPE set_orthogonal(e_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation, l); }
   inline UNIT_TYPE set_normal_dimension(e_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation, l); }
   inline UNIT_TYPE set_normal(e_orientation eorientation, UNIT_TYPE l) noexcept { return set_orthogonal_dimension(eorientation, l); }

   inline void set(UNIT_TYPE c) noexcept { this->cx = this->cy = c; }
   inline void set(UNIT_TYPE cx, UNIT_TYPE cy) noexcept { this->cx = cx; this->cy = cy; }

   inline size_type min(const size_type & s)const noexcept { return size_type(::min(this->cx, s.cx), ::min(this->cy, s.cy)); }
   inline size_type max(const size_type& s)const noexcept { return size_type(::max(this->cx, s.cx), ::max(this->cy, s.cy)); }

   inline size_type & ensure_at_most(const size_type & s) noexcept { this->cx = ::min(this->cx, s.cx); this->cy = ::min(this->cy, s.cy); return *this; }
   inline size_type & ensure_at_least(const size_type & s) noexcept { this->cx = ::max(this->cx, s.cx); this->cy = ::max(this->cy, s.cy); return *this; }

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


   inline size_type & operator+=(const size_type & size) noexcept { this->cx += size.cx; this->cy += size.cy; return *this; }
   inline size_type & operator-=(const size_type & size) noexcept { this->cx -= size.cx; this->cy -= size.cy; return *this; }

   inline size_type & operator+=(const POINT_TYPE & point) noexcept { this->cx += point.x; this->cy += point.y; return *this; }
   inline size_type & operator-=(const POINT_TYPE & point) noexcept { this->cx -= point.x; this->cy -= point.y; return *this; }

   inline void set_size(UNIT_TYPE cx, UNIT_TYPE cy) noexcept {this->cx = cx; this->cy = cy; }
   inline void set_size(const size_type & size_type) noexcept { set_size(size_type.cx, size_type.cy); }

   inline size_type operator+(const size_type & size) const noexcept { return size_type(this->cx + size.cx, this->cy + size.cy); }
   inline size_type operator-(const size_type & size) const noexcept { return size_type(this->cx - size.cx, this->cy - size.cy); }

   inline size_type operator-() const noexcept { return size_type(-this->cx, -this->cy); }

#ifdef WINDOWS
   inline size_type operator /(int i) const noexcept { return size_type((UNIT_TYPE)(this->cx / i), (UNIT_TYPE)(this->cy / i)); }
#endif
   inline size_type operator /(::i32 l) const noexcept { return size_type((UNIT_TYPE)(this->cx / l), (UNIT_TYPE)(this->cy / l)); }
   inline size_type operator /(i64 i) const noexcept { return size_type((UNIT_TYPE)(this->cx / i), (UNIT_TYPE)(this->cy / i)); }
   inline size_type operator /(float f) const noexcept { return size_type((UNIT_TYPE)(this->cx / f), (UNIT_TYPE)(this->cy / f)); }
   inline size_type operator /(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx / d), (UNIT_TYPE)(this->cy / d)); }

   inline size_type operator *(int i) const noexcept { return size_type(this->cx * i, this->cy * i); }
   inline size_type operator *(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx * d), (UNIT_TYPE)(this->cy * d)); }

   inline size_type operator +(int i) const noexcept { return size_type(this->cx + i, this->cy + i); }
   inline size_type operator +(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx + d), (UNIT_TYPE)(this->cy + d)); }

   inline size_type operator -(int i) const noexcept { return size_type(this->cx - i, this->cy - i); }
   inline size_type operator -(double d) const noexcept { return size_type((UNIT_TYPE)(this->cx - d), (UNIT_TYPE)(this->cy - d)); }


   inline size_type half_away(const size_type& size) { return (*this - size) / (UNIT_TYPE) 2; }

   inline bool operator==(::std::nullptr_t) const noexcept { return ::is_size_null(this); }
   inline bool operator!=(::std::nullptr_t) const noexcept { return !operator==(nullptr); }

   inline bool operator == (const size_type & size) const noexcept { return this->cx == size.cx && this->cy == size.cy; }
   inline bool operator != (const size_type & size) const noexcept { return !operator ==(size); }

   inline bool operator == (const RECT_TYPE & rect) const noexcept { return this->cx == rect.width() && this->cy == rect.height(); }
   inline bool operator != (const RECT_TYPE & rect) const noexcept { return !operator ==(rect); }

   inline bool operator > (const size_type & size) const noexcept { return this->cx > size.cx && this->cy > size.cy; }
   inline bool operator >= (const size_type & size) const noexcept { return this->cx >= size.cx && this->cy >= size.cy; }
   inline bool operator < (const size_type & size) const noexcept { return this->cx < size.cx && this->cy < size.cy; }
   inline bool operator <= (const size_type & size) const noexcept { return this->cx <= size.cx && this->cy <= size.cy; }

   inline bool operator > (const RECT_TYPE & rect) const noexcept { return this->operator > (rect.size()); }
   inline bool operator >= (const RECT_TYPE & rect) const noexcept { return this->operator >= (rect.size()); }
   inline bool operator < (const RECT_TYPE & rect) const noexcept { return this->operator < (rect.size()); }
   inline bool operator <= (const RECT_TYPE & rect) const noexcept { return this->operator <= (rect.size()); }

   inline bool any_gt (const size_type & size) const noexcept { return this->cx > size.cx || this->cy > size.cy; }
   inline bool any_ge (const size_type & size) const noexcept { return this->cx >= size.cx || this->cy >= size.cy; }
   inline bool any_lt (const size_type & size) const noexcept { return this->cx < size.cx || this->cy < size.cy; }
   inline bool any_le (const size_type & size) const noexcept { return this->cx <= size.cx || this->cy <= size.cy; }

   inline bool any_gt (const RECT_TYPE & rect) const noexcept { return this->any_gt(rect.size()); }
   inline bool any_ge (const RECT_TYPE & rect) const noexcept { return this->any_ge(rect.size()); }
   inline bool any_lt (const RECT_TYPE & rect) const noexcept { return this->any_lt(rect.size()); }
   inline bool any_le (const RECT_TYPE & rect) const noexcept { return this->any_le(rect.size()); }

};




inline auto abs(const ::size& size) noexcept { return ::size(abs(size.cx), abs(size.cy)); }
inline auto abs(const ::size64& size) noexcept { return ::size64(abs(size.cx), abs(size.cy)); }
inline auto abs(const ::sizef& size) noexcept { return ::sizef(abs(size.cx), abs(size.cy)); }
inline auto abs(const ::sized& size) noexcept { return ::sized(abs(size.cx), abs(size.cy)); }


