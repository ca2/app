#pragma once

#undef new
#ifdef WINDOWS_DESKTOP
#include <gdiplus.h>
#endif
#define new ACME_NEW
#ifdef WINDOWS
#include <D2d1.h>
#endif



template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
class rect_type :
 public BASE_TYPE
{
public:


   using RECT_BASE_TYPE = BASE_TYPE;
   using UNIT_TYPE = decltype(RECT_BASE_TYPE::left);
   using POINT_TYPE = point_type < POINT_BASE_TYPE, SIZE_BASE_TYPE, RECT_BASE_TYPE >;
   using SIZE_TYPE = size_type < SIZE_BASE_TYPE, POINT_BASE_TYPE, RECT_BASE_TYPE >;
   using POINT_ARRAY_TYPE = typename POINT_TYPE::POINT_ARRAY_TYPE;

   rect_type() noexcept : rect_type((UNIT_TYPE)0) { }
   rect_type(e_no_init) noexcept { }
   rect_type(::std::nullptr_t) noexcept : rect_type((UNIT_TYPE)0) {}
   rect_type(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) noexcept { this->left = (UNIT_TYPE)l; this->top = (UNIT_TYPE)t; this->right = (UNIT_TYPE)r; this->bottom = (UNIT_TYPE)b; }
   rect_type(UNIT_TYPE x, UNIT_TYPE y) noexcept : rect_type(x, y, x, y) {}
   rect_type(UNIT_TYPE i) noexcept : rect_type(i, i) {}
#ifdef WINDOWS_DESKTOP
   rect_type(const Gdiplus::Rect & t) noexcept { __copy(this, &t); }
   rect_type(const Gdiplus::RectF & t) noexcept { __copy(this, &t); }
   rect_type(const Gdiplus::Rect * p) noexcept { __copy(this, p); }
   rect_type(const Gdiplus::RectF * p) noexcept { __copy(this, p); }
#endif
#ifdef WINDOWS
   rect_type(const D2D1_RECT_F& t) noexcept { ::copy(this, &t); }
   //rect_type(const Gdiplus::RectF& t) noexcept : { ::copy(this, &t); }
   //rect_type(const Gdiplus::Rect* p) noexcept : { ::copy(this, p); }
   //rect_type(const Gdiplus::RectF* p) noexcept : { ::copy(this, p); }
#endif
#ifdef APPLE
   rect_type(const CGRect & t) noexcept : { ::copy(this, &t); }
   rect_type(const Gdiplus::RectF& t) noexcept : { ::copy(this, &t); }
   rect_type(const CGRect * p) noexcept : { ::copy(this, p); }
   rect_type(const Gdiplus::RectF* p) noexcept : { ::copy(this, p); }
#endif
   rect_type(const POINT_TYPE& point, const SIZE_TYPE& size) noexcept : rect_type(point.x, point.y, point.x + size.cx, point.y + size.cy) {}
   rect_type(const SIZE_TYPE& size) noexcept : rect_type(nullptr, size) {}
   rect_type(const POINT_TYPE& point1, const POINT_TYPE& point2) noexcept { top_left() = point1; bottom_right() = point2; }
   rect_type(const RECT& t) noexcept { ::copy_rect(this, &t); }
   rect_type(const RECT64& t) noexcept { ::copy_rect(this, &t); }
   rect_type(const RECTF& t) noexcept { ::copy_rect(this, &t); }
   rect_type(const RECTD& t) noexcept { ::copy_rect(this, &t); }
   rect_type(const RECT* p) noexcept { ::copy_rect(this, p); }
   rect_type(const RECT64* p) noexcept { ::copy_rect(this, p); }
   rect_type(const RECTF* p) noexcept { ::copy_rect(this, p); }
   rect_type(const RECTD* p) noexcept { ::copy_rect(this, p); }

 //UNIT_TYPE width() const noexcept;
 //UNIT_TYPE height() const noexcept;
 //SIZE_TYPE size() const noexcept;
 //void set_size(UNIT_TYPE cx, UNIT_TYPE cy) noexcept;
 //void set_size(const SIZE_TYPE& size) noexcept;
 //POINT_TYPE& top_left() noexcept;
 POINT_TYPE& origin() noexcept { return top_left(); }
 const POINT_TYPE& origin() const noexcept { return top_left(); }
 const POINT_TYPE& bottom_right() const noexcept { return ((rect_type*)this)->bottom_right(); }
 const POINT_TYPE& top_left() const noexcept { return ((rect_type *)this)->top_left(); }
 UNIT_TYPE center_x() const { return (this->left + this->right) / (UNIT_TYPE)2; }
 UNIT_TYPE center_y() const { return (this->top + this->bottom) / (UNIT_TYPE)2; }
 POINT_TYPE center() const noexcept { return POINT_TYPE(center_x(), center_y()); }


 inline bool is_set() const noexcept { return !is_empty(); }
 inline bool is_empty() const noexcept { return ::is_rect_empty(this); }
 inline bool is_null() const noexcept { return ::is_rect_null(this); }
 inline bool contains(const POINT_TYPE& point) const noexcept { return ::rect_contains(this, point.x, point.y); }
 inline bool contains_x(UNIT_TYPE x) const noexcept { return ::rect_contains_x(this, x); }
 inline bool contains_y(UNIT_TYPE y) const noexcept { return ::rect_contains_y(this, y); }


 POINT_TYPE random_point() {  return POINT_TYPE(__random(this->left, this->right), __random(this->top, this->bottom)); }
 POINT_TYPE random_point(double dRate) { ::rect rect(this); rect.rate(dRate); return rect.random_point(); }


   template < typename RECT_TYPE >
   rect_type & max(const RECT_TYPE & rect)
   {

      this->left = (decltype(RECT_TYPE::left))::min(this->left, rect.left);
      this->top = (decltype(RECT_TYPE::top))::min(this->top, rect.top);
      this->right = (decltype(RECT_TYPE::right))::max(this->right, rect.right);
      this->bottom = (decltype(RECT_TYPE::bottom))::max(this->bottom, rect.bottom);

      return *this;

   }


   inline pointd to_point_rate(const POINT_TYPE & point) const
   {

      return pointd(((double)point.x - (double)this->left) / (double)width(),
         ((double)point.y - (double)this->top) / (double)height());

   }

   inline POINT_TYPE from_point_rate(const pointd & point) const
   {

      return POINT_TYPE((UNIT_TYPE) (point.x * (double) width()  + (double)this->left),
         (UNIT_TYPE)(point.y * (double)height() + (double)this->top));

   }

 //void align_outsize_rate(double x, double y, const rect_type& rect_type);
 inline POINT_TYPE top_right() const { return POINT_TYPE(this->right, this->top); }
 inline POINT_TYPE bottom_left() const { return POINT_TYPE(this->left, this->bottom); }

// void assign(const rect_type& rect_type, e_orientation eorientation) noexcept;
 //void assign_normal(const rect_type& rect_type, e_orientation eorientation) noexcept;

 UNIT_TYPE minimum_dimension() const noexcept { return ::min(width(), height()); }
 UNIT_TYPE maximum_dimension() const noexcept { return ::max(width(), height()); }
 UNIT_TYPE min_dimension() const noexcept { return minimum_dimension(); }
 UNIT_TYPE max_dimension() const noexcept { return maximum_dimension(); }
 UNIT_TYPE min_dim() const noexcept { return min_dimension(); }
 UNIT_TYPE max_dim() const noexcept { return max_dimension(); }

 UNIT_TYPE max_border() const noexcept { return ::max(::max(this->top, this->left), ::max(this->bottom, this->right)); }

 UNIT_TYPE minimum_natural_dimension() const noexcept { return ::min(::max((UNIT_TYPE) 0, width()), ::max((UNIT_TYPE)0, height())); }
 UNIT_TYPE maximum_natural_dimension() const noexcept { return ::max(::max((UNIT_TYPE) 0, width()), ::max((UNIT_TYPE)0, height())); }

 UNIT_TYPE minimum_absolute_dimension() const noexcept { return ::min(abs(width()), abs(height())); }
 UNIT_TYPE maximum_absolute_dimension() const noexcept { return ::min(abs(width()), abs(height())); }

 //UNIT_TYPE minimum_signed_absolute_dimension(bool bNegativePreference = true) const noexcept;
 //UNIT_TYPE maximum_signed_absolute_dimension(bool bPositivePreference = true) const noexcept;


 UNIT_TYPE width() const noexcept{ return this->right - this->left; }
 UNIT_TYPE height() const noexcept { return this->bottom - this->top; }
 SIZE_TYPE size() const noexcept { return SIZE_TYPE(width(), height()); }

 void set_width(UNIT_TYPE cx) noexcept { this->right = this->left + cx; }
 void set_height(UNIT_TYPE cy) noexcept { this->bottom = this->top + cy; }
 void set_size(UNIT_TYPE cx, UNIT_TYPE cy) noexcept { set_width(cx); set_height(cy); }
 void set_size(const SIZE_TYPE & size) noexcept { set_size(size.cx, size.cy); }

 rect_type & move_top_to(UNIT_TYPE top) noexcept { this->bottom = height() + top; this->top = top; return *this; }
 rect_type & move_left_to(UNIT_TYPE left) noexcept { this->right = width() + left; this->left = left; return *this; }

 rect_type & move_right_to(UNIT_TYPE right) noexcept { this->left = right - width(); this->right = right; return *this; }
 rect_type & move_bottom_to(UNIT_TYPE bottom) noexcept { this->top = bottom - height(); this->bottom = bottom; return *this; }

 rect_type & move_to(UNIT_TYPE left, UNIT_TYPE top) noexcept { move_left_to(left); return move_top_to(top); return *this; }
 rect_type & move_to(const POINT_TYPE & point) noexcept { return move_to(point.x, point.y); }

 POINT_TYPE & top_left() noexcept { return *((POINT_TYPE*)this); }
 POINT_TYPE & bottom_right() noexcept { return *((POINT_TYPE*)this + 1); }
 void swap_left_right() noexcept { ::swap_left_right(this); }

 operator RECT_BASE_TYPE* () noexcept { return this; }
 operator const RECT_BASE_TYPE * () const noexcept { return (const RECT_BASE_TYPE*)this; }

 operator bool () const noexcept { return is_set(); }

 rect_type& set(UNIT_TYPE i) noexcept { return *::set_rect(this, i, i, i, i); }
 rect_type& set(UNIT_TYPE x, UNIT_TYPE y) noexcept { return *::set_rect(this, x, y, x, y); }
 rect_type& set(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) noexcept { return *::set_rect(this, l, t, r, b); }
 rect_type& set(const POINT_TYPE& p1, const POINT_TYPE& p2) noexcept { return *::set_rect(this, p1.x, p1.y, p2.x, p2.y); }
 rect_type& set(const POINT_TYPE& p, const SIZE_TYPE& s) noexcept { return *::set_rect_point_size(this, p, s); }

 rect_type& set_dim(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE w, UNIT_TYPE h) noexcept { return *::set_rect_dim(this, l, t, w, h); }

 rect_type& Null() noexcept { return *::null_rect(this); }

 rect_type& copy(const rect_type& rect) noexcept { ::copy(this, &rect); return *this; }

 bool is_equal(const rect_type & rect) const noexcept { return ::rect_equals(this, &rect); }

 rect_type & inflate(UNIT_TYPE x, UNIT_TYPE y) noexcept { return *::rect_inflate_point(this, x, y); }
 rect_type & inflate(const SIZE_TYPE& size) noexcept { return*::rect_inflate_point(this, size.cx, size.cy);}
 rect_type & deflate(UNIT_TYPE x, UNIT_TYPE y) noexcept { return*::rect_deflate_point(this, x, y); }
 rect_type & deflate(const SIZE_TYPE& size) noexcept { return *::rect_deflate_point(this, size.cx, size.cy); }

 rect_type & offset(UNIT_TYPE x, UNIT_TYPE y) noexcept { return *::offset_rect(this, x, y); }
 UNIT_TYPE offset_x(UNIT_TYPE x) noexcept { return ::x_offset_rect(this, x); }
 UNIT_TYPE offset_y(UNIT_TYPE y) noexcept { return ::y_offset_rect(this, y); }
 rect_type& inflate(UNIT_TYPE u) noexcept { return *::rect_inflate_unit(this, u); }
 rect_type& deflate(UNIT_TYPE u) noexcept { return *::rect_deflate_unit(this, u); }

 rect_type & offset(const POINT_TYPE & point) noexcept { return *::offset_rect(this, point.x, point.y); }
 rect_type & offset(const SIZE_TYPE& size) noexcept { return *::offset_rect(this, size.cx, size.cy); }

 bool x_intersects(const rect_type& rect) const noexcept { return ::x_intersect_rect((RECT_BASE_TYPE*)nullptr, this, &rect); }
 bool y_intersects(const rect_type& rect) const noexcept { return ::y_intersect_rect((RECT_BASE_TYPE*)nullptr, this, &rect); }
 bool intersects(const rect_type& rect) const noexcept { return ::intersect_rect((RECT_BASE_TYPE *)nullptr, this, &rect); }

 bool intersect_x(const rect_type& rect1, const rect_type& rect2) noexcept { return ::x_intersect_rect(this, &rect1, &rect2); }
 bool intersect_y(const rect_type& rect1, const rect_type& rect2) noexcept { return ::y_intersect_rect(this, &rect1, &rect2); }
 bool intersect(const rect_type& rect1, const rect_type& rect2) noexcept { return ::intersect_rect(this, &rect1, &rect2); }

 rect_type& intersect(const rect_type& rect) noexcept { ::intersect_rect(this, this, &rect); return *this; }

 rect_type& constrain_to(const rect_type& rect) noexcept { return intersect(rect); }


 inline rect_type & constrain(rect_type & rect) const
 {

    if (rect.left < this->left)
       rect.left = this->left;

    if (rect.right < this->right)
       rect.right = this->right;

    if (rect.top < this->top)
       rect.top = this->top;

    if (rect.bottom < this->bottom)
       rect.bottom = this->bottom;

    return rect;

 }

 rect_type intersection(const rect_type & rect1) const noexcept
 {

    rect_type rect;

    ::intersect_rect(&rect, this, &rect1);

    return rect;

 }

 bool null_intersect(const rect_type & rect1, const rect_type& rect2) noexcept { return ::null_intersect_rect(this, &rect1, &rect2); }
 bool top_left_null_intersect(const rect_type& rect1, const rect_type& rect2) noexcept { return ::top_left_null_intersect_rect(this, &rect1, &rect2); }

 bool unite(const rect_type& rect1, const rect_type& rect2) noexcept { return ::union_rect(this, &rect1, &rect2); }
 rect_type & unite(const rect_type & rect) noexcept { return *::union_rect(this, this, &rect); }
 rect_type get_union(const rect_type & rect1) const noexcept { rect_type rect(*this); rect.unite(rect1); return *this;}

 rect_type & operator=(const rect_type& rect) noexcept { return *::copy_rect(this, &rect); }

 bool operator==(const rect_type& rect) const noexcept { return ::rect_equals(this, &rect); }
 bool operator!=(const rect_type& rect) const noexcept { return !operator ==(rect); }

 rect_type & operator+=(const POINT_TYPE & point) noexcept { return *::offset_rect(this, point.x, point.y); }
 rect_type & operator+=(const SIZE_TYPE& size) noexcept { return *::offset_rect(this, size.cx, size.cy); }
 rect_type & operator+=(const rect_type & rect) noexcept { return*::rect_inflate(this, &rect); }
 rect_type & operator*=(const rect_type & rect) noexcept { return*::rect_multiply_inline(this, &rect); }

 rect_type & operator-=(const POINT_TYPE& point) noexcept { return *::subtract_rect(this, point.x, point.y); }
 rect_type & operator-=(const SIZE_TYPE& size) noexcept { return *::subtract_rect(this, -size.cx, -size.cy); }
 rect_type & operator-=(const rect_type & rect) noexcept { return *::rect_deflate(this, &rect); }

 rect_type & operator&=(const rect_type & rect) noexcept { ::intersect_rect(this, this, &rect); return*this;}
 rect_type & operator|=(const rect_type & rect) noexcept { return unite(rect); }

 rect_type operator+(const POINT_TYPE & point) const noexcept
 {
 rect_type rect(this); rect.offset(point.x, point.y); return rect;
 }
 rect_type operator-(const POINT_TYPE & point) const noexcept
 {
 rect_type rect(this); rect.offset(-point.x, -point.y); return rect;
 }
 rect_type operator+(const SIZE_TYPE& size) const noexcept
 {
 rect_type rect(this); rect.offset(size.cx, size.cy); return rect;
 }
 rect_type operator-(const SIZE_TYPE& size) const noexcept
 {
 rect_type rect(this); rect.offset(-size.cx, -size.cy); return rect;
 }
 rect_type operator+(const rect_type & rectAdd) const noexcept
 {
 rect_type rect(this); rect.inflate(rectAdd); return rect;
 }
 rect_type operator-(const rect_type & rectSub) const noexcept

 {
 rect_type rect(this); rect.deflate(rectSub); return rect;
 }
 rect_type operator&(const rect_type& rect2) const noexcept
 {
 rect_type rect; ::intersect_rect(&rect,this, & rect2);
 return rect;
 }
 rect_type operator|(const rect_type& rectOr) const noexcept
 {
 rect_type rect; ::union_rect(&rect, this, & rectOr);
 return rect;
 }

 bool subtract(const rect_type& rectSrc1, const rect_type& rectSrc2) noexcept
 {
   return ::subtract_rect(this, &rectSrc1, &rectSrc2);
 }

 void normalize() noexcept { __sort(this->left, this->right); __sort(this->top, this->bottom); }

 void inflate(const rect_type & rect) noexcept

 {
 this->left -= rect.left; this->top -= rect.top;

 this->right += rect.right; this->bottom += rect.bottom;

 }

 void inflate(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) noexcept {
 this->left -= l; this->top -= t;
 this->right += r; this->bottom += b;
 }

 void deflate(const rect_type & rect) noexcept

 {
 this->left += rect.left; this->top += rect.top;

 this->right -= rect.right; this->bottom -= rect.bottom;

 }

 void deflate(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) noexcept
 {
 this->left += l; this->top += t;
 this->right -= r; this->bottom -= b;
 }

 rect_type muldiv(i32 iMul, i32 iDiv) const noexcept { return rect_type(::i32muldiv(this->left, iMul, iDiv), ::i32muldiv(this->top, iMul, iDiv), ::i32muldiv(this->right, iMul, iDiv), ::i32muldiv(this->bottom, iMul, iDiv)); }


   UNIT_TYPE area() const
   {

      return size().area();

   }


   void get_bounding_rect(const POINT_BASE_TYPE * ppoint, ::count count);
   void get_bounding_rect(const POINT_ARRAY_TYPE & pointa) { pointa.get_bounding_rect(this); }


   void rate(double d) noexcept
   {

      POINT_TYPE point = center();

      UNIT_TYPE w = (UNIT_TYPE)(d * width());

      UNIT_TYPE h = (UNIT_TYPE)(d * height());

      this->left = point.x - w / 2;

      this->right = this->left + w;

      this->top = point.y - h / 2;

      this->bottom = this->top + h;

   }


   rect_type operator * (double d) const noexcept
   {

      return rect_type(
         (UNIT_TYPE) (this->left * d),
         (UNIT_TYPE) (this->top * d),
         (UNIT_TYPE) (this->right * d),
         (UNIT_TYPE) (this->bottom * d));

   }


   void DeflateBottomRightSizeByRate(double dRate)
   {
      double dx = width();
      double dy = height();
      double dxNew = dx / dRate;
      double dyNew = dy / dRate;
      dx = dx - dxNew;
      dy = dy - dyNew;
      this->right -= (long)dx;
      this->bottom -= (long)dy;
   }

   void SetBottomRightSize(UNIT_TYPE iWidth, UNIT_TYPE iHeight)
   {
      this->right = this->left + iWidth;
      this->bottom = this->top + iHeight;
   }


   void SetBottomRightSize(const SIZE_TYPE& size)
   {
      SetBottomRightSize(size.cx, size.cy);
   }

   void ExtendOnCenter(const rect_type& rect)
   {

      UNIT_TYPE cx = width();
      UNIT_TYPE cy = height();

      double dx = ::width(rect);
      double dy = ::height(rect);
      double dr = ::max(dx / cx, dy / cy);

      UNIT_TYPE cw = (UNIT_TYPE)(cx * dr);
      UNIT_TYPE ch = (UNIT_TYPE)(cy * dr);

      this->left = (UNIT_TYPE)((dx - cw) / 2.0);
      this->top = (UNIT_TYPE)((dy - ch) / 2.0);
      this->right = this->left + cw;
      this->bottom = this->top + ch;

   }

   void FitOnCenterOf(const rect_type & rect, const SIZE_TYPE & size)
   {

      UNIT_TYPE cx = size.cx;
      UNIT_TYPE cy = size.cy;

      double dx = ::width(rect);
      double dy = ::height(rect);
      double dr = ::min(cx == 0 ? 1 : dx / cx, cy == 0 ? 1 : dy / cy);

      UNIT_TYPE cw = cx == 0 ? (UNIT_TYPE)dx : ((UNIT_TYPE)(cx * dr));
      UNIT_TYPE ch = cy == 0 ? (UNIT_TYPE)dy : ((UNIT_TYPE)(cy * dr));

      this->left = (UNIT_TYPE)((rect.left) + (dx - cw) / 2.0);
      this->top = (UNIT_TYPE)((rect.top) + (dy - ch) / 2.0);
      this->right = this->left + cw;
      this->bottom = this->top + ch;

   }

 void FitOnCenterOf(const rect_type & rect)
 {

    FitOnCenterOf(rect, size());

 }


 void CenterOf(const rect_type & rect, const SIZE_TYPE & size)
 {
    UNIT_TYPE cx = size.cx;
    UNIT_TYPE cy = size.cy;

    UNIT_TYPE dx = ::width(rect);
    UNIT_TYPE dy = ::height(rect);

    this->left = rect.left + (dx - cx) / 2;
    this->top = rect.top + (dy - cy) / 2;
    this->right = this->left + cx;
    this->bottom = this->top + cy;

 }

 void CenterOf(const rect_type & rect)
 {

    CenterOf(rect, size());

 }


 void ScaleRect(double dx, double dy, UNIT_TYPE ix, UNIT_TYPE iy)
 {

    this->left = (UNIT_TYPE)(((this->left - ix) * dx) + ix);
    this->top = (UNIT_TYPE)(((this->top - iy) * dy) + iy);
    this->right = (UNIT_TYPE)(((this->right - ix) * dx) + ix);
    this->bottom = (UNIT_TYPE)(((this->bottom - iy) * dy) + iy);

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


 void Align(::e_align e_align, const rect_type & rect)
 {

    POINT_TYPE point;

    if ((e_align & e_align_horizontal) == e_align_horizontal_center)
    {

       point.x = rect.left + (rect.right - rect.left) / 2 - width() / 2 - this->left;

    }
    else if ((e_align & e_align_horizontal) == e_align_left)
    {

       point.x = rect.left - this->left;

    }
    else if ((e_align & e_align_horizontal) == e_align_right)
    {

       point.x = rect.right - this->right;

    }

    if ((e_align & e_align_vertical) == e_align_vertical_center)
    {
       
       point.y = rect.top + (rect.bottom - rect.top) / 2 - height() / 2 - this->top;

    }
    else if ((e_align & e_align_vertical) == e_align_top)
    {
       
       point.y = rect.top - this->top;

    }
    else if ((e_align & e_align_vertical) == e_align_bottom)
    {

       point.y = rect.bottom - this->bottom;

    }

    offset(point);

 }


 void _001Align(double x, double y, const rect_type & rect)
 {

    _001AlignX(x, rect);

    _001AlignY(y, rect);

 }


 void _001AlignX(double dRate, const rect_type & rect)
 {

    if (fabs(dRate) < 1000.0)
    {

       align_x(dRate, rect);

    }
    else if (dRate >= 1000.0)
    {

       dRate -= 1000.0;

       double x = rect.right + width() * dRate;

       move_left_to((UNIT_TYPE)x);

    }
    else if (dRate <= -1000.0)
    {

       dRate += 1000.0;

       double x = rect.left + width() * dRate;

       move_left_to((UNIT_TYPE)(x - width()));

    }

 }


 void _001AlignY(double dRate, const rect_type & rect)
 {

    if (fabs(dRate) < 1000.0)
    {

       align_y(dRate, rect);

    }
    else if (dRate >= 1000.0)
    {

       dRate -= 1000.0;

       double y = rect.bottom + height() * dRate;

       move_top_to((UNIT_TYPE)y);


    }
    else if (dRate <= -1000.0)
    {

       dRate += 1000.0;

       double y = rect.top + height() * dRate;

       move_top_to((UNIT_TYPE)(y - height()));

    }


 }

 void align_rate(double x, double y, const rect_type & rect)
 {

    align_x(x, rect);

    align_y(y, rect);

 }

 void align_x(double dRate, const rect_type & rect)
 {

    UNIT_TYPE x;

    x = (UNIT_TYPE)(rect.left + (rect.right - rect.left - width()) * ((dRate + 1.0) / 2.0));

    move_left_to(x);

 }


 void align_y(double dRate, const rect_type & rect)
 {

    UNIT_TYPE y;

    y = (UNIT_TYPE)(rect.top + (rect.bottom - rect.top - height()) * ((dRate + 1.0) / 2.0));

    move_top_to(y);

 }


 void constraint_v5(const rect_type & rect, const SIZE_TYPE & sizeMin)
 {
    if (this->left < rect.left)
       this->left = rect.left;
    if (this->right > rect.right)
       this->right = rect.right;
    if (this->top < rect.top)
       this->top = rect.top;
    if (this->bottom > rect.bottom)
       this->bottom = rect.bottom;

    if (width() < sizeMin.cx)
       this->right = this->left + sizeMin.cx;
    if (height() < sizeMin.cy)
       this->bottom = this->top + sizeMin.cy;

 }

 void constraint_v7(const rect_type & rect)
 {

    const SIZE_TYPE& size = this->size();

    if (size.cx > ::width(rect))
    {

       intersect_x(this, &rect);

    }
    else if (intersect_x(this, &rect))
    {

       if (this->left == rect.left)
       {

          this->right = this->left + size.cx;

       }
       else
       {

          this->left = this->right - size.cx;

       }

    }

    if (size.cy > ::height(rect))
    {

       intersect_y(this, &rect);

    }
    else if (intersect_y(this, &rect))
    {

       if (this->top == rect.top)
       {

          this->bottom = this->top + size.cy;

       }
       else
       {

          this->top = this->bottom - size.cy;

       }

    }

 }

 void _001Constraint(const rect_type & rect)
 {

    _001ConstraintX(rect);

    _001ConstraintY(rect);

 }


 void _001ConstraintX(const rect_type & rect)
 {

    if (this->right > rect.right)
    {

       offset_x(rect.right - this->right);

    }

    if (this->left < rect.left)
    {

       offset_x(rect.left - this->left);

    }

 }


 void _001ConstraintY(const rect_type & rect)
 {

    if (this->bottom > rect.bottom)
    {

       offset_y(rect.bottom - this->bottom);

    }

    if (this->top < rect.top)
    {

       offset_y(rect.top - this->top);

    }

 }


 void _001Constraint(const rect_type & rect, RECT_BASE_TYPE * prectBounding)

 {

    _001ConstraintX(rect, prectBounding);


    _001ConstraintY(rect, prectBounding);


 }


 void _001ConstraintX(const rect_type & rect, RECT_BASE_TYPE * prectBounding)

 {

    if (prectBounding->right > rect.right)
    {

       offset_x(::x_offset_rect(prectBounding, rect.right - prectBounding->right));


    }

    if (prectBounding->left < rect.left)

    {

       offset_x(::x_offset_rect(prectBounding, rect.left - prectBounding->left));


    }


 }


 void _001ConstraintY(const rect_type & rect, RECT_BASE_TYPE * prectBounding)

 {

    if (prectBounding->bottom > rect.bottom)

    {

       offset_y(::y_offset_rect(prectBounding, rect.bottom - prectBounding->bottom));


    }

    if (prectBounding->top < rect.top)

    {

       offset_y(::y_offset_rect(prectBounding, rect.top - prectBounding->top));


    }

 }


 bool contains(const rect_type & rect) const
 {
    return rect.left >= this->left
       && rect.right <= this->right
       && rect.top >= this->top
       && rect.bottom <= this->bottom;
 }

 // Subtract minor from major and return the greatest box around.
 void SubtractRectMajor(const rect_type & rectMajor, const rect_type& rectMinor)

 {
    rect_type rectIntersect;
    rect_type rectRet(*this);
    if (!rectIntersect.intersect(rectMajor, rectMinor))
    {

       rectRet = rectMajor;

    }
    else
    {
       if (rectIntersect == rectMajor)

       {
          rectRet.set(0, 0, 0, 0);
       }
       else
       {
          if (rectIntersect.left == rectMajor.left

             && rectIntersect.right == rectMajor.right)

          {
             if (rectIntersect.top == rectMajor.top)

             {
                ::set_rect(&rectRet,
                   rectMajor.left,

                   rectIntersect.top,
                   rectMajor.right,

                   rectMajor.bottom);

             }
             else if (rectIntersect.bottom == rectMajor.bottom)

             {
                ::set_rect(&rectRet,
                   rectMajor.left,

                   rectMajor.top,

                   rectMajor.right,

                   rectIntersect.bottom);
             }
             else
             {
                rectRet = rectMajor;

             }
          }
          else if (rectIntersect.top == rectMajor.top

             && rectIntersect.bottom == rectMajor.bottom)

          {
             if (rectIntersect.left == rectMajor.left)

             {
                rectRet.set(
                   rectIntersect.left,
                   rectMajor.top,

                   rectMajor.right,

                   rectMajor.bottom);

             }
             else if (rectIntersect.right == rectMajor.right)

             {
                rectRet.set(
                   rectMajor.left,

                   rectMajor.top,

                   rectIntersect.right,
                   rectMajor.bottom);

             }
             else
             {
                rectRet = rectMajor;

             }
          }
          else
          {
             rectRet = rectMajor;

          }
       }
    }
    *this = rectRet;
    return;

 }

 void SubtractRectMinor(const rect_type & rectMajor, const rect & rectMinor)

 {
    UNREFERENCED_PARAMETER(rectMajor);

    UNREFERENCED_PARAMETER(rectMinor);

 }


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

       return ::min(w, h);

    }
    else // ... otherwise prefer positive
    {

       return ::max(w, h);

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

       return ::max(w, h);

    }
    else // ... otherwise prefer negative
    {

       return ::min(w, h);

    }


 }


 inline void assign(const rect_type & rect, e_orientation eorientation) noexcept
 {

    if (eorientation == orientation_horizontal)
    {

       this->left = rect.left;
       this->right = rect.right;

    }
    else if (eorientation == orientation_vertical)
    {

       this->top = rect.top;
       this->bottom = rect.bottom;

    }

 }


 inline void assign_normal(const rect_type & rect, e_orientation eorientation) noexcept
 {

    if (eorientation == orientation_horizontal)
    {

       this->top = rect.top;
       this->bottom = rect.bottom;

    }
    else if (eorientation == orientation_vertical)
    {

       this->left = rect.left;
       this->right = rect.right;

    }

 }

   inline bool operator==(::std::nullptr_t) const noexcept { return ::is_rect_null(this); }
   inline bool operator!=(::std::nullptr_t) const noexcept { return !operator==(nullptr); }

   inline bool operator == (const SIZE_TYPE & size) const noexcept { return this->width() == size.cx && this->height() == size.cy; }
   inline bool operator != (const SIZE_TYPE & size) const noexcept { return !operator ==(size); }

   inline bool operator > (const SIZE_TYPE & size) const noexcept { return this->size() > size; }
   inline bool operator >= (const SIZE_TYPE & size) const noexcept { return this->size() >= size; }
   inline bool operator < (const SIZE_TYPE & size) const noexcept { return this->size() < size; }
   inline bool operator <= (const SIZE_TYPE & size) const noexcept { return this->size() <= size; }

//   inline bool operator > (const rect_type & rect) const noexcept { return this->operator > (rect.size()); }
//   inline bool operator >= (const rect_type & rect) const noexcept { return this->operator >= (rect.size()); }
//   inline bool operator < (const rect_type & rect) const noexcept { return this->operator < (rect.size()); }
//   inline bool operator <= (const rect_type & rect) const noexcept { return this->operator <= (rect.size()); }

   inline bool any_gt (const SIZE_TYPE & size) const noexcept { return this->size().any_gt(size); }
   inline bool any_ge (const SIZE_TYPE & size) const noexcept { return this->size().any_ge(size); }
   inline bool any_lt (const SIZE_TYPE & size) const noexcept { return this->size().any_lt(size); }
   inline bool any_le (const SIZE_TYPE & size) const noexcept { return this->size().any_le(size); }

//   inline bool any_gt (const rect_type & rect) const noexcept { return this->any_gt(rect.size()); }
//   inline bool any_ge (const rect_type & rect) const noexcept { return this->any_ge(rect.size()); }
//   inline bool any_lt (const rect_type & rect) const noexcept { return this->any_lt(rect.size()); }
//   inline bool any_le (const rect_type & rect) const noexcept { return this->any_le(rect.size()); }


};



