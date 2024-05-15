//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#pragma once


#include "display_base.h"
//#include "event_listener.h"
#include "acme/operating_system/x11/_atom.h"


struct wl_display;


namespace wayland
{


   namespace nano
   {
      namespace user
      {
         class window;


         class CLASS_DECL_ACME display :
            virtual public ::wayland::nano::user::display_base
            //virtual public event_listener
         {
         public:


            bool                                      m_bUnhook;
            //::wl_display *                          m_pwldisplay;
            //pointer_array < event_listener >        m_eventlistenera;
            //pointer_array < nano_window_base >      m_windowa;
            //Window                                  m_windowActive;
            //map < enum_atom, Atom >                 m_atommap;

            //static display *                          g_pdisplay;


            display();
            ~display() override;


            void initialize(::particle * pparticle) override;


            virtual void set_wl_display(::wl_display * pwldisplay);


            bool is_branch_current() const override;


            ::wl_display * __get_wayland_display() override;


            //virtual Atom intern_atom(const char *pszAtomName, bool bCreate);
            //virtual Atom intern_atom(enum_atom eatom, bool bCreate);

            //virtual Atom _intern_atom_unlocked(const char *pszAtomName, bool bCreate);
            //virtual Atom _intern_atom_unlocked(enum_atom eatom, bool bCreate);

            //unsigned char * _get_string_property(Display *display, Window window, char *property_name);
            //unsigned long _get_long_property(Display *d, Window w, char *property_name);


            //virtual Window _get_active_window();


            //static Window window_from_name_search(Display *display, Window current, char const *needle, int iOffset = 0, int depth = 1);

            //Window window_from_name(char const *name, int iOffset, int depth = 1);


            bool message_loop_step() override;
            //void aaa_message_loop ();

            void init_task() override;

            void run() override;


            //      //void add_listener(event_listener * plistener);
            //      void add_window(nano_window_base * pwindow);
            //
            //      //void erase_listener(event_listener * plistener);
            //      void erase_window(nano_window_base * pwindow);

            //bool _on_event(XEvent * pevent) override;

            //virtual bool aaa_x11_event(XEvent * pevent);

            //virtual bool aaa_x11_posted();

            //void aaa_display_post(const ::procedure & procedure) override;
            //void aaa_display_send(const ::procedure & procedure);
            //bool aaa_display_posted_routine_step();

            ::size_i32 get_main_screen_size() override;


         };
      } //namespace user
   } // namespace nano


} // namespace x11



