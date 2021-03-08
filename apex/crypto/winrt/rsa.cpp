#include "framework.h"
#include "_winrt.h"


namespace winrt
{


   rsa::rsa()
   {


   }


   rsa::rsa(const string& nParam)
   {

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

      ::memory_file memfile;

      //blob.Magic = 0x31415352; // BCRYPT_RSAPUBLIC_MAGIC;
      blob.Magic = 0x31415352; // BCRYPT_RSAPUBLIC_MAGIC;
      blob.BitLength = 1024;
      blob.cbPublicExp = 3;
      blob.cbModulus = 1024 / 8;
      blob.cbPrime1 = 0;
      blob.cbPrime2 = 0;

      //      memory memVer;

            //    memVer.from_hex("00");

            //  memVer.prefix_der_::u32();

      memfile.write(&blob, sizeof(blob));

      memory memMod;

      string strRsaModulus(nParam);

      memMod.from_hex(strRsaModulus);

      //memMod.reverse();



      //memMod.prefix_der_::u32();

      memory memExp;

      memExp.from_hex("010001");

      //memExp.reverse();

      memfile.write(memExp.get_data(), memExp.get_size());

      memfile.write(memMod.get_data(), memMod.get_size());

      //memExp.prefix_der_::u32();

      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider^ cipher =
      
      ::Windows::Security::Cryptography::Core::AsymmetricKeyAlgorithmProvider::OpenAlgorithm(::Windows::Security::Cryptography::Core::AsymmetricAlgorithmNames::RsaPkcs1);


      //memory memKey;

      //memKey = memVer;
      //memKey += memMod;
      //memKey = memMod;
      //memKey += memExp;


      //memKey.prefix_der_sequence();

      //string strRsaPrivateKey = "-----BEGIN RSA PUBLIC KEY-----\r\n";
      //strRsaPrivateKey += chunk_split(::apex::get_system()->base64().encode(memKey));
      //strRsaPrivateKey += "-----END RSA PUBLIC KEY-----";

      //memKey.set_size(strRsaPrivateKey.get_length());

      //::memcpy_dup(memKey.get_data(), strRsaPrivateKey, memKey.get_size());

      //m_prsa = cipher->ImportPublicKey(memKey.get_os_crypt_buffer(),::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType::Pkcs1RsaPublicKey);

      m_pkey = cipher->ImportPublicKey(memfile.get_memory()->get_os_crypt_buffer(), ::Windows::Security::Cryptography::Core::CryptographicPublicKeyBlobType::BCryptPublicKey);

   }


   rsa::~rsa()
   {

      m_pkey = nullptr;

   }


   int rsa::public_encrypt(memory& out, const memory& in, string& strError)
   {

      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(m_pkey, in.get_os_crypt_buffer(), nullptr));

      return int(out.get_size());

   }


   int rsa::private_decrypt(memory& out, const memory& in, string& strError)
   {

      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_pkey, in.get_os_crypt_buffer(), nullptr));

      return int(out.get_size());

   }


   int rsa::private_encrypt(memory& out, const memory& in, string& strError)
   {

      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Encrypt(m_pkey, in.get_os_crypt_buffer(), nullptr));

      return int(out.get_size());

   }


   int rsa::public_decrypt(memory& out, const memory& in, string& strError)
   {

      out.set_os_crypt_buffer(::Windows::Security::Cryptography::Core::CryptographicEngine::Decrypt(m_pkey, in.get_os_crypt_buffer(), nullptr));

      return int(out.get_size());

   }


} // namespace winrt




__pointer(::crypto::rsa) __create_rsa(const string& str)
{

   return __new(::winrt::rsa(str));

}






