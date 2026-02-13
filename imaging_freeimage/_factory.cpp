#include "framework.h"
#include "image_context.h"


//namespace imaging_freeimage
//{
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

   pfactory->add_factory_item < ::imaging_freeimage::image_context, ::image::image_context >();

}



