#pragma once



struct SHIFT_I32
{

   int Δx;
   int Δy;

};


template < typename SHIFT >
class shift_type :
   public SHIFT
{
public:

   using UNIT_TYPE = decltype(SHIFT::Δx);


   shift_type() noexcept { this->Δx = (UNIT_TYPE)0; this->Δy = (UNIT_TYPE)0; }
   shift_type(enum_no_initialize) noexcept {  }
   shift_type(::std::nullptr_t) noexcept { this->Δx = (UNIT_TYPE)0; this->Δy = (UNIT_TYPE)0; }
   template < primitive_number X, primitive_number Y >
   shift_type(X x, Y y) noexcept { this->Δx = (UNIT_TYPE) x; this->Δy = (UNIT_TYPE) y; }
   template < primitive_point POINT >
   shift_type(const POINT & point) { this->Δx = (UNIT_TYPE)point.x; this->Δy = (UNIT_TYPE)point.y; }
   template < primitive_size SIZE >
   shift_type(const SIZE & size) { this->Δx = (UNIT_TYPE)size.cx; this->Δy = (UNIT_TYPE)size.cy; }


   shift_type operator -() const {  return { -this->Δx, -this->Δy }; }


   shift_type operator +(const SHIFT & shift) const { return { this->Δx + shift.Δx, this->Δy + shift.Δy }; }
   shift_type operator -(const SHIFT & shift) const { return { this->Δx - shift.Δx, this->Δy - shift.Δy }; }
   

   template < primitive_point POINT >
   inline POINT & operator()(POINT & point) const noexcept { point.x = (decltype(point.x)(point.x + this->Δx)); point.y = (decltype(point.y)(point.y + this->Δy)); return point; }

   template < primitive_size SIZE >
   inline SIZE & operator()(SIZE & size) const noexcept { size.cx = (decltype(size.cx)(size.cx + this->Δx)); size.cy = (decltype(size.cy)(size.cy + this->Δy)); return size; }

   template < primitive_rectangle RECTANGLE >
   inline RECTANGLE & operator()(RECTANGLE & rectangle) const noexcept { rectangle.left = (decltype(rectangle.left)(rectangle.left + this->Δx)); rectangle.top = (decltype(rectangle.top)(rectangle.top + this->Δy)); rectangle.right = (decltype(rectangle.right)(rectangle.right + this->Δx)); rectangle.bottom = (decltype(rectangle.bottom)(rectangle.bottom + this->Δy)); return rectangle; }


   template < primitive_point POINT >
   inline POINT get(const POINT & point) const noexcept { return { (decltype(point.x)(point.x + this->Δx)), (decltype(point.y)(point.y + this->Δy)) }; }

   template < primitive_size SIZE >
   inline SIZE get(const SIZE & size) const noexcept { return { (decltype(size.cx)(size.cx + this->Δx)), (decltype(size.cy)(size.cy + this->Δy)) }; }

   template < primitive_rectangle RECTANGLE >
   inline RECTANGLE get(const RECTANGLE & rectangle) const noexcept { return { (decltype(rectangle.left)(rectangle.left + this->Δx)), (decltype(rectangle.top)(rectangle.top + this->Δy)), (decltype(rectangle.right)(rectangle.right + this->Δx)), (decltype(rectangle.bottom)(rectangle.bottom + this->Δy)) }; }


};


using shift_i32 = shift_type < SHIFT_I32 >;



