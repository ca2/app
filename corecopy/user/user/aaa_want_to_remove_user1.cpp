#include "framework.h"
#include "aura/update.h"
#include "simple_view.h"


namespace user
{


   user::user()
   {

      //m_pufeschema = nullptr;
      //m_pufe = nullptr;

   }


   user::~user()
   {

   }


   ::estatus user::init1()
   {

      create_factory < ::simple_scroll_bar, ::user::scroll_bar>();
      create_factory <::user::document >();
      create_factory <::user::message_queue >();
      create_factory <::user::simple_view >();
      create_factory <::user::still >();
      create_factory <::user::combo_box >();
      create_factory <::user::font_combo_box >();

      //if(get_context_application()->is_system())
      {

         create_factory <keyboard_layout >();

      }

      if (!::aura::department::init1())
      {

         return false;

      }

      return true;

   }


   ::estatus user::init()
   {

      if (!::aura::department::init())
      {

         return false;

      }

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
      //   Session.set_locale(strLangUser,::source_database);

      //if(strStyleUser.has_char())
      //   Session.set_schema(strStyleUser,::source_database);

      string strLicense = Application.get_license_id();


      //var & varTopicQuey = System.commnam_varTopicQuery;

      bool bHasInstall = System.is_true("install");

      bool bHasUninstall = System.is_true("uninstall");

      debug_print("user::initialize bHasInstall %c", bHasInstall);

      debug_print("user::initialize bHasUninstall %c", bHasUninstall);

      if (!::aura::department::init())
      {

         return false;

      }

      return true;

   }


   ::estatus user::init2()
   {

      if(!::aura::department::init2())
         return false;

      return true;

   }


   void user::term()
   {


      //m_puserstyle.release();
//      ::aura::del(m_pufeschema);
//
//      ::aura::del(m_pufe);


      try
      {

         ::aura::department::term();

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


   void user::SendMessageToWindows(UINT message,WPARAM wparam,LPARAM lparam)
   {


      for (auto& papp : Session.m_applicationa)
      {

         sync_lock sl(&papp->m_mutexFrame);

         __pointer(::user::interaction) pinteraction;

         while (papp->get_frame(pinteraction))
         {

            if (pinteraction != nullptr && pinteraction->is_window())
            {

               pinteraction->send_message(message, wparam, lparam);

               pinteraction->send_message_to_descendants(message, wparam, lparam);

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

   ::type user::controltype_to_typeinfo(::user::e_control_type econtroltype)
   {

      return ::type();

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



   CLASS_DECL_CORE __pointer(::user::interaction) create_virtual_window(::object * pobject, u32 dwExStyle, const char * pClassName, const char * lpWindowName, u32 uStyle,

         const ::rect & rect, ::user::interaction * puiParent, id id, HINSTANCE hInstance, LPVOID pParam);



   CLASS_DECL_CORE __pointer(::user::interaction) create_virtual_window(::object * pobject, u32 dwExStyle, const char * pClassName, const char * pWindowName, u32 uStyle, ::user::interaction * puiParent, id id, HINSTANCE hInstance, LPVOID pParam)
   {

      UNREFERENCED_PARAMETER(dwExStyle);
      UNREFERENCED_PARAMETER(pClassName);
      UNREFERENCED_PARAMETER(pWindowName);
      UNREFERENCED_PARAMETER(uStyle);
      UNREFERENCED_PARAMETER(hInstance);
      UNREFERENCED_PARAMETER(pParam);

      auto pinteraction = __new(::user::interaction);

      if(pinteraction->create_window(puiParent, id))
      {

         return pinteraction;

      }

      pinteraction.release();

      return nullptr;

   }




} // namespace user











namespace aura
{


   void application::close(::aura::e_end eend)
   {

      try
      {

         if (m_pdocmanager.is_set())
         {

            m_pdocmanager->close_all_documents(eend != ::aura::end_close);

         }

      }
      catch (...)
      {


      }

      if (eend == ::aura::end_close)
      {

         return;

      }

      m_ethreadClose = thread_application;

      if (get_context_session())
      {

         if (Session.m_pdocmanager)
         {

            Session.m_pdocmanager->close_all_documents(true);

         }

      }

      if (eend == ::aura::end_app)
      {

         set_finish();

         return;

      }

      if (eend == ::aura::end_session)
      {

         try
         {

            if (get_context_session())
            {

               Session.set_finish();

            }

         }
         catch (...)
         {

         }

         return;

      }


      if (eend == ::aura::end_system)
      {

         try
         {

            if (get_context_system())
            {

               System.set_finish();

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

   //   ::aura::del(pdocs);

   //}


   ::draw2d::font_list * session::get_single_column_font_list()
   {

      if (m_pfontlistSingleColumn.is_null())
      {

         __compose(m_pfontlistSingleColumn, __create_new < ::draw2d::font_list > ());

         m_pfontlistSingleColumn->m_etype = ::draw2d::font_list::type_single_column;

         m_pfontlistSingleColumn->set_need_layout();

      }

      return m_pfontlistSingleColumn;

   }


//   void session::on_app_request_bergedge_callback(::object * pobject)
//   {
//
//      if (&App(pobject) != nullptr)
//      {
//
//         Session.m_pappCurrent = &App(pobject);
//
//      }
//
//      if (Session.m_bShowPlatform)
//      {
//         //__pointer(::simple_frame_window) pframeApp = get_document()->get_typed_view < ::bergedge::pane_view >()->get_view_uie();
//         //if(pframeApp != nullptr)
//         //{
//         //   pframeApp->display(display_full_screen);
//         //}
//         //__pointer(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::pane_view >()->GetParentFrame();
//         //if(pframe != nullptr)
//         //{
//         //   pframe->display(display_normal);
//         //}
//      }
//      else
//      {
//         //if(get_document() != nullptr && get_document()->get_typed_view < ::bergedge::view >() != nullptr)
//         //{
//         //   __pointer(::simple_frame_window) pframe = get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame();
//         //   if(pframe != nullptr)
//         //   {
//         //      pframe->display(display_normal);
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
////      if (Session.m_pappCurrent != nullptr && Session.m_pappCurrent->m_psession->m_paccount->m_puser != nullptr)
////      {
////         try
////         {
////            get_view()->GetParentFrame()->set_window_text(Session.m_pappCurrent->m_psession->m_paccount->m_puser->m_strLogin);
////         }
////         catch (...)
////         {
////         }
////      }
//
//   }


   __pointer(::user::document) session::get_document()
   {

      //return m_pdocs->m_pbergedgedocument;
      return nullptr;

   }


   __pointer(::user::impact) session::get_view()
   {

      if (get_document() == nullptr)
      {

         return nullptr;

      }

      return nullptr;

   }


   __pointer(::user::document) session::get_platform()
   {
      //return m_pdocs->m_pplatformdocument;
      return nullptr;
   }

   __pointer(::user::document) session::get_nature()
   {
      //return m_pdocs->m_pnaturedocument;
      return nullptr;
   }

   //bool session::get_monitor_rect(index iMonitor, RECT * prect)

   //{

   //   if (get_document() != nullptr && get_view() != nullptr)
   //   {

   //      get_view()->get_window_rect(prect);


   //      return true;

   //   }
   //   else
   //   {

   //      return ::aura::session::get_monitor_rect(iMonitor, prect);


   //   }

   //}
   ::type system::get_simple_frame_window_type_info()
   {

      return __type(simple_frame_window);

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


      ::user::interaction * puiParent = nullptr;

      if (pcreate->m_pcommandline->m_varQuery["uicontainer"].cast < ::user::interaction >() != nullptr)
         puiParent = pcreate->m_pcommandline->m_varQuery["uicontainer"].cast < ::user::interaction >();

      if (puiParent == nullptr && pcreate->m_puserinteractionParent != nullptr)
      {
         puiParent = dynamic_cast < ::user::interaction * > (pcreate->m_puserinteractionParent);
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
      pinteraction = Session.get_document()->get_bergedge_view();
      }

      return pinteraction;

      }*/

      if (pcreate->m_bClientOnly ||
            Application.has_property("client_only") ||
            pcreate->m_bOuterPopupAlertLike)
      {
         return puiParent;
      }


      //bool bCreateBergedge = false;

      //if(bCreateBergedge)
      //{

      //   if(!create_bergedge(pcreate))
      //   {
      //      return nullptr;


      //   }

      //}




      ::aura::application & app = App(pinteraction->get_context_application());

      string strAppName = app.m_strAppName;

      if (strAppName != "bergedge")
      {

         if (get_document() != nullptr)
         {

            //if(get_document()->get_typed_view < ::bergedge::pane_view >() != nullptr)
            //{

            //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + strAppName);

            //   puiParent = get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_holder(get_document()->get_typed_view < ::bergedge::pane_view >()->get_tab_by_id("app:" + strAppName));

            //}
            //else
            //{

            //   puiParent = get_document()->get_typed_view < ::bergedge::view >();

            //}

         }

      }

      return puiParent;

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
         return false;

      ::user::interaction* puiAscendant = pinteraction;

      do
      {

         puiAscendant = puiAscendant->GetOwner();


         if (puiParent == puiAscendant)
            return true;

      } while (puiAscendant != nullptr);


      puiAscendant = pinteraction;

      do
      {

         puiAscendant = puiAscendant->GetParent();


         if (puiParent == puiAscendant)
            return true;

      } while (puiAscendant != nullptr);


      return false;

   }


} // namespace user





string __get_text(string str)
{

   ::aura::application* papp = ::get_context_application();

   if (papp == nullptr)
   {

      //return Sys(::get_context_system()).__get_text(str);

      return str;

   }

   return papp->__get_text(str);

}


CLASS_DECL_CORE int __c_get_text_length(const char* psz)
{

   string str = __get_text(psz);

   return (int)str.get_length();

}


CLASS_DECL_CORE void __c_get_text(char* pszText, int iLen, const char* psz)
{

   string str = __get_text(psz);

   iLen = MIN(iLen, (int)str.get_length());

   strncpy(pszText, str, iLen);

   pszText[iLen] = '\0';

}








static int g_iWeatherDarkness = 0;

CLASS_DECL_CORE int get_simple_ui_darkness()
{

   return g_iWeatherDarkness;

}

CLASS_DECL_CORE void set_simple_ui_darkness(int iWeatherDarkness)
{

   g_iWeatherDarkness = iWeatherDarkness;

}







COLORREF argb_swap_rb(COLORREF cr)
{
   return ARGB(
      colorref_get_a_value(cr),
      colorref_get_b_value(cr),
      colorref_get_g_value(cr),
      colorref_get_r_value(cr));
}


