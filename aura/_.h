///TBS__<3tbs
#pragma once

//#pragma pack(show)


#include "aqua/_.h"


#if defined(_AURA_LIBRARY)
#define CLASS_DECL_AURA  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_AURA  CLASS_DECL_IMPORT
#endif



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



#include "__standard_type.h"


typedef iptr memsize_storage;
typedef iptr strsize_storage;


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





#if defined(DEBUG)


#define RELEASE_INLINE


#else


#define RELEASE_INLINE inline


#endif


#define MEMORY_INLINE RELEASE_INLINE


#if defined(WINDOWS)


#define inplace_new_throw_spec noexcept
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

#elif defined(FREEBSD)
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


//#if defined(__cplusplus) && !defined(_ACID_LIBRARY)
//#include "aura/memory/allocation.h"
//#endif


#ifdef __cplusplus


namespace aura
{


   //class patch;
   class history;
   class application;
   class session;
   class system;


} // namespace aura


#undef SYSTEM_TYPE
#define SYSTEM_TYPE ::aura::system

#undef SESSION_TYPE
#define SESSION_TYPE ::aura::session

#undef APP_TYPE
#define APP_TYPE ::aura::application


#endif


#if !defined(_UWP) && !defined(APPLE_IOS) && !defined(ANDROID) && !defined(SMALLCODE) && !defined(RASPBIAN)

#define HOTPLUGIN_SUBSYSTEM

#endif

//#include "aura/platform/object_reference_count_debug.h"

//#include "aura/platform/object_type_counter.h"

//#include "aura/const/_const.h"

//#include "aura/platform/struct.h"

#include "aura/node/operating_system/operating_system.h"

//#include "aura/memory/heap_c.h"
//
//#include "aura/memory/allocate_processor_cache_oriented.h"

//#include "aura/platform/number.h"

#include "aura/include/_include.h"



//#define __get_acid_app \
//extern "C" __declspec(dllexport) ::aura::application * get_acid_app() \
//{ \
//\
//   return new application(); \
//\
//}


