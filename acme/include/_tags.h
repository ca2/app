// Created by camilo on 2023-06-14 13:24 <3ThomasBorregaardSorensen!!
#pragma once


struct no_initialize_t {};




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


