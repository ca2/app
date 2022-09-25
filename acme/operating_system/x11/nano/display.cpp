
//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


#define MAXSTR 1000


void x11_init_threads();
void * x11_get_display();


void set_main_user_thread();


namespace x11
{


   display * display::g_p = nullptr;


   display::display()
   {

      m_pdisplay = nullptr;

      m_bUnhook = false;

      if(!g_p)
      {

         g_p = this;

      }

      defer_create_mutex();


   }


   display::~display()
   {


   }


   Atom display::intern_atom(const char *pszAtomName, bool bCreate)
   {

      if (m_pdisplay == nullptr)
      {

         return 0;

      }

      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);

      if (atom == None)
      {

         windowing_output_debug_string("ERROR: cannot find atom for " + string(pszAtomName) + "\n");

         return None;

      }

      return atom;

   }


   Atom display::intern_atom(enum_atom eatom, bool bCreate)
   {

      if (eatom < 0 || eatom >= e_atom_count)
      {

         return None;

      }

      Atom atom = m_atoma[eatom];

      if (atom == None)
      {

         atom = intern_atom(atom_name(eatom), bCreate);

         m_atoma[eatom] = atom;

      }

      return atom;

   }



   unsigned char* display::_get_string_property(Display * display, Window window, char* property_name)
   {

      unsigned char * prop;
      Atom actual_type, filter_atom;
      int actual_format, status;
      unsigned long nitems, bytes_after;

      filter_atom = XInternAtom(display, property_name, True);

      status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
                                  &actual_type, &actual_format, &nitems, &bytes_after, &prop);

      x11_check_status(status, window);

      return prop;

   }


   unsigned long display::_get_long_property(Display *d, Window w, char *property_name)
   {

      unsigned char *prop = _get_string_property(d, w, property_name);

      unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);

      XFree(prop);

      return long_property;

   }


   Window display::_get_active_window()
   {

      int screen = XDefaultScreen(m_pdisplay);

      Window windowRoot = RootWindow(m_pdisplay, screen);

      Window window = _get_long_property(m_pdisplay, windowRoot, (char *) "_NET_ACTIVE_WINDOW");

      return window;

   }


   Window display::window_from_name_search(Display *display, Window current, char const *needle, int iOffset, int depth)
   {

      Window window, root, parent, *children;

      unsigned children_count;

      char *name = NULL;

      window = 0;

      /* If it does not: check all subwindows recursively. */
      if(0 != XQueryTree(display, current, &root, &parent, &children, &children_count))
      {

         unsigned i;

         for(i = 0; i < children_count; ++i)
         {

            /* Check if this window has the name we seek */
            if(XFetchName(display,  children[i], &name) > 0)
            {

               int r = strcmp(needle, name);

               XFree(name);

               if(r == 0)
               {

                  window = children[i+iOffset];

                  break;

               }

            }

            if(depth > 1)
            {

               Window win = window_from_name_search(display, children[i], needle, depth - 1);

               if (win != 0)
               {

                  window = win;

                  break;

               }

            }

         }

         XFree(children);

      }
      
      return window;
      
   }
   

   Window display::window_from_name(char const *name, int iOffset, int depth)
   {
      
      auto display = m_pdisplay;
      
      auto windowRoot = XDefaultRootWindow(display);
      
      auto window = window_from_name_search(display, windowRoot, name, iOffset, depth);
      
      return window;
      
   }


   display * display::get(::object * pobject, bool bBranch, Display * pdisplay)
   {

      synchronous_lock lock(::acme::get_global_mutex());

      if (g_p == nullptr)
      {

         auto p = memory_new display;

         p->initialize(pobject);

         p->add_listener(p);

         p->m_pdisplay = pdisplay;

         if(bBranch)
         {

            p->branch_synchronously();

         }
         else
         {

            p->init_task();

         }

      }

      return g_p;

   }


   void display::add_listener(event_listener * plistener)
   {

      synchronous_lock synchronouslock(mutex());

      m_eventlistenera.add(plistener);

   }


   void display::add_window(nano_window * pwindow)
   {

      synchronous_lock synchronouslock(mutex());

      m_windowa.add(pwindow);

   }


   void display::erase_listener(event_listener * plistener)
   {

      synchronous_lock synchronouslock(mutex());

      m_eventlistenera.erase(plistener);

   }


   void display::erase_window(nano_window * pwindow)
   {

      synchronous_lock synchronouslock(mutex());

      m_windowa.erase(pwindow);

   }


   bool display::message_loop_step()
   {

      if (!XPending(m_pdisplay))
      {

         return false;

      }

      XEvent event{};

      XNextEvent(m_pdisplay, &event);

      x11_event(&event);

      return true;

   }


   bool display::x11_posted()
   {

      return display_posted_routine_step();

   }


   bool display::x11_event(XEvent * pevent)
   {

      bool bHandled = false;

      ::index i = 0;

      synchronous_lock synchronouslock(mutex());

      for (; i < m_eventlistenera.get_count(); i++)
      {

         auto plistener = m_eventlistenera[i];

         synchronouslock.unlock();

         if(i == 0)
         {

            if (plistener->_on_event(pevent))
            {

               bHandled = true;

               break;

            }

         }
         else
         {

            if (plistener->_on_event(pevent))
            {

               bHandled = true;

               break;

            }

         }

         synchronouslock.lock();

      }

      return bHandled;

   }


   void display::message_loop()
   {

      bool bHandled1;

      bool bHandled2;

      while (::task_get_run())
      {

         if(m_bUnhook)
         {

            break;

         }

         bHandled1 = false;

         bHandled2 = false;

         while(message_loop_step())
         {

            bHandled1 = true;

         }

         if(!bHandled1)
         {

            bHandled2 = x11_posted();

         }

         if(!bHandled1 && !bHandled2)
         {

            preempt(5_ms);

         }

      }

      INFORMATION("Finished display::message_loop for nano::display");

   }


   void display::init_task()
   {

      if(m_psystem->m_ewindowing == e_windowing_none)
      {

         //set_main_user_thread();

         m_psystem->m_ewindowing = e_windowing_x11;

      }

      XInitThreads();

      if(!m_pdisplay)
      {

         set_X11_Display(XOpenDisplay(nullptr));

      }

   }


   void display::set_X11_Display(Display * pdisplay)
   {

      m_pdisplay = pdisplay;

      if (!m_pdisplay)
      {

         throw ::exception(error_null_pointer);

      }

               ::rectangle_i32 rectangleMainScreen;

      auto pscreen = DefaultScreenOfDisplay(m_pdisplay);

      int wScreen = WidthOfScreen(pscreen);
      int hScreen = HeightOfScreen(pscreen);

      //printf("::x11::display::init_task pscreen=%" PRIxPTR "\n", pscreen);
      //printf("::x11::display::init_task (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

      //rectangleMainScreen.left = 0;
      //rectangleMainScreen.top = 0;
      //rectangleMainScreen.right = wScreen;
      //rectangleMainScreen.bottom = hScreen;

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

      ::task_set_name("x11:display:run");

      set_main_user_thread();

      message_loop();

      if (m_pdisplay != nullptr)
      {

         XCloseDisplay(m_pdisplay);

         m_pdisplay = nullptr;

      }

   }


   bool display::_on_event(XEvent * pevent)
   {

      if (pevent->xany.window == DefaultRootWindow(m_pdisplay))
      {

         if(pevent->xany.type == PropertyNotify)
         {

            Atom atom = XInternAtom(m_pdisplay, "_NET_ACTIVE_WINDOW", False);

            if (atom == pevent->xproperty.atom)
            {

               auto windowActive = m_windowActive;

               for(auto & pwindow : m_windowa)
               {

                  bool bNcActive = windowActive == pwindow->m_window;

                  if (is_different(bNcActive, pwindow->m_pinterface->m_bNcActive))
                  {

                     pwindow->m_pinterface->m_bNcActive = bNcActive;

                     pwindow->redraw();

                  }

               }

               m_windowActive = windowActive;

            }

         }

      }

      return false;

   }


   ::size_i32 display::get_main_screen_size()
   {

      auto snum = DefaultScreen(m_pdisplay);

      auto width = DisplayWidth(m_pdisplay, snum);

      auto height = DisplayHeight(m_pdisplay, snum);

      return { width, height };

   }


} // namespace x11


void * x11_get_display(::object * pobject)
{

   auto pdisplay = ::x11::display::get(pobject, false);

   return pdisplay->m_pdisplay;

}


void initialize_x11_display(::object * pobject, void * pX11Display)
{

   ::x11::display::get(pobject, false, (Display *) pX11Display);

}


void * initialize_x11_display(::object * pobject)
{

   auto pdisplay = ::x11::display::get(pobject, false);

   return pdisplay->m_pdisplay;

}



