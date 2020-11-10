#pragma once

// Contains a 64-bit value representing the number
// of 100-nanosecond intervals since January 1, 1601 (UTC).
using filetime_t = ::u64;
#pragma pack(push, cross, 1)
using color32_t = ::u32;

using dummy_pointer = void *;

#pragma pop(cross)

#ifdef WINDOWS

#define U32_INFINITE_TIMEOUT INFINITE

#define SIZE32 SIZE
#define POINT32 POINT32
#define RECT32 RECT32

#else
#define TCHAR char
#define LPSECURITY_ATTRIBUTES dummy_pointer
#define _MAX_PATH 260
#define UNREFERENCED_PARAMETER(u)	(void)(u)
#define U32_INFINITE_TIMEOUT 0xffffffff
#define MAXIMUM_WAIT_OBJECTS 64
using errno_t = ::i32;

struct SIZE32
{

   ::i32 cx;
   ::i32 cy;

};


struct POINT32
{

   ::i32 x;
   ::i32 y;

};


struct RECT32
{

   ::i32 left;
   ::i32 top;
   ::i32 right;
   ::i32 bottom;

};


#endif



//#ifndef WINDOWS
//
//#ifdef cplusplus
//
//class event;
//
//#endif
//
//struct oswindow_data;
//
//typedef struct oswindow_data * oswindow;
//
//#endif
//
//
//
///*
// * Defines for the fVirt field of the Accelerator table structure.
// */
//#define WIN_FVIRTKEY  TRUE          /* Assumed to be == TRUE */
//#define WIN_FNOINVERT 0x02
//#define WIN_FSHIFT    0x04
//#define WIN_FCONTROL  0x08
//#define WIN_FALT      0x10
//
//
//
//
//#ifndef WINDOWS_DESKTOP
//
//#ifdef LINUX
//#undef inline
//#endif
//
//#include "windows/_.h"
//
//#endif
//
//
//#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(SOLARIOS)
//
////#include "ansios/ansios_file_raw.h"
//
//#else
//
////#include "ansios/ansios.h"
//
//#endif
//
//
//


using LPCRECT32 = const RECT32 *;
using LPRECT32 = RECT32 *;