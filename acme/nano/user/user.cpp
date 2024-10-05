// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
//
// // Merged from windowing_base to
//     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
//                   //
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// // Merged from windowing_base to
//     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "user.h"
#include "interchange.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/node.h"
#include "acme/platform/department.h"


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

        pointer<::sequencer<::conversation>> user::message_box(const ::string& strMessage, const ::string& strTitle,
                                                               const ::e_message_box& emessagebox,
                                                               const ::string& strDetails, ::nano::graphics::icon * picon)
        {
            auto pnode = node();

            auto psequencer = pnode->create_message_box_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);

            return psequencer;
        }


        pointer<::sequencer<::conversation>> user::exception_message_box(
            const ::exception& exception, const ::string& strMessageParam, const ::string& strTitleParam,
            const ::e_message_box& emessagebox, const ::string& strDetailsParam, ::nano::graphics::icon * picon)
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


        pointer<::sequencer<::conversation>> user::message_console(const ::string& strMessage, const ::string& strTitle,
                                                                   const ::e_message_box& emessagebox,
                                                                   const ::string& strDetails, ::nano::graphics::icon * picon)
        {
            auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox, strDetails, picon);

            return psequencer;
        }


        pointer<::sequencer<::conversation>> user::exception_message_console(
            const ::exception& exception, const ::string& strMessage, const ::string& strTitle,
            const ::e_message_box& emessagebox, const ::string& strDetails, ::nano::graphics::icon * picon)
        {
            string strExceptionDetails = exception.get_consolidated_details(this);

            auto psequencer = node()->create_message_sequencer(strMessage, strTitle, emessagebox,
                                                               strDetails + "\n" + strExceptionDetails, picon);

            return psequencer;
        }


        void user::handle(::topic* ptopic, ::context* pcontext)
        {
            if (ptopic->m_atom == id_set_application_dark_mode)
            {
                for (auto& pinterchange : m_interchangea)
                {
                    pinterchange->handle(ptopic, pcontext);
                }
            }
        }


        void user::sync(const ::procedure& procedure)
        {
        }


        void user::async(const ::procedure& procedure)
        {
        }

void user::process_messages()
{


}

         bool user::init_threads()
         {

           return true;

         }
// // Merged from windowing_base to
//     windowing to nano_use by camilo on 2024-10-05 11:12 <3ThomasBorregaardSorensen!!
//                   //
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// // Merged from windowing_base to
//     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
//

//
#include "framework.h"
#include "windowing_base.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/handler/topic.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/display.h"
#include "acme/nano/user/user.h"
#include "acme/windowing/window_base.h"
#include "platform/system.h"


         namespace windowing
         {


            windowing_base::windowing_base()
            {


            }


            windowing_base::~windowing_base()
            {


            }


            void windowing_base::on_initialize_particle()
            {

               ::acme::department::on_initialize_particle();

               defer_create_synchronization();

            }

            void windowing_base::destroy()
            {

               windowing_system_post_quit();

               ::acme::department::destroy();

            }



            ::nano::user::display * windowing_base::display()
            {

               if (!m_pdisplaybase)
               {

                  system()->do_user_system_factory();

                  __construct(m_pdisplaybase);

                  m_pdisplaybase->open_display();

               }

               return m_pdisplaybase;

            }


            void windowing_base::on_start_system()
            {


            }


            ::e_status windowing_base::defer_initialize_windowing_system()
            {

               return ::success;

            }


            ::e_status windowing_base::initialize_windowing_system()
            {

               return ::success;

            }


            void * windowing_base::get_display()
            {

               return nullptr;

            }


            void windowing_base::main_send(const ::procedure & procedure)
            {

               nano()->user()->sync(procedure);

            }


            void windowing_base::async(const ::procedure & procedure)
            {

               nano()->user()->async(procedure);

            }


            void windowing_base::display_error_trap_push(int i)
            {


            }


            void windowing_base::display_error_trap_pop_ignored(int i)
            {


            }


            void * windowing_base::fetch_windowing_system_display()
            {

               return nullptr;

            }


            void windowing_base::process_messages()
            {

               nano()->user()->process_messages();

               // #ifdef HAS_WAYLAND
               //         if(psystem->m_ewindowing == e_windowing_wayland)
               //         {
               //
               //             ::wayland::nano::user::process_messages();
               //
               //         }
               //         else
               // #endif
               //             if(psystem->m_ewindowing == e_windowing_xcb)
               //             {
               //
               //                 ::xcb::nano::user::process_messages();
               //
               //             }
               //             else
               //             {
               //
               //                 ::x11::nano::user::process_messages();
               //
               //             }


            }


            void windowing_base::windowing_system_application_main_loop()
            {



            }


            void windowing_base::windowing_system_post_quit()
            {


            }


            ::color::color windowing_base::get_system_color(enum_system_color esystemcolor)
            {

               throw ::interface_only();

               return argb(0, 0, 0, 0);

            }


            void windowing_base::on_system_dark_mode_change(bool bDarkMode, const ::color::color & colorBackground)
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

               for (auto & pwindowbase : m_windowbasea)
               {

                  pwindowbase->handle(ptopic, nullptr);

                  pwindowbase->set_need_redraw();

                  pwindowbase->post_redraw();

               }

            }


            bool windowing_base::dark_mode()
            {

               return false;

            }


            void windowing_base::set_dark_mode(bool bDarkMode)
            {



            }


            void windowing_base::fetch_system_background_color()
            {



            }



            ::color::color windowing_base::reinterpreted_background_color()
            {

               if (dark_mode())
               {

                  return ::color::black;

               }

               return ::color::white;

            }




            void windowing_base::_do_tasks()
            {

               _synchronous_lock synchronouslock(this->synchronization());

               auto windowbasea = m_windowbasea;

               synchronouslock.unlock();

               //if (::nano::user::window_implementation::nanowindowimplementationa().has_element())
               //{

               for (auto & pimplementation : windowbasea)
               {

                  if (pimplementation)
                  {

                     pimplementation->implementation_message_loop_step();

                  }

               }




            }


            ::pixmap windowing_base::get_pixmap_from_file(::memory & memoryHost, const void * psourceFile, memsize sizeSourceFile)
            {

               return {};

            }




    } // namespace user
} // namespace nano
