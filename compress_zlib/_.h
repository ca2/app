// Refactor by camilo from bz on 2021-11-10 10:32 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/_.h"


#if defined(_compress_zlib_project)
#define CLASS_DECL_COMPRESS_ZLIB  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_COMPRESS_ZLIB  CLASS_DECL_IMPORT
#endif


int z_compress(void* dest, u64* destLen, const void* source, u64 sourceLen);
int z_uncompress(void* dest, u64* destLen, const void* source, u64 sourceLen);



