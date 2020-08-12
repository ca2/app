#include "framework.h"
#include "linux.h"


namespace linux
{


   crypto::crypto()
   {

   }


   crypto::~crypto()
   {
   }


   ::file::path crypto::get_crypt_key_file_path()
   {

      return Context.dir().appdata() / ".ca2/cryptkey";

   }


   bool crypto::decrypt(memory & storageDecrypt, const memory & storageEncrypt, const char * pszSalt)
   {

      memory memOut;

      memory memIn;

      memIn.append(storageEncrypt.get_data(), storageEncrypt.get_size());

      memory memSalt;

      memSalt.append(pszSalt, strlen(pszSalt));

      if(!::crypto_decrypt(memOut, memIn, memSalt))
         return false;


      storageDecrypt = memOut;

      return true;

   }

   bool crypto::encrypt(memory & storageEncrypt, const memory & storageDecrypt, const char * pszSalt)
   {

      memory memOut;

      memory memIn;

      memIn.append(storageDecrypt.get_data(), storageDecrypt.get_size());

      memory memSalt;

      memSalt.append(pszSalt, strlen(pszSalt));

      if(!::crypto_encrypt(memOut, memIn, memSalt))
         return false;


      storageEncrypt = memOut;

      return true;

   }


} // namespace linux


