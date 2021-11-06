#include "framework.h"
//#include <sched.h>
//#include <time.h>
//#include "acme/node/operating_system/ansi/_pthread.h"



bool defer_process_x_message(htask_t htask, MESSAGE * lpMsg, oswindow interaction_impl, bool bPeek)
{
#ifndef ANDROID


   if(htask == nullptr || htask->m_pthread == nullptr || htask->get_x_window_count() <= 0)
      return false;

   synchronous_lock synchronouslock(&user_mutex());

   bool bRet = false;

   bool bContinue = true;

   while(bContinue && !bRet)
   {

      bContinue = false;

      for(int i = 0; i < ::oswindow_data::s_pdataptra->get_count() && !bRet; i++)
      {

         ::oswindow_data * pdata = ::oswindow_data::s_pdataptra->element_at(i);

         if(pdata == nullptr || pdata->m_bMessageOnlyWindow)
            continue;

         if(pdata->m_htask != htask && g_oswindowDesktop != pdata)
            continue;

         Display * display = pdata->display();

         if(display == nullptr)
            continue;


         xdisplay d(display);

         XEvent e;

         if(XPending(display))
         {

            bContinue = false;

            XNextEvent(display, &e);

            if(e.type == Expose)
            {

               lpMsg->message       = e_message_paint;
               lpMsg->hwnd          = oswindow_get(display, e.xbutton.interaction_impl);
               lpMsg->lParam        = 0;
               lpMsg->wParam        = 0;

               bRet                 = true;

            }
            else if(e.type == ConfigureNotify)
            {
               if(e.xconfigure.interaction_impl == g_oswindowDesktop->interaction_impl())
               {
                  for(int j = 0; j < ::oswindow_data::s_pdataptra->get_count(); j++)
                  {
                     if(j == i)
                        continue;
                     PostMessage(::oswindow_data::s_pdataptra->element_at(j), e_message_display_change, 0, 0);
                  }
                  continue;
               }
               //               XClearWindow(w.display(), w.interaction_impl());
            }
            else if(e.type == ButtonPress || e.type == ButtonRelease)
            {

               bRet                 = true;

               if(e.xbutton.type == ButtonPress)
               {
                  if(e.xbutton.button == Button1)
                  {
                     lpMsg->message = e_message_left_button_down;
                  }
                  else if(e.xbutton.button == Button2)
                  {
                     lpMsg->message = e_message_middle_button_down;
                  }
                  else if(e.xbutton.button == Button3)
                  {
                     lpMsg->message = e_message_right_button_down;
                  }
                  else
                  {
                     bRet = false;
                  }

               }
               else if(e.xbutton.type == ButtonRelease)
               {
                  if(e.xbutton.button == Button1)
                  {
                     lpMsg->message = e_message_left_button_up;
                  }
                  else if(e.xbutton.button == Button2)
                  {
                     lpMsg->message = e_message_middle_button_up;
                  }
                  else if(e.xbutton.button == Button3)
                  {
                     lpMsg->message = e_message_right_button_up;
                  }
                  else
                  {
                     bRet = false;
                  }

               }
               else
               {

                  bRet = false;

               }


               if(bRet)
               {

                  lpMsg->hwnd          = oswindow_get(display, e.xbutton.interaction_impl);
                  lpMsg->wParam        = 0;
                  lpMsg->lParam        = __MAKE_LONG(e.xbutton.x_root, e.xbutton.y_root);

               }

            }
            else if(e.type == KeyPress || e.type == KeyRelease)
            {

               oswindow w = oswindow_get(display, e.xexpose.interaction_impl);

               bRet                 = true;

               if(e.xkey.type == KeyPress)
               {

                  lpMsg->message = e_message_key_down;

               }
               else if(e.xkey.type == KeyRelease)
               {

                  lpMsg->message = e_message_key_up;

               }
               else
               {

                  bRet = false;

               }

               lpMsg->hwnd          = oswindow_get(display, e.xbutton.interaction_impl);
               lpMsg->wParam        = e.xkey.keycode;
               lpMsg->lParam        = __MAKE_LONG(0, e.xkey.keycode);



            }
            else if(e.type == MotionNotify)
            {

               lpMsg->hwnd          = oswindow_get(display, e.xbutton.interaction_impl);
               lpMsg->message       = e_message_mouse_move;
               lpMsg->wParam        = 0;
               lpMsg->lParam        = __MAKE_LONG(e.xmotion.x_root, e.xmotion.y_root);

               bRet                 = true;

            }
            else if(e.type == DestroyNotify)
            {

               lpMsg->hwnd          = oswindow_get(display, e.xdestroywindow.interaction_impl);
               lpMsg->message       = e_message_destroy;

               bRet                 = true;

            }

            if(bPeek && bRet)
               XPutBackEvent(display, &e);



         }

         if(bRet && lpMsg->hwnd->interaction_impl() != None)
         {

            if(lpMsg->hwnd->m_htask != htask)
            {

               bRet = false;

               bContinue = true;

               PostMessage(lpMsg->hwnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam);

            }

         }

      }

   }

   return bRet;

#endif

   return false;

}




void get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority)
{

  int iOsPolicy;

  int iCa2Min;

  int iCa2Max;

/*   if(nCa2Priority == ::e_priority_normal)
  {

     iOsPolicy = SCHED_OTHER;

     iCa2Min = (int) ::e_priority_normal;

     iCa2Max = (int) ::e_priority_normal;

  }*/
  if(nCa2Priority > ::e_priority_normal)
  {

     iOsPolicy = SCHED_RR;

     iCa2Min = (int) ::e_priority_normal;

     iCa2Max = 99;

  }
  else
  {

     //iOsPolicy = SCHED_IDLE;
     iOsPolicy = SCHED_OTHER;

     iCa2Min = 0;

     iCa2Max = (int) ::e_priority_normal;

  }

  int iOsMax = sched_get_priority_max(iOsPolicy);

  int iOsMin = sched_get_priority_min(iOsPolicy);

  int iOsPriority;

  if(iCa2Min == iCa2Max)
  {
     iOsPriority = 0;
  }
  else
  {
     iOsPriority = (((nCa2Priority - iCa2Min)  * (iOsMax - iOsMin)) / (iCa2Max - iCa2Min)) + iOsMin;
  }

  iOsPriority = maximum(iOsMin, minimum(iOsMax, iOsPriority));

  *piPolicy = iOsPolicy;

  pparam->sched_priority = iOsPriority;

}

//
//i32 get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
//{
//
//   int iCa2Min;
//
//   int iCa2Max;
//
//
//   if(iOsPolicy == SCHED_RR)
//   {
//
//      iCa2Min = (int) ::e_priority_normal;
//
//      iCa2Max = 99;
//
//   }
///*   else if(iOsPolicy == SCHED_IDLE)
//   {
//
//      iCa2Min = 0;
//
//      iCa2Max = (int) ::e_priority_normal;
//
//   }*/
//   else
//   {
//
//      //iCa2Min = (int) ::e_priority_normal;
//      iCa2Min = (int) 0;
//
//      iCa2Max = (int) ::e_priority_normal;
//
//   }
//
//   int iOsMax = sched_get_priority_max(iOsPolicy);
//
//   int iOsMin = sched_get_priority_min(iOsPolicy);
//
//   int iCa2Priority;
//
//   if(iOsMax == iOsMin)
//   {
//      iCa2Priority = (i32) ::e_priority_normal;
//   }
//   else
//   {
//      iCa2Priority = (((pparam->sched_priority - iOsMin)  * (iCa2Max - iCa2Min)) / (iOsMax - iOsMin)) + iCa2Min;
//   }
//
//   iCa2Priority = maximum(iCa2Min, minimum(iCa2Max, iCa2Priority));
//
//   return iCa2Priority;
//
//}
//
//
//void thread_get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority)
//{
//
//   get_os_priority(piPolicy, pparam, nCa2Priority);
//
//}
//
//
//i32 thread_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
//{
//
//   return get_scheduling_priority(iOsPolicy, pparam);
//
//}
//
//
//void process_get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority)
//{
//
//   get_os_priority(piPolicy, pparam, nCa2Priority);
//
//}
//
//
//i32 process_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
//{
//
//   return get_scheduling_priority(iOsPolicy, pparam);
//
//}
//
//
//
//
//
//
//namespace apex
//{
//
//   CLASS_DECL_APEX bool set_priority_class(i32 priority)
//   {
//
//      i32 iPolicy = SCHED_OTHER;
//
//      sched_param schedparam;
//
//      schedparam.sched_priority = 0;
//
//      get_os_priority(&iPolicy, &schedparam, priority);
//
//      sched_setscheduler(0, iPolicy, &schedparam);
//
//      return true;
//
//   }
//
//
//
//
//} // namespace apex


#if !defined(ANDROID) || defined(__arm__)

::thread_object < _TEB > t_pteb;

struct _TEB * WINAPI NtCurrentTeb(void)
{

   return t_pteb;

}

#endif






/*
bool on_init_thread()
{

   if(!__os_init_thread())
   {

      return false;

   }

   return true;

}


bool on_term_thread()
{

   bool bOk1 = __os_term_thread();

   return bOk1;

}





void __node_init_multithreading()
{

}



void __node_term_multithreading()
{

}

*/


// thread_int_ptr < HRESULT > thread_set("hresult_co_initialize");


bool __os_init_thread()
{

   return true;

}



bool __os_term_thread()
{

   //thread_shutdown();

   return true;

}


//int get_processor_count()
//{
//
//   return sysconf(_SC_NPROCESSORS_ONLN);
//
//   //int c = 0;
//
//   //int s, j;
//
//   //cpu_set_t cpuset;
//
//   //pthread_t thread = pthread_self();
//
//   //s = pthread_getaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
//
//   //if (s != 0)
//   //{
//
//   //   return -1;
//
//   //}
//
//   //for (j = 0; j < CPU_SETSIZE; j++)
//   //{
//
//   //   if (CPU_ISSET(j, &cpuset))
//   //   {
//
//   //      c++;
//
//   //   }
//
//   //}
//
//   //return c;
//
//}

int get_processor_count();

int get_current_process_affinity_order()
{

   return get_processor_count();

}




