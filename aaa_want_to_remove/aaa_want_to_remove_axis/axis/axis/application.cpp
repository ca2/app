#include "framework.h"
#include "aqua/xml.h"
#include "aura/const/idpool.h"


namespace axis
{


   application::application()
   {

   }


   void application::initialize(::object * pobject)
   {

      auto estatus = aura::application::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

#ifdef CUBE

      ([a-z0-9_]+)_factory(&::([a-z0-9_]+)_factory);

#endif


      m_bInitializeDataCentral = true;

      //if (m_psystem != nullptr)
      //{

      //   m_bInitializeDataCentral = psystem->m_bInitializeDataCentral;

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


   void application::assert_ok() const
   {

      thread::assert_ok();


   }


   void application::dump(dump_context & dumpcontext) const
   {

      aura::application::dump(dumpcontext);

   }


   string application::load_string(const ::atom & atom)
   {

      synchronous_lock synchronouslock(&m_mutexStr);

      string str;

      if(m_stringmap.lookup(atom, str))
      {

         return str;

      }

      if(!load_string(str,atom))
      {

         atom.to_string(str);

         return str;

      }

      m_stringmap.set_at(atom, str);

      return str;

   }


   bool application::load_string(string & str,const ::atom & atom)
   {

      if(!load_cached_string(str,atom,true))
      {

         return false;

      }

      return true;

   }


   bool application::load_cached_string(string & str,const ::atom & atom,bool bLoadStringTable)
   {

      auto pdocument = __new(::xml::document);

      if(!pdocument->load(atom))
      {

         return load_cached_string_by_id(str,atom,bLoadStringTable);

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


   bool application::load_cached_string_by_id(string & str,const ::atom & atom,bool bLoadStringTable)
   {

      string strId(atom.str());

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

      synchronous_lock synchronouslock(&m_mutexStr);

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

         return load_cached_string_by_id(str,atom,false);

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


   void application::verb()
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


   void     application::main()
   {

      return ::aura::application::main();

   }


   void     application::on_run()
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

      string strType = __type_name(this);

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


   void application::init_application()
   {

      return ::aura::application::init_application();

   }


   void application::application_pre_run()
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


   void application::os_native_bergedge_start()
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


   void     application::run()
   {

      return ::aura::application::run();

   }


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


   void application::process_init()
   {

      add_factory_item < ::database::field_array >();
      add_factory_item < ::database::row >();
      add_factory_item < ::database::row_array >();

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

      if (!::aura::application::process_init())
      {

         FATAL("axis::application::process_init .1");

         return false;

      }


      //m_bAxisProcessInitializeResult = true;

      FATAL("axis::application::process_init success");

      return true;

   }


   void application::init_instance()
   {

      //if (m_bAxisInitializeInstance)
      //{

      //   return m_bAxisInitializeInstanceResult;

      //}

      INFORMATION("axis::application::init_instance .1");

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

            pathDatabase = pcontext->m_papexcontext->dir().appdata() / "system.sqlite";

         }
         else if (is_session())
         {

            pathDatabase = pcontext->m_papexcontext->dir().appdata() / "session.sqlite";

         }
         else
         {

            pathDatabase = pcontext->m_papexcontext->dir().appdata() / "app.sqlite";

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

      INFORMATION("axis::application::init_instance success");

      return true;

   }


   string application::calc_data_key()
   {

      return ::database::key("app://" + m_strAppName, is_local_data());

   }


   void application::init1()
   {

      //if (m_bAxisInitialize1)
      //{

      //   return m_bAxisInitialize1Result;

      //}

      //m_bAxisInitialize1 = true;

      //m_bAxisInitialize1Result = false;

      m_durationHeartBeat.Now();

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


   void application::init2()
   {

      if(!::aura::application::init2())
         return false;

      return true;

   }


   void application::init3()
   {

      if(!::aura::application::init3())
      {

         return false;

      }

      return true;

   }


   void application::init()
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
m_durationHeartBeat.Now();

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
m_durationHeartBeat.Now();

      //if(is_system() 
      //      && !m_varTopicQuery["app"].get_string().begins_ci("app-core/netnode")
      //      && m_varTopicQuery["app"] != "app-core/netnode_dynamic_web_server"
      //      && m_varTopicQuery["app"] != "app-gtech/alarm"
      //      && m_varTopicQuery["app"] != "app-gtech/sensible_service")
      //{
      //   pcontext->m_papexcontext->http().defer_auto_initialize_proxy_configuration();
      //}
m_durationHeartBeat.Now();

//      m_bAxisInitializeResult = true;

//      dappy(__type_name(this) + " : initialize ok : " + __string(m_iErrorCode));

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

            m_psimpledb->destroy();

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

      auto plocaleschema = __create_new < ::text::international::locale_schema >();

      //psession->fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, plocaleschema->m_atomLocale, plocaleschema->m_atomSchema);

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

         psystem->install_progress_add_up();

      }


      return true;

   }

   bool application::update_appmatter(::sockets::socket_handler & handler, __pointer(::sockets::http_session) & psession,const ::file::path & pszRoot,const string & pszRelative,const string & pszLocale,const string & pszStyle)
   {

      string strLocale;
      string strSchema;
      FORMATTED_TRACE("update_appmatter(root=%s, relative=%s, locale=%s, style=%s)",pszRoot.c_str(),pszRelative.c_str(),pszLocale.c_str(),pszStyle.c_str());
      ::file::path strRelative = ::file::path(pszRoot) / "appmatter" / pszRelative  / get_locale_schema_dir(pszLocale,pszStyle) + ".zip";
      ::file::path strFile = pcontext->m_papexcontext->dir().install() / strRelative;
      ::file::path strUrl(::file::path_url);

      if(framework_is_basis())
      {
         strUrl = "http://basis-server.ca2.software/api/spaignition/download?authnone&configuration=basis&stage=";
      }
      else
      {
         strUrl = "http://stage-server.ca2.software/api/spaignition/download?authnone&configuration=stage&stage=";
      }

      strUrl += purl->url_encode(strRelative);

      if(psession == nullptr)
      {

         while(true)
         {

            property_set setEmpty;

            if (pcontext->m_papexcontext->http().open(handler, psession, purl->get_server(strUrl), purl->get_protocol(strUrl), setEmpty, nullptr))
            {

               break;

            }

            sleep(200_ms);

         }

      }

      property_set set;

      set["get_memory"] = "";

      if (!pcontext->m_papexcontext->http().request(handler, psession, strUrl, set))
      {

         return false;

      }

      ::memory_file file;

      if(set["get_memory"].cast < memory >() != nullptr && set["get_memory"].cast < memory >()->get_size() > 0)
      {

         zip_context zip(this);

         string strDir = strFile;

         ::str().ends_eat_ci(strDir,".zip");

         try
         {

            zip.extract_all(strDir,&file);

         }
         catch(...)
         {

            // spa app_app_admin.exe would recover by retrying or someone would fix the resource packaging problem and then zip extraction at least should work.

            return false;

         }

         //psystem->compress().extract_all(strFile, this);

      }

      return true;

   }





   bool application::assert_user_logged_in()
   {

      const char * pszRequestUrl = nullptr;

      string strRequestUrl;

      if(m_psystem->m_pacmefile->as_string(         auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\system\\ignition_server.txt").has_char())
      {

         strRequestUrl = "https://" + m_psystem->m_pacmefile->as_string(         auto psystem = m_psystem;

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\system\\ignition_server.txt") + "/api/spaignition";

         pszRequestUrl = strRequestUrl;

      }

      if (get_session() == nullptr)
      {

         return false;

      }

      if (get_session()->account() == nullptr)
      {

         return false;

      }

      if (interactive_get_user() == nullptr)
      {

         return false;

      }

      return true;

   }




   string application::matter_as_string(const ::string & pszMatter, const ::string & pszMatter2)
   {

      ::payload payloadFile;

      payloadFile["disable_ca2_sessid"] = true;

      string strMatter = pcontext->m_papexcontext->dir().matter(::file::path(pszMatter) / pszMatter2);

      payloadFile["url"] = strMatter;

      return pcontext->m_papexcontext->file().as_string(payloadFile);

   }

   //string application::dir().matter(const ::string & pszMatter, const ::string & pszMatter2)
   //{

   //   return dir().matter(pszMatter,pszMatter2);

   //}

   //bool application::is_inside_time_dir(const ::string & pszPath)
   //{
   //   return dir().is_inside_time(pszPath);
   //}


   //bool application::file_is_read_only(const ::string & pszPath)
   //{

   //   return false;
   //   //return file().is_read_only(pszPath);

   //}



   void application::process_message_filter(i32 code,::message::message * pmessage)
   {

      //__pointer(::user::message) pusermessage(pmessage);

      __UNREFERENCED_PARAMETER(code);

      __UNREFERENCED_PARAMETER(pmessage);


   }







   void application::DoWaitCursor(i32 nCode)
   {

      if(nCode < 0)
      {

         m_iWaitCursorCount = 0;
         show_wait_cursor(false);

      }
      else if(nCode == 0)
      {

         if(m_iWaitCursorCount > 0)
         {
            m_iWaitCursorCount--;
         }

         if(m_iWaitCursorCount > 0)
         {

            show_wait_cursor(true);

         }

         m_iWaitCursorCount = 0;
         show_wait_cursor(false);

      }
      else
      {

         if(m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         show_wait_cursor(true);

      }



   }

   //void application::show_wait_cursor(bool bShow)
   //{

   //}



   void application::TermThread(HINSTANCE hInstTerm)
   {

      throw ::interface_only();

   }




   //string application::get_version()
   //{

   //   throw ::interface_only();

   //   return "";

   //}




//   void application::set_env_var(const string & payload,const string & value)
//   {
//
//      throw ::interface_only();
//
//   }



   ::aura::printer * application::get_printer(const ::string & pszDeviceName)
   {

      throw ::interface_only();

      return nullptr;

   }


   bool application::do_prompt_file_name(::payload & payloadFile,string nIDSTitle,u32 lFlags,bool bOpenFileDialog,::user::impact_system * ptemplate,::user::document * pdocument)
   {

      __UNREFERENCED_PARAMETER(payloadFile);
      __UNREFERENCED_PARAMETER(nIDSTitle);

      return false;

   }






   //bool application::get_temp_file_name_template(string & strRet, const ::string & lpszName, const ::string & pszExtension, const ::string & pszTemplate)
   //{

   //   throw ::not_implemented();

   //   return false;

   //}


   //bool application::get_temp_file_name(string & strRet, const ::string & lpszName, const ::string & pszExtension)
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


   //__pointer(::user::message) application::get_message_base(LPMESSAGE pmsg)

   //{

   //   return get_message_base(pmsg->message,lpmsg->wParam,lpmsg->lParam);


   //}



   //i32 application::message_box(::user::primitive * puiOwner, const ::string & pszMessage,::u32 fuStyle)
   //{

   //   return ::message_box(puiOwner->get_safe_handle(),pszMessage,m_strAppName,fuStyle);

   //}


   //i32 application::message_box(const ::string & pszMessage,::u32 fuStyle)
   //{

   //   return ::message_box(nullptr,pszMessage,m_strAppName,fuStyle);

   //}


   //string application::message_box(const string & pszMatter,property_set & propertyset)
   //{

   //   message_box(pszMatter,0);

   //   return "";

   //}




   i32 application::hotplugin_host_starter_start_sync(const ::string & pszCommandLine,::aura::application * papp,hotplugin::host * phost,hotplugin::plugin * pplugin)
   {

      {

         ::install::mutex mutex(process_platform_dir_name2());

         if (mutex.already_exists())
         {

//            output_error_message("Could not launch spa installer. It is already running.", e_message_box_ok);

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

         return ::call_sync(::path::app_app(process_platform_dir_name2(), process_configuration_dir_name()),pszCommandLine,::path::app_app(process_platform_dir_name2(), process_configuration_dir_name()),e_display_restored, 2_min, set);

#endif

      }
      else
      {

         return hotplugin_host_host_starter_start_sync(pszCommandLine,get_app(),nullptr);

      }

   }

   i32 application::hotplugin_host_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      return -1;

   }



   void application::handle(::topic * ptopic, ::context * pcontext)
   {

   }


   bool application::on_open_document(::user::document * pdocument,::payload payloadFile)
   {

      __UNREFERENCED_PARAMETER(pdocument);
      __UNREFERENCED_PARAMETER(payloadFile);
      return true;

   }


   bool application::on_save_document(::user::document * pdocument,::payload payloadFile)
   {

      __UNREFERENCED_PARAMETER(pdocument);
      __UNREFERENCED_PARAMETER(payloadFile);
      return true;

   }


   void application::on_update_view(::user::impact * pimpact,::user::impact * pviewSender,LPARAM lHint,object* pHint)
   {


   }


//   void     application::interactive_credentials(::account::credentials * pcredentials)
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
//   void application::set_cred(string strToken, const ::string & pszUsername, const ::string & pszPassword)
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

   //   return new ::html::html(get_app());

   //}


   //string application::http_get(const ::string & strUrl, ::property_set & set)
   //{

   //   return http().get(strUrl, set);

   //}

   //bool application::app_data_set(::const ::atom & atom, stream & stream)
   //{

   //   return data_save(atom, stream);

   //}


   //bool application::app_data_get(::const ::atom & atom, stream & stream)
   //{

   //   return data_get(atom, stream);

   //}


   //bool application::app_data_set(::const ::atom & atom, ::object & obj)
   //{

   //   return data_set(atom, obj);

   //}


   //bool application::app_data_get(::const ::atom & atom, ::object & obj)
   //{

   //   return data_get(atom, obj);

   //}


   //bool application::compress_ungz(const ::stream & os, const ::stream & is)
   //{

   //   return psystem->compress().ungz(this, os, is);


   //}


   //bool application::compress_ungz(memory_base & mem)
   //{

   //   return psystem->compress().ungz(this, mem);

   //}


   //bool application::compress_gz(const ::stream & os, const ::stream & is, int iLevel)

   //{

   //   return psystem->compress().gz(this, os, is, iLevel);


   //}


   //bool application::compress_gz(const ::stream & os, const ::stream & is, int iLevel)
   //{

   //   return psystem->compress().gz(this, os, is, iLevel);

   //}


   bool application::is_local_data()
   {

      return m_datakey.m_bLocalData;

   }





} // namespace axis



