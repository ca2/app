#pragma once


//namespace html
//{
//
//
//   class CLASS_DECL_CORE ::rectf
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
//      inline ::rectf();
//
//
//      inline ::pointf & top_left();
//      inline ::pointf & bottom_right();
//      inline ::pointf top_left() const;
//      inline ::pointf bottom_right() const;
//      inline ::pointf top_right() const;
//      inline ::pointf bottom_left() const;
//
//      inline ::rectf & constrain(::rectf & rect) const;
//
//
//      inline bool contains(float x, float y) const;
//      inline bool contains(const ::pointf & point) const;
//      inline void offset_x(float x);
//      inline void offset_y(float y);
//      inline void offset_xy(float x, float y);
//      inline void set_x(float x);
//      inline void set_y(float y);
//      inline void set_xy(float x, float y);
//      inline void set_xy(const ::pointf & point);
//      inline void set_cx(float cx);
//      inline void set_cy(float cy);
//      inline void set_cxy(float cx, float cy);
//      inline void set_cxy(::sizef sz);
//      inline void set_cxy(::sizef sz);
//      inline void set_pos_dim(float x, float y, float cx, float cy);
//      inline RECT32 * get(RECT32 * prect) const;
//
//      inline float get_cx() const;
//      inline float get_cy() const;
//      inline ::sizef get_cxy() const;
//      inline float area() const;
//
//      inline ::rectf & operator = (const ::rect & rect);
//
//   };
//
//
//   inline ::rectf::rectf()
//   {
//
//      left     = 0.0f;
//      top      = 0.0f;
//      right    = 0.0f;
//      bottom   = 0.0f;
//
//   }
//
//   inline bool ::rectf::contains(float x, float y) const
//   {
//
//      return x >= left && x <= right && y >= top  && y <= bottom;
//
//   }
//
//   inline bool ::rectf::contains(const ::pointf & point) const
//   {
//
//      return contains((float) ::pointf.x, (float) ::pointf.y);
//
//   }
//
//   inline void ::rectf::set_cx(float cx)
//   {
//      right = left + cx;
//   }
//
//   inline void ::rectf::set_cy(float cy)
//   {
//      bottom = top + cy;
//   }
//
//   inline void ::rectf::set_cxy(float cx, float cy)
//   {
//      set_cx(cx);
//      set_cy(cy);
//   }
//
//   inline void ::rectf::set_cxy(::sizef sz)
//   {
//      set_cxy((float) sz.cx, (float) sz.cy);
//   }
//
//   inline void ::rectf::set_cxy(::sizef sz)
//   {
//      set_cxy(sz.cx, sz.cy);
//   }
//
//   inline void ::rectf::offset_x(float x)
//   {
//      left     += x;
//      right    += x;
//   }
//
//   inline void ::rectf::offset_y(float y)
//   {
//      top      += y;
//      bottom   += y;
//   }
//
//   inline void ::rectf::offset_xy(float x, float y)
//   {
//      offset_x(x);
//      offset_y(y);
//   }
//
//   inline void ::rectf::set_x(float x)
//   {
//      right    = right - left + x;
//      left     = x;
//   }
//
//   inline void ::rectf::set_y(float y)
//   {
//      bottom   = bottom - top + y;
//      top      = y;
//   }
//
//   inline void ::rectf::set_xy(float x, float y)
//   {
//      set_x(x);
//      set_y(y);
//   }
//
//   inline void ::rectf::set_xy(const ::pointf & point)
//   {
//      set_xy((float) ::pointf.x, (float) ::pointf.y);
//   }
//
//   inline RECT32 * ::rectf::get(RECT32 * prect) const
//
//   {
//      prect->left      = (i32) left;
//
//      prect->right     = (i32) right;
//
//      prect->top       = (i32) top;
//
//      prect->bottom    = (i32) bottom;
//
//      return prect;
//
//   }
//
//   inline float ::rectf::get_cx() const
//   {
//      return right - left;
//   }
//
//
//   inline float ::rectf::get_cy() const
//   {
//      return bottom - top;
//   }
//
//   inline ::sizef ::rectf::get_cxy() const
//   {
//      return ::sizef(get_cx(), get_cy());
//   }
//
//   inline ::pointf & rect::top_left()
//   {
//      return *((::pointf *) &left);
//   }
//
//   inline ::pointf & rect::bottom_right()
//   {
//      return *((::pointf *) &right);
//   }
//
//   inline ::pointf ::rectf::top_left() const
//   {
//      return ::pointf(left, top);
//   }
//
//   inline ::pointf ::rectf::bottom_right() const
//   {
//      return ::pointf(right, bottom);
//   }
//
//   inline ::pointf ::rectf::top_right() const
//   {
//      return ::pointf(right, top);
//   }
//
//   inline  ::pointf ::rectf::bottom_left() const
//   {
//      return ::pointf(left, bottom);
//   }
//
//   inline ::rectf & rect::constrain(::rectf & rect) const
//   {
//
//      if(::rectf.left < left)
//         ::rectf.left = left;
//
//      if(::rectf.right < right)
//         ::rectf.right = right;
//
//      if(::rectf.top < top)
//         ::rectf.top = top;
//
//      if(::rectf.bottom < bottom)
//         ::rectf.bottom = bottom;
//
//      return ::rectf;
//
//   }
//
//   inline void ::rectf::set_pos_dim(float x, float y, float cx, float cy)
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
//   inline ::rectf & rect::operator = (const ::rect & rect)
//   {
//
//      left     = (float) rect.left;
//      top      = (float) rect.top;
//      right    = (float) rect.right;
//      bottom   = (float) rect.bottom;
//
//      return *this;
//
//   }
//
//   inline float ::rectf::area() const
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


