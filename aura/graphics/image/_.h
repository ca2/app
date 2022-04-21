// Created by camilo on 2022-03-11 08:24 PM <3ThomasBorregaardSørensen!!
#pragma once


CLASS_DECL_AURA void vertical_swap_copy_colorref(::color32_t * pcolorrefDst, int cx, int cy, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);
CLASS_DECL_AURA void copy_colorref(::color32_t * pcolorrefDst, int cx, int cy, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);
CLASS_DECL_AURA void copy_colorref(::color32_t * pcolorrefDst, int x, int y, int cx, int cy, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);


inline void copy_colorref(::color32_t * pcolorrefDst, const ::size_i32 & size, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc)
{

   copy_colorref(pcolorrefDst, size.cx, size.cy, iStrideDst, pcolorrefSrc, iStrideSrc);

}



