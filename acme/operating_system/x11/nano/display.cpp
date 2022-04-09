
//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


void set_main_user_thread();


namespace x11
{


   display * display::g_p = nullptr;


   display::display()
   {

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


   void display::display_post(const ::routine & routine)
   {

      defer_create_mutex();

      synchronous_lock synchronouslock(mutex());

      m_routineaPost.add(routine);

   }


   bool display::display_posted_routine_step()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_routineaPost.has_element())
      {

         auto proutine = m_routineaPost.pick_first();

         if (proutine)
         {

            synchronouslock.unlock();

            proutine->run();

            return true;

         }

      }

      return false;

   }


   void display::display_send(const ::routine & routine)
   {

      if(m_bUnhook)
      {



      }

      /*auto estatus = */ __send_routine(this, &display::display_post, routine);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

//int g_fdX11[2] = {};
//
//bool g_bX11Idle = false;
//
//
//
//void display::wait_timer_or_event()
//{
//
//   struct timeval tv;
//
//   // This returns the FD of the X11 display (or something like that)
//   int x11_fd = ConnectionNumber(m_pdisplay);
//
//   fd_set in_fds;
//
//   // Create a File Description Set containing x11_fd
//   FD_ZERO(&in_fds);
//   FD_SET(x11_fd, &in_fds);
//   FD_SET(g_fdX11[0], &in_fds);
//
//   // Set our timer.  One second sounds good.
//   tv.tv_usec = 0;
//   tv.tv_sec = 1;
//
//   // Wait for X Event or a Timer
//   int num_ready_fds = select(maximum(x11_fd, g_fdX11[0]) + 1, &in_fds, NULL, NULL, &tv);
//
//   if (num_ready_fds > 0)
//   {
//
//      //printf("Event Received!\n");
//
//      g_bX11Idle = false;
//
//      char buf[32];
//
//      int iRead;
//
//      while((iRead = read(g_fdX11[0], buf, sizeof(buf)))>0)
//      {
//
//         //printf("X11 fork count = %d\n", iRead);
//
//      }
//
//   }
//   else if (num_ready_fds == 0)
//   {
//
//      // Handle timer here
//      //printf("Timer Fired!\n");
//
//   }
//   else
//   {
//
//      //printf("An error occured!\n");
//
//   }
//
//}
//

   display * display::get(::object * pobject, bool bBranch)
   {

      synchronous_lock lock(::acme::get_global_mutex());

      if (g_p == nullptr)
      {

         auto p = new display;

         p->initialize(pobject);

         p->add_listener(p);

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

      XEvent event;

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

         if (plistener->_on_event(pevent))
         {

            bHandled = true;

            break;

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

      XInitThreads();

      m_pdisplay = XOpenDisplay(NULL);

      if (!m_pdisplay)
      {

         throw ::exception(error_null_pointer);

      }

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



} // namespace x11



