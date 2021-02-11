#include "framework.h"





//i64 MulDiv(i64 nNumber, i64 nNumerator, i64 nDenominator)
//{
//   return muldiv64(nNumber, nNumerator, nDenominator);
//}
//
//
//bool null(RECTANGLE_I32 * prectDest)
//{
//
//   prectDest->left      = 0;
//   prectDest->top       = 0;
//   prectDest->right     = 0;
//   prectDest->bottom    = 0;
//   return true;
//
//}
//
//
//bool x_intersect_rect(RECTANGLE_I32 * prectangle, const rectangle_i32 & prect1, const rectangle_i32 & prect2)
//{
//
//   prectangle->left   = max(prect1->left, prect2->left);
//
//   prectangle->right  = min(prect1->right, prect2->right);
//
//   if(prectangle->right > prectangle->left)
//   {
//      
//      return true;
//
//   }
//   else
//   {
//
//      return false;
//
//   }
//
//}
//
//
//bool y_intersect_rect(RECTANGLE_I32 * prectangle,const rectangle_i32 & prect1,const rectangle_i32 & prect2)
//{
//
//   prectangle->top     = max(prect1->top,prect2->top);
//
//   prectangle->bottom  = min(prect1->bottom,prect2->bottom);
//
//   if(prectangle->top < prectangle->bottom)
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      null(prectangle);
//
//      return false;
//
//   }
//
//}
//
//
//bool x_null_intersect_rect(RECTANGLE_I32 * prectangle,const rectangle_i32 & rect1,const rectangle_i32 & rect2)
//{
//
//   prectangle->left    = max(rect1.left,rect2.left);
//
//   prectangle->right   = min(rect1.right,rect2.right);
//
//   if(prectangle->right >= prectangle->left)
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      prectangle->left = 0;
//
//      prectangle->right = 0;
//
//      return false;
//
//   }
//
//}
//
//
//bool y_null_intersect_rect(RECTANGLE_I32 * prectangle,const rectangle_i32 & rect1,const rectangle_i32 & rect2)
//{
//
//   prectangle->top     = max(rect1.top,rect2.top);
//
//   prectangle->bottom  = min(rect1.bottom,rect2.bottom);
//
//   if(prectangle->top <= prectangle->bottom)
//   {
//
//      return true;
//
//   }
//   else
//   {
//      
//      prectangle->top = 0;
//
//      prectangle->bottom= 0;
//
//      return false;
//
//   }
//
//}
//
//
//CLASS_DECL_ACME bool null_intersect_rect(RECTANGLE_I32 * prectangle,const rectangle_i32 & rect1,const rectangle_i32 & rect2)
//{
//
//   if(x_null_intersect_rect(prectangle,rect1,rect2) && y_null_intersect_rect(prectangle,rect1,rect2))
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      null(prectangle);
//
//      return false;
//
//   }
//
//}
//
//
//bool x_left_null_intersect_rect(RECTANGLE_I32 * prectangle,const rectangle_i32 & rect1,const rectangle_i32 & rect2)
//{
//
//   prectangle->left    = max(rect1.left,rect2.left);
//
//   prectangle->right   = min(rect1.right,rect2.right);
//
//   if(prectangle->right > prectangle->left || (prectangle->right == prectangle->left && rect1.left == rect2.left))
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      prectangle->left = 0;
//
//      prectangle->right = 0;
//
//      return false;
//
//   }
//
//}
//
//
//bool y_top_null_intersect_rect(RECTANGLE_I32 * prectangle,const rectangle_i32 & rect1, const rectangle_i32 & rect2)
//{
//
//   prectangle->top     = max(rect1.top, rect2.top);
//
//   prectangle->bottom  = min(rect1.bottom, rect2.bottom);
//
//   if(prectangle->top < prectangle->bottom || (prectangle->top == prectangle->bottom && rect1.top == rect2.top))
//   {
//
//      return true;
//
//   }
//   else
//   {
//      prectangle->top = 0;
//
//      prectangle->bottom= 0;
//
//      return false;
//   }
//
//}
//
//
//CLASS_DECL_ACME bool top_left_null_intersect_rect(RECTANGLE_I32 * prectangle,const rectangle_i32 & rect1,const rectangle_i32 & rect2)
//
//{
//   if(x_left_null_intersect_rect(prectangle,rect1,rect2)
//
//         && y_top_null_intersect_rect(prectangle,rect1,rect2))
//
//   {
//      return true;
//   }
//   else
//   {
//      null(prectangle);
//
//      return false;
//   }
//}
//
//bool copy(RECTANGLE_F64 * prectDest, const RECTANGLE_F64 * prectSrc)
//{
//   *prectDest = *prectSrc;
//   return true;
//}
//
//bool copy(RECTANGLE_F64 * prectDest, const ::rectangle_i32 & prectSrc)
//{
//   prectDest->left      = prectSrc->left;
//   prectDest->top       = prectSrc->top;
//   prectDest->right     = prectSrc->right;
//   prectDest->bottom    = prectSrc->bottom;
//   return true;
//}
//
//bool copy(RECTANGLE_I32 * prectDest, const RECTANGLE_F64 * prectSrc)
//{
//   if(!is32integer(prectSrc->left) || !is32integer(prectSrc->top) || !is32integer(prectSrc->right) || !is32integer(prectSrc->bottom))
//      return false;
//   prectDest->left      = (::i32) prectSrc->left;
//   prectDest->top       = (::i32) prectSrc->top;
//   prectDest->right     = (::i32) prectSrc->right;
//   prectDest->bottom    = (::i32) prectSrc->bottom;
//   return true;
//}
//
//bool copy(RECTANGLE_F64 * prectDest, const RECTANGLE_I64 * prectSrc)
//{
//   if(!is_double(prectSrc->left) || !is_double(prectSrc->top) || !is_double(prectSrc->right) || !is_double(prectSrc->bottom))
//      return false;
//   prectDest->left      = (double) prectSrc->left;
//   prectDest->top       = (double) prectSrc->top;
//   prectDest->right     = (double) prectSrc->right;
//   prectDest->bottom    = (double) prectSrc->bottom;
//   return true;
//}
//
//bool copy(RECTANGLE_I64 * prectDest, const RECTANGLE_F64 * prectSrc)
//{
//   prectDest->left      = (::i32) prectSrc->left;
//   prectDest->top       = (::i32) prectSrc->top;
//   prectDest->right     = (::i32) prectSrc->right;
//   prectDest->bottom    = (::i32) prectSrc->bottom;
//   return true;
//}
//bool is_empty(const RECTANGLE_F64 * prectangle)
//{
//   return
//   prectangle->left   >= prectangle->right
//   && prectangle->top >= prectangle->bottom;
//}
//
//bool contains(const RECTANGLE_F64 * prectangle, POINT_F64 point_i32)
//{
//   return
//   point.x >= prectangle->left && point.x <= prectangle->right
//   && point.y >= prectangle->top && point.y <= prectangle->bottom;
//}
//bool set_rect(RECTANGLE_F64 * prectDest, double x1, double y1, double x2, double y2)
//{
//   prectDest->left      = x1;
//   prectDest->top       = y1;
//   prectDest->right     = x2;
//   prectDest->bottom    = y2;
//   return true;
//}
//bool null(RECTANGLE_F64 * prectDest)
//{
//   prectDest->left      = 0;
//   prectDest->top       = 0;
//   prectDest->right     = 0;
//   prectDest->bottom    = 0;
//   return true;
//}
//bool is_equal(const RECTANGLE_F64 * prect1, const RECTANGLE_F64 * prect2)
//{
//
//   return
//   prect1->left      == prect2->left &&
//   prect1->top       == prect2->top &&
//   prect1->right     == prect2->right &&
//   prect1->bottom    == prect2->bottom;
//
//}
//
//
//bool inflate(RECTANGLE_F64 * prectangle, double x, double y)
//{
//
//   prectangle->left      -= x;
//   prectangle->top       -= y;
//   prectangle->right     += x;
//   prectangle->bottom    += y;
//   return true;
//
//}
//
//
//bool deflate(RECTANGLE_F64 * prectangle, double x, double y)
//{
//
//   prectangle->left      += x;
//   prectangle->top       += y;
//   prectangle->right     -= x;
//   prectangle->bottom    -= y;
//   return true;
//
//}
//
//
//bool offset(RECTANGLE_F64 * prectangle, double x, double y)
//{
//
//   prectangle->left      += x;
//   prectangle->top       += y;
//   prectangle->right     += x;
//   prectangle->bottom    += y;
//   return true;
//
//}
//
//
//bool x_intersect_rect(RECTANGLE_F64 * prectangle, const RECTANGLE_F64 * prect1, const RECTANGLE_F64 * prect2)
//{
//   prectangle->left    = max(prect1->left, prect2->left);
//   prectangle->right   = min(prect1->right, prect2->right);
//   if(prectangle->right > prectangle->left)
//   {
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//}
//
//
//bool y_intersect_rect(RECTANGLE_F64 * prectangle, const RECTANGLE_F64 * prect1, const RECTANGLE_F64 * prect2)
//{
//   prectangle->top     = max(prect1->top, prect2->top);
//   prectangle->bottom  = min(prect1->bottom, prect2->bottom);
//   if(prectangle->top < prectangle->bottom)
//   {
//      return true;
//   }
//   else
//   {
//      null(prectangle);
//      return false;
//   }
//}
//
//
//
//
//bool x_null_intersect_rect(RECTANGLE_F64 * prectangle,const RECTANGLE_F64 * prect1,const RECTANGLE_F64 * prect2)
//{
//   prectangle->left    = max(prect1->left,prect2->left);
//   prectangle->right   = min(prect1->right,prect2->right);
//   if(prectangle->right >= prectangle->left)
//   {
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//}
//
//
//bool y_null_intersect_rect(RECTANGLE_F64 * prectangle,const RECTANGLE_F64 * prect1,const RECTANGLE_F64 * prect2)
//{
//   prectangle->top     = max(prect1->top,prect2->top);
//   prectangle->bottom  = min(prect1->bottom,prect2->bottom);
//   if(prectangle->top <= prectangle->bottom)
//   {
//      return true;
//   }
//   else
//   {
//      null(prectangle);
//      return false;
//   }
//}
//
//
//bool intersect(RECTANGLE_F64 * prectangle, const RECTANGLE_F64 * prect1, const RECTANGLE_F64 * prect2)
//{
//   if(x_intersect_rect(prectangle, prect1, prect2)
//         && y_intersect_rect(prectangle, prect1, prect2))
//   {
//      return true;
//   }
//   else
//   {
//      null(prectangle);
//      return false;
//   }
//}
//
//
//bool unite(RECTANGLE_F64 * prectangle, const RECTANGLE_F64 * prect1, const RECTANGLE_F64 * prect2)
//{
//   if(is_empty(prect1))
//   {
//      if(is_empty(prect2))
//      {
//         null(prectangle);
//         return false;
//      }
//      else
//      {
//         *prectangle =* prect2;
//         return true;
//      }
//   }
//   else if(is_empty(prect2))
//   {
//      *prectangle = *prect1;
//      return true;
//   }
//   prectangle->left    = min(prect1->left, prect2->left);
//   prectangle->right   = max(prect1->right, prect2->right);
//   prectangle->top     = min(prect1->top, prect2->top);
//   prectangle->bottom  = max(prect1->bottom, prect2->bottom);
//   if(prectangle->right > prectangle->left &&
//         prectangle->bottom > prectangle->top)
//   {
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//}
//
//
//
//CLASS_DECL_ACME double width(const ::rectangle_f64 & rectangle)
//
//{
//   return pcrect->right - pcrect->left;
//
//}
//
//CLASS_DECL_ACME double height(const ::rectangle_f64 & rectangle)
//
//{
//   return pcrect->bottom - pcrect->top;
//
//}
//
//CLASS_DECL_ACME double width(const ::rectangle_f64 & rectangle)
//{
//   return ::width(&rectangle);
//}
//
//CLASS_DECL_ACME double height(const ::rectangle_f64 & rectangle)
//{
//   return ::height(&rectangle);
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
//bool copy(RECTANGLE_I64 * prectDest, const RECTANGLE_I64 * prectSrc)
//{
//   *prectDest = *prectSrc;
//   return true;
//}
//
//bool copy(RECTANGLE_I64 * prectDest, const ::rectangle_i32 & prectSrc)
//{
//   prectDest->left      = prectSrc->left;
//   prectDest->top       = prectSrc->top;
//   prectDest->right     = prectSrc->right;
//   prectDest->bottom    = prectSrc->bottom;
//   return true;
//}
//
//bool copy(RECTANGLE_I32 * prectDest, const RECTANGLE_I64 * prectSrc)
//{
//   if(!is32integer(prectSrc->left) || !is32integer(prectSrc->top) || !is32integer(prectSrc->right) || !is32integer(prectSrc->bottom))
//      return false;
//   prectDest->left      = (::i32) prectSrc->left;
//   prectDest->top       = (::i32) prectSrc->top;
//   prectDest->right     = (::i32) prectSrc->right;
//   prectDest->bottom    = (::i32) prectSrc->bottom;
//   return true;
//}
//bool is_empty(const RECTANGLE_I64 * prectangle)
//{
//   return
//   prectangle->left   >= prectangle->right
//   && prectangle->top >= prectangle->bottom;
//}
//
//
//bool contains(const RECTANGLE_I64 * prectangle, point_i64 point)
//{
//
//   return
//   point.x >= prectangle->left && point.x <= prectangle->right
//   && point.y >= prectangle->top && point.y <= prectangle->bottom;
//
//}
//
//bool set_rect(RECTANGLE_I64 * prectDest, i64 x1, i64 y1, i64 x2, i64 y2)
//{
//
//   prectDest->left      = x1;
//   prectDest->top       = y1;
//   prectDest->right     = x2;
//   prectDest->bottom    = y2;
//   return true;
//
//}
//
//
//bool null(RECTANGLE_I64 * prectDest)
//{
//
//   prectDest->left      = 0;
//   prectDest->top       = 0;
//   prectDest->right     = 0;
//   prectDest->bottom    = 0;
//   return true;
//
//}
//
//bool is_equal(const RECTANGLE_I64 * prect1, const RECTANGLE_I64 * prect2)
//{
//   return
//   prect1->left      == prect2->left &&
//   prect1->top       == prect2->top &&
//   prect1->right     == prect2->right &&
//   prect1->bottom    == prect2->bottom;
//}
//
//bool inflate(RECTANGLE_I64 * prectangle, i64 x, i64 y)
//{
//
//   prectangle->left      -= x;
//   prectangle->top       -= y;
//   prectangle->right     += x;
//   prectangle->bottom    += y;
//   return true;
//
//}
//
//bool deflate(RECTANGLE_I64 * prectangle, i64 x, i64 y)
//{
//
//   prectangle->left      += x;
//   prectangle->top       += y;
//   prectangle->right     -= x;
//   prectangle->bottom    -= y;
//   return true;
//
//}
//
//
//bool offset(RECTANGLE_I64 * prectangle, i64 x, i64 y)
//{
//
//   prectangle->left      += x;
//   prectangle->top       += y;
//   prectangle->right     += x;
//   prectangle->bottom    += y;
//   return true;
//
//}
//
//
//bool resize(RECTANGLE_I64 * prectangle,i64 cx,i64 cy)
//{
//   prectangle->right     = prectangle->left + cx;
//   prectangle->bottom    = prectangle->top + cy;
//   return true;
//
//}
//
//
//bool reverse_size(RECTANGLE_I64 * prectangle,i64 cx,i64 cy)
//{
//
//   prectangle->left      = prectangle->right  - cx;
//   prectangle->top       = prectangle->bottom - cy;
//   return true;
//
//}
//
//bool x_intersect_rect(RECTANGLE_I64 * prectangle, const RECTANGLE_I64 * prect1, const RECTANGLE_I64 * prect2)
//{
//
//   prectangle->left    = max(prect1->left, prect2->left);
//   prectangle->right   = min(prect1->right, prect2->right);
//
//   if(prectangle->right > prectangle->left)
//   {
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//
//}
//
//
//bool y_intersect_rect(RECTANGLE_I64 * prectangle, const RECTANGLE_I64 * prect1, const RECTANGLE_I64 * prect2)
//{
//   prectangle->top     = max(prect1->top, prect2->top);
//   prectangle->bottom  = min(prect1->bottom, prect2->bottom);
//   if(prectangle->top < prectangle->bottom)
//   {
//      return true;
//   }
//   else
//   {
//      null(prectangle);
//      return false;
//   }
//
//}
//
//
//bool intersect(RECTANGLE_I64 * prectangle, const RECTANGLE_I64 * prect1, const RECTANGLE_I64 * prect2)
//{
//   if(x_intersect_rect(prectangle, prect1, prect2)
//         && y_intersect_rect(prectangle, prect1, prect2))
//   {
//      return true;
//   }
//   else
//   {
//      null(prectangle);
//      return false;
//   }
//
//}
//
//
//bool unite(RECTANGLE_I64 * prectangle, const RECTANGLE_I64 * prect1, const RECTANGLE_I64 * prect2)
//{
//   if(is_empty(prect1))
//   {
//      if(is_empty(prect2))
//      {
//         null(prectangle);
//         return false;
//      }
//      else
//      {
//         *prectangle =* prect2;
//         return true;
//      }
//   }
//   else if(is_empty(prect2))
//   {
//      *prectangle = *prect1;
//      return true;
//   }
//   prectangle->left    = min(prect1->left, prect2->left);
//   prectangle->right   = max(prect1->right, prect2->right);
//   prectangle->top     = min(prect1->top, prect2->top);
//   prectangle->bottom  = max(prect1->bottom, prect2->bottom);
//   if(prectangle->right > prectangle->left &&
//         prectangle->bottom > prectangle->top)
//   {
//      return true;
//   }
//   else
//   {
//      return false;
//   }
//}
//
//
//
//
//
//
//
//CLASS_DECL_ACME bool deflate(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle)
//
//{
//   prectangle->left    += pcrect->left;
//
//   prectangle->right   -= pcrect->right;
//
//   prectangle->top     += pcrect->top;
//
//   prectangle->bottom  -= pcrect->bottom;
//
//   return true;
//}
//
//CLASS_DECL_ACME bool deflate(RECTANGLE_I32 * prectangle,const ::rectangle_i32 & rectangle)
//{
//   return deflate(prectangle, &rectangle);
//}
//
//
//
//CLASS_DECL_ACME bool copy(POINT_I64 * pptDst,const point_i32 & pointSrc)
//
//{
//
//   pptDst->x = lpptSrc->x;
//
//
//   pptDst->y = lpptSrc->y;
//
//
//   return true;
//
//}
//
//
//CLASS_DECL_ACME bool copy(POINT_I32 * pptDst,const POINT_I64 * lpptSrc)
//
//{
//
//   pptDst->x = (::i32)lpptSrc->x;
//
//
//   pptDst->y = (::i32)lpptSrc->y;
//
//
//   return true;
//
//
//}
//
//
//
//#ifdef __APPLE__
//
//
//
//
//void copy(CGRect & rectDst, const rectangle_i32 & rectSrc)
//{
//   rectDst.origin.x = rectSrc.left;
//   rectDst.origin.y = rectSrc.top;
//   rectDst.size.width = width(rectSrc);
//   rectDst.size.height = height(rectSrc);
//
//}
//
//
//void copy(RECTANGLE_I32 * prectDst, const CGRect & rectSrc)
//
//{
//   prectDst->left = rectSrc.origin.x;
//
//   prectDst->top = rectSrc.origin.y;
//
//   prectDst->right = rectSrc.origin.x + rectSrc.size.width;
//
//   prectDst->bottom = rectSrc.origin.y + rectSrc.size.height;
//
//}
//
//void copy(CGRect & rectangle, const ::rectangle_i32 & rectangle)
//
//{
//
//   rectangle.origin.x = pcrect->left;
//
//   rectangle.origin.y = pcrect->top;
//
//   rectangle.size.width = width(pcrect);
//
//   rectangle.size.height = height(pcrect);
//
//
//
//}
//
//#endif
//
//
//CLASS_DECL_ACME int_bool IsRectEmpty(const ::rectangle_i32 & rectangle)
//{
//
//   return IsRectEmpty((const rectangle_i32 &)&rectangle);
//
//}



