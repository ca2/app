#include "framework.h"
#include "metrowin.h"


//#define CA4_CRYPT_V5_FINAL_HASH_BYTES (WHIRLPOOL_DIGEST_LENGTH * 16)
//#define CA4_CRYPT_V5_SALT_BYTES (CA4_CRYPT_V5_FINAL_HASH_BYTES - WHIRLPOOL_DIGEST_LENGTH)
//
//#include <openssl/crypto.h>
//#include <openssl/rand.h>
//#include <openssl/bio.h>
//#include <openssl/evp.h>
//
//extern "C" void SSLInitializer_SSL_locking_function(i32 mode,i32 n,const char * file,i32 line);
//extern "C" unsigned long SSLInitializer_SSL_id_function();
//extern "C" void SSLInitializer_rand_seed(const void * buf,i32 num);
//extern "C" i32 SSLInitializer_rand_bytes(uchar * buf,i32 num);
//extern "C" void SSLInitializer_rand_cleanup();
//extern "C" void SSLInitializer_rand_add(const void * buf,i32 num,double entropy);
//extern "C" i32 SSLInitializer_rand_pseudorand(uchar * buf,i32 num);
//extern "C" i32 SSLInitializer_rand_status();



namespace metrowin
{


   crypto::crypto(::object * pobject) :
      ::object(pobject),
      ::crypto::crypto(pobject)
   {

      m_psslinit = new sockets::SSLInitializer(get_object());
   }


   crypto::~crypto()
   {
   }


   bool crypto::decrypt(memory & storageDecrypt, const memory & storageEncrypt, const char * pszSalt)
   {


      UNREFERENCED_PARAMETER(pszSalt);

      ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider ^ provider = ref new ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider;

      ::Windows::Storage::Streams::IBuffer ^ bufferIn = storageEncrypt.get_os_crypt_buffer();

      if(bufferIn == nullptr)
         return false;

      ::Windows::Storage::Streams::IBuffer ^ bufferOut = ::wait(provider->UnprotectAsync(bufferIn));

      storageDecrypt.set_os_crypt_buffer(bufferOut);

      return true;

   }

   bool crypto::encrypt(memory & storageEncrypt, const memory & storageDecrypt, const char * pszSalt)
   {

      UNREFERENCED_PARAMETER(pszSalt);

      ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider ^ provider = ref new ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider("LOCAL=user");

      ::Windows::Storage::Streams::IBuffer ^ bufferIn = storageDecrypt.get_os_crypt_buffer();

      ::Windows::Storage::Streams::IBuffer ^ bufferOut = ::wait(provider->ProtectAsync(bufferIn));

      storageEncrypt.set_os_crypt_buffer(bufferOut);

      return true;

   }






   void crypto::md5(memory & memMd5,const memory & mem)
   {

      ::Windows::Security::Cryptography::Core::HashAlgorithmProvider ^ hasher =
      ::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::HashAlgorithmNames::Md5);

      memMd5.set_os_crypt_buffer(hasher->HashData(mem.get_os_crypt_buffer()));

   }


   void crypto::sha1(memory & memSha1,const memory & mem)
   {

      ::Windows::Security::Cryptography::Core::HashAlgorithmProvider ^ hasher =
      ::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::HashAlgorithmNames::Sha1);

      memSha1.set_os_crypt_buffer(hasher->HashData(mem.get_os_crypt_buffer()));

   }


   //namespace metrowin_crypto
   //{

   //#include "openssl/ssl.h"








//         map < i32,i32,::mutex *,::mutex *>  * g_pmapMutex = nullptr;
//
//         ::mutex * g_pmutexMap = nullptr;
//
//
//
//
//         RAND_METHOD rand_meth;
//
//
//         ::aura::system * SSLInitializer::s_psystem = nullptr;
//
//         SSLInitializer::SSLInitializer(::object * pobject):
//            ::object(pobject)
//         {
//
//
//
//            TRACE("SSLInitializer()\n");
//
//            bio_err = nullptr;
//            m_rand_size = 1024;
//
//            s_psystem = papp->m_psystem;
//
//            /* An error write context */
//            bio_err = BIO_new_fp(stderr,BIO_NOCLOSE);
//
//            g_pmapMutex = new map < i32,i32,::mutex *,::mutex *>;
//
//            g_pmutexMap = new ::mutex();
//
//            /* Global system initialization*/
////            SSL_library_init();
//  //          SSL_load_error_strings();
//    //        OpenSSL_add_all_algorithms();
////            CRYPTO_set_locking_callback(SSLInitializer_SSL_locking_function);
//  //          CRYPTO_set_id_callback(SSLInitializer_SSL_id_function);
//
//
//            /* Ignore broken pipes which would cause our program to terminate
//            prematurely */
//
//      //      rand_meth.add = &SSLInitializer_rand_add;
//        //    rand_meth.bytes = &SSLInitializer_rand_bytes;
//          //  rand_meth.cleanup = &SSLInitializer_rand_cleanup;
//            //rand_meth.pseudorand = &SSLInitializer_rand_pseudorand;
//            //rand_meth.seed = &SSLInitializer_rand_seed;
//            //rand_meth.status = &SSLInitializer_rand_status;
//
//            //RAND_set_rand_method(&rand_meth);
//
//
//
//            /*   char *randfile =
//            char *home = getenv("HOME");
//            if (!randfile && !home)
//            {
//            char *homepath = getenv("HOMEPATH");
//            if (homepath)
//            {
//            Utility::SetEnv("HOME", homepath);
//            }
//            }*/
//
//            //memory memstorage;
//            //memstorage.set_size(5000);
//            //memstorage.set_size(5000);
//            //System.math().gen_rand(memstorage.get_data(), memstorage.get_size());
//
//            /*for(i32 i = 0; i < memstorage.get_size(); i += 3)
//            {
//            i32 iValue = __random(0, 0x00ffffff);
//            memstorage.get_data()[i] = iValue & 0xff;
//            memstorage.get_data()[i+1] = (iValue >> 8) & 0xff;
//            memstorage.get_data()[i+2] = (iValue >> 16) & 0xff;
//            }*/
//
//            /*m_rand_file = Context.file().time_square();
//            //*path = 0;
//            //RAND_file_name(path, 512);
//            //if (*path)
//            //{
//
//
//
//            i32 iWritten = RAND_write_file(m_rand_file);
//            m_rand_size = iWritten;
//            //}
//            //else
//            //{
//            //TRACE("SSLInitializer: no random file generated\n");
//            //   }
//
//            file_pointer spfile(e_create);
//
//            spfile->open(m_rand_file, ::file::type_binary | ::file::mode_read);
//
//
//            //memstorage.FullLoad(spfile);
//
//            /* Load randomness */
//            /*if (!m_rand_file.get_length())
//            {
//            TRACE("SSLInitializer: PRNG not initialized\n");
//            }*/
//            /*RAND_add(
//            memstorage.get_data(),
//            memstorage.get_size(),
//            memstorage.get_size());*/
//
//            //RAND_seed(memstorage.get_data(), memstorage.get_size());
//
//         }
//
//
//         SSLInitializer::~SSLInitializer()
//         {
//            //      TRACE("~SSLInitializer()\n");
//            //DeleteRandFile();
//            // %! delete mutexes
//
//
//            if(g_pmapMutex != nullptr)
//            {
//               delete g_pmapMutex;
//
//               g_pmapMutex = nullptr;
//            }
//
//            if(g_pmutexMap != nullptr)
//            {
//               delete g_pmutexMap;
//
//               g_pmutexMap = nullptr;
//            }
//
//         }
//
//
//         void SSLInitializer::DeleteRandFile()
//         {
//
//            if(m_rand_file.get_length())
//            {
//
//               Context.file().del(m_rand_file);
//
//            }
//
//         }
//
//
} // namespace metrowin





//
//
//
//
//
//
//      extern "C" void SSLInitializer_SSL_locking_function(i32 mode,i32 n,const char * file,i32 line)
//      {
//         UNREFERENCED_PARAMETER(file);
//         UNREFERENCED_PARAMETER(line);
//
//
//         sync_lock sl(::metrowin::g_pmutexMap);
//
//         ::mutex * pmutex = nullptr;
//         if(!::metrowin::g_pmapMutex->lookup(n,pmutex))
//         {
//            ::metrowin::g_pmapMutex->operator [](n) = new ::mutex();
//            if(!::metrowin::g_pmapMutex->lookup(n,pmutex))
//            {
//               return;
//            }
//         }
//
//         if(pmutex == nullptr)
//         {
//            return;
//         }
//
//         sl.unlock();
//
//         if(mode & CRYPTO_LOCK)
//         {
//            pmutex->lock();
//         }
//         else
//         {
//            pmutex->unlock();
//         }
//
//      }
//
//
//
//      extern "C" unsigned long SSLInitializer_SSL_id_function()
//      {
//#ifdef WIN32
//         return ::GetCurrentThreadId();
//#else
//         return (unsigned long)(iptr) ::pthread_self();
//#endif
//      }
//
//      extern "C" void SSLInitializer_rand_seed(const void * buf,i32 num)
//      {
//         UNREFERENCED_PARAMETER(buf);
//         UNREFERENCED_PARAMETER(num);
//      }
//
//      extern "C" i32 SSLInitializer_rand_bytes(uchar * buf,i32 num)
//      {
//         ::metrowin::SSLInitializer::s_psystem->math().gen_rand(buf,num);
//         return num;
//      }
//
//      extern "C" void SSLInitializer_rand_cleanup()
//      {
//      }
//
//      extern "C" void SSLInitializer_rand_add(const void * buf,i32 num,double entropy)
//      {
//         UNREFERENCED_PARAMETER(buf);
//         UNREFERENCED_PARAMETER(num);
//         UNREFERENCED_PARAMETER(entropy);
//      }
//
//      extern "C" i32 SSLInitializer_rand_pseudorand(uchar * buf,i32 num)
//      {
//         ::metrowin::SSLInitializer::s_psystem->math().gen_rand(buf,num);
//         return num;
//      }
//
//      extern "C" i32 SSLInitializer_rand_status()
//      {
//         return 1024;
//      }
//
