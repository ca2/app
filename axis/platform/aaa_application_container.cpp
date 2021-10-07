#include "framework.h"
#include "aura/platform/app_core.h"


application_container::application_container()
{
   
   m_bFinalizeIfNoApplicationSetting = true;
   m_bFinalizeIfNoApplication = false;

}


application_container::~application_container()
{

}


void application_container::app_add(::aura::application * papp)
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

}


void application_container::app_erase(::aura::application * papp)
{

   m_applicationa.erase(papp);

   if (m_applicationa.isEmpty() && m_bFinalizeIfNoApplication)
   {

      set_finish();

   }

}



void application_container::request_exit()
{

   fork([this]()
      {

         auto applicationa = m_applicationa;

         for (auto & papp : applicationa)
         {

            try
            {

               if (!papp->_001OnAgreeExit())
               {

                  return;

               }

            }
            catch (...)
            {

            }

         }

         for (auto & papp : applicationa)
         {

            papp->m_bFranceExit = false;

         }

         for (auto & papp : applicationa)
         {

            fork([papp]()
               {

                  papp->_001FranceExit();

               });

         }

         int i = 50;

         while (i > 0 && applicationa.get_size() > 0)
         {

            for (index j = 0; j < applicationa.get_size(); )
            {

               auto pappItem = applicationa[j];

               if (!pappItem || pappItem->m_bFranceExit)
               {

                  applicationa.erase_at(j);

               }
               else
               {

                  TRACE("Waiting France Exit of %s", typeid(pappItem.m_p).name());

                  j++;

               }

            }

            task_sleep(500_ms);

            i--;

         }

         destroy();

      });

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


//void application_container::app_add(::aura::application * papp)
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
//void application_container::app_erase(::aura::application * papp)
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


__pointer(::aura::application) application_container::instantiate_application(const ::string & pszAppId, ::create * pcreate)
{

   INFORMATION("aura::application::instantiate_application");

   __pointer(::aura::application) papp;

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

      if (psystem->m_papplicationStartup.is_set())
      {

         if (psystem->m_papplicationStartup->m_strAppId != strAppId)
         {

            TRACE("Wrong papplication Data Type");

            return nullptr;

         }

         papp = psystem->m_papplicationStartup;

         psystem->m_papplicationStartup.release();

      }
      else
      {

         papp = psystem->get_new_application(this, strAppId);

      }

      set_context_app(papp);

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


__pointer(::aura::application) application_container::create_application(const ::string & pszAppId, bool bSynch, ::create * pcreate)
{

   __pointer(::aura::application) papp = instantiate_application(pszAppId, pcreate);

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


__pointer(::aura::application) application_container::create_platform(::aura::session * psession)
{

   return nullptr;

}







__pointer(::aura::application) application_container::assert_running(const ::string & pszAppId, const ::string & strLocale, const ::string & strSchema)
{

  __pointer(::aura::application) papp;

  {

     synchronous_lock synchronouslock(mutex());

     papp = m_applicationa.find_running_defer_try_quit_damaged(pszAppId);

  }

  if (papp.is_null())
  {

     __pointer(::create) spcreate(e_create_new);

     papp = start_application(pszAppId, spcreate, strLocale, strSchema);

  }

  return papp;

}




__pointer(::aura::application) application_container::start_application(const ::string & pszAppId, ::create * pcreate, const ::string & strLocale, const ::string & strSchema)
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

   ::file::path pathExe = m_psystem->m_pacmepath->app_module();

   if (!is_application_installed(pathExe, strApp, strBuild, psystem->get_system_platform(),
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

            output_error_message("papplication \"" + strApp + "\"\nat path \"" + pathExe + "\"\n is not installed.");

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

      TRACE("One or more errors occurred during on_start_application execution.");

   }


   //      if (strApp != "session")
   //      {

   psystem->merge_accumulated_on_open_file(pcreate);

   papp->do_request(pcreate);

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





::aura::application * application_container::application_get(const ::string & pszAppId, bool bCreate, bool bSynch, ::create * pcreate)
   {

      __pointer(::aura::application) papp;

      if(m_applicationa.lookup(pszAppId,papp))
      {

         return papp;

      }

      if(!bCreate)
         return nullptr;

      papp = nullptr;

      try
      {

         papp = create_application(pszAppId, bSynch, pcreate);

      }
      catch (const ::exception & e)
      {

         if (handle_exception(pe))
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

      app_add(papp);

      return papp;

   }

