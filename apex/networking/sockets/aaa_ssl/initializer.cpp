/**
 **   \file SSLInitializer.cpp
 **   \date  2007-04-30
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2007  Anders Hedstrom

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
#include "framework.h"
#include "initializer.h"
//#include "apex/networking/sockets/_sockets.h"
//
//#ifdef WINDOWS
//extern "C"
//{
//
//#include "openssl/applink.c"
// 
//} // extern "C"
//
//#endif


#ifdef PARALLELIZATION_PTHREAD


#include "acme/operating_system/ansi/_pthread.h"


#endif


#ifdef HAVE_OPENSSL
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/engine.h>
#include <openssl/conf.h>


#include <openssl/conf.h>


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)


#include "acme/operating_system/ansi/_pthread.h"

#endif



extern void *OPENSSL_UplinkTable[];


//#ifdef UNIVERSAL_WINDOWS
//extern "C"
//__declspec(dllimport)
//void OPENSSL_UplinkAll();
//#endif

namespace sockets
{



#ifdef LINUX
   // ssl_sigpipe_handle ---------------------------------------------------------
   void ssl_sigpipe_handle(int x)
   {
      /* Ignore broken pipes */
   }
#endif


   SSLInitializer::SSLInitializer()
   {

   }


   SSLInitializer::~SSLInitializer()
   {

//      BIO_free(bio_err);

//      bio_err = nullptr;
      //ENGINE_cleanup();
      //sk_SSL_COMP_free(SSL_COMP_get_compression_methods());
      //SSL_COMP_free_compression_methods(); .
      //ERR_free_strings();
      //EVP_cleanup();

//      ERR_erase_state(0);



      //EVP_cleanup();

      //ERR_free_strings();

      //CRYPTO_cleanup_all_ex_data();

      //ENGINE_cleanup();

      //CONF_modules_unload(1);

      //CONF_modules_free();

      //sk_SSL_COMP_free(SSL_COMP_get_compression_methods());

      //RAND_cleanup();

      //      information("~SSLInitializer()\n");
      //DeleteRandFile();
      // %! delete mutexes


   }


   void SSLInitializer::initialize(::particle * pparticle)
   {

      //auto estatus = ::object::initialize(pparticle);

      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //#if defined(UNIVERSAL_WINDOWS)
//
//      OPENSSL_Applink();
//
//#endif

      //information() << "SSLInitializer::SSLInitializer .1";

#if OPENSSL_VERSION_NUMBER < 0x10100000L

      ERR_load_crypto_strings();
      //SSL_load_error_strings(); // just once
      SSL_load_error_strings();
      SSL_library_init();
      OpenSSL_add_all_algorithms();
#else

      OPENSSL_init_ssl(OPENSSL_INIT_SSL_DEFAULT, nullptr);

#endif

      //information() << "SSLInitializer::SSLInitializer .2";


      //ENGINE_load_openssl();
      //ENGINE_load_dynamic();
#ifndef OPENSSL_NO_STATIC_ENGINE
      //ENGINE_load_4758cca();
      //ENGINE_load_aep();
      //ENGINE_load_atalla();
      //ENGINE_load_chil();
      //ENGINE_load_cswift();
      ////ENGINE_load_gmp();
      //ENGINE_load_nuron();
      //ENGINE_load_sureware();
      //ENGINE_load_ubsec();
#endif
      //ENGINE_load_cryptodev();
      //ENGINE_load_builtin_engines();

      //return ::success;

   }


} // namespace sockets


#endif



