#include "framework.h"


exit_exception::exit_exception(__pointer(::layered) playeredThreadExit, const char * pszMessage) :
   exception(pszMessage),
   m_pthreadExit(playeredThreadExit)
{

   //if(m_pthreadExit)
 /*  {

      m_pthreadExit->m_result.add(this);

   }*/

   m_iCheck = 0;

}


exit_exception::~exit_exception()
{

}


::e_status exit_exception::finish(::context_object * pcontextobjectFinish)
{

   try
   {

      if(m_pthreadExit.is_null())
      {

         return ::success;

      }

      m_pthreadExit->finish(pcontextobjectFinish);

      m_pthreadExit.release();

   }
   catch(...)
   {

   }

   return ::success;

}



