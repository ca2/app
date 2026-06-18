//
// Created by camilo on 2025-07-11 05:26 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "compress.h"



__FACTORY_EXPORT void nano_compress_windows_factory(::factory::factory * pfactory)
{

    pfactory->add_factory_item<::windows_common::nano::compress::compress, ::nano::compress::compress>();

}



