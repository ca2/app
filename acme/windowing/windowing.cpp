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
#include "window.h"
#include "windowing.h"
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

      //   if (strExceptionDetails.has_char())
      //   {
      //      if (strDetails.has_char())
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


      void windowing::handle(::topic * ptopic, ::context * pcontext)
      {
         if (ptopic->m_atom == id_set_application_dark_mode)
         {
            for (auto & pwindow : m_windowa)
            {
               pwindow->handle(ptopic, pcontext);
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

         defer_create_synchronization();

      }

      void windowing::destroy()
      {

         //windowing_system_post_quit();

         ::acme::department::destroy();

      }




      ::acme::windowing::display * windowing::acme_display()
      {

         if (!m_pacmedisplay)
         {

            system()->do_graphics_and_windowing_system_factory();

            __construct(m_pacmedisplay);

            m_pacmedisplay->open_display();

         }

         return m_pacmedisplay;

      }


      void windowing::on_start_system()
      {


      }


      ::windowing::windowing * windowing::windowing_windowing()
      {

         return nullptr;

      }


      ::e_status windowing::defer_initialize_windowing_system()
      {

         return ::success;

      }


      ::e_status windowing::initialize_windowing_system()
      {

         return ::success;

      }


      void * windowing::get_display()
      {

         return nullptr;

      }


      void windowing::_main_send(const ::procedure & procedure)
      {

         //main_send(procedure);

      }


      void windowing::_main_post(const ::procedure & procedure)
      {

         //main_post(procedure);

      }


      void windowing::display_error_trap_push(int i)
      {


      }


      void windowing::display_error_trap_pop_ignored(int i)
      {


      }


      void * windowing::fetch_windowing_system_display()
      {

         return nullptr;

      }


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


      void windowing::windowing_system_application_main_loop()
      {



      }


      void windowing::windowing_system_post_quit()
      {


      }


      ::color::color windowing::get_system_color(enum_system_color esystemcolor)
      {

         throw ::interface_only();

         return argb(0, 0, 0, 0);

      }


      void windowing::on_system_dark_mode_change(bool bDarkMode, const ::color::color & colorBackground)
      {

         if (colorBackground != ::color::transparent)
         {

            system()->background_color(colorBackground);

         }
         else
         {

            system()->set_dark_mode(bDarkMode);

         }

         auto ptopic = __new ::topic(id_application_dark_mode_change);

         for (auto & pwindow : m_windowa)
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

         for (auto & pwindow : interchangea)
         {

            if (pwindow)
            {

               pwindow->window_message_loop_step();

            }

         }




      }


      ::pixmap windowing::get_pixmap_from_file(::memory & memoryHost, const void * psourceFile, memsize sizeSourceFile)
      {

         return {};

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

   } // namespace user


} // namespace acme


namespace windowing
{

   ::string get_user_toolkit_id()
   {

      return ::as_string(get_etoolkit());

   }


} // namespace windowing