// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once

inline ::user::interaction_impl * __interaction_impl(::windowing::window * pwindow)
{

   if (::is_null(pwindow)) return nullptr;

   auto pimpl = pwindow->m_pimpl.m_p;

   if (::is_null(pimpl)) return nullptr;

   return pimpl;

}




namespace windowing
{


   class CLASS_DECL_AURA windowing :
      virtual public ::apex::department
   {
   public:


      ::point_i32                            m_pointCursor;

      display_map                            m_displaymap;

      ::mutex                                m_mutexDisplay;
      ::mutex                                m_mutexWindow;
      ::mutex                                m_mutexMonitor;


      bool                                   m_bSettingCursorMatter;
      __pointer(cursor_set)                  m_pcursorset;
      __composite(keyboard)          m_pkeyboard;



      __pointer(::windowing::cursor)         m_pcursor;
      __pointer(::windowing::cursor)         m_pcursorCursor;
      enum_cursor                            m_ecursorDefault;
      enum_cursor                            m_ecursor;

      bool                                   m_bDrawCursor;
      __reference(::user::user)              m_puser;


      windowing();
      virtual ~windowing();

      ::windowing::keyboard * keyboard();



      virtual ::e_status initialize_windowing(::user::user * puser);

      virtual void defer_term_ui();


      virtual void finalize_windowing();

      virtual void finalize();


      virtual ::e_status os_application_system_run();
      

      __pointer(cursor) get_cursor(enum_cursor ecursor);
      virtual ::e_status set_cursor_set_from_matter(const ::file::path & pathDir);

      
      virtual ::e_status set_cursor_position(const ::point_i32 & point);



      virtual ::windowing::window * window(oswindow oswindow);



      virtual ::windowing::window * get_desktop_window();

      virtual ::windowing::window * get_foreground_window();

      virtual ::windowing::window * get_active_window(::thread * pthread);

      virtual ::e_status clear_active_window(::thread * pthread);

      virtual ::windowing::window * get_keyboard_focus(::thread * pthread);

      virtual ::windowing::window * get_mouse_capture(::thread * pthread);

      virtual ::e_status release_mouse_capture();


      


      virtual result_pointer < ::windowing::icon > load_icon(const ::payload & payloadFile);


      virtual void term1();

      virtual void term2();

      virtual ::windowing::display * display();

      virtual size_i32 get_window_minimum_size();

      virtual void kick_idle();

      virtual void __wait_timer_or_event(class display * pdisplay);

      virtual void __hook_on_idle(class display * pdisplay);

      //virtual ::mutex * mutex();

      virtual ::e_status defer_initialize_x11();
      virtual void handle_just_hooks();
      virtual void defer_handle_just_hooks();
      //virtual int message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
      virtual bool __hook_process_event(class display * pdisplay, void * pevent, void * cookie);


      virtual bool sn_start_context();


      virtual __pointer(::windowing::cursor) load_default_cursor(enum_cursor ecursor);


      //virtual bool set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor);
      //virtual bool set_cursor(::user::interaction * pinteraction, enum_cursor ecursor);
      //virtual bool set_default_cursor(::user::interaction * pinteraction, enum_cursor ecursor);
      virtual ::windowing::cursor * get_cursor();
      virtual ::windowing::cursor * get_default_cursor();

      //virtual int_bool window_set_mouse_cursor(window * pwindow, ::draw2d::cursor * pcursor);

      //virtual bool set_window_icon(window * pwindow, const ::file::path & path);

      virtual int message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox);

      virtual int message_box_timeout(const char* pszMessage, const char* pszTitle, const ::duration & duration, const ::e_message_box & emessagebox);

      virtual class window * new_message_window(::user::interaction_impl * pimpl);

      virtual class window * new_window(::user::interaction_impl * pimpl);

      virtual ::e_status remove_window(::windowing::window * pwindow);

      //virtual ::e_status hook(class hook * phook);

      //virtual ::e_status unhook(class hook * phook);

      bool route_message(::user::message * pusermessage);

      void on_idle(class display *pdisplay);

      virtual void get_cursor_pos(POINT_I32 * ppoint);

      inline ::point_i32 get_cursor_pos() { ::point_i32 point; get_cursor_pos(&point); return point; }

      //virtual void enum_draw2d_fonts(::write_text::font_enum_item_array& itema);

      virtual int_bool point_is_window_origin(POINT_I32 ptHitTest, oswindow oswindowExclude, int iMargin);

      //virtual void top_windows_by_z_order(::user::oswindow_array & a);

      virtual bool is_window(oswindow oswindow);

      virtual ::e_status load_cursor(::windowing::cursor * pcursor, ::file::path path, bool bSync, bool bCache = true);

      virtual void set(::message::key * pkey, oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam);
      virtual void set(::message::mouse * pmouse, oswindow oswindow, ::windowing::window * pwindow, const ::id & id, wparam wparam, ::lparam lparam);

      virtual void initialize_keyboard(::windowing::keyboard * pkeyboard);

      virtual ::e_status lock_set_foreground_window(bool bLock = true);


      virtual ::e_status user_sync(const ::duration & duration, const ::promise::routine & routine);
      virtual ::e_status user_fork(const ::promise::routine & routine);


   };


} // namespace windowing



