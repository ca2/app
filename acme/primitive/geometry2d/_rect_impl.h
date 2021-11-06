#pragma once



























































//
//
//
//
//
//
//
//i64 rectangle_i64::width() const noexcept
//{
//   return right - left;
//}
//i64 rectangle_i64::height() const noexcept
//{
//   return bottom - top;
//}
//size_i64 rect64SIZE_TYPE() const noexcept
//{
//   return size_i64(right - left, bottom - top);
//}
//point_i64& rectangle_i64::top_left() noexcept
//{
//   return *((point_i64*)this);
//}
//point_i64& rectangle_i64::bottom_right() noexcept
//{
//   return *((point_i64*)this + 1);
//}
//const point_i64& rectangle_i64::top_left() const noexcept
//{
//   return *((point_i64*)this);
//}
//const point_i64& rectangle_i64::bottom_right() const noexcept
//{
//   return *((point_i64*)this + 1);
//}
//TEMPLATE void rectangle_i64::swap_left_right() noexcept
//{
//   swap_left_right((RECTANGLE_I64*)(this));
//}
//void WINAPI rectangle_i64::swap_left_right(RECTANGLE_I64 * RECT_TEMPLATE) noexcept
//
//{
//   i64 temp = RECT_TEMPLATE.left; RECT_TEMPLATE.left = RECT_TEMPLATE.right; RECT_TEMPLATE.right = temp;
//}
//
//rectangle_i64::operator RECTANGLE_I64* () noexcept
//{
//   return this;
//}
//rectangle_i64::operator const RECTANGLE_I64* () const noexcept
//{
//   return this;
//}
//rectangle_i64::operator RECT_TEMPLATE() const
//{
//   return ::rect_TEMPLATE((const RECTANGLE_I64&)* this);
//}
//TEMPLATE bool rectangle_i64::contains(POINT_I64 point_i32) const noexcept
//{
//   return ::contains(this, point);
//}
//TEMPLATE void rectangle_i64::set(i64 x1, i64 y1, i64 x2, i64 y2) noexcept
//{
//   ::set_rect(this, x1, y1, x2, y2);
//}
//TEMPLATE void rectangle_i64::set(POINT_I64 topLeft, POINT_I64 bottomRight) noexcept
//{
//   ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
//}
//TEMPLATE void rectangle_i64::null() noexcept
//{
//   ::null(this);
//}
//TEMPLATE void rect64__copy(const RECTANGLE_I64 * pSrcRect) noexcept
//
//{
//   ::copy(this, pSrcRect);
//}
//
//TEMPLATE bool rectangle_i64::is_equal(const RECTANGLE_I64 * RECT_TEMPLATE) const noexcept
//
//{
//   return ::is_equal(this, RECT_TEMPLATE);
//}
//
//TEMPLATE void rectangle_i64::inflate(i64 x, i64 y) noexcept
//{
//   ::inflate(this, x, y);
//}
//TEMPLATE void rectangle_i64::inflate(SIZE_I64 size_i64) noexcept
//{
//   ::inflate(this, size_i64.cx, size_i64.cy);
//}
//TEMPLATE void rectangle_i64::deflate(i64 x, i64 y) noexcept
//{
//   ::inflate(this, -x, -y);
//}
//TEMPLATE void rectangle_i64::deflate(SIZE_I64 size_i64) noexcept
//{
//   ::inflate(this, -size_i64.cx, -size_i64.cy);
//}
//TEMPLATE void rectangle_i64::offset(i64 x, i64 y) noexcept
//{
//   ::offset(this, x, y);
//}
//TEMPLATE void rectangle_i64::offset(POINT_I64 point_i64) noexcept
//{
//   ::offset(this, point_i64.x, point_i64.y);
//}
//TEMPLATE void rectangle_i64::set_size(SIZE_I64 s) noexcept
//{
//   this->set_size(s.cx, s.cy);
//}
//TEMPLATE void rectangle_i64::rsize(SIZE_I64 s) noexcept
//{
//   this->rsize(s.cx, s.cy);
//}
//TEMPLATE void rectangle_i64::set_size(i64 cx, i64 cy) noexcept
//{
//   ::resize(this, cx, cy);
//}
//TEMPLATE void rectangle_i64::rsize(i64 cx, i64 cy) noexcept
//{
//   ::reverse_size(this, cx, cy);
//}
//TEMPLATE void rectangle_i64::offset(SIZE_I64 size_i64) noexcept
//{
//   ::offset(this, size_i64.cx, size_i64.cy);
//}
//TEMPLATE void rectangle_i64::move_to_y(i64 y) noexcept
//{
//   bottom = height() + y; top = y;
//}
//TEMPLATE void rectangle_i64::move_to_x(i64 x) noexcept
//{
//   right = width() + x; left = x;
//}
//TEMPLATE void rectangle_i64::move_to(i64 x, i64 y) noexcept
//{
//   move_to_x(x); move_to_y(y);
//}
//TEMPLATE void rectangle_i64::move_to(POINT_I64 point_i32) noexcept
//{
//   move_to_x(point.x); move_to_y(point.y);
//}
//TEMPLATE bool rectangle_i64::intersect(const RECTANGLE_I64 * rect1, const RECTANGLE_I64 * rect2) noexcept
//
//{
//   return ::intersect(this, rect1, rect2);
//}
//
//TEMPLATE bool rectangle_i64::unite(const RECTANGLE_I64 * rect1, const RECTANGLE_I64 * rect2) noexcept
//
//{
//   return ::unite(this, rect1, rect2);
//}
//
//TEMPLATE void rectangle_i64::operator=(const RECTANGLE_I64 & rectangleSource) noexcept
//{
//   ::copy(this, &rectangleSource);
//}
//TEMPLATE bool rectangle_i64::operator==(const RECTANGLE_I64 & rectangle_i64) const noexcept
//{
//   return ::is_equal(this, &rectangle_i64);
//}
//TEMPLATE bool rectangle_i64::operator!=(const RECTANGLE_I64 & rectangle_i64) const noexcept
//{
//   return !::is_equal(this, &rectangle_i64);
//}
//TEMPLATE void rectangle_i64::operator+=(POINT_I64 point_i64) noexcept
//{
//   ::offset(this, point_i64.x, point_i64.y);
//}
//TEMPLATE void rectangle_i64::operator+=(SIZE_I64 size_i64) noexcept
//{
//   ::offset(this, size_i64.cx, size_i64.cy);
//}
//TEMPLATE void rectangle_i64::operator+=(const RECTANGLE_I64 * RECT_TEMPLATE) noexcept
//
//{
//   inflate(RECT_TEMPLATE);
//}
//
//TEMPLATE void rectangle_i64::operator-=(POINT_I64 point_i64) noexcept
//{
//   ::offset(this, -point_i64.x, -point_i64.y);
//}
//TEMPLATE void rectangle_i64::operator-=(SIZE_I64 size_i64) noexcept
//{
//   ::offset(this, -size_i64.cx, -size_i64.cy);
//}
//TEMPLATE void rectangle_i64::operator-=(const RECTANGLE_I64 * RECT_TEMPLATE) noexcept
//
//{
//   deflate(RECT_TEMPLATE);
//}
//
//TEMPLATE void rectangle_i64::operator&=(const RECTANGLE_I64 & rectangle_i64) noexcept
//{
//   ::intersect(this, this, &rectangle_i64);
//}
//TEMPLATE void rectangle_i64::operator|=(const RECTANGLE_I64 & rectangle_i64) noexcept
//{
//   ::unite(this, this, &rectangle_i64);
//}
//rectangle_i64 rectangle_i64::operator+(POINT_I64 point_i32) const noexcept
//{
//   rectangle_i64 rectangle_i64(*this); ::offset(&rectangle_i64, point.x, point.y); return rectangle_i64;
//}
//rectangle_i64 rectangle_i64::operator-(POINT_I64 point_i32) const noexcept
//{
//   rectangle_i64 rectangle_i64(*this); ::offset(&rectangle_i64, -point.x, -point.y); return rectangle_i64;
//}
//rectangle_i64 rectangle_i64::operator+(SIZE_I64 size_i64) const noexcept
//{
//   rectangle_i64 rectangle_i64(*this); ::offset(&rectangle_i64, size_i64.cx, size_i64.cy); return rectangle_i64;
//}
//rectangle_i64 rectangle_i64::operator-(SIZE_I64 size_i64) const noexcept
//{
//   rectangle_i64 rectangle_i64(*this); ::offset(&rectangle_i64, -size_i64.cx, -size_i64.cy); return rectangle_i64;
//}
//rectangle_i64 rectangle_i64::operator+(const RECTANGLE_I64 * RECT_TEMPLATE) const noexcept
//
//{
//   rectangle_i64 rectangle_i64(this); rectangle_i64.inflate(RECT_TEMPLATE); return rectangle_i64;
//}
//
//rectangle_i64 rectangle_i64::operator-(const RECTANGLE_I64 * RECT_TEMPLATE) const noexcept
//
//{
//   rectangle_i64 rectangle_i64(this); rectangle_i64.deflate(RECT_TEMPLATE); return rectangle_i64;
//}
//
//rectangle_i64 rectangle_i64::operator&(const RECTANGLE_I64 & rect2) const noexcept
//{
//   rectangle_i64 rectangle_i64; ::intersect(&rectangle_i64, this, &rect2);
//   return rectangle_i64;
//}
//rectangle_i64 rectangle_i64::operator|(const RECTANGLE_I64 & rect2) const noexcept
//{
//   rectangle_i64 rectangle_i64; ::unite(&rectangle_i64, this, &rect2);
//   return rectangle_i64;
//}
////TEMPLATE bool rectangle_i64::subtract(const RECTANGLE_I64 * pRectSrc1, const RECTANGLE_I64 * lpRectSrc2) noexcept
//
////   { return ::subtract(this, pRectSrc1, lpRectSrc2); }
//
//
//TEMPLATE void rectangle_i64::normalize() noexcept
//{
//   i64 nTemp;
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
//TEMPLATE void rectangle_i64::inflate(const RECTANGLE_I64 * RECT_TEMPLATE) noexcept
//
//{
//   left -= RECT_TEMPLATE.left;      top -= RECT_TEMPLATE.top;
//
//   right += RECT_TEMPLATE.right;      bottom += RECT_TEMPLATE.bottom;
//
//}
//
//TEMPLATE void rectangle_i64::inflate(i64 l, i64 t, i64 r, i64 b) noexcept
//{
//   left -= l;         top -= t;
//   right += r;         bottom += b;
//}
//
//TEMPLATE void rectangle_i64::deflate(const RECTANGLE_I64 * RECT_TEMPLATE) noexcept
//
//{
//   left += RECT_TEMPLATE.left;   top += RECT_TEMPLATE.top;
//
//   right -= RECT_TEMPLATE.right;   bottom -= RECT_TEMPLATE.bottom;
//
//}
//
//TEMPLATE void rectangle_i64::deflate(i64 l, i64 t, i64 r, i64 b) noexcept
//{
//   left += l;      top += t;
//   right -= r;      bottom -= b;
//}
//
//rectangle_i64 rectangle_i64::MulDiv(i64 nMultiplier, i64 nDivisor) const noexcept
//{
//   return rectangle_i64(
//      ::MulDiv(left, nMultiplier, nDivisor),
//      ::MulDiv(top, nMultiplier, nDivisor),
//      ::MulDiv(right, nMultiplier, nDivisor),
//      ::MulDiv(bottom, nMultiplier, nDivisor));
//}
//
//
//i64 rectangle_i64::area() const
//{
//
//   return size().area();
//
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//TEMPLATE double rectangle_f64::width() const noexcept { return right - left; }
//TEMPLATE double rectangle_f64::height() const noexcept { return bottom - top; }
//TEMPLATE class size_f64 rectdSIZE_TYPE() const noexcept { return ::size_f64(width(), height()); }
//
//
//TEMPLATE void rectangle_f64::set_size(double cx, double cy) noexcept { right = left + cx;  bottom = top + cy; }
//TEMPLATE void rectangle_f64::set_size(const size_f64 & size) noexcept { set_size(size.cx, size.cy); }
//TEMPLATE point_f64& rectangle_f64::top_left() noexcept { return *((point_f64*)this); }
//TEMPLATE point_f64& rectangle_f64::bottom_right() noexcept { return *((point_f64*)this + 1); }
//TEMPLATE const point_f64& rectangle_f64::top_left() const noexcept { return *((const point_f64*)this); }
//TEMPLATE const point_f64& rectangle_f64::bottom_right() const noexcept {
//   return *((const point_f64*)this + 1);
//  TEMPLATE void rectangle_f64::swap_left_right() noexcept { ::swap_left_right(this); }
//
//  TEMPLATE rectangle_f64::operator RECTANGLE_F64* () noexcept
//   {
//      return this;
//   }
//  TEMPLATE rectangle_f64::operator const rectangle_f64& () const noexcept
//   {
//      return (const rectangle_f64&)this;
//   }
//  TEMPLATE bool rectangle_f64::contains(POINT_F64 point_i32) const noexcept
//   {
//      return ::contains((const rectangle_f64&)this, point_i32) != false;
//   }
//  TEMPLATE void rectangle_f64::set(double x1, double y1, double x2, double y2) noexcept
//   {
//      ::set_rect(this, x1, y1, x2, y2);
//   }
//  TEMPLATE void rectangle_f64::set(POINT_F64 topLeft, POINT_F64 bottomRight) noexcept
//   {
//      ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
//   }
//
//  TEMPLATE void rectangle_f64::null() noexcept
//   {
//
//      ::null(this);
//
//   }
//
//
//  TEMPLATE bool rectangle_f64::is_empty() const noexcept
//   {
//
//      return left == right && top == bottom;
//
//   }
//
//
//  TEMPLATE void rectd__copy(const rectangle_f64 & pSrcRect) noexcept
//
//   {
//      ::copy(this, pSrcRect);
//   }
//
//  TEMPLATE bool rectangle_f64::is_equal(const rectangle_f64 & RECT_TEMPLATE) const noexcept
//
//   {
//      return ::is_equal((const rectangle_f64&)this, RECT_TEMPLATE) != false;
//   }
//
//  TEMPLATE void rectangle_f64::inflate(double x, double y) noexcept
//   {
//      ::inflate(this, x, y);
//   }
//  TEMPLATE void rectangle_f64::inflate(SIZE_F64 size_i32) noexcept
//   {
//      ::inflate(this, size.cx, size.cy);
//   }
//  TEMPLATE void rectangle_f64::deflate(double x, double y) noexcept
//   {
//      ::inflate(this, -x, -y);
//   }
//  TEMPLATE void rectangle_f64::deflate(SIZE_F64 size_i32) noexcept
//   {
//      ::inflate(this, -size.cx, -size.cy);
//   }
//  TEMPLATE void rectangle_f64::offset(double x, double y) noexcept
//   {
//      ::offset(this, x, y);
//   }
//  TEMPLATE void rectangle_f64::offset(POINT_F64 point_i32) noexcept
//   {
//      ::offset(this, point.x, point.y);
//   }
//  TEMPLATE void rectangle_f64::offset(SIZE_F64 size_i32) noexcept
//   {
//      ::offset(this, size.cx, size.cy);
//   }
//  TEMPLATE void rectangle_f64::move_to_y(double y) noexcept
//   {
//      bottom = height() + y; top = y;
//   }
//  TEMPLATE void rectangle_f64::move_to_x(double x) noexcept
//   {
//      right = width() + x; left = x;
//   }
//  TEMPLATE void rectangle_f64::move_to(double x, double y) noexcept
//   {
//      move_to_x(x); move_to_y(y);
//   }
//  TEMPLATE void rectangle_f64::move_to(POINT_F64 point_i32) noexcept
//   {
//      move_to_x(point.x); move_to_y(point.y);
//   }
//   //TEMPLATE bool rectangle_f64::intersect_x(const rectangle_f64 & rect1, const rectangle_f64 & rect2) noexcept
//
//   //{
//   //   return ::x_intersect_rect(this, rect1, rect2) != false;
//
//   //}
//   //TEMPLATE bool rectangle_f64::intersect_y(const rectangle_f64 & rect1, const rectangle_f64 & rect2) noexcept
//
//   //{
//   //   return ::y_intersect_rect(this, rect1, rect2) != false;
//
//   //}
//  TEMPLATE bool rectangle_f64::intersect(const rectangle_f64 & rect1, const rectangle_f64 & rect2) noexcept
//
//   {
//      return ::intersect(this, rect1, rect2) != false;
//
//   }
//   //rectangle_f64 rectangle_f64::intersect(const rectangle_f64 & RECT_TEMPLATE) const noexcept
//
//   //{
//   //   ::rectangle_f64 RECT_TEMPLATE;
//   //   ::intersect(&RECT_TEMPLATE, this, RECT_TEMPLATE);
//
//   //   return RECT_TEMPLATE;
//   //}
//  TEMPLATE bool rectangle_f64::unite(const rectangle_f64 & rect1, const rectangle_f64 & rect2) noexcept
//
//   {
//      return ::unite(this, rect1, rect2) != false;
//   }
//
//  TEMPLATE void rectangle_f64::operator=(const ::rectangle_f64 & rectectSrc) noexcept
//   {
//      ::copy(this, (const rectangle_f64&)& rectangleSource);
//   }
//  TEMPLATE bool rectangle_f64::operator==(const ::rectangle_f64 & rectectd) const noexcept
//   {
//      return ::is_equal((const rectangle_f64&)this, (const rectangle_f64&)& rectangle_f64) != false;
//   }
//  TEMPLATE bool rectangle_f64::operator!=(const ::rectangle_f64 & rectectd) const noexcept
//   {
//      return !::is_equal((const rectangle_f64&)this, (const rectangle_f64&)& rectangle_f64) != false;
//   }
//  TEMPLATE void rectangle_f64::operator+=(POINT_F64 point_i32) noexcept
//   {
//      ::offset(this, point.x, point.y);
//   }
//  TEMPLATE void rectangle_f64::operator+=(SIZE_F64 size_i32) noexcept
//   {
//      ::offset(this, size.cx, size.cy);
//   }
//  TEMPLATE void rectangle_f64::operator+=(const rectangle_f64 & RECT_TEMPLATE) noexcept
//
//   {
//      inflate(RECT_TEMPLATE);
//   }
//
//  TEMPLATE void rectangle_f64::operator-=(POINT_F64 point_i32) noexcept
//   {
//      ::offset(this, -point.x, -point.y);
//   }
//  TEMPLATE void rectangle_f64::operator-=(SIZE_F64 size_i32) noexcept
//   {
//      ::offset(this, -size.cx, -size.cy);
//   }
//  TEMPLATE void rectangle_f64::operator-=(const rectangle_f64 & RECT_TEMPLATE) noexcept
//
//   {
//      deflate(RECT_TEMPLATE);
//   }
//
//  TEMPLATE void rectangle_f64::operator&=(const ::rectangle_f64 & rectectd) noexcept
//   {
//      ::intersect(this, this, (const rectangle_f64&)& rectangle_f64);
//   }
//  TEMPLATE void rectangle_f64::operator|=(const ::rectangle_f64 & rectectd) noexcept
//   {
//      ::unite(this, this, (const rectangle_f64&)& rectangle_f64);
//   }
//  TEMPLATE rectangle_f64 rectangle_f64::operator+(POINT_F64 point_i32) const noexcept
//   {
//      rectangle_f64 rectangle_f64(*this); ::offset(&rectangle_f64, point.x, point.y); return rectangle_f64;
//   }
//  TEMPLATE rectangle_f64 rectangle_f64::operator-(POINT_F64 point_i32) const noexcept
//   {
//      rectangle_f64 rectangle_f64(*this); ::offset(&rectangle_f64, -point.x, -point.y); return rectangle_f64;
//   }
//  TEMPLATE rectangle_f64 rectangle_f64::operator+(SIZE_F64 size_i32) const noexcept
//   {
//      rectangle_f64 rectangle_f64(*this); ::offset(&rectangle_f64, size.cx, size.cy); return rectangle_f64;
//   }
//  TEMPLATE rectangle_f64 rectangle_f64::operator-(SIZE_F64 size_i32) const noexcept
//   {
//      rectangle_f64 rectangle_f64(*this); ::offset(&rectangle_f64, -size.cx, -size.cy); return rectangle_f64;
//   }
//  TEMPLATE rectangle_f64 rectangle_f64::operator+(const rectangle_f64 & RECT_TEMPLATE) const noexcept
//
//   {
//      ::rectangle_f64 rectangle_f64((const rectangle_f64&)this); rectangle_f64.inflate(RECT_TEMPLATE); return rectangle_f64;
//   }
//
//  TEMPLATE rectangle_f64 rectangle_f64::operator-(const rectangle_f64 & RECT_TEMPLATE) const noexcept
//
//   {
//      ::rectangle_f64 rectangle_f64((const rectangle_f64&)this); rectangle_f64.deflate(RECT_TEMPLATE); return rectangle_f64;
//   }
//
//  TEMPLATE rectangle_f64 rectangle_f64::operator&(const ::rectangle_f64 & rectect2) const noexcept
//   {
//      ::rectangle_f64 rectangle_f64; ::intersect(&rectangle_f64, (const rectangle_f64&)this, (const rectangle_f64&)& rect2);
//      return rectangle_f64;
//   }
//  TEMPLATE rectangle_f64 rectangle_f64::operator|(const ::rectangle_f64 & rectect2) const noexcept
//   {
//      ::rectangle_f64 rectangle_f64; ::unite(&rectangle_f64, (const rectangle_f64&)this, (const rectangle_f64&)& rect2);
//      return rectangle_f64;
//   }
//   //TEMPLATE bool rectangle_f64::subtract(const rectangle_f64 & pRectSrc1, const rectangle_f64 & lpRectSrc2) noexcept
//
//   // { return ::subtract(this, pRectSrc1, lpRectSrc2) != false; }
//
//
//  TEMPLATE void rectangle_f64::normalize() noexcept
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
//  TEMPLATE void rectangle_f64::inflate(const rectangle_f64 & RECT_TEMPLATE) noexcept
//
//   {
//      left -= RECT_TEMPLATE.left;      top -= RECT_TEMPLATE.top;
//
//      right += RECT_TEMPLATE.right;      bottom += RECT_TEMPLATE.bottom;
//
//   }
//
//  TEMPLATE void rectangle_f64::inflate(double l, double t, double r, double b) noexcept
//   {
//      left -= l;         top -= t;
//      right += r;         bottom += b;
//   }
//
//  TEMPLATE void rectangle_f64::deflate(const rectangle_f64 & RECT_TEMPLATE) noexcept
//
//   {
//      left += RECT_TEMPLATE.left;   top += RECT_TEMPLATE.top;
//
//      right -= RECT_TEMPLATE.right;   bottom -= RECT_TEMPLATE.bottom;
//
//   }
//
//  TEMPLATE void rectangle_f64::deflate(double l, double t, double r, double b) noexcept
//   {
//      left += l;      top += t;
//      right -= r;      bottom -= b;
//   }
//
//  TEMPLATE rectangle_f64 rectangle_f64::MulDiv(double nMultiplier, double nDivisor) const noexcept
//   {
//      return rectangle_f64(left * nMultiplier / nDivisor,
//         top * nMultiplier / nDivisor,
//         right * nMultiplier / nDivisor,
//         bottom * nMultiplier / nDivisor);
//   }
//
//  TEMPLATE double rectangle_f64::area()
//   {
//
//      return size().area();
//
//   }
//
//
//  TEMPLATE void rectangle_f64::get_bounding_rectangle(const POINT_F64 * ppoint, ::count count)
//
//   {
//
//      point_f64_array::get_bounding_rectangle(this, ppoint, count);
//
//
//   }
//
//  TEMPLATE void rectangle_f64::get_bounding_rectangle(const point_f64_array & pointa)
//   {
//
//      pointa.get_bounding_rectangle(this);
//
//   }
//
//
//
//
//
//  TEMPLATE void rectangle_f64::CenterOf(const rectangle_f64 & RECT_TEMPLATE, SIZE_F64 size_i32)
//
//   {
//      double cx = size.cx;
//      double cy = size.cy;
//
//      double dx = ::width(RECT_TEMPLATE);
//
//      double dy = ::height(RECT_TEMPLATE);
//
//
//      left = RECT_TEMPLATE.left + (dx - cx) / 2;
//
//      top = RECT_TEMPLATE.top + (dy - cy) / 2;
//
//      right = left + cx;
//      bottom = top + cy;
//
//   }
//
//  TEMPLATE void rectangle_f64::CenterOf(const rectangle_f64 & RECT_TEMPLATE)
//
//   {
//
//      CenterOf(RECT_TEMPLATE, size());
//
//
//   }
//
//
//
//
//
//  TEMPLATE double rectangle_f64::minimum_signed_absolute_dimension(bool bNegativePreference) const noexcept
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
//   double rectangle_f64::maximum_signed_absolute_dimension(bool bPositivePreference) const noexcept
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
//   double rectangle_f64::minimum_absolute_dimension() const noexcept { return minimum(fabs(width()), fabs(height())); }
//   double rectangle_f64::maximum_absolute_dimension() const noexcept { return minimum(fabs(width()), fabs(height())); }
//
//
//
//
//  TEMPLATE bool rectangle_f64::contains_x(double x) const noexcept
//   {
//      return left <= x && x <= right;
//   }
//  TEMPLATE bool rectangle_f64::contains_y(double y) const noexcept
//   {
//      return top <= y && y <= bottom;
//   }
//
//
//  TEMPLATE rectangle_f64& rectangle_f64::intersect(const rectangle_f64 & RECT_TEMPLATE) noexcept
//
//   {
//      ::intersect(this, this, RECT_TEMPLATE);
//
//      return *this;
//   }
//
//
//  TEMPLATE rectangle_f64 rectangle_f64::intersect(const rectangle_f64 & RECT_TEMPLATE) const noexcept
//
//   {
//      ::rectangle_f64 RECT_TEMPLATE;
//      ::intersect(&RECT_TEMPLATE, this, RECT_TEMPLATE);
//
//      return RECT_TEMPLATE;
//   }
//
//
//
//
//
//  TEMPLATE void rectangle_f64::set(double d) noexcept
//   {
//
//      set(d, d, d, d);
//
//   }
//
//
//  TEMPLATE bool rectangle_f64::is_null() const noexcept
//   {
//
//      return left == 0.0 && right == 0.0 && top == 0.0 && bottom == 0.0;
//
//   }
//
//
//
//
//  TEMPLATE void rectangle_f64::offset_x(double x) noexcept
//   {
//      left += x;
//      right += x;
//   }
//
//
//  TEMPLATE void rectangle_f64::offset_y(double y) noexcept
//   {
//      top += y;
//      bottom += y;
//   }
//
//
//  TEMPLATE point_f64 rectangle_f64::center() const noexcept
//   {
//
//      return point_f64((left + right) / 2.0, (top + bottom) / 2.0);
//
//   }
//
//
//  TEMPLATE point_f64 rectangle_f64::top_right() const
//   {
//
//      return point_f64(right, top);
//
//   }
//
//  TEMPLATE point_f64 rectangle_f64::bottom_left() const
//   {
//
//      return point_f64(left, bottom);
//
//   }
//
//
//  TEMPLATETEMPLATE void rectangle_f64::align_rate(double x, double y, const rectangle_f64 & RECT_TEMPLATE)
//   {
//
//      align_x(x, RECT_TEMPLATE);
//
//      align_y(y, RECT_TEMPLATE);
//
//   }
//
//  TEMPLATETEMPLATE void rectangle_f64::align_x(double dRate, const rectangle_f64 & RECT_TEMPLATE)
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
//  TEMPLATETEMPLATE void rectangle_f64::align_y(double dRate, const rectangle_f64 & RECT_TEMPLATE)
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
//  TEMPLATETEMPLATE bool rectangle_f64::intersects(const rectangle_f64 & RECT_TEMPLATE) const noexcept
//
//   {
//
//      return intersects_x(RECT_TEMPLATE) && intersects_y(RECT_TEMPLATE);
//
//
//   }
//
//
//  TEMPLATETEMPLATE bool rectangle_f64::intersects_x(const rectangle_f64 & RECT_TEMPLATE) const noexcept
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
//  TEMPLATETEMPLATE bool rectangle_f64::intersects_y(const rectangle_f64 & RECT_TEMPLATE) const noexcept
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
void rectangle_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > ::get_bounding_rectangle(const POINT_BASE_TYPE * ppoint, ::count count)
{

   ::get_bounding_rectangle(this, ppoint, count);

}




