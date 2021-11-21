#include "framework.h"


__FACTORY_EXPORT void compress_bzip2_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::compress_bzip2::compress, ::compress >();
   pfactory->add_factory_item < ::compress_bzip2::uncompress, ::uncompress >();
   
}



