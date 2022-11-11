// Created by camilo on 2021-11-10 10:33 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/_.h"
#ifdef MACOS
#include <Carbon/Carbon.h>
#endif


#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>



#if defined(_CRYPTO_OPENSSL_LIBRARY)
#define CLASS_DECL_CRYPTO_OPENSSL  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_CRYPTO_OPENSSL  CLASS_DECL_IMPORT
#endif


#define HAVE_OPENSSL 1


namespace crypto_openssl
{


   class hasher;
   class hasher_algorithm;
   class crypto;


} // namespace crypto_openssl



