#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


//BEGIN_FACTORY(crypto_openssl)
//FACTORY_ITEM(::crypto_openssl::crypto)
//FACTORY_ITEM(::crypto_openssl::initializer)
//FACTORY_ITEM(::crypto_openssl::hasher_algorithm)
//END_FACTORY()


__FACTORY_EXPORT void crypto_openssl_factory(::factory::factory * pfactory)
{


   pfactory->add_factory_item < ::crypto_openssl::crypto, ::crypto::crypto >();
   pfactory->add_factory_item < ::crypto_openssl::initializer, ::crypto::initializer >();
   pfactory->add_factory_item < ::crypto_openssl::hasher_algorithm, ::crypto::hasher_algorithm >();

   
}



