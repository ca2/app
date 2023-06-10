// Created by camilo on 2023-06-09 21:38 <3ThomasBorregaardSorensen!!
#pragma once


constexpr ::u8 lower_u8(::iptr i) { return (::u8)(i & 0xff); }
constexpr ::u8 upper_u8(::iptr i) { return (::u8)((i >> 8) & 0xff); }
constexpr ::u16 lower_u16(::iptr i) { return (::u16)(i & 0xffff); }
constexpr ::u16 upper_u16(::iptr i) { return (::u16)((i >> 16) & 0xffff); }
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



