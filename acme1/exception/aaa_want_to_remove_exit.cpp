#include "framework.h"


exit_exception::exit_exception(::generic * pgenericExit, const char * pszMessage) :
   exception(pszMessage),
   m_pgenericExit(pgenericExit)
{

   //if(m_pgenericExit)
   //{

   //   m_pgenericExit->m_result.add(this);

   //}

   m_iCheck = 0;

}


exit_exception::~exit_exception()
{

}


void exit_exception::set_finish()
{

   try
   {

      if(m_pthreadExit.is_null())
      {

         return;

      }

      m_pthreadExit->set_finish();

      m_pthreadExit.release();

   }
   catch(...)
   {

   }

}



