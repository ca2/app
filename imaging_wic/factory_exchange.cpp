#include "framework.h"


namespace imaging_wic
{

   class factory_exchange
   {
   public:

      
      factory_exchange();
      virtual ~factory_exchange();

   };


//#define new ACME_NEW
//
//
   factory_exchange::factory_exchange()
   {

      create_factory < ::imaging_wic::context_image, ::context_image >();

   }

//
   factory_exchange::~factory_exchange()
   {

   }
//
//
} // namespace imaging_wic
//

extern "C"
void imaging_wic_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::imaging_wic::context_image, ::context_image >();

}




//imaging_wic::factory_exchange g_imagingwicfactoryexchange;