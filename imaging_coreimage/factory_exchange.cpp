#include "framework.h"


//namespace coreimage_imaging
//{
//
//
//#define new AURA_NEW
//
//
//   factory_exchange::factory_exchange()
//   {
//
//      create_factory < imaging, ::imaging >();
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
//} // namespace coreimage_imaging


extern "C"
void imaging_factory_exchange()
{

   create_factory < ::coreimage_imaging::imaging, ::imaging >();
   //coreimage_imaging::factory_exchange factoryexchange;

}



