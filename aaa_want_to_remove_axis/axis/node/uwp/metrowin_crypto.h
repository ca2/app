#pragma once

typedef struct bio_st BIO;


namespace uwp
{


   //class CLASS_DECL_AXIS SSLInitializer:
   //   public ::object
   //{
   //public:

   //   static ::aura::system * s_psystem;

   //   /**
   //   init openssl
   //   bio_err
   //   create random file
   //   */
   //   SSLInitializer(::object * pobject);

   //   /**
   //   remove random file
   //   */
   //   ~SSLInitializer();

   //   void DeleteRandFile();

   //   /** SSL; ::mutex locking function callback. */
   //   //static void SSL_locking_function(i32 mode, i32 n, const char *file, i32 line);

   //   /** Return thread id. */
   //   //static unsigned long SSL_id_function();

   //   BIO *bio_err;

   //private:
   //   string m_rand_file;
   //   long m_rand_size;

   //};


   class CLASS_DECL_AXIS crypto :
      virtual public ::crypto::crypto
   {
   public:

      sockets::SSLInitializer *                             m_psslinit;



      crypto(::object * pobject);
      virtual ~crypto();


      virtual bool encrypt(memory & storageEncrypt, const memory & storageDecrypt, const char * pszSalt);
      virtual bool decrypt(memory & storageDecrypt, const memory & storageEncrypt, const char * pszSalt);
      static u32 crc32(u32 dwPrevious,const char * psz);

      void md5(memory & memMd5,const memory & mem);
      void sha1(memory & memSha1,const memory & mem);
      //void nessie(memory & memSha1,const memory & mem);

      //// result is 20-byte digest
      //void hmac(void * result,const memory & memMessage,const memory & key);
      //void hmac(void * result,const string & memMessage,const string & key);


   };


} // namespace ca4



