///TBS__<3tbs
#pragma once

//#pragma pack(show)

#include "aura/_.h"



#if defined(_AXIS_LIBRARY)
#define CLASS_DECL_AXIS  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AXIS  CLASS_DECL_IMPORT
#endif


// #ifdef _DEBUG
// #ifndef _DEBUG
// #define _DEBUG
// #endif
// #endif


// #ifdef _DEBUG
// #define __DEBUG
// #ifndef DEBUG
// #define DEBUG
// #endif
// #else
// #define NNDEBUG
// #endif

#define CA2_AURA

#define __class(EXPORT, DERIVED, ...) \
   using DERIVED##_t =  __VA_ARGS__; \
   class EXPORT DERIVED : \
      virtual public DERIVED##_t \
   { \
   public: using DERIVED##_t::DERIVED##_t; \
   }


#define __discrete_cflag(EXPORT, CLASS, ENUM) __class(EXPORT, CLASS, enumeration < ENUM >)


#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
#define TOKEN_AT_LINE(token) TOKENPASTE2(TOKENPASTE2(token, _atLine_), __LINE__)


#define __DEBUG_POWER


#if defined(__cplusplus)

#define DECL_EXTERN_C      extern "C"
#define BEGIN_EXTERN_C      extern "C" {
#define END_EXTERN_C         }

#else

#define DECL_EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C

#endif


//#include "app/axis/version.h"


#include "__standard_type.h"


typedef i64 memsize_storage;
typedef i64 strsize_storage;


typedef iptr memsize;
typedef iptr strsize;
typedef i64 filesize;


#if WCHAR_T_SIZE == 16
#define __END_CHARBIT(xxx) __CONCAT(xxx, 16)
#define __MID_CHARBIT(xxx, zzz) __CONCAT3(xxx, 16, zzz)
#elif WCHAR_T_SIZE == 32
#define __END_CHARBIT(xxx) __CONCAT(xxx, 32)
#define __MID_CHARBIT(xxx, zzz) __CONCAT3(xxx, 32, zzz)
#else
#error "Please define WCHAR_T_SIZE"
#endif


#undef __spin_namespace


#include "axis/include/_.h"



