#include "framework.h"





//i64 MulDiv(i64 nNumber, i64 nNumerator, i64 nDenominator)
//{
//   return muldiv64(nNumber, nNumerator, nDenominator);
//}
//
//
//bool null(RECT32 * prectDest)
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
//bool x_intersect_rect(RECT32 * prect, const rect & prect1, const rect & prect2)
//{
//
//   prect->left   = max(prect1->left, prect2->left);
//
//   prect->right  = min(prect1->right, prect2->right);
//
//   if(prect->right > prect->left)
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
//bool y_intersect_rect(RECT32 * prect,const rect & prect1,const rect & prect2)
//{
//
//   prect->top     = max(prect1->top,prect2->top);
//
//   prect->bottom  = min(prect1->bottom,prect2->bottom);
//
//   if(prect->top < prect->bottom)
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      null(prect);
//
//      return false;
//
//   }
//
//}
//
//
//bool x_null_intersect_rect(RECT32 * prect,const rect & rect1,const rect & rect2)
//{
//
//   prect->left    = max(rect1.left,rect2.left);
//
//   prect->right   = min(rect1.right,rect2.right);
//
//   if(prect->right >= prect->left)
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      prect->left = 0;
//
//      prect->right = 0;
//
//      return false;
//
//   }
//
//}
//
//
//bool y_null_intersect_rect(RECT32 * prect,const rect & rect1,const rect & rect2)
//{
//
//   prect->top     = max(rect1.top,rect2.top);
//
//   prect->bottom  = min(rect1.bottom,rect2.bottom);
//
//   if(prect->top <= prect->bottom)
//   {
//
//      return true;
//
//   }
//   else
//   {
//      
//      prect->top = 0;
//
//      prect->bottom= 0;
//
//      return false;
//
//   }
//
//}
//
//
//CLASS_DECL_ACME bool null_intersect_rect(RECT32 * prect,const rect & rect1,const rect & rect2)
//{
//
//   if(x_null_intersect_rect(prect,rect1,rect2) && y_null_intersect_rect(prect,rect1,rect2))
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      null(prect);
//
//      return false;
//
//   }
//
//}
//
//
//bool x_left_null_intersect_rect(RECT32 * prect,const rect & rect1,const rect & rect2)
//{
//
//   prect->left    = max(rect1.left,rect2.left);
//
//   prect->right   = min(rect1.right,rect2.right);
//
//   if(prect->right > prect->left || (prect->right == prect->left && rect1.left == rect2.left))
//   {
//
//      return true;
//
//   }
//   else
//   {
//
//      prect->left = 0;
//
//      prect->right = 0;
//
//      return false;
//
//   }
//
//}
//
//
//bool y_top_null_intersect_rect(RECT32 * prect,const rect & rect1, const rect & rect2)
//{
//
//   prect->top     = max(rect1.top, rect2.top);
//
//   prect->bottom  = min(rect1.bottom, rect2.bottom);
//
//   if(prect->top < prect->bottom || (prect->top == prect->bottom && rect1.top == rect2.top))
//   {
//
//      return true;
//
//   }
//   else
//   {
//      prect->top = 0;
//
//      prect->bottom= 0;
//
//      return false;
//   }
//
//}
//
//
//CLASS_DECL_ACME bool top_left_null_intersect_rect(RECT32 * prect,const rect & rect1,const rect & rect2)
//
//{
//   if(x_left_null_intersect_rect(prect,rect1,rect2)
//
//         && y_top_null_intersect_rect(prect,rect1,rect2))
//
//   {
//      return true;
//   }
//   else
//   {
//      null(prect);
//
//      return false;
//   }
//}
//
//bool copy(RECTD * prectDest, const RECTD * prectSrc)
//{
//   *prectDest = *prectSrc;
//   return TRUE;
//}
//
//bool copy(RECTD * prectDest, const ::rect & prectSrc)
//{
//   prectDest->left      = prectSrc->left;
//   prectDest->top       = prectSrc->top;
//   prectDest->right     = prectSrc->right;
//   prectDest->bottom    = prectSrc->bottom;
//   return TRUE;
//}
//
//bool copy(RECT32 * prectDest, const RECTD * prectSrc)
//{
//   if(!is32integer(prectSrc->left) || !is32integer(prectSrc->top) || !is32integer(prectSrc->right) || !is32integer(prectSrc->bottom))
//      return FALSE;
//   prectDest->left      = (::i32) prectSrc->left;
//   prectDest->top       = (::i32) prectSrc->top;
//   prectDest->right     = (::i32) prectSrc->right;
//   prectDest->bottom    = (::i32) prectSrc->bottom;
//   return TRUE;
//}
//
//bool copy(RECTD * prectDest, const RECT64 * prectSrc)
//{
//   if(!is_double(prectSrc->left) || !is_double(prectSrc->top) || !is_double(prectSrc->right) || !is_double(prectSrc->bottom))
//      return FALSE;
//   prectDest->left      = (double) prectSrc->left;
//   prectDest->top       = (double) prectSrc->top;
//   prectDest->right     = (double) prectSrc->right;
//   prectDest->bottom    = (double) prectSrc->bottom;
//   return TRUE;
//}
//
//bool copy(RECT64 * prectDest, const RECTD * prectSrc)
//{
//   prectDest->left      = (::i32) prectSrc->left;
//   prectDest->top       = (::i32) prectSrc->top;
//   prectDest->right     = (::i32) prectSrc->right;
//   prectDest->bottom    = (::i32) prectSrc->bottom;
//   return TRUE;
//}
//bool is_empty(const RECTD * prect)
//{
//   return
//   prect->left   >= prect->right
//   && prect->top >= prect->bottom;
//}
//
//bool contains(const RECTD * prect, POINTD point)
//{
//   return
//   point.x >= prect->left && point.x <= prect->right
//   && point.y >= prect->top && point.y <= prect->bottom;
//}
//bool set_rect(RECTD * prectDest, double x1, double y1, double x2, double y2)
//{
//   prectDest->left      = x1;
//   prectDest->top       = y1;
//   prectDest->right     = x2;
//   prectDest->bottom    = y2;
//   return TRUE;
//}
//bool null(RECTD * prectDest)
//{
//   prectDest->left      = 0;
//   prectDest->top       = 0;
//   prectDest->right     = 0;
//   prectDest->bottom    = 0;
//   return true;
//}
//bool is_equal(const RECTD * prect1, const RECTD * prect2)
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
//bool inflate(RECTD * prect, double x, double y)
//{
//
//   prect->left      -= x;
//   prect->top       -= y;
//   prect->right     += x;
//   prect->bottom    += y;
//   return true;
//
//}
//
//
//bool deflate(RECTD * prect, double x, double y)
//{
//
//   prect->left      += x;
//   prect->top       += y;
//   prect->right     -= x;
//   prect->bottom    -= y;
//   return true;
//
//}
//
//
//bool offset(RECTD * prect, double x, double y)
//{
//
//   prect->left      += x;
//   prect->top       += y;
//   prect->right     += x;
//   prect->bottom    += y;
//   return true;
//
//}
//
//
//bool x_intersect_rect(RECTD * prect, const RECTD * prect1, const RECTD * prect2)
//{
//   prect->left    = max(prect1->left, prect2->left);
//   prect->right   = min(prect1->right, prect2->right);
//   if(prect->right > prect->left)
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
//bool y_intersect_rect(RECTD * prect, const RECTD * prect1, const RECTD * prect2)
//{
//   prect->top     = max(prect1->top, prect2->top);
//   prect->bottom  = min(prect1->bottom, prect2->bottom);
//   if(prect->top < prect->bottom)
//   {
//      return true;
//   }
//   else
//   {
//      null(prect);
//      return false;
//   }
//}
//
//
//
//
//bool x_null_intersect_rect(RECTD * prect,const RECTD * prect1,const RECTD * prect2)
//{
//   prect->left    = max(prect1->left,prect2->left);
//   prect->right   = min(prect1->right,prect2->right);
//   if(prect->right >= prect->left)
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
//bool y_null_intersect_rect(RECTD * prect,const RECTD * prect1,const RECTD * prect2)
//{
//   prect->top     = max(prect1->top,prect2->top);
//   prect->bottom  = min(prect1->bottom,prect2->bottom);
//   if(prect->top <= prect->bottom)
//   {
//      return true;
//   }
//   else
//   {
//      null(prect);
//      return false;
//   }
//}
//
//
//bool intersect(RECTD * prect, const RECTD * prect1, const RECTD * prect2)
//{
//   if(x_intersect_rect(prect, prect1, prect2)
//         && y_intersect_rect(prect, prect1, prect2))
//   {
//      return true;
//   }
//   else
//   {
//      null(prect);
//      return false;
//   }
//}
//
//
//bool unite(RECTD * prect, const RECTD * prect1, const RECTD * prect2)
//{
//   if(is_empty(prect1))
//   {
//      if(is_empty(prect2))
//      {
//         null(prect);
//         return false;
//      }
//      else
//      {
//         *prect =* prect2;
//         return true;
//      }
//   }
//   else if(is_empty(prect2))
//   {
//      *prect = *prect1;
//      return true;
//   }
//   prect->left    = min(prect1->left, prect2->left);
//   prect->right   = max(prect1->right, prect2->right);
//   prect->top     = min(prect1->top, prect2->top);
//   prect->bottom  = max(prect1->bottom, prect2->bottom);
//   if(prect->right > prect->left &&
//         prect->bottom > prect->top)
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
//CLASS_DECL_ACME double width(const ::rectd & rect)
//
//{
//   return pcrect->right - pcrect->left;
//
//}
//
//CLASS_DECL_ACME double height(const ::rectd & rect)
//
//{
//   return pcrect->bottom - pcrect->top;
//
//}
//
//CLASS_DECL_ACME double width(const ::rectd & rect)
//{
//   return ::width(&rect);
//}
//
//CLASS_DECL_ACME double height(const ::rectd & rect)
//{
//   return ::height(&rect);
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
//bool copy(RECT64 * prectDest, const RECT64 * prectSrc)
//{
//   *prectDest = *prectSrc;
//   return TRUE;
//}
//
//bool copy(RECT64 * prectDest, const ::rect & prectSrc)
//{
//   prectDest->left      = prectSrc->left;
//   prectDest->top       = prectSrc->top;
//   prectDest->right     = prectSrc->right;
//   prectDest->bottom    = prectSrc->bottom;
//   return TRUE;
//}
//
//bool copy(RECT32 * prectDest, const RECT64 * prectSrc)
//{
//   if(!is32integer(prectSrc->left) || !is32integer(prectSrc->top) || !is32integer(prectSrc->right) || !is32integer(prectSrc->bottom))
//      return FALSE;
//   prectDest->left      = (::i32) prectSrc->left;
//   prectDest->top       = (::i32) prectSrc->top;
//   prectDest->right     = (::i32) prectSrc->right;
//   prectDest->bottom    = (::i32) prectSrc->bottom;
//   return TRUE;
//}
//bool is_empty(const RECT64 * prect)
//{
//   return
//   prect->left   >= prect->right
//   && prect->top >= prect->bottom;
//}
//
//
//bool contains(const RECT64 * prect, point64 point)
//{
//
//   return
//   point.x >= prect->left && point.x <= prect->right
//   && point.y >= prect->top && point.y <= prect->bottom;
//
//}
//
//bool set_rect(RECT64 * prectDest, i64 x1, i64 y1, i64 x2, i64 y2)
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
//bool null(RECT64 * prectDest)
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
//bool is_equal(const RECT64 * prect1, const RECT64 * prect2)
//{
//   return
//   prect1->left      == prect2->left &&
//   prect1->top       == prect2->top &&
//   prect1->right     == prect2->right &&
//   prect1->bottom    == prect2->bottom;
//}
//
//bool inflate(RECT64 * prect, i64 x, i64 y)
//{
//
//   prect->left      -= x;
//   prect->top       -= y;
//   prect->right     += x;
//   prect->bottom    += y;
//   return true;
//
//}
//
//bool deflate(RECT64 * prect, i64 x, i64 y)
//{
//
//   prect->left      += x;
//   prect->top       += y;
//   prect->right     -= x;
//   prect->bottom    -= y;
//   return true;
//
//}
//
//
//bool offset(RECT64 * prect, i64 x, i64 y)
//{
//
//   prect->left      += x;
//   prect->top       += y;
//   prect->right     += x;
//   prect->bottom    += y;
//   return true;
//
//}
//
//
//bool resize(RECT64 * prect,i64 cx,i64 cy)
//{
//   prect->right     = prect->left + cx;
//   prect->bottom    = prect->top + cy;
//   return true;
//
//}
//
//
//bool reverse_size(RECT64 * prect,i64 cx,i64 cy)
//{
//
//   prect->left      = prect->right  - cx;
//   prect->top       = prect->bottom - cy;
//   return true;
//
//}
//
//bool x_intersect_rect(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2)
//{
//
//   prect->left    = max(prect1->left, prect2->left);
//   prect->right   = min(prect1->right, prect2->right);
//
//   if(prect->right > prect->left)
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
//bool y_intersect_rect(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2)
//{
//   prect->top     = max(prect1->top, prect2->top);
//   prect->bottom  = min(prect1->bottom, prect2->bottom);
//   if(prect->top < prect->bottom)
//   {
//      return true;
//   }
//   else
//   {
//      null(prect);
//      return false;
//   }
//
//}
//
//
//bool intersect(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2)
//{
//   if(x_intersect_rect(prect, prect1, prect2)
//         && y_intersect_rect(prect, prect1, prect2))
//   {
//      return true;
//   }
//   else
//   {
//      null(prect);
//      return false;
//   }
//
//}
//
//
//bool unite(RECT64 * prect, const RECT64 * prect1, const RECT64 * prect2)
//{
//   if(is_empty(prect1))
//   {
//      if(is_empty(prect2))
//      {
//         null(prect);
//         return false;
//      }
//      else
//      {
//         *prect =* prect2;
//         return TRUE;
//      }
//   }
//   else if(is_empty(prect2))
//   {
//      *prect = *prect1;
//      return true;
//   }
//   prect->left    = min(prect1->left, prect2->left);
//   prect->right   = max(prect1->right, prect2->right);
//   prect->top     = min(prect1->top, prect2->top);
//   prect->bottom  = max(prect1->bottom, prect2->bottom);
//   if(prect->right > prect->left &&
//         prect->bottom > prect->top)
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
//CLASS_DECL_ACME bool deflate(RECT32 * prect, const ::rect & rect)
//
//{
//   prect->left    += pcrect->left;
//
//   prect->right   -= pcrect->right;
//
//   prect->top     += pcrect->top;
//
//   prect->bottom  -= pcrect->bottom;
//
//   return true;
//}
//
//CLASS_DECL_ACME bool deflate(RECT32 * prect,const ::rect & rect)
//{
//   return deflate(prect, &rect);
//}
//
//
//
//CLASS_DECL_ACME bool copy(POINT64 * pptDst,const point & pointSrc)
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
//CLASS_DECL_ACME bool copy(POINT32 * pptDst,const POINT64 * lpptSrc)
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
//void copy(CGRect & rectDst, const rect & rectSrc)
//{
//   rectDst.origin.x = rectSrc.left;
//   rectDst.origin.y = rectSrc.top;
//   rectDst.size.width = width(rectSrc);
//   rectDst.size.height = height(rectSrc);
//
//}
//
//
//void copy(RECT32 * prectDst, const CGRect & rectSrc)
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
//void copy(CGRect & rect, const ::rect & rect)
//
//{
//
//   rect.origin.x = pcrect->left;
//
//   rect.origin.y = pcrect->top;
//
//   rect.size.width = width(pcrect);
//
//   rect.size.height = height(pcrect);
//
//
//
//}
//
//#endif
//
//
//CLASS_DECL_ACME int_bool IsRectEmpty(const ::rect & rect)
//{
//
//   return IsRectEmpty((const rect &)&rect);
//
//}



