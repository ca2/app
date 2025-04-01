// Created by camilo on 2022-11-08 23:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "color_indexes.h"


//#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD) || defined(OPENBSD)
//
//
//#define IMAGE_ARGB(a, r, g, b)         ((::color::color)((lower_byte(b)|((unsigned short)(lower_byte(g))<<8))|(((unsigned int)lower_byte(r))<<16)|(((unsigned int)lower_byte(a))<<24)))
//
//
//#define image_r_value(rgb)    (lower_byte((rgb)>>16))
//#define image_g_value(rgb)    (lower_byte((rgb)>>8))
//#define image_b_value(rgb)    (lower_byte((rgb)))
//#define image_a_value(rgb)    (lower_byte((rgb)>>24))
//
//
//#else
//
//
//#define IMAGE_ARGB(a, r, g, b)         ((::color::color)((lower_byte(r)|((unsigned short)(lower_byte(g))<<8))|(((unsigned int)lower_byte(b))<<16)|(((unsigned int)lower_byte(a))<<24)))
//
//
//#define image_r_value(rgb)    (lower_byte((rgb)))
//#define image_g_value(rgb)    (lower_byte((rgb)>>8))
//#define image_b_value(rgb)    (lower_byte((rgb)>>16))
//#define image_a_value(rgb)    (lower_byte((rgb)>>24))
//
//
//#endif


#ifdef __APPLE__


#define IMAGE_Y(y, h) ((h) - (y) - 1)


#else


#define IMAGE_Y(y, h) (y)


#endif


#if defined(WINDOWS) || defined(LINUX) || defined(__i386__) || defined(FREEBSD) || defined(OPENBSD)


constexpr inline color_indexes common_system_image_color_indexes() { return bgra_indexes(); }

#elif defined(__APPLE__)

constexpr inline color_indexes common_system_image_color_indexes() { return rbga_indexes(); }

#else


constexpr inline color_indexes common_system_image_color_indexes() { return rgba_indexes(); }


#endif



