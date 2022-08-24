// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
//#include "aura/node/windows/system_interaction.h"
//#include "_windowing.h"

#if !BROAD_PRECOMPILED_HEADER

#include "aura/user/user/_component.h"

#endif


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


   void windowing::_initialize_windowing()
   {


   }


   void windowing::initialize_windowing(::user::user * puser)
   {

      //auto estatus = initialize(puser);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //auto estatus = 
      
      __refer(m_puser, puser);


      ::factory::add_factory_item < cursor_manager >();

      //if(!estatus)
      //{

      //   return estatus;

      //}

      m_ecursorDefault = e_cursor_arrow;

      m_ecursor = e_cursor_default;
      
      m_bDrawCursor = false;

//      return ::success;

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

      //auto estatus = 
      
      ::acme::department::destroy();

      //return estatus;

   }


   //void windowing::destroy()
   //{

   //   auto estatus = ::acme::department::destroy();

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   return estatus;

   //}


//   void windowing::start()
//   {
//
//      //return ::success;
//
//   }
//

   void windowing::windowing_main()
   {


   }


   void windowing::windowing_post_quit()
   {


   }


   text_editor_interface * windowing::get_text_editor_interface()
   {

      return nullptr;

   }
   
   
   __pointer(cursor) windowing::get_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pcursormanager.is_null())
      {

         //auto estatus = 
         
         __construct_new(m_pcursormanager);

         //if (!estatus)
         //{

         //   return nullptr;

         //}

         //m_pcursormanager->set_cursor_set_system_default();

      }

      return m_pcursormanager->get_cursor(ecursor);

   }


   void windowing::set_cursor_set_from_matter(::object * pobjectContext, const ::file::path & pathDir)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_bSettingCursorMatter)
      {

         //return error_already_working_on_it;
         return;

      }

      __keep(m_bSettingCursorMatter);

      synchronouslock.unlock();

      //auto estatus = 
      
      __construct(m_pcursormanager);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      m_pcursormanager->set_cursor_set_from_matter(pobjectContext, pathDir);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void windowing::set_cursor_position(const ::point_i32 & pointCursor)
   {

      m_pointCursor = pointCursor;

   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      return nullptr;

   }


   //::user::interaction_impl * windowing::interaction_impl(::windowing::window * pwindow)
   //{

   //   auto pwindow = window(oswindow);

   //   if (::is_null(pwindow))
   //   {

   //      return nullptr;

   //   }

   //   return pwindow->m_pimpl;

   //}


   //::user::interaction * windowing::interaction(::windowing::window * pwindow)
   //{

   //   auto pimpl = interaction_impl(oswindow);

   //   if (::is_null(pimpl))
   //   {

   //      return nullptr;

   //   }

   //   return pimpl->m_puserinteraction;

   //}

   void windowing::defer_initialize_host_window(const RECTANGLE_I32* lpcrect)
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

      //throw ::interface_only();

   }


   ::windowing::display * windowing::display()
   {

      throw ::interface_only();

      return nullptr;

   }


   void windowing::__hook_on_idle(class display * pdisplay)
   {

      throw ::interface_only();

   }


   bool windowing::message_loop_step()
   {

      return false;

   }


//    void windowing::defer_initialize_x11()
//   {
//
//       return ::success;
//   }

   void windowing::handle_just_hooks()
   {

   }


    void windowing::defer_handle_just_hooks()
   {

   }


   // int windowing::message_box(const ::string & str, const ::string & strTitle, const ::e_message_box & emessagebox)
   //{

   //    throw ::interface_only();
   //    return 0;
   //}


   bool windowing::__hook_process_event(class display * pdisplay, void * pevent, void * cookie)
   {


      return false;

   }


   //void windowing::get_cursor_position(POINT_I32 * ppoint)
   //{

   //   *ppoint = m_pointCursor;

   //}


   ::windowing::window * windowing::get_keyboard_focus(::thread *)
   {

      return nullptr;

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


   __pointer(::windowing::cursor) windowing::load_default_cursor(enum_cursor ecursor)
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


   //int_bool windowing::window_set_mouse_cursor(window *pwindow, hcursor hcursor)
   //{

   //   return false;

   //}


//   bool windowing::sn_start_context()
//   {
//
//
//      return false;
//
//   }

   
   void windowing::release_mouse_capture()
   {

      throw ::interface_only();

   }


   /// pwindowGainingFocusIfAny
   /// handlers of this notification should NOT...
   /// NOT... set focus to pwindowGainingFocusIfAny
   void windowing::clear_keyboard_focus(::user::element* pelementGainingFocusIfAny)
   {

      throw ::interface_only();

   }


   //::extended::transport < ::windowing::icon > window::load_icon(const ::payload & payloadFile)
   //{

   //   return nullptr;

   //}

   //
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

      //return ::success;

   }
   //bool windowing::set_window_icon(window *pwindow, const ::file::path &path)
   //{


   //   return false;

   //}


   //__pointer(::future < enum_dialog_result >) windowing::message_box(const ::string &pszMessage, const ::string &pszTitle, const ::e_message_box &emessagebox)
   //{

   //   return nullptr;

   //}


   //enum_dialog_result windowing::message_box_timeout(const ::string &pszMessage, const ::string &pszTitle, const ::duration &duration,
   //                                   const ::e_message_box &emessagebox)
   //{

   //   return e_dialog_result_none;

   //}


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

      //if (!m_windowmap.erase_key(pwindow->get_os_data()))
      //{

        // return ::error_failed;

      //}

      //return ::success;

   }


//   void windowing::hook(class hook *phook)
//   {
//
//      throw ::interface_only();
//
//      return
//         error_interface_only;
//
//   }
//
//
//   void windowing::unhook(class hook * phook)
//   {
//
//      throw ::interface_only();
//
//      return
//         error_interface_only;
//
//   }



   bool windowing::route_message(::user::message * pusermessage)
   {

      auto puserinteraction = pusermessage->userinteraction();

      puserinteraction->m_pinteractionimpl->message_handler(pusermessage);

      return true;

   }


   void windowing::on_idle(class display *pdisplay)
   {


   }


   //void windowing::enum_draw2d_fonts(::write_text::font_enumeration_item_array & itema)
   //{



   //}


   int_bool windowing::point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin)
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

         //return ::error_bad_argument;

         throw ::exception(error_bad_argument);

      }

      string str(path);

      if (!::str().ends_eat_ci(str, ".png"))
      {

         //return false;

         return;

      }

      ////pcursor->m_pimage = pcontextimage->load_image(path, bFromCache, bSync);

      //return true;

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

      //return error_not_implemented;
    
   }


   void windowing::windowing_send(const ::procedure & procedure)
   {

      __send_procedure(this, &windowing::windowing_post, procedure);

   }


   void windowing::windowing_post(const ::procedure & procedure)
   {

      throw ::interface_only();

   }


   ::windowing::keyboard * windowing::keyboard()
   {

      if (!m_pkeyboard)
      {

         __compose(m_pkeyboard);

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


   void windowing::register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


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

      //throw ::interface_only();

   }


   ::e_status windowing::is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt)
   {

      return ::success;

   }


   void windowing::install_keyboard_hook(::matter * pmatterListener)
   {

      //return ::success;

   }


   void windowing::uninstall_keyboard_hook(::matter * pmatterListener)
   {

      //return ::success;

   }


   ::e_status windowing::is_mouse_hook_enabled(::user::interaction * puserinteractionEnablePrompt)
   {

      return ::success;

   }


   void windowing::install_mouse_hook(::matter * pmatterListener)
   {

      //return ::success;

   }


   void windowing::uninstall_mouse_hook(::matter * pmatterListener)
   {

      //return ::success;

   }


} // namespace windowing




