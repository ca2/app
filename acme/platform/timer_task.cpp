#include "framework.h"
#include "acme/id.h"


timer_task::timer_task()
{

}


timer_task::~timer_task()
{

}


#ifdef DEBUG


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


::e_status timer_task::initialize_timer(::acme::timer_array * ptimera, uptr uiTimer, PFN_TIMER pfnTimer, void* pvoidData, class synchronization_object* pmutex)
{

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

   return ::success;

}


bool timer_task::start(const ::duration& duration, bool bPeriodic)
{

   synchronous_lock synchronouslock(mutex());

   if (::is_set(m_ptimercallback) && !m_ptimercallback->e_timer_is_ok())
   {

      return false;

   }

   set_ok();

   m_bPeriodic = bPeriodic;

   m_duration = duration;

   try
   {

      m_bRunning = true;

      m_strDebugNote.Format("uEvent=%d", m_uEvent);

      //auto pparent = m_ptimera->m_pobject;

      //if (pparent)
      //{

      //   auto pcontextobjectParent = pparent.cast < ::object>();

      //   if (pcontextobjectParent)
      //   {

      //      auto playeredContainer = pcontextobjectParent->m_pobject;

      //      string strFormat;

      //      strFormat.Format(",container: [% s", typeid(*playeredContainer).name());

      //      m_strDebugNote += strFormat;

      //      auto pcontextobjectContainer = playeredContainer.cast < ::object> ();

      //      if (pcontextobjectContainer)
      //      {

      //         strFormat.Format(", id = % s]", __str(pcontextobjectContainer->m_id).c_str());
      //         
      //         m_strDebugNote += strFormat;

      //      }
      //      else
      //      {

      //         m_strDebugNote += "]";

      //      }

      //   }

      //}

      m_id = m_strDebugNote;

      if (!branch())
      {

         return false;

      }



   }
   catch (...)
   {

      m_bRunning = false;

      return false;

   }

   return true;

}


bool timer_task::on_timer()
{

   m_bRet = false;

   if (m_pfnTimer != nullptr)
   {

      m_pfnTimer(this);

      return true;

   }

   if (m_ptimercallback != nullptr)
   {

      return m_ptimercallback->on_timer(this);

   }

   return true;

}


void timer_task::term_task()
{

   ::task::term_task();

}


bool timer_task::task_active() const
{

   return m_bRunning && ::task::task_active();

}


::e_status timer_task::run()
{

   ::i64 iSleepMs = m_duration.u32_millis();

   ::millis c100Ms = iSleepMs / 100;

   ::millis r100Ms = iSleepMs % 100;

   while (true)
   {

      for (::index i = 0; i < c100Ms; i++)
      {

         sleep(100_ms);

         if (!task_get_run())
         {

            break;

         }

      }

      sleep(r100Ms);

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

   return m_estatus;

}



::e_status timer_task::destroy()
{

   {

      synchronous_lock synchronouslock(mutex());

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

   return ::success;

}



