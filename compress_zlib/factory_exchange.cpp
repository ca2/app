#include "framework.h"


extern "C"
void compress_zlib_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::compress_zlib::compress, ::compress >();
   pfactorymap->create_factory < ::compress_zlib::uncompress, ::uncompress >();
   
}



