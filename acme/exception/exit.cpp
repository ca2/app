#include "framework.h"
#include "exit.h"
#include "acme/parallelization/task.h"
#include "acme/platform/application.h"
#include "acme/platform/session.h"
#include "acme/platform/system.h"


exit_exception::exit_exception(const ::e_status & estatus, ::task * playeredThreadExit, const ::scoped_string & scopedstrMessage) :
   exception(::error_failed, scopedstrMessage),
   m_ptaskExit(playeredThreadExit)
{

   //if(m_pthreadExit)
 /*  {

      m_pthreadExit->m_result.add(this);

   }*/

   m_iCheck = 0;

}


exit_exception::exit_exception(::acme::application * papplication, const ::scoped_string & scopedstrMessage) :
   exit_exception(error_exit_application, papplication, scopedstrMessage) 
{

}


exit_exception::exit_exception(::acme::session * psession, const ::scoped_string & scopedstrMessage) :
   exit_exception(error_exit_session, psession, scopedstrMessage) 
{

}


exit_exception::exit_exception(::acme::system * psystem, const ::scoped_string & scopedstrMessage) :
   exit_exception(error_exit_system, psystem, scopedstrMessage) 
{


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


CLASS_DECL_ACME void throw_exit_exception(const ::e_status& estatus, ::task* playeredThreadExit, const ::scoped_string & scopedstrMessage)
{

   throw ::exit_exception(estatus);

}



