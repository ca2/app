#pragma once


//#if defined(HAVE_OPENSSL)
//
//typedef struct rsa_st RSA;
//
//#define AXIS_RSA_KEY RSA *
//
//#else
//
//
//namespace crypto
//{ 
//
//   
//   class rsa;
//
//
//} // namespace crypto
//
//
//using AXIS_RSA_KEY = ::winrt::Windows::Security::Cryptography::Core::CryptographicKey^;
//
//
//#endif


#include "_.h"

CLASS_DECL_APEX i32 crypto_encrypt(memory & storageEncrypt, const memory & storageDecrypt, memory & key);

CLASS_DECL_APEX i32 crypto_decrypt(memory & storageDecrypt, const memory & storageEncrypt, memory & key);



