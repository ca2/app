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
#include "acme/operating_system/window.h"
#include "acme/constant/lightui.h"

#ifdef WINDOWS_DESKTOP
#include "acme/operating_system/windows/_window_class.h"
#endif


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


         //::pointer_array < ::acme::windowing::window >      m_windowa;
         
         //::map < ::operating_system::window, ::pointer < ::acme::windowing::window > > m_windowmap;
         
         ::pointer<::acme::windowing::display>              m_pacmedisplay;
         ::windowing::enum_windowing                        m_ewindowing;
         ::pointer<::acme::windowing::window>               m_pacmewindowingwindowMouseCapture;
         class ::time                                       m_timeDarkMode;

         ::windowing::enum_bias                             m_ewindowingbias;


         ::procedure                                        m_callbackOnApplicationActivate;

         bool                                               m_bApplicationActivated;
         bool                                               m_bIsOperatingAmbientApplicationHeld;



         windowing();
         ~windowing() override;

         virtual ::windowing::enum_bias calculate_windowing_bias();

         inline ::windowing::enum_bias windowing_bias() { return m_ewindowingbias; }


         virtual ::string get_version();
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

         virtual ::particle * defer_initialize_host_window(const ::i32_rectangle* lpcrect);
         
         virtual void _will_finish_launching();
         
         virtual void _did_finish_launching();
         
         virtual void set_clipboard_text(const_char_pointer psz);
         
         virtual ::acme::windowing::window* get_application_host_window();

         virtual ::pointer < ::acme::windowing::window > get_new_window();
         
         //      ::windowing::window* new_window(::windowing::window* pimpl) override;
         //
         virtual void add_window(::acme::windowing::window *pwindow);
         virtual void erase_window(::acme::windowing::window* pwindow);
         
         //virtual ::acme::windowing::window* window_from_HWND(void * pHWND);

         virtual void each_window(const ::function<void(::acme::windowing::window *)> &function);  
         virtual void on_user_command(::uptr u, ::lightui::enum_notification enotification, ::uptr uControl);
         virtual void _message_handler(void* p);
         
         virtual ::acme::windowing::window * get_keyboard_focus(::thread* pthread);
         
         virtual ::acme::windowing::window * get_mouse_capture(::thread* pthread);
         
         
         virtual bool defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow);
         
         
         //         virtual void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr);
         
         virtual void hide_application();

         
         void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


         void main_send(const ::procedure & procedure) override;
         void main_post(const ::procedure & procedure) override;

         //void _main_send(::subparticle * p) override;
         //void _main_post(::subparticle * p) override;

         virtual void process_messages();

         virtual bool init_threads();

         void __task_suffix() override;

         
         virtual void show(::particle_pointer pparticle);

         //// windowing_system

         virtual ::pointer < ::user::activation_token > get_user_activation_token();
         //


#ifdef WINDOWS_DESKTOP


         virtual ::windows::window_class _custom_window_class(const ::scoped_string & scopedstrClassName, void * pHICON_Big, void * pHICON_Small);
         virtual ::windows::window_class _default_window_class();
         virtual ::windows::window_class _acme_nano_window_class();
         virtual ::windows::window_class _com_host_window_class();

#endif
         //windowing_base();

         //~windowing_base() override;


         void on_initialize_particle() override;


         void destroy() override;

         virtual ::acme::windowing::display * acme_display();

         virtual ::acme::windowing::window * acme_windowing_window(const ::operating_system::window & operatingsystemwindow);

         virtual ::operating_system::window operating_system_window(const ::wparam & wparam);
         
         virtual ::operating_system::window operating_system_window(const ::lparam & lparam);

         virtual ::acme::windowing::window * acme_windowing_window(const ::lparam & lparam);

         virtual ::windowing::windowing * windowing_windowing();

         virtual void _do_tasks();
         
         virtual void application_handle(::i64 l, void * p);

         //virtual void defer_initialize_windowing();

         virtual void initialize_windowing();

         virtual void on_activate();

         virtual void finalize_windowing();


         virtual void on_create_window_object(::acme::user::interaction * puserinteraction);


         //virtual void * get_display();

         //void main_send(const ::procedure & procedure) override;

         //void main_post(const ::procedure & procedure) override;

         virtual void display_error_trap_push(::i32 i);

         virtual void display_error_trap_pop_ignored(::i32 i);

         //virtual void * fetch_windowing_display();

         //virtual void process_messages();

         //virtual void on_start_windowing_application();

         virtual void windowing_application_on_system_start();

         //virtual void windowing_application_on_start();

         void run() override;

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

         //virtual bool defer_realize(         ::pointer < ::reified < ::message_box > > & preifiedMessageBox, ::message_box * p);

         virtual bool has_resizing();


         //virtual enum_bias calculate_bias();

         //virtual void enable_wallpaper_change_notification();

         //virtual bool set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrLocalImagePath, ::acme::windowing::display * pwindowingdisplay);

         //virtual string get_wallpaper(::collection::index iScreen, ::acme::windowing::display * pwindowingdisplay);
         virtual ::f64 get_default_screen_dpi();
         virtual ::f32 default_screen_points_to_pixels(::f32 fPoints);



         virtual void hook_operating_ambient_theme_change_callbacks();


         virtual void on_hold_operating_ambient_application();
         virtual void on_unhold_operating_ambient_application();


         virtual void on_application_activate();


         void run_loop2(::task *ptask) override;


      };

   
   } // namespace user


} // namespace acme



CLASS_DECL_ACME void initialize_acme_user(::factory::factory * pfactory);
CLASS_DECL_ACME::string as_string(::windowing::enum_toolkit etoolkit);

namespace windowing
{

   CLASS_DECL_ACME::string get_user_toolkit_id();


} // namespace windowing



