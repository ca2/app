#pragma once


namespace crypto_openssl
{


   class CLASS_DECL_CRYPTO_OPENSSL crypto :
      virtual public ::crypto::crypto
   {
   public:


      ::pointer<::crypto::initializer>   m_pinitializer;


      crypto();
      ~crypto() override;

      
      void defer_initialize() override;


      //virtual ::pointer<hasher>create_hasher(enum_hash ehash);


      void encrypt(memory& storageEncrypt, const memory& storageDecrypt, const memory& storageKey) override;
      void decrypt(memory& storageDecrypt, const memory& storageEncrypt, const memory& storageKey) override;


      //virtual bool encrypt(memory & storageEncrypt, const memory & storageDecrypt, const ::scoped_string & scopedstrSalt);
      //virtual bool decrypt(memory & storageDecrypt, const memory & storageEncrypt, const ::scoped_string & scopedstrSalt);
      //virtual bool encrypt(memory & storageEncrypt, const ::scoped_string & scopedstrDecrypt, const ::scoped_string & scopedstrSalt);
      //virtual bool decrypt(string & strDecrypt, const memory & storageEncrypt, const ::scoped_string & scopedstrSalt);


      //virtual int key(memory & storage);

      //virtual string strkey();
      //virtual int encrypt(string & str,const ::scoped_string & scopedstr,const ::scoped_string & scopedstrKey);
      //virtual int decrypt(string & str,const ::scoped_string & scopedstr,const ::scoped_string & scopedstrKey);


      //virtual int get_md5_digest_length() const;
      //virtual int get_sha1_digest_length() const;
      //virtual int get_sha256_digest_length() const;
      //virtual int get_nessie_digest_length() const;


      //unsigned int crc32(unsigned int dwPrevious, const ::scoped_string & scopedstr) override;
      //virtual string md5(const ::scoped_string & scopedstr);
      //virtual string sha1(const ::scoped_string & scopedstr);
      //virtual string nessie(const ::scoped_string & scopedstr);

      //virtual string md5(const memory & mem);
      //virtual string sha1(const memory & mem);
      //virtual string nessie(const memory & mem);


      int get_hash_digest_length(enum_hash) const override;


      //virtual void hash(memory& memOut, const block & blockIn, enum_hash ehash);

      //virtual void md5(memory & memMd5, const block& block);
      //virtual void sha1(memory & memSha1, const block& block);
      //virtual void sha256(memory & memSha256, const block& block);
      //virtual void nessie(memory & memNessie, const block& block);

      // result is 20-unsigned char digest
      void hmac(void * result,const memory & memMessage,const memory & key) override;
      void hmac(void * result,const string & memMessage,const string & key) override;

      //virtual bool file_set(::payload payloadFile,const ::scoped_string & scopedstrData,const ::scoped_string & scopedstrSalt, ::apex::application * papp);
      //virtual void     file_get(::payload payloadFile,string & str,const ::scoped_string & scopedstrSalt, ::apex::application * papp);

      // get a aaa_primitive_new salt - 8 hexadecimal characters long
      // current PHP installations should not exceed 8 characters
      // on dechex( mt_rand() )
      // but we future proof it anyway with substr()
      //virtual string v5_get_password_salt();
      //// calculate the hash from a salt and a password
      //virtual string v5_get_password_hash(const ::scoped_string & scopedstrSalt,const ::scoped_string & scopedstrPassword,int iOrder = 0);
      //virtual string v5_get_passhash(const ::scoped_string & scopedstrSalt,const ::scoped_string & scopedstrPassword,int iMaxOrder = 0);
      //virtual bool v5_compare_password(const ::scoped_string & scopedstrPassword,const ::scoped_string & scopedstrHash,int iOrder = 0);
      //// if iOrder == 0 password is plain
      //// if iOrder == 1 password is the first hash
      //// if iOrder == (n > 0) password is the nth hash
      //virtual bool v5_validate_plain_password(const ::scoped_string & scopedstrPassword);
      //virtual string v5_get_password_hash(const ::scoped_string & scopedstrPassword,int iOrder = 0);

      //virtual ::file::path get_crypt_key_file_path();
      //virtual string defer_get_cryptkey();

      
      ::pointer<::crypto::rsa>create_rsa_key(const ::string& strRsa) override;

      ::pointer<::crypto::rsa>generate_rsa_key() override;

      ::pointer<::crypto::rsa>read_priv_pem(const ::string & strFile) override;

      ::pointer<::crypto::rsa>read_pub_pem(const ::string & strFile) override;


      void err_load_rsa_strings();


      void err_load_crypto_strings();


      //virtual string spa_login_crypt(const ::scoped_string & scopedstr,const string & pszRsa);
      //virtual string spa_login_decrypt(const ::scoped_string & scopedstr,const string & pszRsa);

      //virtual string spa_auth_crypt(const ::scoped_string & scopedstr,rsa * prsa);
      //virtual string spa_auth_decrypt(const ::scoped_string & scopedstr,rsa * prsa);
      //virtual string spa_auth_decrypt(const ::scoped_string & scopedstr,const string & pszRsa);

      //virtual string txt_encrypt(const ::scoped_string & scopedstr,rsa * prsa);
      //virtual string txt_decrypt(const ::scoped_string & scopedstr,rsa * prsa);

      virtual void np_make_zigbert_rsa(const ::string & strDir, const ::string & strSignerPath, const ::string & strKeyPath, const ::string & strOthersPath, const ::string & strSignature);


   };


   //typedef ::pointer<crypto>crypto_pointer;

   //typedef pointer_array < rsa > rsaptra;


} //   namespace crypto_openssl


CLASS_DECL_APEX void stunCalculateIntegrity_longterm(char* hmac, const char* input, int length, const char *username, const char *realm, const char *password);

CLASS_DECL_APEX void stunCalculateIntegrity_shortterm(char* hmac, const char* input, int length, const char* key);


CLASS_DECL_APEX void hmac_evp_sha1_1234(unsigned char * hmac, unsigned int * hmacSize, const unsigned char * buf, size_t bufLen);



