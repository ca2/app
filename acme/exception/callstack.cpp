#include "framework.h"


//e_callstack g_ecallstack = callstack_none;





//callstack::callstack(const char * pszFormat, i32 iSkip, void * address, int iCount) :
//   m_pszFormat(pszFormat),
//   m_iCount(iCount),
//   m_caller_address(address)
//{
//
//   if (!g_pmutexException)
//   {
//
//      g_pmutexException = new ::mutex();
//
//   }
//
//   if (iSkip == CALLSTACK_DEFAULT_SKIP_TRIGGER)
//   {
//
//      iSkip = 1;
//
//   }
//   else if (iSkip >= 0)
//   {
//
//      iSkip += 1;
//
//   }
//
//   callstack::trace(m_pszFormat, iSkip, iCount);
//
//}
//
//
//callstack::~callstack()
//{
//
//}


//CLASS_DECL_ACME __pointer(callstack) get_callstack(const char* pszFormat, iptr iSkip, void* caller_address, iptr iCount)
//{
//
//   if (iSkip >= 0)
//   {
//
//      iSkip++;
//
//   }
//
//   auto pcallstack = __new(callstack(pszFormat, (int) iSkip, caller_address, (int) iCount));
//
//   return pcallstack;
//
//}
//

//CLASS_DECL_ACME __pointer(callstack) get_callstack(e_callstack ecallstack, int iCallStackAddUp)
//{
//
//   iCallStackAddUp++;
//
//   switch (ecallstack)
//   {
//   case callstack_fork_global:
//      
//      return get_callstack("%s - %l\n", iCallStackAddUp, nullptr, 1);
//
//   default:
//      return get_callstack();
//   }
//
//}


//CLASS_DECL_ACME void set_callstack_mask(enumeration < e_callstack > ecallstack)
//{
//
//   g_ecallstack = ecallstack;
//
//}


//CLASS_DECL_ACME e_callstack get_callstack_mask()
//{
//
//   return g_ecallstack;
//
//}


//CLASS_DECL_ACME bool is_callstack_enabled(e_callstack ecallstack)
//{
//
//   return g_ecallstack & ecallstack;
//
//}
