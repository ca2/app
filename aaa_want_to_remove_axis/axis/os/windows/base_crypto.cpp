#include "framework.h"
#include <Wincrypt.h>



//i32 crypto_decrypt(memory & storageDecrypt, const memory & storageEncrypt, memory & memorySalt)
//{
//
//
//   DATA_BLOB DataIn;
//   DATA_BLOB DataOut;
//
//   DATA_BLOB DataSalt;
//   DataSalt.pbData = (BYTE *) memorySalt.get_data();
//   DataSalt.cbData = (u32) memorySalt.get_size();
//
//   //--------------------------------------------------------------------
//   // Initialize the DataIn structure.
//
//   DataIn.pbData = (BYTE *) storageEncrypt.get_data();
//   DataIn.cbData = (u32) storageEncrypt.get_size();
//
//   unichar * pwsz = nullptr;

//
//   //--------------------------------------------------------------------
//   //  begin protect phase. Note that the encryption key is created
//   //  by the function and is not passed.
//
//   if(CryptUnprotectData(
//      &DataIn,
//      nullptr, // A description string
//                                          // to be included with the
//                                          // encrypted data.
//      &DataSalt,                               // Optional entropy not used.
//      nullptr,                               // Reserved.
//      nullptr,                               // Pass nullptr for the
//                                          // prompt structure.
//      0,
//      &DataOut))
//   {
////      TRACE("crypt::decrypt The encryption phase worked. \n");
//      storageDecrypt.allocate(DataOut.cbData);
//      ::memcpy_dup(storageDecrypt.get_data(), DataOut.pbData, DataOut.cbData);
//      LocalFree(pwsz);

//      LocalFree(DataOut.pbData);
//      return 1;
//   }
//   else
//   {
//      u32 dwLastError = get_last_error();
//  //    TRACELASTERROR();
//    //  TRACE("crypt::decrypt Decryption error! (1)");
//      return 0;
//   }
//}
//
//i32 crypto_encrypt(memory & storageEncrypt, const memory & storageDecrypt, memory & memorySalt)
//{
//   DATA_BLOB DataIn;
//   DATA_BLOB DataOut;
//
//   DATA_BLOB DataSalt;
//   DataSalt.pbData = (BYTE *) memorySalt.get_data();
//   DataSalt.cbData = (u32) memorySalt.get_size();
//
//
//   //--------------------------------------------------------------------
//   // Initialize the DataIn structure.
//
//   DataIn.pbData = (BYTE *) storageDecrypt.get_data();
//   DataIn.cbData = (u32) storageDecrypt.get_size();
//
////      unichar * pwsz = nullptr;

//
//   //--------------------------------------------------------------------
//   //  begin protect phase. Note that the encryption key is created
//   //  by the function and is not passed.
//
//   if(CryptProtectData(
//         &DataIn,
//         nullptr, // A description string
//                                             // to be included with the
//                                             // encrypted data.
//         &DataSalt,                               // Optional entropy not used.
//         nullptr,                               // Reserved.
//         nullptr,                               // Pass nullptr for the
//                                             // prompt structure.
//         0,
//         &DataOut))
//   {
//      //TRACE("crypt::encrypt The encryption phase worked. \n");
//      storageEncrypt.allocate(DataOut.cbData);
//      ::memcpy_dup(storageEncrypt.get_data(), DataOut.pbData, DataOut.cbData);
//      LocalFree(DataOut.pbData);
//      return 1;
//   }
//   else
//   {
//      u32 dwLastError = get_last_error();
//      //TRACE("crypt::encrypt Encryption error! (1)");
//         return 0;
//   }
//
//}
