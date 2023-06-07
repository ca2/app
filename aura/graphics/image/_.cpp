//
// Created by camilo on 2022-10-22 14:26 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pixmap.h"
#include "acme/primitive/geometry2d/_geometry2d.h"


CLASS_DECL_AURA void copy_colorref(::color32_t * pcolorrefDst, const ::point_i32 & point, const ::size_i32 & size, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc)
{

   byte * pDst = (byte *)pcolorrefDst;

   return copy_colorref((::color32_t *)pDst + point.x() * sizeof(::color32_t) + point.y() * iStrideDst, size.cx(), size.cy(), iStrideDst, pcolorrefSrc, iStrideSrc);

}


CLASS_DECL_AURA void copy_colorref(::color32_t * pcolorrefDst, const ::rectangle_i32 & rectangle, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc)
{

   return copy_colorref(pcolorrefDst, rectangle.top_left(), rectangle.size(), iStrideDst, pcolorrefSrc, iStrideSrc);

}
