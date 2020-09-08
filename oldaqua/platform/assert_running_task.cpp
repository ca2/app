#include "framework.h"


namespace aqua
{


   assert_running_task::assert_running_task(::application_container * pcontainer,const string & strAppId, const string & strLocale, const string & strSchema):
      ::object(pcontainer),
      m_pcontainer(pcontainer),
      m_strLocale(strLocale),
      m_strSchema(strSchema)
   {

      m_strAppId = strAppId;

      m_durationCheckPeriod = millis(5000);

   }


   assert_running_task::~assert_running_task()
   {

   }


   ::estatus     assert_running_task::run()
   {

      while(thread_get_run())
      {

         try
         {

            m_pcontainer->assert_running(m_strAppId, m_strLocale, m_strSchema);

         }
         catch(::exit_exception &)
         {

            ::multithreading::set_finish(&System);

         }
         catch(::exception::exception &)
         {

         }
         catch(...)
         {

         }

         Sleep(m_durationCheckPeriod);

      }

      return ::success;

   }


} // namespace aqua



















































