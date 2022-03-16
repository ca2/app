#include "framework.h"
#include "_openssl.h"
#include "acme/filesystem/filesystem/acme_directory.h"




//namespace str
//{
//
//
//   CLASS_DECL_APEX void from(string& str, const MD5_CTX& ctx)
//   {
//
//      unsigned char digest[MD5_DIGEST_LENGTH];
//
//      MD5_Final(digest, (MD5_CTX*)&ctx);
//
//      str = ::hex::lower_from(digest, MD5_DIGEST_LENGTH);
//
//   }
//
//
//   CLASS_DECL_APEX void from(string& str, const WHIRLPOOL_CTX& ctx)
//   {
//
//      unsigned char digest[WHIRLPOOL_DIGEST_LENGTH];
//
//      WHIRLPOOL_Final(digest, (WHIRLPOOL_CTX*)&ctx);
//
//      str = ::hex::lower_from(digest, WHIRLPOOL_DIGEST_LENGTH);
//
//   }
//
//
//   void md5(void* ptarget, const void* psource, ::memsize size)
//   {
//
//      MD5((const unsigned char*)psource, size, (unsigned char*)ptarget);
//
//   }
//
//
//   void sha1(void* ptarget, const void* psource, ::memsize size)
//   {
//
//      SHA1((const unsigned char*)psource, size, (unsigned char*)ptarget);
//
//   }
//
//
//   void sha256(void* ptarget, const void* psource, ::memsize size)
//   {
//
//      SHA256((const unsigned char*)psource, size, (unsigned char*)ptarget);
//
//   }
//
//
//} // namespace str







#include <zlib.h>

#define CA4_BASE_HASH_DIGEST_LENGTH 32

#define CA4_CRYPT_V5_FINAL_HASH_BYTES 1024
#define CA4_CRYPT_V5_SALT_BYTES (CA4_CRYPT_V5_FINAL_HASH_BYTES - CA4_BASE_HASH_DIGEST_LENGTH)

string chunk_split(const string& body, i32 chunklen = 76, const string& end = "\r\n");
namespace crypto
{


   crypto::crypto()
   {
   }

   crypto::~crypto()
   {
   }




   bool crypto::decrypt(memory& storageDecrypt, const memory& storageEncrypt, const char* pszSalt)
   {

      // default implementation - OS may implement its own HOME/UserDir encryption

      string str = defer_get_cryptkey();

      if (str.is_empty())
         return false;

      str += pszSalt;

      memory key;

      key.from_string(str);

      return decrypt(storageDecrypt, storageEncrypt, key);

   }

   bool crypto::encrypt(memory& storageEncrypt, const memory& storageDecrypt, const char* pszSalt)
   {

      // default implementation - OS may implement its own HOME/UserDir encryption

      string str = defer_get_cryptkey();

      if (str.is_empty())
         return false;

      str += pszSalt;

      memory key;

      key.from_string(str);

      return encrypt(storageEncrypt, storageDecrypt, key);

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

   /**
   AES encryption/decryption demo program using OpenSSL EVP apis
   gcc -Wall openssl_aes.ca -lcrypto

   this is public domain code.

   Saju Pillai (saju.pillai@gmail.com)
   **/
   //http://stackoverflow.com/questions/10366950/openssl-using-evp-vs-algorithm-api-for-symmetric-crypto

   bool crypto::encrypt(memory& storageEncrypt, const memory& storageDecrypt, const memory& memKeyData)
   {

      memory memSha1(this);

      nessie(memSha1, memKeyData);

      memory iv;

      iv.set_size(32);

      iv.set(0);

#ifdef HAVE_OPENSSL


      i32 plainlen = (i32)storageDecrypt.get_size();

      i32 cipherlen, tmplen;

      EVP_CIPHER_CTX* pctx = EVP_CIPHER_CTX_new();

      EVP_EncryptInit(pctx, EVP_aes_256_ecb(), memSha1.get_data(), iv.get_data());

      cipherlen = (i32)(storageDecrypt.get_size() + EVP_CIPHER_CTX_block_size(pctx));

      storageEncrypt.set_size(cipherlen);

      storageEncrypt.set(0);

      if (!EVP_EncryptUpdate(pctx, storageEncrypt.get_data(), &cipherlen, storageDecrypt.get_data(), plainlen))
      {

         storageEncrypt.set(0);

         storageEncrypt.set_size(0);

#if OPENSSL_API_COMPAT < 0x10100000L

         EVP_CIPHER_CTX_cleanup(pctx);

#else

         EVP_CIPHER_CTX_reset(pctx);

#endif

         return false;

      }

      if (!EVP_EncryptFinal(pctx, storageEncrypt.get_data() + cipherlen, &tmplen))
      {

         storageEncrypt.set(0);

         storageEncrypt.set_size(0);

#if OPENSSL_API_COMPAT < 0x10100000L

         EVP_CIPHER_CTX_cleanup(pctx);

#else

         EVP_CIPHER_CTX_reset(pctx);

#endif

         return false;

      }

      cipherlen += tmplen;

      storageEncrypt.set_size(cipherlen);

#if OPENSSL_API_COMPAT < 0x10100000L

      EVP_CIPHER_CTX_cleanup(pctx);

#else

      EVP_CIPHER_CTX_reset(pctx);

#endif

      return true;


#elif defined(_UWP)

      ::winrt::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider^ cipher =
         ::winrt::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider::OpenAlgorithm(::winrt::Windows::Security::Cryptography::Core::SymmetricAlgorithmNames::AesEcb);

      ::winrt::Windows::Security::Cryptography::Core::CryptographicKey^ cipherkey = cipher->CreateSymmetricKey(memSha1.get_os_crypt_buffer());

      storageEncrypt.set_os_crypt_buffer(::winrt::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(cipherkey, storageDecrypt.get_os_crypt_buffer(), iv.get_os_crypt_buffer()));

      return true;

#elif defined(MACOS)

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(nullptr, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeAES);

      CFDataRef keyData = memSha1.get_os_cf_data();

      CFErrorRef error = nullptr;

      SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);

      if (error != nullptr)
      {

         CFRelease(error);

         CFRelease(keyData);

         CFRelease(parameters);

         return false;

      }

      SecTransformRef transform = SecEncryptTransformCreate(key, &error);

      if (error != nullptr)
      {

         CFRelease(error);

         CFRelease(key);

         CFRelease(keyData);

         CFRelease(parameters);

         return false;

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if (error != nullptr)
      {

         CFRelease(transform);

         CFRelease(keyData);

         CFRelease(parameters);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      CFDataRef dataIv = iv.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecIVKey, dataIv, &error);

      if (error != nullptr)
      {

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      CFDataRef dataIn = storageDecrypt.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(dataIv);

         CFRelease(transform);

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(key);

         CFRelease(error);

         return false;

      }

      memory memory;

      storageEncrypt.set_os_cf_data(data);

      CFRelease(data);

      CFRelease(dataIv);

      CFRelease(dataIn);

      CFRelease(transform);

      CFRelease(keyData);

      CFRelease(parameters);

      CFRelease(key);

      return true;


#endif

   }


   bool crypto::decrypt(memory& storageDecrypt, const memory& storageEncrypt, const memory& memKeyData)
   {

      memory memSha1;

      nessie(memSha1, memKeyData);

      memory iv;

      iv.set_size(32);

      iv.set(0);

#if defined(_UWP) && !defined(HAVE_OPENSSL)

      ::winrt::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider^ cipher =
         ::winrt::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider::OpenAlgorithm(::winrt::Windows::Security::Cryptography::Core::SymmetricAlgorithmNames::AesEcb);

      ::winrt::Windows::Security::Cryptography::Core::CryptographicKey^ cipherkey = cipher->CreateSymmetricKey(memSha1.get_os_crypt_buffer());

      storageDecrypt.set_os_crypt_buffer(::winrt::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(cipherkey, storageDecrypt.get_os_crypt_buffer(), iv.get_os_crypt_buffer()));

      return true;

      //#elif defined(MACOS)
      //
      //      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(nullptr, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);
      //
      //      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeAES);
      //
      //      CFDataRef keyData = memSha1.get_os_cf_data();
      //
      //      CFErrorRef error = nullptr;
      //
      //      SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);
      //
      //      if(error != nullptr)
      //      {
      //
      //         CFRelease(error);
      //
      //         CFRelease(keyData);
      //
      //         CFRelease(parameters);
      //
      //         return false;
      //
      //      }
      //
      //      SecTransformRef transform = SecDecryptTransformCreate(key, &error);
      //
      //      if(error != nullptr)
      //      {
      //
      //         CFRelease(error);
      //
      //         CFRelease(key);
      //
      //         CFRelease(keyData);
      //
      //         CFRelease(parameters);
      //
      //         return false;
      //
      //      }
      //
      //      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);
      //
      //      if(error != nullptr)
      //      {
      //
      //         CFRelease(transform);
      //
      //         CFRelease(keyData);
      //
      //         CFRelease(parameters);
      //
      //         CFRelease(key);
      //
      //         CFRelease(error);
      //
      //         return false;
      //
      //      }
      //
      //      CFDataRef dataIv = iv.get_os_cf_data();
      //
      //      SecTransformSetAttribute(transform, kSecIVKey, dataIv, &error);
      //
      //      if(error != nullptr)
      //      {
      //
      //         CFRelease(dataIv);
      //
      //         CFRelease(transform);
      //
      //         CFRelease(parameters);
      //
      //         CFRelease(keyData);
      //
      //         CFRelease(key);
      //
      //         CFRelease(error);
      //
      //         return false;
      //
      //      }
      //
      //      CFDataRef dataIn = storageEncrypt.get_os_cf_data();
      //
      //      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);
      //
      //      if(error != nullptr)
      //      {
      //
      //         CFRelease(dataIn);
      //
      //         CFRelease(dataIv);
      //
      //         CFRelease(transform);
      //
      //         CFRelease(parameters);
      //
      //         CFRelease(keyData);
      //
      //         CFRelease(key);
      //
      //         CFRelease(error);
      //
      //         return false;
      //
      //      }
      //
      //      /* Encrypt the data. */
      //
      //      CFDataRef data = (CFDataRef) SecTransformExecute(transform, &error);
      //
      //      if(error != nullptr)
      //      {
      //
      //         CFRelease(dataIn);
      //
      //         CFRelease(dataIv);
      //
      //         CFRelease(transform);
      //
      //         CFRelease(parameters);
      //
      //         CFRelease(keyData);
      //
      //         CFRelease(key);
      //
      //         CFRelease(error);
      //
      //         return false;
      //
      //      }
      //
      //      memory memory;
      //
      //      storageDecrypt.set_os_cf_data(data);
      //
      //      CFRelease(data);
      //
      //      CFRelease(dataIv);
      //
      //      CFRelease(dataIn);
      //
      //      CFRelease(transform);
      //
      //      CFRelease(keyData);
      //
      //      CFRelease(parameters);
      //
      //      CFRelease(key);
      //
      //      return true;

#else

      i32 cipherlen = (i32)storageEncrypt.get_size();

      i32 plainlen, tmplen;

      EVP_CIPHER_CTX* pctx = EVP_CIPHER_CTX_new();



      int iKeyLen = EVP_CIPHER_key_length(EVP_aes_256_ecb());
      memsize iShaLen = memSha1.get_size();

      if (iShaLen <= 0)
      {

         return false;

      }

      EVP_DecryptInit(pctx, EVP_aes_256_ecb(), memSha1.get_data(), iv.get_data());

      plainlen = (i32)storageEncrypt.get_size() + EVP_CIPHER_CTX_block_size(pctx);

      storageDecrypt.set_size(plainlen);

      if (!EVP_DecryptUpdate(pctx, storageDecrypt.get_data(), &plainlen, storageEncrypt.get_data(), cipherlen))
      {

         storageDecrypt.set(0);

         storageDecrypt.set_size(0);

         EVP_CIPHER_CTX_free(pctx);

         return false;

      }

      if (!EVP_DecryptFinal(pctx, storageDecrypt.get_data() + plainlen, &tmplen))
      {

         storageDecrypt.set(0);

         storageDecrypt.set_size(0);

         EVP_CIPHER_CTX_free(pctx);

         return false;

      }

      plainlen += tmplen;

      storageDecrypt.set_size(plainlen);

      EVP_CIPHER_CTX_free(pctx);

      return true;

#endif

   }

   string crypto::strkey()
   {
      memory storage;
      key(storage);

      //auto psystem = get_system()->m_papexsystem;

      auto psystem = m_psystem;

      auto pbase64 = psystem->base64();

      return pbase64->encode(storage);

   }


   i32 crypto::encrypt(string& strEncrypt, const char* pszDecrypt, const char* pszKey)
   {
      memory storageDecrypt;
      memory storageEncrypt;
      memory storageKey;
      if (pszDecrypt == nullptr || strlen(pszDecrypt) == 0)
      {
         strEncrypt = "";
         return 0;
      }
      storageDecrypt.from_string(pszDecrypt);

      auto psystem = m_psystem;

      auto pbase64 = psystem->base64();

      pbase64->decode(storageKey, pszKey);

      i32 cipherlen = encrypt(storageEncrypt, storageDecrypt, storageKey);

      strEncrypt = pbase64->encode(storageEncrypt);

      return cipherlen;

   }


   i32 crypto::decrypt(string& strDecrypt, const char* pszEncrypt, const char* pszKey)
   {

      memory storageEncrypt;

      memory storageDecrypt;

      memory storageKey;

      auto psystem = m_psystem;

      auto pbase64 = psystem->base64();

      pbase64->decode(storageEncrypt, pszEncrypt);

      pbase64->decode(storageKey, pszKey);

      i32 plainlen = decrypt(storageDecrypt, storageEncrypt, storageKey);

      strDecrypt = storageDecrypt.get_string();

      return plainlen;

   }


   u32 crypto::crc32(u32 dwPrevious, const char* psz)
   {

      return (::u32)::crc32(dwPrevious, (const Bytef*)psz, (::u32)strlen(psz));

   }


   string crypto::md5(const char* psz)
   {

      memory mem;

      mem.assign(psz, strlen(psz));

      return md5(mem);

   }


   string crypto::sha1(const char* psz)
   {

      memory mem;

      mem.assign(psz, strlen(psz));

      return sha1(mem);

   }


   string crypto::nessie(const char* psz)
   {

      memory mem;

      mem.assign(psz, strlen(psz));

      return nessie(mem);

   }


   string crypto::md5(const memory& mem)
   {

      memory memMd5;

      md5(memMd5, mem);

      return memMd5.to_hex();


   }



   string crypto::sha1(const memory& mem)
   {

      memory memSha1;

      sha1(memSha1, mem);

      return memSha1.to_hex();

   }

   string crypto::nessie(const memory& mem)
   {

      memory memNessie;

      nessie(memNessie, mem);

      return memNessie.to_hex();

   }


   int crypto::get_md5_digest_length() const
   {

      return 16;

   }


   int crypto::get_sha1_digest_length() const
   {

      return 20;

   }


   int crypto::get_sha256_digest_length() const
   {

      return 32;

   }


   int crypto::get_nessie_digest_length() const
   {

      return 64;

   }


   void crypto::hash(memory& memMd5, const block & block, enum_hash ehash)
   {

      auto palgorithm = __hasher_algorithm(ehash);

      palgorithm->hash(memMd5, block);

   }

   void crypto::md5(memory& memMd5, const block & block)
   {

      hash(memMd5, block, e_hash_md5);

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

   }


   void crypto::sha1(memory& memSha1, const block & block)
   {

      hash(memSha1, block, e_hash_sha1);

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

   }


   void crypto::sha256(memory& memSha256, const block & block)
   {

      hash(memSha256, block, e_hash_sha256);

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

   }


   void crypto::nessie(memory& memNessie, const block & block)
   {

      //memNessie.set_size(get_nessie_digest_length());

      //nessie(memNessie.get_data(), mem.get_data(), (size_t)mem.get_size());

   }


   bool crypto::file_set(::payload payloadFile, const char* pszData, const char* pszSalt, ::application* papp)
   {

      memory memoryEncrypt;

      if (!encrypt(memoryEncrypt, pszData, pszSalt))
      {

         return false;

      }

      if (!m_pcontext->m_papexcontext->file().put_contents(payloadFile, memoryEncrypt))
      {

         return false;

      }

      return true;

   }


   void     crypto::file_get(::payload payloadFile, string& str, const char* pszSalt, ::application* papp)
   {

      memory memoryEncrypt;

      if (!m_pcontext->m_papexcontext->file().exists(payloadFile))
      {
         str.Empty();
         return success_not_found;
      }

      if (!m_pcontext->m_papexcontext->file().as_memory(payloadFile, memoryEncrypt))
      {
         return error_file;
      }
      if (!decrypt(str, memoryEncrypt, pszSalt))
      {
         str.Empty();
         return error_decryption;
      }
      return ::success;
   }

   bool crypto::encrypt(memory& storageEncrypt, const char* pszDecrypt, const char* pszSalt)
   {
      memory memoryDecrypt;
      memoryDecrypt.from_asc(pszDecrypt);
      return encrypt(storageEncrypt, memoryDecrypt, pszSalt);
   }

   bool crypto::decrypt(string& strDecrypt, const memory& storageEncrypt, const char* pszSalt)
   {
      memory memoryDecrypt;
      if (!decrypt(memoryDecrypt, storageEncrypt, pszSalt))
         return false;
      memoryDecrypt.to_asc(strDecrypt);
      return true;
   }


   // get a new salt - 8 hexadecimal characters long
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
         return false;
      return ::str::has_all_v1(pszPassword);
   }

   string crypto::v5_get_password_hash(const char* pszPassword, i32 iOrder)
   {
      return v5_get_password_hash(v5_get_password_salt(), pszPassword, iOrder);
   }



   void crypto::hmac(void* result, const memory& memMessage, const memory& memKey)
   {

#ifndef _UWP

      unsigned int md_len = 0;

      HMAC(EVP_sha1(), memKey.get_data(), int(memKey.get_size()), memMessage.get_data(), (size_t)memMessage.get_size(), (unsigned char*)result, &md_len);

#endif

   }




   void crypto::hmac(void* result, const string& strMessage, const string& strKey)
   {

#ifndef _UWP

      unsigned int md_len = 0;

      HMAC(EVP_sha1(), strKey.c_str(), int(strKey.length()), (const unsigned char*)(const char*)strMessage, (size_t)strMessage.length(), (unsigned char*)result, &md_len);

#endif

   }


   ::file::path crypto::get_crypt_key_file_path()
   {

      return m_psystem->m_pacmedirectory->system() / "user" / "databin.bin";

   }


   string crypto::defer_get_cryptkey()
   {

      string strPath = get_crypt_key_file_path();

      string str = m_pcontext->m_papexcontext->file().as_string(strPath);

      if (str.has_char())
      {

         return str;

      }

      int iLength = 256;

      generate_random_alphanumeric(str.get_string_buffer(iLength), iLength);

      m_pcontext->m_papexcontext->file().put_contents(strPath, str);

      return str;


   }


#ifdef MACOS_DEPRECATED


   SecKeyRef crypto::get_new_rsa_key()
   {

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(nullptr, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

      CFDictionaryAddValue(parameters, kSecAttrKeySizeInBits, (CFTypeRef)1024);

      SecKeyRef prsa = SecKeyGenerateSymmetric(parameters, nullptr);

      if (prsa == nullptr)
         return;

      CFRelease(parameters);

      return rsa;

   }

   void crypto::free_rsa_key(SecKeyRef prsa)
   {

      CFRelease(prsa);

   }


#elif defined(HAVE_OPENSSL)




#else


   __pointer(::crypto::rsa) crypto::generate_rsa_key()
   {

      ::winrt::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider^ provider =
         ::winrt::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider::OpenAlgorithm(
            ::winrt::Windows::Security::Cryptography::Core::AsymmetricAlgorithmNames::RsaPkcs1);


      return __new(::crypto::rsa(get_app(), provider->CreateKeyPair(1024)));

   }

   /*void crypto::free_rsa_key(__pointer(::crypto::rsa) prsa)
   {

      __UNREFERENCED_PARAMETER(prsa);

   }*/

#endif

   void crypto::err_load_rsa_strings()
   {
//#if defined(HAVE_OPENSSL)
//      ERR_load_RSA_strings();
//
//#endif

   }


   void crypto::err_load_crypto_strings()
   {

#if defined(HAVE_OPENSSL)

#if OPENSSL_API_COMPAT < 0x10100000L

      ERR_load_crypto_strings();

#else

      //      OPENSSL_init_crypto(OPENSSL_INIT_LOAD_CRYPTO_STRINGS, nullptr);

#endif

#endif

   }


   rsa::rsa()
   {

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

      auto prsa = __create_rsa(strRsa);

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

      auto prsa = __create_rsa(strRsa);

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

      auto prsa = __create_rsa(strRsa);

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


   void crypto::np_make_zigbert_rsa(const string& strDir, const string& strSignerPath, const string& strKeyPath, const string& strOthersPath, const string& strSignature)
   {

#if !defined(_UWP) && defined(HAVE_OPENSSL)

      X509* signer = nullptr;
      {
         string strSigner = m_pcontext->m_papexcontext->file().as_string(strSignerPath);
         BIO* pbio = BIO_new_mem_buf((void*)(const char *)strSigner, (i32)strSigner.get_length());
         //signer = PEM_read_bio_X509_AUX(pbio, nullptr, 0, nullptr);
         signer = PEM_read_bio_X509(pbio, nullptr, 0, nullptr);
         BIO_free(pbio);
      }

      EVP_PKEY* pkey;
      {
         string strKey = m_pcontext->m_papexcontext->file().as_string(strKeyPath);
         BIO* pbio = BIO_new_mem_buf((void*)(const char *)strKey, (i32)strKey.get_length());
         pkey = PEM_read_bio_PrivateKey(pbio, nullptr, nullptr, nullptr);
         BIO_free(pbio);
      }


      stack_st_X509* pstack509 = nullptr;
      {
         string strOthers = m_pcontext->m_papexcontext->file().as_string(strOthersPath);
         address_array < X509* > xptra;
         strsize iStart = 0;
         strsize iFind;
         string strEnd = "-----END CERTIFICATE-----";
         string strCertificate;
         strsize iEndLen = strEnd.get_length();
         ::count iCount = 0;
         while ((iFind = strOthers.find("-----BEGIN CERTIFICATE-----", iStart)) >= 0)
         {
            strsize iEnd = strOthers.find(strEnd, iFind);
            if (iEnd < 0)
               break;
            strCertificate = strOthers.Mid(iFind, iEnd + iEndLen - iFind);
            X509* x;
            BIO* pbio = BIO_new(BIO_s_mem());
            BIO_puts(pbio, strCertificate);
            //x = PEM_read_bio_X509_AUX(pbio, nullptr, 0, nullptr);
            x = PEM_read_bio_X509(pbio, nullptr, 0, nullptr);
            BIO_free(pbio);
            if (x == nullptr)
            {
               return;
            }
            xptra.add(x);
            iCount++;
            iStart = iEnd + iEndLen;
         }
         pstack509 = sk_X509_new_null();

         for (i32 i = 0; i < xptra.get_count(); i++)
         {
            sk_X509_push(pstack509, xptra[i]);
         }
      }

      BIO* input = BIO_new_mem_buf((void*)(const char *)strSignature, (i32)strSignature.get_length());

      PKCS7* pkcs7 = PKCS7_sign(signer, pkey, pstack509, input, PKCS7_BINARY | PKCS7_DETACHED);

      BIO_free(input);
      sk_X509_free(pstack509);
      EVP_PKEY_free(pkey);
      X509_free(signer);

      BIO* output = BIO_new(BIO_s_mem());

      i2d_PKCS7_bio(output, pkcs7);

      char* pchData = nullptr;
      long count = BIO_get_mem_data(output, &pchData);

      m_pcontext->m_papexcontext->file().put_contents(strDir / "META-INF/zigbert.rsa", pchData, count);

      BIO_free(output);
      PKCS7_free(pkcs7);
#endif
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

      str = memory.get_string();

      return str;

   }


   __pointer(::crypto::rsa) crypto::generate_rsa_key()
   {

      auto popensslrsa = __new(::crypto_openssl::rsa);

      throw todo;


//
//      RSA*& prsa = popensslrsa->m_prsa;
//
//      prsa = RSA_new();
//
//      {
//
//         BIGNUM* e = BN_new();
//
//         BN_set_word(e, 65537);
//
//         int ret = RSA_generate_key_ex(prsa, 1024, e, nullptr);
//
//         if (ret != 1)
//         {
//
//            BN_free(e);
//
//            return nullptr;
//
//         }
//
//         BN_free(e);
//
//      }
//
//#if OPENSSL_VERSION_NUMBER < 0x10100000L
//
//      char* hexN = BN_bn2hex(prsa->n);
//      char* hexE = BN_bn2hex(prsa->e);
//      char* hexD = BN_bn2hex(prsa->d);
//      char* hexP = BN_bn2hex(prsa->p);
//      char* hexQ = BN_bn2hex(prsa->q);
//      char* hexDmp1 = BN_bn2hex(prsa->dmp1);
//      char* hexDmq1 = BN_bn2hex(prsa->dmq1);
//      char* hexIqmp = BN_bn2hex(prsa->iqmp);
//
//#else
//
//      const BIGNUM* n = nullptr;
//      const BIGNUM* e = nullptr;
//      const BIGNUM* d = nullptr;
//      const BIGNUM* p = nullptr;
//      const BIGNUM* q = nullptr;
//      const BIGNUM* dmp1 = nullptr;
//      const BIGNUM* dmq1 = nullptr;
//      const BIGNUM* iqmp = nullptr;
//
//      RSA_get0_key(prsa, &n, &e, &d);
//      RSA_get0_factors(prsa, &p, &q);
//      RSA_get0_crt_params(prsa, &dmp1, &dmq1, &iqmp);
//
//      char* hexN = BN_bn2hex(n);
//      char* hexE = BN_bn2hex(e);
//      char* hexD = BN_bn2hex(d);
//      char* hexP = BN_bn2hex(p);
//      char* hexQ = BN_bn2hex(q);
//      char* hexDmp1 = BN_bn2hex(dmp1);
//      char* hexDmq1 = BN_bn2hex(dmq1);
//      char* hexIqmp = BN_bn2hex(iqmp);
//
//#endif
//
//      popensslrsa->n = hexN;
//      popensslrsa->e = hexE;
//      popensslrsa->d = hexD;
//      popensslrsa->p = hexP;
//      popensslrsa->q = hexQ;
//      popensslrsa->dmp1 = hexDmp1;
//      popensslrsa->dmq1 = hexDmq1;
//      popensslrsa->iqmp = hexIqmp;
//
//      OPENSSL_free(hexN);
//      OPENSSL_free(hexE);
//      OPENSSL_free(hexD);
//      OPENSSL_free(hexP);
//      OPENSSL_free(hexQ);
//      OPENSSL_free(hexDmp1);
//      OPENSSL_free(hexDmq1);
//      OPENSSL_free(hexIqmp);
//
//      return popensslrsa;

      return nullptr;

   }


   __pointer(rsa) crypto::read_priv_pem(const string& strFile)
   {

      auto memory = m_psystem->m_pacmefile->as_memory(strFile);

      if (memory.is_empty())
      {

         return nullptr;

      }

      auto popensslrsa = __new(::crypto_openssl::rsa);

      throw todo;

      return nullptr;

      //RSA*& prsa = popensslrsa->m_prsa;

      //auto pbio = BIO_new_mem_buf(memory.get_data(), (int) memory.get_size());

      //PEM_read_bio_RSAPrivateKey(pbio, &prsa, nullptr, nullptr);

      //BIO_free(pbio);

      //return popensslrsa;

   }


   __pointer(rsa) crypto::read_pub_pem(const string& strFile)
   {

      auto memory = m_psystem->m_pacmefile->as_memory(strFile);

      if (memory.is_empty())
      {

         return nullptr;

      }

      auto popensslrsa = __new(::openssl::rsa);

      RSA*& prsa = popensslrsa->m_prsa;

      auto pbio = BIO_new_mem_buf(memory.get_data(), (int) memory.get_size());

      PEM_read_bio_RSA_PUBKEY(pbio, &prsa, nullptr, nullptr);

      BIO_free(pbio);

      return popensslrsa;

   }


} // namespace crypto




void
stunCalculateIntegrity_longterm(char* hmac, const char* input, i32 length,
   const char* username, const char* realm, const char* password)
{

#if !defined(_UWP) || defined(HAVE_OPENSSL)
   u32 resultSize = 0;
   uchar HA1[16];
   char HA1_text[1024];

   snprintf(HA1_text, sizeof(HA1_text), "%s:%s:%s", username, realm, password);
   MD5((uchar*)HA1_text, strlen(HA1_text), HA1);

   HMAC(EVP_sha1(),
      HA1, 16,
      (const uchar*)input, length,
      (uchar*)hmac, &resultSize);
#endif
}

void
stunCalculateIntegrity_shortterm(char* hmac, const char* input, i32 length, const char* key)
{
#if !defined(_UWP) || defined(HAVE_OPENSSL)
   u32 resultSize = 0;
   HMAC(EVP_sha1(),
      key, (int)strlen(key),
      (const uchar*)input, length,
      (uchar*)hmac, &resultSize);
#endif
}

void hmac_evp_sha1_1234(unsigned char* hmac, unsigned int* hmacSize, const unsigned char* buf, size_t bufLen)
{
#if !defined(_UWP) || defined(HAVE_OPENSSL)

   HMAC(EVP_sha1(),
      "1234", 4,
      (const uchar*)buf, bufLen - 20 - 4,
      hmac, hmacSize);
#endif

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
