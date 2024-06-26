// Created by camilo on 2024-06-02 23:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dynamic_library.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/platform/application.h"
#include "acme/_operating_system.h"


extern "C" void nano_dynamic_library_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::windows::nano::dynamic_library::dynamic_library, ::nano::dynamic_library::dynamic_library >();

}



