// Created acme/prototype/numeric by camilo on 2022-11-08 18:20 <3ThomasBorregaardSorensen!!
// Created acme/prototype/numeric/types.h by camilo on 2022-11-08 18:21 <3ThomasBorregaardSorensen!!
#pragma once


#if OSBIT == 32


using iptr = ::i32;
using uptr = ::u32;


#define IPTR_MAXIMUM I32_MAXIMUM
#define UPTR_MAXIMUM U32_MAXIMUM
#define IPTR_MINIMUM I32_MINIMUM


#elif OSBIT == 64


// #ifdef __APPLE__


// typedef long iptr;
// typedef ulong uptr;


// #else
//using ::i64 = ::i64 ::i32;
//using ::u64 = ::u64 ::i32;
//#if defined(HAS_HYPER_INTEGER)
//using hyper_integer = __int128;
//using hyper_natural = ::u32 __int128;
//#endif
typedef i64 iptr;
typedef u64 uptr;


#define IPTR_MAXIMUM I64_MAXIMUM
#define UPTR_MAXIMUM U64_MAXIMUM
#define IPTR_MINIMUM I64_MINIMUM


//#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS)
//
//#define DO_FOR_NUMBER_TYPES(DO) \
//DO(::i8, ::i8, ch, CHAR); \
//DO(::u8, unsigned_char, uch, UNSIGNED_CHAR); \
//DO(::i16, ::i16, sh, SHORT); \
//DO(::u16, unsigned_short, ush, UNSIGNED_SHORT); \
//DO(::i32, ::i32, i, INT); \
//DO(::u32, u32, ui, UNSIGNED_INT); \
//DO(long, long, l, LONG); \
//DO(ulong, unsigned_long, ul, UNSIGNED_LONG); \
//DO(::i64, ::i64, hi, HUGE_INTEGER); \
//DO(::u64, ::u64, hn, HUGE_NATURAL); \
//DO(::f32, ::f32, f, FLOAT); \
//DO(::f64, ::f64, d, DOUBLE);
//
//#else


//#endif



// #endif


#else


#error "OSBIT should be defined with system default pointer size in bit count."


#endif

#define DO_FOR_NUMBER_TYPES(DO) \
DO(i8, i8, i8, CHAR); \
DO(u8, u8, u8, UNSIGNED_CHAR); \
DO(i16, i16, i16, SHORT); \
DO(u16, u16, u16, UNSIGNED_SHORT); \
DO(i32, i32, i32, INT); \
DO(u32, u32, u32, UNSIGNED_INT); \
DO(i64, i64, i64, LONG_LONG); \
DO(u64, u64, u64, UNSIGNED_LONG_LONG); \
DO(f32, f32, f32, FLOAT); \
DO(f64, f64, f64, DOUBLE);

//
//
//#if OSBIT == 64
//
//typedef ::u64              rtptr;
//typedef ::u64              ulong_ptr;
//typedef ::u64              dword_ptr;
//
//#else
//
//typedef ::u32              rtptr;
//typedef ::u32              ulong_ptr;
//typedef ::u32              dword_ptr;
//
//#endif

//
//
//#if !defined(__APPLE__) && !defined(OPENBSD)
//
//
//#define ssize_t         iptr
//
//
//#endif


#define __priindex PRIiPTR


#define __pricount PRIiPTR


// insight by listening lastmiles (Dennis Clarke) talk about pthread_equal (it may end up not to be an ::i32 but a pointer in some implementations ?, so should use pthread_equal...)
/// task_index starts at 1, task_index 0 is not ok
typedef u64 task_index;



