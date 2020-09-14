#pragma once



// from 7-zip

namespace acme
{

   template <class T> inline T MyMin(T a, T b)
   {
      return a < b ? a : b;
   }

   template <class T> inline T MyMax(T a, T b)
   {
      return a > b ? a : b;
   }

   template <class T> inline i32 MyCompare(T a, T b)
   {
      return a < b ? -1 : (a == b ? 0 : 1);
   }

   inline i32 BoolToInt(bool value)
   {
      return (value ? 1 : 0);
   }

   inline bool IntToBool(i32 value)
   {
      return (value != 0);
   }

} // // from 7-zip


#ifndef RC_INVOKED

#ifndef __cplusplus
#error acme requires C++ compilation (use a .cpp suffix)
#endif

#ifdef UNDER_CE
#error This version of acme is not currently supported for CE. Look for the CE specific version.
#endif


#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE         // UNICODE is used by Windows headers
#endif
#endif

#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE        // _UNICODE is used by C-runtime/acme API headers
#endif
#endif


#ifdef _WIN64
#define _SUPPORT_VT_I8  // Always support VT_I8 on Win64.
#endif

#if !defined(UNALIGNED)
#if defined(_M_IA64) || defined(_M_AMD64)
#define UNALIGNED __unaligned
#else
#define UNALIGNED
#endif
#endif

#if !defined(_countof)
#if !defined(__cplusplus) || defined(VC6)
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#else
extern "C++"
{
   template <typename _CountofType, size_t _SizeOfArray>
   char (*__countof_helper(UNALIGNED _CountofType (&_Array)[_SizeOfArray]))[_SizeOfArray];
#define _countof(_Array) sizeof(*__countof_helper(_Array))
}
#endif
#endif



/*
Why does ASSUME exist?

acme 8 has two existing validation models

ASSERT/VERIFY - These are used to make sure a debug build reports a problem with the expression/invariant
ENSURE - Debug is the same as VERIFY, retail throws a C++ exception

We added ENSURE because there were too many unreported error paths in acme and we wanted to bail out of more
error conditions rather than just trying to continue in retail.

There might be a case for changing 'lots' of ASSERT to ENSURE, but we chose an incremental approach and only
changed over where we saw a problem with code reported from a customer or test case. This reduces code churn in our
code for this version.

In general, our approach is to try to make sure that when something goes wrong
- the client does not continue to run, because we report an error condition
- debug builds see an assertion about the problem

Sometimes we have code like

HRESULT ComMethod()
{
   ASSUME(m_pFoo);
   return m_pFoo->Method();
}

We could add
   if(!m_pFoo) return E_POINTER;

But this is very unlikely to help, since it removes the ability of the developer to debug this problem if it's seen in a retail
build of the application.

We could try something more severe

   if(!m_pFoo) terminate(); // or your favourite shutdown function

This would ensure good reporting (because VC8 terminate generates a Windows Error Report and crash dump), but hardly seems a big win
over the previous crash.

ENSURE might seem slightly better. It is debuggable and consistent with acme in general. In fact, many parts of acme do just this.
But in this specific action_context, it doesn't look like a great choice. COM methods should not in general be emitting native C++ exceptions
as an error reporting strategy.

So we find ourselves in a quandry. For these kinds of methods, the traditional code (ASSERT followed by a crash), seems be the most
debuggable thing to do in this situation. At least for VS8, we have decided to stick with this shape.

---

Now consider the impact of cl /analyze. We want cl /analyze to not warn about our potential dereferences when they refer to member variables
whose state was previously validated by another method. But we do want to see the impact of function contracts on the parameters of the
function.

So we've done a broad replace of all the member-related ASSERT to ASSUME.

*/

#ifndef __analysis_assume // [
#ifdef _PREFAST_ // [
#define __analysis_assume(expr) __assume(expr)
#else // ][
#define __analysis_assume(expr)
#endif // ]
#endif // ]

#ifndef ASSUME
#if defined(VC6) || defined(VC71)
#define ASSUME(expr) (expr);
#else
#define ASSUME(expr) do { ASSERT(expr); __analysis_assume(!!(expr)); } while(0)
#endif
#endif // ASSERT

#ifndef VERIFY
#ifdef __DEBUG
#define VERIFY(expr) ASSERT(expr)
#else
#define VERIFY(expr) (expr ? void() : __throw(::exception::exception));
#endif // __DEBUG
#endif // VERIFY


#ifndef ENSURE_SUCCEEDED
#define ENSURE_SUCCEEDED(hr) ENSURE_THROW(SUCCEEDED(hr), hr)
#endif // ENSURE

/* Used inside COM methods that do not want to __throw( */
#ifndef ENSURE_RETURN_HR
#define ENSURE_RETURN_HR(expr, hr)          \
do {                                           \
   i32 __atl_condVal=!!(expr);                \
   ASSERT(__atl_condVal);                  \
   if(!(__atl_condVal)) return hr;            \
} while (0)
#endif


/* Used inside COM methods that do not want to __throw( */
#ifndef ENSURE_RETURN
#define ENSURE_RETURN(expr) ENSURE_RETURN_HR(expr, E_FAIL)
#endif






///////////////////////////////////////////////////////////////////////////////
// __declspec(novtable) is used on a class declaration to prevent the vtable
// pointer from being initialized in the constructor and destructor for the
// class.  This has many benefits because the linker can now eliminate the
// vtable and all the functions pointed to by the vtable.  Also, the actual
// constructor and destructor code are now smaller.
///////////////////////////////////////////////////////////////////////////////
// This should only be used on a class that is not directly createable but is
// rather only used as a acme class.  Additionally, the constructor and
// destructor (if provided by the ::account::user) should not call anything that may cause
// a virtual function call to occur back on the generic.
///////////////////////////////////////////////////////////////////////////////
// By default, the wizards will generate new acme generic classes with this
// attribute (through the NO_VTABLE macro).  This is normally safe as long
// the restriction mentioned above is followed.  It is always safe to remove
// this macro from your class, so if in doubt, remove it.
///////////////////////////////////////////////////////////////////////////////

#ifdef _DISABLE_NO_VTABLE
#define NO_VTABLE
#else
#define NO_VTABLE __declspec(novtable)
#endif


/*#ifdef _DISABLE_FORCEINLINE
#define FORCEINLINE
#else
#define FORCEINLINE inline
#endif*/

#if defined(_DISABLE_NOINLINE) || defined(VC6) || defined(LINUX)
#define NOINLINE
#else
#define NOINLINE __declspec( noinline )
#endif

#ifdef _DISABLE_DEPRECATED
#define DEPRECATED(_Message)
#else
#define DEPRECATED(_Message) __declspec( deprecated(_Message) )
#endif

// If 80.DLL is being used then _STATIC_REGISTRY doesn't really make sense
#ifdef _DLL
#undef _STATIC_REGISTRY
#else
// If not linking to 80.DLL, use the static registrar and not building acme.dll
#ifndef _DLL_IMPL
#ifndef _STATIC_REGISTRY
#define _STATIC_REGISTRY
#endif
#endif
#endif

#ifdef DEBUG_REFCOUNT
#ifndef DEBUG_INTERFACES
#define DEBUG_INTERFACES
#endif
#endif


#ifndef _HEAPFLAGS
#ifdef _MALLOC_ZEROINIT
#define _HEAPFLAGS HEAP_ZERO_MEMORY
#else
#define _HEAPFLAGS 0
#endif
#endif

#define API CLASS_DECL_ACME __declspec(nothrow) HRESULT __stdcall
#define API_(x)CLASS_DECL_ACME __declspec(nothrow) x __stdcall
#define APIINL API
#define APIINL_(x) API_(x)


#define offsetofclass(acme, derived) ((uptr)(static_cast<acme*>((derived*)_PACKING))-_PACKING)

/////////////////////////////////////////////////////////////////////////////
// Master version numbers

//#define _     1      // Active Template Library
#define _VER 0x0800 // Active Template Library version 8.00

/////////////////////////////////////////////////////////////////////////////
// Threading

#ifndef _SINGLE_THREADED
#ifndef _APARTMENT_THREADED
#ifndef _FREE_THREADED
#define _FREE_THREADED
#endif
#endif
#endif

// UUIDOF
#ifndef _NO_UUIDOF
#define _IIDOF(x) __uuidof(x)
#else
#define _IIDOF(x) IID_##x
#endif

// Lean and mean
#ifndef NO_LEAN_AND_MEAN
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMCX
#define NOMCX
#endif
#endif   // NO_LEAN_AND_MEAN

#ifdef NOSERVICE
#ifndef _NO_SERVICE
#define _NO_SERVICE
#endif   // _NO_SERVICE
#else
#ifdef _NO_SERVICE
#ifndef NOSERVICE
#define NOSERVICE
#endif   // NOSERVICE
#endif   // _NO_SERVICE
#endif   // NOSERVICE


#endif // RC_INVOKED

#define AXWIN_CLASS   "ca_AxWin80"
#define AXWINLIC_CLASS "ca_AxWinLic80"

// _INSECURE_DEPRECATE define
#ifndef _INSECURE_DEPRECATE
#if defined(_SECURE_NO_DEPRECATE) || defined(VC6) || defined(VC71)
#define _INSECURE_DEPRECATE(_Message)
#else
#define _INSECURE_DEPRECATE(_Message) __declspec(deprecated(_Message))
#endif // _SECURE_NO_DEPRECATE
#endif // _INSECURE_DEPRECATE

/*
This is called when something really bad happens -- so bad
that we consider it dangerous to even __throw( an exception
*/
#ifndef _FATAL_SHUTDOWN
#define _FATAL_SHUTDOWN do { ::TerminateProcess(::GetCurrentProcess(), 0); } while(0);
#endif

//acme/ API code should use standard pointer to member standard syntax &MyClass::MyMethod, instead
//of the legacy non-standard syntax - MyMethod.
#ifdef _ENABLE_PTM_WARNING
#define PTM_WARNING_DISABLE
#define PTM_WARNING_RESTORE
#else
#define PTM_WARNING_DISABLE \
   __pragma(warning( push )) \
   __pragma(warning( disable : 4867 ))
#define PTM_WARNING_RESTORE \
   __pragma(warning( pop ))
#endif //_ENABLE_PTM_WARNING

/* we have to define our own versions of MAKEINTRESOURCE and IS_INTRESOURCE to
 * fix warning 6268. At least until those macros are not cleanend in PSDK.
   Same comes true for those definitions of constants which use the above macros
*/
#ifndef WINDOWS
#define MAKEINTRESOURCEA(i) ((char *)((uptr)((WORD)(i))))
#define MAKEINTRESOURCEW(i) ((unichar *)((uptr)((WORD)(i))))
#endif
#ifdef UNICODE
#define MAKEINTRESOURCE  MAKEINTRESOURCEW
#else
#define MAKEINTRESOURCE  MAKEINTRESOURCEA
#endif // !UNICODE
#ifndef WINDOWS
#define IS_INTRESOURCE(_r) ((((uptr)(_r)) >> 16) == 0)
#endif

/*
 * Predefined Resource Types
 */
#define RT_CURSOR           MAKEINTRESOURCE(1)
#define RT_BITMAP           MAKEINTRESOURCE(2)
#define RT_ICON             MAKEINTRESOURCE(3)
#define RT_MENU             MAKEINTRESOURCE(4)
#define RT_DIALOG           MAKEINTRESOURCE(5)
#define RT_STRING           MAKEINTRESOURCE(6)
#define RT_FONTDIR          MAKEINTRESOURCE(7)
#define RT_FONT             MAKEINTRESOURCE(8)
#define RT_ACCELERATOR      MAKEINTRESOURCE(9)
#define RT_RCDATA           MAKEINTRESOURCE(10)
#define RT_MESSAGETABLE     MAKEINTRESOURCE(11)

#define DIFFERENCE     11
//#define RT_GROUP_CURSOR MAKEINTRESOURCE((uptr)RT_CURSOR + DIFFERENCE)
//#define RT_GROUP_ICON   MAKEINTRESOURCE((uptr)RT_ICON + DIFFERENCE)
#define RT_VERSION      MAKEINTRESOURCE(16)
#define RT_DLGINCLUDE   MAKEINTRESOURCE(17)
#if(WINVER >= 0x0400)
#define RT_PLUGPLAY     MAKEINTRESOURCE(19)
#define RT_VXD          MAKEINTRESOURCE(20)
#define RT_ANICURSOR    MAKEINTRESOURCE(21)
#define RT_ANIICON      MAKEINTRESOURCE(22)
#endif /* WINVER >= 0x0400 */
#define RT_HTML         MAKEINTRESOURCE(23)
#ifdef RC_INVOKED
#define RT_MANIFEST                        24
#define CREATEPROCESS_MANIFEST_RESOURCE_ID  1
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID 2
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID 3
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID 1   /* inclusive */
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID 16  /* inclusive */
#else  /* RC_INVOKED */
#define RT_MANIFEST                        MAKEINTRESOURCE(24)
#define CREATEPROCESS_MANIFEST_RESOURCE_ID MAKEINTRESOURCE( 1)
#define ISOLATIONAWARE_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(2)
#define ISOLATIONAWARE_NOSTATICIMPORT_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(3)
#define MINIMUM_RESERVED_MANIFEST_RESOURCE_ID MAKEINTRESOURCE( 1 /*inclusive*/)
#define MAXIMUM_RESERVED_MANIFEST_RESOURCE_ID MAKEINTRESOURCE(16 /*inclusive*/)
#endif /* RC_INVOKED */

/* sal.h stuff that is not in the current LKG */
#ifndef __out_ecount_part_z
#define __out_ecount_part_z(size,length)                        __out_ecount_part(size,length) __post __nullterminated
#endif

#ifndef __out_ecount_part_z_opt
#define __out_ecount_part_z_opt(size,length)                    __out_ecount_part_opt(size,length) __post __nullterminated
#endif

#ifndef __deref_opt_out_z
#define __deref_opt_out_z                                       __deref_opt_out __post __deref __nullterminated
#endif

#ifndef __out_bcount_part_z
#define __out_bcount_part_z(size,length)                        __out_bcount_part(size,length) __post __nullterminated
#endif






enum EExclusiveInstance
{

   ExclusiveInstanceNone,
   ExclusiveInstanceLocal,
   ExclusiveInstanceLocalId,
   ExclusiveInstanceGlobal,
   ExclusiveInstanceGlobalId,
   ExclusiveInstanceLicense

};


