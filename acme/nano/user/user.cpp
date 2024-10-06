// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
//
// // Merged from user to
//     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
//                   //
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// // Merged from user to
//     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
#include "framework.h"
//#include "display.h"
#include "user.h"
//#include "window.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/handler/topic.h"
#include "acme/nano/nano.h"
#include "acme/nano/windowing/window.h"
#include "acme/nano/windowing/windowing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/department.h"
#include "acme/platform/system.h"
#include "acme/nano/windowing/display.h"
#include "acme/nano/windowing/windowing.h"


namespace nano
{
   namespace user
   {
      user::user()
      {
      }


      user::~user()
      {
      }


      //pointer< ::sequencer < ::conversation > > user::nano()->message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
      //{

      //   auto psequencer = node()->nano()->message_box(strMessage, strTitle, emessagebox, strDetails);

      //   return psequencer;

      //}


      //pointer< ::sequencer < ::conversation > > user::nano()->message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
      //{

      //   auto psequencer = node()->nano()->message_console(strMessage, strTitle, emessagebox, strDetails);

      //   return psequencer;

      //}

      pointer<::sequencer<::conversation>> user::message_box(const ::string & strMessage, const ::string & strTitle,
                                                             const ::e_message_box & emessagebox,
                                                             const ::string & strDetails, ::nano::graphics::icon * picon)
      {
         auto pnode = node();

         auto psequencer = pnode->create_message_box_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);

         return psequencer;
      }


      pointer<::sequencer<::conversation>> user::exception_message_box(
          const ::exception & exception, const ::string & strMessageParam, const ::string & strTitleParam,
          const ::e_message_box & emessagebox, const ::string & strDetailsParam, ::nano::graphics::icon * picon)
      {
         string strExceptionDetails = exception.get_consolidated_details(this);

         string strMessage(strMessageParam);

         if (strMessage.is_empty())
         {
            strMessage = exception.get_message();
         }

         string strTitle(strTitleParam);

         if (strTitle.is_empty())
         {
            strTitle = exception.get_title();
         }

         string strDetails(strDetailsParam);

         if (strExceptionDetails.has_char())
         {
            if (strDetails.has_char())
            {
               strDetails += "\n";
            }

            strDetails += strExceptionDetails;
         }

         auto psequencer = node()->create_message_box_sequencer(
             strMessage,
             strTitle,
             emessagebox,
             strDetails,
             picon);

         return psequencer;
      }


      pointer<::sequencer<::conversation>> user::message_console(const ::string & strMessage, const ::string & strTitle,
                                                                 const ::e_message_box & emessagebox,
                                                                 const ::string & strDetails, ::nano::graphics::icon * picon)
      {
         auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);

         return psequencer;
      }


      pointer<::sequencer<::conversation>> user::exception_message_console(
          const ::exception & exception, const ::string & strMessage, const ::string & strTitle,
          const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
      {
         string strExceptionDetails = exception.get_consolidated_details(this);

         auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox,
                                                            strDetails + "\n" + strExceptionDetails, picon);

         return psequencer;
      }


      void user::handle(::topic * ptopic, ::context * pcontext)
      {
         if (ptopic->m_atom == id_set_application_dark_mode)
         {

            auto windowa = nano()->windowing()->m_windowa;

            for (auto & pnanowindowingwindow : windowa)
            {
               pnanowindowingwindow->handle(ptopic, pcontext);
            }
         }
      }



      void user::process_messages()
      {


      }

      bool user::init_threads()
      {

         return true;

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
      //#include "acme/nano/user/display.h"
      //#include "acme/nano/user/user.h"
      ////#include "acme/windowing/window_base.h"
      //#include "platform/system.h"


               //namespace windowing
               //{


                /*  user::user()
                  {


                  }


                  user::~user()
                  {


                  }*/


      void user::on_initialize_particle()
      {

         ::acme::department::on_initialize_particle();

         defer_create_synchronization();

      }

      void user::destroy()
      {

         windowing_system_post_quit();

         ::acme::department::destroy();

      }


      //::nano::windowing::display * user::display()
      //{

      //   if (!m_pdisplay)
      //   {

      //      system()->do_graphics_user_windowing_system_factory();

      //      __construct(m_pdisplaybase);

      //      m_pdisplaybase->open_display();

      //   }

      //   return m_pdisplaybase;

      //}


      void user::on_start_system()
      {


      }


      ::e_status user::defer_initialize_windowing_system()
      {

         return ::success;

      }


      ::e_status user::initialize_windowing_system()
      {

         return ::success;

      }


      void * user::get_display()
      {

         return nullptr;

      }


      void user::main_send(const ::procedure & procedure)
      {

         nano()->windowing()->main_send(procedure);

      }


      void user::main_post(const ::procedure & procedure)
      {

         nano()->windowing()->main_post(procedure);

      }


      void user::display_error_trap_push(int i)
      {


      }


      void user::display_error_trap_pop_ignored(int i)
      {


      }


      void * user::fetch_windowing_system_display()
      {

         return nullptr;

      }


      //void user::process_messages()
      //{

      //   nano()->user()->process_messages();

      //   // #ifdef HAS_WAYLAND
      //   //         if(psystem->m_ewindowing == ::windowing::e_windowing_wayland)
      //   //         {
      //   //
      //   //             ::wayland::nano::user::process_messages();
      //   //
      //   //         }
      //   //         else
      //   // #endif
      //   //             if(psystem->m_ewindowing == ::windowing::e_windowing_xcb)
      //   //             {
      //   //
      //   //                 ::xcb::nano::user::process_messages();
      //   //
      //   //             }
      //   //             else
      //   //             {
      //   //
      //   //                 ::x11::nano::user::process_messages();
      //   //
      //   //             }


      //}


      void user::windowing_system_application_main_loop()
      {



      }


      void user::windowing_system_post_quit()
      {


      }


      ::color::color user::get_system_color(enum_system_color esystemcolor)
      {

         throw ::interface_only();

         return argb(0, 0, 0, 0);

      }


      void user::on_system_dark_mode_change(bool bDarkMode, const ::color::color & colorBackground)
      {

         if (colorBackground != ::color::transparent)
         {

            system()->background_color(colorBackground);

         }
         else
         {

            system()->set_dark_mode(bDarkMode);

         }

         auto ptopic = ::place(new ::topic(id_application_dark_mode_change));

         auto nanowindowingwindowa = nano()->windowing()->m_windowa;

         for (auto & pnanowindowingwindow : nanowindowingwindowa)
         {

            pnanowindowingwindow->handle(ptopic, nullptr);

            pnanowindowingwindow->set_need_redraw();

            pnanowindowingwindow->post_redraw();

         }

      }


      bool user::dark_mode()
      {

         return false;

      }


      void user::set_dark_mode(bool bDarkMode)
      {



      }


      void user::fetch_system_background_color()
      {



      }



      ::color::color user::reinterpreted_background_color()
      {

         if (dark_mode())
         {

            return ::color::black;

         }

         return ::color::white;

      }




      void user::_do_tasks()
      {

         _synchronous_lock synchronouslock(this->synchronization());

         auto windowa = nano()->windowing()->m_windowa;

         synchronouslock.unlock();

         //if (::nano::user::window_implementation::nanowindowimplementationa().has_element())
         //{

         for (auto & pnanowindowingwindow : windowa)
         {

            if (pnanowindowingwindow)
            {

               pnanowindowingwindow->window_message_loop_step();

            }

         }




      }


      ::pixmap user::get_pixmap_from_file(::memory & memoryHost, const void * psourceFile, memsize sizeSourceFile)
      {

         return {};

      }


      void user::update_nano_user_theme()
      {



      }


      ::nano::user::theme * user::nano_user_theme()
      {


         if (!m_pnanousertheme)
         {

            update_nano_user_theme();

         }

         return m_pnanousertheme;

      }

   } // namespace user
} // namespace nano
