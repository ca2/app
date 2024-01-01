#include "framework.h"
#include "acme/constant/id.h"
#include "timer_task.h"
#include "acme/parallelization/synchronous_lock.h"


timer_task::timer_task()
{

   m_pTimerTask = this;

}


timer_task::~timer_task()
{

}


#ifdef _DEBUG


i64 timer_task::increment_reference_count()
{

   return task::increment_reference_count();

}


i64 timer_task::decrement_reference_count()
{

   return task::decrement_reference_count();

}


i64 timer_task::release()
{

   return task::release();

}


#endif


void timer_task::initialize_timer(::particle * pparticle, ::acme::timer_array * ptimera, uptr uiTimer, PFN_TIMER pfnTimer, void* pvoidData, ::particle * pparticleSynchronization)
{

   ::task::initialize(pparticle);

   m_bRunning = false;

   m_bHandling = false;

   m_uEvent = uiTimer;

   m_pfnTimer = pfnTimer;

   m_pvoidData = pvoidData;

}


void timer_task::start_timer_task(const class time & timeWait, bool bPeriodic)
{

   _synchronous_lock synchronouslock(this->synchronization());

   if (::is_set(m_ptimercallback) && !m_ptimercallback->e_timer_is_ok())
   {

      return;

   }

   set_ok_flag();

   m_bPeriodic = bPeriodic;

   m_timeWait = timeWait;

   //try
   //{

      m_strDebugNote.formatf("uEvent=%d", m_uEvent);

      //auto pparent = m_ptimera->m_pobject;

      //if (pparent)
      //{

      //   auto pcontextobjectParent = pparent.cast < ::object>();

      //   if (pcontextobjectParent)
      //   {

      //      auto playeredContainer = pcontextobjectParent->m_pobject;

      //      string strFormat;

      //      strFormat.formatf(",container: [% s", typeid(*playeredContainer).name());

      //      m_strDebugNote += strFormat;

      //      auto pcontextobjectContainer = playeredContainer.cast < ::object> ();

      //      if (pcontextobjectContainer)
      //      {

      //         strFormat.formatf(", atom = % s]", as_string(pcontextobjectContainer->m_atom).c_str());
      //         
      //         m_strDebugNote += strFormat;

      //      }
      //      else
      //      {

      //         m_strDebugNote += "]";

      //      }

      //   }

      //}

      m_atom = m_strDebugNote;

      m_bRunning = true;

      branch();

      ///if (!branch())
      //{

        // return false;

      //}



   //}
   //catch (...)
   //{

   //   return false;

   //}

   //return true;

}


void timer_task::on_timer()
{

   m_bRet = false;

   if (m_pfnTimer != nullptr)
   {

      m_pfnTimer(this);

      return;
      //return true;

   }

   if (m_ptimercallback != nullptr)
   {

      m_ptimercallback->on_timer(this);

      return;

   }

   //return true;

}


void timer_task::term_task()
{

   ::task::term_task();

}


bool timer_task::task_active() const
{

   return m_bRunning && ::task::task_active();

}


void timer_task::run()
{

   auto waitSleep = m_timeWait;

   const auto intervalTime = 100_ms;

   auto [countDecisecondSleep, remainderDecisecondSleep] = waitSleep.count_and_remainder(intervalTime);

   while (true)
   {

      for (::index i = 0; i < countDecisecondSleep; i++)
      {

         ::preempt(100_ms);

         if (!task_get_run())
         {

            break;

         }

      }

      ::preempt(remainderDecisecondSleep);

      if (!task_get_run())
      {

         break;

      }

      try
      {

         on_timer();

      }
      catch (...)
      {

      }

      if (!m_bPeriodic)
      {

         break;

      }

   }

   m_bRunning = false;

}


void timer_task::stop_timer_task()
{

   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_bRunning)
      {

         set_finish();

      }
      else
      {

         destroy();

      }

   }

}


void timer_task::destroy()
{

   {

      _synchronous_lock synchronouslock(this->synchronization());

      try
      {

         if (m_ptimera)
         {

            synchronouslock.unlock();

            m_ptimera->erase_timer(this);

            synchronouslock._lock();

            m_ptimera.release();

         }

      }
      catch (...)
      {

      }

   }

   ::timer::destroy();

   ::task::destroy();

}



