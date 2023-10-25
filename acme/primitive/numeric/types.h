// Created acme/primitive/numeric by camilo on 2022-11-08 18:20 <3ThomasBorregaardSorensen!!
// Created acme/primitive/numeric/types.h by camilo on 2022-11-08 18:21 <3ThomasBorregaardSorensen!!
#pragma once


#if OSBIT == 32


using iptr = i32;
using uptr = u32;


#define IPTR_MAXIMUM I32_MAXIMUM
#define UPTR_MAXIMUM U32_MAXIMUM
#define IPTR_MINIMUM I32_MINIMUM


#elif OSBIT == 64


// #ifdef __APPLE__


// typedef long iptr;
// typedef unsigned long uptr;


// #else


using iptr = i64;
using uptr = u64;

#define IPTR_MAXIMUM I64_MAXIMUM
#define UPTR_MAXIMUM U64_MAXIMUM
#define IPTR_MINIMUM I64_MINIMUM

// #endif


#else


#error "OSBIT should be defined with system default pointer size_i32 in bit count."


#endif




#if OSBIT == 64

typedef u64              rtptr;
typedef u64              ulong_ptr;
typedef u64              dword_ptr;

#else

typedef u32              rtptr;
typedef u32              ulong_ptr;
typedef u32              dword_ptr;

#endif



#if !defined(__APPLE__) && !defined(OPENBSD)


#define ssize_t         iptr


#endif





#ifdef index
#undef index
#endif // index


using index = iptr;


#define __priindex PRIiPTR




using count = iptr;


#define __pricount PRIiPTR




