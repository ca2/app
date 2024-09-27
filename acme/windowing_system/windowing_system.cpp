//
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing_system.h"
#include "acme/constant/id.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/handler/topic.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/user.h"
#include "acme/windowing/window_base.h"
#include "platform/system.h"


namespace windowing_system
{


    windowing_system::windowing_system()
    {


    }


    windowing_system::~windowing_system()
    {


    }


   void windowing_system::on_initialize_particle()
   {

      ::acme::department::on_initialize_particle();

      defer_create_synchronization();

   }


    void windowing_system::on_start_system()
    {


    }


    ::e_status windowing_system::defer_initialize_windowing_system()
    {

        return ::success;

    }


    ::e_status windowing_system::initialize_windowing_system()
    {

        return ::success;

    }


    void * windowing_system::get_display()
    {

        return nullptr;

    }


    void windowing_system::sync(const ::procedure & procedure)
    {

        nano()->user()->sync(procedure);

    }


    void windowing_system::async(const ::procedure & procedure)
    {

        nano()->user()->async(procedure);

    }


    void windowing_system::display_error_trap_push(int i)
    {


    }


    void windowing_system::display_error_trap_pop_ignored(int i)
    {


    }


    void * windowing_system::fetch_windowing_system_display()
    {

       return nullptr;

    }


    void windowing_system::process_messages()
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


    void windowing_system::windowing_system_application_main_loop()
    {



    }


    void windowing_system::windowing_system_post_quit()
    {


    }


    ::color::color windowing_system::get_system_color(enum_system_color esystemcolor)
    {

        throw ::interface_only();

        return argb(0, 0, 0, 0);

    }


    void windowing_system::on_system_dark_mode_change(bool bDarkMode, const ::color::color & colorBackground)
    {

        if(colorBackground != ::color::transparent)
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


    bool windowing_system::dark_mode()
    {

       return false;

    }


    void windowing_system::set_dark_mode(bool bDarkMode)
    {



    }


    void windowing_system::fetch_system_background_color()
    {



    }



    ::color::color windowing_system::reinterpreted_background_color()
    {

       if (dark_mode())
       {

          return ::color::black;

       }

       return ::color::white;

    }




    void windowing_system::_do_tasks()
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


} // namespace windowing_system



