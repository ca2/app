#pragma once


#if OSBIT == 32


typedef i32 iptr;
typedef u32 uptr;


#elif OSBIT == 64


#ifdef __APPLE__


typedef long iptr;
typedef unsigned long uptr;


#else


typedef i64 iptr;
typedef u64 uptr;


#endif


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



#ifndef __APPLE__


#define ssize_t         iptr


#endif


