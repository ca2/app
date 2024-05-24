#include "framework.h"
#include "exit.h"
#include "acid/parallelization/task.h"
#include "acid/platform/application.h"
#include "acid/platform/session.h"
#include "acid/platform/system.h"


exit_exception::exit_exception(const ::e_status & estatus, ::task * playeredThreadExit, const ::scoped_string & scopedstrMessage) :
   exception(::error_failed, scopedstrMessage),
   m_ptaskExit(playeredThreadExit)
{

   m_estatus = estatus;

   //if(m_pthreadExit)
 /*  {

      m_pthreadExit->m_result.add(this);

   }*/

   m_iCheck = 0;

}


exit_exception::exit_exception(::acid::application * papplication, const ::scoped_string & scopedstrMessage) :
   exit_exception(error_exit_application, papplication, scopedstrMessage) 
{

}


exit_exception::exit_exception(::acid::session * psession, const ::scoped_string & scopedstrMessage) :
   exit_exception(error_exit_session, psession, scopedstrMessage) 
{

}


exit_exception::exit_exception(::acid::system * psystem, const ::scoped_string & scopedstrMessage) :
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

      auto ptaskExit = m_ptaskExit;

      if(!ptaskExit)
      {

         return ::success;

      }

      ptaskExit->post_procedure([ptaskExit]()
         {

            ptaskExit->destroy();

         });

   }
   catch(...)
   {

   }

   return ::success;

}


CLASS_DECL_ACID void throw_exit_exception(const ::e_status& estatus, ::task* playeredThreadExit, const ::scoped_string & scopedstrMessage)
{

   throw ::exit_exception(estatus);

}



