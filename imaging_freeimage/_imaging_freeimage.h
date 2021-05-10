#pragma once


#ifdef LINUX

#undef _WINDOWS_
// dnf install freeimage-devel
// zypper install freeimage-devel
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

