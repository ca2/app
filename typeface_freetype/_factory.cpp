// Created by camilo on 2026-01-06 22:23 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "allocator.h"


__FACTORY_EXPORT void typeface_freetype_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::typeface_freetype::allocator, ::typeface::allocator>();

}



