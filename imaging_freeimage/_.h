#pragma once


#include "aura/_.h"
#include "aura/operating_system.h"



#ifdef _IMAGING_FREEIMAGE_STATIC
#define CLASS_DECL_IMAGING_FREEIMAGE
#elif defined(_IMAGING_FREEIMAGE_LIBRARY)
#define CLASS_DECL_IMAGING_FREEIMAGE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_IMAGING_FREEIMAGE  CLASS_DECL_IMPORT
#endif


#if defined(LINUX) || defined(FREEBSD)

#undef _WINDOWS_
// apt install libfreeimage-dev
// dnf install freeimage-devel
// zypper install freeimage-devel
// pacman -S freeimage
// pkg install freeimage
#include <FreeImage.h>

#else

#include "FreeImage/FreeImage.h"

#endif


namespace imaging_freeimage
{


   CLASS_DECL_IMAGING_FREEIMAGE FIBITMAP * freeimage_from_image(const ::image * pimage);
   CLASS_DECL_IMAGING_FREEIMAGE bool image_from_freeimage(::image * pimage, FIBITMAP * pfibitmap);


} // namespace imaging_freeimage

#include "fimemory.h"







//
//inline auto gdiplus_color(const ::color::color& color)
//{
//
//   return Gdiplus::Color(color.m_iA, color.m_iR, color.m_iG, color.m_iB);
//
//}
//
#include "factory_exchange.h"


#include "context_image.h"



