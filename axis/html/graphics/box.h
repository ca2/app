#pragma once


//namespace html
//{
//
//
//   class CLASS_DECL_CORE ::rectangle_f32
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
//      inline ::rectangle_f32();
//
//
//      inline ::point_f32 & top_left();
//      inline ::point_f32 & bottom_right();
//      inline ::point_f32 top_left() const;
//      inline ::point_f32 bottom_right() const;
//      inline ::point_f32 top_right() const;
//      inline ::point_f32 bottom_left() const;
//
//      inline ::rectangle_f32 & constrain(::rectangle_f32 & rectangle) const;
//
//
//      inline bool contains(float x, float y) const;
//      inline bool contains(const ::point_f32 & point) const;
//      inline void offset_x(float x);
//      inline void offset_y(float y);
//      inline void offset_xy(float x, float y);
//      inline void set_x(float x);
//      inline void set_y(float y);
//      inline void set_xy(float x, float y);
//      inline void set_xy(const ::point_f32 & point);
//      inline void set_cx(float cx);
//      inline void set_cy(float cy);
//      inline void set_cxy(float cx, float cy);
//      inline void set_cxy(::size_f32 sz);
//      inline void set_cxy(::size_f32 sz);
//      inline void set_pos_dim(float x, float y, float cx, float cy);
//      inline RECTANGLE_I32 * get(RECTANGLE_I32 * prectangle) const;
//
//      inline float get_cx() const;
//      inline float get_cy() const;
//      inline ::size_f32 get_cxy() const;
//      inline float area() const;
//
//      inline ::rectangle_f32 & operator = (const ::rectangle_i32 & rectangle);
//
//   };
//
//
//   inline ::rectangle_f32::rectangle_f32()
//   {
//
//      left     = 0.0f;
//      top      = 0.0f;
//      right    = 0.0f;
//      bottom   = 0.0f;
//
//   }
//
//   inline bool ::rectangle_f32::contains(float x, float y) const
//   {
//
//      return x >= left && x <= right && y >= top  && y <= bottom;
//
//   }
//
//   inline bool ::rectangle_f32::contains(const ::point_f32 & point) const
//   {
//
//      return contains((float) ::point_f32.x, (float) ::point_f32.y);
//
//   }
//
//   inline void ::rectangle_f32::set_cx(float cx)
//   {
//      right = left + cx;
//   }
//
//   inline void ::rectangle_f32::set_cy(float cy)
//   {
//      bottom = top + cy;
//   }
//
//   inline void ::rectangle_f32::set_cxy(float cx, float cy)
//   {
//      set_cx(cx);
//      set_cy(cy);
//   }
//
//   inline void ::rectangle_f32::set_cxy(::size_f32 sz)
//   {
//      set_cxy((float) sz.cx, (float) sz.cy);
//   }
//
//   inline void ::rectangle_f32::set_cxy(::size_f32 sz)
//   {
//      set_cxy(sz.cx, sz.cy);
//   }
//
//   inline void ::rectangle_f32::offset_x(float x)
//   {
//      left     += x;
//      right    += x;
//   }
//
//   inline void ::rectangle_f32::offset_y(float y)
//   {
//      top      += y;
//      bottom   += y;
//   }
//
//   inline void ::rectangle_f32::offset_xy(float x, float y)
//   {
//      offset_x(x);
//      offset_y(y);
//   }
//
//   inline void ::rectangle_f32::set_x(float x)
//   {
//      right    = right - left + x;
//      left     = x;
//   }
//
//   inline void ::rectangle_f32::set_y(float y)
//   {
//      bottom   = bottom - top + y;
//      top      = y;
//   }
//
//   inline void ::rectangle_f32::set_xy(float x, float y)
//   {
//      set_x(x);
//      set_y(y);
//   }
//
//   inline void ::rectangle_f32::set_xy(const ::point_f32 & point)
//   {
//      set_xy((float) ::point_f32.x, (float) ::point_f32.y);
//   }
//
//   inline RECTANGLE_I32 * ::rectangle_f32::get(RECTANGLE_I32 * prectangle) const
//
//   {
//      prectangle->left      = (i32) left;
//
//      prectangle->right     = (i32) right;
//
//      prectangle->top       = (i32) top;
//
//      prectangle->bottom    = (i32) bottom;
//
//      return prectangle;
//
//   }
//
//   inline float ::rectangle_f32::get_cx() const
//   {
//      return right - left;
//   }
//
//
//   inline float ::rectangle_f32::get_cy() const
//   {
//      return bottom - top;
//   }
//
//   inline ::size_f32 ::rectangle_f32::get_cxy() const
//   {
//      return ::size_f32(get_cx(), get_cy());
//   }
//
//   inline ::point_f32 & rectangle::top_left()
//   {
//      return *((::point_f32 *) &left);
//   }
//
//   inline ::point_f32 & rectangle::bottom_right()
//   {
//      return *((::point_f32 *) &right);
//   }
//
//   inline ::point_f32 ::rectangle_f32::top_left() const
//   {
//      return ::point_f32(left, top);
//   }
//
//   inline ::point_f32 ::rectangle_f32::bottom_right() const
//   {
//      return ::point_f32(right, bottom);
//   }
//
//   inline ::point_f32 ::rectangle_f32::top_right() const
//   {
//      return ::point_f32(right, top);
//   }
//
//   inline  ::point_f32 ::rectangle_f32::bottom_left() const
//   {
//      return ::point_f32(left, bottom);
//   }
//
//   inline ::rectangle_f32 & rectangle::constrain(::rectangle_f32 & rectangle) const
//   {
//
//      if(::rectangle_f32.left < left)
//         ::rectangle_f32.left = left;
//
//      if(::rectangle_f32.right < right)
//         ::rectangle_f32.right = right;
//
//      if(::rectangle_f32.top < top)
//         ::rectangle_f32.top = top;
//
//      if(::rectangle_f32.bottom < bottom)
//         ::rectangle_f32.bottom = bottom;
//
//      return ::rectangle_f32;
//
//   }
//
//   inline void ::rectangle_f32::set_pos_dim(float x, float y, float cx, float cy)
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
//   inline ::rectangle_f32 & rectangle::operator = (const ::rectangle_i32 & rectangle)
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
//   inline float ::rectangle_f32::area() const
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


