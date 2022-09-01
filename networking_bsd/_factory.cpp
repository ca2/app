#include "framework.h"
#include "address.h"
#include "hasher_algorithm.h"
#include "initializer.h"


__FACTORY_EXPORT void networking_bsd_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::networking_bsd::address, ::networking::address >();

   pfactory->add_factory_item < ::networking_bsd::networking, ::networking::networking >();
   pfactory->add_factory_item < ::crypto_openssl::initializer, ::crypto::initializer >();
   pfactory->add_factory_item < ::crypto_openssl::hasher_algorithm, ::crypto::hasher_algorithm >();

   
}



