#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
//#endif
//#include "acme/const/id.h"
//#include "apex/platform/app_core.h"
#include "acme/platform/static_setup.h"
//#include "apex/platform/str_context.h"

//#ifdef LINUX
//void enum_display_monitors(::aura::session * psession);
//#endif // LINUX


//namespace PLATFORM_NAMESPACE
//{
//
//   CLASS_DECL_AURA bool adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dGamma);
//
//} // namespace PLATFORM_NAMESPACE






#if defined(APPLE_IOS)

#include "aura/node/ios/interaction_impl.h"

#endif


#if defined(APPLE_IOS) || defined(_UWP) || defined(ANDROID)


namespace PLATFORM_NAMESPACE
{


   CLASS_DECL_AURA ::user::interaction * create_host_window();


} // namespace PLATFORM_NAMESPACE


#endif


#ifdef CUBE
extern "C"
::aura::application * cube_get_app();
#endif

//void defer_term_ui();


#ifdef _UWP

#include "aura/os/uwp/_uwp.h"

#elif defined(LINUX)

void x11_on_start_session();

#endif


namespace aura
{




   session::session()
   {

      m_paurasession = this;

      m_bAcceptsFirstResponder = true;

      m_bSimpleMessageLoop = false;
      m_bMessageThread = true;
      m_iEdge = -1;


      create_factory < ::user::user >();
      create_factory < ::aura::session, ::aura::session >();

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

      output_debug_string("aura::session::~session()");

   }


   ::e_status session::initialize(::object * pobject)
   {

      auto estatus = ::aqua::session::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_pauracontext = this;

      m_pnode = m_psystem->node();

      m_pimplPendingFocus2             = nullptr;

      m_papplicationCurrent                    = nullptr;

      m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_puiMouseMoveCapture = nullptr;

      m_puiMouseMoveCapture = nullptr;

      return estatus;

   }


   ::user::style* session::get_user_style()
   {

      return m_puserstyleDefault;

   }


   bool session::simple_ui_draw_focus_rect(::user::interaction* pinteraction, ::draw2d::graphics_pointer& pgraphics)
   {

      return false;

   }


   void session::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema)
   {


   }


   string session::get_locale_schema_dir()
   {

      return "_std/_std";

   }


   bool session::is_session() const
   {

      return true;

   }


   ::e_status session::process_init()
   {

      INFO("aura::session::process_init");

      auto estatus = ::apex::session::process_init();

      if (!estatus)
      {

         return estatus;

      }


      //estatus = __compose_new(m_ptextcontext);

      //if (!estatus)
      //{

      //   INFO("acme::str_context Failed to Allocate!!");

      //   return estatus;

      //}

      __pointer(::aura::system) psystem = get_system();

      if(psystem->m_bAvoidFirstResponder)
      {

         m_bAcceptsFirstResponder = false;

      }

      INFO("acme::str_context Succeeded to Allocate!!");

      INFO("aura::session::process_init success");

      return ::success;

   }


   void session::term2()
   {

      ::apex::session::term2();

   }


   void session::term1()
   {


      ::apex::session::term1();

   }


   void session::process_term()
   {

      ::apex::session::process_term();

   }




   bool session::on_get_thread_name(string& strThreadName)
   {

      __pointer(::aura::system) psystem = get_system();

      if (psystem->is_console_app())
      {

         return false;

      }

      return ::apex::session::on_get_thread_name(strThreadName);

   }


   void session::on_request(::create * pcreate)
   {

      ::apex::session::on_request(pcreate);

   }


   bool session::open_by_file_extension(const char * pszPathName, ::create * pcreate)
   {

      auto pcreateNew = __create_new < ::create >();

      pcreateNew->m_pcommandline->m_varFile = pszPathName;

      pcreateNew->m_puserprimitiveParent = pcreate->m_puserprimitiveParent;

      return open_by_file_extension(pcreateNew);

      //return papplication->platform_open_by_file_extension(m_iEdge, pszPathName, pcreate);

   }


   bool session::open_by_file_extension(::create * pcreate)
   {

      //return papplication->platform_open_by_file_extension(m_iEdge, pcc);

      string strId;

      string strOriginalPathName(pcreate->m_pcommandline->m_varFile);

      ::file::path strPathName(strOriginalPathName);

      strsize iFind = strPathName.find("?");

      if (iFind >= 0)
      {

         strPathName = strPathName.Left(iFind);

      }

      if (::str::ends_ci(strPathName, ".ca2"))
      {

      }

      auto psystem = m_psystem;

      auto purl = psystem->url();

      string strProtocol = purl->get_protocol(strPathName);

      if (strProtocol == "app")
      {

         strId = purl->get_server(strPathName);

         string str = purl->get_object(strPathName);

         ::str::begins_eat(str, "/");

         pcreate->m_pcommandline->m_varFile = str;

      }
      else
      {

         string strExtension = strPathName.extension();

         string_array straApp;

         __throw(todo, "filehandler");

         //psystem->filehandler().get_extension_app(straApp, strExtension);

         //if (straApp.get_count() == 1)
         //{

         //   strId = straApp[0];

         //}
         //else
         //{

         //   strId = "app/sphere/default_file_handler";

         //}

      }

      ::apex::application* papp = application_get(strId, true, true, pcreate);

      if (papp == nullptr)
      {

         return false;

      }

      papp->do_request(pcreate);

      return true;

   }


   bool session::is_licensed(const char * pszAppId, bool bInteractive)
   {

      if (has_property("install"))
      {

         return true;

      }

      if (has_property("uninstall"))
      {

         return true;

      }

      return false;

      //if(m_paccount.is_null())
      //{

      //   return false;

      //}

      //return m_paccount->is_licensed(pszAppId, bInteractive);

   }


   //::account::user * session::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   //{

   //   if(m_paccount.is_null())
   //   {

   //      return nullptr;

   //   }

   //   return m_paccount->get_user(pathUrl, bFetch, bInteractive);

   //}


//   ::account::user * session::interactive_get_user(::file::path pathUrl)
//   {
//
//      if(m_paccount.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return m_paccount->interactive_get_user();
//
//   }
//
//
//   ::account::user * session::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      if(m_paccount.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return m_paccount->noninteractive_get_user(pathUrl);
//
//   }


   bool session::get_auth(const string & pszForm, string & strUsername, string & strPassword)
   {

      throw 0;

      return false;

      //return account()->get_auth(pszForm, strUsername, strPassword);

   }



   //bool session::set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor)
   //{

   //   m_ecursor = cursor_draw2d;

   //   m_pcursor = pcursor;

   //   if (pcursor != nullptr)
   //   {

   //      if (!pinteraction->set_cursor(pcursor->get_cursor()))
   //      {

   //         return false;

   //      }

   //   }
   //   else
   //   {

   //      if (!::draw2d::cursor::reset(pinteraction, this))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //bool session::set_cursor(::user::interaction * pinteraction, enum_cursor ecursor)
   //{

   //   m_ecursor = ecursor;

   //   ::draw2d::cursor * pcursor = get_cursor();

   //   if (pcursor != nullptr)
   //   {

   //      if (!pinteraction->set_cursor(pcursor->get_cursor()))
   //      {

   //         return false;

   //      }

   //   }
   //   else
   //   {

   //      if (!::draw2d::cursor::reset(pinteraction, this))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //bool session::set_default_cursor(::user::interaction * pinteraction, enum_cursor ecursor)
   //{

   //   if (ecursor == e_cursor_default)
   //   {

   //      m_ecursorDefault = cursor_arrow;

   //   }
   //   else
   //   {

   //      m_ecursorDefault = ecursor;

   //   }

   //   return true;

   //}


   //bool session::on_create_frame_window()
   //{

   //   defer_create_session_frame_window();

   //   return true;

   //}


   //::user::primitive * session::GetActiveWindow()
   //{

   //   return psystem->ui_from_handle(::get_active_window());

   //}


   //::user::primitive * session::clear_focus()
   //{

   //   ::user::primitive * pprimitiveFocus = get_keyboard_focus();

   //   if(::is_null(pprimitiveFocus))
   //   {

   //      return nullptr;

   //   }

   //   auto puserinteraction = pprimitiveFocus->get_wnd();

   //   if(!puserinteraction)
   //   {

   //      return nullptr;

   //   }

   //   puserinteraction->clear_keyboard_focus();

   //   set_keyboard_focus(nullptr);

   //   puserinteraction->set_need_redraw();

   //   puserinteraction->post_redraw();

   //   return pprimitiveFocus;

   //}

//   ::user::primitive * session::get_keyboard_focus()
//   {
//
//      ::windowing::window * pwindowFocus = ::get_keyboard_focus();
//
//      if (oswindowFocus == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      ::windowing::window * pwindow = oswindowFocus;
//
//      while (oswindow != nullptr)
//      {
//
//         ::user::interaction_impl * pimpl = ::oswindow_interaction_impl(oswindow);
//
//         if (pimpl != nullptr)
//         {
//
//            auto pprimitiveFocus = pimpl->get_keyboard_focus();
//
//            if (pprimitiveFocus != nullptr)
//            {
//
//               return pprimitiveFocus;
//
//            }
//
//            return pimpl->m_puserinteraction;
//
//         }
//
//#ifdef WINDOWS_DESKTOP
//
//         oswindow = ::get_parent(oswindow);
//
//         if (oswindow != nullptr)
//         {
//
//            oswindow = ::get_window(oswindow, e_relative_owner);
//
//         }
//
//#else
//
//         break;
//
//#endif
//
//      }
//
//      return nullptr;
//
//   }




//   bool session::set_keyboard_focus(::user::primitive * pprimitive)
//   {
//
//      //m_p
//
////      if (::is_null(pprimitive))
////      {
////
////         m_pimplPendingFocus2 = nullptr;
////
////         ::clear_focus();
////
////         return false;
////
////      }
////
////      ::user::interaction * pinteraction = pprimitive->get_host_window();
////
////      if (::is_null(pinteraction))
////      {
////
////         return false;
////
////      }
////
////      ::user::interaction_impl * pimpl = pinteraction->m_pimpl.cast < ::user::interaction_impl > ();
////
////      if (::is_null(pimpl))
////      {
////
////         return false;
////
////      }
////
////      bool bHasFocus = pinteraction->has_keyboard_focus();
////
////      if (!pimpl->set_keyboard_focus(pprimitive))
////      {
////
////         return false;
////
////      }
////
////      if(bHasFocus)
////      {
////
////         return true;
////
////      }
////
////#ifdef WINDOWS_DESKTOP
////      //if (!IsWindowVisible(pimpl->m_oswindow) || pinteraction->GetExStyle() & WS_EX_LAYERED)
////      if (!IsWindowVisible(pimpl->m_oswindow))
////      {
////
////         pimpl->set_pending_focus();
////
////      }
////      else
////#endif
////      {
////
////         ::set_keyboard_focus(pimpl->m_oswindow);
////
////      }
////
////      return true;
////
////      //::user::primitive * pkeyboardfocusParam = pkeyboardfocus;
////
////      //if (pkeyboardfocus == nullptr)
////      //{
////
////      //   pkeyboardfocus = (::user::primitive *) (ulong_ptr) 1;
////
////      //}
////
////      //if (m_pkeyboardfocus != nullptr && m_pkeyboardfocus != pkeyboardfocus && m_pkeyboardfocusRequest != pkeyboardfocus)
////      //{
////
////      //   ::user::primitive * pkeyboardfocusOld = m_pkeyboardfocus;
////
////      //   m_pkeyboardfocusRequest = pkeyboardfocus;
////
////      //   try
////      //   {
////
////      //      if (pkeyboardfocusOld != nullptr)
////      //      {
////
////      //         output_debug_string("axis::session::set_keyboard_focus pkeyboardfocusOld->keyboard_focus_OnKillFocus()\n");
////
////      //         if (!pkeyboardfocusOld->keyboard_focus_OnKillFocus( (pkeyboardfocus != nullptr &&
////      //               pkeyboardfocus != (::user::primitive *) (ulong_ptr) 1) ?
////      //               pkeyboardfocus->get_safe_handle() : nullptr))
////      //         {
////
////      //            return;
////
////      //         }
////
////      //         __pointer(::user::interaction) pinteraction = pkeyboardfocusOld;
////
////      //         if (pinteraction.is_set())
////      //         {
////
////      //            pinteraction->send_message(e_message_kill_focus, (wparam) ( (pkeyboardfocus != nullptr &&
////      //                              pkeyboardfocus != (::user::primitive *) (ulong_ptr) 1 )?
////      //                              pkeyboardfocus->get_safe_handle() : nullptr));
////
////      //         }
////
////      //      }
////
////      //   }
////      //   catch (...)
////      //   {
////
////      //   }
////
////      //}
////
////      //if (pkeyboardfocus == (::user::primitive *) (ulong_ptr) 1)
////      //{
////
////      //   pkeyboardfocus = nullptr;
////
////      //}
////
////      //if (pkeyboardfocus != nullptr)
////      //{
////
////      //   if (!pkeyboardfocus->keyboard_focus_OnSetFocus())
////      //   {
////
////      //      return;
////
////      //   }
////
////      //   if (pkeyboardfocus->get_wnd() != nullptr)
////      //   {
////
////      //      if (!pkeyboardfocus->get_wnd_primitive()->on_keyboard_focus(pkeyboardfocus))
////      //      {
////
////      //         return;
////
////      //      }
////
////      //   }
////
////      //}
////
////      //m_pkeyboardfocus = pkeyboardfocus;
////
////      //on_finally_focus_set(pkeyboardfocus);
//
//   }


//   bool session::erase_keyboard_focus(::user::primitive * pprimitive)
//   {
//
//      if (pprimitive == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ::user::interaction * pinteraction = pprimitive->get_host_window();
//
//      if (pinteraction == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ::user::interaction * puiImpl = pinteraction->get_host_window();
//
//      if (puiImpl == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ::user::interaction_impl * pimpl = puiImpl->m_pimpl.cast < ::user::interaction_impl >();
//
//      if (pimpl == nullptr)
//      {
//
//         ASSERT(false);
//
//         return false;
//
//      }
//
//      bool bHasFocus = puiImpl->has_keyboard_focus();
//
//      if (!pimpl->erase_keyboard_focus(pprimitive))
//      {
//
//         return false;
//
//      }
//
//      if (!bHasFocus)
//      {
//
//         return true;
//
//      }
////
////#ifdef WINDOWS_DESKTOP
////      //if (!IsWindowVisible(pimpl->m_oswindow) || pinteraction->GetExStyle() & WS_EX_LAYERED)
////      if (!IsWindowVisible(pimpl->m_oswindow))
////      {
////
////         pimpl->set_pending_focus();
////
////      }
////      else
////#endif
//      {
//
//         ::erase_focus(pimpl->m_oswindow);
//
//      }
//
//      return true;
//
//      //::user::primitive * pkeyboardfocusParam = pkeyboardfocus;
//
//      //if (pkeyboardfocus == nullptr)
//      //{
//
//      //   pkeyboardfocus = (::user::primitive *) (ulong_ptr) 1;
//
//      //}
//
//      //if (m_pkeyboardfocus != nullptr && m_pkeyboardfocus != pkeyboardfocus && m_pkeyboardfocusRequest != pkeyboardfocus)
//      //{
//
//      //   ::user::primitive * pkeyboardfocusOld = m_pkeyboardfocus;
//
//      //   m_pkeyboardfocusRequest = pkeyboardfocus;
//
//      //   try
//      //   {
//
//      //      if (pkeyboardfocusOld != nullptr)
//      //      {
//
//      //         output_debug_string("axis::session::set_keyboard_focus pkeyboardfocusOld->keyboard_focus_OnKillFocus()\n");
//
//      //         if (!pkeyboardfocusOld->keyboard_focus_OnKillFocus( (pkeyboardfocus != nullptr &&
//      //               pkeyboardfocus != (::user::primitive *) (ulong_ptr) 1) ?
//      //               pkeyboardfocus->get_safe_handle() : nullptr))
//      //         {
//
//      //            return;
//
//      //         }
//
//      //         __pointer(::user::interaction) pinteraction = pkeyboardfocusOld;
//
//      //         if (pinteraction.is_set())
//      //         {
//
//      //            pinteraction->send_message(e_message_kill_focus, (wparam) ( (pkeyboardfocus != nullptr &&
//      //                              pkeyboardfocus != (::user::primitive *) (ulong_ptr) 1 )?
//      //                              pkeyboardfocus->get_safe_handle() : nullptr));
//
//      //         }
//
//      //      }
//
//      //   }
//      //   catch (...)
//      //   {
//
//      //   }
//
//      //}
//
//      //if (pkeyboardfocus == (::user::primitive *) (ulong_ptr) 1)
//      //{
//
//      //   pkeyboardfocus = nullptr;
//
//      //}
//
//      //if (pkeyboardfocus != nullptr)
//      //{
//
//      //   if (!pkeyboardfocus->keyboard_focus_OnSetFocus())
//      //   {
//
//      //      return;
//
//      //   }
//
//      //   if (pkeyboardfocus->get_wnd() != nullptr)
//      //   {
//
//      //      if (!pkeyboardfocus->get_wnd_primitive()->on_keyboard_focus(pkeyboardfocus))
//      //      {
//
//      //         return;
//
//      //      }
//
//      //   }
//
//      //}
//
//      //m_pkeyboardfocus = pkeyboardfocus;
//
//      //on_finally_focus_set(pkeyboardfocus);
//
//   }


//   bool session::clear_keyboard_focus()
//   {
//
//      auto pprimitive = get_focus_ui();
//
//      if (::is_null(pprimitive))
//      {
//
//         return false;
//
//      }
//
//      ::user::interaction * puiImpl = pprimitive->get_host_window();
//
//      if (puiImpl == nullptr)
//      {
//
//         return false;
//
//      }
//
//      ::user::interaction_impl * pimpl = puiImpl->m_pimpl.cast < ::user::interaction_impl >();
//
//      if (pimpl == nullptr)
//      {
//
//         ASSERT(false);
//
//         return false;
//
//      }
//
//      bool bHasFocus = puiImpl->has_keyboard_focus();
//
//      if (!pimpl->clear_keyboard_focus())
//      {
//
//         return false;
//
//      }
//
//      if (!bHasFocus)
//      {
//
//         return true;
//
//      }
//
////#ifdef WINDOWS_DESKTOP
////      //if (!IsWindowVisible(pimpl->m_oswindow) || pinteraction->GetExStyle() & WS_EX_LAYERED)
////      if (!IsWindowVisible(pimpl->m_oswindow))
////      {
////
////         pimpl->set_pending_focus();
////
////      }
////      else
////#endif
//      {
//
//         ::clear_focus();
//
//      }
//
//      return true;
//
//      //::user::primitive * pkeyboardfocusParam = pkeyboardfocus;
//
//      //if (pkeyboardfocus == nullptr)
//      //{
//
//      //   pkeyboardfocus = (::user::primitive *) (ulong_ptr) 1;
//
//      //}
//
//      //if (m_pkeyboardfocus != nullptr && m_pkeyboardfocus != pkeyboardfocus && m_pkeyboardfocusRequest != pkeyboardfocus)
//      //{
//
//      //   ::user::primitive * pkeyboardfocusOld = m_pkeyboardfocus;
//
//      //   m_pkeyboardfocusRequest = pkeyboardfocus;
//
//      //   try
//      //   {
//
//      //      if (pkeyboardfocusOld != nullptr)
//      //      {
//
//      //         output_debug_string("axis::session::set_keyboard_focus pkeyboardfocusOld->keyboard_focus_OnKillFocus()\n");
//
//      //         if (!pkeyboardfocusOld->keyboard_focus_OnKillFocus( (pkeyboardfocus != nullptr &&
//      //               pkeyboardfocus != (::user::primitive *) (ulong_ptr) 1) ?
//      //               pkeyboardfocus->get_safe_handle() : nullptr))
//      //         {
//
//      //            return;
//
//      //         }
//
//      //         __pointer(::user::interaction) pinteraction = pkeyboardfocusOld;
//
//      //         if (pinteraction.is_set())
//      //         {
//
//      //            pinteraction->send_message(e_message_kill_focus, (wparam) ( (pkeyboardfocus != nullptr &&
//      //                              pkeyboardfocus != (::user::primitive *) (ulong_ptr) 1 )?
//      //                              pkeyboardfocus->get_safe_handle() : nullptr));
//
//      //         }
//
//      //      }
//
//      //   }
//      //   catch (...)
//      //   {
//
//      //   }
//
//      //}
//
//      //if (pkeyboardfocus == (::user::primitive *) (ulong_ptr) 1)
//      //{
//
//      //   pkeyboardfocus = nullptr;
//
//      //}
//
//      //if (pkeyboardfocus != nullptr)
//      //{
//
//      //   if (!pkeyboardfocus->keyboard_focus_OnSetFocus())
//      //   {
//
//      //      return;
//
//      //   }
//
//      //   if (pkeyboardfocus->get_wnd() != nullptr)
//      //   {
//
//      //      if (!pkeyboardfocus->get_wnd_primitive()->on_keyboard_focus(pkeyboardfocus))
//      //      {
//
//      //         return;
//
//      //      }
//
//      //   }
//
//      //}
//
//      //m_pkeyboardfocus = pkeyboardfocus;
//
//      //on_finally_focus_set(pkeyboardfocus);
//
//   }


   //void session::on_finally_focus_set(::user::primitive * pprimitiveFocus)
   //{



   //}

   //::user::primitive * session::get_active_ui()
   //{

   //   return nullptr;

   //}


   //::user::primitive * session::get_focus_ui()
   //{

   //   auto window = ::get_keyboard_focus();

   //   if (!window)
   //   {

   //      return nullptr;

   //   }

   //   auto puserinteraction = psystem->ui_from_handle(window);

   //   if (!puserinteraction)
   //   {

   //      return nullptr;

   //   }

   //   auto puserinteractionFocus = puserinteraction->get_keyboard_focus();

   //   if (!puserinteractionFocus)
   //   {

   //      return puserinteraction;

   //   }

   //   return puserinteractionFocus;

   //}


   void session::on_finally_focus_set(::user::primitive * pprimitiveFocus)
   {

      auto puser = user();

      puser->set_mouse_focus_LButtonDown(pprimitiveFocus);

      if (pprimitiveFocus == nullptr)
      {

         return;

      }

      __pointer(::user::interaction) puiFocus = pprimitiveFocus;

      if (puiFocus.is_set())
      {

         if (!puiFocus->get_wnd()->is_active_window())
         {

            auto pwindow = puiFocus->get_window();

            if (pwindow != nullptr)
            {

               pwindow->set_active_window();

            }

         }

         if (!puiFocus->has_keyboard_focus())
         {

            puiFocus->get_wnd()->set_keyboard_focus();

         }

#if defined(APPLE_IOS)

         main_async([this]()
         {

            __pointer(::ios::interaction_impl) pimpl = psession->get_user_interaction_host()->m_pimpl;

            if (pimpl.is_set())
            {

               pimpl->defer_update_text_view();

            }

         });

#endif

      }


   }


   bool session::on_ui_mouse_message(::message::mouse* pmouse)
   {

      auto puser = user();

      if (!puser)
      {

         return false;

      }

      return puser->on_ui_mouse_message(pmouse);

   }


   //bool session::on_ui_mouse_message(::message::mouse * pmouse)
   //{


   //   //::axis::session::on_ui_mouse_message(pmouse);

   //   if (pmouse->m_point == pmouse->m_pointDesired)
   //   {

   //      m_pointCursor = pmouse->m_point;

   //   }

   //   i64 iMessage = pmouse->m_id;

   //   if(iMessage == e_message_left_button_down
   //    //|| iMessage == e_message_left_button_up
   //    || iMessage == e_message_right_button_down
   //    //|| iMessage == e_message_right_button_up
   //    || iMessage == e_message_middle_button_down
   //    //|| iMessage == e_message_middle_button_up
   //    )
   //    {

   //      if(m_uiptraToolWindow.has_element())
   //      {

   //         __pointer_array(::user::interaction) uiptraToolWindow;

   //         {

   //            synchronous_lock synchronouslock(mutex());

   //            ::papaya::array::copy(uiptraToolWindow, m_uiptraToolWindow);

   //         }

   //         for(auto & pinteraction : uiptraToolWindow.ptra())
   //         {

   //            if(pinteraction != pmouse->userinteraction())
   //            {

   //               if(pinteraction->m_bFocus)
   //               {

   //                  pinteraction->post_message(e_message_kill_focus);

   //               }

   //            }

   //         }

   //      }

   //    }

   //   //if (m_puserpresence.is_set())
   //   //{

   //   //   m_puserpresence->on_ui_mouse_message(pmouse);

   //   //}
   //   return true;

   //}





//   void session::get_cursor_position(POINT_I32 * ppoint)
//   {
//
//#if defined(WINDOWS_DESKTOP)
//
//      if (m_bSystemSynchronizedCursor)
//      {
//
//         POINT_I32 point_i32;
//
//         ::get_cursor_position(&point);
//
//         m_pointCursor = point;
//
//      }
//
//#endif
//
//      if (ppoint != nullptr)
//      {
//
//         *ppoint = m_pointCursor;
//
//      }
//
//   }


   //oswindow session::get_capture()
   //{

   //   return ::get_capture();

   //}



//void session::set_active_guie(::user::interaction * pinteraction)
//{
//
//#ifdef WINDOWS_DESKTOP
//
//   if (pinteraction == nullptr)
//   {
//
//      m_pwindowing->set_active_window(nullptr);
//
//   }
//   else
//   {
//
//      m_pwindowing->set_active_window(pinteraction->get_window());
//
//   }
//
//#endif
//
//}

   //::user::interaction * session::get_capture()
   //{

   //   auto pwindowing = windowing();

   //   auto pinteraction = __interaction(pwindowing->get_capture());

   //   if (::is_null(pinteraction))
   //   {

   //      return nullptr;

   //   }

   //   return pinteraction->get_capture();

   //}


   ::color::color session::get_default_color(u64 u)
   {

      return argb(255, 255, 255, 255);

   }


   ::user::copydesk& session::copydesk()
   {

      if (!m_pcopydesk)
      {

         __compose(m_pcopydesk);

      }

      return *m_pcopydesk;

   }


   //index session::get_main_workspace(RECTANGLE_I32 * prectangle)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      if (m_iMainWorkspace >= 0 && m_iMainWorkspace < get_monitor_count())
   //      {

   //         return get_main_workspace(prectangle);

   //      }
   //      else
   //      {

   //         if (get_monitor_rectangle(m_iMainWorkspace, prectangle))
   //         {

   //            return m_iMainMonitor;

   //         }
   //         else
   //         {

   //            get_workspace_rectangle(0, prectangle);


   //            return 0;

   //         }

   //      }

   //   }
   //   else
   //   {

   //      index iMainWorkspace = m_iMainWorkspace;

   //      if (iMainWorkspace < 0 || iMainWorkspace >= m_rectaWorkspace.get_count())
   //      {

   //         iMainWorkspace = 0;

   //      }

   //      if (m_rectaWorkspace.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      if(prectangle != nullptr)
   //      {

   //         *prectangle = m_rectaWorkspace[iMainWorkspace];

   //      }

   //      return iMainWorkspace;

   //   }

   //}




   ::e_status session::finish()
   {

      return ::aqua::session::finish();

   }




   bool session::is_key_pressed(::user::enum_key ekey)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::enum_key, bool >;

      }

      bool bPressed = false;
      if (ekey == ::user::e_key_shift)
      {
         m_pmapKeyPressed->lookup(::user::e_key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_lshift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_rshift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_command)
      {
         m_pmapKeyPressed->lookup(::user::e_key_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_lcommand, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_rcommand, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_control)
      {
         m_pmapKeyPressed->lookup(::user::e_key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_lcontrol, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_rcontrol, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::e_key_alt)
      {
         m_pmapKeyPressed->lookup(::user::e_key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_lalt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::e_key_ralt, bPressed);
         if (bPressed)
            goto ret;
      }
      else
      {

         m_pmapKeyPressed->lookup(ekey, bPressed);

      }

ret:

      return bPressed;

   }


   void session::set_key_pressed(::user::enum_key ekey, bool bPressed)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::enum_key, bool >;

      }

      (*m_pmapKeyPressed)[ekey] = bPressed;

   }


   void session::set_bound_ui(::id idView, ::user::interaction * pinteraction)
   {

      m_mapboundui.set_at(idView, pinteraction);

   }


   ::user::primitive * session::get_bound_ui(::id idView)
   {

      auto p = m_mapboundui.plookup(idView);

      if (!p)
      {

         return nullptr;

      }

      return p->m_element2;

   }


   void session::on_show_user_input_popup(::user::interaction * pinteraction)
   {

      synchronous_lock synchronouslock(mutex());

      try
      {

         if (m_puiLastUserInputPopup != nullptr
               && m_puiLastUserInputPopup != pinteraction)
         {

            m_puiLastUserInputPopup->display(e_display_none);

         }

      }
      catch (...)
      {

      }

      m_puiLastUserInputPopup = pinteraction;

   }


   ::e_status session::init1()
   {

      auto estatus = ::apex::session::init1();

      if (!estatus)
      {

         return estatus;

      }

      //auto estatus = __compose_new(m_pfs);

      //if (!estatus)
      //{

      //   m_result.add(estatus);

      //   return false;

      //}

      //if (psystem->m_bUser)
      //{

      //}

      //if (!m_pifs)
      //{

      //   estatus = __compose(m_pifs, __new(ifs("")));

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      TRACE("Failed to create ifs");

      //   }

      //}

      //if (!m_premotefs)
      //{

      //   estatus = __compose(m_premotefs, __new(::fs::remote_native("")));

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      TRACE("Failed to create remotefs");

      //   }

      //}

      //if (!m_pfsdata)
      //{

      //   auto pset = __create_new<::fs::set>();

      //   auto plink = __create_new < ::fs::link>();

      //   plink->fill_os_user();

      //   pset->m_spafsdata.add(plink);

      //   pset->m_spafsdata.add(__create_new < ::fs::native>());

      //   estatus = __compose(m_pfsdata, pset);

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      TRACE("Failed to create fsdata");

      //   }

      //}

      INFO(".2");

      __pointer(::aura::system) psystem = get_system();

      if (psystem->m_bUser)
      {

         INFO("success");

         auto psetup = static_setup::get_first(::static_setup::flag_object_user);

         if (psetup)
         {

            estatus = __compose(m_puser, psetup->create_new_object());

            if(!estatus)
            {

               output_debug_string("\nFailed to __compose(m_puser)");

            }

         }

         if (!estatus)
         {

            estatus = __compose_new(m_puser);

         }

         if (!estatus || !m_puser)
         {

            output_debug_string("\nFailed to __compose_new(m_puser)");

            ERR(".4");

            return false;

         }

         INFO("end");

         if (!m_puser->init1())
         {

            return false;

         }

         if (!m_puser->init2())
         {

            return false;

         }


      }

     

      return true;

   }


   ::e_status session::defer_initialize_host_window(const RECTANGLE_I32 * lpcrect)
   {

#if !defined(APPLE_IOS) && !defined(_UWP) && !defined(ANDROID)

      return ::success;

#else

      if(m_puserinteractionHost)
      {

         return ::success;

      }

      auto puserinteraction = ::PLATFORM_NAMESPACE::create_host_window();

      if(!puserinteraction)
      {

         return ::error_failed;

      }

      auto estatus = puserinteraction->initialize(get_context_system());

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_puserinteractionHost, puserinteraction);

      if (!estatus)
      {

         return estatus;

      }

      rectangle_i32 rectScreen(lpcrect);

//      if(::is_null(lprect))
//      {
//
//         get_main_monitor(rectScreen);
//
//      }
//      else
//      {
//
//         rectScreen = *lprect;
//
//      }

      auto pcs = __new(::user::system(0, nullptr, nullptr, WS_VISIBLE, rectScreen));

      auto puserinteractionHost = __user_interaction(m_puserinteractionHost);

      if (!puserinteractionHost->create_window_ex(pcs))
      {

         return ::error_failed;

      }

//      puserinteraction->place(rectScreen);
//
//      puserinteraction->display(e_display_normal);
//
//      puserinteraction->set_need_layout();
//
//      puserinteraction->set_need_redraw();
//
//      puserinteraction->post_redraw();

      return true;

#endif

   }


   ::e_status session::init2()
   {

      ::e_status estatus = ::apex::session::init2();

      if (!estatus)
      {

         return estatus;

      }

      INFO("aura::session::init2 .1");

      //if (psystem->m_bUser)
      //{

      //   if(psystem->m_bDraw2d)
      //   {

      //

      //   }

      //}

     /* if (!InitializeLocalDataCentral())
      {

         message_box("Could not initialize Local data central");

         return false;

      }*/

      estatus = __compose_new(m_psavings);

      return estatus;

   }


   ::e_status session::init()
   {

      ::e_status estatus = ::apex::session::init();

      __compose_new(m_puserstyleDefault);

      m_puserstyleDefault->default_style_construct();

      //__pointer(::fs::set) pfsset = m_pfsdata;

      //if (m_bIfs)
      //{

      //   if (m_pfsdata.is_null())
      //   {

      //      __compose(m_pfsdata, __new(::fs::set));

      //   }

      //   pfsset = m_pfsdata;

      //   if (pfsset.is_null())
      //   {

      //      pfsset->m_spafsdata.add_unique(m_pifs);

      //      pfsset->m_spafsdata.add_unique(m_premotefs);

      //   }

      //   ::file::listing patha;

      //   m_pfsdata->root_ones(patha);

      //}

      if (m_puser)
      {

         estatus = m_puser->init();

         if (!estatus)
         {

            return estatus;

         }

      }

      return estatus;

   }


   void session::term()
   {

      ::apex::session::term();

      if (m_puser)
      {

         try
         {

            m_puser->term();

         }
         catch (...)
         {

         }

         __release(m_puser);

      }


      try
      {

         if (m_pcopydesk.is_set())
         {

            m_pcopydesk->finalize();

            __release(m_pcopydesk);

         }

      }
      catch (...)
      {

      }

      auto puser = m_puser;

      if (puser)
      {

         auto pwindowing = puser->m_pwindowing;

         pwindowing->defer_term_ui();

      }

   }


   ::u32 session::get_Long_PhRESSing_time()
   {

      return m_dwLongPhRESSingTime;

   }


   //void session::defer_initialize_user_presence()
   //{

   //   userpresence().defer_initialize_user_presence();

   //}


   bool session::on_create_frame_window()
   {

      return true;

   }


   //void session::translate_os_key_message(::user::key * pkey)
   //{

     // keyboard().translate_os_key_message(pkey);

   //}


   void session::pre_translate_message(::message::message * pmessage)
   {

      if (::is_set(m_papplicationCurrent))
      {

         m_papplicationCurrent->pre_translate_message(pmessage);

      }

   }


} // namespace aura


#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace aura
{






   //::e_status session::initialize(::object * pobject)
   //{

   //   auto estatus = ::aura::session::initialize(pobject);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }


   //   return estatus;

   //}


   void session::install_message_routing(::channel* pchannel)
   {

      ::thread::install_message_routing(pchannel);

   //   //aura::application::install_message_routing(pchannel);
   //   aura::session::install_message_routing(pchannel);

   }



   void session::_001OnFileNew()
   {

   }


   void session::launch_app(const char* psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   void session::install_app(const char* psz)
   {

      UNREFERENCED_PARAMETER(psz);

   }


   void session::do_request(::create* pcreate)
   {

      return ::thread::do_request(pcreate);

   }




   //void session::request_topic_file(::payload& varQuery)
   //{

   //   auto psession = get_session();

   //   request_file(psession->m_varTopicFile, varQuery);

   //}


   //void session::request_topic_file()
   //{

   //   auto psession = get_session();

   //   request_file(psession->m_varTopicFile);

   //}


   __pointer(::aura::application) session::get_current_application()
   {

      auto psession = get_session();

      return psession->m_papplicationCurrent;

   }


   bool session::is_remote_session()
   {

      auto pcontext = get_context();

      return pcontext->m_papexcontext->os().is_remote_session();

   }


   bool session::is_mouse_button_pressed(::user::enum_mouse emouse)
   {

      if (emouse == ::user::e_mouse_left_button)
      {

         return is_key_pressed(::user::e_key_lbutton);

      }
      else if (emouse == ::user::e_mouse_right_button)
      {

         return is_key_pressed(::user::e_key_rbutton);

      }
      else if (emouse == ::user::e_mouse_middle_button)
      {

         return is_key_pressed(::user::e_key_mbutton);

      }
      else
      {

         __throw(::exception::exception("not expected enum_mouse value"));

      }

   }


   bool session::open_file(::filemanager::data* pdata, ::file::item_array& itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      if (itema.get_size() > 0)
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


   //void session::check_topic_file_change()
   //{

   //   if (m_varCurrentViewFile != m_varTopicFile && !m_varTopicFile.is_empty())
   //   {

   //      m_varCurrentViewFile = m_varTopicFile;

   //      request_topic_file();

   //   }

   //}

   //}

   bool session::place(::user::main_frame* pmainframe, ::create* pcreate)
   {

      //get_place_holder(pmainframe, pcreate).hold(pmainframe);

      return true;

   }





   void session::set_app_title(const char* pszAppId, const char* pszTitle)
   {

      __pointer(::apex::application) papp;

      if (m_applicationa.lookup(pszAppId, papp) && papp)
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


   //__pointer(::apex::session) session::get_session()
   //{

   //   return this;

   //}






   ::e_status     session::main()
   {

      //return ::aura::session::main();
      return ::thread::main();

   }


   string_array session::get_user_wallpaper()
   {

      string_array stra;

      //string_array straSource = psession->userex()->get_wallpaper();

      //for (string str : straSource)
      //{

      //   if (::str::begins_eat_ci(str, "file://"))
      //   {

      //      str = purl->url_decode(str);

      //   }

      //   stra.add(str.c_str());

      //}

      return stra;

   }


   ::color::color session::get_color(const ::user::interaction * puserinteraction, ::user::enum_element eelement, ::user::enum_state estate) const
   {

      if (eelement == ::user::e_element_background)
      {

         color32_t crBk;

         __pointer(::aura::system) psystem = get_system();

         if (m_pnode && m_pnode->is_app_dark_mode())
         {

            crBk = argb(255, 0x40, 0x40, 0x40);

         }
         else
         {

            crBk = argb(255, 255, 255, 255);

         }

         return crBk;

      }
      else if (eelement == ::user::e_element_face)
      {

         color32_t crBk;

         __pointer(::aura::system) psystem = get_system();

         if (m_pnode && m_pnode->is_app_dark_mode())
         {

            crBk = argb(255, 127, 127, 127);

         }
         else
         {

            crBk = argb(255, 192, 192, 192);

         }

         return crBk;

      }
      else if (eelement == ::user::e_element_text)
      {

         color32_t crText;

         __pointer(::aura::system) psystem = get_system();

         if (m_pnode && m_pnode->is_app_dark_mode())
         {

            crText = argb(255, 255, 255, 255);

         }
         else
         {

            crText = argb(255, 49, 50, 42);

         }

         return crText;

      }

      return ::color::color();

   }


   bool session::get_int(const ::user::interaction* pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate) const
   {

      return false;

   }


   bool session::get_double(const ::user::interaction* pinteraction, double & d, ::user::enum_double eint, ::user::enum_state estate) const
   {

      return false;

   }


   void session::on_instantiate_application(::apex::application* papp)
   {

      ::aqua::session::on_instantiate_application(papp);

      papp->m_paurasession = this;
      papp->m_paurasystem = m_paurasystem;
      papp->m_pauranode = m_pauranode;

   }


   //void session::frame_pre_translate_message(::message::message* pmessage)
   //{

   //   if (pmessage->m_id == WM_GETTEXT
   //      || pmessage->m_id == WM_GETTEXTLENGTH
   //      )
   //   {

   //      pmessage->m_uiMessageFlags |= 3; // message considered pre translated
   //      pmessage->m_uiMessageFlags |= 16384; //  by early optmization

   //      return;

   //   }
   //   //else if (pmessage->m_id == e_message_mouse_move)
   //   //{

   //   //   pmessage->m_uiMessageFlags |= 0; // message considered pre translated
   //   //   pmessage->m_uiMessageFlags |= 16384; //  by early optmization

   //   //   return;

   //   //}

   //   //try
   //   //{

   //   //   __pointer(::user::interaction) pinteraction;

   //   //   while (get_frame(pinteraction))
   //   //   {

   //   //      try
   //   //      {

   //   //         if (pinteraction != nullptr)
   //   //         {

   //   //            pinteraction->pre_translate_message(pmessage);

   //   //            if (pmessage->m_bRet)
   //   //               return;

   //   //         }

   //   //      }
   //   //      catch (const ::exception::exception & e)
   //   //      {

   //   //         if (e.is < ::exit_exception>())
   //   //         {

   //   //            __rethrow(::move(e));

   //   //         }

   //   //      }
   //   //      catch (...)
   //   //      {
   //   //      }

   //   //   }

   //   //}
   //   //catch (const ::exception::exception & e)
   //   //{

   //   //   if (e.is < ::exit_exception>())
   //   //   {

   //   //      __rethrow(::move(e));

   //   //   }

   //   //}
   //   //catch (...)
   //   //{

   //   //   pmessage->m_bRet = true;

   //   //}

   //}


   ::e_status session::finalize()
   {

      auto estatus = ::apex::session::finalize();

      return estatus;

   }


   __namespace_session_factory(session);


} // namespace aura


namespace aura
{


   void system::on_finish_launching()
   {

      auto psession = get_session();

      auto puserinteractionHost = psession->m_puserprimitiveHost.cast < ::user::interaction>();

      puserinteractionHost->display(e_display_full_screen);

      puserinteractionHost->set_need_layout();

      puserinteractionHost->set_need_redraw();

      puserinteractionHost->post_redraw();

   }


} // namespace aura



