#include "framework.h"


namespace apex
{


   assert_running_task::assert_running_task(::application_container * pcontainer,const string & strAppId, const string & strLocale, const string & strSchema):
      m_pcontainer(pcontainer),
      m_strLocale(strLocale),
      m_strSchema(strSchema)
   {

      initialize(pcontainer);

      m_strAppId = strAppId;

      m_durationCheckPeriod = millis(5000);

   }


   assert_running_task::~assert_running_task()
   {

   }


   ::e_status     assert_running_task::run()
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
         catch(::exception::exception &)
         {

         }
         catch(...)
         {

         }

         sleep(m_durationCheckPeriod);

      }

      return ::success;

   }


} // namespace apex



















































