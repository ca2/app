#pragma once


#include "_function.h"
#include "point.h"
#include "size.h"
#include "acme/prototype/mathematics/numeric_info.h"

template < typename RECTANGLE_SOURCE >
concept rectangle_source = requires(RECTANGLE_SOURCE rectanglesource)
{
   
   {rectanglesource.rectangle_source_get()} -> primitive_rectangle;
   
};


template < primitive_number NUMBER >
class rectangle_type :
   public sequence_type < NUMBER, 4 >

{
public:


   //NUMBER left;
   //NUMBER top;
   //NUMBER right;
   //NUMBER bottom;


   //using RECTANGLE_BASE_TYPE = BASE_TYPE;
   using UNIT_TYPE = NUMBER;
   using POINT_TYPE = point_type < NUMBER >;
   using SIZE_TYPE = size_type < NUMBER >;
   //using POINT_ARRAY_TYPE = point_array_base < POINT_TYPE >;

   rectangle_type() { }
   rectangle_type(no_initialize_t) { }
   //rectangle_type(nullptr_t)  : rectangle_type(0, 0, 0, 0) {}

   template < primitive_number LEFT, primitive_number TOP, primitive_number RIGHT, primitive_number BOTTOM >
   rectangle_type(LEFT left, TOP top, RIGHT right, BOTTOM bottom)  :
      sequence_type < NUMBER, 4 >((NUMBER) left, (NUMBER) top, (NUMBER) right, (NUMBER) bottom)
   { 
   }

   template < primitive_number A, primitive_number B >
   rectangle_type(A a, B b)  : rectangle_type(a, b, a, b) {}

   template < primitive_number N >
   rectangle_type(N n)  : rectangle_type(n, n) {}


//#ifdef APPLE
//   rectangle_type(const CGRect & t)  : { ::copy(*this, &t); }
//   rectangle_type(const Gdiplus::RectF & t)  : { ::copy(this, &t); }
//   rectangle_type(const CGRect * p)  : { ::copy(this, p); }
//   rectangle_type(const Gdiplus::RectF * p)  : { ::copy(this, p); }
//#endif
   template < primitive_point POINT, primitive_size SIZE >
   rectangle_type(const POINT & point, const SIZE & size) :
      rectangle_type((UNIT_TYPE)point.x(), (UNIT_TYPE)point.y(), (UNIT_TYPE)(point.x() + size.cx()), (UNIT_TYPE)(point.y() + size.cy())) 
   {
   }
   template < primitive_size SIZE >
   rectangle_type(const SIZE & size) : rectangle_type(0, 0, size.cx(), size.cy()) {}
   template < primitive_point POINT1, primitive_point POINT2 >
   rectangle_type(const POINT1 & point1, const POINT2 & point2) { top_left() = point1; bottom_right() = point2; }
   template < primitive_rectangle RECTANGLE >
   rectangle_type(const RECTANGLE & t) :
   sequence_type < NUMBER, 4 >(t)
   {
      
//      this->left() = (UNIT_TYPE) t.left();
//      this->top() = (UNIT_TYPE) t.top();
//      this->right() = (UNIT_TYPE) t.right();
//      this->bottom() = (UNIT_TYPE) t.bottom();
      
   }
   template < struct_rectangle RECTANGLE >
   rectangle_type(const RECTANGLE & r) :
      sequence_type < NUMBER, 4 >(r.left, r.top, r.right, r.bottom)
   {
   }
   template < rectangle_source RECTANGLE_SOURCE >
   rectangle_type(RECTANGLE_SOURCE * prectanglesource) :
   rectangle_type(prectanglesource->rectangle_source_get())
   {
    
   }
      // template < primitive_rectangle RECTANGLE >
   // rectangle_type & operator =(const RECTANGLE & rectangle) 
   // {
      
   //    if((void *) this != (void *) &rectangle)
   //    {
      
   //       this->left() = (UNIT_TYPE) rectangle.left();
   //       this->top() = (UNIT_TYPE) rectangle.top();
   //       this->right() = (UNIT_TYPE) rectangle.right();
   //       this->bottom() = (UNIT_TYPE) rectangle.bottom();
      
   //    }
      
   //    return *this;
      
   // }
   

   template < primitive_origin_size ORIGIN_SIZE >
   rectangle_type(const ORIGIN_SIZE & originsize) 
   {
      
      this->left() = (UNIT_TYPE) originsize.origin.x;
      this->top() = (UNIT_TYPE) originsize.origin.y;
      this->right() = (UNIT_TYPE) (originsize.origin.x + originsize.size.width);
      this->bottom() = (UNIT_TYPE) (originsize.origin.y + originsize.size.height);
      
      //return *this;
      
   }


//   constexpr const UNIT_TYPE & x() const {return this->a();}
//   UNIT_TYPE & x() {return this->a();}
//   constexpr const UNIT_TYPE & y() const {return this->b();}
//   UNIT_TYPE & y() {return this->b();}


   constexpr const UNIT_TYPE & left() const {return this->a();}
   UNIT_TYPE & left() {return this->a();}
   constexpr const UNIT_TYPE & top() const {return this->b();}
   UNIT_TYPE & top() {return this->b();}

   constexpr const UNIT_TYPE & right() const {return this->c();}
   UNIT_TYPE & right() {return this->c();}
   constexpr const UNIT_TYPE & bottom() const {return this->d();}
   UNIT_TYPE & bottom() {return this->d();}

   auto & origin()  { return top_left(); }
   const auto & origin() const  { return top_left(); }
   const auto & bottom_right() const  { return ((rectangle_type *)this)->bottom_right(); }
   const auto & top_left() const  { return ((rectangle_type *)this)->top_left(); }
   UNIT_TYPE center_x() const { return (this->left() + this->right()) / (UNIT_TYPE)2; }
   UNIT_TYPE center_y() const { return (this->top() + this->bottom()) / (UNIT_TYPE)2; }
   POINT_TYPE center() const  { return POINT_TYPE(center_x(), center_y()); }


   inline bool is_set() const  { return !is_empty(); }
   inline bool is_empty() const  { return ::is_empty(*this); }
   inline bool is_null() const  { return ::is_null(*this); }
   template < primitive_point POINT >
   inline bool contains(const POINT & point) const  { return ::contains(*this, point.x(), point.y()); }
   inline bool contains_x(UNIT_TYPE x) const  { return ::contains_x(*this, x); }
   inline bool contains_y(UNIT_TYPE y) const  { return ::contains_y(*this, y); }


   template < typename SIZE >
   rectangle_type & ensure_at_least(const SIZE & size)
   {

      this->right() = (UNIT_TYPE)::maximum(this->right(), this->left() + size.cx());
      this->bottom() = (UNIT_TYPE)::maximum(this->bottom(), this->top() + size.cy());

      return *this;

   }


   template < primitive_point POINT >
   inline ::point_f64 to_point_rate(const POINT & point) const
   {

      return { ((double)point.x() - (double)this->left()) / (double)width(),
         ((double)point.y() - (double)this->top()) / (double)height() };

   }

   inline POINT_TYPE from_point_rate(const ::point_f64 & point) const
   {

      return POINT_TYPE((UNIT_TYPE)(point.x() * (double)width() + (double)this->left()),
         (UNIT_TYPE)(point.y() * (double)height() + (double)this->top()));

   }

   //void align_outsize_rate(double x, double y, const rectangle_type& rectangle_type);
   inline POINT_TYPE top_right() const { return POINT_TYPE(this->right(), this->top()); }
   inline POINT_TYPE bottom_left() const { return POINT_TYPE(this->left(), this->bottom()); }

   // void assign(const rectangle_type& rectangle_type, enum_orientation eorientation) ;
    //void assign_normal(const rectangle_type& rectangle_type, enum_orientation eorientation) ;

   UNIT_TYPE minimum_dimension() const  { return ::minimum(width(), height()); }
   UNIT_TYPE maximum_dimension() const  { return ::maximum(width(), height()); }

   UNIT_TYPE max_border() const  { return ::maximum(::maximum(this->top(), this->left()), ::maximum(this->bottom(), this->right())); }

   UNIT_TYPE minimum_natural_dimension() const  { return ::minimum(::maximum((UNIT_TYPE)0, width()), ::maximum((UNIT_TYPE)0, height())); }
   UNIT_TYPE maximum_natural_dimension() const  { return ::maximum(::maximum((UNIT_TYPE)0, width()), ::maximum((UNIT_TYPE)0, height())); }

   UNIT_TYPE minimum_absolute_dimension() const  { return ::minimum(abs(width()), abs(height())); }
   UNIT_TYPE maximum_absolute_dimension() const  { return ::minimum(abs(width()), abs(height())); }

   //UNIT_TYPE minimum_signed_absolute_dimension(bool bNegativePreference = true) const ;
   //UNIT_TYPE maximum_signed_absolute_dimension(bool bPositivePreference = true) const ;

   UNIT_TYPE get_dimension(enum_orientation eorientation, ::collection::index i)
   {

      return eorientation == e_orientation_horizontal ?
         (i == 0 ? left() : right()) :
         (i == 0 ? top() : bottom());

   }

   UNIT_TYPE get_normal_dimension(enum_orientation eorientation, ::collection::index i)
   {

      return eorientation == e_orientation_vertical ?
         (i == 0 ? left() : right()) :
         (i == 0 ? top() : bottom());

   }

   UNIT_TYPE get_first_dimension(enum_orientation eorientation)
   {

      return eorientation == e_orientation_horizontal ?
         (left()) :
         (top());

   }

   UNIT_TYPE get_first_normal_dimension(enum_orientation eorientation)
   {

      return eorientation == e_orientation_vertical ?
         (right()) :
         (bottom());

   }

   UNIT_TYPE get_second_dimension(enum_orientation eorientation)
   {

      return eorientation == e_orientation_horizontal ?
         (right()) :
         (bottom());

   }

   UNIT_TYPE get_second_normal_dimension(enum_orientation eorientation)
   {

      return eorientation == e_orientation_vertical ?
         (right()) :
         (bottom());

   }

   UNIT_TYPE get_total_dimension(enum_orientation eorientation)
   {

      return eorientation == e_orientation_horizontal ?
         left() + right() :
         top() + bottom();

   }

   UNIT_TYPE get_normal_total_dimension(enum_orientation eorientation)
   {

      return eorientation == e_orientation_vertical ?
         left() + right() :
         top() + bottom();

   }


   UNIT_TYPE width() const  { return this->right() - this->left(); }
   UNIT_TYPE height() const  { return this->bottom() - this->top(); }
   SIZE_TYPE size() const  { return SIZE_TYPE(width(), height()); }

   void set_width(UNIT_TYPE cx)  { this->right() = this->left() + cx; }
   void set_height(UNIT_TYPE cy)  { this->bottom() = this->top() + cy; }
   void set_size(UNIT_TYPE cx, UNIT_TYPE cy)  { set_width(cx); set_height(cy); }
   void set_size(const SIZE_TYPE & size)  { set_size(size.cx(), size.cy()); }
   
   rectangle_type & set_center_and_half_size(const POINT_TYPE & center, const SIZE_TYPE & halfsize)
   {
      
      *this = with_center_and_half_size(center, halfsize);
      
      return *this;
      


   }

   rectangle_type & set_square_with_center(const POINT_TYPE & center, const UNIT_TYPE & apothem)
   {
      
      *this = square_with_center_and_apothem(center, apothem);
      
      return *this;
      
   }
   
   
   
   static rectangle_type with_center_and_half_size(const POINT_TYPE & center, const SIZE_TYPE & halfsize)
   {
      
      return {
         center.x() - halfsize.cx(),
         center.y() - halfsize.cy(),
         center.x()+ halfsize.cx(),
         center.y()+ halfsize.cx()
      };
      
   }
   
   static rectangle_type square_with_center_and_apothem(const POINT_TYPE & center, const UNIT_TYPE & apothem)
   {
      
      return with_center_and_half_size(center, {apothem, apothem});
      
   }

   
   rectangle_type & move_top_to(UNIT_TYPE top)  { this->bottom() = height() + top; this->top() = top; return *this; }
   rectangle_type & move_left_to(UNIT_TYPE left)  { this->right() = width() + left; this->left() = left; return *this; }

   rectangle_type & move_right_to(UNIT_TYPE right)  { this->left() = right - width(); this->right() = right; return *this; }
   rectangle_type & move_bottom_to(UNIT_TYPE bottom)  { this->top() = bottom - height(); this->bottom() = bottom; return *this; }

   rectangle_type & move_to(UNIT_TYPE left, UNIT_TYPE top)  { move_left_to(left); return move_top_to(top); return *this; }
   rectangle_type & move_to(const POINT_TYPE & point)  { return move_to(point.x(), point.y()); }

   POINT_TYPE & top_left()  { return *((POINT_TYPE *)this); }
   POINT_TYPE & bottom_right()  { return *((POINT_TYPE *)this + 1); }
   void swap_left_right()  { ::swap_left_right(*this); }

   //operator rectangle_type * ()  { return this; }
   //operator const rectangle_type * () const  { return (const rectangle_type *)this; }

   explicit operator bool() const  { return is_set(); }
   bool operator !() const  { return is_empty(); }

   rectangle_type & set(UNIT_TYPE i)  { return ::assign(*this, i, i, i, i); }
   rectangle_type & set(UNIT_TYPE x, UNIT_TYPE y)  { return ::assign(*this, x, y, x, y); }
   rectangle_type & set(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b)  { return ::assign(*this, l, t, r, b); }
   template < primitive_size SIZE >
   rectangle_type & set(const SIZE & s)  { return ::assign(*this, POINT_TYPE(), s); }
   template < primitive_point POINT1, primitive_point POINT2 >
   rectangle_type & set(const POINT1 & p1, const POINT2 & p2)  { return ::assign(*this, p1.x(), p1.y(), p2.x(), p2.y()); }
   template < primitive_point POINT, primitive_size SIZE >
   rectangle_type & set(const POINT & p, const SIZE & s)  { return ::assign(*this, p, s); }
   template < primitive_rectangle RECTANGLE >
   rectangle_type & set(const RECTANGLE & rectangle)  { return copy(rectangle); }

   rectangle_type & set_dimension(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE w, UNIT_TYPE h) 
   { 
      this->left() = (UNIT_TYPE) l;
      this->top() = (UNIT_TYPE) t;
      this->right() = (UNIT_TYPE) (l + w);
      this->bottom() = (UNIT_TYPE) (t + h);
      return *this;
   }

   rectangle_type & Null()  { return ::null(*this); }

   bool is_equal(const rectangle_type & rectangle) const  
   { 
      return this->left() == rectangle.left()
         && this->top() == rectangle.top()
         && this->right() == rectangle.right()
         && this->bottom() == rectangle.bottom();
   
   }

   template < primitive_number NUMBERX, primitive_number NUMBERY >
   rectangle_type & inflate(NUMBERX x, NUMBERY y)  { this->left() = (UNIT_TYPE) (this->left() - x); this->right() = (UNIT_TYPE) (this->right() + x); this->top() = (UNIT_TYPE)(this->top() - y); this->bottom() = (UNIT_TYPE)(this->bottom() + y); return *this; }
   template < primitive_size SIZE >
   rectangle_type & inflate(const SIZE & size)  { return inflate(size.cx(), size.cy());  }
   template < primitive_number NUMBERX, primitive_number NUMBERY >
   rectangle_type & deflate(NUMBERX x, NUMBERY y) { return inflate(-x, -y); }
   template < primitive_size SIZE >
   rectangle_type & deflate(const SIZE & size)  { return deflate(size.cx(), size.cy()); }

   template < primitive_number NUMBERX, primitive_number NUMBERY >
   rectangle_type & offset(NUMBERX x, NUMBERY y)  { return offset_x(x).offset_y(y); }

   template < primitive_number NUMBERX >
   rectangle_type & offset_x(NUMBERX x)  { this->left() = (UNIT_TYPE) (this->left() + x); this->right() = (UNIT_TYPE) (this->right() + x); return *this; }
   template < primitive_number NUMBERY >
   rectangle_type & offset_y(NUMBERY y)  { this->top() = (UNIT_TYPE) (this->top() + y); this->bottom() = (UNIT_TYPE) (this->bottom() + y); return *this; }
   template < primitive_number NUMBERN >
   rectangle_type & inflate(NUMBERN n)  { return inflate(n, n); }
   template < primitive_number NUMBERN >
   rectangle_type & deflate(NUMBERN n)  { return deflate(n, n); }

   template < primitive_point POINT >
   rectangle_type & offset(const POINT & point)  { return offset_x(point.x()).offset_y(point.y()); }


   template < primitive_size SIZE >
   rectangle_type & offset(const SIZE & size)  { return offset_x(size.cx()).offset_y(size.cy());
   }


   bool x_intersects(const rectangle_type & rectangle) const  { return ::x_intersects(*this, rectangle); }
   bool y_intersects(const rectangle_type & rectangle) const  { return ::y_intersects(*this, rectangle); }
   bool intersects(const rectangle_type & rectangle) const  { return ::intersects(*this, rectangle); }

   bool intersect_x(const rectangle_type & rect1, const rectangle_type & rect2)  { return ::x_intersect(*this, rect1, rect2); }
   bool intersect_y(const rectangle_type & rect1, const rectangle_type & rect2)  { return ::y_intersect(*this, rect1, rect2); }
   bool intersect(const rectangle_type & rect1, const rectangle_type & rect2)  { return ::intersect(*this, rect1, rect2); }

   rectangle_type & intersect(const rectangle_type & rectangle)  { ::intersect(*this, *this, rectangle); return *this; }

   rectangle_type & constrain_to(const rectangle_type & rectangle)  { return intersect(rectangle); }


   inline rectangle_type & constrain(rectangle_type & rectangle) const
   {

      if (rectangle.left() < this->left())
         rectangle.left() = this->left();

      if (rectangle.right() < this->right())
         rectangle.right() = this->right();

      if (rectangle.top() < this->top())
         rectangle.top() = this->top();

      if (rectangle.bottom() < this->bottom())
         rectangle.bottom() = this->bottom();

      return rectangle;

   }


   rectangle_type intersection(const rectangle_type & rect1) const 
   {

      rectangle_type rectangle;

      ::intersect(rectangle, *this, rect1);

      return rectangle;

   }


   bool null_intersect(const rectangle_type & rect1, const rectangle_type & rect2)  { return ::null_intersect(*this, rect1, rect2); }
   bool top_left_null_intersect(const rectangle_type & rect1, const rectangle_type & rect2)  { return ::top_left_null_intersect(*this, rect1, rect2); }

   rectangle_type & unite(const rectangle_type & rectangle1, const rectangle_type & rectangle2) 
   {
      
      if (rectangle1.is_empty())
      {

         if (rectangle2.is_empty())
         {

            this->Null();

         }
         else
         {

            this->operator=(rectangle2);

         }

      }
      else if (rectangle2.is_empty())
      {

         this->operator= (rectangle1);

      }
      else
      {

         this->operator = (rectangle1);
         
         rectangle2.expand_bounding_box(this->top_left(), this->bottom_right());

      }

      return *this;
      
   }
   
   
   rectangle_type & unite(const rectangle_type & rectangle) 
   {
      
      if (this->is_empty())
      {

         if (rectangle.is_empty())
         {

            this->Null();

         }
         else
         {

            this->operator=(rectangle);

         }

      }
      else if (rectangle.is_set())
      {

         rectangle.expand_bounding_box(this->top_left(), this->bottom_right());

      }

      return *this;
      
   }

   rectangle_type get_union(const rectangle_type & rect1) const  { rectangle_type rectangle(*this); rectangle.unite(rect1); return *this; }

   rectangle_type left_difference(const rectangle_type& rectangle) const { return { this->left(), ::maximum(this->top(), rectangle.top()), rectangle.left(), ::minimum(this->bottom(), rectangle.bottom()) }; }
   rectangle_type top_difference(const rectangle_type& rectangle) const { return { ::maximum(this->left(), rectangle.left()), this->top(), ::minimum(this->right(), rectangle.right()), rectangle.top() }; }
   rectangle_type right_difference(const rectangle_type& rectangle) const { return { this->right(), ::maximum(this->top(), rectangle.top()), rectangle.right(), ::minimum(this->bottom(), rectangle.bottom()) }; }
   rectangle_type bottom_difference(const rectangle_type& rectangle) const { return { ::maximum(this->left(), rectangle.left()), this->bottom(), ::minimum(this->right(), rectangle.right()), rectangle.bottom() }; }

   rectangle_type left_plus_difference(const rectangle_type& rectangle) const { return { this->left(), ::minimum(this->top(), rectangle.top()), rectangle.left(),::maximum(this->bottom(), rectangle.bottom()) }; }
   rectangle_type top_plus_difference(const rectangle_type& rectangle) const { return { ::minimum(this->left(), rectangle.left()), this->top(), ::maximum(this->right(), rectangle.right()), rectangle.top() }; }
   rectangle_type right_plus_difference(const rectangle_type& rectangle) const { return { this->right(), ::minimum(this->top(), rectangle.top()), rectangle.right(), ::maximum(this->bottom(), rectangle.bottom()) }; }
   rectangle_type bottom_plus_difference(const rectangle_type& rectangle) const { return { ::minimum(this->left(), rectangle.left()), this->bottom(), ::maximum(this->right(), rectangle.right()), rectangle.bottom() }; }

   rectangle_type & operator =(const rectangle_type & rectangle)  = default;

   // template < primitive_rectangle RECTANGLE >
   // rectangle_type & operator =(const RECTANGLE & rectangle) 
   // {
      
   //    if((void *) this != (void *) &rectangle)
   //    {
      
   //       this->left() = (UNIT_TYPE) rectangle.left();
   //       this->top() = (UNIT_TYPE) rectangle.top();
   //       this->right() = (UNIT_TYPE) rectangle.right();
   //       this->bottom() = (UNIT_TYPE) rectangle.bottom();
      
   //    }
      
   //    return *this;
      
   // }
   

   // template < primitive_origin_size ORIGIN_SIZE >
   // rectangle_type & operator =(const ORIGIN_SIZE & originsize) 
   // {
      
   //    this->left() = (UNIT_TYPE) originsize.origin.x;
   //    this->top() = (UNIT_TYPE) originsize.origin.y;
   //    this->right() = (UNIT_TYPE) originsize.origin.x + originsize.size.width;
   //    this->bottom() = (UNIT_TYPE) originsize.origin.y + originsize.size.height;
      
   //    return *this;
      
   // }


   bool operator==(const rectangle_type & rectangle) const  
   { 
      
      return ::is_equal(*this, rectangle); 
   
   }
//   bool operator!=(const rectangle_type & rectangle) const  { return !operator ==(rectangle); }

   template < primitive_point POINT >
   rectangle_type & operator+=(const POINT & point)  { return ::offset(*this, point.x(), point.y()); }

   template < primitive_size SIZE >
   rectangle_type & operator+=(const SIZE & size)  { return ::offset(*this, size.cx(), size.cy()); }

   rectangle_type & operator+=(const rectangle_type & rectangle)  { return ::inflate(*this, rectangle); }
   rectangle_type & operator*=(const rectangle_type & rectangle)  { return ::multiply_inline(*this, rectangle); }

   template < primitive_number NUMBER2 >
   rectangle_type & operator*=(NUMBER2 n) 
   {
      
      this->left() = (UNIT_TYPE) (this->left() * n);
      this->top() = (UNIT_TYPE)(this->top() * n);
      this->right() = (UNIT_TYPE)(this->right() * n);
      this->bottom() = (UNIT_TYPE)(this->bottom() * n);

      return *this;
      
   }


//   inline rectangle_type & operator+=(const SHIFT_I32 & shift)  { this->left() = (UNIT_TYPE)(this->left() + shift.Δx); this->top() = (UNIT_TYPE)(this->top() + shift.Δy); this->right() = (UNIT_TYPE)(this->right() + shift.Δx); this->bottom() = (UNIT_TYPE)(this->bottom() + shift.Δy); return *this; }
//   inline rectangle_type & operator-=(const SHIFT_I32 & shift)  { this->left() = (UNIT_TYPE)(this->left() - shift.Δx); this->top() = (UNIT_TYPE)(this->top() - shift.Δy); this->right() = (UNIT_TYPE)(this->right() + shift.Δx); this->bottom() = (UNIT_TYPE)(this->bottom() + shift.Δy); return *this; }
//
//
//   inline rectangle_type & operator()(const SHIFT_I32 & shift)  { return operator +=(shift); }
//
//
//   inline rectangle_type operator+(const SHIFT_I32 & shift)  { return { (UNIT_TYPE)(this->left() + shift.Δx), (UNIT_TYPE)(this->top() + shift.Δy), (UNIT_TYPE)(this->right() + shift.Δx), (UNIT_TYPE)(this->bottom() + shift.Δy) }; }
//   inline rectangle_type operator-(const SHIFT_I32 & shift)  { return { (UNIT_TYPE)(this->left() - shift.Δx), (UNIT_TYPE)(this->top() - shift.Δy), (UNIT_TYPE)(this->right() - shift.Δx), (UNIT_TYPE)(this->bottom() - shift.Δy) }; }


   template < primitive_point POINT >
   rectangle_type & operator-=(const POINT & point)  { return ::subtract(*this, point.x(), point.y()); }

   template < primitive_size SIZE >
   rectangle_type & operator-=(const SIZE & size)  { return ::subtract(*this, -size.cx(), -size.cy()); }
   rectangle_type & operator-=(const rectangle_type & rectangle)  { return ::subtract(*this, rectangle); }

   rectangle_type & operator&=(const rectangle_type & rectangle)  { ::intersect(*this, *this, rectangle); return*this; }
   rectangle_type & operator|=(const rectangle_type & rectangle)  { return unite(rectangle); }

   rectangle_type operator+(const POINT_TYPE & point) const 
   {
      rectangle_type rectangle(*this); rectangle.offset(point.x(), point.y()); return rectangle;
   }
   rectangle_type operator-(const POINT_TYPE & point) const 
   {
      rectangle_type rectangle(*this); rectangle.offset(-point.x(), -point.y()); return rectangle;
   }

   template < primitive_size SIZE >
   rectangle_type operator+(const SIZE & size) const 
   {

      rectangle_type rectangle(*this); rectangle.offset(size.cx(), size.cy()); return rectangle;

   }

   template < primitive_size SIZE >
   rectangle_type operator-(const SIZE & size) const 
   {

      rectangle_type rectangle(*this); rectangle.offset(-size.cx(), -size.cy()); return rectangle;

   }

   rectangle_type operator+(const rectangle_type & rectangleAdd) const 
   {
      rectangle_type rectangle(*this); rectangle.inflate(rectangleAdd); return rectangle;
   }
   rectangle_type operator-(const rectangle_type & rectangleSub) const 

   {
      rectangle_type rectangle(*this); rectangle.deflate(rectangleSub); return rectangle;
   }
   rectangle_type operator&(const rectangle_type & rect2) const 
   {
      rectangle_type rectangle; ::intersect(rectangle, *this, rect2);
      return rectangle;
   }
   rectangle_type operator|(const rectangle_type & rectangleOr) const 
   {
      rectangle_type rectangle; 
      rectangle.unite(*this, rectangleOr);
      return rectangle;
   }

   
   rectangle_type & subtract(const rectangle_type & rectangleSrc1, const rectangle_type & rectangleSrc2) 
   {
      
      return ::subtract(*this, rectangleSrc1, rectangleSrc2);

   }

   void normalize() ;

   template < primitive_rectangle RECTANGLE >
   void inflate(const RECTANGLE & rectangle) 
   {

      this->left() = (UNIT_TYPE)(this->left() - rectangle.left());
      this->top() = (UNIT_TYPE)(this->top() - rectangle.top());
      this->right() = (UNIT_TYPE)(this->right() + rectangle.right());
      this->bottom() = (UNIT_TYPE)(this->bottom() + rectangle.bottom());

   }

   void inflate(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b)  {
      this->left() = (UNIT_TYPE)(this->left() - l);
      this->top() = (UNIT_TYPE)(this->top() - t);
      this->right() = (UNIT_TYPE)(this->right() + r);
      this->bottom() = (UNIT_TYPE)(this->bottom() + b);
   }


   template < primitive_rectangle RECTANGLE >
   void deflate(const RECTANGLE & rectangle) 
   {

      this->left() = (UNIT_TYPE)(this->left() + rectangle.left());
      this->top() = (UNIT_TYPE)(this->top() + rectangle.top());
      this->right() = (UNIT_TYPE)(this->right() - rectangle.right());
      this->bottom() = (UNIT_TYPE)(this->bottom() - rectangle.bottom());

   }

   void deflate(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) 
   {
      this->left() = (UNIT_TYPE)(this->left() + l);
      this->top() = (UNIT_TYPE)(this->top() + t);
      this->right() = (UNIT_TYPE)(this->right() - r);
      this->bottom() = (UNIT_TYPE)(this->bottom() - b);
   }



   UNIT_TYPE area() const
   {

      return size().area();

   }


   //void get_bounding_box(const POINT_BASE_TYPE * ppoint, ::collection::count count);
   //void get_bounding_box(const POINT_ARRAY_TYPE & pointa) { pointa.get_bounding_box(*this); }


   void rate(double d) 
   {

      POINT_TYPE point = center();

      UNIT_TYPE w = (UNIT_TYPE)(d * width());

      UNIT_TYPE h = (UNIT_TYPE)(d * height());

      this->left() = point.x() - w / 2;

      this->right() = this->left() + w;

      this->top() = point.y() - h / 2;

      this->bottom() = this->top() + h;

   }


   rectangle_type operator * (double d) const 
   {

      return rectangle_type(
         (UNIT_TYPE)(this->left() * d),
         (UNIT_TYPE)(this->top() * d),
         (UNIT_TYPE)(this->right() * d),
         (UNIT_TYPE)(this->bottom() * d));

   }


   void DeflateBottomRightSizeByRate(double dRate)
   {
      double Δx = width();
      double Δy = height();
      double dxNew = Δx / dRate;
      double dyNew = Δy / dRate;
      Δx = Δx - dxNew;
      Δy = Δy - dyNew;
      this->right() -= (long)Δx;
      this->bottom() -= (long)Δy;
   }

   void SetBottomRightSize(UNIT_TYPE iWidth, UNIT_TYPE iHeight)
   {
      this->right() = this->left() + iWidth;
      this->bottom() = this->top() + iHeight;
   }


   void SetBottomRightSize(const SIZE_TYPE & size)
   {
      SetBottomRightSize(size.cx(), size.cy());
   }

   void ExtendOnCenter(const rectangle_type & rectangle)
   {

      UNIT_TYPE cx = width();
      UNIT_TYPE cy = height();

      double Δx = ::width(rectangle);
      double Δy = ::height(rectangle);
      double dr = ::maximum(Δx / cx, Δy / cy);

      UNIT_TYPE cw = (UNIT_TYPE)(cx * dr);
      UNIT_TYPE ch = (UNIT_TYPE)(cy * dr);

      this->left() = (UNIT_TYPE)((Δx - cw) / 2.0);
      this->top() = (UNIT_TYPE)((Δy - ch) / 2.0);
      this->right() = this->left() + cw;
      this->bottom() = this->top() + ch;

   }

   void FitOnCenterOf(const rectangle_type & rectangle, const SIZE_TYPE & size)
   {

      UNIT_TYPE cx = size.cx();
      UNIT_TYPE cy = size.cy();

      double Δx = ::width(rectangle);
      double Δy = ::height(rectangle);
      double dr = ::minimum(cx == 0 ? 1 : Δx / cx, cy == 0 ? 1 : Δy / cy);

      UNIT_TYPE cw = cx == 0 ? (UNIT_TYPE)Δx : ((UNIT_TYPE)(cx * dr));
      UNIT_TYPE ch = cy == 0 ? (UNIT_TYPE)Δy : ((UNIT_TYPE)(cy * dr));

      this->left() = (UNIT_TYPE)((rectangle.left()) + (Δx - cw) / 2.0);
      this->top() = (UNIT_TYPE)((rectangle.top()) + (Δy - ch) / 2.0);
      this->right() = this->left() + cw;
      this->bottom() = this->top() + ch;

   }

   void FitOnCenterOf(const rectangle_type & rectangle)
   {

      FitOnCenterOf(rectangle, size());

   }


   void CenterOf(const rectangle_type & rectangle, const SIZE_TYPE & size)
   {
      UNIT_TYPE cx = size.cx();
      UNIT_TYPE cy = size.cy();

      UNIT_TYPE Δx = ::width(rectangle);
      UNIT_TYPE Δy = ::height(rectangle);

      this->left() = rectangle.left() + (Δx - cx) / 2;
      this->top() = rectangle.top() + (Δy - cy) / 2;
      this->right() = this->left() + cx;
      this->bottom() = this->top() + cy;

   }

   void CenterOf(const rectangle_type & rectangle)
   {

      CenterOf(rectangle, size());

   }


   void ScaleRect(double Δx, double Δy, UNIT_TYPE ix, UNIT_TYPE iy)
   {

      this->left() = (UNIT_TYPE)(((this->left() - ix) * Δx) + ix);
      this->top() = (UNIT_TYPE)(((this->top() - iy) * Δy) + iy);
      this->right() = (UNIT_TYPE)(((this->right() - ix) * Δx) + ix);
      this->bottom() = (UNIT_TYPE)(((this->bottom() - iy) * Δy) + iy);

   }


   void ScaleHeightAspect(UNIT_TYPE iNewHeight, UNIT_TYPE iCenterX, UNIT_TYPE iCenterY)
   {
      UNIT_TYPE iHeight = height();
      if (iHeight != 0)
      {
         double d = (double)iNewHeight / iHeight;
         ScaleRect(d, d, iCenterX, iCenterY);
      }

   }


   void Align(::e_align ealign, const rectangle_type & rectangle)
   {

      POINT_TYPE point;

      if ((ealign & e_align_horizontal) == e_align_horizontal_center)
      {

         point.x() = rectangle.left() + (rectangle.right() - rectangle.left()) / 2 - width() / 2 - this->left();

      }
      else if ((ealign & e_align_horizontal) == e_align_left)
      {

         point.x() = rectangle.left() - this->left();

      }
      else if ((ealign & e_align_horizontal) == e_align_right)
      {

         point.x() = rectangle.right() - this->right();

      }

      if ((ealign & e_align_vertical) == e_align_vertical_center)
      {

         point.y() = rectangle.top() + (rectangle.bottom() - rectangle.top()) / 2 - height() / 2 - this->top();

      }
      else if ((ealign & e_align_vertical) == e_align_top)
      {

         point.y() = rectangle.top() - this->top();

      }
      else if ((ealign & e_align_vertical) == e_align_bottom)
      {

         point.y() = rectangle.bottom() - this->bottom();

      }

      offset(point);

   }


   void _001Align(double x, double y, const rectangle_type & rectangle)
   {

      _001AlignX(x, rectangle);

      _001AlignY(y, rectangle);

   }


   void _001AlignX(double dRate, const rectangle_type & rectangle)
   {

      if (fabs(dRate) < 1000.0)
      {

         align_x(dRate, rectangle);

      }
      else if (dRate >= 1000.0)
      {

         dRate -= 1000.0;

         double x = rectangle.right() + width() * dRate;

         move_left_to((UNIT_TYPE)x);

      }
      else if (dRate <= -1000.0)
      {

         dRate += 1000.0;

         double x = rectangle.left() + width() * dRate;

         move_left_to((UNIT_TYPE)(x - width()));

      }

   }


   void _001AlignY(double dRate, const rectangle_type & rectangle)
   {

      if (fabs(dRate) < 1000.0)
      {

         align_y(dRate, rectangle);

      }
      else if (dRate >= 1000.0)
      {

         dRate -= 1000.0;

         double y = rectangle.bottom() + height() * dRate;

         move_top_to((UNIT_TYPE)y);


      }
      else if (dRate <= -1000.0)
      {

         dRate += 1000.0;

         double y = rectangle.top() + height() * dRate;

         move_top_to((UNIT_TYPE)(y - height()));

      }


   }


   ::size_f64 aspect_size(const rectangle_type & rectangle) const
   {

      ::size_f64 size = { (double) width(), (double) height()};

      double dW = (double)rectangle.width() / size.cx();

      double dH = (double)rectangle.height() / size.cy();

      double d = minimum(dW, dH);

      return { size.cx() * d, size.cy() * d };

   }


   void aspect_fit(const rectangle_type & rectangle)
   {

      auto size = aspect_size(rectangle);

      set_size(size);

   }


   void aspect_align_fit(double x, double y, const rectangle_type & rectangle)
   {

      aspect_fit(rectangle);

      align_x(x, rectangle);

      align_y(y, rectangle);

   }

   void align_rate(double x, double y, const rectangle_type & rectangle)
   {

      align_x(x, rectangle);

      align_y(y, rectangle);

   }

   void align_x(double dRate, const rectangle_type & rectangle)
   {

      UNIT_TYPE x;

      x = (UNIT_TYPE)(rectangle.left() + (rectangle.right() - rectangle.left() - width()) * ((dRate + 1.0) / 2.0));

      move_left_to(x);

   }


   void align_y(double dRate, const rectangle_type & rectangle)
   {

      UNIT_TYPE y;

      y = (UNIT_TYPE)(rectangle.top() + (rectangle.bottom() - rectangle.top() - height()) * ((dRate + 1.0) / 2.0));

      move_top_to(y);

   }


   void _005Constrain(const rectangle_type & rectangle, const SIZE_TYPE & sizeMin)
   {
      if (this->left() < rectangle.left())
         this->left() = rectangle.left();
      if (this->right() > rectangle.right())
         this->right() = rectangle.right();
      if (this->top() < rectangle.top())
         this->top() = rectangle.top();
      if (this->bottom() > rectangle.bottom())
         this->bottom() = rectangle.bottom();

      if (width() < sizeMin.cx())
         this->right() = this->left() + sizeMin.cx();
      if (height() < sizeMin.cy())
         this->bottom() = this->top() + sizeMin.cy();

   }

   void _007Constrain(const rectangle_type & rectangle)
   {

      const SIZE_TYPE & size = this->size();

      if (size.cx() > ::width(rectangle))
      {

         intersect_x(*this, rectangle);

      }
      else if (intersect_x(*this, rectangle))
      {

         if (this->left() == rectangle.left())
         {

            this->right() = this->left() + size.cx();

         }
         else
         {

            this->left() = this->right() - size.cx();

         }

      }

      if (size.cy() > ::height(rectangle))
      {

         intersect_y(*this, rectangle);

      }
      else if (intersect_y(*this, rectangle))
      {

         if (this->top() == rectangle.top())
         {

            this->bottom() = this->top() + size.cy();

         }
         else
         {

            this->top() = this->bottom() - size.cy();

         }

      }

   }


   void _001Constrain(const rectangle_type & rectangle)
   {

      _001ConstrainX(rectangle);

      _001ConstrainY(rectangle);

   }


   void _001ConstrainX(const rectangle_type & rectangle)
   {

      if (this->right() > rectangle.right())
      {

         offset_x(rectangle.right() - this->right());

      }

      if (this->left() < rectangle.left())
      {

         offset_x(rectangle.left() - this->left());

      }

   }


   void _001ConstrainY(const rectangle_type & rectangle)
   {

      if (this->bottom() > rectangle.bottom())
      {

         offset_y(rectangle.bottom() - this->bottom());

      }

      if (this->top() < rectangle.top())
      {

         offset_y(rectangle.top() - this->top());

      }

   }


   template < primitive_rectangle RECTANGLE >
   void _001Constrain(const rectangle_type & rectangle, RECTANGLE& rectangleBounding)
   {

      _001ConstrainX(rectangle, rectangleBounding);

      _001ConstrainY(rectangle, rectangleBounding);

   }


   template < primitive_rectangle RECTANGLE >
   void _001ConstrainX(const rectangle_type & rectangle, RECTANGLE & rectangleBounding)
   {

      if (rectangleBounding.right() > rectangle.right())
      {

         auto xOffset = rectangle.right() - rectangleBounding.right();

         ::x_offset(rectangleBounding, xOffset);

         offset_x(xOffset);

      }

      if (rectangleBounding.left() < rectangle.left())
      {

         auto xOffset = rectangle.left() - rectangleBounding.left();

         ::x_offset(rectangleBounding, xOffset);

         offset_x(xOffset);

      }

   }


   template < primitive_rectangle RECTANGLE >
   void _001ConstrainY(const rectangle_type & rectangle, RECTANGLE & rectangleBounding)
   {

      if (rectangleBounding.bottom() > rectangle.bottom())
      {

         auto yOffset = rectangle.bottom() - rectangleBounding.bottom();

         ::y_offset(rectangleBounding, yOffset);

         offset_y(yOffset);

      }

      if (rectangleBounding.top() < rectangle.top())
      {

         auto yOffset = rectangle.top() - rectangleBounding.top();

         ::y_offset(rectangleBounding, yOffset);

         offset_y(yOffset);

      }

   }

   template < primitive_rectangle RECTANGLE >
   bool contains(const RECTANGLE & rectangle) const
   {
      return rectangle.left() >= this->left()
         && rectangle.right() <= this->right()
         && rectangle.top() >= this->top()
         && rectangle.bottom() <= this->bottom();
   }

   // Subtract minor from major and return the greatest box around.
   void SubtractRectMajor(const rectangle_type & rectangleMajor, const rectangle_type & rectangleMinor)

   {
      rectangle_type rectangleIntersect;
      rectangle_type rectangleRet(*this);
      if (!rectangleIntersect.intersect(rectangleMajor, rectangleMinor))
      {

         rectangleRet = rectangleMajor;

      }
      else
      {
         if (rectangleIntersect == rectangleMajor)

         {
            rectangleRet.set(0, 0, 0, 0);
         }
         else
         {

            if (rectangleIntersect.left() == rectangleMajor.left()
               && rectangleIntersect.right() == rectangleMajor.right())
            {

               if (rectangleIntersect.top() == rectangleMajor.top())
               {

                  ::assign(rectangleRet,
                     rectangleMajor.left(),
                     rectangleIntersect.top(),
                     rectangleMajor.right(),
                     rectangleMajor.bottom());

               }
               else if (rectangleIntersect.bottom() == rectangleMajor.bottom())
               {

                  ::assign(rectangleRet,
                     rectangleMajor.left(),
                     rectangleMajor.top(),
                     rectangleMajor.right(),
                     rectangleIntersect.bottom());

               }
               else
               {

                  rectangleRet = rectangleMajor;

               }

            }
            else if (rectangleIntersect.top() == rectangleMajor.top()
               && rectangleIntersect.bottom() == rectangleMajor.bottom())
            {

               if (rectangleIntersect.left() == rectangleMajor.left())
               {

                  rectangleRet.set(
                     rectangleIntersect.left(),
                     rectangleMajor.top(),
                     rectangleMajor.right(),
                     rectangleMajor.bottom());

               }
               else if (rectangleIntersect.right() == rectangleMajor.right())
               {

                  rectangleRet.set(
                     rectangleMajor.left(),
                     rectangleMajor.top(),
                     rectangleIntersect.right(),
                     rectangleMajor.bottom());

               }
               else
               {

                  rectangleRet = rectangleMajor;

               }

            }
            else
            {

               rectangleRet = rectangleMajor;

            }

         }

      }

      *this = rectangleRet;

      return;

   }



   //void SubtractRectMinor(const rectangle_type & rectangleMajor, const rectangle_type & rectangleMinor)
   //{

   //   //__UNREFERENCED_PARAMETER(rectangleMajor);

   //   //__UNREFERENCED_PARAMETER(rectangleMinor);

   //}


   UNIT_TYPE minimum_signed_absolute_dimension(bool bNegativePreference = true) const 
   {

      auto w = width();

      auto h = height();

      if (abs(w) < abs(h))
      {

         return w;

      }
      else if (abs(h) < abs(w))
      {

         return h;

      }
      else if (bNegativePreference) // absolutely equal, prefer negative ...
      {

         return ::minimum(w, h);

      }
      else // ... otherwise prefer positive
      {

         return ::maximum(w, h);

      }


   }


   UNIT_TYPE maximum_signed_absolute_dimension(bool bPositivePreference = true) const 
   {

      auto w = width();

      auto h = height();

      if (abs(w) > abs(h))
      {

         return w;

      }
      else if (abs(h) > abs(w))
      {

         return h;

      }
      else if (bPositivePreference) // absolutely equal, prefer positive ...
      {

         return ::maximum(w, h);

      }
      else // ... otherwise prefer negative
      {

         return ::minimum(w, h);

      }


   }


   inline void assign(const rectangle_type & rectangle, enum_orientation eorientation) 
   {

      if (eorientation == e_orientation_horizontal)
      {

         this->left() = rectangle.left();
         this->right() = rectangle.right();

      }
      else if (eorientation == e_orientation_vertical)
      {

         this->top() = rectangle.top();
         this->bottom() = rectangle.bottom();

      }

   }


   inline void assign_normal(const rectangle_type & rectangle, enum_orientation eorientation) 
   {

      if (eorientation == e_orientation_horizontal)
      {

         this->top() = rectangle.top();
         this->bottom() = rectangle.bottom();

      }
      else if (eorientation == e_orientation_vertical)
      {

         this->left() = rectangle.left();
         this->right() = rectangle.right();

      }

   }

   inline bool operator==(nullptr_t) const  { return ::is_null(*this); }
//   inline bool operator!=(nullptr_t) const  { return !operator==(nullptr); }

   template < primitive_size SIZE >
   inline bool operator == (const SIZE & size) const  { return this->width() == size.cx() && this->height() == size.cy(); }

   template < primitive_size SIZE >
   inline bool operator != (const SIZE & size) const  { return !operator ==(size); }

   template < primitive_size SIZE >
   inline bool operator > (const SIZE & size) const  { return this->size() > size; }

   template < primitive_size SIZE >
   inline bool operator >= (const SIZE & size) const  { return this->size() >= size; }

   template < primitive_size SIZE >
   inline bool operator < (const SIZE & size) const  { return this->size() < size; }

   template < primitive_size SIZE >
   inline bool operator <= (const SIZE & size) const  { return this->size() <= size; }

   template < primitive_size SIZE >
   inline bool any_gt(const SIZE & size) const  { return this->size().any_gt(size); }

   template < primitive_size SIZE >
   inline bool any_ge(const SIZE & size) const  { return this->size().any_ge(size); }

   template < primitive_size SIZE >
   inline bool any_lt(const SIZE & size) const  { return this->size().any_lt(size); }

   template < primitive_size SIZE >
   inline bool any_le(const SIZE & size) const  { return this->size().any_le(size); }


   void maximum_minimum()
   {

      ::maximum(this->left());
      ::maximum(this->top());
      ::minimum(this->right());
      ::minimum(this->bottom());

   }
   
   
   void expand_bounding_box(POINT_TYPE & top_left, POINT_TYPE & bottom_right) const
   {
      
      expand_minimum_maximum(top_left.x(), bottom_right.x(), this->left());
      expand_minimum_maximum(top_left.y(), bottom_right.y(), this->top());
      expand_minimum_maximum(top_left.x(), bottom_right.x(), this->right());
      expand_minimum_maximum(top_left.y(), bottom_right.y(), this->bottom());

   }


};








//using rectangle = ::rectangle_f64;



// Split to _defer_shape.h by camilo on 2022-06-28 21:20 <3ThomasBorregaardSorensen!! (Mummi and bilbo in ca2HQ)



template < primitive_number NUMBER >
inline void rectangle_type < NUMBER >::normalize() 
{

   __sort(this->left(), this->right());

   __sort(this->top(), this->bottom());

}





//template < primitive_number NUMBER >
//void rectangle_type < NUMBER > ::get_bounding_box(const POINT_BASE_TYPE * ppoint, ::collection::count count)
//{
//
//   ::get_bounding_box(*this, ppoint, count);
//
//}


template < primitive_number X, primitive_number Y, primitive_number W, primitive_number H >
inline rectangle_i32 rectangle_int_dimension(X x, Y y, W w, H h)
{

   return rectangle_i32(x, y, x + w, y + h);

}


template < primitive_number X, primitive_number Y, primitive_number W, primitive_number H >
inline rectangle_i64 rectangle_i64_dimension(X x, Y y, W w, H h)
{

   return rectangle_i64(x, y, x + w, y + h);

}


template < primitive_number X, primitive_number Y, primitive_number W, primitive_number H >
inline rectangle_f32 rectangle_float_dimension(X x, Y y, W w, H h)
{

   return rectangle_f32(x, y, x + w, y + h);

}


template < primitive_number X, primitive_number Y, primitive_number W, primitive_number H >
inline rectangle_f64 rectangle_double_dimension(X x, Y y, W w, H h)
{

   return rectangle_f64(x, y, x + w, y + h);

}

//
//CLASS_DECL_ACME rectangle_i32 & muldiv(rectangle_i32 & rectangle, int numerator, int denominator);
//CLASS_DECL_ACME rectangle_i64 & muldiv(rectangle_i64 & rectangle, ::i64 numerator, ::i64 denominator);
//
//
//
//CLASS_DECL_ACME rectangle_i32 & muldiv(rectangle_i32 & rectangle, int numerator, int denominator);
//CLASS_DECL_ACME rectangle_i64 & muldiv(rectangle_i64 & rectangle, ::i64 numerator, ::i64 denominator);
//
//template < primitive_integral NUMERATOR, primitive_integral DENOMINATOR >
//rectangle_type muldiv(NUMERATOR numerator, DENOMINATOR denominator) const 
//{
//   return rectangle_type(
//      ::muldiv(this->left(), numerator, denominator),
//      ::muldiv(this->top(), numerator, denominator),
//      ::muldiv(this->right(), numerator, denominator),
//      ::muldiv(this->bottom(), numerator, denominator)
//   );
//}
//
