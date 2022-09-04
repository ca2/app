// Created by camilo on 2022-03-11 08:24 PM <3ThomasBorregaardSørensen!!
#pragma once


class imaging;
class image_drawing;
class image_drawing_options;
class image_frame;
class image_frame_array;
class save_image;
class image_list;


using image_list_pointer = __pointer(::image_list);


CLASS_DECL_AURA void vertical_swap_copy_colorref(::color32_t * pcolorrefDst, int cx, int cy, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);
CLASS_DECL_AURA void copy_colorref(::color32_t * pcolorrefDst, int cx, int cy, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);
CLASS_DECL_AURA void copy_colorref(::color32_t * pcolorrefDst, int x, int y, int cx, int cy, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);


CLASS_DECL_AURA void copy_colorref(::color32_t * pcolorrefDst, const ::size_i32 & size, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);


