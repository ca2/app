#include "framework.h"
//#include <math.h>


//
//
//
//
//
//void rect64::DeflateBottomRightSizeByRate(double dRate)
//{
//   double dx = (double) width();
//   double dy = (double) height();
//   double dxNew = dx / dRate;
//   double dyNew = dy / dRate;
//   dx = dx - dxNew;
//   dy = dy - dyNew;
//   right -= (long) dx;
//   bottom -= (long) dy;
//}
//
//void rect64::SetBottomRightSize(i64 iWidth, i64 iHeight)
//{
//   right = left + iWidth;
//   bottom = top + iHeight;
//}
//
//void rect64::ExtendOnCenter(const ::rect64 & rect)
//
//{
//   i64 cx = width();
//   i64 cy = height();
//
//   double dx = (double) (rect.right - rect.left);
//
//   double dy = (double) (rect.bottom - rect.top);
//
//   double dr = MAX(dx / cx, dy / cy);
//
//   i64 cw = (i64) (cx * dr);
//   i64 ch = (i64) (cy * dr);
//   left = (long) ((dx - cw) / 2.0);
//   top = (long) ((dy - ch) / 2.0);
//   right = left + cw;
//   bottom = top + ch;
//}
//
//
//void rect64::FitOnCenterOf(const ::rect64 & rect)
//
//{
//   i64 cx = width();
//   i64 cy = height();
//
//   double dx = (double) (rect.right - rect.left);
//
//   double dy = (double) (rect.bottom - rect.top);
//
//   double dr = MIN(cx == 0 ? 1 : dx / cx, cy == 0 ? 1 : dy / cy);
//
//   i64 cw = cx == 0 ? (i64) dx : ((i64) (cx * dr));
//   i64 ch = cy == 0 ? (i64) dy : ((i64) (cy * dr));
//   left = (long) ((rect.left) + (dx - cw) / 2.0);
//
//   top = (long) ((rect.top) + (dy - ch) / 2.0);
//
//   right = left + cw;
//   bottom = top + ch;
//}
//
//void rect64::ScaleRect(double dx, double dy, i64 ix, i64 iy)
//{
//   left    = (long) (((left    - ix) * dx) + ix);
//   top     = (long) (((top     - iy) * dy) + iy);
//   right   = (long) (((right   - ix) * dx) + ix);
//   bottom  = (long) (((bottom  - iy) * dy) + iy);
//
//}
//
//void rect64::ScaleHeightAspect(i64 iNewHeight, i64 iCenterX, i64 iCenterY)
//{
//   i64 iHeight = height();
//   if(iHeight != 0)
//   {
//      double d = (double) iNewHeight / iHeight;
//      ScaleRect(d, d, iCenterX, iCenterY);
//   }
//}
//
//void rect64::Align(i64 align, const ::rect64 & rect)
//
//{
//
//   point64 ::point();
//
//   if((align & align_horizontal) == align_horizontal_center)
//   {
//      point.x = rect.left + (rect.right - rect.left) / 2 - width() / 2 - left;
//
//   }
//   else if((align & align_horizontal) == align_left)
//   {
//      point.x = rect.left - left;
//
//   }
//   else if((align & align_horizontal) == align_right)
//   {
//      point.x = rect.right - right;
//
//   }
//
//   if((align & align_vertical) ==  align_vertical_center)
//   {
//      point.y = rect.top + (rect.bottom - rect.top) / 2 - height() / 2 - top;
//
//   }
//   else if((align & align_vertical) == align_top)
//   {
//      point.y = rect.top - top;
//
//   }
//   else if((align & align_vertical) == align_bottom)
//   {
//      point.y = rect.bottom - bottom;
//
//   }
//
//   offset(point);
//
//}
//
//void rect64::constraint_v5(const ::rect64 & rect, const class ::size64 & sizeMin)
//
//{
//   if(left < rect.left)
//
//      left = rect.left;
//
//   if(right > rect.right)
//
//      right = rect.right;
//
//   if(top < rect.top)
//
//      top = rect.top;
//
//   if(bottom > rect.bottom)
//
//      bottom = rect.bottom;
//
//
//   if(width() < sizeMin.cx)
//      right = left + sizeMin.cx;
//   if(height() < sizeMin.cy)
//      bottom = top + sizeMin.cy;
//
//}
//
//bool rect64::contains(const ::rect64 & rect) const
//
//{
//   return rect.left >= left
//
//          && rect.right <= right
//
//          && rect.top >= top
//
//          && rect.bottom <= bottom;
//
//}
//
//// Subtract minor from major and return the greatest box around.
//void rect64::SubtractRectMajor(const ::rect64 & rectMajor, const ::rect64 & rectMinor)
//
//{
//   rect64 rectIntersect;
//   rect64 rectRet(*this);
//   if(rectIntersect.is_empty().intersect(rectMajor, rectMinor))
//
//   {
//      rectRet = rectMajor;
//
//   }
//   else
//   {
//      if(rectIntersect == rectMajor)
//
//      {
//         rectRet.set(0, 0, 0, 0);
//      }
//      else
//      {
//         if(rectIntersect.left == rectMajor.left
//
//               && rectIntersect.right == rectMajor.right)
//
//         {
//            if(rectIntersect.top == rectMajor.top)
//
//            {
//               rectRet.set(
//               rectMajor.left,
//
//               rectIntersect.top,
//               rectMajor.right,
//
//               rectMajor.bottom);
//
//            }
//            else if(rectIntersect.bottom == rectMajor.bottom)
//
//            {
//               rectRet.set(
//               rectMajor.left,
//
//               rectMajor.top,
//
//               rectMajor.right,
//
//               rectIntersect.bottom);
//            }
//            else
//            {
//               rectRet = rectMajor;
//
//            }
//         }
//         else if(rectIntersect.top == rectMajor.top
//
//                 && rectIntersect.bottom == rectMajor.bottom)
//
//         {
//            if(rectIntersect.left == rectMajor.left)
//
//            {
//               rectRet.set(
//               rectIntersect.left,
//               rectMajor.top,
//
//               rectMajor.right,
//
//               rectMajor.bottom);
//
//            }
//            else if(rectIntersect.right == rectMajor.right)
//
//            {
//               rectRet.set(
//               rectMajor.left,
//
//               rectMajor.top,
//
//               rectIntersect.right,
//               rectMajor.bottom);
//
//            }
//            else
//            {
//               rectRet = rectMajor;
//
//            }
//         }
//         else
//         {
//            rectRet = rectMajor;
//
//         }
//      }
//   }
//   *this = rectRet;
//   return;
//
//}
//
//void rect64::SubtractRectMinor(const ::rect64 & rectMajor, const ::rect64 & rectMinor)
//
//{
//   UNREFERENCED_PARAMETER(rectMajor);
//
//   UNREFERENCED_PARAMETER(rectMinor);
//
//}
//
//
//
//i64 rect64::minimum_absolute_dimension() const noexcept { return MIN(INTABS(width()),INTABS(height())); }
//i64 rect64::maximum_absolute_dimension() const noexcept { return MIN(INTABS(width()),INTABS(height())); }
//
//
//
//i64 rect64::minimum_signed_absolute_dimension(bool bNegativePreference) const noexcept
//{
//
//   i64 w = width();
//
//   i64 h = height();
//
//   if(abs(w) < abs(h))
//   {
//
//      return w;
//
//   }
//   else if(abs(h) < abs(w))
//   {
//
//      return h;
//
//   }
//   else if(bNegativePreference) // absolutely equal, prefer negative ...
//   {
//
//      return MIN(w,h);
//
//   }
//   else // ... otherwise prefer positive
//   {
//
//      return MAX(w,h);
//
//   }
//
//
//}
//
//
//i64 rect64::maximum_signed_absolute_dimension(bool bPositivePreference) const noexcept
//{
//
//   i64 w = width();
//
//   i64 h = height();
//
//   if(abs(w) > abs(h))
//   {
//
//      return w;
//
//   }
//   else if(abs(h) > abs(w))
//   {
//
//      return h;
//
//   }
//   else if(bPositivePreference) // absolutely equal, prefer positive ...
//   {
//
//      return MAX(w,h);
//
//   }
//   else // ... otherwise prefer negative
//   {
//
//      return MIN(w,h);
//
//   }
//
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
//void rectd::_001Constraint(const rectd& rect)
//
//{
//
//   _001ConstraintX(rect);
//
//
//   _001ConstraintY(rect);
//
//
//}
//
//
//void rectd::_001ConstraintX(const rectd& rect)
//
//{
//
//   if (right > rect.right)
//
//   {
//
//      offset_x(rect.right - right);
//
//
//   }
//
//   if (left < rect.left)
//
//   {
//
//      offset_x(rect.left - left);
//
//
//   }
//
//
//}
//
//
//void rectd::_001ConstraintY(const rectd & rect)
//
//{
//
//   if (bottom > rect.bottom)
//
//   {
//
//      offset_y(rect.bottom - bottom);
//
//
//   }
//
//   if (top < rect.top)
//
//   {
//
//      offset_y(rect.top - top);
//
//
//   }
//
//}
//
//
//void rectd::_001Constraint(const rectd & rect, RECTD * prectBounding)
//
//{
//
//   _001ConstraintX(rect, prectBounding);
//
//
//   _001ConstraintY(rect, prectBounding);
//
//
//}
//
//
//void rectd::_001ConstraintX(const rectd & rect, RECTD * prectBounding)
//
//{
//
//   if (prectBounding->right > rect.right)
//
//   {
//
//      offset_x(::offset_x(prectBounding, rect.right - prectBounding->right));
//
//
//   }
//
//   if (prectBounding->left < rect.left)
//
//   {
//
//      offset_x(::offset_x(prectBounding, rect.left - prectBounding->left));
//
//
//   }
//
//
//}
//
//
//void rectd::_001ConstraintY(const rectd & rect, RECTD * prectBounding)
//
//{
//
//   if (prectBounding->bottom > rect.bottom)
//
//   {
//
//      offset_y(::offset_y(prectBounding, rect.bottom - prectBounding->bottom));
//
//
//   }
//
//   if (prectBounding->top < rect.top)
//
//   {
//
//      offset_y(::offset_y(prectBounding, rect.top - prectBounding->top));
//
//
//   }
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
//void rectd::_001Align(double x, double y, const rectd& rect)
//{
//
//   _001AlignX(x, rect);
//
//   _001AlignY(y, rect);
//
//}
//
//
//void rectd::_001AlignX(double dRate, const rectd& rect)
//{
//
//   if (fabs(dRate) < 1000.0)
//   {
//
//      align_x(dRate, rect);
//
//   }
//   else if (dRate >= 1000.0)
//   {
//
//      dRate -= 1000.0;
//
//      double x = rect.right + width() * dRate;
//
//      move_to_x(x);
//
//
//   }
//   else if (dRate <= -1000.0)
//   {
//
//      dRate += 1000.0;
//
//      double x = rect.left + width() * dRate;
//
//      move_to_x(x - width());
//
//   }
//
//}
//
//
//void rectd::_001AlignY(double dRate, const rectd & rect)
//{
//
//   if (fabs(dRate) < 1000.0)
//   {
//
//      align_y(dRate, rect);
//
//   }
//   else if (dRate >= 1000.0)
//   {
//
//      dRate -= 1000.0;
//
//      double y = rect.bottom + height() * dRate;
//
//      move_to_y(y);
//
//
//   }
//   else if (dRate <= -1000.0)
//   {
//
//      dRate += 1000.0;
//
//      double y = rect.top + height() * dRate;
//
//      move_to_y(y - height());
//
//   }
//
//
//}
//
//
