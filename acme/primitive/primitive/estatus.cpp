//
// Created by camilo on 12/11/2020.
//
#include "framework.h"


CLASS_DECL_ACME void to_string(string & str, const e_status & estatus)
{

   str.format("%" PRIestatus, estatus.m_estatus);

}


CLASS_DECL_ACME string __string(const ::e_status & estatus)
{

    return __string((::i64) estatus.m_estatus);

}


int e_status::exit_code() const
{

#ifdef WINDOWS

   return succeeded() ? 0 : (int) m_estatus;

#else

   if(m_estatus >= 0)
   {

      return 0;

   }
   else if(m_estatus >= -125)
   {

      return -(int)(m_estatus);

   }
   else
   {

      return 125;

   }

#endif

}


CLASS_DECL_ACME ::e_status worst(enum_status e1, enum_status e2)
{

   // heuristic/simple/easy implementation

   return (::e_status)minimum((::i64)e1, (::i64)e2);

}


CLASS_DECL_ACME::e_status operator & (enum_status e1, enum_status e2)
{

   return worst(e1, e2);

}
