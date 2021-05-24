#pragma once


namespace crypto
{


   class rsa;


   class initializer;


   class CLASS_DECL_APEX crypto :
      virtual public ::object
   {
   public:


      // salt here may be dangerous for the universe

      __composite(::crypto::initializer)    m_pinitializer;


      crypto();
      virtual ~crypto();

      
      virtual void defer_initialize();


      virtual __pointer(hasher) create_hasher(enum_hash ehash);


      virtual bool encrypt(memory & storageEncrypt, const memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(memory & storageDecrypt, const memory & storageEncrypt, const char * pszSalt);
      virtual bool encrypt(memory & storageEncrypt, const char * pszDecrypt, const char * pszSalt);
      virtual bool decrypt(string & strDecrypt, const memory & storageEncrypt, const char * pszSalt);


      virtual i32 key(memory & storage);
      virtual bool encrypt(memory & storageEncrypt, const memory & storageDecrypt, const memory & storageKey);
      virtual bool decrypt(memory & storageDecrypt, const memory & storageEncrypt, const memory & storageKey);

      virtual string strkey();
      virtual i32 encrypt(string & str,const char * psz,const char * pszKey);
      virtual i32 decrypt(string & str,const char * psz,const char * pszKey);


      virtual int get_md5_digest_length() const;
      virtual int get_sha1_digest_length() const;
      virtual int get_sha256_digest_length() const;
      virtual int get_nessie_digest_length() const;


      static u32 crc32(u32 dwPrevious, const char * psz);
      virtual string md5(const char * psz);
      virtual string sha1(const char * psz);
      virtual string nessie(const char * psz);

      virtual string md5(const memory & mem);
      virtual string sha1(const memory & mem);
      virtual string nessie(const memory & mem);


      virtual void hash(memory& memMd5, const block & block, enum_hash ehash);

      virtual void md5(memory & memMd5, const block& block);
      virtual void sha1(memory & memSha1, const block& block);
      virtual void sha256(memory & memSha256, const block& block);
      virtual void nessie(memory & memNessie, const block& block);

      // result is 20-byte digest
      virtual void hmac(void * result,const memory & memMessage,const memory & key);
      virtual void hmac(void * result,const string & memMessage,const string & key);

      virtual bool file_set(::payload varFile,const char * pszData,const char * pszSalt, ::apex::application * papp);
      virtual ::e_status     file_get(::payload varFile,string & str,const char * pszSalt, ::apex::application * papp);

      // get a new salt - 8 hexadecimal characters long
      // current PHP installations should not exceed 8 characters
      // on dechex( mt_rand() )
      // but we future proof it anyway with substr()
      virtual string v5_get_password_salt();
      // calculate the hash from a salt and a password
      virtual string v5_get_password_hash(const char * pszSalt,const char * pszPassword,i32 iOrder = 0);
      virtual string v5_get_passhash(const char * pszSalt,const char * pszPassword,i32 iMaxOrder = 0);
      virtual bool v5_compare_password(const char * pszPassword,const char * pszHash,i32 iOrder = 0);
      // if iOrder == 0 password is plain
      // if iOrder == 1 password is the first hash
      // if iOrder == (n > 0) password is the nth hash
      virtual bool v5_validate_plain_password(const char * pszPassword);
      virtual string v5_get_password_hash(const char * pszPassword,i32 iOrder = 0);

      virtual ::file::path get_crypt_key_file_path();
      virtual string defer_get_cryptkey();


      virtual __pointer(rsa) generate_rsa_key();

      virtual __pointer(rsa) read_priv_pem(const string & strFile);

      virtual __pointer(rsa) read_pub_pem(const string & strFile);


      virtual void err_load_rsa_strings();


      virtual void err_load_crypto_strings();


      virtual string spa_login_crypt(const char * psz,const string & pszRsa);
      virtual string spa_login_decrypt(const char * psz,const string & pszRsa);

      virtual string spa_auth_crypt(const char * psz,rsa * prsa);
      virtual string spa_auth_decrypt(const char * psz,rsa * prsa);
      virtual string spa_auth_decrypt(const char * psz,const string & pszRsa);

      virtual string txt_encrypt(const char * psz,rsa * prsa);
      virtual string txt_decrypt(const char * psz,rsa * prsa);

      virtual void np_make_zigbert_rsa(const string & strDir, const string & strSignerPath, const string & strKeyPath, const string & strOthersPath, const string & strSignature);


   };


   typedef ___pointer < crypto > crypto_pointer;

   typedef __pointer_array(rsa) rsaptra;


} //   namespace crypto






CLASS_DECL_APEX void stunCalculateIntegrity_longterm(char* hmac, const char* input, i32 length, const char *username, const char *realm, const char *password);

CLASS_DECL_APEX void stunCalculateIntegrity_shortterm(char* hmac, const char* input, i32 length, const char* key);


CLASS_DECL_APEX void hmac_evp_sha1_1234(unsigned char * hmac, unsigned int * hmacSize, const unsigned char * buf, size_t bufLen);
