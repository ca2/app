#pragma once


#pragma pack(push, cross_windows, 1)







#include "acme/graphics/draw2d/color32.h"


#pragma pack(pop, cross_windows)



using dummy_pointer = void *;


#define U32_LO_I16(u) ((::i16)((((::uptr)(u))) & 0xffff))
#define U32_HI_I16(u) ((::i16)((((::uptr)(u)) >> 16) & 0xffff))
//
////#ifdef WINDOWS
//
//
//using HSYNC = iptr;
//
//
//#define INVALID_HSYNC_VALUE INVALID_HANDLE_VALUE
//#define U32_INFINITE_TIMEOUT INFINITE
//
//
//using POINT_I32 = POINT;
//
//using LPPOINT32 = LPPOINT;
//
//using SIZE_I32 = SIZE;
//
//using LPSIZE32 = LPSIZE;
//
//using RECTANGLE_I32 = RECT;
//
//using RECTANGLE_I32 * = LPRECT;
//
//using const RECTANGLE_I32 * = LPCRECT;
//
//
//
////#else
//


/*
* set_window_position Flags
*/
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send e_message_non_client_calcsize */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send e_message_window_position_changing */

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER

//#if(WINVER >= 0x0400)
#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000
//#endif /* WINVER >= 0x0400 */


#define WS_OVERLAPPEDWINDOW 0x00CF0000



/*
 * Key State Masks for Mouse Messages
 */
#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010
//#if(_WIN32_WINNT >= 0x0500)
#define MK_XBUTTON1         0x0020
#define MK_XBUTTON2         0x0040
//#endif /* _WIN32_WINNT >= 0x0500 */


#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)


#define WS_EX_LAYERED           0x00080000


#define HWND_TOP        ((::oswindow)(::iptr)0)
#define HWND_BOTTOM     ((::oswindow)(::iptr)1)
#define HWND_TOPMOST    ((::oswindow)(::iptr)-1)
#define HWND_NOTOPMOST  ((::oswindow)(::iptr)-2)


#define MAKEWORD(a, b)      ((::u16)(((byte)(((dword_ptr)(a)) & 0xff)) | ((::u16)((byte)(((dword_ptr)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((::i32)(((::u16)(((dword_ptr)(a)) & 0xffff)) | ((::u32)((::u16)(((dword_ptr)(b)) & 0xffff))) << 16))
//#define LOWORD(l)           ((::u16)(((dword_ptr)(l)) & 0xffff))
//#define HIWORD(l)           ((::u16)((((dword_ptr)(l)) >> 16) & 0xffff))
#define __LOBYTE(w)           ((byte)(((dword_ptr)(w)) & 0xff))
#define HIBYTE(w)           ((byte)((((dword_ptr)(w)) >> 8) & 0xff))

#define MAKEWPARAM(l, h)      ((WPARAM)(::u32)MAKELONG(l, h))
#define MAKELPARAM(l, h)      ((LPARAM)(::u32)MAKELONG(l, h))
#define MAKELRESULT(l, h)     ((LRESULT)(::u32)MAKELONG(l, h))


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
//
//
//typedef struct tagCREATESTRUCTA
//{
//   void *         lpCreateParams;
//   void *         hInstance;
//   void *         hMenu;
//   oswindow       hwndParent;
//   i32            cy;
//   i32            cx;
//   i32            y;
//   i32            x;
//   ::i32          style;
//   const char *   lpszName;
//   const char *   lpszClass;
//   ::u32          dwExStyle;
//} CREATESTRUCTA,*LPCREATESTRUCTA;

#define CREATESTRUCT CREATESTRUCTA

#define WAIT_TIMEOUT                     258L    // dderror


#ifdef cplusplus

class event;

#endif

//struct oswindow_data;

//typedef struct oswindow_data * oswindow;



typedef char TCHAR, *PTCHAR;
typedef unsigned char TBYTE, *PTBYTE ;
typedef void * LPSECURITY_ATTRIBUTES;
#define _MAX_PATH 260
#define MAX_PATH _MAX_PATH
#define __UNREFERENCED_PARAMETER(u)	(void)(u)
//#define U32_INFINITE_TIMEOUT 0xffffffff
typedef ::i32 errno_t;







#define GetRValue(rgb)      (__LOBYTE(rgb))
#define GetGValue(rgb)      (__LOBYTE(((::u16)(rgb)) >> 8))
#define GetBValue(rgb)      (__LOBYTE((rgb)>>16))

#define rgb(r,g,b)          ((::color::color)(((byte)(r)|((::u16)((byte)(g))<<8))|(((::u32)(byte)(b))<<16)))



//#endif // !defined(WINDOWS)

//
//#ifdef WINDOWS_DESKTOP
//
//using MESSAGE = MSG;
//
//using MESSAGE = MSG;
//
//using PMESSAGE = MESSAGE *;
//
//using MESSAGE * = MESSAGE *;
//
//typedef const MESSAGE * LPCMESSAGE;
//
//#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
//
//
//#else


//#define MESSAGE_WINDOW_PARENT (::oswindow((void *) (iptr) 1))

#ifndef _UWP

/* Types use for passing & returning polymorphic values */
typedef uptr            WPARAM;
typedef iptr            LPARAM;
typedef iptr            LRESULT;


#endif

//
//typedef struct _tagMESSAGE
//{
//
//   oswindow        hwnd;
//   ::u32           message;
//   WPARAM          wParam;
//   LPARAM          lParam;
//   ::u32           time;
//   POINT_I32         pt;
//
//} MESSAGE, * PMESSAGE, * MESSAGE *;

//typedef const MESSAGE * LPCMESSAGE;


//
//#endif // if !defined(WINDOWS_DESKTOP)
//



typedef struct RECTANGLE_F64 RECTANGLE_F64;



