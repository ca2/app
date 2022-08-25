#include "framework.h"
#include "base/user/simple/_component.h"
#include "base/user/menu/_menu.h"
#include "aura/windowing/window.h"
#include "simple_impact.h"
#include "acme/platform/system_setup.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "aura/graphics/draw2d/_component.h"


namespace base
{


   user::user()
   {

      m_pbaseuser = this;

   }


   user::~user()
   {

   }


   void user::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::axis::user::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      ::user::document_manager_container::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}



      //return estatus;

   }


   void user::init1()
   {


      ::factory::add_factory_item <::user::document >();
      //add_factory_item <::user::message_queue >();
      ::factory::add_factory_item <::user::simple_impact >();
      ::factory::add_factory_item <::user::still >();
      ::factory::add_factory_item <::user::combo_box >();
      ::factory::add_factory_item <::user::place_holder >();


      ::factory::add_factory_item <::simple_tab_document >();


      //add_factory_item <::user::font_combo_box >();

      ////if(get_app()->is_system())
      //{

      //   add_factory_item <keyboard_layout >();

      //}

      ::axis::user::init1();

      //if (!::axis::user::init1())
      //{

      //   return false;

      //}

      initialize1_experience();

      //if (!initialize1_experience())
      //{

      //   return false;

      //}

      //return true;

   }


   void user::init()
   {

      ::axis::user::init();

      //if (!::axis::user::init())
      //{

      //   return false;

      //}

      ::factory::add_factory_item <::simple_scroll_bar, ::user::scroll_bar>();

      ::factory::add_factory_item <::user::menu_item >();
      ::factory::add_factory_item <::user::menu >();
      ::factory::add_factory_item <::user::menu_list_impact >();


      ::factory::add_factory_item < ::user::split_layout  >();
      ::factory::add_factory_item < ::user::split_bar  >();


      ::factory::add_factory_item < simple_frame_window  >();
      //add_factory_item < prodevian_translucent_simple_frame_window  >();
      ::factory::add_factory_item < simple_main_frame  >();
      ::factory::add_factory_item < ::user::document  >();
      ::factory::add_factory_item < ::user::split_impact  >();


      //auto estatus = 
      
      __compose_new(m_pmenucentral);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //auto estatus = create_user_shell();

      //if (!estatus)
      //{

      //   return estatus;

      //}



      TRACE("::user::application::initialize");

      //xml::document docUser;

      //string strUser = pcontext->m_papexcontext->file().as_string(pcontext->m_papexcontext->dir().appdata()/"langstyle_settings.xml");

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

      //string strLicense = papp->get_license_id();


      //::payload & varTopicQuey = psystem->commnam_varTopicQuery;

      auto psystem = m_psystem->m_pbasesystem;

      bool bHasInstall = psystem->is_true("install");

      bool bHasUninstall = psystem->is_true("uninstall");

      debug_print("user::initialize bHasInstall %c", bHasInstall);

      debug_print("user::initialize bHasUninstall %c", bHasUninstall);

      //return true;

   }


   void user::init2()
   {

      ::user::user::init2();
      //if (!::acme::department::init2())
      //{

      //   return false;

      //}

      //return true;

   }


   void user::term()
   {


      //pstyle.release();
//      ::acme::del(m_pufeschema);
//
//      ::acme::del(m_pufe);


      try
      {

         ::acme::department::term();

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

      //return ::success;

   }


   void user::destroy()
   {

      for (auto& style : m_mapUserStyle.values())
      {

         __finalize(style);

      }

      m_mapUserStyle.erase_all();

      //auto estatus = 
      
      ::axis::user::destroy();

      //return estatus;

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


   void user::SendMessageToWindows(const ::atom & atom,wparam wparam,lparam lparam)
   {

      //auto pappBase = get_app();

      auto psession = get_session();

      for (auto& pappApex : psession->m_applicationa)
      {

         __pointer(::base::application) pappItem = pappApex;

         synchronous_lock synchronouslock(&pappItem->m_mutexFrame);

         __pointer(::user::interaction) pinteraction;

         while (pappItem->get_frame(pinteraction))
         {

            if (pinteraction != nullptr && pinteraction->is_window())
            {

               pinteraction->send_message(atom, wparam, lparam);

               pinteraction->send_message_to_descendants(atom, wparam, lparam);

            }

         }

      }

   }


//   ::user::front_end_schema * GetUfeSchema(::object * pobject)
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
//   ::user::front_end * GetUfe(::object * pobject)
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


   __pointer(::user::menu_interaction) user::create_menu_button(::user::style* pstyle, ::user::menu_item* pmenuitem)
   {

      auto pmenubutton = __new(::user::menu_button);

      pmenubutton->initialize_menu_interaction(pmenuitem);

      if (pmenuitem->m_pimage->is_set())
      {

         pmenubutton->set_button_style(::user::button::e_style_image_and_text);

         auto eimage = (enum_image)pmenuitem->m_pmenu->payload("image_transform").i32();

         ::image_pointer pimage = pmenuitem->m_pimage + eimage;

         pmenubutton->LoadBitmaps(pimage);

      }

      return pmenubutton;

   }


//   __pointer(::user::impact) user::get_impact()
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


   CLASS_DECL_BASE __pointer(::user::interaction) create_virtual_window(::object * pobject, u32 dwExStyle, const ::string & pClassName, const ::string & lpWindowName, u32 uStyle, const ::rectangle_i32 & rectangle, ::user::interaction * puiParent, atom atom, hinstance hInstance, void * pParam);


   CLASS_DECL_BASE __pointer(::user::interaction) create_virtual_window(::object * pobject, u32 dwExStyle, const ::string & pClassName, const ::string & pWindowName, u32 uStyle, ::user::interaction * puiParent, hinstance hInstance, void * pParam)
   {

      __UNREFERENCED_PARAMETER(dwExStyle);
      __UNREFERENCED_PARAMETER(pClassName);
      __UNREFERENCED_PARAMETER(pWindowName);
      __UNREFERENCED_PARAMETER(uStyle);
      __UNREFERENCED_PARAMETER(hInstance);
      __UNREFERENCED_PARAMETER(pParam);

      auto pinteraction = __new(::user::interaction);

      pinteraction->create_child(puiParent);

      //if(pinteraction->create_child(puiParent))
      //{

         return pinteraction;

      //}

      //pinteraction.release();

      //return nullptr;

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

   //   if (get_session())
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

   //         if (get_session())
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

   //            psystem->finish();

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


   //::write_text::font_list * session::get_single_column_font_list()
   //{

   //   if (m_pfontlistSingleColumn.is_null())
   //   {

   //      __compose(m_pfontlistSingleColumn, __create_new < ::write_text::font_list > ());

   //      m_pfontlistSingleColumn->m_etype = ::write_text::font_list::type_single_column;

   //      m_pfontlistSingleColumn->set_need_layout();

   //   }

   //   return m_pfontlistSingleColumn;

   //}


//   void session::on_app_request_bergedge_callback(::object * pobject)
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
//         //__pointer(::simple_frame_window) pframeApp = get_document()->get_type_impact < ::bergedge::pane_impact >()->get_impact_uie();
//         //if(pframeApp != nullptr)
//         //{
//         //   pframeApp->display(e_display_full_screen);
//         //}
//         //__pointer(::simple_frame_window) pframe = get_document()->get_type_impact < ::bergedge::pane_impact >()->get_parent_frame();
//         //if(pframe != nullptr)
//         //{
//         //   pframe->display(e_display_restored);
//         //}
//      }
//      else
//      {
//         //if(get_document() != nullptr && get_document()->get_type_impact < ::bergedge::impact >() != nullptr)
//         //{
//         //   __pointer(::simple_frame_window) pframe = get_document()->get_type_impact < ::bergedge::impact >()->get_parent_frame();
//         //   if(pframe != nullptr)
//         //   {
//         //      pframe->display(e_display_restored);
//         //      if(pframe->GetTypedParent < ::plugin::host_interaction > () != nullptr)
//         //      {
//         //         pframe->GetTypedParent < ::plugin::host_interaction > ()->on_layout(pgraphics);
//         //      }
//         //      else
//         //      {
//         //         pframe->_001FancyInitialFramePlacement();
//         //      }
//         //   }
//         //}
//      }
//
////      if (psession->m_pappCurrent != nullptr && psession->m_pappCurrent->m_psession->m_paccount->m_puser != nullptr)
////      {
////         try
////         {
////            get_impact()->get_parent_frame()->set_window_text(psession->m_pappCurrent->m_psession->m_paccount->m_puser->m_strLogin);
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


   //__pointer(::user::impact) session::get_impact()
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

   //bool session::get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)

   //{

   //   if (get_document() != nullptr && get_impact() != nullptr)
   //   {

   //      get_impact()->get_window_rect(prectangle);


   //      return true;

   //   }
   //   else
   //   {

   //      return ::aura::session::get_monitor_rectangle(iMonitor, prectangle);


   //   }

   //}
   //::type system::get_simple_frame_window_type_info()
   //{

   //   return ::type();

   //}





   //::count session::get_monitor_count()
   //{

   //   if (get_document() != nullptr && get_impact() != nullptr)
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
//      if (pcreate->payload("uicontainer").cast < ::user::interaction >() != nullptr)
//         puiParent = pcreate->payload("uicontainer").cast < ::user::interaction >();
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
////      if (puiParent == nullptr && pcreate->m_pappbias.is_set())
////      {
////         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_pappbias->m_puserinteractionParent);
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
//      pinteraction = psession->get_document()->get_bergedge_impact();
//      }
//
//      return pinteraction;
//
//      }*/
//
//      if (pcreate->m_bExperienceMainFrame ||
//            papp->m_bExperienceMainFrame ||
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
//      ::aura::application & app = App(pinteraction->get_app());
//
//      string strAppName = app.m_strAppName;
//
//      if (strAppName != "bergedge")
//      {
//
//         if (get_document() != nullptr)
//         {
//
//            //if(get_document()->get_type_impact < ::bergedge::pane_impact >() != nullptr)
//            //{
//
//            //   get_document()->get_type_impact < ::bergedge::pane_impact >()->set_current_tab_by_id("app:" + strAppName);
//
//            //   puiParent = get_document()->get_type_impact < ::bergedge::pane_impact >()->get_tab_holder(get_document()->get_type_impact < ::bergedge::pane_impact >()->get_tab_by_id("app:" + strAppName));
//
//            //}
//            //else
//            //{
//
//            //   puiParent = get_document()->get_type_impact < ::bergedge::impact >();
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

   bool user::track_popup_menu(::user::interaction* pinteraction, ::user::menu_item * pitem, i32 iFlags, ::channel* pchannelNotify)
   {

      ::point_i32 point;

      auto pwindow = pinteraction->window();

      auto pointCursor = pwindow->get_cursor_position();

      return track_popup_menu(pinteraction, pitem, iFlags, pointCursor, pchannelNotify);

   }


   __pointer(::user::menu) user::track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags, ::channel* pchannelNotify)
   {

      auto pwindow = pinteraction->window();

      auto pointCursor = pwindow->get_cursor_position();

      return track_popup_xml_menu(pinteraction, strXml, iFlags, pointCursor, ::size_i32(), pchannelNotify);

   }


   __pointer(::user::menu) user::track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, ::channel* pchannelNotify)
   {

      auto pwindow = pinteraction->window();

      auto pointCursor = pwindow->get_cursor_position();

      return track_popup_xml_matter_menu(pinteraction, pszMatter, iFlags, pointCursor, pchannelNotify);

   }



   bool user::track_popup_menu(::user::interaction* pinteraction, ::user::menu_item * pitem, i32 iFlags, ::message::message * pmessage, ::channel* pchannelNotify)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_point;

      pinteraction->screen_to_client(point);

      return track_popup_menu(pinteraction, pitem, iFlags, point, pchannelNotify);

   }


   __pointer(::user::menu) user::track_popup_xml_menu_text(::user::interaction* pinteraction, string strXml, i32 iFlags, ::message::message * pmessage, ::channel* pchannelNotify)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto point = pmouse->m_point;

      pinteraction->screen_to_client(point);

      return track_popup_xml_menu(pinteraction, strXml, iFlags, point, ::size_i32(), pchannelNotify);

   }


   __pointer(::user::menu) user::track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, ::message::message * pmessage, ::channel* pchannelNotify)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::point_i32 point = pmouse->m_point;

      return track_popup_xml_matter_menu(pinteraction, pszMatter, iFlags, point, pchannelNotify);

   }


   bool user::track_popup_menu(::user::interaction* pinteraction, ::user::menu_item * pitem, i32 iFlags, const ::point_i32 & point, ::channel* pchannelNotify)
   {

      __pointer(::user::menu) pmenu = __create <  ::user::menu  > ();

      pmenu->m_pmenuitem = pitem;

      if (!pmenu->track_popup_menu(pchannelNotify, pinteraction))
      {

         pmenu.release();

         return false;

      }

      return true;

   }


   __pointer(::user::menu) user::track_popup_xml_menu(::user::interaction* pinteraction, const ::payload & varXml, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum, ::channel* pchannelNotify)
   {

      __pointer(::user::menu) pmenu = pinteraction->__create <  ::user::menu  > ();

      pmenu->m_sizeMinimum = sizeMinimum;

      if (!pmenu->load_xml_menu(varXml))
      {

         pmenu.release();

         return pmenu;

      }

      pmenu->hints(iFlags, point);

      if (!pmenu->track_popup_menu(pchannelNotify, pinteraction))
      {

         pmenu.release();

         return pmenu;

      }

      return pmenu;

   }


   __pointer(::user::menu) user::track_popup_xml_matter_menu(::user::interaction* pinteraction, const ::string & pszMatter, i32 iFlags, const ::point_i32 & pointParam, ::channel * pchannelNotify)
   {

      string strMatterSource(pszMatter);

      ::point_i32 point(pointParam);

      fork([this, strMatterSource, iFlags, point, pinteraction, pchannelNotify]()
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

         if (!pmenu->track_popup_menu(pchannelNotify, pinteraction))
         {

            pmenu.release();

            return false;

         }

         return true;

      });

      return nullptr;

   }


   __pointer(::user::menu) user::track_popup_xml_menu_file(::user::interaction * pinteraction, ::payload varXmlFile, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum, ::channel* pchannelNotify)
   {

      auto pcontext = get_context();

      string strXml = pcontext->m_papexcontext->file().as_string(varXmlFile);

      return track_popup_xml_menu(pinteraction, strXml, iFlags, point, sizeMinimum, pchannelNotify);

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

      auto psession = get_session();

      return psession->user()->controltype_to_typeinfo(econtroltype);


   }


   ::user::style_pointer user::get_user_style(const ::string & pszExperienceLibrary, ::application* papp)
   {

      auto& pstyle = m_mapUserStyle[pszExperienceLibrary];

      if (!pstyle)
      {

         auto pstyleNew = instantiate_user_style(pszExperienceLibrary, papp);

         pstyle = pstyleNew;

      }

      return pstyle;

   }


   ::user::style_pointer user::instantiate_user_style(const ::string & strExperience, ::application* papp)
   {

      auto pexperience = experience()->experience(papp, strExperience);

      ::user::style_pointer pstyle;

      pexperience->m_pfactory->__construct(pstyle);

      if (!pstyle)
      {

         INFORMATION("could not create user_style from " << pexperience->m_strExperience);

         return nullptr;

      }

      pstyle->initialize(papp);

      pstyle->m_pfactory = pexperience->m_pfactory;

      m_puserstyle = pstyle;

      if (!pstyle)
      {

         output_error_message("Failed to find/open 'experience' library.\n\nSome reasons:\n   - No 'experience' library present;\n   - Failure to open any suitable 'experience' library.",nullptr, e_message_box_ok);

         throw exit_exception(get_system());

      }

      if (pstyle)
      {

         pstyle->initialize_style();

      }

      return pstyle;

   }


   void user::on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array& patha)
   {


   }


   void user::defer_instantiate_user_style(const ::string & pszUiInteractionLibrary)
   {

      if (!m_puserstyle)
      {

         m_puserstyle = get_user_style(pszUiInteractionLibrary);

         if (!m_puserstyle)
         {

            ERROR("aura::session::defer_instantiate_user_theme");

            throw ::exception(error_resource);

         }

      }

   }


//   ::user::menu_central* user::menu()



   __namespace_object_factory(user, ::system_setup::flag_object_user);


} // namespace base


//string __get_text(string str)
//{
//
//   ::aura::application* papp = ::get_app();
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


//CLASS_DECL_BASE int __c_get_text_length(const ::string & psz)
//{
//
//   string str = __get_text(psz);
//
//   return (int)str.get_length();
//
//}


//CLASS_DECL_BASE void __c_get_text(char* pszText, int iLen, const ::string & psz)
//{
//
//   string str = __get_text(psz);
//
//   iLen = minimum(iLen, (int)str.get_length());
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
//::color::color argb_swap_rb(::color32_t color32)
//{
//   return argb(
//      colorref_get_a_value(color32),
//      colorref_get_b_value(color32),
//      colorref_get_g_value(color32),
//      colorref_get_r_value(color32));
//}



