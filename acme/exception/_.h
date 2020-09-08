#pragma once





#include "callstack.h"

#include "exception.h"

#include "base.h"

#include "simple.h"
#include "cancel.h"

#include "memory.h"
#include "invalid_argument.h"

#include "standard_translator.h"
#include "standard.h"


namespace win
{

   CLASS_DECL_ACME string error_message(u32 dwError);

}


namespace exception
{

   CLASS_DECL_ACME void throw_interface_only(const char * pszMessage = nullptr);
   CLASS_DECL_ACME void throw_not_implemented(const char * pszMessage = nullptr);

}



#include "error.h"
#include "overflow_error.h"
#include "runtime_error.h"
#include "range_error.h"


#include "not_implemented.h"
#include "void_implementation.h"
#include "interface_only.h"
#include "not_installed.h"
#include "not_supported.h"
#include "exit.h"
#include "not_licensed.h"
#include "temporary.h"
#include "installing.h"

#include "assert.h"
#include "misc.h"



#include "io.h"
#include "resource.h"
#include "user.h"





#include "hresult.h"




#ifndef ___JUMPBUF
// Use portable 'jmp_buf' defined by ANSI by default.
#define ___JUMPBUF jmp_buf
#endif

namespace datetime
{


   class time_span;
   class time;


} // namespace datetime


class dump_context;

// ::datetime::time_span diagnostics and serialization
CLASS_DECL_ACME dump_context & operator<<(dump_context & dumpcontext, const ::datetime::time_span & dateSpanSrc);
CLASS_DECL_ACME dump_context & operator<<(dump_context & dumpcontext, const ::datetime::time & dateSrc);








#if defined(NNDEBUG) && !defined(___NO_DEBUG_CRT)



//#define afxMemDF _crtDbgFlag
//
//enum e_memdbg // memory debug/diagnostic flags
//{
//   memdbg_alloc            = _DEBUG_ALLOC_MEM_DF,         // turn on debugging allocator
//   memdbg_delay_free       = _DEBUG_DELAY_FREE_MEM_DF,         // delay freeing memory
//   memdbg_check_every16    = _DEBUG_CHECK_EVERY_16_DF,
//   memdbg_check_every128   = _DEBUG_CHECK_EVERY_128_DF,
//   memdbg_check_every1024  = _DEBUG_CHECK_EVERY_1024_DF,
//   memdbg_check_default    = _DEBUG_CHECK_DEFAULT_DF
//};

#define __output_debug_string TRACE

// turn on/off tracking for a i16 while
CLASS_DECL_ACME bool __enable_memory_tracking(bool bTrack);

// Turn on/off the global flag gen_MemoryLeakOverride. if bEnable is TRUE
// then further calls to __enable_memory_tracking() wont change the current
// memory tracking state, until __enable_memory_leak_override(bool bEnable)
// is called again with bEnable == FALSE.
CLASS_DECL_ACME bool __enable_memory_leak_override(bool bEnable);



//#include "memory_state.h"

// Enumerate allocated objects or runtime classes
/*void __do_for_all_objects(void (c_cdecl *pfn)(generic* pObject, void * pContext),
   void * pContext);
void ::acme::DoForAllClasses(void (c_cdecl *pfn)(::type pClass,
   void * pContext), void * pContext);*/


#else

// non-DEBUG_ALLOC version that assume everything is OK
#define __enable_memory_tracking(bTrack) FALSE
#define __enable_memory_leak_override(bEnable) TRUE
#define __output_debug_string(psz) ::output_debug_string(psz)



#endif // NNDEBUG



#define __stack_dump_TARGET_TRACE                     0x0001
#define __stack_dump_TARGET_CLIPBOARD 0x0002
#define __stack_dump_TARGET_BOTH                      0x0003
#define __stack_dump_TARGET_ODS                       0x0004
#ifdef NNDEBUG
#define __stack_dump_TARGET_DEFAULT           __stack_dump_TARGET_TRACE
#else //NNDEBUG
#define __stack_dump_TARGET_DEFAULT           __stack_dump_TARGET_CLIPBOARD
#endif //!NNDEBUG




#ifdef NNDEBUG


#define DEBUG_NOTE __FILE__


#define THREAD_NOTE __get_thread_note()
#define SET_THREAD_NOTE(x) __set_thread_note(x);


#else //NNDEBUG


#define SET_THREAD_NOTE(x)


#endif //NNDEBUG


CLASS_DECL_ACME string __get_thread_note();
CLASS_DECL_ACME void __set_thread_note(const char * pszNote);



#include "debug.h"



// Debug ASSERTs then throws. Retail throws if condition not met
#define ENSURE_THROW(cond, exception)   \
   do { i32 _gen__condVal=!!(cond); ASSERT(_gen__condVal); if (!(_gen__condVal)){exception;} } while (false)
#define ENSURE(cond)      ENSURE_THROW(cond, __throw(invalid_argument_exception()))
#define ENSURE_ARG(cond)   ENSURE_THROW(cond, __throw(invalid_argument_exception()))

// Debug ASSERT_VALIDs then throws. Retail throws if pOb is nullptr
#define ENSURE_VALID_THROW(pOb, exception)   \
   do { ASSERT_VALID(pOb); if (!(pOb)){exception;} } while (false)
#define ENSURE_VALID(pOb)   ENSURE_VALID_THROW(pOb, __throw(invalid_argument_exception() ))

#define ASSERT_POINTER(point, type) \
   ASSERT(((point) != nullptr) && __is_valid_address((point), sizeof(type), FALSE))

#define ASSERT_NULL_OR_POINTER(point, type) \
   ASSERT(((point) == nullptr) || __is_valid_address((point), sizeof(type), FALSE))


#if defined(__arm__)
#  define UNUSED_ALWAYS(x)
#elif defined(__GNUC__)
#  define UNUSED_ALWAYS(x) __attribute__((__unused__))
#elif defined(_MSC_VER)
#  define UNUSED_ALWAYS(x)
#else
#  define UNUSED_ALWAYS(x) x
#endif


#ifdef NNDEBUG
#  define UNUSED(x) x
#else
#  define UNUSED(x) UNUSED_ALWAYS(x)
#endif //NNDEBUG


#ifdef NNDEBUG
#define REPORT_EXCEPTION(pException, szMsg) \
   do { \
      string str; \
      if (pException->get_error_message(str, 0)) \
         TRACE(trace_category_appmsg, 0, "%s (%s:%d)\n%s\n", szMsg, __FILE__, __LINE__, str); \
      else \
         TRACE(trace_category_appmsg, 0, "%s (%s:%d)\n", szMsg, __FILE__, __LINE__); \
      ASSERT(FALSE); \
   } while (0)
#else // NNDEBUG
#define REPORT_EXCEPTION(pException, szMsg) \
   do { \
      string strMsg; \
      char  szErrorMessage[512]; \
      if (pException->get_error_message(szErrorMessage, sizeof(szErrorMessage)/sizeof(*szErrorMessage), 0)) \
         strMsg.Format("%s (%s:%d)\n%s", szMsg, __FILE__, __LINE__, szErrorMessage); \
      else \
         strMsg.Format("%s (%s:%d)", szMsg, __FILE__, __LINE__); \
      System.message_box(strMsg); \
   } while (0)
#endif //!NNDEBUG



#define EXCEPTION_IN_DTOR(pException) \
   do { \
      REPORT_EXCEPTION((pException), "Exception thrown in destructor"); \
      delete pException; \
   } while (0)

#define __BEGIN_DESTRUCTOR try {
#define __END_DESTRUCTOR   } catch (::exception::exception *pException) { EXCEPTION_IN_DTOR(pException); }



#define C_RUNTIME_ERROR_CHECK(expr) ::c_runtime_error_check(expr)
#ifndef C_RUNTIME_ERRORCHECK_SPRINTF
#define C_RUNTIME_ERRORCHECK_SPRINTF(expr) \
do { \
   errno_t _saveErrno = errno; \
   errno = 0; \
   (expr); \
   if(0 != errno) \
   { \
      ::c_runtime_error_check(errno); \
   } \
   else \
   { \
      errno = _saveErrno; \
   } \
} while (0)
#endif // C_RUNTIME_ERRORCHECK_SPRINTF


CLASS_DECL_ACME errno_t c_runtime_error_check(errno_t error);
CLASS_DECL_ACME void __cdecl __clearerr_s(FILE *stream);
















CLASS_DECL_ACME int __assert_failed_line(const char * pszFileName, int nLine);

//CLASS_DECL_ACME void TRACE(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * psz);
//CLASS_DECL_ACME void __tracef(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, ...);
//CLASS_DECL_ACME void __tracev(e_trace_category ecategory, e_trace_level elevel, const char * pszFunction, const char * pszFile, i32 iLine, const char * pszFormat, va_list args);
CLASS_DECL_ACME void __assert_valid_object(const ::generic * pOb, const char * pszFileName, i32 nLine);

CLASS_DECL_ACME void __dump(const ::generic * pOb);


#define THIS_FILE          __FILE__



#include "last_error.h"

// mrs/src as of 2012-08-18
// cyaxis/os/exception
#include "os.h"
#include "invalid_index.h"
#include "invalid_handle.h"
#include "operation_canceled.h"


#include "invalid_character.h"

#include "todo.h"

#include "system.h"


#include "parsing.h"


#include "invalid_type.h"
