#include "framework.h"


exit_exception::exit_exception(__pointer(::layered) playeredThreadExit, const char * pszMessage) :
   exception(pszMessage),
   m_playeredThreadExit(playeredThreadExit)
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


void exit_exception::set_finish()
{

   try
   {

      if(m_playeredThreadExit.is_null())
      {

         return;

      }

      m_playeredThreadExit->set_finish();

      m_playeredThreadExit.release();

   }
   catch(...)
   {

   }

}



