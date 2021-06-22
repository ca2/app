#pragma once


#ifdef _WIN32


CLASS_DECL_ACME void* memmem(const void* l, size_t l_len, const void* s, size_t s_len);


#endif


CLASS_DECL_ACME void* reverse_memchr(const void* l, int ch, size_t l_len);
CLASS_DECL_ACME void* reverse_memmem(const void* l, size_t l_len, const void* s, size_t s_len);
CLASS_DECL_ACME void* reverse_byte_not_in_block(const void* l, int l_len, const void* s, size_t s_len);


//#if !defined(WINDOWS)
//
//
//#include "pmutex_lock.h"
//
//
//#endif


#include "datetime_c.h"


#include "ansios_file.h"


#include "file_raw.h"




