#include "framework.h"


//const char * callstack::get_dup(const char * pszFormat, i32 iSkip, int iCount)
//{
//
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
//   //psz = strdup(::exception_engine().stack_trace(m_addressa, ));
//
//#elif defined(__APPLE__)
//
//   ::exception_engine().stack_trace(iSkip, m_caller_address, m_pszFormat, m_iCount);
//
//   psz = _strdup(::exception_engine()._strS);
//
//#else
//
//   return psz;
//
//#endif
//
//}


#if defined(LINUX) || defined(__APPLE__)


void * standard_exception::siginfodup(void * psiginfo)
{

   auto p = malloc(sizeof(siginfo_t));

   memcpy(p, psiginfo, sizeof(siginfo_t));

   return p;

}


void standard_exception::siginfofree(void * psiginfo)
{

   ::free(psiginfo);

}


#endif



