#include "framework.h"
#include "acme/operating_system/ansi/call_stack.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
//#include "_openbsd.h"
#include <execinfo.h>
#include <cxxabi.h>
#undef USE_MISC


#define DISABLE_BACKTRACE 1


string get_callstack(::particle * pparticle,  const ::scoped_string & scopedstrFormat, int iSkip, void * caller_address, int iCount)
{

#if DISABLE_BACKTRACE

   return "";

#else

    const size_t iMaximumFramesToCapture = 64;

    void * stack[iMaximumFramesToCapture];

    auto frames = ::backtrace(stack, iMaximumFramesToCapture);

    return _ansi_stack_trace(pparticle, stack, frames, scopedstrFormat);

#endif

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
//   //   synchronous_lock synchronouslock(::exception_engine().mutex(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//   //
//   //   ::exception_engine().xxxstack_trace(iSkip, nullptr, m_pszFormat, m_iCount);
//   //
//   //   psz = _strdup(::exception_engine()._strS);
//   //
//   //   return psz;
//   //
//   }


//} // namespace linux



void openbsd_backtrace_symbol_parse(::particle * pparticle, string & strSymbolName, string & strModule, string & strAddress, char * pmessage, void * address)
{

   if(ansi_str(pmessage, "EPT_"))
   {

      output_debug_string("EPT_");

   }

   char * pszMangledName = nullptr;

   char * pszModuleName = nullptr;

   char * pszOffsetBegin = nullptr;

   char * pszOffsetEnd = nullptr;

   // find parantheses and +address offset surrounding mangled name
   for (char * psz = pmessage; *psz; ++psz)
   {

      if (*psz == '<')
      {

         pszMangledName = psz;

      }
      else if (*psz == '+')
      {

         pszOffsetBegin = psz;

      }
      else if (*psz == '>')
      {

         pszOffsetEnd = psz;

      }
      else if (psz[0] == ' ' && psz[1] == 'a' && psz[2] == 't' && psz[3] == ' ')
      {

         psz+=4;

         pszModuleName = psz;

      }

   }

   if (pszMangledName && pszOffsetBegin && pszOffsetEnd && pszMangledName < pszOffsetBegin)
   {

      *pszMangledName++ = '\0';
      *pszOffsetBegin++ = '\0';
      *pszOffsetEnd = '\0';

      strModule = pszModuleName;

      int status = 0;

      auto psynchronization = ::system()->synchronization();

      _synchronous_lock sl(psynchronization);

      try
      {

         //acme::malloc<char *> pszRealName = abi::__cxa_demangle(scopedstrMangledName, 0, 0, &status);

//         if (status == 0)
//         {
//
//            strSymbolName = (const_char_pointer )(char *) pszRealName;
//
//         }
//         else
         {

            strSymbolName = pszMangledName;

         }

      }
      catch(...)
      {

         strSymbolName = pszMangledName;

      }

      strAddress = pszOffsetBegin;

   }

}

