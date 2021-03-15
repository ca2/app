#include "framework.h"


namespace sphere
{



   application::application(::context_object * pcontextobject) :
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject)
   {

      m_bContextTheme = true;

      m_bLicense = false;

      m_bDrawCursor = true;
      m_bShowPlatform = false;
      m_papplicationCurrent = nullptr;
      m_bLicense = false;

      m_ppaneview = nullptr;

      m_strAppName = "app/sphere";


   }


   application::~application()
   {

   }


   ::e_status application::init_instance()
   {

      if (!::aura::application::init_instance())
      {

         return false;

      }


      create_factory <main_frame >();



      set_local_data();

      initialize_bergedge_application_interface();

      //puser->filemanager()->m_strLevelUp = "levelup";

      SetRegistryKey("ca2core");

      //return true;

      return true;

   }


   bool application::init1()
   {

      if (!::aura::application::init1())
         return false;

      return true;

   }


   bool application::init()
   {

      if (!::aura::application::init())
      {

         return false;

      }

      return true;

   }




   u32 application::guess_code_page(const string & str)
   {

      return charguess(str)();

   }


   colorertake5::ParserFactory & application::parser_factory()
   {

      if (m_pparserfactory == nullptr)
      {

         m_pparserfactory = new colorertake5::ParserFactory(this);

      }

      return *m_pparserfactory;

   }


   __pointer(::aura::application) application::get_context_system()
   {

      return new application(this);

   }


   //::e_status application::init_instance()
   //{



   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if(strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   if(chFirst == 'd')
   //   {
   //      if(strId == "default_file_handler")
   //      {
   //         return ::filehandler::application::init_instance();
   //      }
   //   }
   //   else if(chFirst == 'u')
   //   {
   //      if(strId == "userstack")
   //      {
   //         return ::userstack::application::init_instance();
   //      }
   //   }

   //   return asphere::application::init_instance();

   //}


   void application::term_instance()
   {

      if (m_pconsole.is_set())
      {

         m_pconsole->term_instance();

         m_pconsole.release();

      }

      if (m_pprompt.is_set())
      {

         m_pprompt->term_instance();

         m_pprompt.release();

      }


      if (m_pfilehandler.is_set())
      {

         m_pfilehandler->term_instance();

         m_pfilehandler.release();

      }

      if (m_pcalculator.is_set())
      {

         m_pcalculator->term_instance();

         m_pcalculator.release();

      }


      aura::application::term_instance();

   }


   void application::_001OnFileNew()
   {

      string strId = m_strId;

      char chFirst = '\0';

      if(strId.get_length() > 0)
      {

         chFirst = strId[0];

      }

//      ::asphere::application::_001OnFileNew();

   }


   bool application::bergedge_start()
   {
      //string strId = m_strId;
      //char chFirst = '\0';
      //if(strId.get_length() > 0)
      //{
      //   chFirst = strId[0];
      //}
      //if(chFirst == 'd')
      //{
      //   if(strId == "default_file_handler")
      //   {
      //      return ::filehandler::application::bergedge_start();
      //   }
      //}
      //else if(chFirst == 'u')
      //{
      //   if(strId == "userstack")
      //   {
      //      return ::userstack::application::bergedge_start();
      //   }
      //}

      //return ::asphere::application::bergedge_start();

      return false;

   }

   bool application::on_install()
   {
      //string strId = m_strId;
      //char chFirst = '\0';
      //if(strId.get_length() > 0)
      //{
      //   chFirst = strId[0];
      //}
      //if(chFirst == 'd')
      //{
      //   if(strId == "default_file_handler")
      //   {
      //      return ::filehandler::application::on_install();
      //   }
      //}
      //else if(chFirst == 'u')
      //{
      //   if(strId == "userstack")
      //   {
      //      return ::userstack::application::on_install();
      //   }
      //}

      //return asphere::application::on_install();
      return true;
   }


   bool application::on_uninstall()
   {
      //string strId = m_strId;
      //char chFirst = '\0';
      //if(strId.get_length() > 0)
      //{
      //   chFirst = strId[0];
      //}
      //if(chFirst == 'd')
      //{
      //   if(strId == "default_file_handler")
      //   {
      //      return ::filehandler::application::on_uninstall();
      //   }
      //}
      //else if(chFirst == 'u')
      //{
      //   if(strId == "userstack")
      //   {
      //      return ::userstack::application::on_uninstall();
      //   }

      //}

      //return asphere::application::on_uninstall();

      return true;

   }


   void application::on_request(::create * pcreate)
   {

      ::aura::application::on_request(pcreate);

      m_ptemplate_pane->do_request(pcreate);

      //string strId = m_strId;
      //char chFirst = '\0';
      //if(strId.get_length() > 0)
      //{
      //   chFirst = strId[0];
      //}
      //if(chFirst == 'd')
      //{
      //   if(strId == "default_file_handler")
      //   {
      //      return ::filehandler::application::on_request(pcreate);
      //   }
      //}
      //else if(chFirst == 'u')
      //{
      //   if(strId == "userstack")
      //   {
      //      return ::userstack::application::on_request(pcreate);
      //   }
      //}
      //return ::asphere::application::on_request(pcreate);


   }


   bool application::is_serviceable() const
   {


      //string strId = m_strId;

      //char chFirst = '\0';

      //if(strId.get_length() > 0)
      //{

      //   chFirst = strId[0];

      //}

      //if(chFirst == 'd')
      //{

      //   if(strId == "default_file_handler")
      //   {

      //      return ::filehandler::application::is_serviceable();

      //   }

      //}

      //return ::asphere::application::is_serviceable();

      return false;

   }

   service_base * application::allocate_new_service()
   {
      //string strId = m_strId;
      //char chFirst = '\0';
      //if(strId.get_length() > 0)
      //{
      //   chFirst = strId[0];
      //}
      //if(chFirst == 'd')
      //{
      //   if(strId == "default_file_handler")
      //   {

      //      return ::filehandler::application::allocate_new_service();

      //   }

      //}

      //return ::asphere::application::allocate_new_service();

      return nullptr;

   }


   ::user::document *  application::_001OpenDocumentFile(::payload varFile)
   {

      //string strId = m_strId;

      //char chFirst = '\0';

      //if(strId.get_length() > 0)
      //{

      //   chFirst = strId[0];

      //}

      //if(chFirst == 'd')
      //{

      //   if(strId == "default_file_handler")
      //   {

      //      return ::filehandler::application::_001OpenDocumentFile(varFile);

      //   }

      //}
      //else if(chFirst == 'r')
      //{

      //}

      //return ::asphere::application::_001OpenDocumentFile(varFile);

      return nullptr;

   }


   ::e_status     application::run()
   {

      return ::aura::application::run();

   }




   //void department::construct()
   //{

   //   m_strAppName = "userstack";
   //   m_strBaseSupportId = "ca2_userstack";
   //   m_strInstallToken = "userstack";
   //   m_bLicense = false;
   //   m_eexclusiveinstance = ::ExclusiveInstanceNone;

   //}

   console::department * application::console()
   {

      if (m_pconsole.is_null())
      {

         m_pconsole = __new(::console::department(this));

         MESSAGE_LINK(WM_APP + 3243, this, m_pconsole.m_p, &console::department::_001OnImpact);


      }

      return m_pconsole;

   }


   prompt::department * application::prompt()
   {

      if (m_pprompt.is_null())
      {

         m_pprompt = __new(::prompt::department(this));

      }

      return m_pprompt;

   }


   filehandler::department * application::filehandler()
   {

      if (m_pfilehandler.is_null())
      {

         m_pfilehandler = __new(::filehandler::department(this));

      }

      return m_pfilehandler;

   }


   calculator::department * application::calculator()
   {

      if (m_pcalculator.is_null())
      {

         m_pcalculator = __new(::calculator::department(this));

      }

      return m_pcalculator;

   }



   //void department::term_instance()
   //{


   //   //      string strId;
   //   //
   //   //      __pointer(::apex::department) pcaapp;
   //   //
   //   //      POSITION pos = m_mapApplication.get_start_position();
   //   //
   //   //      while (pos != nullptr)
   //   //      {
   //   //
   //   //         strId.Empty();
   //   //
   //   //         pcaapp = nullptr;
   //   //
   //   //         m_mapApplication.get_next_assoc(pos, strId, pcaapp);
   //   //
   //   //         __pointer(::apex::department) papp = (pcaapp);
   //   //
   //   //         papp->set_finish();
   //   //
   //   //      }

   //   try
   //   {

   //      ::asphere::department::term_instance();

   //   }
   //   catch (...)
   //   {

   //   }



   //}


   //bool department::bergedge_start()
   //{

   //   return true;

   //}


   //void department::OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema)
   //{

   //   UNREFERENCED_PARAMETER(pdata);

   //}


   void application::load_string_table()
   {
      ::aura::application::load_string_table();
      ::aura::application::load_string_table("platform", "");
   }

   bool application::file_manager_open_file(
   ::filemanager::data * pdata,
   ::file::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      if (itema.get_size() > 0)
      {
         return true;
      }
      return false;
   }


   void application::initialize_bergedge_application_interface()
   {

      //i32 iCount = 32; // todo: get from bergedge profile

      create_factory < ::userstack::document >();
      create_factory < ::userstack::view >();
      create_factory < ::userstack::pane_view >();
      create_factory < ::userstack::frame >();

      m_ptemplate_pane = new ::user::single_document_template(
      this,
      "bergedge/frame",
      __type(::userstack::document),
      __type(::userstack::frame),
      __type(::userstack::pane_view));

   }


   void application::launch_app(const char * psz)
   {
      UNREFERENCED_PARAMETER(psz);
   }

   void application::install_app(const char * psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   //void application::on_request(::create * pcreate)
   //{


   //}


   bool application::on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId)
   {

      if (m_strAppName == "app/userstack")
      {

         if (eexclusive == ::ExclusiveInstanceLocalId)
         {
#ifdef WINDOWS_DESKTOP
            ::memory_file file(this);
            file.from_string(m_varTopicFile);
            COPYDATASTRUCT data;
            data.dwData = 2000;
            data.cbData = (u32)file.get_length();
            data.lpData = file.get_data();
            ::oswindow oswindow = ::FindWindowA(nullptr, "::ca2::account::message_wnd::department::");

            ::SendMessage(oswindow, WM_COPYDATA, (WPARAM)0, (LPARAM)&data);

            return true;
#else
            __throw(todo);
#endif
         }

      }

      return ::aura::application::on_exclusive_instance_conflict(bHandled, eexclusive, strId);

   }



   /*   void department::request(::create * pcreate)
      {

         if(m_papplicationCurrent != nullptr && m_papplicationCurrent != this
            && (pcreate->m_pcommandline->m_strApp.is_empty()
            ||App(m_papplicationCurrent).m_strAppName == pcreate->m_pcommandline->m_strApp))
         {
            if(get_document() != nullptr && get_document()->get_typed_view < pane_view >() != nullptr)
            {
               get_document()->get_typed_view < pane_view >()->set_cur_tab_by_id("app:" + App(m_papplicationCurrent).m_strAppName);
            }
            App(m_papplicationCurrent).do_request(pcreate);
            if(pcreate->m_pcommandline->m_varQuery["document"].cast < ::user::document > () == nullptr)
            {
               goto alt1;
            }

         }
         else
         {
            alt1:
            if(pcreate->m_pcommandline->m_varFile.get_type() == ::e_type_string)
            {
               if(::str::ends_ci(pcreate->m_pcommandline->m_varFile, ".ca2"))
               {
                  string strCommand = pcontext->file().as_string(pcreate->m_pcommandline->m_varFile);
                  if(::str::begins_eat(strCommand, "ca2prompt\r")
                  || ::str::begins_eat(strCommand, "ca2prompt\n"))
                  {
                     strCommand.trim();
                     add_fork_uri(strCommand);
                  }
                  return;
               }
               else
               {
                  on_request(pcreate);
               }
            }
            else if(pcreate->m_pcommandline->m_strApp.has_char() &&
               get_document() != nullptr && get_document()->get_typed_view < pane_view >() != nullptr
               && (!pcreate->m_papplicationbias.is_set() || pcreate->m_papplicationbias->m_puserinteractionParent == nullptr))
            {
               //message_box(nullptr, "request3", "request3", e_message_box_icon_exclamation);
               get_document()->get_typed_view < pane_view >()->set_cur_tab_by_id("app:" + pcreate->m_pcommandline->m_strApp);
               App(m_papplicationCurrent).do_request(pcreate);
            }
            else
            {
               //message_box(nullptr, "request4", "request4", e_message_box_icon_exclamation);
               on_request(pcreate);
            }
         }
      }*/

   void application::request_topic_file(::payload & varQuery)
   {
   }

   void application::request_topic_file()
   {
   }


   __pointer(::aura::application) application::application_get(const char * pszAppId, bool bCreate, bool bSynch, application_bias * papplicationbias)
   {

      __pointer(::aura::application) papp;

      if (appptra().lookup(pszAppId, papp))
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

         papp = create_application(pszAppId, bSynch, papplicationbias);

      }
      catch (...)
      {

         papp = nullptr;

      }

      if (papp == nullptr)
      {

         return nullptr;

      }

      if (is_null(App(papp)))
      {

         return nullptr;

      }

      appptra_add(papp);

      psession->appptra_add(papp);

      return papp;

   }

   __pointer(::aura::application) application::get_current_application()
   {
      return m_papplicationCurrent;
   }


   void application::check_topic_file_change()
   {
      if (m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
      {
         m_varCurrentViewFile = m_varTopicFile;
         request_topic_file();
      }
   }


   //bool application::on_install()
   //{

   //   string strFormat;

   //   string strSentinelPath;

   //   strSentinelPath = pcontext->dir().install() / "stage/x86/app.sentinel.exe";

   //   pcontext->os().local_machine_set_run("ca2 app.sentinel", "\"" + strSentinelPath + "\"", true);

   //   return ::asphere::department::on_install();
   //}


   void application::set_app_title(const char * pszType, const char * pszAppId, const char * pszTitle)
   {

      __pointer(::aura::application) papp;

      if (appptra().lookup(string(pszType) + ":" + string(pszAppId), papp) && papp.is_set())
      {

         //__pointer(pane_view) ppaneview = m_ppaneview;

         //if (ppaneview != nullptr)
         //{

         //   string strAppName(pszAppId);

         //   ::user::tab_pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

         //   if (ppane != nullptr)
         //   {

         //      ppane->set_title(pszTitle);

         //      ppaneview->on_layout(::draw2d::graphics_pointer & pgraphics);

         //   }

         //}

      }

   }


   //bool application::init1()
   //{


   //   if (!::asphere::department::init1())
   //      return false;


   //   return true;


   //}


   //bool application::init()
   //{

   //   if (!::asphere::department::init())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   bool application::os_native_bergedge_start()
   {

      return ::aura::application::os_native_bergedge_start();

   }


   ::e_status     application::main()
   {

      return ::aura::application::main();

   }





   //bool application::on_uninstall()
   //{

   //   bool bOk = true;

   //   try
   //   {

   //      if (!::aura::application::on_uninstall())
   //      {

   //         bOk = false;

   //      }

   //   }
   //   catch (...)
   //   {

   //      m_error.set_if_not_set();

   //      bOk = false;

   //   }

   //   return bOk;

   //}


   //bool application::is_serviceable()
   //{

   //   return false;

   //}


   //service_base * application::allocate_new_service()
   //{

   //   return nullptr;

   //}


   void application::pre_translate_message(::message::message * pmessage)
   {

      if (m_pconsole.is_set())
      {

         m_pconsole->pre_translate_message(pmessage);

         if(pmessage->m_bRet)
         {

            return;

         }


      }

      return ::aura::application::pre_translate_message(pmessage);

   }

   void application::route_command_message(::message::command * pcommand)
   {

      ::aura::application::route_command_message(pcommand);

   }

} //namespace sphere



