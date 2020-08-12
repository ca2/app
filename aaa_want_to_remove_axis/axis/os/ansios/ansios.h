#pragma once


#ifdef cplusplus


i32 crypto_encrypt(memory & storageEncrypt,const memory & storageDecrypt,memory & key);
i32 crypto_decrypt(memory & storageDecrypt,const memory & storageEncrypt,memory & key);


#endif


#include "ansios_multithreading.h"
