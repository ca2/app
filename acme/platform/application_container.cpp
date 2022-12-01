#include "framework.h"
#include "application_container.h"
#include "request.h"
#include "node.h"
#include "application.h"
#include "system.h"
#include "acme/constant/message.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/parallelization/multiple_lock.h"
#include "acme/parallelization/synchronous_lock.h"


namespace acme
{


   application_container::application_container()
   {

      m_bFinalizeIfNoApplicationSetting = true;
      m_bFinalizeIfNoApplication = false;

   }


   application_container::~application_container()
   {

   }


   void application_container::add_application(::acme::application* papplication)
   {

      if (!::is_set(papplication))
      {

         return;

      }

      if (m_applicationa.is_empty())
      {

         m_bFinalizeIfNoApplication = m_bFinalizeIfNoApplicationSetting;

      }

      m_applicationa.add(papplication);

   }


   void application_container::erase_application(::acme::application* papplication)
   {

      auto iSizeBefore = m_applicationa.get_size();

      m_applicationa.erase(papplication);

      auto iSizeAfter = m_applicationa.get_size();

      if (m_applicationa.is_empty() && m_bFinalizeIfNoApplication)
      {

         set_finish();

      }

   }


   //void application_container::request_exit_application()
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


   void application_container::exit_application()
   {

      //auto applicationa = m_applicationa;

      //for (auto & papplication : applicationa)
      //{

      //   try
      //   {

      //      auto bCanExit = papplication->can_exit_application();

      //      if (!bCanExit)
      //      {

      //         return;

      //      }

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      //multiple_lock multiplelock;

      //for (auto & papplication : applicationa)
      //{

      //   __construct_new(papplication->m_peventFinished);

      //   multiplelock.m_synchronizationa.add(papplication->m_peventFinished);

      //}

      //for (auto & pappapplicationp : applicationa)
      //{

      //   fork([papplication]()
      //      {

      //         papplication->m_bProcessingApplicationExitRequest = true;

      //         try
      //         {

      //            papplication->exit_application();

      //         }
      //         catch (...)
      //         {

      //         }

      //         papplication->m_bProcessingApplicationExitRequest = false;


      //      });

      //}

      //multiplelock.lock();

      ////int i = 50;

      ////while (i > 0 && applicationa.get_size() > 0)
      ////{

      ////   for (index j = 0; j < applicationa.get_size(); )
      ////   {

      ////      auto pappItem = applicationa[j];

      ////      if (!pappItem || pappItem->m_bFranceExit)
      ////      {

      ////         applicationa.erase_at(j);

      ////      }
      ////      else
      ////      {

      ////         FORMATTED_TRACE("Waiting France Exit of %s", typeid(pappItem.m_p).name());

      ////         j++;

      ////      }

      ////   }

      ////   task_sleep(500_ms);

      ////   i--;

      ////}



      //destroy();

      /////return ::success;

   }


   application_array& application_container::applicationa()
   {

      return m_applicationa;

   }


   application_array application_container::get_applicationa()
   {

      synchronous_lock synchronouslock(this->synchronization());

      return m_applicationa;

   }


   //void application_container::app_add(::apex::application * papp)
   //{
   //
   //   if (::is_null(papp))
   //   {
   //
   //      return;
   //
   //   }
   //
   //   synchronous_lock synchronouslock(this->synchronization());
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
   //void application_container::app_erase(::apex::application * papp)
   //{
   //
   //   synchronous_lock synchronouslock(this->synchronization());
   //
   //   if (m_applicationa.is_set())
   //   {
   //
   //      m_applicationa.erase(papp);
   //
   //   }
   //
   //}


   ::pointer<::acme::application>application_container::instantiate_application(const ::string& strAppId)
   {

      INFORMATION("apex::application::instantiate_application");

      ::e_status estatus = ::success;

      ::pointer<::acme::application> papplication;

      //if (strAppId == "session")
      //{

      //   papp = create_platform(get_app()->get_session());

      //   if (!papp)
      //   {

      //      return nullptr;

      //   }

      //   papp->m_strAppId = "session";

      //}
      //else
      //{

      auto psystem = acmesystem();

      if (::is_set(psystem->m_pacmeapplication))
      {

         string strStartupApplicationAppId = psystem->m_pacmeapplication->m_strAppId;

         if (strStartupApplicationAppId != strAppId ||
            !strAppId.begins(strStartupApplicationAppId))
         {

            INFORMATION("Wrong papp Data Type");

            return nullptr;

         }

         papplication = psystem->m_pacmeapplication;

      }
      //else
      //{

      //   papp = psystem->new_app(strAppId);

      //   ::acme::application::g_p->initialize_application(papp, this);

      //}

      if (!papplication)
      {

         return nullptr;

      }

      //strAppId = papp->m_strAppId;

      if (papplication->m_strInstallToken.is_empty())
      {

         papplication->m_strInstallToken = papplication->m_strAppId;

      }

      //   }

      papplication->initialize(this);

      on_instantiate_application(papplication);

      /* if (prequest != nullptr)
       {

          papp->post_request(prequest);

       }
       else
       {

          papp->payload("SessionSynchronizedInput") = true;

          papp->payload("NativeWindowFocus") = true;

       }*/

      return papplication;

   }


   ::pointer<::acme::application>application_container::create_application(const ::string& strAppId, ::request* prequest)
   {

      auto papplication = instantiate_application(strAppId);

      if (!papplication)
      {

         return nullptr;

      }

      papplication->start_application(prequest);

      return papplication;

   }


   //::pointer<::apex::application>application_container::create_platform(::apex::session * psession)
   //{

   //   return nullptr;

   //}


   void application_container::on_instantiate_application(::acme::application* papplication)
   {


   }


   ::pointer<::acme::application>application_container::assert_running(const ::string& strAppId)
   {

      ::pointer<::acme::application>papplication;

      {

         synchronous_lock synchronouslock(this->synchronization());

         papplication = m_applicationa.find_running_defer_try_quit_damaged(strAppId);

      }

      if (papplication.is_null())
      {

         ::pointer<::request> prequest(e_create_new, this);

         papplication = create_application(strAppId, prequest);

      }

      return papplication;

   }


   //   ::pointer<::acme::application>application_container::start_application(const ::string & strAppId, ::request * prequest)
   //   {
   //
   //      auto papplication = application_get(strAppId, true, true, prequest);
   //
   //      if (!papplication)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      if (prequest->has_property("install")
   //         || prequest->has_property("uninstall"))
   //      {
   //
   //         m_applicationa.erase(papplication);
   //
   //         return nullptr;
   //
   //      }
   //
   //      string strBuild;
   //
   //      ::file::path pathExe = acmefile()->module();
   //
   //      auto psystem = acmesystem()->m_papexsystem;
   //
   //      if (!acmesystem()->m_papexsystem->m_papexnode->is_application_installed(pathExe, strApp, strBuild, psystem->get_system_platform(),
   //         psystem->get_system_configuration(), strLocale, strSchema))
   //      {
   //
   //         if (papp->m_bRequiresInstallation)
   //         {
   //
   //            bool bConvenientInstallation = false;
   //
   //#ifdef __DEBUG
   //
   //            bConvenientInstallation = true;
   //
   //#endif // __DEBUG
   //
   //            if (is_debugger_attached() || bConvenientInstallation)
   //            {
   //
   //               papp->do_install();
   //
   //            }
   //            else
   //            {
   //
   //               //output_error_message("papp \"" + strApp + "\"\nat path \"" + pathExe + "\"\n is not installed.");
   //               output_debug_string("papp \"" + strApp + "\"\nat path \"" + pathExe + "\"\n is not installed.");
   //
   //               return nullptr;
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      if (pcreate)
   //      {
   //
   //         pcreate->m_eventReady.ResetEvent();
   //
   //      }
   //
   //      m_applicationa.add_unique(papp);
   //
   //      m_pappCurrent = papp;
   //
   //      if (!papp->on_start_application())
   //      {
   //
   //         INFORMATION("One or more errors occurred during on_start_application execution.");
   //
   //      }
   //
   //
   //      //      if (strApp != "session")
   //      //      {
   //
   //      //psystem->merge_accumulated_on_open_file(pcreate);
   //
   //      //papp->do_request(pcreate);
   //      papp->post_element(e_message_system, e_system_message_create, pcreate);
   //
   //      //         while (task_get_run())
   //      //         {
   //      //
   //      //            if (pcreate->m_eventReady.wait(::time(84)).signaled())
   //      //               break;
   //      //
   //      //         }
   //      //
   //      //      }
   //      //
   //      return papp;
   //
   //   }


   ::acme::application* application_container::get_application(const ::string& strAppId, bool bCreate, ::request* prequest)
   {

      ::pointer<::acme::application>papplication;

      if (m_applicationa.lookup(strAppId, papplication))
      {

         return papplication;

      }

      if (!bCreate)
      {

         return nullptr;

      }

      papplication = nullptr;

      try
      {

         papplication = create_application(strAppId, prequest);

      }
      catch (const ::exception& e)
      {


         handle_exception(e);
         //{

         //   papp = nullptr;

         //}

      }
      catch (...)
      {

         papplication = nullptr;

      }

      if (papplication == nullptr)
      {

         return nullptr;

      }

      add_application(papplication);

      return papplication;

   }


} // namespace acme



