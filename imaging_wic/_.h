#pragma once


#include "aura/_.h"
#include <wincodec.h>


#ifdef _IMAGING_WIC_STATIC
#define CLASS_DECL_IMAGING_WIC
#elif defined(_IMAGING_WIC_LIBRARY)
#define CLASS_DECL_IMAGING_WIC  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_IMAGING_WIC  CLASS_DECL_IMPORT
#endif




namespace imaging_wic
{


   comptr < IWICImagingFactory > get_imaging_factory();


   CLASS_DECL_IMAGING_WIC bool node_save_image(comptr < IStream > pstream, const ::image * pimage, ::save_image * psaveimage);


#ifdef _UWP
   
   
   CLASS_DECL_IMAGING_WIC bool node_save_image(Windows::Storage::Streams::IRandomAccessStream ^ stream, const ::image * pimage, ::save_image * psaveimage);


#endif


} // namespace imaging_wic


#include "factory_exchange.h"


comptr < IWICImagingFactory > wic_get_imaging_factory();


#include "imaging.h"

