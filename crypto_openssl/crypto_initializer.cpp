//
// crypto_initializer.h
//
// Created by camilo 2021-05-24 05:39 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "crypto_initializer.h"

#ifdef HAVE_OPENSSL
#include <openssl/ssl.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/engine.h>
#include <openssl/conf.h>


#include <openssl/conf.h>



#if OPENSSL_API_COMPAT < 0x10100000L

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

namespace crypto
{


#if OPENSSL_API_COMPAT < 0x10100000L


   map < i32, ::mutex* >* g_pmapMutex = nullptr;


   ::mutex* g_pmutexMap = nullptr;


#endif
   

   initializer::initializer()
   {

#if OPENSSL_API_COMPAT < 0x10100000L

      m_rand_size = 1024;

      g_pmapMutex = new map < i32, ::mutex*>;

      g_pmutexMap = new ::mutex();

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



   void initializer::DeleteRandFile()
   {

#if OPENSSL_API_COMPAT < 0x10100000L

      if (m_rand_file.get_length())
      {

         m_pcontext->m_papexcontext->file().del(m_rand_file);

      }

#endif

   }


} // namespace crypto


#if OPENSSL_API_COMPAT < 0x10100000L
extern "C" void crypto_initializer_SSL_locking_function(i32 mode, i32 n, const char* file, i32 line)
{

   __UNREFERENCED_PARAMETER(file);

   __UNREFERENCED_PARAMETER(line);

   synchronous_lock synchronouslock(::crypto::g_pmutexMap);

   ::mutex* pmutex = nullptr;

   if (::crypto::g_pmapMutex != nullptr && !::crypto::g_pmapMutex->lookup(n, pmutex))
   {

      ::crypto::g_pmapMutex->operator [](n) = new ::mutex();

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

#endif

extern "C" unsigned long crypto_initializer_SSL_id_function()
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


extern "C" int crypto_initializer_rand_seed(const void* buf, i32 num)
{
   __UNREFERENCED_PARAMETER(buf);
   __UNREFERENCED_PARAMETER(num);
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
   __UNREFERENCED_PARAMETER(buf);
   __UNREFERENCED_PARAMETER(num);
   __UNREFERENCED_PARAMETER(entropy);
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

#endif // HAVE_OPENSSL



