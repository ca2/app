#pragma once



// Δ greek delta


template < prototype_number NUMBER >
class shift_type
{
public:

   using UNIT_TYPE = NUMBER;

   NUMBER Δx;
   NUMBER Δy;


   shift_type() noexcept { this->Δx = (UNIT_TYPE)0; this->Δy = (UNIT_TYPE)0; }
   shift_type(no_initialize_t) noexcept {  }
   shift_type(nullptr_t) noexcept { this->Δx = (UNIT_TYPE)0; this->Δy = (UNIT_TYPE)0; }
   template < prototype_number X, prototype_number Y >
   shift_type(X x, Y y) noexcept { this->Δx = (UNIT_TYPE) x; this->Δy = (UNIT_TYPE) y; }
   template < prototype_sequence2 SEQUENCE >
   shift_type(const SEQUENCE & s) { this->Δx = (UNIT_TYPE)s.x; this->Δy = (UNIT_TYPE)s.y; }
   // template < prototype_size SIZE >
   // shift_type(const SIZE & size) { this->Δx = (UNIT_TYPE)size.cx; this->Δy = (UNIT_TYPE)size.cy; }


   shift_type operator -() const {  return { -this->Δx, -this->Δy }; }


   shift_type operator +(const shift_type & shift) const { return { this->Δx + shift.Δx, this->Δy + shift.Δy }; }
   shift_type operator -(const shift_type & shift) const { return { this->Δx - shift.Δx, this->Δy - shift.Δy }; }
   

   template < prototype_sequence2 SEQUENCE >
   inline SEQUENCE & operator()(SEQUENCE & s) const noexcept
   requires (!prototype_rectangle<SEQUENCE>)
   { 
      
      s.x = (::std::decay_t<decltype(s.x)>)(s.x + this->Δx);
      
      s.y = (::std::decay_t<decltype(s.y)>)(s.y + this->Δy);
      
      return s;
   
   }


   // template < prototype_size SIZE >
   // inline SIZE & operator()(SIZE & size) const noexcept
   // {
   //
   //    size.cx = (::std::decay_t<decltype(size.cx)>)(size.cx + this->Δx);
   //
   //    size.cy = (::std::decay_t<decltype(size.cy)>)(size.cy + this->Δy);
   //
   //    return size;
   //
   // }

   
   template < prototype_rectangle RECTANGLE >
   inline RECTANGLE & operator()(RECTANGLE & rectangle) const noexcept
   {
      
      rectangle.left = (::std::decay_t<decltype(rectangle.left)>)(rectangle.left + this->Δx);
      
      rectangle.top = (::std::decay_t<decltype(rectangle.top)>)(rectangle.top + this->Δy);
      
      rectangle.right = (::std::decay_t<decltype(rectangle.right)>)(rectangle.right + this->Δx);
      
      rectangle.bottom = (::std::decay_t<decltype(rectangle.bottom)>)(rectangle.bottom + this->Δy);
      
      return rectangle;
   
   }


   template < prototype_point POINT >
   inline POINT get(const POINT & point) const noexcept { return { (decltype(point.x))(point.x + this->Δx), (decltype(point.y))(point.y + this->Δy) }; }

   template < prototype_size SIZE >
   inline SIZE get(const SIZE & size) const noexcept { return { (decltype(size.cx))(size.cx + this->Δx), (decltype(size.cy))(size.cy + this->Δy) }; }

   template < prototype_rectangle RECTANGLE >
   inline RECTANGLE get(const RECTANGLE & rectangle) const noexcept { return { (decltype(rectangle.left))(rectangle.left + this->Δx), (decltype(rectangle.top))(rectangle.top + this->Δy), (decltype(rectangle.right))(rectangle.right + this->Δx), (decltype(rectangle.bottom))(rectangle.bottom + this->Δy) }; }


};


using shift_int = shift_type < int >;



