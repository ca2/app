#include "framework.h"
#include "hasher.h"
#include "hasher_algorithm.h"
#include "acme/primitive/primitive/memory.h"
//#include "_openssl.h"


//namespace openssl
//{
//
//
//   ::pointer<::crypto::hasher>get_hasher(enum_hash ehash)
//   {
//
//      switch (ehash)
//      {
//      case e_hash_md5:
//         return __new(hasher < MD5_CTX, e_hash_md5 > ());
//      case e_hash_sha1:
//         return __new(hasher < SHA_CTX, e_hash_sha1>());
//      case e_hash_sha256:
//         return __new(hasher < SHA256_CTX, e_hash_sha256 >());
//      default:
//         return nullptr;
//      }
//
//   }
//
//
//} // namespace openssl


//#include "framework.h"
//#include "_.h"


#include <openssl/ssl.h>
#include <openssl/md5.h>
#include <openssl/err.h>
#include <openssl/whrlpool.h>


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
//


//i32 crypto_encrypt(memory& storageEncrypt, const memory& storageDecrypt, memory& key)
//{
//   i32 plainlen = (i32)storageDecrypt.get_size();
//   i32 cipherlen, tmplen;
//   unsigned char iv[8] = { 1,2,3,4,5,6,7,8 };
//   EVP_CIPHER_CTX* pctx = EVP_CIPHER_CTX_new();
//   EVP_EncryptInit(pctx, EVP_bf_cbc(), (unsigned char*)key.get_data(), iv);
//   cipherlen = (i32)(storageDecrypt.get_size() + 16 - 1); //; 16 = key size_i32
//   storageEncrypt.set_size(cipherlen);
//   if (!EVP_EncryptUpdate(pctx, (unsigned char*)storageEncrypt.get_data(), &cipherlen, (const unsigned char*)storageDecrypt.get_data(), plainlen))
//   {
//      return -1;
//   }
//   if (!EVP_EncryptFinal(pctx, ((unsigned char*)storageEncrypt.get_data()) + cipherlen, &tmplen))
//   {
//      return -1;
//   }
//   cipherlen += tmplen;
//   storageEncrypt.set_size(cipherlen);
//   EVP_CIPHER_CTX_free(pctx);
//   return cipherlen;
//}
//
//i32 crypto_decrypt(memory& storageDecrypt, const memory& storageEncrypt, memory& key)
//{
//   i32 cipherlen = (i32)storageEncrypt.get_size();
//   i32 plainlen, tmplen;
//   unsigned char iv[8] = { 1,2,3,4,5,6,7,8 };
//   EVP_CIPHER_CTX* pctx = EVP_CIPHER_CTX_new();
//   EVP_DecryptInit(pctx, EVP_bf_cbc(), (const unsigned char*)key.get_data(), iv);
//   plainlen = (i32)storageEncrypt.get_size();
//   storageDecrypt.set_size(plainlen);
//   if (!EVP_DecryptUpdate(pctx, (unsigned char*)storageDecrypt.get_data(), &plainlen, (const unsigned char*)storageEncrypt.get_data(), cipherlen))
//   {
//      return -1;
//   }
//   if (!EVP_DecryptFinal(pctx, ((unsigned char*)storageDecrypt.get_data()) + plainlen, &tmplen))
//   {
//      storageDecrypt.set_size(plainlen);
//      EVP_CIPHER_CTX_free(pctx);
//      return plainlen;
//   }
//   plainlen += tmplen;
//   storageDecrypt.set_size(plainlen);
//   EVP_CIPHER_CTX_free(pctx);
//   return plainlen;
//}
//
//
//
//
///* Cipher mode info */
//struct php_openssl_cipher_mode {
//   int_bool is_aead;
//   int_bool is_single_run_aead;
//   int aead_get_tag_flag;
//   int aead_set_tag_flag;
//   int aead_ivlen_flag;
//};
//
//static void php_openssl_load_cipher_mode(struct php_openssl_cipher_mode* mode, const EVP_CIPHER* cipher_type) /* {{{ */
//{
//   switch (EVP_CIPHER_mode(cipher_type)) {
//#ifdef EVP_CIPH_GCM_MODE
//   case EVP_CIPH_GCM_MODE:
//      mode->is_aead = 1;
//      mode->is_single_run_aead = 0;
//      mode->aead_get_tag_flag = EVP_CTRL_GCM_GET_TAG;
//      mode->aead_set_tag_flag = EVP_CTRL_GCM_SET_TAG;
//      mode->aead_ivlen_flag = EVP_CTRL_GCM_SET_IVLEN;
//      break;
//#endif
//#ifdef EVP_CIPH_CCM_MODE
//   case EVP_CIPH_CCM_MODE:
//      mode->is_aead = 1;
//      mode->is_single_run_aead = 1;
//      mode->aead_get_tag_flag = EVP_CTRL_CCM_GET_TAG;
//      mode->aead_set_tag_flag = EVP_CTRL_CCM_SET_TAG;
//      mode->aead_ivlen_flag = EVP_CTRL_CCM_SET_IVLEN;
//      break;
//#endif
//   default:
//      memset(mode, 0, sizeof(struct php_openssl_cipher_mode));
//   }
//}
///* }}} */
//
////static int php_openssl_validate_iv(char** piv, size_t* piv_len, size_t iv_required_len,
////   int_bool* free_iv, EVP_CIPHER_CTX* cipher_ctx, struct php_openssl_cipher_mode* mode) /* {{{ */
////{
////   char* iv_new;
////
////   /* Best case scenario, user behaved */
////   if (*piv_len == iv_required_len) {
////      return true;
////   }
////
////   if (mode->is_aead) {
////      if (EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_ivlen_flag, *piv_len, NULL) != 1) {
////         //php_error_docref(NULL, E_WARNING, "Setting of IV length for AEAD mode failed");
////         return false;
////      }
////      return true;
//  // }
//
//   //iv_new = ecalloc(1, iv_required_len + 1);
//
//   //if (*piv_len == 0) {
//   //   /* BC behavior */
//   //   *piv_len = iv_required_len;
//   //   *piv = iv_new;
//   //   *free_iv = 1;
//   //   return SUCCESS;
//
//   //}
//
//   //if (*piv_len < iv_required_len) {
//   //   php_error_docref(NULL, E_WARNING,
//   //      "IV passed is only %zd bytes long, cipher expects an IV of precisely %zd bytes, padding with \\0",
//   //      *piv_len, iv_required_len);
//   //   memcpy(iv_new, *piv, *piv_len);
//   //   *piv_len = iv_required_len;
//   //   *piv = iv_new;
//   //   *free_iv = 1;
//   //   return SUCCESS;
//   //}
//
//   //php_error_docref(NULL, E_WARNING,
//   //   "IV passed is %zd bytes long which is longer than the %zd expected by selected cipher, truncating",
//   //   *piv_len, iv_required_len);
//   //memcpy(iv_new, *piv, iv_required_len);
//   //*piv_len = iv_required_len;
//   //*piv = iv_new;
//   //*free_iv = 1;
////   return SUCCESS;
//
////}
///* }}} */
//
////static int php_openssl_cipher_init(const EVP_CIPHER* cipher_type,
////   EVP_CIPHER_CTX* cipher_ctx, struct php_openssl_cipher_mode* mode,
////   char** ppassword, size_t* ppassword_len, zend_bool* free_password,
////   char** piv, size_t* piv_len, zend_bool* free_iv,
////   char* tag, int tag_len, zend_long options, int enc)  /* {{{ */
////{
////   unsigned char* key;
////   int key_len, password_len;
////   size_t max_iv_len;
////
////   *free_password = 0;
////
////   max_iv_len = EVP_CIPHER_iv_length(cipher_type);
////   if (enc && *piv_len == 0 && max_iv_len > 0 && !mode->is_aead) {
////      php_error_docref(NULL, E_WARNING,
////         "Using an empty Initialization Vector (iv) is potentially insecure and not recommended");
////   }
////
////   if (!EVP_CipherInit_ex(cipher_ctx, cipher_type, NULL, NULL, NULL, enc)) {
////      php_openssl_store_errors();
////      return FAILURE;
////   }
////   if (php_openssl_validate_iv(piv, piv_len, max_iv_len, free_iv, cipher_ctx, mode) == FAILURE) {
////      return FAILURE;
////   }
////   if (mode->is_single_run_aead && enc) {
////      EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_set_tag_flag, tag_len, NULL);
////   }
////   else if (!enc && tag && tag_len > 0) {
////      if (!mode->is_aead) {
////         php_error_docref(NULL, E_WARNING, "The tag cannot be used because the cipher method does not support AEAD");
////      }
////      else if (!EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_set_tag_flag, tag_len, (unsigned char*)tag)) {
////         php_error_docref(NULL, E_WARNING, "Setting tag for AEAD cipher decryption failed");
////         return FAILURE;
////      }
////   }
////   /* check and set key */
////   password_len = (int)* ppassword_len;
////   key_len = EVP_CIPHER_key_length(cipher_type);
////   if (key_len > password_len) {
////      if ((OPENSSL_DONT_ZERO_PAD_KEY & options) && !EVP_CIPHER_CTX_set_key_length(cipher_ctx, password_len)) {
////         php_openssl_store_errors();
////         php_error_docref(NULL, E_WARNING, "Key length cannot be set for the cipher method");
////         return FAILURE;
////      }
////      key = emalloc(key_len);
////      memset(key, 0, key_len);
////      memcpy(key, *ppassword, password_len);
////      *ppassword = (char*)key;
////      *ppassword_len = key_len;
////      *free_password = 1;
////   }
////   else {
////      if (password_len > key_len && !EVP_CIPHER_CTX_set_key_length(cipher_ctx, password_len)) {
////         php_openssl_store_errors();
////      }
////      key = (unsigned char*)* ppassword;
////   }
////
////   if (!EVP_CipherInit_ex(cipher_ctx, NULL, NULL, key, (unsigned char*)* piv, enc)) {
////      php_openssl_store_errors();
////      return FAILURE;
////   }
////   if (options & OPENSSL_ZERO_PADDING) {
////      EVP_CIPHER_CTX_set_padding(cipher_ctx, 0);
////   }
////
////   return SUCCESS;
////}
//
//
//
//
////i32 crypto_encrypt2(memory& storageEncrypt, const memory& storageDecrypt, memory& key)
////{
////   i32 plainlen = (i32)storageDecrypt.get_size();
////   i32 cipherlen, tmplen;
////   const char* iv = "skdfjghsdlkfjghs";
////   EVP_CIPHER_CTX* pctx = EVP_CIPHER_CTX_new();
////   EVP_EncryptInit(pctx, EVP_bf_cbc(), (unsigned char*)key.get_data(), iv);
////   cipherlen = (i32)(storageDecrypt.get_size() + 16 - 1); //; 16 = key size_i32
////   storageEncrypt.allocate(cipherlen);
////   if (!EVP_EncryptUpdate(pctx, (unsigned char*)storageEncrypt.get_data(), &cipherlen, (const unsigned char*)storageDecrypt.get_data(), plainlen))
////   {
////      return -1;
////   }
////   if (!EVP_EncryptFinal(pctx, ((unsigned char*)storageEncrypt.get_data()) + cipherlen, &tmplen))
////   {
////      return -1;
////   }
////   cipherlen += tmplen;
////   storageEncrypt.allocate(cipherlen);
////   EVP_CIPHER_CTX_free(pctx);
////   return cipherlen;
////}
//
//CLASS_DECL_APEX i32 crypto_decrypt2(memory& storageDecrypt, const memory& storageEncrypt, memory& key)
//{
//   const char* iv = "skdajhgbmvkbjghs";
//   EVP_CIPHER_CTX* cipher_ctx = EVP_CIPHER_CTX_new();
//   auto cipher_type = EVP_aes_128_cbc();
//   auto data_len = storageEncrypt.get_length();
//   if (!EVP_CipherInit_ex(cipher_ctx, cipher_type, NULL, NULL, NULL, 0))
//   {
//
//      return 0;
//   }
//
//   if (!EVP_CipherInit_ex(cipher_ctx, NULL, NULL, (unsigned char*)key.get_data(), (unsigned char*)(iv), 0))
//   {
//
//      return 0;
//
//   }
//   storageDecrypt.set_size((int)data_len + EVP_CIPHER_block_size(cipher_type));
//   int outlen = 0;
//   if (!EVP_CipherUpdate(cipher_ctx, (unsigned char*)storageDecrypt.get_data(), &outlen, (const unsigned char*)storageEncrypt.get_data(), (int)data_len))
//   {
//      return -1;
//   }
//   int i = 0;
//   {
//      if (EVP_DecryptFinal(cipher_ctx, ((unsigned char*)storageDecrypt.get_data()) + outlen, &i))
//      {
//         outlen = outlen + i;
//      }
//      else
//      {
//         outlen = 0;
//      }
//   }
//   storageDecrypt.set_size(outlen);
//   //EVP_CIPHER_CTX_cleanup(cipher_ctx);
//   EVP_CIPHER_CTX_free(cipher_ctx);
//   return outlen;
//}
//
//
//CLASS_DECL_APEX i32 crypto_encrypt2(memory& storageDecrypt, const memory& storageEncrypt, memory& key)
//{
//   const char* iv = "skdajhgbmvkbjghs";
//   EVP_CIPHER_CTX* cipher_ctx = EVP_CIPHER_CTX_new();
//   auto cipher_type = EVP_aes_128_cbc();
//   auto data_len = storageEncrypt.get_length();
//   if (!EVP_CipherInit_ex(cipher_ctx, cipher_type, NULL, NULL, NULL, 1))
//   {
//
//      return 0;
//   }
//
//   if (!EVP_CipherInit_ex(cipher_ctx, NULL, NULL, (unsigned char*)key.get_data(), (unsigned char*)(iv), 1))
//   {
//
//      return 0;
//
//   }
//   storageDecrypt.set_size((int)data_len + EVP_CIPHER_block_size(cipher_type));
//   int outlen = 0;
//   if (!EVP_CipherUpdate(cipher_ctx, (unsigned char*)storageDecrypt.get_data(), &outlen, (const unsigned char*)storageEncrypt.get_data(), (int)data_len))
//   {
//      return -1;
//   }
//   int i = 0;
//   {
//      if (EVP_EncryptFinal(cipher_ctx, ((unsigned char*)storageDecrypt.get_data()) + outlen, &i))
//      {
//         outlen = outlen + i;
//      }
//      else
//      {
//         outlen = 0;
//      }
//   }
//   storageDecrypt.set_size(outlen);
//   //EVP_CIPHER_CTX_cleanup(cipher_ctx);
//   EVP_CIPHER_CTX_free(cipher_ctx);
//   return outlen;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//


namespace crypto_openssl
{


   hasher::hasher(hasher_algorithm* palgorithm)
   {

      m_phasheralgorithm = palgorithm;

      m_pctx = EVP_MD_CTX_create();

      EVP_DigestInit_ex(m_pctx, palgorithm->m_pmd, NULL);

      // m_phasheralgorithm->m_pinit(&m_ctx);

   }


   hasher::~hasher()
   {

      EVP_MD_CTX_destroy(m_pctx);

   }


   enum_hash hasher::ehash() const
   {

      return m_ehash;

   }

   
   void hasher::update(const block& block)
   {

      EVP_DigestUpdate(m_pctx, block.get_data(), block.get_size());

   }


   memory hasher::get_hash_and_reset()
   {

#if OPENSSL_VERSION_NUMBER >= 0x30000000

      unsigned int md_len = EVP_MD_CTX_get_size(m_pctx);

#else

      unsigned int md_len = EVP_MD_CTX_size(m_pctx);

#endif

      memory memory;

      memory.set_size(md_len);

      EVP_DigestFinal_ex(m_pctx, memory.get_data(), &md_len);

      memory.set_size(md_len);

      return ::move(memory);

   }


} // namespace crypto_openssl



