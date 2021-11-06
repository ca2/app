#pragma once


//#include "aura/net/sockets/trace_interface.h"
//
//
//#define _DEBUG_WIDE_(s) L ## s
//#define _DEBUG_WIDE(s) _DEBUG_WIDE_(s)
//
//#define _NORMAL_BLOCK 1
//
//
//CLASS_DECL_AURA i32 DECL_C debug_report(
//i32 _ReportType,
//const char * _Filename,
//i32 _LineNumber,
//const char * _ModuleName,
//const char * _Format,
//...);
//
//
//CLASS_DECL_AURA i32 DECL_C debug_report(
//i32 _ReportType,
//const wchar_t * _Filename,
//i32 _LineNumber,
//const wchar_t * _ModuleName,
//const wchar_t * _Format,
//...);
//
//
////////////////////////////////////////////////////////////////////////////////////
////
////    Debug Reporting
////
//typedef void * _HFILE; /* file handle pointer */
//
//#define _DEBUG_WARN           0
//#define _DEBUG_ERROR          1
//#define _DEBUG_ASSERT         2
//#define _DEBUG_ERRCNT         3
//
//#define _DEBUG_MODE_FILE      0x1
//#define _DEBUG_MODE_DEBUG     0x2
//#define _DEBUG_MODE_WNDW      0x4
//#define _DEBUG_REPORT_MODE    -1
//
//#ifndef WINDOWS
//
//#if defined(_M_IX86)
//#define _DEBUG_INVALID_HFILE ((_HFILE)-1)
//#define _DEBUG_HFILE_ERROR   ((_HFILE)-2)
//#define _DEBUG_FILE_STDOUT   ((_HFILE)-4)
//#define _DEBUG_FILE_STDERR   ((_HFILE)-5)
//#define _DEBUG_REPORT_FILE   ((_HFILE)-6)
//#else
//#define _DEBUG_INVALID_HFILE ((_HFILE)(i64)-1)
//#define _DEBUG_HFILE_ERROR   ((_HFILE)(i64)-2)
//#define _DEBUG_FILE_STDOUT   ((_HFILE)(i64)-4)
//#define _DEBUG_FILE_STDERR   ((_HFILE)(i64)-5)
//#define _DEBUG_REPORT_FILE   ((_HFILE)(i64)-6)
//#endif
//
//#endif
//
//
//#define _DEBUG_RPTHOOK_INSTALL  0
//#define _DEBUG_RPTHOOK_REMOVE   1
//
//
//#define _DEBUG_ALLOC_MEM_DF        0x01  /* Turn on debug allocation */
//#define _DEBUG_DELAY_FREE_MEM_DF   0x02  /* Don't actually free memory */
//#define _DEBUG_CHECK_ALWAYS_DF     0x04  /* Check heap every alloc/dealloc */
//#define _DEBUG_RESERVED_DF         0x08  /* Reserved - do not use */
//#define _DEBUG_CHECK_DEBUG_DF      0x10  /* Leak check/diff __DEBUG blocks */
//#define _DEBUG_LEAK_CHECK_DF       0x20  /* Leak check at program exit */
//
///*
// * Some bit values for _crtDbgFlag which correspond to frequencies for checking
// * the the heap.
// */
//#define _DEBUG_CHECK_EVERY_16_DF   0x00100000  /* check heap every 16 heap ops */
//#define _DEBUG_CHECK_EVERY_128_DF  0x00800000  /* check heap every 128 heap ops */
//#define _DEBUG_CHECK_EVERY_1024_DF 0x04000000  /* check heap every 1024 heap ops */
///*
//We do not check the heap by default at this point because the cost was too high
//for some applications. You can still turn this feature on manually.
// */
//#define _DEBUG_CHECK_DEFAULT_DF    0
//
//#define _DEBUG_REPORT_FLAG         -1    /* Query bitflag status */
//
//#define _BLOCK_TYPE(block)          (block & 0xFFFF)
//#define _BLOCK_SUBTYPE(block)       (block >> 16 & 0xFFFF)
//
//
///****************************************************************************
// *
// * Memory state
// *
// ***************************************************************************/
//
///* Memory block identification */
//#define _FREE_BLOCK      0
//#define _NORMAL_BLOCK    1
//#define _DEBUG_BLOCK       2
//#define _IGNORE_BLOCK    3
//#define _CLIENT_BLOCK    4
//#define _MAX_BLOCKS      5
//
//
//
//struct MEMORY_BLOCK_HEADER;
//
//typedef struct _MEMORY_STATE
//{
//
//   struct MEMORY_BLOCK_HEADER * pBlockHeader;
//   size_t lCounts[_MAX_BLOCKS];
//   size_t lSizes[_MAX_BLOCKS];
//   size_t lHighWaterCount;
//   size_t lTotalCount;
//
//} MEMORY_STATE;
//
//
///****************************************************************************
// *
// * Declarations, prototype and function-like macros
// *
// ***************************************************************************/
//
///* _STATIC_ASSERT is for enforcing boolean/integral conditions at compile time.
//   Since it is purely a compile-time mechanism that generates no code, the check
//   is left in even if __DEBUG is not defined. */
//
//#ifndef _STATIC_ASSERT
//#define _STATIC_ASSERT(expr) typedef char __static_assert_t[ (expr) ]
//#endif
//
//#ifndef __DEBUG
//
//////////////////////////////////////////////////////////////////////////////////////
////
////    Debug OFF
//
//
//////////////////////////////////////////////////////////////////////////////////////
////
////  We allow our basic _ASSERT macros to be overridden by pre-existing definitions.
////    This is not the ideal mechanism, but is helpful in some scenarios and helps avoid
////    multiple definition problems
//
//#ifndef _ASSERT
//#define _ASSERT(expr) ((void)0)
//#endif
//
//#ifndef _ASSERTE
//#define _ASSERTE(expr) ((void)0)
//#endif
//
//#ifndef _ASSERT_EXPR
//#define _ASSERT_EXPR(expr, expr_str) (()0)
//#endif
//
////
////  __DEBUG Off
////
///////////////////////////////
//
//
//#elif !defined(__MDEBUG) && !defined(__VLD)
//
//
///////////////////////////////
////
////  __DEBUG ON
////
//
//
/////////////////////////////////////////////////////////////////
////
////    Asserts
////    We use !! below to ensure that any overloaded operators used to evaluate expr do not end up at operator ||
////
//#undef _ASSERT_EXPR
//#define _ASSERT_EXPR(expr, msg) \
//        (void) ((!!(expr)) || \
//                (1 != debug_report(_DEBUG_ASSERT, _DEBUG_WIDE(__FILE__), __LINE__, nullptr, msg)) || \
//                (debug_break(), 0))
//
//
//#ifndef _ASSERT
//#define _ASSERT(expr)   _ASSERT_EXPR((expr), nullptr)
//#endif
//
//#ifndef _ASSERTE
//#define _ASSERTE(expr)  _ASSERT_EXPR((expr), _T("##expr##"))
//#endif
//
//
//#if !defined(WINDOWS_DESKTOP) && !defined(_UWP)
//#define debug_break() debug_break()
//#endif
//
//
//#endif
//
//
//
//// CLASS_DECL_AURA i32 FUNCTION_DEBUGBOX(const ::string & pszMessage, const ::string & pszTitle, i32 iFlags);
//
//// CLASS_DECL_AURA i32 FUNCTION_DEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, i32 iFlags);
//
//// inline i32 FUNCTION_XXDEBUGBOX(const ::string & pszMessage, const ::string & pszTitle, i32 iFlags)
//// {
//
////    __UNREFERENCED_PARAMETER(pszMessage);
////    __UNREFERENCED_PARAMETER(pszTitle);
////    __UNREFERENCED_PARAMETER(iFlags);
//
////    return 0;
//
//// }
//
//// inline i32 FUNCTION_XXDEBUGBOXW(const WCHAR * pszMessage, const WCHAR * pszTitle, i32 iFlags)
//// {
//
////    __UNREFERENCED_PARAMETER(pszMessage);
////    __UNREFERENCED_PARAMETER(pszTitle);
////    __UNREFERENCED_PARAMETER(iFlags);
//
////    return 0;
//
//// }
//
////#define debug_box FUNCTION_DEBUGBOX
////#define xxdebug_box FUNCTION_XXDEBUGBOX
//
//// Use!!
//// #include "aura/inline/set_xxdebug_box.inl"
//// and
//// #include "aura/inline/clear_xxdebug_box.inl"
//
//
//
//
//void CLASS_DECL_AURA TRACELASTERROR();
//
//
//
//CLASS_DECL_AURA string FormatMessageFromSystem(u32 dwError);
//
//
//#ifdef MEMDLEAK
//
//CLASS_DECL_AURA string get_mem_info_report1();
//CLASS_DECL_AURA ::count get_mem_info(i32 ** ppiUse, const ::string &** ppszFile, const ::string &** pszCallStack, u32 ** ppuiLine, size_t ** ppsize);
//CLASS_DECL_AURA ::count get_mem_info2(i32 ** ppiUse, const ::string &** ppszFile, DWORD64 ** ppuiStack[64], i64 ** ppiStack, i32 ** ppiLine, i64 ** ppiSize);
//
//
//
//#endif
//
//
//
//
////class CLASS_DECL_AURA trace_interface //:
//////   virtual public ::sockets::trace_interface
////{
////public:
////
////
////
////   //virtual void sockets_trace(::sockets::base_socket_handler * phandler, ::sockets::base_socket * psocket, enum_trace_level elevel, const ::string & strContext, i32 iError, const ::string & strContext) override;
////   //virtual void sockets_trace(::sockets::base_socket_handler * phandler, ::sockets::base_socket * psocket, enum_trace_level elevel, const ::string & strContext, i32 iError, const ::string & strContext) override;
////
////
////};
//
//
//extern critical_section * g_pcsTrace;
//extern object * g_pobjecTracer;
//
//CLASS_DECL_AURA void os_trace(enum_trace_level elevel, const ::string & pszTag, const ::string & pszMessage);
//CLASS_DECL_AURA void trace(enum_trace_level elevel, const ::string & pszTag, const ::string & psz, const ::string & pszFile = nullptr, int iLine = -1);
//
//
//
//
//
//
//
////#define LOG(level, tag) ::text_stream_log_line(level, tag, __FILE__, __LINE__)
//
//
//
////#define cinfo LOG(e_trace_level_information, LOG_TAG)
////#define cwarn LOG(e_trace_level_warning, LOG_TAG)
////#define cerror LOG(e_trace_level_error, LOG_TAG)
////#define cfatal LOG(e_trace_level_fatal, LOG_TAG)
//
//
////#define thisinfo LOG(e_trace_level_information, LOG_THIS_TAG) << LOG_MEMBER_PREFIX << "; "
////#define thiswarn LOG(e_trace_level_warning, LOG_THIS_TAG)  << LOG_MEMBER_PREFIX << "; "
////#define thiserr LOG(e_trace_level_error, LOG_THIS_TAG) << LOG_MEMBER_PREFIX << "; "
////#define thisfatal LOG(e_trace_level_fatal, LOG_THIS_TAG) << LOG_MEMBER_PREFIX << "; "
//
////#define thisstart thisinfo << "start "
////#define thisexit thisinfo << "exit " << str_flag_ifnumberparenthesizeandspace
////#define thisok thisinfo << "ok " << str_flag_ifnumberparenthesizeandspace
////#define thisexc thiserr << "exception " << str_flag_ifnumberparenthesizeandspace
////#define thisexcall thiserr << "exception(...) " << str_flag_ifnumberparenthesizeandspace
////#define thisfail thiserr << "failure " << str_flag_ifnumberparenthesizeandspace
////#define thisend thisinfo << "end "
//
//
//
//extern CLASS_DECL_AURA ::mutex * g_pmutexMemoryCounters;
//
//CLASS_DECL_AURA bool memory_counter_on();
//
//CLASS_DECL_AURA ::file::path memory_counter_base_path();
//
//template < typename T >
//::file::path memory_counter_path(T * pthis);
//
//template < typename T >
//void memory_counter_increment(T * pthis);
//
//template < typename T >
//void memory_counter_decrement(T * pthis);
//
//
//namespace papaya
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
