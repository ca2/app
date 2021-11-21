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


__FACTORY_EXPORT void imaging_freeimage_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::imaging_freeimage::context_image, ::context_image >();

}



