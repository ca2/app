#pragma once


#if OSBIT == 32


typedef int iptr;
typedef unsigned int uptr;


#elif OSBIT == 64


#ifdef __APPLE__


typedef long iptr;
typedef unsigned long uptr;


#else


typedef huge_integer iptr;
typedef huge_natural uptr;


#endif


#else


#error "OSBIT should be defined with system default pointer int_size in bit count."


#endif




#if OSBIT == 64

typedef huge_natural              rtptr;
typedef huge_natural              ulong_ptr;
typedef huge_natural              dword_ptr;

#else

typedef unsigned int              rtptr;
typedef unsigned int              ulong_ptr;
typedef unsigned int              dword_ptr;

#endif



#ifndef __APPLE__


#define ssize_t         iptr


#endif


