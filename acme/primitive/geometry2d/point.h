#pragma once
//
//#undef new
//#ifdef WINDOWS_DESKTOP
//#include <gdiplus.h>
//#endif
//#define new ACME_NEW


template < typename BASE_TYPE, typename SIZE_BASE_TYPE, typename RECT_BASE_TYPE >
class point_type :
   public BASE_TYPE
{
public:


   using POINT_BASE_TYPE = BASE_TYPE;
   using UNIT_TYPE = decltype(POINT_BASE_TYPE::x);
   using SIZE_TYPE = size_type < SIZE_BASE_TYPE, POINT_BASE_TYPE, RECT_BASE_TYPE >;
   using RECT_TYPE = rect_type < RECT_BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE >;
   using POINT_ARRAY_TYPE = point_array_base < point_type >;


   point_type() noexcept { this->x = (UNIT_TYPE)0; this->y = (UNIT_TYPE)0; }
   point_type(enum_no_initialize) noexcept {  }
   point_type(::std::nullptr_t) noexcept { this->x = (UNIT_TYPE)0; this->y = (UNIT_TYPE)0; }
   point_type(UNIT_TYPE x, UNIT_TYPE y) noexcept { this->x = x; this->y = y; }
   //point_type(const ::lparam& lparam) noexcept : point_type(lparam.x(), lparam.y()) {}
   //point_type(const ::u32 u) noexcept : point_type((UNIT_TYPE) __u32x(u), (UNIT_TYPE)__u32y(u)) {}
   //point_type(const ::u64 u) noexcept : point_type((UNIT_TYPE)__u64x(u), (UNIT_TYPE)__u64y(u)) {}
   //point_type(const SIZE_TYPE & size) noexcept : point_type(size.cx, size.cy) {}
   template < primitive_point POINT >
   point_type(const POINT & point) noexcept { ::copy(this, &point); }

   template < primitive_point POINT >
   point_type(const POINT * ppoint) noexcept { ::copy(this, ppoint); }

   template < primitive_size SIZE >
   point_type(const SIZE & size) noexcept { ::copy(this, &size); }

   template < primitive_size SIZE >
   point_type(const SIZE * psize) noexcept { ::copy(this, psize); }

#ifdef WINDOWS
   //rect_type(const Gdiplus::Rect& t) noexcept : { ::copy(this, &t); }
   //rect_type(const Gdiplus::RectF& t) noexcept : { ::copy(this, &t); }
   //rect_type(const Gdiplus::Rect* p) noexcept : { ::copy(this, p); }
   //rect_type(const Gdiplus::RectF* p) noexcept : { ::copy(this, p); }
#endif
#ifdef APPLEOS
   point_type(const CGPoint & point) noexcept : point_type(point.x, point.y){}
   point_type(const CGPoint * ppoint) noexcept : point_type(ppoint->x, ppoint->y){}
#endif


   inline point_type & operator = (const point_type & point) { this->x = point.x; this->y = point.y; return *this; }

   operator POINT_BASE_TYPE*() noexcept { return this; }
   operator const POINT_BASE_TYPE*() const noexcept { return this; }
   operator ::lparam() const { return lparam(); }

   ::u32 u32() const noexcept { return __u32(this->x, this->y); }
   ::u64 u64() const noexcept { return __u64(this->x, this->y); }
   ::lparam lparam() const noexcept { return { this->x, this->y }; }

   point_type& Null() { this->x = (UNIT_TYPE)0; this->y = (UNIT_TYPE) 0;  return *this; }


   point_type & offset(UNIT_TYPE xOffset, UNIT_TYPE yOffset) noexcept { this->x += xOffset; this->y += yOffset; return *this; }
   point_type & offset(const point_type& point) noexcept { this->x += point.x; this->y += point.y; return *this; }
   point_type & offset(const SIZE_TYPE& size) noexcept { this->x += size.cx; this->y += size.cy; return *this; }
   point_type & set(UNIT_TYPE x, UNIT_TYPE y) noexcept { this->x = x; this->y = y; return *this; }



   inline UNIT_TYPE get_dimension(e_orientation eorientation) const noexcept { return ::get_dimension(eorientation, this->x, this->y); }
   inline UNIT_TYPE get_orthogonal_dimension(e_orientation eorientation) const noexcept { return ::get_normal_dimension(eorientation, this->x, this->y); }
   inline UNIT_TYPE get_orthogonal(e_orientation eorientation)const noexcept { return get_orthogonal_dimension(eorientation); }
   inline UNIT_TYPE get_normal_dimension(e_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }
   inline UNIT_TYPE get_normal(e_orientation eorientation) const noexcept { return get_orthogonal_dimension(eorientation); }


   inline UNIT_TYPE set_dimension(e_orientation eorientation, UNIT_TYPE l) noexcept;
   inline UNIT_TYPE set_orthogonal_dimension(e_orientation eorientation, UNIT_TYPE l) noexcept;
   inline UNIT_TYPE set_orthogonal(e_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation,l); }
   inline UNIT_TYPE set_normal_dimension(e_orientation eorientation, UNIT_TYPE l)  noexcept { return set_orthogonal_dimension(eorientation,l); }
   inline UNIT_TYPE set_normal(e_orientation eorientation, UNIT_TYPE l) noexcept { return set_orthogonal_dimension(eorientation,l); }




   inline bool operator==(const point_type & point) const noexcept { return (this->x == point.x && this->y == point.y); }
   inline bool operator!=(const point_type & point) const noexcept { return (this->x != point.x || this->y != point.y); }

   inline bool operator==(::std::nullptr_t) const noexcept { return ::is_point_null(this); }
   inline bool operator!=(::std::nullptr_t) const noexcept { return !::is_point_null(this); }

   template < primitive_size SIZE >
   inline point_type& operator+=(const SIZE& size) noexcept { this->x = (UNIT_TYPE) (this->x + size.cx); this->y = (UNIT_TYPE)(this->y + size.cy); return *this; }

   template < primitive_size SIZE >
   inline point_type& operator-=(const SIZE& size) noexcept { this->x = (UNIT_TYPE)(this->x - size.cx); this->y = (UNIT_TYPE)(this->y - size.cy); return *this; }

   template < primitive_point POINT >
   inline point_type& operator+=(const POINT& point) noexcept { this->x = (UNIT_TYPE)(this->x + point.x); this->y = (UNIT_TYPE)(this->y + point.y); return *this; }

   template < primitive_point POINT >
   inline point_type& operator-=(const POINT& point) noexcept { this->x = (UNIT_TYPE)(this->x - point.x); this->y = (UNIT_TYPE)(this->y - point.y); return *this; }

   template < primitive_size SIZE >
   inline point_type operator+(const SIZE & size) const noexcept { return point_type(this->x + size.cx, this->y + size.cy); }

   template < primitive_point POINT >
   inline point_type operator+(const POINT & point) const noexcept { return point_type(this->x + point.x, this->y + point.y); }

   template < primitive_point POINT >
   inline SIZE_TYPE operator-(const POINT & point) const noexcept { return SIZE_TYPE(this->x - point.x, this->y - point.y); }

   template < primitive_size SIZE >
   inline point_type operator-(const SIZE & size) const noexcept { return point_type(this->x - size.cx, this->y - size.cy); }

   inline point_type operator-() const noexcept { return point_type(-this->x, -this->y); }
   inline point_type operator+() const noexcept { return point_type(this->x, this->y); }
   //inline point_type operator+(const point_type& point) const noexcept { return point_type(this->x + point.x, this->y + point.y); }
   //inline SIZE_TYPE operator-(const point_type& point) const noexcept { return SIZE_TYPE(this->x - point.x, this->y - point.y); }

   inline RECT_TYPE operator+(const RECT_TYPE & rectangle) const noexcept { return RECT_TYPE(rectangle) + *this; }
   inline RECT_TYPE operator-(const RECT_TYPE & rectangle) const noexcept { return RECT_TYPE(rectangle) - *this; }

   void x_constraint(const RECT_TYPE& rectangle) noexcept
   {

      if (this->x < rectangle.left)
      {

         this->x = rectangle.left;

      }
      else if (this->x > rectangle.right)
      {

         this->x = rectangle.right;

      }

   }

   void y_constraint(const RECT_TYPE& rectangle) noexcept
   {

      if (this->y < rectangle.top)
      {

         this->y = rectangle.top;

      }
      else if (this->y > rectangle.bottom)
      {

         this->y = rectangle.bottom;

      }

   }

   void constraint(const RECT_TYPE & rectangle) noexcept
   {

      x_constraint(rectangle);

      y_constraint(rectangle);

   }



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


};





