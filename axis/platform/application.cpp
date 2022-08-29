#include "framework.h"
//#include "axis/user/_user.h"
#include "aura/id.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "axis/platform/application.h"
#include "axis/platform/session.h"
#include "axis/user/user/combo_box.h"
#include "aura/user/user/button.h"
#include "aura/user/user/still.h"
#include "aura/user/user/check_box.h"
#include "system.h"


namespace axis
{


   void initialize()
   {

      ::factory::add_factory_item< ::axis::system, class ::system>();

   }


   application::application()
   {


      ::axis::initialize();

      m_paxisapplication = this;
      m_bInitializeDataCentral = true;

      ::factory::add_factory_item < ::networking_application >();

   }


   application::~application()
   {

   }


   void application::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::aura::application::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void application::assert_ok() const
   {

      thread::assert_ok();

   }


   void application::dump(dump_context & dumpcontext) const
   {

      thread::dump(dumpcontext);

//#ifdef WINDOWS
//
//      dumpcontext << "m_hinstance = " << (void *)m_hinstance;
//
//#endif

      //dumpcontext << "\nm_strCmdLine = " << m_strCmdLine;
      //dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
      dumpcontext << "\nm_bHelpMode = " << m_strAppName;

      dumpcontext << "\n";

   }


   string application::__get_text(string str)
   {

      if (!m_puserlanguagemap)
      {

         return str;

      }

      return m_puserlanguagemap->__get_text(str);

   }


   //::user::style* application::get_user_style() const
   //{

   //   if (m_psession)
   //   {

   //      return m_psession->user()->get_user_style();

   //   }

   //   return nullptr;

   //}


   //string application::dialog_box(const ::string & pszMatter, property_set & propertyset)
   //{

   //   throw_todo();

   //   return "";

   //}


   bool application::app_data_set(const ::atom & atom, stream & os)
   {

      return false;

   }


   bool application::app_data_get(const ::atom & atom, stream & is)
   {

      return false;

   }


   bool application::app_data_set(const ::atom & atom, ::object & obj)
   {

      return false;

   }


   bool application::app_data_get(const ::atom & atom, ::object & obj)
   {

      return false;

   }


//#ifdef WINDOWS_DESKTOP
//
//
//   class open_browser_enum
//   {
//   public:
//
//      string                           m_strWindowEnd;
//      string                           m_strTopic;
//      string                           m_strCounterTopic;
//      oswindow                         m_hwnd;
//      comparable_array < oswindow >    m_hwndaTopic;
//      comparable_array < oswindow >    m_hwndaCounterTopic;
//
//   };
//
//
//   int_bool CALLBACK enum_proc(HWND hwnd, LPARAM lparam)
//   {
//
//      open_browser_enum * penum = (open_browser_enum *)lparam;
//
//      string str = ::str().get_window_text_timeout(hwnd, 1000);
//
//      if (::str().ends_ci(str, penum->m_strWindowEnd))
//      {
//
//         penum->m_hwnd = hwnd;
//
//         return false;
//
//      }
//
//      return true;
//
//   }
//
//
//   int_bool CALLBACK enum_proc_ff_topic(oswindow hwnd, lparam lparam)
//   {
//
//      open_browser_enum * penum = (open_browser_enum *)lparam;
//
//      string str = ::str().get_window_text_timeout(hwnd);
//
//      if (::str().ends_ci(str, penum->m_strTopic))
//      {
//
//         penum->m_hwndaTopic.add(hwnd);
//
//      }
//
//      return true;
//
//   }
//
//   int_bool CALLBACK enum_proc_ff_counter_topic(oswindow hwnd, lparam lparam)
//
//   {
//
//      open_browser_enum * penum = (open_browser_enum *)lparam;
//
//
//      string str = ::str().get_window_text_timeout(hwnd, 1000);
//
//      if (::str().ends_ci(str, penum->m_strCounterTopic))
//      {
//
//         penum->m_hwndaCounterTopic.add(hwnd);
//
//      }
//
//      return true;
//
//   }
//
//#endif
//










   //void application::DoWaitCursor(i32 nCode) // 0 => restore, 1=> begin, -1=> end
   //{

   //   __UNREFERENCED_PARAMETER(nCode);

   //}


//   void application::show_wait_cursor(bool bShow)
//   {
//
//      if (m_pappimpl.is_null())
//         return;
//
//      m_pappimpl->show_wait_cursor(bShow);
//
//
//   }
//
//

//   string CLASS_DECL_AXIS application::get_cred(const ::string & strRequestUrl, const ::rectangle_i32 & rectangle, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive)
// {

//  throw ::not_implemented();

//}






//   void     application::main()
//   {
//
//      INFORMATION("aura::application::main");
//
//      try
//      {
//
//         m_bReady = true;
//
//         m_estatus = on_run();
//
////         if(m_iErrorCode != 0)
////         {
////
////            dappy(__type_name(this) + " : on_run failure : " + __string(m_iErrorCode));
////
////            ::output_debug_string("application::main on_run termination failure\n");
////
////         }
//
//      }
//      catch (const ::exception & e)
//      {
//
//         if (!handle_exception(e))
//         {
//
//
//         }
//
//      }
//      catch (...)
//      {
//
//         //dappy(__type_name(this) + " : on_run general exception");
//
//      }
//
//      return m_estatus;
//
//   }
//

   void application::init_instance()
   {

      //auto estatus =
      ::aura::application::init_instance();

      //if (!estatus)
      //{

      //   return estatus;

      //}



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

         if (payload("locale").get_count() > 0)
         {

            str = payload("locale").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::e_source_database);

         }
         else if (payload("lang").get_count() > 0)
         {

            str = payload("lang").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::e_source_database);

         }
         else if (data_get({ "locale", true }, str))
         {

            if (str.has_char())
            {

               set_locale(str, ::e_source_database);

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

         if (payload("schema").get_count() > 0)
         {

            str = payload("schema").stra()[0];

            data_set({ "system_schema", true }, str);

            data_set({ "schema", true }, str);

            set_schema(str, ::e_source_database);

         }
         else if (data_get({ "schema", true }, str))
         {

            if (str.has_char())
            {

               set_schema(str, ::e_source_database);

            }

         }

         //data_pulse_change({ "ca2.savings", true }, nullptr);

         auto psystem = m_psystem->m_paurasystem;

         psystem->appa_load_string_table();

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

         if (payload("locale").get_count() > 0)
         {

            str = payload("locale").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::e_source_database);

         }
         else if (payload("lang").get_count() > 0)
         {

            str = payload("lang").stra()[0];

            data_set({ "system_locale", true }, str);

            data_set({ "locale", true }, str);

            set_locale(str, ::e_source_database);

         }
         else if (data_get({ "locale", true }, str))
         {

            if (str.has_char())
            {

               set_locale(str, ::e_source_database);

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

         if (payload("schema").get_count() > 0)
         {

            str = payload("schema").stra()[0];

            data_set({ "system_schema", true }, str);

            data_set({ "schema", true }, str);

            set_schema(str, ::e_source_database);

         }
         else if (data_get({ "schema", true }, str))
         {

            if (str.has_char())
            {

               set_schema(str, ::e_source_database);

            }

         }

         // data_pulse_change({ "ca2.savings", true }, nullptr);

         psystem->appa_load_string_table();

      //return true;

   }


   void application::application_pre_run()
   {

      //auto estatus = 
      
      ::aura::application::application_pre_run();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //bool application::InitApplication()
   //{

   //   auto bOk = ::aura::application::InitApplication();

   //   if (!bOk)
   //   {

   //      return false;

   //   }

   //   return true;

   //}



   void application::os_native_bergedge_start()
   {

      return ::aura::application::os_native_bergedge_start();

   }


   void     application::run()
   {

      return ::aura::application::run();

   }














   void application::process_init()
   {

      //auto estatus = 
      
      ::aura::application::process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //string_array stra;

      //stra.explode("/", m_XstrAppId);

      //m_strRoot = stra[0];

      //m_strDomain = stra.slice(1).implode("/");

      //add_matter_locator(this);


      //if (is_system() || is_session())
      //{

      //   on_update_matter_locator();

      //}
      //else
      //{


      //}

//      if (!m_bAppHasInstallerChangedProtected)
//      {
//
//#ifdef _UWP
//
//         set_has_installer(false);
//
//#else
//
//         //if (psystem->m_pappcore == nullptr)
//         //{
//
//         //   set_has_installer(false);
//
//         //}
//         //else
//         {
//
//            set_has_installer(!psystem->has_apex_application_factory());
//
//         }
//
//#endif
//
//      }

      //auto estatus = initialize_context();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ////if (m_bAuraProcessInitialize)
      ////{

      ////   return m_bAuraProcessInitializeResult;

      ////}

      INFORMATION("axis::application::process_init");

      ::factory::add_factory_item < ::database::field_array >();
      ::factory::add_factory_item < ::database::row >();
      ::factory::add_factory_item < ::database::row_array >();

      //if (m_bAxisProcessInitialize)
      //{

      //   return m_bAxisProcessInitializeResult;

      //}

      INFORMATION("axis::application::process_init");

      //m_bAxisProcessInitialize = true;

      //m_bAxisProcessInitializeResult = false;

      if (m_psimpledb.is_null())
      {

         __construct_new(m_psimpledb);

      }

      //if (!::aura::application::process_init())
      //{

      //   FATAL("axis::application::process_init .1");

      //   return false;

      //}


      //m_bAxisProcessInitializeResult = true;

      //INFORMATION("axis::application::process_init success");

      //return true;

     /* estatus = userfs_process_init();

      if(!estatus && estatus != error_not_implemented)
      {

         ERROR(".2");

         return false;

      }*/

      INFORMATION("success");

      //return true;

   }


   void application::process_term()
   {

      ::aura::application::process_term();

      //try
      //{

      //   impl_process_term();

      //}
      //catch(...)
      //{

      //}

      //try
      //{

      //   ca_process_term();

      //}
      //catch(...)
      //{

      //}

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

            auto psystem = m_psystem->m_paurasystem;

            if (psystem != nullptr)
            {

               psystem->check_exit();

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         m_stringtable.erase_all();

         m_stringtableStd.erase_all();

      }
      catch(...)
      {

      }

      //m_spfile.release();

      //m_spdir.release();

      //::acme::del(m_pimaging);


      /// commented out the code below
      /// reasoning: better leave to the session the responsability
      /// to do those checks/actions.
//      if (!is_session() && !is_system())
//      {
//
//         try
//         {
//
//            if (psession->appptra().get_count() <= 1)
//            {
//
//               if (psystem->thread::get_os_data() != nullptr)
//               {
//
//                  ::parallelization::finish(System);
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


//   void application::init_application()
//   {
//
//      //if (m_bAuraInitializeInstance)
//      //{
//
//      //   return m_bAuraInitializeInstanceResult;
//
//      //}
//
//      INFORMATION("aura::application::init_application");
//
//      //m_bAuraInitializeInstance = true;
//
//      //m_bAuraInitializeInstanceResult = false;
//
//      m_durationHeartBeat.Now();
//
//      if (!init1())
//      {
//
//         //dappy(__type_name(this) + " : init1 failure : " + __string(m_iErrorCode));
//
//         return false;
//
//      }
//
//      psystem->install_progress_add_up(); // 2
//
//      //xxdebug_box("init1 ok", "init1 ok", e_message_box_icon_information);
//
//      m_durationHeartBeat.Now();
//
//      if (!init2())
//      {
//
//         //dappy(__type_name(this) + " : init2 failure : " + __string(m_iErrorCode));
//
//         return false;
//
//      }
//
//      psystem->install_progress_add_up(); // 3
//
//      //xxdebug_box("init2 ok", "init2 ok", e_message_box_icon_information);
//
//      m_durationHeartBeat.Now();
//
//      if (!init3())
//      {
//
//         //dappy(__type_name(this) + " : init3 failure : " + __string(m_iErrorCode));
//
//         return false;
//
//      }
//
//      psystem->install_progress_add_up(); // 4
//
//      //xxdebug_box("init3 ok", "init3 ok", e_message_box_icon_information);
//
//      m_durationHeartBeat.Now();
//
//      //dappy(__type_name(this) + " : init3 ok : " + __string(m_iErrorCode));
//
//      try
//      {
//
//         if (!init())
//         {
//
//            //dappy(__type_name(this) + " : initialize failure : " + __string(m_iErrorCode));
//
//            return false;
//
//         }
//
//      }
//      catch (const ::string & psz)
//      {
//
//         if (!strcmp(psz, "You have not logged in! Exiting!"))
//         {
//
//            return false;
//
//         }
//
//         return false;
//
//      }
//
//      psystem->install_progress_add_up(); // 5
//
////      m_bAuraInitializeInstanceResult = true;
//
//      return true;
//
//   }



   void application::init1()
   {

      //::e_status estatus = 
      
      ::aura::application::init1();

      //if (!estatus)
      //{

      //   return estatus;

      //}



      //if (psystem->payload("locale").get_count() > 0)
      //{

      //   strLocale = psystem->payload("locale").stra()[0];

      //}

      //if (psystem->payload("schema").get_count() > 0)
      //{

      //   strSchema = psystem->payload("schema").stra()[0];

      //}

      //if (papp->payload("locale").get_count() > 0)
      //{

      //   strLocale = papp->payload("locale").stra()[0];

      //}

      //if (papp->payload("schema").get_count() > 0)
      //{

      //   strSchema = papp->payload("schema").stra()[0];

      //}

      //set_locale(strLocale, ::e_source_database);

      //set_schema(strSchema, ::e_source_database);

      //if (!initialize_contextualized_theme())
      //{

      //   FATAL("Failed to initialize_contextualized_theme");

      //   return false;

      //}

      //INFORMATION("start");

      ////if (!::aura::application::init1())
      ////{

      ////   ERROR(".1");

      ////   return false;

      ////}

      ////if (!initialize1_experience())
      ////{

      ////   ERROR(".2");

      ////   return false;

      ////}

      //m_durationHeartBeat.Now();

      ////estatus = __compose(m_puserfs);

      ////if (!estatus)
      ////{

      ////   return estatus;

      ////}

      ////if (!userfs_init1())
      ////{

      ////   ERROR(".3");

      ////   return false;

      ////}



      ///*if(!m_spuser->init1())
      //return false;
      //if(!m_spuser->init2())
      //return false;*/

      if (m_bInitializeDataCentral)
      {

         if (m_strDatabaseAppId.is_empty())
         {

            m_strDatabaseAppId = m_strAppId;

         }

         ::file::path pathDatabase;

         auto pcontext = get_context();

         ::file::path pathFolder = pcontext->m_papexcontext->dir().appdata(m_strDatabaseAppId);

         if (is_system())
         {

            pathDatabase = pathFolder / "system.sqlite";

         }
         else if (is_session())
         {

            pathDatabase = pathFolder / "session.sqlite";

         }
         else
         {

            pathDatabase = pathFolder / "app.sqlite";

         }

         //throw ::exception(todo("database"));

         //auto estatus = 
         
         m_psimpledb->initialize_simpledb_server(this, pathDatabase);

         //if (!estatus)
         //{

         //   m_result.add(estatus);

         //   if(m_bDataCentralRequired)
         //   {

         //      return estatus;

         //   }

         //}
         //else
         //{

            set_data_server(m_psimpledb);

         //}

      }

      //return ::success;

   }


   void application::term1()
   {

      ::aura::application::term1();

      ////try
      ////{

      ////   impl_term1();

      ////}
      ////catch (...)
      ////{

      ////}

      //try
      //{

      //   ca_term1();

      //}
      //catch(...)
      //{

      //}

   }

   void application::init2()
   {

      //if (!impl_init2())
      //{

      //   return false;

      //}

      //if (!ca_init2())
      //{

      //   return false;

      //}



      //return true;

   }

   void application::term2()
   {

      ::aura::application::term2();
      ////try
      ////{

      ////   impl_term2();

      ////}
      ////catch (...)
      ////{

      ////}

      //try
      //{

      //   ca_term2();

      //}
      //catch(...)
      //{

      //}

   }

   void application::init3()
   {

      string strFolder = m_strAppName;

      strFolder.replace_with("_", ".");
      strFolder.replace_with("-", "::");
      strFolder.replace_with("_", ":");

      m_strRelativeFolder = strFolder;

      //if (!impl_init3())
      //{

      //   return false;

      //}

      //if (!ca_init3())
      //{

      //   return false;

      //}

      //return true;

   }


   void application::term3()
   {

      ::aura::application::term3();

      ////try
      ////{

      ////   impl_term3();

      ////}
      ////catch (...)
      ////{

      ////}

      //try
      //{

      //   ca_term3();

      //}
      //catch(...)
      //{

      //}

   }



   void application::term_application()
   {

      ::aura::application::term_application();

      //try
      //{

      //   m_spobjectUserFs.release();

      //}
      //catch (...)
      //{


      //}

      //m_puserfs = nullptr;

      //__release(m_pexperience);

      //try
      //{

      //   ::aura::application::term_application();

      //}
      //catch (...)
      //{

      //}

      release_exclusive();

      //::application_message signal(::application_message_term_instance);

      //try
      //{

      //   route_message(&signal);

      //}
      //catch (...)
      //{

      //}

      try
      {

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

            m_psimpledb->destroy();

         }
         catch (...)
         {

            //m_result.add(error_failed);

         }

      }

      m_psimpledb.release();

   }


   bool application::Ex2OnAppInstall()
   {

      return true;

   }


   bool application::Ex2OnAppUninstall()
   {

      return true;

   }



   //string application::http_get_locale_schema(const ::string & pszUrl, const ::string & pszLocale, const ::string & pszSchema)
   //{

   //   throw ::interface_only();

   //   return "";

   //}





   //void application::set_locale(const string & pcsz, const ::action_context & context)

   //{

   //   string strLocale(pcsz);


   //   strLocale.trim();

   //   m_strLocale = strLocale;

   //   on_set_locale(m_strLocale, context);

   //}


   //void application::set_schema(const string & pcsz, const ::action_context & context)

   //{

   //   string strSchema(pcsz);


   //   strSchema.trim();

   //   m_strSchema = strSchema;

   //   on_set_schema(m_strSchema, context);

   //}


   //void application::on_set_locale(const string & pcsz, const ::action_context & context)

   //{
   //   __UNREFERENCED_PARAMETER(context);
   //   __UNREFERENCED_PARAMETER(pcsz);

   //   //psystem->appa_load_string_table();
   //}


   //void application::on_set_schema(const string & pcsz, const ::action_context & context)

   //{
   //   __UNREFERENCED_PARAMETER(context);
   //   __UNREFERENCED_PARAMETER(pcsz);

   //   //psystem->appa_load_string_table();
   //}





   void application::interactive_credentials(::account::credentials * pcredentials)
   {

      __pointer(::axis::session) psession = get_session();

      psession->interactive_credentials(pcredentials);

   }


   ::account::user * application::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   {

      if(::is_null(get_session()))
      {

         return nullptr;

      }

      __pointer(::axis::session) psession = get_session();

      return psession->get_user(pathUrl, bFetch, bInteractive);

   }


   ::account::user * application::interactive_get_user(::file::path pathUrl)
   {

      return get_user(pathUrl, true, true);

   }


   ::account::user * application::noninteractive_get_user(::file::path pathUrl)
   {

      return get_user(pathUrl, true, false);

   }



   ::simpledb::server * application::simpledb()
   {

      return m_psimpledb;

   }


   ::database::server * application::dataserver()
   {

      return m_psimpledb;

   }




   void application::verb()
   {

      //return true;

   }


   void application::on_run()
   {

      //try
      //{

      //   ::application_message signal(::application_message_begin);

      //   route_message(&signal);

      //}
      //catch (...)
      //{

      //}

      install_message_routing(this);

      m_bReady = true;

      try
      {

         string strType = __type_name(this);

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

      //resume_on_exception:

         try
         {

            run();

         }
         catch (const ::exception & e)
         {

            handle_exception(e);
//            {
//
//               goto resume_on_exception;
//
//            }

            m_estatus = e.m_estatus;

         }

      }
      catch (const ::exception &)
      {

      }


      try
      {

         thread * pthread = this;

         if (pthread != nullptr && pthread->m_peventReady != nullptr)
         {

            pthread->m_peventReady->SetEvent();

         }

      }
      catch (...)
      {

         //m_result.add(error_failed);

      }

      //return m_estatus;

   }





   //void application::application_pre_run()
   //{

   //   return ::aura::application::application_pre_run();

   //}



   //bool application::InitApplication()
   //{

   //   return true;

   //}


   //bool application::do_install()
   //{


   //   if (!::aura::application::do_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::do_uninstall()
   //{

   //   bool bOk = aura::application::do_uninstall();

   //   return bOk;

   //}


   //bool application::on_install()
   //{

   //   if (!aura::application::on_install())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //bool application::on_uninstall()
   //{

   //   if (!aura::application::on_uninstall())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::os_native_bergedge_start()
   //{

   //   if (!::aura::application::os_native_bergedge_start())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //void application::on_request(::create * pcreate)
   //{

   //   aura::application::on_request(pcreate);

   //}


   //void     application::run()
   //{

   //   return ::aura::application::run();

   //}


   //__pointer(::aura::application) application::assert_running(const ::string & pszAppId)
   //{

   //   __pointer(::aura::application) papp;

   //   papp = psession->m_applicationa.find_running_defer_try_quit_damaged(pszAppId);

   //   if(papp.is_null())
   //   {

   //      __pointer(::create) spcreate(e_create);

   //      papp = psession->start_application(pszAppId,spcreate);

   //   }

   //   return papp;

   //}


   ::database::key application::calc_data_key()
   {

      return ::database::key("app://" + m_strDatabaseAppId, is_local_data());

   }




   //void application::init1()
   //{

   //   //if (m_bAxisInitialize1)
   //   //{

   //   //   return m_bAxisInitialize1Result;

   //   //}

   //   //m_bAxisInitialize1 = true;

   //   //m_bAxisInitialize1Result = false;

   //   m_durationHeartBeat.Now();

   //   if (!::aura::application::init1())
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


   //void application::init2()
   //{

   //   if (!::aura::application::init2())
   //      return false;

   //   return true;

   //}


   //void application::init3()
   //{

   //   if (!::aura::application::init3())
   //   {

   //      return false;

   //   }

   //   return true;

   //}

//


   void application::init()
   {

      //auto estatus = 
      
      ::aura::application::init();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


//

   //void application::term_application()
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

   //         aura::application::term_application();

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

   //         m_psimpledb->destroy();

   //      }
   //      catch (...)
   //      {

   //         m_result.add(error_failed);

   //      }

   //   }

   //   m_psimpledb.release();

   //}


   void application::term()
   {

      ::aura::application::term();

   }


   bool application::assert_user_logged_in()
   {

      const char * pszRequestUrl = nullptr;

      string strRequestUrl;

      if (m_psystem->m_pacmefile->as_string(m_psystem->m_pacmedirectory->system() / "config\\system\\ignition_server.txt").has_char())
      {

         strRequestUrl = "https://" + m_psystem->m_pacmefile->as_string(m_psystem->m_pacmedirectory->system() / "config\\system\\ignition_server.txt") + "/api/spaignition";

         pszRequestUrl = strRequestUrl;

      }

      if (get_session() == nullptr)
      {

         return false;

      }

      __pointer(::axis::session) psession = get_session();

      if (psession->account() == nullptr)
      {

         return false;

      }

      if (interactive_get_user() == nullptr)
      {

         return false;

      }

      return true;

   }


   ::type application::control_type_from_id(const ::atom& atom, ::user::enum_control_type& econtroltype)
   {

      string str(atom);

      if (str.begins_ci("still_"))
      {

         econtroltype = ::user::e_control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("label_"))
      {

         econtroltype = ::user::e_control_type_static;

         return __type(::user::still);

      }
      else if (str.begins_ci("combo_"))
      {

         econtroltype = ::user::e_control_type_combo_box;

         return __type(::user::combo_box);

      }
      else if (str.begins_ci("check_") || str.begins_ci("checkbox_"))
      {

         econtroltype = ::user::e_control_type_check_box;

         return __type(::user::check_box);

      }
      if (str.begins_ci("button_"))
      {

         econtroltype = ::user::e_control_type_button;

         return __type(::user::button);

      }

      return ::axis::application::control_type_from_id(atom, econtroltype);

   }


   ::user::interaction* application::create_menu_interaction()
   {

      return new ::user::button;

   }


} // namespace axis



