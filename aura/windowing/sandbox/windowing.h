// Created by camilo on 2022-06-02 12:41 PM <3ThomasBorregaardSorensen!!
#pragma once


namespace sandbox_windowing
{ 


   class window;


   // created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
   // recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
   // Adapted by Camilo for android 2022-01-05 04:34 <3TBS (Thomas likes number 5), Mummi and bilbo!!
   // Adapted by Camilo for cached/simulation of mouse-capture/keyboard-focus state information and
   // a few other things present in sandboxed applications (mobile/tablet/small devices)
   //     - 2022-06-02 12:44 PM <3TBS (Thomas likes number 5), Mummi and bilbo!!


   class CLASS_DECL_AURA windowing :
      virtual public ::windowing::windowing
   {
   public:


      __pointer(::sandbox_windowing::window)          m_pwindowKeyboardFocus;
      __pointer(::sandbox_windowing::window)          m_pwindowMouseCapture;
      __pointer(::sandbox_windowing::window)          m_pwindowActive;


      __pointer(host_interaction)                     m_phostinteraction;

      __pointer(::windowing::window)                  m_pwindowApplicationHost;

      itask_t                                         m_itask;

      ::procedure_list                                m_procedurelist;


      windowing();
      ~windowing() override;


      void initialize(::object* pobject) override;


      bool is_branch_current() const override;


      virtual void initialize_windowing();

      virtual void terminate_windowing();

      void defer_initialize_host_window(const RECTANGLE_I32* lpcrect) override;

      ::windowing::window* get_application_host_window() override;


      //::windowing::display* display() override;


      virtual __pointer(::windowing::cursor) load_default_cursor(enum_cursor ecursor) override;

      ::windowing::window* new_window(::user::interaction_impl* pimpl) override;

      void erase_window(::windowing::window* pwindow) override;

      ::windowing::window* window(oswindow oswindow) override;

      virtual void _message_handler(void* p) override;

      ::windowing::window* get_keyboard_focus(::thread* pthread) override;

      ::windowing::window* get_mouse_capture(::thread* pthread) override;


      void release_mouse_capture() override;


      void clear_keyboard_focus(::windowing::window* pwindowGainingFocusIfAny = nullptr) override;


      void windowing_post(const ::procedure& procedure) override;

      virtual bool x11_runnable_step();


      //::windowing::text_editor_interface* get_text_editor_interface() override;


      using ::windowing::windowing::get_cursor;


      __pointer(::windowing::cursor) get_cursor(enum_cursor ecursor) override;


   };


} // namespace sandbox_windowing
