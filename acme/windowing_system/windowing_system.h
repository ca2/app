//
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/department.h"
#include "acme/graphics/image/pixmap.h"


namespace windowing_system
{


    class CLASS_DECL_ACME windowing_system :
    virtual public ::acme::department
    {
    public:


       ::pointer_array < ::windowing::window_base >           m_windowbasea;



        windowing_system();
        ~windowing_system() override;


        void on_initialize_particle() override;


       virtual void on_start_system();

       virtual void _do_tasks();
        virtual ::e_status defer_initialize_windowing_system();
        virtual ::e_status initialize_windowing_system();
        virtual void * get_display();
        virtual void sync(const ::procedure & procedure);
        virtual void async(const ::procedure & procedure);
        virtual void display_error_trap_push(int i);
        virtual void display_error_trap_pop_ignored(int i);

       virtual void * fetch_windowing_system_display();

        virtual void process_messages();

       virtual void windowing_system_application_main_loop();
       virtual void windowing_system_post_quit();

       virtual ::color::color get_system_color(enum_system_color esystemcolor);


       virtual void on_system_dark_mode_change(bool bDarkMode, const ::color::color & colorBackground = ::color::transparent);
       
       virtual void set_dark_mode(bool bDarkMode);


       virtual bool dark_mode();

       virtual void fetch_system_background_color();


       ::color::color reinterpreted_background_color();


       virtual ::pixmap get_pixmap_from_file(::memory & memoryHost, const void * psourceFile, memsize sizeSourceFile);


    };


} // namespace windowing_system



