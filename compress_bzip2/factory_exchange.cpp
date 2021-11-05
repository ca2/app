#include "framework.h"


extern "C"
void compress_bzip2_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::compress_bz, ::object >();
   
}



