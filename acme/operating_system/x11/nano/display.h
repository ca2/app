//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "acme/user/nano/display.h"
#include "event_listener.h"


namespace x11
{


   class nano_window;


   class display :
      virtual public ::nano::display,
      virtual public event_listener
   {
   public:


      bool                                   m_bUnhook;
      Display   *                            m_pdisplay;
      __pointer_array(event_listener)        m_eventlistenera;
      __pointer_array(nano_window)           m_windowa;
      Window                                 m_windowActive;
      Atom                                   m_atoma[e_atom_count];


      static display *                       g_p;


      display();
      ~display() override;


      bool is_branch_current() const override;


      virtual Atom intern_atom(const char *pszAtomName, bool bCreate);
      virtual Atom intern_atom(enum_atom eatom, bool bCreate);

      unsigned char * _get_string_property(Display *display, Window window, char *property_name);
      unsigned long _get_long_property(Display *d, Window w, char *property_name);


      virtual Window _get_active_window();




      static display * get(::object * pobject, bool bBranch = true, Display * pdisplay = nullptr);

      bool message_loop_step();
      void message_loop();

      void init_task() override;

      void run() override;


      void add_listener(event_listener * plistener);
      void add_window(nano_window * pwindow);

      void erase_listener(event_listener * plistener);
      void erase_window(nano_window * pwindow);

      bool _on_event(XEvent * pevent) override;

      virtual bool x11_event(XEvent * pevent);

      virtual bool x11_posted();

      //void display_post(const ::procedure & function) override;
      //void display_send(const ::procedure & function);
      //bool display_posted_routine_step();


   };


} // namespace x11



