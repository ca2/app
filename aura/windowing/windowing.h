// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA windowing :
      virtual public ::apex::department
   {
   public:


      display_map          m_displaymap;
      window_map           m_windowmap;
      monitor_map          m_monitormap;

      ::mutex              m_mutexDisplay;
      ::mutex              m_mutexWindow;
      ::mutex              m_mutexMonitor;


      windowing();
      virtual ~windowing();


      virtual ::e_status process_init() override;


      virtual display * get_display();

      virtual void kick_idle();

      virtual void __wait_timer_or_event(display * pdisplay);

      virtual void __hook_on_idle(display * pdisplay);

      virtual ::mutex * mutex();

      virtual ::e_status defer_initialize_x11();
      virtual void handle_just_hooks();
      virtual void defer_handle_just_hooks();
      virtual int message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
      virtual bool __hook_process_event(display * pdisplay, void * pevent, void * cookie);


      virtual bool sn_start_context();

      virtual __pointer(::draw2d::cursor) load_default_cursor(e_cursor ecursor);

      virtual int_bool window_set_mouse_cursor(window * pwindow, ::draw2d::cursor * pcursor);

      virtual bool set_window_icon(window * pwindow, const ::file::path & path);

      virtual int message_box(const char* pszMessage, const char* pszTitle, const ::e_message_box & emessagebox);

      virtual int message_box_timeout(const char* pszMessage, const char* pszTitle, const ::duration & duration, const ::e_message_box & emessagebox);

      virtual window * new_message_window(::user::interaction_impl * pimpl);

      virtual window * new_window(::user::interaction_impl * pimpl);

      virtual ::e_status remove_window(::user::interaction_impl * pimpl);

      //virtual ::e_status hook(class hook * phook);

      //virtual ::e_status unhook(class hook * phook);

      bool route_message(::message::base * pmessagebase);

      void on_idle(display *pdisplay);


   };


} // namespace windowing



