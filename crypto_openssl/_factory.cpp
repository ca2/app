#include "framework.h"


__FACTORY_EXPORT void crypto_openssl_factory(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::crypto_openssl::crypto, ::crypto::crypto >();
   pfactory->add_factory_item < ::crypto_openssl::initializer, ::crypto::initializer >();
   pfactory->add_factory_item < ::crypto_openssl::hasher_algorithm, ::crypto::hasher_algorithm >();

   
}



