#include "framework.h"
#include "compress.h"
#include "uncompress.h"



CLASS_DECL_COMPRESS_BZIP2 void compress_bzip2_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::compress_bzip2::compress, ::compress >();
   pfactory->add_factory_item < ::compress_bzip2::uncompress, ::uncompress >();
   
}



