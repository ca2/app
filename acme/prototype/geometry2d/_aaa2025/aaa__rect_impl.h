#pragma once



























































//
//
//
//long long i64_rectangle::width() const noexcept
//{
//   return right - left;
//}
//long long i64_rectangle::height() const noexcept
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
//   long long temp = RECT_TEMPLATE.left; RECT_TEMPLATE.left = RECT_TEMPLATE.right; RECT_TEMPLATE.right = temp;
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
//TEMPLATE void i64_rectangle::set(long long x1, long long y1, long long x2, long long y2) noexcept
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
//TEMPLATE void i64_rectangle::inflate(long long x, long long y) noexcept
//{
//   ::inflate(this, x, y);
//}
//TEMPLATE void i64_rectangle::inflate(::i64_size i64_size) noexcept
//{
//   ::inflate(this, i64_size.cx, i64_size.cy);
//}
//TEMPLATE void i64_rectangle::deflate(long long x, long long y) noexcept
//{
//   ::inflate(this, -x, -y);
//}
//TEMPLATE void i64_rectangle::deflate(::i64_size i64_size) noexcept
//{
//   ::inflate(this, -i64_size.cx, -i64_size.cy);
//}
//TEMPLATE void i64_rectangle::offset(long long x, long long y) noexcept
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
//TEMPLATE void i64_rectangle::set_size(long long cx, long long cy) noexcept
//{
//   ::resize(this, cx, cy);
//}
//TEMPLATE void i64_rectangle::rsize(long long cx, long long cy) noexcept
//{
//   ::reverse_size(this, cx, cy);
//}
//TEMPLATE void i64_rectangle::offset(::i64_size i64_size) noexcept
//{
//   ::offset(this, i64_size.cx, i64_size.cy);
//}
//TEMPLATE void i64_rectangle::move_to_y(long long y) noexcept
//{
//   bottom = height() + y; top = y;
//}
//TEMPLATE void i64_rectangle::move_to_x(long long x) noexcept
//{
//   right = width() + x; left = x;
//}
//TEMPLATE void i64_rectangle::move_to(long long x, long long y) noexcept
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
//   long long nTemp;
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
//TEMPLATE void i64_rectangle::inflate(long long l, long long t, long long r, long long b) noexcept
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
//TEMPLATE void i64_rectangle::deflate(long long l, long long t, long long r, long long b) noexcept
//{
//   left += l;      top += t;
//   right -= r;      bottom -= b;
//}
//
//i64_rectangle i64_rectangle::MulDiv(long long nMultiplier, long long nDivisor) const noexcept
//{
//   return i64_rectangle(
//      ::MulDiv(left, nMultiplier, nDivisor),
//      ::MulDiv(top, nMultiplier, nDivisor),
//      ::MulDiv(right, nMultiplier, nDivisor),
//      ::MulDiv(bottom, nMultiplier, nDivisor));
//}
//
//
//long long i64_rectangle::area() const
//{
//
//   return size().area();
//
//}
//
//TEMPLATE double double_rectangle::width() const noexcept { return right - left; }
//TEMPLATE double double_rectangle::height() const noexcept { return bottom - top; }
//TEMPLATE class double_size rectdSIZE_TYPE() const noexcept { return ::double_size(width(), height()); }
//
//
//TEMPLATE void double_rectangle::set_size(double cx, double cy) noexcept { right = left + cx;  bottom = top + cy; }
//TEMPLATE void double_rectangle::set_size(const double_size & size) noexcept { set_size(size.cx, size.cy); }
//TEMPLATE double_point& double_rectangle::top_left() noexcept { return *((double_point*)this); }
//TEMPLATE double_point& double_rectangle::bottom_right() noexcept { return *((double_point*)this + 1); }
//TEMPLATE const double_point& double_rectangle::top_left() const noexcept { return *((const double_point*)this); }
//TEMPLATE const double_point& double_rectangle::bottom_right() const noexcept {
//   return *((const double_point*)this + 1);
//  TEMPLATE void double_rectangle::swap_left_right() noexcept { ::swap_left_right(this); }
//
//  TEMPLATE double_rectangle::operator ::double_rectangle* () noexcept
//   {
//      return this;
//   }
//  TEMPLATE double_rectangle::operator const double_rectangle& () const noexcept
//   {
//      return (const double_rectangle&)this;
//   }
//  TEMPLATE bool double_rectangle::contains(::double_point i32_point) const noexcept
//   {
//      return ::contains((const double_rectangle&)this, i32_point) != false;
//   }
//  TEMPLATE void double_rectangle::set(double x1, double y1, double x2, double y2) noexcept
//   {
//      ::set_rect(this, x1, y1, x2, y2);
//   }
//  TEMPLATE void double_rectangle::set(::double_point topLeft, ::double_point bottomRight) noexcept
//   {
//      ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
//   }
//
//  TEMPLATE void double_rectangle::null() noexcept
//   {
//
//      ::null(this);
//
//   }
//
//
//  TEMPLATE bool double_rectangle::is_empty() const noexcept
//   {
//
//      return left == right && top == bottom;
//
//   }
//
//
//  TEMPLATE void rectdcopy(const double_rectangle & pSrcRect) noexcept
//
//   {
//      ::copy(this, pSrcRect);
//   }
//
//  TEMPLATE bool double_rectangle::is_equal(const double_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      return ::is_equal((const double_rectangle&)this, RECT_TEMPLATE) != false;
//   }
//
//  TEMPLATE void double_rectangle::inflate(double x, double y) noexcept
//   {
//      ::inflate(this, x, y);
//   }
//  TEMPLATE void double_rectangle::inflate(::double_size i32_size) noexcept
//   {
//      ::inflate(this, size.cx, size.cy);
//   }
//  TEMPLATE void double_rectangle::deflate(double x, double y) noexcept
//   {
//      ::inflate(this, -x, -y);
//   }
//  TEMPLATE void double_rectangle::deflate(::double_size i32_size) noexcept
//   {
//      ::inflate(this, -size.cx, -size.cy);
//   }
//  TEMPLATE void double_rectangle::offset(double x, double y) noexcept
//   {
//      ::offset(this, x, y);
//   }
//  TEMPLATE void double_rectangle::offset(::double_point i32_point) noexcept
//   {
//      ::offset(this, point.x, point.y);
//   }
//  TEMPLATE void double_rectangle::offset(::double_size i32_size) noexcept
//   {
//      ::offset(this, size.cx, size.cy);
//   }
//  TEMPLATE void double_rectangle::move_to_y(double y) noexcept
//   {
//      bottom = height() + y; top = y;
//   }
//  TEMPLATE void double_rectangle::move_to_x(double x) noexcept
//   {
//      right = width() + x; left = x;
//   }
//  TEMPLATE void double_rectangle::move_to(double x, double y) noexcept
//   {
//      move_to_x(x); move_to_y(y);
//   }
//  TEMPLATE void double_rectangle::move_to(::double_point i32_point) noexcept
//   {
//      move_to_x(point.x); move_to_y(point.y);
//   }
//   //TEMPLATE bool double_rectangle::intersect_x(const double_rectangle & rect1, const double_rectangle & rect2) noexcept
//
//   //{
//   //   return ::x_intersect_rect(this, rect1, rect2) != false;
//
//   //}
//   //TEMPLATE bool double_rectangle::intersect_y(const double_rectangle & rect1, const double_rectangle & rect2) noexcept
//
//   //{
//   //   return ::y_intersect_rect(this, rect1, rect2) != false;
//
//   //}
//  TEMPLATE bool double_rectangle::intersect(const double_rectangle & rect1, const double_rectangle & rect2) noexcept
//
//   {
//      return ::intersect(this, rect1, rect2) != false;
//
//   }
//   //double_rectangle double_rectangle::intersect(const double_rectangle & RECT_TEMPLATE) const noexcept
//
//   //{
//   //   ::double_rectangle RECT_TEMPLATE;
//   //   ::intersect(&RECT_TEMPLATE, this, RECT_TEMPLATE);
//
//   //   return RECT_TEMPLATE;
//   //}
//  TEMPLATE bool double_rectangle::unite(const double_rectangle & rect1, const double_rectangle & rect2) noexcept
//
//   {
//      return ::unite(this, rect1, rect2) != false;
//   }
//
//  TEMPLATE void double_rectangle::operator=(const ::double_rectangle & rectectSrc) noexcept
//   {
//      ::copy(this, (const double_rectangle&)& rectangleSource);
//   }
//  TEMPLATE bool double_rectangle::operator==(const ::double_rectangle & rectectd) const noexcept
//   {
//      return ::is_equal((const double_rectangle&)this, (const double_rectangle&)& double_rectangle) != false;
//   }
//  TEMPLATE bool double_rectangle::operator!=(const ::double_rectangle & rectectd) const noexcept
//   {
//      return !::is_equal((const double_rectangle&)this, (const double_rectangle&)& double_rectangle) != false;
//   }
//  TEMPLATE void double_rectangle::operator +=(::double_point i32_point) noexcept
//   {
//      ::offset(this, point.x, point.y);
//   }
//  TEMPLATE void double_rectangle::operator +=(::double_size i32_size) noexcept
//   {
//      ::offset(this, size.cx, size.cy);
//   }
//  TEMPLATE void double_rectangle::operator +=(const double_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      inflate(RECT_TEMPLATE);
//   }
//
//  TEMPLATE void double_rectangle::operator-=(::double_point i32_point) noexcept
//   {
//      ::offset(this, -point.x, -point.y);
//   }
//  TEMPLATE void double_rectangle::operator-=(::double_size i32_size) noexcept
//   {
//      ::offset(this, -size.cx, -size.cy);
//   }
//  TEMPLATE void double_rectangle::operator-=(const double_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      deflate(RECT_TEMPLATE);
//   }
//
//  TEMPLATE void double_rectangle::operator&=(const ::double_rectangle & rectectd) noexcept
//   {
//      ::intersect(this, this, (const double_rectangle&)& double_rectangle);
//   }
//  TEMPLATE void double_rectangle::operator|=(const ::double_rectangle & rectectd) noexcept
//   {
//      ::unite(this, this, (const double_rectangle&)& double_rectangle);
//   }
//  TEMPLATE double_rectangle double_rectangle::operator +(::double_point i32_point) const noexcept
//   {
//      double_rectangle double_rectangle(*this); ::offset(&double_rectangle, point.x, point.y); return double_rectangle;
//   }
//  TEMPLATE double_rectangle double_rectangle::operator-(::double_point i32_point) const noexcept
//   {
//      double_rectangle double_rectangle(*this); ::offset(&double_rectangle, -point.x, -point.y); return double_rectangle;
//   }
//  TEMPLATE double_rectangle double_rectangle::operator +(::double_size i32_size) const noexcept
//   {
//      double_rectangle double_rectangle(*this); ::offset(&double_rectangle, size.cx, size.cy); return double_rectangle;
//   }
//  TEMPLATE double_rectangle double_rectangle::operator-(::double_size i32_size) const noexcept
//   {
//      double_rectangle double_rectangle(*this); ::offset(&double_rectangle, -size.cx, -size.cy); return double_rectangle;
//   }
//  TEMPLATE double_rectangle double_rectangle::operator +(const double_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      ::double_rectangle double_rectangle((const double_rectangle&)this); double_rectangle.inflate(RECT_TEMPLATE); return double_rectangle;
//   }
//
//  TEMPLATE double_rectangle double_rectangle::operator-(const double_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      ::double_rectangle double_rectangle((const double_rectangle&)this); double_rectangle.deflate(RECT_TEMPLATE); return double_rectangle;
//   }
//
//  TEMPLATE double_rectangle double_rectangle::operator&(const ::double_rectangle & rectect2) const noexcept
//   {
//      ::double_rectangle double_rectangle; ::intersect(&double_rectangle, (const double_rectangle&)this, (const double_rectangle&)& rect2);
//      return double_rectangle;
//   }
//  TEMPLATE double_rectangle double_rectangle::operator|(const ::double_rectangle & rectect2) const noexcept
//   {
//      ::double_rectangle double_rectangle; ::unite(&double_rectangle, (const double_rectangle&)this, (const double_rectangle&)& rect2);
//      return double_rectangle;
//   }
//   //TEMPLATE bool double_rectangle::subtract(const double_rectangle & pRectSrc1, const double_rectangle & lpRectSrc2) noexcept
//
//   // { return ::subtract(this, pRectSrc1, lpRectSrc2) != false; }
//
//
//  TEMPLATE void double_rectangle::normalize() noexcept
//   {
//      double nTemp;
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
//  TEMPLATE void double_rectangle::inflate(const double_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      left -= RECT_TEMPLATE.left;      top -= RECT_TEMPLATE.top;
//
//      right += RECT_TEMPLATE.right;      bottom += RECT_TEMPLATE.bottom;
//
//   }
//
//  TEMPLATE void double_rectangle::inflate(double l, double t, double r, double b) noexcept
//   {
//      left -= l;         top -= t;
//      right += r;         bottom += b;
//   }
//
//  TEMPLATE void double_rectangle::deflate(const double_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      left += RECT_TEMPLATE.left;   top += RECT_TEMPLATE.top;
//
//      right -= RECT_TEMPLATE.right;   bottom -= RECT_TEMPLATE.bottom;
//
//   }
//
//  TEMPLATE void double_rectangle::deflate(double l, double t, double r, double b) noexcept
//   {
//      left += l;      top += t;
//      right -= r;      bottom -= b;
//   }
//
//  TEMPLATE double_rectangle double_rectangle::MulDiv(double nMultiplier, double nDivisor) const noexcept
//   {
//      return double_rectangle(left * nMultiplier / nDivisor,
//         top * nMultiplier / nDivisor,
//         right * nMultiplier / nDivisor,
//         bottom * nMultiplier / nDivisor);
//   }
//
//  TEMPLATE double double_rectangle::area()
//   {
//
//      return size().area();
//
//   }
//
//
//  TEMPLATE void double_rectangle::get_bounding_box(const ::double_point * ppoint, ::collection::count count)
//
//   {
//
//      double_point_array::get_bounding_box(this, ppoint, count);
//
//
//   }
//
//  TEMPLATE void double_rectangle::get_bounding_box(const double_point_array & pointa)
//   {
//
//      pointa.get_bounding_box(this);
//
//   }
//
//  TEMPLATE void double_rectangle::CenterOf(const double_rectangle & RECT_TEMPLATE, ::double_size i32_size)
//
//   {
//      double cx = size.cx;
//      double cy = size.cy;
//
//      double Δx = ::width(RECT_TEMPLATE);
//
//      double Δy = ::height(RECT_TEMPLATE);
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
//  TEMPLATE void double_rectangle::CenterOf(const double_rectangle & RECT_TEMPLATE)
//
//   {
//
//      CenterOf(RECT_TEMPLATE, size());
//
//
//   }
//
//  TEMPLATE double double_rectangle::minimum_signed_absolute_dimension(bool bNegativePreference) const noexcept
//   {
//
//      double w = width();
//
//      double h = height();
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
//   double double_rectangle::maximum_signed_absolute_dimension(bool bPositivePreference) const noexcept
//   {
//
//      double w = width();
//
//      double h = height();
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
//   double double_rectangle::minimum_absolute_dimension() const noexcept { return minimum(fabs(width()), fabs(height())); }
//   double double_rectangle::maximum_absolute_dimension() const noexcept { return minimum(fabs(width()), fabs(height())); }
//  TEMPLATE bool double_rectangle::contains_x(double x) const noexcept
//   {
//      return left <= x && x <= right;
//   }
//  TEMPLATE bool double_rectangle::contains_y(double y) const noexcept
//   {
//      return top <= y && y <= bottom;
//   }
//
//
//  TEMPLATE double_rectangle& double_rectangle::intersect(const double_rectangle & RECT_TEMPLATE) noexcept
//
//   {
//      ::intersect(this, this, RECT_TEMPLATE);
//
//      return *this;
//   }
//
//
//  TEMPLATE double_rectangle double_rectangle::intersect(const double_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//      ::double_rectangle RECT_TEMPLATE;
//      ::intersect(&RECT_TEMPLATE, this, RECT_TEMPLATE);
//
//      return RECT_TEMPLATE;
//   }
//
//  TEMPLATE void double_rectangle::set(double d) noexcept
//   {
//
//      set(d, d, d, d);
//
//   }
//
//
//  TEMPLATE bool double_rectangle::is_null() const noexcept
//   {
//
//      return left == 0.0 && right == 0.0 && top == 0.0 && bottom == 0.0;
//
//   }
//  TEMPLATE void double_rectangle::offset_x(double x) noexcept
//   {
//      left += x;
//      right += x;
//   }
//
//
//  TEMPLATE void double_rectangle::offset_y(double y) noexcept
//   {
//      top += y;
//      bottom += y;
//   }
//
//
//  TEMPLATE double_point double_rectangle::center() const noexcept
//   {
//
//      return double_point((left + right) / 2.0, (top + bottom) / 2.0);
//
//   }
//
//
//  TEMPLATE double_point double_rectangle::top_right() const
//   {
//
//      return double_point(right, top);
//
//   }
//
//  TEMPLATE double_point double_rectangle::bottom_left() const
//   {
//
//      return double_point(left, bottom);
//
//   }
//
//
//  TEMPLATETEMPLATE void double_rectangle::align_rate(double x, double y, const double_rectangle & RECT_TEMPLATE)
//   {
//
//      align_x(x, RECT_TEMPLATE);
//
//      align_y(y, RECT_TEMPLATE);
//
//   }
//
//  TEMPLATETEMPLATE void double_rectangle::align_x(double dRate, const double_rectangle & RECT_TEMPLATE)
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
//  TEMPLATETEMPLATE void double_rectangle::align_y(double dRate, const double_rectangle & RECT_TEMPLATE)
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
//  TEMPLATETEMPLATE bool double_rectangle::intersects(const double_rectangle & RECT_TEMPLATE) const noexcept
//
//   {
//
//      return intersects_x(RECT_TEMPLATE) && intersects_y(RECT_TEMPLATE);
//
//
//   }
//
//
//  TEMPLATETEMPLATE bool double_rectangle::intersects_x(const double_rectangle & RECT_TEMPLATE) const noexcept
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
//  TEMPLATETEMPLATE bool double_rectangle::intersects_y(const double_rectangle & RECT_TEMPLATE) const noexcept
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




