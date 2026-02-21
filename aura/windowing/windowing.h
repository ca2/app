// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "acme/windowing/windowing.h"
#include "acme/prototype/collection/int_map.h"
#include "acme/prototype/collection/list.h"


//CLASS_DECL_AURA ::windowing::window * __interaction_impl(::windowing::window * pwindow);


namespace windowing
{


   using display_map = iptr_map < ::pointer<display > >;


   class CLASS_DECL_AURA windowing :
      virtual public ::acme::windowing::windowing
   {
   public:


      ::sandbox_windowing::windowing *          m_psandboxwindowing;

      display_map                               m_displaymap;

      ::pointer < ::mutex >                     m_pmutexDisplay;
      ::pointer < ::mutex >                     m_pmutexWindow;
      ::pointer < ::mutex >                     m_pmutexMonitor;


      bool                                      m_bSettingCursorMatter;
      ::pointer<::windowing::cursor_manager>    m_pcursormanager;
      ::pointer<::windowing::keyboard>          m_pkeyboard;



      ::pointer<::windowing::cursor>            m_pcursor;
      ::pointer<::windowing::cursor>            m_pcursorCursor;
      enum_cursor                               m_ecursorDefault;
      enum_cursor                               m_ecursor;

      bool                                      m_bDrawCursor;

      void *                                    m_pSnLauncheeContext;

      //::pointer<::user::user>                   m_puser;

      // Fallback implementation of a Main thread mouse capture

      windowing();
      ~windowing() override;


      ::windowing::keyboard * keyboard();


      bool is_branch_current() const override;
      
      virtual void set_dark_mode(bool bDarkMode) override;


      //::aura::application* get_app();
      //::aura::session* get_session();
      //::aura::system* system();

      ::windowing::windowing * windowing_windowing() override;

      virtual bool combo_box_list_box_is_top_level();

      void on_create_window_object(::acme::user::interaction * puserinteraction) override;
      //virtual void _initialize_windowing();

      virtual bool has_readily_gettable_absolute_coordinates() const;
      virtual bool has_mouse_capture_capability();


      //virtual void initialize_windowing(::user::user * puser);

      void initialize_windowing() override;

      //virtual void terminate_windowing();

      virtual void defer_term_ui();

      virtual void finalize_windowing() override;

      void destroy() override;

      //virtual void windowing_main();

      virtual void windowing_post_quit() override;

      virtual text_editor_interface * get_text_editor_interface();
      

      virtual ::pointer<cursor>get_cursor(enum_cursor ecursor);
      virtual void set_cursor_set_from_matter(::object * pobjectContext, const ::file::path & pathFolder);

      
      //inline ::int_point get_cursor_position() { return m_pointCursor; }
      //virtual void set_cursor_position(const ::int_point & pointCursor);
      virtual ::windowing::display * display();

      ::acme::windowing::window * acme_windowing_window(const ::operating_system::window & operatingsystemwindow) override;
      ::acme::windowing::window * acme_windowing_window(const ::lparam & lparam) override;
      virtual ::windowing::window * windowing_window(const ::operating_system::window & operatingsystemwindow);
      virtual ::windowing::window * windowing_window(const ::lparam & lparam);

      
      ::particle * defer_initialize_host_window(const ::int_rectangle* lpcrect) override;

      virtual bool is_sandboxed();
      
      virtual ::acme::windowing::window * get_application_host_window() override;

      virtual ::windowing::window * get_desktop_window();

      virtual ::windowing::window * get_foreground_window();

      virtual ::windowing::window * get_active_window(::thread * pthread);

      virtual void clear_active_window(::thread * pthread, ::windowing::window * pwindow);

      virtual ::acme::windowing::window * get_keyboard_focus(::thread * pthread) override;

      virtual ::int_point try_absolute_mouse_position(::user::interaction* puserinteraction, const ::int_point& point);
      virtual ::acme::windowing::window * get_mouse_capture(::thread * pthread) override;
      virtual void set_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow);
      virtual bool has_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow);
      virtual bool is_mouse_captured(::thread * pthread, ::acme::windowing::window * pwindow);
      virtual void release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow);

       bool defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow) override;

      virtual void set_mouse_cursor2(::windowing::cursor * pcursor);

      //virtual void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr) override;

      void term1() override;

      void term2() override;

      //virtual ::acme::windowing::display * acme_display();

      virtual int_size get_window_minimum_size();

      void kick_idle() override;

      virtual void __wait_timer_or_event(class display * pdisplay);

      virtual void __hook_on_idle(class display * pdisplay);

      virtual bool message_loop_step();


      virtual void handle_just_hooks();
      virtual void defer_handle_just_hooks();
      virtual bool __hook_process_event(class display * pdisplay, void * phappening, void * cookie);



      virtual bool is_screen_visible(::e_display edisplay);

      virtual ::pointer<::windowing::cursor>load_default_cursor(enum_cursor ecursor);



      virtual ::windowing::cursor * get_cursor();
      virtual ::windowing::cursor * get_default_cursor();



      virtual ::pointer < ::windowing::window > new_message_window();

      
      ::pointer < ::acme::windowing::window > get_new_window()  override;
      

      virtual ::pointer < ::windowing::window > new_window();
      

      virtual void erase_window(::windowing::window * pwindow);

      bool route_message(::user::message * pusermessage);

      void on_idle(class display *pdisplay);

      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);

      virtual int_bool point_is_window_origin(::int_point ptHitTest, ::acme::windowing::window * pacmewindowingwindowExclude, int iMargin);

      //virtual void top_windows_by_z_order(::user::oswindow_array & a);

      virtual bool is_window(::acme::windowing::window * pacmewindowingwindow);

      virtual void load_cursor(::windowing::cursor * pcursor, ::file::path path, bool bSync, bool bCache = true);

      virtual void set(::message::key * pkey, const ::operating_system::window & operatingsystemwindow, ::windowing::window * pwindow, ::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam);
      virtual void set(::message::mouse * pmouse, const ::operating_system::window & operatingsystemwindow, ::windowing::window * pwindow, ::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam);

      virtual void initialize_keyboard(::windowing::keyboard * pkeyboard);

      virtual void lock_set_foreground_window(bool bLock = true);


      //virtual void windowing_send(const ::procedure & procedure);
      //virtual void windowing_post(const ::procedure & procedure);


      virtual void _main_loop();

      // MSG * for windows
      // XEvent * for X11 (Gnome)
      // xcb_event * for xcb (KDE)
      void _message_handler(void * p) override;


#if defined(LINUX) || defined(__BSD__)


      virtual void _libsn_start_context();

      virtual bool _xcb_process_event(void * p);

      virtual bool xcb_message_loop_step();


#endif


      virtual wstring _windows_calc_icon_window_class(::user::interaction* pinteraction, unsigned int dwDefaultStyle, const ::scoped_string & scopedstrMatter);
      virtual wstring _windows_get_user_interaction_window_class(::user::interaction* pinteraction);


      template < typename OBJECT_POINTER, typename OBJECT_METHOD, typename PAYLOAD_POINTER >
      void user_get_posted_payload_synchronously(OBJECT_POINTER preturning, OBJECT_METHOD returning_method, PAYLOAD_POINTER ppayload)
      {

         return ::matter::__get_posted_payload_synchronously(this, &particle::user_post, preturning, returning_method, ppayload);

      }


      //virtual void register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


#ifdef WINDOWS_DESKTOP


      virtual bool _visible_top_level_contains_name(const ::scoped_string & scopedstr) = 0;
      virtual bool _visible_top_level_contains_all_names(const ::string_array_base & stra) = 0;
      virtual bool _top_level_contains_name(const ::scoped_string & scopedstr) = 0;
      virtual string _get_window_text_timeout(::acme::windowing::window * pacmewindowingwindow, const class ::time& time = 1_s) = 0;


#endif
       
       
      virtual void os_menu_item_enable(void * pitem, bool bEnable);
      virtual void os_menu_item_check(void * pitem, bool bCheck);

      virtual void defer_create_main_menu(const string_array_base & straParent, const string_array_base & straMenu, const string_array_base & straId);

      virtual ::pointer < ::user::interaction > create_message_window(const ::scoped_string & scopedstrName, ::user::interaction_listener * plistener = nullptr);


      virtual void windowing_application_main_loop() override;

      virtual int system_metrics_get_cx_icon_spacing();
      virtual int system_metrics_get_cy_icon_spacing();
      virtual int system_metrics_get_cx_icon();
      virtual int system_metrics_get_cy_icon();
      virtual int system_metrics_get_cy_caption();


//      virtual ::pointer < ::graphics::graphics > create_graphics();


   };


} // namespace windowing



