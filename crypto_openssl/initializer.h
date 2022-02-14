//
// crypto_initializer.h
//
// Created by camilo 2021-05-24 05:39 BRT <3ThomasBS_!!
// Refactored to crypto_openssl by camilo 2021-11-19 14:20 BRT <3ThomasBS_!!
//
#pragma once


namespace crypto_openssl
{


   class CLASS_DECL_CRYPTO_OPENSSL initializer :
      virtual public ::crypto::initializer
   {
   public:


      __creatable_from_library(initializer, ::crypto::initializer, "crypto_openssl");


#if OPENSSL_VERSION_NUMBER < 0x10100000L


      string m_rand_file;
      long m_rand_size;


#endif


      initializer();
      ~initializer() override;


#if OPENSSL_VERSION_NUMBER < 0x10100000L

      void DeleteRandFile();

#endif


   };


} // namespace crypto_openssl



