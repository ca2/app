#include "framework.h"


exit_exception::exit_exception(__pointer(::task) playeredThreadExit, const char * pszMessage) :
   exception(pszMessage),
   m_ptaskExit(playeredThreadExit)
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


::e_status exit_exception::finish(::property_object * pcontextobjectFinish)
{

   try
   {

      if(m_ptaskExit.is_null())
      {

         return ::success;

      }

      m_ptaskExit->finish(pcontextobjectFinish);

      m_ptaskExit.release();

   }
   catch(...)
   {

   }

   return ::success;

}



