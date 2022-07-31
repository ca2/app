#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


__FACTORY_EXPORT void compress_zlib_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::compress_zlib::compress, ::compress >();
   pfactory->add_factory_item < ::compress_zlib::uncompress, ::uncompress >();
   
}



