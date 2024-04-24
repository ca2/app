#include "framework.h"
#include "compress.h"
#include "uncompress.h"
#include "acme/primitive/primitive/factory.h"


__FACTORY_EXPORT void compress_zlib_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::compress_zlib::compress, ::compress >();
   pfactory->add_factory_item < ::compress_zlib::uncompress, ::uncompress >();
   
}



