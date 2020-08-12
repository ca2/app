#include "framework.h"


namespace imaging_wic
{

   class factory_exchange
   {
   public:

      
      factory_exchange();
      virtual ~factory_exchange();

   };


//#define new AURA_NEW
//
//
   factory_exchange::factory_exchange()
   {

      create_factory < ::imaging_wic::imaging, ::imaging >();

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
void imaging_factory_exchange()
{

   create_factory < ::imaging_wic::imaging, ::imaging >();

}


#ifdef CUBE

void initialize_imaging_factory_exchange()
{

   g_pfnfactoryexchangeImaging = &imaging_factory_exchange;

}

#endif



imaging_wic::factory_exchange g_imagingwicfactoryexchange;