#include "framework.h"

#if defined(HAVE_OPENSSL)

#include <openssl/rsa.h>
#include <openssl/md5.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/crypto.h>
#include <openssl/hmac.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <openssl/whrlpool.h>




#include <openssl/ssl.h>

#endif

#define CA4_CRYPT_V5_FINAL_HASH_BYTES (WHIRLPOOL_DIGEST_LENGTH * 16)
#define CA4_CRYPT_V5_SALT_BYTES (CA4_CRYPT_V5_FINAL_HASH_BYTES - WHIRLPOOL_DIGEST_LENGTH)

string chunk_split(const string & body,i32 chunklen = 76,const string & end = "\r\n");
namespace crypto
{


   crypto::crypto()
   {
   }

   crypto::~crypto()
   {
   }


   bool crypto::decrypt(memory & storageDecrypt, const memory & storageEncrypt, const char * pszSalt)
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

   bool crypto::encrypt(memory & storageEncrypt, const memory & storageDecrypt, const char * pszSalt)
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



   i32 crypto::key(memory & storage)
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

   bool crypto::encrypt(memory & storageEncrypt, const memory & storageDecrypt, const memory & memKeyData)
   {

      memory memSha1(get_context_object());

      nessie(memSha1,memKeyData);

      memory iv;

      iv.set_size(32);

      iv.set(0);

#ifdef HAVE_OPENSSL


      i32 plainlen = (i32)storageDecrypt.get_size();

      i32 cipherlen,tmplen;

      EVP_CIPHER_CTX * pctx = EVP_CIPHER_CTX_new();

      EVP_EncryptInit(pctx,EVP_aes_256_ecb(),memSha1.get_data(),iv.get_data());

      cipherlen = (i32)(storageDecrypt.get_size() + EVP_CIPHER_CTX_block_size(pctx));

      storageEncrypt.set_size(cipherlen);

      storageEncrypt.set(0);

      if(!EVP_EncryptUpdate(pctx,storageEncrypt.get_data(),&cipherlen,storageDecrypt.get_data(),plainlen))
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

      if(!EVP_EncryptFinal(pctx,storageEncrypt.get_data() + cipherlen,&tmplen))
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

      ::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider ^ cipher =
      ::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::SymmetricAlgorithmNames::AesEcb);

      ::Windows::Security::Cryptography::Core::CryptographicKey ^ cipherkey = cipher->CreateSymmetricKey(memSha1.get_os_crypt_buffer());

      storageEncrypt.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(cipherkey, storageDecrypt.get_os_crypt_buffer(), iv.get_os_crypt_buffer()));

      return true;

#elif defined(MACOS)

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(nullptr, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeAES);

      CFDataRef keyData = memSha1.get_os_cf_data();

      CFErrorRef error = nullptr;

      SecKeyRef key = SecKeyCreateFromData(parameters, keyData, &error);

      if(error != nullptr)
      {

         CFRelease(error);

         CFRelease(keyData);

         CFRelease(parameters);

         return false;

      }

      SecTransformRef transform = SecEncryptTransformCreate(key, &error);

      if(error != nullptr)
      {

         CFRelease(error);

         CFRelease(key);

         CFRelease(keyData);

         CFRelease(parameters);

         return false;

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if(error != nullptr)
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

      if(error != nullptr)
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

      if(error != nullptr)
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

      CFDataRef data = (CFDataRef) SecTransformExecute(transform, &error);

      if(error != nullptr)
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


   bool crypto::decrypt(memory & storageDecrypt, const memory & storageEncrypt, const memory & memKeyData)
   {

      memory memSha1;

      nessie(memSha1, memKeyData);

      memory iv;

      iv.set_size(32);

      iv.set(0);

#if defined(_UWP) && !defined(HAVE_OPENSSL)

      ::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider ^ cipher =
      ::Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::SymmetricAlgorithmNames::AesEcb);

      ::Windows::Security::Cryptography::Core::CryptographicKey ^ cipherkey = cipher->CreateSymmetricKey(memSha1.get_os_crypt_buffer());

      storageDecrypt.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(cipherkey, storageDecrypt.get_os_crypt_buffer(), iv.get_os_crypt_buffer()));

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

      EVP_CIPHER_CTX * pctx = EVP_CIPHER_CTX_new();



      int iKeyLen = EVP_CIPHER_key_length(EVP_aes_256_ecb());
      memsize iShaLen = memSha1.get_size();

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
      return System.base64().encode(storage);
   }

   i32 crypto::encrypt(string & strEncrypt, const char * pszDecrypt, const char * pszKey)
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
      System.base64().decode(storageKey, pszKey);
      i32 cipherlen = encrypt(storageEncrypt, storageDecrypt, storageKey);
      strEncrypt = System.base64().encode(storageEncrypt);
      return cipherlen;
   }

   i32 crypto::decrypt(string & strDecrypt, const char * pszEncrypt, const char * pszKey)
   {

      memory storageEncrypt;

      memory storageDecrypt;

      memory storageKey;

      System.base64().decode(storageEncrypt, pszEncrypt);

      System.base64().decode(storageKey, pszKey);

      i32 plainlen = decrypt(storageDecrypt, storageEncrypt, storageKey);
      
      storageDecrypt.to_string(strDecrypt);
      
      return plainlen;

   }


   string crypto::md5(const char * psz)
   {

      memory mem;

      mem.assign(psz,strlen(psz));

      return md5(mem);

   }


   string crypto::sha1(const char * psz)
   {

      memory mem;

      mem.assign(psz,strlen(psz));

      return sha1(mem);

   }


   string crypto::nessie(const char * psz)
   {

      memory mem;

      mem.assign(psz,strlen(psz));

      return nessie(mem);

   }


   string crypto::md5(const memory & mem)
   {

      memory memMd5;

      md5(memMd5, mem);

      return memMd5.to_hex();


   }



   string crypto::sha1(const memory & mem)
   {

      memory memSha1;

      sha1(memSha1, mem);

      return memSha1.to_hex();

   }

   string crypto::nessie(const memory & mem)
   {

      memory memNessie;

      nessie(memNessie,mem);

      return memNessie.to_hex();

   }


   void crypto::md5(memory & memMd5,const memory & mem)
   {

//#ifdef _UWP
//
//      __throw(interface_only_exception());
//
//#else

      memMd5.set_size(MD5_DIGEST_LENGTH);

      MD5(mem.get_data(),(size_t) mem.get_size(),memMd5.get_data());

//#endif

   }


   void crypto::sha1(memory & memSha1, const memory & mem)
   {

//#ifdef _UWP
//
//      __throw(interface_only_exception());
//
//#else

      memSha1.set_size(SHA_DIGEST_LENGTH);

      SHA1(mem.get_data(), (size_t)mem.get_size(), memSha1.get_data());

//#endif

   }

   void crypto::sha256(memory & memSha256, const memory & mem)
   {

      //#ifdef _UWP
      //
      //      __throw(interface_only_exception());
      //
      //#else

      memSha256.set_size(SHA256_DIGEST_LENGTH); // 32 bytes (2^5 * 2^3) (32*8) (2^(5+3)) (256 bits)

      // 10^2 * 10^3 = 10^5 = 100.000 = 10 * 10 * 10 * 10 * 10

      SHA256(mem.get_data(), (size_t)mem.get_size(), memSha256.get_data());

      //#endif

   }
   void crypto::nessie(memory & memNessie,const memory & mem)
   {

      memNessie.set_size(WHIRLPOOL_DIGEST_LENGTH);

      WHIRLPOOL(mem.get_data(), (size_t)mem.get_size(),memNessie.get_data());

   }




   bool crypto::file_set(var varFile, const char * pszData, const char * pszSalt, ::aura::application * papp)
   {
      memory memoryEncrypt;
      if (!encrypt(memoryEncrypt, pszData, pszSalt))
      {
         return false;
      }
      if (!Context.file().put_contents(varFile, memoryEncrypt))
      {
         return false;
      }
      return true;
   }


   ::estatus     crypto::file_get(var varFile, string & str, const char * pszSalt, ::aura::application * papp)
   {

      memory memoryEncrypt;

      if (!Context.file().exists(varFile))
      {
         str.Empty();
         return success_not_found;
      }

      if (!Context.file().as_memory(varFile, memoryEncrypt))
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

   bool crypto::encrypt(memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt)
   {
      memory memoryDecrypt;
      memoryDecrypt.from_asc(pszDecrypt);
      return encrypt(storageEncrypt, memoryDecrypt, pszSalt);
   }

   bool crypto::decrypt(string & strDecrypt, const memory & storageEncrypt, const char * pszSalt)
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
      for(i32 i = 0; i < CA4_CRYPT_V5_FINAL_HASH_BYTES - WHIRLPOOL_DIGEST_LENGTH; i += 2)
      {
         i64 iDigit = __random<char>();
         strFormat.Format("%02x", iDigit);
         strSalt += strFormat;
      }
      return strSalt;
   }

   // calculate the hash from a salt and a password
   // slow hash is more secure for personal attack possibility (strong fast hashs are only good for single transactional operations and not for a possibly lifetime password)
   string crypto::v5_get_password_hash(const char * pszSalt, const char * pszPassword, i32 iOrder)
   {
      string strHash(pszPassword);
      string strSalt(pszSalt);
      strSalt = strSalt.Left(CA4_CRYPT_V5_SALT_BYTES);
      for(i32 i = iOrder; i < CA4_CRYPT_V5_FINAL_HASH_BYTES - WHIRLPOOL_DIGEST_LENGTH; i++)
      {
         string strStepSalt = strSalt.Mid(i) + strSalt.Left(i);
         strHash = nessie(strStepSalt + strHash).lowered();
      }
      return strSalt + strHash;
   }

   string crypto::v5_get_passhash(const char * pszSalt, const char * pszPassword, i32 iMaxOrder)
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

   bool crypto::v5_compare_password(const char * pszPassword, const char * pszHash, i32 iOrder)
   {
      string strHash(pszHash);
      string strSalt = strHash.Left(CA4_CRYPT_V5_SALT_BYTES);
      return strHash == v5_get_password_hash(strSalt, pszPassword, iOrder);
   }

   bool crypto::v5_validate_plain_password(const char * pszPassword)
   {
      string str(pszPassword);
      if (str.get_length() < 6)
         return false;
      return ::str::has_all_v1(pszPassword);
   }

   string crypto::v5_get_password_hash(const char * pszPassword, i32 iOrder)
   {
      return v5_get_password_hash(v5_get_password_salt(), pszPassword, iOrder);
   }



   void crypto::hmac(void * result, const memory & memMessage, const memory & memKey)
   {

//#ifndef _UWP

      unsigned int md_len = 0;

      HMAC(EVP_sha1(), memKey.get_data(), int(memKey.get_size()), memMessage.get_data(), (size_t)memMessage.get_size(), (unsigned char *) result, &md_len);

//#endif

   }




   void crypto::hmac(void * result,const string & strMessage,const string & strKey)
   {

//#ifndef _UWP

      unsigned int md_len = 0;

      HMAC(EVP_sha1(),strKey.c_str(), int(strKey.length()),(const unsigned char *)(const char *)strMessage, (size_t)strMessage.length(),(unsigned char *)result,&md_len);

//#endif

   }


   ::file::path crypto::get_crypt_key_file_path()
   {

      return ::dir::system() / "user" / "databin.bin";

   }


   string crypto::defer_get_cryptkey()
   {

      string strPath = get_crypt_key_file_path();

      string str = Context.file().as_string(strPath);

      if (str.has_char())
      {

         return str;

      }

      int iLength = 256;

      generate_random_alphanumeric(str.get_string_buffer(iLength), iLength);

      Context.file().put_contents(strPath, str);

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


   __pointer(::crypto::rsa) crypto::generate_rsa_key()
   {

      __pointer(::crypto::rsa) rsa = __new(::crypto::rsa(get_context_object()));

      RSA * & prsa = rsa->m_prsa;

      prsa = RSA_new();

      {

         BIGNUM * e = BN_new();

         BN_set_word(e, 65537);

         int ret = RSA_generate_key_ex(prsa, 1024, e, nullptr);

         if (ret != 1)
         {

            BN_free(e);

            return nullptr;

         }

         BN_free(e);

      }

#if (defined(_UWP) && (!defined(RASPBIAN))) && (OPENSSL_API_COMPAT < 0x10100000L)

      char * hexN       = BN_bn2hex(prsa->n);
      char * hexE       = BN_bn2hex(prsa->e);
      char * hexD       = BN_bn2hex(prsa->d);
      char * hexP       = BN_bn2hex(prsa->p);
      char * hexQ       = BN_bn2hex(prsa->q);
      char * hexDmp1    = BN_bn2hex(prsa->dmp1);
      char * hexDmq1    = BN_bn2hex(prsa->dmq1);
      char * hexIqmp    = BN_bn2hex(prsa->iqmp);

#else

      const BIGNUM * n = nullptr;
      const BIGNUM * e = nullptr;
      const BIGNUM * d = nullptr;
      const BIGNUM * p = nullptr;
      const BIGNUM * q = nullptr;
      const BIGNUM * dmp1 = nullptr;
      const BIGNUM * dmq1 = nullptr;
      const BIGNUM * iqmp = nullptr;

      RSA_get0_key(prsa, &n, &e, &d);
      RSA_get0_factors(prsa, &p, &q);
      RSA_get0_crt_params(prsa, &dmp1, &dmq1, &iqmp);

      char * hexN = BN_bn2hex(n);
      char * hexE = BN_bn2hex(e);
      char * hexD = BN_bn2hex(d);
      char * hexP = BN_bn2hex(p);
      char * hexQ = BN_bn2hex(q);
      char * hexDmp1 = BN_bn2hex(dmp1);
      char * hexDmq1 = BN_bn2hex(dmq1);
      char * hexIqmp = BN_bn2hex(iqmp);

#endif

      rsa->n            = hexN;
      rsa->e            = hexE;
      rsa->d            = hexD;
      rsa->p            = hexP;
      rsa->q            = hexQ;
      rsa->dmp1         = hexDmp1;
      rsa->dmq1         = hexDmq1;
      rsa->iqmp         = hexIqmp;

      OPENSSL_free(hexN);
      OPENSSL_free(hexE);
      OPENSSL_free(hexD);
      OPENSSL_free(hexP);
      OPENSSL_free(hexQ);
      OPENSSL_free(hexDmp1);
      OPENSSL_free(hexDmq1);
      OPENSSL_free(hexIqmp);

      return rsa;

   }


   __pointer(rsa) crypto::read_priv_pem(const string & strFile)
   {

#ifdef WINDOWS_DESKTOP

      FILE * pfile = ::_fsopen(strFile, "rb", _SH_DENYNO);

#else

      FILE * pfile = ::fopen(strFile, "rb");

#endif

      if (!pfile)
      {

         return nullptr;

      }

      auto pcryptorsa = __new(::crypto::rsa(this));

      RSA * & prsa = pcryptorsa->m_prsa;

      PEM_read_RSAPrivateKey(pfile, &prsa, nullptr, nullptr);

      ::fclose(pfile);

      return pcryptorsa;

   }


   __pointer(rsa) crypto::read_pub_pem(const string & strFile)
   {

      FILE * pfile = ::fopen(strFile,"rb");

      if (!pfile)
      {

         return nullptr;

      }

      auto pcryptorsa = __new(::crypto::rsa(this));

      RSA * & prsa = pcryptorsa->m_prsa;

      PEM_read_RSA_PUBKEY(pfile, &prsa, nullptr, nullptr);

      ::fclose(pfile);

      return pcryptorsa;

   }



#else


   __pointer(::crypto::rsa) crypto::generate_rsa_key()
   {

      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider ^ provider =
      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider::OpenAlgorithm(
      ::Windows::Security::Cryptography::Core::AsymmetricAlgorithmNames::RsaPkcs1);


      return __new(::crypto::rsa(get_context_application(), provider->CreateKeyPair(1024)));

   }

   /*void crypto::free_rsa_key(__pointer(::crypto::rsa) prsa)
   {

      UNREFERENCED_PARAMETER(prsa);

   }*/

#endif

   void crypto::err_load_rsa_strings()
   {
#if defined(HAVE_OPENSSL)
      ERR_load_RSA_strings();

#endif

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


   rsa::rsa(::object * pobjectContext) :
      ::object(pobjectContext)
   {
      defer_create_mutex();
#if defined(_UWP)  && !defined(HAVE_OPENSSL)

      m_prsa = nullptr;
#else
      m_prsa = nullptr;
#endif

   }


   rsa::rsa(::object * pobjectContext, const string & nParam) :
      ::object(pobjectContext)
   {
defer_create_mutex();
#ifdef MACOS_DEPRECATED

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(nullptr, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

      // not needed, defaults to true    CFDictionaryAddValue(parameters, kSecAttrCanEncrypt, kCFBooleanTrue);

      memory memKeyData;

      memKeyData.from_hex(strPass);

      CFDataRef keyData = memKeyData.get_os_cf_data();

      CFErrorRef error = nullptr;

      m_prsa = SecKeyCreateFromData(parameters, keyData, &error);

      if (error != nullptr)
      {

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(error);

         __throw(resource_exception());

      }

      CFRelease(parameters);

      CFRelease(keyData);


#elif defined(_UWP) && !defined(HAVE_OPENSSL)


      typedef struct _BCRYPT_RSAKEY_BLOB
      {
         ULONG Magic;
         ULONG BitLength;
         ULONG cbPublicExp;
         ULONG cbModulus;
         ULONG cbPrime1;
         ULONG cbPrime2;
      } BCRYPT_RSAKEY_BLOB;

      BCRYPT_RSAKEY_BLOB blob;

      ::memory_file memfile(get_object());

      //blob.Magic = 0x31415352; // BCRYPT_RSAPUBLIC_MAGIC;
      blob.Magic = 0x31415352; // BCRYPT_RSAPUBLIC_MAGIC;
      blob.BitLength = 1024;
      blob.cbPublicExp = 3;
      blob.cbModulus = 1024 / 8;
      blob.cbPrime1 = 0;
      blob.cbPrime2 = 0;

//      memory memVer;

      //    memVer.from_hex("00");

      //  memVer.prefix_der_uint();

      memfile.write(&blob, sizeof(blob));

      memory memMod;

      string strRsaModulus(nParam);

      memMod.from_hex(strRsaModulus);

      //memMod.reverse();



      //memMod.prefix_der_uint();

      memory memExp;

      memExp.from_hex("010001");

      //memExp.reverse();

      memfile.write(memExp.get_data(), memExp.get_size());

      memfile.write(memMod.get_data(), memMod.get_size());

      //memExp.prefix_der_uint();

      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider ^ cipher =
      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::AsymmetricAlgorithmNames::RsaPkcs1);


      //memory memKey;

      //memKey = memVer;
      //memKey += memMod;
      //memKey = memMod;
      //memKey += memExp;


      //memKey.prefix_der_sequence();

      //string strRsaPrivateKey = "-----BEGIN RSA PUBLIC KEY-----\r\n";
      //strRsaPrivateKey += chunk_split(System.base64().encode(memKey));
      //strRsaPrivateKey += "-----END RSA PUBLIC KEY-----";

      //memKey.set_size(strRsaPrivateKey.get_length());

      //::memcpy_dup(memKey.get_data(), strRsaPrivateKey, memKey.get_size());

      //m_prsa = cipher->ImportPublicKey(memKey.get_os_crypt_buffer(),::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType::Pkcs1RsaPublicKey);
      m_prsa = cipher->ImportPublicKey(memfile.get_memory()->get_os_crypt_buffer(), ::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType::BCryptPublicKey);

#else

      BIGNUM * n = BN_new();
      BIGNUM * e = BN_new();

      m_prsa = RSA_new();

      BN_hex2bn(&n, nParam);
      BN_hex2bn(&e, "10001");

#if (defined(_UWP)) && (OPENSSL_API_COMPAT < 0x10100000L)
      m_prsa->n = n;
      m_prsa->e = e;
#else
      RSA_set0_key(m_prsa, n, e, nullptr);
#endif

      //BN_free(n);
      //BN_free(e);


#endif

   }

#ifdef HAVE_OPENSSL

   rsa::rsa(::object * pobjectContext,
            const string & strN,
            const string & strE,
            const string & strD,
            const string & strP,
            const string & strQ,
            const string & strDmp1,
            const string & strDmq1,
            const string & strIqmp) :
      ::object(pobjectContext)
   {
defer_create_mutex();
      m_prsa = RSA_new();

      BIGNUM * n = BN_new();
      BIGNUM * e = BN_new();
      BIGNUM * d = BN_new();
      BIGNUM * point = BN_new();
      BIGNUM * q = BN_new();
      BIGNUM * dmp1 = BN_new();
      BIGNUM * dmq1 = BN_new();
      BIGNUM * iqmp = BN_new();

      BN_hex2bn(&n, strN);
      BN_hex2bn(&e, strE);
      BN_hex2bn(&d, strD);
      BN_hex2bn(&point, strP);
      BN_hex2bn(&q, strQ);
      BN_hex2bn(&dmp1, strDmp1);
      BN_hex2bn(&dmq1, strDmq1);
      BN_hex2bn(&iqmp, strIqmp);

#if defined(_UWP) && (OPENSSL_API_COMPAT < 0x10100000L)
      m_prsa->n = n;
      m_prsa->e = e;
      m_prsa->d = d;
      m_prsa->p = point;
      m_prsa->q = q;
      m_prsa->dmp1 = dmp1;
      m_prsa->dmq1 = dmq1;
      m_prsa->iqmp = iqmp;
#else
      RSA_set0_key(m_prsa, n, e, d);
      RSA_set0_factors(m_prsa, point, q);
      RSA_set0_crt_params(m_prsa, dmp1, dmq1, iqmp);
#endif

   }

#endif

   rsa::~rsa()
   {

#ifdef MACOS_DEPRECATED
      if (m_prsa != nullptr)
      {

         CFRelease(m_prsa);
         m_prsa = nullptr;
      }
#elif defined(_UWP) && !defined(HAVE_OPENSSL)

      m_prsa = nullptr;

#else
      if (m_prsa != nullptr)
      {

         RSA_free(m_prsa);
         m_prsa = nullptr;

      }
#endif

   }

   int rsa::public_encrypt(memory & out, const memory & in, string & strError)
   {
#ifdef MACOS_DEPRECATED


      SecTransformRef transform = SecEncryptTransformCreate(m_prsa, &error);

      if (error != nullptr)
      {

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if (error != nullptr)
      {

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      memory memDataIn;

      memDataIn.from_hex(strRsaModulus);

      CFDataRef dataIn = memDataIn.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }


      string strHex;

      memory memory;

      memory.set_os_cf_data(data);

      memory.to_hex(strHex);

      CFRelease(data);

      CFRelease(dataIn);

      CFRelease(transform);

#elif defined(_UWP) && !defined(HAVE_OPENSSL)



      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));




#else

      i32 i = RSA_public_encrypt((i32)in.get_size(), (const uchar *)(const char *)in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);

      strError = ERR_error_string(ERR_get_error(), nullptr);

      out.set_size(i);



#endif

      return int (out.get_size());


   }

   int rsa::private_decrypt(memory & out, const memory & in, string & strError)
   {


#if defined(_UWP) && !defined(HAVE_OPENSSL)



      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa, in.get_os_crypt_buffer(), nullptr));




#else

      single_lock sl(mutex(), true);

      i32 iRsaSize = 8192;

      out.set_size(iRsaSize);

      out.set(0);

      ::count i = RSA_private_decrypt((int)in.get_size(), in.get_data(), out.get_data(), m_prsa, RSA_PKCS1_PADDING);

      if (i < 0 || i >(1024 * 1024))
      {

         strError = ERR_error_string(ERR_get_error(), nullptr);

         return (int)i;

      }

      out.set_size(i);

#endif

      return int (out.get_size());

   }

   int rsa::private_encrypt(memory & out,const memory & in,string & strError)
   {
#ifdef MACOS_DEPRECATED


      SecTransformRef transform = SecEncryptTransformCreate(m_prsa,&error);

      if(error != nullptr)
      {

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform,kSecPaddingKey,kSecPaddingPKCS1Key,&error);

      if(error != nullptr)
      {

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      memory memDataIn;

      memDataIn.from_hex(strRsaModulus);

      CFDataRef dataIn = memDataIn.get_os_cf_data();

      SecTransformSetAttribute(transform,kSecTransformInputAttributeName,dataIn,&error);

      if(error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef)SecTransformExecute(transform,&error);

      if(error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }


      string strHex;

      memory memory;

      memory.set_os_cf_data(data);

      memory.to_hex(strHex);

      CFRelease(data);

      CFRelease(dataIn);

      CFRelease(transform);

#elif defined(_UWP) && !defined(HAVE_OPENSSL)



      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(m_prsa,in.get_os_crypt_buffer(),nullptr));




#else

      auto iInSize = (i32)in.get_size();

      auto pInData = (const uchar*)(const char*)in.get_data();

      auto pOutData = out.get_data();

      auto prsa = m_prsa;

      i32 i = RSA_private_encrypt(iInSize, pInData, pOutData, prsa, RSA_PKCS1_PADDING);

      strError = ERR_error_string(ERR_get_error(), nullptr);

      out.set_size(i);



#endif

      return int (out.get_size());

   }


   int rsa::public_decrypt(memory & out,const memory & in,string & strError)
   {


#if defined(_UWP) && !defined(HAVE_OPENSSL)



      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_prsa,in.get_os_crypt_buffer(),nullptr));




#else

      single_lock sl(mutex(),true);

      i32 iRsaSize = 8192;

      out.set_size(iRsaSize);

      out.set(0);

      ::count i = RSA_public_decrypt((int)in.get_size(),in.get_data(),out.get_data(),m_prsa,RSA_PKCS1_PADDING);

      if(i < 0 || i >(1024 * 1024))
      {

         strError = ERR_error_string(ERR_get_error(),nullptr);

         return (int)i;

      }

      out.set_size(i);

#endif

      return int (out.get_size());

   }


   string crypto::spa_login_crypt(const char * psz, const string & strRsa)
   {

      __pointer(::crypto::rsa) prsa = __new(::crypto::rsa(get_context_application(), strRsa));

      memory memory;

      ::memory memIn;

      memIn.from_hex(psz);

      memory.set_size(2048);

      memory.set(0);

      string strError;

      int i = prsa->public_encrypt(memory, memIn, strError);

      if (i < 0 || i >(1024 * 1024))
      {

         TRACE("%s", strError.c_str());

      }

      return memory.to_hex();

   }


   string crypto::spa_login_decrypt(const char * psz,const string & strRsa)
   {

      __pointer(::crypto::rsa) prsa = __new(::crypto::rsa(get_context_application(),strRsa));

      memory memory;

      ::memory memIn;

      memIn.from_hex(psz);

      memory.set_size(2048);

      memory.set(0);

      string strError;

      int i = prsa->private_decrypt(memory,memIn,strError);

      if(i < 0 || i >(1024 * 1024))
      {

         TRACE("%s", strError.c_str());

      }

      return memory.to_hex();

   }
   string crypto::spa_auth_decrypt(const char * psz,rsa * prsa)
   {

      memory memory;

      ::memory memIn;

      memIn.from_hex(psz);

      memory.set_size(2048);

      memory.set(0);

      string strError;

      int i = prsa->public_decrypt(memory,memIn,strError);

      if(i < 0 || i >(1024 * 1024))
      {

         TRACE("%s", strError.c_str());

      }

      return memory.to_hex();

   }

   string crypto::spa_auth_decrypt(const char * psz,const string & strRsa)
   {

      __pointer(::crypto::rsa) prsa = __new(::crypto::rsa(get_context_application(),strRsa));

      memory memory;

      ::memory memIn;

      memIn.from_hex(psz);

      memory.set_size(2048);

      memory.set(0);

      string strError;

      int i = prsa->public_decrypt(memory,memIn,strError);

      if(i < 0 || i >(1024 * 1024))
      {

         TRACE("%s", strError.c_str());

      }

      return memory.to_hex();

   }


   string crypto::spa_auth_crypt(const char * psz,rsa * prsa)
   {

      memory memory;

      ::memory memIn;

      memIn.from_hex(psz);

      memory.set_size(2048);

      memory.set(0);

      string strError;

      int i = prsa->private_encrypt(memory,memIn,strError);

      if(i < 0 || i >(1024 * 1024))
      {

         TRACE("%s", strError.c_str());

      }

      return memory.to_hex();

   }


   void crypto::np_make_zigbert_rsa(const string & strDir, const string & strSignerPath, const string & strKeyPath, const string & strOthersPath, const string & strSignature)
   {

#if !defined(_UWP) && defined(HAVE_OPENSSL)

      X509 * signer = nullptr;
      {
         string strSigner = Context.file().as_string(strSignerPath);
         BIO * pbio = BIO_new_mem_buf((void *)(LPCSTR)strSigner, (i32)strSigner.get_length());
         //signer = PEM_read_bio_X509_AUX(pbio, nullptr, 0, nullptr);
         signer = PEM_read_bio_X509(pbio, nullptr, 0, nullptr);
         BIO_free(pbio);
      }

      EVP_PKEY * pkey;
      {
         string strKey = Context.file().as_string(strKeyPath);
         BIO * pbio = BIO_new_mem_buf((void *)(LPCSTR)strKey, (i32)strKey.get_length());
         pkey = PEM_read_bio_PrivateKey(pbio, nullptr, nullptr, nullptr);
         BIO_free(pbio);
      }


      stack_st_X509 * pstack509 = nullptr;
      {
         string strOthers = Context.file().as_string(strOthersPath);
         address_array < X509 * > xptra;
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
            X509 * x;
            BIO * pbio = BIO_new(BIO_s_mem());
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

      BIO * input = BIO_new_mem_buf((void *)(LPCSTR)strSignature, (i32)strSignature.get_length());

      PKCS7 * pkcs7 = PKCS7_sign(signer, pkey, pstack509, input, PKCS7_BINARY | PKCS7_DETACHED);

      BIO_free(input);
      sk_X509_free(pstack509);
      EVP_PKEY_free(pkey);
      X509_free(signer);

      BIO * output = BIO_new(BIO_s_mem());

      i2d_PKCS7_bio(output, pkcs7);

      char * pchData = nullptr;
      long count = BIO_get_mem_data(output, &pchData);

      Context.file().put_contents(strDir / "META-INF/zigbert.rsa", pchData, count);

      BIO_free(output);
      PKCS7_free(pkcs7);
#endif
   }


   string crypto::txt_encrypt(const char * psz,rsa * prsa)
   {

      memory memory;

      ::memory memIn;

      memIn.assign(psz,strlen(psz));

      memory.set_size(2048);

      memory.set(0);

      string strError;

      int i = prsa->private_encrypt(memory,memIn,strError);

      if(i < 0 || i >(1024 * 1024))
      {

         TRACE("%s", strError.c_str());

      }

      return memory.to_hex();

   }


   string crypto::txt_decrypt(const char * psz,rsa * prsa)
   {

      memory memory;

      ::memory memIn;

      memIn.from_hex(psz);

      memory.set_size(2048);

      memory.set(0);

      string strError;

      int i = prsa->public_decrypt(memory,memIn,strError);

      if(i < 0 || i >(1024 * 1024))
      {

         TRACE("%s", strError.c_str());

      }

      string str;

      memory.to_string(str);

      return str;

   }


} // namespace crypto




void
stunCalculateIntegrity_longterm(char* hmac, const char* input, i32 length,
                                const char *username, const char *realm, const char *password)
{

#if !defined(_UWP) || defined(HAVE_OPENSSL)
   u32 resultSize = 0;
   uchar HA1[16];
   char HA1_text[1024];

   snprintf(HA1_text, sizeof(HA1_text), "%s:%s:%s", username, realm, password);
   MD5((uchar *)HA1_text, strlen(HA1_text), HA1);

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

void hmac_evp_sha1_1234(unsigned char * hmac, unsigned int * hmacSize, const unsigned char * buf, size_t bufLen)
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
