#include "framework.h"
#include "_ansios.h"


namespace ansios
{


   callstack::callstack()
   {

   }


   callstack::~callstack()
   {

   }


   const char * callstack::get_dup(const ::string & pszFormat, i32 iSkip, int iCount)
   {

      return nullptr;

   //   if (iSkip >= 0)
   //   {
   //
   //      iSkip++;
   //
   //   }
   //
   //   const char * psz;
   //
   //   synchronous_lock synchronouslock(::exception::engine().mutex());
   //
   //   ::exception::engine().stack_trace(iSkip, nullptr, m_pszFormat, m_iCount);
   //
   //   psz = _strdup(::exception::engine()._strS);
   //
   //   return psz;
   //
   }


} // namespace ansios



