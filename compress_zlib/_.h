// Refactor by camilo from bz on 2021-11-10 10:32 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/_.h"


#if defined(_compress_zlib_project)
#define CLASS_DECL_COMPRESS_ZLIB  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_COMPRESS_ZLIB  CLASS_DECL_IMPORT
#endif


int z_compress(void* dest, huge_natural* destLen, const void* source, huge_natural sourceLen);
int z_uncompress(void* dest, huge_natural* destLen, const void* source, huge_natural sourceLen);



