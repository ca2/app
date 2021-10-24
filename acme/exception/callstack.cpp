#include "framework.h"


// 0 - most deep call stack logging
// 4 - most lite call stack logging
int g_iCallStackLevel = 4;

e_callstack g_ecallstack = callstack_none;


callstack::callstack(const char * pszFormat, i32 iSkip, void * address, int iCount) :
   m_pszFormat(pszFormat),
   m_iCount(iCount),
   m_caller_address(address)
{

   m_pszCallStack = nullptr;

   if (iSkip == CALLSTACK_DEFAULT_SKIP_TRIGGER)
   {

      iSkip = 1;

   }
   else if (iSkip >= 0)
   {

      iSkip += 1;

   }

   m_pszCallStack = callstack::get_dup(m_pszFormat, iSkip, iCount);

}




callstack::~callstack()
{

   if (m_pszCallStack != nullptr)
   {

      free((void*)m_pszCallStack);

   }

}

const char * callstack::get_dup(const char * pszFormat, i32 iSkip, int iCount)
{

   return nullptr;

}

//   if (iSkip >= 0)
//   {
//
//      iSkip++;
//
//   }
//
//   const char * psz;
//
//   synchronous_lock synchronouslock(::exception_engine().mutex());
//
//#if defined(LINUX)
//
//   psz = strdup(::exception_engine().stack_trace(iSkip, m_caller_address));
//
//#elif defined(__APPLE__)
//   
//   ::exception_engine().stack_trace(iSkip, m_caller_address, m_pszFormat, m_iCount);
//   
//   psz = _strdup(::exception_engine()._strS);
//
//#else
//
//   ::exception_engine().stack_trace(iSkip, m_pszFormat, m_iCount);
//
//   psz = _strdup(::exception_engine()._strS);
//
//#endif
//
//   return psz;
//
//}

const char * callstack::stack_trace() const
{

   return m_pszCallStack;

}


CLASS_DECL_ACME __pointer(callstack) get_callstack(const char* pszFormat, iptr iSkip, void* caller_address, iptr iCount)
{

   if (iSkip >= 0)
   {

      iSkip++;

   }

   auto pcallstack = __new(callstack(pszFormat, (int) iSkip, caller_address, (int) iCount));

   return pcallstack;

}


CLASS_DECL_ACME __pointer(callstack) get_callstack(e_callstack ecallstack, int iCallStackAddUp)
{

   iCallStackAddUp++;

   switch (ecallstack)
   {
   case callstack_fork_global:
      return get_callstack("%s - %l\n", iCallStackAddUp, nullptr, 1);
   default:
      return get_callstack();
   }

}


CLASS_DECL_ACME void set_callstack_mask(enumeration < e_callstack > ecallstack)
{

   g_ecallstack = ecallstack;

}


CLASS_DECL_ACME e_callstack get_callstack_mask()
{

   return g_ecallstack;

}


//CLASS_DECL_ACME bool is_callstack_enabled(e_callstack ecallstack)
//{
//
//   return g_ecallstack & ecallstack;
//
//}
