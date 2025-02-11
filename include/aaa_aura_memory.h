#pragma once


#if OSBIT == 32


typedef int iptr;
typedef unsigned int uptr;


#elif OSBIT == 64


#ifdef __APPLE__


typedef long iptr;
typedef unsigned long uptr;


#else


typedef long long iptr;
typedef unsigned long long uptr;


#endif


#else


#error "OSBIT should be defined with system default pointer int_size in bit count."


#endif




#if OSBIT == 64

typedef unsigned long long              rtptr;
typedef unsigned long long              ulong_ptr;
typedef unsigned long long              dword_ptr;

#else

typedef unsigned int              rtptr;
typedef unsigned int              ulong_ptr;
typedef unsigned int              dword_ptr;

#endif



#ifndef __APPLE__


#define ssize_t         iptr


#endif


