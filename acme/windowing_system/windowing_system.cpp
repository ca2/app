//
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing_system.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/user.h"


namespace windowing_system
{


    windowing_system::windowing_system()
    {


    }


    windowing_system::~windowing_system()
    {


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


} // namespace windowing_system



