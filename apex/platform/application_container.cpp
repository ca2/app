#include "framework.h"
#include "apex/platform/app_core.h"
#include "apex/platform/node.h"
#include "acme/filesystem/filesystem/acme_path.h"


extern ::app_core * g_pappcore;


application_container::application_container()
{
   
   m_bFinalizeIfNoApplicationSetting = true;
   m_bFinalizeIfNoApplication = false;

}


application_container::~application_container()
{

}


void application_container::add_application(::application * papp)
{

   if (!::is_set(papp))
   {

      return;

   }

   if (m_applicationa.is_empty())
   {

      m_bFinalizeIfNoApplication = m_bFinalizeIfNoApplicationSetting;

   }

   m_applicationa.add(papp);

   add_composite(papp);

}


void application_container::erase_application(::application * papp)
{

   auto iSizeBefore = m_applicationa.get_size();

   m_applicationa.erase(papp);

   auto iSizeAfter = m_applicationa.get_size();

   if (m_applicationa.is_empty() && m_bFinalizeIfNoApplication)
   {

      set_finish();

   }

}


//::e_status application_container::request_exit_application()
//{
//
//   if (m_bProcessingApplicationExitRequest)
//   {
//
//      return ::success_scheduled;
//
//   }
//
//   m_bProcessingApplicationExitRequest = true;
//
//   fork([this]()
//      {
//
//         try
//         {
//
//            exit_application();
//
//         }
//         catch (...)
//         {
//
//         }
//
//         m_bProcessingApplicationExitRequest = false;
//
//      });
//
//   return ::success;
//
//}


::e_status application_container::exit_application()
{

   auto applicationa = m_applicationa;

   for (auto & papp : applicationa)
   {

      try
      {

         auto estatus = papp->can_exit_application();

         if(!estatus)
         {

            return estatus;

         }

      }
      catch (...)
      {

      }

   }

   multiple_lock multiplelock;

   for (auto & papp : applicationa)
   {

      __construct_new(papp->m_peventFinished);

      multiplelock.m_synchronizationa.add(papp->m_peventFinished);

   }

   for (auto & papp : applicationa)
   {

      fork([papp]()
         {

            papp->m_bProcessingApplicationExitRequest = true;

            try
            {

               papp->exit_application();

            }
            catch (...)
            {

            }

            papp->m_bProcessingApplicationExitRequest = false;


         });

   }

   multiplelock.lock();

   //int i = 50;

   //while (i > 0 && applicationa.get_size() > 0)
   //{

   //   for (index j = 0; j < applicationa.get_size(); )
   //   {

   //      auto pappItem = applicationa[j];

   //      if (!pappItem || pappItem->m_bFranceExit)
   //      {

   //         applicationa.erase_at(j);

   //      }
   //      else
   //      {

   //         FORMATTED_TRACE("Waiting France Exit of %s", typeid(pappItem.m_p).name());

   //         j++;

   //      }

   //   }

   //   task_sleep(500_ms);

   //   i--;

   //}



   destroy();

   return ::success;

}


application_array & application_container::applicationa()
{

   return m_applicationa;

}


application_array application_container::get_applicationa()
{

   synchronous_lock synchronouslock(mutex());

   return m_applicationa;

}


//void application_container::app_add(::application * papp)
//{
//
//   if (::is_null(papp))
//   {
//
//      return;
//
//   }
//
//   synchronous_lock synchronouslock(mutex());
//
//   if (papp == this)
//   {
//
//      return;
//
//   }
//
//   m_applicationa.add_unique(papp);
//
//}
//
//
//void application_container::app_erase(::application * papp)
//{
//
//   synchronous_lock synchronouslock(mutex());
//
//   if (m_applicationa.is_set())
//   {
//
//      m_applicationa.erase(papp);
//
//   }
//
//}


__pointer(::application) application_container::instantiate_application(const char * pszAppId, ::create * pcreate)
{

   INFORMATION("apex::application::instantiate_application");

   ::e_status estatus = ::success;

   __pointer(::application) papp;

   string strAppId(pszAppId);

   if (strAppId == "session")
   {

      papp = create_platform(get_application()->get_session());

      if (!papp)
      {

         return nullptr;

      }

      papp->m_strAppId = "session";

   }
   else
   {

      auto psystem = get_system()->m_papexsystem;

      if (psystem->m_papplicationStartup.is_set())
      {

         if (psystem->m_papplicationStartup->m_strAppId != strAppId)
         {

            INFORMATION("Wrong papplication Data Type");

            return nullptr;

         }

         papp = psystem->m_papplicationStartup;

         __refer(psystem->m_papplicationMain, psystem->m_papplicationStartup.get());

         __unbind(psystem, m_papplicationStartup OBJECT_REFERENCE_COUNT_DEBUG_COMMA_P_NOTE(psystem, ""));

      }
      else
      {

         papp = psystem->new_application(strAppId);

         estatus = ::g_pappcore->initialize_application(papp, this);

      }

      if (!papp)
      {

         return nullptr;

      }

      strAppId = papp->m_strAppId;

      if (papp->m_strInstallToken.is_empty())
      {

         papp->m_strInstallToken = papp->m_strAppId;

      }

   }

   papp->initialize(this);

   on_instantiate_application(papp);

   if (pcreate != nullptr)
   {

      papp->on_command_create(pcreate);

   }
   else
   {

      papp->payload("SessionSynchronizedInput") = true;

      papp->payload("NativeWindowFocus") = true;

   }

   return papp;

}


__pointer(::application) application_container::create_application(const char * pszAppId, bool bSynch, ::create * pcreate)
{

   __pointer(::application) papp = instantiate_application(pszAppId, pcreate);

   if (!papp)
   {

      return nullptr;

   }

   if (!papp->start_application(bSynch, pcreate))
   {

      return nullptr;

   }

   return papp;

}


__pointer(::application) application_container::create_platform(::apex::session * psession)
{

   return nullptr;

}





void application_container::on_instantiate_application(::application* papp)
{


}


__pointer(::application) application_container::assert_running(const char * pszAppId, const ::string & strLocale, const ::string & strSchema)
{

  __pointer(::application) papp;

  {

     synchronous_lock synchronouslock(mutex());

     papp = m_applicationa.find_running_defer_try_quit_damaged(pszAppId);

  }

  if (papp.is_null())
  {

     __pointer(::create) spcreate(e_create_new, this);

     papp = start_application(pszAppId, spcreate, strLocale, strSchema);

  }

  return papp;

}




__pointer(::application) application_container::start_application(const char * pszAppId, ::create * pcreate, const ::string & strLocale, const ::string & strSchema)
{

   string strApp(pszAppId);

   auto papp = application_get(strApp, true, true, pcreate);

   if (!papp)
   {

      return nullptr;

   }

   if (pcreate->m_pcommandline->m_varQuery.has_property("install")
      || pcreate->m_pcommandline->m_varQuery.has_property("uninstall"))
   {

      m_applicationa.erase(papp);

      return nullptr;

   }

   string strBuild;

   ::file::path pathExe = m_psystem->m_pacmefile->executable();

   auto psystem = get_system()->m_papexsystem;

   if (!m_psystem->m_papexsystem->m_papexnode->is_application_installed(pathExe, strApp, strBuild, psystem->get_system_platform(),
      psystem->get_system_configuration(), strLocale, strSchema))
   {

      if (papp->m_bRequiresInstallation)
      {

         bool bConvenientInstallation = false;

#ifdef __DEBUG

         bConvenientInstallation = true;

#endif // __DEBUG

         if (is_debugger_attached() || bConvenientInstallation)
         {

            papp->do_install();

         }
         else
         {

            //output_error_message("papplication \"" + strApp + "\"\nat path \"" + pathExe + "\"\n is not installed.");
            output_debug_string("papplication \"" + strApp + "\"\nat path \"" + pathExe + "\"\n is not installed.");

            return nullptr;

         }

      }

   }

   if (pcreate->m_pcommandline)
   {

      pcreate->m_pcommandline->m_eventReady.ResetEvent();

   }

   m_applicationa.add_unique(papp);

   m_papplicationCurrent = papp;

   if (!papp->on_start_application())
   {

      INFORMATION("One or more errors occurred during on_start_application execution.");

   }


   //      if (strApp != "session")
   //      {

   psystem->merge_accumulated_on_open_file(pcreate);

   //papp->do_request(pcreate);
   papp->post_element(e_message_system, e_system_message_create, pcreate);

   //         while (task_get_run())
   //         {
   //
   //            if (pcreate->m_pcommandline->m_eventReady.wait(::duration(84)).signaled())
   //               break;
   //
   //         }
   //
   //      }
   //
   return papp;

}


::application * application_container::application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate)
{

   __pointer(::application) papp;

   if(m_applicationa.lookup(pszAppId,papp))
   {

      return papp;

   }

   if (!bCreate)
   {

      return nullptr;

   }

   papp = nullptr;

   try
   {

      papp = create_application(pszAppId, bSynch, pcreate);

   }
   catch (const ::exception & e)
   {

      if (handle_exception(e))
      {

         papp = nullptr;

      }

   }
   catch(...)
   {

      papp = nullptr;

   }

   if (papp == nullptr)
   {

      return nullptr;

   }

   add_application(papp);

   return papp;

}



