#include "framework.h"

bool defer_process_x_message(htask_t htask, MESSAGE * lpMsg, oswindow window, bool bPeek)
{

   if(htask == nullptr || htask->m_pthread == nullptr || htask->m_pthread->get_x_window_count() <= 0)
      return false;

   mutex_lock synchronouslock(user_mutex(), true);

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
               lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
               lpMsg->lParam        = 0;
               lpMsg->wParam        = 0;

               bRet                 = true;

            }
            else if(e.type == ConfigureNotify)
            {
               if(e.xconfigure.window == g_oswindowDesktop->window())
               {
                  for(int j = 0; j < ::oswindow_data::s_pdataptra->get_count(); j++)
                  {
                     if(j == i)
                        continue;
                     PostMessage(::oswindow_data::s_pdataptra->element_at(j), e_message_display_change, 0, 0);
                  }
                  continue;
               }
                              //               XClearWindow(w.display(), w.window());
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

                  lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
                  lpMsg->wParam        = 0;
                  lpMsg->lParam        = __MAKE_LONG(e.xbutton.x_root, e.xbutton.y_root);

               }

            }
            else if(e.type == KeyPress || e.type == KeyRelease)
            {

               oswindow w = oswindow_get(display, e.xexpose.window);

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

               lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
               lpMsg->wParam        = e.xkey.keycode;
               lpMsg->lParam        = __MAKE_LONG(0, e.xkey.keycode);



            }
            else if(e.type == MotionNotify)
            {

               lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
               lpMsg->message       = e_message_mouse_move;
               lpMsg->wParam        = 0;
               lpMsg->lParam        = __MAKE_LONG(e.xmotion.x_root, e.xmotion.y_root);

               bRet                 = true;

            }
            else if(e.type == DestroyNotify)
            {

               lpMsg->hwnd          = oswindow_get(display, e.xdestroywindow.window);
               lpMsg->message       = e_message_destroy;

               bRet                 = true;

            }

            if(bPeek && bRet)
               XPutBackEvent(display, &e);



         }

         if(bRet && lpMsg->hwnd->window() != None)
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

}





void get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

   if(nCa2Priority == ::ca2::scheduling_priority_normal)
   {

      iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::ca2::scheduling_priority_normal;

      iCa2Max = (int) ::ca2::scheduling_priority_normal;

   }
   else if(nCa2Priority > ::ca2::scheduling_priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::ca2::scheduling_priority_normal;

      iCa2Max = 99;

   }
   else
   {

      iOsPolicy = SCHED_IDLE;

      iCa2Min = 0;

      iCa2Max = (int) ::ca2::scheduling_priority_normal;

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

i32 get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   int iCa2Min;

   int iCa2Max;


   if(iOsPolicy == SCHED_RR)
   {

      iCa2Min = (int) ::ca2::scheduling_priority_normal;

      iCa2Max = 99;

   }
   else if(iOsPolicy == SCHED_IDLE)
   {

      iCa2Min = 0;

      iCa2Max = (int) ::ca2::scheduling_priority_normal;

   }
   else
   {

      iCa2Min = (int) ::ca2::scheduling_priority_normal;

      iCa2Max = (int) ::ca2::scheduling_priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iCa2Priority;

   if(iOsMax == iOsMin)
   {
      iCa2Priority = (i32) ::ca2::scheduling_priority_normal;
   }
   else
   {
      iCa2Priority = (((pparam->sched_priority - iOsMin)  * (iCa2Max - iCa2Min)) / (iOsMax - iOsMin)) + iCa2Min;
   }

   iCa2Priority = maximum(iCa2Min, minimum(iCa2Max, iCa2Priority));

   return iCa2Priority;

}


void thread_get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority)
{

   get_os_priority(piPolicy, pparam, nCa2Priority);

}


i32 thread_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}


void process_get_os_priority(i32 * piPolicy, sched_param * pparam, i32 nCa2Priority)
{

   get_os_priority(piPolicy, pparam, nCa2Priority);

}


i32 process_get_scheduling_priority(i32 iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}






namespace ca2
{

   CLASS_DECL_ca bool set_priority_class(i32 priority)
	{

      i32 iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, priority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

	}




} // namespace ca2
