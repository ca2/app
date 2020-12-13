#include "framework.h"
#include "core/user/userex/_userex.h"
#include "acme/filesystem/filemanager/_.h"
#include "acme/user/account/account.h"


#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace acme
{

   //session_docs * create_session_docs();

   //void destroy_session_docs(session_docs * pdocs);

   session::session()
   {


      create_factory < ::user::user >();
      create_factory < ::acme::session, ::acme::session >();

      //m_strAppId                    = "core_session";
      //m_strAppName                  = "core_session";
      //m_strBaseSupportId            = "core_session";
      //m_strInstallToken             = "core_session";

      m_puiLastUserInputPopup = nullptr;

      //m_pdocs = create_session_docs();

      //m_bLicense				               = false;

      //m_bLicense           = false;
      //m_eexclusiveinstance = ExclusiveInstanceNone;

   }


   session::~session()
   {

      //destroy_session_docs(m_pdocs);

   }


   ::estatus session::initialize(::matter * pobjectContext)
   {

      auto estatus = ::acme::session::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }


      //m_strAppId = "base_session";
//m_strAppName = "base_session";
//m_strBaseSupportId = "base_session";
//m_strInstallToken = "base_session";

      m_iMainMonitor = -1;

      m_puiCapture = nullptr;

      m_puiMouseMoveCapture = nullptr;

      m_ecursorDefault = cursor_arrow;

      m_ecursor = cursor_default;

      m_puiMouseMoveCapture = nullptr;

      m_psavings = __new(class ::acme::savings(this));

      return estatus;

   }


   void session::install_message_routing(::channel * pchannel)
   {

      //acme::application::install_message_routing(pchannel);
      acme::session::install_message_routing(pchannel);

   }


   ::estatus session::process_init()
   {

      /*if(!::acme::application::process_init())
         return false;*/

      if(!::acme::session::process_init())
         return false;

      //auto estatus = process_init_userex();

      //if(!estatus)
      //{

      //   return estatus;

      //}
      auto estatus = __construct(m_puser);

      if (!estatus || !m_puser)
      {

         ERR(".4");

         return false;

      }

      INFO("end");
      return true;

   }


   ::estatus session::init1()
   {

      //if (!::acme::application::init1())
      //{

      //   return false;

      //}

      if (!::acme::session::init1())
      {

         return false;

      }



         if (!::acme::session::init1())
            return false;

         //if (!::acme::application::init1())
           // return false;

         //if (m_puserstyle.is_null())
         //{
         //
         //   defer_create_user_style(preferred_experience());
         //
         //}

         if (!m_puser->init1())
            return false;

         if (!m_puser->init2())
            return false;



      auto estatus = __compose_new(m_puserex);

      if(!estatus)
      {

         return false;

      }

      if (!m_puserex->init())
      {

         return false;

      }

      if (!m_puserex->init1())
      {

         return false;

      }

      if (!m_puserex->init2())
      {

         return false;

      }

      return true;


   }


   ::estatus session::init()
   {

      //if (!::acme::application::init())
      //{

      //   return false;

      //}

      if (!::acme::session::init())
      {

         return false;

      }



      return true;

   }


   ::estatus session::init2()
   {

      //if (!::acme::application::init2())
      //{

      //   return false;

      //}

      if (!::acme::session::init2())
      {

         return false;

      }

      return true;

   }



   ::estatus session::init_session()
   {

      //if (!::acme::application::init_application())
      //{

      //   return false;

      //}

      if (!::acme::session::init_session())
      {

         return false;

      }

      initialize_bergedge_application_interface();

      //SetRegistryKey("ca2core");

      if(!InitializeLocalDataCentral())
      {

         message_box("Could not initialize Local data central");

         return false;

      }

      initialize_bergedge_application_interface();

      if(is_remote_session())
      {

         //psession->savings().save(::acme::resource_display_bandwidth);
         //psession->savings().save(::acme::resource_blur_background);
         //psession->savings().save(::acme::resource_blurred_text_embossing);
         //psession->savings().save(::acme::resource_translucent_background);

      }

      if (!initialize_filemanager_component(this))
      {

         return false;

      }

      return true;

   }


   void session::term_session()
   {


      try
      {

         ::acme::session::term_session();

      }
      catch (...)
      {

      }
      try
      {

         m_puser->term();

      }
      catch (...)
      {

      }


      m_puser.release();

      try
      {

         if (m_puserex.is_set())
         {

            m_puserex->term();

         }

      }
      catch (...)
      {

      }

      //__releasem_puserex.release();




      filemanager_finalize();

   }


   void session::term()
   {

      try
      {

         ::acme::session::term();

      }
      catch(...)
      {

         m_result.add(error_failed);

      }

      //try
      //{

      //   ::acme::application::term();

      //}
      //catch(...)
      //{

      //   m_result.add(error_failed);

      //}

   }


   //::estatus session::bergedge_start()
   //{

   //   return true;

   //}


   void session::_001OnFileNew()
   {

   }


   //void session::route_command_message(::user::command * pcommand)
   //{

   //   return application::route_command_message(pcommand);

   //}


   //void session::load_string_table()
   //{

   //   application::load_string_table();
   //   application::load_string_table("plane", "");
   //   application::load_string_table();
   //   application::load_string_table("session", "");

   //}


   void session::launch_app(const char * psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   void session::install_app(const char * psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   void session::on_request(::create * pcreate)
   {

      ::acme::session::on_request(pcreate);

   }

   ::estatus     session::do_request(::create * pcreate)
   {

      return ::acme::session::do_request(pcreate);

   }


   bool session::open_by_file_extension(const char * pszPathName, ::create * pcreate)
   {

      auto pcreateNew = __create_new < ::create >();

      pcreateNew->m_pcommandline->m_varFile = pszPathName;

      pcreateNew->m_puserinteractionParent = pcreate->m_puserinteractionParent;

      return open_by_file_extension(pcreateNew);

   }


   bool session::open_by_file_extension(::create * pcreate)
   {

      string strId;

      string strOriginalPathName(pcreate->m_pcommandline->m_varFile);

      ::file::path strPathName(strOriginalPathName);

      strsize iFind = strPathName.find("?");

      if(iFind >= 0)
      {

         strPathName = strPathName.Left(iFind);

      }

      if(::str::ends_ci(strPathName, ".ca2"))
      {

      }

      string strProtocol = System.url().get_protocol(strPathName);

      if(strProtocol == "app")
      {

         strId = System.url().get_server(strPathName);

         string str = System.url().get_object(strPathName);

         ::str::begins_eat(str, "/");

         pcreate->m_pcommandline->m_varFile = str;

      }
      else
      {

         string strExtension = strPathName.extension();

         string_array straApp;

         System.filehandler().get_extension_app(straApp, strExtension);

         if(straApp.get_count() == 1)
         {

            strId = straApp[0];

         }
         else
         {

            strId = "app/sphere/default_file_handler";

         }

      }

      ::acme::application * papp = application_get(strId, true, true, pcreate);

      if (papp == nullptr)
      {

         return false;

      }

      papp->do_request(pcreate);

      return true;

   }


   session::run_application::run_application()
   {

   }

   //   void session::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
   //   {
   //
   //      if(eexclusive == ExclusiveInstanceLocalId)
   //      {
   //         /*
   //         ::memory_file file(get_object());
   //         file.from_string(m_varTopicFile);
   //         COPYDATASTRUCT data;
   //         data.dwData = 2000;
   //         data.cbData = (u32) file.get_length();
   //         data.pData = file.get_data();

   //         oswindow oswindow = ::FindWindowA(nullptr, "::draw2d::account::message_wnd::session::");
   //
   //         ::SendMessage(oswindow, WM_COPYDATA, nullptr, (LPARAM) &data);*/
   //
   //#if defined(WINDOWS_DESKTOP) || defined(LINUX) || defined(APPLEOS)
   //
   //         ::acme::ipc::tx channel;
   //
   //         if(channel.open("::draw2d::account::message_wnd::session::"))
   //         {
   //            channel.send(m_varTopicFile, false);
   //            channel.close();
   //         }
   //
   //#else
   //
   //          __throw(todo());
   //
   //#endif
   //
   //
   //      }
   //
   //   }
   //
//
//   void session::request(::create * pcreate)
//   {
//
//      ::acme::session::do_request(pcreate);
//
//   }


   void session::request_topic_file(payload & varQuery)
   {

      request_file(psession->m_varTopicFile, varQuery);

   }


   void session::request_topic_file()
   {

      request_file(psession->m_varTopicFile);

   }


   /*void session::request_application(const char * pszId, payload varFile, payload varQuery, application_bias * papplicationbias)
   {

   ::acme::application_request request;

   request.m_iEdge         = m_iEdge;
   request.m_strApp        = pszId;
   request.m_varFile       = varFile;
   request.m_varQuery      = varQuery;
   request.m_papplicationbias   = papplicationbias;

   request_application(&request);

   }*/
   /*
   __pointer(::acme::application) session::application_get(const char * pszType, const char * pszId, bool bCreate, bool bSynch, application_bias * papplicationbias)
   {
   ::acme::application * papp = nullptr;

   if(m_mapApplication.lookup(string(pszType) + ":" + string(pszId), papp))
   return papp;
   else
   {

   if(!bCreate)
   return nullptr;

   papp = nullptr;

   try
   {

   papp = create_application(pszType, pszId, bSynch, papplicationbias);

   }
   catch(::exit_exception & e)
   {

   __throw(e);

   }
   catch(::exception::exception &)
   {

   if(!Application.on_run_exception(e))
   __throw(exit_exception());

   }
   catch(...)
   {

   papp = nullptr;

   }

   if(papp == nullptr)
   return nullptr;

   m_mapApplication.set_at(string(pszType) + ":" + string(pszId), papp);
   return papp;
   }
   }
   */


   bool session::is_session() const
   {

      return true;

   }


   __pointer(::acme::application) session::get_current_application()
   {
      return psession->m_pappCurrent;
   }




   //bool session::on_install()
   //{

   //   string strFormat;

   //   string strSentinelPath;

   //   strSentinelPath = Context.dir().install() / "stage/x86/app.sentinel.exe";

   //   Context.os().local_machine_set_run("acme app.sentinel", "\"" + strSentinelPath + "\"", true);

   //   Context.os().defer_register_ca2_plugin_for_mozilla();

   //   //return ::acme::application::on_install();
   //   return acme::session::on_install();

   //}




   bool session::is_remote_session()
   {


      return Context.os().is_remote_session();


   }


   bool session::is_mouse_button_pressed(::user::enum_mouse emouse)
   {

      if(emouse == ::user::e_mouse_left_button)
      {
         return psession->is_key_pressed(::user::key_lbutton);
      }
      else if(emouse == ::user::e_mouse_right_button)
      {
         return psession->is_key_pressed(::user::key_rbutton);
      }
      else if(emouse == ::user::e_mouse_middle_button)
      {
         return psession->is_key_pressed(::user::key_mbutton);
      }
      else
      {
         __throw(::exception::exception("not expected e_mouse value"));
      }


   }






   bool session::open_file(::filemanager::data * pdata, ::file::item_array & itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      if(itema.get_size() > 0)
      {

         return true;

      }

      return false;

   }








   bool session::InitializeLocalDataCentral()
   {

      //m_pdatabase = new nature::database(this);

      //if(m_pdatabase == nullptr)
      //{
      //   TRACE("VmpLightApp::init_instance failed to instatiate LightDB\n");
      //   return false;
      //}

      //if(!m_pdatabase->Initialize())
      //{
      //   TRACE("VmpLightApp::init_instance failed to initialize LightDB\n");
      //   return false;
      //}

      return true;

   }


//   bool session::on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strid)
//   {
//      if(eexclusive == ExclusiveInstanceLocalId)
//      {
//#ifdef WINDOWS_DESKTOP
//         ::memory_file file(get_object());
//         file.from_string(m_varTopicFile);
//         COPYDATASTRUCT data;
//         data.dwData = 2000;
//         data.cbData = (u32) file.get_length();
//         data.lpData = file.get_data();
//
//         ::oswindow oswindow = ::FindWindowA(nullptr, "::draw2d::account::message_wnd::bergedge::");
//
//
//         ::SendMessage(oswindow, WM_COPYDATA, 0, (LPARAM) &data);
//
//         return true;
//
//#else
//
//         __throw(todo());
//
//#endif
//
//      }
//
//      return false;
//
//   }


   /*void session::request_application(const char * pszId, payload varFile, payload varQuery, application_bias * papplicationbias)
   {

   ::acme::application_request request;

   request.m_iEdge         = m_iEdge;
   request.m_strApp        = pszId;
   request.m_varFile       = varFile;
   request.m_varQuery      = varQuery;
   request.m_papplicationbias   = papplicationbias;

   request_application(&request);

   }*/

   
   void session::check_topic_file_change()
   {

      if(psession->m_varCurrentViewFile != psession->m_varTopicFile && !psession->m_varTopicFile.is_empty())
      {

         psession->m_varCurrentViewFile = psession->m_varTopicFile;

         request_topic_file();

      }

   }


   //::user::place_holder_ptra session::get_place_holder(__pointer(::user::frame_window) pmainframe, ::create * pcreate)
   //{

   //   UNREFERENCED_PARAMETER(pcreate);

   //   ::user::place_holder_ptra holderptra;


   //   ::acme::application & app = App(pmainframe->get_context_application());

   //   string strAppName = app.m_strAppName;

   //   //if(get_document()->get_typed_view < ::bergedge::pane_view >() != nullptr)
   //   //{

   //   //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName)));

   //   //}
   //   //else
   //   //{

   //   //   holderptra.add(get_document()->get_typed_view < ::bergedge::view >());

   //   //}

   //   return holderptra;

   //}

   bool session::place(::user::main_frame * pmainframe, ::create * pcreate)
   {

      //get_place_holder(pmainframe, pcreate).hold(pmainframe);

      return true;

   }





   void session::set_app_title(const char * pszAppId, const char * pszTitle)
   {

      __pointer(::acme::application) papp;

      if(m_applicationa.lookup(pszAppId, papp) && papp)
      {

         //__pointer(::bergedge::pane_view) ppaneview = get_document()->get_typed_view < ::bergedge::pane_view >();

         //if(ppaneview != nullptr)
         //{

         //   string strAppName(pszAppId);

         //   ::user::tab::pane * ppane = ppaneview->get_pane_by_id("app:" + strAppName);

         //   if(ppane != nullptr)
         //   {

         //      ppane->m_istrTitleEx = pszTitle;

         //      ppaneview->on_layout(::draw2d::graphics_pointer & pgraphics);

         //   }

         //}

      }

   }



   __pointer(::acme::session) session::get_context_session()
   {

      return this;

   }



//   bool session::is_serviceable() const
//   {
//
//
////      return ::session::application::is_serviceable();
//      return false;
//
//
//   }


   //bool session::on_uninstall()
   //{


   //   bool bOk1 = true;
   //   bool bOk2 = true;

   //   try
   //   {

   //      bOk1 = ::acme::session::on_uninstall();

   //   }
   //   catch(...)
   //   {
   //      bOk1 = false;
   //   }




   //   return bOk1 && bOk2;


   //}


   //::estatus session::os_native_bergedge_start()
   //{

   //   if (!::acme::application::os_native_bergedge_start())
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //service_base * session::allocate_new_service()
   //{


   //   return ::acme::application::allocate_new_service();


   //}





   ::draw2d::cursor * session::get_default_cursor()
   {

      return System.draw2d().get_cursor(m_ecursorDefault);

   }


   ::estatus     session::main()
   {

      return ::acme::session::main();

   }


   //::acme::session * session::query_bergedge()
   //{

   //   ::acme::session * psession = nullptr;

   //   if(System.m_pbergedgemap == nullptr)
   //      return nullptr;

   //   if(!System.m_pbergedgemap->lookup(0,psession))
   //   {
   //      return nullptr;
   //   }

   //   return psession;

   //}


   void session::on_user_logon(::account::user * puser)
   {

      ::acme::session::on_user_logon(puser);

   }


   void session::interactive_credentials(::account::credentials * pcredentials)
   {


      pcredentials->m_estatus = error_failed;

      manual_reset_event ev;

      if (!pcredentials->m_bInteractive)
      {

         pcredentials->m_estatus = error_credentials_non_interactive;

         return;

      }

      //if (m_pmainpane != nullptr && m_pmainpane == nullptr)
      //{

      //   try
      //   {

      //      m_pmainpane->interactive_credentials(pcredentials);

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      if(pcredentials->m_estatus == ::success_credentials ||
            ::failed(pcredentials->m_estatus, STATUS_RANGE_AUTHENTICATION))
      {

         return;

      }

#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID)
      //attach_thread_input_to_main_thread(false);
#endif

      ::acme::session::interactive_credentials(pcredentials);

      if (pcredentials->m_estatus == ::success_credentials)
      {

         return;

      }

      if (!pcredentials->m_bInteractive)
      {

         pcredentials->m_estatus = error_credentials_non_interactive;

         return;

      }

      auto puser = pcredentials->m_puser;

      auto pdialog = ::__create_new<::account::dialog>();

      pdialog->initialize_account_dialog(pcredentials);

      pdialog->get_credentials();

      pdialog->DestroyWindow();


   }


   void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect & rect, ::draw2d::brush_pointer & brushText)
   {

      string_array & straTitle = pane.m_straTitle;

      pgraphics->SelectObject(brushText);

      if (straTitle.get_count() <= 1)
      {

         pgraphics->_DrawText(pane.get_title(), recte_bottom_left, e_draw_text_no_prefix);

      }
      else
      {

         ::rect rectText(rect);


         ::draw2d::font_pointer font;
         font = pgraphics->get_current_font();
         size sSep = ptab->get_data()->m_sizeSep;
         ::rect rectEmp;
         for (index i = 0; i < straTitle.get_size(); i++)
         {
            string str = straTitle[i];
            size s = pane.m_sizeaText[i];
            rectText.right = rectText.left + s.cx;
            pgraphics->_DrawText(str, rectTexte_bottom_left, e_draw_text_no_prefix);
            rectText.left += s.cx;
            if (i < straTitle.get_upper_bound())
            {
               rectText.right = rectText.left + sSep.cx;
               rectEmp = rectText;
               rectEmp.deflate(1, 1);
               ::draw2d::enum_alpha_mode emode = pgraphics->m_ealphamode;
               pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
               if (ptab->m_itemHover == (::user::enum_element)(::user::e_element_split + i))
               {
                  pgraphics->fill_rect(rectEmp, ARGB(128, 150, 184, 255));
                  pgraphics->SelectObject(ptab->get_data()->m_brushTextHover);
               }
               else
               {
                  //pgraphics->fill_rect(rectEmp,ARGB(128,208,223,233));
                  pgraphics->SelectObject(ptab->get_data()->m_brushText);
               }
               pgraphics->set_font(ptab->_001GetFont(::user::font_tab_big_bold));
               pgraphics->set_alpha_mode(emode);
               pgraphics->_DrawText(MAGIC_PALACE_TAB_TEXT, rectText, e_align_center, e_draw_text_no_prefix);
               rectText.left += sSep.cx;
               pgraphics->selectFont(font);
               pgraphics->SelectObject(brushText);
            }
         }

      }

   }


   string_array session::get_user_wallpaper()
   {

      string_array stra;

      string_array straSource = psession->userex()->get_wallpaper();

      for(string str : straSource)
      {

         if(::str::begins_eat_ci(str, "file://"))
         {

            str = System.url().url_decode(str);

         }

         stra.add(str.c_str());

      }

      return stra;

   }




   //bool session::initialize_filemanager()
   //{

   //   if (m_pfilemanager == nullptr)
   //   {

   //      m_pfilemanager = __new(::filemanager::department(this));

   //      m_pfilemanager->construct(this);

   //      if (!m_pfilemanager->initialize())
   //      {

   //         return false;

   //      }



   //   }

   //   return true;

   //}


    __pointer(::user::document) session::create_form(::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload, ::payload varArgs)
    {

       return Sess(this).userex()->create_form(
          pcallback ? pcallback : pwndParent ? pwndParent : this, 
          pcallback, pwndParent, payload, varArgs);

    }


    __pointer(::user::document) session::create_form(::type point, __pointer(::user::interaction) pwndParent, payload payload, ::payload varArgs)
    {

       return Sess(this).userex()->create_form(this, point, pwndParent, payload, varArgs);

    }


    __pointer(::user::document) session::create_form(__pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload, ::payload varArgs)
    {

       return Sess(this).userex()->create_form(this, pview, pcallback, pwndParent, payload, varArgs);

    }


    __pointer(::user::document) session::create_child_form(::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload, ::payload varArgs)
    {

       return Sess(this).userex()->create_child_form(
          pcallback ? pcallback : pwndParent ? pwndParent : this,
          pcallback, pwndParent, payload, varArgs);


    }


    __pointer(::user::document) session::create_child_form(::type point, __pointer(::user::interaction) pwndParent, payload payload)
    {

       return Sess(this).userex()->create_child_form(this, point, pwndParent, payload);

    }


    __pointer(::user::document) session::create_child_form(__pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload)
    {

       return Sess(this).userex()->create_child_form(this, pview, pcallback, pwndParent, payload);

    }




    //session::session()
    //{

    //}


    //session::~session()
    //{


    //}


    //::estatus session::initialize(::matter* pobjectContext)
    //{

    //   auto estatus = ::acme::session::initialize(pobjectContext);

    //   if (!estatus)
    //   {

    //      return estatus;

    //   }


    //   //m_strAppId = "base_session";
    //   //m_strAppName = "base_session";
    //   //m_strBaseSupportId = "base_session";
    //   //m_strInstallToken = "base_session";

    //   m_iMainMonitor = -1;

    //   m_puiCapture = nullptr;

    //   m_puiMouseMoveCapture = nullptr;

    //   m_ecursorDefault = cursor_arrow;

    //   m_ecursor = cursor_default;

    //   m_puiMouseMoveCapture = nullptr;

    //   m_psavings = __new(class ::acme::savings(this));

    //   m_pcopydesk = nullptr;

    //   return estatus;

    //}


    //::estatus session::process_init()
    //{

    //   //m_himc = ImmCreateContext();

    //   INFO(".1");

    //   if (!::acme::session::process_init())
    //   {

    //      ERR(".2");

    //      return false;

    //   }

    //   //if (!::acme::application::process_init())
    //   //{

    //   //   ERR(".3");

    //   //   return false;

    //   //}

    //   //m_puser = create_user();

    //   //if (m_puser == nullptr)
    //   //{

    //   //   ERR(".4");

    //   //   return false;

    //   //}

    //   //m_puser->add_ref(OBJ_REF_DBG_ARGS);

    //   auto estatus = __construct(m_puser);

    //   if (!estatus || !m_puser)
    //   {

    //      ERR(".4");

    //      return false;

    //   }

    //   INFO("end");

    //   return true;

    //}


    //::estatus session::init1()
    //{


    //   if (!::acme::session::init1())
    //      return false;

    //   //if (!::acme::application::init1())
    //     // return false;

    //   //if (m_puserstyle.is_null())
    //   //{
    //   //
    //   //   defer_create_user_style(preferred_experience());
    //   //
    //   //}

    //   if (!m_puser->init1())
    //      return false;

    //   if (!m_puser->init2())
    //      return false;


    //   return true;

    //}


    //::estatus session::init()
    //{

    //   if (!::acme::session::init())
    //   {

    //      return false;

    //   }

    //   //if (!::acme::application::init())
    //   //{

    //   //   return false;

    //   //}

    //   if (!m_puser->init())
    //   {

    //      return false;

    //   }

    //   ::set_message_box(&::simple_ui_message_box);

    //   return true;

    //}


    //void session::term_session()
    //{

    //   //::acme::application::term_application();

    //   ::acme::session::term_session();

    //   try
    //   {

    //      m_puser->term();

    //   }
    //   catch (...)
    //   {

    //   }


    //   m_puser.release();

    //}




    bool session::prepare_menu_button(::user::menu_item* pitem)
    {

       __pointer(::user::button) pbutton = pitem->m_puserinteraction;

       if (pbutton->m_id == "close_menu")
       {

          pbutton->m_econtroltype = ::user::e_control_type_menu_button_close;

          pbutton->set_stock_icon(stock_icon_close);

          pbutton->resize_to_fit();

          return true;

       }
       else
       {

          pbutton->m_econtroltype = ::user::e_control_type_menu_button;

          int cx = pbutton->width();

          int cy = pbutton->height();

          pbutton->m_pmenuitemThis = pitem;

          ::rect rectMargin = pbutton->_001GetRect(::user::rect_menu_margin);

          int iCheckBoxSize = pbutton->_001GetInt(::user::int_check_box_size);

          int iElementPadding = pbutton->_001GetInt(::user::int_element_padding);

          auto& rectCheckBox = pbutton->m_rectCheckBox;

          rectCheckBox.left = rectMargin.left;
          rectCheckBox.top = rectMargin.top;
          rectCheckBox.bottom = cy - rectMargin.bottom;
          rectCheckBox.right = rectCheckBox.left + iCheckBoxSize;

          auto& rectText = pbutton->m_rectText;

          rectText.left = rectCheckBox.right + iElementPadding;
          rectText.top = rectMargin.top;
          rectText.bottom = cy - rectMargin.bottom;
          rectText.right = cx - rectMargin.right;

       }

       return true;

    }



    void session::frame_pre_translate_message(::message::message* pmessage)
    {

       if (pmessage->m_id == WM_GETTEXT
          || pmessage->m_id == WM_GETTEXTLENGTH
          )
       {

          pmessage->m_uiMessageFlags |= 3; // message considered pre translated
          pmessage->m_uiMessageFlags |= 16384; //  by early optmization

          return;

       }
       //else if (pmessage->m_id == e_message_mouse_move)
       //{

       //   pmessage->m_uiMessageFlags |= 0; // message considered pre translated
       //   pmessage->m_uiMessageFlags |= 16384; //  by early optmization

       //   return;

       //}

       //try
       //{

       //   __pointer(::user::interaction) pinteraction;

       //   while (get_frame(pinteraction))
       //   {

       //      try
       //      {

       //         if (pinteraction != nullptr)
       //         {

       //            pinteraction->pre_translate_message(pmessage);

       //            if (pmessage->m_bRet)
       //               return;

       //         }

       //      }
       //      catch (exception_pointer e)
       //      {

       //         if (e.is < ::exit_exception>())
       //         {

       //            __rethrow(::move(e));

       //         }

       //      }
       //      catch (...)
       //      {
       //      }

       //   }

       //}
       //catch (exception_pointer e)
       //{

       //   if (e.is < ::exit_exception>())
       //   {

       //      __rethrow(::move(e));

       //   }

       //}
       //catch (...)
       //{

       //   pmessage->m_bRet = true;

       //}

    }


    /*void session::interactive_credentials(::account::credentials* pcredentials)
    {

       ::acme::session::interactive_credentials(pcredentials);

       if (pcredentials->m_estatus == ::success_credentials)
       {

          return;

       }

       if (!pcredentials->m_bInteractive)
       {

          pcredentials->m_estatus = error_credentials_non_interactive;

          return;

       }

       auto puser = pcredentials->m_puser;

       auto pdialog = ::__create_new<::account::dialog>();

       pdialog->initialize_account_dialog(pcredentials);

       pdialog->get_credentials();

       pdialog->DestroyWindow();

    }*/


    //__pointer(::user::impact) session::get_view()
    //{

    //   return nullptr;

    //}


    //void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect& rect, ::draw2d::brush_pointer& brushText)

    //{

    //   __throw(interface_only_exception());

    //}


    void session::on_finally_focus_set(::user::primitive* pelementalFocus)
    {

       user()->set_mouse_focus_LButtonDown(pelementalFocus);

       acme::session::on_finally_focus_set(pelementalFocus);

    }


    bool session::on_ui_mouse_message(::message::mouse* pmouse)
    {

       ::acme::session::on_ui_mouse_message(pmouse);

       if (m_puserpresence.is_set())
       {

          m_puserpresence->on_ui_mouse_message(pmouse);

       }

       return true;

    }


} // namespace acme



