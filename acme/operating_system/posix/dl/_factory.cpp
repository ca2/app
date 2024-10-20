// From idn on 2024-06-02 19:42 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano_dynamic_library_dl.h"


IMPLEMENT_FACTORY(nano_dynamic_library)
{

   pfactory->add_factory_item < ::dl::nano::dynamic_library::dynamic_library, ::nano::dynamic_library::dynamic_library >();

}

