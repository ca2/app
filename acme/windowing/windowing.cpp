// Split/separation of concerns from micro to
// acme::windowing by camilo on 2024-10-05 18:06 <3ThomasBorregaardSorensen!!
// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
//
// // Merged from user to
//     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
//                   //
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// // Merged from user to
//     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "display.h"
//#include "user.h"
#include "acme/user/user/interaction.h"
#include "window.h"
#include "windowing.h"
//#include "windowing_gtk4/windowing.h"

#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/department.h"
#include "acme/platform/system.h"


namespace acme
{


   namespace windowing
   {


      windowing::windowing()
      {

         m_ewindowing = ::windowing::e_windowing_none;
         m_ewindowingbias = ::windowing::e_bias_unknown;

      }


      windowing::~windowing()
      {
      }


      //::pointer < ::subparticle > windowing::nano()->message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
      //{

      //   auto psequencer = node()->nano()->message_box(strMessage, strTitle, emessagebox, strDetails);

      //   return psequencer;

      //}


      //::pointer < ::subparticle > windowing::nano()->message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
      //{

      //   auto psequencer = node()->nano()->message_console(strMessage, strTitle, emessagebox, strDetails);

      //   return psequencer;

      //}

      //::pointer < ::subparticle > windowing::message_box(const ::string & strMessage, const ::string & strTitle,
      //                                                       const ::e_message_box & emessagebox,
      //                                                       const ::string & strDetails, ::nano::graphics::icon * picon)
      //{
      //   auto pnode = node();

      //   auto psequencer = pnode->create_message_box_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);

      //   return psequencer;
      //}


      //::pointer < ::subparticle > windowing::exception_message_box(
      //    const ::exception & exception, const ::string & strMessageParam, const ::string & strTitleParam,
      //    const ::e_message_box & emessagebox, const ::string & strDetailsParam, ::nano::graphics::icon * picon)
      //{
      //   string strExceptionDetails = exception.get_consolidated_details(this);

      //   string strMessage(strMessageParam);

      //   if (strMessage.is_empty())
      //   {
      //      strMessage = exception.get_message();
      //   }

      //   string strTitle(strTitleParam);

      //   if (strTitle.is_empty())
      //   {
      //      strTitle = exception.get_title();
      //   }

      //   string strDetails(strDetailsParam);

      //   if (strExceptionDetails.has_character())
      //   {
      //      if (strDetails.has_character())
      //      {
      //         strDetails += "\n";
      //      }

      //      strDetails += strExceptionDetails;
      //   }

      //   auto psequencer = node()->create_message_box_sequencer(
      //       strMessage,
      //       strTitle,
      //       emessagebox,
      //       strDetails,
      //       picon);

      //   return psequencer;
      //}


      //::pointer < ::subparticle > windowing::message_console(const ::string & strMessage, const ::string & strTitle,
      //                                                           const ::e_message_box & emessagebox,
      //                                                           const ::string & strDetails, ::nano::graphics::icon * picon)
      //{
      //   auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);

      //   return psequencer;
      //}


      //::pointer < ::subparticle > windowing::exception_message_console(
      //    const ::exception & exception, const ::string & strMessage, const ::string & strTitle,
      //    const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
      //{
      //   string strExceptionDetails = exception.get_consolidated_details(this);

      //   auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox,
      //                                                      strDetails + "\n" + strExceptionDetails, picon);

      //   return psequencer;
      //}


      void windowing::defer_initialize_host_window(const ::int_rectangle* lpcrect)
      {


      }


      void windowing::_will_finish_launching()
      {

         //system()->defer_post_initial_request();

      }

      void windowing::_did_finish_launching()
      {

         //system()->defer_post_initial_request();

      }


      void windowing::set_clipboard_text(const char* psz)
      {


      }


      ::acme::windowing::window* windowing::get_application_host_window()
      {

         return nullptr;

      }


      ::pointer<::acme::windowing::window> windowing::get_new_window()
      {


         return {};

      }


      //      ::windowing::window* new_window(::windowing::window* pimpl) override;
      //
      void windowing::erase_window(::acme::windowing::window* pwindow)
      {


      }


      ::acme::windowing::window* windowing::window(oswindow oswindow)
      {


         return nullptr;

      }


      void windowing::_message_handler(void* p)
      {


      }


      ::acme::windowing::window* windowing::get_keyboard_focus(::thread* pthread)
      {

         return nullptr;

      }


      ::acme::windowing::window* windowing::get_mouse_capture(::thread* pthread)
      {

         return m_pwindowMouseCapture;

      }


      bool windowing::defer_release_mouse_capture(::thread* pthread, ::acme::windowing::window* pwindow)
      {

         return false;

      }


      //void windowing::clear_keyboard_focus(::user::element * pelementGainingFocusIfAny)
      //{
      //
      //
      //
      //}


      void windowing::handle(::topic * ptopic, ::handler_context * phandlercontext)
      {
         if (ptopic->id() == id_set_application_dark_mode)
         {
            for (auto& pwindow: m_windowa)
            {
               pwindow->handle(ptopic, phandlercontext);
            }
         }
      }


      void windowing::process_messages()
      {


      }


      bool windowing::init_threads()
      {

         return true;

      }


      void windowing::__task_suffix()
      {

         windowing_post_quit();

      }


      void windowing::show(::particle_pointer pparticle)
      {


      }


      // // Merged from user to
      //     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
      //                   //
      // Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
      // // Merged from user to
      //     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
      //
      //
      ////
      //#include "framework.h"
      ////#include "user.h"
      //#include "acme/constant/id.h"
      //#include "acme/exception/interface_only.h"
      //#include "acme/parallelization/synchronous_lock.h"
      //#include "acme/handler/topic.h"
      //#include "acme/nano/nano.h"
      //#include "acme/user/micro/display.h"
      //#include "acme/user/micro/user.h"
      ////#include "acme/windowing/window_base.h"
      //#include "platform/system.h"


      //namespace windowing
      //{


      /*  windowing::user()
       {


       }


       windowing::~user()
       {


       }*/


      void windowing::on_initialize_particle()
      {

         ::acme::department::on_initialize_particle();

         ::task::on_initialize_particle();

         initialize_windowing();

      }


      void windowing::destroy()
      {

         m_pacmedisplay.defer_destroy();

         m_windowa.clear();

         ::acme::department::destroy();

      }


      ::acme::windowing::display* windowing::acme_display()
      {

         if (!m_pacmedisplay)
         {

            system()->do_graphics_and_windowing_factory();

            __øconstruct(m_pacmedisplay);

            m_pacmedisplay->open_display();

         }

         return m_pacmedisplay;

      }


      void windowing::on_start_system()
      {


      }


      ::windowing::windowing* windowing::windowing_windowing()
      {

         return nullptr;

      }


      // ::e_status windowing::defer_initialize_windowing()
      // {
      //
      //    return ::success;
      //
      // }


      void windowing::initialize_windowing()
      {

         //return ::success;

      }


      void windowing::on_activate()
      {


      }


      void windowing::finalize_windowing()
      {


      }


      void windowing::on_create_window_object(::acme::user::interaction* puserinteraction)
      {

         puserinteraction->__defer_construct(puserinteraction->m_pacmewindowingwindow);

      }


      //      void * windowing::get_display()
      //      {
      //
      //         return nullptr;
      //
      //      }


      ::windowing::enum_bias windowing::calculate_windowing_bias()
      {

         return ::windowing::e_bias_none;

      }


      void windowing::_main_send(const ::procedure& procedure)
      {

         _user_send(procedure);

      }


      void windowing::_main_post(const ::procedure& procedure)
      {

         _user_post(procedure);

      }


      void windowing::display_error_trap_push(int i)
      {


      }


      void windowing::display_error_trap_pop_ignored(int i)
      {


      }


      //      void * windowing::fetch_windowing_sydisplay()
      //      {
      //
      //         return nullptr;
      //
      //      }


      //void windowing::process_messages()
      //{

      //   system()->acme_windowing()->process_messages();

      //   // #ifdef HAS_WAYLAND
      //   //         if(psystem->m_ewindowing == ::windowing::e_windowing_wayland)
      //   //         {
      //   //
      //   //             ::wayland::acme::windowing::process_messages();
      //   //
      //   //         }
      //   //         else
      //   // #endif
      //   //             if(psystem->m_ewindowing == ::windowing::e_windowing_xcb)
      //   //             {
      //   //
      //   //                 ::xcb::micro::process_messages();
      //   //
      //   //             }
      //   //             else
      //   //             {
      //   //
      //   //                 ::x11::micro::process_messages();
      //   //
      //   //             }


      //}


      void windowing::windowing_application_main_loop()
      {


      }


      void windowing::windowing_post_quit()
      {


      }


      ::color::color windowing::get_system_color(enum_system_color esystemcolor)
      {

         throw ::interface_only();

         return argb(0, 0, 0, 0);

      }


      ::color::color windowing::get_operating_system_background_color()
      {

         return ::color::white;

      }


      void windowing::fetch_dark_mode()
      {

         auto color = get_operating_system_background_color();

         on_system_dark_mode_change(color.get_luminance() <= 0.5, color);

      }


      void windowing::on_system_dark_mode_change(bool bDarkMode, const ::color::color& colorBackground)
      {

         if (colorBackground != ::color::transparent)
         {

            system()->set_background_color(colorBackground);

         }
         else
         {

            system()->set_dark_mode(bDarkMode);

         }

         auto ptopic = __allocate ::topic(id_application_dark_mode_change);

         for (auto& pwindow: m_windowa)
         {

            pwindow->handle(ptopic, nullptr);

            pwindow->set_need_redraw();

            pwindow->post_redraw();

         }

      }


      bool windowing::dark_mode()
      {

         return false;

      }


      class ::time windowing::dark_mode_time() const
      {

         return m_timeDarkMode;

      }


      void windowing::set_dark_mode_time(const class ::time& time)
      {

         m_timeDarkMode = time;

      }


      void windowing::set_dark_mode(bool bDarkMode)
      {


      }


      void windowing::fetch_system_background_color()
      {


      }


      ::color::color windowing::reinterpreted_background_color()
      {

         if (dark_mode())
         {

            return ::color::black;

         }

         return ::color::white;

      }


      void windowing::_do_tasks()
      {

         _synchronous_lock synchronouslock(this->synchronization());

         auto interchangea = m_windowa;

         synchronouslock.unlock();

         //if (::micro::window_implementation::nanowindowimplementationa().has_element())
         //{

         for (auto& pwindow: interchangea)
         {

            if (pwindow)
            {

               pwindow->window_message_loop_step();

            }

         }

      }


      void windowing::application_handle(long long l, void* p)
      {


      }


      ::pixmap windowing::get_pixmap_from_file(::memory& memoryHost, const void* psourceFile, memsize sizeSourceFile)
      {

         return {};

      }


      ::windowing::enum_windowing windowing::calculate_ewindowing()
      {

         return ::windowing::e_windowing_none;

      }


      ::windowing::enum_windowing windowing::get_ewindowing()
      {

         if (m_ewindowing == ::windowing::e_windowing_none)
         {

            m_ewindowing = calculate_ewindowing();

         }

         return m_ewindowing;

      }


      bool windowing::shell_open(const ::file::path& path)
      {
         return false;
      }


      //void windowing::update_nano_user_theme()
      //{


      //}


      //::micro::theme * windowing::nano_user_theme()
      //{


      //   if (!m_pnanousertheme)
      //   {

      //      update_nano_user_theme();

      //   }

      //   return m_pnanousertheme;

      //}


      bool windowing::defer_realize(::pointer<::reified<::message_box>>& preifiedMessageBox, ::message_box* p)
      {

         return false;

      }


      bool windowing::has_resizing()
      {

         return true;

      }


      // bool windowing::is_dark_mode_through_theming()
      // {
      //
      //    return false;
      //
      // }


      ::pointer < ::user::activation_token > windowing::get_user_activation_token()
      {

         return {};

      }


//      void windowing::enable_wallpaper_change_notification()
//      {
//
//
//      }
//
//
//      bool windowing::set_wallpaper(::collection::index iScreen, string strLocalImagePath, ::acme::windowing::display * pwindowingdisplay)
//      {
//
//         throw interface_only();
//
//         //return pnode->set_wallpaper(iScreen, strLocalImagePath);
//
//         return false;
//
//      }
//
//
//      string windowing::get_wallpaper(::collection::index iScreen, ::acme::windowing::display * pwindowingdisplay)
//      {
//
//         return "";
//
//      }

      double windowing::get_default_screen_dpi()
      {

         // just a guess lol :D
         return 96.0;

      }


      float windowing::default_screen_points_to_pixels(float fPoints)
      {

         return (int)(fPoints * (get_default_screen_dpi() / 72.0));
      }



   } // namespace windowing


} // namespace acme


namespace windowing
{

   ::string get_user_toolkit_id()
   {

      return ::as_string(get_etoolkit());

   }


} // namespace windowing
