#pragma once


//namespace html
//{
//
//
//   class CLASS_DECL_CORE ::float_rectangle
//   {
//   public:
//
//
//      float    left;
//      float    top;
//      float    right;
//      float    bottom;
//
//
//      inline ::float_rectangle();
//
//
//      inline ::float_point & top_left();
//      inline ::float_point & bottom_right();
//      inline ::float_point top_left() const;
//      inline ::float_point bottom_right() const;
//      inline ::float_point top_right() const;
//      inline ::float_point bottom_left() const;
//
//      inline ::float_rectangle & constrain(::float_rectangle & rectangle) const;
//
//
//      inline bool contains(float x, float y) const;
//      inline bool contains(const ::float_point & point) const;
//      inline void offset_x(float x);
//      inline void offset_y(float y);
//      inline void offset_xy(float x, float y);
//      inline void set_x(float x);
//      inline void set_y(float y);
//      inline void set_xy(float x, float y);
//      inline void set_xy(const ::float_point & point);
//      inline void set_cx(float cx);
//      inline void set_cy(float cy);
//      inline void set_cxy(float cx, float cy);
//      inline void set_cxy(::float_size sz);
//      inline void set_cxy(::float_size sz);
//      inline void set_pos_dim(float x, float y, float cx, float cy);
//      inline ::int_rectangle * get(::int_rectangle * prectangle) const;
//
//      inline float get_cx() const;
//      inline float get_cy() const;
//      inline ::float_size get_cxy() const;
//      inline float area() const;
//
//      inline ::float_rectangle & operator = (const ::int_rectangle & rectangle);
//
//   };
//
//
//   inline ::float_rectangle::float_rectangle()
//   {
//
//      left     = 0.0f;
//      top      = 0.0f;
//      right    = 0.0f;
//      bottom   = 0.0f;
//
//   }
//
//   inline bool ::float_rectangle::contains(float x, float y) const
//   {
//
//      return x >= left && x <= right && y >= top  && y <= bottom;
//
//   }
//
//   inline bool ::float_rectangle::contains(const ::float_point & point) const
//   {
//
//      return contains((float) ::float_point.x, (float) ::float_point.y);
//
//   }
//
//   inline void ::float_rectangle::set_cx(float cx)
//   {
//      right = left + cx;
//   }
//
//   inline void ::float_rectangle::set_cy(float cy)
//   {
//      bottom = top + cy;
//   }
//
//   inline void ::float_rectangle::set_cxy(float cx, float cy)
//   {
//      set_cx(cx);
//      set_cy(cy);
//   }
//
//   inline void ::float_rectangle::set_cxy(::float_size sz)
//   {
//      set_cxy((float) sz.cx, (float) sz.cy);
//   }
//
//   inline void ::float_rectangle::set_cxy(::float_size sz)
//   {
//      set_cxy(sz.cx, sz.cy);
//   }
//
//   inline void ::float_rectangle::offset_x(float x)
//   {
//      left     += x;
//      right    += x;
//   }
//
//   inline void ::float_rectangle::offset_y(float y)
//   {
//      top      += y;
//      bottom   += y;
//   }
//
//   inline void ::float_rectangle::offset_xy(float x, float y)
//   {
//      offset_x(x);
//      offset_y(y);
//   }
//
//   inline void ::float_rectangle::set_x(float x)
//   {
//      right    = right - left + x;
//      left     = x;
//   }
//
//   inline void ::float_rectangle::set_y(float y)
//   {
//      bottom   = bottom - top + y;
//      top      = y;
//   }
//
//   inline void ::float_rectangle::set_xy(float x, float y)
//   {
//      set_x(x);
//      set_y(y);
//   }
//
//   inline void ::float_rectangle::set_xy(const ::float_point & point)
//   {
//      set_xy((float) ::float_point.x, (float) ::float_point.y);
//   }
//
//   inline ::int_rectangle * ::float_rectangle::get(::int_rectangle * prectangle) const
//
//   {
//      prectangle->left      = (int) left;
//
//      prectangle->right     = (int) right;
//
//      prectangle->top       = (int) top;
//
//      prectangle->bottom    = (int) bottom;
//
//      return prectangle;
//
//   }
//
//   inline float ::float_rectangle::get_cx() const
//   {
//      return right - left;
//   }
//
//
//   inline float ::float_rectangle::get_cy() const
//   {
//      return bottom - top;
//   }
//
//   inline ::float_size ::float_rectangle::get_cxy() const
//   {
//      return ::float_size(get_cx(), get_cy());
//   }
//
//   inline ::float_point & rectangle::top_left()
//   {
//      return *((::float_point *) &left);
//   }
//
//   inline ::float_point & rectangle::bottom_right()
//   {
//      return *((::float_point *) &right);
//   }
//
//   inline ::float_point ::float_rectangle::top_left() const
//   {
//      return ::float_point(left, top);
//   }
//
//   inline ::float_point ::float_rectangle::bottom_right() const
//   {
//      return ::float_point(right, bottom);
//   }
//
//   inline ::float_point ::float_rectangle::top_right() const
//   {
//      return ::float_point(right, top);
//   }
//
//   inline  ::float_point ::float_rectangle::bottom_left() const
//   {
//      return ::float_point(left, bottom);
//   }
//
//   inline ::float_rectangle & rectangle::constrain(::float_rectangle & rectangle) const
//   {
//
//      if(::float_rectangle.left < left)
//         ::float_rectangle.left = left;
//
//      if(::float_rectangle.right < right)
//         ::float_rectangle.right = right;
//
//      if(::float_rectangle.top < top)
//         ::float_rectangle.top = top;
//
//      if(::float_rectangle.bottom < bottom)
//         ::float_rectangle.bottom = bottom;
//
//      return ::float_rectangle;
//
//   }
//
//   inline void ::float_rectangle::set_pos_dim(float x, float y, float cx, float cy)
//   {
//
//      left     = x;
//      top      = y;
//      right    = x + cx;
//      bottom   = y + cy;
//
//
//   }
//
//   inline ::float_rectangle & rectangle::operator = (const ::int_rectangle & rectangle)
//   {
//
//      left     = (float) rectangle.left;
//      top      = (float) rectangle.top;
//      right    = (float) rectangle.right;
//      bottom   = (float) rectangle.bottom;
//
//      return *this;
//
//   }
//
//   inline float ::float_rectangle::area() const
//   {
//
//      return (get_cx() < 0.f && get_cy() < 0.f ? -1.0f : 1.0f) * get_cx() * get_cy();
//
//   }
//
//
//} // namespace html
//
//


