// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "aura/node/windows/system_interaction.h"
#include "_windowing.h"

#if !BROAD_PRECOMPILED_HEADER

#include "aura/user/_user.h"

#endif


namespace windowing
{


   windowing::windowing()
   {

      m_bSettingCursorMatter = false;

   }


   windowing::~windowing()
   {

   }


   ::e_status windowing::initialize_windowing(::user::user * puser)
   {

      auto estatus = initialize(puser);

      if (!estatus)
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

      if (m_pcursorset)
      {

         m_pcursorset->finalize();

      }

   }


   void windowing::finalize()
   {

      m_pcursorset.release();

      ::apex::department::finalize();

   }


   __pointer(cursor) windowing::get_cursor(enum_cursor ecursor)
   {

      sync_lock sl(mutex());

      if (m_pcursorset.is_null())
      {

         auto estatus = __construct_new(m_pcursorset);

         if (!estatus)
         {

            return nullptr;

         }

         m_pcursorset->set_cursor_set_system_default();

      }

      return m_pcursorset->get_cursor(ecursor);

   }


   bool windowing::set_cursor_set_from_matter(const ::file::path & pathDir)
   {

      sync_lock sl(mutex());

      if (m_bSettingCursorMatter)
      {

         return false;

      }

      __keep(m_bSettingCursorMatter);

      sl.unlock();

      auto pcursorset = __create_new < ::draw2d::cursor_set >();

      if (!pcursorset->set_cursor_set_from_matter(pathDir))
      {

         return false;

      }

      m_pcursorset = pcursorset;

      return true;

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


   ::windowing::window * windowing::get_active_window()
   {

      return nullptr;

   }


   ::windowing::display * windowing::display()
   {

      __throw(interface_only_exception());

      return nullptr;

   }


   void windowing::__hook_on_idle(class display * pdisplay)
   {

      __throw(interface_only_exception());

   }


    ::e_status windowing::defer_initialize_x11()
   {

       return ::success;
   }
    void windowing::handle_just_hooks()
   {

   }


    void windowing::defer_handle_just_hooks()
   {

   }


    int windowing::message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox)
   {

       __throw(interface_only_exception());
       return 0;
   }


   bool windowing::__hook_process_event(class display * pdisplay, void * pevent, void * cookie)
   {


      return false;

   }


   void windowing::get_cursor_pos(POINT_I32 * ppoint)
   {

   }


   bool windowing::defer_create_system_window()
   {

#ifdef WINDOWS_DESKTOP

      if (m_puserinteraction)
      {

         return true;

      }

      m_puserinteraction = create_system_window();

      if (!m_puserinteraction)
      {

         return false;

      }

#endif

      return true;

   }


   __pointer(::user::interaction) windowing::create_system_window()
   {

      return nullptr;

   }


   ::windowing::window * windowing::get_focus()
   {

      return nullptr;

   }


   ::windowing::window * windowing::get_capture()
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


   bool windowing::sn_start_context()
   {


      return false;

   }

   
   ::e_status windowing::release_capture()
   {

      return error_interface_only;

   }


   ::user::interaction * windowing::get_system_window()
   {

#ifdef WINDOWS_DESKTOP

      return m_puserinteraction;

#else

      return nullptr;

#endif

   }

   
   void windowing::term1()
   {

#ifdef WINDOWS

#ifdef WINDOWS_DESKTOP

      if (m_puserinteraction)
      {

         m_puserinteraction->DestroyWindow();

      }

#endif

#endif

   }


   size_i32 windowing::get_window_minimum_size()
   {

      return size_i32(300, 300);

   }


   void windowing::term2()
   {

#ifdef WINDOWS_DESKTOP

      m_puserinteraction.release();

#endif

   }
   //bool windowing::set_window_icon(window *pwindow, const ::file::path &path)
   //{


   //   return false;

   //}


   int windowing::message_box(const char *pszMessage, const char *pszTitle, const ::e_message_box &emessagebox)
   {

      return -1;

   }


   int windowing::message_box_timeout(const char *pszMessage, const char *pszTitle, const ::duration &duration,
                                      const ::e_message_box &emessagebox)
   {

      return -1;

   }


   window *windowing::new_message_window(::user::interaction_impl *pimpl)
   {

      __throw(interface_only_exception());

      return nullptr;

   }


   window *windowing::new_window(::user::interaction_impl *pimpl)
   {

      __throw(interface_only_exception());

      return nullptr;

   }


   ::e_status windowing::remove_window(::windowing::window * pwindow)
   {

      //if (!m_windowmap.remove_key(pwindow->get_os_data()))
      //{

        // return ::error_failed;

      //}

      return ::success;

   }


//   ::e_status windowing::hook(class hook *phook)
//   {
//
//      __throw(interface_only_exception());
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
//      __throw(interface_only_exception());
//
//      return
//         error_interface_only;
//
//   }



   bool windowing::route_message(::message::base * pmessagebase)
   {

       auto puserinteraction = __user_interaction(pmessagebase->m_playeredUserPrimitive);

      puserinteraction->m_pimpl->message_handler(pmessagebase);

      return true;

   }


   void windowing::on_idle(class display *pdisplay)
   {


   }


   void windowing::enum_draw2d_fonts(::draw2d::font_enum_item_array & itema)
   {



   }


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

      ////pcursor->m_pimage = Application.image().load_image(path, bFromCache, bSync);

      return true;

   }


   void windowing::initialize_keyboard(::user::keyboard * pkeyboard)
   {



   }


   //void windowing::top_windows_by_z_order(oswindow_array & a)
   //{


   //}



} // namespace windowing




