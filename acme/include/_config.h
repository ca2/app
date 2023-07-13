#pragma once


#define NTDDI_VERSION   0x0A000000 // NTDDI_WIN10
#define _WIN32_WINNT    0x0A00 // _WIN32_WINNT_WIN10
#define WINVER          0x0A00 // _WIN32_WINNT_WIN10
#define _WIN32_IE       0x0A00 // _WIN32_IE_IE110


#define WCHAR_T_SIZE 16

#ifndef UNIVERSAL_WINDOWS
#define UNIVERSAL_WINDOWS
#endif

#ifndef WINDOWS
#define WINDOWS
#endif

#ifndef _WINDOWS
#define _WINDOWS
#endif


#ifndef WIN32
#define WIN32
#endif


#define OPERATING_SYSTEM_NAMESPACE universal_windows

#define DEFAULT_DIR_SEPARATOR "\\"


#define VARIADIC_TEMPLATE_FORMAT2


#define WINRT_SOCKETS
//#define BSD_STYLE_SOCKETS


#define OPERATING_SYSTEM_NAME   "universal_windows"

// #ifdef _DEBUG
// #define DEBUG
// #endif


#define DECL_C __cdecl


#define CLASS_DECL_EXPORT __declspec(dllexport)
#define CLASS_DECL_IMPORT __declspec(dllimport)
#define CLASS_DECL_THREAD __declspec(thread)

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_RAND_S

#define __PLACEMENT_NEW_INLINE



#define _WIDEN(x) L#x



#include "bit.h"


#pragma warning(disable:4250) // disable warning if inherited via dominance
#pragma warning(disable:4275) // disable warning about dll-interface inheriting from non-dll interface (always true for template bases)... : classical and clear linkage errors will appear if it is not template class


#define DRAWDIB_INCLUDE_STRETCHDIB


#define static_inline static







#ifdef __cplusplus

#define LOG_THIS_TAG (__type_name(this))
#define LOG_MEMBER_PREFIX __FUNCTION__

#define ALOG_FUNCTION __FUNCTION__
#define ALOG_LINE __LINE__

#endif


#define STR_NEWLINE "\r\n"



