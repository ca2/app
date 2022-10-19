#pragma once



template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
class rectangle_type :
   public BASE_TYPE
{
public:


   using RECTANGLE_BASE_TYPE = BASE_TYPE;
   using UNIT_TYPE = decltype(RECTANGLE_BASE_TYPE::left);
   using POINT_TYPE = point_type < POINT_BASE_TYPE, SIZE_BASE_TYPE, RECTANGLE_BASE_TYPE >;
   using SIZE_TYPE = size_type < SIZE_BASE_TYPE, POINT_BASE_TYPE, RECTANGLE_BASE_TYPE >;
   using POINT_ARRAY_TYPE = typename POINT_TYPE::POINT_ARRAY_TYPE;

   rectangle_type() noexcept : rectangle_type((UNIT_TYPE)0) { }
   rectangle_type(enum_no_initialize) noexcept { }
   rectangle_type(::std::nullptr_t) noexcept : rectangle_type((UNIT_TYPE)0) {}

   template < primitive_number LEFT, primitive_number TOP, primitive_number RIGHT, primitive_number BOTTOM >
   rectangle_type(LEFT left, TOP top, RIGHT right, BOTTOM bottom) noexcept { this->left = (UNIT_TYPE)left; this->top = (UNIT_TYPE)top; this->right = (UNIT_TYPE)right; this->bottom = (UNIT_TYPE)bottom; }
   rectangle_type(UNIT_TYPE x, UNIT_TYPE y) noexcept : rectangle_type(x, y, x, y) {}
   rectangle_type(UNIT_TYPE i) noexcept : rectangle_type(i, i) {}


#ifdef APPLE
   rectangle_type(const CGRect & t) noexcept : { ::copy(this, &t); }
   rectangle_type(const Gdiplus::RectF & t) noexcept : { ::copy(this, &t); }
   rectangle_type(const CGRect * p) noexcept : { ::copy(this, p); }
   rectangle_type(const Gdiplus::RectF * p) noexcept : { ::copy(this, p); }
#endif
   template < primitive_point POINT, primitive_size SIZE >
   rectangle_type(const POINT & point, const SIZE & size) noexcept : rectangle_type((UNIT_TYPE)point.x, (UNIT_TYPE)point.y, (UNIT_TYPE)(point.x + size.cx), (UNIT_TYPE)(point.y + size.cy)) {}
   template < primitive_size SIZE >
   rectangle_type(const SIZE & size) noexcept : rectangle_type(POINT_TYPE(), size) {}
   template < primitive_point POINT1, primitive_point POINT2 >
   rectangle_type(const POINT1 & point1, const POINT2 & point2) noexcept { top_left() = point1; bottom_right() = point2; }
   template < primitive_rectangle RECTANGLE >
   rectangle_type(const RECTANGLE & t) noexcept { ::copy(this, &t); }
   template < primitive_rectangle RECTANGLE >
   rectangle_type(const RECTANGLE * p) noexcept { ::copy(this, p); }


   POINT_TYPE & origin() noexcept { return top_left(); }
   const POINT_TYPE & origin() const noexcept { return top_left(); }
   const POINT_TYPE & bottom_right() const noexcept { return ((rectangle_type *)this)->bottom_right(); }
   const POINT_TYPE & top_left() const noexcept { return ((rectangle_type *)this)->top_left(); }
   UNIT_TYPE center_x() const { return (this->left + this->right) / (UNIT_TYPE)2; }
   UNIT_TYPE center_y() const { return (this->top + this->bottom) / (UNIT_TYPE)2; }
   POINT_TYPE center() const noexcept { return POINT_TYPE(center_x(), center_y()); }


   inline bool is_set() const noexcept { return !is_empty(); }
   inline bool is_empty() const noexcept { return ::is_rect_empty(*this); }
   inline bool is_null() const noexcept { return ::is_rect_null(*this); }
   template < primitive_point POINT >
   inline bool contains(const POINT & point) const noexcept { return ::rectangle_contains(*this, point.x, point.y); }
   inline bool contains_x(UNIT_TYPE x) const noexcept { return ::rectangle_contains_x(*this, x); }
   inline bool contains_y(UNIT_TYPE y) const noexcept { return ::rectangle_contains_y(*this, y); }


   POINT_TYPE random_point() { return POINT_TYPE(__random(this->left, this->right), __random(this->top, this->bottom)); }
   POINT_TYPE random_point(double dRate) { auto rectangle = *this; rectangle.rate(dRate); return rectangle.random_point(); }


   template < typename RECTANGLE_TYPE >
   rectangle_type & maximum(const RECTANGLE_TYPE & rectangle)
   {

      this->left = (decltype(RECTANGLE_TYPE::left))::minimum(this->left, rectangle.left);
      this->top = (decltype(RECTANGLE_TYPE::top))::minimum(this->top, rectangle.top);
      this->right = (decltype(RECTANGLE_TYPE::right))::maximum(this->right, rectangle.right);
      this->bottom = (decltype(RECTANGLE_TYPE::bottom))::maximum(this->bottom, rectangle.bottom);

      return *this;

   }


   inline point_f64 to_point_rate(const POINT_TYPE & point) const
   {

      return point_f64(((double)point.x - (double)this->left) / (double)width(),
         ((double)point.y - (double)this->top) / (double)height());

   }

   inline POINT_TYPE from_point_rate(const point_f64 & point) const
   {

      return POINT_TYPE((UNIT_TYPE)(point.x * (double)width() + (double)this->left),
         (UNIT_TYPE)(point.y * (double)height() + (double)this->top));

   }

   //void align_outsize_rate(double x, double y, const rectangle_type& rectangle_type);
   inline POINT_TYPE top_right() const { return POINT_TYPE(this->right, this->top); }
   inline POINT_TYPE bottom_left() const { return POINT_TYPE(this->left, this->bottom); }

   // void assign(const rectangle_type& rectangle_type, enum_orientation eorientation) noexcept;
    //void assign_normal(const rectangle_type& rectangle_type, enum_orientation eorientation) noexcept;

   UNIT_TYPE minimum_dimension() const noexcept { return ::minimum(width(), height()); }
   UNIT_TYPE maximum_dimension() const noexcept { return ::maximum(width(), height()); }
   UNIT_TYPE min_dimension() const noexcept { return minimum_dimension(); }
   UNIT_TYPE max_dimension() const noexcept { return maximum_dimension(); }
   UNIT_TYPE min_dim() const noexcept { return min_dimension(); }
   UNIT_TYPE max_dim() const noexcept { return max_dimension(); }

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
   void set_size(const SIZE_TYPE & size) noexcept { set_size(size.cx, size.cy); }

   rectangle_type & move_top_to(UNIT_TYPE top) noexcept { this->bottom = height() + top; this->top = top; return *this; }
   rectangle_type & move_left_to(UNIT_TYPE left) noexcept { this->right = width() + left; this->left = left; return *this; }

   rectangle_type & move_right_to(UNIT_TYPE right) noexcept { this->left = right - width(); this->right = right; return *this; }
   rectangle_type & move_bottom_to(UNIT_TYPE bottom) noexcept { this->top = bottom - height(); this->bottom = bottom; return *this; }

   rectangle_type & move_to(UNIT_TYPE left, UNIT_TYPE top) noexcept { move_left_to(left); return move_top_to(top); return *this; }
   rectangle_type & move_to(const POINT_TYPE & point) noexcept { return move_to(point.x, point.y); }

   POINT_TYPE & top_left() noexcept { return *((POINT_TYPE *)this); }
   POINT_TYPE & bottom_right() noexcept { return *((POINT_TYPE *)this + 1); }
   void swap_left_right() noexcept { ::swap_left_right(this); }

   operator RECTANGLE_BASE_TYPE * () noexcept { return this; }
   operator const RECTANGLE_BASE_TYPE * () const noexcept { return (const RECTANGLE_BASE_TYPE *)this; }

   operator bool() const noexcept { return is_set(); }

   rectangle_type & set(UNIT_TYPE i) noexcept { return ::set_rect(*this, i, i, i, i); }
   rectangle_type & set(UNIT_TYPE x, UNIT_TYPE y) noexcept { return ::set_rect(*this, x, y, x, y); }
   rectangle_type & set(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE r, UNIT_TYPE b) noexcept { return ::set_rect(*this, l, t, r, b); }
   template < primitive_size SIZE >
   rectangle_type & set(const SIZE & s) noexcept { return ::set_rect_point_size(*this, POINT_TYPE(), s); }
   template < primitive_point POINT1, primitive_point POINT2 >
   rectangle_type & set(const POINT1 & p1, const POINT2 & p2) noexcept { return ::set_rect(*this, p1.x, p1.y, p2.x, p2.y); }
   template < primitive_point POINT, primitive_size SIZE >
   rectangle_type & set(const POINT & p, const SIZE & s) noexcept { return ::set_rect_point_size(*this, p, s); }
   template < primitive_rectangle RECTANGLE >
   rectangle_type & set(const RECTANGLE & rectangle) noexcept { return copy(rectangle); }

   rectangle_type & set_dim(UNIT_TYPE l, UNIT_TYPE t, UNIT_TYPE w, UNIT_TYPE h) noexcept { return ::set_dim(*this, l, t, w, h); }

   rectangle_type & Null() noexcept { return ::null_rect(*this); }

   template < primitive_rectangle RECTANGLE >
   rectangle_type & copy(const RECTANGLE & rectangle) noexcept { ::copy(*this, &rectangle); return *this; }
   template < primitive_rectangle RECTANGLE >
   rectangle_type & copy(const RECTANGLE * prectangle) noexcept { ::copy(*this, prectangle); return *this; }

   bool is_equal(const rectangle_type & rectangle) const noexcept { return ::rect_equals(*this, &rectangle); }

   rectangle_type & inflate(UNIT_TYPE x, UNIT_TYPE y) noexcept { return ::rect_inflate_point(*this, x, y); }
   rectangle_type & inflate(const SIZE_TYPE & size) noexcept { return ::rect_inflate_point(*this, size.cx, size.cy); }
   rectangle_type & deflate(UNIT_TYPE x, UNIT_TYPE y) noexcept { return ::rect_deflate_point(*this, x, y); }
   rectangle_type & deflate(const SIZE_TYPE & size) noexcept { return ::rect_deflate_point(*this, size.cx, size.cy); }

   rectangle_type & offset(UNIT_TYPE x, UNIT_TYPE y) noexcept { return ::offset_rect(*this, x, y); }
   UNIT_TYPE offset_x(UNIT_TYPE x) noexcept { return ::x_offset_rect(*this, x); }
   UNIT_TYPE offset_y(UNIT_TYPE y) noexcept { return ::y_offset_rect(*this, y); }
   rectangle_type & inflate(UNIT_TYPE u) noexcept { return ::rect_inflate_unit(*this, u); }
   rectangle_type & deflate(UNIT_TYPE u) noexcept { return ::rect_deflate_unit(*this, u); }

   template < primitive_point POINT >
   rectangle_type & offset(const POINT & point) noexcept { return ::offset_rect(*this, point.x, point.y); }


   template < primitive_size SIZE >
   rectangle_type & offset(const SIZE & size) noexcept { return ::offset_rect(*this, size.cx, size.cy); }


   bool x_intersects(const rectangle_type & rectangle) const noexcept { return ::x_intersects(*this, rectangle); }
   bool y_intersects(const rectangle_type & rectangle) const noexcept { return ::y_intersects(*this, rectangle); }
   bool intersects(const rectangle_type & rectangle) const noexcept { return ::intersects(*this, rectangle); }

   bool intersect_x(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::x_intersect_rect(*this, rect1, rect2); }
   bool intersect_y(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::y_intersect_rect(*this, rect1, rect2); }
   bool intersect(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::intersect_rect(*this, rect1, rect2); }

   rectangle_type & intersect(const rectangle_type & rectangle) noexcept { ::intersect_rect(*this, *this, rectangle); return *this; }

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

      ::intersect_rect(rectangle, *this, rect1);

      return rectangle;

   }

   bool null_intersect(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::null_intersect_rect(*this, rect1, rect2); }
   bool top_left_null_intersect(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::top_left_null_intersect_rect(*this, rect1, rect2); }

   bool unite(const rectangle_type & rect1, const rectangle_type & rect2) noexcept { return ::union_rect(*this, rect1, rect2); }
   rectangle_type & unite(const rectangle_type & rectangle) noexcept { return ::union_rect(*this, *this, rectangle); }
   rectangle_type get_union(const rectangle_type & rect1) const noexcept { rectangle_type rectangle(*this); rectangle.unite(rect1); return *this; }

   template < primitive_rectangle RECTANGLE >
   rectangle_type & operator=(const RECTANGLE & rectangle) noexcept { return ::copy(*this, rectangle); }

   bool operator==(const rectangle_type & rectangle) const noexcept { return ::rect_equals(*this, rectangle); }
   bool operator!=(const rectangle_type & rectangle) const noexcept { return !operator ==(rectangle); }

   template < primitive_point POINT >
   rectangle_type & operator+=(const POINT & point) noexcept { return ::offset_rect(*this, point.x, point.y); }

   template < primitive_size SIZE >
   rectangle_type & operator+=(const SIZE & size) noexcept { return ::offset_rect(*this, size.cx, size.cy); }

   rectangle_type & operator+=(const rectangle_type & rectangle) noexcept { return ::rect_inflate(*this, rectangle); }
   rectangle_type & operator*=(const rectangle_type & rectangle) noexcept { return ::rect_multiply_inline(*this, rectangle); }


   inline rectangle_type & operator+=(const SHIFT_I32 & shift) noexcept { this->left = (UNIT_TYPE)(this->left + shift.Δx); this->top = (UNIT_TYPE)(this->top + shift.Δy); this->right = (UNIT_TYPE)(this->right + shift.Δx); this->bottom = (UNIT_TYPE)(this->bottom + shift.Δy); return *this; }
   inline rectangle_type & operator-=(const SHIFT_I32 & shift) noexcept { this->left = (UNIT_TYPE)(this->left - shift.Δx); this->top = (UNIT_TYPE)(this->top - shift.Δy); this->right = (UNIT_TYPE)(this->right + shift.Δx); this->bottom = (UNIT_TYPE)(this->bottom + shift.Δy); return *this; }


   inline rectangle_type & operator()(const SHIFT_I32 & shift) noexcept { return operator +=(shift); }


   inline rectangle_type operator+(const SHIFT_I32 & shift) noexcept { return { (UNIT_TYPE)(this->left + shift.Δx), (UNIT_TYPE)(this->top + shift.Δy), (UNIT_TYPE)(this->right + shift.Δx), (UNIT_TYPE)(this->bottom + shift.Δy) }; }
   inline rectangle_type operator-(const SHIFT_I32 & shift) noexcept { return { (UNIT_TYPE)(this->left - shift.Δx), (UNIT_TYPE)(this->top - shift.Δy), (UNIT_TYPE)(this->right - shift.Δx), (UNIT_TYPE)(this->bottom - shift.Δy) }; }


   template < primitive_point POINT >
   rectangle_type & operator-=(const POINT & point) noexcept { return ::subtract_rect(*this, point.x, point.y); }

   template < primitive_size SIZE >
   rectangle_type & operator-=(const SIZE & size) noexcept { return ::subtract_rect(*this, -size.cx, -size.cy); }
   rectangle_type & operator-=(const rectangle_type & rectangle) noexcept { return ::rect_deflate(*this, rectangle); }

   rectangle_type & operator&=(const rectangle_type & rectangle) noexcept { ::intersect_rect(*this, *this, rectangle); return*this; }
   rectangle_type & operator|=(const rectangle_type & rectangle) noexcept { return unite(rectangle); }

   rectangle_type operator+(const POINT_TYPE & point) const noexcept
   {
      rectangle_type rectangle(this); rectangle.offset(point.x, point.y); return rectangle;
   }
   rectangle_type operator-(const POINT_TYPE & point) const noexcept
   {
      rectangle_type rectangle(this); rectangle.offset(-point.x, -point.y); return rectangle;
   }

   template < primitive_size SIZE >
   rectangle_type operator+(const SIZE & size) const noexcept
   {

      rectangle_type rectangle(this); rectangle.offset(size.cx, size.cy); return rectangle;

   }

   template < primitive_size SIZE >
   rectangle_type operator-(const SIZE & size) const noexcept
   {

      rectangle_type rectangle(this); rectangle.offset(-size.cx, -size.cy); return rectangle;

   }

   rectangle_type operator+(const rectangle_type & rectangleAdd) const noexcept
   {
      rectangle_type rectangle(this); rectangle.inflate(rectangleAdd); return rectangle;
   }
   rectangle_type operator-(const rectangle_type & rectangleSub) const noexcept

   {
      rectangle_type rectangle(this); rectangle.deflate(rectangleSub); return rectangle;
   }
   rectangle_type operator&(const rectangle_type & rect2) const noexcept
   {
      rectangle_type rectangle; ::intersect_rect(rectangle, *this, rect2);
      return rectangle;
   }
   rectangle_type operator|(const rectangle_type & rectangleOr) const noexcept
   {
      rectangle_type rectangle; ::union_rect(rectangle, *this, rectangleOr);
      return rectangle;
   }

   bool subtract(const rectangle_type & rectangleSrc1, const rectangle_type & rectangleSrc2) noexcept
   {
      return ::subtract_rect(*this, rectangleSrc1, rectangleSrc2);
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

   template < primitive_integral NUMERATOR, primitive_integral DENOMINATOR >
   rectangle_type muldiv(NUMERATOR numerator, DENOMINATOR denominator) const noexcept
   {
      return rectangle_type(
         ::muldiv(this->left, numerator, denominator),
         ::muldiv(this->top, numerator, denominator),
         ::muldiv(this->right, numerator, denominator),
         ::muldiv(this->bottom, numerator, denominator)
      );
   }


   UNIT_TYPE area() const
   {

      return size().area();

   }


   void get_bounding_rectangle(const POINT_BASE_TYPE * ppoint, ::count count);
   void get_bounding_rectangle(const POINT_ARRAY_TYPE & pointa) { pointa.get_bounding_rectangle(*this); }


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
      double Δx = width();
      double Δy = height();
      double dxNew = Δx / dRate;
      double dyNew = Δy / dRate;
      Δx = Δx - dxNew;
      Δy = Δy - dyNew;
      this->right -= (long)Δx;
      this->bottom -= (long)Δy;
   }

   void SetBottomRightSize(UNIT_TYPE iWidth, UNIT_TYPE iHeight)
   {
      this->right = this->left + iWidth;
      this->bottom = this->top + iHeight;
   }


   void SetBottomRightSize(const SIZE_TYPE & size)
   {
      SetBottomRightSize(size.cx, size.cy);
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

      this->left = (UNIT_TYPE)((Δx - cw) / 2.0);
      this->top = (UNIT_TYPE)((Δy - ch) / 2.0);
      this->right = this->left + cw;
      this->bottom = this->top + ch;

   }

   void FitOnCenterOf(const rectangle_type & rectangle, const SIZE_TYPE & size)
   {

      UNIT_TYPE cx = size.cx;
      UNIT_TYPE cy = size.cy;

      double Δx = ::width(rectangle);
      double Δy = ::height(rectangle);
      double dr = ::minimum(cx == 0 ? 1 : Δx / cx, cy == 0 ? 1 : Δy / cy);

      UNIT_TYPE cw = cx == 0 ? (UNIT_TYPE)Δx : ((UNIT_TYPE)(cx * dr));
      UNIT_TYPE ch = cy == 0 ? (UNIT_TYPE)Δy : ((UNIT_TYPE)(cy * dr));

      this->left = (UNIT_TYPE)((rectangle.left) + (Δx - cw) / 2.0);
      this->top = (UNIT_TYPE)((rectangle.top) + (Δy - ch) / 2.0);
      this->right = this->left + cw;
      this->bottom = this->top + ch;

   }

   void FitOnCenterOf(const rectangle_type & rectangle)
   {

      FitOnCenterOf(rectangle, size());

   }


   void CenterOf(const rectangle_type & rectangle, const SIZE_TYPE & size)
   {
      UNIT_TYPE cx = size.cx;
      UNIT_TYPE cy = size.cy;

      UNIT_TYPE Δx = ::width(rectangle);
      UNIT_TYPE Δy = ::height(rectangle);

      this->left = rectangle.left + (Δx - cx) / 2;
      this->top = rectangle.top + (Δy - cy) / 2;
      this->right = this->left + cx;
      this->bottom = this->top + cy;

   }

   void CenterOf(const rectangle_type & rectangle)
   {

      CenterOf(rectangle, size());

   }


   void ScaleRect(double Δx, double Δy, UNIT_TYPE ix, UNIT_TYPE iy)
   {

      this->left = (UNIT_TYPE)(((this->left - ix) * Δx) + ix);
      this->top = (UNIT_TYPE)(((this->top - iy) * Δy) + iy);
      this->right = (UNIT_TYPE)(((this->right - ix) * Δx) + ix);
      this->bottom = (UNIT_TYPE)(((this->bottom - iy) * Δy) + iy);

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

         point.x = rectangle.left + (rectangle.right - rectangle.left) / 2 - width() / 2 - this->left;

      }
      else if ((ealign & e_align_horizontal) == e_align_left)
      {

         point.x = rectangle.left - this->left;

      }
      else if ((ealign & e_align_horizontal) == e_align_right)
      {

         point.x = rectangle.right - this->right;

      }

      if ((ealign & e_align_vertical) == e_align_vertical_center)
      {

         point.y = rectangle.top + (rectangle.bottom - rectangle.top) / 2 - height() / 2 - this->top;

      }
      else if ((ealign & e_align_vertical) == e_align_top)
      {

         point.y = rectangle.top - this->top;

      }
      else if ((ealign & e_align_vertical) == e_align_bottom)
      {

         point.y = rectangle.bottom - this->bottom;

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

      ::size_f64 size = this->size();

      double dW = (double)rectangle.width() / size.cx;

      double dH = (double)rectangle.height() / size.cy;

      double d = minimum(dW, dH);

      return { size.cx * d, size.cy * d };

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

      if (width() < sizeMin.cx)
         this->right = this->left + sizeMin.cx;
      if (height() < sizeMin.cy)
         this->bottom = this->top + sizeMin.cy;

   }

   void _007Constrain(const rectangle_type & rectangle)
   {

      const SIZE_TYPE & size = this->size();

      if (size.cx > ::width(rectangle))
      {

         intersect_x(*this, rectangle);

      }
      else if (intersect_x(*this, rectangle))
      {

         if (this->left == rectangle.left)
         {

            this->right = this->left + size.cx;

         }
         else
         {

            this->left = this->right - size.cx;

         }

      }

      if (size.cy > ::height(rectangle))
      {

         intersect_y(*this, rectangle);

      }
      else if (intersect_y(*this, rectangle))
      {

         if (this->top == rectangle.top)
         {

            this->bottom = this->top + size.cy;

         }
         else
         {

            this->top = this->bottom - size.cy;

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


   void _001Constrain(const rectangle_type & rectangle, RECTANGLE_BASE_TYPE & rectangleBounding)
   {

      _001ConstrainX(rectangle, rectangleBounding);

      _001ConstrainY(rectangle, rectangleBounding);

   }


   void _001ConstrainX(const rectangle_type & rectangle, RECTANGLE_BASE_TYPE & rectangleBounding)
   {

      if (rectangleBounding.right > rectangle.right)
      {

         auto xOffset = rectangle.right - rectangleBounding.right;

         ::x_offset_rect(rectangleBounding, xOffset);

         offset_x(xOffset);

      }

      if (rectangleBounding.left < rectangle.left)
      {

         auto xOffset = rectangle.left - rectangleBounding.left;

         ::x_offset_rect(rectangleBounding, xOffset);

         offset_x(xOffset);

      }

   }


   void _001ConstrainY(const rectangle_type & rectangle, RECTANGLE_BASE_TYPE & rectangleBounding)
   {

      if (rectangleBounding.bottom > rectangle.bottom)
      {

         auto yOffset = rectangle.bottom - rectangleBounding.bottom;

         ::y_offset_rect(rectangleBounding, yOffset);

         offset_y(yOffset);

      }

      if (rectangleBounding.top < rectangle.top)
      {

         auto yOffset = rectangle.top - rectangleBounding.top;

         ::y_offset_rect(rectangleBounding, yOffset);

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
                  ::set_rect(&rectangleRet,
                     rectangleMajor.left,

                     rectangleIntersect.top,
                     rectangleMajor.right,

                     rectangleMajor.bottom);

               }
               else if (rectangleIntersect.bottom == rectangleMajor.bottom)

               {
                  ::set_rect(&rectangleRet,
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

   //   //__UNREFERENCED_PARAMETER(rectangleMajor);

   //   //__UNREFERENCED_PARAMETER(rectangleMinor);

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

   inline bool operator==(::std::nullptr_t) const noexcept { return ::is_rect_null(*this); }
   inline bool operator!=(::std::nullptr_t) const noexcept { return !operator==(nullptr); }

   template < primitive_size SIZE >
   inline bool operator == (const SIZE & size) const noexcept { return this->width() == size.cx && this->height() == size.cy; }

   template < primitive_size SIZE >
   inline bool operator != (const SIZE & size) const noexcept { return !operator ==(size); }

   template < primitive_size SIZE >
   inline bool operator > (const SIZE & size) const noexcept { return this->size() > size; }

   template < primitive_size SIZE >
   inline bool operator >= (const SIZE & size) const noexcept { return this->size() >= size; }

   template < primitive_size SIZE >
   inline bool operator < (const SIZE & size) const noexcept { return this->size() < size; }

   template < primitive_size SIZE >
   inline bool operator <= (const SIZE & size) const noexcept { return this->size() <= size; }

   template < primitive_size SIZE >
   inline bool any_gt(const SIZE & size) const noexcept { return this->size().any_gt(size); }

   template < primitive_size SIZE >
   inline bool any_ge(const SIZE & size) const noexcept { return this->size().any_ge(size); }

   template < primitive_size SIZE >
   inline bool any_lt(const SIZE & size) const noexcept { return this->size().any_lt(size); }

   template < primitive_size SIZE >
   inline bool any_le(const SIZE & size) const noexcept { return this->size().any_le(size); }


};



