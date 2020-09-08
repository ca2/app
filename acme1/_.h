///TBS__<3tbs
#pragma once

//#pragma pack(show)




#include "acme/version/version.h"
#include "acme/platform/_features.h"
#include "platform/platform_setup.h"
#include "setup/debug.h"
#include "platform/_.h"
#include "include/_setup.h"

#if defined(_ace_LIBRARY)
#define CLASS_DECL_ACME  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_ACME  CLASS_DECL_IMPORT
#endif


#ifdef DEBUG
#ifndef _DEBUG
#define _DEBUG
#endif
#endif


#ifdef _DEBUG
#define __DEBUG
#ifndef DEBUG
#define DEBUG
#endif
#else
#define NNDEBUG
#endif

#define CA2_ace

#define __class(EXPORT, DERIVED, ...) \
   using DERIVED##_t =  __VA_ARGS__; \
   class EXPORT DERIVED : \
      virtual public DERIVED##_t \
   { \
   public: using DERIVED##_t::DERIVED##_t; \
   }


#define __discrete_cflag(EXPORT, CLASS, ENUM) __class(EXPORT, CLASS, cflag < ENUM >)


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


//#include "app/acme/version.h"


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


#if defined(__cplusplus)

inline bool __found(::i32 i) { return i >= 0; }
inline bool __not_found(::i32 i) { return i < 0; }
inline bool __found(::i64 i) { return i >= 0; }
inline bool __not_found(::i64 i) { return i < 0; }

#else

#define __found_index(i) ((i) >= 0)
#define __not_found_index(i) ((i) < 0)

#endif


#if defined(DEBUG)


#define RELEASE_INLINE


#else


#define RELEASE_INLINE inline


#endif


#define MEMORY_INLINE RELEASE_INLINE


#if defined(WINDOWS)

//#define inplace_new_throw_spec
#define inplace_new_throw_spec noexcept // as of C++17
#define new_throw_spec
#define del_throw_spec noexcept
#define MEMORY_DECL __cdecl

#elif defined(SOLARIS)

#define inplace_new_throw_spec
#define new_throw_spec throw (std::bad_alloc)
#define del_throw_spec throw()
#define MEMORY_DECL

#elif defined(LINUX)
#define inplace_new_throw_spec noexcept
#define new_throw_spec
#define del_throw_spec noexcept
#define MEMORY_DECL

#elif defined(__APPLE__)

#define inplace_new_throw_spec throw()
#define new_throw_spec
#define del_throw_spec throw()
#define MEMORY_DECL

#elif defined(ANDROID)

#define inplace_new_throw_spec noexcept
#define new_throw_spec
#define del_throw_spec noexcept
#define MEMORY_DECL

#else

#define inplace_new_throw_spec
#define new_throw_spec
#define del_throw_spec
#define MEMORY_DECL

#endif


#if defined(__cplusplus) && !defined(_ACID_LIBRARY)
#include "acme/memory/allocation.h"
#endif


#ifdef __cplusplus


namespace acme
{


   //class patch;
   class history;
   //class application;
   //class session;
   //class system;


} // namespace acme


#undef SYSTEM_TYPE
#define SYSTEM_TYPE ::acme::system

#undef SESSION_TYPE
#define SESSION_TYPE ::acme::session

#undef APP_TYPE
#define APP_TYPE ::acme::application


#endif


#if !defined(_UWP) && !defined(APPLE_IOS) && !defined(ANDROID) && !defined(SMALLCODE) && !defined(RASPBIAN)

#define HOTPLUGIN_SUBSYSTEM

#endif

#include "acme/platform/obj_ref_dbg.h"

#include "acme/platform/obj_typ_ctr.h"

#include "acme/const/_const.h"

//#include "acme/platform/struct.h"

//#include "acme/os/acme.h"

#include "acme/memory/heap_c.h"

#include "acme/memory/allocate_processor_cache_oriented.h"

#include "acme/platform/number.h"

#include "acme/include/_include.h"



//#define __get_acid_app \
//extern "C" __declspec(dllexport) ::acme::application * get_acid_app() \
//{ \
//\
//   return new application(); \
//\
//}


