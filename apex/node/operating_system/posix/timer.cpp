#include "framework.h"


#include <signal.h>
#include <time.h>


//#if defined(LINUX) || defined(ANDROID)

//void apex_timer_handler(sigval sigval);


//void timer::impl_init()
//{
//
//   //__zero(m_sev);
//
//   // m_timerid = nullptr;
//
//   // m_sev.sigev_notify = SIGEV_THREAD;
//
//   // m_sev.sigev_signo = 0;
//
//   // m_sev.sigev_value.sival_ptr = this;
//
//   // m_sev.sigev_notify_function = apex_timer_handler;
//
//   //m_bInit = !e_timer_create(CLOCK_REALTIME, &m_sev, &m_timerid);
//
//   //if (e_timer_create(CLOCK_REALTIME, &m_sev, &m_timerid) == -1)
//   //{
//
//   //   __throw(::exception("e_timer_create failed"));
//
//   //}
//
//   m_bInit = true;
//
//}
//

//bool timer::impl_start()
//{
//
//   if (!m_bInit)
//   {
//
//      return false;
//
//   }
//
//   //itimerspec & its = m_its;
//
//   //its.it_value.tv_sec = m_dwMillis / 1000;
//
//   //its.it_value.tv_nsec = (m_dwMillis * 1000 * 1000) % (1000 * 1000 * 1000);
//
//
//   begin();
//
////   if (m_bPeriodic)
////   {
////
////      its.it_interval = its.it_value;
////
////      if (e_timer_settime(m_timerid, 0, &its, nullptr) == -1)
////      {
////
////         return false;
////
////      }
////
////   }
////   else
//////   {
////
////      its.it_interval.tv_nsec = 0;
////      its.it_interval.tv_sec = 0;
////
////      if (e_timer_settime(m_timerid, 0, &its, nullptr) == -1)
////      {
////
////         return false;
////
////      }
//
//   //}
//
//
//   return true;
//
//}
//
//
//void timer::impl_term()
//{
//
//   if (m_bInit)
//   {
//
//      m_bInit = false;
////
////      e_timer_delete(m_timerid);
//
//      //m_timerid = nullptr;
//
//   }
//
//}
//
//
//void timer::impl_stop()
//{
//
//set_finish();
//
////   if (m_bInit)
////   {
////
////      itimerspec its;
////
////      its.it_value.tv_nsec = 0;
////      its.it_value.tv_sec = 0;
////      its.it_interval.tv_nsec = 0;
////      its.it_interval.tv_sec = 0;
////
////      if(e_timer_settime(m_timerid, 0, &its, nullptr) == -1)
////      {
////
////         printf("Failed to stop the timer.");
////
////      }
////
////   }
//
//}
//
//
//bool timer::impl_restart()
//{
//
//   if (!m_bInit)
//   {
//
//      return false;
//
//   }
////
////   if (!task_get_run())
////   {
////
////      return false;
////
////   }
////
////   impl_stop();
////
////   if (e_timer_settime(m_timerid, 0, &m_its, nullptr) == -1)
////   {
////
////      return false;
////
////   }
////
//   return true;
//
//}
//
//::e_status timer::run()
//{
//
//   while(task_sleep(::millis(m_dwMillis)))
//   {
//
//      try
//      {
//
//         on_timer();
//
//      }
//      catch (...)
//      {
//
//      }
//
//      if(!m_bPeriodic)
//      {
//
//         break;
//
//      }
//
//   }
//
//   return m_estatus;
//
//}
////void apex_timer_handler(sigval sigval)
////{
////
////   ::timer * ptimer = (::timer *) sigval.sival_ptr;
////
////   try
////   {
////
////      ptimer->call_on_timer();
////
////   }
////   catch (...)
////   {
////
////   }
////
////}
//
////#endif
//
