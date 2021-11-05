#pragma once


namespace android
{


   class CLASS_DECL_AXIS crypto :
      virtual public ::crypto::crypto
   {
   public:


      crypto(::object * pobject);
      virtual ~crypto();


      //virtual bool encrypt(memory & storageEncrypt, const memory & storageDecrypt, const ::string & pszSalt);
      //virtual bool decrypt(memory & storageDecrypt, const memory & storageEncrypt, const ::string & pszSalt);


      virtual ::file::path get_crypt_key_file_path();



   };


} // namespace android



