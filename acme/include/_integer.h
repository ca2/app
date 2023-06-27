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


constexpr ::u8 lower_u8(::iptr i) { return (::u8)(i & 0xff); }
constexpr ::u8 upper_u8(::iptr i) { return (::u8)((i >> 8) & 0xff); }
constexpr ::u16 lower_u16(::iptr i) { return (::u16)(i & 0xffff); }
constexpr ::u16 upper_u16(::iptr i) { return (::u16)((i >> 16) & 0xffff); }
constexpr ::i16 upper_i16(::iptr i) { return (::i16)((i >> 16) & 0xffff); }
constexpr ::u32 lower_u32(::u64 u) { return (::u32)(u); }
constexpr ::u32 upper_u32(::u64 u) { return (::u32)((u >> 32) & 0xffffffff); }


constexpr ::i32 i32_x(::iptr i) { return (::i32)(::i16)lower_u16(i); }
constexpr ::i32 i32_y(::iptr i) { return (::i32)(::i16)upper_u16(i); }
constexpr ::i32 u32_x(::uptr u) { return (::i32)(::i16)lower_u16(u); }
constexpr ::i32 u32_y(::uptr u) { return (::i32)(::i16)upper_u16(u); }
constexpr ::i32 u64_x(::u64 u) { return (::i32)lower_u32(u); }
constexpr ::i32 u64_y(::u64 u) { return (::i32)upper_u32(u); }


constexpr ::u16 make_u16(::iptr a, ::iptr b) { return (::u16)((::u8)a) | ((::u16)((::u8)b) << 8); }
constexpr ::i32 make_i32(::iptr a, ::iptr b) { return (::i32)((::u16)a) | ((::u32)((::u16)b) << 16); }
constexpr ::u32 make_u32(::iptr a, ::iptr b) { return (::u32) make_i32(a, b); }
constexpr ::u32 make_u32(::iptr a, ::iptr b, ::iptr c, ::iptr d) { return make_u32(make_u16(a, b), make_u16(c, d)); }


constexpr ::u16 swap_u16(::u16 u) { return make_u16(upper_u8(u), lower_u8(u)); }
constexpr ::u32 swap_u32(::u32 u) { return make_u32(swap_u16(upper_u16(u)), swap_u16(lower_u16(u))); }



