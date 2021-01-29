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
//      hook_map             m_hookmap;

      ::mutex              m_mutexDisplay;
      ::mutex              m_mutexWindow;
//      ::mutex              m_mutexHook;


      windowing();
      virtual ~windowing();


      virtual ::e_status process_init() override;




      virtual bool sn_start_context();

      virtual HCURSOR load_default_cursor(e_cursor ecursor);

      virtual int_bool window_set_mouse_cursor(window * pwindow, HCURSOR hcursor);

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



