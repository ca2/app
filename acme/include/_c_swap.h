#pragma once


//#ifndef HIBYTE
//#define HIBYTE(x) (((x) >> 8) & 0x00ff)
//#endif
//
//
//#ifndef HIWORD
//#define HIWORD(x) (((x) >> 16) & 0x0000ffff)
//#endif
//
//
//#ifndef LOWORD
//#define LOWORD(x) ((x) & 0x0000ffff)
//#endif
//
//
//#ifndef MAKEWORD
//#define MAKEWORD(lo, hi) (((lo) & 0xff) | (((hi) << 8) & 0xff00))
//#endif
//
//
//
//#define SWAPWORD(x)		MAKEWORD(HIBYTE(x), lower_byte(x))
//#define SWAPLONG(x)		make_int(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))
//
//
//
//#define first_unsigned_short(u) ((u) & 0xffff)
//#define second_unsigned_short(u) (((u) >> 16) & 0xffff)
//#define first_short(u) ((short)(((int)(u)) & 0xffff)) // signed first_unsigned_short or at least should be designed to be signed
//#define second_short(u) ((short)((((int)(u)) >> 16) & 0xffff)) // signed second_unsigned_short or at least should be designed to be signed
//#define x_short(u) first_short(u)
//#define y_short(u) second_short(u)
//#define lower32_from64(u) ((u) & 0xffffffff)
//#define upper32_from64(u) ((u >> 32) & 0xffffffff)
//
//
//
