#pragma once


#include "aura/_.h"





#ifdef _COREIMAGE_IMAGING_STATIC
#define CLASS_DECL_COREIMAGE_IMAGING
#elif defined(_COREIMAGE_IMAGING_LIBRARY)
#define CLASS_DECL_COREIMAGE_IMAGING  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_COREIMAGE_IMAGING  CLASS_DECL_IMPORT
#endif


//namespace coreimage_imaging
//{
//
//
//   CLASS_DECL_COREIMAGE_IMAGING FIBITMAP * coreimage_from_image(const ::image * pimage);
//   CLASS_DECL_COREIMAGE_IMAGING bool image_from_coreimage(::image * pimage, FIBITMAP * pfibitmap);
//
//
//} // namespace coreimage_imaging
//
//#include "fimemory.h"

//
//inline auto gdiplus_color(const ::color& color)
//{
//
//   return Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB);
//
//}
//

#ifdef __OBJC__

#else

#include "factory_exchange.h"


#include "imaging.h"

#endif



