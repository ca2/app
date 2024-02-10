// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/asynchronous.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/keep.h"
#include "aura/platform/application.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/message/user.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/user.h"
#include "aura/platform/node.h"
#include "aura/platform/system.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/cursor.h"
#include "aura/windowing/cursor_manager.h"
#include "aura/windowing/window.h"
#include "aura/windowing/keyboard.h"


namespace windowing
{


   windowing::windowing()
   {

      m_psandboxwindowing = nullptr;

      m_pWindowing4 = nullptr;

      m_bSettingCursorMatter = false;

   }


   windowing::~windowing()
   {

   }


   bool windowing::has_readily_gettable_absolute_coordinates() const
   {

      return true;

   }


   void windowing::initialize_windowing(::user::user * puser)
   {

      informationf("aura::windowing::initialize_windowing");

      m_puser = puser;

      factory()->add_factory_item < cursor_manager >();

      m_ecursorDefault = e_cursor_arrow;

      m_ecursor = e_cursor_default;
      
      m_bDrawCursor = false;

      informationf("aura::windowing::initialize_windowing end");

   }


   void windowing::terminate_windowing()
   {


   }


   void windowing::defer_term_ui()
   {


   }


   void windowing::finalize_windowing()
   {

      if (m_pcursormanager)
      {

         m_pcursormanager->destroy();

      }

   }


   void windowing::destroy()
   {

      m_pcursormanager.release();

      ::acme::department::destroy();

   }


   void windowing::windowing_post_quit()
   {


   }


   text_editor_interface * windowing::get_text_editor_interface()
   {

      return nullptr;

   }
   
   
   ::pointer<cursor>windowing::get_cursor(enum_cursor ecursor)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pcursormanager.is_null())
      {

         __construct_new(m_pcursormanager);

      }

      return m_pcursormanager->get_cursor(ecursor);

   }


   void windowing::set_cursor_set_from_matter(::object * pobjectContext, const ::file::path & pathDir)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_bSettingCursorMatter)
      {

         //return error_already_working_on_it;
         return;

      }

      KEEP(m_bSettingCursorMatter);

      synchronouslock.unlock();

      __defer_construct(m_pcursormanager);

      m_pcursormanager->set_cursor_set_from_matter(pobjectContext, pathDir);

   }


//   void windowing::set_cursor_position(const ::point_i32 & pointCursor)
//   {
//
//      m_pointCursor = pointCursor;
//
//   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      return nullptr;

   }


   void windowing::defer_initialize_host_window(const ::rectangle_i32* lpcrect)
   {


   }

   
   bool windowing::is_sandboxed()
   {

      auto pwindow = get_application_host_window();

      if (::is_null(pwindow))
      {

         return false;

      }

      return true;

   }


   ::windowing::window * windowing::get_application_host_window()
   {

      return nullptr;

   }


   ::windowing::window * windowing::get_desktop_window()
   {

      return nullptr;

   }


   ::windowing::window * windowing::get_foreground_window()
   {

      return nullptr;

   }


   ::windowing::window * windowing::get_active_window(::thread *)
   {

      return nullptr;

   }


   void windowing::clear_active_window(::thread *, ::windowing::window *)
   {

      throw ::interface_only();

   }


   ::windowing::display * windowing::display()
   {

      throw ::interface_only();

   }


   void windowing::__hook_on_idle(class display * pdisplay)
   {

      throw ::interface_only();

   }


   bool windowing::message_loop_step()
   {

      return false;

   }


   void windowing::handle_just_hooks()
   {


   }


   void windowing::defer_handle_just_hooks()
   {


   }


   bool windowing::__hook_process_event(class display * pdisplay, void * pevent, void * cookie)
   {


      return false;

   }


   ::windowing::window_base * windowing::get_keyboard_focus(::thread *)
   {

      return nullptr;

   }


   ::point_i32 windowing::try_absolute_mouse_position(::user::interaction* puserinteraction, const ::point_i32& point)
   {

      auto p = point;

      //puserinteraction->client_to_screen()(p);

      return p;

   }


   ::windowing::window * windowing::get_mouse_capture(::thread *)
   {

      return nullptr;

   }


   void windowing::kick_idle()
   {


   }


   void windowing::__wait_timer_or_event(class display * pdisplay)
   {


   }


   bool windowing::is_screen_visible(::e_display edisplay)
   {

      return ::is_screen_visible(edisplay);

   }


   ::pointer<::windowing::cursor>windowing::load_default_cursor(enum_cursor ecursor)
   {

      return nullptr;

   }


   ::windowing::cursor * windowing::get_cursor()
   {

      return nullptr;

   }


   ::windowing::cursor * windowing::get_default_cursor()
   {

      return nullptr;

   }


   void windowing::set_mouse_capture(::thread *, ::windowing::window * pwindow)
   {

      throw ::interface_only();

   }


//   ::windowing::window * windowing::get_mouse_capture(::thread *)
//   {
//
//      throw ::interface_only();
//
//      return nullptr;
//
//   }


   void windowing::release_mouse_capture(::thread *)
   {

      throw ::interface_only();

   }


   void windowing::set_mouse_cursor(::windowing::cursor * pcursor)
   {

      throw ::interface_only();

      //return nullptr;

   }


//   void windowing::release_mouse_capture(::thread * pthread)
//   {
//
//      throw ::interface_only();
//
//   }


   bool windowing::defer_release_mouse_capture(::thread * pthread, ::windowing::window * pwindow)
   {

      throw ::interface_only();

      return false;

   }


//   void windowing::set_mouse_cursor(::windowing::cursor * pcursor)
//   {
//
////      void * poscursor = nullptr;
////
////      if (::is_set(pcursor))
//
////      HCURSOR hcursor = nullptr;
////
////      if (::is_set(pcursor))
////      {
////
////         hcursor = (HCURSOR)pcursor->get_os_data();
////
////         if (hcursor == nullptr)
////         {
////
////            //auto estatus =
////
////            pcursor->_create_os_cursor();
////
////            //if (!estatus)
////            //{
////
////            //   return estatus;
////
////            //};
////
////            hcursor = (HCURSOR)pcursor->get_os_data();
////
////            //if (!hcursor)
////            //{
////
////            //   return error_resource;
////
////            //}
////
////         }
////
////      }
////
////      // At windows SetMouseCursor(nullptr) removes the cursor from screen
////      // similar apis in other platforms behave the same?
////
////      if (!::SetCursor(hcursor))
////      {
////
////         throw ::exception(error_failed);
////
////      }
////
////      //return ::success;
////
//
//
//   }


   /// pwindowGainingFocusIfAny
   /// handlers of this notification should NOT...
   /// NOT... set focus to pwindowGainingFocusIfAny
   void windowing::clear_keyboard_focus(::user::element* pelementGainingFocusIfAny)
   {

      throw ::interface_only();

   }


   void windowing::term1()
   {

      //return ::success;

   }


   size_i32 windowing::get_window_minimum_size()
   {

      return size_i32(300, 300);

   }


   void windowing::term2()
   {

   }


   window *windowing::new_message_window(::user::interaction_impl *pimpl)
   {

      throw ::interface_only();

      return nullptr;

   }


   window *windowing::new_window(::user::interaction_impl *pimpl)
   {

      auto pwindow = pimpl->__create < ::windowing::window >();

      pwindow->create_window(pimpl);

      return pwindow;

   }


   void windowing::erase_window(::windowing::window * pwindow)
   {

   }


   bool windowing::route_message(::user::message * pusermessage)
   {

      auto pwindow = pusermessage->window();

      if (!pwindow)
      {

         throw ::exception(error_wrong_state);

      }

      auto puserinteractionimpl = pwindow->m_puserinteractionimpl;

      if (!puserinteractionimpl)
      {

         throw ::exception(error_wrong_state);

      }

      puserinteractionimpl->message_handler(pusermessage);

      return true;

   }


   void windowing::on_idle(class display *pdisplay)
   {


   }


   int_bool windowing::point_is_window_origin(::point_i32 ptHitTest, oswindow oswindowExclude, int iMargin)
   {

      return false;

   }


   bool windowing::is_window(oswindow oswindow)
   {

      return false;

   }


   void windowing::load_cursor(::windowing::cursor * pcursor, ::file::path path, bool bSync, bool bCache)
   {

      if (::is_null(pcursor))
      {

         throw ::exception(error_bad_argument);

      }

      string str(path);

      if (!str.case_insensitive_ends_eat(".png"))
      {

         return;

      }

   }


   void windowing::set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   {

      auto pkeyboard = keyboard();

      pkeyboard->translate_os_key_message(pkey);

   }


   void windowing::set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
   {


   }


   void windowing::initialize_keyboard(::windowing::keyboard * pkeyboard)
   {


   }


   void windowing::lock_set_foreground_window(bool bLock)
   {

   }


//   void windowing::windowing_send(const ::procedure & procedure)
//   {
//
//      __matter_send_procedure(this, this, &windowing::windowing_post, procedure);
//
//   }
//
//
//   void windowing::windowing_post(const ::procedure & procedure)
//   {
//
//      if(node()->m_pauranode->defer_windowing_post(procedure))
//      {
//
//         return;
//
//      }
//
//   }


   ::windowing::keyboard * windowing::keyboard()
   {

      if (!m_pkeyboard)
      {

         __construct(m_pkeyboard);

         initialize_keyboard(m_pkeyboard);

      }

      return m_pkeyboard;

   }


   bool windowing::is_branch_current() const
   {

      return false;

   }


   void windowing::_main_loop()
   {

   }


   void windowing::_message_handler(void * p)
   {

   }


   wstring windowing::_windows_calc_icon_window_class(::user::interaction* pinteraction, u32 dwDefaultStyle, const ::string & pszMatter)
   {
   
      return "windows_interaction_impl";

   }

   
   wstring windowing::_windows_get_user_interaction_window_class(::user::interaction* pinteraction)
   {
   
      return "windows_interaction_impl";

   }


#if defined(LINUX) || defined(FREEBSD)


   void windowing::_libsn_start_context()
   {


   }


   bool windowing::_xcb_process_event(void * p)
   {

      return false;

   }


   bool windowing::xcb_message_loop_step()
   {

      return true;

   }


#endif


//   void windowing::register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard)
//   {
//
//      throw ::interface_only();
//
//   }


   void windowing::os_menu_item_enable(void * pitem, bool bEnable)
   {

      throw ::interface_only();

   }


   void windowing::os_menu_item_check(void * pitem, bool bCheck)
   {

      throw ::interface_only();

   }


   void windowing::defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId)
   {

   }


//   ::e_status windowing::is_keyboard_message_handling_enabled(::user::interaction * puserinteractionEnablePrompt)
//   {
//
//      return ::success;
//
//   }
//
//
//   void windowing::add_keyboard_message_handler(::particle * pparticle)
//   {
//
//   }
//
//
//   void windowing::erase_keyboard_message_handler(::particle * pparticle)
//   {
//
//   }
//
//
//   ::e_status windowing::is_mouse_message_handling_enabled(::user::interaction * puserinteractionEnablePrompt)
//   {
//
//      return ::success;
//
//   }
//
//
//   void windowing::add_mouse_message_handler(::particle * pparticle)
//   {
//
//   }
//
//
//   void windowing::erase_mouse_message_handler(::particle * pparticle)
//   {
//
//   }


   ::aura::application* windowing::get_app()
   {

      return m_pcontext && m_pcontext->m_pacmeapplication ? m_pcontext->m_pacmeapplication->m_pauraapplication : nullptr;

   }


   ::aura::session* windowing::get_session()
   {

      return m_pcontext && m_pcontext->m_pacmesession ? m_pcontext->m_pacmesession->m_paurasession : nullptr;

   }


   ::pointer < ::user::interaction > windowing::create_message_window(const ::string & pszName, ::user::interaction_listener * plistener)
   {

      return nullptr;

   }


} // namespace windowing




