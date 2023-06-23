//
// crypto_initializer.h
//
// Created by camilo 2021-05-24 05:39 BRT <3ThomasBS_!!
// Refactored to crypto_openssl by camilo 2021-11-19 14:19 BRT <3ThomasBS_!!
//
#include "framework.h"

#include "initializer.h"


#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/engine.h>
#include <openssl/conf.h>


#include <openssl/conf.h>


#if OPENSSL_VERSION_NUMBER < 0x10100000L

RAND_METHOD rand_meth;
extern "C" void crypto_initializer_locking_function(i32 mode, i32 n, const char* file, i32 line);
extern "C" unsigned long crypto_initializer_id_function();

extern "C" int crypto_initializer_rand_seed(const void* buf, i32 num);
extern "C" i32 crypto_initializer_rand_bytes(uchar * buf, i32 num);
extern "C" void crypto_initializer_rand_cleanup();
extern "C" int crypto_initializer_rand_add(const void* buf, int num, double entropy);
extern "C" i32 crypto_initializer_rand_pseudorand(uchar * buf, i32 num);
extern "C" i32 crypto_initializer_rand_status();

#endif

namespace crypto_openssl
{


#if OPENSSL_VERSION_NUMBER < 0x10100000L


   map < i32, ::pointer < ::mutex >* >* g_pmapMutex = nullptr;


   ::pointer < ::mutex >* g_pmutexMap = nullptr;


#endif
   

   initializer::initializer()
   {

#if OPENSSL_VERSION_NUMBER < 0x10100000L

      m_rand_size = 1024;

      g_pmapMutex = memory_new map < i32, ::pointer < ::mutex >*>;

      g_pmutexMap = memory_new ::pointer < ::mutex >();

      OpenSSL_add_all_digests();

      CRYPTO_set_locking_callback(crypto_initializer_locking_function);
      CRYPTO_set_id_callback(crypto_initializer_id_function);


#endif


//#if OPENSSL_API_COMPAT < 0x10100000L
//
//      rand_meth.add = &crypto_initializer_rand_add;
//      rand_meth.bytes = &crypto_initializer_rand_bytes;
//      rand_meth.cleanup = &crypto_initializer_rand_cleanup;
//      rand_meth.pseudorand = &crypto_initializer_rand_pseudorand;
//      rand_meth.seed = &crypto_initializer_rand_seed;
//      rand_meth.status = &crypto_initializer_rand_status;
//
//      RAND_set_rand_method(&rand_meth);
//
//#endif

      //if (!initialized)
      {
         RAND_poll();
         // initialized = 1;
      }



   }


   initializer::~initializer()
   {

#if OPENSSL_VERSION_NUMBER < 0x10100000L

      DeleteRandFile();

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


#if OPENSSL_VERSION_NUMBER < 0x10100000L


   void initializer::DeleteRandFile()
   {

      if (m_rand_file.get_length())
      {

         file()->del(m_rand_file);

      }

   }


#endif


} // namespace crypto


#if OPENSSL_VERSION_NUMBER < 0x10100000L


extern "C" void crypto_initializer_SSL_locking_function(i32 mode, i32 n, const char* file, i32 line)
{

   UNREFERENCED_PARAMETER(file);

   UNREFERENCED_PARAMETER(line);

   synchronous_lock synchronouslock(::crypto::g_pmutexMap);

   ::pointer < ::mutex >* pmutex = nullptr;

   if (::crypto::g_pmapMutex != nullptr && !::crypto::g_pmapMutex->lookup(n, pmutex))
   {

      ::crypto::g_pmapMutex->operator [](n) = memory_new ::pointer < ::mutex >();

      if (!::crypto::g_pmapMutex->lookup(n, pmutex))
      {

         return;

      }

   }

   if (pmutex == nullptr)
   {

      return;

   }

   synchronouslock.unlock();

   if (mode & CRYPTO_LOCK)
   {

      pmutex->lock();

   }
   else
   {

      pmutex->unlock();

   }

}

extern "C" unsigned long crypto_initializer_SSL_id_function()
{

   //#ifdef WIN32

   return (unsigned long) ::get_current_itask();

   //#else
   //
   //   unsigned long ul = (unsigned long)(iptr) ::pthread_self();
   //
   //   return ul;
   //
   //#endif
   //
}


extern "C" int crypto_initializer_rand_seed(const void* buf, i32 num)
{
   UNREFERENCED_PARAMETER(buf);
   UNREFERENCED_PARAMETER(num);
   return 1;
}


extern "C" i32 crypto_initializer_rand_bytes(uchar * buf, i32 num)
{

   generate_random_bytes(buf, num);

   return 1;

}


extern "C" void crypto_initializer_rand_cleanup()
{

}


extern "C" int crypto_initializer_rand_add(const void* buf, int num, double entropy)
{
   UNREFERENCED_PARAMETER(buf);
   UNREFERENCED_PARAMETER(num);
   UNREFERENCED_PARAMETER(entropy);
   return 1;
}


extern "C" i32 crypto_initializer_rand_pseudorand(uchar * buf, i32 num)
{

   generate_random_bytes(buf, num);

   return num;

}


extern "C" i32 crypto_initializer_rand_status()
{

   return 1024;

}


#endif



