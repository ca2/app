// Created by camilo on 2022-11-08 23:35 <3ThomasBorregaardSorensen!!
#pragma once


#define NOK_IMAGE (::e_flag_none)
#define OK_IMAGE (::e_flag_success)
#define DEFAULT_CREATE_IMAGE_FLAG (::e_flag_success)


#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD)


#define IMAGE_ARGB(a, r, g, b)         ((::color::color)((low_byte(b)|((::u16)(low_byte(g))<<8))|(((u32)low_byte(r))<<16)|(((u32)low_byte(a))<<24)))


#define image_r_value(rgb)    (low_byte((rgb)>>16))
#define image_g_value(rgb)    (low_byte((rgb)>>8))
#define image_b_value(rgb)    (low_byte((rgb)))
#define image_a_value(rgb)    (low_byte((rgb)>>24))


#else


#define IMAGE_ARGB(a, r, g, b)         ((::color::color)((low_byte(r)|((::u16)(low_byte(g))<<8))|(((u32)low_byte(b))<<16)|(((u32)low_byte(a))<<24)))


#define image_r_value(rgb)    (low_byte((rgb)))
#define image_g_value(rgb)    (low_byte((rgb)>>8))
#define image_b_value(rgb)    (low_byte((rgb)>>16))
#define image_a_value(rgb)    (low_byte((rgb)>>24))


#endif







#ifdef __APPLE__


#define IMAGE_Y(y, h) ((h) - (y) - 1)


#else


#define IMAGE_Y(y, h) (y)


#endif
