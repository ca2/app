#pragma once






template < primitive_number NUMBER >
class shift_type
{
public:

   using UNIT_TYPE = NUMBER;

   NUMBER greekdeltax;
   NUMBER greekdeltay;


   shift_type() noexcept { this->greekdeltax = (UNIT_TYPE)0; this->greekdeltay = (UNIT_TYPE)0; }
   shift_type(enum_no_initialize) noexcept {  }
   shift_type(::std::nullptr_t) noexcept { this->greekdeltax = (UNIT_TYPE)0; this->greekdeltay = (UNIT_TYPE)0; }
   template < primitive_number X, primitive_number Y >
   shift_type(X x, Y y) noexcept { this->greekdeltax = (UNIT_TYPE) x; this->greekdeltay = (UNIT_TYPE) y; }
   template < primitive_point POINT >
   shift_type(const POINT & point) { this->greekdeltax = (UNIT_TYPE)point.x(); this->greekdeltay = (UNIT_TYPE)point.y(); }
   template < primitive_size SIZE >
   shift_type(const SIZE & size) { this->greekdeltax = (UNIT_TYPE)size.cx(); this->greekdeltay = (UNIT_TYPE)size.cy(); }


   shift_type operator -() const {  return { -this->greekdeltax, -this->greekdeltay }; }


   shift_type operator +(const shift_type & shift) const { return { this->greekdeltax + shift.greekdeltax, this->greekdeltay + shift.greekdeltay }; }
   shift_type operator -(const shift_type & shift) const { return { this->greekdeltax - shift.greekdeltax, this->greekdeltay - shift.greekdeltay }; }
   

   template < primitive_point POINT >
   inline POINT & operator()(POINT & point) const noexcept 
   { 
      
      point.x() = (::std::decay_t<decltype(point.x())>)(point.x() + this->greekdeltax);
      
      point.y() = (::std::decay_t<decltype(point.y())>)(point.y() + this->greekdeltay);
      
      return point; 
   
   }


   template < primitive_size SIZE >
   inline SIZE & operator()(SIZE & size) const noexcept
   { 
      
      size.cx() = (::std::decay_t<decltype(size.cx())>)(size.cx() + this->greekdeltax);
      
      size.cy() = (::std::decay_t<decltype(size.cy())>)(size.cy() + this->greekdeltay);
      
      return size; 
   
   }

   
   template < primitive_rectangle RECTANGLE >
   inline RECTANGLE & operator()(RECTANGLE & rectangle) const noexcept
   { 
      
      rectangle.left = (::std::decay_t<decltype(rectangle.left)>)(rectangle.left + this->greekdeltax);
      
      rectangle.top = (::std::decay_t<decltype(rectangle.top)>)(rectangle.top + this->greekdeltay);
      
      rectangle.right = (::std::decay_t<decltype(rectangle.right)>)(rectangle.right + this->greekdeltax);
      
      rectangle.bottom = (::std::decay_t<decltype(rectangle.bottom)>)(rectangle.bottom + this->greekdeltay);
      
      return rectangle;
   
   }


   template < primitive_point POINT >
   inline POINT get(const POINT & point) const noexcept { return { (decltype(point.x()))(point.x() + this->greekdeltax), (decltype(point.y()))(point.y() + this->greekdeltay) }; }

   template < primitive_size SIZE >
   inline SIZE get(const SIZE & size) const noexcept { return { (decltype(size.cx()))(size.cx() + this->greekdeltax), (decltype(size.cy()))(size.cy() + this->greekdeltay) }; }

   template < primitive_rectangle RECTANGLE >
   inline RECTANGLE get(const RECTANGLE & rectangle) const noexcept { return { (decltype(rectangle.left))(rectangle.left + this->greekdeltax), (decltype(rectangle.top))(rectangle.top + this->greekdeltay), (decltype(rectangle.right))(rectangle.right + this->greekdeltax), (decltype(rectangle.bottom))(rectangle.bottom + this->greekdeltay) }; }


};


using shift_i32 = shift_type < ::i32 >;



