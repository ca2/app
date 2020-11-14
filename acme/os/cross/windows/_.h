#pragma once


#pragma pack(push, cross_windows, 1)


// Contains a 64-bit value representing the number
// of 100-nanosecond intervals since January 1, 1601 (UTC).
using filetime_t = ::u64;

using color32_t = ::u32;

using dummy_pointer = void *;

typedef struct _tagSIZE32
{

    ::i32 cx;
    ::i32 cy;

} SIZE32, * PSIZE32, * LPSIZE32;


typedef const SIZE32 * LPCSIZE32;

typedef struct _tagPOINT32
{

    ::i32 x;
    ::i32 y;

} POINT32, * PPOINT32, * LPPOINT32;


typedef const POINT32 * LPCPOINT32;


typedef struct _tagRECT32
{

    ::i32 left;
    ::i32 top;
    ::i32 right;
    ::i32 bottom;

} RECT32, * PRECT32, * LPRECT32;


typedef const RECT32 * LPCRECT32;


typedef struct _tagMESSAGE
{

    oswindow        hwnd;
    ::u32           message;
    WPARAM          wParam;
    LPARAM          lParam;
    ::u32           time;
    POINT32         pt;

} MESSAGE, * PMESSAGE, * LPMESSAGE;

typedef const MESSAGE * LPCMESSAGE;


#ifdef WINDOWS


using HSYNC = HANDLE;


#define INVALID_HSYNC_VALUE INVALID_HANDLE_VALUE


#else


#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)


#define WS_EX_LAYERED           0x00080000


#define MAKEWORD(a, b)      ((::u16)(((byte)(((dword_ptr)(a)) & 0xff)) | ((::u16)((byte)(((dword_ptr)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((::i32)(((::u16)(((dword_ptr)(a)) & 0xffff)) | ((::u32)((::u16)(((dword_ptr)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((::u16)(((dword_ptr)(l)) & 0xffff))
#define HIWORD(l)           ((::u16)((((dword_ptr)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((byte)(((dword_ptr)(w)) & 0xff))
#define HIBYTE(w)           ((byte)((((dword_ptr)(w)) >> 8) & 0xff))



#define WS_CHILD            0x40000000L
#define WS_VISIBLE          0x10000000L



#define STATUS_WAIT_0            ((::u32   ) 0x00000000L)
#define STATUS_ABANDONED_WAIT_0  ((::u32   ) 0x00000080L)
#define STATUS_USER_APC          ((::u32   ) 0x000000C0L)
#define STATUS_TIMEOUT           ((::u32   ) 0x00000102L)


#ifndef _UWP

#define WAIT_FAILED              ((::u32   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((::u32   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((::u32   ) STATUS_ABANDONED_WAIT_0 + 0)

#endif

#define WAIT_IO_COMPLETION                   STATUS_USER_APC

// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64



typedef unsigned long WINULONG;
typedef WINULONG *PWINULONG;
typedef unsigned short WINUSHORT;
typedef WINUSHORT *PWINUSHORT;
typedef char *PSZ;
typedef unsigned char WINUCHAR;
typedef WINUCHAR *PWINUCHAR;


#include "windows_wincon.h"


typedef struct tagCREATESTRUCTA
{
   void *         lpCreateParams;
   void *         hInstance;
   void *         hMenu;
   oswindow       hwndParent;
   i32            cy;
   i32            cx;
   i32            y;
   i32            x;
   ::i32          style;
   const char *   lpszName;
   const char *   lpszClass;
   ::u32          dwExStyle;
} CREATESTRUCTA,*LPCREATESTRUCTA;



#define WAIT_TIMEOUT                     258L    // dderror


#ifdef cplusplus

class event;

#endif

struct oswindow_data;

typedef struct oswindow_data * oswindow;



typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE, *PTBYTE ;
typedef void * LPSECURITY_ATTRIBUTES;
#define _MAX_PATH 260
#define MAX_PATH _MAX_PATH
#define UNREFERENCED_PARAMETER(u)	(void)(u)
#define U32_INFINITE_TIMEOUT 0xffffffff
#define MAXIMUM_WAIT_OBJECTS 64
typedef ::i32 errno_t;
#define INVALID_HSYNC_VALUE ((HSYNC)nullptr)


#define PM_NOREMOVE 0
#define PM_REMOVE 1


class sync;

using HSYNC = sync *;


#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((::u16)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))

#define RGB(r,g,b)          ((color32_t)(((byte)(r)|((::u16)((byte)(g))<<8))|(((::u32)(byte)(b))<<16)))



#endif // !defined(WINDOWS)


#pragma pack(pop, cross_windows)


struct SIZEPARENTPARAMS
{

   RECT32  rect;       // parent client rectangle (trim as appropriate)
   SIZE32  sizeTotal;  // total size on each side as on_layout proceeds
   bool  bStretch;   // should stretch to fill all space

};


typedef struct RECTD RECTD;



