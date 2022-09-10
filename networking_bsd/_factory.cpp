#include "framework.h"
#include "address.h"
#include "networking.h"


__FACTORY_EXPORT void networking_bsd_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::networking_bsd::address, ::networking::address >();

   pfactory->add_factory_item < ::networking_bsd::networking, ::networking::networking >();

   
}



