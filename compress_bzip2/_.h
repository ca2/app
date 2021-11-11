// Refactor by camilo from bz on 2021-11-10 10:32 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/_.h"


#if defined(_COMPRESS_BZIP2_LIBRARY)
#define CLASS_DECL_COMPRESS_BZIP2  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_COMPRESS_BZIP2  CLASS_DECL_IMPORT
#endif



