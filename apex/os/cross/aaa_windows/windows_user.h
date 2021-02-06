#pragma once














//#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CLASS_DECL_APEX int_bool destroy_window(oswindow window);

CLASS_DECL_APEX int_bool GetCursorPos(POINT32 * lppointCursor);

//CLASS_DECL_APEX int_bool PostMessage(oswindow oswindow, ::u32 Msg, WPARAM wParam, LPARAM lParam);

#define MESSAGE_WINDOW_PARENT (::oswindow((void *) (iptr) 1))


#ifndef _UWP





int_bool is_window(oswindow oswindow);
int_bool IsChild(oswindow oswindowParent, oswindow oswindowcandidateChildOrDescendant);
// oswindow get_parent(oswindow oswindow);
// oswindow SetParent(oswindow oswindowChild, oswindow oswindowNewParent);
int_bool show_window(oswindow oswindow, const ::e_display & edisplay);
::i32 GetWindowLongA(oswindow oswindow, int nIndex);
::i32 SetWindowLongA(oswindow oswindow, int nIndex, ::i32 l);
int_bool _001ClientToScreen(oswindow oswindow, POINT32 * lppoint);
int_bool _001ScreenToClient(oswindow oswindow, POINT32 * lppoint);
int_bool IsIconic(oswindow oswindow);
int_bool IsWindowVisible(oswindow oswindow);
#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA



CLASS_DECL_APEX int_bool is_window(oswindow oswindow);


//CLASS_DECL_APEX int_bool GetCursorPos(POINT32 * lppointCursor);

#ifndef HWND_MESSAGE

#define HWND_MESSAGE     ((oswindow)-3)

#endif





typedef VOID(CALLBACK* TIMERPROC)(oswindow,::u32,uptr,::u32);
typedef int_bool(CALLBACK* GRAYSTRINGPROC)(HDC,LPARAM,i32);
typedef int_bool(CALLBACK* WNDENUMPROC)(oswindow,LPARAM);
typedef LRESULT(CALLBACK* HOOKPROC)(i32 code,WPARAM wParam,LPARAM lParam);
typedef VOID(CALLBACK* SENDASYNCPROC)(oswindow,::u32,ulong_ptr,LRESULT);

typedef int_bool(CALLBACK* PROPENUMPROca)(oswindow,const char *,HANDLE);
typedef int_bool(CALLBACK* PROPENUMPROCW)(oswindow,const widechar *,HANDLE);

typedef int_bool(CALLBACK* PROPENUMPROCEXA)(oswindow,char *,HANDLE,ulong_ptr);
typedef int_bool(CALLBACK* PROPENUMPROCEXW)(oswindow,LPWSTR,HANDLE,ulong_ptr);

typedef i32(CALLBACK* EDITWORDBREAKPROca)(char * lpch,i32 ichCurrent,i32 cch,i32 code);
typedef i32(CALLBACK* EDITWORDBREAKPROCW)(LPWSTR lpch,i32 ichCurrent,i32 cch,i32 code);


#endif


#ifndef NOWINOFFSETS

/*
* Window field offsets for GetWindowLong()
*/
#define GWL_WNDPROC         (-4)
#define GWL_HINSTANCE       (-6)
#define GWL_HWNDPARENT      (-8)
#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)
#define GWL_USERDATA        (-21)
#define GWL_ID              (-12)

#ifdef OS64BIT

#undef GWL_WNDPROC
#undef GWL_HINSTANCE
#undef GWL_HWNDPARENT
#undef GWL_USERDATA

#endif /* OS64BIT */

#define GWLP_WNDPROC        (-4)
#define GWLP_HINSTANCE      (-6)
#define GWLP_HWNDPARENT     (-8)
#define GWLP_USERDATA       (-21)
#define GWLP_ID             (-12)

/*
* Class field offsets for GetClassLong()
*/
#define GCL_MENUNAME        (-8)
#define GCL_HBRBACKGROUND   (-10)
#define GCL_HCURSOR         (-12)
#define GCL_HICON           (-14)
#define GCL_HMODULE         (-16)
#define GCL_CBWNDEXTRA      (-18)
#define GCL_CBCLSEXTRA      (-20)
#define GCL_WNDPROC         (-24)
#define GCL_STYLE           (-26)
#define GCW_ATOM            (-32)

#if(WINVER >= 0x0400)
#define GCL_HICONSM         (-34)
#endif /* WINVER >= 0x0400 */

#ifdef OS64BIT

#undef GCL_MENUNAME
#undef GCL_HBRBACKGROUND
#undef GCL_HCURSOR
#undef GCL_HICON
#undef GCL_HMODULE
#undef GCL_WNDPROC
#undef GCL_HICONSM

#endif /* OS64BIT */

#define GCLP_MENUNAME       (-8)
#define GCLP_HBRBACKGROUND  (-10)
#define GCLP_HCURSOR        (-12)
#define GCLP_HICON          (-14)
#define GCLP_HMODULE        (-16)
#define GCLP_WNDPROC        (-24)
#define GCLP_HICONSM        (-34)

#endif /* !NOWINOFFSETS */




#if(_WIN32_WINNT >= 0x0400)
/* Value for rolling one detent */
#define WHEEL_DELTA                     120
#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))

/* Setting to scroll one page for SPI_GET/SETWHEELSCROLLLINES */
#define WHEEL_PAGESCROLL                (UINT_MAX)
#endif /* _WIN32_WINNT >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define GET_KEYSTATE_WPARAM(wParam)     (LOWORD(wParam))
#define GET_NCHITTEST_WPARAM(wParam)    ((short)LOWORD(wParam))
#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))

/* XButton values are ::u16 flags */
#define XBUTTON1      0x0001
#define XBUTTON2      0x0002
/* Were there to be an XBUTTON3, its value would be 0x0004 */
#endif /* _WIN32_WINNT >= 0x0500 */

#define WM_PARENTNOTIFY                 0x0210
#define WM_ENTERMENULOOP                0x0211
#define WM_EXITMENULOOP                 0x0212

#if(WINVER >= 0x0400)
#define WM_NEXTMENU                     0x0213
#define WM_SIZING                       0x0214
#define WM_CAPTURECHANGED               0x0215
#define WM_MOVING                       0x0216
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)


#define WM_POWERBROADCAST               0x0218

#ifndef _WIN32_WCE
#define PBT_APMQUERYSUSPEND             0x0000
#define PBT_APMQUERYSTANDBY             0x0001

#define PBT_APMQUERYSUSPENDFAILED       0x0002
#define PBT_APMQUERYSTANDBYFAILED       0x0003

#define PBT_APMSUSPEND                  0x0004
#define PBT_APMSTANDBY                  0x0005

#define PBT_APMRESUMECRITICAL           0x0006
#define PBT_APMRESUMESUSPEND            0x0007
#define PBT_APMRESUMESTANDBY            0x0008

#define PBTF_APMRESUMEFROMFAILURE       0x00000001

#define PBT_APMBATTERYLOW               0x0009
#define PBT_APMPOWERSTATUSCHANGE        0x000A

#define PBT_APMOEMEVENT                 0x000B


#define PBT_APMRESUMEAUTOMATIC          0x0012
#if (_WIN32_WINNT >= 0x0502)
#ifndef PBT_POWERSETTINGCHANGE
#define PBT_POWERSETTINGCHANGE          0x8013
typedef struct
{
   GUID PowerSetting;
   ::u32 DataLength;
   WINUCHAR Data[1];
} POWERBROADcaST_SETTING,*PPOWERBROADcaST_SETTING;


#endif // PBT_POWERSETTINGCHANGE

#endif // (_WIN32_WINNT >= 0x0502)
#endif

#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0400)
#define WM_DEVICECHANGE                 0x0219
#endif /* WINVER >= 0x0400 */

#define WM_MDICREATE                    0x0220
#define WM_MDIDESTROY                   0x0221
#define WM_MDIACTIVATE                  0x0222
#define WM_MDIRESTORE                   0x0223
#define WM_MDINEXT                      0x0224
#define WM_MDIMAXIMIZE                  0x0225
#define WM_MDITILE                      0x0226
#define WM_MDIcaScaDE                   0x0227
#define WM_MDIICONARRANGE               0x0228
#define WM_MDIGETACTIVE                 0x0229


#define WM_MDISETMENU                   0x0230
#define WM_ENTERSIZEMOVE                0x0231
#define WM_EXITSIZEMOVE                 0x0232
#define WM_DROPFILES                    0x0233
#define WM_MDIREFRESHMENU               0x0234

#if(WINVER >= 0x0601)
#define WM_TOUCH                        0x0240
#endif /* WINVER >= 0x0601 */


#if(WINVER >= 0x0400)
#define WM_IME_SETCONTEXT               0x0281
#define WM_IME_NOTIFY                   0x0282
#define WM_IME_CONTROL                  0x0283
#define WM_IME_COMPOSITIONFULL          0x0284
#define WM_IME_SELECT                   0x0285
#define WM_IME_CHAR                     0x0286
#endif /* WINVER >= 0x0400 */
#if(WINVER >= 0x0500)
#define WM_IME_REQUEST                  0x0288
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0400)
#define WM_IME_KEYDOWN                  0x0290
#define WM_IME_KEYUP                    0x0291
#endif /* WINVER >= 0x0400 */

#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
#define WM_MOUSEHOVER                   0x02A1
#define e_message_mouse_leave                   0x02A3
#endif
#if(WINVER >= 0x0500)
#define WM_NCMOUSEHOVER                 0x02A0
#define WM_NCMOUSELEAVE                 0x02A2
#endif /* WINVER >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_WTSSESSION_CHANGE            0x02B1

#define WM_TABLET_FIRST                 0x02c0
#define WM_TABLET_LAST                  0x02df
#endif /* _WIN32_WINNT >= 0x0501 */

#define WM_CUT                          0x0300
#define WM_COPY                         0x0301
#define WM_PASTE                        0x0302
#define WM_CLEAR                        0x0303
#define WM_UNDO                         0x0304
#define WM_RENDERFORMAT                 0x0305
#define WM_RENDERALLFORMATS             0x0306
#define WM_DESTROYCLIPBOARD             0x0307
#define WM_DRAWCLIPBOARD                0x0308
#define e_message_paintCLIPBOARD               0x0309
#define e_message_vscrollCLIPBOARD             0x030A
#define WM_SIZECLIPBOARD                0x030B
#define WM_ASKCBFORMATNAME              0x030C
#define WM_CHANGECBCHAIN                0x030D
#define e_message_hscrollCLIPBOARD             0x030E
#define WM_QUERYNEWPALETTE              0x030F
#define WM_PALETTEISCHANGING            0x0310
#define WM_PALETTECHANGED               0x0311
#define WM_HOTKEY                       0x0312

#if(WINVER >= 0x0400)
#define WM_PRINT                        0x0317
#define WM_PRINTCLIENT                  0x0318
#endif /* WINVER >= 0x0400 */

#if(_WIN32_WINNT >= 0x0500)
#define WM_APPCOMMAND                   0x0319
#endif /* _WIN32_WINNT >= 0x0500 */

#if(_WIN32_WINNT >= 0x0501)
#define WM_THEMECHANGED                 0x031A
#endif /* _WIN32_WINNT >= 0x0501 */


#if(_WIN32_WINNT >= 0x0501)
#define WM_CLIPBOARDUPDATE              0x031D
#endif /* _WIN32_WINNT >= 0x0501 */

#if(_WIN32_WINNT >= 0x0600)
#define WM_DWMCOMPOSITIONCHANGED        0x031E
#define WM_DWMNCRENDERINGCHANGED        0x031F
#define WM_DWMCOLORIZATIONCOLORCHANGED  0x0320
#define WM_DWMWINDOWMAXIMIZEDCHANGE     0x0321
#endif /* _WIN32_WINNT >= 0x0600 */

#if(_WIN32_WINNT >= 0x0601)
#define WM_DWMSENDICONICTHUMBNAIL           0x0323
#define WM_DWMSENDICONICLIVEPREVIEWBITMAP   0x0326
#endif /* _WIN32_WINNT >= 0x0601 */


#if(WINVER >= 0x0600)
#define WM_GETTITLEBARINFOEX            0x033F
#endif /* WINVER >= 0x0600 */

#if(WINVER >= 0x0400)

#define WM_HANDHELDFIRST                0x0358
#define WM_HANDHELDLAST                 0x035F

#define WM_AFXFIRST                     0x0360
#define WM_AFXLAST                      0x037F
#endif /* WINVER >= 0x0400 */

#define WM_PENWINFIRST                  0x0380
#define WM_PENWINLAST                   0x038F


#if(WINVER >= 0x0400)
#define WM_APP                          0x8000
#endif /* WINVER >= 0x0400 */


/*
* NOTE: All Message Numbers below 0x0400 are RESERVED.
*
* Private Window Messages Start Here:
*/
#define WM_USER                         0x0400

#if(WINVER >= 0x0400)

/*  wParam for WM_SIZING message  */
#define WMSZ_LEFT           1
#define WMSZ_RIGHT          2
#define WMSZ_TOP            3
#define WMSZ_TOPLEFT        4
#define WMSZ_TOPRIGHT       5
#define WMSZ_BOTTOM         6
#define WMSZ_BOTTOMLEFT     7
#define WMSZ_BOTTOMRIGHT    8
#endif /* WINVER >= 0x0400 */

#ifndef NONCMESSAGES

/*
* e_message_nchittest and MOUSEHOOKSTRUCT Mouse Position Codes
*/
#define HTERROR             (-2)
#define HTTRANSPARENT       (-1)
#define HTNOWHERE           0
#define HTCLIENT            1
#define HTcaPTION           2
#define HTSYSMENU           3
#define HTGROWBOX           4
#define HTSIZE              HTGROWBOX
#define HTMENU              5
#define HTHSCROLL           6
#define HTVSCROLL           7
#define HTMINBUTTON         8
#define HTMAXBUTTON         9
#define HTLEFT              10
#define HTRIGHT             11
#define HTTOP               12
#define HTTOPLEFT           13
#define HTTOPRIGHT          14
#define HTBOTTOM            15
#define HTBOTTOMLEFT        16
#define HTBOTTOMRIGHT       17
#define HTBORDER            18
#define HTREDUCE            HTMINBUTTON
#define HTZOOM              HTMAXBUTTON
#define HTSIZEFIRST         HTLEFT
#define HTSIZELAST          HTBOTTOMRIGHT
#if(WINVER >= 0x0400)
#define HTOBJECT            19
#define HTCLOSE             20
#define HTHELP              21
#endif /* WINVER >= 0x0400 */


/*
* SendMessageTimeout values
*/
#define SMTO_NORMAL         0x0000
#define SMTO_BLOCK          0x0001
#define SMTO_ABORTIFHUNG    0x0002
#if(WINVER >= 0x0500)
#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
#endif /* WINVER >= 0x0500 */
#if(WINVER >= 0x0600)
#define SMTO_ERRORONEXIT    0x0020
#endif /* WINVER >= 0x0600 */

#endif /* !NONCMESSAGES */

/*
* e_message_mouse_activate Return Codes
*/
#define MA_ACTIVATE         1
#define MA_ACTIVATEANDEAT   2
#define MA_NOACTIVATE       3
#define MA_NOACTIVATEANDEAT 4

/*
* WM_SETICON / WM_GETICON Type Codes
*/
#define ICON_SMALL          0
#define ICON_BIG            1
#if(_WIN32_WINNT >= 0x0501)
#define ICON_SMALL2         2
#endif /* _WIN32_WINNT >= 0x0501 */


/*

::u32
WINAPI
RegisterWindowMessageA(
const char * lpString);

::u32
WINAPI
RegisterWindowMessageW(
const widechar * lpString);
#ifdef UNICODE
#define RegisterWindowMessage  RegisterWindowMessageW
#else
#define RegisterWindowMessage  RegisterWindowMessageA
#endif // !UNICODE
*/


/*
* set_window_pos Flags
*/
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send e_message_nccalcsize */
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




/*
* Window Styles
*/
#define WS_OVERLAPPED       0x00000000L
#define WS_POPUP            0x80000000L
#define WS_CHILD            0x40000000L
#define WS_MINIMIZE         0x20000000L
#define WS_VISIBLE          0x10000000L
#define WS_DISABLED         0x08000000L
#define WS_CLIPSIBLINGS     0x04000000L
#define WS_CLIPCHILDREN     0x02000000L
#define WS_MAXIMIZE         0x01000000L
#define WS_caPTION          0x00C00000L     /* WS_BORDER | WS_DLGFRAME  */
#define WS_BORDER           0x00800000L
#define WS_DLGFRAME         0x00400000L
#define WS_VSCROLL          0x00200000L
#define WS_HSCROLL          0x00100000L
#define WS_SYSMENU          0x00080000L
#define WS_THICKFRAME       0x00040000L
#define WS_GROUP            0x00020000L
#define WS_TABSTOP          0x00010000L

#define WS_MINIMIZEBOX      0x00020000L
#define WS_MAXIMIZEBOX      0x00010000L


#define WS_TILED            WS_OVERLAPPED
#define WS_ICONIC           WS_MINIMIZE
#define WS_SIZEBOX          WS_THICKFRAME
#define WS_TILEDWINDOW      WS_OVERLAPPEDWINDOW

#ifndef _UWP
/*
* Common Window Styles
*/
#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED     | \
   WS_caPTION | \
   WS_SYSMENU | \
   WS_THICKFRAME | \
   WS_MINIMIZEBOX | \
   WS_MAXIMIZEBOX)

#define WS_POPUPWINDOW      (WS_POPUP          | \
   WS_BORDER | \
   WS_SYSMENU)
#endif

#define WS_CHILDWINDOW      (WS_CHILD)

/*
* Extended Window Styles
*/
#define WS_EX_DLGMODALFRAME     0x00000001L
#define WS_EX_NOPARENTNOTIFY    0x00000004L
#define WS_EX_TOPMOST           0x00000008L
#define WS_EX_ACCEPTFILES       0x00000010L
#define WS_EX_TRANSPARENT       0x00000020L
//#if(WINVER >= 0x0400)
#define WS_EX_MDICHILD          0x00000040L
#define WS_EX_TOOLWINDOW        0x00000080L
#define WS_EX_WINDOWEDGE        0x00000100L
#define WS_EX_CLIENTEDGE        0x00000200L
#define WS_EX_CONTEXTHELP       0x00000400L

//#endif /* WINVER >= 0x0400 */
//#if(WINVER >= 0x0400)

#define WS_EX_RIGHT             0x00001000L
#define WS_EX_LEFT              0x00000000L
#define WS_EX_RTLREADING        0x00002000L
#define WS_EX_LTRREADING        0x00000000L
#define WS_EX_LEFTSCROLLBAR     0x00004000L
#define WS_EX_RIGHTSCROLLBAR    0x00000000L

#define WS_EX_CONTROLPARENT     0x00010000L
#define WS_EX_STATICEDGE        0x00020000L
#define WS_EX_APPWINDOW         0x00040000L


#define WS_EX_OVERLAPPEDWINDOW  (WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE)
#define WS_EX_PALETTEWINDOW     (WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST)

//#endif /* WINVER >= 0x0400 */

#define WS_EX_LAYERED           0x00080000

//#if(WINVER >= 0x0500)
#define WS_EX_NOINHERITLAYOUT   0x00100000L // Disable inheritence of mirroring by children
#define WS_EX_LAYOUTRTL         0x00400000L // Right to left mirroring
//#endif /* WINVER >= 0x0500 */

//#if(_WIN32_WINNT >= 0x0501)
#define WS_EX_COMPOSITED        0x02000000L
//#endif /* _WIN32_WINNT >= 0x0501 */
//#if(_WIN32_WINNT >= 0x0500)
#define WS_EX_NOACTIVATE        0x08000000L
//#endif /* _WIN32_WINNT >= 0x0500 */


/*int_bool
WINAPI
EnableWindow(
oswindow hWnd,
int_bool bEnable);

int_bool
WINAPI
IsWindowEnabled(
oswindow hWnd);
*/











//#if(WINVER >= 0x0400)
#define DT_EDITCONTROL              0x00002000
#define DT_PATH_ELLIPSIS            0x00004000
#define DT_END_ELLIPSIS             0x00008000
#define DT_MODIFYSTRING             0x00010000
#define DT_RTLREADING               0x00020000
#define DT_WORD_ELLIPSIS            0x00040000
//#if(WINVER >= 0x0500)
#define DT_NOFULLWIDTHCHARBREAK     0x00080000
//#if(_WIN32_WINNT >= 0x0500)
#define DT_HIDEPREFIX               0x00100000
#define DT_PREFIXONLY               0x00200000
//#endif /* _WIN32_WINNT >= 0x0500 */
//#endif /* WINVER >= 0x0500 */



//
//#ifndef _UWP
//
//typedef struct tagDRAWTEXTPARAMS
//{
//   ::u32    cbSize;
//   i32     iTabLength;
//   i32     iLeftMargin;
//   i32     iRightMargin;
//   ::u32    uiLengthDrawn;
//} DRAWTEXTPARAMS,*LPDRAWTEXTPARAMS;
//
//#endif
//
//
//
//
//
//
//
///*
//oswindow
//WINAPI
//get_desktop_window(
//VOID);
//*/
//
//
//oswindow
//WINAPI
//get_parent(
//oswindow hWnd);
//
//
//oswindow
//WINAPI
//SetParent(
//oswindow hWndChild,
//oswindow hWndNewParent);
//
////#ifndef
////
////int_bool
////WINAPI
////EnumChildWindows(
////oswindow hWndParent,
////WNDENUMPROC lpEnumFunc,
////LPARAM lParam);
//
//
///*oswindow
//WINAPI
//FindWindowA(
//const char * lpClassName,
//const char * lpWindowName);
//
//oswindow
//WINAPI
//FindWindowW(
//const widechar * lpClassName,
//const widechar * lpWindowName);*/
//#ifdef UNICODE
//#define FindWindow  FindWindowW
//#else
//#define FindWindow  FindWindowA
//#endif // !UNICODE
//
//
//
///*
//* e_message_size message wParam values
//*/
//#define SIZE_RESTORED       0
//#define SIZE_MINIMIZED      1
//#define SIZE_MAXIMIZED      2
//#define SIZE_MAXSHOW        3
//#define SIZE_MAXHIDE        4
//
///*
//* Obsolete constant names
//*/
//#define SIZENORMAL          SIZE_RESTORED
//#define SIZEICONIC          SIZE_MINIMIZED
//#define SIZEFULLSCREEN      SIZE_MAXIMIZED
//#define SIZEZOOMSHOW        SIZE_MAXSHOW
//#define SIZEZOOMHIDE        SIZE_MAXHIDE
//
//
///*
//* e_message_nccalcsize "window valid rect" return values
//*/
//#define WVR_ALIGNTOP        0x0010
//#define WVR_ALIGNLEFT       0x0020
//#define WVR_ALIGNBOTTOM     0x0040
//#define WVR_ALIGNRIGHT      0x0080
//#define WVR_HREDRAW         0x0100
//#define WVR_VREDRAW         0x0200
//#define WVR_REDRAW         (WVR_HREDRAW | \
//   WVR_VREDRAW)
//#define WVR_VALIDRECTS      0x0400
//
//
///*
//* ShowWindow() Commands
//*/
//#define SW_HIDE             0
//#define SW_SHOWNORMAL       1
//#define SW_NORMAL           1
//#define SW_SHOWMINIMIZED    2
//#define SW_SHOWMAXIMIZED    3
//#define SW_MAXIMIZE         3
//#define SW_SHOWNOACTIVATE   4
//#define SW_SHOW             5
//#define SW_MINIMIZE         6
//#define SW_SHOWMINNOACTIVE  7
//#define SW_SHOWNA           8
//#define SW_RESTORE          9
//#define SW_SHOWDEFAULT      10
//#define SW_FORCEMINIMIZE    11
//#define SW_MAX              11
//
//
///*
//* Old ShowWindow() Commands
//*/
//#define HIDE_WINDOW         0
//#define SHOW_OPENWINDOW     1
//#define SHOW_ICONWINDOW     2
//#define SHOW_FULLSCREEN     3
//#define SHOW_OPENNOACTIVATE 4
//
///*
//* Identifiers for the e_message_show_window message
//*/
//#define SW_PARENTCLOSING    1
//#define SW_OTHERZOOM        2
//#define SW_PARENTOPENING    3
//
//
//
//
//
//
//
//
//
//
////oswindow
////WINAPI
////GetLastActivePopup(
////    oswindow hWnd);
//
///*
//* GetWindow() Constants
//*/
//#define GW_HWNDFIRST        0
//#define GW_HWNDLAST         1
//#define GW_HWNDNEXT         2
//#define GW_HWNDPREV         3
//#define GW_OWNER            4
//#define GW_CHILD            5
//#if(WINVER <= 0x0400)
//#define GW_MAX              5
//#else
//#define GW_ENABLEDPOPUP     6
//#define GW_MAX              6
//#endif
//
///*
//oswindow
//WINAPI
//GetWindow(
//oswindow hWnd,
//::u32 uCmd);
//*/
//
//
//
///*
//* MessageBox() Flags
//*/
//#define e_message_box_ok                       0x00000000L
//#define MB_OKCANCEL                 0x00000001L
//#define MB_ABORTRETRYIGNORE         0x00000002L
//#define MB_YESNOCANCEL              0x00000003L
//#define MB_YESNO                    0x00000004L
//#define MB_RETRYCANCEL              0x00000005L
////#if(WINVER >= 0x0500)
//#define MB_CANCELTRYCONTINUE        0x00000006L
////#endif /* WINVER >= 0x0500 */
//
//
//#define MB_ICONHAND                 0x00000010L
//#define MB_ICONQUESTION             0x00000020L
//#define e_message_box_icon_exclamation          0x00000030L
//#define MB_ICONASTERISK             0x00000040L
//
////#if(WINVER >= 0x0400)
//#define MB_USERICON                 0x00000080L
//#define e_message_box_icon_warning              e_message_box_icon_exclamation
//#define MB_ICONERROR                MB_ICONHAND
////#endif /* WINVER >= 0x0400 */
//
//#define e_message_box_icon_information          MB_ICONASTERISK
//#define e_message_box_icon_stop                 MB_ICONHAND
//
//#define MB_DEFBUTTON1               0x00000000L
//#define MB_DEFBUTTON2               0x00000100L
//#define MB_DEFBUTTON3               0x00000200L
////#if(WINVER >= 0x0400)
//#define MB_DEFBUTTON4               0x00000300L
////#endif /* WINVER >= 0x0400 */
//
//#define MB_APPLMODAL                0x00000000L
//#define e_message_box_system_modal              0x00001000L
//#define MB_TASKMODAL                0x00002000L
//#if(WINVER >= 0x0400)
//#define MB_HELP                     0x00004000L // Help Button
//#endif /* WINVER >= 0x0400 */
//
//#define MB_NOFOCUS                  0x00008000L
//#define MB_SETFOREGROUND            0x00010000L
//#define MB_DEFAULT_DESKTOP_ONLY     0x00020000L
//
//#if(WINVER >= 0x0400)
//#define MB_TOPMOST                  0x00040000L
//#define MB_RIGHT                    0x00080000L
//#define MB_RTLREADING               0x00100000L
//
//#endif /* WINVER >= 0x0400 */
//
//#ifdef _WIN32_WINNT
//#if (_WIN32_WINNT >= 0x0400)
//#define MB_SERVICE_NOTIFIcaTION          0x00200000L
//#else
//#define MB_SERVICE_NOTIFIcaTION          0x00040000L
//#endif
//#define MB_SERVICE_NOTIFIcaTION_NT3X     0x00040000L
//#endif
//
//#define MB_TYPEMASK                 0x0000000FL
//#define MB_ICONMASK                 0x000000F0L
//#define MB_DEFMASK                  0x00000F00L
//#define MB_MODEMASK                 0x00003000L
//#define MB_MISCMASK                 0x0000C000L
//
//
//
//
//
///*
//* Color Types
//*/
//#define CTLCOLOR_MSGBOX         0
//#define CTLCOLOR_EDIT           1
//#define CTLCOLOR_LISTBOX        2
//#define CTLCOLOR_BTN            3
//#define CTLCOLOR_DLG            4
//#define CTLCOLOR_SCROLLBAR      5
//#define CTLCOLOR_STATIC         6
//#define CTLCOLOR_MAX            7
//
//#define COLOR_SCROLLBAR         0
//#define COLOR_BACKGROUND        1
//#define COLOR_ACTIVEcaPTION     2
//#define COLOR_INACTIVEcaPTION   3
//#define COLOR_MENU              4
//#define COLOR_WINDOW            5
//#define COLOR_WINDOWFRAME       6
//#define COLOR_MENUTEXT          7
//#define COLOR_WINDOWTEXT        8
//#define COLOR_caPTIONTEXT       9
//#define COLOR_ACTIVEBORDER      10
//#define COLOR_INACTIVEBORDER    11
//#define COLOR_APPWORKSPACE      12
//#define COLOR_HIGHLIGHT         13
//#define COLOR_HIGHLIGHTTEXT     14
//#define COLOR_BTNFACE           15
//#define COLOR_BTNSHADOW         16
//#define COLOR_GRAYTEXT          17
//#define COLOR_BTNTEXT           18
//#define COLOR_INACTIVEcaPTIONTEXT 19
//#define COLOR_BTNHIGHLIGHT      20
//
//#if(WINVER >= 0x0400)
//#define COLOR_3DDKSHADOW        21
//#define COLOR_3DLIGHT           22
//#define COLOR_INFOTEXT          23
//#define COLOR_INFOBK            24
//#endif /* WINVER >= 0x0400 */
//
//#if(WINVER >= 0x0500)
//#define COLOR_HOTLIGHT          26
//#define COLOR_GRADIENTACTIVEcaPTION 27
//#define COLOR_GRADIENTINACTIVEcaPTION 28
//#if(WINVER >= 0x0501)
//#define COLOR_MENUHILIGHT       29
//#define COLOR_MENUBAR           30
//#endif /* WINVER >= 0x0501 */
//#endif /* WINVER >= 0x0500 */
//
//#if(WINVER >= 0x0400)
//#define COLOR_DESKTOP           COLOR_BACKGROUND
//#define COLOR_3DFACE            COLOR_BTNFACE
//#define COLOR_3DSHADOW          COLOR_BTNSHADOW
//#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
//#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
//#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT
//#endif /* WINVER >= 0x0400 */
//
//
//
//
//
//
///*
//* Dialog Box Command IDs
//*/
//#define e_dialog_result_ok                1
//#define e_dialog_result_cancel            2
//#define IDABORT             3
//#define IDRETRY             4
//#define IDIGNORE            5
//#define e_dialog_result_yes               6
//#define e_dialog_result_no                7
////#if(WINVER >= 0x0400)
//#define IDCLOSE         8
//#define IDHELP          9
////#endif /* WINVER >= 0x0400 */
//
////#if(WINVER >= 0x0500)
//#define IDTRYAGAIN      10
//#define IDCONTINUE      11
////#endif /* WINVER >= 0x0500 */
//
////#if(WINVER >= 0x0501)
//#ifndef IDTIMEOUT
//#define IDTIMEOUT 32000
//#endif
////#endif /* WINVER >= 0x0501 */
//
//#ifndef _UWP
//struct user_menu;
//
//typedef struct _hmenu
//{
//
//   struct user_menu * m_p;
//
//} * HMENU;
//
//
//
//struct visual_cursor;
//
//#ifdef LINUX
//typedef unsigned long HCURSOR;
//#define hcursor_null ((HCURSOR) 0)
//#else
//typedef void * HCURSOR;
//#define hcursor_null ((HCURSOR) nullptr)
//#endif
//
//typedef void * HDROP;
//
//
//
//typedef struct tagACCEL
//{
//#ifndef _MAC
//   byte   fVirt;               /* Also called the flags field */
//   ::u16   key;
//   ::u16   cmd;
//#else
//   ::u16   fVirt;               /* Also called the flags field */
//   ::u16   key;
//   ::u32  cmd;
//#endif
//} ACCEL,*LPACCEL;
//
//typedef LPACCEL HACCEL;
//
//typedef struct tagPAINTSTRUCT
//{
//   HDC         hdc;
//   int_bool        fErase;
//   RECT32        rcPaint;
//   int_bool        fRestore;
//   int_bool        fIncUpdate;
//   byte        rgbReserved[32];
//} PAINTSTRUCT,*PPAINTSTRUCT,*NPPAINTSTRUCT,*LPPAINTSTRUCT;
//
//
//typedef struct tagCREATESTRUCTA
//{
//   LPVOID      lpCreateParams;
//   HINSTANCE   hInstance;
//   HMENU       hMenu;
//   oswindow        hwndParent;
//   i32         cy;
//   i32         cx;
//   i32         y;
//   i32         x;
//   ::i32        style;
//   const char *      lpszName;
//   const char *      lpszClass;
//   ::u32       dwExStyle;
//} CREATESTRUCTA,*LPCREATESTRUCTA;
//typedef struct tagCREATESTRUCTW
//{
//   LPVOID      lpCreateParams;
//   HINSTANCE   hInstance;
//   HMENU       hMenu;
//   oswindow    hwndParent;
//   i32         cy;
//   i32         cx;
//   i32         y;
//   i32         x;
//   ::i32        style;
//   const widechar *     lpszName;
//   const widechar *     lpszClass;
//   ::u32       dwExStyle;
//} CREATESTRUCTW,*LPCREATESTRUCTW;
//#ifdef UNICODE
//typedef CREATESTRUCTW CREATESTRUCT;
//typedef LPCREATESTRUCTW LPCREATESTRUCT;
//#else
//typedef CREATESTRUCTA CREATESTRUCT;
//typedef LPCREATESTRUCTA LPCREATESTRUCT;
//#endif // UNICODE
//
//
//typedef struct tagWINDOWPLACEMENT
//{
//   ::u32  length;
//   ::u32  flags;
//   ::u32  showCmd;
//   POINT32 pointMinPosition;
//   POINT32 pointMaxPosition;
//   RECT32  rcNormalPosition;
//#ifdef _MAC
//   RECT32  rcDevice;
//#endif
//} WINDOWPLACEMENT;
//typedef WINDOWPLACEMENT *PWINDOWPLACEMENT,*LPWINDOWPLACEMENT;
//
//#define WPF_SETMINPOSITION          0x0001
//#define WPF_RESTORETOMAXIMIZED      0x0002
//#if(_WIN32_WINNT >= 0x0500)
//#define WPF_ASYNCWINDOWPLACEMENT    0x0004
//#endif /* _WIN32_WINNT >= 0x0500 */
//
//#endif
///*
//
//typedef struct tag_MSG
//{
//oswindow    hwnd;
//::u32        message;
//WPARAM      wParam;
//LPARAM      lParam;
//POINT32       pt;
//} MESSAGE, * LPMESSAGE;
//
//*/
//
//#ifndef _UWP
//
//HDC BeginPaint(oswindow hwnd,PAINTSTRUCT * ps);
//
//int_bool EndPaint(oswindow hwnd,PAINTSTRUCT * ps);
//
//#endif
//
//#ifndef _UWP
//#define HWND_TOP        ((::oswindow)(::iptr)0)
//#define HWND_BOTTOM     ((::oswindow)(::iptr)1)
//#define HWND_TOPMOST    ((::oswindow)(::iptr)-1)
//#define HWND_NOTOPMOST  ((::oswindow)(::iptr)-2)
//#endif
//
//
//int_bool WINAPI SetWindowPos(oswindow hWnd,oswindow hWndInsertAfter,i32 X,i32 Y,i32 cx,i32 cy,::u32 uFlags);
//
//int_bool WINAPI IsWindowVisible(oswindow hWnd);
//
//int_bool WINAPI IsIconic(oswindow hWnd);
//
////#ifndef _UWP
////
////#define e_zorder_top -1
////#define ZORDER_BOTTOM -2
////#define ZORDER_TOPMOST -3
////#define ZORDER_NOTOPMOST -4sss
////
////#endif
//
////int_bool RedrawWindow(oswindow hWnd, const RECT32 *lprcUpdate, HRGN hrgnUpdate, ::u32 flags);
//
//
///*
//* RedrawWindow() flags
//*/
//#define RDW_INVALIDATE          0x0001
//#define RDW_INTERNALPAINT       0x0002
//#define RDW_ERASE               0x0004
//
//#define RDW_VALIDATE            0x0008
//#define RDW_NOINTERNALPAINT     0x0010
//#define RDW_NOERASE             0x0020
//
//#define RDW_NOCHILDREN          0x0040
//#define RDW_ALLCHILDREN         0x0080
//
//#define RDW_UPDATENOW           0x0100
//#define RDW_ERASENOW            0x0200
//
//#define RDW_FRAME               0x0400
//#define RDW_NOFRAME             0x0800
//
//
//#define DI_MASK         0x0001
//#define DI_IMAGE        0x0002
//#define DI_NORMAL       0x0003
//#define DI_COMPAT       0x0004
//#define DI_DEFAULTSIZE  0x0008
//#if(_WIN32_WINNT >= 0x0501)
//#define DI_NOMIRROR     0x0010
//#endif /* _WIN32_WINNT >= 0x0501 */
//
//
//::i32
//WINAPI
//GetWindowLongA(
//oswindow hWnd,
//i32 nIndex);
//
//
//::i32
//WINAPI
//GetWindowLongW(
//oswindow hWnd,
//i32 nIndex);
//#ifdef UNICODE
//#define GetWindowLong  GetWindowLongW
//#else
//#define GetWindowLong  GetWindowLongA
//#endif // !UNICODE
//
//LONG_PTR
//WINAPI
//GetWindowLongPtrA(
//oswindow hWnd,
//i32 nIndex);
//
//
//LONG_PTR
//WINAPI
//GetWindowLongPtrW(
//oswindow hWnd,
//i32 nIndex);
//#ifdef UNICODE
//#define GetWindowLongPtr  GetWindowLongPtrW
//#else
//#define GetWindowLongPtr  GetWindowLongPtrA
//#endif // !UNICODE
//
//
//::i32
//WINAPI
//SetWindowLongA(
//oswindow hWnd,
//i32 nIndex,
//::i32 l);
//
//
//::i32
//WINAPI
//SetWindowLongW(
//oswindow hWnd,
//i32 nIndex,
//::i32 l);
//#ifdef UNICODE
//#define SetWindowLong  SetWindowLongW
//#else
//#define SetWindowLong  SetWindowLongA
//#endif // !UNICODE
//
//LONG_PTR
//WINAPI
//SetWindowLongPtrA(
//oswindow hWnd,
//i32 nIndex,
//LONG_PTR l);
//
//
//LONG_PTR
//WINAPI
//SetWindowLongPtrW(
//oswindow hWnd,
//i32 nIndex,
//LONG_PTR l);
//#ifdef UNICODE
//#define SetWindowLongPtr  SetWindowLongPtrW
//#else
//#define SetWindowLongPtr  SetWindowLongPtrA
//#endif // !UNICODE
//
//
//#ifndef _UWP
//typedef struct tagNMHDR
//{
//   oswindow      hwndFrom;
//   UINT_PTR  idFrom;
//   ::u32      code;         // NM_ code
//}   NMHDR;
//
//
//typedef NMHDR * LPNMHDR;
//
//
//typedef struct tagSTYLESTRUCT
//{
//   ::u32   styleOld;
//   ::u32   styleNew;
//} STYLESTRUCT,* LPSTYLESTRUCT;
//
//#endif
//
//
//
///*
// * Scroll Bar Constants
// */
//#define SB_HORZ             0
//#define SB_VERT             1
//#define SB_CTL              2
//#define SB_BOTH             3
//
///*
// * Scroll Bar Commands
// */
//#define SB_LINEUP           0
//#define SB_LINELEFT         0
//#define SB_LINEDOWN         1
//#define SB_LINERIGHT        1
//#define SB_PAGEUP           2
//#define SB_PAGELEFT         2
//#define SB_PAGEDOWN         3
//#define SB_PAGERIGHT        3
//#define SB_THUMBPOSITION    4
//#define SB_THUMBTRACK       5
//#define SB_TOP              6
//#define SB_LEFT             6
//#define SB_BOTTOM           7
//#define SB_RIGHT            7
//#define SB_ENDSCROLL        8
//
//
//
//
//
//
///*
// * Virtual Keys, Standard Set
// */
//#define VK_LBUTTON        0x01
//#define VK_RBUTTON        0x02
//#define VK_CANCEL         0x03
//#define VK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */
//
//#if(_WIN32_WINNT >= 0x0500)
//#define VK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
//#define VK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
//#endif /* _WIN32_WINNT >= 0x0500 */
//
///*
// * 0x07 : unassigned
// */
//
//#define VK_BACK           0x08
//#define VK_TAB            0x09
//
///*
// * 0x0A - 0x0B : reserved
// */
//
//#define VK_CLEAR          0x0C
//#define VK_RETURN         0x0D
//
//#define VK_SHIFT          0x10
//#define VK_CONTROL        0x11
//#define VK_MENU           0x12
//#define VK_PAUSE          0x13
//#define VK_CAPITAL        0x14
//
//#define VK_KANA           0x15
//#define VK_HANGEUL        0x15  /* old name - should be here for compatibility */
//#define VK_HANGUL         0x15
//#define VK_JUNJA          0x17
//#define VK_FINAL          0x18
//#define VK_HANJA          0x19
//#define VK_KANJI          0x19
//
//#define VK_ESCAPE         0x1B
//
//#define VK_CONVERT        0x1C
//#define VK_NONCONVERT     0x1D
//#define VK_ACCEPT         0x1E
//#define VK_MODECHANGE     0x1F
//
//#define VK_SPACE          0x20
//#define VK_PRIOR          0x21
//#define VK_NEXT           0x22
//#define VK_END            0x23
//#define VK_HOME           0x24
//#define VK_LEFT           0x25
//#define VK_UP             0x26
//#define VK_RIGHT          0x27
//#define VK_DOWN           0x28
//#define VK_SELECT         0x29
//#define VK_PRINT          0x2A
//#define VK_EXECUTE        0x2B
//#define VK_SNAPSHOT       0x2C
//#define VK_INSERT         0x2D
//#define VK_DELETE         0x2E
//#define VK_HELP           0x2F
//
///*
// * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
// * 0x40 : unassigned
// * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
// */
//
//#define VK_LWIN           0x5B
//#define VK_RWIN           0x5C
//#define VK_APPS           0x5D
//
///*
// * 0x5E : reserved
// */
//
//#define VK_SLEEP          0x5F
//
//#define VK_NUMPAD0        0x60
//#define VK_NUMPAD1        0x61
//#define VK_NUMPAD2        0x62
//#define VK_NUMPAD3        0x63
//#define VK_NUMPAD4        0x64
//#define VK_NUMPAD5        0x65
//#define VK_NUMPAD6        0x66
//#define VK_NUMPAD7        0x67
//#define VK_NUMPAD8        0x68
//#define VK_NUMPAD9        0x69
//#define VK_MULTIPLY       0x6A
//#define VK_ADD            0x6B
//#define VK_SEPARATOR      0x6C
//#define VK_SUBTRACT       0x6D
//#define VK_DECIMAL        0x6E
//#define VK_DIVIDE         0x6F
//#define VK_F1             0x70
//#define VK_F2             0x71
//#define VK_F3             0x72
//#define VK_F4             0x73
//#define VK_F5             0x74
//#define VK_F6             0x75
//#define VK_F7             0x76
//#define VK_F8             0x77
//#define VK_F9             0x78
//#define VK_F10            0x79
//#define VK_F11            0x7A
//#define VK_F12            0x7B
//#define VK_F13            0x7C
//#define VK_F14            0x7D
//#define VK_F15            0x7E
//#define VK_F16            0x7F
//#define VK_F17            0x80
//#define VK_F18            0x81
//#define VK_F19            0x82
//#define VK_F20            0x83
//#define VK_F21            0x84
//#define VK_F22            0x85
//#define VK_F23            0x86
//#define VK_F24            0x87
//
///*
// * 0x88 - 0x8F : unassigned
// */
//
//#define VK_NUMLOCK        0x90
//#define VK_SCROLL         0x91
//
///*
// * NEC PC-9800 kbd definitions
// */
//#define VK_OEM_NEC_EQUAL  0x92   // '=' key on numpad
//
///*
// * Fujitsu/OASYS kbd definitions
// */
//#define VK_OEM_FJ_JISHO   0x92   // 'Dictionary' key
//#define VK_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
//#define VK_OEM_FJ_TOUROKU 0x94   // 'Register word' key
//#define VK_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
//#define VK_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key
//
///*
// * 0x97 - 0x9F : unassigned
// */
//
///*
// * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
// * Used only as parameters to GetAsyncKeyState() and GetKeyState().
// * No other API or message will distinguish left and right keys in this way.
// */
//#define VK_LSHIFT         0xA0
//#define VK_RSHIFT         0xA1
//#define VK_LCONTROL       0xA2
//#define VK_RCONTROL       0xA3
//#define VK_LMENU          0xA4
//#define VK_RMENU          0xA5
//
//#if(_WIN32_WINNT >= 0x0500)
//#define VK_BROWSER_BACK        0xA6
//#define VK_BROWSER_FORWARD     0xA7
//#define VK_BROWSER_REFRESH     0xA8
//#define VK_BROWSER_STOP        0xA9
//#define VK_BROWSER_SEARCH      0xAA
//#define VK_BROWSER_FAVORITES   0xAB
//#define VK_BROWSER_HOME        0xAC
//
//#define VK_VOLUME_MUTE         0xAD
//#define VK_VOLUME_DOWN         0xAE
//#define VK_VOLUME_UP           0xAF
//#define VK_MEDIA_NEXT_TRACK    0xB0
//#define VK_MEDIA_PREV_TRACK    0xB1
//#define VK_MEDIA_STOP          0xB2
//#define VK_MEDIA_PLAY_PAUSE    0xB3
//#define VK_LAUNCH_MAIL         0xB4
//#define VK_LAUNCH_MEDIA_SELECT 0xB5
//#define VK_LAUNCH_APP1         0xB6
//#define VK_LAUNCH_APP2         0xB7
//
//#endif /* _WIN32_WINNT >= 0x0500 */
//
///*
// * 0xB8 - 0xB9 : reserved
// */
//
//#define VK_OEM_1          0xBA   // ';:' for US
//#define VK_OEM_PLUS       0xBB   // '+' any country
//#define VK_OEM_COMMA      0xBC   // ',' any country
//#define VK_OEM_MINUS      0xBD   // '-' any country
//#define VK_OEM_PERIOD     0xBE   // '.' any country
//#define VK_OEM_2          0xBF   // '/?' for US
//#define VK_OEM_3          0xC0   // '`~' for US
//
//
//
///*
// * 0xC1 - 0xD7 : reserved
// */
//
///*
// * 0xD8 - 0xDA : unassigned
// */
//
//#define VK_OEM_4          0xDB  //  '[{' for US
//#define VK_OEM_5          0xDC  //  '\|' for US
//#define VK_OEM_6          0xDD  //  ']}' for US
//#define VK_OEM_7          0xDE  //  ''"' for US
//#define VK_OEM_8          0xDF
//
///*
// * 0xE0 : reserved
// */
//
///*
// * Various extended or enhanced keyboards
// */
//#define VK_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
//#define VK_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
//#define VK_ICO_HELP       0xE3  //  Help key on ICO
//#define VK_ICO_00         0xE4  //  00 key on ICO
//
//#if(WINVER >= 0x0400)
//#define VK_PROCESSKEY     0xE5
//#endif /* WINVER >= 0x0400 */
//
//#define VK_ICO_CLEAR      0xE6
//
//
//#if(_WIN32_WINNT >= 0x0500)
//#define VK_PACKET         0xE7
//#endif /* _WIN32_WINNT >= 0x0500 */
//
///*
// * 0xE8 : unassigned
// */
//
///*
// * Nokia/Ericsson definitions
// */
//#define VK_OEM_RESET      0xE9
//#define VK_OEM_JUMP       0xEA
//#define VK_OEM_PA1        0xEB
//#define VK_OEM_PA2        0xEC
//#define VK_OEM_PA3        0xED
//#define VK_OEM_WSCTRL     0xEE
//#define VK_OEM_CUSEL      0xEF
//#define VK_OEM_ATTN       0xF0
//#define VK_OEM_FINISH     0xF1
//#define VK_OEM_COPY       0xF2
//#define VK_OEM_AUTO       0xF3
//#define VK_OEM_ENLW       0xF4
//#define VK_OEM_BACKTAB    0xF5
//
//#define VK_ATTN           0xF6
//#define VK_CRSEL          0xF7
//#define VK_EXSEL          0xF8
//#define VK_EREOF          0xF9
//#define VK_PLAY           0xFA
//#define VK_ZOOM           0xFB
//#define VK_NONAME         0xFC
//#define VK_PA1            0xFD
//#define VK_OEM_CLEAR      0xFE
//
///*
// * 0xFF : reserved
// */
//
//
///*
// * WH_MSGFILTER Filter Proc Codes
// */
//#define MSGF_DIALOGBOX      0
//#define MSGF_MESSAGEBOX     1
//#define MSGF_MENU           2
//#define MSGF_SCROLLBAR      5
//#define MSGF_NEXTWINDOW     6
//#define MSGF_MAX            8                       // unused
//#define MSGF_USER           4096
//
//
//
//
//
//
///*
// * Window Messages
// */
//
//#define e_message_null                         0x0000
//#define e_message_create                       0x0001
//#define e_message_destroy                      0x0002
//#define e_message_move                         0x0003
//#define e_message_size                         0x0005
//
//#define e_message_activate                     0x0006
///*
// * e_message_activate state values
// */
//#define     WA_INACTIVE     0
//#define     WA_ACTIVE       1
//#define     WA_CLICKACTIVE  2
//
//#define e_message_set_focus                     0x0007
//#define e_message_kill_focus                    0x0008
//#define e_message_enable                       0x000A
//#define WM_SETREDRAW                    0x000B
//#define WM_SETTEXT                      0x000C
//#define WM_GETTEXT                      0x000D
//#define WM_GETTEXTLENGTH                0x000E
//#define e_message_paint                        0x000F
//#define WM_CLOSE                        0x0010
////#ifndef _WIN32_WCE
//#define WM_QUERYENDSESSION              0x0011
//#define WM_QUERYOPEN                    0x0013
//#define WM_ENDSESSION                   0x0016
////#endif
//#define e_message_quit                         0x0012
//#define e_message_erase_background                   0x0014
//#define WM_SYSCOLORCHANGE               0x0015
//#define e_message_show_window                   0x0018
//#define WM_WININICHANGE                 0x001A
////#if(WINVER >= 0x0400)
//#define WM_SETTINGCHANGE                WM_WININICHANGE
////#endif /* WINVER >= 0x0400 */
//
//
//#define WM_DEVMODECHANGE                0x001B
//#define WM_ACTIVATEAPP                  0x001C
//#define WM_FONTCHANGE                   0x001D
//#define WM_TIMECHANGE                   0x001E
//#define WM_CANCELMODE                   0x001F
//#define e_message_set_cursor                    0x0020
//#define e_message_mouse_activate                0x0021
//#define WM_CHILDACTIVATE                0x0022
//#define WM_QUEUESYNC                    0x0023
//
//#define WM_GETMINMAXINFO                0x0024
///*
// * Struct pointed to by WM_GETMINMAXINFO lParam
// */
//typedef struct tagMINMAXINFO
//{
//   POINT32 pointReserved;
//   POINT32 pointMaxSize;
//   POINT32 pointMaxPosition;
//   POINT32 pointMinTrackSize;
//   POINT32 pointMaxTrackSize;
//} MINMAXINFO, *PMINMAXINFO, *LPMINMAXINFO;
//
//#define e_message_paintICON                    0x0026
//#define WM_ICONERASEBKGND               0x0027
//#define WM_NEXTDLGCTL                   0x0028
//#define WM_SPOOLERSTATUS                0x002A
//#define WM_DRAWITEM                     0x002B
//#define e_message_measure_item                  0x002C
//#define WM_DELETEITEM                   0x002D
//#define WM_VKEYTOITEM                   0x002E
//#define WM_CHARTOITEM                   0x002F
//#define WM_SETFONT                      0x0030
//#define WM_GETFONT                      0x0031
//#define WM_SETHOTKEY                    0x0032
//#define WM_GETHOTKEY                    0x0033
//#define WM_QUERYDRAGICON                0x0037
//#define WM_COMPAREITEM                  0x0039
////#if(WINVER >= 0x0500)
////#ifndef _WIN32_WCE
//#define WM_GETOBJECT                    0x003D
////#endif
////#endif /* WINVER >= 0x0500 */
//#define WM_COMPACTING                   0x0041
//#define WM_COMMNOTIFY                   0x0044  /* no longer suported */
//#define e_message_window_position_changing            0x0046
//#define e_message_window_position_changed             0x0047
//
//#define WM_POWER                        0x0048
///*
// * wParam for WM_POWER interaction_impl message and DRV_POWER driver notification
// */
//#define PWR_OK              1
//#define PWR_FAIL            (-1)
//#define PWR_SUSPENDREQUEST  1
//#define PWR_SUSPENDRESUME   2
//#define PWR_CRITICALRESUME  3
//
//#define WM_COPYDATA                     0x004A
//#define WM_CANCELJOURNAL                0x004B
//
//
///*
// * lParam of WM_COPYDATA message points to...
// */
//typedef struct tagCOPYDATASTRUCT
//{
//   uptr dwData;
//   ::u32 cbData;
//   PVOID lpData;
//} COPYDATASTRUCT, *PCOPYDATASTRUCT;
//
//#if(WINVER >= 0x0400)
//typedef struct tagMDINEXTMENU
//{
//   HMENU   hmenuIn;
//   HMENU   hmenuNext;
//   oswindow    hwndNext;
//} MDINEXTMENU, * PMDINEXTMENU, * LPMDINEXTMENU;
//#endif /* WINVER >= 0x0400 */
//
//
////#if(WINVER >= 0x0400)
//#define WM_NOTIFY                       0x004E
//#define WM_INPUTLANGCHANGEREQUEST       0x0050
//#define WM_INPUTLANGCHANGE              0x0051
//#define WM_TCARD                        0x0052
//#define WM_HELP                         0x0053
//#define WM_USERCHANGED                  0x0054
//#define WM_NOTIFYFORMAT                 0x0055
//
//#define NFR_ANSI                             1
//#define NFR_UNICODE                          2
//#define NF_QUERY                             3
//#define NF_REQUERY                           4
//
//#define e_message_context_menu                  0x007B
//#define WM_STYLECHANGING                0x007C
//#define WM_STYLECHANGED                 0x007D
//#define e_message_display_change                0x007E
//#define WM_GETICON                      0x007F
//#define WM_SETICON                      0x0080
////#endif /* WINVER >= 0x0400 */
//
//#define e_message_nccreate                     0x0081
//#define e_message_ncdestroy                    0x0082
//#define e_message_nccalcsize                   0x0083
//#define e_message_nchittest                    0x0084
//#define e_message_ncpaint                      0x0085
//#define e_message_ncactivate                   0x0086
//#define WM_GETDLGCODE                   0x0087
////#ifndef _WIN32_WCE
//#define WM_SYNCPAINT                    0x0088
////#endif
//#define e_message_non_client_mouse_move                  0x00A0
//#define e_message_non_client_left_button_down                0x00A1
//#define e_message_non_client_left_button_up                  0x00A2
//#define WM_NCLBUTTONDBLCLK              0x00A3
//#define WM_NCRBUTTONDOWN                0x00A4
//#define WM_NCRBUTTONUP                  0x00A5
//#define WM_NCRBUTTONDBLCLK              0x00A6
//#define WM_NCMBUTTONDOWN                0x00A7
//#define WM_NCMBUTTONUP                  0x00A8
//#define WM_NCMBUTTONDBLCLK              0x00A9
//
//
//
////#if(_WIN32_WINNT >= 0x0500)
//#define WM_NCXBUTTONDOWN                0x00AB
//#define WM_NCXBUTTONUP                  0x00AC
//#define WM_NCXBUTTONDBLCLK              0x00AD
////#endif /* _WIN32_WINNT >= 0x0500 */
//
//
////#if(_WIN32_WINNT >= 0x0501)
//#define WM_INPUT_DEVICE_CHANGE          0x00FE
////#endif /* _WIN32_WINNT >= 0x0501 */
//
////#if(_WIN32_WINNT >= 0x0501)
//#define WM_INPUT                        0x00FF
////#endif /* _WIN32_WINNT >= 0x0501 */
//
//#define e_message_key_first                     0x0100
//#define e_message_key_down                      0x0100
//#define e_message_key_up                        0x0101
//#define e_message_char                         0x0102
//#define e_message_dead_char                     0x0103
//#define e_message_sys_key_down                   0x0104
//#define e_message_sys_key_up                     0x0105
//#define e_message_sys_char                      0x0106
//#define e_message_sys_dead_char                  0x0107
////#if(_WIN32_WINNT >= 0x0501)
//#define e_message_uni_char                      0x0109
//#define e_message_key_last                      0x0109
//#define UNICODE_NOCHAR                  0xFFFF
////#else
////#define e_message_key_last                      0x0108
////#endif /* _WIN32_WINNT >= 0x0501 */
//
////#if(WINVER >= 0x0400)
//#define WM_IME_STARTCOMPOSITION         0x010D
//#define WM_IME_ENDCOMPOSITION           0x010E
//#define WM_IME_COMPOSITION              0x010F
//#define WM_IME_KEYLAST                  0x010F
////#endif /* WINVER >= 0x0400 */
//
//#define WM_INITDIALOG                   0x0110
//#define e_message_command                      0x0111
//#define WM_SYSCOMMAND                   0x0112
//#define e_message_timer                        0x0113
//#define e_message_hscroll                      0x0114
//#define e_message_vscroll                      0x0115
//#define WM_INITMENU                     0x0116
//#define e_message_initialize_menu_popup                0x0117
////#if(WINVER >= 0x0601)
//#define WM_GESTURE                      0x0119
//#define WM_GESTURENOTIFY                0x011A
////#endif /* WINVER >= 0x0601 */
//#define WM_MENUSELECT                   0x011F
//#define WM_MENUCHAR                     0x0120
//#define WM_ENTERIDLE                    0x0121
////#if(WINVER >= 0x0500)
////#ifndef _WIN32_WCE
//#define WM_MENURBUTTONUP                0x0122
//#define WM_MENUDRAG                     0x0123
//#define WM_MENUGETOBJECT                0x0124
//#define WM_UNINITMENUPOPUP              0x0125
//#define WM_MENUCOMMAND                  0x0126
//
////#ifndef _WIN32_WCE
////#if(_WIN32_WINNT >= 0x0500)
//#define WM_CHANGEUISTATE                0x0127
//#define WM_UPDATEUISTATE                0x0128
//#define WM_QUERYUISTATE                 0x0129
//
///*
// * LOWORD(wParam) values in WM_*UISTATE*
// */
//#define UIS_SET                         1
//#define UIS_CLEAR                       2
//#define UIS_INITIALIZE                  3
//
///*
// * HIWORD(wParam) values in WM_*UISTATE*
// */
//#define UISF_HIDEFOCUS                  0x1
//#define UISF_HIDEACCEL                  0x2
////#if(_WIN32_WINNT >= 0x0501)
//#define UISF_ACTIVE                     0x4
////#endif /* _WIN32_WINNT >= 0x0501 */
////#endif /* _WIN32_WINNT >= 0x0500 */
////#endif
//
////#endif
////#endif /* WINVER >= 0x0500 */
//
//#define WM_CTLCOLORMSGBOX               0x0132
//#define WM_CTLCOLOREDIT                 0x0133
//#define WM_CTLCOLORLISTBOX              0x0134
//#define WM_CTLCOLORBTN                  0x0135
//#define WM_CTLCOLORDLG                  0x0136
//#define WM_CTLCOLORSCROLLBAR            0x0137
//#define WM_CTLCOLORSTATIC               0x0138
//#define MN_GETHMENU                     0x01E1
//
//#define WM_MOUSEFIRST                   0x0200
//#define e_message_mouse_move                    0x0200
//#define WM_LBUTTONDOWN                  0x0201
//#define WM_LBUTTONUP                    0x0202
//#define e_message_left_button_double_click                0x0203
//#define WM_RBUTTONDOWN                  0x0204
//#define WM_RBUTTONUP                    0x0205
//#define e_message_right_button_double_click                0x0206
//#define e_message_middle_button_down                  0x0207
//#define e_message_middle_button_up                    0x0208
//#define e_message_middle_button_double_click                0x0209
////#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
//#define WM_MOUSEWHEEL                   0x020A
////#endif
////#if (_WIN32_WINNT >= 0x0500)
//#define WM_XBUTTONDOWN                  0x020B
//#define WM_XBUTTONUP                    0x020C
//#define WM_XBUTTONDBLCLK                0x020D
////#endif
////#if (_WIN32_WINNT >= 0x0600)
//#define WM_MOUSEHWHEEL                  0x020E
////#endif
//
////#if (_WIN32_WINNT >= 0x0600)
//#define WM_MOUSELAST                    0x020E
////#elif (_WIN32_WINNT >= 0x0500)
////#define WM_MOUSELAST                    0x020D
////#elif (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
////#define WM_MOUSELAST                    0x020A
////#else
////#define WM_MOUSELAST                    0x0209
////#endif /* (_WIN32_WINNT >= 0x0600) */
//
//
//
//
//
//
////#if(_WIN32_WINNT >= 0x0400)
///* Value for rolling one detent */
//#define WHEEL_DELTA                     120
//#define GET_WHEEL_DELTA_WPARAM(wParam)  ((short)HIWORD(wParam))
//
///* Setting to scroll one page for SPI_GET/SETWHEELSCROLLLINES */
//#define WHEEL_PAGESCROLL                (UINT_MAX)
////#endif /* _WIN32_WINNT >= 0x0400 */
//
////#if(_WIN32_WINNT >= 0x0500)
//#define GET_KEYSTATE_WPARAM(wParam)     (LOWORD(wParam))
//#define GET_NCHITTEST_WPARAM(wParam)    ((short)LOWORD(wParam))
//#define GET_XBUTTON_WPARAM(wParam)      (HIWORD(wParam))
//
///* XButton values are ::u16 flags */
//#define XBUTTON1      0x0001
//#define XBUTTON2      0x0002
///* Were there to be an XBUTTON3, its value would be 0x0004 */
////#endif /* _WIN32_WINNT >= 0x0500 */
//
//#define WM_PARENTNOTIFY                 0x0210
//#define WM_ENTERMENULOOP                0x0211
//#define WM_EXITMENULOOP                 0x0212
//
////#if(WINVER >= 0x0400)
//#define WM_NEXTMENU                     0x0213
//#define WM_SIZING                       0x0214
//#define WM_CAPTURECHANGED               0x0215
//#define WM_MOVING                       0x0216
////#endif /* WINVER >= 0x0400 */
//
////#if(WINVER >= 0x0400)
//
//
//#define WM_POWERBROADCAST               0x0218
//
//#ifndef _WIN32_WCE
//#define PBT_APMQUERYSUSPEND             0x0000
//#define PBT_APMQUERYSTANDBY             0x0001
//
//#define PBT_APMQUERYSUSPENDFAILED       0x0002
//#define PBT_APMQUERYSTANDBYFAILED       0x0003
//
//#define PBT_APMSUSPEND                  0x0004
//#define PBT_APMSTANDBY                  0x0005
//
//#define PBT_APMRESUMECRITICAL           0x0006
//#define PBT_APMRESUMESUSPEND            0x0007
//#define PBT_APMRESUMESTANDBY            0x0008
//
//#define PBTF_APMRESUMEFROMFAILURE       0x00000001
//
//#define PBT_APMBATTERYLOW               0x0009
//#define PBT_APMPOWERSTATUSCHANGE        0x000A
//
//#define PBT_APMOEMEVENT                 0x000B
//
//
//#define PBT_APMRESUMEAUTOMATIC          0x0012
////#if (_WIN32_WINNT >= 0x0502)
////#ifndef PBT_POWERSETTINGCHANGE
//#define PBT_POWERSETTINGCHANGE          0x8013
//
////#pragma region Desktop Family
////#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
//
//typedef struct
//{
//   GUID PowerSetting;
//   ::u32 DataLength;
//   WINUCHAR Data[1];
//} POWERBROADCAST_SETTING, *PPOWERBROADCAST_SETTING;
//
//
////#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
////#pragma endregion
//
////#endif // PBT_POWERSETTINGCHANGE
//
////#endif // (_WIN32_WINNT >= 0x0502)
////#endif
//
////#endif /* WINVER >= 0x0400 */
//
////#if(WINVER >= 0x0400)
//#define WM_DEVICECHANGE                 0x0219
////#endif /* WINVER >= 0x0400 */
//
//#define WM_MDICREATE                    0x0220
//#define WM_MDIDESTROY                   0x0221
//#define WM_MDIACTIVATE                  0x0222
//#define WM_MDIRESTORE                   0x0223
//#define WM_MDINEXT                      0x0224
//#define WM_MDIMAXIMIZE                  0x0225
//#define WM_MDITILE                      0x0226
//#define WM_MDICASCADE                   0x0227
//#define WM_MDIICONARRANGE               0x0228
//#define WM_MDIGETACTIVE                 0x0229
//
//
//#define WM_MDISETMENU                   0x0230
//#define WM_ENTERSIZEMOVE                0x0231
//#define WM_EXITSIZEMOVE                 0x0232
//#define WM_DROPFILES                    0x0233
//#define WM_MDIREFRESHMENU               0x0234
//
////#if(WINVER >= 0x0602)
//#define WM_POINTERDEVICECHANGE          0x238
//#define WM_POINTERDEVICEINRANGE         0x239
//#define WM_POINTERDEVICEOUTOFRANGE      0x23A
////#endif /* WINVER >= 0x0602 */
//
////#if(WINVER >= 0x0601)
//#define WM_TOUCH                        0x0240
////#endif /* WINVER >= 0x0601 */
//
////#if(WINVER >= 0x0602)
//#define WM_NCPOINTERUPDATE              0x0241
//#define WM_NCPOINTERDOWN                0x0242
//#define WM_NCPOINTERUP                  0x0243
//#define WM_POINTERUPDATE                0x0245
//#define WM_POINTERDOWN                  0x0246
//#define WM_POINTERUP                    0x0247
//#define WM_POINTERENTER                 0x0249
//#define WM_POINTERLEAVE                 0x024A
//#define WM_POINTERACTIVATE              0x024B
//#define WM_POINTERCAPTURECHANGED        0x024C
//#define WM_TOUCHHITTESTING              0x024D
//#define WM_POINTERWHEEL                 0x024E
//#define WM_POINTERHWHEEL                0x024F
////#endif /* WINVER >= 0x0602 */
//
//
////#if(WINVER >= 0x0400)
//#define WM_IME_SETCONTEXT               0x0281
//#define WM_IME_NOTIFY                   0x0282
//#define WM_IME_CONTROL                  0x0283
//#define WM_IME_COMPOSITIONFULL          0x0284
//#define WM_IME_SELECT                   0x0285
//#define WM_IME_CHAR                     0x0286
////#endif /* WINVER >= 0x0400 */
////#if(WINVER >= 0x0500)
//#define WM_IME_REQUEST                  0x0288
////#endif /* WINVER >= 0x0500 */
////#if(WINVER >= 0x0400)
//#define WM_IME_KEYDOWN                  0x0290
//#define WM_IME_KEYUP                    0x0291
////#endif /* WINVER >= 0x0400 */
//
////#if((_WIN32_WINNT >= 0x0400) || (WINVER >= 0x0500))
//#define WM_MOUSEHOVER                   0x02A1
//#define e_message_mouse_leave                   0x02A3
////#endif
////#if(WINVER >= 0x0500)
//#define WM_NCMOUSEHOVER                 0x02A0
//#define WM_NCMOUSELEAVE                 0x02A2
////#endif /* WINVER >= 0x0500 */
//
////#if(_WIN32_WINNT >= 0x0501)
//#define WM_WTSSESSION_CHANGE            0x02B1
//
//#define WM_TABLET_FIRST                 0x02c0
//#define WM_TABLET_LAST                  0x02df
////#endif /* _WIN32_WINNT >= 0x0501 */
//
//#define WM_CUT                          0x0300
//#define WM_COPY                         0x0301
//#define WM_PASTE                        0x0302
//#define WM_CLEAR                        0x0303
//#define WM_UNDO                         0x0304
//#define WM_RENDERFORMAT                 0x0305
//#define WM_RENDERALLFORMATS             0x0306
//#define WM_DESTROYCLIPBOARD             0x0307
//#define WM_DRAWCLIPBOARD                0x0308
//#define e_message_paintCLIPBOARD               0x0309
//#define e_message_vscrollCLIPBOARD             0x030A
//#define WM_SIZECLIPBOARD                0x030B
//#define WM_ASKCBFORMATNAME              0x030C
//#define WM_CHANGECBCHAIN                0x030D
//#define e_message_hscrollCLIPBOARD             0x030E
//#define WM_QUERYNEWPALETTE              0x030F
//#define WM_PALETTEISCHANGING            0x0310
//#define WM_PALETTECHANGED               0x0311
//#define WM_HOTKEY                       0x0312
//
////#if(WINVER >= 0x0400)
//#define WM_PRINT                        0x0317
//#define WM_PRINTCLIENT                  0x0318
////#endif /* WINVER >= 0x0400 */
//
////#if(_WIN32_WINNT >= 0x0500)
//#define WM_APPCOMMAND                   0x0319
////#endif /* _WIN32_WINNT >= 0x0500 */
//
////#if(_WIN32_WINNT >= 0x0501)
//#define WM_THEMECHANGED                 0x031A
////#endif /* _WIN32_WINNT >= 0x0501 */
//
//
////#if(_WIN32_WINNT >= 0x0501)
//#define WM_CLIPBOARDUPDATE              0x031D
////#endif /* _WIN32_WINNT >= 0x0501 */
//
////#if(_WIN32_WINNT >= 0x0600)
//#define WM_DWMCOMPOSITIONCHANGED        0x031E
//#define WM_DWMNCRENDERINGCHANGED        0x031F
//#define WM_DWMCOLORIZATIONCOLORCHANGED  0x0320
//#define WM_DWMWINDOWMAXIMIZEDCHANGE     0x0321
////#endif /* _WIN32_WINNT >= 0x0600 */
//
////#if(_WIN32_WINNT >= 0x0601)
//#define WM_DWMSENDICONICTHUMBNAIL           0x0323
//#define WM_DWMSENDICONICLIVEPREVIEWBITMAP   0x0326
////#endif /* _WIN32_WINNT >= 0x0601 */
//
//
////#if(WINVER >= 0x0600)
//#define WM_GETTITLEBARINFOEX            0x033F
//#endif /* WINVER >= 0x0600 */
//
////#if(WINVER >= 0x0400)
//
//#define WM_HANDHELDFIRST                0x0358
//#define WM_HANDHELDLAST                 0x035F
//
//#define WM_AFXFIRST                     0x0360
//#define WM_AFXLAST                      0x037F
////#endif /* WINVER >= 0x0400 */
//
//#define WM_PENWINFIRST                  0x0380
//#define WM_PENWINLAST                   0x038F
//
//
////#if(WINVER >= 0x0400)
//#define WM_APP                          0x8000
////#endif /* WINVER >= 0x0400 */
//
//
///*
// * NOTE: All Message Numbers below 0x0400 are RESERVED.
// *
// * Private Window Messages Start Here:
// */
//#define WM_USER                         0x0400
//
////#if(WINVER >= 0x0400)
//
///*  wParam for WM_SIZING message  */
//#define WMSZ_LEFT           1
//#define WMSZ_RIGHT          2
//#define WMSZ_TOP            3
//#define WMSZ_TOPLEFT        4
//#define WMSZ_TOPRIGHT       5
//#define WMSZ_BOTTOM         6
//#define WMSZ_BOTTOMLEFT     7
//#define WMSZ_BOTTOMRIGHT    8
////#endif /* WINVER >= 0x0400 */
//
////#ifndef NONCMESSAGES
//
///*
// * e_message_nchittest and MOUSEHOOKSTRUCT Mouse Position Codes
// */
//#define HTERROR             (-2)
//#define HTTRANSPARENT       (-1)
//#define HTNOWHERE           0
//#define HTCLIENT            1
//#define HTCAPTION           2
//#define HTSYSMENU           3
//#define HTGROWBOX           4
//#define HTSIZE              HTGROWBOX
//#define HTMENU              5
//#define HTHSCROLL           6
//#define HTVSCROLL           7
//#define HTMINBUTTON         8
//#define HTMAXBUTTON         9
//#define HTLEFT              10
//#define HTRIGHT             11
//#define HTTOP               12
//#define HTTOPLEFT           13
//#define HTTOPRIGHT          14
//#define HTBOTTOM            15
//#define HTBOTTOMLEFT        16
//#define HTBOTTOMRIGHT       17
//#define HTBORDER            18
//#define HTREDUCE            HTMINBUTTON
//#define HTZOOM              HTMAXBUTTON
//#define HTSIZEFIRST         HTLEFT
//#define HTSIZELAST          HTBOTTOMRIGHT
////#if(WINVER >= 0x0400)
//#define HTOBJECT            19
//#define HTCLOSE             20
//#define HTHELP              21
////#endif /* WINVER >= 0x0400 */
//
//
///*
// * SendMessageTimeout values
// */
//#define SMTO_NORMAL         0x0000
//#define SMTO_BLOCK          0x0001
//#define SMTO_ABORTIFHUNG    0x0002
////#if(WINVER >= 0x0500)
//#define SMTO_NOTIMEOUTIFNOTHUNG 0x0008
////#endif /* WINVER >= 0x0500 */
////#if(WINVER >= 0x0600)
////#define SMTO_ERRORONEXIT    0x0020
////#endif /* WINVER >= 0x0600 */
////#if(WINVER >= 0x0602)
////#endif /* WINVER >= 0x0602 */
//
////#endif /* !NONCMESSAGES */
//
///*
// * e_message_mouse_activate Return Codes
// */
//#define MA_ACTIVATE         1
//#define MA_ACTIVATEANDEAT   2
//#define MA_NOACTIVATE       3
//#define MA_NOACTIVATEANDEAT 4
//
///*
// * WM_SETICON / WM_GETICON Type Codes
// */
//#define ICON_SMALL          0
//#define ICON_BIG            1
////#if(_WIN32_WINNT >= 0x0501)
//#define ICON_SMALL2         2
////#endif /* _WIN32_WINNT >= 0x0501 */
//
//
////#pragma region Desktop Family
////#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
//
//
//::u32
//WINAPI
//RegisterWindowMessageA(
//const char * lpString);
//
//::u32
//WINAPI
//RegisterWindowMessageW(
//const widechar * lpString);
////#ifdef UNICODE
//#define RegisterWindowMessage  RegisterWindowMessageW
////#else
////#define RegisterWindowMessage  RegisterWindowMessageA
////#endif // !UNICODE
//
////#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
////#pragma endregion
//
//
///*
// * e_message_size message wParam values
// */
//#define SIZE_RESTORED       0
//#define SIZE_MINIMIZED      1
//#define SIZE_MAXIMIZED      2
//#define SIZE_MAXSHOW        3
//#define SIZE_MAXHIDE        4
//
///*
// * Obsolete constant names
// */
//#define SIZENORMAL          SIZE_RESTORED
//#define SIZEICONIC          SIZE_MINIMIZED
//#define SIZEFULLSCREEN      SIZE_MAXIMIZED
//#define SIZEZOOMSHOW        SIZE_MAXSHOW
//#define SIZEZOOMHIDE        SIZE_MAXHIDE
//
//
////#pragma region Desktop Family
////#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
//
///*
// * e_message_window_position_changing/CHANGED struct pointed to by lParam
// */
//typedef struct tagWINDOWPOS
//{
//   oswindow    hwnd;
//   oswindow    hwndInsertAfter;
//   i32     x;
//   i32     y;
//   i32     cx;
//   i32     cy;
//   ::u32    flags;
//} WINDOWPOS, *LPWINDOWPOS, *PWINDOWPOS;
//
///*
// * e_message_nccalcsize parameter structure
// */
//typedef struct tagNCCALCSIZE_PARAMS
//{
//   RECT32       rgrc[3];
//   PWINDOWPOS lppos;
//} NCCALCSIZE_PARAMS, *LPNCCALCSIZE_PARAMS;
//
////#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
////#pragma endregion
//
///*
// * e_message_nccalcsize "interaction_impl valid rect" return values
// */
//#define WVR_ALIGNTOP        0x0010
//#define WVR_ALIGNLEFT       0x0020
//#define WVR_ALIGNBOTTOM     0x0040
//#define WVR_ALIGNRIGHT      0x0080
//#define WVR_HREDRAW         0x0100
//#define WVR_VREDRAW         0x0200
//#define WVR_REDRAW         (WVR_HREDRAW | \
//                            WVR_VREDRAW)
//#define WVR_VALIDRECTS      0x0400
//
//
////#ifndef NOKEYSTATES
//
///*
// * Key State Masks for Mouse Messages
// */
//#define MK_LBUTTON          0x0001
//#define MK_RBUTTON          0x0002
//#define MK_SHIFT            0x0004
//#define MK_CONTROL          0x0008
//#define MK_MBUTTON          0x0010
////#if(_WIN32_WINNT >= 0x0500)
//#define MK_XBUTTON1         0x0020
//#define MK_XBUTTON2         0x0040
////#endif /* _WIN32_WINNT >= 0x0500 */
//
////#endif /* !NOKEYSTATES */
//
//
////#if(_WIN32_WINNT >= 0x0400)
////#ifndef NOTRACKMOUSEEVENT
//
//#define TME_HOVER       0x00000001
//#define TME_LEAVE       0x00000002
////#if(WINVER >= 0x0500)
//#define TME_NONCLIENT   0x00000010
////#endif /* WINVER >= 0x0500 */
//#define TME_QUERY       0x40000000
//#define TME_CANCEL      0x80000000
//
//
//#define HOVER_DEFAULT   0xFFFFFFFF
////#endif /* _WIN32_WINNT >= 0x0400 */
//
////#if(_WIN32_WINNT >= 0x0400)
//
////#pragma region Desktop Family
////#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
//
//typedef struct tagTRACKMOUSEEVENT
//{
//   ::u32 cbSize;
//   ::u32 dwFlags;
//   oswindow  hwndTrack;
//   ::u32 dwHoverTime;
//} TRACKMOUSEEVENT, *LPTRACKMOUSEEVENT;
//
//
//int_bool
//WINAPI
//TrackMouseEvent(
//LPTRACKMOUSEEVENT lpEventTrack);
//
////#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
////#pragma endregion
//
////#endif /* _WIN32_WINNT >= 0x0400 */
//
////#if(_WIN32_WINNT >= 0x0400)
//
////#endif /* !NOTRACKMOUSEEVENT */
////#endif /* _WIN32_WINNT >= 0x0400 */
//
//
//
//
//
///*
// * GetSystemMetrics() codes
// */
//
//#define SM_CXSCREEN             0
//#define SM_CYSCREEN             1
//#define SM_CXVSCROLL            2
//#define SM_CYHSCROLL            3
//#define SM_CYCAPTION            4
//#define SM_CXBORDER             5
//#define SM_CYBORDER             6
//#define SM_CXDLGFRAME           7
//#define SM_CYDLGFRAME           8
//#define SM_CYVTHUMB             9
//#define SM_CXHTHUMB             10
//#define SM_CXICON               11
//#define SM_CYICON               12
//#define SM_CXCURSOR             13
//#define SM_CYCURSOR             14
//#define SM_CYMENU               15
//#define SM_CXFULLSCREEN         16
//#define SM_CYFULLSCREEN         17
//#define SM_CYKANJIWINDOW        18
//#define SM_MOUSEPRESENT         19
//#define SM_CYVSCROLL            20
//#define SM_CXHSCROLL            21
//#define SM_DEBUG                22
//#define SM_SWAPBUTTON           23
//#define SM_RESERVED1            24
//#define SM_RESERVED2            25
//#define SM_RESERVED3            26
//#define SM_RESERVED4            27
//#define SM_CXMIN                28
//#define SM_CYMIN                29
//#define SM_CXSIZE               30
//#define SM_CYSIZE               31
//#define SM_CXFRAME              32
//#define SM_CYFRAME              33
//#define SM_CXMINTRACK           34
//#define SM_CYMINTRACK           35
//#define SM_CXDOUBLECLK          36
//#define SM_CYDOUBLECLK          37
//#define SM_CXICONSPACING        38
//#define SM_CYICONSPACING        39
//#define SM_MENUDROPALIGNMENT    40
//#define SM_PENWINDOWS           41
//#define SM_DBCSENABLED          42
//#define SM_CMOUSEBUTTONS        43
//
////#if(WINVER >= 0x0400)
//#define SM_CXFIXEDFRAME           SM_CXDLGFRAME  /* ;win40 name change */
//#define SM_CYFIXEDFRAME           SM_CYDLGFRAME  /* ;win40 name change */
//#define SM_CXSIZEFRAME            SM_CXFRAME     /* ;win40 name change */
//#define SM_CYSIZEFRAME            SM_CYFRAME     /* ;win40 name change */
//
//#define SM_SECURE               44
//#define SM_CXEDGE               45
//#define SM_CYEDGE               46
//#define SM_CXMINSPACING         47
//#define SM_CYMINSPACING         48
//#define SM_CXSMICON             49
//#define SM_CYSMICON             50
//#define SM_CYSMCAPTION          51
//#define SM_CXSMSIZE             52
//#define SM_CYSMSIZE             53
//#define SM_CXMENUSIZE           54
//#define SM_CYMENUSIZE           55
//#define SM_ARRANGE              56
//#define SM_CXMINIMIZED          57
//#define SM_CYMINIMIZED          58
//#define SM_CXMAXTRACK           59
//#define SM_CYMAXTRACK           60
//#define SM_CXMAXIMIZED          61
//#define SM_CYMAXIMIZED          62
//#define SM_NETWORK              63
//#define SM_CLEANBOOT            67
//#define SM_CXDRAG               68
//#define SM_CYDRAG               69
////#endif /* WINVER >= 0x0400 */
//#define SM_SHOWSOUNDS           70
////#if(WINVER >= 0x0400)
//#define SM_CXMENUCHECK          71   /* Use instead of GetMenuCheckMarkDimensions()! */
//#define SM_CYMENUCHECK          72
//#define SM_SLOWMACHINE          73
//#define SM_MIDEASTENABLED       74
////#endif /* WINVER >= 0x0400 */
//
////#if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
//#define SM_MOUSEWHEELPRESENT    75
////#endif
////#if(WINVER >= 0x0500)
//#define SM_XVIRTUALSCREEN       76
//#define SM_YVIRTUALSCREEN       77
//#define SM_CXVIRTUALSCREEN      78
//#define SM_CYVIRTUALSCREEN      79
//#define SM_CMONITORS            80
//#define SM_SAMEDISPLAYFORMAT    81
////#endif /* WINVER >= 0x0500 */
////#if(_WIN32_WINNT >= 0x0500)
//#define SM_IMMENABLED           82
////#endif /* _WIN32_WINNT >= 0x0500 */
////#if(_WIN32_WINNT >= 0x0501)
//#define SM_CXFOCUSBORDER        83
//#define SM_CYFOCUSBORDER        84
////#endif /* _WIN32_WINNT >= 0x0501 */
//
////#if(_WIN32_WINNT >= 0x0501)
//#define SM_TABLETPC             86
//#define SM_MEDIACENTER          87
//#define SM_STARTER              88
//#define SM_SERVERR2             89
////#endif /* _WIN32_WINNT >= 0x0501 */
//
////#if(_WIN32_WINNT >= 0x0600)
//#define SM_MOUSEHORIZONTALWHEELPRESENT    91
//#define SM_CXPADDEDBORDER       92
////#endif /* _WIN32_WINNT >= 0x0600 */
//
////#if(WINVER >= 0x0601)
//
//#define SM_DIGITIZER            94
//#define SM_MAXIMUMTOUCHES       95
////#endif /* WINVER >= 0x0601 */
//
////#if (WINVER < 0x0500) && (!defined(_WIN32_WINNT) || (_WIN32_WINNT < 0x0400))
////#define SM_CMETRICS             76
////#elif WINVER == 0x500
////#define SM_CMETRICS             83
////#elif WINVER == 0x501
////#define SM_CMETRICS             91
////#elif WINVER == 0x600
////#define SM_CMETRICS             93
////#else
//#define SM_CMETRICS             97
////#endif
//
////#if(WINVER >= 0x0500)
//#define SM_REMOTESESSION        0x1000
//
//
////#if(_WIN32_WINNT >= 0x0501)
//#define SM_SHUTTINGDOWN         0x2000
////#endif /* _WIN32_WINNT >= 0x0501 */
//
////#if(WINVER >= 0x0501)
//#define SM_REMOTECONTROL        0x2001
////#endif /* WINVER >= 0x0501 */
//
////#if(WINVER >= 0x0501)
//#define SM_CARETBLINKINGENABLED 0x2002
////#endif /* WINVER >= 0x0501 */
//
////#if(WINVER >= 0x0602)
//#define SM_CONVERTIBLESLATEMODE 0x2003
//#define SM_SYSTEMDOCKED         0x2004
////#endif /* WINVER >= 0x0602 */
//
////#endif /* WINVER >= 0x0500 */
//
//
////#pragma region Desktop Family
////#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
//
//CLASS_DECL_APEX i32 WINAPI GetSystemMetrics(i32 nIndex);
//
//
////#endif /* WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) */
////#pragma endregion
//
//
//
//
//
//
//
//
//
///*
// * Color Types
// */
//#define CTLCOLOR_MSGBOX         0
//#define CTLCOLOR_EDIT           1
//#define CTLCOLOR_LISTBOX        2
//#define CTLCOLOR_BTN            3
//#define CTLCOLOR_DLG            4
//#define CTLCOLOR_SCROLLBAR      5
//#define CTLCOLOR_STATIC         6
//#define CTLCOLOR_MAX            7
//
//#define COLOR_SCROLLBAR         0
//#define COLOR_BACKGROUND        1
//#define COLOR_ACTIVECAPTION     2
//#define COLOR_INACTIVECAPTION   3
//#define COLOR_MENU              4
//#define COLOR_WINDOW            5
//#define COLOR_WINDOWFRAME       6
//#define COLOR_MENUTEXT          7
//#define COLOR_WINDOWTEXT        8
//#define COLOR_CAPTIONTEXT       9
//#define COLOR_ACTIVEBORDER      10
//#define COLOR_INACTIVEBORDER    11
//#define COLOR_APPWORKSPACE      12
//#define COLOR_HIGHLIGHT         13
//#define COLOR_HIGHLIGHTTEXT     14
//#define COLOR_BTNFACE           15
//#define COLOR_BTNSHADOW         16
//#define COLOR_GRAYTEXT          17
//#define COLOR_BTNTEXT           18
//#define COLOR_INACTIVECAPTIONTEXT 19
//#define COLOR_BTNHIGHLIGHT      20
//
////#if(WINVER >= 0x0400)
//#define COLOR_3DDKSHADOW        21
//#define COLOR_3DLIGHT           22
//#define COLOR_INFOTEXT          23
//#define COLOR_INFOBK            24
////#endif /* WINVER >= 0x0400 */
//
////#if(WINVER >= 0x0500)
//#define COLOR_HOTLIGHT          26
//#define COLOR_GRADIENTACTIVECAPTION 27
//#define COLOR_GRADIENTINACTIVECAPTION 28
////#if(WINVER >= 0x0501)
//#define COLOR_MENUHILIGHT       29
//#define COLOR_MENUBAR           30
////#endif /* WINVER >= 0x0501 */
////#endif /* WINVER >= 0x0500 */
//
////#if(WINVER >= 0x0400)
//#define COLOR_DESKTOP           COLOR_BACKGROUND
//#define COLOR_3DFACE            COLOR_BTNFACE
//#define COLOR_3DSHADOW          COLOR_BTNSHADOW
//#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
//#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
//#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT
////#endif /* WINVER >= 0x0400 */
//
//
//
//
///*
// * System Menu Command Values
// */
//#define SC_SIZE         0xF000
//#define SC_MOVE         0xF010
//#define SC_MINIMIZE     0xF020
//#define SC_MAXIMIZE     0xF030
//#define SC_NEXTWINDOW   0xF040
//#define SC_PREVWINDOW   0xF050
//#define SC_CLOSE        0xF060
//#define SC_VSCROLL      0xF070
//#define SC_HSCROLL      0xF080
//#define SC_MOUSEMENU    0xF090
//#define SC_KEYMENU      0xF100
//#define SC_ARRANGE      0xF110
//#define SC_RESTORE      0xF120
//#define SC_TASKLIST     0xF130
//#define SC_SCREENSAVE   0xF140
//#define SC_HOTKEY       0xF150
//#if(WINVER >= 0x0400)
//#define SC_DEFAULT      0xF160
//#define SC_MONITORPOWER 0xF170
//#define SC_CONTEXTHELP  0xF180
//#define SC_SEPARATOR    0xF00F
//#endif /* WINVER >= 0x0400 */
//
//#if(WINVER >= 0x0600)
//#define SCF_ISSECURE    0x00000001
//#endif /* WINVER >= 0x0600 */
//
//#ifndef _UWP
//
//#define GET_SC_WPARAM(wParam) ((i32)wParam & 0xFFF0)
//
//#endif
//
///*
// * Obsolete names
// */
//#define SC_ICON         SC_MINIMIZE
//#define SC_ZOOM         SC_MAXIMIZE
//
//
//
//
//
//
//
//
//
///*
// * Static Control Constants
// */
//#define SS_LEFT             0x00000000L
//#define SS_CENTER           0x00000001L
//#define SS_RIGHT            0x00000002L
//#define SS_ICON             0x00000003L
//#define SS_BLACKRECT        0x00000004L
//#define SS_GRAYRECT         0x00000005L
//#define SS_WHITERECT        0x00000006L
//#define SS_BLACKFRAME       0x00000007L
//#define SS_GRAYFRAME        0x00000008L
//#define SS_WHITEFRAME       0x00000009L
//#define SS_USERITEM         0x0000000AL
//#define SS_SIMPLE           0x0000000BL
//#define SS_LEFTNOWORDWRAP   0x0000000CL
////#if(WINVER >= 0x0400)
//#define SS_OWNERDRAW        0x0000000DL
//#define SS_BITMAP           0x0000000EL
//#define SS_ENHMETAFILE      0x0000000FL
//#define SS_ETCHEDHORZ       0x00000010L
//#define SS_ETCHEDVERT       0x00000011L
//#define SS_ETCHEDFRAME      0x00000012L
//#define SS_TYPEMASK         0x0000001FL
////#endif /* WINVER >= 0x0400 */
////#if(WINVER >= 0x0501)
//#define SS_REALSIZECONTROL  0x00000040L
////#endif /* WINVER >= 0x0501 */
//#define SS_NOPREFIX         0x00000080L /* Don't do "&" character translation */
////#if(WINVER >= 0x0400)
//#define SS_NOTIFY           0x00000100L
//#define SS_CENTERIMAGE      0x00000200L
//#define SS_RIGHTJUST        0x00000400L
//#define SS_REALSIZEIMAGE    0x00000800L
//#define SS_SUNKEN           0x00001000L
//#define SS_EDITCONTROL      0x00002000L
//#define SS_ENDELLIPSIS      0x00004000L
//#define SS_PATHELLIPSIS     0x00008000L
//#define SS_WORDELLIPSIS     0x0000C000L
//#define SS_ELLIPSISMASK     0x0000C000L
////#endif /* WINVER >= 0x0400 */
//
//
//
//
//
//
//
//
//#define SBM_SETPOS                  0x00E0 /*not in win3.1 */
//#define SBM_GETPOS                  0x00E1 /*not in win3.1 */
//#define SBM_SETRANGE                0x00E2 /*not in win3.1 */
//#define SBM_SETRANGEREDRAW          0x00E6 /*not in win3.1 */
//#define SBM_GETRANGE                0x00E3 /*not in win3.1 */
//#define SBM_ENABLE_ARROWS           0x00E4 /*not in win3.1 */
////#if(WINVER >= 0x0400)
//#define SBM_SETSCROLLINFO           0x00E9
//#define SBM_GETSCROLLINFO           0x00EA
////#endif /* WINVER >= 0x0400 */
//
////#if(_WIN32_WINNT >= 0x0501)
//#define SBM_GETSCROLLBARINFO        0x00EB
////#endif /* _WIN32_WINNT >= 0x0501 */
//
////#if(WINVER >= 0x0400)
//#define SIF_RANGE           0x0001
//#define SIF_PAGE            0x0002
//#define SIF_POS             0x0004
//#define SIF_DISABLENOSCROLL 0x0008
//#define SIF_TRACKPOS        0x0010
//#define SIF_ALL             (SIF_RANGE | SIF_PAGE | SIF_POS | SIF_TRACKPOS)
//
//
//
//
//#define DI_MASK         0x0001
//#define DI_IMAGE        0x0002
//#define DI_NORMAL       0x0003
//#define DI_COMPAT       0x0004
//#define DI_DEFAULTSIZE  0x0008
//#if(_WIN32_WINNT >= 0x0501)
//#define DI_NOMIRROR     0x0010
//#endif /* _WIN32_WINNT >= 0x0501 */
//
//
//
//
//
//
//CLASS_DECL_APEX int_bool CopyRect(RECTANGLE_I32 * prectDest, LPCRECT32 pcrectSrc);
//CLASS_DECL_APEX int_bool PtInRect(LPCRECT32 prect, POINT32 point);
//CLASS_DECL_APEX int_bool SetRect(RECTANGLE_I32 * prect, i32 x1, i32 y1, i32 x2, i32 y2);
//CLASS_DECL_APEX int_bool SetRectEmpty(RECTANGLE_I32 * prect);
//CLASS_DECL_APEX int_bool EqualRect(LPCRECT32 prect1, LPCRECT32 prect2);
//CLASS_DECL_APEX int_bool InflateRect(RECTANGLE_I32 * prect, i32 x, i32 y);
//CLASS_DECL_APEX int_bool OffsetRect(RECTANGLE_I32 * prect, i32 x, i32 y);
//CLASS_DECL_APEX int_bool IntersectRect(RECTANGLE_I32 * prect, LPCRECT32 prect1, LPCRECT32 prect2);
////CLASS_DECL_APEX int_bool x_intersect_rect(RECTANGLE_I32 * prect, LPCRECT32 prect1, LPCRECT32 prect2);
////CLASS_DECL_APEX int_bool y_intersect_rect(RECTANGLE_I32 * prect, LPCRECT32 prect1, LPCRECT32 prect2);
//CLASS_DECL_APEX int_bool UnionRect(RECTANGLE_I32 * prect, LPCRECT32 prect1, LPCRECT32 prect2);
//CLASS_DECL_APEX int_bool SubtractRect(RECTANGLE_I32 * prect, LPCRECT32 prect1, LPCRECT32 prect2);
//
////typedef struct oswindow_data *   oswindow;
//
///*
//* Message structure
//*/
//typedef struct tagMESSAGE
//{
//   oswindow    hwnd;
//   ::u32        message;
//   WPARAM      wParam;
//   LPARAM      lParam;
//   ::u32       time;
//   POINT32       pt;
//#ifdef _MAC
//   ::u32       lPrivate;
//#endif
//} MESSAGE, *PMESSAGE, *NPMESSAGE, *LPMESSAGE;
//
//CLASS_DECL_APEX int_bool TranslateMessage(const MESSAGE * pmsg);
//CLASS_DECL_APEX LRESULT DispatchMessage(const MESSAGE * pmsg);
//
//
//
//void set_TranslateMessage(int_bool (*pfn)(const MESSAGE * lpmessage));
//void set_DispatchMessage(LRESULT (*pfn)(const MESSAGE * lpmessage));
//
//CLASS_DECL_APEX int_bool IsRectEmpty(LPCRECT32 lpcrect);
//
////#ifdef cplusplus
////
////CLASS_DECL_APEX int_bool IsRectEmpty(const ::rect & rect);
////
////#endif
//
///*
//* Button Control Styles
//*/
//#define BS_PUSHBUTTON       0x00000000L
//#define BS_DEFPUSHBUTTON    0x00000001L
//#define BS_CHECKBOX         0x00000002L
//#define BS_AUTOCHECKBOX     0x00000003L
//#define BS_RADIOBUTTON      0x00000004L
//#define BS_3STATE           0x00000005L
//#define BS_AUTO3STATE       0x00000006L
//#define BS_GROUPBOX         0x00000007L
//#define BS_USERBUTTON       0x00000008L
//#define BS_AUTORADIOBUTTON  0x00000009L
//#define BS_PUSHBOX          0x0000000AL
//#define BS_OWNERDRAW        0x0000000BL
//#define BS_TYPEMASK         0x0000000FL
//#define BS_LEFTTEXT         0x00000020L
//#if(WINVER >= 0x0400)
//#define BS_TEXT             0x00000000L
//#define BS_ICON             0x00000040L
//#define BS_BITMAP           0x00000080L
//#define BS_LEFT             0x00000100L
//#define BS_RIGHT            0x00000200L
//#define BS_CENTER           0x00000300L
//#define BS_TOP              0x00000400L
//#define BS_BOTTOM           0x00000800L
//#define BS_VCENTER          0x00000C00L
//#define BS_PUSHLIKE         0x00001000L
//#define BS_MULTILINE        0x00002000L
//#define BS_NOTIFY           0x00004000L
//#define BS_FLAT             0x00008000L
//#define BS_RIGHTBUTTON      BS_LEFTTEXT
//#endif /* WINVER >= 0x0400 */
//
///*
//* User Button Notification Codes
//*/
//#define BN_CLICKED          0
//#define BN_PAINT            1
//#define BN_HILITE           2
//#define BN_UNHILITE         3
//#define BN_DISABLE          4
//#define BN_DOUBLECLICKED    5
//#if(WINVER >= 0x0400)
//#define BN_PUSHED           BN_HILITE
//#define BN_UNPUSHED         BN_UNHILITE
//#define BN_DBLCLK           BN_DOUBLECLICKED
//#define BN_SETFOCUS         6
//#define BN_KILLFOCUS        7
//#endif /* WINVER >= 0x0400 */
//
///*
//* Button Control Messages
//*/
//#define BM_GETCHECK        0x00F0
//#define BM_SETCHECK        0x00F1
//#define BM_GETSTATE        0x00F2
//#define BM_SETSTATE        0x00F3
//#define BM_SETSTYLE        0x00F4
//#if(WINVER >= 0x0400)
//#define BM_CLICK           0x00F5
//#define BM_GETIMAGE        0x00F6
//#define BM_SETIMAGE        0x00F7
//#endif /* WINVER >= 0x0400 */
//#if(WINVER >= 0x0600)
//#define BM_SETDONTCLICK    0x00F8
//#endif /* WINVER >= 0x0600 */
//
//#if(WINVER >= 0x0400)
//#define BST_UNCHECKED      0x0000
//#define BST_CHECKED        0x0001
//#define BST_INDETERMINATE  0x0002
//#define BST_PUSHED         0x0004
//#define BST_FOCUS          0x0008
//#endif /* WINVER >= 0x0400 */
//
///*
//* Static Control Constants
//*/
//#define SS_LEFT             0x00000000L
//#define SS_CENTER           0x00000001L
//#define SS_RIGHT            0x00000002L
//#define SS_ICON             0x00000003L
//#define SS_BLACKRECT        0x00000004L
//#define SS_GRAYRECT         0x00000005L
//#define SS_WHITERECT        0x00000006L
//#define SS_BLACKFRAME       0x00000007L
//#define SS_GRAYFRAME        0x00000008L
//#define SS_WHITEFRAME       0x00000009L
//#define SS_USERITEM         0x0000000AL
//#define SS_SIMPLE           0x0000000BL
//#define SS_LEFTNOWORDWRAP   0x0000000CL
//#if(WINVER >= 0x0400)
//#define SS_OWNERDRAW        0x0000000DL
//#define SS_BITMAP           0x0000000EL
//#define SS_ENHMETAFILE      0x0000000FL
//#define SS_ETCHEDHORZ       0x00000010L
//#define SS_ETCHEDVERT       0x00000011L
//#define SS_ETCHEDFRAME      0x00000012L
//#define SS_TYPEMASK         0x0000001FL
//#endif /* WINVER >= 0x0400 */
//#if(WINVER >= 0x0501)
//#define SS_REALSIZECONTROL  0x00000040L
//#endif /* WINVER >= 0x0501 */
//#define SS_NOPREFIX         0x00000080L /* Don't do "&" character translation */
//#if(WINVER >= 0x0400)
//#define SS_NOTIFY           0x00000100L
//#define SS_CENTERIMAGE      0x00000200L
//#define SS_RIGHTJUST        0x00000400L
//#define SS_REALSIZEIMAGE    0x00000800L
//#define SS_SUNKEN           0x00001000L
//#define SS_EDITCONTROL      0x00002000L
//#define SS_ENDELLIPSIS      0x00004000L
//#define SS_PATHELLIPSIS     0x00008000L
//#define SS_WORDELLIPSIS     0x0000C000L
//#define SS_ELLIPSISMASK     0x0000C000L
//#endif /* WINVER >= 0x0400 */
