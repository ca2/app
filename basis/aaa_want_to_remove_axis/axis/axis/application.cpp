#include "framework.h"
#include "aqua/xml.h"
#include "aura/const/idpool.h"


namespace axis
{


   application::application()
   {

   }


   ::e_status application::initialize(::layered * pobjectContext)
   {

      auto estatus = aura::application::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

#ifdef CUBE

      set_draw2d_factory_exchange(&::draw2d_factory_exchange);

#endif


      m_bInitializeDataCentral = true;

      //if (m_psystem != nullptr)
      //{

      //   m_bInitializeDataCentral = System.m_bInitializeDataCentral;

      //}

      //m_bAxisProcessInitialize         = false;
      //m_bAxisProcessInitializeResult   = false;

      //m_bAxisInitialize1               = false;
      //m_bAxisInitialize1Result         = false;

      //m_bAxisInitialize                = false;
      //m_bAxisInitializeResult          = false;

      //m_bAxisInitializeInstance        = false;
      //m_bAxisInitializeInstanceResult  = false;


      m_pdataserver                    = nullptr;

      m_iWaitCursorCount               = 0;

      return estatus;

   }


   application::~application()
   {

   }


   void application::assert_valid() const
   {

      thread::assert_valid();


   }


   void application::dump(dump_context & dumpcontext) const
   {

      aura::application::dump(dumpcontext);

   }


   string application::load_string(const ::id & id)
   {

      sync_lock sl(&m_mutexStr);

      string str;

      if(m_stringmap.lookup(id, str))
      {

         return str;

      }

      if(!load_string(str,id))
      {

         id.to_string(str);

         return str;

      }

      m_stringmap.set_at(id, str);

      return str;

   }


   bool application::load_string(string & str,const ::id & id)
   {

      if(!load_cached_string(str,id,true))
      {

         return false;

      }

      return true;

   }


   bool application::load_cached_string(string & str,const ::id & id,bool bLoadStringTable)
   {

      auto pdocument = __new(::xml::document);

      if(!pdocument->load(id))
      {

         return load_cached_string_by_id(str,id,bLoadStringTable);

      }

      auto pnodeRoot = pdocument->get_root();

      if(pnodeRoot->get_name() == "string")
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


   bool application::load_cached_string_by_id(string & str,const ::id & id,bool bLoadStringTable)
   {

      string strId(id.str());

      string strTable;

      string strString;

      index iFind = 0;

      if((iFind = strId.find(':')) <= 0)
      {

         strTable = "";

         strString = strId;

      }
      else
      {

         strTable = strId.Mid(0,iFind);

         strString = strId.Mid(iFind + 1);

      }

      sync_lock sl(&m_mutexStr);

      __pointer(string_to_string) pmap;

      if(m_stringtableStd.lookup(strTable,pmap))
      {

         if(pmap != nullptr && pmap->lookup(strString,str))
         {

            return true;

         }

      }
      else if(m_stringtable.lookup(strTable,pmap))
      {

         if(pmap != nullptr && pmap->lookup(strString,str))
         {

            return true;

         }

      }
      else if(bLoadStringTable)
      {

         load_string_table(strTable,"");

         return load_cached_string_by_id(str,id,false);

      }

      return false;

   }


   void application::load_string_table(const string & pszApp,const string & pszId)
   {


   }




   void application::load_string_table()
   {

      load_string_table("","");

   }


   bool application::is_system() const
   {

      return false;

   }


   bool application::is_session() const
   {

      return false;

   }


   bool application::is_serviceable() const
   {

      return false;

   }


   ::simpledb::server * application::simpledb()
   {

      return m_psimpledb;

   }


   ::database::server * application::dataserver()
   {

      return simpledb();

   }


   ::e_status application::verb()
   {

      return true;

   }


   void application::SetCurrentHandles()
   {

      ::aura::application::SetCurrentHandles();

   }


   void application::_001CloseApplication()
   {

      set_finish();

   }


   bool application::process_exception(::exception_pointer e)
   {

      return aura::application::process_exception(e);

   }


   ::e_status     application::main()
   {

      return ::aura::application::main();

   }


   ::e_status     application::on_run()
   {

      try
      {

         ::aura::application_message signal(::aura::application_message_begin);

         route_message(&signal);

      }
      catch(...)
      {

      }

      thread * pthread = ::get_task();

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

      if(::is_set(m_pappParent))
      {

         m_pappParent->add_reference(this);

      }

resume_on_exception:

         try
         {

            m_estatus = run();

         }
         catch (::exception_pointer e)
         {

            if (handle_exception(e))
            {

               goto resume_on_exception;

            }

            m_estatus = e->m_estatus;

         }

      }
      catch (exception_pointer e)
      {

      }


      try
      {

         thread * pthread = this;

         if(pthread != nullptr && pthread->m_pevReady != nullptr)
         {

            pthread->m_pevReady->SetEvent();

         }

      }
      catch(...)
      {

         m_result.add(error_failed);

      }

      return m_estatus;

   }


   ::e_status application::init_application()
   {

      return ::aura::application::init_application();

   }


   ::e_status application::application_pre_run()
   {

      return ::aura::application::application_pre_run();

   }



   bool application::InitApplication()
   {

      return true;

   }


   bool application::do_install()
   {


      if (!::aura::application::do_install())
      {

         return false;

      }

      return true;

   }


   bool application::do_uninstall()
   {

      bool bOk = aura::application::do_uninstall();

      return bOk;

   }


   bool application::on_install()
   {

      if (!aura::application::on_install())
      {

         return false;

      }

      return true;

   }


   bool application::on_uninstall()
   {

      if(!aura::application::on_uninstall())
      {

         return false;

      }

      return true;

   }


   ::e_status application::os_native_bergedge_start()
   {

      if (!::aura::application::os_native_bergedge_start())
      {

         return false;

      }

      return true;

   }


   void application::on_request(::create * pcreate)
   {

      aura::application::on_request(pcreate);

   }


   ::e_status     application::run()
   {

      return ::aura::application::run();

   }


   //__pointer(::aura::application) application::assert_running(const char * pszAppId)
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


   ::e_status application::process_init()
   {

      create_factory < ::database::field_array >();
      create_factory < ::database::row >();
      create_factory < ::database::row_array >();

      //if (m_bAxisProcessInitialize)
      //{

      //   return m_bAxisProcessInitializeResult;

      //}

      INFO("axis::application::process_init");

      //m_bAxisProcessInitialize = true;

      //m_bAxisProcessInitializeResult = false;

      if (m_psimpledb.is_null())
      {

         __construct_new(m_psimpledb);

      }

      if (!::aura::application::process_init())
      {

         FATAL("axis::application::process_init .1");

         return false;

      }


      //m_bAxisProcessInitializeResult = true;

      FATAL("axis::application::process_init success");

      return true;

   }


   ::e_status application::init_instance()
   {

      //if (m_bAxisInitializeInstance)
      //{

      //   return m_bAxisInitializeInstanceResult;

      //}

      INFO("axis::application::init_instance .1");

      //m_bAxisInitializeInstance = true;

      //m_bAxisInitializeInstanceResult = false;

      if(!::aura::application::init_instance())
      {

         FATAL("axis::application::init_instance .2");

         return false;

      }


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

      INFO("axis::application::init_instance success");

      return true;

   }


   string application::calc_data_key()
   {

      return ::database::key("app://" + m_strAppName, is_local_data());

   }


   ::e_status application::init1()
   {

      //if (m_bAxisInitialize1)
      //{

      //   return m_bAxisInitialize1Result;

      //}

      //m_bAxisInitialize1 = true;

      //m_bAxisInitialize1Result = false;

      m_millisHeartBeat.Now();

      if (!::aura::application::init1())
      {

         return false;

      }

 /*     if (!m_psystem->m_phtml->initialize())
      {

         return false;

      }*/



      //m_bAxisInitialize1Result = true;

      return true;

   }


   ::e_status application::init2()
   {

      if(!::aura::application::init2())
         return false;

      return true;

   }


   ::e_status application::init3()
   {

      if(!::aura::application::init3())
      {

         return false;

      }

      return true;

   }


   ::e_status application::init()
   {

      //if (m_bAxisInitialize)
      //{

      //   return m_bAxisInitializeResult;

      //}

      //m_bAxisInitialize = true;

      //m_bAxisInitializeResult = false;

      ::aura::application_message signal(::aura::application_message_init);

      route_message(&signal);

      if(!signal.m_bOk)
         return false;
m_millisHeartBeat.Now();

      if(is_system())
      {

         if(has_property("save_processing"))
         {

            psession->savings().save(::e_resource_processing);

         }

         if(has_property("save_blur_back"))
         {

            psession->savings().save(::e_resource_blur_background);

         }

         if(has_property("save_transparent_back"))
         {

            psession->savings().save(::e_resource_translucent_background);

         }

      }

      if(has_property("install"))
      {
         // aura level app install
         if(!Ex2OnAppInstall())
            return false;
      }
      else if(has_property("uninstall"))
      {
         // aura level app uninstall
         if(!Ex2OnAppUninstall())
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

         if(!OpenProcessToken(
               hprocess,
               TOKEN_ALL_ACCESS,
               &htoken))
            return false;

         if(!ImpersonateLoggedOnUser(htoken))
         {
            TRACELASTERROR();
            return false;
         }
#endif
      }
m_millisHeartBeat.Now();

      //if(is_system() 
      //      && !m_varTopicQuery["app"].get_string().begins_ci("app-core/netnode")
      //      && m_varTopicQuery["app"] != "app-core/netnode_dynamic_web_server"
      //      && m_varTopicQuery["app"] != "app-gtech/alarm"
      //      && m_varTopicQuery["app"] != "app-gtech/sensible_service")
      //{
      //   Context.http().defer_auto_initialize_proxy_configuration();
      //}
m_millisHeartBeat.Now();

//      m_bAxisInitializeResult = true;

//      dappy(string(typeid(*this).name()) + " : initialize ok : " + __str(m_iErrorCode));

      return true;

   }


   void application::term_application()
   {


      try
      {


         //destroy_message_queue();

      }
      catch(...)
      {

         m_result.add(error_failed);

      }

      release_exclusive();

      ::aura::application_message signal(::aura::application_message_term_instance);

      try
      {

         route_message(&signal);

      }
      catch(...)
      {

      }

      try
      {

         try
         {

            aura::application::term_application();

         }
         catch(...)
         {

         }

      }
      catch(...)
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

      m_psimpledb.release();

   }


   void application::term()
   {

      try
      {

         ::aura::application::term();

      }
      catch(...)
      {

         m_result.add(error_failed);

      }

   }


   bool application::is_running()
   {

      return is_alive();

   }


   bool application::Ex2OnAppInstall()
   {
      return true;
   }


   bool application::Ex2OnAppUninstall()
   {

      return true;

   }


   bool application::update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession,const ::file::path & pszRoot,const string & pszRelative)
   {

      auto plocaleschema = __create_new < ::str::international::locale_schema >();

      //psession->fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, plocaleschema->m_idLocale, plocaleschema->m_idSchema);

      ::count iCount = plocaleschema->m_idaLocale.get_count();

      for(index i = 0; i < iCount; i++)
      {

         if(plocaleschema->m_idaLocale[i] == __id(std) && plocaleschema->m_idaSchema[i] == __id(std) && bIgnoreStdStd)
            continue;

         string strLocale;

         plocaleschema->m_idaLocale[i].to_string(strLocale);

         string strSchema;

         plocaleschema->m_idaSchema[i].to_string(strSchema);

         update_appmatter(handler, psession,pszRoot,pszRelative,strLocale,strSchema);

         System.install_progress_add_up();

      }


      return true;

   }

   bool application::update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession,const ::file::path & pszRoot,const string & pszRelative,const string & pszLocale,const string & pszStyle)
   {

      string strLocale;
      string strSchema;
      TRACE("update_appmatter(root=%s, relative=%s, locale=%s, style=%s)",pszRoot.c_str(),pszRelative.c_str(),pszLocale.c_str(),pszStyle.c_str());
      ::file::path strRelative = ::file::path(pszRoot) / "appmatter" / pszRelative  / get_locale_schema_dir(pszLocale,pszStyle) + ".zip";
      ::file::path strFile = Context.dir().install() / strRelative;
      ::file::path strUrl(::file::path_url);

      if(framework_is_basis())
      {
         strUrl = "http://basis-server.ca2.cc/api/spaignition/download?authnone&configuration=basis&stage=";
      }
      else
      {
         strUrl = "http://stage-server.ca2.cc/api/spaignition/download?authnone&configuration=stage&stage=";
      }

      strUrl += System.url().url_encode(strRelative);

      if(psession == nullptr)
      {

         while(true)
         {

            property_set setEmpty;

            if (Context.http().open(handler, psession, System.url().get_server(strUrl), System.url().get_protocol(strUrl), setEmpty, nullptr))
            {

               break;

            }

            sleep(200_ms);

         }

      }

      property_set set;

      set["get_memory"] = "";

      if (!Context.http().request(handler, psession, strUrl, set))
      {

         return false;

      }

      ::memory_file file;

      if(set["get_memory"].cast < memory >() != nullptr && set["get_memory"].cast < memory >()->get_size() > 0)
      {

         zip_context zip(get_context_object());

         string strDir = strFile;

         ::str::ends_eat_ci(strDir,".zip");

         try
         {

            zip.extract_all(strDir,&file);

         }
         catch(...)
         {

            // spa app_app_admin.exe would recover by retrying or someone would fix the resource packaging problem and then zip extraction at least should work.

            return false;

         }

         //System.compress().extract_all(strFile, this);

      }

      return true;

   }





   bool application::assert_user_logged_in()
   {

      const char * pszRequestUrl = nullptr;

      string strRequestUrl;

      if(file_as_string(::dir::system() / "config\\system\\ignition_server.txt").has_char())
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




   string application::matter_as_string(const char * pszMatter,const char * pszMatter2)
   {

      ::payload varFile;

      varFile["disable_ca2_sessid"] = true;

      string strMatter = Context.dir().matter(::file::path(pszMatter) / pszMatter2);

      varFile["url"] = strMatter;

      return Context.file().as_string(varFile);

   }

   //string application::dir().matter(const char * pszMatter,const char * pszMatter2)
   //{

   //   return dir().matter(pszMatter,pszMatter2);

   //}

   //bool application::is_inside_time_dir(const char * pszPath)
   //{
   //   return dir().is_inside_time(pszPath);
   //}


   //bool application::file_is_read_only(const char * pszPath)
   //{

   //   return false;
   //   //return file().is_read_only(pszPath);

   //}



   void application::process_message_filter(i32 code,::message::message * pmessage)
   {

      //__pointer(::message::base) pbase(pmessage);

      UNREFERENCED_PARAMETER(code);

      UNREFERENCED_PARAMETER(pmessage);


   }







   void application::DoWaitCursor(i32 nCode)
   {

      if(nCode < 0)
      {

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else if(nCode == 0)
      {

         if(m_iWaitCursorCount > 0)
         {
            m_iWaitCursorCount--;
         }

         if(m_iWaitCursorCount > 0)
         {

            ShowWaitCursor(true);

         }

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else
      {

         if(m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         ShowWaitCursor(true);

      }



   }

   //void application::ShowWaitCursor(bool bShow)
   //{

   //}



   void application::TermThread(HINSTANCE hInstTerm)
   {

      ::exception::throw_interface_only();

   }




   //string application::get_version()
   //{

   //   ::exception::throw_interface_only();

   //   return "";

   //}




//   void application::set_env_var(const string & payload,const string & value)
//   {
//
//      ::exception::throw_interface_only();
//
//   }



   ::aura::printer * application::get_printer(const char * pszDeviceName)
   {

      ::exception::throw_interface_only();

      return nullptr;

   }


   bool application::do_prompt_file_name(::payload & varFile,string nIDSTitle,u32 lFlags,bool bOpenFileDialog,::user::impact_system * ptemplate,::user::document * pdocument)
   {

      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nIDSTitle);

      return false;

   }






   //bool application::get_temp_file_name_template(string & strRet,const char * lpszName,const char * pszExtension,const char * pszTemplate)
   //{

   //   __throw(not_implemented());

   //   return false;

   //}


   //bool application::get_temp_file_name(string & strRet,const char * lpszName,const char * pszExtension)
   //{

   //   return get_temp_file_name_template(strRet,lpszName,pszExtension,nullptr);

   //}








   ::draw2d::icon * application::set_icon(object * pobject,::draw2d::icon * picon,bool bBigIcon)
   {

      return nullptr;

   }


   ::draw2d::icon * application::get_icon(object * pobject,bool bBigIcon) const
   {

      return nullptr;

   }


   void application::on_service_request(::create * pcreate)
   {

      ::aura::application::on_service_request(pcreate);

   }


   string application::get_mutex_name_gen()
   {
      return m_strAppName;
   }



   string application::get_license_id()
   {

      if(m_strLicense.has_char())
         return m_strLicense;

      if(m_strInstallToken.has_char())
         return m_strInstallToken;

      return m_strAppId;

   }






   //bool application::assert_user_logged_in()
   //{

   //   return axis::application::assert_user_logged_in();

   //}








   ::user::primitive * application::window_from_os_data(void * pdata)
   {

      return nullptr;

   }


   //__pointer(::message::base) application::get_message_base(LPMESSAGE pmsg)

   //{

   //   return get_message_base(pmsg->message,lpmsg->wParam,lpmsg->lParam);


   //}



   //i32 application::message_box(::user::primitive * puiOwner,const char * pszMessage,::u32 fuStyle)
   //{

   //   return ::message_box(puiOwner->get_safe_handle(),pszMessage,m_strAppName,fuStyle);

   //}


   //i32 application::message_box(const char * pszMessage,::u32 fuStyle)
   //{

   //   return ::message_box(nullptr,pszMessage,m_strAppName,fuStyle);

   //}


   //string application::message_box(const string & pszMatter,property_set & propertyset)
   //{

   //   message_box(pszMatter,0);

   //   return "";

   //}




   i32 application::hotplugin_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,hotplugin::host * phost,hotplugin::plugin * pplugin)
   {

      {

         ::install::mutex mutex(process_platform_dir_name2());

         if (mutex.already_exists())
         {

//            message_box("Could not launch spa installer. It is already running.", e_message_box_ok);

            return -35;

         }

      }

      string strValue;

      if(get_command_line_param(strValue,pszCommandLine,"enable_desktop_launch"))
      {

#ifdef _UWP

         return -1;

#else

         ::property_set set;

         return ::call_sync(::path::app_app(process_platform_dir_name2(), process_configuration_dir_name()),pszCommandLine,::path::app_app(process_platform_dir_name2(), process_configuration_dir_name()),e_display_normal, 2_min, set);

#endif

      }
      else
      {

         return hotplugin_host_host_starter_start_sync(pszCommandLine,get_context_application(),nullptr);

      }

   }

   i32 application::hotplugin_host_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      return -1;

   }



   void application::on_control_event(::user::control_event * pevent)
   {

   }


   bool application::on_open_document(::user::document * pdocument,::payload varFile)
   {

      UNREFERENCED_PARAMETER(pdocument);
      UNREFERENCED_PARAMETER(varFile);
      return true;

   }


   bool application::on_save_document(::user::document * pdocument,::payload varFile)
   {

      UNREFERENCED_PARAMETER(pdocument);
      UNREFERENCED_PARAMETER(varFile);
      return true;

   }


   void application::on_update_view(::user::impact * pview,::user::impact * pviewSender,LPARAM lHint,object* pHint)
   {


   }


//   ::e_status     application::interactive_credentials(::account::credentials * pcredentials)
//   {
//
//      return ::aura::applciation::interactive_credentials(pcredentials);
//
//   }
//
//
//   string application::interactive_get_credentials(string & strUsername, string & strPassword, string strToken)
//   {
//
//      return ::account::get_cred(this, strUsername, strPassword, strToken);
//
//   }
//
//   void application::set_cred(string strToken, const char * pszUsername, const char * pszPassword)
//   {
//
//      ::account::set_cred(this,strToken, pszUsername, pszPassword);
//
//   }
//
//   void application::set_cred_ok(string strToken, bool bOk)
//   {
//
//      ::account::set_cred_ok(this, strToken, bOk);
//
//   }

   //::html::html * application::create_html()
   //{

   //   return new ::html::html(get_context_application());

   //}


   //string application::http_get(const string & strUrl, ::property_set & set)
   //{

   //   return http().get(strUrl, set);

   //}

   //bool application::app_data_set(::const ::id & id, stream & stream)
   //{

   //   return data_save(id, stream);

   //}


   //bool application::app_data_get(::const ::id & id, stream & stream)
   //{

   //   return data_get(id, stream);

   //}


   //bool application::app_data_set(::const ::id & id, ::object & obj)
   //{

   //   return data_set(id, obj);

   //}


   //bool application::app_data_get(::const ::id & id, ::object & obj)
   //{

   //   return data_get(id, obj);

   //}


   //bool application::compress_ungz(const ::stream & os, const ::stream & is)
   //{

   //   return System.compress().ungz(this, os, is);


   //}


   //bool application::compress_ungz(memory_base & mem)
   //{

   //   return System.compress().ungz(this, mem);

   //}


   //bool application::compress_gz(const ::stream & os, const ::stream & is, int iLevel)

   //{

   //   return System.compress().gz(this, os, is, iLevel);


   //}


   //bool application::compress_gz(const ::stream & os, const ::stream & is, int iLevel)
   //{

   //   return System.compress().gz(this, os, is, iLevel);

   //}


   bool application::is_local_data()
   {

      return m_datakey.m_bLocalData;

   }





} // namespace axis



