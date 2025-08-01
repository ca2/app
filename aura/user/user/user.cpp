#include "framework.h"
#include "button.h"
#include "user.h"
#include "shell.h"
#include "style.h"
#include "interaction_graphics_thread.h"
#include "interaction_thread.h"
#include "interaction.h"
#include "plain_edit.h"
#include "still.h"
#include "check_box.h"
#include "notify_icon.h"
#include "progress.h"
#include "acme/constant/message.h"
#include "acme/constant/simple_command.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/keep.h"
#include "acme/platform/system_setup.h"
#include "acme/prototype/collection/_container.h"
#include "apex/message/simple_command.h"
#include "acme/handler/request.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/windowing/desktop_environment.h"
#include "aura/graphics/write_text/font_list.h"
#include "aura/message/user.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/platform/application.h"
#include "aura/platform/node.h"
#include "aura/user/user/frame_interaction.h"

#if defined(FREEBSD) || defined(OPENBSD) || defined(__APPLE__)
#include <stdio.h>
#endif

//::pointer< ::mutex > g_pmutexUser = nullptr;


//CLASS_DECL_AURA void initialize_user_mutex();
//CLASS_DECL_AURA void finalize_user_mutex();


//::critical_section g_criticalsectionChildren;

//::critical_section * children_critical_section() { return &g_criticalsectionChildren; }



namespace user
{


   //void initialize_children_mutex();
   //void finalize_children_mutex();


   user::user()
   {

      print_line("user::user::initialize (aura)");

      // m_paxisuser = nullptr;
      // m_pbaseuser = nullptr;
      // m_pbreduser = nullptr;
      // m_pcoreuser = nullptr;
      // //::initialize_user_mutex();
      // //initialize_children_mutex();

      m_bOnInitializeWindowObject = false;

   }


   user::~user()
   {

      //finalize_children_mutex();
      //::finalize_user_mutex();
      //g_pmutexUser = nullptr;
      //m_pmutexUser.release();

   }


   void user::initialize(::particle * pparticle)
   {

      //auto estatus =

      print_line("::user::user::initialize (aura)");


      ::acme::department::initialize(pparticle);


      m_pmutexUser = node()->create_mutex();

      //g_pmutexUser = m_pmutexUser;


      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =

      print_line("user::user::initialize (2) (aura)");

      //create_windowing();

      //if (!estatus)
      //{

      //   informationf("\nFailed to create_windowing at user::user::initialize.");

      //   return estatus;

      //}

      //return estatus;

   }


   void user::on_initialize_window_object(::acme::windowing::window* pacmewindowingwindow)
   {

      if (m_bOnInitializeWindowObject)
      {

         //return ::success_none;

         return;

      }

      __keep_true(m_bOnInitializeWindowObject);

      //m_bOnInitializeWindowObject = true;

      //auto estatus = 
      
      _on_initialize_window_object(pacmewindowingwindow);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void user::_on_initialize_window_object(::acme::windowing::window* pacmewindowingwindow)
   {

      if (!pacmewindowingwindow->m_pacmeuserinteraction->m_bMessageOnlyWindow)
      {

         //auto estatus = 

         if (__defer_construct_new(m_puserstyle))
         {

            //if (!estatus)
            //{

            //   return estatus;

            //}

            //system()->m_pnode->fetch_user_color();

            m_puserstyle->default_style_construct();

         }

      }

      //return estatus;

   }



   ::user::shell* user::shell()
   {

      if (!m_pshell)
      {

         //auto estatus = 
         
         create_user_shell();

         //if (!estatus)
         //{

         //   information() << "failed to create user shell";

         //}

      }

      return m_pshell;

   }


   ::user::interaction * user::interaction(oswindow oswindow)
   {

      auto pwindowing =system()->windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->window(oswindow);

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   return nullptr;

      //}
      
      ::cast< ::user::interaction > puserinteraction = pwindow->m_pacmeuserinteraction;

      return puserinteraction;

   }


   ::user::interaction * user::get_mouse_capture(::thread * pthread)
   {

      auto pwindowing = system()->windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->get_mouse_capture(pthread);

      if (::is_null(pwindow))
      {

         return nullptr;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   return nullptr;

      //}
      
      ::cast< ::user::interaction > puserinteraction = pwindow->m_pacmeuserinteractionMouseCapture;

      return puserinteraction;

   }


   ::user::interaction * user::get_keyboard_focus(::thread * pthread)
   {

      auto pwindowing = system()->windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindowFocus = pwindowing->get_keyboard_focus(pthread);

      if (::is_null(pwindowFocus))
      {

         return nullptr;

      }

      auto puserelementFocus = pwindowFocus->get_keyboard_focus();

      if (::is_null(puserelementFocus))
      {

         return nullptr;

      }

      ::cast < ::user::interaction > puserinteractionFocus = puserelementFocus;

      if (::is_null(puserinteractionFocus))
      {

         return nullptr;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   return nullptr;

      //}

      //return pwindow->aaa_m_pacmeuserinteractionKeyboardFocus;

      return puserinteractionFocus;

   }


   ::user::interaction * user::get_active_window(::thread * pthread)
   {

      auto pwindowing = system()->windowing()

      ;if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->get_active_window(pthread);

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   return nullptr;

      //}

      return pwindow->user_interaction();

   }


   void user::set_active_window(::user::interaction * puserinteraction)
   {

      ::windowing::window * pwindow = nullptr;

      if (::is_set(puserinteraction))
      {

         pwindow = puserinteraction->window();

      }

      //auto estatus =
      
      pwindow->set_active_window();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return ::success;

   }


   ::user::interaction * user::get_foreground_window()
   {

      auto pwindowing = system()->windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->get_foreground_window();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   return nullptr;

      //}

      return pwindow->user_interaction();

   }


   // void user::set_foreground_window(::user::interaction * puserinteraction)
   // {
   //
   //    ::windowing::window * pwindow = nullptr;
   //
   //    if (::is_set(puserinteraction))
   //    {
   //
   //       pwindow = puserinteraction->window();
   //
   //    }
   //
   //    //auto estatus =
   //
   //    pwindow->set_foreground_window();
   //
   //    //if (!estatus)
   //    //{
   //
   //    //   return estatus;
   //
   //    //}
   //
   //    //return ::success;
   //
   // }


   ::user::style* user::user_style()
   {

      return m_puserstyle;

   }


   void user::init1()
   {

      ::acme::department::init1();


      factory()->add_factory_item <::user::thread >();
      factory()->add_factory_item <::user::graphics_thread >();

      factory()->add_factory_item <::user::button >();
      factory()->add_factory_item <::user::check_box >();
      factory()->add_factory_item <::user::still >();

      if (!factory()->get_factory_item < ::user::notify_icon >())
      {

         factory()->add_factory_item <::user::notify_icon >();

      }

      factory()->add_factory_item <::user::still >();

      factory()->add_factory_item <::user::progress >();

   }


   void user::init()
   {

      //if (!
      ::acme::department::init();

      //{

      //   return false;

      //}

      factory()->add_factory_item <::user::plain_edit >();



      //auto estatus = create_user_shell();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      information() << "::user::application::initialize";

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

      //if(strLangUser.has_character())
      //   psession->set_locale(strLangUser,::e_source_database);

      //if(strStyleUser.has_character())
      //   psession->set_schema(strStyleUser,::e_source_database);

      //string strLicense = papp->get_license_id();


      //::payload & varTopicQuey = psystem->commnam_varTopicQuery;

      auto psystem = system();

      bool bHasInstall = psystem->is_true("install");

      bool bHasUninstall = psystem->is_true("uninstall");

      informationf("user::initialize bHasInstall %c", bHasInstall);

      informationf("user::initialize bHasUninstall %c", bHasUninstall);

      //return true;

   }


   void user::init2()
   {

      //auto estatus =
      
      ::acme::department::init2();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //estatus = create_windowing();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void user::destroy()
   {

      m_puserstyle.defer_destroy();

      for (auto & pstyle : m_mapUserStyle.payloads())
      {

         try
         {

            pstyle.defer_destroy();

         }
         catch (...)
         {

         }

      }
      m_mapUserStyle.erase_all();



      //auto estatus =
      ::acme::department::destroy();

      // if (m_pdesktopenvironment)
      // {
      //
      //    m_pdesktopenvironment->destroy();
      //
      // }
      //
      // m_pdesktopenvironment.release();

      if (m_pshell)
      {

         m_pshell->destroy();

      }

      m_pshell.release();

      m_listRunnable.clear();

      m_pmutexRunnable.release();

      m_pmutexUser.release();

      auto psystem = system();

      if (psystem && psystem->m_pacmewindowing)
      {
         
         psystem->m_pacmewindowing->finalize_windowing();

      }

      //windowing().defer_destroy();

      m_uiptraToolWindow.clear();

      if (m_phtml)
      {

         m_phtml.m_psubparticle->destroy();

      }

      m_phtml.release();

      m_mapUserStyle.clear();

      m_pmousefocusLButtonDown.release();

      m_pmousefocusRButtonDown.release();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void user::term()
   {

      set_finishing_flag();

      //try
      //{

      //   auto pwindowing = system()->windowing();

      //   if(::is_set(pwindowing))
      //   {

      //      pwindowing->windowing_post_quit();

      //   }


      //}
      //catch(...)
      //{


      //}

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

      //return ::success;

   }


   void user::create_user_shell()
   {

      //::e_status estatus = ::success;

      if (!m_pshell)
      {

         //estatus = __øconstruct(m_pshell, __allocate ::windows::shell());
         //estatus =
         __øconstruct(m_pshell);

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }

      //if (!m_pshell)
      //{

      //   return ::error_failed;

      //}

      //return ::success;

   }




   ::user::interaction_base * user::get_mouse_focus_LButtonDown()
   {

      return m_pmousefocusLButtonDown;

   }


   void user::set_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_pmousefocusLButtonDown = pmousefocus;

   }


   void user::defer_erase_mouse_focus_LButtonDown(::user::interaction_base * pmousefocus)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pmousefocusLButtonDown == pmousefocus)
      {

         m_pmousefocusLButtonDown = nullptr;

      }

   }


   ::user::interaction_base * user::get_mouse_focus_RButtonDown()
   {

      return m_pmousefocusRButtonDown;

   }


   void user::set_mouse_focus_RButtonDown(::user::interaction_base * pmousefocus)
   {

      m_pmousefocusRButtonDown = pmousefocus;

   }


   void user::SendMessageToWindows(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      auto psession = session();

      for (auto& papp : psession->m_applicationa)
      {

         ::pointer<::aura::application>pappAura = papp;

         _synchronous_lock synchronouslock(pappAura->m_pmutexFrame);

         ::pointer<::user::interaction>pinteraction;

         while (pappAura->get_frame(pinteraction))
         {

            if (pinteraction != nullptr && pinteraction->is_window())
            {

               pinteraction->send_message(emessage, wparam, lparam);

               pinteraction->send_message_to_descendants(emessage, wparam, lparam);

            }

         }

      }

   }


::html::html*user:: html()
{
    return m_phtml;
    
}


::type_atom user::get_html_document_type() { return m_typeatomHtmlDocument; }
::type_atom user::get_html_impact_type() { return m_typeatomHtmlImpact; }


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


   //void user::close_all_documents(bool bEndSession)
   //{

   //   throw ::interface_only();

   //}


   //::pointer<::user::menu_interaction>user::create_menu_button(::user::style * pstyle, ::menu::item* pitem)
   //{

   //   return nullptr;

   //}


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


   //CLASS_DECL_AURA ::pointer<::user::interaction>create_virtual_window(::particle * pparticle, unsigned int dwExStyle, const ::scoped_string & scopedstrClassName, const ::string & lpWindowName, unsigned int uStyle, const ::int_rectangle & rectangle, ::user::interaction * puiParent, atom atom, HINSTANCE hInstance, LPVOID pParam);


   //CLASS_DECL_AURA ::pointer<::user::interaction>create_virtual_window(::particle * pparticle, unsigned int dwExStyle, const ::scoped_string & scopedstrClassName, const ::scoped_string & scopedstrWindowName, unsigned int uStyle, ::user::interaction * puiParent, atom atom, HINSTANCE hInstance, LPVOID pParam)
   CLASS_DECL_AURA ::pointer<::user::interaction>create_virtual_window(::particle * pparticle, ::user::interaction * pinteractionParent)
   {

      auto pinteraction = pparticle->__create_new < ::user::interaction >();

      pinteraction->create_child(pinteractionParent);

      //if()
      //{

         return ::transfer(pinteraction);

      //}

      //pinteraction.release();

      //return nullptr;

   }


} // namespace user


namespace aura
{


   void application::close(::enum_exit eexit)
   {

      if (eexit == ::e_exit_close)
      {

         return;

      }

      m_ethreadcontextClose = e_thread_context_application;

      //if (get_session())
      //{

      //   if (psession->m_pdocmanager)
      //   {

      //      psession->m_pdocmanager->close_all_documents(true);

      //   }

      //}

      if (eexit == ::e_exit_application)
      {

         destroy();

         return;

      }

      if (eexit == ::e_exit_session)
      {

         try
         {

            auto psession = session();

            if (psession)
            {

               psession->destroy();

            }

         }
         catch (...)
         {

         }

         return;

      }

      if (eexit == ::e_exit_system)
      {

         try
         {

            auto psystem = system();

            if (psystem)
            {

               psystem->destroy();

            }

         }
         catch (...)
         {

         }

      }

   }


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


   ::write_text::font_list * session::get_single_column_font_list()
   {

      if (m_pfontlistSingleColumn.is_null())
      {

         m_pfontlistSingleColumn = __create_new < ::write_text::font_list > ();

         m_pfontlistSingleColumn->set_font_list_type(::write_text::e_font_list_single_column);

         // m_pfontlistSingleColumn->set_need_layout();

      }

      return m_pfontlistSingleColumn;

   }


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

   //bool session::get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle)

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
   ::type_atom system::get_simple_frame_window_type_info()
   {

      return {};

   }


   //void system::_on_initialize_window_object()
   //{

   //   auto estatus = ::aqua::system::_on_initialize_window_object();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   auto psession = session();

   //   estatus = psession->on_initialize_window_object();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

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


   ::user::interaction * session::get_request_parent_ui(::user::interaction * pinteraction, ::request * prequest)
   {

      ::pointer<::user::interaction>puserinteractionParent;

      if (prequest->payload("uicontainer").cast < ::user::interaction >() != nullptr)
      {

         puserinteractionParent = prequest->payload("uicontainer").cast < ::user::interaction >();

      }

      if (!puserinteractionParent && prequest->m_puserelementParent)
      {

         puserinteractionParent = prequest->m_puserelementParent;

      }

//      if (puiParent == nullptr && pcreate != nullptr)
//      {
//         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_puserinteractionParent);
//      }

//      if (puiParent == nullptr && pcreate->m_pappbias.is_set())
//      {
//         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_pappbias->m_puserinteractionParent);
//      }


      /*      if(pinteraction == nullptr && m_puiInitialPlaceHolderContainer != nullptr)
      {
      pinteraction = m_puiInitialPlaceHolderContainer;
      }*/

      /*      if(pinteraction == nullptr && m_bShowPlatform && m_pbergedge->get_document() != nullptr)
      {
      pinteraction = psession->get_document()->get_bergedge_impact();
      }

      return pinteraction;

      }*/

      ::pointer<::aura::application>papp = pinteraction->get_app();

      if (prequest->m_bExperienceMainFrame ||
            papp->m_bExperienceMainFrame ||
            prequest->m_bOuterPopupAlertLike)
      {
         
         return puserinteractionParent;

      }

      //bool bCreateBergedge = false;

      //if(bCreateBergedge)
      //{

      //   if(!create_bergedge(pcreate))
      //   {
      //      return nullptr;


      //   }

      //}

      //auto papp = pinteraction->get_app();

      string strAppName = papp->m_strAppName;

      //if (strAppName != "bergedge")
      //{

      //   if (get_document() != nullptr)
      //   {

      //      //if(get_document()->get_typed_impact < ::bergedge::pane_impact >() != nullptr)
      //      //{

      //      //   get_document()->get_typed_impact < ::bergedge::pane_impact >()->set_current_tab_by_id("app:" + strAppName);

      //      //   puiParent = get_document()->get_typed_impact < ::bergedge::pane_impact >()->get_tab_holder(get_document()->get_typed_impact < ::bergedge::pane_impact >()->get_tab_by_id("app:" + strAppName));

      //      //}
      //      //else
      //      //{

      //      //   puiParent = get_document()->get_typed_impact < ::bergedge::impact >();

      //      //}

      //   }

      //}

      return puserinteractionParent;

   }


} // namespace aura


namespace user
{


   bool is_descendant(::user::interaction* puiParent, ::user::interaction* pinteraction)
      // helper for detecting whether child descendent of parent
      //  (works with owned popups as well)
   {

      if (pinteraction == nullptr)
      {

         return false;

      }

      ::user::interaction* puiAscendant = pinteraction;

      do
      {

         puiAscendant = puiAscendant->get_owner();

         if (puiParent == puiAscendant)
         {

            return true;

         }

      } while (puiAscendant != nullptr);


      puiAscendant = pinteraction;

      do
      {

         puiAscendant = puiAscendant->get_parent();

         if (puiParent == puiAscendant)
         {

            return true;

         }

      } while (puiAscendant != nullptr);


      return false;

   }


   bool user::on_ui_mouse_message(::message::mouse_base * pmouse)
   {

      if (pmouse->m_pointAbsolute == pmouse->m_pointDesired)
      {

         auto psession = session();

         psession->m_pointCursor = pmouse->m_pointAbsolute;

      }

      auto emessage = pmouse->m_emessage;

      if(emessage == e_message_left_button_down
       //|| emessage == e_message_left_button_up
       || emessage == e_message_right_button_down
       //|| emessage == e_message_right_button_up
       || emessage == e_message_middle_button_down
       //|| emessage == e_message_middle_button_up
       )
       {

         if(m_uiptraToolWindow.has_element())
         {

            pointer_array < ::user::interaction > uiptraToolWindow;

            {

               _synchronous_lock synchronouslock(this->synchronization());

               ::generic::container::copy(uiptraToolWindow, m_uiptraToolWindow);

            }

            auto puserinteraction = pmouse->m_pwindow->user_interaction();

            for (auto & pinteraction : uiptraToolWindow)
            {

               if (pinteraction != puserinteraction)
               {

                  if (pinteraction->m_ewindowflag & e_window_flag_focus)
                  {

                     pinteraction->post_message(e_message_kill_focus);

                  }

               }

            }

         }

       }

      //if (m_puserpresence.is_set())
      //{

      //   m_puserpresence->on_ui_mouse_message(pmouse);

      //}
      return true;

   }


   //void user::create_windowing()
   //{

   //   if(m_pdesktopenvironment && windowing())
   //   {

   //      return;

   //   }

   //   //::e_status estatus = ::success;

   //   //estatus =

   //   node()->user_send([this]()
   //   {

   //      print_line("aura::user::create_windowing (1) (aura)");

   //      desktop_environment()->windowing() = windowing();

   //      //__øconstruct(windowing());

   //      //m_pdesktopenvironment->windowing() = windowing();

   //      //debugf("aura::user::create_windowing (2.1)");

   //      //windowing()->initialize_windowing(this);

   //      debugf("aura::user::create_windowing (2.2)\n");

   //      auto paurasystem = psystem;

   //      pauranode->m_pwindowingAuraNode = windowing();

   //      debugf("aura::user::create_windowing end");

   //   });

   //}


   bool user::runnable_step()
   {

      bool bDoneALotOfThings = false;

      _synchronous_lock synchronouslock(m_pmutexRunnable);

      while (m_listRunnable.has_elements() && ::task_get_run())
      {

         auto prunnable = m_listRunnable.pop_front();

         synchronouslock.unlock();

         prunnable->call();

         synchronouslock._lock();

         bDoneALotOfThings = true;

      }

      return bDoneALotOfThings;

   }


   //__namespace_object_factory(user, ::system_setup::flag_object_user);

   
   // ::windowing::windowing* user::windowing()
   // {
   //
   //    auto pwindowing = system()->windowing();
   //
   //    if (pwindowing)
   //    {
   //
   //       if (!pwindowing->m_puser)
   //       {
   //
   //          pwindowing->initialize_windowing(this);
   //
   //       }
   //
   //    }
   //
   //    return pwindowing;
   //
   //    //if (::is_null(windowing()))
   //    //{
   //
   //    //   system()->do_graphics_and_windowing_system_factory();
   //
   //    //   __øconstruct(windowing());
   //
   //    //   windowing()->initialize_windowing(this);
   //
   //    //}
   //
   //    return windowing();
   //
   // }


   // ::aura::application * user::get_app()
   // {
   //
   //    return m_papplication && m_papplication->m_papplication ? m_papplication->m_papplication : nullptr;
   //
   // }
   //
   //
   // ::aura::session * user::get_session()
   // {
   //
   //    return m_papplication ? m_papplication->m_psession : nullptr;
   //
   // }


   // ::windowing::desktop_environment * user::desktop_environment()
   // {
   //
   //    if (!m_pdesktopenvironment)
   //    {
   //
   //       __øconstruct(m_pdesktopenvironment);
   //
   //
   //    }
   //
   //    return m_pdesktopenvironment;
   //
   // }


   //::aura::system * useracmesystem()
   //{

   //   return ::is_set(system()) ? dynamic_cast <::aura::system *> (system()) : nullptr;

   //}

   
   ::pointer<::user::plain_edit>user::create_calculator_edit()
   {

      return __allocate ::user::plain_edit();

   }

   
   void user::add_impact_system(const ::atom & atom, ::user::impact_system * pimpactsystem)
   {

      throw interface_only();

   }


   ::pointer<::user::impact_system> user::impact_system(const ::atom & atom)
   {

      throw interface_only();

   }



   ::pointer < ::menu::menu > user::menu_from_xml(::particle * pparticleContext, const ::scoped_string & scopedstrXml)
   {
      
      throw ::interface_only();
      
      return {};
      
      
   }


} // namespace user


CLASS_DECL_AURA ::particle * user_synchronization()
{

   auto pplatform = platform::get();

   if (::is_null(pplatform))
   {

      return nullptr;

   }

   auto psystem = pplatform->system();

   if (::is_null(psystem))
   {

      return nullptr;

   }

   auto psession = psystem->session();

   if (::is_null(psession))
   {

      return nullptr;

   }

   auto paurasession = psession;

   if (::is_null(paurasession))
   {

      return nullptr;

   }

   auto puser = paurasession->user();

   if (::is_null(puser))
   {

      return nullptr;

   }

   auto pmutexUser = puser->m_pmutexUser;

   if (::is_null(pmutexUser))
   {

      return nullptr;

   }

   return pmutexUser;

}

