// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
//#include "aura/node/windows/system_interaction.h"
#include "_windowing.h"

#if !BROAD_PRECOMPILED_HEADER

#include "aura/user/_user.h"

#endif


namespace windowing
{


   windowing::windowing()
   {

      m_pWindowing = nullptr;

      m_pWindowing2 = nullptr;

      m_bSettingCursorMatter = false;

   }


   windowing::~windowing()
   {

   }


   ::e_status windowing::initialize_windowing(::user::user * puser)
   {

      //auto estatus = initialize(puser);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto estatus = __refer(m_puser, puser);

      if(!estatus)
      {

         return estatus;

      }

      m_ecursorDefault = e_cursor_arrow;

      m_ecursor = e_cursor_default;

      m_bDrawCursor = false;

      return ::success;

   }


   void windowing::defer_term_ui()
   {


   }


   void windowing::finalize_windowing()
   {

      if (m_pcursormanager)
      {

         m_pcursormanager->finalize();

      }

   }


   ::e_status windowing::finalize()
   {

      m_pcursormanager.release();

      auto estatus = ::acme::department::finalize();

      return estatus;

   }


   ::e_status windowing::finish()
   {

      auto estatus = ::acme::department::finish();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status windowing::start()
   {

      return ::success;

   }


   void windowing::windowing_main()
   {


   }


   void windowing::windowing_post_quit()
   {


   }


   __pointer(cursor) windowing::get_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pcursormanager.is_null())
      {

         auto estatus = __construct_new(m_pcursormanager);

         if (!estatus)
         {

            return nullptr;

         }

         //m_pcursormanager->set_cursor_set_system_default();

      }

      return m_pcursormanager->get_cursor(ecursor);

   }


   ::e_status windowing::set_cursor_set_from_matter(const ::file::path & pathDir)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_bSettingCursorMatter)
      {

         return error_already_working_on_it;

      }

      __keep(m_bSettingCursorMatter);

      synchronouslock.unlock();

      auto estatus = __construct(m_pcursormanager);

      if (!estatus)
      {

         return estatus;

      }

      estatus = m_pcursormanager->set_cursor_set_from_matter(pathDir);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status windowing::set_cursor_position(const ::point_i32 & point)
   {

      __throw(error_interface_only);

      return ::error_interface_only;

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


   ::e_status windowing::clear_active_window(::thread *)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::windowing::display * windowing::display()
   {

      __throw(error_interface_only);

      return nullptr;

   }


   void windowing::__hook_on_idle(class display * pdisplay)
   {

      __throw(error_interface_only);

   }


   bool windowing::message_loop_step()
   {

      return false;

   }


//    ::e_status windowing::defer_initialize_x11()
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


   // int windowing::message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox)
   //{

   //    __throw(error_interface_only);
   //    return 0;
   //}


   bool windowing::__hook_process_event(class display * pdisplay, void * pevent, void * cookie)
   {


      return false;

   }


   void windowing::get_cursor_position(POINT_I32 * ppoint)
   {

      *ppoint = m_pointCursor;

   }


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

   
   ::e_status windowing::release_mouse_capture()
   {

      return error_interface_only;

   }






   ::extended::transport < ::windowing::icon > windowing::load_icon(const ::payload & payloadFile)
   {

      return nullptr;

   }

   
   ::e_status windowing::term1()
   {

      return ::success;

   }


   size_i32 windowing::get_window_minimum_size()
   {

      return size_i32(300, 300);

   }


   ::e_status windowing::term2()
   {

      return ::success;

   }
   //bool windowing::set_window_icon(window *pwindow, const ::file::path &path)
   //{


   //   return false;

   //}


   //__pointer(::future < enum_dialog_result >) windowing::message_box(const char *pszMessage, const char *pszTitle, const ::e_message_box &emessagebox)
   //{

   //   return nullptr;

   //}


   //enum_dialog_result windowing::message_box_timeout(const char *pszMessage, const char *pszTitle, const ::duration &duration,
   //                                   const ::e_message_box &emessagebox)
   //{

   //   return e_dialog_result_none;

   //}


   window *windowing::new_message_window(::user::interaction_impl *pimpl)
   {

      __throw(error_interface_only);

      return nullptr;

   }


   window *windowing::new_window(::user::interaction_impl *pimpl)
   {

      __throw(error_interface_only);

      return nullptr;

   }


   ::e_status windowing::erase_window(::windowing::window * pwindow)
   {

      //if (!m_windowmap.erase_key(pwindow->get_os_data()))
      //{

        // return ::error_failed;

      //}

      return ::success;

   }


//   ::e_status windowing::hook(class hook *phook)
//   {
//
//      __throw(error_interface_only);
//
//      return
//         error_interface_only;
//
//   }
//
//
//   ::e_status windowing::unhook(class hook * phook)
//   {
//
//      __throw(error_interface_only);
//
//      return
//         error_interface_only;
//
//   }



   bool windowing::route_message(::user::message * pusermessage)
   {

      auto puserinteraction = pusermessage->userinteraction();

      puserinteraction->m_pimpl->message_handler(pusermessage);

      return true;

   }


   void windowing::on_idle(class display *pdisplay)
   {


   }


   //void windowing::enum_draw2d_fonts(::write_text::font_enum_item_array & itema)
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


   ::e_status windowing::load_cursor(::windowing::cursor * pcursor, ::file::path path, bool bSync, bool bCache)
   {

      if (::is_null(pcursor))
      {

         return ::error_invalid_argument;

      }

      string str(path);

      if (!::str::ends_eat_ci(str, ".png"))
      {

         return false;

      }

      ////pcursor->m_pimage = pcontextimage->load_image(path, bFromCache, bSync);

      return true;

   }


   void windowing::set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {

      auto pwindowing = pwindow->windowing();

      auto pkeyboard = pwindowing->keyboard();

      pkeyboard->translate_os_key_message(pkey);

   }


   void windowing::set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam)
   {


   }


   void windowing::initialize_keyboard(::windowing::keyboard * pkeyboard)
   {


   }


   ::e_status windowing::lock_set_foreground_window(bool bLock)
   {

      return error_not_implemented;
    
   }


   ::e_status windowing::windowing_sync(const ::duration & duration, const ::routine & routine)
   {

      auto estatus = __sync_routine(duration, this, &windowing::windowing_branch, routine);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status windowing::windowing_branch(const ::routine & routine)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   //void windowing::top_windows_by_z_order(oswindow_array & a)
   //{


   //}




   ::windowing::keyboard * windowing::keyboard()
   {

      if (!m_pkeyboard)
      {

         auto estatus = __compose(m_pkeyboard);

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

                  //papplication->on_create_keyboard();

         initialize_keyboard(m_pkeyboard);

      }

      return m_pkeyboard;

   }


   void windowing::_main_loop()
   {

   }


   void windowing::_message_handler(void * p)
   {

   }


   wstring windowing::_windows_calc_icon_window_class(::user::interaction* pinteraction, u32 dwDefaultStyle, const char* pszMatter)
   {
   
      return "windows_interaction_impl";

   }

   
   wstring windowing::_windows_get_user_interaction_window_class(::user::interaction* pinteraction)
   {
   
      return "windows_interaction_impl";

   }



#ifdef LINUX


   void windowing::_libsn_start_context()
   {


   }


#endif


   ::e_status windowing::register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }




} // namespace windowing




