// Split/separation of concerns from micro to
// acme::windowing by camilo on 2024-10-05 18:03 <3ThomasBorregaardSorensen!!
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
#include "acme/prototype/collection/comparable_list.h"
#include "_.h"


namespace acme
{

   
   namespace windowing
   {
      
      
      class CLASS_DECL_ACME windowing :
         virtual public ::acme::department
      {
      public:


         ::pointer_array < ::acme::windowing::window >     m_windowa;
         ::pointer<::acme::windowing::display>             m_pacmedisplay;
         // ::pointer_array<::acme::windowing::window> m_windowbasea;
         //::pointer < ::micro::theme >            m_pnanousertheme;


         windowing();
         ~windowing() override;


         //inline static const char * represented_component_name() { return "nano_windowing"; }

         //::acme::windowing::window * windowing_window() override;
         //::micro::theme * nano_user_theme();
         //::pointer < ::subparticle > nano()->message_box(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);
         //virtual void update_nano_user_theme();

         ////pointer< ::sequence < ::conversation > > message_box(const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr);

         //::pointer < ::subparticle > nano()->message_console(const ::string& strMessage, const ::string& strTitle = nullptr, const ::e_message_box& emessagebox = e_message_box_ok, const ::string& strDetails = nullptr);


         //::pointer < ::subparticle > message_box(const ::string & strMessage, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

         //::pointer < ::subparticle > exception_message_box(const ::exception & exception, const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

         //::pointer < ::subparticle > message_console(const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

         //::pointer < ::subparticle > exception_message_console(const ::exception & exception, const ::string & strMessage = nullptr, const ::string & strTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::string & strDetails = nullptr, ::nano::graphics::icon * picon = nullptr);


         void handle(::topic * ptopic, ::context * pcontext) override;


         void _main_send(const ::procedure & procedure) override;
         void _main_post(const ::procedure & procedure) override;

         //void _main_send(::subparticle * p) override;
         //void _main_post(::subparticle * p) override;

         virtual void process_messages();

         virtual bool init_threads();

         
         virtual void show(::particle_pointer pparticle);

         //// windowing_system


         //

         //windowing_base();

         //~windowing_base() override;


         void on_initialize_particle() override;


         void destroy() override;


         virtual ::acme::windowing::display * acme_display();


         virtual ::windowing::windowing * windowing_windowing();

         virtual void on_start_system();

         virtual void _do_tasks();

         virtual ::e_status defer_initialize_windowing_system();

         virtual ::e_status initialize_windowing_system();

         virtual void * get_display();

         //void main_send(const ::procedure & procedure) override;

         //void main_post(const ::procedure & procedure) override;

         virtual void display_error_trap_push(int i);

         virtual void display_error_trap_pop_ignored(int i);

         virtual void * fetch_windowing_system_display();

         //virtual void process_messages();

         virtual void windowing_system_application_main_loop();

         virtual void windowing_system_post_quit();

         virtual ::color::color get_system_color(enum_system_color esystemcolor);


         virtual void on_system_dark_mode_change(bool bDarkMode,
                                                 const ::color::color & colorBackground = ::color::transparent);

         virtual void set_dark_mode(bool bDarkMode);


         virtual bool dark_mode();

         virtual void fetch_system_background_color();


         ::color::color reinterpreted_background_color();


         virtual ::pixmap get_pixmap_from_file(::memory & memoryHost, const void * psourceFile, memsize sizeSourceFile);

      };



   } // namespace user


} // namespace acme



CLASS_DECL_ACME void initialize_acme_user(::factory::factory * pfactory);
CLASS_DECL_ACME::string as_string(::windowing::enum_toolkit etoolkit);

namespace windowing
{

   CLASS_DECL_ACME::string get_user_toolkit_id();


} // namespace windowing



