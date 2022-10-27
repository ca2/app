#include "framework.h"
#include "app_container.h"
#include "assert_running_task.h"
#include "acme/exception/exit.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"


namespace apex
{


   assert_running_task::assert_running_task(::apex::application_container * pcontainer,const ::string & strAppId, const ::string & strLocale, const ::string & strSchema):
      m_pcontainer(pcontainer),
      m_strLocale(strLocale),
      m_strSchema(strSchema)
   {

      initialize(pcontainer);

      m_strAppId = strAppId;

      m_durationCheckPeriod = 5_s;

   }


   assert_running_task::~assert_running_task()
   {

   }


   void assert_running_task::run()
   {

      while(task_get_run())
      {

         try
         {

            m_pcontainer->assert_running(m_strAppId, m_strLocale, m_strSchema);

         }
         catch(::exit_exception &)
         {

            //e.finish(psystem);

         }
         catch(::exception &)
         {

         }
         catch(...)
         {

         }

         sleep(m_durationCheckPeriod);

      }

      //return ::success;

   }


} // namespace apex



















































