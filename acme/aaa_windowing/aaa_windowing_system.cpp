//
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// // Merged from windowing_base to
//     windowing by camilo on 2024-10-05 10:36 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing_base.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/handler/topic.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/display.h"
#include "acme/user/micro/user.h"
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



    ::acme::windowing::display * windowing_base::display()
    {

        if(!m_pdisplaybase)
        {

            system()->do_graphics_and_windowing_system_factory();

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

        system()->acme_windowing()->sync(procedure);

    }


    void windowing_base::async(const ::procedure & procedure)
    {

        system()->acme_windowing()->async(procedure);

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

        system()->acme_windowing()->process_messages();

// #ifdef HAS_WAYLAND
//         if(psystem->m_ewindowing == ::windowing::e_windowing_wayland)
//         {
//
//             ::wayland::micro::process_messages();
//
//         }
//         else
// #endif
//             if(psystem->m_ewindowing == ::windowing::e_windowing_xcb)
//             {
//
//                 ::xcb::micro::process_messages();
//
//             }
//             else
//             {
//
//                 ::x11::micro::process_messages();
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

        if(colorBackground != ::color::transparent)
        {

            system()->background_color(colorBackground);

        }
        else
        {

            system()->set_dark_mode(bDarkMode);

        }

        auto ptopic = __new ::topic(id_application_dark_mode_change);

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

       //if (::micro::window_implementation::nanowindowimplementationa().has_element())
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


} // namespace windowing_base



