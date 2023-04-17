// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "acme/platform/department.h"
#include "acme/primitive/collection/int_map.h"
#include "acme/primitive/geometry2d/_geometry2d.h"


CLASS_DECL_AURA ::user::interaction_impl * __interaction_impl(::windowing::window * pwindow);


namespace windowing
{


   using display_map = iptr_map < ::pointer<display > >;


   class CLASS_DECL_AURA windowing :
      virtual public ::acme::department
   {
   public:


      ::sandbox_windowing::windowing *          m_psandboxwindowing;
      void *                                    m_pWindowing4;

      ::point_i32                               m_pointCursor;

      display_map                               m_displaymap;

      ::pointer < ::mutex >                                   m_pmutexDisplay;
      ::pointer < ::mutex >                                   m_pmutexWindow;
      ::pointer < ::mutex >                                   m_pmutexMonitor;


      bool                                      m_bSettingCursorMatter;
      ::pointer<::windowing::cursor_manager>   m_pcursormanager;
      ::pointer<::windowing::keyboard>       m_pkeyboard;



      ::pointer<::windowing::cursor>           m_pcursor;
      ::pointer<::windowing::cursor>           m_pcursorCursor;
      enum_cursor                               m_ecursorDefault;
      enum_cursor                               m_ecursor;

      bool                                      m_bDrawCursor;
      ::pointer<::user::user>                m_puser;
      


      windowing();
      ~windowing() override;


      ::windowing::keyboard * keyboard();


      bool is_branch_current() const override;
      
      


      ::aura::application* get_app();
      ::aura::session* get_session();
      //::aura::system* acmesystem();


      virtual void _initialize_windowing();


      virtual void initialize_windowing(::user::user * puser);

      virtual void defer_term_ui();


      virtual void finalize_windowing();

      void destroy() override;

      virtual void windowing_main();

      virtual void windowing_post_quit();

      virtual text_editor_interface * get_text_editor_interface();
      

      virtual ::pointer<cursor>get_cursor(enum_cursor ecursor);
      virtual void set_cursor_set_from_matter(::object * pobjectContext, const ::file::path & pathDir);

      
      inline ::point_i32 get_cursor_position() { return m_pointCursor; }
      virtual void set_cursor_position(const ::point_i32 & pointCursor);


      virtual ::windowing::window * window(oswindow oswindow);

      virtual void defer_initialize_host_window(const RECTANGLE_I32* lpcrect);

      virtual bool is_sandboxed();
      
      virtual ::windowing::window * get_application_host_window();

      virtual ::windowing::window * get_desktop_window();

      virtual ::windowing::window * get_foreground_window();

      virtual ::windowing::window * get_active_window(::thread * pthread);

      virtual void clear_active_window(::thread * pthread, ::windowing::window * pwindow);

      virtual ::windowing::window * get_keyboard_focus(::thread * pthread);

      virtual ::windowing::window * get_mouse_capture(::thread * pthread);

      virtual void release_mouse_capture();

      virtual void clear_keyboard_focus(::user::element * pelementGainingFocusIfAny = nullptr);

      void term1() override;

      void term2() override;

      virtual ::windowing::display * display();

      virtual size_i32 get_window_minimum_size();

      void kick_idle() override;

      virtual void __wait_timer_or_event(class display * pdisplay);

      virtual void __hook_on_idle(class display * pdisplay);

      virtual bool message_loop_step();


      virtual void handle_just_hooks();
      virtual void defer_handle_just_hooks();
      virtual bool __hook_process_event(class display * pdisplay, void * pevent, void * cookie);



      virtual ::pointer<::windowing::cursor>load_default_cursor(enum_cursor ecursor);



      virtual ::windowing::cursor * get_cursor();
      virtual ::windowing::cursor * get_default_cursor();



      virtual class window * new_message_window(::user::interaction_impl * pimpl);

      virtual class window * new_window(::user::interaction_impl * pimpl);

      virtual void erase_window(::windowing::window * pwindow);

      bool route_message(::user::message * pusermessage);

      void on_idle(class display *pdisplay);

      //virtual void enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema);

      virtual int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin);

      //virtual void top_windows_by_z_order(::user::oswindow_array & a);

      virtual bool is_window(oswindow oswindow);

      virtual void load_cursor(::windowing::cursor * pcursor, ::file::path path, bool bSync, bool bCache = true);

      virtual void set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam);
      virtual void set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam);

      virtual void initialize_keyboard(::windowing::keyboard * pkeyboard);

      virtual void lock_set_foreground_window(bool bLock = true);


      virtual void windowing_send(const ::procedure & procedure);
      virtual void windowing_post(const ::procedure & procedure);


      virtual void _main_loop();

      // MSG * for windows
      // XEvent * for X11 (Gnome)
      // xcb_event * for xcb (KDE)
      virtual void _message_handler(void * p);


#if defined(LINUX) || defined(FREEBSD)


      virtual void _libsn_start_context();

      virtual bool _xcb_process_event(void * p);

      virtual bool xcb_message_loop_step();


#endif


      virtual wstring _windows_calc_icon_window_class(::user::interaction* pinteraction, u32 dwDefaultStyle, const ::string & pszMatter);
      virtual wstring _windows_get_user_interaction_window_class(::user::interaction* pinteraction);


      template < typename OBJECT_POINTER, typename OBJECT_METHOD, typename PAYLOAD_POINTER >
      void windowing_get_posted_payload_synchronously(OBJECT_POINTER preturning, OBJECT_METHOD returning_method, PAYLOAD_POINTER ppayload)
      {

         return ::matter::__get_posted_payload_synchronously(this, &windowing::windowing_post, preturning, returning_method, ppayload);

      }


      virtual void register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


#ifdef WINDOWS_DESKTOP


      virtual bool _visible_top_level_contains_name(string str) = 0;
      virtual bool _visible_top_level_contains_all_names(const ::string_array & stra) = 0;
      virtual bool _top_level_contains_name(string str) = 0;
      virtual string _get_window_text_timeout(oswindow oswindow, const class ::time& time = 1_s) = 0;


#endif
       
       
      virtual void os_menu_item_enable(void * pitem, bool bEnable);
      virtual void os_menu_item_check(void * pitem, bool bCheck);

      virtual void defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId);

      virtual ::e_status is_keyboard_hook_enabled(::user::interaction * puserinteractionEnablePrompt);

      virtual void install_keyboard_hook(::matter * pmatterListener);
      virtual void uninstall_keyboard_hook(::matter * pmatterListener);

      virtual ::e_status is_mouse_hook_enabled(::user::interaction * puserinteractionEnablePrompt);

      virtual void install_mouse_hook(::matter * pmatterListener);
      virtual void uninstall_mouse_hook(::matter * pmatterListener);

      virtual ::user::interaction * create_message_window(const ::string & pszName, ::user::interaction_listener * plistener = nullptr);


   };


} // namespace windowing



