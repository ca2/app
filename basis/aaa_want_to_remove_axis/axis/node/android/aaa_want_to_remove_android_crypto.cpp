#include "framework.h"
//#include "android.h"


namespace android
{


   crypto::crypto(::object * pobject) :
      ::object(pobject),
      ::crypto::crypto(pobject)
   {
   }


   crypto::~crypto()
   {
   }


   ::file::path crypto::get_crypt_key_file_path()
   {

      return pcontext->m_papexcontext->dir().appdata() /  ".ca2/cryptkey";

   }


   //bool crypto::decrypt(memory & storageDecrypt, const memory & storageEncrypt, const char * pszSalt)
   //{

   //   memory memOut;

   //   memory memIn;

   //   memIn.assign(storageEncrypt.get_data(), storageEncrypt.get_size());

   //   if(!::crypto_decrypt(memOut, memIn, pszSalt))
   //      return false;


   //   storageDecrypt = memOut;

   //   return true;

   //}

   //bool crypto::encrypt(memory & storageEncrypt, const memory & storageDecrypt, const char * pszSalt)
   //{

   //   memory memOut;

   //   memory memIn;

   //   memIn.assign(storageDecrypt.get_data(), storageDecrypt.get_size());

   //   if(!::crypto_encrypt(memOut, memIn, pszSalt))
   //      return false;


   //   storageEncrypt = memOut;

   //   return true;

   //}


} // namespace android


