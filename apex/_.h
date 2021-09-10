///TBS__<3tbs
#pragma once

//#pragma pack(show)


#include "acme/_.h"


#if defined(_APEX_LIBRARY)
#define CLASS_DECL_APEX  CLASS_DECL_EXPORT
#define LIBIDN_BUILDING
#else
#define CLASS_DECL_APEX  CLASS_DECL_IMPORT
#endif




#define CA2_APEX

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


//#include "app/apex/version.h"


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




#ifdef __cplusplus


namespace apex
{


   //class patch;
   class history;
   class session;
   class system;
   class user;


   class application;


} // namespace apex


#undef SYSTEM_TYPE
#define SYSTEM_TYPE ::apex::system

#undef SESSION_TYPE
#define SESSION_TYPE ::apex::session

#undef APP_TYPE
#define APP_TYPE ::application


#endif


#if !defined(_UWP) && !defined(APPLE_IOS) && !defined(ANDROID) && !defined(SMALLCODE) && !defined(RASPBIAN)

#define HOTPLUGIN_SUBSYSTEM

#endif

#include "apex/node/operating_system/operating_system.h"

#include "apex/include/_include.h"



//#define __get_acid_app \
//extern "C" __declspec(dllexport) ::application * get_acid_app() \
//{ \
//\
//   return new application(); \
//\
//}


