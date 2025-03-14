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


long long timer_task::increment_reference_count()
{

   return task::increment_reference_count();

}


long long timer_task::decrement_reference_count()
{

   return task::decrement_reference_count();

}


long long timer_task::release()
{

   return task::release();

}


#endif


void timer_task::initialize_timer(::particle * pparticle, ::acme::timer_array * ptimera, uptr uiTimer, const::procedure& procedure, ::particle * pparticleSynchronization)
{

   ::task::initialize(pparticle);

   clear_flag(e_flag_running);

   m_bHandling = false;

   m_uTimer = uiTimer;

   m_procedure = procedure;

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

      m_strDebugNote.formatf("uTimer-%d", m_uTimer);

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

      //         strFormat.formatf(", atom = % s]", as_string(pcontextobjectContainer->id()).c_str());
      //         
      //         m_strDebugNote += strFormat;

      //      }
      //      else
      //      {

      //         m_strDebugNote += "]";

      //      }

      //   }

      //}

      id() = m_strDebugNote;

      set_flag(e_flag_running);

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

   if (m_procedure)
   {

      m_procedure();

      return;
      //return true;

   }

   if (m_ptimercallback != nullptr)
   {

      m_ptimercallback->call_on_timer(this);

      return;

   }

   //return true;

}


void timer_task::term_task()
{

   ::task::term_task();

}


//bool timer_task::is_task_set() const
//{
//
//   return ::task::is_task_set();
//
//}


void timer_task::run()
{

   auto waitSleep = m_timeWait;

   const auto intervalTime = 100_ms;

   auto [countDecisecondSleep, remainderDecisecondSleep] = waitSleep.count_and_remainder(intervalTime);

   while (true)
   {

      task_iteration();

      for (::collection::index i = 0; i < countDecisecondSleep; i++)
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

   //m_bRunning = false;

   clear_flag(e_flag_running);

}


void timer_task::stop_timer_task()
{

   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (is_task_set())
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



