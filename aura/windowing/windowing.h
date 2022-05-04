// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


inline ::user::interaction_impl * __interaction_impl(::windowing::window * pwindow)
{

   if (::is_null(pwindow)) return nullptr;

   auto pimpl = pwindow->m_puserinteractionimpl.m_p;

   if (::is_null(pimpl)) return nullptr;

   return pimpl;

}


namespace windowing
{


   class CLASS_DECL_AURA windowing :
      virtual public ::acme::department
   {
   public:


      void *                                    m_pWindowing;
      void *                                    m_pWindowing2;

      ::point_i32                               m_pointCursor;

      display_map                               m_displaymap;

      ::mutex                                   m_mutexDisplay;
      ::mutex                                   m_mutexWindow;
      ::mutex                                   m_mutexMonitor;


      bool                                      m_bSettingCursorMatter;
      __pointer(::windowing::cursor_manager)    m_pcursormanager;
      __composite(::windowing::keyboard)        m_pkeyboard;



      __pointer(::windowing::cursor)            m_pcursor;
      __pointer(::windowing::cursor)            m_pcursorCursor;
      enum_cursor                               m_ecursorDefault;
      enum_cursor                               m_ecursor;

      bool                                      m_bDrawCursor;
      __reference(::user::user)                 m_puser;


      windowing();
      ~windowing() override;


      ::windowing::keyboard * keyboard();


      bool is_branch_current() const override;


      inline ::aura::application* get_app() const;
      inline ::aura::session* get_session() const;
      inline ::aura::system* get_system() const;


      virtual void initialize_windowing(::user::user * puser);

      virtual void defer_term_ui();


      virtual void finalize_windowing();

      //virtual void destroy() override;

      void destroy() override;


      //virtual void start();

      virtual void windowing_main();

      virtual void windowing_post_quit();


      virtual text_editor_interface * get_text_editor_interface();
      

      __pointer(cursor) get_cursor(enum_cursor ecursor);
      virtual void set_cursor_set_from_matter(::object * pobjectContext, const ::file::path & pathDir);

      
      virtual void set_cursor_position(const ::point_i32 & point);



      virtual ::windowing::window * window(oswindow oswindow);

      
      
      virtual ::windowing::window * get_application_host_window();

      virtual ::windowing::window * get_desktop_window();

      virtual ::windowing::window * get_foreground_window();

      virtual ::windowing::window * get_active_window(::thread * pthread);

      virtual void clear_active_window(::thread * pthread, ::windowing::window * pwindow);

      virtual ::windowing::window * get_keyboard_focus(::thread * pthread);

      virtual ::windowing::window * get_mouse_capture(::thread * pthread);

      virtual void release_mouse_capture();

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



      virtual __pointer(::windowing::cursor) load_default_cursor(enum_cursor ecursor);



      virtual ::windowing::cursor * get_cursor();
      virtual ::windowing::cursor * get_default_cursor();



      virtual class window * new_message_window(::user::interaction_impl * pimpl);

      virtual class window * new_window(::user::interaction_impl * pimpl);

      virtual void erase_window(::windowing::window * pwindow);

      bool route_message(::user::message * pusermessage);

      void on_idle(class display *pdisplay);

      virtual void get_cursor_position(POINT_I32 * ppoint);

      inline ::point_i32 get_cursor_position() { ::point_i32 point; get_cursor_position(&point); return point; }

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


#endif


      virtual wstring _windows_calc_icon_window_class(::user::interaction* pinteraction, u32 dwDefaultStyle, const ::string & pszMatter);
      virtual wstring _windows_get_user_interaction_window_class(::user::interaction* pinteraction);


      template < typename OBJECT_POINTER, typename OBJECT_METHOD, typename PAYLOAD_POINTER >
      void windowing_send(OBJECT_POINTER pobject, OBJECT_METHOD object_method, PAYLOAD_POINTER ppayload)
      {

         return ::material_object::__send_payload(this, &windowing::windowing_post, pobject, object_method, ppayload);

      }


      virtual void register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


#ifdef WINDOWS_DESKTOP


      virtual bool _visible_top_level_contains_name(string str) = 0;
      virtual bool _visible_top_level_contains_all_names(const ::string_array & stra) = 0;
      virtual bool _top_level_contains_name(string str) = 0;
      virtual string _get_window_text_timeout(oswindow oswindow, const ::duration& duration = 1_s) = 0;


#endif


   };


} // namespace windowing



