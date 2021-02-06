#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/simple/_simple.h"
#include "base/user/menu/_menu.h"
#endif
#include "aura/update.h"
#include "simple_view.h"
#include "apex/platform/static_setup.h"


namespace base
{


   user::user()
   {

      m_pbaseuser = this;
      m_pcoreuser = nullptr;
      //m_pufeschema = nullptr;
      //m_pufe = nullptr;


   }


   user::~user()
   {

   }


   ::e_status user::initialize(::layered * pobjectContext)
   {

      auto estatus = ::axis::user::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      estatus = ::user::document_manager_container::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status user::init1()
   {


      create_factory <::user::document >();
      create_factory <::user::message_queue >();
      create_factory <::user::simple_view >();
      create_factory <::user::still >();
      create_factory <::user::combo_box >();
      create_factory <::user::place_holder >();
      //create_factory <::user::font_combo_box >();

      ////if(get_context_application()->is_system())
      //{

      //   create_factory <keyboard_layout >();

      //}

      if (!::axis::user::init1())
      {

         return false;

      }

      if (!initialize1_experience())
      {

         return false;

      }

      return true;

   }


   ::e_status user::init()
   {

      if (!::axis::user::init())
      {

         return false;

      }

      create_factory <::simple_scroll_bar, ::user::scroll_bar>();

      create_factory <::user::menu_item >();
      create_factory <::user::menu >();
      create_factory <::user::menu_list_view >();


      create_factory < ::user::split_layout  >();
      create_factory < ::user::split_bar  >();


      create_factory < simple_frame_window  >();
      //create_factory < prodevian_translucent_simple_frame_window  >();
      create_factory < simple_main_frame  >();
      create_factory < ::user::document  >();
      create_factory < ::user::split_view  >();


      auto estatus = __compose_new(m_pmenucentral);

      if (!estatus)
      {

         return estatus;

      }

      //auto estatus = create_user_shell();

      //if (!estatus)
      //{

      //   return estatus;

      //}



      TRACE("::user::application::initialize");

      //xml::document docUser;

      //string strUser = Context.file().as_string(Context.dir().appdata()/"langstyle_settings.xml");

      //string strLangUser;

      //string strStyleUser;

      //if(docUser.load(strUser))
      //{

      //   if(docUser.get_child("lang") != nullptr)
      //   {

      //      strLangUser = docUser.get_child("lang")->get_value();

      //   }

      //   if(docUser.get_child("style") != nullptr)
      //   {

      //      strStyleUser = docUser.get_child("style")->get_value();

      //   }

      //}

      //if(strLangUser.has_char())
      //   psession->set_locale(strLangUser,::e_source_database);

      //if(strStyleUser.has_char())
      //   psession->set_schema(strStyleUser,::e_source_database);

      //string strLicense = Application.get_license_id();


      //::payload & varTopicQuey = System.commnam_varTopicQuery;

      bool bHasInstall = System.is_true("install");

      bool bHasUninstall = System.is_true("uninstall");

      debug_print("user::initialize bHasInstall %c", bHasInstall);

      debug_print("user::initialize bHasUninstall %c", bHasUninstall);

      return true;

   }


   ::e_status user::init2()
   {

      if (!::apex::department::init2())
      {

         return false;

      }

      return true;

   }


   void user::term()
   {


      //pstyle.release();
//      ::acme::del(m_pufeschema);
//
//      ::acme::del(m_pufe);


      try
      {

         ::apex::department::term();

      }
      catch(...)
      {

      }


      try
      {

         __release(m_pmenucentral);

      }
      catch (...)
      {

      }

   }


   void user::finalize()
   {

      for (auto& style : m_mapUserStyle.values())
      {

         __finalize(style);

      }

      m_mapUserStyle.remove_all();

      ::axis::user::finalize();

   }


   ::user::primitive * user::get_mouse_focus_LButtonDown()
   {

      return m_pmousefocusLButtonDown;

   }


   void user::set_mouse_focus_LButtonDown(::user::primitive * pmousefocus)
   {

      m_pmousefocusLButtonDown = pmousefocus;

   }


   ::user::primitive * user::get_mouse_focus_RButtonDown()
   {

      return m_pmousefocusRButtonDown;

   }


   void user::set_mouse_focus_RButtonDown(::user::primitive * pmousefocus)
   {

      m_pmousefocusRButtonDown = pmousefocus;

   }


   void user::SendMessageToWindows(const ::id & id,wparam wparam,lparam lparam)
   {

      auto psession = Session;

      for (auto& papp : psession->m_applicationa)
      {

         auto & app = App(papp);

         sync_lock sl(&app.m_mutexFrame);

         __pointer(::user::interaction) pinteraction;

         while (app.get_frame(pinteraction))
         {

            if (pinteraction != nullptr && pinteraction->is_window())
            {

               pinteraction->send_message(id, wparam, lparam);

               pinteraction->send_message_to_descendants(id, wparam, lparam);

            }

         }

      }

   }


//   ::user::front_end_schema * GetUfeSchema(::layered * pobjectContext)
//   {
//
//      if (papp == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      if (papp->m_psession == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      if (papp->m_psession->m_puser == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      return Sess(papp).user()->GetUfeSchema();
//
//   }
//
//
//   ::user::front_end * GetUfe(::layered * pobjectContext)
//   {
//
//      return Sess(papp).user()->GetUfe();
//
//   }


//   ::user::front_end_schema * user::GetUfeSchema()
//   {
//
//      return m_pufeschema;
//
//   }
//
//
//   ::user::front_end * user::GetUfe()
//   {
//
//      return m_pufe;
//
//   }


   ::type user::controltype_to_typeinfo(::user::enum_control_type econtroltype)
   {

      return ::type();

   }


   __pointer(::user::menu_interaction) user::create_menu_button(::user::style* pstyle, ::user::menu_item* pitem)
   {

      auto pinteraction = __new(::user::menu_button(pitem));

      if (pitem->m_pimage->is_set())
      {

         pinteraction->set_button_style(::user::button::style_image_and_text);

         enum_image eimage = (enum_image)pitem->m_pmenu->payload("image_transform").i32();

         ::image_pointer pimage = pitem->m_pimage + eimage;

         pinteraction->LoadBitmaps(pimage);

      }

      return pinteraction;

   }


//   __pointer(::user::impact) user::get_view()
//   {
//
//      return nullptr;
//
//   }


//   ::user::style * user::get_user_style()
//   {
//
//      retu
//
//   }


#ifdef WINDOWS_DESKTOP


   CLASS_DECL_BASE __pointer(::user::interaction) create_virtual_window(::object * pobject, u32 dwExStyle, const char * pClassName, const char * lpWindowName, u32 uStyle, const ::rectangle_i32 & rectangle, ::user::interaction * puiParent, id id, HINSTANCE hInstance, LPVOID pParam);


   CLASS_DECL_BASE __pointer(::user::interaction) create_virtual_window(::object * pobject, u32 dwExStyle, const char * pClassName, const char * pWindowName, u32 uStyle, ::user::interaction * puiParent, HINSTANCE hInstance, LPVOID pParam)
   {

      UNREFERENCED_PARAMETER(dwExStyle);
      UNREFERENCED_PARAMETER(pClassName);
      UNREFERENCED_PARAMETER(pWindowName);
      UNREFERENCED_PARAMETER(uStyle);
      UNREFERENCED_PARAMETER(hInstance);
      UNREFERENCED_PARAMETER(pParam);

      auto pinteraction = __new(::user::interaction);

      if(pinteraction->create_child(puiParent))
      {

         return pinteraction;

      }

      pinteraction.release();

      return nullptr;

   }


#endif


} // namespace user


namespace base
{


   //void application::close(::aura::e_end eend)
   //{

   //   try
   //   {

   //      if (m_pdocmanager.is_set())
   //      {

   //         m_pdocmanager->close_all_documents(eend != ::aura::end_close);

   //      }

   //   }
   //   catch (...)
   //   {


   //   }

   //   if (eend == ::aura::end_close)
   //   {

   //      return;

   //   }

   //   m_ethreadClose = thread_application;

   //   if (get_context_session())
   //   {

   //      if (psession->m_pdocmanager)
   //      {

   //         psession->m_pdocmanager->close_all_documents(true);

   //      }

   //   }

   //   if (eend == ::aura::end_app)
   //   {

   //      finish();

   //      return;

   //   }

   //   if (eend == ::aura::end_session)
   //   {

   //      try
   //      {

   //         if (get_context_session())
   //         {

   //            psession->finish();

   //         }

   //      }
   //      catch (...)
   //      {

   //      }

   //      return;

   //   }


   //   if (eend == ::aura::end_system)
   //   {

   //      try
   //      {

   //         if (get_context_system())
   //         {

   //            System.finish();

   //         }

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //}


   //session_docs::session_docs()
   //{

   //   m_pnaturedocument = nullptr;
   //   m_pplatformdocument = nullptr;
   //   m_pbergedgedocument = nullptr;


   //}


   //session_docs::~session_docs()
   //{

   //   close_all_documents();

   //}


   //void session_docs::close_all_documents()
   //{

   //   if (m_pnaturedocument != nullptr)
   //   {

   //      m_pnaturedocument.cast < ::user::document>()->on_close_document();

   //   }

   //   if (m_pplatformdocument != nullptr)
   //   {

   //      m_pplatformdocument.cast < ::user::document>()->on_close_document();

   //   }

   //   if (m_pbergedgedocument != nullptr)
   //   {

   //      m_pbergedgedocument.cast < ::user::document>()->on_close_document();

   //   }

   //}


   //session_docs * create_session_docs()
   //{

   //   return new session_docs();

   //}


   //void destroy_session_docs(session_docs * pdocs)
   //{

   //   ::acme::del(pdocs);

   //}


   //::draw2d::font_list * session::get_single_column_font_list()
   //{

   //   if (m_pfontlistSingleColumn.is_null())
   //   {

   //      __compose(m_pfontlistSingleColumn, __create_new < ::draw2d::font_list > ());

   //      m_pfontlistSingleColumn->m_etype = ::draw2d::font_list::type_single_column;

   //      m_pfontlistSingleColumn->set_need_layout();

   //   }

   //   return m_pfontlistSingleColumn;

   //}


//   void session::on_app_request_bergedge_callback(::layered * pobjectContext)
//   {
//
//      if (&App(pobject) != nullptr)
//      {
//
//         psession->m_pappCurrent = &App(pobject);
//
//      }
//
//      if (psession->m_bShowPlatform)
//      {
//         //__pointer(::simple_frame_window) pframeApp = get_document()->get_typed_view < ::bergedge::pane_view >()->get_view_uie();
//         //if(pframeApp != nullptr)
//         //{
//         //   pframeApp->display(e_display_full_screen);
//         //}
//         //__pointer(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::pane_view >()->get_parent_frame();
//         //if(pframe != nullptr)
//         //{
//         //   pframe->display(e_display_normal);
//         //}
//      }
//      else
//      {
//         //if(get_document() != nullptr && get_document()->get_typed_view < ::bergedge::view >() != nullptr)
//         //{
//         //   __pointer(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::view >()->get_parent_frame();
//         //   if(pframe != nullptr)
//         //   {
//         //      pframe->display(e_display_normal);
//         //      if(pframe->GetTypedParent < ::plugin::host_interaction > () != nullptr)
//         //      {
//         //         pframe->GetTypedParent < ::plugin::host_interaction > ()->on_layout(::draw2d::graphics_pointer & pgraphics);
//         //      }
//         //      else
//         //      {
//         //         pframe->InitialFramePosition();
//         //      }
//         //   }
//         //}
//      }
//
////      if (psession->m_pappCurrent != nullptr && psession->m_pappCurrent->m_psession->m_paccount->m_puser != nullptr)
////      {
////         try
////         {
////            get_view()->get_parent_frame()->set_window_text(psession->m_pappCurrent->m_psession->m_paccount->m_puser->m_strLogin);
////         }
////         catch (...)
////         {
////         }
////      }
//
//   }


   //__pointer(::user::document) session::get_document()
   //{

   //   //return m_pdocs->m_pbergedgedocument;
   //   return nullptr;

   //}


   //__pointer(::user::impact) session::get_view()
   //{

   //   if (get_document() == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return nullptr;

   //}


   //__pointer(::user::document) session::get_platform()
   //{
   //   //return m_pdocs->m_pplatformdocument;
   //   return nullptr;
   //}

   //__pointer(::user::document) session::get_nature()
   //{
   //   //return m_pdocs->m_pnaturedocument;
   //   return nullptr;
   //}

   //bool session::get_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle)

   //{

   //   if (get_document() != nullptr && get_view() != nullptr)
   //   {

   //      get_view()->get_window_rect(prectangle);


   //      return true;

   //   }
   //   else
   //   {

   //      return ::aura::session::get_monitor_rect(iMonitor, prectangle);


   //   }

   //}
   //::type system::get_simple_frame_window_type_info()
   //{

   //   return ::type();

   //}





   //::count session::get_monitor_count()
   //{

   //   if (get_document() != nullptr && get_view() != nullptr)
   //   {

   //      return 1;

   //   }
   //   else
   //   {

   //      return ::aura::session::get_monitor_count();

   //   }

   //}


//   ::user::interaction * session::get_request_parent_ui(::user::interaction * pinteraction, ::create * pcreate)
//   {
//
//
//      ::user::interaction * puiParent = nullptr;
//
//      if (pcreate->m_pcommandline->m_varQuery["uicontainer"].cast < ::user::interaction >() != nullptr)
//         puiParent = pcreate->m_pcommandline->m_varQuery["uicontainer"].cast < ::user::interaction >();
//
//      if (puiParent == nullptr && pcreate->m_puserinteractionParent != nullptr)
//      {
//         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_puserinteractionParent);
//      }
//
////      if (puiParent == nullptr && pcreate != nullptr)
////      {
////         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_puserinteractionParent);
////      }
//
////      if (puiParent == nullptr && pcreate->m_papplicationbias.is_set())
////      {
////         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_papplicationbias->m_puserinteractionParent);
////      }
//
//
//      /*      if(pinteraction == nullptr && m_puiInitialPlaceHolderContainer != nullptr)
//      {
//      pinteraction = m_puiInitialPlaceHolderContainer;
//      }*/
//
//      /*      if(pinteraction == nullptr && m_bShowPlatform && m_pbergedge->get_document() != nullptr)
//      {
//      pinteraction = psession->get_document()->get_bergedge_view();
//      }
//
//      return pinteraction;
//
//      }*/
//
//      if (pcreate->m_bClientOnly ||
//            Application.has_property("client_only") ||
//            pcreate->m_bOuterPopupAlertLike)
//      {
//         return puiParent;
//      }
//
//
//      //bool bCreateBergedge = false;
//
//      //if(bCreateBergedge)
//      //{
//
//      //   if(!create_bergedge(pcreate))
//      //   {
//      //      return nullptr;
//
//
//      //   }
//
//      //}
//
//
//
//
//      ::aura::application & app = App(pinteraction->get_context_application());
//
//      string strAppName = app.m_strAppName;
//
//      if (strAppName != "bergedge")
//      {
//
//         if (get_document() != nullptr)
//         {
//
//            //if(get_document()->get_typed_view < ::bergedge::pane_view >() != nullptr)
//            //{
//
//            //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);
//
//            //   puiParent = get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName));
//
//            //}
//            //else
//            //{
//
//            //   puiParent = get_document()->get_typed_view < ::bergedge::view >();
//
//            //}
//
//         }
//
//      }
//
//      return puiParent;
//
//   }

//} // namespace base
//
//
//namespace user
//{

   //run_application::run_application()
   //{

   //}

   //bool is_descendant(::user::interaction* puiParent, ::user::interaction* pinteraction)
   //   // helper for detecting whether child descendent of parent
   //   //  (works with owned popups as well)
   //{

   //   if (pinteraction == nullptr)
   //      return false;

   //   ::user::interaction* puiAscendant = pinteraction;

   //   do
   //   {

   //      puiAscendant = puiAscendant->get_owner();


   //      if (puiParent == puiAscendant)
   //         return true;

   //   } while (puiAscendant != nullptr);


   //   puiAscendant = pinteraction;

   //   do
   //   {

   //      puiAscendant = puiAscendant->get_parent();


   //      if (puiParent == puiAscendant)
   //         return true;

   //   } while (puiAscendant != nullptr);


   //   return false;

   //}

   bool user::track_popup_menu(::user::interaction* pinteraction, ::user::menu_item * pitem, i32 iFlags)
   {

      ::point_i32 point;

      auto psession = Session;

      psession->get_cursor_pos(point);

      return track_popup_menu(pinteraction, pitem, iFlags, point);

   }


   __pointer(::user::menu) user::track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags)
   {

      auto psession = Session;

      auto point = psession->get_cursor_pos();

      return track_popup_xml_menu(pinteraction, strXml, iFlags, point);

   }


   __pointer(::user::menu) user::track_popup_xml_matter_menu(::user::interaction* pinteraction, const char * pszMatter, i32 iFlags)
   {

      auto psession = Session;

      auto point = psession->get_cursor_pos();

      return track_popup_xml_matter_menu(pinteraction, pszMatter, iFlags, point);

   }



   bool user::track_popup_menu(::user::interaction* pinteraction, ::user::menu_item * pitem, i32 iFlags, ::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      ::point_i32 point = pmouse->m_point;

      pinteraction->_001ScreenToClient(point);

      return track_popup_menu(pinteraction, pitem, iFlags, point);

   }


   __pointer(::user::menu) user::track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags, ::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      auto point = pmouse->m_point;

      pinteraction->_001ScreenToClient(point);

      return track_popup_xml_menu(pinteraction, strXml, iFlags, point);


   }


   __pointer(::user::menu) user::track_popup_xml_matter_menu(::user::interaction* pinteraction, const char * pszMatter, i32 iFlags, ::message::message * pmessage)
   {

      __pointer(::message::mouse) pmouse(pmessage);

      ::point_i32 point = pmouse->m_point;

      return track_popup_xml_matter_menu(pinteraction, pszMatter, iFlags, point);

   }


   bool user::track_popup_menu(::user::interaction* pinteraction, ::user::menu_item * pitem, i32 iFlags, const ::point_i32 & point)
   {

      __pointer(::user::menu) pmenu = __create <  ::user::menu  > ();

      pmenu->m_pmenuitem = pitem;

      if (!pmenu->track_popup_menu(pinteraction, pinteraction))
      {

         pmenu.release();

         return false;

      }

      return true;

   }


   __pointer(::user::menu) user::track_popup_xml_menu(::user::interaction* pinteraction, const ::payload & varXml, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum)
   {

      __pointer(::user::menu) pmenu = __create <  ::user::menu  > ();

      pmenu->m_sizeMinimum = sizeMinimum;

      if (!pmenu->load_xml_menu(varXml))
      {

         pmenu.release();

         return pmenu;

      }

      pmenu->hints(iFlags, point);

      if (!pmenu->track_popup_menu(pinteraction, pinteraction))
      {

         pmenu.release();

         return pmenu;

      }

      return pmenu;

   }


   __pointer(::user::menu) user::track_popup_xml_matter_menu(::user::interaction* pinteraction, const char * pszMatter, i32 iFlags, const ::point_i32 & pointParam)
   {

      string strMatterSource(pszMatter);

      ::point_i32 point(pointParam);

      fork([this, strMatterSource, iFlags, point, pinteraction]()
      {

         auto pmenu = __create <  ::user::menu  >();

         string strMatter(strMatterSource);

         if (!strMatter.begins_ci("matter://"))
         {

            strMatter = "matter://" + strMatter;

         }

         if (!pmenu->load_xml_menu(strMatter))
         {

            pmenu.release();

            return false;

         }

         pmenu->hints(iFlags, point);

         if (!pmenu->track_popup_menu(pinteraction, pinteraction))
         {

            pmenu.release();

            return false;

         }

         return true;

      });

      return nullptr;

   }


   __pointer(::user::menu) user::track_popup_xml_menu_file(::user::interaction * pinteraction, ::payload varXmlFile, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum)
   {

      string strXml = Context.file().as_string(varXmlFile);

      return track_popup_xml_menu(pinteraction, strXml, iFlags, point, sizeMinimum);

      //__pointer(::user::menu) pmenu = alloc <  ::user::menu  > ();

      //pmenu->m_sizeMinimum = sizeMinimum;

      //if (!pmenu->load_xml_menu_file(varXmlFile))
      //{

      //   pmenu.release();

      //   return pmenu;

      //}

      //pmenu->hints(iFlags, point);

      //if (!pmenu->track_popup_menu(this))
      //{

      //   pmenu.release();

      //   return pmenu;

      //}

      //return pmenu;

   }


   ::type user::user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype)
   {

      auto psession = Sess(get_context_session());

      return psession->user()->controltype_to_typeinfo(econtroltype);


   }


   ::user::style_pointer user::get_user_style(const char* pszExperienceLibrary, ::apex::application* papp)
   {

      auto& pstyle = m_mapUserStyle[pszExperienceLibrary];

      if (!pstyle)
      {

         auto pstyleNew = instantiate_user_style(pszExperienceLibrary, papp);

         pstyle = pstyleNew;

      }

      return pstyle;

   }


   ::user::style_pointer user::instantiate_user_style(const char* pszExperienceLibrary, ::apex::application* papp)
   {

      INFO("aura::session::instantiate_user_theme");

      if (papp == nullptr)
      {

         papp = get_context_application();

      }

      string_array straLibrary;

      {

         string strId(pszExperienceLibrary);

         if (strId.has_char())
         {

            straLibrary.add(strId);

         }

      }

      {

         string strId(App(papp).preferred_experience());

         if (strId.has_char())
         {

            straLibrary.add(strId);

         }

      }

      {

         string strConfig;

         if (has_property("experience"))
         {

            strConfig = payload("experience");

         }

         if (strConfig.has_char())
         {

            string strLibrary = string("experience_") + strConfig;

            straLibrary.add(strConfig);

         }

      }

      {

         string strWndFrm = Ctx(papp).file().as_string(::dir::config() / App(papp).m_strAppName / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = Ctx(papp).file().as_string(::dir::config() / ::file::path(App(papp).m_strAppName).folder() / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = Ctx(papp).file().as_string(::dir::config() / ::file::path(App(papp).m_strAppName).name() / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = Ctx(papp).file().as_string(::dir::config() / "system/experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      straLibrary.add("experience_lite");

      straLibrary.add("experience_metro");

      straLibrary.add("experience_rootkiller");

      straLibrary.add("experience_hyper");

      ::user::style_pointer pstyle;

      for (string strLibrary : straLibrary)
      {

         strLibrary.replace("-", "_");

         strLibrary.replace("/", "_");

         if (!::str::begins_ci(strLibrary, "experience_"))
         {

            strLibrary = "experience_" + strLibrary;

         }

         auto plibrary = System.get_library(strLibrary, true);

         if (::is_null(plibrary))
         {

            ERR("Failed to Load %s", strLibrary.c_str());

            continue;

         }

         pstyle = plibrary->create_object(papp, "user_theme");

         if (!pstyle)
         {

            INFO("could not create user_style from ", strLibrary.c_str());

            continue;

         }

         //sync_lock sl(&System.m_mutexLibrary);

         //System.m_mapLibrary[strLibrary] = plibrary;

         pstyle->m_plibrary = plibrary;

         m_puserstyle = pstyle;

         break;

      }

      if (!pstyle)
      {

         message_box("Failed to find/open 'experience' library.\n\nSome reasons:\n   - No 'experience' library present;\n   - Failure to open any suitable 'experience' library.",nullptr, e_message_box_ok);

         __throw(exit_exception(get_context_system()));

      }

      if (pstyle)
      {

         pstyle->initialize_style();

      }

      return pstyle;

   }


   void user::on_frame_window_drop_files(::user::interaction* pinteraction, ::file::patha& patha)
   {


   }


   void user::defer_instantiate_user_style(const char* pszUiInteractionLibrary)
   {

      if (!m_puserstyle)
      {

         m_puserstyle = get_user_style(pszUiInteractionLibrary);

         if (!m_puserstyle)
         {

            ERR("aura::session::defer_instantiate_user_theme");

            __throw(resource_exception());

         }

      }

   }


//   ::user::menu_central* user::menu()



   __namespace_object_factory(user, ::static_setup::flag_object_user);


} // namespace base


//string __get_text(string str)
//{
//
//   ::aura::application* papp = ::get_context_application();
//
//   if (papp == nullptr)
//   {
//
//      papp = ::get_global_application();
//
//      if (papp == nullptr)
//      {
//
//         return str;
//
//      }
//
//   }
//
//   return papp->__get_text(str);
//
//}


//CLASS_DECL_BASE int __c_get_text_length(const char* psz)
//{
//
//   string str = __get_text(psz);
//
//   return (int)str.get_length();
//
//}


//CLASS_DECL_BASE void __c_get_text(char* pszText, int iLen, const char* psz)
//{
//
//   string str = __get_text(psz);
//
//   iLen = min(iLen, (int)str.get_length());
//
//   strncpy(pszText, str, iLen);
//
//   pszText[iLen] = '\0';
//
//}


//static int g_iWeatherDarkness = 0;
//
//
//CLASS_DECL_BASE int get_simple_ui_darkness()
//{
//
//   return g_iWeatherDarkness;
//
//}
//
//
//CLASS_DECL_BASE void set_simple_ui_darkness(int iWeatherDarkness)
//{
//
//   g_iWeatherDarkness = iWeatherDarkness;
//
//}
//
//
//
//color32_t argb_swap_rb(color32_t cr)
//{
//   return ARGB(
//      colorref_get_a_value(cr),
//      colorref_get_b_value(cr),
//      colorref_get_g_value(cr),
//      colorref_get_r_value(cr));
//}



