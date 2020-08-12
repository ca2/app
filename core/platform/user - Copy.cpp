#include "framework.h"
#include "core/xml.h"
#include "aura/id.h"
#include "aura/platform/version.h"
#include "aura/platform/machine_event_data2.h"
#include "aura/platform/machine_event2.h"
#include "aura/platform/machine_event_central2.h"
#include "aura/platform/app_core.h"
#include "aura/platform/profiler2.h"


int windows_desktop1_main(HINSTANCE hInstance, int nCmdShow);





#include "aura/node/_node.h"

#ifdef WINDOWS_DESKTOP

#include "aura/os/windows/_.h"

#endif


extern ::app_core * g_pappcore;


//extern "C"
//{
//
//   typedef void FN_factory_exchange();
//
//   typedef FN_factory_exchange * PFN_factory_exchange;
//
//}

//PFN_factory_exchange g_pfnfactoryDraw2d = nullptr;
//
//
//PFN_factory_exchange get_draw2d_factory_exchange()
//{
//
//   return g_pfnfactoryDraw2d;
//
//}
//
//
//void set_draw2d_factory_exchange(PFN_factory_exchange pfnfactoryDraw2d)
//{
//
//   g_pfnfactoryDraw2d = pfnfactoryDraw2d;
//
//}



#ifdef WINDOWS_DESKTOP

CLASS_DECL_CORE void windows_install_crash_dump_reporting(::object * pobject);

#endif


#ifdef MACOS
::file::path macos_app_path(string strApp);
//void ns_app_terminate();
// 0x00010000 NSWorkspaceLaunchAsync
// 0x00080000 NSWorkspaceLaunchNewInstance
void ns_launch_app(const char * psz, const char ** argv, int iFlags);
#endif

#if defined(LINUX)
#ifdef _GNU_SOURCE
#undef _GNU_SOURCE

//#include "aura/node/ansios/ansios.h"
#include "aura/node/linux/_linux.h"

//#include <X11/cursorfont.h>
#include <sys/time.h>
#include <link.h>
#include <pthread.h>

#endif
#define _GNU_SOURCE
//#include <link.h>
#elif defined(__APPLE__)
//#include <dlfcn.h>
#elif defined(ANDROID)

//#include "aura/node/ansios/ansios.h"
#include "aura/node/android/_.h"

//#elif defined(WINDOWS_DESKTOP)

//#include "aura/node/windows/windows_registry.h"

#endif


#if defined(APPLE_IOS) || defined(_UWP)
CLASS_DECL_CORE int ui_open_url(const char * psz);
#endif


extern void * g_pf1;


namespace core
{



   user2::user2()
   {

   }


   ::estatus user2::initialize(::object * pobjectContext)
   {

      auto estatus = ::aura::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   user2::~user2()
   {

   }


   ::file::path command_find_path(const char * pszCommand)
   {

#ifdef _UWP

      return "";

#else

      string strPath = getenv("PATH");

      string_array straPath;

      straPath.explode(":", strPath);

      for (auto & str : straPath)
      {

         ::file::path path;

         path = str;

         path /= pszCommand;

         if (file_exists(path))
         {

            return path;

         }

      }

      return pszCommand;

#endif

   }
#ifdef WINDOWS_DESKTOP


   class open_browser_enum
   {
   public:

      string                           m_strWindowEnd;
      string                           m_strTopic;
      string                           m_strCounterTopic;
      oswindow                         m_hwnd;
      comparable_array < oswindow >    m_hwndaTopic;
      comparable_array < oswindow >    m_hwndaCounterTopic;

   };


   WINBOOL CALLBACK enum_proc(oswindow hwnd, LPARAM lparam)
   {

      open_browser_enum * penum = (open_browser_enum *)lparam;

      string str = ::str::get_window_text_timeout(hwnd, 1000);

      if (::str::ends_ci(str, penum->m_strWindowEnd))
      {

         penum->m_hwnd = hwnd;

         return FALSE;

      }

      return TRUE;

   }


   WINBOOL CALLBACK enum_proc_ff_topic(oswindow hwnd, LPARAM lparam)
   {

      open_browser_enum * penum = (open_browser_enum *)lparam;

      string str = ::str::get_window_text_timeout(hwnd);

      if (::str::ends_ci(str, penum->m_strTopic))
      {

         penum->m_hwndaTopic.add(hwnd);

      }

      return TRUE;

   }

   WINBOOL CALLBACK enum_proc_ff_counter_topic(oswindow hwnd, LPARAM lparam)

   {

      open_browser_enum * penum = (open_browser_enum *)lparam;


      string str = ::str::get_window_text_timeout(hwnd, 1000);

      if (::str::ends_ci(str, penum->m_strCounterTopic))
      {

         penum->m_hwndaCounterTopic.add(hwnd);

      }

      return TRUE;

   }

#endif




   //::file::path user2::defer_process_path(::file::path path)
   //{

   //   return get_context_application()->get_context_system()->defer_process_path(path, this);

   //}


   //::file::path user2::full_process_path(::file::path path)
   //{

   //   if (!(path & ::file::flag_dont_resolve_alias))
   //   {

   //      path |= ::file::flag_resolve_alias;

   //   }

   //   return get_context_application()->get_context_system()->full_process_path(path, this);

   //}




   //void user2::sync_open_profile_link(string strUrl, string strProfile, string strTarget)
   //{

   //   browser(strUrl, "", strProfile, strTarget);

   //}


   //bool user2::open_link(string strLink, string strProfile, string strTarget)
   //{

   //   if (is_system())
   //   {

   //      if (strLink.begins_ci("mailto:"))
   //      {

   //         return Context.os().file_open(this, strLink);

   //      }

   //      open_profile_link(strLink, strProfile, strTarget);

   //      return true;

   //   }
   //   else
   //   {

   //      return Session.open_link(strLink, strProfile, strTarget);

   //   }

   //   return false;

   //}


   void user2::TermThread(HINSTANCE hInstTerm)
   {

      ::exception::throw_interface_only();

   }



   bool user2::_001OnDDECommand(const char * pcsz)

   {

      ::exception::throw_interface_only();

      return false;

   }



   /*::user::document *  user2::_001OpenDocumentFile(var varFile)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }*/


   //void user2::_001OnFileNew(::message::message * pmessage)
   //{

   //   ::exception::throw_interface_only();

   //}


//bool user2::update_module_paths()
//{


//   if(is_system())
//   {

//      if(!m_pimpl->update_module_paths())
//         return false;


//   }

//   return true;


//}





   //void user2::_001CloseApplication()
   //{

   //   __throw(todo());

   //}












   //void user2::DoWaitCursor(i32 nCode) // 0 => restore, 1=> begin, -1=> end
   //{

   //   UNREFERENCED_PARAMETER(nCode);

   //}


//   void user2::ShowWaitCursor(bool bShow)
//   {
//
//      if (m_pappimpl.is_null())
//         return;
//
//      m_pappimpl->ShowWaitCursor(bShow);
//
//
//   }
//
//

//   string CLASS_DECL_CORE user2::get_cred(const string & strRequestUrl, const ::rect & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive)
// {

//  __throw(not_implemented());

//}




   bool user2::get_temp_file_name_template(string & strRet, const char * lpszName, const char * pszExtension, const char * pszTemplate)
   {

      __throw(not_implemented());

      return false;

   }


   bool user2::get_temp_file_name(string & strRet, const char * lpszName, const char * pszExtension)
   {

      return get_temp_file_name_template(strRet, lpszName, pszExtension, nullptr);

   }


   bool user2::process_exception(::exception_pointer pe)
   {

      return ::thread::process_exception(pe);

   }


   //bool user2::final_handle_exception(::exception::exception * pe)
   //{

   //   UNREFERENCED_PARAMETER(pe);

   //   //linux      exit(-1);

   //   if (!is_system())
   //   {

   //      // get_context_application() may be it self, it is ok...
   //      if (System.final_handle_exception(pe))
   //         return true;


   //   }

   //   return false;
   //}


   ::estatus     user2::main()
   {

      INFO("aura::user2::main");

      try
      {

         m_bReady = true;

         m_estatus = on_run();

//         if(m_iErrorCode != 0)
//         {
//
//            dappy(string(typeid(*this).name()) + " : on_run failure : " + __str(m_iErrorCode));
//
//            ::output_debug_string("user2::main on_run termination failure\n");
//
//         }

      }
      catch (::exception_pointer pe)
      {

         if (!handle_exception(pe))
         {


         }

      }
      catch (...)
      {

         //dappy(string(typeid(*this).name()) + " : on_run general exception");

      }

      return m_estatus;

   }


   ::estatus user2::init_thread()
   {

      try
      {

         Session.add_reference(this);

      }
      catch (...)
      {

      }

      try
      {

         if (!pre_run())
         {

            return false;

         }

      }
      catch (::exception_pointer pe)
      {

         handle_exception(pe);

         return false;

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   void user2::term_thread()
   {

      INFO("aura::user2::term_thread");

      m_tickHeartBeat.Now();

      try
      {

         pos_run();

      }
      catch (...)
      {

      }

      ::thread::term_thread();

   }


   ::estatus user2::pre_run()
   {

      INFO("aura::user2::pre_run");

      try
      {

         m_tickHeartBeat.Now();

         if(!application_pre_run())
         {

            m_bReady = true;

            return false;

         }

         //    if(!check_install())
         //    {

         //       m_bReady = true;

         //       return false;

         //    }

//         if(!is_system() && !is_session())
//         {
//
//            if(!is_installed())
//            {
//
//
//            }
//
//         }

         //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", MB_ICONINFORMATION);

         if (!initial_check_directrix())
         {

            m_bReady = true;

            return false;

         }

         m_tickHeartBeat.Now();

         if (!os_native_bergedge_start())
         {

            m_bReady = true;

            return false;

         }

         INFO("aura::user2::pre_run success");

         return true;

      }
      catch (::exception_pointer pe)
      {

         handle_exception(pe);

      }
      catch (...)
      {

         INFO("aura::user2::pre_run exception.4");

      }

      return false;

   }


//   ::estatus user2::on_run()
//   {
//
//      ::estatus     estatus = ::success;
//
//      try
//      {
//
//         application_message message(application_message_begin);
//
//         route_message(&message);
//
//      }
//      catch (...)
//      {
//
//      }
//
//      //thisstart << m_iErrorCode;
//
//      thread * pthread = ::get_thread();
//
//      install_message_routing(pthread);
//
//      //thisok << 1 << m_iErrorCode;
//
//      //try
//      //{
//
//      m_bReady = true;
//
//      //   if (m_pevAppBeg != nullptr)
//      //   {
//
//      //      m_pevAppBeg->SetEvent();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      //if(::is_set(get_context_system()))
//      //{
//
//      //   get_context_system()->add_reference(this);
//
//      //}
//
//      //if(::is_set(get_context_session()))
//      //{
//
//      //   get_context_session()->add_reference(this);
//
//      //}
//
//      //if(::is_set(m_pappParent))
//      //{
//
//      //   m_pappParent->__add_reference(this);
//
//      //}
//
//      if (::is_set(m_pappParent))
//      {
//
//         m_pappParent->add_reference(this);
//
//      }
//
//      try
//      {
//
//resume_on_exception:
//
//         try
//         {
//
//            estatus = run();
//
//         }
//         catch (::exception_pointer pe)
//         {
//
//            if (handle_exception(e))
//            {
//
//               goto resume_on_exception;
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }
//
//      //try
//      //{
//
//      //   if (m_pevAppEnd != nullptr)
//      //   {
//
//      //      m_pevAppEnd->SetEvent();
//
//      //   }
//
//      //}
//      //catch (...)
//      //{
//
//      //}
//
//      return estatus;
//
//   }


   void user2::on_pos_run_thread()
   {

      try
      {

         m_pipi.release();

      }
      catch (...)
      {

      }


      ::thread::on_pos_run_thread();

      sync_lock sl(mutex());

      //try
      //{

      //   for (auto & papp : m_applicationa)
      //   {

      //      try
      //      {

      //         if (papp != this && papp->get_context_application() == this)
      //         {

      //            set_context_object(nullptr);

      //         }

      //         if (is_session())
      //         {

      //            ::aura::session * psessionThis = dynamic_cast <::aura::session *>(this);

      //            if (papp->get_context_session() == psessionThis && papp != this)
      //            {

      //               papp->get_context_session() = nullptr;

      //            }

      //         }

      //         if (is_system())
      //         {

      //            ::aura::system * psystemThis = dynamic_cast <::aura::system *>(this);

      //            if (papp->get_context_system() == psystemThis && papp != this)
      //            {

      //               papp->get_context_system() = nullptr;

      //            }

      //         }

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

   }


   //void user2::release_parents()
   //{

   //   try
   //   {

   //      if(::is_set(get_context_system()))
   //      {

   //         get_context_system()->appptra_remove(this);

   //      }

   //   }
   //   catch(...)
   //   {

   //   }

   //   try
   //   {

   //      if(::is_set(get_context_session()))
   //      {

   //         get_context_session()->appptra_remove(this);

   //      }

   //   }
   //   catch(...)
   //   {

   //   }

   //   ::thread::release_parents();

   //}


   void user2::pos_run()
   {

      INFO("aura::user2::pos_run");

      try
      {

         m_tickHeartBeat.Now();

         application_pos_run();

         //xxdebug_box("pre_run 1 ok", "pre_run 1 ok", MB_ICONINFORMATION);

      }
      catch (...)
      {

         INFO("aura::user2::pos_run exception.4");

      }

   }


   ::estatus user2::init_instance()
   {

      //xxdebug_box("check_exclusive", "check_exclusive", MB_ICONINFORMATION);

      if (m_bIpi)
      {

         try
         {

            m_pipi = create_ipi();

         }
         catch (...)
         {

         }

         if (!m_pipi)
         {

            return ::error_failed;

         }

         auto estatus = m_pipi->initialize(this);

         if (!estatus)
         {

            return estatus;

         }

      }

      INFO("aura::user2::init_application .1");

      bool bHandled = false;

      if (!check_exclusive(bHandled))
      {

         if (!bHandled &&
            (!has_property("install")
            && !has_property("uninstall")))
         {

            duration durationTimeout;

//#ifdef __DEBUG
//
//          durationTimeout = minutes(5);
//
//#else //__DEBUG

            durationTimeout = 5_s;

//#endif //!__DEBUG

            var var;

            var["message"] = "Another instance of \"" + m_strAppName + "\" is already running (and some exclusivity policy is active).";

//          var["prefix_html"] = "<img src=\"matter://system/exclusive.png\" width=80 height=80 style=\"display:block;\"><br/><br/>";

            message_box_timeout(var, m_strAppName, durationTimeout, message_box_icon_asterisk);

            INFO("aura::user2::init_application exit");

            __throw(exit_exception(this));

         }

      }

      INFO("aura::user2::init_application .2");

      if (m_pipi)
      {

         m_pipi->on_new_instance(Context.file().module(), Context.os().get_pid());

      }

      //xxdebug_box("check_exclusive ok", "check_exclusive ok", MB_ICONINFORMATION);

      if (m_bInitializeDataCentral)
      {


         ::file::path pathDatabase;

         if (is_system())
         {

            pathDatabase = Context.dir().appdata() / "system.sqlite";

         }
         else if (is_session())
         {

            pathDatabase = Context.dir().appdata() / "session.sqlite";

         }
         else
         {

            pathDatabase = Context.dir().appdata() / "app.sqlite";

         }

         auto estatus = m_psimpledb->initialize_simpledb_server(this, pathDatabase);

         if (!estatus)
         {

            m_result.add(estatus);

            return false;

         }

         set_data_server(m_psimpledb);

      }

      //m_bAxisInitializeInstanceResult = true;

      INFO("axis::user2::init_instance success");

      auto estatus = create_impact_system();

      if (failed(estatus))
      {

         return false;

      }


      if (!is_system() && !is_session())
      {

         string str;
         // if system locale has changed (compared to last recorded one by aura)
         // use the system locale
         if (data_get({ "system_locale", true }, str))
         {

            if (str.has_char())
            {

               if (str != get_locale())
               {

                  try
                  {

                     data_set({ "system_locale", true }, get_locale());

                     data_set({ "locale", true }, get_locale());

                  }
                  catch (...)
                  {

                  }

               }

            }

         }
         else
         {

            data_set({ "system_locale", true }, get_locale());

         }

         if (value("locale").get_count() > 0)
         {

            str = value("locale").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::source_database);

         }
         else if (value("lang").get_count() > 0)
         {

            str = value("lang").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::source_database);

         }
         else if (data_get({ "locale", true }, str))
         {

            if (str.has_char())
            {

               set_locale(str, ::source_database);

            }

         }
         // if system schema has changed (compared to last recorded one by aura)
         // use the system schema
         if (data_get({ "system_schema", true }, str))
         {

            if (str.has_char())
            {

               if (str != get_schema())
               {

                  try
                  {

                     data_set({ "system_schema", true }, get_schema());

                     data_set({ "schema", true }, get_schema());

                  }
                  catch (...)
                  {

                  }

               }

            }

         }
         else
         {

            data_set({ "system_schema", true }, get_schema());

         }

         if (value("schema").get_count() > 0)
         {

            str = value("schema").stra()[0];

            data_set({ "system_schema", true }, str);

            data_set({ "schema", true }, str);

            set_schema(str, ::source_database);

         }
         else if (data_get({ "schema", true }, str))
         {

            if (str.has_char())
            {

               set_schema(str, ::source_database);

            }

         }

         data_pulse_change({ "ca2.savings", true }, nullptr);

         Sys(this).appa_load_string_table();

      }
      if (!is_system() && !is_session())
      {

         string str;
         // if system locale has changed (compared to last recorded one by aura)
         // use the system locale
         if (data_get({ "system_locale", true }, str))
         {

            if (str.has_char())
            {

               if (str != get_locale())
               {

                  try
                  {

                     data_set({ "system_locale", true }, get_locale());

                     data_set({ "locale", true }, get_locale());

                  }
                  catch (...)
                  {

                  }

               }

            }

         }
         else
         {

            data_set({ "system_locale", true }, get_locale());

         }

         if (value("locale").get_count() > 0)
         {

            str = value("locale").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::source_database);

         }
         else if (value("lang").get_count() > 0)
         {

            str = value("lang").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::source_database);

         }
         else if (data_get({ "locale", true }, str))
         {

            if (str.has_char())
            {

               set_locale(str, ::source_database);

            }

         }
         // if system schema has changed (compared to last recorded one by aura)
         // use the system schema
         if (data_get({ "system_schema", true }, str))
         {

            if (str.has_char())
            {

               if (str != get_schema())
               {

                  try
                  {

                     data_set({ "system_schema", true }, get_schema());

                     data_set({ "schema", true }, get_schema());

                  }
                  catch (...)
                  {

                  }

               }

            }

         }
         else
         {

            data_set({ "system_schema", true }, get_schema());

         }

         if (value("schema").get_count() > 0)
         {

            str = value("schema").stra()[0];

            data_set({ "system_schema", true }, str);

            data_set({ "schema", true }, str);

            set_schema(str, ::source_database);

         }
         else if (data_get({ "schema", true }, str))
         {

            if (str.has_char())
            {

               set_schema(str, ::source_database);

            }

         }

         data_pulse_change({ "ca2.savings", true }, nullptr);

         Sys(this).appa_load_string_table();

      }
      return true;

   }


   void user2::term_instance()
   {


   }

   ::estatus user2::ca_init3()
   {

      application_message message(application_message_init3);

      route_message(&message);

      return message.m_bOk;

   }


   void user2::ca_process_term()
   {

      application_message message(application_message_process_term);

      route_message(&message);

      //return message.m_bOk;

   }


   void user2::TermApplication()
   {


   }


   ::estatus user2::application_pre_run()
   {

      INFO("aura::user2::application_pre_run");

#ifdef WINDOWS_DESKTOP

      MESSAGE msg;

      // Create Windows Message Queue
      ::PeekMessageA(&msg, nullptr, 0, 0xffff, 0);

      if (!is_system() && is_true("SessionSynchronizedInput"))
      {

         ::AttachThreadInput(GetCurrentThreadId(), (u32)System.get_os_int(), TRUE);

      }

#endif

      m_tickHeartBeat.Now();

      try
      {

         if (!InitApplication())
         {

            return false;

         }

      }
      catch (::exit_exception * pe)
      {

         throw pe;

      }
      catch (const ::exception::exception * pe)
      {

         //thisexc << 1 << m_iErrorCode;

         ::aura::del(pe);

         return false;

      }
      catch (...)
      {

         //thisexcall << 1 << m_iErrorCode;

         return false;

      }

      m_tickHeartBeat.Now();

      try
      {

         if (!process_init())
         {

            return false;

         }

      }
      catch (::exit_exception * pe)
      {

         throw pe;

      }
      catch (const ::exception::exception * pe)
      {

         ::aura::del(pe);

         return false;

      }
      catch (...)
      {

         return false;

      }

      System.install_progress_add_up();

      m_tickHeartBeat.Now();

      try
      {

         if (!init_application())
         {

            return false;

         }

      }
      catch (::exception_pointer pe)
      {

         handle_exception(pe);

         return false;

      }
      catch (...)
      {

         return false;

      }

      m_tickHeartBeat.Now();

      try
      {

         if (!is_system() && !is_session())
         {

            if (System.is_true("uninstall"))
            {

               do_uninstall();

               return false;

            }
            else if (System.is_true("install"))
            {

               do_install();

               return false;

            }

         }

         if (!init_instance())
         {

            return false;

         }

         on_update_matter_locator();

      }
      catch (exit_exception * pexception)
      {

         __rethrow(pexception);

      }
      catch(::exception::exception * pexception)
      {

         ::exception_pointer esp(pexception);

         return false;

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   void user2::application_pos_run()
   {

      try
      {

         //if (!is_installing() && !is_unstalling())
         {

            term_instance();

         }

      }
      catch (...)
      {

      }

      try
      {

         term_application();

      }
      catch (...)
      {

      }
m_tickHeartBeat.Now();

      try
      {

         process_term();

      }
      catch (...)
      {

      }

      try
      {

         TermApplication();

      }
      catch (...)
      {

      }



   }

   bool user2::InitApplication()
   {

      LoadSysPolicies();

      return true;

   }



   bool user2::do_install()
   {

      if (!on_install())
      {

         ::output_debug_string("Failed at on_install : " + m_strAppId + "\n\n");

         System.m_result.add(error_failed);

         return false;

      }

      string strBuild = m_strBuild;

      string strAppId = m_strAppId;

      //xxdebug_box("on_install1", strAppId, 0);

      system_add_app_install(strAppId, strBuild);


      return true;

   }


   ::estatus user2::initial_check_directrix()
   {

      string strLicense = get_license_id();

      //var & varTopicQuey = System.m_varTopicQuery;

      bool bHasInstall = System.is_true("install");

      bool bHasUninstall = System.is_true("uninstall");

      if (!(bHasInstall || bHasUninstall)
            && m_bLicense
            && strLicense.has_char())
      {

         if (!assert_user_logged_in())
         {
            return false;
         }

         // call user2's is_licensed function
         // because if delay is needed for authentication -
         // or either asking for authentication -
         // current user2 startup won't be
         // exited by timeout.

         i32 iRetry = 1;

retry_license:

         iRetry--;

         if (!Session.is_licensed(strLicense))
         {

            if (iRetry > 0)
               goto retry_license;

            return false;

         }

      }

      INFO("initial_check_directrix : ok (%s)%s\n\n", typeid(*this).name(), m_strAppId.c_str());

//      auto pcommand = m_pcommand;
//
//      if(pcommand.is_set())
//      {
//
//         m_pcommand.release();
//
//         request(pcommand);
//
//         pcommand.release();
//
//         ::output_debug_string("initial_check_directrix : command processed");
//
//      }

      return true;

   }



   bool user2::do_uninstall()
   {

      if (!on_uninstall())
      {

         return false;

//         System.install().remove_spa_start(m_strAppId);

      }

      return true;

   }




   bool user2::on_install()
   {

      if (is_serviceable())
      {

         if (!init_service())
         {

            return false;

         }

         os_start_service();

      }
      else
      {

#ifdef WINDOWS_DESKTOP

         windows_install_crash_dump_reporting(this);

#endif

      }
      return true;

   }


   bool user2::on_uninstall()
   {

      //bool bOk = axis::user2::on_uninstall();

      bool bOk = true;


      if (is_serviceable())
      {

         if (!os_remove_service())
         {

            bOk = false;

         }

      }

      return bOk;

   }


   bool user2::system_add_app_install(const char * pszId, const char * pszBuild)
   {

      // cool install

      string strBuild(pszBuild);

      if (strBuild.is_empty())
      {

         strBuild = "0000-00-00 00:00:00";

      }

      sync_lock sl(System.m_spmutexSystemAppData);

      string strId(pszId);
      string strSystemLocale = System.m_strLocale;
      string strSystemSchema = System.m_strSchema;
      string_array straLocale;
      string_array straSchema;

      straLocale = value("locale");
      straSchema = value("schema");

      ::file::path pathExe = ::file::app_module();

      straLocale.insert_at(0, strSystemLocale);
      straSchema.insert_at(0, strSystemSchema);
      straLocale.insert_at(0, "_std");
      straSchema.insert_at(0, "_std");


      for (index i = 0; i < straLocale.get_count() && i < straSchema.get_count(); i++)
      {

         string strLocale = straLocale[i];

         string strSchema = straSchema[i];

         set_application_installed(pathExe, strId, strBuild, System.get_system_platform(), System.get_system_configuration(), strLocale, strSchema);

      }

      //System.install().remove_spa_start(strId);
      //System.install().add_app_install(strId, strBuild, strSystemLocale, m_strSchema);
      //System.install().add_app_install(strId, strBuild, strSystemLocale, strSystemSchema);
      //System.install().add_app_install(strId, strBuild, m_strLocale, m_strSchema);

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   System.install().add_app_install(strId, strBuild, straLocale[iLocale], m_strSchema);

      //}

      //for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //{

      //   System.install().add_app_install(strId, strBuild, m_strLocale, straSchema[iSchema]);

      //}

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //   {

      //      System.install().add_app_install(strId, strBuild, straLocale[iLocale], straSchema[iSchema]);

      //   }

      //}

      //System.install().add_app_install(strId, strBuild, strSystemLocale, "");
      //System.install().add_app_install(strId, strBuild, m_strLocale, "");

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   System.install().add_app_install(strId, strBuild, straLocale[iLocale], "");

      //}

      //System.install().add_app_install(strId, strBuild, "", m_strSchema);
      //System.install().add_app_install(strId, strBuild, "", strSystemSchema);

      //for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //{

      //   System.install().add_app_install(strId, strBuild, "", straSchema[iSchema]);

      //}

      //System.install().add_app_install(strId, strBuild, "", "");

      return true;

   }


   ::estatus user2::os_native_bergedge_start()
   {

      return true;

   }


   ::estatus     user2::run()
   {

      if (is_system())
      {



      }

      return ::thread::run();

   }


   bool user2::safe_is_running()
   {

      bool bRunning = false;

      try
      {

         if (is_running())
         {

            bRunning = true;

         }

      }
      catch (...)
      {

         bRunning = false;

      }


      return bRunning;

   }













   bool user2::init_service()
   {

      if (!is_serviceable())
      {

         __throw(::exception::exception(error_unsupported_function));

      }

      if (m_pservice)
      {

         return false;

      }

      m_pservice = allocate_new_service();

      if (!m_pservice)
      {

         return false;

      }

      auto estatus = m_pservice->initialize(this);

      if (!estatus)
      {

         return false;

      }

      System.m_serviceptra.add(m_pservice);

      return true;

   }



   bool user2::os_create_service()
   {

      return Context.os().create_service();

   }


   bool user2::os_remove_service()
   {

      return Context.os().remove_service();

   }


   bool user2::os_start_service()
   {

      return Context.os().start_service();

   }


   bool user2::os_stop_service()
   {

      return Context.os().stop_service();

   }


   void user2::on_service_request(::create * pcreate)
   {

      if (!is_serviceable())
      {

         return;

      }

      if (pcreate->m_pcommandline->m_varQuery.has_property("create_service"))
      {

         os_create_service();

      }
      else if (pcreate->m_pcommandline->m_varQuery.has_property("start_service"))
      {

         os_start_service();

      }
      else if (pcreate->m_pcommandline->m_varQuery.has_property("stop_service"))
      {

         os_stop_service();

      }
      else if (pcreate->m_pcommandline->m_varQuery.has_property("remove_service"))
      {

         os_remove_service();

      }
      else if (has_property("service"))
      {

         init_service();

         ::service_base::serve(*m_pservice);

      }
      else if (has_property("run"))
      {

         init_service();

         m_pservice->Start(0);

      }

   }


   //void user2::on_update_matter_locator()
   //{



   //}

   ::estatus user2::process_init()
   {


      string_array stra;

      stra.explode("/", m_strAppId);

      m_strRoot = stra[0];

      m_strDomain = stra.slice(1).implode("/");

      add_matter_locator(this);


      //if (is_system() || is_session())
      //{

      //   on_update_matter_locator();

      //}
      //else
      //{


      //}

      if (!m_bAppHasInstallerChangedProtected)
      {

#ifdef _UWP

         set_has_installer(false);

#else

         //if (get_context_system()->m_pappcore == nullptr)
         //{

         //   set_has_installer(false);

         //}
         //else
         {

            set_has_installer(!get_context_system()->has_aura_application_factory());

         }

#endif

      }

      auto estatus = initialize_context();

      if (!estatus)
      {

         return estatus;

      }

      //if (m_bAuraProcessInitialize)
      //{

      //   return m_bAuraProcessInitializeResult;

      //}

      INFO("aura::user2::process_init");

      //m_bAuraProcessInitialize = true;

      //m_bAuraProcessInitializeResult = false;

      //if (!is_system())
      {

         if (get_context_system() != nullptr)
         {

            m_bThreadToolsForIncreasedFps = get_context_system()->m_bThreadToolsForIncreasedFps;

         }

      }



      //if (!__construct(m_spdir))
      //{

      //   return false;

      //}

      //if (!__construct(m_spfile))
      //{

      //   return false;

      //}

      if (::get_thread() == nullptr)
      {

         ::set_thread(dynamic_cast <thread *> (this));

      }

      if (!ca_process_init())
      {

         FATAL("aura::user2::process_init .1");

         return false;

      }

      //if (!impl_process_init())
      //{

      //   FATAL("aura::user2::process_init .2");

      //   return false;

      //}

//      m_bAuraProcessInitializeResult = true;

      INFO("aura::user2::process_init success");

      create_factory < ::database::field_array >();
      create_factory < ::database::row >();
      create_factory < ::database::row_array >();

      //if (m_bAxisProcessInitialize)
      //{

      //   return m_bAxisProcessInitializeResult;

      //}

      INFO("axis::user2::process_init");

      //m_bAxisProcessInitialize = true;

      //m_bAxisProcessInitializeResult = false;

      if (m_psimpledb.is_null())
      {

         __construct_new(m_psimpledb);

      }

      //if (!::aura::user2::process_init())
      //{

      //   FATAL("axis::user2::process_init .1");

      //   return false;

      //}


      //m_bAxisProcessInitializeResult = true;

      INFO("axis::user2::process_init success");

      //return true;

      if (!userfs_process_init())
      {

         ERR(".2");

         return false;

      }

      INFO("success");

      return true;

   }


   void user2::process_term()
   {

      //try
      //{

      //   impl_process_term();

      //}
      //catch(...)
      //{

      //}

      try
      {

         ca_process_term();

      }
      catch(...)
      {

      }

      try
      {

         release_exclusive();

      }
      catch(...)
      {

      }

      //try
      //{

      //   m_phttp->message_receiver_destruct();

      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   m_phttp.release();

      //}
      //catch (...)
      //{

      //}

      //m_phandler.release();

//      try
//      {
//
//         route_message(&message);
//
//      }
//      catch (...)
//      {
//
//      }

      try
      {

         if (!is_session() && !is_system())
         {

            if (get_context_system() != nullptr)
            {

               get_context_system()->request({::command_check_exit});

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         m_stringtable.remove_all();

         m_stringtableStd.remove_all();

      }
      catch(...)
      {

      }

      //m_spfile.release();

      //m_spdir.release();

      //::aura::del(m_pimaging);


      /// commented out the code below
      /// reasoning: better leave to the session the responsability
      /// to do those checks/actions.
//      if (!is_session() && !is_system())
//      {
//
//         try
//         {
//
//            if (Session.appptra().get_count() <= 1)
//            {
//
//               if (System.thread::get_os_data() != nullptr)
//               {
//
//                  ::multithreading::set_finish(&System);
//
//               }
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }

   }


   ::estatus user2::init_application()
   {

      //if (m_bAuraInitializeInstance)
      //{

      //   return m_bAuraInitializeInstanceResult;

      //}

      INFO("aura::user2::init_application");

      //m_bAuraInitializeInstance = true;

      //m_bAuraInitializeInstanceResult = false;

      m_tickHeartBeat.Now();

      if (!init1())
      {

         //dappy(string(typeid(*this).name()) + " : init1 failure : " + __str(m_iErrorCode));

         return false;

      }

      System.install_progress_add_up(); // 2

      //xxdebug_box("init1 ok", "init1 ok", MB_ICONINFORMATION);

      m_tickHeartBeat.Now();

      if (!init2())
      {

         //dappy(string(typeid(*this).name()) + " : init2 failure : " + __str(m_iErrorCode));

         return false;

      }

      System.install_progress_add_up(); // 3

      //xxdebug_box("init2 ok", "init2 ok", MB_ICONINFORMATION);

      m_tickHeartBeat.Now();

      if (!init3())
      {

         //dappy(string(typeid(*this).name()) + " : init3 failure : " + __str(m_iErrorCode));

         return false;

      }

      System.install_progress_add_up(); // 4

      //xxdebug_box("init3 ok", "init3 ok", MB_ICONINFORMATION);

      m_tickHeartBeat.Now();

      //dappy(string(typeid(*this).name()) + " : init3 ok : " + __str(m_iErrorCode));

      try
      {

         if (!init())
         {

            //dappy(string(typeid(*this).name()) + " : initialize failure : " + __str(m_iErrorCode));

            return false;

         }

      }
      catch (const char * psz)
      {

         if (!strcmp(psz, "You have not logged in! Exiting!"))
         {

            return false;

         }

         return false;

      }

      System.install_progress_add_up(); // 5

//      m_bAuraInitializeInstanceResult = true;

      return true;

   }


   __pointer(::aura::ipi) user2::create_ipi()
   {

      try
      {

         return __new(::aura::ipi(m_strAppName));

      }
      catch (...)
      {

         return nullptr;

      }

   }


   ::estatus user2::init1()
   {

      ::estatus estatus = __construct_new(m_puserlanguagemap);

      if (!estatus)
      {

         return estatus;

      }

      if (get_context_system())
      {

         if (get_context_system()->m_pintstringLanguageResourceMap != nullptr)
         {

            m_puserlanguagemap->set_language_resource_map(get_context_system()->m_pintstringLanguageResourceMap);

         }

      }

      string strLang = System.get_user_language();

      if (!m_puserlanguagemap->set_language(this, strLang))
      {

         m_puserlanguagemap->set_default_language(this);

      }

      g_pf1 = (void *)(uptr) ::str::to_u64(Context.file().as_string(::dir::system() / "config\\system\\pf1.txt"));

      m_tickHeartBeat.Now();

      if (!ca_init1())
      {

         return ::error_failed;

      }

      string strLocaleSystem;

      string strSchemaSystem;

      string strPath = Context.dir().appdata() / "langstyle_settings.xml";

      if (Context.file().exists(strPath))
      {

         string strSystem = Context.file().as_string(strPath);

         ::xml::document docSystem;

         if (docSystem.load(strSystem))
         {

            if (docSystem.get_child("lang") != nullptr)
            {

               strLocaleSystem = docSystem.get_child("lang")->get_value();

            }

            if (docSystem.get_child("style") != nullptr)
            {

               strSchemaSystem = docSystem.get_child("style")->get_value();

            }

         }

      }

      string strLocale;

      string strSchema;

      if (System.get_user_language().has_char())
      {

         m_strLocale = System.get_user_language();

         m_strSchema = m_strLocale;

      }
      else
      {

#ifdef _UWP

         string_array stra;

         try
         {

            stra.explode("-", ::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride);

         }
         catch (long)
         {

         }

         strLocale = stra[0];

         strSchema = stra[0];

#elif defined(WINDOWS)

         LANGID langid = ::GetUserDefaultLangID();

         string strIso = ::windows::langid_to_iso(langid);

         strLocale = strIso;

         strSchema = strIso;

#endif

      }

      if (strLocale.is_empty())
      {

         strLocale = "_std";

      }

      if (strSchema.is_empty())
      {

         strSchema = strLocale;

      }

      if (strLocaleSystem.has_char())
      {

         strLocale = strLocaleSystem;

      }

      if (strSchemaSystem.has_char())
      {

         strSchema = strSchemaSystem;

      }

      if (System.value("locale").get_count() > 0)
      {

         strLocale = System.value("locale").stra()[0];

      }

      if (System.value("schema").get_count() > 0)
      {

         strSchema = System.value("schema").stra()[0];

      }

      if (Application.value("locale").get_count() > 0)
      {

         strLocale = Application.value("locale").stra()[0];

      }

      if (Application.value("schema").get_count() > 0)
      {

         strSchema = Application.value("schema").stra()[0];

      }

      set_locale(strLocale, ::source_database);

      set_schema(strSchema, ::source_database);

      if (!initialize_contextualized_theme())
      {

         FATAL("Failed to initialize_contextualized_theme");

         return false;

      }

      INFO("start");

      //if (!::aura::user2::init1())
      //{

      //   ERR(".1");

      //   return false;

      //}

      if (!initialize1_experience())
      {

         ERR(".2");

         return false;

      }

      m_tickHeartBeat.Now();

      estatus = __compose(m_puserfs);

      if (!estatus)
      {

         return estatus;

      }

      if (!userfs_init1())
      {

         ERR(".3");

         return false;

      }



      /*if(!m_spuser->init1())
      return false;
      if(!m_spuser->init2())
      return false;*/



      return ::success;

   }


   void user2::term1()
   {

      //try
      //{

      //   impl_term1();

      //}
      //catch (...)
      //{

      //}

      try
      {

         ca_term1();

      }
      catch(...)
      {

      }

   }

   ::estatus user2::init2()
   {

      //if (!impl_init2())
      //{

      //   return false;

      //}

      if (!ca_init2())
      {

         return false;

      }



      return true;

   }

   void user2::term2()
   {

      //try
      //{

      //   impl_term2();

      //}
      //catch (...)
      //{

      //}

      try
      {

         ca_term2();

      }
      catch(...)
      {

      }

   }

   ::estatus user2::init3()
   {

      string strFolder = m_strAppName;

      strFolder.replace(".", "_");
      strFolder.replace("::", "-");
      strFolder.replace(":", "_");

      m_strRelativeFolder = strFolder;

      //if (!impl_init3())
      //{

      //   return false;

      //}

      if (!ca_init3())
      {

         return false;

      }

      return true;

   }


   void user2::term3()
   {

      //try
      //{

      //   impl_term3();

      //}
      //catch (...)
      //{

      //}

      try
      {

         ca_term3();

      }
      catch(...)
      {

      }

   }


   //::estatus user2::init()
   //{

   //   return true;


   //}
//
//
//   void user2::term()
//   {
//
//      //::aura::del(m_pimaging);
//
////      bool bOk = true;
////
////      return bOk;
//
//   }




   //void user2::release_children()
   //{

   //   ::thread::release_children();

   //}


   void user2::term_application()
   {


      try
      {

         close(::aura::end_app);

      }
      catch (...)
      {

      }


      //try
      //{

      //   m_spobjectUserFs.release();

      //}
      //catch (...)
      //{


      //}

      //m_puserfs = nullptr;

      __release(m_pexperience);

      //try
      //{

      //   ::aura::user2::term_application();

      //}
      //catch (...)
      //{

      //}

      release_exclusive();

      ::aura::application_message signal(::aura::application_message_term_instance);

      try
      {

         route_message(&signal);

      }
      catch (...)
      {

      }

      try
      {

         if(::is_set(m_pappParent))
         {

            m_pappParent->app_remove(this);

         }

         if(::is_set(get_context_session()))
         {

            get_context_session()->app_remove(this);

         }

         //if(::is_set(get_context_system()))
         //{

         //   get_context_system()->app_remove(this);

         //}

         try
         {

            m_pipi.release();

         }
         catch (...)
         {

         }

         try
         {

            term();

         }
         catch(...)
         {


         }

         try
         {

            term3();

         }
         catch(...)
         {


         }

         try
         {

            term2();

         }
         catch(...)
         {


         }

         try
         {

            term1();

         }
         catch(...)
         {


         }


      }
      catch (...)
      {

      }

      if (m_psimpledb.is_set())
      {

         try
         {

            m_psimpledb->finalize();

         }
         catch (...)
         {

            m_result.add(error_failed);

         }

      }


      try
      {

         __release(m_pdocmanager);

      }
      catch (...)
      {

      }


      m_psimpledb.release();


   }






//   bool user2::impl_process_init()
//   {
//
//      return true;
//
//   }

//   bool user2::impl_init1()
//   {
//
//      //set_run();
//
//      return true;
//
//   }

//   bool user2::impl_init2()
//   {
//      return true;
//   }

//   bool user2::impl_init3()
//   {
//      return true;
//   }

// thread termination
//   void user2::impl_process_term() // default will 'delete this'
//   {
//
//      set_os_data(nullptr);
//
//      //i32 iRet = ::aura::user2::term_instance();
//
//      //return 0;
//
//   }


//   void user2::impl_term3()
//   {
//
//
//   }
//
//
//   void user2::impl_term2()
//   {
//
//
//   }
//
//
//   void user2::impl_term1()
//   {
//
//
//   }
 /*  bool user2::is_running()
   {

      return is_alive();

   }*/


   service_base * user2::allocate_new_service()
   {

      return nullptr;

   }


   ::estatus user2::ca_init2()
   {

      application_message message(application_message_init2);

      route_message(&message);

      return message.m_bOk;

   }

   void user2::ca_term2()
   {

      application_message message(application_message_term2);

      route_message(&message);

   }


   void user2::ca_term3()
   {

      application_message message(application_message_init3);

      route_message(&message);

//      if (!message.m_bOk)
//         return false;
//
//      return true;

   }

   __pointer(::aura::exclusive) user2::get_exclusive(string strId, LPSECURITY_ATTRIBUTES psa)
   {

      auto & pexclusive = m_mapExclusive[strId];

      if(!pexclusive)
      {

         pexclusive = __new(::aura::exclusive(strId, psa));

      }

      return pexclusive;

   }


   bool user2::exclusive_fails(string strId, LPSECURITY_ATTRIBUTES psa)
   {

      auto pexclusive = get_exclusive(strId, psa);

      if(!pexclusive)
      {

         return false;

      }

      return pexclusive->exclusive_fails();

   }


   bool user2::check_exclusive(bool & bHandled)
   {

#ifdef _UWP

      return true;

#endif

      bool bSetOk;

      LPSECURITY_ATTRIBUTES psa = nullptr;

      bool bResourceException = false;

#ifdef WINDOWS_DESKTOP

      bSetOk = false;

      SECURITY_ATTRIBUTES MutexAttributes;
      ZeroMemory(&MutexAttributes, sizeof(MutexAttributes));
      MutexAttributes.nLength = sizeof(MutexAttributes);
      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      bool bInitOk = InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION) != FALSE;
      if (bInitOk)
      {
         // give the security descriptor a Null Dacl
         // done using the  "TRUE, (PACL)nullptr" here
         bSetOk = SetSecurityDescriptorDacl(&SD,
                                            TRUE,
                                            (PACL)nullptr,
                                            FALSE) != FALSE;
      }

      if (bSetOk)
      {

         MutexAttributes.lpSecurityDescriptor = &SD;


         psa = &MutexAttributes;


      }

#else

      bSetOk = true;

#endif


      if (bSetOk)
      {

         bool bGlobalExclusiveFail = exclusive_fails(get_global_mutex_name(), psa);

         if(bGlobalExclusiveFail && m_eexclusiveinstance == ExclusiveInstanceGlobal)
         {

            TRACE("A instance of the user2:<br><br> - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this user2 can run globally: at the same machine.<br><br>Exiting this new instance.");

            try
            {

               if(!on_exclusive_instance_conflict(bHandled, ExclusiveInstanceGlobal, ""))
               {

                  return false;

               }

            }
            catch(...)
            {

               return false;

            }

         }

         if (m_eexclusiveinstance == ExclusiveInstanceGlobalId)
         {

            bool bGlobalIdExclusiveFail = exclusive_fails(get_global_id_mutex_name(), psa);

            if (bGlobalIdExclusiveFail)
            {

               TRACE("A instance of the user2:<br><br>-" + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same machine<br>Only one instance of this user2 can run globally: at the same machine with the same id.<br><br>Exiting this new instance.");

               try
               {

                  if(!on_exclusive_instance_conflict(bHandled, ExclusiveInstanceGlobalId, get_global_mutex_id()))
                  {

                     return false;

                  }

               }
               catch(...)
               {

                  return false;

               }

            }

         }

         bool bLocalExclusiveFail = exclusive_fails(get_local_mutex_name(), psa);

         if (bLocalExclusiveFail && m_eexclusiveinstance == ExclusiveInstanceLocal)
         {

            try
            {

               TRACE("A instance of the user2:<br><br>-" + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this user2 can run locally: at the same account.<br><br>Exiting this new instance.");

               if(!on_exclusive_instance_conflict(bHandled, ExclusiveInstanceLocal, ""))
               {

                  return false;

               }

            }
            catch (...)
            {

               return false;

            }

         }

         if (m_eexclusiveinstance == ExclusiveInstanceLocalId)
         {

            bool bLocalIdExclusiveFail = exclusive_fails(get_local_id_mutex_name(), psa);

            if (bLocalIdExclusiveFail)
            {

               try
               {

                  // Should in some way activate the other instance
                  TRACE("A instance of the user2:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same account.<br>Only one instance of this user2 can run locally: at the same ac::count with the same id.<br><br>Exiting this new instance.");

                  if(!on_exclusive_instance_conflict(bHandled, ExclusiveInstanceLocalId, get_local_mutex_id()))
                  {

                     return false;

                  }

               }
               catch (...)
               {

                  return false;

               }

            }

         }

      }

      return true;

   }


   bool user2::release_exclusive()
   {

      m_mapExclusive.remove_all();

      return true;

   }


   ::estatus user2::ca_process_init()
   {

      application_message message(application_message_process_init);

      route_message(&message);

      return true;

   }


   ::estatus user2::ca_init1()
   {

      application_message message(application_message_init1);

      route_message(&message);

      return message.m_bOk;

   }



   void user2::ca_term1()
   {

      application_message message(application_message_term1);

      try
      {

         route_message(&message);

      }
      catch (...)
      {

      }

      //return message.m_bOk;

   }




   string user2::get_local_mutex_name()
   {
      return System.get_local_mutex_name(get_mutex_name_gen());
   }


   string user2::get_local_id_mutex_name()
   {

      return System.get_local_id_mutex_name(get_mutex_name_gen(), get_local_mutex_id());

   }


   string user2::get_global_mutex_name()
   {
      return System.get_global_mutex_name(get_mutex_name_gen());
   }

   string user2::get_global_id_mutex_name()
   {
      return System.get_global_id_mutex_name(get_mutex_name_gen(), get_global_mutex_id());
   }




   bool user2::on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId)
   {

      if (eexclusive == ExclusiveInstanceLocal)
      {

         return on_exclusive_instance_local_conflict(bHandled);

      }
      else if (eexclusive == ExclusiveInstanceLocalId)
      {

         return on_exclusive_instance_local_conflict_id(bHandled, strId);

      }

      return false;

   }


   bool user2::on_exclusive_instance_local_conflict(bool & bHandled)
   {

      bool bContinue = false;

      try
      {

         if (m_pipi)
         {

            auto pcall = m_pipi->create_call("user2", "on_additional_local_instance");

            pcall->add_arg(Context.file().module());

            pcall->add_arg(Context.os().get_pid());

            pcall->add_arg(System.command_line_text());

            string strId;

            pcall->add_arg(strId);

            pcall->announce();

            pcall->wait();

            for(auto & pair : pcall->m_mapTask)
            {

               auto & pobjectTask = pair.element2();

               if(bContinue && pobjectTask->has_property("continue"))
               {

                  bContinue = pobjectTask->m_var["continue"];

               }

               if(!bHandled && pobjectTask->has_property("handled"))
               {

                  bHandled = pobjectTask->m_var["handled"];

               }

            }

         }

      }
      catch (...)
      {

      }

      return bContinue;

   }


   bool user2::on_exclusive_instance_local_conflict_id(bool & bHandled, string strId)
   {

      bool bContinue = false;

      try
      {

         if (m_pipi)
         {

            auto pcall = m_pipi->create_call("user2", "on_additional_local_instance");

            pcall->add_arg(Context.file().module());

            pcall->add_arg(Context.os().get_pid());

            pcall->add_arg(System.command_line_text());

            pcall->add_arg(strId);

            for(auto & task : pcall->tasks())
            {

               if(!bHandled)
               {

                  bHandled = task.is_true("handled");

                  if(bHandled)
                  {

                     bContinue = task.is_true("continue");

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      return bContinue;

   }


   bool user2::on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine)
   {

      auto pcommandline = __new(command_line(this, strCommandLine));

      request({pcommandline});

      bHandled = true;

      return false;

   }


   void user2::on_new_instance(string strModule, const ::id & iPid)
   {

   }


   //string user2::get_mutex_name_gen()
   //{
   //   return m_strAppName;
   //}


   string user2::get_local_mutex_id()
   {

      return value("local_mutex_id");

   }


   string user2::get_global_mutex_id()
   {

      return value("global_mutex_id");

   }


   bool user2::Ex2OnAppInstall()
   {

      return true;

   }


   bool user2::Ex2OnAppUninstall()
   {

      return true;

   }


   void user2::on_set_scalar(e_scalar escalar, i64 iValue, int iFlags)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   m_iProgressInstallStep = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   m_iProgressInstallStart = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   m_iProgressInstallEnd = iValue;

      //}
      //else
      {

         return ::int_scalar_source::on_set_scalar(escalar, iValue, iFlags);

      }

   }


   void user2::get_scalar_minimum(e_scalar escalar, i64 & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }

   void user2::get_scalar(e_scalar escalar, i64 & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStep;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else
      {

         ::int_scalar_source::get_scalar(escalar, i);

      }

   }

   void user2::get_scalar_maximum(e_scalar escalar, i64 & i)
   {

      //if (escalar == scalar_download_size)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0x7fffffff;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0x7fffffff;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }


   //i32 user2::sync_message_box_timeout(::user::primitive * pwndOwner, var var, const char * pszTitle, ::duration durationTimeOut, UINT fuStyle)
   //{

   //   UNREFERENCED_PARAMETER(durationTimeOut);

   //   return sync_message_box(pwndOwner, var, pszTitle, fuStyle);

   //}



   service_base * user2::get_service()
   {

      return m_pservice;

   }






   string user2::http_get_locale_schema(const char * pszUrl, const char * pszLocale, const char * pszSchema)
   {

      ::exception::throw_interface_only();

      return "";

   }




   void user2::message_handler(::message::base * pbase)
   {

      ::thread::message_handler(pbase);

   }


   void user2::set_locale(const string & pcsz, const ::action_context & context)

   {

      string strLocale(pcsz);


      strLocale.trim();

      m_strLocale = strLocale;

      on_set_locale(m_strLocale, context);

   }


   void user2::set_schema(const string & pcsz, const ::action_context & context)

   {

      string strSchema(pcsz);


      strSchema.trim();

      m_strSchema = strSchema;

      on_set_schema(m_strSchema, context);

   }


   void user2::on_set_locale(const string & pcsz, const ::action_context & context)

   {
      UNREFERENCED_PARAMETER(context);
      UNREFERENCED_PARAMETER(pcsz);

      //System.appa_load_string_table();
   }


   void user2::on_set_schema(const string & pcsz, const ::action_context & context)

   {
      UNREFERENCED_PARAMETER(context);
      UNREFERENCED_PARAMETER(pcsz);

      //System.appa_load_string_table();
   }





   string user2::get_locale_schema_dir()
   {

      return ::str::_001Concat(get_locale(), "/", get_schema());

   }


   string user2::get_locale_schema_dir(const string & strLocale)
   {

      return ::str::_001Concat(strLocale.is_empty() ? get_locale() : strLocale, "/", get_schema());

   }


   void user2::matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {

      if (strLocale.is_empty() || strSchema.is_empty())
      {

         return;

      }

      for (auto & strMatterLocator : straMatterLocator)
      {

         string strLs = get_locale_schema_dir(strLocale, strSchema);

         stra.add_unique(::file::path(strMatterLocator) / strLs);

      }

   }


   void user2::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("map", "map"));

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      ::aura::str_context * pcontext = Session.str_context();

      for (i32 i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
      {

         string strLocale = pcontext->localeschema().m_idaLocale[i];

         string strSchema = pcontext->localeschema().m_idaSchema[i];

         matter_locator_locale_schema_matter(stra, straMatterLocator, strLocale, strSchema);

      }

      matter_locator_locale_schema_matter(stra, straMatterLocator, "en", "en");

      matter_locator_locale_schema_matter(stra, straMatterLocator, "_std", "_std");

      if (straMatterLocator.has_elements())
      {

         stra.add_unique(::file::path(straMatterLocator.first()) / get_locale_schema_dir("404", "404"));

      }

   }


   string user2::get_locale_schema_dir(const string & strLocale, const string & strSchema)
   {

      return ::str::_001Concat(strLocale, "/", strSchema);

   }


   void user2::fill_locale_schema(::str::international::locale_schema & localeschema, const string & pszLocale, const string & pszSchema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      string strLocale(pszLocale);
      string strSchema(pszSchema);


      localeschema.m_idLocale = pszLocale;
      localeschema.m_idSchema = pszSchema;


      localeschema.add_locale_variant(strLocale, strSchema);
      localeschema.add_locale_variant(get_locale(), strSchema);
      localeschema.add_locale_variant(__id(std), strSchema);
      localeschema.add_locale_variant(__id(en), strSchema);


      localeschema.finalize();


   }


   void user2::fill_locale_schema(::str::international::locale_schema & localeschema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      //localeschema.m_bAddAlternateStyle = true;


      string_array straLocale;
      string_array straSchema;

      straLocale.add(get_locale());
      straSchema.add(get_schema());


      string_array stra;

      stra = value("locale").stra();

      stra.remove_ci("_std");

      straLocale.add_unique(value("locale").stra());

      stra.empty();

      stra = value("schema").stra();

      stra.remove_ci("_std");

      straSchema.add_unique(value("schema").stra());

      localeschema.m_idLocale = straLocale[0];
      localeschema.m_idSchema = straSchema[0];

      for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
         {

            localeschema.add_locale_variant(straLocale[iLocale], straSchema[iSchema]);

         }

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(get_locale(), straSchema[iSchema]);

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(std), straSchema[iSchema]);

      }


      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(en), straSchema[iSchema]);

      }

      localeschema.finalize();


   }


//   void user2::defer_add_thread_run_wait(sync_array & soa)
//   {
//
////      soa.add(&axiom()->m_ev);
//
//   }
//

   bool user2::platform_open_by_file_extension(index iEdge, const char * pszPathName, ::create * pcreate)
   {

      return false;

   }


   bool user2::platform_open_by_file_extension(index iEdge, ::create * pcc)
   {

      return false;

   }




   //i32 user2::hotplugin_host_starter_start_sync(const char * pszCommandLine, ::aura::user2 * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   //{

   //   return -1;

   //}


   bool user2::is_application() const
   {

      return !is_session() && !is_system();

   }



   //bool user2::_001OnAgreeExit()
   //{

   //   return true;

   //}


   void user2::_001OnFranceExit()
   {

      if (System.m_pmultimedia)
      {

         System.m_pmultimedia->_001OnFranceExit();

      }


      HideApplication();

      close(::aura::end_app);

   }


   void user2::_001FranceExit()
   {

      _001OnFranceExit();

      m_bFranceExit = true;

   }


   //void user2::dispatch_user_message(::user::message * pusermessage)
   //{

   //   pusermessage->send();

   //}


   //void user2::play_audio(var varFile, bool bSynch)
   //{

   //   UNREFERENCED_PARAMETER(varFile);
   //   UNREFERENCED_PARAMETER(bSynch);

   //}

   void user2::post_critical_error_message(const char * pszMessage, bool bShowLog)
   {

      string strMessage;

      strMessage = System.datetime().international().get_gmt_date_time();
      strMessage += " ";
      strMessage += pszMessage;
      strMessage += "\n";

      {

         sync_lock sl(mutex());

         Context.file().add_contents(Context.dir().appdata() / (Context.file().module().name() + "_log_error.txt"), strMessage);

      }

      if (bShowLog)
      {

         show_critical_error_log();

      }

   }


   string user2::get_app_user_friendly_task_bar_name()
   {

      ::file::path path = m_strAppName;

      string strTitle = path.title();

      return strTitle;

   }



   void user2::show_critical_error_log()
   {

      static int g_iCount = 0;

      string strFile = Context.dir().appdata() / (Context.file().module().name() + "_log_error.txt");

      g_iCount++;

      if (g_iCount == 1)
      {

         Context.os().file_open(strFile);

      }

//#ifdef _UWP
//
//      output_debug_string(strFile);
//
//#elif defined(WINDOWS)
//
//      call_async("C:\\Program Files (x86)\\Notepad++\\Notepad++.exe", "\"" + strFile + "\"", "", display_normal, false);
//
//#elif defined(LINUX)
//
//      call_async("gedit", "\"" + strFile + "\"", "", display_normal, false);
//
//#else
//
//      ::fork(this, [=]()
//      {
//
//         system("open \"" + strFile + "\"");
//
//      });
//
//
//#endif




   }


   void user2::update(::update * pupdate)
   {


   }




   //bool user2::compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed)
   //{

   //   return System.compress().ungz(this, pfileUncompressed, pfileCompressed);

   //}


   //bool user2::compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel)
   //{

   //   return System.compress().gz(this, pfileCompressed, pfileUncompressed, iLevel);


   //}

   void user2::interactive_credentials(::account::credentials * pcredentials)
   {

      Session.interactive_credentials(pcredentials);

   }


   ::file::path user2::get_executable_path()
   {

      return ::dir::module() / (get_executable_title() + get_executable_extension());


   }


   string user2::get_executable_extension()
   {

#ifdef WINDOWS

      return ".exe";

#else

      return "";

#endif

   }


   string user2::get_executable_title()
   {

      return executable_title_from_appid(get_executable_appid());

   }


   string user2::get_executable_appid()
   {

      return m_strAppId;

   }




   bool user2::app_set(string strPath, string strValue)
   {

      return Context.sys_set(::file::path(m_strAppName) / strPath, strValue);

   }


   string user2::app_get(string strPath, string strDefault)
   {

      return Context.sys_get(::file::path(m_strAppName) / strPath, strDefault);

   }


   bool user2::on_open_document_file(var varFile)
   {

      request_file(varFile);

      return varFile["document"].cast < ::object > () != nullptr;

   }



   void user2::install_trace(const string & str)
   {

      sync_lock sl(mutex());

      //::install::trace_file(this, m_strInstallTraceLabel).print(str);

   }


   void user2::install_trace(double dRate)
   {

      sync_lock sl(mutex());

      //::install::trace_file(this, m_strInstallTraceLabel).print(dRate);

   }


   bool user2::register_spa_file_type()
   {

#ifdef WINDOWS_DESKTOP

      HKEY hkey;

      wstring extension = L".spa";                     // file extension
      wstring desc = L"spafile";          // file type description
      wstring content_type = L"user2/x-spa";

      wstring app(::dir::stage(m_strAppId, process_platform_dir_name(), process_configuration_dir_name()));

      wstring icon(app);

      app = L"\"" + app + L"\"" + L" \"%1\"";
      icon = L"\"" + icon + L"\",107";

      wstring action = L"Open";

      wstring sub = L"\\shell\\";

      wstring path = L"spafile\\shell\\open\\command";


      // 1: Create subkey for extension -> HKEY_CLASSES_ROOT\.002
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, extension.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (BYTE*)desc.c_str(), DWORD (desc.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegSetValueExW(hkey, L"ContentType", 0, REG_SZ, (BYTE*)content_type.c_str(), DWORD (content_type.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegCloseKey(hkey);



      // 2: Create Subkeys for action ( "Open with my program" )
      // HKEY_CLASSES_ROOT\.002\Shell\\open with my program\\command
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (BYTE*)app.c_str(), DWORD(app.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);


      path = L"spafile\\DefaultIcon";

      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (BYTE*)icon.c_str(), DWORD (icon.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);

      wstring wstr(dir::stage(m_strAppId, process_platform_dir_name(), process_configuration_dir_name()) / "spa_register.txt");

      int iRetry = 9;

      while (!file_exists(utf8(wstr.c_str())) && iRetry > 0)
      {

         dir::mk(dir::name(utf8(wstr.c_str())).c_str());

         file_put_contents_dup(utf8(wstr.c_str()).c_str(), "");

         iRetry--;

         Sleep(100);

      }

#endif

      return true;

   }


   bool user2::low_is_app_app_admin_running(string strPlatform, string strConfiguration)
   {

      ::install::admin_mutex smutex(strPlatform);

      return smutex.already_exists();

   }


   void user2::defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {

      if (low_is_app_app_admin_running(strPlatform, strConfiguration))
      {

         return;

      }

      start_program_files_app_app_admin(strPlatform, strConfiguration);

   }


   void user2::start_program_files_app_app_admin(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS_DESKTOP

      SHELLEXECUTEINFOW sei = {};

      string str = ::path::app_app_admin(strPlatform, strConfiguration);

      if (!::file_exists(str))
      {

         return;

      }

      ::install::admin_mutex mutexStartup("-startup");

      wstring wstr(str);

      sei.cbSize = sizeof(SHELLEXECUTEINFOW);
      sei.fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;
      sei.lpVerb = L"RunAs";

      sei.lpFile = wstr.c_str();

      ::ShellExecuteExW(&sei);
      DWORD dwGetLastError = get_last_error();

#endif

   }


   string user2::get_app_id(string wstr)
   {

      if (wstr.length() <= 0)
      {

         return "";

      }

      wstr.trim();

      ::str::trim_any_quotes(wstr);

      wstr.trim();

      if (wstr.length() <= 0)
      {

         return "";

      }


      ::string strPath = wstr.c_str();

      ::string strContents = file_as_string(strPath.c_str());

      ::xml::document doc;

      if (!doc.load(strContents.c_str()))
      {

         return "";

      }

      const char * psz = doc.GetChildAttrValue("launch", "app");

      if (psz == nullptr || *psz == '\0')
      {

         return "";

      }

      return psz;

   }


   LPWAVEOUT user2::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      __throw(interface_only_exception(nullptr));

      return nullptr;

   }


   void user2::on_create_keyboard()
   {

      set_keyboard_layout(nullptr,::source_database);

   }


   bool user2::set_keyboard_layout(const char * pszPath, const ::action_context & context)
   {

      if(get_context_application()->get_context_session() == nullptr)
      {

         return false;

      }

      if(pszPath == nullptr)
      {

         if(is_set_ref(Session.keyboard().on_layout()))
         {

            //            if(Session.account()->m_puser != nullptr
            //             && Session.account()->m_puser->m_strFontopusServerSessId.has_char())
            //        {

            // xxx data_set("keyboard_layout", keyboard().on_layout(::draw2d::graphics_pointer & pgraphics).m_strPath);

            //      }

            return true;
         }

         string strCurrentSystemLayout = Session.keyboard().get_current_system_layout();

         if(strCurrentSystemLayout.is_empty())
            return false;

         if(!set_keyboard_layout(strCurrentSystemLayout,::source_database))
            return false;

         //         if(Session.account()->m_puser != nullptr
         //          && Session.account()->m_puser->m_strFontopusServerSessId.has_char())
         //     {

         // xxx            data_set("keyboard_layout", keyboard().on_layout(::draw2d::graphics_pointer & pgraphics).m_strPath);

         //   }

         return true;
      }

      if(!Session.keyboard().load_layout(pszPath,context))
         return false;

      // xxx Application.simpledb().on_set_keyboard_layout(pszPath, context);

      return true;
   }


   bool user2::keyboard_focus_is_focusable(::user::primitive * pue)
   {

      return false;

   }


   bool user2::keyboard_focus_OnSetFocus(::user::primitive * pue)
   {

      return true;

   }


   bool user2::get_frame(__pointer(::user::interaction) & pinteraction)
   {

#ifdef ANDROID

      if (Session.m_puiHost != nullptr)
      {

         if (Session.m_puiHost != nullptr)
         {

            return Session.m_puiHost->m_uiptraChild.get_child(pinteraction);

         }

      }

#endif

      sync_lock sl(&m_mutexFrame);

      return m_puiptraFrame->get_child(pinteraction);

   }




   void user2::add_frame(::user::interaction * pwnd)
   {

      if (pwnd == Session.m_puiHost)
      {

         return;

      }

      if (pwnd->is_system_message_window())
      {

         return;

      }

      if (pwnd == nullptr)
      {

         return;

      }

      sync_lock sl(&m_mutexFrame); // recursive lock (on m_framea.add(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex

      if (m_puiptraFrame->add_unique(pwnd))
      {

         TRACE("::base::user2::add_frame ::user::interaction = 0x%" PRIxPTR " (%s) app=%s", pwnd, typeid(*pwnd).name(), typeid(*this).name());

         if (!(pwnd->m_ewindowflag & window_flag_satellite_window))
         {

            Session.on_create_frame_window();

         }

         if (m_puiMain1 == nullptr)
         {

            m_puiMain1 = pwnd;

         }

         if (Session.m_puiHost)
         {

            Session.m_puiHost->m_uiptraChild.add_unique(pwnd);

            //pwnd->set_need_redraw();

            //pwnd->post_redraw();

         }

      }

   }


   void user2::remove_frame(::user::interaction * pwnd)
   {

      sync_lock sl(&m_mutexFrame); // recursive lock (on m_framea.remove(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex


      //if(get_active_uie() == pwnd)
      //{

      //   set_a

      //}


      if (m_puiMain1 == pwnd)
      {

         m_puiMain1 = nullptr;

      }

      if (m_puiptraFrame != nullptr)
      {

         if (m_puiptraFrame->remove(pwnd) > 0)
         {

            TRACE("::base::user2::remove_frame ::user::interaction = 0x%016x (%s) app=%s", pwnd, typeid(*pwnd).name(), typeid(*this).name());

         }

      }


   }



   bool user2::send_message_to_windows(UINT message, WPARAM wparam, LPARAM lparam) // with tbs in <3

   {

      __pointer(::user::interaction) pwnd;

      try
      {

         while (get_frame(pwnd))
         {

            try
            {

               if (pwnd && pwnd->is_window())
               {

                  try
                  {

                     pwnd->send_message(message, wparam, lparam);


                  }
                  catch (...)
                  {

                  }

                  try
                  {

                     pwnd->send_message_to_descendants(message, wparam, lparam);


                  }
                  catch (...)
                  {


                  }

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      return true;

   }


   bool user2::route_message_to_windows(::message::message * pmessage) // with tbs in <3
   {

      __pointer(::user::interaction) pwnd;

      try
      {

         while (get_frame(pwnd))
         {

            try
            {

               if (pwnd && pwnd->is_window())
               {

                  try
                  {

                     pwnd->route_message(pmessage);

                  }
                  catch (...)
                  {

                  }

                  try
                  {

                     pwnd->route_message_to_descendants(pmessage);

                  }
                  catch (...)
                  {


                  }

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {


      }

      return true;

   }


   void user2::send_language_change_message()
   {

      ::message::message message(::message::type_language);

      route_message_to_windows(&message);

   }


   ::user::interaction * user2::main_window()
   {

      if (!m_puiMain1)
      {

         return nullptr;

      }

      return m_puiMain1->m_puiThis;

   }


   string user2::preferred_experience()
   {

      string strExperience;

      strExperience = value("experience");

      if (strExperience.has_char())
      {

         return strExperience;

      }

      return "aura";

   }

   ::user::document *user2::place_hold(::user::interaction * pinteraction)
   {

      return nullptr;

   }


   bool user2::post_message(UINT message, WPARAM wparam, lparam lparam )
   {

      return ::thread::post_message(message, wparam, lparam);

   }


   //::draw2d::icon * user2::set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon)
   //{

   //   ::draw2d::icon * piconOld = get_icon(pobject, bBigIcon);

   //   if (bBigIcon)
   //   {

   //      pobject->value("big_icon") = (__pointer(object)) picon;

   //   }
   //   else
   //   {

   //      pobject->value("small_icon") = (__pointer(object)) picon;

   //   }

   //   return piconOld;

   //}


   //::draw2d::icon * user2::get_icon(object * pobject, bool bBigIcon) const
   //{

   //   if (bBigIcon)
   //   {

   //      return ((object *)pobject)->cast < ::draw2d::icon >("big_icon");

   //   }
   //   else
   //   {

   //      return ((object *)pobject)->cast <::draw2d::icon>("small_icon");

   //   }

   //}


   void user2::_001OnAppExit(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      close(end_app);

   }


   bool user2::is_equal_file_path(const ::file::path & path1Param, const ::file::path & path2Param)
   {

      ::file::path path1;

      ::file::path path2;

      path1 = Context.defer_process_path(path1Param);

      path2 = Context.defer_process_path(path2Param);

      path1 = node_full_file_path(path1);

      path2 = node_full_file_path(path2);

      return strcmp(path1, path2) == 0;

   }


//   void user2::on_event(::u64 u, ::object * pobject)
//   {
//
//      object_ptra ptra;
//
//      {
//
//         sync_lock sl(mutex());
//
//         ptra = m_objectptraEventHook;
//
//      }
//
//      for(auto & pobject : ptra)
//      {
//
//         pobject->on_event(u, pobject);
//
//      }
//
//
//   }


   ::file::path user2::appconfig_folder()
   {

      return ::dir::config() / m_strAppName;

   }


   ::account::user * user2::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   {

      if(::is_null(get_context_session()))
      {

         return nullptr;

      }

      return get_context_session()->get_user(pathUrl, bFetch, bInteractive);

   }


   ::account::user * user2::interactive_get_user(::file::path pathUrl)
   {

      return get_user(pathUrl, true, true);

   }


   ::account::user * user2::noninteractive_get_user(::file::path pathUrl)
   {

      return get_user(pathUrl, true, false);

   }


   void user2::on_initial_frame_position(::user::frame * pframe)
   {

      get_context_system()->on_initial_frame_position(pframe);

   }


   void user2::on_graphics_ready()
   {

   }


   __pointer(::user::document) user2::defer_create_view(string strView, ::user::interaction * puiParent, ewindowflag ewindowflag, const ::id & id)
   {

      auto pcontroller = Multimedia.defer_create_view(strView, puiParent, ewindowflag, id);

      if (pcontroller)
      {

         return pcontroller;

      }

      return nullptr;

   }

   void user2::process_message(::message::base * pbase)
   {

      return ::thread::process_message(pbase);

   }


//   ::account::user * user2::interactive_get_user(::file::path pathUrl)
//   {
//
//      if(::is_null(get_context_session()))
//      {
//
//         return nullptr;
//
//      }
//
//      return get_context_session()->interactive_get_user();
//
//   }
//
//
//   ::account::user * user2::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      if(::is_null(get_context_session()))
//      {
//
//         return nullptr;
//
//      }
//
//      return get_context_session()->noninteractive_get_user();
//
//   }


   //::type user2::user_default_controltype_to_typeinfo(::user::e_control_type econtroltype)
   //{

   //   return __type(::user::interaction);

   //}


   //::type user2::control_type_from_id(const ::id & id, ::user::e_control_type & econtroltype)
   //{

   //   econtroltype = ::user::control_type_none;

   //   return __type(::user::interaction);

   //}


   ::id user2::translate_property_id(const ::id & id)
   {

      //if(!is_system())
      //{

        // if(!is_session())
         //{

           // return Session.translate_property_id(id);

         //}
         //else
         //{

           // return System.translate_property_id(id);

         //}

      //}

      return id;

   }


   //void user2::record(::create * pcommand)
   //{

   //   sync_lock sl(mutex());

   //   get_command()->m_createa.add(pcommand);

   //}


   bool user2::on_start_application()
   {

      string strAppId = m_strAppId;

      auto& file = System.file();

      string strJson = file.as_string(::dir::config() / strAppId / +"http.json");

      if (strJson.has_char())
      {

         try
         {

            System.http().m_setHttp.parse_json(strJson);

         }
         catch (...)
         {

         }

      }

      set_last_run_application_path(strAppId);

      if (!os_on_start_application())
      {

         return false;

      }

      return true;

   }


   bool user2::start_application(bool bSynch, ::create * pcreate)
   {

//      try
//      {
//
//         if (pbias != nullptr)
//         {
//
//            if (pbias->m_pcallback != nullptr)
//            {
//
//               pbias->m_pcallback->connect_to(this);
//
//            }
//
//         }
//      }
//      catch (...)
//      {
//      }

//      if (pbias != nullptr)
//      {
//
//         m_biasCalling = *pbias;
//
//      }

      if (bSynch)
      {

         if (!begin_synch())
         {

            return false;

         }

      }
      else
      {

         begin();

      }


      return true;

   }


   void user2::HideApplication()
   {


      try
      {


         if (m_puiMain1)
         {

            m_puiMain1->display(::display_hide);

            m_puiMain1->set_need_redraw();

            m_puiMain1->post_redraw();

         }

      }
      catch (...)
      {

      }

   }


   string user2::load_string(const ::id & id)
   {

      sync_lock sl(&m_mutexStr);

      string str;

      if (m_stringmap.lookup(id, str))
      {

         return str;

      }

      if (!load_string(str, id))
      {

         id.to_string(str);

         return str;

      }

      m_stringmap.set_at(id, str);

      return str;

   }


   bool user2::load_string(string & str, const ::id & id)
   {

      if (!load_cached_string(str, id, true))
      {

         return false;

      }

      return true;

   }


   bool user2::load_cached_string(string & str, const ::id & id, bool bLoadStringTable)
   {

      auto pdocument = __new(::xml::document);

      if (!pdocument->load(id) || !*pdocument)
      {

         return load_cached_string_by_id(str, id, bLoadStringTable);

      }

      auto pnodeRoot = pdocument->root();

      if (pnodeRoot->get_name() == "string")
      {

         string strId = pnodeRoot->attribute("id");

         if (!load_cached_string_by_id(str, strId, bLoadStringTable))
         {

            str = pnodeRoot->get_value();

         }

         return true;

      }

      return false;

   }


   //bool user2::load_cached_string_by_id(string & str, const ::id & id, bool bLoadStringTable)
   //{

   //   string strId(id.str());

   //   string strTable;

   //   string strString;

   //   index iFind = 0;

   //   if ((iFind = strId.find(':')) <= 0)
   //   {

   //      strTable = "";

   //      strString = strId;

   //   }
   //   else
   //   {

   //      strTable = strId.Mid(0, iFind);

   //      strString = strId.Mid(iFind + 1);

   //   }

   //   sync_lock sl(&m_mutexStr);

   //   __pointer(string_to_string) pmap;

   //   if (m_stringtableStd.lookup(strTable, pmap))
   //   {

   //      if (pmap != nullptr && pmap->lookup(strString, str))
   //      {

   //         return true;

   //      }

   //   }
   //   else if (m_stringtable.lookup(strTable, pmap))
   //   {

   //      if (pmap != nullptr && pmap->lookup(strString, str))
   //      {

   //         return true;

   //      }

   //   }
   //   else if (bLoadStringTable)
   //   {

   //      load_string_table(strTable, "");

   //      return load_cached_string_by_id(str, id, false);

   //   }

   //   return false;

   //}


   void user2::load_string_table(const string & pszApp, const string & pszId)
   {


   }




   //void user2::load_string_table()
   //{

   //   load_string_table("", "");

   //}


   //bool user2::is_system() const
   //{

   //   return false;

   //}


   //bool user2::is_session() const
   //{

   //   return false;

   //}


   //bool user2::is_serviceable() const
   //{

   //   return false;

   //}


   ::simpledb::server * user2::simpledb()
   {

      return m_psimpledb;

   }


   ::database::server * user2::dataserver()
   {

      return simpledb();

   }


   ::estatus user2::verb()
   {

      return true;

   }


   //void user2::SetCurrentHandles()
   //{

   //   ::aura::user2::SetCurrentHandles();

   //}


   void user2::_001CloseApplication()
   {

      close(end_app);

   }


   //bool user2::process_exception(::exception_pointer pe)
   //{

   //   return aura::user2::process_exception(e);

   //}


   //::estatus     user2::main()
   //{

   //   return ::aura::user2::main();

   //}


   ::estatus user2::on_run()
   {

      try
      {

         ::aura::application_message signal(::aura::application_message_begin);

         route_message(&signal);

      }
      catch (...)
      {

      }

      thread * pthread = ::get_thread();

      install_message_routing(pthread);

      m_bReady = true;

      try
      {

         string strType = type_name();

         //if(::is_set(m_psystem))
         //{

         //   m_psystem->add_reference(this);

         //}

         //if(::is_set(m_psession))
         //{

         //   m_psession->add_reference(this);

         //}

         if (::is_set(m_pappParent))
         {

            m_pappParent->add_reference(this);

         }

      resume_on_exception:

         try
         {

            m_estatus = run();

         }
         catch (::exception::exception_pointer pe)
         {

            if (handle_exception(pe))
            {

               goto resume_on_exception;

            }

            m_estatus = pe->m_estatus;

         }

      }
      catch (::exception_pointer pe)
      {

      }


      try
      {

         thread * pthread = this;

         if (pthread != nullptr && pthread->m_pevReady != nullptr)
         {

            pthread->m_pevReady->SetEvent();

         }

      }
      catch (...)
      {

         m_result.add(error_failed);

      }

      return m_estatus;

   }


   //::estatus user2::init_application()
   //{

   //   return ::aura::user2::init_application();

   //}


   //::estatus user2::application_pre_run()
   //{

   //   return ::aura::user2::application_pre_run();

   //}



   //bool user2::InitApplication()
   //{

   //   return true;

   //}


   //bool user2::do_install()
   //{


   //   if (!::aura::user2::do_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool user2::do_uninstall()
   //{

   //   bool bOk = aura::user2::do_uninstall();

   //   return bOk;

   //}


   //bool user2::on_install()
   //{

   //   if (!aura::user2::on_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool user2::on_uninstall()
   //{

   //   if (!aura::user2::on_uninstall())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //::estatus user2::os_native_bergedge_start()
   //{

   //   if (!::aura::user2::os_native_bergedge_start())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void user2::on_request(::create * pcreate)
   //{

   //   aura::user2::on_request(pcreate);

   //}


   //::estatus     user2::run()
   //{

   //   return ::aura::user2::run();

   //}


   //__pointer(::aura::user2) user2::assert_running(const char * pszAppId)
   //{

   //   __pointer(::aura::user2) papp;

   //   papp = Session.m_applicationa.find_running_defer_try_quit_damaged(pszAppId);

   //   if(papp.is_null())
   //   {

   //      __pointer(::create) spcreate(e_create);

   //      papp = Session.start_application(pszAppId,spcreate);

   //   }

   //   return papp;

   //}


   //::estatus user2::process_init()
   //{

   //   create_factory < ::database::field_array >();
   //   create_factory < ::database::row >();
   //   create_factory < ::database::row_array >();

   //   //if (m_bAxisProcessInitialize)
   //   //{

   //   //   return m_bAxisProcessInitializeResult;

   //   //}

   //   INFO("axis::user2::process_init");

   //   //m_bAxisProcessInitialize = true;

   //   //m_bAxisProcessInitializeResult = false;

   //   if (m_psimpledb.is_null())
   //   {

   //      __construct_new(m_psimpledb);

   //   }

   //   if (!::aura::user2::process_init())
   //   {

   //      FATAL("axis::user2::process_init .1");

   //      return false;

   //   }


   //   //m_bAxisProcessInitializeResult = true;

   //   FATAL("axis::user2::process_init success");

   //   return true;

   //}


   //::estatus user2::init_instance()
   //{

   //   //if (m_bAxisInitializeInstance)
   //   //{

   //   //   return m_bAxisInitializeInstanceResult;

   //   //}

   //   INFO("axis::user2::init_instance .1");

   //   //m_bAxisInitializeInstance = true;

   //   //m_bAxisInitializeInstanceResult = false;

   //   if (!::aura::user2::init_instance())
   //   {

   //      FATAL("axis::user2::init_instance .2");

   //      return false;

   //   }


   //   if (m_bInitializeDataCentral)
   //   {


   //      ::file::path pathDatabase;

   //      if (is_system())
   //      {

   //         pathDatabase = Context.dir().appdata() / "system.sqlite";

   //      }
   //      else if (is_session())
   //      {

   //         pathDatabase = Context.dir().appdata() / "session.sqlite";

   //      }
   //      else
   //      {

   //         pathDatabase = Context.dir().appdata() / "app.sqlite";

   //      }

   //      auto estatus = m_psimpledb->initialize_simpledb_server(this, pathDatabase);

   //      if (!estatus)
   //      {

   //         m_result.add(estatus);

   //         return false;

   //      }

   //      set_data_server(m_psimpledb);

   //   }



   //   //m_bAxisInitializeInstanceResult = true;

   //   INFO("axis::user2::init_instance success");

   //   return true;

   //}


   ::database::key user2::calc_data_key()
   {

      return ::database::key("app://" + m_strAppName, is_local_data());

   }




   //::estatus user2::init1()
   //{

   //   //if (m_bAxisInitialize1)
   //   //{

   //   //   return m_bAxisInitialize1Result;

   //   //}

   //   //m_bAxisInitialize1 = true;

   //   //m_bAxisInitialize1Result = false;

   //   m_tickHeartBeat.Now();

   //   if (!::aura::user2::init1())
   //   {

   //      return false;

   //   }

   //   /*     if (!m_psystem->m_phtml->initialize())
   //        {

   //           return false;

   //        }*/



   //        //m_bAxisInitialize1Result = true;

   //   return true;

   //}


   //::estatus user2::init2()
   //{

   //   if (!::aura::user2::init2())
   //      return false;

   //   return true;

   //}


   //::estatus user2::init3()
   //{

   //   if (!::aura::user2::init3())
   //   {

   //      return false;

   //   }

   //   return true;

   //}

//


   ::estatus user2::init()
   {

      //if (m_bAxisInitialize)
      //{

      //   return m_bAxisInitializeResult;

      //}

      //m_bAxisInitialize = true;

      //m_bAxisInitializeResult = false;

      ::aura::application_message signal(::aura::application_message_init);

      route_message(&signal);

      if (!signal.m_bOk)
         return false;
      m_tickHeartBeat.Now();

      if (is_system())
      {

         if (has_property("save_processing"))
         {

            Session.savings().save(::aura::resource_processing);

         }

         if (has_property("save_blur_back"))
         {

            Session.savings().save(::aura::resource_blur_background);

         }

         if (has_property("save_transparent_back"))
         {

            Session.savings().save(::aura::resource_translucent_background);

         }

      }

      if (has_property("install"))
      {
         // aura level app install
         if (!Ex2OnAppInstall())
            return false;
      }
      else if (has_property("uninstall"))
      {
         // aura level app uninstall
         if (!Ex2OnAppUninstall())
            return false;
      }
      else
      {
#ifdef WINDOWS_DESKTOP
         // when this process is started in the context of a system account,
         // for example, this code ensure that the process will
         // impersonate a loggen on ::account::user
         HANDLE hprocess;
         HANDLE htoken;

         hprocess = ::GetCurrentProcess();

         if (!OpenProcessToken(
            hprocess,
            TOKEN_ALL_ACCESS,
            &htoken))
            return false;

         if (!ImpersonateLoggedOnUser(htoken))
         {
            TRACELASTERROR();
            return false;
         }
#endif
      }
      m_tickHeartBeat.Now();

      //if(is_system()
      //      && !m_varTopicQuery["app"].get_string().begins_ci("app-core/netnode")
      //      && m_varTopicQuery["app"] != "app-core/netnode_dynamic_web_server"
      //      && m_varTopicQuery["app"] != "app-gtech/alarm"
      //      && m_varTopicQuery["app"] != "app-gtech/sensible_service")
      //{
      //   Context.http().defer_auto_initialize_proxy_configuration();
      //}
      m_tickHeartBeat.Now();

      //      m_bAxisInitializeResult = true;

      //      dappy(string(typeid(*this).name()) + " : initialize ok : " + __str(m_iErrorCode));


      //::estatus user2::init()
      //{

      //   if (!::aura::user2::init())
      //   {

      //      return false;

      //   }

         //xxdebug_box("::aura::user2::initialize ok", "::aura::user2::initialize ok", MB_ICONINFORMATION);

         //xxdebug_box("m_pcalculator::initialize ok", "m_pcalculator::initialize ok", MB_ICONINFORMATION);

         //xxdebug_box("m_pcolorertake5::initialize ok", "m_pcolorertake5::initialize ok", MB_ICONINFORMATION);

         m_tickHeartBeat.Now();

         if (!initialize_userex())
         {

            return false;

         }

         //xxdebug_box("m_pfilemanager::initialize ok", "m_pfilemanager::initialize ok", MB_ICONINFORMATION);

         //xxdebug_box("m_pusermail::initialize ok", "m_pusermail::initialize ok", MB_ICONINFORMATION);
         m_tickHeartBeat.Now();

         //xxdebug_box("register_bergedge_application ok", "register_bergedge_application ok", MB_ICONINFORMATION);
         m_tickHeartBeat.Now();

         ensure_app_interest();

         //xxdebug_box("ensure_app_interest ok", "ensure_app_interest ok", MB_ICONINFORMATION);


         INFO(".2");

         if (!is_session() && !is_system())
         {

            if (is_true("install"))
            {

               if (is_user_service())
               {

                  //               if (Session.account()->m_puser != nullptr && Session.account()->m_puser->m_strLogin == "system")
                  //               {
                  //
                  //                  Session.account()->m_puser = nullptr;
                  //
                  //               }
                  //
                  //               if (!m_strAppId.begins_ci("app-core/netnode") && m_strAppId != "app-core/mydns")
                  //               {
                  //
                  //                  ApplicationUser;
                  //
                  //               }

               }

            }
            else
            {

               //Session.keyboard();

            }

            ERR("1.1");

            index i = applicationmenu().get_count();

            applicationmenu().add_item(i++, _("Transparent Frame"), "transparent_frame");

            application_menu_update();

         }

         INFO("success");

      //   return true;

      //}

      return true;

   }


//

   //void user2::term_application()
   //{


   //   try
   //   {


   //      //destroy_message_queue();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //   release_exclusive();

   //   ::aura::application_message signal(::aura::application_message_term_instance);

   //   try
   //   {

   //      route_message(&signal);

   //   }
   //   catch (...)
   //   {

   //   }

   //   try
   //   {

   //      try
   //      {

   //         aura::user2::term_application();

   //      }
   //      catch (...)
   //      {

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //   if (m_psimpledb.is_set())
   //   {

   //      try
   //      {

   //         m_psimpledb->finalize();

   //      }
   //      catch (...)
   //      {

   //         m_result.add(error_failed);

   //      }

   //   }

   //   m_psimpledb.release();

   //}


   void user2::term()
   {



   }


   bool user2::is_running()
   {

      return is_alive();

   }


   //bool user2::Ex2OnAppInstall()
   //{
   //   return true;
   //}


   //bool user2::Ex2OnAppUninstall()
   //{

   //   return true;

   //}


   bool user2::update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative)
   {

      auto plocaleschema = __create_new < ::str::international::locale_schema >();

      //Session.fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, plocaleschema->m_idLocale, plocaleschema->m_idSchema);

      ::count iCount = plocaleschema->m_idaLocale.get_count();

      for (index i = 0; i < iCount; i++)
      {

         if (plocaleschema->m_idaLocale[i] == __id(std) && plocaleschema->m_idaSchema[i] == __id(std) && bIgnoreStdStd)
            continue;

         string strLocale;

         plocaleschema->m_idaLocale[i].to_string(strLocale);

         string strSchema;

         plocaleschema->m_idaSchema[i].to_string(strSchema);

         update_appmatter(handler, psession, pszRoot, pszRelative, strLocale, strSchema);

         System.install_progress_add_up();

      }


      return true;

   }

   bool user2::update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession, const ::file::path & pszRoot, const string & pszRelative, const string & pszLocale, const string & pszStyle)
   {

      string strLocale;
      string strSchema;
      TRACE("update_appmatter(root=%s, relative=%s, locale=%s, style=%s)", pszRoot.c_str(), pszRelative.c_str(), pszLocale.c_str(), pszStyle.c_str());
      ::file::path strRelative = ::file::path(pszRoot) / "_matter" / pszRelative / get_locale_schema_dir(pszLocale, pszStyle) + ".zip";
      ::file::path strFile = Context.dir().install() / strRelative;
      ::file::path strUrl(::file::path_url);

      if (framework_is_basis())
      {
         strUrl = "http://basis-server.ca2.cc/api/spaignition/download?authnone&configuration=basis&stage=";
      }
      else
      {
         strUrl = "http://stage-server.ca2.cc/api/spaignition/download?authnone&configuration=stage&stage=";
      }

      strUrl += System.url().url_encode(strRelative);

      if (psession == nullptr)
      {

         while (true)
         {

            property_set setEmpty;

            if (Context.http().open(handler, psession, System.url().get_server(strUrl), System.url().get_protocol(strUrl), setEmpty, nullptr))
            {

               break;

            }

            Sleep(200);

         }

      }

      property_set set;

      set["get_memory"] = "";

      if (!Context.http().request(handler, psession, strUrl, set))
      {

         return false;

      }

      ::memory_file file;

      if (set["get_memory"].cast < memory >() != nullptr && set["get_memory"].cast < memory >()->get_size() > 0)
      {

         zip_context zip(get_context_object());

         string strDir = strFile;

         ::str::ends_eat_ci(strDir, ".zip");

         try
         {

            zip.extract_all(strDir, &file);

         }
         catch (...)
         {

            // spa app_app_admin.exe would recover by retrying or someone would fix the resource packaging problem and then zip extraction at least should work.

            return false;

         }

         //System.compress().extract_all(strFile, this);

      }

      return true;

   }





   bool user2::assert_user_logged_in()
   {

      const char * pszRequestUrl = nullptr;

      string strRequestUrl;

      if (file_as_string(::dir::system() / "config\\system\\ignition_server.txt").has_char())
      {

         strRequestUrl = "https://" + file_as_string(::dir::system() / "config\\system\\ignition_server.txt") + "/api/spaignition";

         pszRequestUrl = strRequestUrl;

      }

      if (get_context_session() == nullptr)
      {

         return false;

      }

      if (get_context_session()->account() == nullptr)
      {

         return false;

      }

      if (interactive_get_user() == nullptr)
      {

         return false;

      }

      return true;

   }




   string user2::matter_as_string(const char * pszMatter, const char * pszMatter2)
   {

      var varFile;

      varFile["disable_ca2_sessid"] = true;

      string strMatter = Context.dir().matter(::file::path(pszMatter) / pszMatter2);

      varFile["url"] = strMatter;

      return Context.file().as_string(varFile);

   }

   //string user2::dir().matter(const char * pszMatter,const char * pszMatter2)
   //{

   //   return dir().matter(pszMatter,pszMatter2);

   //}

   //bool user2::is_inside_time_dir(const char * pszPath)
   //{
   //   return dir().is_inside_time(pszPath);
   //}


   //bool user2::file_is_read_only(const char * pszPath)
   //{

   //   return false;
   //   //return file().is_read_only(pszPath);

   //}



   //void user2::process_message_filter(i32 code, ::message::message * pmessage)
   //{

   //   //SCAST_PTR(::message::base,pbase,pmessage);

   //   UNREFERENCED_PARAMETER(code);

   //   UNREFERENCED_PARAMETER(pmessage);


   //}







   void user2::DoWaitCursor(i32 nCode)
   {

      if (nCode < 0)
      {

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else if (nCode == 0)
      {

         if (m_iWaitCursorCount > 0)
         {
            m_iWaitCursorCount--;
         }

         if (m_iWaitCursorCount > 0)
         {

            ShowWaitCursor(true);

         }

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else
      {

         if (m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         ShowWaitCursor(true);

      }



   }

   //void user2::ShowWaitCursor(bool bShow)
   //{

   //}



   //void user2::TermThread(HINSTANCE hInstTerm)
   //{

   //   ::exception::throw_interface_only();

   //}




   //string user2::get_version()
   //{

   //   ::exception::throw_interface_only();

   //   return "";

   //}




//   void user2::set_env_var(const string & var,const string & value)
//   {
//
//      ::exception::throw_interface_only();
//
//   }



   ::aura::printer * user2::get_printer(const char * pszDeviceName)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   //bool user2::do_prompt_file_name(var & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   //{

   //   UNREFERENCED_PARAMETER(varFile);
   //   UNREFERENCED_PARAMETER(nIDSTitle);

   //   return false;

   //}






   //bool user2::get_temp_file_name_template(string & strRet,const char * lpszName,const char * pszExtension,const char * pszTemplate)
   //{

   //   __throw(not_implemented());

   //   return false;

   //}


   //bool user2::get_temp_file_name(string & strRet,const char * lpszName,const char * pszExtension)
   //{

   //   return get_temp_file_name_template(strRet,lpszName,pszExtension,nullptr);

   //}








   //::draw2d::icon * user2::set_icon(object * pobject, ::draw2d::icon * picon, bool bBigIcon)
   //{

   //   return nullptr;

   //}


   //::draw2d::icon * user2::get_icon(object * pobject, bool bBigIcon) const
   //{

   //   return nullptr;

   //}


   //void user2::on_service_request(::create * pcreate)
   //{

   //   ::aura::user2::on_service_request(pcreate);

   //}


   string user2::get_mutex_name_gen()
   {
      return m_strAppName;
   }



   string user2::get_license_id()
   {

      if (m_strLicense.has_char())
         return m_strLicense;

      if (m_strInstallToken.has_char())
         return m_strInstallToken;

      return m_strAppId;

   }






   //bool user2::assert_user_logged_in()
   //{

   //   return axis::user2::assert_user_logged_in();

   //}





   i32 user2::hotplugin_host_starter_start_sync(const char * pszCommandLine, ::aura::user2 * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      {

         ::install::mutex mutex(process_platform_dir_name2());

         if (mutex.already_exists())
         {

            //            message_box("Could not launch spa installer. It is already running.", MB_OK);

            return -35;

         }

      }

      string strValue;

      if (get_command_line_param(strValue, pszCommandLine, "enable_desktop_launch"))
      {

#ifdef _UWP

         return -1;

#else

         ::property_set set;

         return ::call_sync(::path::app_app(process_platform_dir_name2(), process_configuration_dir_name()), pszCommandLine, ::path::app_app(process_platform_dir_name2(), process_configuration_dir_name()), display_normal, 2_min, set);

#endif

      }
      else
      {

         return hotplugin_host_host_starter_start_sync(pszCommandLine, get_context_application(), nullptr);

      }

   }

   i32 user2::hotplugin_host_host_starter_start_sync(const char * pszCommandLine, ::aura::user2 * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      return -1;

   }



   //void user2::on_control_event(::user::control_event * pevent)
   //{

   //}


   bool user2::on_open_document(::user::document * pdocument, var varFile)
   {

      UNREFERENCED_PARAMETER(pdocument);
      UNREFERENCED_PARAMETER(varFile);
      return true;

   }


   bool user2::on_save_document(::user::document * pdocument, var varFile)
   {

      UNREFERENCED_PARAMETER(pdocument);
      UNREFERENCED_PARAMETER(varFile);
      return true;

   }


   void user2::on_update_view(::user::impact * pview, ::user::impact * pviewSender, LPARAM lHint, object * pHint)
   {


   }

   //void user2::on_control_event(::user::control_event* pevent)
   //{

   //}


   void user2::on_notify_control_event(::user::control_event* pevent)
   {


   }


   void user2::route_control_event(::user::control_event* pevent)
   {

      on_control_event(pevent);

      if (pevent->m_bRet)
      {

         return;

      }

      on_notify_control_event(pevent);

      if (pevent->m_bRet)
      {

         return;

      }

   }



   //   ::estatus     user2::interactive_credentials(::account::credentials * pcredentials)
   //   {
   //
   //      return ::aura::applciation::interactive_credentials(pcredentials);
   //
   //   }
   //
   //
   //   string user2::interactive_get_credentials(string & strUsername, string & strPassword, string strToken)
   //   {
   //
   //      return ::account::get_cred(this, strUsername, strPassword, strToken);
   //
   //   }
   //
   //   void user2::set_cred(string strToken, const char * pszUsername, const char * pszPassword)
   //   {
   //
   //      ::account::set_cred(this,strToken, pszUsername, pszPassword);
   //
   //   }
   //
   //   void user2::set_cred_ok(string strToken, bool bOk)
   //   {
   //
   //      ::account::set_cred_ok(this, strToken, bOk);
   //
   //   }

      //::html::html * user2::create_html()
      //{

      //   return new ::html::html(get_context_application());

      //}


      //string user2::http_get(const string & strUrl, ::property_set & set)
      //{

      //   return http().get(strUrl, set);

      //}

      //bool user2::app_data_set(::const ::id & id, stream & stream)
      //{

      //   return data_save(id, stream);

      //}


      //bool user2::app_data_get(::const ::id & id, stream & stream)
      //{

      //   return data_get(id, stream);

      //}


      //bool user2::app_data_set(::const ::id & id, ::object & obj)
      //{

      //   return data_set(id, obj);

      //}


      //bool user2::app_data_get(::const ::id & id, ::object & obj)
      //{

      //   return data_get(id, obj);

      //}


      //bool user2::compress_ungz(const ::stream & os, const ::stream & is)
      //{

      //   return System.compress().ungz(this, os, is);


      //}


      //bool user2::compress_ungz(memory_base & mem)
      //{

      //   return System.compress().ungz(this, mem);

      //}


      //bool user2::compress_gz(const ::stream & os, const ::stream & is, int iLevel)

      //{

      //   return System.compress().gz(this, os, is, iLevel);


      //}


      //bool user2::compress_gz(const ::stream & os, const ::stream & is, int iLevel)
      //{

      //   return System.compress().gz(this, os, is, iLevel);

      //}


   bool user2::is_local_data()
   {

      return m_datakey.m_bLocalData;

   }





} // namespace aura







namespace aura
{


   const char user2::gen_FileSection[] = "Recent File List";
   const char user2::gen_FileEntry[] = "File%d";
   const char user2::gen_PreviewSection[] = "Settings";
   const char user2::gen_PreviewEntry[] = "PreviewPages";


   //user2::user2()
   //{

   //   create_factory < ::user::user >();
   //   create_factory < ::userfs::userfs >();

   //   m_pmainpane = nullptr;

   //   m_ppaneviewMain = nullptr;

   //   // almost always forgotten, assumed, as exception, responsability of user2 to add first ref on constructor.
   //   //::add_ref(this);

   //   srand((u32) ::get_tick());

   //   m_bService = false;

   //   m_iResourceId = 8001;

   //   ::aura::profiler::initialize();

   //   m_pdocmanager = nullptr;

   //   m_eexclusiveinstance = ExclusiveInstanceNone;
   //   m_strLocale = "_std";
   //   m_strSchema = "_std";

   //   m_iGcomBackgroundUpdateMillis = -1;

   //}


   //user2::~user2()
   //{

   //}


   //::estatus user2::initialize(::object* pobjectContext)
   //{

   //   auto estatus = ::aura::user2::initialize(pobjectContext);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


   bool user2::on_application_menu_action(const char* pszCommand)
   {

      if (m_puiMain1 != nullptr)
      {

         ::user::command command;

         command.m_id = ::id(pszCommand);

         m_puiMain1->route_command_message(&command);

         if (command.m_bRet)
         {

            return true;

         }

      }

      return false;

   }


   //::aura::user2 * user2::get_context_application() const
   //{

   //   return (user2 *) this;

   //}








   //bool user2::is_system() const
   //{

   //   return false;

   //}


   //bool user2::is_session() const
   //{

   //   return false;

   //}


   u32 user2::guess_code_page(const string& str)
   {

      return 0;

   }


   LRESULT user2::GetPaintMsgProc(i32 nCode, WPARAM wParam, LPARAM lParam)
   {

      UNREFERENCED_PARAMETER(nCode);
      UNREFERENCED_PARAMETER(wParam);
      UNREFERENCED_PARAMETER(lParam);

      return 0;

   }


   bool user2::CreateFileFromRawResource(UINT nID, const char* pcszType, const char* pcszFilePath)
   {

      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pcszType);
      UNREFERENCED_PARAMETER(pcszFilePath);

      return false;

   }


#ifdef WINDOWS

   bool user2::OnMessageWindowMessage(LPMESSAGE pmsg)

   {

      UNREFERENCED_PARAMETER(pmsg);


      return false;

   }

#elif defined(LINUX)

   bool user2::OnX11WindowMessage(void* pXevent) // XEvent *
   {

      UNREFERENCED_PARAMETER(pXevent);

      return false;

   }

#endif

   void user2::OnUpdateRecentFileMenu(::user::command* pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

   }


   bool user2::GetResourceData(UINT nID, const char* pcszType, memory& storage)

   {

      UNREFERENCED_PARAMETER(nID);
      UNREFERENCED_PARAMETER(pcszType);

      UNREFERENCED_PARAMETER(storage);

      return false;

   }


#ifdef WINDOWS_DESKTOP

   HENHMETAFILE user2::LoadEnhMetaFile(UINT uiResource)
   {

      memory storage;

      if (!GetResourceData(uiResource, "EnhMetaFile", storage))
      {

         return nullptr;

      }

      return SetEnhMetaFileBits((UINT)storage.get_size(), storage.get_data());

   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // WinApp UI related functions

   void user2::EnableModelessEx(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
#endif


   }



  /* ::estatus     user2::run()
   {

      return ::aura::user2::run();

   }*/


   bool user2::on_idle(LONG lCount)
   {

      return false;

   }


   void user2::process_window_procedure_exception(::exception_pointer pe, ::message::message* pmessage)
   {

      ENSURE_ARG(pe != nullptr);

      ENSURE_ARG(pmessage != nullptr);

      SCAST_PTR(::message::base, pbase, pmessage);

      // handle certain messages in thread

      switch (pbase->m_id)
      {
      case WM_CREATE:
      case WM_PAINT:

         return thread::process_window_procedure_exception(pe, pmessage);

      }

      // handle all the rest
      //linux UINT nIDP = __IDP_INTERNAL_FAILURE;   // generic message string
      const char* nIDP = "Internal Failure";
      pbase->m_lresult = 0;        // sensible default
      if (pbase->m_id == WM_COMMAND)
      {
         if (pbase->m_lparam == 0)
            //linux nIDP = __IDP_COMMAND_FAILURE; // command (not from a control)
            nIDP = "Command Failure";
         pbase->m_lresult = (LRESULT)TRUE;        // pretend the command was handled
      }

      if (pe.is < memory_exception >())
      {

         report_error(pe, MB_ICONEXCLAMATION | MB_SYSTEMMODAL, nIDP);

      }
      else if (pe.is < user_exception >())
      {

         // ::account::user has not been alerted yet of this catastrophic problem

         report_error(pe, MB_ICONSTOP, nIDP);

      }

   }


   void user2::route_command_message(::user::command* pcommand)
   {

      ::thread::route_command_message(pcommand);

   }


   /*
   bool user2::hex_to_memory(memory & memory, const char * pszHex)
   {
   ::count len = strlen(pszHex);
   ::count count = (len + 1) / 2;
   memory.set_size(count);
   index i = 0;
   byte b;
   while(*pszHex != '\0')
   {
   char ch = (char) tolower(*pszHex);
   if(ch >= '0' && ch <= '9')
   {
   b = ch - '0';
   }
   else if(ch >= 'a' && ch <= 'f')
   {
   b = ch - 'a' + 10;
   }
   else
   {
   return false;
   }
   pszHex++;
   if(*pszHex == '\0')
   {
   memory.get_data()[i] = b;
   return true;
   }
   b = b << 4;
   ch = (char) tolower(*pszHex);
   if(ch >= '0' && ch <= '9')
   {
   b |= (ch - '0');
   }
   else if(ch >= 'a' && ch <= 'f')
   {
   b |= (ch - 'a' + 10);
   }
   else
   {
   return false;
   }
   pszHex++;
   memory.get_data()[i] = b;
   i++;
   }
   return true;
   }


   void user2::memory_to_hex(string & strHex, memory & memory)
   {
   ::count count = memory.get_size();
   LPSTR psz = strHex.get_string_buffer(count * 2);

   for(index i = 0; i < count; i++)
   {
   *psz++ = ::hex::lower_from((byte) ((memory.get_data()[i] >> 4) & 0xf));

   *psz++ = ::hex::lower_from((byte) (memory.get_data()[i] & 0xf));

   }
   strHex.ReleaseBuffer(count * 2);
   }
   */











   // // BEGIN_MESSAGE_MAP(user2, channel)
   //{{__MSG_MAP(user2)
   // Global File commands
   //   ON_COMMAND(ID_APP_EXIT, &user2::OnAppExit)
   // MRU - most recently used file menu
   //   ON_UPDATE_::user::command(ID_FILE_MRU_FILE1, &user2::OnUpdateRecentFileMenu)
   //   ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, &user2::OnOpenRecentFile)
   //}}__MSG_MAP
   // // END_MESSAGE_MAP()

   /*#ifdef WINDOWS


   typedef LANGID (WINAPI*PFNGETUSERDEFAULTUILANGUAGE)();
   typedef LANGID (WINAPI*PFNGETSYSTEMDEFAULTUILANGUAGE)();


   class CActivationContext
   {
   protected :
   HANDLE m_hCtxt;
   uptr m_uCookie;

   // If pointers are nullptr then we are on a platform that does not support WinSXS.
   typedef HANDLE (WINAPI * PFNCreateActCtx)(PCACTCTX);
   static PFNCreateActCtx s_pfnCreateActCtx;

   typedef void (WINAPI * PFNReleaseActCtx)(HANDLE);
   static PFNReleaseActCtx s_pfnReleaseActCtx;

   typedef bool (WINAPI * PFNActivateActCtx)(HANDLE, uptr*);
   static PFNActivateActCtx s_pfnActivateActCtx;

   typedef bool (WINAPI * PFNDeactivateActCtx)(u32, uptr);
   static PFNDeactivateActCtx s_pfnDeactivateActCtx;

   static bool s_bPFNInitialized;

   public:
   CActivationContext(HANDLE hCtxt = INVALID_HANDLE_VALUE) : m_hCtxt( hCtxt ), m_uCookie( 0 )
   {
   // Multiple threads initializing is fine since they will initialize the pointers to the
   // same value.
   if (!s_bPFNInitialized)
   {
   HMODULE hKernel = GetModuleHandle("KERNEL32");
   ENSURE (hKernel != nullptr);
   #ifdef _UNICODE
   s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxW");
   #else
   s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxA");
   #endif
   s_pfnReleaseActCtx = (PFNReleaseActCtx) GetProcAddress(hKernel, "ReleaseActCtx");
   s_pfnActivateActCtx = (PFNActivateActCtx) GetProcAddress(hKernel, "ActivateActCtx");
   s_pfnDeactivateActCtx = (PFNDeactivateActCtx) GetProcAddress(hKernel, "DeactivateActCtx");
   if (s_pfnCreateActCtx != nullptr)
   {
   // If one of the functions is present then all the functions have to be present.
   ENSURE( s_pfnReleaseActCtx != nullptr &&
   s_pfnActivateActCtx != nullptr &&
   s_pfnDeactivateActCtx != nullptr);
   }
   else
   {
   // If one of the functions is not present then all the functions should not be present.
   ENSURE( s_pfnReleaseActCtx == nullptr &&
   s_pfnActivateActCtx == nullptr &&
   s_pfnDeactivateActCtx == nullptr);
   }
   s_bPFNInitialized = true;
   }
   };

   ~CActivationContext()
   {
   Release();
   }

   bool create( PCACTCTX pactctx )
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnCreateActCtx == nullptr)
   {
   return true;
   }

   ASSERT( pactctx != nullptr );
   if ( pactctx == nullptr )
   {
   return false;
   }

   ASSERT( m_hCtxt == INVALID_HANDLE_VALUE );
   if ( m_hCtxt != INVALID_HANDLE_VALUE )
   {
   return false;
   }

   return ( ( m_hCtxt = s_pfnCreateActCtx( pactctx ) ) != INVALID_HANDLE_VALUE );
   }

   void Release()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnReleaseActCtx == nullptr)
   {
   return;
   }

   if ( m_hCtxt != INVALID_HANDLE_VALUE )
   {
   Deactivate();
   s_pfnReleaseActCtx( m_hCtxt );
   }
   }

   bool Activate()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnActivateActCtx == nullptr)
   {
   return true;
   }

   ASSERT( m_hCtxt != INVALID_HANDLE_VALUE );
   if ( m_hCtxt == INVALID_HANDLE_VALUE )
   {
   return false;
   }

   ASSERT( m_uCookie == 0 );
   if ( m_uCookie != 0 )
   {
   return false;
   }

   return ( s_pfnActivateActCtx( m_hCtxt, &m_uCookie) == TRUE );
   }

   bool Deactivate()
   {
   // nullptr on a platform that do not support WinSXS
   if (s_pfnDeactivateActCtx == nullptr)
   {
   return true;
   }

   if ( m_uCookie != 0 )
   {
   uptr uCookie = m_uCookie;
   m_uCookie = 0;
   return ( s_pfnDeactivateActCtx(0, uCookie) == TRUE );
   }
   return true;
   }
   };


   CActivationContext::PFNCreateActCtx CActivationContext::s_pfnCreateActCtx = nullptr;
   CActivationContext::PFNReleaseActCtx CActivationContext::s_pfnReleaseActCtx = nullptr;
   CActivationContext::PFNActivateActCtx CActivationContext::s_pfnActivateActCtx = nullptr;
   CActivationContext::PFNDeactivateActCtx CActivationContext::s_pfnDeactivateActCtx = nullptr;
   bool CActivationContext::s_bPFNInitialized = false;


   // HINSTANCE of the module
   extern "C" IMAGE_DOS_HEADER __ImageBase;

   */


   bool user2::LoadSysPolicies()
   {
      return _LoadSysPolicies();
   }

   // This function is not exception safe - will leak a registry key if exceptions are thrown from some places
   // To reduce risk of leaks, I've declared the whole function noexcept. This despite the fact that its callers have
   // no dependency on non-throwing.
   bool user2::_LoadSysPolicies() noexcept
   {

#ifdef WINDOWS_DESKTOP

      HKEY hkPolicy = nullptr;
      DWORD dwValue = 0;
      DWORD dwDataLen = sizeof(dwValue);
      DWORD dwType = 0;

      //// clear current policy settings.
      //m_dwPolicies = ___SYSPOLICY_NOTINITIALIZED;

      //static __system_policy_data rgExplorerData[] =
      //{
      //   {"NoRun",___SYSPOLICY_NORUN},
      //   {"NoDrives",___SYSPOLICY_NODRIVES},
      //   {"RestrictRun",___SYSPOLICY_RESTRICTRUN},
      //   {"NoNetConnectDisconnect",___SYSPOLICY_NONETCONNECTDISCONNECTD},
      //   {"NoRecentDocsHistory",___SYSPOLICY_NORECENTDOCHISTORY},
      //   {"NoClose",___SYSPOLICY_NOCLOSE},
      //   {nullptr,0}
      //};

      //static __system_policy_data rgNetworkData[] =
      //{
      //   {"NoEntireNetwork",___SYSPOLICY_NOENTIRENETWORK},
      //   {nullptr,0}
      //};

      //static __system_policy_data rgComDlgData[] =
      //{
      //   {"NoPlacesBar",___SYSPOLICY_NOPLACESBAR},
      //   {"NoBackButton",___SYSPOLICY_NOBACKBUTTON},
      //   {"NoFileMru",___SYSPOLICY_NOFILEMRU},
      //   {nullptr,0}
      //};

      //static __system_policies rgPolicies[] =
      //{
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
      //      rgExplorerData
      //   },
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",
      //      rgNetworkData
      //   },
      //   {  "Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32",
      //      rgComDlgData
      //   },
      //   {nullptr,0}
      //};

      //__system_policies *pPolicies = rgPolicies;
      //__system_policy_data *pData = nullptr;

      //while (pPolicies->szPolicyKey != nullptr)
      //{

      //   if (ERROR_SUCCESS == ::RegOpenKeyEx(
      //            HKEY_CURRENT_USER,
      //            pPolicies->szPolicyKey,
      //            0,
      //            KEY_QUERY_VALUE,
      //            &hkPolicy
      //         ))
      //   {
      //      pData = pPolicies->pData;
      //      while (pData->szPolicyName)
      //      {
      //         if (ERROR_SUCCESS == ::RegQueryValueEx(
      //                  hkPolicy,
      //                  pData->szPolicyName,
      //                  nullptr,
      //                  &dwType,
      //                  (BYTE*)&dwValue,
      //                  &dwDataLen))
      //         {
      //            if (dwType == REG_DWORD)
      //            {
      //               if (dwValue != 0)
      //                  m_dwPolicies |= pData->dwID;
      //               else
      //                  m_dwPolicies &= ~pData->dwID;
      //            }
      //         }
      //         dwValue = 0;
      //         dwDataLen = sizeof(dwValue);
      //         dwType = 0;
      //         pData++;
      //      }
      //      ::RegCloseKey(hkPolicy);
      //      hkPolicy = nullptr;
      //   }
      //   pPolicies++;
      //};

#endif

      return TRUE;


   }

   bool user2::GetSysPolicyValue(u32 dwPolicyID, bool* pbValue)
   {
      if (!pbValue)
         return FALSE; // bad pointer
      *pbValue = (m_dwPolicies & dwPolicyID) != 0;
      return TRUE;
   }

   //bool user2::InitApplication()
   //{


   //   LoadSysPolicies();

   //   return TRUE;


   //}



   /*   void user2::LoadStdProfileSettings(UINT nMaxMRU)
   {
   UNREFERENCED_PARAMETER(nMaxMRU);
   ASSERT_VALID(this);

   // 0 by default means not set
   m_nNumPreviewPages = GetProfileInt(gen_PreviewSection, gen_PreviewEntry, 0);
   }*/

   /*void user2::ParseCommandLine(CCommandLineInfo& rCmdInfo)
   {
   for (i32 i = 1; i < __argc; i++)
   {
   const char * pszParam = __targv[i];
   bool bFlag = FALSE;
   bool bLast = ((i + 1) == __argc);
   if (pszParam[0] == '-' || pszParam[0] == '/')
   {
   // remove flag specifier
   bFlag = TRUE;
   ++pszParam;
   }
   rCmdInfo.ParseParam(pszParam, bFlag, bLast);
   }
   }*/

   /////////////////////////////////////////////////////////////////////////////
   // CCommandLineInfo implementation

   /*CCommandLineInfo::CCommandLineInfo()
   {
   m_bShowSplash = TRUE;
   m_bRunEmbedded = FALSE;
   m_bRunAutomated = FALSE;
   m_nShellCommand = FileNew;
   }

   CCommandLineInfo::~CCommandLineInfo()
   {
   }

   void CCommandLineInfo::ParseParam(const char* pszParam,bool bFlag,bool bLast)
   {
   if (bFlag)
   {
   const astring strParam(pszParam);
   ParseParamFlag(strParam.GetString());
   }
   else
   ParseParamNotFlag(pszParam);

   ParseLast(bLast);
   }*/

   /*
   #ifdef UNICODE
   void CCommandLineInfo::ParseParam(const char* pszParam, bool bFlag, bool bLast)
   {
   if (bFlag)
   ParseParamFlag(pszParam);
   else
   ParseParamNotFlag(pszParam);

   ParseLast(bLast);
   }
   #endif // UNICODE
   */

   /*
   void CCommandLineInfo::ParseParamFlag(const char* pszParam)
   {
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (lstrcmpA(pszParam, "point") == 0)
   m_nShellCommand = FilePrintTo;
   else if (lstrcmpA(pszParam, "point") == 0)
   m_nShellCommand = FilePrint;
   else if (::__invariant_stricmp(pszParam, "Register") == 0 ||
   ::__invariant_stricmp(pszParam, "Regserver") == 0)
   m_nShellCommand = AppRegister;
   else if (::__invariant_stricmp(pszParam, "Unregister") == 0 ||
   ::__invariant_stricmp(pszParam, "Unregserver") == 0)
   m_nShellCommand = AppUnregister;
   else if (lstrcmpA(pszParam, "dde") == 0)
   {
   m_nShellCommand = FileDDE;
   }
   else if (::__invariant_stricmp(pszParam, "Embedding") == 0)
   {
   m_bRunEmbedded = TRUE;
   m_bShowSplash = FALSE;
   }
   else if (::__invariant_stricmp(pszParam, "Automation") == 0)
   {
   m_bRunAutomated = TRUE;
   m_bShowSplash = FALSE;
   }
   }

   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
   {
   if (m_strFileName.is_empty())
   m_strFileName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
   m_strPrinterName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
   m_strDriverName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
   m_strPortName = pszParam;
   }

   #ifdef UNICODE
   void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
   {
   if (m_strFileName.is_empty())
   m_strFileName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
   m_strPrinterName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
   m_strDriverName = pszParam;
   else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
   m_strPortName = pszParam;
   }
   #endif

   void CCommandLineInfo::ParseLast(bool bLast)
   {
   if (bLast)
   {
   if (m_nShellCommand == FileNew && !m_strFileName.is_empty())
   m_nShellCommand = FileOpen;
   m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
   }
   }
   */

   /////////////////////////////////////////////////////////////////////////////
   // App termination

   void user2::SaveStdProfileSettings()
   {
      ASSERT_VALID(this);


      //      if (m_nNumPreviewPages != 0)
      //       WriteProfileInt(gen_PreviewSection, gen_PreviewEntry, m_nNumPreviewPages);
   }


   //
   //
   //
   //
   //#ifdef WINDOWS_DESKTOP
   //
   //
   //   /////////////////////////////////////////////////////////////////////////////
   //   // WinHelp Helper
   //
   //
   //   void user2::WinHelp(uptr dwData, UINT nCmd)
   //   {
   //      UNREFERENCED_PARAMETER(dwData);
   //      UNREFERENCED_PARAMETER(nCmd);
   //
   //      // return global cast help mode state to FALSE (backward compatibility)
   //      m_bHelpMode = FALSE;
   //      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
   //
   //      //trans pMainWnd->WinHelp(dwData, nCmd);
   //   }
   //
   //   /////////////////////////////////////////////////////////////////////////////
   //   // HtmlHelp Helper
   //
   //   void user2::HtmlHelp(uptr dwData, UINT nCmd)
   //   {
   //
   //      UNREFERENCED_PARAMETER(dwData);
   //
   //      UNREFERENCED_PARAMETER(nCmd);
   //
   //      // return global cast help mode state to FALSE (backward compatibility)
   //      m_bHelpMode = FALSE;
   //      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
   //
   //      // trans pMainWnd->HtmlHelp(dwData, nCmd);
   //   }
   //
   //
   //   void user2::WinHelpInternal(uptr dwData, UINT nCmd)
   //   {
   //      UNREFERENCED_PARAMETER(dwData);
   //      UNREFERENCED_PARAMETER(nCmd);
   //      //   __pointer(::user::interaction) pMainWnd = System.m_puiMain;
   //      //   ENSURE_VALID(pMainWnd);
   //
   //      // return global cast help mode state to FALSE (backward compatibility)
   //      m_bHelpMode = FALSE;
   //      // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
   //      // trans pMainWnd->WinHelpInternal(dwData, nCmd);
   //   }
   //
   //
   //#endif
   //




      /////////////////////////////////////////////////////////////////////////////
      // user2 idle processing

   void user2::DevModeChange(LPTSTR pDeviceName)

   {
      UNREFERENCED_PARAMETER(pDeviceName);


#ifdef WINDOWS
      if (m_hDevNames == nullptr)
         return;

#endif

   }


   //bool user2::process_exception(::exception_pointer pe)
   //{

   //   return ::aura::user2::on_run_exception(pexception))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool user2::final_handle_exception(::exception::exception * pexception)
   //{

   //   UNREFERENCED_PARAMETER(pexception);

   //   if (!is_system())
   //   {

   //      if (System.final_handle_exception(pexception))
   //      {

   //         return true;

   //      }

   //   }

   //   return false;

   //}


   /*   bool user2::open_link(const char * pszLink, const char * pszTarget)
   {
   UNREFERENCED_PARAMETER(pszLink);
   UNREFERENCED_PARAMETER(pszTarget);
   return false;
   }
   */










   void user2::_001OnFileNew()
   {
      string strId = m_strId;
      char chFirst = '\0';
      if (strId.get_length() > 0)
      {
         chFirst = strId[0];
      }
      /*      if (m_pdocmanager != nullptr)
      document_manager()->_001OnFileNew();*/
   }

   void user2::on_file_open()
   {
      ENSURE(m_pdocmanager != nullptr);
      //document_manager()->on_file_open();
   }


   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /*void ::aura::FormatString1(string & rString, UINT nIDS, const char * psz1)

   {
   __format_strings(rString, nIDS, &psz1, 1);

   }

   void ::aura::FormatString2(string & rString, UINT nIDS, const char * psz1,

   const char * psz2)

   {
   const char * rgpsz[2];
   rgpsz[0] = psz1;

   rgpsz[1] = psz2;

   __format_strings(rString, nIDS, rgpsz, 2);
   }*/

   /////////////////////////////////////////////////////////////////////////////


   /////////////////////////////////////////////////////////////////////////////
   // Basic Help support (for backward compatibility to aura API 2.0)

   void user2::OnHelp()  // use context to derive help context
   {
      if (m_dwPromptContext != 0)
      {
         // do not call WinHelp when the error is failing to lauch help
         //         if (m_dwPromptContext != HID_BASE_PROMPT+__IDP_FAILED_TO_LAUNCH_HELP)
         //          WinHelpInternal(m_dwPromptContext);
         return;
      }

      // otherwise, use window::OnHelp implementation
      /* trans ::user::interaction_impl * pwindow = System.m_puiMain;
      ENSURE_VALID(pwindow);
      if (!pwindow->is_frame_window())
      pwindow->OnHelp();
      else
      ((pwindow))->OnHelp();*/
   }


   void user2::OnHelpIndex()
   {
      //
      //#ifdef WINDOWS_DESKTOP
      //
      //      WinHelpInternal(0L, HELP_INDEX);
      //
      //#endif
      //
   }


   void user2::OnHelpFinder()
   {

      //#ifdef WINDOWS_DESKTOP
      //
      //      WinHelpInternal(0L, HELP_FINDER);
      //
      //#endif

   }


   void user2::OnHelpUsing()
   {

      //#ifdef WINDOWS_DESKTOP
      //
      //      WinHelpInternal(0L, HELP_HELPONHELP);
      //
      //#endif
      //
   }


   /////////////////////////////////////////////////////////////////////////////
   // Context Help Mode support (backward compatibility to aura API 2.0)

   void user2::OnContextHelp()
   {
      // just use frame_window::OnContextHelp implementation
      /* trans   m_bHelpMode = HELP_ACTIVE;
      __pointer(::user::frame_window) pMainWnd = (System.m_puiMain);
      ENSURE_VALID(pMainWnd);
      ENSURE(pMainWnd->is_frame_window());
      pMainWnd->OnContextHelp();
      m_bHelpMode = pMainWnd->m_bHelpMode;
      pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update */
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //




   /////////////////////////////////////////////////////////////////////////////
   // WinApp support for printing

   /*bool user2::GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg)
   {
   UpdatePrinterSelection(m_hDevNames == nullptr); //force default if no current
   if (m_hDevNames == nullptr)
   return FALSE;               // no printer defaults

   ENSURE_ARG(pPrintDlg != nullptr);
   pPrintDlg->hDevNames = m_hDevNames;
   pPrintDlg->hDevMode = m_hDevMode;

   ::GlobalUnlock(m_hDevNames);
   ::GlobalUnlock(m_hDevMode);
   return TRUE;
   }*/

   void user2::UpdatePrinterSelection(bool bForceDefaults)
   {
      UNREFERENCED_PARAMETER(bForceDefaults);
   }


   void user2::OnFilePrintSetup()
   {
   }

   void user2::SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld)
   {
      UNREFERENCED_PARAMETER(hDevNames);
      UNREFERENCED_PARAMETER(hDevMode);
      UNREFERENCED_PARAMETER(bFreeOld);
      ::exception::throw_not_implemented();
   }

   ::draw2d::graphics* user2::CreatePrinterDC()
   {
      ::exception::throw_not_implemented();
      return nullptr;
   }

   /////////////////////////////////////////////////////////////////////////////


   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //



   /////////////////////////////////////////////////////////////////////////////
   // user2 User Interface Extensions

   void user2::OnAppExit()
   {

      // same as double-clicking on main window close box

      ASSERT(m_puiMain1 != nullptr);

      m_puiMain1->m_puiThis->send_message(WM_CLOSE);

   }


   //void user2::HideApplication()
   //{

   //   try
   //   {

   //      if (m_puiMain1 == nullptr)
   //      {

   //         return;

   //      }

   //      // hide the user2's windows before closing all the documents
   //      m_puiMain1->m_puiThis->display(display_none);
   //      // trans    m_puiMain->ShowOwnedPopups(FALSE);


   //      m_puiMain1->m_puiThis->order(zorder_bottom);
   //      //m_puiMain->m_puiThis->m_bZ = true;
   //      // put the window at the bottom of zorder, so it isn't activated
   //      // m_puiMain->m_puiThis->zorder();

   //      //m_puiMain->m_puiThis->wait_redraw();

   //      m_puiMain1->m_puiThis->display(display_none);


   //   }
   //   catch (...)
   //   {
   //   }

   //}





   bool user2::save_all_modified()
   {
      /*      if (m_pdocmanager != nullptr)
      return document_manager()->save_all_modified();*/
      return TRUE;
   }



   //   bool user2::OnDDECommand(LPTSTR pszCommand)
   //
   //   {
   //      /*      if (m_pdocmanager != nullptr)
   //      return document_manager()->OnDDECommand(pszCommand);
   //
   //      else*/
   //      return FALSE;
   //   }



   void user2::EnableModeless(bool bEnable)
   {
      DoEnableModeless(bEnable);
   }

   void user2::DoEnableModeless(bool bEnable)
   {
      UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
      UNUSED(bEnable);
#endif

      // no-op if main window is nullptr or not a frame_window
      /*   __pointer(::user::interaction) pMainWnd = System.m_puiMain;
      if (pMainWnd == nullptr || !pMainWnd->is_frame_window())
      return;*/

#ifndef ___NO_OLE_SUPPORT
      // check if notify hook installed
      /*xxx
      ASSERT_KINDOF(frame_window, pMainWnd);
      __pointer(::user::frame_window) pFrameWnd = (__pointer(::user::frame_window))pMainWnd;
      if (pFrameWnd->m_pNotifyHook != nullptr)
      pFrameWnd->m_pNotifyHook->OnEnableModeless(bEnable);
      */
#endif
   }












   void user2::RegisterShellFileTypes(bool bCompat)
   {
      ENSURE(m_pdocmanager != nullptr);
      //      document_manager()->RegisterShellFileTypes(bCompat);
   }

   void user2::UnregisterShellFileTypes()
   {
      ENSURE(m_pdocmanager != nullptr);
      //    document_manager()->UnregisterShellFileTypes();
   }


   i32 user2::get_open_document_count()
   {
      ENSURE(m_pdocmanager != nullptr);
      //  return document_manager()->get_open_document_count();
      return 0;
   }


   // This is aura API library.
   //
   //
   //
   //
   //
   //
   //
   //

   /////////////////////////////////////////////////////////////////////////////
   // user2 Settings Helpers


   void user2::SetRegistryKey(const char* pszRegistryKey)

   {
      //ASSERT(m_pszRegistryKey == nullptr);
      //ASSERT(pszRegistryKey != nullptr);

      //ASSERT(m_strAppName.has_char());

      ////bool bEnable = __enable_memory_tracking(FALSE);
      //free((void *)m_pszRegistryKey);
      //m_pszRegistryKey = strdup(pszRegistryKey);

      //free((void *)m_pszProfileName);
      //m_pszProfileName = strdup(m_strAppName);
      ////__enable_memory_tracking(bEnable);
   }

   void user2::SetRegistryKey(UINT nIDRegistryKey)
   {
      //UNREFERENCED_PARAMETER(nIDRegistryKey);
      //ASSERT(m_pszRegistryKey == nullptr);
      //::exception::throw_not_implemented();
      ///*char szRegistryKey[256];
      //VERIFY(::aura::LoadString(nIDRegistryKey, szRegistryKey));
      //SetRegistryKey(szRegistryKey);*/
   }


#ifdef WINDOWS_DESKTOP

   // returns key for HKEY_CURRENT_USER\"Software"\RegistryKey\ProfileName
   // creating it if it doesn't exist
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY user2::GetAppRegistryKey()
   {
      //ASSERT(m_pszRegistryKey != nullptr);
      //ASSERT(m_pszProfileName != nullptr);

      //HKEY hAppKey = nullptr;
      //HKEY hSoftKey = nullptr;
      //HKEY hCompanyKey = nullptr;
      //if(RegOpenKeyEx(HKEY_CURRENT_USER,"software",0,KEY_WRITE | KEY_READ,
      //   &hSoftKey) == ERROR_SUCCESS)
      //{
      //   DWORD dw;
      //   if(RegCreateKeyEx(hSoftKey,m_pszRegistryKey,0,REG_NONE,
      //      REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,nullptr,
      //      &hCompanyKey,&dw) == ERROR_SUCCESS)
      //   {
      //      RegCreateKeyEx(hCompanyKey,m_pszProfileName,0,REG_NONE,
      //         REG_OPTION_NON_VOLATILE,KEY_WRITE | KEY_READ,nullptr,
      //         &hAppKey,&dw);
      //   }
      //}
      //if(hSoftKey != nullptr)
      //   RegCloseKey(hSoftKey);
      //if(hCompanyKey != nullptr)
      //   RegCloseKey(hCompanyKey);

//      return hAppKey;
      return nullptr;
   }

   // returns key for:
   //      HKEY_CURRENT_USER\"Software"\RegistryKey\AppName\pszSection

   // creating it if it doesn't exist.
   // responsibility of the caller to call RegCloseKey() on the returned HKEY
   HKEY user2::GetSectionKey(const char* pszSection)

   {
      ASSERT(pszSection != nullptr);


      HKEY hSectionKey = nullptr;
      HKEY hAppKey = GetAppRegistryKey();
      if (hAppKey == nullptr)
         return nullptr;

      DWORD dw;
      RegCreateKeyExW(hAppKey, wstring(pszSection), 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE | KEY_READ, nullptr, &hSectionKey, &dw);

      RegCloseKey(hAppKey);
      return hSectionKey;
   }

#endif

   /*   UINT user2::GetProfileInt(const char * pszSection, const char * pszEntry,

   i32 nDefault)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr) // use registry
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return nDefault;
   u32 dwValue;
   u32 dwType;
   u32 dwCount = sizeof(u32);
   LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)pszEntry, nullptr, &dwType,

   (byte *)&dwValue, &dwCount);
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_DWORD);
   ASSERT(dwCount == sizeof(dwValue));
   return (UINT)dwValue;
   }
   return nDefault;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);
   return ::GetPrivateProfileInt(pszSection, pszEntry, nDefault,

   m_pszProfileName);
   }
   }

   string user2::GetProfileString(const char * pszSection, const char * pszEntry,

   const char * pszDefault)

   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return pszDefault;

   string strValue;
   u32 dwType=REG_NONE;
   u32 dwCount=0;
   LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)pszEntry, nullptr, &dwType,

   nullptr, &dwCount);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   lResult = RegQueryValueEx(hSecKey, (LPTSTR)pszEntry, nullptr, &dwType,

   (byte *)strValue.GetBuffer(dwCount/sizeof(char)), &dwCount);
   strValue.ReleaseBuffer();
   }
   RegCloseKey(hSecKey);
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_SZ);
   return strValue;
   }
   return pszDefault;

   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   if (pszDefault == nullptr)

   pszDefault = "";   // don't pass in nullptr

   char szT[4096];
   u32 dw = ::GetPrivateProfileString(pszSection, pszEntry,

   pszDefault, szT, _countof(szT), m_pszProfileName);

   ASSERT(dw < 4095);
   return szT;
   }
   }

   bool user2::GetProfileBinary(const char * pszSection, const char * pszEntry,

   BYTE** ppData, UINT* pBytes)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   ASSERT(ppData != nullptr);
   ASSERT(pBytes != nullptr);
   *ppData = nullptr;
   *pBytes = 0;
   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   {
   return FALSE;
   }

   // ensure destruction

   // linux ::aura::CRegKey rkSecKey(hSecKey);

   u32 dwType=0;
   u32 dwCount=0;
   LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)pszEntry, nullptr, &dwType, nullptr, &dwCount);

   *pBytes = dwCount;
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   *ppData = new BYTE[*pBytes];
   lResult = RegQueryValueEx(hSecKey, (LPTSTR)pszEntry, nullptr, &dwType,

   *ppData, &dwCount);
   }
   if (lResult == ERROR_SUCCESS)
   {
   ASSERT(dwType == REG_BINARY);
   return TRUE;
   }
   else
   {
   delete [] *ppData;
   *ppData = nullptr;
   }
   return FALSE;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   string str = GetProfileString(pszSection, pszEntry, nullptr);

   if (str.is_empty())
   return FALSE;
   ASSERT(str.get_length()%2 == 0);
   iptr nLen = str.get_length();
   *pBytes = UINT(nLen)/2;
   *ppData = new BYTE[*pBytes];
   for (i32 i=0;i<nLen;i+=2)
   {
   (*ppData)[i/2] = (BYTE)
   (((str[i+1] - 'A') << 4) + (str[i] - 'A'));
   }
   return TRUE;
   }
   }


   bool user2::WriteProfileInt(const char * pszSection, const char * pszEntry,

   i32 nValue)
   {
   ASSERT(pszSection != nullptr);

   ASSERT(pszEntry != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   LONG lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_DWORD,

   (byte *)&nValue, sizeof(nValue));
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);

   char szT[16];
   _stprintf_s(szT, _countof(szT), "%d", nValue);
   return ::WritePrivateProfileString(pszSection, pszEntry, szT,

   m_pszProfileName);
   }
   }

   bool user2::WriteProfileString(const char * pszSection, const char * pszEntry,

   const char * pszValue)

   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   LONG lResult;
   if (pszEntry == nullptr) //delete whole department

   {
   HKEY hAppKey = GetAppRegistryKey();
   if (hAppKey == nullptr)
   return FALSE;
   lResult = ::RegDeleteKey(hAppKey, pszSection);

   RegCloseKey(hAppKey);
   }
   else if (pszValue == nullptr)

   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   // necessary to cast away const below
   lResult = ::RegDeleteValue(hSecKey, (LPTSTR)pszEntry);

   RegCloseKey(hSecKey);
   }
   else
   {
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_SZ,

   (byte *)pszValue, (lstrlen(pszValue)+1)*sizeof(char));

   RegCloseKey(hSecKey);
   }
   return lResult == ERROR_SUCCESS;
   }
   else
   {
   ASSERT(m_pszProfileName != nullptr);
   ASSERT(lstrlen(m_pszProfileName) < 4095); // can't read in bigger
   return ::WritePrivateProfileString(pszSection, pszEntry, pszValue,

   m_pszProfileName);
   }
   }

   bool user2::WriteProfileBinary(const char * pszSection, const char * pszEntry,

   byte * pData, UINT nBytes)
   {
   ASSERT(pszSection != nullptr);

   if (m_pszRegistryKey != nullptr)
   {
   LONG lResult;
   HKEY hSecKey = GetSectionKey(pszSection);

   if (hSecKey == nullptr)
   return FALSE;
   lResult = RegSetValueEx(hSecKey, pszEntry, nullptr, REG_BINARY,

   pData, nBytes);
   RegCloseKey(hSecKey);
   return lResult == ERROR_SUCCESS;
   }

   // convert to string and write out
   LPTSTR psz = new char[nBytes*2+1];

   UINT i;
   for (i = 0; i < nBytes; i++)
   {
   psz[i*2] = (char)((pData[i] & 0x0F) + 'A'); //low nibble

   psz[i*2+1] = (char)(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble

   }
   psz[i*2] = 0;


   ASSERT(m_pszProfileName != nullptr);

   bool bResult = WriteProfileString(pszSection, pszEntry, psz);

   delete[] psz;

   return bResult;
   }

   #include "framework.h"*/




   /*   property_set & user2::propset(object * pobject)
   {
   single_lock sl(&m_mapObjectSet, TRUE);
   return m_mapObjectSet[pobject];
   }

   property_set * user2::existing_propset(object * pobject)
   {
   single_lock sl(&m_mapObjectSet, TRUE);
   auto point = m_mapObjectSet.plookup(pobject);
   if(point == nullptr)
   return nullptr;
   return &point->m_value;
   }*/



   bool user2::does_launch_window_on_startup()
   {

      return true;

   }


   bool user2::activate_app()
   {

      if (m_puiMain1 != nullptr)
      {

         m_puiMain1->m_puiThis->display(SW_SHOWNORMAL);

      }

      return true;

   }


   //void user2::term()
   //{


   //   try
   //   {

   //      if (m_puiMain1 == nullptr)
   //      {

   //         return;

   //      }

   //      // hide the user2's windows before closing all the documents
   //      m_puiMain1->m_puiThis->display(display_none);
   //      // trans    m_puiMain->ShowOwnedPopups(FALSE);


   //      m_puiMain1->m_puiThis->order(zorder_bottom);
   //      //m_puiMain->m_puiThis->m_bZ = true;
   //      // put the window at the bottom of zorder, so it isn't activated
   //      // m_puiMain->m_puiThis->zorder();

   //      //m_puiMain->m_puiThis->wait_redraw();

   //      m_puiMain1->m_puiThis->display(display_none);


   //   }
   //   catch (...)
   //   {
   //   }

   //   try
   //   {

   //      ::aura::user2::term();

   //   }
   //   catch (...)
   //   {

   //      m_result.add(error_failed);

   //   }

   //}


   ::user::interaction* user2::get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate)
   {

      ::user::interaction* puiParent = nullptr;

      if (puiParent == nullptr)
      {
         puiParent = dynamic_cast <::user::interaction*> (pcreate->m_puserinteractionParent);
      }

      //      if (puiParent == nullptr && pcreate->m_papplicationbias.is_set())
      //      {
      //         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_papplicationbias->m_puserinteractionParent);
      //      }

            //if(puiParent == nullptr && m_psession != nullptr && m_psession->m_psession != nullptr && !pcreate->m_bClientOnly
            /*if (puiParent == nullptr && m_psession != nullptr && m_psession != nullptr
                  && !pcreate->m_bOuterPopupAlertLike && m_psession != dynamic_cast < session * > (this))
            {
               puiParent = Session.get_request_parent_ui(pinteraction, pcreate);
            }*/

      return puiParent;

   }







   void user2::_001OnFileNew(::message::message* pmessage)
   {

      var varFile;

      var varQuery;

      varQuery["command"] = "new_file";

      request_file(varFile, varQuery);

      pmessage->m_bRet = true;

   }



   //   bool user2::on_open_document_file(var varFile)
   //   {
   //
   //      return _001OpenDocumentFile(varFile);
   //
   //   }

   ::user::document* user2::_001OpenDocumentFile(var varFile)
   {

      request_file(varFile);

      return varFile["document"].cast < ::user::document >();

   }


   //bool user2::_001OnDDECommand(const char* pcsz)

   //{
   //   ::exception::throw_not_implemented();
   //   //return m_pimpl->_001OnDDECommand(pcsz);


   //   return false;
   //}

   //   ::aura::file_system & user2::file_system()
   // {
   //  return m_spfilesystem;
   //}







   ::user::interaction * user2::get_desktop_window()
   {
#if defined(_UWP) || defined(APPLEOS)
      __throw(todo());
      /*#elif defined(LINUX)

      //      sync_lock sl(&user_mutex());

      xdisplay pdisplay.
      pdisplay.open(nullptr) = x11_get_display();

      oswindow window(pdisplay, DefaultRootWindow(pdisplay));

      XCloseDisplay(pdisplay);

      return window_from_os_data(window);
      */
#else

      return System.ui_from_handle(::get_desktop_window());

#endif

   }





   //void user2::assert_valid() const
   //{
   //   thread::assert_valid();


   //   if (::get_thread() != (thread*)this)
   //      return;     // only do subset if called from different thread

   //   ASSERT(::get_thread() == this);
   //   //ASSERT(afxCurrentInstanceHandle == m_hInstance);

   //   /*      if (m_pdocmanager != nullptr)
   //   ASSERT_VALID(m_pdocmanager);*/
   //}

//   void user2::dump(dump_context& dumpcontext) const
//   {
//
//      ::aura::user2::dump(dumpcontext);
//
//      dumpcontext << "\nm_bHelpMode = " << m_bHelpMode;
//      dumpcontext << "\nm_pszHelpFilePath = " << m_strHelpFilePath;
//      dumpcontext << "\nm_pszProfileName = " << m_strProfileName;
//
//#ifdef WINDOWS
//      dumpcontext << "\nm_hDevMode = " << (void*)m_hDevMode;
//      dumpcontext << "\nm_hDevNames = " << (void*)m_hDevNames;
//#endif
//
//      dumpcontext << "\nm_dwPromptContext = " << (UINT)m_dwPromptContext;
//      //      dumpcontext << "\nm_eHelpType = " << m_eHelpType;
//
//
//      /*      if (m_pdocmanager != nullptr)
//      document_manager()->dump(dumpcontext);*/
//
//      dumpcontext << "\nm_nWaitCursorCount = " << m_iWaitCursorCount;
//      dumpcontext << "\nm_nNumPreviewPages = " << m_nNumPreviewPages;
//
//      dumpcontext << "\n";
//   }


   //void user2::install_message_routing(::channel* pchannel)
   //{

   //   aura::user2::install_message_routing(pchannel);

   //   connect_command("switch_context_theme", &user2::_001OnSwitchContextTheme);

   //}


   bool user2::base_support()
   {

      //if(!user2::base_support())
      // return false;

      if (m_strBaseSupportId.is_empty())
      {

         property_set propertyset;

         dialog_box("err\\developer\\base_support\\support_id_not_specified.xml", propertyset);

         return false;

      }

      return true;
   }


   //string user2::sync_message_box(const string & pszMatter, property_set & propertyset)
   //{
   //
   //   UNREFERENCED_PARAMETER(propertyset);
   //
   //   UNREFERENCED_PARAMETER(pszMatter);
   //
   //   return "";

   //}


   //::estatus user2::bergedge_start()
   //{

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.get_length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return true;

   //}


#ifdef WINDOWS_DESKTOP


   bool Is_Vista_or_Later()
   {
      OSVERSIONINFOEX osvi;
      DWORDLONG dwlConditionMask = 0;
      byte op = VER_GREATER_EQUAL;

      // Initialize the OSVERSIONINFOEX structure.

      ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
      osvi.dwMajorVersion = 6;
      //   osvi.dwMinorVersion = 1;
      //   osvi.wServicePackMajor = 0;
      //   osvi.wServicePackMinor = 0;

      // Initialize the condition mask.

      VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, op);
      //VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
      //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMINOR, op );

      // Perform the test.

      return VerifyVersionInfo(
         &osvi,
         VER_MAJORVERSION | VER_MINORVERSION |
         VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
         dwlConditionMask) != FALSE;
   }


#endif


   //::estatus user2::init()
   //{

   //   if (!::aura::user2::init())
   //   {

   //      return false;

   //   }

   //   xxdebug_box("::aura::user2::initialize ok", "::aura::user2::initialize ok", MB_ICONINFORMATION);

   //   xxdebug_box("m_pcalculator::initialize ok", "m_pcalculator::initialize ok", MB_ICONINFORMATION);

   //   xxdebug_box("m_pcolorertake5::initialize ok", "m_pcolorertake5::initialize ok", MB_ICONINFORMATION);

   //   m_tickHeartBeat.Now();

   //   if (!initialize_userex())
   //   {

   //      return false;

   //   }

   //   xxdebug_box("m_pfilemanager::initialize ok", "m_pfilemanager::initialize ok", MB_ICONINFORMATION);

   //   xxdebug_box("m_pusermail::initialize ok", "m_pusermail::initialize ok", MB_ICONINFORMATION);
   //   m_tickHeartBeat.Now();

   //   xxdebug_box("register_bergedge_application ok", "register_bergedge_application ok", MB_ICONINFORMATION);
   //   m_tickHeartBeat.Now();

   //   ensure_app_interest();

   //   xxdebug_box("ensure_app_interest ok", "ensure_app_interest ok", MB_ICONINFORMATION);


   //   INFO(".2");

   //   if (!is_session() && !is_system())
   //   {

   //      if (command() && has_property("install"))
   //      {

   //         if (is_user_service())
   //         {

   //            //               if (Session.account()->m_puser != nullptr && Session.account()->m_puser->m_strLogin == "system")
   //            //               {
   //            //
   //            //                  Session.account()->m_puser = nullptr;
   //            //
   //            //               }
   //            //
   //            //               if (!m_strAppId.begins_ci("app-core/netnode") && m_strAppId != "app-core/mydns")
   //            //               {
   //            //
   //            //                  ApplicationUser;
   //            //
   //            //               }

   //         }

   //      }
   //      else
   //      {

   //         //Session.keyboard();

   //      }

   //      ERR("1.1");

   //      index i = applicationmenu().get_count();

   //      applicationmenu().add_item(i++, _("Transparent Frame"), "transparent_frame");

   //      application_menu_update();

   //   }

   //   INFO("success");

   //   return true;

   //}


   void user2::pre_translate_message(::message::message* pmessage)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (pbase->m_id == WM_USER + 124 && pbase->m_puserinteraction == nullptr)
      {

         /*

         OnMachineEvent((flags < machine_event::e_flag> *) pmsg->lParam);
         delete (flags < machine_event::e_flag> *) pmsg->lParam;

         */

         pbase->m_bRet = true;

         return;

      }

      return thread::pre_translate_message(pmessage);

   }


   void user2::on_create_split_view(::user::split_view* psplit)
   {

   }


   void user2::EnableShellOpen()
   {

      ASSERT(m_atomApp == 0 && m_atomSystemTopic == 0); // do once

      if (m_atomApp != 0 || m_atomSystemTopic != 0)
      {

         return;

      }

      // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
      // i16 file name so we need to use the i16 file name.
      string strShortName;

      strShortName = Context.file().module();

      // strip out path
      //string strFileName = ::PathFindFileName(strShortName);
      // strip out extension
      //LPTSTR pszFileName = strFileName.GetBuffer();
      //::PathRemoveExtension(pszFileName);
      //strFileName.ReleaseBuffer();

      //      m_atomApp = ::GlobalAddAtom(strFileName);
      //    m_atomSystemTopic = ::GlobalAddAtom("system");

   }


   __pointer(::user::interaction) user2::uie_from_point(const ::point& point)
   {

      user::interaction_pointer_array wnda = *m_puiptraFrame;

      user::oswindow_array oswindowa;

      oswindowa = wnda.get_hwnda();

      user::window_util::SortByZOrder(oswindowa);

      for (i32 i = 0; i < oswindowa.get_count(); i++)
      {

         __pointer(::user::interaction) puieWindow = wnda.find_first(oswindowa[i]);

         __pointer(::user::interaction) puie = puieWindow->_001FromPoint(point);

         if (puie != nullptr)
         {

            return puie;

         }

      }

      return nullptr;

   }


   //bool user2::on_install()
   //{

   //   if (!::aura::user2::on_install())
   //   {

   //      return false;

   //   }

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.get_length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return true;

   //}


   bool user2::on_run_install()
   {

      if (m_strId == "session" || m_strAppName == "session")
      {

         if (is_false("session_start"))
         {

            ::multithreading::set_finish(&System);

         }

      }
      else
      {

         ::multithreading::set_finish(&System);

      }

      return true;

   }


   //bool user2::on_uninstall()
   //{

   //   bool bOk = ::aura::user2::on_uninstall();

   //   string strId = m_strId;

   //   char chFirst = '\0';

   //   if (strId.get_length() > 0)
   //   {

   //      chFirst = strId[0];

   //   }

   //   return bOk;

   //}


   bool user2::on_run_uninstall()
   {

      if (m_strId == "session")
      {

         if (is_false("session_start"))
         {

            ::multithreading::set_finish(&System);

         }

      }
      else
      {

         ::multithreading::set_finish(&System);

      }

      return true;

   }


   void user2::on_application_signal(::message::message* pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   //::aura::printer* user2::get_printer(const char* pszDeviceName)
   //{

   //   return nullptr;

   //}


   //bool user2::set_keyboard_layout(const char* pszPath, const ::action_context& context)
   //{

   //   return Session.keyboard().load_layout(pszPath, context);

   //}


   i32 user2::track_popup_menu(const char* pszMatter, const ::point& point, __pointer(::user::interaction) puie)
   {

      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(puie);

      return 1;

   }


   bool user2::get_fs_size(string& strSize, const char* pszPath, bool& bPending)
   {

      i64 i64Size;

      if (!get_fs_size(i64Size, pszPath, bPending))
      {

         strSize.Empty();

         return false;

      }

      if (i64Size > 1024 * 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);

         strSize.Format("%0.2f GB", d);

      }
      else if (i64Size > 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0);

         strSize.Format("%0.1f MB", d);

      }
      else if (i64Size > 1024)
      {

         double d = (double)i64Size / (1024.0);

         strSize.Format("%0.0f KB", d);

      }
      else if (i64Size > 0)
      {

         strSize.Format("1 KB");

      }
      else
      {

         strSize.Format("0 KB");

      }

      if (bPending)
      {

         strSize = "~" + strSize;

      }

      return true;

   }


   bool user2::get_fs_size(i64& i64Size, const char* pszPath, bool& bPending)
   {
      return false;
      //db_server * pcentral = dynamic_cast <db_server *> (&System.m_psimpledb->db());

      //if (pcentral == nullptr)
      //{

      //   return false;

      //}

      //return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);

   }


   void user2::set_title(const char* pszTitle)
   {

      Session.set_app_title(m_strAppName, pszTitle);

   }


   bool user2::_001CloseApplicationByUser(__pointer(::user::interaction) pwndExcept)
   {

      // Closing just this user2.
      // It is different of a system exit.
      // System (a single ca2 process) can host
      // multiple ca2 user2 objects.

      // attempt to save all documents
      if (!save_all_modified())
      {

         return false;     // don't close it

      }

      // hide the user2's windows before closing all the documents
      HideApplication();

      close(::aura::end_app);

      return true;

   }


   oswindow user2::get_ca2_app_wnd(const char* psz)
   {

      UNREFERENCED_PARAMETER(psz);

      return nullptr;

   }


   i32 user2::send_simple_command(const char* psz, void* osdataSender)
   {
      string strApp;
      string_array stra;
      stra.add_tokens(psz, "::", true);
      if (stra.get_size() > 0)
      {
         strApp = stra[0];
         oswindow oswindow = get_ca2_app_wnd(strApp);
         if (oswindow != nullptr)
         {
            return send_simple_command((void*)oswindow, psz, osdataSender);
         }
      }
      return -1;
   }


   i32 user2::send_simple_command(void* osdata, const char* psz, void* osdataSender)
   {
#ifdef WINDOWS_DESKTOP
      ::oswindow oswindow = (::oswindow) osdata;
      if (!::IsWindow(oswindow))
         return -1;
      COPYDATASTRUCT cds;
      __memset(&cds, 0, sizeof(cds));
      cds.dwData = 888888;
      cds.cbData = (u32)strlen(psz);
      cds.lpData = (PVOID)psz;

      return (i32)SendMessage(oswindow, WM_COPYDATA, (WPARAM)osdataSender, (LPARAM)&cds);
#else
      __throw(todo());
#endif
   }


   void user2::ensure_app_interest()
   {

#ifndef _UWP

      for (i32 i = 0; i < m_straAppInterest.get_count(); i++)
      {
         if (m_straAppInterest[i] != m_strAppName && !::is_window(m_mapAppInterest[m_straAppInterest[i]]))
         {
            System.assert_running_local(m_straAppInterest[i]);
         }
      }

#else

      //__throw(todo());

#endif

   }




   //::aura::user2 * user2::get_context_system()
   //{

   //   return ::object::get_context_system();

   //}


















   /*
   __pointer(::aura::user2) user2::assert_running(const char * pszAppId)
   {


   __pointer(::aura::user2) papp = nullptr;


   try
   {

   bool bFound = false;

   for(i32 i  = 0; i < System.m_appptra.get_count(); i++)
   {
   try
   {

   papp = System.m_appptra(i);

   if(papp->m_strAppName == pszAppId)
   {
   bFound = true;
   break;
   }

   }
   catch(...)
   {
   }

   }

   bool bCreate = !bFound;

   if(bFound)
   {

   bool bRunning = false;

   try
   {
   if(papp->is_running())
   {
   bRunning = true;
   }
   }
   catch(...)
   {
   }


   if(bCreate)
   {

   __pointer(::create) spcreate(e_create);

   papp = Session.start_application("user2", pszAppId, spcreate);

   }

   }
   catch(const ::exit_exception & e)
   {

   __throw(e);

   }
   catch(const ::exception_pointer pe)
   {

   if(!Application.on_run_exception((::exception::exception &) e))
   __throw(exit_exception());

   }
   catch(...)
   {

   papp = nullptr;

   }


   return papp;

   }
   */





   //typedef  void (* PFN_factory_exchange)();














   //__pointer(::aura::user2) user2::create_application(const char * pszType,const char * pszId,bool bSynch,application_bias * pbias)
   //{

   //   __pointer(::aura::user2) pbaseapp = instantiate_application(pszType,pszId,pbias);

   //   if(pbaseapp == nullptr)
   //      return nullptr;

   //   ::aura::user2 * papp = (pbaseapp);

   //   if(!papp->start_application(bSynch,pbias))
   //   {
   //      try
   //      {
   //         pbaseapp.release();
   //      }
   //      catch(...)
   //      {
   //      }
   //      return nullptr;
   //   }


   //   return pbaseapp;

   //}




   //::user::document* user2::place_hold(::user::interaction* pinteraction)
   //{

   //   return nullptr;

   //}



   //::estatus user2::add_library(::aura::library * plibrary)
   //{

   //   plibrary->set_context_object(this);

   //   System.add_library(plibrary);

   //   return true;

   //}


   void user2::data_on_after_change(::message::message* pmessage)
   {

      SCAST_PTR(::database::change_event, pchange, pmessage);

      if (pchange->m_datakey.m_strDataKey == "ca2.savings")
      {

         Session.savings().m_eresourceflagsShouldSave = (::aura::e_resource) pchange->data_get().i32();

      }

   }


   i32 user2::GetVisibleTopLevelFrameCountExcept(__pointer(::user::interaction) pwndExcept)
   {

      ::user::interaction_pointer_array wnda = *m_puiptraFrame;

      i32 iCount = 0;
      for (i32 i = 0; i < wnda.get_size(); i++)
      {
         __pointer(::user::interaction) pwnd = wnda.element_at(i);
         __pointer(simple_frame_window) pframewindow = pwnd;
         bool bDefaultNotifyIcon = (pframewindow.is_set() && pframewindow->m_bDefaultNotifyIcon);
         if (pwnd != nullptr &&
            pwnd != pwndExcept &&
            pwnd->is_window() &&
            (pwnd->is_window_visible() || bDefaultNotifyIcon) &&
            pwnd->get_window_type() == ::user::interaction::type_frame &&
            !(pwnd->GetStyle() & WS_CHILD))
         {
            iCount++;
         }
      }
      return iCount;
   }


   i32 user2::GetVisibleFrameCount()
   {

      ::user::interaction_pointer_array wnda = *m_puiptraFrame;

      i32 iCount = 0;
      for (i32 i = 0; i < wnda.get_size(); i++)
      {
         __pointer(::user::interaction) pwnd = wnda.element_at(i);
         if (pwnd != nullptr
            && pwnd->is_window()
            && pwnd->is_window_visible())
         {
            iCount++;
         }
      }
      return iCount;
   }


   //void user2::on_create_keyboard()
   //{

   //   string str;

   //   // keyboard on_layout
   //   //if(data_get("keyboard_layout",str) && str.has_char())
   //   {
   //      // Session.set_keyboard_layout(str,::source_database);
   //   }
   //   //else
   //   {
   //      set_keyboard_layout(nullptr, ::source_database);
   //   }

   //}


   //::type user2::user_default_controltype_to_typeinfo(enum user::e_control_type econtroltype)
   //{

   //   return Sess(this).userex()->controltype_to_typeinfo(econtroltype);

   //}


   //bool user2::platform_open_by_file_extension(int iEdge, const char * pszPathName, application_bias * papplicationbias)
   //{

   //   return System.get_platform(iEdge)->open_by_file_extension(pszPathName, papplicationbias);
   //}

   //bool user2::platform_open_by_file_extension(int iEdge, ::create * pcc)
   //{

   //   return System.get_platform(iEdge)->open_by_file_extension(pcc);
   //}


   __pointer(::aura::user2) user2::create_platform(::aura::session* psession)
   {

      return __new(::aura::session);

   }


   void user2::on_change_cur_sel(::user::tab* ptab)
   {



   }


   bool user2::_001OnAgreeExit()
   {

      if (!save_all_modified())
      {

         return false;

      }

      return true;

   }


   //void user2::_001OnFranceExit()
   //{

   //   ::aura::user2::_001OnFranceExit();

   //}


   void user2::prepare_form(id id, ::form_document* pdocument)
   {



   }


   void user2::report_error(::exception::exception* pexception, int iMessageFlags, const char* pszTopic)
   {

      string strMessage;

      strMessage += pszTopic;

      strMessage += " : ";

      strMessage += pexception->get_message();

      m_puiMain1->message_box(strMessage + ::enum_message_box(iMessageFlags));

   }


   bool user2::on_close_frame_window(::user::frame* pframe)
   {

      if (pframe->m_bCloseApplicationIfLastVisibleFrame)
      {
         if (GetVisibleTopLevelFrameCountExcept(pframe) <= 0)
         {

            _001CloseApplication();

         }
         else
         {

            pframe->hide();

         }
      }
      else
      {

         pframe->DestroyWindow();

      }

      return true;

   }


   ::type user2::control_type_from_id(const ::id& id, ::user::e_control_type& econtroltype)
   {

      string str(id);

      if (str.begins_ci("combo_"))
      {

         econtroltype = ::user::control_type_combo_box;

         return __type(::user::combo_box);

      }
      else if (str.begins_ci("check_") || str.begins_ci("checkbox_"))
      {

         econtroltype = ::user::control_type_check_box;

         return __type(::user::check_box);

      }
      else if (str.begins_ci("still_"))
      {

         econtroltype = ::user::control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("label_"))
      {

         econtroltype = ::user::control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("edit_"))
      {

         econtroltype = ::user::control_type_edit_plain_text;

         return __type(::user::plain_edit);

      }
      else if (str.begins_ci("button_"))
      {

         econtroltype = ::user::control_type_button;

         return __type(::user::button);

      }

      return ::aura::user2::control_type_from_id(id, econtroltype);

   }


   string user2::get_theme()
   {

      if (!m_ptheme)
      {

         return ::aura::user2::get_theme();

      }

      return m_ptheme->get_theme();

   }


   estatus user2::initialize_contextualized_theme()
   {

      auto estatus = __compose_new(m_ptheme);

      if (!estatus)
      {

         return estatus;

      }

      if (m_bContextTheme)
      {

         estatus = m_ptheme->initialize_contextualized_theme();

         if (!estatus)
         {

            return estatus;

         }

      }

      return estatus;

   }


   //void user2::on_change_theme()
   //{


   //}


   void user2::_001OnSwitchContextTheme(::message::message* pmessage)
   {

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

      if (!m_ptheme)
      {

         return;

      }

      if (m_bContextTheme)
      {

         m_ptheme->switch_context_theme();

      }

   }


   //user2::user2()
   //{

   //   create_factory < ::user::user >();

   //   //m_bBaseProcessInitialize         = false;
   //   //m_bBaseProcessInitializeResult   = false;

   //   //m_bBaseInitialize1               = false;
   //   //m_bBaseInitialize1Result         = false;

   //   //m_bBaseInitialize                = false;
   //   //m_bBaseInitializeResult          = false;

   //   //m_bBaseInitializeInstance        = false;
   //   //m_bBaseInitializeInstanceResult  = false;




   //}

   //user2::~user2()
   //{

   //}


   //::estatus user2::initialize(::object* pobjectContext)
   //{

   //   auto estatus = ::aura::user2::initialize(pobjectContext);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}

   //   void user2::install_message_routing(::channel * pchannel)
   //   {
   //
   //
   //
   //   }


      //void user2::update(::update * pupdate)
      //{

      //   ::aura::user2::update(pupdate);

      //   if (pupdate->m_bRet)
      //   {
      //
      //      return;

      //   }
      //
      //   ::user::form_callback::update(pupdate);

      //   if (pupdate->m_bRet)
      //   {

      //      return;

      //   }

      //}


   //::estatus user2::process_init()
   //{

   //   if (::aura::user2::process_init())
   //   {

   //      return true;

   //   }

   //   return true;

   //}


   //::estatus user2::init_instance()
   //{

   //   if (!::aura::user2::init_instance())
   //   {

   //      return false;

   //   }

   //   auto estatus = create_impact_system();

   //   if (failed(estatus))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   ::estatus     user2::create_impact_system()
   {

      return ::success;

   }


   void user2::process_message_filter(i32 code, ::message::message* pmessage)
   {

      if (pmessage == nullptr)
         return;   // not handled

      SCAST_PTR(::message::base, pbase, pmessage);

      __pointer(::user::frame_window) pTopFrameWnd;
      //::user::interaction * pMainWnd;
      ::user::interaction* pMsgWnd;
      switch (code)
      {
         //case MSGF_DDEMGR:
         // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
         //  never call the next hook.
         // By returning FALSE, the message will be dispatched
         //  instead (the default behavior).
         //return;

      case MSGF_MENU:

         pMsgWnd = dynamic_cast <::user::interaction*> (pbase->m_puserinteraction);

         if (pMsgWnd != nullptr)
         {
            pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
            if (pTopFrameWnd != nullptr && pTopFrameWnd->IsTracking() &&
               pTopFrameWnd->m_bHelpMode)
            {
               //pMainWnd = __get_main_window();
               //if((m_puiMain != nullptr) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
               //{
               //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
               //   pbase->m_bRet = true;
               //   return;
               //}
            }
         }
         // fall through...

      case MSGF_DIALOGBOX:    // handles message boxes as well.
         //pMainWnd = __get_main_window();
         if (code == MSGF_DIALOGBOX && m_puiActive != nullptr &&
            pbase->m_id >= WM_KEYFIRST && pbase->m_id <= WM_KEYLAST)
         {
         }
         break;
      }
      // default to not handled

   }





















   /*string user2::get_cred(const string & strRequestUrlParam,const ::rect & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      string str = ::account::get_cred(this,strUsername,strPassword,strToken);

      if(str == "ok" && strUsername.has_char() && strPassword.has_char())
         return "ok";

      if(!bInteractive)
         return "failed";

      __pointer(::account::simple_ui) pinteraction;

      string strRequestUrl(strRequestUrlParam);

      if(strRequestUrl.is_empty())
      {

         string strIgnitionServer = file_as_string(::dir::system() / "config\\system\\ignition_server.txt");

         if(::str::ends_ci(strIgnitionServer,".ca2.cc"))
         {

            strRequestUrl = "https://" + strIgnitionServer + "/";

         }
         else
         {

            strRequestUrl = "https://account.ca2.cc/";

         }

         strRequestUrl = "https://account.ca2.cc/";

      }

      pinteraction = __new(::account::simple_ui(this,strRequestUrl));

      pinteraction->m_login.m_peditUser->set_window_text(strUsername);

      pinteraction->m_login.m_ppassword->set_window_text("");

      string strResult = pinteraction->get_cred(rect,strUsername,strPassword,strToken,strTitle);

      pinteraction->DestroyWindow();

      ::account::set_cred(this,strToken,strUsername,strPassword);

      return strResult;

   }*/


   //__pointer(::user::user) user2::create_user()
   //{

   //   return __new(::user::user);

   //}


   bool user2::on_thread_on_idle(::thread* pthread, LONG lCount)
   {

      if (lCount <= 0)
      {

         __pointer(::user::interaction) pinteraction;

         while (get_frame(pinteraction))
         {
            //::user::interaction * pinteraction = (::user::interaction *) pimpl->m_spuiptra->element_at(i)->m_pvoidUserInteraction;
            bool bOk = false;
            try
            {

               bOk = pinteraction != nullptr && pinteraction->is_window_visible();
            }
            catch (...)
            {
            }
            if (!bOk)
            {
               //   try
               //   {
               //      Application.remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      Session.remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
               //   try
               //   {
               //      System.remove_frame(pinteraction);
               //   }
               //   catch(...)
               //   {
               //   }
            }
            else
            {
               //               sl.unlock();
               try
               {
                  pinteraction->send_message(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);
               }
               catch (...)
               {

               }
               //             sl.lock();
            }
         }


      }
      else if (lCount >= 0)
      {
      }

      return lCount < 0;  // nothing more to do if lCount >= 0

   }





   void user2::on_create_impact(::user::impact_data* pimpactdata)
   {


   }


   bool user2::process_message()
   {

      return ::thread::process_message();

   }


   //void user2::SetCurrentHandles()
   //{

   //   ::aura::user2::SetCurrentHandles();

   //}


   //void user2::term_application()
   //{

   //   try
   //   {

   //      aura::user2::term_application();

   //   }
   //   catch (...)
   //   {

   //   }

   //}


   ::draw2d::icon* user2::set_icon(object* pobject, ::draw2d::icon* picon, bool bBigIcon)
   {

      ::draw2d::icon* piconOld = get_icon(pobject, bBigIcon);

      if (bBigIcon)
      {

         pobject->value("big_icon") = (__pointer(object)) picon;

      }
      else
      {

         pobject->value("small_icon") = (__pointer(object)) picon;

      }

      return piconOld;

   }


   ::draw2d::icon* user2::get_icon(object* pobject, bool bBigIcon) const
   {

      if (bBigIcon)
      {

         return const_cast <object*> (pobject)->cast < ::draw2d::icon >("big_icon");

      }
      else
      {

         return const_cast <object*> (pobject)->cast < ::draw2d::icon >("small_icon");

      }

   }


   void user2::on_control_event(::user::control_event* pevent)
   {

      if (pevent->m_eevent == ::user::event_initialize_control)
      {

         if (pevent->m_puie->m_id == __id(system_startup_checkbox))
         {

            try
            {
               __pointer(::user::check) pcheck = pevent->m_puie;

               if (pcheck.is_set())
               {

                  pcheck->_001SetCheck(
                     Context.os().is_user_auto_start(get_executable_appid()),
                     ::source_initialize);

               }
            }
            catch (...)
            {

            }

         }

      }
      else if (pevent->m_eevent == ::user::event_set_check)
      {

         if (pevent->m_puie->m_id == __id(system_startup_checkbox)
            && pevent->m_actioncontext.is_user_source())
         {

            try
            {

               __pointer(::user::check) pcheck = pevent->m_puie;

               if (pcheck.is_set())
               {

                  Context.os().register_user_auto_start(
                     get_executable_appid(),
                     get_executable_path(),
                     pcheck->echeck() == ::check_checked);

               }

               pevent->m_bRet = true;

               return;

            }
            catch (...)
            {

            }

         }

      }

   }


   ::user::interaction* user2::create_menu_interaction()
   {

      return __new(::user::button);

   }


   //__pointer(::user::document) user2::defer_create_view(string strView, ::user::interaction* puiParent, ewindowflag ewindowflag, const ::id& id)
   //{

   //   auto pcontroller = ::aura::user2::defer_create_view(strView, puiParent, ewindowflag, id);

   //   if (pcontroller)
   //   {

   //      return pcontroller;

   //   }

   //   return nullptr;

   //}


   void user2::on_song_added(const string& str)
   {

   }


   //::type user2::control_type_from_id(const ::id& id, ::user::e_control_type& econtroltype)
   //{

   //
   //}


   //::form_property_set * user2::get_form_property_set()
   //{

   //   auto pset = ::user::form_callback::get_form_property_set();

   //   if (::is_set(pset))
   //   {

   //      return pset;

   //   }

   //   return this;

   //}

   string user2::get_visual_studio_build()
   {

      ::file::path path = dir::config() / "programming/vs_build.txt";

      string strBuild = Context.file().as_string(path);

      strBuild.trim();

      return strBuild;

   }


   string user2::sound_path(const char* psz)
   {

      string strFileName = string(psz) + string(".wav");

      string strFilePath = dir().matter(strFileName);

      return strFilePath;

   }

   
   string user2::get_default_playlist_path()
   {

      return "playlist/default";

   }


   ::type user2::get_pane_tab_view_type_info()
   {


   }



   ::type user2::get_simple_frame_window_type_info()
   {


   }


   ::type user2::get_simple_child_frame_type_info()
   {


   }


} // namespace core



