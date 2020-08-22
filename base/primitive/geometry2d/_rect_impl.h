#pragma once



























































//
//
//
//
//
//
//
//i64 rect64::width() const noexcept
//{
//   return right - left;
//}
//i64 rect64::height() const noexcept
//{
//   return bottom - top;
//}
//size64 rect64SIZE_TYPE() const noexcept
//{
//   return size64(right - left, bottom - top);
//}
//point64& rect64::top_left() noexcept
//{
//   return *((point64*)this);
//}
//point64& rect64::bottom_right() noexcept
//{
//   return *((point64*)this + 1);
//}
//const point64& rect64::top_left() const noexcept
//{
//   return *((point64*)this);
//}
//const point64& rect64::bottom_right() const noexcept
//{
//   return *((point64*)this + 1);
//}
//TEMPLATE void rect64::swap_left_right() noexcept
//{
//   swap_left_right((RECT64*)(this));
//}
//void WINAPI rect64::swap_left_right(RECT64 * RECT_TEMPLATE) noexcept
//
//{
//   i64 temp = RECT_TEMPLATE.left; RECT_TEMPLATE.left = RECT_TEMPLATE.right; RECT_TEMPLATE.right = temp;
//}
//
//rect64::operator RECT64* () noexcept
//{
//   return this;
//}
//rect64::operator const RECT64* () const noexcept
//{
//   return this;
//}
//rect64::operator RECT_TEMPLATE() const
//{
//   return ::RECT_TEMPLATE((const RECT64&)* this);
//}
//TEMPLATE bool rect64::contains(POINT64 point) const noexcept
//{
//   return ::contains(this, point);
//}
//TEMPLATE void rect64::set(i64 x1, i64 y1, i64 x2, i64 y2) noexcept
//{
//   ::set_rect(this, x1, y1, x2, y2);
//}
//TEMPLATE void rect64::set(POINT64 topLeft, POINT64 bottomRight) noexcept
//{
//   ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
//}
//TEMPLATE void rect64::null() noexcept
//{
//   ::null(this);
//}
//TEMPLATE void rect64__copy(const RECT64 * pSrcRect) noexcept
//
//{
//   ::copy(this, pSrcRect);
//}
//
//TEMPLATE bool rect64::is_equal(const RECT64 * RECT_TEMPLATE) const noexcept
//
//{
//   return ::is_equal(this, RECT_TEMPLATE);
//}
//
//TEMPLATE void rect64::inflate(i64 x, i64 y) noexcept
//{
//   ::inflate(this, x, y);
//}
//TEMPLATE void rect64::inflate(SIZE64 size64) noexcept
//{
//   ::inflate(this, size64.cx, size64.cy);
//}
//TEMPLATE void rect64::deflate(i64 x, i64 y) noexcept
//{
//   ::inflate(this, -x, -y);
//}
//TEMPLATE void rect64::deflate(SIZE64 size64) noexcept
//{
//   ::inflate(this, -size64.cx, -size64.cy);
//}
//TEMPLATE void rect64::offset(i64 x, i64 y) noexcept
//{
//   ::offset(this, x, y);
//}
//TEMPLATE void rect64::offset(POINT64 point64) noexcept
//{
//   ::offset(this, point64.x, point64.y);
//}
//TEMPLATE void rect64::set_size(SIZE64 s) noexcept
//{
//   this->set_size(s.cx, s.cy);
//}
//TEMPLATE void rect64::rsize(SIZE64 s) noexcept
//{
//   this->rsize(s.cx, s.cy);
//}
//TEMPLATE void rect64::set_size(i64 cx, i64 cy) noexcept
//{
//   ::resize(this, cx, cy);
//}
//TEMPLATE void rect64::rsize(i64 cx, i64 cy) noexcept
//{
//   ::reverse_size(this, cx, cy);
//}
//TEMPLATE void rect64::offset(SIZE64 size64) noexcept
//{
//   ::offset(this, size64.cx, size64.cy);
//}
//TEMPLATE void rect64::move_to_y(i64 y) noexcept
//{
//   bottom = height() + y; top = y;
//}
//TEMPLATE void rect64::move_to_x(i64 x) noexcept
//{
//   right = width() + x; left = x;
//}
//TEMPLATE void rect64::move_to(i64 x, i64 y) noexcept
//{
//   move_to_x(x); move_to_y(y);
//}
//TEMPLATE void rect64::move_to(POINT64 point) noexcept
//{
//   move_to_x(point.x); move_to_y(point.y);
//}
//TEMPLATE bool rect64::intersect(const RECT64 * rect1, const RECT64 * rect2) noexcept
//
//{
//   return ::intersect(this, rect1, rect2);
//}
//
//TEMPLATE bool rect64::unite(const RECT64 * rect1, const RECT64 * rect2) noexcept
//
//{
//   return ::unite(this, rect1, rect2);
//}
//
//TEMPLATE void rect64::operator=(const RECT64 & rectSrc) noexcept
//{
//   ::copy(this, &rectSrc);
//}
//TEMPLATE bool rect64::operator==(const RECT64 & rect64) const noexcept
//{
//   return ::is_equal(this, &rect64);
//}
//TEMPLATE bool rect64::operator!=(const RECT64 & rect64) const noexcept
//{
//   return !::is_equal(this, &rect64);
//}
//TEMPLATE void rect64::operator+=(POINT64 point64) noexcept
//{
//   ::offset(this, point64.x, point64.y);
//}
//TEMPLATE void rect64::operator+=(SIZE64 size64) noexcept
//{
//   ::offset(this, size64.cx, size64.cy);
//}
//TEMPLATE void rect64::operator+=(const RECT64 * RECT_TEMPLATE) noexcept
//
//{
//   inflate(RECT_TEMPLATE);
//}
//
//TEMPLATE void rect64::operator-=(POINT64 point64) noexcept
//{
//   ::offset(this, -point64.x, -point64.y);
//}
//TEMPLATE void rect64::operator-=(SIZE64 size64) noexcept
//{
//   ::offset(this, -size64.cx, -size64.cy);
//}
//TEMPLATE void rect64::operator-=(const RECT64 * RECT_TEMPLATE) noexcept
//
//{
//   deflate(RECT_TEMPLATE);
//}
//
//TEMPLATE void rect64::operator&=(const RECT64 & rect64) noexcept
//{
//   ::intersect(this, this, &rect64);
//}
//TEMPLATE void rect64::operator|=(const RECT64 & rect64) noexcept
//{
//   ::unite(this, this, &rect64);
//}
//rect64 rect64::operator+(POINT64 point) const noexcept
//{
//   rect64 rect64(*this); ::offset(&rect64, point.x, point.y); return rect64;
//}
//rect64 rect64::operator-(POINT64 point) const noexcept
//{
//   rect64 rect64(*this); ::offset(&rect64, -point.x, -point.y); return rect64;
//}
//rect64 rect64::operator+(SIZE64 size64) const noexcept
//{
//   rect64 rect64(*this); ::offset(&rect64, size64.cx, size64.cy); return rect64;
//}
//rect64 rect64::operator-(SIZE64 size64) const noexcept
//{
//   rect64 rect64(*this); ::offset(&rect64, -size64.cx, -size64.cy); return rect64;
//}
//rect64 rect64::operator+(const RECT64 * RECT_TEMPLATE) const noexcept
//
//{
//   rect64 rect64(this); rect64.inflate(RECT_TEMPLATE); return rect64;
//}
//
//rect64 rect64::operator-(const RECT64 * RECT_TEMPLATE) const noexcept
//
//{
//   rect64 rect64(this); rect64.deflate(RECT_TEMPLATE); return rect64;
//}
//
//rect64 rect64::operator&(const RECT64 & rect2) const noexcept
//{
//   rect64 rect64; ::intersect(&rect64, this, &rect2);
//   return rect64;
//}
//rect64 rect64::operator|(const RECT64 & rect2) const noexcept
//{
//   rect64 rect64; ::unite(&rect64, this, &rect2);
//   return rect64;
//}
////TEMPLATE bool rect64::subtract(const RECT64 * pRectSrc1, const RECT64 * lpRectSrc2) noexcept
//
////   { return ::subtract(this, pRectSrc1, lpRectSrc2); }
//
//
//TEMPLATE void rect64::normalize() noexcept
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
//TEMPLATE void rect64::inflate(const RECT64 * RECT_TEMPLATE) noexcept
//
//{
//   left -= RECT_TEMPLATE.left;      top -= RECT_TEMPLATE.top;
//
//   right += RECT_TEMPLATE.right;      bottom += RECT_TEMPLATE.bottom;
//
//}
//
//TEMPLATE void rect64::inflate(i64 l, i64 t, i64 r, i64 b) noexcept
//{
//   left -= l;         top -= t;
//   right += r;         bottom += b;
//}
//
//TEMPLATE void rect64::deflate(const RECT64 * RECT_TEMPLATE) noexcept
//
//{
//   left += RECT_TEMPLATE.left;   top += RECT_TEMPLATE.top;
//
//   right -= RECT_TEMPLATE.right;   bottom -= RECT_TEMPLATE.bottom;
//
//}
//
//TEMPLATE void rect64::deflate(i64 l, i64 t, i64 r, i64 b) noexcept
//{
//   left += l;      top += t;
//   right -= r;      bottom -= b;
//}
//
//rect64 rect64::MulDiv(i64 nMultiplier, i64 nDivisor) const noexcept
//{
//   return rect64(
//      ::MulDiv(left, nMultiplier, nDivisor),
//      ::MulDiv(top, nMultiplier, nDivisor),
//      ::MulDiv(right, nMultiplier, nDivisor),
//      ::MulDiv(bottom, nMultiplier, nDivisor));
//}
//
//
//i64 rect64::area() const
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
//TEMPLATE double rectd::width() const noexcept { return right - left; }
//TEMPLATE double rectd::height() const noexcept { return bottom - top; }
//TEMPLATE class sized rectdSIZE_TYPE() const noexcept { return ::sized(width(), height()); }
//
//
//TEMPLATE void rectd::set_size(double cx, double cy) noexcept { right = left + cx;  bottom = top + cy; }
//TEMPLATE void rectd::set_size(const sized & size) noexcept { set_size(size.cx, size.cy); }
//TEMPLATE pointd& rectd::top_left() noexcept { return *((pointd*)this); }
//TEMPLATE pointd& rectd::bottom_right() noexcept { return *((pointd*)this + 1); }
//TEMPLATE const pointd& rectd::top_left() const noexcept { return *((const pointd*)this); }
//TEMPLATE const pointd& rectd::bottom_right() const noexcept {
//   return *((const pointd*)this + 1);
//  TEMPLATE void rectd::swap_left_right() noexcept { ::swap_left_right(this); }
//
//  TEMPLATE rectd::operator RECTD* () noexcept
//   {
//      return this;
//   }
//  TEMPLATE rectd::operator const rectd& () const noexcept
//   {
//      return (const rectd&)this;
//   }
//  TEMPLATE bool rectd::contains(POINTD point) const noexcept
//   {
//      return ::contains((const rectd&)this, point) != FALSE;
//   }
//  TEMPLATE void rectd::set(double x1, double y1, double x2, double y2) noexcept
//   {
//      ::set_rect(this, x1, y1, x2, y2);
//   }
//  TEMPLATE void rectd::set(POINTD topLeft, POINTD bottomRight) noexcept
//   {
//      ::set_rect(this, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
//   }
//
//  TEMPLATE void rectd::null() noexcept
//   {
//
//      ::null(this);
//
//   }
//
//
//  TEMPLATE bool rectd::is_empty() const noexcept
//   {
//
//      return left == right && top == bottom;
//
//   }
//
//
//  TEMPLATE void rectd__copy(const rectd & pSrcRect) noexcept
//
//   {
//      ::copy(this, pSrcRect);
//   }
//
//  TEMPLATE bool rectd::is_equal(const rectd & RECT_TEMPLATE) const noexcept
//
//   {
//      return ::is_equal((const rectd&)this, RECT_TEMPLATE) != FALSE;
//   }
//
//  TEMPLATE void rectd::inflate(double x, double y) noexcept
//   {
//      ::inflate(this, x, y);
//   }
//  TEMPLATE void rectd::inflate(SIZED size) noexcept
//   {
//      ::inflate(this, size.cx, size.cy);
//   }
//  TEMPLATE void rectd::deflate(double x, double y) noexcept
//   {
//      ::inflate(this, -x, -y);
//   }
//  TEMPLATE void rectd::deflate(SIZED size) noexcept
//   {
//      ::inflate(this, -size.cx, -size.cy);
//   }
//  TEMPLATE void rectd::offset(double x, double y) noexcept
//   {
//      ::offset(this, x, y);
//   }
//  TEMPLATE void rectd::offset(POINTD point) noexcept
//   {
//      ::offset(this, point.x, point.y);
//   }
//  TEMPLATE void rectd::offset(SIZED size) noexcept
//   {
//      ::offset(this, size.cx, size.cy);
//   }
//  TEMPLATE void rectd::move_to_y(double y) noexcept
//   {
//      bottom = height() + y; top = y;
//   }
//  TEMPLATE void rectd::move_to_x(double x) noexcept
//   {
//      right = width() + x; left = x;
//   }
//  TEMPLATE void rectd::move_to(double x, double y) noexcept
//   {
//      move_to_x(x); move_to_y(y);
//   }
//  TEMPLATE void rectd::move_to(POINTD point) noexcept
//   {
//      move_to_x(point.x); move_to_y(point.y);
//   }
//   //TEMPLATE bool rectd::intersect_x(const rectd & rect1, const rectd & rect2) noexcept
//
//   //{
//   //   return ::x_intersect_rect(this, rect1, rect2) != FALSE;
//
//   //}
//   //TEMPLATE bool rectd::intersect_y(const rectd & rect1, const rectd & rect2) noexcept
//
//   //{
//   //   return ::y_intersect_rect(this, rect1, rect2) != FALSE;
//
//   //}
//  TEMPLATE bool rectd::intersect(const rectd & rect1, const rectd & rect2) noexcept
//
//   {
//      return ::intersect(this, rect1, rect2) != FALSE;
//
//   }
//   //rectd rectd::intersect(const rectd & RECT_TEMPLATE) const noexcept
//
//   //{
//   //   ::rectd RECT_TEMPLATE;
//   //   ::intersect(&RECT_TEMPLATE, this, RECT_TEMPLATE);
//
//   //   return RECT_TEMPLATE;
//   //}
//  TEMPLATE bool rectd::unite(const rectd & rect1, const rectd & rect2) noexcept
//
//   {
//      return ::unite(this, rect1, rect2) != FALSE;
//   }
//
//  TEMPLATE void rectd::operator=(const ::rectd & rectectSrc) noexcept
//   {
//      ::copy(this, (const rectd&)& rectSrc);
//   }
//  TEMPLATE bool rectd::operator==(const ::rectd & rectectd) const noexcept
//   {
//      return ::is_equal((const rectd&)this, (const rectd&)& rectd) != FALSE;
//   }
//  TEMPLATE bool rectd::operator!=(const ::rectd & rectectd) const noexcept
//   {
//      return !::is_equal((const rectd&)this, (const rectd&)& rectd) != FALSE;
//   }
//  TEMPLATE void rectd::operator+=(POINTD point) noexcept
//   {
//      ::offset(this, point.x, point.y);
//   }
//  TEMPLATE void rectd::operator+=(SIZED size) noexcept
//   {
//      ::offset(this, size.cx, size.cy);
//   }
//  TEMPLATE void rectd::operator+=(const rectd & RECT_TEMPLATE) noexcept
//
//   {
//      inflate(RECT_TEMPLATE);
//   }
//
//  TEMPLATE void rectd::operator-=(POINTD point) noexcept
//   {
//      ::offset(this, -point.x, -point.y);
//   }
//  TEMPLATE void rectd::operator-=(SIZED size) noexcept
//   {
//      ::offset(this, -size.cx, -size.cy);
//   }
//  TEMPLATE void rectd::operator-=(const rectd & RECT_TEMPLATE) noexcept
//
//   {
//      deflate(RECT_TEMPLATE);
//   }
//
//  TEMPLATE void rectd::operator&=(const ::rectd & rectectd) noexcept
//   {
//      ::intersect(this, this, (const rectd&)& rectd);
//   }
//  TEMPLATE void rectd::operator|=(const ::rectd & rectectd) noexcept
//   {
//      ::unite(this, this, (const rectd&)& rectd);
//   }
//  TEMPLATE rectd rectd::operator+(POINTD point) const noexcept
//   {
//      rectd rectd(*this); ::offset(&rectd, point.x, point.y); return rectd;
//   }
//  TEMPLATE rectd rectd::operator-(POINTD point) const noexcept
//   {
//      rectd rectd(*this); ::offset(&rectd, -point.x, -point.y); return rectd;
//   }
//  TEMPLATE rectd rectd::operator+(SIZED size) const noexcept
//   {
//      rectd rectd(*this); ::offset(&rectd, size.cx, size.cy); return rectd;
//   }
//  TEMPLATE rectd rectd::operator-(SIZED size) const noexcept
//   {
//      rectd rectd(*this); ::offset(&rectd, -size.cx, -size.cy); return rectd;
//   }
//  TEMPLATE rectd rectd::operator+(const rectd & RECT_TEMPLATE) const noexcept
//
//   {
//      ::rectd rectd((const rectd&)this); rectd.inflate(RECT_TEMPLATE); return rectd;
//   }
//
//  TEMPLATE rectd rectd::operator-(const rectd & RECT_TEMPLATE) const noexcept
//
//   {
//      ::rectd rectd((const rectd&)this); rectd.deflate(RECT_TEMPLATE); return rectd;
//   }
//
//  TEMPLATE rectd rectd::operator&(const ::rectd & rectect2) const noexcept
//   {
//      ::rectd rectd; ::intersect(&rectd, (const rectd&)this, (const rectd&)& rect2);
//      return rectd;
//   }
//  TEMPLATE rectd rectd::operator|(const ::rectd & rectect2) const noexcept
//   {
//      ::rectd rectd; ::unite(&rectd, (const rectd&)this, (const rectd&)& rect2);
//      return rectd;
//   }
//   //TEMPLATE bool rectd::subtract(const rectd & pRectSrc1, const rectd & lpRectSrc2) noexcept
//
//   // { return ::subtract(this, pRectSrc1, lpRectSrc2) != FALSE; }
//
//
//  TEMPLATE void rectd::normalize() noexcept
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
//  TEMPLATE void rectd::inflate(const rectd & RECT_TEMPLATE) noexcept
//
//   {
//      left -= RECT_TEMPLATE.left;      top -= RECT_TEMPLATE.top;
//
//      right += RECT_TEMPLATE.right;      bottom += RECT_TEMPLATE.bottom;
//
//   }
//
//  TEMPLATE void rectd::inflate(double l, double t, double r, double b) noexcept
//   {
//      left -= l;         top -= t;
//      right += r;         bottom += b;
//   }
//
//  TEMPLATE void rectd::deflate(const rectd & RECT_TEMPLATE) noexcept
//
//   {
//      left += RECT_TEMPLATE.left;   top += RECT_TEMPLATE.top;
//
//      right -= RECT_TEMPLATE.right;   bottom -= RECT_TEMPLATE.bottom;
//
//   }
//
//  TEMPLATE void rectd::deflate(double l, double t, double r, double b) noexcept
//   {
//      left += l;      top += t;
//      right -= r;      bottom -= b;
//   }
//
//  TEMPLATE rectd rectd::MulDiv(double nMultiplier, double nDivisor) const noexcept
//   {
//      return rectd(left * nMultiplier / nDivisor,
//         top * nMultiplier / nDivisor,
//         right * nMultiplier / nDivisor,
//         bottom * nMultiplier / nDivisor);
//   }
//
//  TEMPLATE double rectd::area()
//   {
//
//      return size().area();
//
//   }
//
//
//  TEMPLATE void rectd::get_bounding_rect(const POINTD * ppoint, ::count count)
//
//   {
//
//      pointd_array::get_bounding_rect(this, ppoint, count);
//
//
//   }
//
//  TEMPLATE void rectd::get_bounding_rect(const pointd_array & pointa)
//   {
//
//      pointa.get_bounding_rect(this);
//
//   }
//
//
//
//
//
//  TEMPLATE void rectd::CenterOf(const rectd & RECT_TEMPLATE, SIZED size)
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
//  TEMPLATE void rectd::CenterOf(const rectd & RECT_TEMPLATE)
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
//  TEMPLATE double rectd::minimum_signed_absolute_dimension(bool bNegativePreference) const noexcept
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
//         return MIN(w, h);
//
//      }
//      else // ... otherwise prefer positive
//      {
//
//         return MAX(w, h);
//
//      }
//
//
//   }
//
//
//   double rectd::maximum_signed_absolute_dimension(bool bPositivePreference) const noexcept
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
//         return MAX(w, h);
//
//      }
//      else // ... otherwise prefer negative
//      {
//
//         return MIN(w, h);
//
//      }
//
//
//   }
//
//
//
//   double rectd::minimum_absolute_dimension() const noexcept { return MIN(fabs(width()), fabs(height())); }
//   double rectd::maximum_absolute_dimension() const noexcept { return MIN(fabs(width()), fabs(height())); }
//
//
//
//
//  TEMPLATE bool rectd::contains_x(double x) const noexcept
//   {
//      return left <= x && x <= right;
//   }
//  TEMPLATE bool rectd::contains_y(double y) const noexcept
//   {
//      return top <= y && y <= bottom;
//   }
//
//
//  TEMPLATE rectd& rectd::intersect(const rectd & RECT_TEMPLATE) noexcept
//
//   {
//      ::intersect(this, this, RECT_TEMPLATE);
//
//      return *this;
//   }
//
//
//  TEMPLATE rectd rectd::intersect(const rectd & RECT_TEMPLATE) const noexcept
//
//   {
//      ::rectd RECT_TEMPLATE;
//      ::intersect(&RECT_TEMPLATE, this, RECT_TEMPLATE);
//
//      return RECT_TEMPLATE;
//   }
//
//
//
//
//
//  TEMPLATE void rectd::set(double d) noexcept
//   {
//
//      set(d, d, d, d);
//
//   }
//
//
//  TEMPLATE bool rectd::is_null() const noexcept
//   {
//
//      return left == 0.0 && right == 0.0 && top == 0.0 && bottom == 0.0;
//
//   }
//
//
//
//
//  TEMPLATE void rectd::offset_x(double x) noexcept
//   {
//      left += x;
//      right += x;
//   }
//
//
//  TEMPLATE void rectd::offset_y(double y) noexcept
//   {
//      top += y;
//      bottom += y;
//   }
//
//
//  TEMPLATE pointd rectd::center() const noexcept
//   {
//
//      return pointd((left + right) / 2.0, (top + bottom) / 2.0);
//
//   }
//
//
//  TEMPLATE pointd rectd::top_right() const
//   {
//
//      return pointd(right, top);
//
//   }
//
//  TEMPLATE pointd rectd::bottom_left() const
//   {
//
//      return pointd(left, bottom);
//
//   }
//
//
//  TEMPLATETEMPLATE void rectd::align_rate(double x, double y, const rectd & RECT_TEMPLATE)
//   {
//
//      align_x(x, RECT_TEMPLATE);
//
//      align_y(y, RECT_TEMPLATE);
//
//   }
//
//  TEMPLATETEMPLATE void rectd::align_x(double dRate, const rectd & RECT_TEMPLATE)
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
//  TEMPLATETEMPLATE void rectd::align_y(double dRate, const rectd & RECT_TEMPLATE)
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
//  TEMPLATETEMPLATE bool rectd::intersects(const rectd & RECT_TEMPLATE) const noexcept
//
//   {
//
//      return intersects_x(RECT_TEMPLATE) && intersects_y(RECT_TEMPLATE);
//
//
//   }
//
//
//  TEMPLATETEMPLATE bool rectd::intersects_x(const rectd & RECT_TEMPLATE) const noexcept
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
//  TEMPLATETEMPLATE bool rectd::intersects_y(const rectd & RECT_TEMPLATE) const noexcept
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




template < typename TARGET, typename SOURCE >
inline TARGET * _001CopyRect(TARGET * prectTarget, const SOURCE * prectSource)
{

   return _001SetRectDim(
      prectTarget,
      (decltype(::left(prectTarget))) ::left(prectSource),
      (decltype(::top(prectTarget))) ::top(prectSource),
      (decltype(::width(prectTarget))) ::width(prectSource),
      (decltype(::height(prectTarget))) ::height(prectSource));

}


template < typename BASE_TYPE, typename POINT_BASE_TYPE, typename SIZE_BASE_TYPE >
void rect_type < BASE_TYPE, POINT_BASE_TYPE, SIZE_BASE_TYPE > ::get_bounding_rect(const POINT_BASE_TYPE * ppoint, ::count count)
{

   ::get_bounding_rect(this, ppoint, count);

}




