#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "acme/const/id.h"
#include "apex/platform/app_core.h"
#include "apex/platform/static_setup.h"
#include "apex/platform/str_context.h"
#include "acme/os/cross/windows/_windows.h"

#ifdef LINUX
void enum_display_monitors(::aura::session * psession);
#endif // LINUX


//namespace PLATFORM_NAMESPACE
//{
//
//   CLASS_DECL_AURA bool adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dGamma);
//
//} // namespace PLATFORM_NAMESPACE


#ifdef WINDOWS_DESKTOP



//#include "base/os/windows/windows_system_interaction_impl.h"


#include <HighLevelMonitorConfigurationAPI.h>

::u32 mc_color_kelvin(MC_COLOR_TEMPERATURE e)
{
   switch (e)
   {
   case MC_COLOR_TEMPERATURE_4000K:
      return 4000;
   case MC_COLOR_TEMPERATURE_5000K:
      return 5000;
   case MC_COLOR_TEMPERATURE_6500K:
      return 6500;
   case MC_COLOR_TEMPERATURE_7500K:
      return 7500;
   case MC_COLOR_TEMPERATURE_8200K:
      return 8200;
   case MC_COLOR_TEMPERATURE_9300K:
      return 9300;
   case MC_COLOR_TEMPERATURE_10000K:
      return 10000;
   case MC_COLOR_TEMPERATURE_11500K:
      return 11500;
   default:
      return 0;
   }
}



#elif defined(LINUX)


#endif



CLASS_DECL_AURA ::user::interaction * create_system_message_window(::layered * pobject);


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

void defer_term_ui();


int_bool point_is_window_origin(POINT32 ptHitTest, oswindow oswindowExclude, int iMargin);

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
      m_paxissession = nullptr;
      m_pbasesession = nullptr;
      m_pcoresession = nullptr;


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


   ::e_status session::initialize(::layered * pobjectContext)
   {

      auto estatus = ::aqua::session::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      m_pimplPendingFocus2             = nullptr;

      m_ecursorDefault                 = cursor_arrow;

      m_ecursor                        = cursor_default;

      m_ecursorDefault                 = cursor_arrow;

      m_ecursor                        = cursor_default;

      m_bDrawCursor                    = false;

      m_pappCurrent                    = nullptr;

      m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_puiCapture = nullptr;

      m_puiMouseMoveCapture = nullptr;

      m_ecursorDefault = cursor_arrow;

      m_ecursor = cursor_default;

      m_puiMouseMoveCapture = nullptr;

      return estatus;

   }


   ::user::style* session::get_user_style()
   {

      return nullptr;

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




   color32_t session::get_default_color(u64 u)
   {

      switch (u)
      {
      case COLOR_3DFACE:
         return ARGB(127, 192, 192, 184);
      case COLOR_WINDOW:
         return ARGB(127, 255, 255, 255);
      case COLOR_3DLIGHT:
         return ARGB(127, 218, 218, 210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127, 238, 238, 230);
      case COLOR_3DSHADOW:
         return ARGB(127, 138, 138, 130);
      case COLOR_3DDKSHADOW:
         return ARGB(127, 90, 90, 80);
      default:
         break;
      }

      return ARGB(127, 0, 0, 0);

   }


   size session::get_window_minimum_size()
   {

      return size(300, 300);

   }


   //::e_status session::init_thread()
   //{

   //   auto estatus = process_init();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   estatus = init_session();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   // // now there is attempt here
   //   //estatus = defer_initialize_host_window();

   //   //if(!estatus)
   //   //{

   //   //   __throw(::exception::exception(estatus));

   //   //}


   //   INFO(".1");

   //   return true;

   //   return estatus;

   //}


   ::e_status session::process_init()
   {

      INFO("aura::session::process_init");

      auto estatus = ::apex::session::process_init();

      if (!estatus)
      {

         return estatus;

      }


      //estatus = __compose_new(m_puserstrcontext);

      //if (!estatus)
      //{

      //   INFO("apex::str_context Failed to Allocate!!");

      //   return estatus;

      //}

      auto& system = System;

      if(system.m_bAvoidFirstResponder)
      {

         m_bAcceptsFirstResponder = false;

      }

      INFO("apex::str_context Succeeded to Allocate!!");

      INFO("aura::session::process_init success");

      return ::success;

   }


   void session::term2()
   {

      ::apex::session::term2();

   }


   void session::term1()
   {

#ifdef WINDOWS

#ifdef WINDOWS_DESKTOP

      if (m_puiSession)
      {

         __user_interaction(m_puiSession)->DestroyWindow();

      }

#endif

#endif

      ::apex::session::term1();

   }


   void session::process_term()
   {

      ::apex::session::process_term();

   }


   bool session::defer_create_session_frame_window()
   {

#ifdef WINDOWS_DESKTOP

      if (m_puiSession)
      {

         return true;

      }

      ::e_status estatus = __compose(m_puiSession, move_transfer(create_system_message_window(this)));

      if (!estatus)
      {

         return false;

      }

#endif

      return true;

   }


   bool session::on_get_thread_name(string& strThreadName)
   {

      if (System.is_console_app())
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

      pcreateNew->m_puserinteractionParent = pcreate->m_puserinteractionParent;

      return open_by_file_extension(pcreateNew);

      //return Application.platform_open_by_file_extension(m_iEdge, pszPathName, pcreate);

   }


   bool session::open_by_file_extension(::create * pcreate)
   {

      //return Application.platform_open_by_file_extension(m_iEdge, pcc);

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

      string strProtocol = System.url().get_protocol(strPathName);

      if (strProtocol == "app")
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

         __throw(todo("filehandler"));

         //System.filehandler().get_extension_app(straApp, strExtension);

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



   bool session::set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor)
   {

      m_ecursor = cursor_draw2d;

      m_pcursor = pcursor;

      if (pcursor != nullptr)
      {

         if (!pcursor->set_current(pinteraction, this))
         {

            return false;

         }

      }
      else
      {

         if (!::draw2d::cursor::reset(pinteraction, this))
         {

            return false;

         }

      }

      return true;

   }


   bool session::set_cursor(::user::interaction * pinteraction, e_cursor ecursor)
   {

      m_ecursor = ecursor;

      ::draw2d::cursor * pcursor = get_cursor();

      if (pcursor != nullptr)
      {

         if (!pcursor->set_current(pinteraction, this))
         {

            return false;

         }

      }
      else
      {

         if (!::draw2d::cursor::reset(pinteraction, this))
         {

            return false;

         }

      }

      return true;

   }


   bool session::set_default_cursor(::user::interaction * pinteraction, e_cursor ecursor)
   {

      if (ecursor == cursor_default)
      {

         m_ecursorDefault = cursor_arrow;

      }
      else
      {

         m_ecursorDefault = ecursor;

      }

      return true;

   }


   //bool session::on_create_frame_window()
   //{

   //   defer_create_session_frame_window();

   //   return true;

   //}


   ::user::primitive * session::GetFocus()
   {

      return System.ui_from_handle(::get_focus());

   }


   ::user::primitive * session::GetActiveWindow()
   {

      return System.ui_from_handle(::get_active_window());

   }


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
//      oswindow oswindowFocus = ::get_focus();
//
//      if (oswindowFocus == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      oswindow oswindow = oswindowFocus;
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


   ::user::keyboard& session::keyboard()
   {

      if (!m_pkeyboard)
      {

         auto estatus = __compose_new(m_pkeyboard);

         if (!m_pkeyboard)
         {

            __throw(::exception::exception("Could not create keyboard"));

         }
//
//#if !defined(WINDOWS) && !defined(__APPLE__)
//
//         if (!m_pkeyboard->initialize())
//         {
//
//            __throw(::exception::exception("Could not initialize keyboard"));
//
//         }
//
//#endif

         //Application.on_create_keyboard();

      }

      return *m_pkeyboard;

   }


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
////      bool bHasFocus = pinteraction->has_focus();
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
////         ::set_focus(pimpl->m_oswindow);
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
////      //            pinteraction->send_message(e_message_kill_focus, (WPARAM) ( (pkeyboardfocus != nullptr &&
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


//   bool session::remove_keyboard_focus(::user::primitive * pprimitive)
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
//         ASSERT(FALSE);
//
//         return false;
//
//      }
//
//      bool bHasFocus = puiImpl->has_focus();
//
//      if (!pimpl->remove_keyboard_focus(pprimitive))
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
//         ::remove_focus(pimpl->m_oswindow);
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
//      //            pinteraction->send_message(e_message_kill_focus, (WPARAM) ( (pkeyboardfocus != nullptr &&
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
//         ASSERT(FALSE);
//
//         return false;
//
//      }
//
//      bool bHasFocus = puiImpl->has_focus();
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
//      //            pinteraction->send_message(e_message_kill_focus, (WPARAM) ( (pkeyboardfocus != nullptr &&
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

   ::user::primitive * session::get_active_ui()
   {

      return nullptr;

   }


   //::user::primitive * session::get_focus_ui()
   //{

   //   auto window = ::get_focus();

   //   if (!window)
   //   {

   //      return nullptr;

   //   }

   //   auto puserinteraction = System.ui_from_handle(window);

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

      user()->set_mouse_focus_LButtonDown(pprimitiveFocus);

      if (pprimitiveFocus == nullptr)
      {

         return;

      }

      __pointer(::user::interaction) puiFocus = pprimitiveFocus;

      if (puiFocus.is_set())
      {

         if (!puiFocus->get_wnd()->is_active())
         {

            if (puiFocus->get_wnd() != nullptr)
            {

               puiFocus->get_wnd()->SetActiveWindow();

            }

         }

         if (puiFocus->get_keyboard_focus() != puiFocus->get_wnd())
         {

            if (puiFocus->get_wnd() != nullptr)
            {

               puiFocus->get_wnd()->SetFocus();

            }

         }

#if defined(APPLE_IOS)

         main_async([this]()
         {

            __pointer(::ios::interaction_impl) pimpl = psession->m_puiHost->m_pimpl;

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

      auto puser = User;

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

   //            sync_lock sl(mutex());

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


   ::draw2d::cursor * session::get_cursor()
   {

      if (m_ecursor == cursor_none)
      {

         return nullptr;

      }
      else if (m_ecursor == cursor_default)
      {

         return System.draw2d().get_cursor(m_ecursorDefault);

      }
      else
      {

         return System.draw2d().get_cursor(m_ecursor);

      }

   }



   void session::get_cursor_pos(POINT32 * ppoint)
   {

#if defined(WINDOWS_DESKTOP)

      if (m_bSystemSynchronizedCursor)
      {

         POINT32 point;

         ::get_cursor_pos(&point);

         m_pointCursor = point;

      }

#endif

      if (ppoint != nullptr)
      {

         *ppoint = m_pointCursor;

      }

   }


   oswindow session::get_capture()
   {

      return ::get_capture();

   }


   bool session::ReleaseCapture()
   {

      ::release_capture();

      m_puiCapture = nullptr;

      return true;

   }


   __pointer(::user::interaction) session::GetCapture()
   {

      oswindow oswindowCapture = ::get_capture();

      if (oswindowCapture == nullptr)
      {

         return nullptr;

      }

      __pointer(::user::interaction) pinteraction = System.ui_from_handle(oswindowCapture);

      if (pinteraction.is_null())
      {

         return nullptr;

      }

      return pinteraction->GetCapture();

   }


   ::user::copydesk& session::copydesk()
   {

      if (!m_pcopydesk)
      {

         __compose(m_pcopydesk);

      }

      return *m_pcopydesk;

   }


   //index session::get_main_wkspace(RECT32 * prect)
   //{

   //   if (m_bSystemSynchronizedScreen)
   //   {

   //      if (m_iMainWkspace >= 0 && m_iMainWkspace < get_monitor_count())
   //      {

   //         return get_main_wkspace(prect);

   //      }
   //      else
   //      {

   //         if (get_monitor_rect(m_iMainWkspace, prect))
   //         {

   //            return m_iMainMonitor;

   //         }
   //         else
   //         {

   //            get_wkspace_rect(0, prect);


   //            return 0;

   //         }

   //      }

   //   }
   //   else
   //   {

   //      index iMainWkspace = m_iMainWkspace;

   //      if (iMainWkspace < 0 || iMainWkspace >= m_rectaWkspace.get_count())
   //      {

   //         iMainWkspace = 0;

   //      }

   //      if (m_rectaWkspace.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      if(prect != nullptr)
   //      {

   //         *prect = m_rectaWkspace[iMainWkspace];

   //      }

   //      return iMainWkspace;

   //   }

   //}


   bool session::set_main_wkspace(index iWkspace)
   {

      if (iWkspace == -1)
      {

         m_iMainWkspace = -1;

         return true;

      }
      else if (iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }
      else
      {

         m_iMainWkspace = iWkspace;

         return true;

      }

   }


#ifdef WINDOWS_DESKTOP

   BOOL CALLBACK session::monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, RECT32* prcMonitor, LPARAM dwData)

   {

      ::aura::session* psystem = (::aura::session*) dwData;

      psystem->monitor_enum(hmonitor, hdcMonitor, prcMonitor);


      return TRUE; // to enumerate all

   }

   void session::monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, RECT32* prcMonitor)

   {

      UNREFERENCED_PARAMETER(hdcMonitor);
      UNREFERENCED_PARAMETER(prcMonitor);


      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);

      xxf_zero(m_monitorinfoa.last());

      m_hmonitora.add(hmonitor);

      m_monitorinfoa.last().cbSize = sizeof(MONITORINFO);

      ::GetMonitorInfo(hmonitor, &m_monitorinfoa.last());

      MONITORINFO mi = m_monitorinfoa.last();

      TRACE("session::monitor_enum\n");
      TRACE("upper_bound %d\n", m_monitorinfoa.get_upper_bound());
      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom);
      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);

   }


#endif

   ::e_status session::finish(::context_object * pcontextobjectFinish)
   {

      return ::aqua::session::finish(pcontextobjectFinish);

   }


   void session::enum_display_monitors()
   {

#ifdef WINDOWS_DESKTOP

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(nullptr, nullptr, &session::monitor_enum_proc, (LPARAM)(dynamic_cast <::aura::session*> (this)));

#elif defined(LINUX)

      ::enum_display_monitors(this);

#endif

   }



   index session::get_main_monitor(RECT32* prect)
   {

      index iMainMonitor = 0;

#ifdef WINDOWS_DESKTOP

      HMONITOR hmonitorPrimary = GetPrimaryMonitorHandle();

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         if (m_hmonitora[iMonitor] == hmonitorPrimary)
         {

            iMainMonitor = iMonitor;

            break;

         }

      }


#endif

      if (prect != nullptr)
      {

         if (!get_monitor_rect(iMainMonitor, prect))
         {

            return -1;

         }

      }

      return iMainMonitor;

   }


   ::count session::get_monitor_count()
   {

#ifdef WINDOWS_DESKTOP

      return m_monitorinfoa.get_count();

#elif defined(MACOS)

      return GetScreenCount();

#elif defined(LINUX)

      sync_lock sl(mutex());

      return m_rectaMonitor.get_count();

#else

      return 1;

#endif

   }


   bool session::get_monitor_rect(index iMonitor, RECT32* prect)
   {

#ifdef _UWP

      return false;

      //prect->left = 0;

      //prect->top = 0;

      //auto puserinteraction = __user_interaction(m_puiHost);

      //prect->right = puserinteraction->layout().sketch().width();

      //prect->bottom = puserinteraction->layout().sketch().height();

      //return true;

#elif MOBILE_PLATFORM

      GetMainScreenRect(prect);

      return true;

#elif defined(WINDOWS_DESKTOP)

      if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }

      *prect = m_monitorinfoa[iMonitor].rcMonitor;


#elif defined(_UWP)


      return false;


#elif defined(LINUX)

      sync_lock sl(mutex());

      if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }

      *prect = m_rectaMonitor[iMonitor];


#elif defined(__APPLE__)

      if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }

      GetScreenRect(prect, (int)iMonitor);


#else

      prect->left = 0;

      prect->top = 0;

      prect->right = oslocal().m_iScreenWidth;

      prect->bottom = oslocal().m_iScreenHeight;


#endif

      return true;

   }


   ::count session::get_desk_monitor_count()
   {

      return get_monitor_count();

   }


   bool session::get_desk_monitor_rect(index iMonitor, RECT32* prect)

   {

      return get_monitor_rect(iMonitor, prect);


   }


   index session::get_main_wkspace(RECT32* prect)

   {

      index iMainWkspace = 0;

#ifdef WINDOWS_DESKTOP

      HMONITOR hwkspacePrimary = GetPrimaryMonitorHandle();

      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         if (m_hmonitora[iWkspace] == hwkspacePrimary)
         {

            iMainWkspace = iWkspace;

            break;

         }

      }


#endif

      if (prect != nullptr)

      {

         get_wkspace_rect(iMainWkspace, prect);


      }

      return iMainWkspace;

   }


   ::count session::get_wkspace_count()
   {

#ifdef WINDOWS_DESKTOP

      return m_monitorinfoa.get_count();

#else

      return get_monitor_count();

#endif

   }


   bool session::get_wkspace_rect(index iWkspace, RECT32* prect)
   {

#ifdef WINDOWS_DESKTOP

      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
         return false;

      *prect = m_monitorinfoa[iWkspace].rcWork;


#elif defined(_UWP)

      return get_monitor_rect(iWkspace, prect);


      //#elif defined(LINUX)
      //
      //return false;
      //
#elif defined(__APPLE__)

      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }

      GetWkspaceRect(prect, (int)iWkspace);


      //      prect->top += ::mac::get_system_main_menu_bar_height();

      //    prect->bottom -= ::mac::get_system_dock_height();

#elif defined(LINUX)

      sync_lock sl(mutex());

      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }

      *prect = m_rectaWkspace[iWkspace];


      return true;

#else

      //__throw(todo());

      //::get_window_rect(::get_desktop_window(),prect);


      get_monitor_rect(iWkspace, prect);


#endif

      return true;

   }


   ::count session::get_desk_wkspace_count()
   {

      return get_wkspace_count();

   }


   bool session::get_desk_wkspace_rect(index iWkspace, RECT32* prect)

   {

      return get_wkspace_rect(iWkspace, prect);


   }


   bool session::set_main_monitor(index iMonitor)
   {

      if (iMonitor == -1)
      {

         m_iMainMonitor = -1;

         return true;

      }
      else if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }
      else
      {

         m_iMainMonitor = iMonitor;

         return true;

      }

   }


   bool session::wkspace_to_monitor(RECT32 * prect, index iMonitor, index iWkspace)
   {

      ::rect rect(*prect);

      ::rect rectWkspace;

      if (!get_wkspace_rect(iWkspace, rectWkspace))
      {

         return false;

      }

      rect -= rectWkspace.top_left();

      ::rect rectMonitor;

      if (!get_monitor_rect(iMonitor, rectMonitor))
      {

         return false;

      }

      rect += rectMonitor.top_left();

      *prect = rect;


      return true;

   }


   bool session::wkspace_to_monitor(RECT32 * prect)
   {

      index iWkspace = get_best_wkspace(nullptr, rect(prect));

      return wkspace_to_monitor(prect, iWkspace, iWkspace);

   }


   bool session::monitor_to_wkspace(RECT32 * prect)
   {

      index iMonitor = get_best_monitor(nullptr, rect(prect));

      return monitor_to_wkspace(prect, iMonitor, iMonitor);

   }


   bool session::monitor_to_wkspace(RECT32 * prect, index iWkspace, index iMonitor)
   {

      ::rect rect(prect);

      ::rect rectMonitor;

      if (!get_monitor_rect(iMonitor, rectMonitor))
      {

         return false;

      }

      rect -= rectMonitor.top_left();

      ::rect rectWkspace;

      if (!get_wkspace_rect(iWkspace, rectWkspace))
      {

         return false;

      }

      rect += rectWkspace.top_left();

      *prect = rect;

      return true;

   }


   void session::get_monitor(rect_array& rectaMonitor, rect_array& rectaIntersect, const rect& rectParam)
   {

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rect rectIntersect;

         ::rect rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(&rectParam, rectMonitor))
            {

               if (rectIntersect.area() >= 0)
               {

                  rectaMonitor.add(rectMonitor);

                  rectaIntersect.add(rectIntersect);

               }

            }

         }

      }

   }


   ::u32 session::get_monitor_color_temperature(index iMonitor)
   {

#ifdef _UWP

      return 0;

#elif defined(LINUX)

      return 0;

#elif defined(MACOS)

      return 0;

#elif defined(APPLE_IOS)

      return 0;

#elif defined(ANDROID)

      return 0;

#else

      if (iMonitor < 0)
      {

         return 0;

      }

      if (iMonitor >= m_hmonitora.get_count())
      {

         return 0;

      }

      MC_COLOR_TEMPERATURE e;

      if (!GetMonitorColorTemperature(m_hmonitora[iMonitor], &e))
      {

         return 0;

      }

      return mc_color_kelvin(e);

#endif

   }

   ::mutex g_monitor_adjust;

   bool session::adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dGamma)
   {

#ifdef _UWP

      return true;

#elif defined(LINUX)

      return true;

#elif defined(MACOS)

      return true;

#elif defined(APPLE_IOS)

      return true;

#elif defined(ANDROID)

      return true;

#else

      sync_lock sl(&g_monitor_adjust);

      return os_adjust_monitor(iMonitor, dwTemperature, dBrightness, dGamma);

#endif

   }


#define ZONEING_COMPARE ::comparison

   i64 g_i_get_best_zoneing = 0;

   index session::_get_best_zoneing(edisplay * pedisplay, ::rect * prect, const ::rect & rectRequest, bool bPreserveSize)
   {

      ::rect rect(rectRequest);

      ::rect rectWkspace;

      index iBestWkspace = get_best_wkspace(&rectWkspace, rect);

      edisplay edisplay;

      ::e_display edisplayPrevious = *pedisplay;

      double dMargin = System.m_dpi;

      if (ZONEING_COMPARE::is_equal(rect.top, rectWkspace.top, dMargin, !(edisplayPrevious & e_display_top)))
      {

         edisplay |= e_display_top;

         if (bPreserveSize)
         {

            rect.move_top_to(rectWkspace.top);

         }
         else
         {

            rect.top = rectWkspace.top;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rect.bottom, rectWkspace.bottom, dMargin, !(edisplayPrevious & e_display_bottom)))
      {

         edisplay |= e_display_bottom;

         if (bPreserveSize)
         {

            rect.move_bottom_to(rectWkspace.bottom);

         }
         else
         {

            rect.bottom = rectWkspace.bottom;

         }

      }

      if (ZONEING_COMPARE::is_equal(rectRequest.left, rectWkspace.left, dMargin, !(edisplayPrevious & e_display_left)))
      {

         edisplay |= e_display_left;

         if (bPreserveSize)
         {

            rect.move_left_to(rectWkspace.left);

         }
         else
         {

            rect.left = rectWkspace.left;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectRequest.right, rectWkspace.right, dMargin, !(edisplayPrevious & e_display_right)))
      {

         edisplay |= e_display_right;

         if (bPreserveSize)
         {

            rect.move_right_to(rectWkspace.right);

         }
         else
         {

            rect.right = rectWkspace.right;

         }

      }

      if (!(edisplay & e_display_top || edisplay & e_display_bottom)
         && is_different(edisplay & e_display_left, edisplay & e_display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.top, rect.top, rect.bottom, rectWkspace.bottom))
         {

            edisplay |= e_display_bottom;

            edisplay |= e_display_top;

            rect.bottom = rectWkspace.bottom;

            rect.top = rectWkspace.top;

         }

      }

      if (!(edisplay & e_display_left || edisplay & e_display_right)
         && is_different(edisplay & e_display_top, edisplay & e_display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.left, rect.left, rect.right, rectWkspace.right))
         {

            edisplay |= e_display_left;

            edisplay |= e_display_right;

            rect.left = rectWkspace.left;

            rect.right = rectWkspace.right;

         }

      }

      bool bLeftXorRight = is_different(edisplay & e_display_left, edisplay & e_display_right);

      bool bTopXorBottom = is_different(edisplay & e_display_top, edisplay & e_display_bottom);

      bool bTopAndBottom = edisplay & e_display_top && edisplay & e_display_bottom;

      bool bLeftAndRight = edisplay & e_display_left && edisplay & e_display_right;

      if (bLeftXorRight && bTopXorBottom)
      {

      }
      else if (bTopAndBottom && bLeftAndRight)
      {

         edisplay = e_display_zoomed;

      }
      else
      {

         if (bLeftXorRight && !bTopAndBottom)
         {

            edisplay = e_display_none;

         }

         if (bTopXorBottom && !bLeftAndRight)
         {

            edisplay = e_display_none;

         }

         if (bTopAndBottom)
         {

            edisplay -= e_display_top;

            edisplay -= e_display_bottom;

         }

         if (bLeftAndRight)
         {

            edisplay -= e_display_left;

            edisplay -= e_display_right;

         }

      }

      if (edisplay == e_display_none)
      {

         edisplay = e_display_normal;

      }

      if (is_docking_appearance(edisplay))
      {

         *prect = rect;

      }
      else if (edisplay == e_display_zoomed)
      {

         *prect = rectWkspace;

      }
      else
      {

         *prect = rectRequest;

      }

      if (pedisplay)
      {

         *pedisplay = edisplay;

      }

      //if (g_i_get_best_zoneing % 10 == 0)
      //{

      //   string strE("e");
      //   if (edisplay & e_display_left)
      //      strE += "L";
      //   if (edisplay & e_display_top)
      //      strE += "T";
      //   if (edisplay & e_display_right)
      //      strE += "R";
      //   if (edisplay & e_display_bottom)
      //      strE += "B";

      //   string strP("p");
      //   if (edisplayPrevious & e_display_left)
      //      strP += "L";
      //   if (edisplayPrevious & e_display_top)
      //      strP += "T";
      //   if (edisplayPrevious & e_display_right)
      //      strP += "R";
      //   if (edisplayPrevious & e_display_bottom)
      //      strP += "B";

      //   ::output_debug_string(
      //      "w" + ::str::from(rectWkspace.left) + ","
      //      + ::str::from(rectWkspace.top) + ","
      //      + ::str::from(rectWkspace.right) + ","
      //      + ::str::from(rectWkspace.bottom) + " " +
      //      "r" + ::str::from(prect->left) + ","
      //      + ::str::from(prect->top) + ","
      //      + ::str::from(prect->right) + ","
      //      + ::str::from(prect->bottom) + " " +
      //      strE + " " + strP + "\n");

      //}


      //g_i_get_best_zoneing++;

      //   rectWkspace.left,
      //   rectWkspace.top,
      //   rectWkspace.right,
      //   rectWkspace.bottom,
      //   (edisplay & e_display_left)?'L':' ',
      //   (edisplay & e_display_top) ? 'T':' ',
      //   (edisplay & e_display_right) ? 'R':' ',
      //   (edisplay & e_display_bottom) ? 'B':' ',
      //   (edisplayPrevious & e_display_left) ? 'L':' ',
      //   (edisplayPrevious & e_display_top) ? 'T':' ',
      //   (edisplayPrevious & e_display_right) ? 'R':' ',
      //   (edisplayPrevious & e_display_bottom) ? 'B':' ');

      return iBestWkspace;

   }


   index session::get_best_monitor(RECT32 * prect, const rect & rectParam, ::e_activation eactivation)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      ::rect rectMatch;

      ::rect rect(rectParam);

      if (eactivation & e_activation_under_mouse_cursor || rect.is_null())
      {

         ::point pointCursor = get_cursor_pos();

         rect.set(pointCursor - ::size(5, 5), ::size(10, 10));

      }

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rect rectIntersect;

         ::rect rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rect, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rect))
            {

               iMatchingMonitor = iMonitor;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingMonitor >= 0)
      {

         if (prect != nullptr)
         {

            *prect = rectMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(prect);

      return iMatchingMonitor;

   }


   index session::get_best_wkspace(::rect * prect, const rect & rectParam, ::e_activation eactivation)
   {

      index iMatchingWkspace = -1;

      i64 iBestArea = -1;

      ::rect rectMatch;

      ::rect rect(rectParam);

      if (eactivation & e_activation_under_mouse_cursor || rect.is_null())
      {

         ::point pointCursor = get_cursor_pos();

         rect.set(pointCursor - ::size(5, 5), ::size(10, 10));

      }

      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         ::rect rectIntersect;

         ::rect rectMonitor;

         if (get_wkspace_rect(iWkspace, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rect, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWkspace;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rect))
            {

               iMatchingWkspace = iWkspace;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingWkspace >= 0)
      {

         if(prect != nullptr)
         {

            *prect = rectMatch;

         }

         return iMatchingWkspace;

      }

      iMatchingWkspace = get_main_wkspace(prect);

      return iMatchingWkspace;

   }


   index session::get_good_iconify(RECT32 * prect, const rect & rectParam)
   {

      ::rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      prect->left = rectMonitor.left;

      prect->top = rectMonitor.top;

      prect->right = rectMonitor.left;

      prect->bottom = rectMonitor.top;

      return iMatchingMonitor;

   }


   index session::initial_frame_position(RECT32 * prect, const rect & rectParam, bool bMove, ::user::interaction * pinteraction)
   {

      ::rect rectRestore(rectParam);

      ::rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      ::size sizeMin;

      if (pinteraction != nullptr)
      {

         sizeMin  = pinteraction->get_window_minimum_size();

      }
      else
      {

         sizeMin = get_window_minimum_size();

      }

      ::rect rectIntersect;

      if (bMove)
      {

         rect_array rectaMonitor;

         rect_array rectaIntersect;

         get_monitor(rectaMonitor, rectaIntersect, rectParam);

         rectaIntersect.get_box(rectIntersect);

      }
      else
      {

         rectIntersect.intersect(rectMonitor, &rectParam);

      }

      auto sizeMax = rectMonitor.size() * 0.9;

      if (rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy
         || rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy )
      {

         if (rectMonitor.width() / 7 + max(sizeMin.cx, rectMonitor.width() * 2 / 5) > rectMonitor.width()
               || rectMonitor.height() / 7 + max(sizeMin.cy, rectMonitor.height() * 2 / 5) > rectMonitor.width())
         {

            rectRestore = rectMonitor;

         }
         else
         {

            rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;

            rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;

            rectRestore.right = rectRestore.left + max(sizeMin.cx, rectMonitor.width() * 2 / 5);

            rectRestore.bottom = rectRestore.top + max(sizeMin.cy, rectMonitor.height() * 2 / 5);

            if (rectRestore.right > rectMonitor.right - rectMonitor.width() / 7)
            {

               rectRestore.offset(rectMonitor.right - rectMonitor.width() / 7 - rectRestore.right, 0);

            }

            if (rectRestore.bottom > rectMonitor.bottom - rectMonitor.height() / 7)
            {

               rectRestore.offset(0, rectMonitor.bottom - rectMonitor.height() / 7 - rectRestore.bottom);

            }

         }

         *prect = rectRestore;

         return iMatchingMonitor;

      }
      else
      {

         if (!bMove)
         {

            *prect = rectIntersect;

         }

         return -1;

      }

   }


   index session::get_window_restore_1(RECT32 * prect, const rect & rectParam, ::user::interaction * pinteraction, edisplay edisplayRestore)
   {

      ::rect rectRestore(rectParam);

      ::rect rectWkspace;

      ::size sizeMin;

      index iMatchingWkspace;

      ::size sizeBroad;

      ::size sizeCompact;

      if (pinteraction != nullptr)
      {

         sizeMin = pinteraction->get_window_minimum_size();

         iMatchingWkspace = pinteraction->calculate_broad_and_compact_restore(rectWkspace, sizeMin, rectParam);

         sizeBroad = pinteraction->m_sizeRestoreBroad;

         sizeCompact = pinteraction->m_sizeRestoreCompact;

      }
      else
      {

         sizeMin = get_window_minimum_size();

         iMatchingWkspace = get_best_wkspace(&rectWkspace, rectParam);

         sizeBroad = sizeMin.max(rectWkspace.size() * 4 / 5);

         sizeCompact = sizeMin.max(rectWkspace.size() * 2 / 5);

      }

      auto rectIntersect = rectWkspace & rectParam;

      auto rectTolerance(rectWkspace);

      auto sizeMax = rectWkspace.size();

      bool b1 = !rectTolerance.contains(rectRestore);
      bool b2 = rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy;
      bool b3 = rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy;
      bool b4 = (edisplayRestore == e_display_compact && rectRestore.size() != sizeCompact);
      bool b5 = (edisplayRestore == e_display_broad && rectRestore.size() != sizeBroad);
      bool b6 = (rectRestore.size() == sizeCompact || rectRestore.size() == sizeBroad);
      bool b66 = !(edisplayRestore == e_display_compact || edisplayRestore == e_display_broad);

      bool bNotHappyWithTheSizeAndOrPosition = b1 || b2 || b3 || b4 || b5 || (b6 && b66);

      if (bNotHappyWithTheSizeAndOrPosition)
      {

         if (edisplayRestore == e_display_broad || sizeCompact == rectRestore.size())
         {

            rectRestore.set_size(sizeBroad);

         }
         else
         {

            rectRestore.set_size(sizeCompact);

         }

         ::rect rectWkspaceBitSmaller(rectWkspace);

         rectWkspaceBitSmaller.deflate(5);

         if (!rectWkspaceBitSmaller.contains(rectRestore))
         {

            rectRestore.move_to(rectWkspace.origin() + rectWkspace.size() / 10);

         }

         *prect = rectRestore;

         return iMatchingWkspace;

      }
      else
      {

         return -1;

      }

   }


   index session::get_window_restore_2(RECT32* prect, const rect& rectParam, ::user::interaction* pinteraction, edisplay edisplayRestore)
   {

      ::rect rect(rectParam);

      index iBestWkspace = get_window_restore_1(prect, rect, pinteraction, edisplayRestore);

      bool bChangedSize = ::size(*prect) != rectParam.size();

      if (iBestWkspace < 0 && !bChangedSize)
      {

         return -1;

      }

      ::rect rectWkspace;

      ::rect rectStart(prect);

      ::point pointLineStart(::top_left(prect));

      get_wkspace_rect(iBestWkspace, rectWkspace);

      if (rectStart > pinteraction->m_sizeRestoreCompact)
      {

         pointLineStart = rectWkspace.origin();

         pointLineStart.offset(49, 49);

         rect.move_to(pointLineStart);

      }

      if(::is_window(pinteraction->get_handle()))
      {

         do
         {

            if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
            {

               return iBestWkspace;

            }

            rect = *prect;

            if (rect > pinteraction->m_sizeRestoreCompact)
            {

               rect.offset(49, 0);

               if (!rectWkspace.contains(rect))
               {

                  pointLineStart.offset(0, 49);

                  rect.move_to(pointLineStart);

                  if (!rectWkspace.contains(rect))
                  {

                     break;

                  }

               }

            }
            else
            {

               rect.offset(49, 49);

            }

            *prect = rect;

         }
         while (rectWkspace.contains(rect));

      }

      if (rect.size() >= pinteraction->m_sizeRestoreCompact)
      {

         pointLineStart = rectWkspace.origin();

         pointLineStart.offset(49, 49);

         rect.move_to(pointLineStart);

         *prect = rect;

         return iBestWkspace;

      }

      rect = rectStart;

      rect.set_size(pinteraction->m_sizeRestoreCompact);

      if(::is_window(pinteraction->get_handle()))
      {

         do
         {

            if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
            {

               return iBestWkspace;

            }

            rect = *prect;

            rect.offset(49, 49);

            *prect = rect;

         } while (rectWkspace.contains(rect));

      }

      pointLineStart = rectWkspace.origin();

      pointLineStart.offset(49, 49);

      rect.move_to(pointLineStart);

      if(::is_window(pinteraction->get_handle()))
      {

         do
         {

            if (!point_is_window_origin(::top_left(prect), pinteraction->get_handle(), 49))
            {

               return iBestWkspace;

            }

            rect = *prect;

            rect.offset(49, 0);

            if (!rectWkspace.contains(rect))
            {

               pointLineStart.offset(0, 49);

               rect.move_to(pointLineStart);

               if (!rectWkspace.contains(rect))
               {

                  break;

               }

            }

            *prect = rect;

         } while (rectWkspace.contains(rect));

      }

      pointLineStart = rectWkspace.origin();

      pointLineStart.offset(49, 49);

      rect.move_to(pointLineStart);

      *prect = rect;

      return iBestWkspace;

   }


   index session::get_good_move(RECT32 * prect, const rect & rectParam, ::user::interaction * pinteraction)
   {

      index iMatchingMonitor = initial_frame_position(prect, rectParam, true, pinteraction);

      if (__memcmp(prect, &rectParam, sizeof(const rect &)))
      {

         return iMatchingMonitor;

      }
      else
      {

         return -1;

      }

   }


   index session::get_ui_wkspace(::user::interaction * pinteraction)
   {

      if (m_bSystemSynchronizedScreen)
      {

         return get_ui_wkspace(pinteraction);

      }
      else
      {

         ::rect rect;

         pinteraction->layout().sketch().screen_rect(rect);

         return get_best_wkspace(nullptr, rect);

      }

   }


   bool session::is_key_pressed(::user::e_key ekey)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;

      }

      bool bPressed = false;
      if (ekey == ::user::key_shift)
      {
         m_pmapKeyPressed->lookup(::user::key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lshift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rshift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_command)
      {
         m_pmapKeyPressed->lookup(::user::key_command, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lcommand, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rcommand, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_control)
      {
         m_pmapKeyPressed->lookup(::user::key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lcontrol, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_rcontrol, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_alt)
      {
         m_pmapKeyPressed->lookup(::user::key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_lalt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->lookup(::user::key_ralt, bPressed);
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


   void session::set_key_pressed(::user::e_key ekey, bool bPressed)
   {

      if (m_pmapKeyPressed == nullptr)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;

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

      sync_lock sl(mutex());

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

      if (System.m_bUser)
      {

         bool bCreateSessionWindow = defer_create_session_frame_window();

         if (!bCreateSessionWindow)
         {

            WARN("Could not create session window");

         }

      }

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

      if (System.m_bUser)
      {

         INFO("success");

         auto psetup = static_setup::get_first(::static_setup::flag_object_user);

         if (psetup)
         {

            estatus = __compose(m_puser, psetup->create_new_object());

         }

         if (!estatus)
         {

            estatus = __compose_new(m_puser);

         }

         if (!estatus || !m_puser)
         {

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

      if (System.m_bDraw2d)
      {

         System.draw2d().enum_draw2d_fonts(m_fontenumitema);

      }

      enum_display_monitors();

      return true;

   }


   ::e_status session::defer_initialize_host_window(LPCRECT32 lpcrect)
   {

#if !defined(APPLE_IOS) && !defined(_UWP) && !defined(ANDROID)

      return ::success;

#else

      if(m_puiHost)
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

      estatus = __refer(m_puiHost, puserinteraction);

      if (!estatus)
      {

         return estatus;

      }

      rect rectScreen(lpcrect);

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

      auto pcs = __new(::user::create_struct(0, nullptr, nullptr, WS_VISIBLE, rectScreen));

      auto puiHost = __user_interaction(m_puiHost);

      if (!puiHost->create_window_ex(pcs))
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

      //if (System.m_bUser)
      //{

      //   if(System.m_bDraw2d)
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

      defer_term_ui();

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


   void session::translate_os_key_message(::user::key * pkey)
   {

      keyboard().translate_os_key_message(pkey);

   }


   void session::pre_translate_message(::message::message * pmessage)
   {

      if (::is_set(m_pappCurrent))
      {

         m_pappCurrent->pre_translate_message(pmessage);

      }

   }


} // namespace aura


#define MAGIC_PALACE_TAB_SPLT "->:<-"
#define MAGIC_PALACE_TAB_SIZE "-/-"
#define MAGIC_PALACE_TAB_TEXT "/"


namespace aura
{






   //::e_status session::initialize(::layered * pobjectContext)
   //{

   //   auto estatus = ::aura::session::initialize(pobjectContext);

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


   ::e_status     session::do_request(::create* pcreate)
   {

      return ::thread::do_request(pcreate);

   }




   void session::request_topic_file(payload& varQuery)
   {

      auto psession = Session;

      request_file(psession->m_varTopicFile, varQuery);

   }


   void session::request_topic_file()
   {

      auto psession = Session;

      request_file(psession->m_varTopicFile);

   }


   __pointer(::aura::application) session::get_current_application()
   {

      auto psession = Session;

      return psession->m_pappCurrent;

   }

   bool session::is_remote_session()
   {


      return Context.os().is_remote_session();


   }


   bool session::is_mouse_button_pressed(::user::enum_mouse emouse)
   {

      auto psession = Session;


      if (emouse == ::user::e_mouse_left_button)
      {
         return psession->is_key_pressed(::user::key_lbutton);
      }
      else if (emouse == ::user::e_mouse_right_button)
      {
         return psession->is_key_pressed(::user::key_rbutton);
      }
      else if (emouse == ::user::e_mouse_middle_button)
      {
         return psession->is_key_pressed(::user::key_mbutton);
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


   void session::check_topic_file_change()
   {

      auto psession = Session;

      if (psession->m_varCurrentViewFile != psession->m_varTopicFile && !psession->m_varTopicFile.is_empty())
      {

         psession->m_varCurrentViewFile = psession->m_varTopicFile;

         request_topic_file();

      }

   }

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


   __pointer(::apex::session) session::get_context_session()
   {

      return this;

   }




   ::draw2d::cursor* session::get_default_cursor()
   {

      return System.draw2d().get_cursor(m_ecursorDefault);

   }


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

      //      str = System.url().url_decode(str);

      //   }

      //   stra.add(str.c_str());

      //}

      return stra;

   }


   ::color session::get_color(const ::user::interaction * puserinteraction, ::user::enum_element eelement, ::user::enum_state estate) const
   {

      if (eelement == ::user::e_element_background)
      {

         color32_t crBk;

         if (::user::is_app_dark_mode())
         {

            crBk = ARGB(255, 0x40, 0x40, 0x40);

         }
         else
         {

            crBk = ARGB(255, 255, 255, 255);

         }

         return crBk;

      }
      else if (eelement == ::user::e_element_face)
      {

         color32_t crBk;

         if (::user::is_app_dark_mode())
         {

            crBk = ARGB(255, 127, 127, 127);

         }
         else
         {

            crBk = ARGB(255, 192, 192, 192);

         }

         return crBk;

      }
      else if (eelement == ::user::e_element_text)
      {

         color32_t crText;

         if (::user::is_app_dark_mode())
         {

            crText = ARGB(255, 255, 255, 255);

         }
         else
         {

            crText = ARGB(255, 49, 50, 42);

         }

         return crText;

      }

      return ::color();

   }


   bool session::get_int(const ::user::interaction* pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate) const
   {

      return false;

   }


   bool session::get_double(const ::user::interaction* pinteraction, double & d, ::user::enum_double eint, ::user::enum_state estate) const
   {

      return false;

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
      //      catch (::exception_pointer pe)
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
      //catch (::exception_pointer pe)
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


   void session::finalize()
   {

      ::apex::session::finalize();

   }


   __namespace_session_factory(session);


} // namespace aura




void os_on_finish_launching()
{

   auto psystem = ::get_context_system();

   auto psession = System.get_context_session();

   auto puiHost = __user_interaction(psession->m_puiHost);

   puiHost->display(e_display_full_screen);

   puiHost->set_need_layout();

   puiHost->set_need_redraw();

   puiHost->post_redraw();

}



