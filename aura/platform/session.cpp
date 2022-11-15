#include "framework.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/networking/url_department.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system_setup.h"
#include "apex/platform/create.h"
#include "apex/platform/os_context.h"
#include "apex/platform/savings.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/window.h"
#include "aura/user/user/user.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
#include "aura/platform/application.h"


#if defined(APPLE_IOS) || defined(_UWP) || defined(ANDROID)


namespace OPERATING_SYSTEM_NAMESPACE
{


   CLASS_DECL_AURA ::user::interaction * create_host_window();


} // namespace OPERATING_SYSTEM_NAMESPACE


#endif


#ifdef CUBE
extern "C"
::aura::application * cube_get_app();
#endif

//void defer_term_ui();


#ifdef _UWP

//#include "aura/operating_system/universal_windows/_universal_windows.h"

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


      //add_factory_item < ::user::user >();
      //add_factory_item < ::aura::session, ::aura::session >();

      //m_XstrAppId                    = "core_session";
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


   void session::on_initialize_particle()
   {

      //auto estatus = 
      
      ::aqua::session::on_initialize_particle();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      ::aura::context::on_initialize_particle();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //estatus = ::user::style_base::on_initialize_particle();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void session::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::aqua::session::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pauracontext = this;

      //m_pnode = acmenode();

      m_pimplPendingFocus2             = nullptr;

      m_pappCurrent                    = nullptr;

      m_puiLastLButtonDown             = nullptr;

      m_pmapKeyPressed                 = nullptr;

      m_puiMouseMoveCapture            = nullptr;

      m_puiMouseMoveCapture = nullptr;

      m_puiMouseMoveCapture = nullptr;

      //return estatus;

   }


   //void session::_on_initialize_window_object()
   //{

   //   auto estatus = ::aqua::session::_on_initialize_window_object();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   __construct_new(m_puserstyle);

   //   m_puserstyle->default_style_construct();

   //   return estatus;


   //}

   //::user::style* session::get_user_style()
   //{

   //   return m_puserstyleDefault;

   //}


   //bool session::simple_ui_draw_focus_rect(::user::interaction* pinteraction, ::draw2d::graphics_pointer& pgraphics)
   //{

   //   return false;

   //}


   void session::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema)
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


   void session::process_init()
   {

      INFORMATION("aura::session::process_init");

      //auto estatus = 
      
      ::apex::session::process_init();

      //if (!estatus)
      //{

      //   return estatus;

      //}


      //estatus = __construct_new(m_ptextcontext);

      //if (!estatus)
      //{

      //   INFORMATION("acme::str_context Failed to Allocate!!");

      //   return estatus;

      //}

      auto psystem = get_system()->m_paurasystem;

      if(psystem->m_bAvoidFirstResponder)
      {

         m_bAcceptsFirstResponder = false;

      }

      INFORMATION("acme::str_context Succeeded to Allocate!!");

      INFORMATION("aura::session::process_init success");

      //return ::success;

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




   bool session::on_get_task_name(string& strThreadName)
   {

      auto psystem = get_system()->m_paurasystem;

      if (psystem->is_console_app())
      {

         return false;

      }

      return ::apex::session::on_get_task_name(strThreadName);

   }


   void session::on_request(::create * pcreate)
   {

      ::apex::session::on_request(pcreate);

   }


   bool session::open_by_file_extension(const ::string & pszPathName, ::create * pcreate)
   {

      auto pcreateNew = __create_new < ::create >();

      pcreateNew->m_payloadFile = pszPathName;

      pcreateNew->m_puserprimitiveParent = pcreate->m_puserprimitiveParent;

      return open_by_file_extension(pcreateNew.get());

      //return papp->platform_open_by_file_extension(m_iEdge, pszPathName, pcreate);

   }


   bool session::open_by_file_extension(::create * pcreate)
   {

      //return papp->platform_open_by_file_extension(m_iEdge, pcc);

      string strId;

      string strOriginalPathName(pcreate->m_payloadFile.get_string());

      ::file::path strPathName(strOriginalPathName);

      strsize iFind = strPathName.find("?");

      if (iFind >= 0)
      {

         strPathName = strPathName.Left(iFind);

      }

      if (strPathName.ends_ci(".ca2"))
      {

      }

      auto psystem = acmesystem();

      auto purl = psystem->url();

      string strProtocol = purl->get_protocol(strPathName);

      if (strProtocol == "app")
      {

         strId = purl->get_server(strPathName);

         string str = purl->get_object(strPathName);

         str.begins_eat("/");

         pcreate->m_payloadFile = str;

      }
      else
      {

         string strExtension = strPathName.final_extension();

         string_array straApp;

         throw ::exception(todo, "filehandler");

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

      auto papp = application_get(strId, true, true, pcreate);

      if (papp == nullptr)
      {

         return false;

      }

      papp->do_request(pcreate);

      return true;

   }


   bool session::is_licensed(const ::string & pszAppId, bool bInteractive)
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
////      //         ::pointer<::user::interaction>pinteraction = pkeyboardfocusOld;
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
//      //         ::pointer<::user::interaction>pinteraction = pkeyboardfocusOld;
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
//      //         ::pointer<::user::interaction>pinteraction = pkeyboardfocusOld;
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

      ::pointer<::user::interaction>puiFocus = pprimitiveFocus;

      if (puiFocus.is_set())
      {

         if (!puiFocus->get_wnd()->is_active_window())
         {

            auto pwindow = puiFocus->window();

            if (pwindow != nullptr)
            {

               pwindow->set_active_window();

            }

         }

         if (!puiFocus->has_keyboard_focus())
         {

            puiFocus->get_wnd()->set_keyboard_focus();

         }

//#if defined(APPLE_IOS)
//
//         main_async([this]()
//         {
//
//            ::pointer<::ios::interaction_impl>pimpl = psession->get_user_interaction_host()->m_pimpl;
//
//            if (pimpl.is_set())
//            {
//
//               pimpl->defer_update_text_impact();
//
//            }
//
//         });
//
//#endif

      }


   }


   bool session::on_ui_mouse_message(::message::mouse_base * pmouse)
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

   //   i64 iMessage = pmouse->m_atom;

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

   //         pointer_array < ::user::interaction > uiptraToolWindow;

   //         {

   //            synchronous_lock synchronouslock(this->synchronization());

   //            ::acme::container::copy(uiptraToolWindow, m_uiptraToolWindow);

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

   //      if (iMainWorkspace < 0 || iMainWorkspace >= m_rectangleaWorkspace.get_count())
   //      {

   //         iMainWorkspace = 0;

   //      }

   //      if (m_rectangleaWorkspace.get_count() <= 0)
   //      {

   //         return -1;

   //      }

   //      if(prectangle != nullptr)
   //      {

   //         *prectangle = m_rectangleaWorkspace[iMainWorkspace];

   //      }

   //      return iMainWorkspace;

   //   }

   //}


   void session::destroy()
   {

      return ::aqua::session::destroy();

   }


//   bool session::is_key_pressed(::user::enum_key ekey)
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (m_pmapKeyPressed == nullptr)
//      {
//
//         m_pmapKeyPressed = memory_new ::map < ::user::enum_key, bool >;
//
//      }
//
//      bool bPressed = false;
//      if (ekey == ::user::e_key_shift)
//      {
//         m_pmapKeyPressed->lookup(::user::e_key_shift, bPressed);
//         if (bPressed)
//            goto ret;
//         m_pmapKeyPressed->lookup(::user::e_key_left_shift, bPressed);
//         if (bPressed)
//            goto ret;
//         m_pmapKeyPressed->lookup(::user::e_key_right_shift, bPressed);
//         if (bPressed)
//            goto ret;
//      }
//      else if (ekey == ::user::e_key_command)
//      {
//         m_pmapKeyPressed->lookup(::user::e_key_command, bPressed);
//         if (bPressed)
//            goto ret;
//         m_pmapKeyPressed->lookup(::user::e_key_left_command, bPressed);
//         if (bPressed)
//            goto ret;
//         m_pmapKeyPressed->lookup(::user::e_key_right_command, bPressed);
//         if (bPressed)
//            goto ret;
//      }
//      else if (ekey == ::user::e_key_control)
//      {
//         m_pmapKeyPressed->lookup(::user::e_key_control, bPressed);
//         if (bPressed)
//            goto ret;
//         m_pmapKeyPressed->lookup(::user::e_key_left_control, bPressed);
//         if (bPressed)
//            goto ret;
//         m_pmapKeyPressed->lookup(::user::e_key_right_control, bPressed);
//         if (bPressed)
//            goto ret;
//      }
//      else if (ekey == ::user::e_key_alt)
//      {
//         m_pmapKeyPressed->lookup(::user::e_key_alt, bPressed);
//         if (bPressed)
//            goto ret;
//         m_pmapKeyPressed->lookup(::user::e_key_left_alt, bPressed);
//         if (bPressed)
//            goto ret;
//         m_pmapKeyPressed->lookup(::user::e_key_right_alt, bPressed);
//         if (bPressed)
//            goto ret;
//      }
//      else
//      {
//
//         m_pmapKeyPressed->lookup(ekey, bPressed);
//
//      }
//
//ret:
//
//      return bPressed;
//
//   }
//
//
//   void session::set_key_pressed(::user::enum_key ekey, bool bPressed)
//   {
//
//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (m_pmapKeyPressed == nullptr)
//      {
//
//         m_pmapKeyPressed = memory_new ::map < ::user::enum_key, bool >;
//
//      }
//
//      (*m_pmapKeyPressed)[ekey] = bPressed;
//
//   }


   void session::set_bound_ui(::atom idImpact, ::user::interaction * pinteraction)
   {

      m_mapboundui.set_at(idImpact, pinteraction);

   }


   ::user::primitive * session::get_bound_ui(::atom idImpact)
   {

      auto p = m_mapboundui.plookup(idImpact);

      if (!p)
      {

         return nullptr;

      }

      return p->m_element2;

   }


   void session::on_show_user_input_popup(::user::interaction * pinteraction)
   {

      synchronous_lock synchronouslock(this->synchronization());

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


   void session::init1()
   {

      //auto estatus = 
      
      ::apex::session::init1();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //auto estatus = __construct_new(m_pfs);

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

      //   estatus = __construct(m_pifs, __new(ifs("")));

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      TRACE("Failed to create ifs");

      //   }

      //}

      //if (!m_premotefs)
      //{

      //   estatus = __construct(m_premotefs, __new(::fs::remote_native("")));

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

      //   estatus = __construct(m_pfsdata, pset);

      //   if (!estatus)
      //   {

      //      m_result.add(estatus);

      //      TRACE("Failed to create fsdata");

      //   }

      //}

      INFORMATION(".2");

      auto psystem = get_system()->m_paurasystem;

      if (psystem->m_bUser)
      {

         INFORMATION("success");

         //auto psetup = system_setup::get_first(::system_setup::flag_object_user);

         //if (psetup)
         //{

         //   estatus = __construct(m_puser, psetup->create_new_object());

         //   if(!estatus)
         //   {

         //      output_debug_string("\nFailed to __construct(m_puser)");

         //   }

         //}

         //if (!estatus)
         //{

         //estatus =
         
         __construct(m_puser);

         //}

         if (!m_puser)
         {

            output_debug_string("\nFailed to __construct_new(m_puser)");

            ERROR(".4");

            return;

         }

         INFORMATION("end");

         m_puser->init1();

         //if (!m_puser->init1())
         //{

         //   return false;

         //}

         m_puser->init2();

         //if (!m_puser->init2())
         //{

         //   return false;

         //}


      }

     

      //return true;

   }


   void session::defer_initialize_host_window(const RECTANGLE_I32 * lpcrect)
   {

      auto puser = m_puser;

      puser->windowing1()->defer_initialize_host_window(lpcrect);

      //return ::success;

//#if !defined(APPLE_IOS) && !defined(_UWP) && !defined(ANDROID)
//
//      return ::success;
//
//#else
//
//      if(m_puserinteractionHost)
//      {
//
//         return ::success;
//
//      }
//
//      auto puserinteraction = ::OPERATING_SYSTEM_NAMESPACE::create_host_window();
//
//      if(!puserinteraction)
//      {
//
//         return ::error_failed;
//
//      }
//
//      auto estatus = puserinteraction->initialize(get_context_system());
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      estatus = __refer(m_puserinteractionHost, puserinteraction);
//
//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      rectangle_i32 rectangleScreen(lpcrect);
//
////      if(::is_null(lprect))
////      {
////
////         get_main_monitor(rectangleScreen);
////
////      }
////      else
////      {
////
////         rectangleScreen = *lprect;
////
////      }
//
//      auto pcs = __new(::user::system(0, nullptr, nullptr, WS_VISIBLE, rectangleScreen));
//
//      auto puserinteractionHost = __user_interaction(m_puserinteractionHost);
//
//      if (!puserinteractionHost->create_window_ex(pcs))
//      {
//
//         return ::error_failed;
//
//      }
//
////      puserinteraction->place(rectangleScreen);
////
////      puserinteraction->display(e_display_restored);
////
////      puserinteraction->set_need_layout();
////
////      puserinteraction->set_need_redraw();
////
////      puserinteraction->post_redraw();
//
//      return true;
//
//#endif

   }


   void session::init2()
   {

      //::e_status estatus = 
      
      ::apex::session::init2();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      INFORMATION("aura::session::init2 .1");

      //if (psystem->m_bUser)
      //{

      //   if(psystem->m_bDraw2d)
      //   {

      //

      //   }

      //}

     /* if (!InitializeLocalDataCentral())
      {

         output_error_message("Could not initialize Local data central");

         return false;

      }*/

      //estatus = 
      
      __construct_new(m_psavings);

      //return estatus;

   }


   void session::init()
   {

      //::e_status estatus =
      
      ::apex::session::init();


      //::pointer<::fs::set>pfsset = m_pfsdata;

      //if (m_bIfs)
      //{

      //   if (m_pfsdata.is_null())
      //   {

      //      __construct(m_pfsdata, __new(::fs::set));

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

         //estatus =
         
         m_puser->init();

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }

      //return estatus;

   }


   //void session::ui_init()
   //{

   //   if (!m_bUiInit)
   //   {

   //      return ::success_none;

   //   }

   //   m_bUiInit = true;

   //   __construct_new(m_puserstyleDefault);

   //   m_puserstyleDefault->default_style_construct();

   //   return ::success;

   //}


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

         m_puser.release();

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






   //void session::initialize(::particle * pparticle)
   //{

   //   auto estatus = ::aura::session::initialize(pparticle);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }


   //   return estatus;

   //}


   void session::install_message_routing(::channel* pchannel)
   {

      ::apex::session::install_message_routing(pchannel);

   //   //aura::application::install_message_routing(pchannel);
   //   aura::session::install_message_routing(pchannel);

   }



   void session::_001OnFileNew()
   {

   }


   void session::launch_app(const ::string & psz)
   {

      __UNREFERENCED_PARAMETER(psz);

   }


   void session::install_app(const ::string & psz)
   {

      __UNREFERENCED_PARAMETER(psz);

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


   ::pointer<::aura::application>session::get_current_application()
   {

      auto psession = get_session();

      return psession->m_pappCurrent;

   }


   bool session::is_remote_session()
   {

      auto pcontext = get_context();

      return pcontext->m_papexcontext->os_context()->is_remote_session();

   }


   bool session::is_mouse_button_pressed(::user::enum_mouse emouse)
   {

      if (emouse == ::user::e_mouse_left_button)
      {

         return is_key_pressed(::user::e_key_left_button);

      }
      else if (emouse == ::user::e_mouse_right_button)
      {

         return is_key_pressed(::user::e_key_right_button);

      }
      else if (emouse == ::user::e_mouse_middle_button)
      {

         return is_key_pressed(::user::e_key_middle_button);

      }
      else
      {

         throw unexpected_situation("not expected enum_mouse value");

      }

   }


   bool session::open_file(::filemanager::data* pdata, ::file::item_array& itema)
   {

      __UNREFERENCED_PARAMETER(pdata);

      if (itema.get_size() > 0)
      {

         return true;

      }

      return false;

   }








   bool session::InitializeLocalDataCentral()
   {

      //m_pdatabase = memory_new nature::database(this);

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

   //   if (m_varCurrentImpactFile != m_varTopicFile && !m_varTopicFile.is_empty())
   //   {

   //      m_varCurrentImpactFile = m_varTopicFile;

   //      request_topic_file();

   //   }

   //}

   //}

   bool session::place(::user::main_frame* pmainframe, ::create* pcreate)
   {

      //get_place_holder(pmainframe, pcreate).hold(pmainframe);

      return true;

   }





   void session::set_app_title(const ::string & pszAppId, const ::string & pszTitle)
   {

      ::pointer<::apex::application>papp;

      if (m_applicationa.lookup(pszAppId, papp) && papp)
      {

         //::pointer<::bergedge::pane_impact>ppaneimpact = get_document()->get_typed_impact < ::bergedge::pane_impact >();

         //if(ppaneimpact != nullptr)
         //{

         //   string strAppName(pszAppId);

         //   ::user::tab::pane * ppane = ppaneimpact->get_pane_by_id("app:" + strAppName);

         //   if(ppane != nullptr)
         //   {

         //      ppane->m_istrTitleEx = pszTitle;

         //      ppaneimpact->on_layout(pgraphics);

         //   }

         //}

      }

   }


   void     session::main()
   {

      //auto estatus =
      
      ::aqua::session::main();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //string_array session::get_user_wallpaper()
   //{

   //   string_array stra;

   //   auto psession 

   //   string_array straSource = psession->userex()->get_wallpaper();

   //   for (string str : straSource)
   //   {

   //      if (str.begins_eat_ci("file://"))
   //      {

   //         str = purl->url_decode(str);

   //      }

   //      stra.add(str.c_str());

   //   }

   //   return stra;

   //}


   void session::on_instantiate_application(::apex::application* papp)
   {

      ::aqua::session::on_instantiate_application(papp);

      papp->m_paurasession = this;
      papp->m_paurasystem = m_paurasystem;
      papp->m_pauranode = m_pauranode;

   }


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


   ::aura::system * session::get_system()
   {

      return ::is_set(acmesystem()) ? acmesystem()->m_paurasystem : nullptr;

   }



} // namespace aura



