#pragma once



























































//
//
//
//::i64 i64_rectangle::width() const noexcept
//{
//   return right - left;
//}
//::i64 i64_rectangle::height() const noexcept
//{
//   return bottom - top;
//}
//i64_size rect64SIZE_TYPE() const noexcept
//{
//   return i64_size(right - left, bottom - top);
//}
//long_long_point& i64_rectangle::top_left() noexcept
//{
//   return *((long_long_point*)this);
//}
//long_long_point& i64_rectangle::bottom_right() noexcept
//{
//   return *((long_long_point*)this + 1);
//}
//const long_long_point& i64_rectangle::top_left() const noexcept
//{
//   return *((long_long_point*)this);
//}
//const long_long_point& i64_rectangle::bottom_right() const noexcept
//{
//   return *((long_long_point*)this + 1);
//}
//TEMPLATE void i64_rectangle::swap_left_right() noexcept
//{
//   swap_left_right((::i64_rectangle*)(this));
//}
//void WINAPI i64_rectangle::swap_left_right(::i64_rectangle * RECT_TEMPLATE) noexcept
//
//{
//   ::i64 temp = RECT_TEMPLATE.left; RECT_TEMPLATE.left = RECT_TEMPLATE.right; RECT_TEMPLATE.right = temp;
//}
//
//i64_rectangle::operator ::i64_rectangle* () noexcept
//{
//   return this;
//}
//i64_rectangle::operator const ::i64_rectangle* () const noexcept
//{
//   return this;
//}
//i64_rectangle::operator RECT_TEMPLATE() const
//{
//   return ::rect_TEMPLATE((const ::i64_rectangle&)* this);
//}
//TEMPLATE bool i64_rectangle::contains(::long_long_point i32_point) const noexcept
//{
//   return ::contains(this, point);
//}
//TEMPLATE void i64_rectangle::set(::i64 x1, ::i64 y1, ::i64 x2, ::i64 y2) noexcept
//{
//   ::set_rect(this, x1, y1, x2, y2);
//}
//TEMPLATE void i64_rectangle::set(::long_long_point topLeft, ::long_long_point bottomRight) noexcept
//{
//   ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
//}
//TEMPLATE void i64_rectangle::null() noexcept
//{
//   ::null(this);
//}
//TEMPLATE void rect64copy(const ::i64_rectangle * pSrcRect) noexcept
//
//{
//   ::copy(this, pSrcRect);
//}
//
//TEMPLATE bool i64_rectangle::is_equal(const ::i64_rectangle * RECT_TEMPLATE) const noexcept
//
//{
//   return ::is_equal(this, RECT_TEMPLATE);
//}
//
//TEMPLATE void i64_rectangle::inflate(::i64 x, ::i64 y) noexcept
//{
//   ::inflate(this, x, y);
//}
//TEMPLATE void i64_rectangle::inflate(::i64_size i64_size) noexcept
//{
//   ::inflate(this, i64_size.cx, i64_size.cy);
//}
//TEMPLATE void i64_rectangle::deflate(::i64 x, ::i64 y) noexcept
//{
//   ::inflate(this, -x, -y);
//}
//TEMPLATE void i64_rectangle::deflate(::i64_size i64_size) noexcept
//{
//   ::inflate(this, -i64_size.cx, -i64_size.cy);
//}
//TEMPLATE void i64_rectangle::offset(::i64 x, ::i64 y) noexcept
//{
//   ::offset(this, x, y);
//}
//TEMPLATE void i64_rectangle::offset(::long_long_point long_long_point) noexcept
//{
//   ::offset(this, long_long_point.x, long_long_point.y);
//}
//TEMPLATE void i64_rectangle::set_size(::i64_size s) noexcept
//{
//   this->set_size(s.cx, s.cy);
//}
//TEMPLATE void i64_rectangle::rsize(::i64_size s) noexcept
//{
//   this->rsize(s.cx, s.cy);
//}
//TEMPLATE void i64_rectangle::set_size(::i64 cx, ::i64 cy) noexcept
//{
//   ::resize(this, cx, cy);
//}
//TEMPLATE void i64_rectangle::rsize(::i64 cx, ::i64 cy) noexcept
//{
//   ::reverse_size(this, cx, cy);
//}
//TEMPLATE void i64_rectangle::offset(::i64_size i64_size) noexcept
//{
//   ::offset(this, i64_size.cx, i64_size.cy);
//}
//TEMPLATE void i64_rectangle::move_to_y(::i64 y) noexcept
//{
//   bottom = height() + y; top = y;
//}
//TEMPLATE void i64_rectangle::move_to_x(::i64 x) noexcept
//{
//   right = width() + x; left = x;
//}
//TEMPLATE void i64_rectangle::move_to(::i64 x, ::i64 y) noexcept
//{
//   move_to_x(x); move_to_y(y);
//}
//TEMPLATE void i64_rectangle::move_to(::long_long_point i32_point) noexcept
//{
//   move_to_x(point.x); move_to_y(point.y);
//}
//TEMPLATE bool i64_rectangle::intersect(const ::i64_rectangle * rect1, const ::i64_rectangle * rect2) noexcept
//
//{
//   return ::intersect(this, rect1, rect2);
//}
//
//TEMPLATE bool i64_rectangle::unite(const ::i64_rectangle * rect1, const ::i64_rectangle * rect2) noexcept
//
//{
//   return ::unite(this, rect1, rect2);
//}
//
//TEMPLATE void i64_rectangle::operator=(const ::i64_rectangle & rectangleSource) noexcept
//{
//   ::copy(this, &rectangleSource);
//}
//TEMPLATE bool i64_rectangle::operator==(const ::i64_rectangle & i64_rectangle) const noexcept
//{
//   return ::is_equal(this, &i64_rectangle);
//}
//TEMPLATE bool i64_rectangle::operator!=(const ::i64_rectangle & i64_rectangle) const noexcept
//{
//   return !::is_equal(this, &i64_rectangle);
//}
//TEMPLATE void i64_rectangle::operator +=(::long_long_point long_long_point) noexcept
//{
//   ::offset(this, long_long_point.x, long_long_point.y);
//}
//TEMPLATE void i64_rectangle::operator +=(::i64_size i64_size) noexcept
//{
//   ::offset(this, i64_size.cx, i64_size.cy);
//}
//TEMPLATE void i64_rectangle::operator +=(const ::i64_rectangle * RECT_TEMPLATE) noexcept
//
//{
//   inflate(RECT_TEMPLATE);
//}
//
//TEMPLATE void i64_rectangle::operator-=(::long_long_point long_long_point) noexcept
//{
//   ::offset(this, -long_long_point.x, -long_long_point.y);
//}
//TEMPLATE void i64_rectangle::operator-=(::i64_size i64_size) noexcept
//{
//   ::offset(this, -i64_size.cx, -i64_size.cy);
//}
//TEMPLATE void i64_rectangle::operator-=(const ::i64_rectangle * RECT_TEMPLATE) noexcept
//
//{
//   deflate(RECT_TEMPLATE);
//}
//
//TEMPLATE void i64_rectangle::operator&=(const ::i64_rectangle & i64_rectangle) noexcept
//{
//   ::intersect(this, this, &i64_rectangle);
//}
//TEMPLATE void i64_rectangle::operator|=(const ::i64_rectangle & i64_rectangle) noexcept
//{
//   ::unite(this, this, &i64_rectangle);
//}
//i64_rectangle i64_rectangle::operator +(::long_long_point i32_point) const noexcept
//{
//   i64_rectangle i64_rectangle(*this); ::offset(&i64_rectangle, point.x, point.y); return i64_rectangle;
//}
//i64_rectangle i64_rectangle::operator-(::long_long_point i32_point) const noexcept
//{
//   i64_rectangle i64_rectangle(*this); ::offset(&i64_rectangle, -point.x, -point.y); return i64_rectangle;
//}
//i64_rectangle i64_rectangle::operator +(::i64_size i64_size) const noexcept
//{
//   i64_rectangle i64_rectangle(*this); ::offset(&i64_rectangle, i64_size.cx, i64_size.cy); return i64_rectangle;
//}
//i64_rectangle i64_rectangle::operator-(::i64_size i64_size) const noexcept
//{
//   i64_rectangle i64_rectangle(*this); ::offset(&i64_rectangle, -i64_size.cx, -i64_size.cy); return i64_rectangle;
//}
//i64_rectangle i64_rectangle::operator +(const ::i64_rectangle * RECT_TEMPLATE) const noexcept
//
//{
//   i64_rectangle i64_rectangle(this); i64_rectangle.inflate(RECT_TEMPLATE); return i64_rectangle;
//}
//
//i64_rectangle i64_rectangle::operator-(const ::i64_rectangle * RECT_TEMPLATE) const noexcept
//
//{
//   i64_rectangle i64_rectangle(this); i64_rectangle.deflate(RECT_TEMPLATE); return i64_rectangle;
//}
//
//i64_rectangle i64_rectangle::operator&(const ::i64_rectangle & rect2) const noexcept
//{
//   i64_rectangle i64_rectangle; ::intersect(&i64_rectangle, this, &rect2);
//   return i64_rectangle;
//}
//i64_rectangle i64_rectangle::operator|(const ::i64_rectangle & rect2) const noexcept
//{
//   i64_rectangle i64_rectangle; ::unite(&i64_rectangle, this, &rect2);
//   return i64_rectangle;
//}
////TEMPLATE bool i64_rectangle::subtract(const ::i64_rectangle * pRectSrc1, const ::i64_rectangle * lpRectSrc2) noexcept
//
////   { return ::subtract(this, pRectSrc1, lpRectSrc2); }
//
//
//TEMPLATE void i64_rectangle::normalize() noexcept
//{
//   ::i64 nTemp;
//   if (left > right)
//   {
//      nTemp = left;
//      left = right;
//      right = nTemp;
//   }
//   if (top > bottom)
//   {
//      nTemp = top;
//      top = bottom;
//      bottom = nTemp;
//   }
//}
//
//TEMPLATE void i64_rectangle::inflate(const ::i64_rectangle * RECT_TEMPLATE) noexcept
//
//{
//   left -= RECT_TEMPLATE.left;      top -= RECT_TEMPLATE.top;
//
//   right += RECT_TEMPLATE.right;      bottom += RECT_TEMPLATE.bottom;
//
//}
//
//TEMPLATE void i64_rectangle::inflate(::i64 l, ::i64 t, ::i64 r, ::i64 b) noexcept
//{
//   left -= l;         top -= t;
//   right += r;         bottom += b;
//}
//
//TEMPLATE void i64_rectangle::deflate(const ::i64_rectangle * RECT_TEMPLATE) noexcept
//
//{
//   left += RECT_TEMPLATE.left;   top += RECT_TEMPLATE.top;
//
//   right -= RECT_TEMPLATE.right;   bottom -= RECT_TEMPLATE.bottom;
//
//}
//
//TEMPLATE void i64_rectangle::deflate(::i64 l, ::i64 t, ::i64 r, ::i64 b) noexcept
//{
//   left += l;      top += t;
//   right -= r;      bottom -= b;
//}
//
//i64_rectangle i64_rectangle::MulDiv(::i64 nMultiplier, ::i64 nDivisor) const noexcept
//{
//   return i64_rectangle(
//      ::MulDiv(left, nMultiplier, nDivisor),
//      ::MulDiv(top, nMultiplier, nDivisor),
//      ::MulDiv(right, nMultiplier, nDivisor),
//      ::MulDiv(bottom, nMultiplier, nDivisor));
//}
//
//
//::i64 i64_rectangle::area() const
//{
//
//   return size().area();
//
//}
//
//TEMPLATE ::f64 ::f64_rectangle::width() const noexcept { return right - left; }
//TEMPLATE ::f64 ::f64_rectangle::height() const noexcept { return bottom - top; }
//TEMPLATE class ::f64_size rectdSIZE_TYPE() const noexcept { return ::f64_size(width(), height()); }
//
//
//TEMPLATE void ::f64_rectangle::set_size(::f64 cx, ::f64 cy) noexcept { right = left + cx;  bottom = top + cy; }
//TEMPLATE void ::f64_rectangle::set_size(const ::f64_size & size) noexcept { set_size(size.cx, size.cy); }
//TEMPLATE ::f64_point& ::f64_rectangle::top_left() noexcept { return *((::f64_point*)this); }
//TEMPLATE ::f64_point& ::f64_rectangle::bottom_right() noexcept { return *((::f64_point*)this + 1); }
//TEMPLATE const ::f64_point& ::f64_rectangle::top_left() const noexcept { return *((const ::f64_point*)this); }
//TEMPLATE const ::f64_point& ::f64_rectangle::bottom_right() const noexcept {
//   return *((const ::f64_point*)this + 1);
//  TEMPLATE void ::f64_rectangle::swap_left_right() noexcept { ::swap_left_right(this); }
//
//  TEMPLATE ::f64_rectangle::operator ::f64_rectangle* () noexcept
//   {
//      return this;
//   }
//  TEMPLATE ::f64_rectangle::operator const ::f64_rectangle& () const noexcept
//   {
//      return (const ::f64_rectangle&)this;
//   }
//  TEMPLATE bool ::f64_rectangle::contains(::f64_point i32_point) const noexcept
//   {
//      return ::contains((const ::f64_rectangle&)this, i32_point) != false;
//   }
//  TEMPLATE void ::f64_rectangle::set(::f64 x1, ::f64 y1, ::f64 x2, ::f64 y2) noexcept
//   {
//      ::set_rect(this, x1, y1, x2, y2);
//   }
//  TEMPLATE void ::f64_rectangle::set(::f64_point topLeft, ::f64_point bottomRight) noexcept
//   {
//      ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
//   }
//
//  TEMPLATE void ::f64_rectangle::null() noexcept
//   {
//
//      ::null(this);
//
//   }
//
//
//  TEMPLATE bool ::f64_rectangle::is_empty() const noexcept
//   {
//
//      return left == right && top == bottom;
//
//   }
//
//
//  TEMPLATE void rectdcopy(const ::f64_rectangle & pSrcRect) noexcept
//
//   {
//      ::copy(this, pSrcRect);
//   }
//
//  TEMPLATE bool ::f64_rectangle::is_equal(const ::f64_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      return ::is_equal((const ::f64_rectangle&)this, RECT_TEMPLATE) != false;
//   }
//
//  TEMPLATE void ::f64_rectangle::inflate(::f64 x, ::f64 y) noexcept
//   {
//      ::inflate(this, x, y);
//   }
//  TEMPLATE void ::f64_rectangle::inflate(::f64_size i32_size) noexcept
//   {
//      ::inflate(this, size.cx, size.cy);
//   }
//  TEMPLATE void ::f64_rectangle::deflate(::f64 x, ::f64 y) noexcept
//   {
//      ::inflate(this, -x, -y);
//   }
//  TEMPLATE void ::f64_rectangle::deflate(::f64_size i32_size) noexcept
//   {
//      ::inflate(this, -size.cx, -size.cy);
//   }
//  TEMPLATE void ::f64_rectangle::offset(::f64 x, ::f64 y) noexcept
//   {
//      ::offset(this, x, y);
//   }
//  TEMPLATE void ::f64_rectangle::offset(::f64_point i32_point) noexcept
//   {
//      ::offset(this, point.x, point.y);
//   }
//  TEMPLATE void ::f64_rectangle::offset(::f64_size i32_size) noexcept
//   {
//      ::offset(this, size.cx, size.cy);
//   }
//  TEMPLATE void ::f64_rectangle::move_to_y(::f64 y) noexcept
//   {
//      bottom = height() + y; top = y;
//   }
//  TEMPLATE void ::f64_rectangle::move_to_x(::f64 x) noexcept
//   {
//      right = width() + x; left = x;
//   }
//  TEMPLATE void ::f64_rectangle::move_to(::f64 x, ::f64 y) noexcept
//   {
//      move_to_x(x); move_to_y(y);
//   }
//  TEMPLATE void ::f64_rectangle::move_to(::f64_point i32_point) noexcept
//   {
//      move_to_x(point.x); move_to_y(point.y);
//   }
//   //TEMPLATE bool ::f64_rectangle::intersect_x(const ::f64_rectangle & rect1, const ::f64_rectangle & rect2) noexcept
//
//   //{
//   //   return ::x_intersect_rect(this, rect1, rect2) != false;
//
//   //}
//   //TEMPLATE bool ::f64_rectangle::intersect_y(const ::f64_rectangle & rect1, const ::f64_rectangle & rect2) noexcept
//
//   //{
//   //   return ::y_intersect_rect(this, rect1, rect2) != false;
//
//   //}
//  TEMPLATE bool ::f64_rectangle::intersect(const ::f64_rectangle & rect1, const ::f64_rectangle & rect2) noexcept
//
//   {
//      return ::intersect(this, rect1, rect2) != false;
//
//   }
//   //::f64_rectangle ::f64_rectangle::intersect(const ::f64_rectangle & RECT_TEMPLATE) const noexcept
//
//   //{
//   //   ::f64_rectangle RECT_TEMPLATE;
//   //   ::intersect(&RECT_TEMPLATE, this, RECT_TEMPLATE);
//
//   //   return RECT_TEMPLATE;
//   //}
//  TEMPLATE bool ::f64_rectangle::unite(const ::f64_rectangle & rect1, const ::f64_rectangle & rect2) noexcept
//
//   {
//      return ::unite(this, rect1, rect2) != false;
//   }
//
//  TEMPLATE void ::f64_rectangle::operator=(const ::f64_rectangle & rectectSrc) noexcept
//   {
//      ::copy(this, (const ::f64_rectangle&)& rectangleSource);
//   }
//  TEMPLATE bool ::f64_rectangle::operator==(const ::f64_rectangle & rectectd) const noexcept
//   {
//      return ::is_equal((const ::f64_rectangle&)this, (const ::f64_rectangle&)& ::f64_rectangle) != false;
//   }
//  TEMPLATE bool ::f64_rectangle::operator!=(const ::f64_rectangle & rectectd) const noexcept
//   {
//      return !::is_equal((const ::f64_rectangle&)this, (const ::f64_rectangle&)& ::f64_rectangle) != false;
//   }
//  TEMPLATE void ::f64_rectangle::operator +=(::f64_point i32_point) noexcept
//   {
//      ::offset(this, point.x, point.y);
//   }
//  TEMPLATE void ::f64_rectangle::operator +=(::f64_size i32_size) noexcept
//   {
//      ::offset(this, size.cx, size.cy);
//   }
//  TEMPLATE void ::f64_rectangle::operator +=(const ::f64_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      inflate(RECT_TEMPLATE);
//   }
//
//  TEMPLATE void ::f64_rectangle::operator-=(::f64_point i32_point) noexcept
//   {
//      ::offset(this, -point.x, -point.y);
//   }
//  TEMPLATE void ::f64_rectangle::operator-=(::f64_size i32_size) noexcept
//   {
//      ::offset(this, -size.cx, -size.cy);
//   }
//  TEMPLATE void ::f64_rectangle::operator-=(const ::f64_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      deflate(RECT_TEMPLATE);
//   }
//
//  TEMPLATE void ::f64_rectangle::operator&=(const ::f64_rectangle & rectectd) noexcept
//   {
//      ::intersect(this, this, (const ::f64_rectangle&)& ::f64_rectangle);
//   }
//  TEMPLATE void ::f64_rectangle::operator|=(const ::f64_rectangle & rectectd) noexcept
//   {
//      ::unite(this, this, (const ::f64_rectangle&)& ::f64_rectangle);
//   }
//  TEMPLATE ::f64_rectangle ::f64_rectangle::operator +(::f64_point i32_point) const noexcept
//   {
//      ::f64_rectangle ::f64_rectangle(*this); ::offset(&::f64_rectangle, point.x, point.y); return ::f64_rectangle;
//   }
//  TEMPLATE ::f64_rectangle ::f64_rectangle::operator-(::f64_point i32_point) const noexcept
//   {
//      ::f64_rectangle ::f64_rectangle(*this); ::offset(&::f64_rectangle, -point.x, -point.y); return ::f64_rectangle;
//   }
//  TEMPLATE ::f64_rectangle ::f64_rectangle::operator +(::f64_size i32_size) const noexcept
//   {
//      ::f64_rectangle ::f64_rectangle(*this); ::offset(&::f64_rectangle, size.cx, size.cy); return ::f64_rectangle;
//   }
//  TEMPLATE ::f64_rectangle ::f64_rectangle::operator-(::f64_size i32_size) const noexcept
//   {
//      ::f64_rectangle ::f64_rectangle(*this); ::offset(&::f64_rectangle, -size.cx, -size.cy); return ::f64_rectangle;
//   }
//  TEMPLATE ::f64_rectangle ::f64_rectangle::operator +(const ::f64_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      ::f64_rectangle ::f64_rectangle((const ::f64_rectangle&)this); ::f64_rectangle.inflate(RECT_TEMPLATE); return ::f64_rectangle;
//   }
//
//  TEMPLATE ::f64_rectangle ::f64_rectangle::operator-(const ::f64_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      ::f64_rectangle ::f64_rectangle((const ::f64_rectangle&)this); ::f64_rectangle.deflate(RECT_TEMPLATE); return ::f64_rectangle;
//   }
//
//  TEMPLATE ::f64_rectangle ::f64_rectangle::operator&(const ::f64_rectangle & rectect2) const noexcept
//   {
//      ::f64_rectangle ::f64_rectangle; ::intersect(&::f64_rectangle, (const ::f64_rectangle&)this, (const ::f64_rectangle&)& rect2);
//      return ::f64_rectangle;
//   }
//  TEMPLATE ::f64_rectangle ::f64_rectangle::operator|(const ::f64_rectangle & rectect2) const noexcept
//   {
//      ::f64_rectangle ::f64_rectangle; ::unite(&::f64_rectangle, (const ::f64_rectangle&)this, (const ::f64_rectangle&)& rect2);
//      return ::f64_rectangle;
//   }
//   //TEMPLATE bool ::f64_rectangle::subtract(const ::f64_rectangle & pRectSrc1, const ::f64_rectangle & lpRectSrc2) noexcept
//
//   // { return ::subtract(this, pRectSrc1, lpRectSrc2) != false; }
//
//
//  TEMPLATE void ::f64_rectangle::normalize() noexcept
//   {
//      ::f64 nTemp;
//      if (left > right)
//      {
//         nTemp = left;
//         left = right;
//         right = nTemp;
//      }
//      if (top > bottom)
//      {
//         nTemp = top;
//         top = bottom;
//         bottom = nTemp;
//      }
//   }
//
//  TEMPLATE void ::f64_rectangle::inflate(const ::f64_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      left -= RECT_TEMPLATE.left;      top -= RECT_TEMPLATE.top;
//
//      right += RECT_TEMPLATE.right;      bottom += RECT_TEMPLATE.bottom;
//
//   }
//
//  TEMPLATE void ::f64_rectangle::inflate(::f64 l, ::f64 t, ::f64 r, ::f64 b) noexcept
//   {
//      left -= l;         top -= t;
//      right += r;         bottom += b;
//   }
//
//  TEMPLATE void ::f64_rectangle::deflate(const ::f64_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      left += RECT_TEMPLATE.left;   top += RECT_TEMPLATE.top;
//
//      right -= RECT_TEMPLATE.right;   bottom -= RECT_TEMPLATE.bottom;
//
//   }
//
//  TEMPLATE void ::f64_rectangle::deflate(::f64 l, ::f64 t, ::f64 r, ::f64 b) noexcept
//   {
//      left += l;      top += t;
//      right -= r;      bottom -= b;
//   }
//
//  TEMPLATE ::f64_rectangle ::f64_rectangle::MulDiv(::f64 nMultiplier, ::f64 nDivisor) const noexcept
//   {
//      return ::f64_rectangle(left * nMultiplier / nDivisor,
//         top * nMultiplier / nDivisor,
//         right * nMultiplier / nDivisor,
//         bottom * nMultiplier / nDivisor);
//   }
//
//  TEMPLATE ::f64 ::f64_rectangle::area()
//   {
//
//      return size().area();
//
//   }
//
//
//  TEMPLATE void ::f64_rectangle::get_bounding_box(const ::f64_point * ppoint, ::collection::count count)
//
//   {
//
//      f64_point_array::get_bounding_box(this, ppoint, count);
//
//
//   }
//
//  TEMPLATE void ::f64_rectangle::get_bounding_box(const f64_point_array & pointa)
//   {
//
//      pointa.get_bounding_box(this);
//
//   }
//
//  TEMPLATE void ::f64_rectangle::CenterOf(const ::f64_rectangle & RECT_TEMPLATE, ::f64_size i32_size)
//
//   {
//      ::f64 cx = size.cx;
//      ::f64 cy = size.cy;
//
//      ::f64 Δx = ::width(RECT_TEMPLATE);
//
//      ::f64 Δy = ::height(RECT_TEMPLATE);
//
//
//      left = RECT_TEMPLATE.left + (Δx - cx) / 2;
//
//      top = RECT_TEMPLATE.top + (Δy - cy) / 2;
//
//      right = left + cx;
//      bottom = top + cy;
//
//   }
//
//  TEMPLATE void ::f64_rectangle::CenterOf(const ::f64_rectangle & RECT_TEMPLATE)
//
//   {
//
//      CenterOf(RECT_TEMPLATE, size());
//
//
//   }
//
//  TEMPLATE ::f64 ::f64_rectangle::minimum_signed_absolute_dimension(bool bNegativePreference) const noexcept
//   {
//
//      ::f64 w = width();
//
//      ::f64 h = height();
//
//      if (fabs(w) < fabs(h))
//      {
//
//         return w;
//
//      }
//      else if (fabs(h) < fabs(w))
//      {
//
//         return h;
//
//      }
//      else if (bNegativePreference) // absolutely equal, prefer negative ...
//      {
//
//         return minimum(w, h);
//
//      }
//      else // ... otherwise prefer positive
//      {
//
//         return maximum(w, h);
//
//      }
//
//
//   }
//
//
//   ::f64 ::f64_rectangle::maximum_signed_absolute_dimension(bool bPositivePreference) const noexcept
//   {
//
//      ::f64 w = width();
//
//      ::f64 h = height();
//
//      if (fabs(w) > fabs(h))
//      {
//
//         return w;
//
//      }
//      else if (fabs(h) > fabs(w))
//      {
//
//         return h;
//
//      }
//      else if (bPositivePreference) // absolutely equal, prefer positive ...
//      {
//
//         return maximum(w, h);
//
//      }
//      else // ... otherwise prefer negative
//      {
//
//         return minimum(w, h);
//
//      }
//
//
//   }
//
//
//
//   ::f64 ::f64_rectangle::minimum_absolute_dimension() const noexcept { return minimum(fabs(width()), fabs(height())); }
//   ::f64 ::f64_rectangle::maximum_absolute_dimension() const noexcept { return minimum(fabs(width()), fabs(height())); }
//  TEMPLATE bool ::f64_rectangle::contains_x(::f64 x) const noexcept
//   {
//      return left <= x && x <= right;
//   }
//  TEMPLATE bool ::f64_rectangle::contains_y(::f64 y) const noexcept
//   {
//      return top <= y && y <= bottom;
//   }
//
//
//  TEMPLATE ::f64_rectangle& ::f64_rectangle::intersect(const ::f64_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      ::intersect(this, this, RECT_TEMPLATE);
//
//      return *this;
//   }
//
//
//  TEMPLATE ::f64_rectangle ::f64_rectangle::intersect(const ::f64_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      ::f64_rectangle RECT_TEMPLATE;
//      ::intersect(&RECT_TEMPLATE, this, RECT_TEMPLATE);
//
//      return RECT_TEMPLATE;
//   }
//
//  TEMPLATE void ::f64_rectangle::set(::f64 d) noexcept
//   {
//
//      set(d, d, d, d);
//
//   }
//
//
//  TEMPLATE bool ::f64_rectangle::is_null() const noexcept
//   {
//
//      return left == 0.0 && right == 0.0 && top == 0.0 && bottom == 0.0;
//
//   }
//  TEMPLATE void ::f64_rectangle::offset_x(::f64 x) noexcept
//   {
//      left += x;
//      right += x;
//   }
//
//
//  TEMPLATE void ::f64_rectangle::offset_y(::f64 y) noexcept
//   {
//      top += y;
//      bottom += y;
//   }
//
//
//  TEMPLATE ::f64_point ::f64_rectangle::center() const noexcept
//   {
//
//      return ::f64_point((left + right) / 2.0, (top + bottom) / 2.0);
//
//   }
//
//
//  TEMPLATE ::f64_point ::f64_rectangle::top_right() const
//   {
//
//      return ::f64_point(right, top);
//
//   }
//
//  TEMPLATE ::f64_point ::f64_rectangle::bottom_left() const
//   {
//
//      return ::f64_point(left, bottom);
//
//   }
//
//
//  TEMPLATETEMPLATE void ::f64_rectangle::align_rate(::f64 x, ::f64 y, const ::f64_rectangle & RECT_TEMPLATE)
//   {
//
//      align_x(x, RECT_TEMPLATE);
//
//      align_y(y, RECT_TEMPLATE);
//
//   }
//
//  TEMPLATETEMPLATE void ::f64_rectangle::align_x(::f64 dRate, const ::f64_rectangle & RECT_TEMPLATE)
//   {
//
//      UNIT_TYPE x;
//
//      x = (UNIT_TYPE)(RECT_TEMPLATE.left + (RECT_TEMPLATE.right - RECT_TEMPLATE.left - width()) * ((dRate + 1.0) / 2.0));
//
//      move_to_x(x);
//
//   }
//
//
//  TEMPLATETEMPLATE void ::f64_rectangle::align_y(::f64 dRate, const ::f64_rectangle & RECT_TEMPLATE)
//   {
//
//      UNIT_TYPE y;
//
//      y = (UNIT_TYPE)(RECT_TEMPLATE.top + (RECT_TEMPLATE.bottom - RECT_TEMPLATE.top - height()) * ((dRate + 1.0) / 2.0));
//
//      move_to_y(y);
//
//   }
//
//
//  TEMPLATETEMPLATE bool ::f64_rectangle::intersects(const ::f64_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//
//      return intersects_x(RECT_TEMPLATE) && intersects_y(RECT_TEMPLATE);
//
//
//   }
//
//
//  TEMPLATETEMPLATE bool ::f64_rectangle::intersects_x(const ::f64_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      return (left >= RECT_TEMPLATE.left && left <= RECT_TEMPLATE.right) ||
//
//         (right >= RECT_TEMPLATE.left && right <= RECT_TEMPLATE.right) ||
//
//         (RECT_TEMPLATE.left >= left && RECT_TEMPLATE.left <= right) ||
//
//         (RECT_TEMPLATE.right >= left && RECT_TEMPLATE.right <= right);
//
//   }
//
//  TEMPLATETEMPLATE bool ::f64_rectangle::intersects_y(const ::f64_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      return (top >= RECT_TEMPLATE.top && top <= RECT_TEMPLATE.bottom) ||
//
//         (bottom >= RECT_TEMPLATE.top && bottom <= RECT_TEMPLATE.bottom) ||
//
//         (RECT_TEMPLATE.top >= top && RECT_TEMPLATE.top <= bottom) ||
//
//         (RECT_TEMPLATE.bottom >= top && RECT_TEMPLATE.bottom <= bottom);
//
//   }
//
//
//




//template < typename TARGET, typename SOURCE >
//inline TARGET * _001CopyRect(TARGET * prectTarget, const SOURCE * prectSource)
//{
//
//   return _001SetRectDim(
//      prectTarget,
//      (decltype(::left(prectTarget))) ::left(prectSource),
//      (decltype(::top(prectTarget))) ::top(prectSource),
//      (decltype(::width(prectTarget))) ::width(prectSource),
//      (decltype(::height(prectTarget))) ::height(prectSource));
//
//}


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
void rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > ::get_bounding_box(const POINT_BASE_TYPE * ppoint, ::collection::count count)
{

   ::get_bounding_box(this, ppoint, count);

}




