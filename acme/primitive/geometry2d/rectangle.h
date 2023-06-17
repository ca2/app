#pragma once


#include "_function.h"
#include "size.h"
#include "acme/primitive/mathematics/numeric_info.h"


//template < primitive_number NUMBER >
template < primitive_number NUMBER >
class rectangle_type
{
public:


   NUMBER left;
   NUMBER top;
   NUMBER right;
   NUMBER bottom;


   //using RECTANGLE_BASE_TYPE = BASE_TYPE;
   using UNIT_TYPE = decltype(left);
   using POINT_TYPE = point_type < NUMBER >;
   using SIZE_TYPE = size_type < NUMBER >;
   //using POINT_ARRAY_TYPE = point_array_base < POINT_TYPE >;

   rectangle_type() noexcept : rectangle_type(0, 0, 0, 0) { }
   rectangle_type(enum_no_initialize) noexcept { }
   rectangle_type(::std::nullptr_t) noexcept : rectangle_type(0, 0, 0, 0) {}

   template < primitive_number LEFT, primitive_number TOP, primitive_number RIGHT, primitive_number BOTTOM >
   rectangle_type(LEFT left, TOP top, RIGHT right, BOTTOM bottom) noexcept { this->left = (UNIT_TYPE)left; this->top = (UNIT_TYPE)top; this->right = (UNIT_TYPE)right; this->bottom = (UNIT_TYPE)bottom; }
   //rectangle_type(UNIT_TYPE x, UNIT_TYPE y) noexcept : rectangle_type(x, y, x, y) {}
   //rectangle_type(UNIT_TYPE i) noexcept : rectangle_type(i, i) {}


//#ifdef APPLE
//   rectangle_type(const CGRect & t) noexcept : { ::copy(*this, &t); }
//   rectangle_type(const Gdiplus::RectF & t) noexcept : { ::copy(this, &t); }
//   rectangle_type(const CGRect * p) noexcept : { ::copy(this, p); }
//   rectangle_type(const Gdiplus::RectF * p) noexcept : { ::copy(this, p); }
//#endif
   template < primitive_point POINT, primitive_size SIZE >
   rectangle_type(const POINT & point, const SIZE & size) noexcept : rectangle_type((UNIT_TYPE)point.x(), (UNIT_TYPE)point.y(), (UNIT_TYPE)(point.x() + size.cx()), (UNIT_TYPE)(point.y() + size.cy())) {}
   template < primitive_size SIZE >
   rectangle_type(const SIZE & size) noexcept : rectangle_type(POINT_TYPE(), size) {}
   template < primitive_point POINT1, primitive_point POINT2 >
   rectangle_type(const POINT1 & point1, const POINT2 & point2) noexcept { top_left() = point1; bottom_right() = point2; }
   template < primitive_rectangle RECTANGLE >
   rectangle_type(const RECTANGLE & t) noexcept
   {
      
      this->left = (UNIT_TYPE) t.left;
      this->top = (UNIT_TYPE) t.top;
      this->right = (UNIT_TYPE) t.right;
      this->bottom = (UNIT_TYPE) t.bottom;
      
   }


   POINT_TYPE & origin() noexcept { return top_left(); }
   const POINT_TYPE & origin() const noexcept { return top_left(); }
   const POINT_TYPE & bottom_right() const noexcept { return ((rectangle_type *)this)->bottom_right(); }
   const POINT_TYPE & top_left() const noexcept { return ((rectangle_type *)this)->top_left(); }
   UNIT_TYPE center_x() const { return (this->left + this->right) / (UNIT_TYPE)2; }
   UNIT_TYPE center_y() const { return (this->top + this->bottom) / (UNIT_TYPE)2; }
   POINT_TYPE center() const noexcept { return POINT_TYPE(center_x(), center_y()); }


   inline bool is_set() const noexcept { return !is_empty(); }
   inline bool is_empty() const noexcept { return ::is_empty(*this); }
   inline bool is_null() const noexcept { return ::is_null(*this); }
   template < primitive_point POINT >
   inline bool contains(const POINT & point) const noexcept { return ::contains(*this, point.x(), point.y()); }
   inline bool contains_x(UNIT_TYPE x) const noexcept { return ::contains_x(*this, x); }
   inline bool contains_y(UNIT_TYPE y) const noexcept { return ::contains_y(*this, y); }


   template < typename RECTANGLE_TYPE >
   rectangle_type & maximum(const RECTANGLE_TYPE & rectangle)
   {

      this->left = (decltype(RECTANGLE_TYPE::left))::minimum(this->left, rectangle.left);
      this->top = (decltype(RECTANGLE_TYPE::top))::minimum(this->top, rectangle.top);
      this->right = (decltype(RECTANGLE_TYPE::right))::maximum(this->right, rectangle.right);
      this->bottom = (decltype(RECTANGLE_TYPE::bottom))::maximum(this->bottom, rectangle.bottom);

      return *this;

   }


   inline ::point_f64 to_point_rate(const POINT_TYPE & point) const
   {

      return { ((double)point.x() - (double)this->left) / (double)width(),
         ((double)point.y() - (double)this->top) / (double)height() };

   }

   inline POINT_TYPE from_point_rate(const ::point_f64 & point) const
   {

      return POINT_TYPE((UNIT_TYPE)(point.x() * (double)width() + (double)this->left),
         (UNIT_TYPE)(point.y() * (double)height() + (double)this->top));

   }

   //void align_outsize_rate(double x, double y, const rectangle_type& rectangle_type);
   inline POINT_TYPE top_right() const { return POINT_TYPE(this->right, this->top); }
   inline POINT_TYPE bottom_left() const { return POINT_TYPE(this->left, this->bottom); }

   // void assign(const rectangle_type& rectangle_type, enum_orientation eorientation) noexcept;
    //void assign_normal(const rectangle_type& rectangle_type, enum_orientation eorientation) noexcept;

   UNIT_TYPE minimum_dimension() const noexcept { return ::minimum(width(), height()); }
   UNIT_TYPE maximum_dimension() const noexcept { return ::maximum(width(), height()); }

   UNIT_TYPE max_border() const noexcept { return ::maximum(::maximum(this->top, this->left), ::maximum(this->bottom, this->right)); }

   UNIT_TYPE minimum_natural_dimension() const noexcept { return ::minimum(::maximum((UNIT_TYPE)0, width()), ::maximum((UNIT_TYPE)0, height())); }
   UNIT_TYPE maximum_natural_dimension() const noexcept { return ::maximum(::maximum((UNIT_TYPE)0, width()), ::maximum((UNIT_TYPE)0, height())); }

   UNIT_TYPE minimum_absolute_dimension() const noexcept { return ::minimum(abs(width()), abs(height())); }
   UNIT_TYPE maximum_absolute_dimension() const noexcept { return ::minimum(abs(width()), abs(height())); }

   //UNIT_TYPE minimum_signed_absolute_dimension(bool bNegativePreference = true) const noexcept;
   //UNIT_TYPE maximum_signed_absolute_dimension(bool bPositivePreference = true) const noexcept;


   UNIT_TYPE width() const noexcept { return this->right - this->left; }
   UNIT_TYPE height() const noexcept { return this->bottom - this->top; }
   SIZE_TYPE size() const noexcept { return SIZE_TYPE(width(), height()); }

   void set_width(UNIT_TYPE cx) noexcept { this->right = this->left + cx; }
   void set_height(UNIT_TYPE cy) noexcept { this->bottom = this->top + cy; }
   void set_size(UNIT_TYPE cx, UNIT_TYPE cy) noexcept { set_width(cx); set_height(cy); }
   void set_size(const SIZE_TYPE & size) noexcept { set_size(size.cx(), size.cy()); }

   rectangle_type & move_top_to(UNIT_TYPE top) noexcept { this->bottom = height() + top; this->top = top; return *this; }
   rectangle_type & move_left_to(UNIT_TYPE left) noexcept { this->right = width() + left; this->left = left; return *this; }

   rectangle_type & move_right_to(UNIT_TYPE right) noexcept { this->left = right - width(); this->right = right; return *this; }
   rectangle_type & move_bottom_to(UNIT_TYPE bottom) noexcept { this->top = bottom - height(); this->bottom = bottom; return *this; }

   rectangle_type & move_to(UNIT_TYPE left, UNIT_TYPE top) noexcept { move_left_to(left); return move_top_to(top); return *this; }
   rectangle_type & move_to(const POINT_TYPE & point) noexcept { return move_to(point.x(), point.y()); }

   POINT_TYPE & top_left() noexcept { return *((POINT_TYPE *)this); }
   POINT_TYPE & bottom_right() noexcept { return *((POINT_TYPE *)this + 1); }
   void swap_left_right() noexcept { ::swap_left_right(*this); }

   //operator rectangle_type * () noexcept { return this; }
   //operator const rectangle_type * () const noexcept { return (const rectangle_type *)this; }

   explicit operator bool() const noexcept { return is_set(); }
   bool operator !() const noexcept { return is_empty(); }

   rectangle_type & set(UNIT_TYPE i) noexcept { return ::assign(*this, i, i, i, i); }
   rectangle_type & set(UNIT_TYPE x, UNIT_TYPE y) noexcept { return ::assign(*this, x, y, x, y); }
   rectangle_type & set(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) noexcept { return ::assign(*this, l, t, r, b); }
   template < primitive_size SIZE >
   rectangle_type & set(const SIZE & s) noexcept { return ::assign(*this, POINT_TYPE(), s); }
   template < primitive_point POINT1, primitive_point POINT2 >
   rectangle_type & set(const POINT1 & p1, const POINT2 & p2) noexcept { return ::assign(*this, p1.x(), p1.y(), p2.x(), p2.y()); }
   template < primitive_point POINT, primitive_size SIZE >
   rectangle_type & set(const POINT & p, const SIZE & s) noexcept { return ::assign(*this, p, s); }
   template < primitive_rectangle RECTANGLE >
   rectangle_type & set(const RECTANGLE & rectangle) noexcept { return copy(rectangle); }

   rectangle_type & set_dimension(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE w, UNIT_TYPE h) noexcept
   { 
      this->left = (UNIT_TYPE) l;
      this->top = (UNIT_TYPE) t;
      this->right = (UNIT_TYPE) (l + w);
      this->bottom = (UNIT_TYPE) (t + h);
      return *this;
   }

   rectangle_type & Null() noexcept { return ::null(*this); }

   bool is_equal(const rectangle_type & rectangle) const noexcept 
   { 
      return this->left == rectangle.left
         && this->top == rectangle.top
         && this->right == rectangle.right
         && this->bottom == rectangle.bottom;
   
   }

   rectangle_type & inflate(UNIT_TYPE x, UNIT_TYPE y) noexcept { this->left -= x; this->right += y; this->top -= x; this->bottom += y; return *this; }
   rectangle_type & inflate(const SIZE_TYPE & size) noexcept { this->left -= size.cx(); this->right += size.cy(); this->top -= size.cx(); this->bottom += size.cy(); return *this; }
   rectangle_type & deflate(UNIT_TYPE x, UNIT_TYPE y) noexcept { this->left += x; this->right -= y; this->top += x; this->bottom -= y; return *this; }
   rectangle_type & deflate(const SIZE_TYPE & size) noexcept { this->left += size.cx(); this->right -= size.cy(); this->top += size.cx(); this->bottom -= size.cy(); return *this; }

   rectangle_type & offset(UNIT_TYPE x, UNIT_TYPE y) noexcept { return offset_x(x).offset_y(y); }
   rectangle_type & offset_x(UNIT_TYPE x) noexcept { this->left += x; this->right += x; return *this; }
   rectangle_type & offset_y(UNIT_TYPE y) noexcept { this->top += y; this->bottom += y; return *this; }
   rectangle_type & inflate(UNIT_TYPE u) noexcept { return inflate(u, u); }
   rectangle_type & deflate(UNIT_TYPE u) noexcept { return deflate(u, u); }

   template < primitive_point POINT >
   rectangle_type & offset(const POINT & point) noexcept { return offset_x(point.x()).offset_y(point.y()); }


   template < primitive_size SIZE >
   rectangle_type & offset(const SIZE & size) noexcept { return offset_x(size.cx()).offset_y(size.cy());
   }


   bool x_intersects(const rectangle_type & rectangle) const noexcept { return ::x_intersects(*this, rectangle); }
   bool y_intersects(const rectangle_type & rectangle) const noexcept { return ::y_intersects(*this, rectangle); }
   bool intersects(const rectangle_type & rectangle) const noexcept { return ::intersects(*this, rectangle); }

   bool intersect_x(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::x_intersect(*this, rect1, rect2); }
   bool intersect_y(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::y_intersect(*this, rect1, rect2); }
   bool intersect(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::intersect(*this, rect1, rect2); }

   rectangle_type & intersect(const rectangle_type & rectangle) noexcept { ::intersect(*this, *this, rectangle); return *this; }

   rectangle_type & constrain_to(const rectangle_type & rectangle) noexcept { return intersect(rectangle); }


   inline rectangle_type & constrain(rectangle_type & rectangle) const
   {

      if (rectangle.left < this->left)
         rectangle.left = this->left;

      if (rectangle.right < this->right)
         rectangle.right = this->right;

      if (rectangle.top < this->top)
         rectangle.top = this->top;

      if (rectangle.bottom < this->bottom)
         rectangle.bottom = this->bottom;

      return rectangle;

   }


   rectangle_type intersection(const rectangle_type & rect1) const noexcept
   {

      rectangle_type rectangle;

      ::intersect(rectangle, *this, rect1);

      return rectangle;

   }


   bool null_intersect(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::null_intersect(*this, rect1, rect2); }
   bool top_left_null_intersect(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::top_left_null_intersect(*this, rect1, rect2); }

   rectangle_type & unite(const rectangle_type & rectangle1, const rectangle_type & rectangle2) noexcept
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
   
   
   rectangle_type & unite(const rectangle_type & rectangle) noexcept
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

   rectangle_type get_union(const rectangle_type & rect1) const noexcept { rectangle_type rectangle(*this); rectangle.unite(rect1); return *this; }

   rectangle_type left_difference(const rectangle_type& rectangle) const { return { this->left, ::maximum(this->top, rectangle.top), rectangle.left, ::minimum(this->bottom, rectangle.bottom) }; }
   rectangle_type top_difference(const rectangle_type& rectangle) const { return { ::maximum(this->left, rectangle.left), this->top, ::minimum(this->right, rectangle.right), rectangle.top }; }
   rectangle_type right_difference(const rectangle_type& rectangle) const { return { this->right, ::maximum(this->top, rectangle.top), rectangle.right, ::minimum(this->bottom, rectangle.bottom) }; }
   rectangle_type bottom_difference(const rectangle_type& rectangle) const { return { ::maximum(this->left, rectangle.left), this->bottom, ::minimum(this->right, rectangle.right), rectangle.bottom }; }

   rectangle_type left_plus_difference(const rectangle_type& rectangle) const { return { this->left, ::minimum(this->top, rectangle.top), rectangle.left,::maximum(this->bottom, rectangle.bottom) }; }
   rectangle_type top_plus_difference(const rectangle_type& rectangle) const { return { ::minimum(this->left, rectangle.left), this->top, ::maximum(this->right, rectangle.right), rectangle.top }; }
   rectangle_type right_plus_difference(const rectangle_type& rectangle) const { return { this->right, ::minimum(this->top, rectangle.top), rectangle.right, ::maximum(this->bottom, rectangle.bottom) }; }
   rectangle_type bottom_plus_difference(const rectangle_type& rectangle) const { return { ::minimum(this->left, rectangle.left), this->bottom, ::maximum(this->right, rectangle.right), rectangle.bottom }; }

   template < primitive_rectangle RECTANGLE >
   rectangle_type & operator =(const RECTANGLE & rectangle) noexcept
   {
      
      if((void *) this != (void *) &rectangle)
      {
      
         this->left = (UNIT_TYPE) rectangle.left;
         this->top = (UNIT_TYPE) rectangle.top;
         this->right = (UNIT_TYPE) rectangle.right;
         this->bottom = (UNIT_TYPE) rectangle.bottom;
      
      }
      
      return *this;
      
   }
   

   template < primitive_origin_size ORIGIN_SIZE >
   rectangle_type & operator =(const ORIGIN_SIZE & originsize) noexcept
   {
      
      this->left = (UNIT_TYPE) originsize.origin.x;
      this->top = (UNIT_TYPE) originsize.origin.y;
      this->right = (UNIT_TYPE) originsize.origin.x + originsize.size.width;
      this->bottom = (UNIT_TYPE) originsize.origin.y + originsize.size.height;
      
      return *this;
      
   }


   bool operator==(const rectangle_type & rectangle) const noexcept 
   { 
      
      return ::is_equal(*this, rectangle); 
   
   }
//   bool operator!=(const rectangle_type & rectangle) const noexcept { return !operator ==(rectangle); }

//   template < primitive_point POINT >
//   rectangle_type & operator+=(const POINT & point) noexcept { return ::offset(*this, point.x(), point.y()); }
//
//   template < primitive_size SIZE >
//   rectangle_type & operator+=(const SIZE & size) noexcept { return ::offset(*this, size.cx(), size.cy()); }

   rectangle_type & operator+=(const rectangle_type & rectangle) noexcept { return ::inflate(*this, rectangle); }
   rectangle_type & operator*=(const rectangle_type & rectangle) noexcept { return ::multiply_inline(*this, rectangle); }

   template < primitive_number NUMBER2 >
   rectangle_type & operator*=(NUMBER2 n) noexcept
   {
      
      this->left = (UNIT_TYPE) (this->left * n);
      this->top = (UNIT_TYPE)(this->top * n);
      this->right = (UNIT_TYPE)(this->right * n);
      this->bottom = (UNIT_TYPE)(this->bottom * n);

      return *this;
      
   }


//   inline rectangle_type & operator+=(const SHIFT_I32 & shift) noexcept { this->left = (UNIT_TYPE)(this->left + shift.greekdeltax); this->top = (UNIT_TYPE)(this->top + shift.greekdeltay); this->right = (UNIT_TYPE)(this->right + shift.greekdeltax); this->bottom = (UNIT_TYPE)(this->bottom + shift.greekdeltay); return *this; }
//   inline rectangle_type & operator-=(const SHIFT_I32 & shift) noexcept { this->left = (UNIT_TYPE)(this->left - shift.greekdeltax); this->top = (UNIT_TYPE)(this->top - shift.greekdeltay); this->right = (UNIT_TYPE)(this->right + shift.greekdeltax); this->bottom = (UNIT_TYPE)(this->bottom + shift.greekdeltay); return *this; }
//
//
//   inline rectangle_type & operator()(const SHIFT_I32 & shift) noexcept { return operator +=(shift); }
//
//
//   inline rectangle_type operator+(const SHIFT_I32 & shift) noexcept { return { (UNIT_TYPE)(this->left + shift.greekdeltax), (UNIT_TYPE)(this->top + shift.greekdeltay), (UNIT_TYPE)(this->right + shift.greekdeltax), (UNIT_TYPE)(this->bottom + shift.greekdeltay) }; }
//   inline rectangle_type operator-(const SHIFT_I32 & shift) noexcept { return { (UNIT_TYPE)(this->left - shift.greekdeltax), (UNIT_TYPE)(this->top - shift.greekdeltay), (UNIT_TYPE)(this->right - shift.greekdeltax), (UNIT_TYPE)(this->bottom - shift.greekdeltay) }; }


   //template < primitive_point POINT >
   //rectangle_type & operator-=(const POINT & point) noexcept { return ::subtract(*this, point.x(), point.y()); }

   template < primitive_size SIZE >
   rectangle_type & operator-=(const SIZE & size) noexcept { return ::subtract(*this, -size.cx(), -size.cy()); }
   rectangle_type & operator-=(const rectangle_type & rectangle) noexcept { return ::subtract(*this, rectangle); }

   rectangle_type & operator&=(const rectangle_type & rectangle) noexcept { ::intersect(*this, *this, rectangle); return*this; }
   rectangle_type & operator|=(const rectangle_type & rectangle) noexcept { return unite(rectangle); }

   rectangle_type operator+(const POINT_TYPE & point) const noexcept
   {
      rectangle_type rectangle(*this); rectangle.offset(point.x(), point.y()); return rectangle;
   }
   rectangle_type operator-(const POINT_TYPE & point) const noexcept
   {
      rectangle_type rectangle(*this); rectangle.offset(-point.x(), -point.y()); return rectangle;
   }

   template < primitive_size SIZE >
   rectangle_type operator+(const SIZE & size) const noexcept
   {

      rectangle_type rectangle(*this); rectangle.offset(size.cx(), size.cy()); return rectangle;

   }

   template < primitive_size SIZE >
   rectangle_type operator-(const SIZE & size) const noexcept
   {

      rectangle_type rectangle(*this); rectangle.offset(-size.cx(), -size.cy()); return rectangle;

   }

   rectangle_type operator+(const rectangle_type & rectangleAdd) const noexcept
   {
      rectangle_type rectangle(*this); rectangle.inflate(rectangleAdd); return rectangle;
   }
   rectangle_type operator-(const rectangle_type & rectangleSub) const noexcept

   {
      rectangle_type rectangle(*this); rectangle.deflate(rectangleSub); return rectangle;
   }
   rectangle_type operator&(const rectangle_type & rect2) const noexcept
   {
      rectangle_type rectangle; ::intersect(rectangle, *this, rect2);
      return rectangle;
   }
   rectangle_type operator|(const rectangle_type & rectangleOr) const noexcept
   {
      rectangle_type rectangle; 
      rectangle.unite(*this, rectangleOr);
      return rectangle;
   }

   
   rectangle_type & subtract(const rectangle_type & rectangleSrc1, const rectangle_type & rectangleSrc2) noexcept
   {
      
      return ::subtract(*this, rectangleSrc1, rectangleSrc2);

   }

   void normalize() noexcept;

   template < primitive_rectangle RECTANGLE >
   void inflate(const RECTANGLE & rectangle) noexcept
   {

      this->left = (decltype(this->left))(this->left - rectangle.left);
      this->top = (decltype(this->top))(this->top - rectangle.top);
      this->right = (decltype(this->right))(this->right + rectangle.right);
      this->bottom = (decltype(this->bottom))(this->bottom + rectangle.bottom);

   }

   void inflate(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) noexcept {
      this->left = (decltype(this->left))(this->left - l);
      this->top = (decltype(this->top))(this->top - t);
      this->right = (decltype(this->right))(this->right + r);
      this->bottom = (decltype(this->bottom))(this->bottom + b);
   }


   template < primitive_rectangle RECTANGLE >
   void deflate(const RECTANGLE & rectangle) noexcept
   {

      this->left = (decltype(this->left))(this->left + rectangle.left);
      this->top = (decltype(this->top))(this->top + rectangle.top);
      this->right = (decltype(this->right))(this->right - rectangle.right);
      this->bottom = (decltype(this->bottom))(this->bottom - rectangle.bottom);

   }

   void deflate(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) noexcept
   {
      this->left = (decltype(this->left))(this->left + l);
      this->top = (decltype(this->top))(this->top + t);
      this->right = (decltype(this->right))(this->right - r);
      this->bottom = (decltype(this->bottom))(this->bottom - b);
   }



   UNIT_TYPE area() const
   {

      return size().area();

   }


   //void get_bounding_box(const POINT_BASE_TYPE * ppoint, ::count count);
   //void get_bounding_box(const POINT_ARRAY_TYPE & pointa) { pointa.get_bounding_box(*this); }


   void rate(double d) noexcept
   {

      POINT_TYPE point = center();

      UNIT_TYPE w = (UNIT_TYPE)(d * width());

      UNIT_TYPE h = (UNIT_TYPE)(d * height());

      this->left = point.x() - w / 2;

      this->right = this->left + w;

      this->top = point.y() - h / 2;

      this->bottom = this->top + h;

   }


   rectangle_type operator * (double d) const noexcept
   {

      return rectangle_type(
         (UNIT_TYPE)(this->left * d),
         (UNIT_TYPE)(this->top * d),
         (UNIT_TYPE)(this->right * d),
         (UNIT_TYPE)(this->bottom * d));

   }


   void DeflateBottomRightSizeByRate(double dRate)
   {
      double greekdeltax = width();
      double greekdeltay = height();
      double dxNew = greekdeltax / dRate;
      double dyNew = greekdeltay / dRate;
      greekdeltax = greekdeltax - dxNew;
      greekdeltay = greekdeltay - dyNew;
      this->right -= (long)greekdeltax;
      this->bottom -= (long)greekdeltay;
   }

   void SetBottomRightSize(UNIT_TYPE iWidth, UNIT_TYPE iHeight)
   {
      this->right = this->left + iWidth;
      this->bottom = this->top + iHeight;
   }


   void SetBottomRightSize(const SIZE_TYPE & size)
   {
      SetBottomRightSize(size.cx(), size.cy());
   }

   void ExtendOnCenter(const rectangle_type & rectangle)
   {

      UNIT_TYPE cx = width();
      UNIT_TYPE cy = height();

      double greekdeltax = ::width(rectangle);
      double greekdeltay = ::height(rectangle);
      double dr = ::maximum(greekdeltax / cx, greekdeltay / cy);

      UNIT_TYPE cw = (UNIT_TYPE)(cx * dr);
      UNIT_TYPE ch = (UNIT_TYPE)(cy * dr);

      this->left = (UNIT_TYPE)((greekdeltax - cw) / 2.0);
      this->top = (UNIT_TYPE)((greekdeltay - ch) / 2.0);
      this->right = this->left + cw;
      this->bottom = this->top + ch;

   }

   void FitOnCenterOf(const rectangle_type & rectangle, const SIZE_TYPE & size)
   {

      UNIT_TYPE cx = size.cx();
      UNIT_TYPE cy = size.cy();

      double greekdeltax = ::width(rectangle);
      double greekdeltay = ::height(rectangle);
      double dr = ::minimum(cx == 0 ? 1 : greekdeltax / cx, cy == 0 ? 1 : greekdeltay / cy);

      UNIT_TYPE cw = cx == 0 ? (UNIT_TYPE)greekdeltax : ((UNIT_TYPE)(cx * dr));
      UNIT_TYPE ch = cy == 0 ? (UNIT_TYPE)greekdeltay : ((UNIT_TYPE)(cy * dr));

      this->left = (UNIT_TYPE)((rectangle.left) + (greekdeltax - cw) / 2.0);
      this->top = (UNIT_TYPE)((rectangle.top) + (greekdeltay - ch) / 2.0);
      this->right = this->left + cw;
      this->bottom = this->top + ch;

   }

   void FitOnCenterOf(const rectangle_type & rectangle)
   {

      FitOnCenterOf(rectangle, size());

   }


   void CenterOf(const rectangle_type & rectangle, const SIZE_TYPE & size)
   {
      UNIT_TYPE cx = size.cx();
      UNIT_TYPE cy = size.cy();

      UNIT_TYPE greekdeltax = ::width(rectangle);
      UNIT_TYPE greekdeltay = ::height(rectangle);

      this->left = rectangle.left + (greekdeltax - cx) / 2;
      this->top = rectangle.top + (greekdeltay - cy) / 2;
      this->right = this->left + cx;
      this->bottom = this->top + cy;

   }

   void CenterOf(const rectangle_type & rectangle)
   {

      CenterOf(rectangle, size());

   }


   void ScaleRect(double greekdeltax, double greekdeltay, UNIT_TYPE ix, UNIT_TYPE iy)
   {

      this->left = (UNIT_TYPE)(((this->left - ix) * greekdeltax) + ix);
      this->top = (UNIT_TYPE)(((this->top - iy) * greekdeltay) + iy);
      this->right = (UNIT_TYPE)(((this->right - ix) * greekdeltax) + ix);
      this->bottom = (UNIT_TYPE)(((this->bottom - iy) * greekdeltay) + iy);

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

         point.x() = rectangle.left + (rectangle.right - rectangle.left) / 2 - width() / 2 - this->left;

      }
      else if ((ealign & e_align_horizontal) == e_align_left)
      {

         point.x() = rectangle.left - this->left;

      }
      else if ((ealign & e_align_horizontal) == e_align_right)
      {

         point.x() = rectangle.right - this->right;

      }

      if ((ealign & e_align_vertical) == e_align_vertical_center)
      {

         point.y() = rectangle.top + (rectangle.bottom - rectangle.top) / 2 - height() / 2 - this->top;

      }
      else if ((ealign & e_align_vertical) == e_align_top)
      {

         point.y() = rectangle.top - this->top;

      }
      else if ((ealign & e_align_vertical) == e_align_bottom)
      {

         point.y() = rectangle.bottom - this->bottom;

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

         double x = rectangle.right + width() * dRate;

         move_left_to((UNIT_TYPE)x);

      }
      else if (dRate <= -1000.0)
      {

         dRate += 1000.0;

         double x = rectangle.left + width() * dRate;

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

         double y = rectangle.bottom + height() * dRate;

         move_top_to((UNIT_TYPE)y);


      }
      else if (dRate <= -1000.0)
      {

         dRate += 1000.0;

         double y = rectangle.top + height() * dRate;

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

      x = (UNIT_TYPE)(rectangle.left + (rectangle.right - rectangle.left - width()) * ((dRate + 1.0) / 2.0));

      move_left_to(x);

   }


   void align_y(double dRate, const rectangle_type & rectangle)
   {

      UNIT_TYPE y;

      y = (UNIT_TYPE)(rectangle.top + (rectangle.bottom - rectangle.top - height()) * ((dRate + 1.0) / 2.0));

      move_top_to(y);

   }


   void _005Constrain(const rectangle_type & rectangle, const SIZE_TYPE & sizeMin)
   {
      if (this->left < rectangle.left)
         this->left = rectangle.left;
      if (this->right > rectangle.right)
         this->right = rectangle.right;
      if (this->top < rectangle.top)
         this->top = rectangle.top;
      if (this->bottom > rectangle.bottom)
         this->bottom = rectangle.bottom;

      if (width() < sizeMin.cx())
         this->right = this->left + sizeMin.cx();
      if (height() < sizeMin.cy())
         this->bottom = this->top + sizeMin.cy();

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

         if (this->left == rectangle.left)
         {

            this->right = this->left + size.cx();

         }
         else
         {

            this->left = this->right - size.cx();

         }

      }

      if (size.cy() > ::height(rectangle))
      {

         intersect_y(*this, rectangle);

      }
      else if (intersect_y(*this, rectangle))
      {

         if (this->top == rectangle.top)
         {

            this->bottom = this->top + size.cy();

         }
         else
         {

            this->top = this->bottom - size.cy();

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

      if (this->right > rectangle.right)
      {

         offset_x(rectangle.right - this->right);

      }

      if (this->left < rectangle.left)
      {

         offset_x(rectangle.left - this->left);

      }

   }


   void _001ConstrainY(const rectangle_type & rectangle)
   {

      if (this->bottom > rectangle.bottom)
      {

         offset_y(rectangle.bottom - this->bottom);

      }

      if (this->top < rectangle.top)
      {

         offset_y(rectangle.top - this->top);

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

      if (rectangleBounding.right > rectangle.right)
      {

         auto xOffset = rectangle.right - rectangleBounding.right;

         ::x_offset(rectangleBounding, xOffset);

         offset_x(xOffset);

      }

      if (rectangleBounding.left < rectangle.left)
      {

         auto xOffset = rectangle.left - rectangleBounding.left;

         ::x_offset(rectangleBounding, xOffset);

         offset_x(xOffset);

      }

   }


   template < primitive_rectangle RECTANGLE >
   void _001ConstrainY(const rectangle_type & rectangle, RECTANGLE & rectangleBounding)
   {

      if (rectangleBounding.bottom > rectangle.bottom)
      {

         auto yOffset = rectangle.bottom - rectangleBounding.bottom;

         ::y_offset(rectangleBounding, yOffset);

         offset_y(yOffset);

      }

      if (rectangleBounding.top < rectangle.top)
      {

         auto yOffset = rectangle.top - rectangleBounding.top;

         ::y_offset(rectangleBounding, yOffset);

         offset_y(yOffset);

      }

   }

   template < primitive_rectangle RECTANGLE >
   bool contains(const RECTANGLE & rectangle) const
   {
      return rectangle.left >= this->left
         && rectangle.right <= this->right
         && rectangle.top >= this->top
         && rectangle.bottom <= this->bottom;
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

            if (rectangleIntersect.left == rectangleMajor.left
               && rectangleIntersect.right == rectangleMajor.right)
            {

               if (rectangleIntersect.top == rectangleMajor.top)
               {

                  ::assign(rectangleRet,
                     rectangleMajor.left,
                     rectangleIntersect.top,
                     rectangleMajor.right,
                     rectangleMajor.bottom);

               }
               else if (rectangleIntersect.bottom == rectangleMajor.bottom)
               {

                  ::assign(rectangleRet,
                     rectangleMajor.left,
                     rectangleMajor.top,
                     rectangleMajor.right,
                     rectangleIntersect.bottom);

               }
               else
               {

                  rectangleRet = rectangleMajor;

               }

            }
            else if (rectangleIntersect.top == rectangleMajor.top
               && rectangleIntersect.bottom == rectangleMajor.bottom)
            {

               if (rectangleIntersect.left == rectangleMajor.left)
               {

                  rectangleRet.set(
                     rectangleIntersect.left,
                     rectangleMajor.top,
                     rectangleMajor.right,
                     rectangleMajor.bottom);

               }
               else if (rectangleIntersect.right == rectangleMajor.right)
               {

                  rectangleRet.set(
                     rectangleMajor.left,
                     rectangleMajor.top,
                     rectangleIntersect.right,
                     rectangleMajor.bottom);

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

   //   //UNREFERENCED_PARAMETER(rectangleMajor);

   //   //UNREFERENCED_PARAMETER(rectangleMinor);

   //}


   UNIT_TYPE minimum_signed_absolute_dimension(bool bNegativePreference = true) const noexcept
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


   UNIT_TYPE maximum_signed_absolute_dimension(bool bPositivePreference = true) const noexcept
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


   inline void assign(const rectangle_type & rectangle, enum_orientation eorientation) noexcept
   {

      if (eorientation == e_orientation_horizontal)
      {

         this->left = rectangle.left;
         this->right = rectangle.right;

      }
      else if (eorientation == e_orientation_vertical)
      {

         this->top = rectangle.top;
         this->bottom = rectangle.bottom;

      }

   }


   inline void assign_normal(const rectangle_type & rectangle, enum_orientation eorientation) noexcept
   {

      if (eorientation == e_orientation_horizontal)
      {

         this->top = rectangle.top;
         this->bottom = rectangle.bottom;

      }
      else if (eorientation == e_orientation_vertical)
      {

         this->left = rectangle.left;
         this->right = rectangle.right;

      }

   }

   inline bool operator==(::std::nullptr_t) const noexcept { return ::is_null(*this); }
//   inline bool operator!=(::std::nullptr_t) const noexcept { return !operator==(nullptr); }

   template < primitive_size SIZE >
   inline bool operator == (const SIZE & size) const noexcept { return this->width() == size.cx() && this->height() == size.cy(); }

//   template < primitive_size SIZE >
//   inline bool operator != (const SIZE & size) const noexcept { return !operator ==(size); }

//   template < primitive_size SIZE >
//   inline bool operator > (const SIZE & size) const noexcept { return this->size() > size; }
//
//   template < primitive_size SIZE >
//   inline bool operator >= (const SIZE & size) const noexcept { return this->size() >= size; }
//
//   template < primitive_size SIZE >
//   inline bool operator < (const SIZE & size) const noexcept { return this->size() < size; }
//
//   template < primitive_size SIZE >
//   inline bool operator <= (const SIZE & size) const noexcept { return this->size() <= size; }

   template < primitive_size SIZE >
   inline bool any_gt(const SIZE & size) const noexcept { return this->size().any_gt(size); }

   template < primitive_size SIZE >
   inline bool any_ge(const SIZE & size) const noexcept { return this->size().any_ge(size); }

   template < primitive_size SIZE >
   inline bool any_lt(const SIZE & size) const noexcept { return this->size().any_lt(size); }

   template < primitive_size SIZE >
   inline bool any_le(const SIZE & size) const noexcept { return this->size().any_le(size); }


   void maximum_minimum()
   {

      ::maximum(this->left);
      ::maximum(this->top);
      ::minimum(this->right);
      ::minimum(this->bottom);

   }
   
   
   void expand_bounding_box(::point_type < UNIT_TYPE > & top_left, ::point_type < UNIT_TYPE > & bottom_right) const
   {
      
      expand_minimum_maximum(top_left.x(), bottom_right.x(), this->left);
      expand_minimum_maximum(top_left.y(), bottom_right.y(), this->top);
      expand_minimum_maximum(top_left.x(), bottom_right.x(), this->right);
      expand_minimum_maximum(top_left.y(), bottom_right.y(), this->bottom);

   }


};








//using rectangle = ::rectangle_f64;



// Split to _defer_shape.h by camilo on 2022-06-28 21:20 <3ThomasBorregaardSorensen!! (Mummi and bilbo in ca2HQ)



template < primitive_number NUMBER >
inline void rectangle_type < NUMBER >::normalize() noexcept
{

   __sort(this->left, this->right);

   __sort(this->top, this->bottom);

}





//template < primitive_number NUMBER >
//void rectangle_type < NUMBER > ::get_bounding_box(const POINT_BASE_TYPE * ppoint, ::count count)
//{
//
//   ::get_bounding_box(*this, ppoint, count);
//
//}


template < typename X, typename Y, typename W, typename H >
inline rectangle_i32 rectangle_i32_dimension(X x, Y y, W w, H h)
{

   return rectangle_i32((i32)(x), (i32)(y), (i32)(x + w), (i32)(y + h));

}


template < typename X, typename Y, typename W, typename H >
inline rectangle_i64 rectangle_i64_dimension(X x, Y y, W w, H h)
{

   return rectangle_i64((i64)x, (i64)y, (i64)(x + w), (i64)(y + h));

}


template < typename X, typename Y, typename W, typename H >
inline rectangle_f32 rectangle_f32_dimension(X x, Y y, W w, H h)
{

   return rectangle_f32((f32)x, (f32)y, (f32)(x + w), (f32)(y + h));

}


template < typename X, typename Y, typename W, typename H >
inline rectangle_f64 rectangle_f64_dimension(X x, Y y, W w, H h)
{

   return rectangle_f64((f64)x, (f64)y, (f64)(x + w), (f64)(y + h));

}

//
//CLASS_DECL_ACME rectangle_i32 & muldiv(rectangle_i32 & rectangle, ::i32 numerator, ::i32 denominator);
//CLASS_DECL_ACME rectangle_i64 & muldiv(rectangle_i64 & rectangle, ::i64 numerator, ::i64 denominator);
//
//
//
//CLASS_DECL_ACME rectangle_i32 & muldiv(rectangle_i32 & rectangle, ::i32 numerator, ::i32 denominator);
//CLASS_DECL_ACME rectangle_i64 & muldiv(rectangle_i64 & rectangle, ::i64 numerator, ::i64 denominator);
//
//template < primitive_integral NUMERATOR, primitive_integral DENOMINATOR >
//rectangle_type muldiv(NUMERATOR numerator, DENOMINATOR denominator) const noexcept
//{
//   return rectangle_type(
//      ::muldiv(this->left, numerator, denominator),
//      ::muldiv(this->top, numerator, denominator),
//      ::muldiv(this->right, numerator, denominator),
//      ::muldiv(this->bottom, numerator, denominator)
//   );
//}
//
