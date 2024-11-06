// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
//
// // Merged from user to
//     windowing to micro_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
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
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/department.h"
#include "acme/platform/system.h"
#include "acme/user/micro/details_window.h"
#include "acme/user/micro/message_box.h"
#include "acme/user/micro/theme.h"
#include "acme/windowing/display.h"
#include "acme/windowing/window.h"
#include "acme/windowing/windowing.h"


namespace micro
{

   user::user()
      {
      }


      user::~user()
      {
      }


      //::pointer < ::subparticle > user::micro()->message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
      //{

      //   auto psequencer = node()->micro()->message_box(strMessage, strTitle, emessagebox, strDetails);

      //   return psequencer;

      //}


      //::pointer < ::subparticle > user::micro()->message_console(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox, const ::string& strDetails)
      //{

      //   auto psequencer = node()->micro()->message_console(strMessage, strTitle, emessagebox, strDetails);

      //   return psequencer;

      //}

      //::pointer < ::message_box > user::message_box(const ::string & strMessage, const ::string & strTitle,
      //                                                       const ::e_message_box & emessagebox,
      //                                                       const ::string & strDetails, ::nano::graphics::icon * picon)
      //{
      //   auto pnode = node();

      //   auto psequencer = pnode->create_message_box_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);

      //   return psequencer;
      //}


      //::pointer < ::message_box > user::exception_message_box(
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


      //::pointer < ::message_box > user::message_console(const ::string & strMessage, const ::string & strTitle,
      //                                                           const ::e_message_box & emessagebox,
      //                                                           const ::string & strDetails, ::nano::graphics::icon * picon)
      //{
      //   auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);

      //   return psequencer;
      //}


      //::pointer < ::message_box > user::exception_message_console(
      //    const ::exception & exception, const ::string & strMessage, const ::string & strTitle,
      //    const ::e_message_box & emessagebox, const ::string & strDetails, ::nano::graphics::icon * picon)
      //{
      //   string strExceptionDetails = exception.get_consolidated_details(this);

      //   auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox,
      //                                                      strDetails + "\n" + strExceptionDetails, picon);

      //   return psequencer;
      //}


      void user::handle(::topic * ptopic, ::context * pcontext)
      {
         if (ptopic->m_atom == id_set_application_dark_mode)
         {

            auto windowa = system()->acme_windowing()->m_windowa;

            for (auto & pacmewindowingwindow : windowa)
            {
               pacmewindowingwindow->handle(ptopic, pcontext);
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
      //     windowing to micro_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
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


      //::acme::windowing::display * user::display()
      //{

      //   if (!m_pdisplay)
      //   {

      //      system()->do_graphics_and_windowing_system_factory();

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


      void user::_main_send(const ::procedure & procedure)
      {

         system()->acme_windowing()->main_send(procedure);

      }


      void user::_main_post(const ::procedure & procedure)
      {

         system()->acme_windowing()->main_post(procedure);

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

      //   system()->acme_windowing()->process_messages();

      //   // #ifdef HAS_WAYLAND
      //   //         if(psystem->m_ewindowing == ::windowing::e_windowing_wayland)
      //   //         {
      //   //
      //   //             ::wayland::micro::process_messages();
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

         auto ptopic = __allocate ::topic(id_application_dark_mode_change);

         auto microwindowingwindowa = system()->acme_windowing()->m_windowa;

         for (auto & pacmewindowingwindow : microwindowingwindowa)
         {

            pacmewindowingwindow->handle(ptopic, nullptr);

            pacmewindowingwindow->set_need_redraw();

            pacmewindowingwindow->post_redraw();

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

         auto windowa = system()->acme_windowing()->m_windowa;

         synchronouslock.unlock();

         //if (::micro::window_implementation::microwindowimplementationa().has_element())
         //{

         for (auto & pacmewindowingwindow : windowa)
         {

            if (pacmewindowingwindow)
            {

               pacmewindowingwindow->window_message_loop_step();

            }

         }




      }


      ::pixmap user::get_pixmap_from_file(::memory & memoryHost, const void * psourceFile, memsize sizeSourceFile)
      {

         return {};

      }


      void user::update_micro_theme()
      {

         __defer_construct_new(m_pmicrotheme);

         m_pmicrotheme->update_drawing_objects();


      }


      ::micro::theme * user::micro_theme()
      {


         if (!m_pmicrotheme)
         {

            update_micro_theme();

         }

         return m_pmicrotheme;

      }


      ::pointer < ::reified < ::message_box > > user::realize(::realizable < ::message_box > * p)
      {

         ::pointer < ::message_box > pmessageboxRealizable;

         pmessageboxRealizable = p;

         ::pointer < ::reified < ::message_box > > pmessageboxReified;

         if (pmessageboxRealizable->m_bDetails)
         {

            pmessageboxReified = __create_new < ::micro::details_window >();

         }
         else
         {

            pmessageboxReified = __create_new < ::micro::message_box >();

         }

         pmessageboxReified->realize(p);

         return pmessageboxReified;

      }

   
} // namespace micro



