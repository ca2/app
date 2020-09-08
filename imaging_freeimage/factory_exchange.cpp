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
void imaging_factory_exchange()
{

   create_factory < ::imaging_freeimage::imaging, ::imaging >();

}



