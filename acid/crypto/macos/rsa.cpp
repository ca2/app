#include "framework.h"


namespace macos
{


   rsa::rsa(const string& nParam)
   {

      CFMutableDictionaryRef parameters = CFDictionaryCreateMutable(nullptr, 0, &kCFTypeDictionaryKeyCallBacks, &kCFTypeDictionaryValueCallBacks);

      CFDictionaryAddValue(parameters, kSecAttrKeyType, kSecAttrKeyTypeRSA);

      // not needed, defaults to true    CFDictionaryAddValue(parameters, kSecAttrCanEncrypt, kCFBooleanTrue);

      memory memKeyData;

      memKeyData.from_hex(strPass);

      CFDataRef keyData = memKeyData.get_os_cf_data();

      CFErrorRef error = nullptr;

      m_prsa = SecKeyCreateFromData(parameters, keyData, &error);

      if (error != nullptr)
      {

         CFRelease(parameters);

         CFRelease(keyData);

         CFRelease(error);

         throw ::exception(error_resource);

      }

      CFRelease(parameters);

      CFRelease(keyData);

   }


   rsa::~rsa()
   {

      if (m_prsa != nullptr)
      {

         CFRelease(m_prsa);
         m_prsa = nullptr;
      }

   }


   int rsa::public_encrypt(memory& out, const memory& in, string& strError)
   {

      SecTransformRef transform = SecEncryptTransformCreate(m_prsa, &error);

      if (error != nullptr)
      {

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if (error != nullptr)
      {

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      memory memDataIn;

      memDataIn.from_hex(strRsaModulus);

      CFDataRef dataIn = memDataIn.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }


      string strHex;

      memory memory;

      memory.set_os_cf_data(data);

      memory.to_hex(strHex);

      CFRelease(data);

      CFRelease(dataIn);

      CFRelease(transform);


      return int(out.get_size());


   }





   int rsa::private_decrypt(memory& out, const memory& in, string& strError)
   {



      return int(out.get_size());

   }

   int rsa::private_encrypt(memory& out, const memory& in, string& strError)
   {


      SecTransformRef transform = SecEncryptTransformCreate(m_prsa, &error);

      if (error != nullptr)
      {

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if (error != nullptr)
      {

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      memory memDataIn;

      memDataIn.from_hex(strRsaModulus);

      CFDataRef dataIn = memDataIn.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }


      string strHex;

      memory memory;

      memory.set_os_cf_data(data);

      memory.to_hex(strHex);

      CFRelease(data);

      CFRelease(dataIn);

      CFRelease(transform);

      return int(out.get_size());

   }


   int rsa::public_decrypt(memory& out, const memory& in, string& strError)
   {



      return int(out.get_size());

   }




   int rsa::private_decrypt(memory& out, const memory& in, string& strError)
   {



      return int(out.get_size());

   }


   int rsa::private_encrypt(memory& out, const memory& in, string& strError)
   {


      SecTransformRef transform = SecEncryptTransformCreate(m_prsa, &error);

      if (error != nullptr)
      {

         CFRelease(error);

         return "";

      }

      SecTransformSetAttribute(transform, kSecPaddingKey, kSecPaddingPKCS1Key, &error);

      if (error != nullptr)
      {

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      memory memDataIn;

      memDataIn.from_hex(strRsaModulus);

      CFDataRef dataIn = memDataIn.get_os_cf_data();

      SecTransformSetAttribute(transform, kSecTransformInputAttributeName, dataIn, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }

      /* Encrypt the data. */

      CFDataRef data = (CFDataRef)SecTransformExecute(transform, &error);

      if (error != nullptr)
      {

         CFRelease(dataIn);

         CFRelease(transform);

         CFRelease(error);

         return "";

      }


      string strHex;

      memory memory;

      memory.set_os_cf_data(data);

      memory.to_hex(strHex);

      CFRelease(data);

      CFRelease(dataIn);

      CFRelease(transform);


      return int(out.get_size());

   }


   int rsa::public_decrypt(memory& out, const memory& in, string& strError)
   {

      return int(out.get_size());

   }

} // namespace macos
