#pragma once


CLASS_DECL_ACME void defer_dock_application(int_bool bDock);


CLASS_DECL_ACME WINBOOL IsProcessRunning(DWORD pid);



#include "file.h"


#include "threading.h"

#include "cross.h"

CLASS_DECL_ACME int __c_get_text_length(const char * psz);
CLASS_DECL_ACME void __c_get_text(char * pszText, int iLen, const char * psz);


/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/


#ifdef cplusplus

inline bool IsDirSep(WCHAR ch);



#endif

CLASS_DECL_ACME void set_splash(oswindow oswindow);
CLASS_DECL_ACME oswindow get_splash(void);

CLASS_DECL_ACME int get_processor_count(void);

CLASS_DECL_ACME void output_debug_string(const char * psz);
CLASS_DECL_ACME void w_output_debug_string(const widechar * psz);
#ifdef __cplusplus
CLASS_DECL_ACME void output_debug_string(const widechar * pwsz);
#endif
CLASS_DECL_ACME void writeln(const char * psz);


#include "time.h"


#if defined(MACOS)

#elif defined(APPLE_IOS)

#elif defined(LINUX)

#elif defined(_UWP)

#define BSD_STYLE_SOCKETS

#elif defined(WINDOWS_DESKTOP)

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(ANDROID)

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(SOLARIS)

#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL

#elif defined(APPLE_IOS)

#else

#error Not supported operating system

#endif





CLASS_DECL_ACME void set_command_line_dup(const char * psz);

CLASS_DECL_ACME void get_command_line_dup(char * psz, int iBuffer);





#ifdef __cplusplus

#include "windowing.h"

#endif


#include "graphics.h"


#pragma once


#include "acme/os/binreloc.h"




#ifdef AMD64
#define OS64BIT
#elif defined(__LP64)
#define OS64BIT
#else
#define OS32BIT
#endif











