//
// crypto_initializer.h
//
// Created by camilo 2021-05-24 05:39 BRT <3ThomasBS_!!
//
#pragma once


namespace crypto
{


   class CLASS_DECL_APEX initializer :
      virtual public ::object
   {
   public:


#if OPENSSL_API_COMPAT < 0x10100000L


      string m_rand_file;
      long m_rand_size;


#endif


      initializer();
      ~initializer() override;


      void DeleteRandFile();


   };


} // namespace crypto



