// Created by camilo on 2023-06-09 21:38 <3ThomasBorregaardSorensen!!
#pragma once


#define ENDIAN_SERIAL_ARRAY   ((const char*)&((const int)(0x00010203)))
#define ENDIAN_CPU_ARRAY      ((const char*)&((const int)(0x03020100)))
#define SERIAL_ENDIANESS             (*ENDIAN_SERIAL_ARRAY)
#define SERIAL_LITTLE_ENDIAN         0x03
#define SERIAL_BIG_ENDIAN            0x00
#define SERIAL_PDP_ENDIAN            0x02
#define SERIAL_HONEYWELL_ENDIAN      0x01
#define CPU_LITTLE_ENDIAN     (3-SERIAL_LITTLE_ENDIAN)
#define CPU_BIG_ENDIAN        (3-SERIAL_BIG_ENDIAN)
#define CPU_PDP_ENDIAN        (3-SERIAL_PDP_ENDIAN)
#define CPU_HONEYWELL_ENDIAN  (3-SERIAL_HONEYWELL_ENDIAN)


#define IS_LITTLE_ENDIAN      (SERIAL_ENDIANESS == SERIAL_LITTLE_ENDIAN)
#define IS_BIG_ENDIAN         (SERIAL_ENDIANESS == SERIAL_BIG_ENDIAN)
#define IS_PDP_ENDIAN         (SERIAL_ENDIANESS == SERIAL_PDP_ENDIAN)
#define IS_HONEYWELL_ENDIAN   (SERIAL_ENDIANESS == SERIAL_HONEYWELL_ENDIAN)


constexpr unsigned char lower_byte(::iptr i) { return (unsigned char)((::uptr)(i) & 0xff); }
constexpr unsigned char upper_byte(::iptr i) { return (unsigned char)(((::uptr)(i) >> 8) & 0xff); }
constexpr unsigned short lower_unsigned_short(::iptr i) { return (unsigned short)((::uptr)(i) & 0xffff); }
constexpr unsigned short upper_unsigned_short(::iptr i) { return (unsigned short)(((::uptr)(i) >> 16) & 0xffff); }
constexpr short upper_short(::iptr i) { return (short)(((::uptr)(i) >> 16) & 0xffff); }
constexpr unsigned int lower_unsigned_int(huge_natural u) { return (unsigned int)(u); }
constexpr unsigned int upper_unsigned_int(huge_natural u) { return (unsigned int)((u >> 32) & 0xffffffff); }


constexpr int lparam_int_x(::iptr i) { return (int)(short)lower_unsigned_short(i); }
constexpr int lparam_int_y(::iptr i) { return (int)(short)upper_unsigned_short(i); }
constexpr int u32_x(::uptr u) { return (int)(short)lower_unsigned_short(u); }
constexpr int u32_y(::uptr u) { return (int)(short)upper_unsigned_short(u); }
constexpr int u64_x(huge_natural u) { return (int)lower_unsigned_int(u); }
constexpr int u64_y(huge_natural u) { return (int)upper_unsigned_int(u); }


constexpr unsigned short make_unsigned_short(::iptr a, ::iptr b) { return (unsigned short)((unsigned char)a) | ((unsigned short)((unsigned char)b) << 8); }
constexpr int make_int(::iptr a, ::iptr b) { return (int)((unsigned short)a) | ((unsigned int)((unsigned short)b) << 16); }
constexpr unsigned int make_unsigned_int(::iptr a, ::iptr b) { return (unsigned int) make_int(a, b); }
constexpr unsigned int make_unsigned_int(::iptr a, ::iptr b, ::iptr c, ::iptr d) { return make_unsigned_int(make_unsigned_short(a, b), make_unsigned_short(c, d)); }
constexpr huge_natural make_huge_natural(unsigned int a, unsigned int b) { return ((huge_natural)a) | (((huge_natural)b) << 32ull); }


constexpr unsigned short swap_unsigned_short(unsigned short u) { return make_unsigned_short(upper_byte(u), lower_byte(u)); }
constexpr unsigned int swap_unsigned_int(unsigned int u) { return make_unsigned_int(swap_unsigned_short(upper_unsigned_short(u)), swap_unsigned_short(lower_unsigned_short(u))); }



