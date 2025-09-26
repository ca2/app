// Created by camilo on 2022-11-19 03:54 <3ThomasBorregaardSorensen!!
// 
// // Merged from (acme)windowing and (acme)windowing_system by
// //   camilo on 2024-10-05 11:06 <3ThomasBorregaardSorensen!!
// //   (acme)windowing_system::windowing_system
// //       ---->windowing::windowing_base
// // //       ---->micro::user
// //   (acme)windowing::window_base
// //       ---->micro::interchange
// 
// Created by camilo on 2024-05-26 21:50 <3ThomasBorregaardSorensen!!
// Merged from windowing_system to
//     windowing by camilo on 2024-10-05 10:35 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"
#include "acme/platform/message_box.h"
#include "acme/prototype/collection/comparable_list.h"
#include "_.h"


namespace micro
{

   class CLASS_DECL_ACME user :
      virtual public acme::department,
      virtual public ::reificator < ::message_box >
   {
   public:


      //::pointer_array < ::acme::windowing::window >      m_windowa;
      // ::pointer<::acme::windowing::display>              m_pdisplay;
      // ::pointer_array<::acme::windowing::window> m_windowbasea;
      ::pointer < ::micro::theme >                  m_pmicrotheme;


      user();
      ~user() override;


      //inline static const_char_pointer represented_component_name() { return "nano_user"; }


      ::micro::theme * micro_theme();
      //::pointer < ::subparticle > nano()->message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);
      virtual void update_micro_theme();

      ////pointer< ::sequence < ::conversation > > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);

      //::pointer < ::subparticle > nano()->message_console(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);



      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      //virtual void sync(const ::procedure & procedure);
      //virtual void async(const ::procedure & procedure);


      virtual void process_messages();

      virtual bool init_threads();



      //// windowing_system


      //

      //windowing_base();

      //~windowing_base() override;


      void on_initialize_particle() override;


      void destroy() override;


      //virtual ::acme::windowing::display * display();


      virtual void on_start_system();

      virtual void _do_tasks();

      virtual ::e_status defer_initialize_windowing_system();

      virtual ::e_status initialize_windowing_system();

      virtual void * get_display();

      void _main_send(const ::procedure & procedure) override;
      void _main_post(const ::procedure & procedure) override;

      //void _main_send(::subparticle * p) override;
      //void _main_post(::subparticle * p) override;

      virtual void display_error_trap_push(int i);

      virtual void display_error_trap_pop_ignored(int i);

      virtual void * fetch_windowing_system_display();

      //virtual void process_messages();

      virtual void windowing_system_application_main_loop();

      virtual void windowing_system_post_quit();


      void display(::message_box * pmessagebox);
      void display_exception(const ::exception & exception, ::message_box * pmessagebox);


      //::pointer < ::message_box > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr) override;
      //::pointer < ::message_box > exception_message_box(const ::exception & exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr) override;
      ////::pointer < ::message_box > message_console(const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr) override;
      ////::pointer < ::message_box > exception_message_console(const ::exception & exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr) override;


      virtual ::color::color get_system_color(enum_system_color esystemcolor);


      virtual void on_system_dark_mode_change(bool bDarkMode,
                                              const ::color::color & colorBackground = ::color::transparent);

      virtual void set_dark_mode(bool bDarkMode);


      virtual bool dark_mode();

      virtual void fetch_system_background_color();


      ::color::color reinterpreted_background_color();


      virtual ::pixmap get_pixmap_from_file(::memory & memoryHost, const void * psourceFile, memsize sizeSourceFile);

      ::pointer < ::reified < ::message_box > > realize(::realizable < ::message_box > * p) override;


   };



} // namespace micro





CLASS_DECL_ACME void initialize_nano_user(::factory::factory * pfactory);



