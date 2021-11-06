#include "framework.h"


//namespace imaging_freeimage
//{
//
//
//#define new ACME_NEW
//
//
//   factory_exchange::factory_exchange()
//   {
//
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//
//} // namespace imaging_freeimage


extern "C"
void imaging_freeimage_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::imaging_freeimage::context_image, ::context_image >();

}



