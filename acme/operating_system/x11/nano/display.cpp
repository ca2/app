
//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


namespace x11
{


   display * display::g_p = nullptr;


   display::display()
   {

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

   display * display::get(::object * pobject)
   {

      synchronous_lock lock(::acme::get_global_mutex());

      if (g_p == nullptr)
      {

         auto p = new display;

         p->initialize(pobject);

         p->add_listener(p);

         p->branch_synchronously();

      }

      return g_p;

   }


//   void hook_into_message_loop(x11_event_listener * plistener)
//   {
//
//      g_px11display->add_listener(plistener);
//
//   }


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

      ::index i = 0;

      synchronous_lock synchronouslock(mutex());

      for (; i < m_eventlistenera.get_count();)
      {

         auto plistener = m_eventlistenera[i];

         synchronouslock.unlock();

         if (!plistener->_on_event(&event))
         {

            synchronouslock.lock();

            m_eventlistenera.erase(plistener);

         }
         else
         {

            i++;

            synchronouslock.lock();

         }

      }

      return false;

   }


   void display::message_loop()
   {

      bool bProcessedSomething1;

      bool bProcessedSomething2;

      while (::task_get_run())
      {

         bProcessedSomething1 = false;

         while (message_loop_step())
         {

            bProcessedSomething1 = true;

         }

         bProcessedSomething2 = display_posted_routine_step();

         if (!bProcessedSomething1 && !bProcessedSomething2)
         {

            preempt(5_ms);

         }

      }

      INFORMATION("Finished display::message_loop");

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


   void display::run()
   {


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

      return true;

   }



} // namespace x11



