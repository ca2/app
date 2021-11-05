#pragma once


#include "aura/_.h"


#if defined(_CA2_FILE_DLL)
   #define CLASS_DECL_CA2_FILE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_CA2_FILE  CLASS_DECL_IMPORT
#endif


#include "file/filesystem/file/file.h"

#include "file/primitive/primitive.h"
