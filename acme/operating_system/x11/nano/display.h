//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSørensen!!
//
#pragma once


namespace x11
{


   class nano_window;


   class display :
      virtual public ::object,
      virtual public event_listener
   {
   public:


      bool                                   m_bUnhook;
      Display   *                            m_pdisplay;
      __pointer_array(event_listener)        m_eventlistenera;
      __pointer_array(nano_window)           m_windowa;
      Window                                 m_windowActive;
      ::routine_array                        m_routineaPost;


      static display *                       g_p;


      display();
      ~display() override;


      //void wait_timer_or_event();

      static display * get(::object * pobject, bool bBranch = true);

      bool message_loop_step();
      void message_loop();

      void init_task() override;

      void run() override;


      bool is_branch_current() const override;


      void add_listener(event_listener * plistener);
      void add_window(nano_window * pwindow);

      void erase_listener(event_listener * plistener);
      void erase_window(nano_window * pwindow);

      bool _on_event(XEvent * pevent) override;

      virtual bool x11_event(XEvent * pevent);

      virtual bool x11_posted();

      void display_post(const ::routine & routine);
      void display_send(const ::routine & routine);
      bool display_posted_routine_step();


   };


} // namespace x11



