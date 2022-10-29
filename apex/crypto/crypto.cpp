﻿#include "framework.h"
#include "crypto.h"
#include "hasher.h"
#include "hasher_algorithm.h"
#include "initializer.h"
#include "rsa.h"
#include "acme/exception/interface_only.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/primitive/string/base64.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/primitive/mathematics/mathematics.h"
#include "acme/primitive/string/base64.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"


namespace crypto
{


   crypto::crypto()
   {


   }


   crypto::~crypto()
   {


   }


   void crypto::defer_initialize()
   {

      /*auto estatus = */ __defer_construct(m_pinitializer);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   ::pointer<hasher_algorithm>crypto::create_hasher_algorithm(enum_hash ehash)
   {

      /*auto estatus = */ defer_initialize();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto palgorithm = __create < ::crypto::hasher_algorithm >();

      if (!palgorithm)
      {

         return palgorithm;

      }

      /*estatus =*/ palgorithm->initialize_hasher_algorithm(ehash);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return palgorithm;

   }


   ::pointer<hasher>crypto::create_hasher(enum_hash ehash)
   {

      auto palgorithm = create_hasher_algorithm(ehash);

      if (!palgorithm)
      {

         return palgorithm;

      }

      auto phasher = palgorithm->create_hasher();

      if (!phasher)
      {

         return phasher;

      }

      return phasher;

   }





//#include <zlib.h>

#define CA4_BASE_HASH_DIGEST_LENGTH 32

#define CA4_CRYPT_V5_FINAL_HASH_BYTES 1024
#define CA4_CRYPT_V5_SALT_BYTES (CA4_CRYPT_V5_FINAL_HASH_BYTES - CA4_BASE_HASH_DIGEST_LENGTH)

   string chunk_split(const string& body, i32 chunklen = 76, const string& end = "\r\n");






      void crypto::decrypt(memory& storageDecrypt, const block& blockEncrypt, const block & blockSalt)
      {

         // default implementation - OS may implement its own HOME/UserDir encryption

         auto key = defer_get_cryptkey();

         if (key.is_empty())
         {
          
            throw ::exception(error_failed);

         }

         key += blockSalt;

         decrypt(storageDecrypt, blockEncrypt, key);

      }

      
      void crypto::encrypt(memory& storageEncrypt, const block & blockDecrypt, const block & blockSalt)
      {

         // default implementation - OS may implement its own HOME/UserDir encryption

         auto key = defer_get_cryptkey();

         if (key.is_empty())
         {

            throw ::exception(error_failed);

         }

         key += blockSalt;

         //memory key;

         //key.from_string(str);

         /*auto estatus = */ encrypt(storageEncrypt, blockDecrypt, key);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;


      }



      i32 crypto::key(memory& storage)
      {

         storage.set_size(16);

         for (memsize i = 0; i < storage.get_size(); i++)
         {

            storage.get_data()[i] = __random<char>() & 0xff;

         }

         return (i32)storage.get_size();

      }



      string crypto::strkey()
      {
         memory storage;
         key(storage);

         //auto psystem = get_system()->m_papexsystem;

         auto psystem = acmesystem();

         auto pbase64 = psystem->base64();

         return pbase64->encode(storage);

      }


      //void crypto::encrypt(string& strEncrypt, const char* pszDecrypt, const char* pszKey)
      //{
      //   
      //   memory storageDecrypt;

      //   memory storageEncrypt;

      //   memory storageKey;

      //   if (pszDecrypt == nullptr || strlen(pszDecrypt) == 0)
      //   {

      //      strEncrypt = "";

      //      return;

      //   }

      //   storageDecrypt.from_string(pszDecrypt);

      //   auto psystem = acmesystem();

      //   auto pbase64 = psystem->base64();

      //   pbase64->decode(storageKey, pszKey);

      //   /* i32 cipherlen = */ encrypt(storageEncrypt, storageDecrypt, storageKey);

      //   strEncrypt = pbase64->encode(storageEncrypt);

      //   //return cipherlen;

      //}


      //void crypto::decrypt(string& strDecrypt, const char* pszEncrypt, const char* pszKey)
      //{

      //   memory storageEncrypt;

      //   memory storageDecrypt;

      //   memory storageKey;

      //   auto psystem = acmesystem();

      //   auto pbase64 = psystem->base64();

      //   pbase64->decode(storageEncrypt, pszEncrypt);

      //   pbase64->decode(storageKey, pszKey);

      //   /*i32 plainlen =*/ decrypt(storageDecrypt, storageEncrypt, storageKey);

      //   strDecrypt = storageDecrypt.as_string();

      //   //return plainlen;

      //}


      //u32 crypto::crc32(u32 dwPrevious, const char* psz)
      //{

      //   throw ::interface_only();

      //   return 0;

      //   //return (::u32)::crc32(dwPrevious, (const Bytef*)psz, (::u32)strlen(psz));

      //}


      //string crypto::md5(const block & block)
      //{

      //   memory mem;

      //   mem.assign(psz, strlen(psz));

      //   return md5(mem);

      //}


      //string crypto::sha1(const char* psz)
      //{

      //   memory mem;

      //   mem.assign(psz, strlen(psz));

      //   return sha1(mem);

      //}


      //string crypto::nessie(const char* psz)
      //{

      //   memory mem;

      //   mem.assign(psz, strlen(psz));

      //   return nessie(mem);

      //}


      string crypto::md5(const block & block)
      {

         memory memMd5;

         md5(memMd5, block);

         return memMd5.to_hex();

      }


      string crypto::sha1(const block & block)
      {

         memory memSha1;

         sha1(memSha1, block);

         return memSha1.to_hex();

      }


      string crypto::nessie(const block & block)
      {

         memory memNessie;

         nessie(memNessie, block);

         return memNessie.to_hex();

      }


      int crypto::get_md5_digest_length() const
      {

         return get_hash_digest_length(e_hash_md5);

      }


      int crypto::get_sha1_digest_length() const
      {

         return get_hash_digest_length(e_hash_sha1);

      }


      int crypto::get_sha256_digest_length() const
      {

         return get_hash_digest_length(e_hash_sha256);

      }


      int crypto::get_nessie_digest_length() const
      {

         return get_hash_digest_length(e_hash_nessie);

      }


      int crypto::get_hash_digest_length(enum_hash) const
      {

         throw ::interface_only();

          return 0;

      }


      void crypto::hash(memory& memOut, const block& block, enum_hash ehash)
      {

         auto palgorithm = create_hasher_algorithm(ehash);

         if (!palgorithm)
         {

            throw ::exception(error_resource);

         }

         /*auto estatus =*/ palgorithm->hash(memOut, block);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }


      void crypto::md5(memory& memMd5, const block& block)
      {

         /*auto estatus = */ hash(memMd5, block, e_hash_md5);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //#ifdef HAVE_OPENSSL
         //
         //      memMd5.set_size(get_md5_digest_length());
         //
         //      md5(memSha1.get_data(), mem.get_data(), (size_t)mem.get_size());
         //
         //#else
         //
         //      auto algorithm = ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(::winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames::Md5);
         //
         //      memMd5.set_os_buffer(algorithm->HashData(mem.get_os_buffer()));
         //
         //#endif

         //return estatus;

      }


      void crypto::sha1(memory& memSha1, const block& block)
      {

         /*auto estatus = */ hash(memSha1, block, e_hash_sha1);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //#ifdef HAVE_OPENSSL
         //
         //      memSha1.set_size(get_sha1_digest_length());
         //
         //      sha1(memSha1.get_data(), mem.get_data(), (size_t)mem.get_size());
         //
         //#else
         //
         //      auto algorithm = ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(::winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames::Sha1);
         //
         //      memSha1.set_os_buffer(algorithm->HashData(mem.get_os_buffer()));
         //
         //#endif

         //return estatus;

      }


      void crypto::sha256(memory& memSha256, const block& block)
      {

         /*auto estatus =*/ hash(memSha256, block, e_hash_sha256);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //#ifdef HAVE_OPENSSL
         //
         //      memSha256.set_size(get_sha1_digest_length());
         //
         //      sha256(memSha256.get_data(), mem.get_data(), (size_t)mem.get_size());
         //
         //#else
         //
         //      auto algorithm = ::winrt::Windows::Security::Cryptography::Core::HashAlgorithmProvider::OpenAlgorithm(::winrt::Windows::Security::Cryptography::Core::HashAlgorithmNames::Sha256);
         //
         //      memSha256.set_os_buffer(algorithm->HashData(mem.get_os_buffer()));
         //
         //#endif

         //return estatus;

      }


      void crypto::nessie(memory& memNessie, const block& block)
      {

         /*auto estatus = */ hash(memNessie, block, e_hash_nessie);

         //if (!estatus)
         //{

         //   return estatus;

         //}

         //return estatus;

      }


      void crypto::file_set(::payload payloadFile, const char* pszData, const char* pszSalt, ::apex::application* papp)
      {

         memory memoryEncrypt;

         encrypt(memoryEncrypt, pszData, pszSalt);

         file()->put_memory(payloadFile, memoryEncrypt);

      }


      void crypto::file_get(::payload payloadFile, string& str, const char* pszSalt, ::apex::application* papp)
      {

         memory memoryEncrypt;

         if (!file()->exists(payloadFile))
         {
            
            str.Empty();

            return;

         }

         file()->as_memory(payloadFile, memoryEncrypt);

         decrypt(str, memoryEncrypt, pszSalt);

      }


      void crypto::encrypt(string & strEncrypt, const block & blockDecrypt, const block & blockSalt)
      {

         memory memoryEncrypt;

         encrypt(memoryEncrypt, blockDecrypt, blockSalt);

         strEncrypt = memoryEncrypt.to_hex();

      }


      void crypto::decrypt(string& strDecrypt, const block& blockEncrypt, const block & blockSalt)
      {

         memory memoryDecrypt;

         decrypt(memoryDecrypt, blockEncrypt, blockSalt);

         strDecrypt = memoryDecrypt.as_string();

      }


      // get a memory_new salt - 8 hexadecimal characters long
      // current PHP installations should not exceed 8 characters
      // on dechex( mt_rand() )
      // but we future proof it anyway with substr()
      string crypto::v5_get_password_salt()
      {

         string strSalt;

         string strFormat;

         for (i32 i = 0; i < CA4_CRYPT_V5_FINAL_HASH_BYTES - CA4_BASE_HASH_DIGEST_LENGTH; i += 2)
         {

            i64 iDigit = __random<char>();

            strFormat.format("%02x", iDigit);

            strSalt += strFormat;

         }

         return strSalt;

      }


      // calculate the hash from a salt and a password
      // slow hash is more secure for personal attack possibility (strong fast hashs are only good for single transactional operations and not for a possibly lifetime password)
      string crypto::v5_get_password_hash(const char* pszSalt, const char* pszPassword, i32 iOrder)
      {

         string strHash(pszPassword);

         string strSalt(pszSalt);

         strSalt = strSalt.Left(CA4_CRYPT_V5_SALT_BYTES);

         for (i32 i = iOrder; i < CA4_CRYPT_V5_FINAL_HASH_BYTES - CA4_BASE_HASH_DIGEST_LENGTH; i++)
         {

            string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);

            strHash = nessie(strStepSalt + strHash).lowered();

         }

         return strSalt + strHash;

      }


      string crypto::v5_get_passhash(const char* pszSalt, const char* pszPassword, i32 iMaxOrder)
      {

         string strHash(pszPassword);

         string strSalt(pszSalt);

         strSalt = strSalt.Left(CA4_CRYPT_V5_SALT_BYTES);

         for (i32 i = 0; i < iMaxOrder; i++)
         {

            string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);

            strHash = nessie(strStepSalt + strHash).lowered();

         }

         return strSalt + strHash;

      }


      bool crypto::v5_compare_password(const char* pszPassword, const char* pszHash, i32 iOrder)
      {

         string strHash(pszHash);

         string strSalt = strHash.Left(CA4_CRYPT_V5_SALT_BYTES);

         return strHash == v5_get_password_hash(strSalt, pszPassword, iOrder);

      }


      bool crypto::v5_validate_plain_password(const char* pszPassword)
      {

         string str(pszPassword);
         
         if (str.get_length() < 6)
         {

            return false;

         }

         return ::str().has_all_v1(pszPassword);

      }


      string crypto::v5_get_password_hash(const char* pszPassword, i32 iOrder)
      {

         return v5_get_password_hash(v5_get_password_salt(), pszPassword, iOrder);

      }


      ::file::path crypto::get_crypt_key_file_path()
      {

         return acmedirectory()->system() / "user" / "databin.bin";

      }


      ::memory crypto::defer_get_cryptkey()
      {

         string strPath = get_crypt_key_file_path();

         string str = file()->as_string(strPath);

         if (str.has_char())
         {

            return str;

         }

         int iLength = 256;

         generate_random_alphanumeric(str.get_string_buffer(iLength), iLength);

         file()->put_memory(strPath, str);

         return str;

      }


      ::pointer<rsa>crypto::create_rsa_key(const ::string& strRsa)
      {

         throw todo;

         return nullptr;

      }

      
      ::pointer<rsa>crypto::generate_rsa_key()
      {

         throw todo;

         return nullptr;

      }

      
      ::pointer<rsa>crypto::read_priv_pem(const ::string& strFile)
      {

         throw todo;

         return nullptr;

      }


      ::pointer<rsa>crypto::read_pub_pem(const ::string& strFile)
      {

         throw todo;

         return nullptr;

      }



      //   int rsa::private_decrypt(memory& out, const memory& in, string& strError)
      //   {
      //
      //
      //#if defined(_UWP) && !defined(HAVE_OPENSSL)
      //
      //
      //
      //      out.set_os_crypt_buffer(::winrt::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));
      //
      //
      //
      //
      //#else
      //
      //      single_lock synchronouslock(mutex(), true);
      //
      //      i32 iRsaSize = 8192;
      //
      //      out.set_size(iRsaSize);
      //
      //      out.set(0);
      //
      //      ::count i = RSA_private_decrypt((int)in.get_size(), in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);
      //
      //      if (i < 0 || i >(1024 * 1024))
      //      {
      //
      //         strError = ERR_error_string(ERR_get_error(), nullptr);
      //
      //         return (int)i;
      //
      //      }
      //
      //      out.set_size(i);
      //
      //#endif
      //
      //      return int(out.get_size());
      //
      //   }
      //
      //   int rsa::private_encrypt(memory& out, const memory& in, string& strError)
      //   {
      //#ifdef MACOS_DEPRECATED
      //
      //
      //      SecTransformRef transform = SecEncryptTransformCreate(m_prsa, &error);
      //
      //      if (error != nullptr)
      //      {
      //
      //         CFRelease(error);
      //
      //         return "";
      //
      //      }
      //
      //      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);
      //
      //      if (error != nullptr)
      //      {
      //
      //         CFRelease(transform);
      //
      //         CFRelease(error);
      //
      //         return "";
      //
      //      }
      //
      //      memory memDataIn;
      //
      //      memDataIn.from_hex(strRsaModulus);
      //
      //      CFDataRef dataIn = memDataIn.get_os_cf_data();
      //
      //      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);
      //
      //      if (error != nullptr)
      //      {
      //
      //         CFRelease(dataIn);
      //
      //         CFRelease(transform);
      //
      //         CFRelease(error);
      //
      //         return "";
      //
      //      }
      //
      //      /* Encrypt the data. */
      //
      //      CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);
      //
      //      if (error != nullptr)
      //      {
      //
      //         CFRelease(dataIn);
      //
      //         CFRelease(transform);
      //
      //         CFRelease(error);
      //
      //         return "";
      //
      //      }
      //
      //
      //      string strHex;
      //
      //      memory memory;
      //
      //      memory.set_os_cf_data(data);
      //
      //      memory.to_hex(strHex);
      //
      //      CFRelease(data);
      //
      //      CFRelease(dataIn);
      //
      //      CFRelease(transform);
      //
      //#elif defined(_UWP) && !defined(HAVE_OPENSSL)
      //
      //
      //
      //      out.set_os_crypt_buffer(::winrt::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));
      //
      //
      //
      //
      //#else
      //
      //      auto iInSize = (i32)in.get_size();
      //
      //      auto pInData = (const uchar*)(const char*)in.get_data();
      //
      //      auto pOutData = out.get_data();
      //
      //      auto prsa = m_prsa;
      //
      //      i32 i = RSA_private_encrypt(iInSize, pInData, pOutData, prsa, RSA_PKCS1_PADDING);
      //
      //      strError = ERR_error_string(ERR_get_error(), nullptr);
      //
      //      out.set_size(i);
      //
      //
      //
      //#endif
      //
      //      return int(out.get_size());
      //
      //   }
      //
      //
      //   int rsa::public_decrypt(memory& out, const memory& in, string& strError)
      //   {
      //
      //
      //#if defined(_UWP) && !defined(HAVE_OPENSSL)
      //
      //
      //
      //      out.set_os_crypt_buffer(::winrt::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));
      //
      //
      //
      //
      //#else
      //
      //      single_lock synchronouslock(mutex(), true);
      //
      //      i32 iRsaSize = 8192;
      //
      //      out.set_size(iRsaSize);
      //
      //      out.set(0);
      //
      //      ::count i = RSA_public_decrypt((int)in.get_size(), in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);
      //
      //      if (i < 0 || i >(1024 * 1024))
      //      {
      //
      //         strError = ERR_error_string(ERR_get_error(), nullptr);
      //
      //         return (int)i;
      //
      //      }
      //
      //      out.set_size(i);
      //
      //#endif
      //
      //      return int(out.get_size());
      //
      //   }


      string crypto::spa_login_crypt(const char* psz, const string& strRsa)
      {

         auto prsa = create_rsa_key(strRsa);

         memory memory;

         ::memory memIn;

         memIn.from_hex(psz);

         memory.set_size(2048);

         memory.set(0);

         string strError;

         int i = prsa->public_encrypt(memory, memIn, strError);

         if (i < 0 || i >(1024 * 1024))
         {

            ERROR(strError);

         }

         return memory.to_hex();

      }


      string crypto::spa_login_decrypt(const char* psz, const string& strRsa)
      {

         auto prsa = create_rsa_key(strRsa);

         memory memory;

         ::memory memIn;

         memIn.from_hex(psz);

         memory.set_size(2048);

         memory.set(0);

         string strError;

         int i = prsa->private_decrypt(memory, memIn, strError);

         if (i < 0 || i >(1024 * 1024))
         {

            ERROR(strError);

         }

         return memory.to_hex();

      }
      string crypto::spa_auth_decrypt(const char* psz, rsa* prsa)
      {

         memory memory;

         ::memory memIn;

         memIn.from_hex(psz);

         memory.set_size(2048);

         memory.set(0);

         string strError;

         int i = prsa->public_decrypt(memory, memIn, strError);

         if (i < 0 || i >(1024 * 1024))
         {

            ERROR(strError);

         }

         return memory.to_hex();

      }

      string crypto::spa_auth_decrypt(const char* psz, const string& strRsa)
      {

         auto prsa = create_rsa_key(strRsa);

         memory memory;

         ::memory memIn;

         memIn.from_hex(psz);

         memory.set_size(2048);

         memory.set(0);

         string strError;

         int i = prsa->public_decrypt(memory, memIn, strError);

         if (i < 0 || i >(1024 * 1024))
         {

            ERROR(strError);

         }

         return memory.to_hex();

      }


      string crypto::spa_auth_crypt(const char* psz, rsa* prsa)
      {

         memory memory;

         ::memory memIn;

         memIn.from_hex(psz);

         memory.set_size(2048);

         memory.set(0);

         string strError;

         int i = prsa->private_encrypt(memory, memIn, strError);

         if (i < 0 || i >(1024 * 1024))
         {

            ERROR(strError);

         }

         return memory.to_hex();

      }



      string crypto::txt_encrypt(const char* psz, rsa* prsa)
      {

         memory memory;

         ::memory memIn;

         memIn.assign(psz, strlen(psz));

         memory.set_size(2048);

         memory.set(0);

         string strError;

         int i = prsa->private_encrypt(memory, memIn, strError);

         if (i < 0 || i >(1024 * 1024))
         {

            ERROR(strError);

         }

         return memory.to_hex();

      }


      string crypto::txt_decrypt(const char* psz, rsa* prsa)
      {

         memory memory;

         ::memory memIn;

         memIn.from_hex(psz);

         memory.set_size(2048);

         memory.set(0);

         string strError;

         int i = prsa->public_decrypt(memory, memIn, strError);

         if (i < 0 || i >(1024 * 1024))
         {

            ERROR(strError);

         }

         string str;

         str = memory.as_string();

         return str;

      }

   /*

   bool crypt_file_get(const char * pszFile, string & str, const char * pszSalt)
   {

   string vsstr;

   if(!crypt_file_get(pszFile, vsstr, pszSalt))
   return false;

   str = vsstr;

   return true;

   }


   */

} // namespace crypto



