#include "framework.h"
#include "document_manager.h"
#include "user.h"
#include "impact_creator.h"
#include "multiple_document_template.h"
#include "single_document_template.h"
#include "style.h"
#include "split_impact.h"
#include "tab_impact.h"
#include "split_bar.h"
#include "acme/exception/exit.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/synchronous_lock.h"
//#include "acme/platform/sequencer.h"
#include "acme/platform/system_setup.h"
#include "acme/handler/request.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "apex/platform/application_menu.h"
#include "aura/graphics/image/image.h"
#include "aura/message/user.h"
#include "aura/user/menu/track_popup.h"
#include "aura/windowing/window.h"
#include "axis/user/user/calculator_edit.h"
#include "base/platform/application.h"
#include "base/platform/session.h"
#include "base/platform/system.h"
#include "base/user/experience/department.h"
#include "base/user/experience/experience.h"
#include "base/user/form/document.h"
#include "base/user/simple/child_frame.h"
#include "base/user/simple/impact.h"
#include "base/user/simple/tab_document.h"
#include "base/user/simple/scroll_bar.h"
#include "base/user/simple/frame_window.h"
#include "base/user/simple/main_frame.h"
#include "base/user/simple/toolbar.h"
#include "base/user/menu/button.h"
#include "base/user/menu/item.h"
#include "base/user/menu/list_impact.h"
#include "base/user/menu/central.h"
#include "base/user/form/impact.h"


//#if defined(FREEBSD) || defined(OPENBSD) || defined(__APPLE__)
//#include <stdio.h>
//#endif




namespace base
{


   user::user()
   {

      print_line("base::user::user");

      //m_pbaseuser = this;

   }


   user::~user()
   {

   }


   void user::initialize(::particle * pparticle)
   {

      //auto estatus =

      print_line("base::user::initialize");

      ::axis::user::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =

      print_line("base::user::initialize (2)");

      ::user::document_manager_container::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}



      //return estatus;

   }


   // ::base::application * user::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::base::session * user::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession->m_pbasesession : nullptr;
   //
   // }
   //
   //
   // ::base::system * user::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }


   //::base::user* user::user()
   //{

   //   

   //   return ::is_set(psession) ? psession->user() : nullptr;

   //}


   void user::init1()
   {


      ::axis::user::init1();


      factory()->add_factory_item <::user::document >();
      factory()->add_factory_item <::simple_impact >();
      factory()->add_factory_item <::user::place_holder >();


      factory()->add_factory_item <::simple_main_frame >();
      factory()->add_factory_item <::simple_tab_document >();

      factory()->add_factory_item <::user::tab_impact >();

      factory()->add_factory_item < ::user::form_impact >();


      factory()->add_factory_item <simple_toolbar >();
      factory()->add_factory_item <simple_toolbar, ::user::toolbar >();



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

      factory()->add_factory_item < simple_child_frame  >();
      factory()->add_factory_item < form_document >();


      factory()->add_factory_item <::simple_scroll_bar, ::user::scroll_bar>();

      factory()->add_factory_item <::menu::item >();
      factory()->add_factory_item <::user::menu >();
      factory()->add_factory_item <::user::menu_list_impact >();


      factory()->add_factory_item < ::user::split_layout  >();
      factory()->add_factory_item < ::user::split_bar  >();


      factory()->add_factory_item < simple_frame_window  >();
      //add_factory_item < prodevian_translucent_simple_frame_window  >();
      factory()->add_factory_item < ::user::document  >();
      factory()->add_factory_item < ::user::split_impact  >();


      //auto estatus = 

      __construct_new(m_pmenucentral);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //auto estatus = create_user_shell();

      //if (!estatus)
      //{

      //   return estatus;

      //}



      informationf("::user::application::initialize");

      //xml::document docUser;

      //string strUser = file()->as_string(directory()->appdata()/"langstyle_settings.xml");

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

      auto psystem = system();

      bool bHasInstall = psystem->is_true("install");

      bool bHasUninstall = psystem->is_true("uninstall");

      debug_print("base::user::initialize bHasInstall %c", bHasInstall);

      debug_print("base::user::initialize bHasUninstall %c", bHasUninstall);

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
      catch (...)
      {

      }

      try
      {

         m_pmenucentral.release();

      }
      catch (...)
      {

      }

      //return ::success;

   }


   void user::destroy()
   {


      //m_ptemplateForm.release();

      //m_ptemplateChildForm.release();

      m_pmousefocusLButtonDown.release();

      m_pmousefocusRButtonDown.release();

      m_pmenucentral.release();

      m_pexperience.release();

      //auto estatus = 




      ::user::document_manager_container::destroy();

      ::axis::user::destroy();





      //return estatus;

   }


   ::user::interaction_base * user::get_mouse_focus_LButtonDown()
   {

      return m_pmousefocusLButtonDown;

   }


   void user::set_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus)
   {

      m_pmousefocusLButtonDown = pmousefocus;

   }


   ::user::interaction_base * user::get_mouse_focus_RButtonDown()
   {

      return m_pmousefocusRButtonDown;

   }


   void user::set_mouse_focus_RButtonDown(::user::interaction_base * pmousefocus)
   {

      m_pmousefocusRButtonDown = pmousefocus;

   }


   void user::SendMessageToWindows(const ::atom & atom, wparam wparam, lparam lparam)
   {

      //auto pappBase = get_app();



      for (auto & pappApex : session()->m_applicationa)
      {

         ::pointer<::base::application>pappItem = pappApex;

         synchronous_lock synchronouslock(pappItem->m_pmutexFrame);

         ::pointer<::user::interaction>pinteraction;

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


   //   ::user::front_end_schema * GetUfeSchema(::particle * pparticle)
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
   //   ::user::front_end * GetUfe(::particle * pparticle)
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


   ::type_atom user::controltype_to_typeinfo(::user::enum_control_type econtroltype)
   {

      return {};

   }


   ::pointer<::user::menu_interaction>user::create_menu_button(::user::style * pstyle, ::menu::item * pmenuitem)
   {

      auto pmenubutton = __allocate::user::menu_button();

      pmenubutton->initialize_menu_interaction(pmenuitem);

      if (pmenuitem->m_pimage->is_set())
      {

         pmenubutton->set_button_style(::user::button::e_style_image_and_text);

         //auto eimage = (enum_image)pmenuitem->m_pmenu->payload("image_transform").i32();

         //::image::image_pointer pimage = *pmenuitem->m_pimage + eimage;

         //pmenubutton->LoadBitmaps(pimage);

      }

      return pmenubutton;

   }


   //   ::pointer<::user::impact>user::get_impact()
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


   CLASS_DECL_BASE::pointer<::user::interaction>create_virtual_window(::particle * pparticle, u32 dwExStyle, const ::string & pClassName, const ::string & lpWindowName, u32 uStyle, const ::rectangle_i32 & rectangle, ::user::interaction * puiParent, atom atom, hinstance hInstance, void * pParam);


   CLASS_DECL_BASE::pointer<::user::interaction>create_virtual_window(::particle * pparticle, u32 dwExStyle, const ::string & pClassName, const ::string & pWindowName, u32 uStyle, ::user::interaction * puiParent, hinstance hInstance, void * pParam)
   {

      __UNREFERENCED_PARAMETER(dwExStyle);
      __UNREFERENCED_PARAMETER(pClassName);
      __UNREFERENCED_PARAMETER(pWindowName);
      __UNREFERENCED_PARAMETER(uStyle);
      __UNREFERENCED_PARAMETER(hInstance);
      __UNREFERENCED_PARAMETER(pParam);

      auto pinteraction = __allocate::user::interaction();

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

   //   return ___new session_docs();

   //}


   //void destroy_session_docs(session_docs * pdocs)
   //{

   //   ::acme::del(pdocs);

   //}


   //::write_text::font_list * session::get_single_column_font_list()
   //{

   //   if (m_pfontlistSingleColumn.is_null())
   //   {

   //      __construct(m_pfontlistSingleColumn, __create_new < ::write_text::font_list > ());

   //      m_pfontlistSingleColumn->m_etype = ::write_text::font_list::type_single_column;

   //      m_pfontlistSingleColumn->set_need_layout();

   //   }

   //   return m_pfontlistSingleColumn;

   //}


//   void session::on_app_request_bergedge_callback(::particle * pparticle)
//   {
//
//      if (&App(pparticle) != nullptr)
//      {
//
//         psession->m_pappCurrent = &App(pparticle);
//
//      }
//
//      if (psession->m_bShowPlatform)
//      {
//         //::pointer<::simple_frame_window>pframeApp = get_document()->get_typed_impact < ::bergedge::pane_impact >()->get_impact_uie();
//         //if(pframeApp != nullptr)
//         //{
//         //   pframeApp->display(e_display_full_screen);
//         //}
//         //::pointer<::simple_frame_window>pframe = get_document()->get_typed_impact < ::bergedge::pane_impact >()->get_parent_frame();
//         //if(pframe != nullptr)
//         //{
//         //   pframe->display(e_display_normal);
//         //}
//      }
//      else
//      {
//         //if(get_document() != nullptr && get_document()->get_typed_impact < ::bergedge::impact >() != nullptr)
//         //{
//         //   ::pointer<::simple_frame_window>pframe = get_document()->get_typed_impact < ::bergedge::impact >()->get_parent_frame();
//         //   if(pframe != nullptr)
//         //   {
//         //      pframe->display(e_display_normal);
//         //      if(pframe->get_typed_parent < ::plugin::host_interaction > () != nullptr)
//         //      {
//         //         pframe->get_typed_parent < ::plugin::host_interaction > ()->on_layout(pgraphics);
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


   //::pointer<::user::document>session::get_document()
   //{

   //   //return m_pdocs->m_pbergedgedocument;
   //   return nullptr;

   //}


   //::pointer<::user::impact>session::get_impact()
   //{

   //   if (get_document() == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return nullptr;

   //}


   //::pointer<::user::document>session::get_platform()
   //{
   //   //return m_pdocs->m_pplatformdocument;
   //   return nullptr;
   //}

   //::pointer<::user::document>session::get_nature()
   //{
   //   //return m_pdocs->m_pnaturedocument;
   //   return nullptr;
   //}

   //bool session::get_monitor_rectangle(::collection::index iMonitor, ::rectangle_i32 * prectangle)

   //{

   //   if (get_document() != nullptr && get_impact() != nullptr)
   //   {

   //      get_impact()->window_rectangle(prectangle);


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





   //::collection::count session::get_monitor_count()
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


//   ::user::interaction * session::get_request_parent_ui(::user::interaction * pinteraction, ::request * prequest)
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
//            //if(get_document()->get_typed_impact < ::bergedge::pane_impact >() != nullptr)
//            //{
//
//            //   get_document()->get_typed_impact < ::bergedge::pane_impact >()->set_current_tab_by_id("app:" + strAppName);
//
//            //   puiParent = get_document()->get_typed_impact < ::bergedge::pane_impact >()->get_tab_holder(get_document()->get_typed_impact < ::bergedge::pane_impact >()->get_tab_by_id("app:" + strAppName));
//
//            //}
//            //else
//            //{
//
//            //   puiParent = get_document()->get_typed_impact < ::bergedge::impact >();
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

   ::pointer<::menu::item > user::menu_item_from_application_menu(::application_menu * papplicationmenu, ::user::menu * pmenu)
   {

      auto pmenuitem = __create_new < ::menu::item >();

      from_application_menu(pmenuitem, papplicationmenu, pmenu);

      return pmenuitem;

   }


   ::pointer<::menu::item > user::popup_menu_item_from_application_menu(::application_menu * papplicationmenu, ::user::menu * pmenu)
   {

      auto pmenuitem = __create_new < ::menu::item >();

      popup_from_application_menu(pmenuitem, papplicationmenu, pmenu);

      return pmenuitem;

   }


   void user::from_application_menu(::menu::item * pmenuitem, ::application_menu * papplicationmenu, ::user::menu * pmenu)
   {

      if (papplicationmenu->is_separator())
      {

         pmenuitem->m_pmenu = pmenu;
         pmenuitem->m_atom = id_separator;

      }
      else if (papplicationmenu->is_popup())
      {

         popup_from_application_menu(pmenuitem, papplicationmenu, pmenu);

      }
      else
      {

         pmenuitem->m_pmenu = pmenu;
         pmenuitem->m_atom = papplicationmenu->m_atom;
         pmenuitem->m_strTitle = papplicationmenu->m_strName;

      }

   }


   ::pointer < ::user::menu > user::user_menu_from_menu(::menu::menu * pmenu)
   {

      ::pointer < ::user::menu > pusermenu = pmenu;

      if (pusermenu)
      {

         return pusermenu;

      }

      ::pointer < ::application_menu > papplicationmenu = pmenu;

      if (papplicationmenu)
      {

         auto pusermenu = pmenu->__create_new < ::user::menu >();

         pusermenu->m_pmenuitem = menu_item_from_application_menu(papplicationmenu, pusermenu);

         return pusermenu;

      }

      return {};

   }


   ::pointer < ::menu::menu > user::menu_from_xml(::particle * pparticleContext, const ::scoped_string & scopedstrXml)
   {

      ::string strXml;

      if (scopedstrXml.case_insensitive_begins("matter://"))
      {

         auto pcontext = pparticleContext->m_papplication;

         strXml = pcontext->file()->as_string(scopedstrXml);

      }
      else
      {

         strXml = scopedstrXml;

      }

      ::pointer<::user::menu>pmenu = pparticleContext->__create <  ::user::menu  >();

      if (!pmenu->load_xml_menu(strXml))
      {

         pmenu.release();

         return nullptr;

      }

      return pmenu;

   }


   void user::track_popup_menu(::menu::track_popup * ptrackpopup)
   {

      auto pusermenu = user_menu_from_menu(ptrackpopup->m_pmenu);

      ptrackpopup->m_pmenuImplementation = pusermenu;


      //__defer_construct(pitem->m_pmenu);

      //pitem->m_pmenu->m_pmenuitem = pitem;

      //pitem->m_pmenu->m_sizeMinimum = sizeMinimum;

      //pitem->m_pmenu->hints(iFlags, pointCursor);

      ///pmenu->track_hints(ptrackpopup);

      pusermenu->track_popup_menu(ptrackpopup);

      //      {
      //
      //         //pitem->m_pmenu.release();
      //
      //         ///return nullptr;
      //
      //      }

            //return pitem->m_pmenu;

   }


   void user::popup_from_application_menu(::menu::item * pmenuitem, ::application_menu * papplicationmenu, ::user::menu * pmenu)
   {

      pmenuitem->m_pmenu = pmenu;
      pmenuitem->m_strTitle = papplicationmenu->m_strName;
      pmenuitem->m_bPopup = true;

      for (auto & pitem : *papplicationmenu)
      {

         auto pmenuitemChild = menu_item_from_application_menu(pitem, pmenu);

         pmenuitem->add_item(pmenuitemChild);

      }

   }


   //   ::pointer<::user::menu> user::track_popup_menu(::user::interaction * pinteraction, ::application_menu * papplicationmenu, i32 iFlags, const ::point_i32 & point, const ::size_i32 & sizeMinimum, ::channel * pchannelNotify)
   //   {
   //
   //      ::pointer<::user::menu> pmenu = __create <  ::user::menu  >();
   //
   //      auto pmenuitem = menu_item_from_application_menu(papplicationmenu, pmenu);
   //
   //      return _track_popup_menu(pinteraction, pmenuitem, iFlags, point, sizeMinimum, pchannelNotify);
   //
   //   }


   //   ::pointer<::user::menu>user::track_popup_menu(::user::interaction * pinteraction, const ::scoped_string & scopedstrXml, i32 iFlags, const ::point_i32 & pointCursor, const ::size_i32 & sizeMinimum, ::channel * pchannelNotify)
   //   {
   //      
   //      ::string strXml;
   //      
   //      if(scopedstrXml.case_insensitive_begins("matter://"))
   //      {
   //         
   //         auto pcontext = pinteraction->m_papplication;
   //       
   //         strXml = pcontext->file()->as_string(scopedstrXml);
   //         
   //      }
   //      else
   //      {
   //         
   //         strXml = scopedstrXml;
   //         
   //      }
   //      
   //      ::pointer<::user::menu>pmenu = pinteraction->__create <  ::user::menu  >();
   //
   //      if (!pmenu->load_xml_menu(strXml))
   //      {
   //
   //         pmenu.release();
   //
   //         return nullptr;
   //
   //      }
   //
   //      return _track_popup_menu(pinteraction, pmenu->m_pmenuitem, iFlags, pointCursor, sizeMinimum, pchannelNotify);
   //
   //   }



   ::type_atom user::user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype)
   {



      return controltype_to_typeinfo(econtroltype);

   }


   ::user::style_pointer user::get_user_style(const ::string & pszExperienceLibrary, ::platform::application * papp)
   {

      auto & pstyle = m_mapUserStyle[pszExperienceLibrary];

      if (!pstyle)
      {

         auto pstyleNew = instantiate_user_style(pszExperienceLibrary, papp);

         pstyle = pstyleNew;

      }

      return pstyle;

   }


   ::user::style_pointer user::instantiate_user_style(const ::string & strExperience, ::platform::application * papp)
   {

      auto pexperience = experience()->experience(papp, strExperience);

      ::user::style_pointer pstyle;

      pexperience->m_pfactory->__construct(papp, pstyle);

      if (!pstyle)
      {

         information() << "could not create user_style from " << pexperience->m_strExperience;

         return nullptr;

      }

      pstyle->initialize(papp);

      pstyle->m_pfactory = pexperience->m_pfactory;

      //m_puserstyle = pstyle;

      if (!pstyle)
      {

         output_error_message("Failed to find/open 'experience' library.\n\nSome reasons:\n   - No 'experience' library present;\n   - Failure to open any suitable 'experience' library.", nullptr, e_message_box_ok);

         throw ::exit_exception(::error_exit_system, system());

      }

      if (pstyle)
      {

         pstyle->initialize_style();

      }

      return pstyle;

   }


   void user::on_frame_window_drop_files(::user::interaction * pinteraction, ::file::path_array & patha)
   {


   }


   ::pointer<::form_document>user::create_typed_form(::particle * pparticle, const ::type_atom & typeatom, ::user::element * puserelementParent, const ::payload & payload, const ::payload & payloadArgs)
   {

      if (!typeatom)
      {

         return nullptr;

      }

      auto pimpactsystem = application()->impact_system(typeatom);

      if (!pimpactsystem)
      {

         throw ::exception(todo);

         //application()->add_impact_system(
         //   m_ptemplateForm->m_atom, 
         //   __initialize_new ::user::multiple_document_template(
         //      m_ptemplateForm->m_atom,
         //      m_ptemplateForm->m_typeatomDocument,
         //      m_ptemplateForm->m_typeatomFrame,
         //      typeatom));

      }

      if (pparticle == nullptr)
      {

         if (::is_set(puserelementParent))
         {

            pparticle = puserelementParent;

         }
         else
         {

            pparticle = this;

         }

      }

      ::pointer<::request>prequest(e_create, this);

      prequest->m_egraphicsoutputpurpose |= ::graphics::e_output_purpose_screen;

      prequest->m_puserelementParent = puserelementParent;

      prequest->m_payloadArguments = payloadArgs;

      auto pathFile = payload.as_file_path();

      if (pathFile.has_char())
      {

         prequest->m_payloadFile = pathFile;

      }

      pimpactsystem->request(prequest);

      ::pointer<::form_document>pformdocument = ::user::__document(prequest);

      if (pformdocument.is_null())
      {

         return nullptr;

      }

      ::pointer<::user::form_window>pform = pformdocument->get_typed_impact < ::user::form_window >();

      return pformdocument;

   }


   ::pointer<::form_document> user::create_form(::particle * pparticle, ::user::form * pform, ::user::form_callback * pcallback, ::user::element * puserelementParent, const ::payload & payload, const ::payload & payloadArgs)
   {

      //if (m_ptemplateForm == nullptr)
      //{

      //   return nullptr;

      //}

      ::pointer<::request>prequest(e_create, this);

      prequest->m_egraphicsoutputpurpose -= ::graphics::e_output_purpose_screen;

      prequest->m_puserelementParent = puserelementParent;

      prequest->m_puserelementAlloc = pform;

      prequest->m_payloadArguments = payloadArgs;

      prequest->m_payloadArguments["form_callback"] = pcallback;

      auto pathFile = payload.as_file_path();

      if (pathFile.has_char())
      {

         prequest->m_payloadFile = pathFile;

      }

      if (payload.get_type() == ::e_type_property_set && payload.has_property("hold") && payload["hold"].is_false())
      {

         prequest->m_bHold = false;

      }

      //m_ptemplateForm->request(prequest);
      impact_system("form")->request(prequest);

      ::pointer<::form_document>pformdocument = ::user::__document(prequest);

      if (pformdocument.is_null())
      {

         return nullptr;

      }

      ::pointer<::user::form_window> pformwindow = pformdocument->get_typed_impact < ::user::form_window >();

      if (pformwindow.is_set())
      {

         pformwindow->set_form_callback(pcallback);

      }

      return pformdocument;

   }


   ::pointer<::form_document>user::create_child_form(::particle * pparticle, ::user::form * pform, ::user::form_callback * pcallback, ::user::element * puserelementParent, const ::payload & payload, const ::payload & payloadArgs)
   {

      //if (m_ptemplateChildForm == nullptr)
      //{

      //   return nullptr;

      //}

      auto papp = pparticle->application();

      if (papp == nullptr)
      {

         if (::is_set(puserelementParent))
         {

            papp = puserelementParent->user_interaction_base()->get_app();

         }
         else if (pcallback != nullptr)
         {

            papp = pcallback->application();

         }
         else
         {

            papp = get_app();

         }

      }

      auto prequest = __create_new< ::request >();

      prequest->m_egraphicsoutputpurpose -= ::graphics::e_output_purpose_screen;

      prequest->m_puserelementParent = puserelementParent;

      prequest->m_puserelementAlloc = pform;

      prequest->m_payloadArguments = payloadArgs;

      prequest->m_payloadArguments["form_callback"] = pcallback;

      auto pathFile = payload.as_file_path();

      if (pathFile.has_char())
      {

         prequest->m_payloadFile = pathFile;

      }

      if (payload.get_type() == ::e_type_property_set && payload.has_property("hold") && payload["hold"].is_false())
      {

         prequest->m_bHold = false;

      }

      prequest->finish_initialization();

      //m_ptemplateChildForm->request(prequest);

      impact_system("child_form")->request(prequest);

      ::pointer<::form_document>pformdocument = ::user::__document(prequest);

      if (pformdocument.is_null())
      {

         return nullptr;

      }

      ::pointer<::user::form_window> pformwindow = pformdocument->get_typed_impact < ::user::form_window >();

      if (pformwindow.is_set())
      {

         pformwindow->set_form_callback(pcallback);

      }

      return pformdocument;

   }


   bool is_html_file(string strFilePath)
   {

      return string(file_path_final_extension(strFilePath)).case_insensitive_order("htm") == 0;

   }


   ::pointer < ::form_document > user::create_typed_child_form(::particle * pparticle, const ::type_atom & typeatom, ::user::element * puserelementParent, const ::payload & payload, const ::payload & payloadArgs)
   {

      auto pathFile = payload.as_file_path();

      try
      {

         if (!typeatom)
         {

            return nullptr;

         }

         auto pimpactsystem = application()->impact_system(typeatom);

         if (!pimpactsystem)
         {

            auto typeDocument = impact_system("child_form")->m_typeatomDocument;

            if (is_html_file(payload.as_file_path()))
            {

               typeDocument = get_html_document_type();

            }

            throw ::exception(todo);

            //add_impact_system(
            //   m_ptemplateChildForm->m_atom,
            //       __initialize_new ::user::multiple_document_template(
            //   m_ptemplateChildForm->m_atom,
            //   typeDocument,
            //   m_ptemplateChildForm->m_typeatomFrame,
            //   typeatom));

           /* pimpactsystemNew->initialize(pparticle);

            pimpactsystem = pimpactsystemNew;

            m_mapimpactsystem[typeatom] = pimpactsystemNew;

            document_manager()->add_document_template(pimpactsystem);*/

         }

         if (pparticle == nullptr)
         {

            if (::is_set(puserelementParent))
            {

               pparticle = puserelementParent;

            }
            else
            {

               pparticle = this;

            }

         }

         auto prequest = pparticle->__create_new < ::request >();

         prequest->m_egraphicsoutputpurpose -= ::graphics::e_output_purpose_screen;

         prequest->m_puserelementParent = puserelementParent;

         prequest->m_payloadArguments = payloadArgs;

         if (pathFile.has_char())
         {

            prequest->m_payloadFile = pathFile;

         }

         pimpactsystem->request(prequest);

         ::pointer<::form_document>pformdocument = ::user::__document(prequest);

         if (pformdocument.is_null())
         {

            return nullptr;

         }

         ::pointer<::user::form_window>pform = pformdocument->get_typed_impact < ::user::form_window >();

         return pformdocument;

      }
      //catch(::exception)
      catch (const ::exception & exception)
      {

#ifdef DEBUG

         auto pmessagebox = __initialize_new::message_box(exception, "Failed to create form \"" + pathFile + "\"");

         pmessagebox->async();

#endif

      }
      catch (...)
      {

#ifdef DEBUG

         ::exception exception(error_catch_all_exception);

         auto pmessagebox = __initialize_new::message_box(exception, "Failed to create form \"" + pathFile + "\"");

         pmessagebox->async();

#endif

      }

      return nullptr;

   }


   void user::defer_instantiate_user_style(const ::string & pszUiInteractionLibrary)
   {

      if (!m_puserstyle)
      {

         m_puserstyle = get_user_style(pszUiInteractionLibrary);

         if (!m_puserstyle)
         {

            error() << "aura::session::defer_instantiate_user_theme";

            throw ::exception(error_resource);

         }

      }

   }


   //   ::user::menu_central* user::menu()



      //__namespace_object_factory(user, ::system_setup::flag_object_user);

   ::pointer<::user::plain_edit>user::create_calculator_edit()
   {

      return __allocate::user::show < ::calculator::edit >();

   }


   void user::add_impact_system(const ::atom & atom, ::user::impact_system * pimpactsystem)
   {

      return document_manager_container::add_impact_system(atom, pimpactsystem);

   }


   bool user::create_impact_system(const ::atom & atom)
   {

      if (atom == "child_form")
      {

         initialize_html();

         add_impact_system(
            atom,
            __allocate::user::multiple_document_template(
               "system/form",
               ::type < form_document >(),
               get_simple_child_frame_type_info(),
               ::type < ::user::form_impact >()));

         return true;

      }

      throw ::exception(error_failed, "Cannot create impact_system with id " + atom.as_string());

      return false;

   }


   ::pointer<::user::impact_system> user::impact_system(const ::atom & atom)
   {

      auto pimpactsystem = document_manager_container::impact_system(atom);

      if (atom == "child_form")
      {

         if (!pimpactsystem)
         {

            create_impact_system(atom);

         }

         pimpactsystem = document_manager_container::impact_system(atom);

      }

      return pimpactsystem;

   }


   ::pointer < ::user::interaction > user::create_menu_button(::user::menu * pusermenu, ::draw2d::graphics_pointer & pgraphics, ::menu::item * pmenuitem)
   {

      auto pmenubutton = __allocate::user::menu_button();

      pmenubutton->initialize_menu_interaction(pmenuitem);

      if (pmenuitem->m_pimage->is_set())
      {

         pmenubutton->set_button_style(::user::button::e_style_image_and_text);

         //auto eimage = (enum_image)pmenuitem->m_pmenu->payload("image_transform").i32();

         //::image::image_pointer pimage = *pmenuitem->m_pimage + eimage;

         //pmenubutton->LoadBitmaps(pimage);

      }

      return pmenubutton;

   }


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
//   return (int)str.length();
//
//}


//CLASS_DECL_BASE void __c_get_text(char* pszText, int iLen, const ::string & psz)
//{
//
//   string str = __get_text(psz);
//
//   iLen = minimum(iLen, (int)str.length());
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
//::color::color argb_swap_red_blue(::color32_t color32)
//{
//   return argb(
//      color32_u8_opacity(color32),
//      color32_u8_blue(color32),
//      color32_u8_green(color32),
//      color32_u8_red(color32));
//}



