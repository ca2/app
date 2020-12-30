#pragma once


#include "aura/_.h"




#ifdef _IMAGING_FREEIMAGE_STATIC
#define CLASS_DECL_IMAGING_FREEIMAGE
#elif defined(_IMAGING_FREEIMAGE_LIBRARY)
#define CLASS_DECL_IMAGING_FREEIMAGE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_IMAGING_FREEIMAGE  CLASS_DECL_IMPORT
#endif



//
//inline auto gdiplus_color(const ::color& color)
//{
//
//   return Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB);
//
//}
//
#include "factory_exchange.h"


#include "context_image.h"



