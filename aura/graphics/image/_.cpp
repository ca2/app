//
// Created by camilo on 2022-10-22 14:26 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pixmap.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"


CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const ::point_i32 & point, const ::size_i32 & size, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   ::u8 * pDst = (::u8 *)pimage32Dst;

   return copy_image32((::image32_t *)pDst + point.x() * sizeof(::image32_t) + point.y() * iStrideDst, size.cx(), size.cy(), iStrideDst, pimage32Src, iStrideSrc);

}


CLASS_DECL_AURA void copy_image32(::image32_t * pimage32Dst, const ::rectangle_i32 & rectangle, int iStrideDst, const ::image32_t * pimage32Src, int iStrideSrc)
{

   return copy_image32(pimage32Dst, rectangle.top_left(), rectangle.size(), iStrideDst, pimage32Src, iStrideSrc);

}
