//
// Created by camilo on 12/11/2020.
//
#include "framework.h"


CLASS_DECL_ACME string __str(const ::e_status & estatus)
{

    return __str((::i64) estatus.m_estatus);

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



