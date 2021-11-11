#include "framework.h"


extern "C"
void crypto_openssl_factory_exchange(::factory_map * pfactorymap)
{


   pfactorymap->create_factory < ::crypto_openssl::crypto, ::crypto::crypto >();
   pfactorymap->create_factory < ::crypto_openssl::hasher_algorithm, ::crypto::hasher_algorithm >();

   
}



