#include "framework.h"


CLASS_DECL_COMPRESS_ZLIB void compress_zlib_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::compress_zlib::compress, ::compress >();
   pfactory->add_factory_item < ::compress_zlib::uncompress, ::uncompress >();
   
}



