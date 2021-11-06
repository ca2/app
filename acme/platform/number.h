#pragma once


//#include <limits.h>


/* Definition of minimum-width integer types
*
* u8   -> u32 integer type, at least 8 bits, equivalent to uchar
* u16  -> u32 integer type, at least 16 bits
* u32  -> u32 integer type, at least 32 bits
*
* s8, s16, s32  -> signed counterparts of u8, u16, u32
*
* Always use macro's T8(), T16() or T32() to obtain exact-width results,
* i.e., to specify the size_i32 of the result of each expression.
*/

/*typedef signed char s8;
typedef uchar u8;

#if UINT_MAX >= 4294967295UL

typedef i16 s16;
typedef i32 s32;
typedef u16 u16;
typedef u32 u32;

#define ONE32   0xffffffffU

#else

typedef i32 s16;
typedef signed long s32;
typedef u32 u16;
typedef u32 long u32;

#define ONE32   0xffffffffUL

#endif*/

#if UINT_MAX >= 4294967295UL

#define ALLONES32   0xffffffffU

#else

#define ALLONES32   0xffffffffUL

#endif

#define ALLONES8    0xffU
#define ALLONES16   0xffffU

#define CLIP8(x)   ((x) & ALLONES8)
#define CLIP16(x)  ((x) & ALLONES16)
#define CLIP32(x)  ((x) & ALLONES32)

#ifdef _MSC_VER
//typedef u64 u64;
//typedef i64 s64;
#define ULL(v)   (v##ui64)
#define ALLONES64   ULL(0xffffffffffffffff)
#else  /* !_MSC_VER */
//typedef u32 long long u64;
//typedef signed long long s64;
#define ULL(v)   (v##ULL)
#define ALLONES64   ULL(0xffffffffffffffff)
#endif /* ?_MSC_VER */
#define CLIP64(x)  ((x) & ONE64)
#define ROTR64(v, n)   (((v) >> (n)) | CLIP64((v) << (64 - (n))))
/*
* Note: the test is used to detect native 64-bit architectures;
* if the u32 long is strictly greater than 32-bit, it is
* assumed to be at least 64-bit. This will not work correctly
* on (old) 36-bit architectures (PDP-11 for instance).
*
* On non-64-bit architectures, "long long" is used.
*/

/*
* U8TO32_BIG(c) returns the 32-bit value stored in big-endian convention
* in the uchar array pointed to by c.
*/
#define U8TO32_BIG(c)  (((u32)CLIP8(*(c)) << 24) | ((u32)CLIP8(*((c) + 1)) << 16) | ((u32)CLIP8(*((c) + 2)) << 8) | ((u32)CLIP8(*((c) + 3))))

/*
* U8TO32_LITTLE(c) returns the 32-bit value stored in little-endian convention
* in the uchar array pointed to by c.
*/
#define U8TO32_LITTLE(c)  (((u32)CLIP8(*(c))) | ((u32)CLIP8(*((c) + 1)) << 8) | (u32)CLIP8(*((c) + 2)) << 16) | ((u32)CLIP8(*((c) + 3)) << 24))

/*
* U8TO32_BIG(c, v) stores the 32-bit-value v in big-endian convention
* into the uchar array pointed to by c.
*/
#define U32TO8_BIG(c, v)    do { u32 x = (v); u8 *d = (c); d[0] = CLIP8(x >> 24); d[1] = CLIP8(x >> 16); d[2] = CLIP8(x >> 8); d[3] = CLIP8(x); } while (0)

/*
* U8TO32_LITTLE(c, v) stores the 32-bit-value v in little-endian convention
* into the uchar array pointed to by c.
*/
#define U32TO8_LITTLE(c, v)    do { u32 x = (v); u8 *d = (c); d[0] = CLIP8(x); d[1] = CLIP8(x >> 8); d[2] = CLIP8(x >> 16); d[3] = CLIP8(x >> 24); } while (0)

/*
* ROTL32(v, n) returns the value of the 32-bit u32 value v after
* a rotation of n bits to the left. It might be replaced by the appropriate
* architecture-specific macro.
*
* It evaluates v and n twice.
*
* The compiler might emit a warning if n is the constant 0. The result
* is undefined if n is greater than 31.
*/
#define ROTL32(v, n)   (CLIP32((v) << (n)) | ((v) >> (32 - (n))))
