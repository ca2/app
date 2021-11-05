#pragma once


#include "acme/_.h"


#if defined(_COMPRESS_BZIP2_LIBRARY)
#define CLASS_DECL_COMPRESS_BZIP2  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_COMPRESS_BZIP2  CLASS_DECL_IMPORT
#endif



