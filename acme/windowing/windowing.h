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
#include "acme/handler/task_handler.h"


namespace acme
{

   
   namespace windowing
   {


      class CLASS_DECL_ACME windowing :
         virtual public ::platform::department,
         virtual public ::task,
         virtual public ::task_handler
      {
      public:


         ::pointer_array < ::acme::windowing::window >      m_windowa;
         ::pointer<::acme::windowing::display>              m_pacmedisplay;
         ::windowing::enum_windowing                        m_ewindowing;
         ::pointer<::acme::windowing::window>               m_pacmewindowingwindowMouseCapture;
         class ::time                                       m_timeDarkMode;

         ::windowing::enum_bias                             m_ewindowingbias;

         windowing();
         ~windowing() override;

         virtual ::windowing::enum_bias calculate_windowing_bias();

         inline ::windowing::enum_bias windowing_bias() { return m_ewindowingbias; }


         //inline static const_char_pointer represented_component_name() { return "nano_windowing"; }

         //::acme::windowing::window * windowing_window() override;
         //::micro::theme * nano_user_theme();
         //::pointer < ::subparticle > nano()->message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);
         //virtual void update_nano_user_theme();

         ////pointer< ::sequence < ::conversation > > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);

         //::pointer < ::subparticle > nano()->message_console(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box& emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr);


         //::pointer < ::subparticle > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

         //::pointer < ::subparticle > exception_message_box(const ::exception & exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

         //::pointer < ::subparticle > message_console(const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

         //::pointer < ::subparticle > exception_message_console(const ::exception & exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

         virtual ::particle * defer_initialize_host_window(const ::int_rectangle* lpcrect);
         
         virtual void _will_finish_launching();
         
         virtual void _did_finish_launching();
         
         virtual void set_clipboard_text(const_char_pointer psz);
         
         virtual ::acme::windowing::window* get_application_host_window();

         virtual ::pointer < ::acme::windowing::window > get_new_window();
         
         //      ::windowing::window* new_window(::windowing::window* pimpl) override;
         //
         virtual void erase_window(::acme::windowing::window* pwindow);
         
         virtual ::acme::windowing::window* window(oswindow oswindow);

         
         virtual void _message_handler(void* p);
         
         virtual ::acme::windowing::window * get_keyboard_focus(::thread* pthread);
         
         virtual ::acme::windowing::window * get_mouse_capture(::thread* pthread);
         
         
         virtual bool defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow);
         
         
         //         virtual void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr);
         

         
         void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


         void _main_send(const ::procedure & procedure) override;
         void _main_post(const ::procedure & procedure) override;

         //void _main_send(::subparticle * p) override;
         //void _main_post(::subparticle * p) override;

         virtual void process_messages();

         virtual bool init_threads();

         void __task_suffix() override;

         
         virtual void show(::particle_pointer pparticle);

         //// windowing_system

         virtual ::pointer < ::user::activation_token > get_user_activation_token();
         //

         //windowing_base();

         //~windowing_base() override;


         void on_initialize_particle() override;


         void destroy() override;

         virtual ::acme::windowing::display * acme_display();


         virtual ::windowing::windowing * windowing_windowing();

         virtual void _do_tasks();
         
         virtual void application_handle(long long l, void * p);

         //virtual void defer_initialize_windowing();

         virtual void initialize_windowing();

         virtual void on_activate();

         virtual void finalize_windowing();


         virtual void on_create_window_object(::acme::user::interaction * puserinteraction);


         //virtual void * get_display();

         //void main_send(const ::procedure & procedure) override;

         //void main_post(const ::procedure & procedure) override;

         virtual void display_error_trap_push(int i);

         virtual void display_error_trap_pop_ignored(int i);

         //virtual void * fetch_windowing_display();

         //virtual void process_messages();

         //virtual void on_start_windowing_application();

         virtual void windowing_application_on_system_start();

         virtual void windowing_application_on_start();

         virtual void windowing_application_main_loop();

         virtual void windowing_post_quit();

         virtual ::color::color get_system_color(enum_system_color esystemcolor);

         virtual ::color::color get_operating_system_background_color();


         virtual void fetch_dark_mode();


         virtual void on_system_dark_mode_change(bool bDarkMode,
                                                 const ::color::color & colorBackground = ::color::transparent);

         virtual void set_dark_mode(bool bDarkMode);
         virtual bool dark_mode();

         virtual class ::time dark_mode_time() const;
         virtual void set_dark_mode_time(const class ::time & time);


         //virtual bool is_dark_mode_through_theming();

         virtual void fetch_system_background_color();


         ::color::color reinterpreted_background_color();


         virtual ::pixmap get_pixmap_from_file(::memory & memoryHost, const void * psourceFile, memsize sizeSourceFile);


         virtual ::windowing::enum_windowing calculate_ewindowing();
         virtual ::windowing::enum_windowing get_ewindowing();


         virtual bool shell_open(const ::file::path & path);

         virtual bool defer_realize(         ::pointer < ::reified < ::message_box > > & preifiedMessageBox, ::message_box * p);

         virtual bool has_resizing();


         //virtual enum_bias calculate_bias();

         //virtual void enable_wallpaper_change_notification();

         //virtual bool set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrLocalImagePath, ::acme::windowing::display * pwindowingdisplay);

         //virtual string get_wallpaper(::collection::index iScreen, ::acme::windowing::display * pwindowingdisplay);
         virtual double get_default_screen_dpi();
         virtual float default_screen_points_to_pixels(float fPoints);


      };

   
   } // namespace user


} // namespace acme



CLASS_DECL_ACME void initialize_acme_user(::factory::factory * pfactory);
CLASS_DECL_ACME::string as_string(::windowing::enum_toolkit etoolkit);

namespace windowing
{

   CLASS_DECL_ACME::string get_user_toolkit_id();


} // namespace windowing



