#include "framework.h"
#include "acme/operating_system/ansi/callstack.h"
#include "_freebsd.h"
#include <execinfo.h>
#include <cxxabi.h>
#undef USE_MISC

string get_callstack(const char* pszFormat, i32 iSkip, void * caller_address, int iCount)
{


    const size_t iMaximumFramesToCapture = 64;

    void * stack[iMaximumFramesToCapture];

    auto frames = ::backtrace(stack, iMaximumFramesToCapture);

    return _ansi_stack_trace(stack, frames, pszFormat);

}
//namespace linux
//{
//
//
//   callstack::callstack()
//   {
//
//   }
//
//
//   callstack::~callstack()
//   {
//
//   }


//   const char * callstack::get_dup(const char * pszFormat, i32 iSkip, int iCount)
//   {
//
//      return nullptr;
//
//   //   if (iSkip >= 0)
//   //   {
//   //
//   //      iSkip++;
//   //
//   //   }
//   //
//   //   const char * psz;
//   //
//   //   synchronous_lock synchronouslock(::exception_engine().mutex());
//   //
//   //   ::exception_engine().xxxstack_trace(iSkip, nullptr, m_pszFormat, m_iCount);
//   //
//   //   psz = _strdup(::exception_engine()._strS);
//   //
//   //   return psz;
//   //
//   }


//} // namespace linux



