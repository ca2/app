#pragma once



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

But this is very unlikely to help, since it erases the ability of the developer to debug this problem if it's seen in a retail
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
#define VERIFY(expr) (expr ? void() : throw ::exception());
#endif // __DEBUG
#endif // VERIFY


#ifndef ENSURE_SUCCEEDED
#define ENSURE_SUCCEEDED(hr) ENSURE_THROW(SUCCEEDED(hr), hr)
#endif // ENSURE

/* Used inside COM methods that do not want to throw ::exception( */
#ifndef ENSURE_RETURN_HR
#define ENSURE_RETURN_HR(expr, hr)          \
do {                                           \
   i32 __atl_condVal=!!(expr);                \
   ASSERT(__atl_condVal);                  \
   if(!(__atl_condVal)) return hr;            \
} while (0)
#endif


/* Used inside COM methods that do not want to throw ::exception( */
#ifndef ENSURE_RETURN
#define ENSURE_RETURN(expr) ENSURE_RETURN_HR(expr, E_FAIL)
#endif




//#include "acme/networking/sockets/trace_interface.h"


CLASS_DECL_ACME void __trace(enum_trace_level elevel, const ::scoped_string & scopedstrTag, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrFile = nullptr, int iLine = -1);


#define _DEBUG_WIDE_(s) L ## s
#define _DEBUG_WIDE(s) _DEBUG_WIDE_(s)

#define _NORMAL_BLOCK 1


CLASS_DECL_ACME i32 DECL_C debug_report(
i32 _ReportType,
const char * _Filename,
i32 _LineNumber,
const char * _ModuleName,
const char * _Format,
...);


CLASS_DECL_ACME i32 DECL_C debug_report(
i32 _ReportType,
const wchar_t * _Filename,
i32 _LineNumber,
const wchar_t * _ModuleName,
const wchar_t * _Format,
...);


//////////////////////////////////////////////////////////////////////////////////
//
//    Debug Reporting
//
typedef void * _HFILE; /* file handle pointer */

#define _DEBUG_WARN           0
#define _DEBUG_ERROR          1
#define _DEBUG_ASSERT         2
#define _DEBUG_ERRCNT         3

#define _DEBUG_MODE_FILE      0x1
#define _DEBUG_MODE_DEBUG     0x2
#define _DEBUG_MODE_WNDW      0x4
#define _DEBUG_REPORT_MODE    -1

#ifndef WINDOWS

#if defined(_M_IX86)
#define _DEBUG_INVALID_HFILE ((_HFILE)-1)
#define _DEBUG_HFILE_ERROR   ((_HFILE)-2)
#define _DEBUG_FILE_STDOUT   ((_HFILE)-4)
#define _DEBUG_FILE_STDERR   ((_HFILE)-5)
#define _DEBUG_REPORT_FILE   ((_HFILE)-6)
#else
#define _DEBUG_INVALID_HFILE ((_HFILE)(i64)-1)
#define _DEBUG_HFILE_ERROR   ((_HFILE)(i64)-2)
#define _DEBUG_FILE_STDOUT   ((_HFILE)(i64)-4)
#define _DEBUG_FILE_STDERR   ((_HFILE)(i64)-5)
#define _DEBUG_REPORT_FILE   ((_HFILE)(i64)-6)
#endif

#endif


#define _DEBUG_RPTHOOK_INSTALL  0
#define _DEBUG_RPTHOOK_REMOVE   1


#define _DEBUG_ALLOC_MEM_DF        0x01  /* Turn on debug allocation */
#define _DEBUG_DELAY_FREE_MEM_DF   0x02  /* Don't actually free memory */
#define _DEBUG_CHECK_ALWAYS_DF     0x04  /* Check heap every alloc/dealloc */
#define _DEBUG_RESERVED_DF         0x08  /* Reserved - do not use */
#define _DEBUG_CHECK_DEBUG_DF      0x10  /* Leak check/diff __DEBUG blocks */
#define _DEBUG_LEAK_CHECK_DF       0x20  /* Leak check at program exit */

/*
 * Some bit values for _crtDbgFlag which correspond to frequencies for checking
 * the the heap.
 */
#define _DEBUG_CHECK_EVERY_16_DF   0x00100000  /* check heap every 16 heap ops */
#define _DEBUG_CHECK_EVERY_128_DF  0x00800000  /* check heap every 128 heap ops */
#define _DEBUG_CHECK_EVERY_1024_DF 0x04000000  /* check heap every 1024 heap ops */
/*
We do not check the heap by default at this point_i32 because the cost was too high
for some applications. You can still turn this feature on manually.
 */
#define _DEBUG_CHECK_DEFAULT_DF    0

#define _DEBUG_REPORT_FLAG         -1    /* Query bitflag status */

#define _BLOCK_TYPE(block)          (block & 0xFFFF)
#define _BLOCK_SUBTYPE(block)       (block >> 16 & 0xFFFF)


/****************************************************************************
 *
 * Memory state
 *
 ***************************************************************************/

/* Memory block identification */
#define _FREE_BLOCK      0
#define _NORMAL_BLOCK    1
#define _DEBUG_BLOCK       2
#define _IGNORE_BLOCK    3
#define _CLIENT_BLOCK    4
#define _MAX_BLOCKS      5



struct MEMORY_BLOCK_HEADER;

typedef struct _MEMORY_STATE
{

   struct MEMORY_BLOCK_HEADER * pBlockHeader;
   size_t lCounts[_MAX_BLOCKS];
   size_t lSizes[_MAX_BLOCKS];
   size_t lHighWaterCount;
   size_t lTotalCount;

} MEMORY_STATE;


/****************************************************************************
 *
 * Declarations, prototype and function-like macros
 *
 ***************************************************************************/

/* _STATIC_ASSERT is for enforcing tristate/integral conditions at compile time.
   Since it is purely a compile-time mechanism that generates no code, the check
   is left in even if __DEBUG is not defined. */

#ifndef _STATIC_ASSERT
#define _STATIC_ASSERT(expr) typedef char __static_assert_t[ (expr) ]
#endif

#ifndef __DEBUG

////////////////////////////////////////////////////////////////////////////////////
//
//    Debug OFF


////////////////////////////////////////////////////////////////////////////////////
//
//  We allow our basic _ASSERT macros to be overridden by pre-existing definitions.
//    This is not the ideal mechanism, but is helpful in some scenarios and helps avoid
//    multiple definition problems

#ifndef _ASSERT
#define _ASSERT(expr) ((void)0)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr) ((void)0)
#endif

#ifndef _ASSERT_EXPR
#define _ASSERT_EXPR(expr, expr_str) (()0)
#endif

//
//  __DEBUG Off
//
/////////////////////////////


#elif !defined(__MDEBUG) && !defined(__VLD)


/////////////////////////////
//
//  __DEBUG ON
//


///////////////////////////////////////////////////////////////
//
//    Asserts
//    We use !! below to ensure that any overloaded operators used to evaluate expr do not end up at operator ||
//
#undef _ASSERT_EXPR
#define _ASSERT_EXPR(expr, msg) \
        (void) ((!!(expr)) || \
                (1 != debug_report(_DEBUG_ASSERT, _DEBUG_WIDE(__FILE__), __LINE__, nullptr, msg)) || \
                (debug_break(), 0))


#ifndef _ASSERT
#define _ASSERT(expr)   _ASSERT_EXPR((expr), nullptr)
#endif

#ifndef _ASSERTE
#define _ASSERTE(expr)  _ASSERT_EXPR((expr), _T("##expr##"))
#endif




#endif



// CLASS_DECL_ACME i32 FUNCTION_DEBUGBOX(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, i32 iFlags);

// CLASS_DECL_ACME i32 FUNCTION_DEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, i32 iFlags);

// inline i32 FUNCTION_XXDEBUGBOX(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, i32 iFlags)
// {

//    __UNREFERENCED_PARAMETER(pszMessage);
//    __UNREFERENCED_PARAMETER(pszTitle);
//    __UNREFERENCED_PARAMETER(iFlags);

//    return 0;

// }

// inline i32 FUNCTION_XXDEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, i32 iFlags)
// {

//    __UNREFERENCED_PARAMETER(pszMessage);
//    __UNREFERENCED_PARAMETER(pszTitle);
//    __UNREFERENCED_PARAMETER(iFlags);

//    return 0;

// }

//#define debug_box FUNCTION_DEBUGBOX
//#define xxdebug_box FUNCTION_XXDEBUGBOX

// Use!!
// #include "acme/inline/set_xxdebug_box.inl"
// and
// #include "acme/inline/clear_xxdebug_box.inl"




//void CLASS_DECL_ACME TRACELASTERROR();//



//CLASS_DECL_ACME string FormatMessageFromSystem(u32 dwError);






//class CLASS_DECL_ACME trace_interface //:
////   virtual public ::sockets::trace_interface
//{
//public:
//
//
//
//   //virtual void sockets_trace(::sockets::base_socket_handler * phandler, ::sockets::base_socket * psocket, enum_trace_level elevel, const ::string & strContext, i32 iError, const ::string & strContext) override;
//   //virtual void sockets_trace(::sockets::base_socket_handler * phandler, ::sockets::base_socket * psocket, enum_trace_level elevel, const ::string & strContext, i32 iError, const ::string & strContext) override;
//
//
//};


//extern critical_section * g_pcsTrace;
//extern matter * g_pobjecTracer;
//
CLASS_DECL_ACME void os_trace(enum_trace_level elevel, const ::scoped_string & scopedstrTag, const ::scoped_string & scopedstrMessage);
//CLASS_DECL_ACME void trace(enum_trace_level elevel, const ::scoped_string & scopedstrTag, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrFile = nullptr, int iLine = -1);







//#define LOG(level, tag) ::text_stream_log_line(level, tag, __FILE__, __LINE__)



//#define cinfo LOG(e_trace_level_information, LOG_TAG)
//#define cwarn LOG(e_trace_level_warning, LOG_TAG)
//#define cerror LOG(e_trace_level_error, LOG_TAG)
//#define cfatal LOG(e_trace_level_fatal, LOG_TAG)


//#define thisinfo LOG(e_trace_level_information, LOG_THIS_TAG) << LOG_MEMBER_PREFIX << "; "
//#define thiswarn LOG(e_trace_level_warning, LOG_THIS_TAG)  << LOG_MEMBER_PREFIX << "; "
//#define thiserr LOG(e_trace_level_error, LOG_THIS_TAG) << LOG_MEMBER_PREFIX << "; "
//#define thisfatal LOG(e_trace_level_fatal, LOG_THIS_TAG) << LOG_MEMBER_PREFIX << "; "

//#define thisstart thisinfo << "start "
//#define thisexit thisinfo << "exit " << str_flag_ifnumberparenthesizeandspace
//#define thisok thisinfo << "ok " << str_flag_ifnumberparenthesizeandspace
//#define thisexc thiserr << "exception " << str_flag_ifnumberparenthesizeandspace
//#define thisexcall thiserr << "exception(...) " << str_flag_ifnumberparenthesizeandspace
//#define thisfail thiserr << "failure " << str_flag_ifnumberparenthesizeandspace
//#define thisend thisinfo << "end "



//extern CLASS_DECL_ACME ::pointer< ::mutex > g_pmutexMemoryCounters;

//CLASS_DECL_ACME bool memory_counter_on();

//CLASS_DECL_ACME ::file::path memory_counter_base_path();



//namespace acme
//{
//   template < typename T >
//   T constraint(T t, T tMin, T tMax)
//   {
//
//      return (t < tMin) ? tMin : ((t > tMax) ? tMax : t);
//
//   }
//
//}
//
//
//inline enum_trace_level trace_level_constraint(enum_trace_level elevel)
//{
//
//   return ::acme::constraint(elevel, e_trace_level_none, e_trace_level_count);
//
//}

//
//extern const char * g_pszTraceLevelName[];
//
//

CLASS_DECL_ACME enum_trace_level trace_level_constraint(enum_trace_level elevel);
//{
//
// return g_pszTraceLevelName[trace_level_constraint(elevel)];
//
//// }

CLASS_DECL_ACME const char * trace_level_name(enum_trace_level elevel);


//extern char g_chaTraceLevel[];;;
//
//
CLASS_DECL_ACME char trace_level_char(enum_trace_level elevel);
//{
//
//   return g_chaTraceLevel[trace_level_constraint(elevel)];
//
//}



//CLASS_DECL_ACME bool is_verbose();





