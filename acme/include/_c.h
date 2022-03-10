//
//  _c.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 24/04/20.
//
#pragma once


#ifdef _WIN32


#define LONG_IS_32BIT 1
#define LONG_IS_64BIT 0


#else


#if OSBIT == 64


#define LONG_IS_32BIT 0
#define LONG_IS_64BIT 1


#else


#define LONG_IS_32BIT 1
#define LONG_IS_64BIT 0


#endif


#endif



CLASS_DECL_ACME void* reverse_memchr(const void* l, int ch, size_t l_len);
CLASS_DECL_ACME void* reverse_memmem(const void* l, size_t l_len, const void* s, size_t s_len);
CLASS_DECL_ACME void* reverse_byte_not_in_block(const void* l, size_t l_len, const void* s, size_t s_len);

CLASS_DECL_ACME::u32 __u32_hash(const char* psz);

// Contains a 64-bit value representing the number
// of 100-nanosecond intervals since January 1, 1601 (UTC).
typedef u64 file_time_t;


#if !defined(WINDOWS)


typedef struct _GUID {
   unsigned long  Data1;
   unsigned short Data2;
   unsigned short Data3;
   unsigned char  Data4[ 8 ];
} GUID;


#endif


#ifndef HIBYTE
#define HIBYTE(x) (((x) >> 8) & 0x00ff)
#endif


#ifndef HIWORD
#define HIWORD(x) (((x) >> 16) & 0x0000ffff)
#endif


#ifndef LOWORD
#define LOWORD(x) ((x) & 0x0000ffff)
#endif


#ifndef MAKEWORD
#define MAKEWORD(lo, hi) (((lo) & 0xff) | (((hi) << 8) & 0xff00))
#endif


#define SWAPWORD(x)		MAKEWORD(HIBYTE(x), __LOBYTE(x))
#define SWAPLONG(x)		__MAKE_LONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))


#include "acme/constant/_constant.h"
#include "acme/constant/_enumeration.h"
#include "acme/primitive/duration/_struct.h"



