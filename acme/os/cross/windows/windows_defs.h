#pragma once


#define WINE_NO_UNICODE_MACROS
#define WINE_UNICODE_NATIVE
#define _WCTYPE_T_DEFINED


#ifdef WINE_NO_UNICODE_MACROS
# define DECL_WINELIB_TYPE_AW(type)  /* nothing */
#else
# define DECL_WINELIB_TYPE_AW(type)  typedef WINELIB_NAME_AW(type) type;
#endif



#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif /* NO_STRICT */

// Win32 defines _WIN32 automatically,
// but Macintosh doesn't, so if we are using
// Win32 Functions, we must do it here

#ifdef __cplusplus
extern "C" {
#endif


/*
 * AXISTYPES is defined in ntdef.h if these types are already defined
 */


//#define MAX_PATH          260

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef OPTIONAL
#define OPTIONAL
#endif

#undef far
#undef near
#undef pascal

#define far
#define near
#if (!defined(_MAC)) && ((_MSC_VER >= 800) || defined(_STDcaLL_SUPPORTED))
#define pascal __stdcall
#else
#define pascal
#endif

#if defined(DOSWIN32) || defined(_MAC)
#define cdecl _cdecl
#ifndef CDECL
#define CDECL _cdecl
#endif
#else
#define cdecl
#ifndef CDECL
#define CDECL
#endif
#endif

#ifdef _MAC
#define CALLBACK    PASCAL
#define WINAPI      CDECL
#define WINAPIV     CDECL
#define APIENTRY    WINAPI
#define APIPRIVATE  CDECL
#ifdef _68K_
#define PASCAL      __pascal
#else
#define PASCAL
#endif
#elif (_MSC_VER >= 800) || defined(_STDcaLL_SUPPORTED)
#define CALLBACK    __stdcall
#define WINAPI      __stdcall
#define WINAPIV     __cdecl
#define APIENTRY    WINAPI
#define APIPRIVATE  __stdcall
#define PASCAL      __stdcall
#else
#define CALLBACK
#define WINAPI
#define WINAPIV
#define APIENTRY    WINAPI
#define APIPRIVATE
//#define PASCAL      pascal
#define PASCAL      pascal
#endif

#ifdef _M_CEE_PURE
#define WINAPI_INLINE  __clrcall
#else
#define WINAPI_INLINE  WINAPI
#endif


typedef unsigned int        u32;
typedef unsigned char       byte;
typedef unsigned short      u16;
typedef float               FLOAT;
typedef FLOAT *             PFLOAT;
typedef int_bool near *     PBOOL;
typedef int_bool far *      LPBOOL;
typedef byte near *         PBYTE;
typedef byte far *          LPBYTE;
typedef i32 near *          PINT;
typedef i32 far *           LPINT;
typedef ::u16 near *        PWORD;
typedef ::u16 far *         LPWORD;
typedef i32 far *           LPLONG;
typedef ::u32 near *        PDWORD;
typedef ::u32 far *         LPDWORD;
typedef void far *          LPVOID;
typedef const void far *    LPCVOID;


typedef i32                 INT;
typedef u32                 UINT;
typedef u32 *               PUINT;


typedef struct win_handle * HANDLE;

typedef HANDLE * LPHANDLE, * PHANDLE;


#if !defined(NT_INCLUDED)
#include "windows_nt.h"
#endif /* NT_INCLUDED */

// xxx #include <specstrings.h>





#ifndef WIN_INTERNAL
//DECLARE_HANDLE            (oswindow);
//DECLARE_HANDLE            (HHOOK);
#ifdef WINABLE
//DECLARE_HANDLE            (HEVENT);
#endif
#endif

typedef ::u16                ATOM;

/*typedef HANDLE          *SPHANDLE;
typedef HANDLE           *LPHANDLE;
typedef HANDLE              HGLOBAL;
typedef HANDLE              HLOcaL;
typedef HANDLE              GLOBALHANDLE;
typedef HANDLE              LOcaLHANDLE;*/
#ifndef _MANAGED
#ifndef _MAC
#ifdef OS64BIT
typedef iptr (WINAPI *FARPROC)(void);
typedef iptr (WINAPI *NEARPROC)(void);
typedef iptr (WINAPI *PROC)(void);
#else
typedef i32 (WINAPI *FARPROC)(void);
typedef i32 (WINAPI *NEARPROC)(void);
typedef i32 (WINAPI *PROC)(void);
#endif  // OS64BIT
#else
typedef i32 (CALLBACK *FARPROC)(void);
typedef i32 (CALLBACK *NEARPROC)(void);
typedef i32 (CALLBACK *PROC)(void);
#endif
#else
typedef iptr (WINAPI *FARPROC)(void);
typedef iptr (WINAPI *NEARPROC)(void);
typedef iptr (WINAPI *PROC)(void);
#endif


DECLARE_HANDLE(HINSTANCE);
typedef HINSTANCE HMODULE;

typedef ::u32   color32_t;
typedef ::u32   *LPCOLORREF;

#define HFILE_ERROR ((HFILE)-1)


typedef struct _RECTL       /* rcl */
{
   ::i32    left;
   ::i32    top;
   ::i32    right;
   ::i32    bottom;
} RECTL, *PRECTL, *LPRECTL;

typedef const RECTL * LPCRECTL;

/*typedef struct tagPOINT
{
    ::i32  x;
    ::i32  y;
} POINT32, *PPOINT, *NPPOINT, *POINT32 *;*/

typedef struct _POINTL      /* ptl  */
{
   ::i32  x;
   ::i32  y;
} POINTL, *PPOINTL;

//typedef struct tagSIZE
//{
//   ::i32        cx;
//   ::i32        cy;
//} SIZE32, *PSIZE, *LPSIZE32;

typedef SIZE32               SIZEL;
typedef SIZE32               *PSIZEL, *LPSIZE32L;

typedef struct tagPOINTS
{
#ifndef _MAC
   SHORT   x;
   SHORT   y;
#else
   SHORT   y;
   SHORT   x;
#endif
} POINTS, *PPOINTS, *POINT32S;

//
//  File System time stamps are represented with the following structure:
//

typedef struct _FILETIME
{
   ::u32 dwLowDateTime;
   ::u32 dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#define _FILETIME_


/* mode selections for the device mode function */
#define DM_UPDATE           1
#define DM_COPY             2
#define DM_PROMPT           4
#define DM_MODIFY           8

#define DM_IN_BUFFER        DM_MODIFY
#define DM_IN_PROMPT        DM_PROMPT
#define DM_OUT_BUFFER       DM_COPY
#define DM_OUT_DEFAULT      DM_UPDATE

/* device capabilities indices */
#define DC_FIELDS           1
#define DC_PAPERS           2
#define DC_PAPERSIZE        3
#define DC_MINEXTENT        4
#define DC_MAXEXTENT        5
#define DC_BINS             6
#define DC_DUPLEX           7
#define DC_SIZE             8
#define DC_EXTRA            9
#define DC_VERSION          10
#define DC_DRIVER           11
#define DC_BINNAMES         12
#define DC_ENUMRESOLUTIONS  13
#define DC_FILEDEPENDENCIES 14
#define DC_TRUETYPE         15
#define DC_PAPERNAMES       16
#define DC_ORIENTATION      17
#define DC_COPIES           18

#ifdef __cplusplus
}
#endif

//typedef void * HGLOBAL;








//#define MAX_PATH          260

#define near
#define far
#define const const



struct tagHandle
{

   void * m_p;

};

//typedef struct tagHandle * HANDLE;


///typedef u32       ::u32;
//typedef i32                 int_bool;
//typedef unsigned char       byte;
//typedef unsigned short      ::u16;
//typedef float               FLOAT;
//typedef FLOAT               *PFLOAT;
//typedef int_bool near           *PBOOL;
//typedef int_bool far            *int_bool *;
//typedef byte near           *PBYTE;
//typedef byte far            *LPBYTE;
//typedef i32 near            *PINT;
//typedef i32 far             *LPINT;
//typedef ::u16 near           *PWORD;
//typedef ::u16 far            *LPWORD;
//typedef i32 far            *LPLONG;
//typedef ::u32 near          *PDWORD;
//typedef ::u32 far           *LPDWORD;
//typedef void far            *LPVOID;
//typedef const void far      *const void *;

//typedef i32                 ::i32;
//typedef u32        ::u32;
//typedef u32        *P::u32;



#define HFILE_ERROR ((HFILE)-1)



//typedef void * LPVOID;
//typedef const void * const void *;

//typedef const char * const char *;
typedef const char * LPCTSTR;
//typedef char * char *;
//typedef char * LPCSTR;



//
// Basics
//

#ifndef VOID
#define VOID void
typedef char char;
typedef short SHORT;
typedef i32 ::i32;
typedef i32 ::i32;
#endif

//
// UNICODE (Wide Character) types
//

#ifndef _MAC
//typedef unichar WCHAR;    // wc,   16-bit UNICODE character
#else
// some Macintosh compilers don't define unichar in a convenient location, or define it as a char
typedef unsigned short WCHAR;    // wc,   16-bit UNICODE character
#endif




//////typedef WCHAR *PWCHAR, *LPWCH, *PWCH;
//typedef const WCHAR *LPCWCH, *PCWCH;

// null terminated
//typedef  WCHAR *NWPSTR, *LPWSTR, *PWSTR;
typedef  PWSTR *PZPWSTR;
typedef  const PWSTR *PCZPWSTR;
typedef  WCHAR UNALIGNED *LPUWSTR, *PUWSTR;
//typedef  const WCHAR *const widechar *, *PCWSTR;
typedef  PCWSTR *PZPCWSTR;
typedef  const WCHAR UNALIGNED *LPCUWSTR, *PCUWSTR;

// null null terminated
typedef  WCHAR *PZZWSTR;
typedef  const WCHAR *PCZZWSTR;
typedef  WCHAR UNALIGNED *PUZZWSTR;
typedef  const WCHAR UNALIGNED *PCUZZWSTR;

// __possibly_notnullterminated
typedef  WCHAR *PNZWCH;
typedef  const WCHAR *PCNZWCH;
typedef  WCHAR UNALIGNED *PUNZWCH;
typedef  const WCHAR UNALIGNED *PCUNZWCH;
//
// ANSI (Multi-byte Character) types
//
//typedef char *PCHAR, *LPCH, *PCH;
//typedef const char *LPCCH, *PCCH;

//typedef  char *NPSTR, *char *, *PSTR;
typedef  PSTR *PZPSTR;
typedef  const PSTR *PCZPSTR;
//typedef  const char *const char *, *PCSTR;
typedef  PCSTR *PZPCSTR;

typedef  char *PZZSTR;
typedef  const char *PCZZSTR;

typedef  char *PNZCH;
typedef  const char *PCNZCH;



//#ifndef _TCHAR_DEFINED
//typedef char TCHAR, *PTCHAR;
//typedef unsigned char TBYTE, *PTBYTE ;
//#define _TCHAR_DEFINED
//#endif /* !_TCHAR_DEFINED */

typedef LPCH LPTCH, PTCH;
typedef LPCCH LPCTCH, PCTCH;
//typedef char * PTSTR, char *, PUTSTR, LPUTSTR;
//typedef const char * PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
typedef PZZSTR PZZTSTR, PUZZTSTR;
typedef PCZZSTR PCZZTSTR, PCUZZTSTR;
typedef PNZCH PNZTCH, PUNZTCH;
typedef PCNZCH PCNZTCH, PCUNZTCH;

#define TEXT(quote) __TEXT(quote)   // r_winnt


//typedef SHORT *PSHORT;
//typedef ::i32 *PLONG;


//typedef void *HINSTANCE;

#ifndef GUID_DEFINED
#define GUID_DEFINED
#if defined(__midl)
typedef struct
{
   unsigned long  Data1;
   unsigned short Data2;
   unsigned short Data3;
   byte           Data4[ 8 ];
} GUID;
#else
typedef struct _GUID
{
   u32   Data1;
   u16   Data2;
   u16   Data3;
   u8    Data4[ 8 ];
} GUID;
#endif
#endif


//#define APIENTRY

#define WINAPI





#define DECLSPEC_NO_RETURN
void RaiseException(::u32 dwExceptionCode, ::u32 dwExceptionFlags, ::u32 nNumberOfArguments, const ulong_ptr *lpArguments);
typedef i32 errno_t;


#ifdef __cplusplus
#define MY_EXTERN_C extern "C"
#else
#define MY_EXTERN_C extern
#endif


//MY_EXTERN_C ::u32 get_last_error(void);
//MY_EXTERN_C void set_last_error(::u32 dw);


/*#define MAKEWORD(a, b)      ((::u16)(((byte)(((DWORD_PTR)(a)) & 0xff)) | ((::u16)((byte)(((DWORD_PTR)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((::i32)(((::u16)(((DWORD_PTR)(a)) & 0xffff)) | ((::u32)((::u16)(((DWORD_PTR)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((::u16)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l)           ((::u16)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((byte)(((DWORD_PTR)(w)) & 0xff))
#define HIBYTE(w)           ((byte)((((DWORD_PTR)(w)) >> 8) & 0xff))*/

#define MAKEWPARAM(l, h)      ((WPARAM)(::u32)MAKELONG(l, h))
#define MAKELPARAM(l, h)      ((LPARAM)(::u32)MAKELONG(l, h))
#define MAKELRESULT(l, h)     ((LRESULT)(::u32)MAKELONG(l, h))









#define _T(psz) psz


//#define c_cdecl __cdecl

//#define c_decl __cdecl



/*
typedef char char;
typedef uchar WINUCHAR;

#undef byte
typedef uchar byte;

typedef i16 SHORT;
typedef u16 WINUSHORT;

#undef ::u16
typedef u16 ::u16;*/
typedef i16 VARIANT_BOOL;
/*
typedef i32 ::i32;
typedef i32 INT32;
typedef u32 ::u32;
typedef u32 ::u32;
#ifndef _UWP
typedef INT32 ::i32;   // ::i32, WINULONG and u32 must be 32-bit
#endif
//typedef ::u32 WINULONG;

#ifndef _UWP
#undef u32
typedef ::u32 u32;
#endif
//typedef i64 ::i64;
//typedef u64 ULONGLONG;

#ifndef _UWP
typedef const char *const char *;
typedef char TCHAR;
#endif
typedef const TCHAR *LPCTSTR;
typedef unichar WCHAR;
typedef const WCHAR *const widechar *;
*/
typedef WCHAR OLECHAR;
typedef OLECHAR *BSTR;
typedef const OLECHAR *LPCOLESTR;
typedef OLECHAR *LPOLESTR;

/*typedef struct _FILETIME
{
  u32 dwLowDateTime;
  u32 dwHighDateTime;
}FILETIME;*/

//#define HRESULT ::i32
//#define FAILED(Status) ((HRESULT)(Status)<0)
typedef WINULONG PROPID;
typedef ::i32 SCODE;

/*#define S_OK    ((HRESULT)0x00000000L)
#define S_FALSE ((HRESULT)0x00000001L)
#define E_NOTIMPL ((HRESULT)0x80004001L)
#define E_NOINTERFACE ((HRESULT)0x80004002L)
#define E_ABORT ((HRESULT)0x80004004L)
#define E_FAIL ((HRESULT)0x80004005L)
#define STG_E_INVALIDFUNCTION ((HRESULT)0x80030001L)
#define E_OUTOFMEMORY ((HRESULT)0x8007000EL)
#define E_INVALIDARG ((HRESULT)0x80070057L)
*/


#ifndef _UWP
#define STDMETHOD_(t, f) virtual t STDMETHODCALLTYPE f
#define STDMETHOD(f) STDMETHOD_(HRESULT, f)
#define STDMETHODIMP_(type) type STDMETHODCALLTYPE
#define PURE = 0
#define MIDL_INTERFACE(x) struct
#endif


#ifdef __cplusplus

//#ifndef _UWP
//
//DEFINE_GUID(IID_IUnknown,
//0x00000000, 0x0000, 0x0000, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);
//struct IUnknown
//{
//  STDMETHOD(QueryInterface) (REFIID iid, void **outObject) PURE;
//  STDMETHOD_(WINULONG, AddRef)() PURE;
//  STDMETHOD_(WINULONG, Release)() PURE;
//  #ifndef _WIN32
//  virtual ~IUnknown() {}
//  #endif
//};
//
//typedef IUnknown *LPUNKNOWN;
//
//#endif
//
#endif

#define VARIANT_TRUE ((VARIANT_BOOL)-1)
#define VARIANT_FALSE ((VARIANT_BOOL)0)

#ifndef _UWP

enum VARENUM
{
   VT_EMPTY = 0,
   VT_NULL = 1,
   VT_I2 = 2,
   VT_I4 = 3,
   VT_R4 = 4,
   VT_R8 = 5,
   VT_CY = 6,
   VT_DATE = 7,
   VT_BSTR = 8,
   VT_DISPATCH = 9,
   VT_ERROR = 10,
   VT_BOOL = 11,
   VT_VARIANT = 12,
   VT_UNKNOWN = 13,
   VT_DECIMAL = 14,
   VT_I1 = 16,
   VT_UI1 = 17,
   VT_UI2 = 18,
   VT_UI4 = 19,
   VT_I8 = 20,
   VT_UI8 = 21,
   VT_INT = 22,
   VT_UINT = 23,
   VT_VOID = 24,
   VT_HRESULT = 25,
   VT_FILETIME = 64
};
#endif
typedef u16 VARTYPE;
typedef ::u16 PROPVAR_PAD1;
typedef ::u16 PROPVAR_PAD2;
typedef ::u16 PROPVAR_PAD3;

#ifdef __cplusplus

#ifndef _UWP

typedef struct tagPROPVARIANT
{
   VARTYPE vt;
   PROPVAR_PAD1 wReserved1;
   PROPVAR_PAD2 wReserved2;
   PROPVAR_PAD3 wReserved3;
   union
   {
      char cVal;
      WINUCHAR bVal;
      SHORT iVal;
      WINUSHORT uiVal;
      ::i32 lVal;
      WINULONG ulVal;
      ::i32 intVal;
      ::u32 untVal;
      LARGE_INTEGER hVal;
      ULARGE_INTEGER updateVal;
      VARIANT_BOOL boolVal;
      SCODE scode;
      FILETIME filetime;
      BSTR bstrVal;
   };
} PROPVARIANT;


typedef PROPVARIANT tagVARIANT;
typedef tagVARIANT VARIANT;
typedef VARIANT VARIANTARG;

MY_EXTERN_C HRESULT VariantClear(VARIANTARG *prop);
MY_EXTERN_C HRESULT VariantCopy(VARIANTARG *dest, VARIANTARG *src);
#endif

#endif

#ifndef WINDOWS
MY_EXTERN_C BSTR SysAllocStringByteLen(const char * psz, ::u32 len);
MY_EXTERN_C BSTR SysAllocString(const OLECHAR *sz);
MY_EXTERN_C void SysFreeString(BSTR bstr);
MY_EXTERN_C ::u32 SysStringByteLen(BSTR bstr);
MY_EXTERN_C ::u32 SysStringLen(BSTR bstr);


MY_EXTERN_C u32 get_last_error(void);
MY_EXTERN_C ::i32 CompareFileTime(const FILETIME* ft1, const FILETIME* ft2);


#define CP_ACP    0
#define CP_OEMCP  1


typedef enum tagSTREAM_SEEK
{
   STREAM_SEEK_SET = 0,
   STREAM_SEEK_CUR = 1,
   STREAM_SEEK_END = 2
} STREAM_SEEK;

#endif // defined(_UWP)





struct win_handle;


#ifdef __cplusplus

struct win_handle
{

   enum enum_type
   {

      type_file,
      type_thread

   };

   enum_type m_etype;


   struct file
   {


      FILE * m_pfile;


   };



   union
   {


      file     m_file;
      void *   m_thread;


   };



};

#endif




VARIANT_BOOL BoolToVARIANT_BOOL(int_bool v);
int_bool VARIANT_BOOLToBool(VARIANT_BOOL v);


//#define INVALID_HSYNC_VALUE ((::sync *) nullptr)

class sync;

typedef ::sync * HSYNC;



