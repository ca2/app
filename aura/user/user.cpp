#include "framework.h"
#include "aura/user/_user.h"
#include "aura/update.h"
//#include "simple_view.h"
#include "apex/platform/static_setup.h"
#include "acme/const/simple_command.h"
#include "apex/message/simple_command.h"


::mutex * g_pmutexUser = nullptr;


CLASS_DECL_AURA void initialize_user_mutex();
CLASS_DECL_AURA void finalize_user_mutex();


namespace user
{


   void initialize_children_mutex();
   void finalize_children_mutex();


   user::user()
   {

      m_paxisuser = nullptr;
      m_pbaseuser = nullptr;
      m_pbreduser = nullptr;
      m_pcoreuser = nullptr;
      ::initialize_user_mutex();
      initialize_children_mutex();

   }


   user::~user()
   {

      finalize_children_mutex();
      ::finalize_user_mutex();

   }


   ::e_status user::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::apex::department::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      estatus = create_windowing();

      if (!estatus)
      {

         output_debug_string("\nFailed to create_windowing at user::user::initialize.");

         return estatus;

      }

      return estatus;

   }


   ::user::interaction * user::interaction(oswindow oswindow)
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->window(oswindow);

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pimpl = pwindow->m_pimpl;

      if (::is_null(pimpl))
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   ::user::interaction * user::get_mouse_capture(::thread * pthread)
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->get_mouse_capture(pthread);

      if (::is_null(pwindow))
      {

         return nullptr;

      }

      auto pimpl = pwindow->m_pimpl;

      if (::is_null(pimpl))
      {

         return nullptr;

      }

      return pimpl->m_puserinteractionCapture;

   }


   ::user::interaction * user::get_keyboard_focus(::thread * pthread)
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->get_keyboard_focus(pthread);

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pimpl = pwindow->m_pimpl;

      if (::is_null(pimpl))
      {

         return nullptr;

      }

      return pimpl->m_puserinteractionFocus1;

   }


   ::user::interaction * user::get_active_window(::thread * pthread)
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->get_active_window(pthread);

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pimpl = pwindow->m_pimpl;

      if (::is_null(pimpl))
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   ::e_status user::set_active_window(::user::interaction * puserinteraction)
   {

      ::windowing::window * pwindow = nullptr;

      if (::is_set(puserinteraction))
      {

         pwindow = puserinteraction->get_window();

      }

      auto estatus = pwindow->set_active_window();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   ::user::interaction * user::get_foreground_window()
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pwindow = pwindowing->get_foreground_window();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pimpl = pwindow->m_pimpl;

      if (::is_null(pimpl))
      {

         return nullptr;

      }

      return pimpl->m_puserinteraction;

   }


   ::e_status user::set_foreground_window(::user::interaction * puserinteraction)
   {

      ::windowing::window * pwindow = nullptr;

      if (::is_set(puserinteraction))
      {

         pwindow = puserinteraction->get_window();

      }

      auto estatus = pwindow->set_foreground_window();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   ::user::style* user::get_user_style()
   {

      return nullptr;

   }


   ::e_status user::init1()
   {

      create_factory <::user::button >();
      create_factory <::user::check_box >();
      create_factory <::user::still >();
      //create_factory <::user::document >();
#ifdef WINDOWS_DESKTOP
      create_factory <::user::message_window >();
#endif
      //create_factory <::user::simple_view >();
      //create_factory <::user::place_holder >();
      //create_factory <::user::font_combo_box >();

      //if(get_application()->is_system())
      //{

      //   create_factory <keyboard_layout >();

      //}

      if (!::apex::department::init1())
      {

         return false;

      }

      return true;

   }


   ::e_status user::init()
   {

      if (!::apex::department::init())
      {

         return false;

      }

      create_factory <::user::plain_edit >();



      //auto estatus = create_user_shell();

      //if (!estatus)
      //{

      //   return estatus;

      //}



      TRACE("::user::application::initialize");

      //xml::document docUser;

      //string strUser = pcontext->file().as_string(pcontext->dir().appdata()/"langstyle_settings.xml");

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

      //string strLicense = papplication->get_license_id();


      //::payload & varTopicQuey = psystem->commnam_varTopicQuery;

      auto psystem = get_system();

      bool bHasInstall = psystem->is_true("install");

      bool bHasUninstall = psystem->is_true("uninstall");

      debug_print("user::initialize bHasInstall %c", bHasInstall);

      debug_print("user::initialize bHasUninstall %c", bHasUninstall);

      return true;

   }


   ::e_status user::init2()
   {

      auto estatus = ::apex::department::init2();

      if(!estatus)
      {

         return estatus;

      }

      //estatus = create_windowing();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      return estatus;

   }


   void user::term()
   {


      try
      {


         auto pwindowing = windowing();

         if(::is_set(pwindowing))
         {

            pwindowing->windowing_post_quit();

         }


      }
      catch(...)
      {


      }

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

   }


   ::user::primitive * user::get_mouse_focus_LButtonDown()
   {

      return m_pmousefocusLButtonDown;

   }


   void user::set_mouse_focus_LButtonDown(::user::primitive * pmousefocus)
   {

      synchronization_lock synchronizationlock(mutex());

      m_pmousefocusLButtonDown = pmousefocus;

   }


   void user::defer_remove_mouse_focus_LButtonDown(::user::primitive * pmousefocus)
   {

      synchronization_lock synchronizationlock(mutex());

      if (m_pmousefocusLButtonDown == pmousefocus)
      {

         m_pmousefocusLButtonDown = nullptr;

      }

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

      auto psession = get_session();

      for (auto& papplication : psession->m_applicationa)
      {

         __pointer(::aura::application) papplicationAura = papplication;

         synchronization_lock synchronizationlock(&papplicationAura->m_mutexFrame);

         __pointer(::user::interaction) pinteraction;

         while (papplicationAura->get_frame(pinteraction))
         {

            if (pinteraction != nullptr && pinteraction->is_window())
            {

               pinteraction->send_message(id, wparam, lparam);

               pinteraction->send_message_to_descendants(id, wparam, lparam);

            }

         }

      }

   }


//   ::user::front_end_schema * GetUfeSchema(::context_object * pcontextobject)
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
//   ::user::front_end * GetUfe(::context_object * pcontextobject)
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


   //::e_status user::close_all_documents(bool bEndSession)
   //{

   //   return ::error_interface_only;

   //}


   //__pointer(::user::menu_interaction) user::create_menu_button(::user::style * pstyle, menu_item* pitem)
   //{

   //   return nullptr;

   //}


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


   //CLASS_DECL_AURA __pointer(::user::interaction) create_virtual_window(::object * pobject, u32 dwExStyle, const char * pClassName, const char * lpWindowName, u32 uStyle, const ::rectangle_i32 & rectangle, ::user::interaction * puiParent, id id, HINSTANCE hInstance, LPVOID pParam);


   //CLASS_DECL_AURA __pointer(::user::interaction) create_virtual_window(::object * pobject, u32 dwExStyle, const char * pClassName, const char * pWindowName, u32 uStyle, ::user::interaction * puiParent, id id, HINSTANCE hInstance, LPVOID pParam)
   CLASS_DECL_AURA __pointer(::user::interaction) create_virtual_window(::object * pobject, ::user::interaction * pinteractionParent)
   {

      auto pinteraction = pobject->__create_new < ::user::interaction >();

      if(pinteraction->create_child(pinteractionParent))
      {

         return pinteraction;

      }

      pinteraction.release();

      return nullptr;

   }


} // namespace user


namespace aura
{


   void application::close(::apex::enum_end eend)
   {

      if (eend == ::apex::e_end_close)
      {

         return;

      }

      m_ethreadClose = thread_application;

      //if (get_session())
      //{

      //   if (psession->m_pdocmanager)
      //   {

      //      psession->m_pdocmanager->close_all_documents(true);

      //   }

      //}

      if (eend == ::apex::e_end_app)
      {

         finish(get_context());

         return;

      }

      if (eend == ::apex::e_end_session)
      {

         try
         {

            auto psession = get_session();

            if (psession)
            {

               psession->finish(get_context());

            }

         }
         catch (...)
         {

         }

         return;

      }

      if (eend == ::apex::e_end_system)
      {

         try
         {

            auto psystem = get_system();

            if (psystem)
            {

               psystem->finish(get_context());

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

   //   return new session_docs();

   //}


   //void destroy_session_docs(session_docs * pdocs)
   //{

   //   ::acme::del(pdocs);

   //}


   ::write_text::font_list * session::get_single_column_font_list()
   {

      if (m_pfontlistSingleColumn.is_null())
      {

         __compose(m_pfontlistSingleColumn, __create_new < ::write_text::font_list > ());

         m_pfontlistSingleColumn->set_font_list_type(::write_text::font_list::type_single_column);

         // m_pfontlistSingleColumn->set_need_layout();

      }

      return m_pfontlistSingleColumn;

   }


//   void session::on_app_request_bergedge_callback(::context_object * pcontextobject)
//   {
//
//      if (&App(pobject) != nullptr)
//      {
//
//         psession->m_papplicationCurrent = &App(pobject);
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
////      if (psession->m_papplicationCurrent != nullptr && psession->m_papplicationCurrent->m_psession->m_paccount->m_puser != nullptr)
////      {
////         try
////         {
////            get_view()->get_parent_frame()->set_window_text(psession->m_papplicationCurrent->m_psession->m_paccount->m_puser->m_strLogin);
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

   //bool session::get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)

   //{

   //   if (get_document() != nullptr && get_view() != nullptr)
   //   {

   //      get_view()->get_window_rect(prectangle);


   //      return true;

   //   }
   //   else
   //   {

   //      return ::aura::session::get_monitor_rectangle(iMonitor, prectangle);


   //   }

   //}
   ::type system::get_simple_frame_window_type_info()
   {

      return ::type();

   }





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


   ::user::interaction * session::get_request_parent_ui(::user::interaction * pinteraction, ::create * pcreate)
   {


      __pointer(::user::interaction) puserinteractionParent;

      if (pcreate->m_pcommandline->m_varQuery["uicontainer"].cast < ::user::interaction >() != nullptr)
      {

         puserinteractionParent = pcreate->m_pcommandline->m_varQuery["uicontainer"].cast < ::user::interaction >();

      }

      if (!puserinteractionParent && pcreate->m_puserprimitiveParent)
      {

         puserinteractionParent = pcreate->m_puserprimitiveParent;

      }

//      if (puiParent == nullptr && pcreate != nullptr)
//      {
//         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_puserinteractionParent);
//      }

//      if (puiParent == nullptr && pcreate->m_papplicationbias.is_set())
//      {
//         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_papplicationbias->m_puserinteractionParent);
//      }


      /*      if(pinteraction == nullptr && m_puiInitialPlaceHolderContainer != nullptr)
      {
      pinteraction = m_puiInitialPlaceHolderContainer;
      }*/

      /*      if(pinteraction == nullptr && m_bShowPlatform && m_pbergedge->get_document() != nullptr)
      {
      pinteraction = psession->get_document()->get_bergedge_view();
      }

      return pinteraction;

      }*/

      __pointer(::aura::application) papplication = get_application();

      if (pcreate->m_bClientOnly ||
            papplication->has_property("client_only") ||
            pcreate->m_bOuterPopupAlertLike)
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

      auto papp = pinteraction->get_application();

      string strAppName = papp->m_strAppName;

      //if (strAppName != "bergedge")
      //{

      //   if (get_document() != nullptr)
      //   {

      //      //if(get_document()->get_typed_view < ::bergedge::pane_view >() != nullptr)
      //      //{

      //      //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

      //      //   puiParent = get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName));

      //      //}
      //      //else
      //      //{

      //      //   puiParent = get_document()->get_typed_view < ::bergedge::view >();

      //      //}

      //   }

      //}

      return puserinteractionParent;

   }


} // namespace aura


namespace user
{

   run_application::run_application()
   {

   }

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


   bool user::on_ui_mouse_message(::message::mouse * pmouse)
   {

      if (pmouse->m_point == pmouse->m_pointDesired)
      {

         auto psession = get_session();

         psession->m_pointCursor = pmouse->m_point;

      }

      i64 iMessage = pmouse->m_id;

      if(iMessage == e_message_left_button_down
       //|| iMessage == e_message_left_button_up
       || iMessage == e_message_right_button_down
       //|| iMessage == e_message_right_button_up
       || iMessage == e_message_middle_button_down
       //|| iMessage == e_message_middle_button_up
       )
       {

         if(m_uiptraToolWindow.has_element())
         {

            __pointer_array(::user::interaction) uiptraToolWindow;

            {

               synchronization_lock synchronizationlock(mutex());

               ::papaya::array::copy(uiptraToolWindow, m_uiptraToolWindow);

            }

            for(auto & pinteraction : uiptraToolWindow.ptra())
            {

               if(pinteraction != pmouse->userinteraction())
               {

                  if(pinteraction->m_ewindowflag & e_window_flag_focus)
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


   ::e_status user::create_windowing()
   {

      ::e_status estatus = ::success;

      estatus = ::__construct(m_pwindowing);

      if (!estatus)
      {

#ifdef LINUX

         auto edesktop = psystem->get_edesktop();

         if (edesktop & ::user::e_desktop_kde)
         {

            estatus = psystem->do_factory_exchange("windowing", "xcb");

         }
         else if (edesktop & ::user::e_desktop_gnome)
         {

            estatus = psystem->do_factory_exchange("windowing", "x11");

         }
         else
         {

            estatus = psystem->do_factory_exchange("windowing", "xcb");

            //if (!estatus)
            {

               estatus = psystem->do_factory_exchange("windowing", "x11");

            }

         }

#elif defined(WINDOWS_DESKTOP)

         auto psystem = get_system();

         estatus = psystem->do_factory_exchange("windowing", "win32");

#endif

         if (!estatus)
         {

            return estatus;

         }

         estatus = ::__construct(m_pwindowing);

         if (!estatus)
         {

            return estatus;

         }

      }

      estatus = m_pwindowing->initialize_windowing(this);

      if (!estatus)
      {

         output_debug_string("\nFailed to initialize_windowing at ::user::user::create_windowing");

         return estatus;

      }

      auto psystem = get_system();

      auto pnode = psystem->node();

      pnode->m_pwindowing = m_pwindowing;

      return estatus;

   }




   bool user::runnable_step()
   {

      bool bDoneALotOfThings = false;

      synchronization_lock synchronizationlock(&m_mutexRunnable);

      while (m_listRunnable.has_elements() && ::task_get_run())
      {

         auto prunnable = m_listRunnable.pop_front();

         synchronizationlock.unlock();

         prunnable->operator()();

         synchronizationlock.lock();

         bDoneALotOfThings = true;

      }

      return bDoneALotOfThings;

   }


   __namespace_object_factory(user, ::static_setup::flag_object_user);


} // namespace user


CLASS_DECL_AURA ::mutex * user_mutex()
{

   return g_pmutexUser;

}


CLASS_DECL_AURA void initialize_user_mutex()
{

   if(g_pmutexUser)
   {

      return;

   }

}


CLASS_DECL_AURA void finalize_user_mutex()
{

   if(!g_pmutexUser)
   {

      return;

   }

   delete g_pmutexUser;

}



