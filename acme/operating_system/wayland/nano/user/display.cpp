
//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"
//#include "acme/primitive/geometry2d/rectangle.h"
#include "acme/nano/user/window.h"


#include "acme/operating_system/x11/_.h"


#define MAXSTR 1000


void x11_init_threads();
//void * x11_get_display();


void set_main_user_thread();


namespace wayland
{


   //display * display::g_p = nullptr;

namespace nano
{
   namespace user
   {
      display::display()
      {

         m_pwldisplay = nullptr;

         m_bUnhook = false;

         //      if(!g_p)
         //      {
         //
         //         g_p = this;
         //
         //      }

         defer_create_synchronization();

         m_bOwnDisplay = false;


      }


      display::~display()
      {


         if(m_bOwnDisplay && m_pwldisplay != nullptr)
         {

            wl_display_disconnect(m_pwldisplay);

            m_pwldisplay = nullptr;

            m_bOwnDisplay = false;

            printf("disconnected from display\n");

         }

      }


      void display::initialize(::particle * pparticle)
      {

         ::nano::user::display::initialize(pparticle);

         ::wayland::nano::user::display_base::initialize(pparticle);

      }


      //   Atom display::intern_atom(const char *pszAtomName, bool bCreate)
      //   {
      //
      //      return _intern_atom_unlocked(pszAtomName, bCreate);
      //
      ////      if (m_pdisplay == nullptr)
      ////      {
      ////
      ////         return 0;
      ////
      ////      }
      ////
      ////      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
      ////
      ////      if (atom == None)
      ////      {
      ////
      ////         windowing_output_debug_string("ERROR: cannot find atom for " + string(pszAtomName) + "\n");
      ////
      ////         return None;
      ////
      ////      }
      ////
      ////      return atom;
      //
      //   }
      //
      //
      //   Atom display::intern_atom(enum_atom eatom, bool bCreate)
      //   {
      //
      //      return _intern_atom_unlocked(eatom, bCreate);
      //
      ////      if (eatom < 0 || eatom >= e_atom_count)
      ////      {
      ////
      ////         return None;
      ////
      ////      }
      ////
      ////      Atom atom = m_atommap[eatom];
      ////
      ////      if (atom == None)
      ////      {
      ////
      ////         atom = intern_atom(atom_name(eatom), bCreate);
      ////
      ////         m_atommap[eatom] = atom;
      ////
      ////      }
      ////
      ////      return atom;
      //
      //   }
      //
      //
      //
      //   Atom display::_intern_atom_unlocked(const char *pszAtomName, bool bCreate)
      //   {
      //
      //      if (m_pdisplay == nullptr)
      //      {
      //
      //         return 0;
      //
      //      }
      //
      //      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
      //
      //      if (atom == None)
      //      {
      //
      //         windowing_output_debug_string("ERROR: cannot find atom for " + string(pszAtomName) + "\n");
      //
      //         return None;
      //
      //      }
      //
      //      return atom;
      //
      //   }
      //
      //
      //   Atom display::_intern_atom_unlocked(enum_atom eatom, bool bCreate)
      //   {
      //
      //      if (eatom < 0 || eatom >= e_atom_count)
      //      {
      //
      //         return None;
      //
      //      }
      //
      //      Atom atom = m_atommap[eatom];
      //
      //      if (atom == None)
      //      {
      //
      //         atom = _intern_atom_unlocked(atom_name(eatom), bCreate);
      //
      //         m_atommap[eatom] = atom;
      //
      //      }
      //
      //      return atom;
      //
      //   }
      //
      //
      //   unsigned char* display::_get_string_property(Display * display, Window window, char* property_name)
      //   {
      //
      //      unsigned char * prop;
      //      Atom actual_type, filter_atom;
      //      int actual_format, status;
      //      unsigned long nitems, bytes_after;
      //
      //      filter_atom = XInternAtom(display, property_name, True);
      //
      //      status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
      //                                  &actual_type, &actual_format, &nitems, &bytes_after, &prop);
      //
      //      x11_check_status(status, window);
      //
      //      return prop;
      //
      //   }
      //
      //
      //   unsigned long display::_get_long_property(Display *d, Window w, char *property_name)
      //   {
      //
      //      unsigned char *prop = _get_string_property(d, w, property_name);
      //
      //      unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);
      //
      //      XFree(prop);
      //
      //      return long_property;
      //
      //   }
      //
      //
      //   Window display::_get_active_window()
      //   {
      //
      //      int screen = XDefaultScreen(m_pdisplay);
      //
      //      Window windowRoot = RootWindow(m_pdisplay, screen);
      //
      //      Window window = _get_long_property(m_pdisplay, windowRoot, (char *) "_NET_ACTIVE_WINDOW");
      //
      //      return window;
      //
      //   }


      //   Window display::window_from_name_search(Display *display, Window current, char const *needle, int iOffset, int depth)
      //   {
      //
      //      Window window, root, parent, *children;
      //
      //      unsigned children_count;
      //
      //      char *name = NULL;
      //
      //      window = 0;
      //
      //      /* If it does not: check all subwindows recursively. */
      //      if(0 != XQueryTree(display, current, &root, &parent, &children, &children_count))
      //      {
      //
      //         unsigned i;
      //
      //         for(i = 0; i < children_count; ++i)
      //         {
      //
      //            /* Check if this window has the name we seek */
      //            if(XFetchName(display,  children[i], &name) > 0)
      //            {
      //
      //               int r = ansi_cmp(needle, name);
      //
      //               XFree(name);
      //
      //               if(r == 0)
      //               {
      //
      //                  window = children[i+iOffset];
      //
      //                  break;
      //
      //               }
      //
      //            }
      //
      //            if(depth > 1)
      //            {
      //
      //               Window win = window_from_name_search(display, children[i], needle, depth - 1);
      //
      //               if (win != 0)
      //               {
      //
      //                  window = win;
      //
      //                  break;
      //
      //               }
      //
      //            }
      //
      //         }
      //
      //         XFree(children);
      //
      //      }
      //
      //      return window;
      //
      //   }


      //   Window display::window_from_name(char const *name, int iOffset, int depth)
      //   {
      //
      ////      auto display = m_pdisplay;
      ////
      ////      auto windowRoot = XDefaultRootWindow(display);
      ////
      ////      auto window = window_from_name_search(display, windowRoot, name, iOffset, depth);
      //
      //
      //
      ////      return window;
      //
      //   }



      ::wl_display * display::__get_wayland_display()
      {

         if(m_pwldisplay)
         {

            return m_pwldisplay;

         }

         m_pwldisplay = wl_display_connect(NULL);
         if (m_pwldisplay == NULL)
         {
            error() << "Can't connect to display";
            throw ::exception(error_failed);
         }
         information() << "connected to display\n";
         m_bOwnDisplay = true;
         //wl_display_disconnect(display);
         //printf("disconnected from display\n");

         return m_pwldisplay;

      }


      //   display * display::get(::particle * pparticle, bool bBranch, ::wl_display * pwldisplay)
      //   {
      //
      //      critical_section_lock lock(this->platform()->globals_critical_section());
      //
      //      if (g_p == nullptr)
      //      {
      //
      //         auto p = __new< display >();
      //
      //         p->initialize(pparticle);
      //
      //         //p->add_listener(p);
      //
      //         p->m_pwldisplay = pwldisplay;
      //
      //         if(bBranch)
      //         {
      //
      //            p->branch_synchronously();
      //
      //         }
      //         else
      //         {
      //
      //            p->init_task();
      //
      //         }
      //
      //      }
      //
      //      return g_p;
      //
      //   }


      //   void display::add_listener(event_listener * plistener)
      //   {
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      m_eventlistenera.add(plistener);
      //
      //   }
      //
      //
      //   void display::add_window(nano::user::window * pwindow)
      //   {
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      m_windowa.add(pwindow);
      //
      //   }

      //
      //   void display::erase_listener(event_listener * plistener)
      //   {
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      m_eventlistenera.erase(plistener);
      //
      //   }
      //
      //
      //   void display::erase_window(nano::user::window * pwindow)
      //   {
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      m_windowa.erase(pwindow);
      //
      //   }

      //
      bool display::message_loop_step()
      {

         return ::wayland::nano::user::display_base::message_loop_step();

      }
      //
      //      if (!XPending(m_pdisplay))
      //      {
      //
      //         return false;
      //
      //      }
      //
      //      XEvent event{};
      //
      //      XNextEvent(m_pdisplay, &event);
      //
      //      x11_event(&event);
      //
      //      return true;
      //
      //   }

      //
      //   bool display::aa_x11_posted()
      //   {
      //
      //      return aaa_display_posted_routine_step();
      //
      //   }
      //
      //
      //   bool display::x11_event(XEvent * pevent)
      //   {
      //
      //      bool bHandled = false;
      //
      //      ::collection::index i = 0;
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      for (; i < m_eventlistenera.get_count(); i++)
      //      {
      //
      //         auto plistener = m_eventlistenera[i];
      //
      //         synchronouslock.unlock();
      //
      //         if(i == 0)
      //         {
      //
      //            if (plistener->_on_event(pevent))
      //            {
      //
      //               bHandled = true;
      //
      //               break;
      //
      //            }
      //
      //         }
      //         else
      //         {
      //
      //            if (plistener->_on_event(pevent))
      //            {
      //
      //               bHandled = true;
      //
      //               break;
      //
      //            }
      //
      //         }
      //
      //         synchronouslock.lock();
      //
      //      }
      //
      //      return bHandled;
      //
      //   }
      //
      //
      //   void display::aaa_message_loop()
      //   {
      //
      //      bool bHandled1;
      //
      //      bool bHandled2;
      //
      //      while (::task_get_run())
      //      {
      //
      //         if(m_bUnhook)
      //         {
      //
      //            break;
      //
      //         }
      //
      //         bHandled1 = false;
      //
      //         bHandled2 = false;
      //
      //         while(aaa_message_loop_step())
      //         {
      //
      //            bHandled1 = true;
      //
      //         }
      //
      //         if(!bHandled1)
      //         {
      //
      //            bHandled2 = aaa_x11_posted();
      //
      //         }
      //
      //         if(!bHandled1 && !bHandled2)
      //         {
      //
      //            preempt(5_ms);
      //
      //         }
      //
      //      }
      //
      //      information() << "Finished display::message_loop for nano::display";
      //
      //   }
      //

      void display::init_task()
      {


         display_base::init_task();

         //      if(system()->m_ewindowing == e_windowing_none)
         //      {
         //
         //         //set_main_user_thread();
         //
         //         system()->m_ewindowing = e_windowing_x11;
         //
         //      }
         ////
         ////      XInitxThreads();
         ////
         ////      if(!m_pdisplay)
         ////      {
         ////
         ////         set_X11_Display(XOpenxDisplay(nullptr));
         ////
         ////      }

      }


      void display::set_wl_display(::wl_display * pwldisplay)
      {

         m_pwldisplay = pwldisplay;

         if (!m_pwldisplay)
         {

            throw ::exception(error_null_pointer);

         }

         ::rectangle_i32 rectangleMainScreen;

         //      auto pscreen = DefaultScreenOfDisplay(m_pdisplay);
         //
         //      int wScreen = WidthOfScreen(pscreen);
         //      int hScreen = HeightOfScreen(pscreen);

         //printf("::x11::display::init_task pscreen=%" PRIxPTR "\n", pscreen);
         //printf("::x11::display::init_task (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

         //rectangleMainScreen.left() = 0;
         //rectangleMainScreen.top() = 0;
         //rectangleMainScreen.right() = wScreen;
         //rectangleMainScreen.bottom() = hScreen;

         //operating_system_set_main_screen_rectangle(rectangleMainScreen);

      }


      bool display::is_branch_current() const
      {

         if(!m_bUnhook && ::object::is_branch_current())
         {

            return true;

         }

         if(m_bUnhook && ::is_main_thread())
         {

            return true;

         }

         return false;

      }


      void display::run()
      {

         display_base::run();

      }


      //   bool display::_on_event(XEvent * pevent)
      //   {
      //
      //      if (pevent->xany.window == DefaultRootWindow(m_pdisplay))
      //      {
      //
      //         if(pevent->xany.type == PropertyNotify)
      //         {
      //
      //            Atom atom = XInternAtom(m_pdisplay, "_NET_ACTIVE_WINDOW", False);
      //
      //            if (atom == pevent->xproperty.atom)
      //            {
      //
      //               auto windowActive = m_windowActive;
      //
      //               for(auto & pwindow : m_windowa)
      //               {
      //
      //                  bool bNcActive = windowActive == pwindow->m_window;
      //
      //                  if (is_different(bNcActive, pwindow->m_pinterface->m_bNcActive))
      //                  {
      //
      //                     pwindow->m_pinterface->m_bNcActive = bNcActive;
      //
      //                     pwindow->redraw();
      //
      //                  }
      //
      //               }
      //
      //               m_windowActive = windowActive;
      //
      //            }
      //
      //         }
      //
      //      }
      //
      //      return false;
      //
      //   }


      ::size_i32 display::get_main_screen_size()
      {

         //      auto snum = DefaultScreen(m_pdisplay);
         //
         //      auto width = DisplayWidth(m_pdisplay, snum);
         //
         //      auto height = DisplayHeight(m_pdisplay, snum);
         //
         //      return { width, height };

         if(m_sizeaMonitor.is_empty())
         {

            return {};

         }

         return m_sizeaMonitor[0];

      }



      void * get_display(::particle * pparticle)
      {

         auto pdisplay = ::wayland::nano::user::display::get(pparticle, false);

         return pdisplay->m_pwldisplay;

      }


      void set_display(::wayland::nano::user::display_base * pdisplaybase)
      {

         ::wayland::nano::user::display_base::s_pdisplaybase = pdisplaybase;

      }


      void initialize_display(::particle * pparticle, void * pwaylanddisplay)
      {

         ::wayland::nano::user::display::get(pparticle, false, (::wl_display *) pwaylanddisplay);

      }


      void * initialize_display(::particle * pparticle)
      {

         auto pdisplay = ::wayland::nano::user::display::get(pparticle, false);

         return pdisplay->m_pwldisplay;

      }


      void process_messages()
      {

         if(::wayland::nano::user::display_base::s_pdisplaybase)
         {

            ::wayland::nano::user::display_base::s_pdisplaybase->message_loop_step();

         }

      }




   }// namespace user
} // namespace nano


} // namespace wayland

