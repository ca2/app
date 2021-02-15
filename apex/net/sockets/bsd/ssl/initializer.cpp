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
#include "apex/net/sockets/_sockets.h"
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


#include "acme/os/ansios/_pthread.h"


#endif


#ifdef HAVE_OPENSSL
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/engine.h>
#include <openssl/conf.h>


#include <openssl/conf.h>



#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

#include "acme/os/ansios/_pthread.h"

#endif



extern void *OPENSSL_UplinkTable[];

extern "C" void SSLInitializer_SSL_locking_function(i32 mode, i32 n, const char * file, i32 line);
extern "C" unsigned long SSLInitializer_SSL_id_function();
extern "C"
#if defined(_UWP) && (!defined(RASPBIAN))
void
#else
int
#endif
SSLInitializer_rand_seed(const void * buf, i32 num);
extern "C" i32 SSLInitializer_rand_bytes(uchar * buf, i32 num);
extern "C" void SSLInitializer_rand_cleanup();
extern "C"
#if defined(_UWP) && (!defined(RASPBIAN))
void
#else
int
#endif
SSLInitializer_rand_add(const void * buf, int num, double entropy);
extern "C" i32 SSLInitializer_rand_pseudorand(uchar * buf, i32 num);
extern "C" i32 SSLInitializer_rand_status();

//#ifdef _UWP
//extern "C"
//__declspec(dllimport)
//void OPENSSL_UplinkAll();
//#endif

namespace sockets
{

#if OPENSSL_API_COMPAT < 0x10100000L

   map < i32, ::mutex * >  * g_pmapMutex = nullptr;

   ::mutex * g_pmutexMap = nullptr;

#endif

#ifdef LINUX
   // ssl_sigpipe_handle ---------------------------------------------------------
   void ssl_sigpipe_handle(int x)
   {
      /* Ignore broken pipes */
   }
#endif


#if OPENSSL_API_COMPAT < 0x10100000L

   RAND_METHOD rand_meth;

#endif

   SSLInitializer::SSLInitializer(::layered * pobjectContext) :
      ::object(pobjectContext)
   {

//#if defined(_UWP)
//
//      OPENSSL_Applink();
//
//#endif

      INFO("SSLInitializer::SSLInitializer .1");

#if OPENSSL_API_COMPAT < 0x10100000L

      m_rand_size = 1024;

      g_pmapMutex = new map < i32, ::mutex *>;

      g_pmutexMap = new ::mutex();

      CRYPTO_set_locking_callback(SSLInitializer_SSL_locking_function);
      CRYPTO_set_id_callback(SSLInitializer_SSL_id_function);

      SSL_load_error_strings();
      SSL_library_init();
#else

      //OPENSSL_init_ssl(OPENSSL_INIT_SSL_DEFAULT, nullptr);

#endif

      INFO("SSLInitializer::SSLInitializer .2");

#if OPENSSL_API_COMPAT < 0x10100000L

      rand_meth.add = &SSLInitializer_rand_add;
      rand_meth.bytes = &SSLInitializer_rand_bytes;
      rand_meth.cleanup = &SSLInitializer_rand_cleanup;
      rand_meth.pseudorand = &SSLInitializer_rand_pseudorand;
      rand_meth.seed = &SSLInitializer_rand_seed;
      rand_meth.status = &SSLInitializer_rand_status;

      RAND_set_rand_method(&rand_meth);

#endif


      //if (!initialized)
      {
         RAND_poll();
         // initialized = 1;
      }

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

//      ERR_remove_state(0);



      //EVP_cleanup();

      //ERR_free_strings();

      //CRYPTO_cleanup_all_ex_data();

      //ENGINE_cleanup();

      //CONF_modules_unload(1);

      //CONF_modules_free();

      //sk_SSL_COMP_free(SSL_COMP_get_compression_methods());

      //RAND_cleanup();

      //      TRACE("~SSLInitializer()\n");
      //DeleteRandFile();
      // %! delete mutexes

#if OPENSSL_API_COMPAT < 0x10100000L

      if (g_pmapMutex != nullptr)
      {

         for (auto i : *g_pmapMutex)
         {

            delete i.element2();

         }
         delete g_pmapMutex;

         g_pmapMutex = nullptr;
      }

      if (g_pmutexMap != nullptr)
      {
         delete g_pmutexMap;

         g_pmutexMap = nullptr;
      }

#endif

   }


   void SSLInitializer::DeleteRandFile()
   {

#if OPENSSL_API_COMPAT < 0x10100000L

      if (m_rand_file.get_length())
      {

         get_context()->file().del(m_rand_file);

      }

#endif

   }


} // namespace sockets

#if OPENSSL_API_COMPAT < 0x10100000L
extern "C" void SSLInitializer_SSL_locking_function(i32 mode, i32 n, const char * file, i32 line)
{

   UNREFERENCED_PARAMETER(file);

   UNREFERENCED_PARAMETER(line);

   synchronization_lock synchronizationlock(::sockets::g_pmutexMap);

   ::mutex * pmutex = nullptr;

   if (::sockets::g_pmapMutex != nullptr && !::sockets::g_pmapMutex->lookup(n, pmutex))
   {

      ::sockets::g_pmapMutex->operator [](n) = new ::mutex();

      if (!::sockets::g_pmapMutex->lookup(n, pmutex))
      {

         return;

      }

   }

   if (pmutex == nullptr)
   {

      return;

   }

   synchronizationlock.unlock();

   if (mode & CRYPTO_LOCK)
   {

      pmutex->lock();

   }
   else
   {

      pmutex->unlock();

   }

}

#endif

extern "C" unsigned long SSLInitializer_SSL_id_function()
{

//#ifdef WIN32

   return (unsigned long) ::get_current_ithread();

//#else
//
//   unsigned long ul = (unsigned long)(iptr) ::pthread_self();
//
//   return ul;
//
//#endif
//
}


#if OPENSSL_API_COMPAT < 0x10100000L

extern "C"
#if defined(_UWP) && (!defined(RASPBIAN))
void
#else
int
#endif
SSLInitializer_rand_seed(const void * buf, i32 num)
{
   UNREFERENCED_PARAMETER(buf);
   UNREFERENCED_PARAMETER(num);
#if defined(_UWP) && (!defined(RASPBIAN))
#else
   return 1;
#endif
}

extern "C" i32 SSLInitializer_rand_bytes(uchar * buf, i32 num)
{
   System.math().gen_rand(buf, num);
   return 1;
}

extern "C" void SSLInitializer_rand_cleanup()
{
}

extern "C"
#if defined(_UWP)
void
#else
int
#endif
SSLInitializer_rand_add(const void * buf, int num, double entropy)
{
   UNREFERENCED_PARAMETER(buf);
   UNREFERENCED_PARAMETER(num);
   UNREFERENCED_PARAMETER(entropy);
#if defined(_UWP)
#else
   return 1;
#endif
}

extern "C" i32 SSLInitializer_rand_pseudorand(uchar * buf, i32 num)
{
   System.math().gen_rand(buf, num);
   return num;
}

extern "C" i32 SSLInitializer_rand_status()
{
   return 1024;
}

#endif

#endif // HAVE_OPENSSL



