// Created by camilo on 2023-04-25 16:18 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano_archive_libarchive.h"

__FACTORY_EXPORT void nano_archive_libarchive_factory(::factory::factory * pfactory)
{

    pfactory->add_factory_item< ::libarchive::nano::archive::archive, ::nano::archive::archive>();

}



