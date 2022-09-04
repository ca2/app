#pragma once



struct SHIFT_I32
{

   int dx;
   int dy;

};


template < typename SHIFT >
class shift_type :
   public SHIFT
{
public:

   using UNIT_TYPE = decltype(SHIFT::dx);


   shift_type() noexcept { this->dx = (UNIT_TYPE)0; this->dy = (UNIT_TYPE)0; }
   shift_type(enum_no_initialize) noexcept {  }
   shift_type(::std::nullptr_t) noexcept { this->dx = (UNIT_TYPE)0; this->dy = (UNIT_TYPE)0; }
   template < primitive_number X, primitive_number Y >
   shift_type(X x, Y y) noexcept { this->dx = (UNIT_TYPE) x; this->dy = (UNIT_TYPE) y; }
   template < primitive_point POINT >
   shift_type(const POINT & point) { this->dx = (UNIT_TYPE)point.x; this->dy = (UNIT_TYPE)point.y; }
   template < primitive_size SIZE >
   shift_type(const SIZE & size) { this->dx = (UNIT_TYPE)size.cx; this->dy = (UNIT_TYPE)size.cy; }


   shift_type operator -() const {  return { -this->dx, -this->dy }; }


   shift_type operator +(const SHIFT & shift) const { return { this->dx + shift.dx, this->dy + shift.dy }; }
   shift_type operator -(const SHIFT & shift) const { return { this->dx - shift.dx, this->dy - shift.dy }; }
   

   template < primitive_point POINT >
   inline POINT & operator()(POINT & point) const noexcept { point.x = (decltype(point.x)(point.x + this->dx)); point.y = (decltype(point.y)(point.y + this->dy)); return point; }

   template < primitive_size SIZE >
   inline SIZE & operator()(SIZE & size) const noexcept { size.cx = (decltype(size.cx)(size.cx + this->dx)); size.cy = (decltype(size.cy)(size.cy + this->dy)); return size; }

   template < primitive_rectangle RECTANGLE >
   inline RECTANGLE & operator()(RECTANGLE & rectangle) const noexcept { rectangle.left = (decltype(rectangle.left)(rectangle.left + this->dx)); rectangle.top = (decltype(rectangle.top)(rectangle.top + this->dy)); rectangle.right = (decltype(rectangle.right)(rectangle.right + this->dx)); rectangle.bottom = (decltype(rectangle.bottom)(rectangle.bottom + this->dy)); return rectangle; }


   template < primitive_point POINT >
   inline POINT get(const POINT & point) const noexcept { return { (decltype(point.x)(point.x + this->dx)), (decltype(point.y)(point.y + this->dy)) }; }

   template < primitive_size SIZE >
   inline SIZE get(const SIZE & size) const noexcept { return { (decltype(size.cx)(size.cx + this->dx)), (decltype(size.cy)(size.cy + this->dy)) }; }

   template < primitive_rectangle RECTANGLE >
   inline RECTANGLE get(const RECTANGLE & rectangle) const noexcept { return { (decltype(rectangle.left)(rectangle.left + this->dx)), (decltype(rectangle.top)(rectangle.top + this->dy)), (decltype(rectangle.right)(rectangle.right + this->dx)), (decltype(rectangle.bottom)(rectangle.bottom + this->dy)) }; }


};


using shift_i32 = shift_type < SHIFT_I32 >;



