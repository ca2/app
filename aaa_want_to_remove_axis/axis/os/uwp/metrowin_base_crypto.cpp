#include "framework.h"



int crypto_decrypt(memory & storageDecrypt, const memory & storageEncrypt, memory & memSalt)
{

   UNREFERENCED_PARAMETER(memSalt);

   ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider ^ provider = ref new ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider;

   ::Windows::Storage::Streams::IBuffer ^ bufferIn = storageEncrypt.get_os_buffer();

   ::Windows::Storage::Streams::IBuffer ^ bufferOut = wait(provider->UnprotectAsync(bufferIn));

   storageDecrypt.set_os_crypt_buffer(bufferOut);

   return 1;

}

int crypto_encrypt(memory & storageEncrypt, const memory & storageDecrypt, memory & memSalt)
{

   UNREFERENCED_PARAMETER(memSalt);

   ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider ^ provider = ref new ::Windows::Security::Cryptography::DataProtection::DataProtectionProvider("LOCAL=user");

   ::Windows::Storage::Streams::IBuffer ^ bufferIn = storageDecrypt.get_os_buffer();

   ::Windows::Storage::Streams::IBuffer ^ bufferOut = wait(provider->ProtectAsync(bufferIn));

   storageEncrypt.set_os_crypt_buffer(bufferOut);

   return 1;

}
