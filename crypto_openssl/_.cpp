#include "framework.h"
#include "acme/_library.h"


#ifdef WINDOWS

#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")

#endif

////#include "_openssl.h"
//#include "apex/crypto/_crypto.h"
//
//
//#ifdef PARALLELIZATION_PTHREAD
//
//
//#include "acme/operating_system/ansi/_pthread.h"
//
//
//#endif
//
//
//#include <openssl/ssl.h>
//#include <openssl/md5.h>
//#include <openssl/err.h>
//
////::i32 SHA1_Init(SHA_CTX* c);
////::i32 SHA1_Update(SHA_CTX* c, const void* data, size_t len);
////::i32 SHA1_Final(::u8* md, SHA_CTX* c);
////::u8* SHA1(const ::u8* d, size_t n, ::u8* md);
////void SHA1_Transform(SHA_CTX* c, const ::u8* data);
//
//// namespace str
//// {
//
////mdctx = EVP_MD_CTX_new();
//
//
//   //CLASS_DECL_APEX ::string as_string(EVP_MD_CTX * pctx)
//   //{
//
//   //   ::u32 md_len = 0;
//
//   //   memory memory;
//
//   //   memory.allocate_add_up(EVP_MD_CTX_get_size(pctx));
//
//   //   EVP_DigestFinal_ex(pctx, memory.get_data(), &md_len);
//
//   //   str = ::hex::lower_from(memory.get_data(), md_len);
//
//   //}
//
//
//   //CLASS_DECL_APEX ::string as_string(const WHIRLPOOL_CTX & ctx)
//   //{
//
//   //   ::u8 digest[WHIRLPOOL_DIGEST_LENGTH];
//
//   //   WHIRLPOOL_Final(digest, (WHIRLPOOL_CTX *) &ctx);
//
//   //   str = ::hex::lower_from(digest, WHIRLPOOL_DIGEST_LENGTH);
//
//   //}
//
//
//// } // namespace str
//
//
//
////::i32 crypto_encrypt(memory & storageEncrypt, const memory & storageDecrypt, memory & key)
////{
////   ::i32 plainlen = (::i32)storageDecrypt.get_size();
////   ::i32 cipherlen, tmplen;
////   ::u8 iv[8] = { 1,2,3,4,5,6,7,8 };
////   EVP_CIPHER_CTX* pctx = EVP_CIPHER_CTX_new();
////   EVP_EncryptInit(pctx, EVP_bf_cbc(), (::u8*)key.get_data(), iv);
////   cipherlen = (::i32)(storageDecrypt.get_size() + 16 - 1); //; 16 = key i32_size
////   storageEncrypt.set_size(cipherlen);
////   if (!EVP_EncryptUpdate(pctx, (::u8*)storageEncrypt.get_data(), &cipherlen, (const ::u8*)storageDecrypt.get_data(), plainlen))
////   {
////      return -1;
////   }
////   if (!EVP_EncryptFinal(pctx, ((::u8*)storageEncrypt.get_data()) + cipherlen, &tmplen))
////   {
////      return -1;
////   }
////   cipherlen += tmplen;
////   storageEncrypt.set_size(cipherlen);
////   EVP_CIPHER_CTX_free(pctx);
////   return cipherlen;
////}
////
////::i32 crypto_decrypt(memory& storageDecrypt, const memory& storageEncrypt, memory& key)
////{
////   ::i32 cipherlen = (::i32)storageEncrypt.get_size();
////   ::i32 plainlen, tmplen;
////   ::u8 iv[8] = { 1,2,3,4,5,6,7,8 };
////   EVP_CIPHER_CTX* pctx = EVP_CIPHER_CTX_new();
////   EVP_DecryptInit(pctx, EVP_bf_cbc(), (const ::u8*)key.get_data(), iv);
////   plainlen = (::i32)storageEncrypt.get_size();
////   storageDecrypt.set_size(plainlen);
////   if (!EVP_DecryptUpdate(pctx, (::u8*)storageDecrypt.get_data(), &plainlen, (const ::u8*)storageEncrypt.get_data(), cipherlen))
////   {
////      return -1;
////   }
////   if (!EVP_DecryptFinal(pctx, ((::u8*)storageDecrypt.get_data()) + plainlen, &tmplen))
////   {
////      storageDecrypt.set_size(plainlen);
////      EVP_CIPHER_CTX_free(pctx);
////      return plainlen;
////   }
////   plainlen += tmplen;
////   storageDecrypt.set_size(plainlen);
////   EVP_CIPHER_CTX_free(pctx);
////   return plainlen;
////}
////
////
////
////
/////* Cipher mode info */
////struct php_openssl_cipher_mode {
////   ::i32_bool is_aead;
////   ::i32_bool is_single_run_aead;
////   ::i32 aead_get_tag_flag;
////   ::i32 aead_set_tag_flag;
////   ::i32 aead_ivlen_flag;
////};
////
////static void php_openssl_load_cipher_mode(struct php_openssl_cipher_mode* mode, const EVP_CIPHER* cipher_type) /* {{{ */
////{
////   switch (EVP_CIPHER_mode(cipher_type)) {
////#ifdef EVP_CIPH_GCM_MODE
////   case EVP_CIPH_GCM_MODE:
////      mode->is_aead = 1;
////      mode->is_single_run_aead = 0;
////      mode->aead_get_tag_flag = EVP_CTRL_GCM_GET_TAG;
////      mode->aead_set_tag_flag = EVP_CTRL_GCM_SET_TAG;
////      mode->aead_ivlen_flag = EVP_CTRL_GCM_SET_IVLEN;
////      break;
////#endif
////#ifdef EVP_CIPH_CCM_MODE
////   case EVP_CIPH_CCM_MODE:
////      mode->is_aead = 1;
////      mode->is_single_run_aead = 1;
////      mode->aead_get_tag_flag = EVP_CTRL_CCM_GET_TAG;
////      mode->aead_set_tag_flag = EVP_CTRL_CCM_SET_TAG;
////      mode->aead_ivlen_flag = EVP_CTRL_CCM_SET_IVLEN;
////      break;
////#endif
////   default:
////      ::memory_set(mode, 0, sizeof(struct php_openssl_cipher_mode));
////   }
////}
/////* }}} */
////
//////static ::i32 php_openssl_validate_iv(char_pointer * piv, size_t* piv_len, size_t iv_required_len,
//////   ::i32_bool* free_iv, EVP_CIPHER_CTX* cipher_ctx, struct php_openssl_cipher_mode* mode) /* {{{ */
//////{
//////   char_pointer iv_new;
//////
//////   /* Best case scenario, user behaved */
//////   if (*piv_len == iv_required_len) {
//////      return true;
//////   }
//////
//////   if (mode->is_aead) {
//////      if (EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_ivlen_flag, *piv_len, NULL) != 1) {
//////         //php_error_docref(NULL, E_WARNING, "Setting of IV length for AEAD mode failed");
//////         return false;
//////      }
//////      return true;
////  // }
////
////   //iv_new = ecalloc(1, iv_required_len + 1);
////
////   //if (*piv_len == 0) {
////   //   /* BC behavior */
////   //   *piv_len = iv_required_len;
////   //   *piv = iv_new;
////   //   *free_iv = 1;
////   //   return SUCCESS;
////
////   //}
////
////   //if (*piv_len < iv_required_len) {
////   //   php_error_docref(NULL, E_WARNING,
////   //      "IV passed is only %zd bytes long, cipher expects an IV of precisely %zd bytes, padding with \\0",
////   //      *piv_len, iv_required_len);
////   //   ::memory_copy(iv_new, *piv, *piv_len);
////   //   *piv_len = iv_required_len;
////   //   *piv = iv_new;
////   //   *free_iv = 1;
////   //   return SUCCESS;
////   //}
////
////   //php_error_docref(NULL, E_WARNING,
////   //   "IV passed is %zd bytes long which is longer than the %zd expected by selected cipher, truncating",
////   //   *piv_len, iv_required_len);
////   //::memory_copy(iv_new, *piv, iv_required_len);
////   //*piv_len = iv_required_len;
////   //*piv = iv_new;
////   //*free_iv = 1;
//////   return SUCCESS;
////
//////}
/////* }}} */
////
//////static ::i32 php_openssl_cipher_init(const EVP_CIPHER* cipher_type,
//////   EVP_CIPHER_CTX* cipher_ctx, struct php_openssl_cipher_mode* mode,
//////   char_pointer * ppassword, size_t* ppassword_len, zend_bool* free_password,
//////   char_pointer * piv, size_t* piv_len, zend_bool* free_iv,
//////   char_pointer tag, ::i32 tag_len, zend_long options, ::i32 enc)  /* {{{ */
//////{
//////   ::u8* key;
//////   ::i32 key_len, password_len;
//////   size_t max_iv_len;
//////
//////   *free_password = 0;
//////
//////   max_iv_len = EVP_CIPHER_iv_length(cipher_type);
//////   if (enc && *piv_len == 0 && max_iv_len > 0 && !mode->is_aead) {
//////      php_error_docref(NULL, E_WARNING,
//////         "Using an empty Initialization Vector (iv) is potentially insecure and not recommended");
//////   }
//////
//////   if (!EVP_CipherInit_ex(cipher_ctx, cipher_type, NULL, NULL, NULL, enc)) {
//////      php_openssl_store_errors();
//////      return FAILURE;
//////   }
//////   if (php_openssl_validate_iv(piv, piv_len, max_iv_len, free_iv, cipher_ctx, mode) == FAILURE) {
//////      return FAILURE;
//////   }
//////   if (mode->is_single_run_aead && enc) {
//////      EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_set_tag_flag, tag_len, NULL);
//////   }
//////   else if (!enc && tag && tag_len > 0) {
//////      if (!mode->is_aead) {
//////         php_error_docref(NULL, E_WARNING, "The tag cannot be used because the cipher method does not support AEAD");
//////      }
//////      else if (!EVP_CIPHER_CTX_ctrl(cipher_ctx, mode->aead_set_tag_flag, tag_len, (::u8*)tag)) {
//////         php_error_docref(NULL, E_WARNING, "Setting tag for AEAD cipher decryption failed");
//////         return FAILURE;
//////      }
//////   }
//////   /* check and set key */
//////   password_len = (::i32)* ppassword_len;
//////   key_len = EVP_CIPHER_key_length(cipher_type);
//////   if (key_len > password_len) {
//////      if ((OPENSSL_DONT_ZERO_PAD_KEY & options) && !EVP_CIPHER_CTX_set_key_length(cipher_ctx, password_len)) {
//////         php_openssl_store_errors();
//////         php_error_docref(NULL, E_WARNING, "Key length cannot be set for the cipher method");
//////         return FAILURE;
//////      }
//////      key = emalloc(key_len);
//////      ::memory_set(key, 0, key_len);
//////      ::memory_copy(key, *ppassword, password_len);
//////      *ppassword = (char_pointer )key;
//////      *ppassword_len = key_len;
//////      *free_password = 1;
//////   }
//////   else {
//////      if (password_len > key_len && !EVP_CIPHER_CTX_set_key_length(cipher_ctx, password_len)) {
//////         php_openssl_store_errors();
//////      }
//////      key = (::u8*)* ppassword;
//////   }
//////
//////   if (!EVP_CipherInit_ex(cipher_ctx, NULL, NULL, key, (::u8*)* piv, enc)) {
//////      php_openssl_store_errors();
//////      return FAILURE;
//////   }
//////   if (options & OPENSSL_ZERO_PADDING) {
//////      EVP_CIPHER_CTX_set_padding(cipher_ctx, 0);
//////   }
//////
//////   return SUCCESS;
//////}
////
////
////
////
//////::i32 crypto_encrypt2(memory& storageEncrypt, const memory& storageDecrypt, memory& key)
//////{
//////   ::i32 plainlen = (::i32)storageDecrypt.get_size();
//////   ::i32 cipherlen, tmplen;
//////   const_char_pointer iv = "skdfjghsdlkfjghs";
//////   EVP_CIPHER_CTX* pctx = EVP_CIPHER_CTX_new();
//////   EVP_EncryptInit(pctx, EVP_bf_cbc(), (::u8*)key.get_data(), iv);
//////   cipherlen = (::i32)(storageDecrypt.get_size() + 16 - 1); //; 16 = key i32_size
//////   storageEncrypt.allocate(cipherlen);
//////   if (!EVP_EncryptUpdate(pctx, (::u8*)storageEncrypt.get_data(), &cipherlen, (const ::u8*)storageDecrypt.get_data(), plainlen))
//////   {
//////      return -1;
//////   }
//////   if (!EVP_EncryptFinal(pctx, ((::u8*)storageEncrypt.get_data()) + cipherlen, &tmplen))
//////   {
//////      return -1;
//////   }
//////   cipherlen += tmplen;
//////   storageEncrypt.allocate(cipherlen);
//////   EVP_CIPHER_CTX_free(pctx);
//////   return cipherlen;
//////}
////
//////
//////
//////CLASS_DECL_APEX ::i32 crypto_decrypt2(memory& storageDecrypt, const memory& storageEncrypt, memory& key)
//////{
//////   const_char_pointer iv = "skdajhgbmvkbjghs";
//////   EVP_CIPHER_CTX* cipher_ctx = EVP_CIPHER_CTX_new();
//////   auto cipher_type = EVP_aes_128_cbc();
//////   auto data_len = storageEncrypt.get_length();
//////   if (!EVP_CipherInit_ex(cipher_ctx, cipher_type, NULL, NULL, NULL, 0))
//////   {
//////
//////      return 0;
//////   }
//////
//////   if (!EVP_CipherInit_ex(cipher_ctx, NULL, NULL, (::u8*)key.get_data(), (::u8*)(iv), 0))
//////   {
//////
//////      return 0;
//////
//////   }
//////   storageDecrypt.set_size((::i32)data_len + EVP_CIPHER_block_size(cipher_type));
//////   ::i32 outlen = 0;
//////   if (!EVP_CipherUpdate(cipher_ctx, (::u8*)storageDecrypt.get_data(), &outlen, (const ::u8*)storageEncrypt.get_data(), (::i32)data_len))
//////   {
//////      return -1;
//////   }
//////   ::i32 i = 0;
//////   {
//////      if (EVP_DecryptFinal(cipher_ctx, ((::u8*)storageDecrypt.get_data()) + outlen, &i))
//////      {
//////         outlen = outlen + i;
//////      }
//////      else
//////      {
//////         outlen = 0;
//////      }
//////   }
//////   storageDecrypt.set_size(outlen);
//////   //EVP_CIPHER_CTX_cleanup(cipher_ctx);
//////   EVP_CIPHER_CTX_free(cipher_ctx);
//////   return outlen;
//////}
//////
//////
//////CLASS_DECL_APEX ::i32 crypto_encrypt2(memory& storageDecrypt, const memory& storageEncrypt, memory& key)
//////{
//////   const_char_pointer iv = "skdajhgbmvkbjghs";
//////   EVP_CIPHER_CTX* cipher_ctx = EVP_CIPHER_CTX_new();
//////   auto cipher_type = EVP_aes_128_cbc();
//////   auto data_len = storageEncrypt.get_length();
//////   if (!EVP_CipherInit_ex(cipher_ctx, cipher_type, NULL, NULL, NULL, 1))
//////   {
//////
//////      return 0;
//////   }
//////
//////   if (!EVP_CipherInit_ex(cipher_ctx, NULL, NULL, (::u8*)key.get_data(), (::u8*)(iv), 1))
//////   {
//////
//////      return 0;
//////
//////   }
//////   storageDecrypt.set_size((::i32)data_len + EVP_CIPHER_block_size(cipher_type));
//////   ::i32 outlen = 0;
//////   if (!EVP_CipherUpdate(cipher_ctx, (::u8*)storageDecrypt.get_data(), &outlen, (const ::u8*)storageEncrypt.get_data(), (::i32)data_len))
//////   {
//////      return -1;
//////   }
//////   ::i32 i = 0;
//////   {
//////      if (EVP_EncryptFinal(cipher_ctx, ((::u8*)storageDecrypt.get_data()) + outlen, &i))
//////      {
//////         outlen = outlen + i;
//////      }
//////      else
//////      {
//////         outlen = 0;
//////      }
//////   }
//////   storageDecrypt.set_size(outlen);
//////   //EVP_CIPHER_CTX_cleanup(cipher_ctx);
//////   EVP_CIPHER_CTX_free(cipher_ctx);
//////   return outlen;
//////
//////}
//////
//////
//////
