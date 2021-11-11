#include "framework.h"


extern "C"
void folder_zip_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::folder_zip::folder, ::folder >();
   
}



