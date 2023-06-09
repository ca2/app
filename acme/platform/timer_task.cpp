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


i64 timer_task::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return task::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 timer_task::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return task::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


i64 timer_task::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
{

   return task::release(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

}


#endif


void timer_task::initialize_timer(::particle * pparticle, ::acme::timer_array * ptimera, uptr uiTimer, PFN_TIMER pfnTimer, void* pvoidData, ::particle * pparticleSynchronization)
{

   /*auto estatus = */ ::task::initialize(pparticle);

   //if(!estatus)
   //{


   //   return estatus;

   //}

   m_bRunning = false;

   m_ptimera.reset(ptimera OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

   if (m_ptimera)
   {

      m_ptimera->m_map[uiTimer] = this;

   }

   m_bHandling = false;

   m_uEvent = uiTimer;

   m_pfnTimer = pfnTimer;

   m_pvoidData = pvoidData;

   //return ::success;

}


void timer_task::start(const class time & timeWait, bool bPeriodic)
{

   synchronous_lock synchronouslock(this->synchronization());

   if (::is_set(m_ptimercallback) && !m_ptimercallback->e_timer_is_ok())
   {

      return;

   }

   set_ok_flag();

   m_bPeriodic = bPeriodic;

   m_timeWait = timeWait;

   //try
   //{

      m_bRunning = true;

      m_strDebugNote.format("uEvent=%d", m_uEvent);

      //auto pparent = m_ptimera->m_pobject;

      //if (pparent)
      //{

      //   auto pcontextobjectParent = pparent.cast < ::object>();

      //   if (pcontextobjectParent)
      //   {

      //      auto playeredContainer = pcontextobjectParent->m_pobject;

      //      string strFormat;

      //      strFormat.format(",container: [% s", typeid(*playeredContainer).name());

      //      m_strDebugNote += strFormat;

      //      auto pcontextobjectContainer = playeredContainer.cast < ::object> ();

      //      if (pcontextobjectContainer)
      //      {

      //         strFormat.format(", atom = % s]", as_string(pcontextobjectContainer->m_atom).c_str());
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

      branch();

      ///if (!branch())
      //{

        // return false;

      //}



   //}
   //catch (...)
   //{

      m_bRunning = false;

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

   auto countDecisecondSleep = (::i32) (waitSleep.integral_millisecond() / 100);

   auto remainderDecisecondSleep = (::i32) (waitSleep.integral_millisecond() % 100);

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

      ::preempt(integral_millisecond(remainderDecisecondSleep));

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

   //return m_estatus;

}



void timer_task::destroy()
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      try
      {

         if (m_ptimera)
         {

            m_ptimera->erase_timer(this);

            m_ptimera.release(OBJECT_REFERENCE_COUNT_DEBUG_THIS);

         }

      }
      catch (...)
      {

      }

   }

   ::timer::destroy();

   ::task::destroy();

   //return ::success;

}



