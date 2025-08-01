#include "framework.h"
#include "acme/operating_system/ansi/call_stack.h"
//#include "_freebsd.h"
#include <execinfo.h>
#include <cxxabi.h>
#undef USE_MISC

string get_callstack(::particle * pparticle, const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
{


    const size_t iMaximumFramesToCapture = 64;

    void * stack[iMaximumFramesToCapture];

    auto frames = ::backtrace(stack, iMaximumFramesToCapture);

    return _ansi_stack_trace(pparticle, stack, frames, scopedstrFormat);

//namespace linux
//{
//
//
//   callstack::callstack()
//   {
}
//
//   }
//
//
//   callstack::~callstack()
//   {
//
//   }


//   const_char_pointer callstack::get_dup(const ::scoped_string & scopedstrFormat, int iSkip, int iCount)
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
//   //   const ::scoped_string & scopedstr;
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










