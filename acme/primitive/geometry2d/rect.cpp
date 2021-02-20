#include "framework.h"
//#include <math.h>


//
//
//
//
//
//void rectangle_i64::DeflateBottomRightSizeByRate(double dRate)
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
//void rectangle_i64::SetBottomRightSize(i64 iWidth, i64 iHeight)
//{
//   right = left + iWidth;
//   bottom = top + iHeight;
//}
//
//void rectangle_i64::ExtendOnCenter(const ::rectangle_i64 & rectangle)
//
//{
//   i64 cx = width();
//   i64 cy = height();
//
//   double dx = (double) (rectangle.right - rectangle.left);
//
//   double dy = (double) (rectangle.bottom - rectangle.top);
//
//   double dr = maximum(dx / cx, dy / cy);
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
//void rectangle_i64::FitOnCenterOf(const ::rectangle_i64 & rectangle)
//
//{
//   i64 cx = width();
//   i64 cy = height();
//
//   double dx = (double) (rectangle.right - rectangle.left);
//
//   double dy = (double) (rectangle.bottom - rectangle.top);
//
//   double dr = minimum(cx == 0 ? 1 : dx / cx, cy == 0 ? 1 : dy / cy);
//
//   i64 cw = cx == 0 ? (i64) dx : ((i64) (cx * dr));
//   i64 ch = cy == 0 ? (i64) dy : ((i64) (cy * dr));
//   left = (long) ((rectangle.left) + (dx - cw) / 2.0);
//
//   top = (long) ((rectangle.top) + (dy - ch) / 2.0);
//
//   right = left + cw;
//   bottom = top + ch;
//}
//
//void rectangle_i64::ScaleRect(double dx, double dy, i64 ix, i64 iy)
//{
//   left    = (long) (((left    - ix) * dx) + ix);
//   top     = (long) (((top     - iy) * dy) + iy);
//   right   = (long) (((right   - ix) * dx) + ix);
//   bottom  = (long) (((bottom  - iy) * dy) + iy);
//
//}
//
//void rectangle_i64::ScaleHeightAspect(i64 iNewHeight, i64 iCenterX, i64 iCenterY)
//{
//   i64 iHeight = height();
//   if(iHeight != 0)
//   {
//      double d = (double) iNewHeight / iHeight;
//      ScaleRect(d, d, iCenterX, iCenterY);
//   }
//}
//
//void rectangle_i64::Align(i64 align, const ::rectangle_i64 & rectangle)
//
//{
//
//   point_i64 ::point_i32();
//
//   if((align & align_horizontal) == e_align_horizontal_center)
//   {
//      point.x = rectangle.left + (rectangle.right - rectangle.left) / 2 - width() / 2 - left;
//
//   }
//   else if((align & align_horizontal) == e_align_left)
//   {
//      point.x = rectangle.left - left;
//
//   }
//   else if((align & align_horizontal) == e_align_right)
//   {
//      point.x = rectangle.right - right;
//
//   }
//
//   if((align & align_vertical) ==  e_align_vertical_center)
//   {
//      point.y = rectangle.top + (rectangle.bottom - rectangle.top) / 2 - height() / 2 - top;
//
//   }
//   else if((align & align_vertical) == e_align_top)
//   {
//      point.y = rectangle.top - top;
//
//   }
//   else if((align & align_vertical) == e_align_bottom)
//   {
//      point.y = rectangle.bottom - bottom;
//
//   }
//
//   offset(point);
//
//}
//
//void rectangle_i64::constraint_v5(const ::rectangle_i64 & rectangle, const class ::size_i64 & sizeMin)
//
//{
//   if(left < rectangle.left)
//
//      left = rectangle.left;
//
//   if(right > rectangle.right)
//
//      right = rectangle.right;
//
//   if(top < rectangle.top)
//
//      top = rectangle.top;
//
//   if(bottom > rectangle.bottom)
//
//      bottom = rectangle.bottom;
//
//
//   if(width() < sizeMin.cx)
//      right = left + sizeMin.cx;
//   if(height() < sizeMin.cy)
//      bottom = top + sizeMin.cy;
//
//}
//
//bool rectangle_i64::contains(const ::rectangle_i64 & rectangle) const
//
//{
//   return rectangle.left >= left
//
//          && rectangle.right <= right
//
//          && rectangle.top >= top
//
//          && rectangle.bottom <= bottom;
//
//}
//
//// Subtract minor from major and return the greatest box around.
//void rectangle_i64::SubtractRectMajor(const ::rectangle_i64 & rectMajor, const ::rectangle_i64 & rectMinor)
//
//{
//   rectangle_i64 rectIntersect;
//   rectangle_i64 rectRet(*this);
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
//void rectangle_i64::SubtractRectMinor(const ::rectangle_i64 & rectMajor, const ::rectangle_i64 & rectMinor)
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
//i64 rectangle_i64::minimum_absolute_dimension() const noexcept { return minimum(INTABS(width()),INTABS(height())); }
//i64 rectangle_i64::maximum_absolute_dimension() const noexcept { return minimum(INTABS(width()),INTABS(height())); }
//
//
//
//i64 rectangle_i64::minimum_signed_absolute_dimension(bool bNegativePreference) const noexcept
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
//      return minimum(w,h);
//
//   }
//   else // ... otherwise prefer positive
//   {
//
//      return maximum(w,h);
//
//   }
//
//
//}
//
//
//i64 rectangle_i64::maximum_signed_absolute_dimension(bool bPositivePreference) const noexcept
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
//      return maximum(w,h);
//
//   }
//   else // ... otherwise prefer negative
//   {
//
//      return minimum(w,h);
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
//void rectangle_f64::_001Constraint(const rectangle_f64& rectangle)
//
//{
//
//   _001ConstraintX(rectangle);
//
//
//   _001ConstraintY(rectangle);
//
//
//}
//
//
//void rectangle_f64::_001ConstraintX(const rectangle_f64& rectangle)
//
//{
//
//   if (right > rectangle.right)
//
//   {
//
//      offset_x(rectangle.right - right);
//
//
//   }
//
//   if (left < rectangle.left)
//
//   {
//
//      offset_x(rectangle.left - left);
//
//
//   }
//
//
//}
//
//
//void rectangle_f64::_001ConstraintY(const rectangle_f64 & rectangle)
//
//{
//
//   if (bottom > rectangle.bottom)
//
//   {
//
//      offset_y(rectangle.bottom - bottom);
//
//
//   }
//
//   if (top < rectangle.top)
//
//   {
//
//      offset_y(rectangle.top - top);
//
//
//   }
//
//}
//
//
//void rectangle_f64::_001Constraint(const rectangle_f64 & rectangle, RECTANGLE_F64 * prectBounding)
//
//{
//
//   _001ConstraintX(rectangle, prectBounding);
//
//
//   _001ConstraintY(rectangle, prectBounding);
//
//
//}
//
//
//void rectangle_f64::_001ConstraintX(const rectangle_f64 & rectangle, RECTANGLE_F64 * prectBounding)
//
//{
//
//   if (prectBounding->right > rectangle.right)
//
//   {
//
//      offset_x(::offset_x(prectBounding, rectangle.right - prectBounding->right));
//
//
//   }
//
//   if (prectBounding->left < rectangle.left)
//
//   {
//
//      offset_x(::offset_x(prectBounding, rectangle.left - prectBounding->left));
//
//
//   }
//
//
//}
//
//
//void rectangle_f64::_001ConstraintY(const rectangle_f64 & rectangle, RECTANGLE_F64 * prectBounding)
//
//{
//
//   if (prectBounding->bottom > rectangle.bottom)
//
//   {
//
//      offset_y(::offset_y(prectBounding, rectangle.bottom - prectBounding->bottom));
//
//
//   }
//
//   if (prectBounding->top < rectangle.top)
//
//   {
//
//      offset_y(::offset_y(prectBounding, rectangle.top - prectBounding->top));
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
//void rectangle_f64::_001Align(double x, double y, const rectangle_f64& rectangle)
//{
//
//   _001AlignX(x, rectangle);
//
//   _001AlignY(y, rectangle);
//
//}
//
//
//void rectangle_f64::_001AlignX(double dRate, const rectangle_f64& rectangle)
//{
//
//   if (fabs(dRate) < 1000.0)
//   {
//
//      align_x(dRate, rectangle);
//
//   }
//   else if (dRate >= 1000.0)
//   {
//
//      dRate -= 1000.0;
//
//      double x = rectangle.right + width() * dRate;
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
//      double x = rectangle.left + width() * dRate;
//
//      move_to_x(x - width());
//
//   }
//
//}
//
//
//void rectangle_f64::_001AlignY(double dRate, const rectangle_f64 & rectangle)
//{
//
//   if (fabs(dRate) < 1000.0)
//   {
//
//      align_y(dRate, rectangle);
//
//   }
//   else if (dRate >= 1000.0)
//   {
//
//      dRate -= 1000.0;
//
//      double y = rectangle.bottom + height() * dRate;
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
//      double y = rectangle.top + height() * dRate;
//
//      move_to_y(y - height());
//
//   }
//
//
//}
//
//




