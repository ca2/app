// Created by speccylad(Twitch) 
// From https://github.com/deetonn/stud/blob/master/stud/forward.hpp
// by camilo on 2023-10-20 00:37 <3ThomasBorregaardSorensen!!
// Merged acme/constant/_constant.h:enum_operating_system on 2023-10-20 00:50 by camilo
#pragma once


#ifndef _STUD_FORWARD_HPP

//#define _STUD_API_BEGIN namespace stud {
//#define _STUD_UNSTABLE_API_BEGIN namespace stud::unsafe {
//#define _STUD_DETAIL_API namespace stud::__detail {
//#define _STUD_API_END }

#define _STUD_API_BEGIN 
#define _STUD_UNSTABLE_API_BEGIN 
//#define _STUD_DETAIL_API 
#define _STUD_API_END 

#define _STUD_API inline constexpr

#define _STUD_NODISCARD [[nodiscard]]

#define _STUD_NOEXCEPT(expr) noexcept(noexcept(expr))

#define DISCARD(expr) ((void)expr)
#define NOOP() DISCARD(0)

#define _STUD ::stud::
//#define _DETAIL ::stud::__detail::

#define _NODISCARD [[nodiscard]]

//_STUD_DETAIL_API

#ifdef _WIN32
_STUD_API bool __is_windows = true;
#else
_STUD_API bool __is_windows = false;
#endif

#define FOR_WINDOWS if constexpr(__is_windows)

#if defined(__linux__) 
_STUD_API bool __is_linux = true;
#else
_STUD_API bool __is_linux = false;
#endif

#define FOR_LINUX if constexpr (__is_linux)

#if defined (__linux__) || defined (__unix__)
_STUD_API bool __is_unix = true;
#else
_STUD_API bool __is_unix = false;
#endif

#define FOR_UNIX if constexpr (__is_unix)

#if defined (__APPLE__) || defined(__MACH__)
_STUD_API bool __is_macos = true;
#else
_STUD_API bool __is_macos = false;
#endif

#define FOR_MACOS if constexpr (__is_macos)

#if defined (__FreeBSD__)
_STUD_API bool __is_freebsd = true;
#else
_STUD_API bool __is_freebsd = false;
#endif


#define FOR_FREEBSD if constexpr (__is_freebsd)

#if defined (__ANDROID__)
_STUD_API bool __is_android = true;
#else
_STUD_API bool __is_android = false;
#endif


#define FOR_ANDROID if constexpr (__is_android)


_STUD_API_END

_STUD_API_BEGIN

#define SYSTEM_DISCOVERY_FUNCTION(name, builtin) \
_STUD_API bool name() noexcept { \
  return builtin; \
}

SYSTEM_DISCOVERY_FUNCTION(is_windows, __is_windows);
SYSTEM_DISCOVERY_FUNCTION(is_linux, __is_linux);
SYSTEM_DISCOVERY_FUNCTION(is_unix, __is_unix);
SYSTEM_DISCOVERY_FUNCTION(is_macos, __is_macos);
SYSTEM_DISCOVERY_FUNCTION(is_freebsd, __is_freebsd);
SYSTEM_DISCOVERY_FUNCTION(is_android, __is_android);


enum enum_operating_system
{


   e_operating_system_unknown = -1,
   e_operating_system_none = 0,
   e_operating_system_current,
   e_operating_system_windows,
   e_operating_system_macos,
   e_operating_system_ios,
   e_operating_system_linux,
   e_operating_system_android,
   e_operating_system_unix,
   e_operating_system_freebsd,


};


_STUD_API bool is_system(enum_operating_system eoperatingsystem) noexcept {
   if (eoperatingsystem == e_operating_system_windows) {
      return is_windows();
   }
   else if (eoperatingsystem == e_operating_system_linux) {
      return is_linux();
   }
   else if (eoperatingsystem == e_operating_system_unix) {
      return is_unix();
   }
   else if (eoperatingsystem == e_operating_system_macos) {
      return is_macos();
   }
   else if (eoperatingsystem == e_operating_system_freebsd) {
      return is_freebsd();
   }
   else if (eoperatingsystem == e_operating_system_android) {
      return is_android();
   }
   else {
      return false;
   }
}

#define _STUD_MAKE_NONCOPYABLE(type) _STUD_API type(const type&) noexcept = delete; \
_STUD_API type& operator=(const type&) noexcept = delete
#define _STUD_MAKE_NONMOVEABLE(type) _STUD_API type(type&&) noexcept = delete;

_STUD_API_END

#define _STUD_FORWARD_HPP
#endif