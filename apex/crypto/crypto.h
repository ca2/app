﻿#pragma once


////#include "acme/primitive/primitive/object.h"


namespace crypto
{


   class rsa;


   class initializer;


   class CLASS_DECL_APEX crypto :
      virtual public ::object
   {
   public:


      // salt here may be dangerous for the universe

      ::pointer<::crypto::initializer>   m_pinitializer;


      crypto();
      ~crypto() override;

      
      virtual void defer_initialize();


      virtual ::pointer<hasher_algorithm>create_hasher_algorithm(enum_hash ehash);
      virtual ::pointer<hasher>create_hasher(enum_hash ehash);


      virtual void encrypt(memory& storageEncrypt, const block & blockDecrypt, const block & blockKey) = 0;
      virtual void decrypt(memory& storageDecrypt, const block & blockEncrypt, const block & blockKey) = 0;

 
      //virtual void encrypt(memory & blockEncrypt, const block & blockDecrypt, const scoped_string & strSalt);
      //virtual void decrypt(memory & blockDecrypt, const block & blockEncrypt, const scoped_string & strSalt);
      //virtual void encrypt(memory & storageEncrypt, const scoped_string & strDecrypt, const scoped_string & strSalt);
      //virtual void decrypt(string & strDecrypt, const memory & storageEncrypt, const scoped_string & strSalt);


      virtual i32 key(memory & storage);

      virtual string strkey();
      virtual void encrypt(string & str, const block & blockDecrypt, const block & blockKey);
      virtual void decrypt(string & str, const block & blockEncrypt, const block & blockKey);


      virtual int get_md5_digest_length() const;
      virtual int get_sha1_digest_length() const;
      virtual int get_sha256_digest_length() const;
      virtual int get_nessie_digest_length() const;


      //virtual u32 crc32(u32 dwPrevious, const scoped_string & str) = 0;
      //virtual string md5(const scoped_string & str);
      //virtual string sha1(const scoped_string & str);
      //virtual string nessie(const scoped_string & str);

      virtual string md5(const block & block);
      virtual string sha1(const block & block);
      virtual string nessie(const block & block);

      virtual int get_hash_digest_length(enum_hash) const = 0;

      virtual void hash(memory& memOut, const block & blockIn, enum_hash ehash);


      virtual void md5(memory & memMd5, const block& block);
      virtual void sha1(memory & memSha1, const block& block);
      virtual void sha256(memory & memSha256, const block& block);
      virtual void nessie(memory & memNessie, const block& block);

      // result is 20-byte digest
      virtual void hmac(void * result,const memory & memMessage,const memory & key) = 0;
      virtual void hmac(void * result,const string & memMessage,const string & key) = 0;

      virtual void file_set(::payload payloadFile,const scoped_string & strData,const scoped_string & strSalt, ::apex::application * papp);
      virtual void file_get(::payload payloadFile,string & str,const scoped_string & strSalt, ::apex::application * papp);

      // get a memory_new salt - 8 hexadecimal characters long
      // current PHP installations should not exceed 8 characters
      // on dechex( mt_rand() )
      // but we future proof it anyway with substr()
      virtual string v5_get_password_salt();
      // calculate the hash from a salt and a password
      virtual string v5_get_password_hash(const scoped_string & strSalt,const scoped_string & strPassword,i32 iOrder = 0);
      virtual string v5_get_passhash(const scoped_string & strSalt,const scoped_string & strPassword,i32 iMaxOrder = 0);
      virtual bool v5_compare_password(const scoped_string & strPassword,const scoped_string & strHash,i32 iOrder = 0);
      // if iOrder == 0 password is plain
      // if iOrder == 1 password is the first hash
      // if iOrder == (n > 0) password is the nth hash
      virtual bool v5_validate_plain_password(const scoped_string & strPassword);
      virtual string v5_get_password_hash(const scoped_string & strPassword,i32 iOrder = 0);

      virtual ::file::path get_crypt_key_file_path();
      virtual ::memory defer_get_cryptkey();

      
      virtual ::pointer<rsa>create_rsa_key(const ::string & strRsa);

      virtual ::pointer<rsa>generate_rsa_key();

      virtual ::pointer<rsa>read_priv_pem(const ::string & strFile);

      virtual ::pointer<rsa>read_pub_pem(const ::string & strFile);


      //void err_load_rsa_strings();


      //void err_load_crypto_strings();


      virtual string spa_login_crypt(const scoped_string & str,const string & pszRsa);
      virtual string spa_login_decrypt(const scoped_string & str,const string & pszRsa);

      virtual string spa_auth_crypt(const scoped_string & str,rsa * prsa);
      virtual string spa_auth_decrypt(const scoped_string & str,rsa * prsa);
      virtual string spa_auth_decrypt(const scoped_string & str,const string & pszRsa);

      virtual string txt_encrypt(const scoped_string & str,rsa * prsa);
      virtual string txt_decrypt(const scoped_string & str,rsa * prsa);

      //virtual void np_make_zigbert_rsa(const ::string & strDir, const ::string & strSignerPath, const ::string & strKeyPath, const ::string & strOthersPath, const ::string & strSignature);


   };


} //   namespace crypto






CLASS_DECL_APEX void stunCalculateIntegrity_longterm(char* hmac, const char* input, i32 length, const char *username, const char *realm, const char *password);

CLASS_DECL_APEX void stunCalculateIntegrity_shortterm(char* hmac, const char* input, i32 length, const char* key);


CLASS_DECL_APEX void hmac_evp_sha1_1234(unsigned char * hmac, unsigned int * hmacSize, const unsigned char * buf, size_t bufLen);
