// Created acme/prototype/numeric by camilo on 2022-11-08 18:20 <3ThomasBorregaardSorensen!!
// Created acme/prototype/numeric/types.h by camilo on 2022-11-08 18:21 <3ThomasBorregaardSorensen!!
#pragma once


#if OSBIT == 32


using iptr = int;
using uptr = unsigned int;


#define IPTR_MAXIMUM I32_MAXIMUM
#define UPTR_MAXIMUM U32_MAXIMUM
#define IPTR_MINIMUM I32_MINIMUM


#elif OSBIT == 64


// #ifdef __APPLE__


// typedef long iptr;
// typedef unsigned long uptr;


// #else
using huge_integer = long long int;
using huge_natural = unsigned long long int;
#if defined(HAS_HYPER_INTEGER)
using hyper_integer = __int128;
using hyper_natural = unsigned __int128;
#endif
using iptr = huge_integer;
using uptr = huge_natural;


#define IPTR_MAXIMUM I64_MAXIMUM
#define UPTR_MAXIMUM U64_MAXIMUM
#define IPTR_MINIMUM I64_MINIMUM


//#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS)
//
//#define DO_FOR_NUMBER_TYPES(DO) \
//DO(char, char, ch, CHAR); \
//DO(unsigned char, unsigned_char, uch, UNSIGNED_CHAR); \
//DO(short, short, sh, SHORT); \
//DO(unsigned short, unsigned_short, ush, UNSIGNED_SHORT); \
//DO(int, int, i, INT); \
//DO(unsigned int, unsigned_int, ui, UNSIGNED_INT); \
//DO(long, long, l, LONG); \
//DO(unsigned long, unsigned_long, ul, UNSIGNED_LONG); \
//DO(huge_integer, huge_integer, hi, HUGE_INTEGER); \
//DO(huge_natural, huge_natural, hn, HUGE_NATURAL); \
//DO(float, float, f, FLOAT); \
//DO(double, double, d, DOUBLE);
//
//#else

#define DO_FOR_NUMBER_TYPES(DO) \
DO(char, char, ch, CHAR); \
DO(unsigned char, unsigned_char, uch, UNSIGNED_CHAR); \
DO(short, short, sh, SHORT); \
DO(unsigned short, unsigned_short, ush, UNSIGNED_SHORT); \
DO(int, int, i, INT); \
DO(unsigned int, unsigned_int, ui, UNSIGNED_INT); \
DO(huge_integer, huge_integer, hi, HUGE_INTEGER); \
DO(huge_natural, huge_natural, hn, HUGE_NATURAL); \
DO(float, float, f, FLOAT); \
DO(double, double, d, DOUBLE);

//#endif



// #endif


#else


#error "OSBIT should be defined with system default pointer size in bit count."


#endif


//
//
//#if OSBIT == 64
//
//typedef huge_natural              rtptr;
//typedef huge_natural              ulong_ptr;
//typedef huge_natural              dword_ptr;
//
//#else
//
//typedef unsigned int              rtptr;
//typedef unsigned int              ulong_ptr;
//typedef unsigned int              dword_ptr;
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


namespace collection
{


   using index = iptr;


} // namespace collection


#define __priindex PRIiPTR


namespace collection
{

   
   using count = ::iptr;


} // namespace collection


#define __pricount PRIiPTR



