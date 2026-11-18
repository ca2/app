#include "platform.h"
#include "acme/operating_system/ansi/call_stack.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/platform_platform.h"
#include "acme/platform/system.h"
//#include "_netbsd.h"
#include "acme/exception/call_stack.h"
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>
#include <cxxabi.h>
#undef USE_MISC


#define DISABLE_BACKTRACE 1


string get_callstack(::particle * pparticle,  const ::scoped_string & scopedstrFormat, ::i32 iSkip, void * caller_address, ::i32 iCount)
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


//   const_char_pointer callstack::get_dup(const ::scoped_string & scopedstrFormat, ::i32 iSkip, ::i32 iCount)
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



void netbsd_backtrace_symbol_parse(::particle * pparticle, string & strSymbolName, string & strModule, string & strAddress, char_pointer pmessage, void * address)
{

   if(ansi_str(pmessage, "EPT_"))
   {

      output_debug_string("EPT_");

   }

   char_pointer pszMangledName = nullptr;

   char_pointer pszModuleName = nullptr;

   char_pointer pszOffsetBegin = nullptr;

   char_pointer pszOffsetEnd = nullptr;

   // find parantheses and +address offset surrounding mangled name
   for (char_pointer psz = pmessage; *psz; ++psz)
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

      ::i32 status = 0;

      auto psynchronization = ::system()->synchronization();

      synchronous_lock sl(psynchronization, pparticle, SYNCHRONOUS_LOCK_SUFFIX);

      try
      {

         //acme::malloc<char_pointer > pszRealName = abi::__cxa_demangle(scopedstrMangledName, 0, 0, &status);

//         if (status == 0)
//         {
//
//            strSymbolName = (const_char_pointer )(char_pointer ) pszRealName;
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


void call_stack::capture(::i32 iSkip, void * caller_address, ::i32 iCount)
{

   free((void *)m_pszCallStack);
   m_pszCallStack = nullptr;
   m_caller_address = caller_address;
   m_u32Hash = 0;
   m_iCount = 0;

   if (iCount == 0)
   {
      return;
   }

   auto frames = ::backtrace(m_stack, TRACE_MAX_STACK_FRAMES);
   // The first frame is capture itself; negative skip selects the default.
   auto skip = iSkip < 0 ? (frames > 0 ? 1 : 0) : (iSkip >= frames ? frames : iSkip + 1);
   // A supplied caller address selects the start when present in this stack.
   if (caller_address)
   {
      for (int i = skip; i < frames; ++i)
      {
         if (m_stack[i] == caller_address)
         {
            skip = i;
            break;
         }
      }
   }
   auto count = frames - skip;
   if (iCount >= 0 && count > iCount)
   {
      count = iCount;
   }
   for (int i = 0; i < count; ++i)
   {
      m_stack[i] = m_stack[i + skip];
      auto address = (uintptr_t)m_stack[i];
      // Fold every byte so that the hash includes all bits of a 64-bit PC.
      for (size_t byte = 0; byte < sizeof(address); ++byte)
      {
         m_u32Hash = m_u32Hash * 33 + (address & 0xff);
         address >>= 8;
      }
   }
   m_iCount = count;

}


::i32 call_stack::_prepare_trace(const_char_pointer pszFormat)
{

   // Match the Windows backend's module + offset representation.
   ::i32 size = 64;
   for (::i32 i = 0; i < m_iCount; ++i)
   {
      Dl_info info = {};
      const char * path = "(unknown)";
      m_modulea[i] = nullptr;
      if (::dladdr(m_stack[i], &info))
      {
         m_modulea[i] = info.dli_fbase;
         if (info.dli_fname && *info.dli_fname)
         {
            path = info.dli_fname;
         }
      }
      ::snprintf(m_szaModulePath[i], MODULE_BUF_SIZE, "%s", path);
      m_u32ModulePathLength[i] = ::strlen(m_szaModulePath[i]);
      size += m_u32ModulePathLength[i] + 64;
   }
   return size;

}


const_char_pointer call_stack::_trace(::i32 iSize, const_char_pointer pszFormat)
{

   if (iSize <= 0)
   {
      return nullptr;
   }
   auto trace = (char *)::malloc(iSize);
   if (!trace)
   {
      return nullptr;
   }
   trace[0] = '\0';
   auto written = ::snprintf(trace, iSize, "Stack hash: 0x%08x\n", (unsigned int)m_u32Hash);
   size_t used = written < 0 ? 0 : (size_t)written;
   for (::i32 i = 0; i < m_iCount && used < (size_t)iSize; ++i)
   {
      auto offset = (uintptr_t)m_stack[i] - (uintptr_t)m_modulea[i];
      written = ::snprintf(trace + used, iSize - used, "%02d:%s+0x%016llx\n",
         i, m_szaModulePath[i], (unsigned long long)offset);
      if (written < 0)
      {
         break;
      }
      used += (size_t)written;
   }
   return trace;

}
