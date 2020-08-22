#include "framework.h"


exit_exception::exit_exception(__pointer(::thread) pthreadExit, const char * pszMessage) :
   exception(pszMessage),
   m_pthreadExit(pthreadExit)
{

   if(m_pthreadExit)
   {

      m_pthreadExit->m_result.add(this);

   }

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



