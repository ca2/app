#pragma once


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


#define make64_from32(l, h) ((::u64) (l)) | (((::u64) (h)) << 32)
#define first_u16(u) ((u) & 0xffff)
#define second_u16(u) (((u) >> 16) & 0xffff)
#define first_i16(u) ((::i16)(((::i32)(u)) & 0xffff)) // signed first_u16 or at least should be designed to be signed
#define second_i16(u) ((::i16)((((::i32)(u)) >> 16) & 0xffff)) // signed second_u16 or at least should be designed to be signed
#define x_i16(u) first_i16(u)
#define y_i16(u) second_i16(u)
#define lower32_from64(u) ((u) & 0xffffffff)
#define upper32_from64(u) ((u >> 32) & 0xffffffff)



