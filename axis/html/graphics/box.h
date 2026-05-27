#pragma once


//namespace html
//{
//
//
//   class CLASS_DECL_CORE ::f32_rectangle
//   {
//   public:
//
//
//      ::f32    left;
//      ::f32    top;
//      ::f32    right;
//      ::f32    bottom;
//
//
//      inline ::f32_rectangle();
//
//
//      inline ::f32_point & top_left();
//      inline ::f32_point & bottom_right();
//      inline ::f32_point top_left() const;
//      inline ::f32_point bottom_right() const;
//      inline ::f32_point top_right() const;
//      inline ::f32_point bottom_left() const;
//
//      inline ::f32_rectangle & constrain(::f32_rectangle & rectangle) const;
//
//
//      inline bool contains(::f32 x, ::f32 y) const;
//      inline bool contains(const ::f32_point & point) const;
//      inline void offset_x(::f32 x);
//      inline void offset_y(::f32 y);
//      inline void offset_xy(::f32 x, ::f32 y);
//      inline void set_x(::f32 x);
//      inline void set_y(::f32 y);
//      inline void set_xy(::f32 x, ::f32 y);
//      inline void set_xy(const ::f32_point & point);
//      inline void set_cx(::f32 cx);
//      inline void set_cy(::f32 cy);
//      inline void set_cxy(::f32 cx, ::f32 cy);
//      inline void set_cxy(::f32_size sz);
//      inline void set_cxy(::f32_size sz);
//      inline void set_pos_dim(::f32 x, ::f32 y, ::f32 cx, ::f32 cy);
//      inline ::i32_rectangle * get(::i32_rectangle * prectangle) const;
//
//      inline ::f32 get_cx() const;
//      inline ::f32 get_cy() const;
//      inline ::f32_size get_cxy() const;
//      inline ::f32 area() const;
//
//      inline ::f32_rectangle & operator = (const ::i32_rectangle & rectangle);
//
//   };
//
//
//   inline ::f32_rectangle::f32_rectangle()
//   {
//
//      left     = 0.0f;
//      top      = 0.0f;
//      right    = 0.0f;
//      bottom   = 0.0f;
//
//   }
//
//   inline bool ::f32_rectangle::contains(::f32 x, ::f32 y) const
//   {
//
//      return x >= left && x <= right && y >= top  && y <= bottom;
//
//   }
//
//   inline bool ::f32_rectangle::contains(const ::f32_point & point) const
//   {
//
//      return contains((::f32) ::f32_point.x, (::f32) ::f32_point.y);
//
//   }
//
//   inline void ::f32_rectangle::set_cx(::f32 cx)
//   {
//      right = left + cx;
//   }
//
//   inline void ::f32_rectangle::set_cy(::f32 cy)
//   {
//      bottom = top + cy;
//   }
//
//   inline void ::f32_rectangle::set_cxy(::f32 cx, ::f32 cy)
//   {
//      set_cx(cx);
//      set_cy(cy);
//   }
//
//   inline void ::f32_rectangle::set_cxy(::f32_size sz)
//   {
//      set_cxy((::f32) sz.cx, (::f32) sz.cy);
//   }
//
//   inline void ::f32_rectangle::set_cxy(::f32_size sz)
//   {
//      set_cxy(sz.cx, sz.cy);
//   }
//
//   inline void ::f32_rectangle::offset_x(::f32 x)
//   {
//      left     += x;
//      right    += x;
//   }
//
//   inline void ::f32_rectangle::offset_y(::f32 y)
//   {
//      top      += y;
//      bottom   += y;
//   }
//
//   inline void ::f32_rectangle::offset_xy(::f32 x, ::f32 y)
//   {
//      offset_x(x);
//      offset_y(y);
//   }
//
//   inline void ::f32_rectangle::set_x(::f32 x)
//   {
//      right    = right - left + x;
//      left     = x;
//   }
//
//   inline void ::f32_rectangle::set_y(::f32 y)
//   {
//      bottom   = bottom - top + y;
//      top      = y;
//   }
//
//   inline void ::f32_rectangle::set_xy(::f32 x, ::f32 y)
//   {
//      set_x(x);
//      set_y(y);
//   }
//
//   inline void ::f32_rectangle::set_xy(const ::f32_point & point)
//   {
//      set_xy((::f32) ::f32_point.x, (::f32) ::f32_point.y);
//   }
//
//   inline ::i32_rectangle * ::f32_rectangle::get(::i32_rectangle * prectangle) const
//
//   {
//      prectangle->left      = (::i32) left;
//
//      prectangle->right     = (::i32) right;
//
//      prectangle->top       = (::i32) top;
//
//      prectangle->bottom    = (::i32) bottom;
//
//      return prectangle;
//
//   }
//
//   inline ::f32 ::f32_rectangle::get_cx() const
//   {
//      return right - left;
//   }
//
//
//   inline ::f32 ::f32_rectangle::get_cy() const
//   {
//      return bottom - top;
//   }
//
//   inline ::f32_size ::f32_rectangle::get_cxy() const
//   {
//      return ::f32_size(get_cx(), get_cy());
//   }
//
//   inline ::f32_point & rectangle::top_left()
//   {
//      return *((::f32_point *) &left);
//   }
//
//   inline ::f32_point & rectangle::bottom_right()
//   {
//      return *((::f32_point *) &right);
//   }
//
//   inline ::f32_point ::f32_rectangle::top_left() const
//   {
//      return ::f32_point(left, top);
//   }
//
//   inline ::f32_point ::f32_rectangle::bottom_right() const
//   {
//      return ::f32_point(right, bottom);
//   }
//
//   inline ::f32_point ::f32_rectangle::top_right() const
//   {
//      return ::f32_point(right, top);
//   }
//
//   inline  ::f32_point ::f32_rectangle::bottom_left() const
//   {
//      return ::f32_point(left, bottom);
//   }
//
//   inline ::f32_rectangle & rectangle::constrain(::f32_rectangle & rectangle) const
//   {
//
//      if(::f32_rectangle.left < left)
//         ::f32_rectangle.left = left;
//
//      if(::f32_rectangle.right < right)
//         ::f32_rectangle.right = right;
//
//      if(::f32_rectangle.top < top)
//         ::f32_rectangle.top = top;
//
//      if(::f32_rectangle.bottom < bottom)
//         ::f32_rectangle.bottom = bottom;
//
//      return ::f32_rectangle;
//
//   }
//
//   inline void ::f32_rectangle::set_pos_dim(::f32 x, ::f32 y, ::f32 cx, ::f32 cy)
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
//   inline ::f32_rectangle & rectangle::operator = (const ::i32_rectangle & rectangle)
//   {
//
//      left     = (::f32) rectangle.left;
//      top      = (::f32) rectangle.top;
//      right    = (::f32) rectangle.right;
//      bottom   = (::f32) rectangle.bottom;
//
//      return *this;
//
//   }
//
//   inline ::f32 ::f32_rectangle::area() const
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


