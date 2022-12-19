#include "framework.h"
#include "exit.h"
#include "acme/parallelization/task.h"


exit_exception::exit_exception(const ::e_status & estatus, ::task * playeredThreadExit, const scoped_string & strMessage) :
   exception(::error_failed, pszMessage),
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

      //m_ptaskExit->finish(pcontextobjectFinish);

      m_ptaskExit->destroy();

      m_ptaskExit.release();

   }
   catch(...)
   {

   }

   return ::success;

}


CLASS_DECL_ACME void throw_exit_exception(const ::e_status& estatus, ::task* playeredThreadExit, const scoped_string & strMessage)
{

   throw ::exit_exception(estatus);

}



