#include "framework.h"
#include "apex/const/id.h"


timer_task::timer_task()
{

}


timer_task::~timer_task()
{

}



i64 timer_task::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return task::add_ref(OBJ_REF_DBG_ARGS);

}


i64 timer_task::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return task::dec_ref(OBJ_REF_DBG_ARGS);

}


i64 timer_task::release(OBJ_REF_DBG_PARAMS_DEF)
{

   return task::release(OBJ_REF_DBG_ARGS);

}


::estatus timer_task::initialize_timer(::apex::timer_array* ptimera, uptr uiTimer, PFN_TIMER pfnTimer, void* pvoidData, class sync* pmutex)
{

   auto estatus = initialize(ptimera);

   if (!estatus)
   {

      return estatus;

   }

   m_bRunning = false;

   initialize(ptimera);

   m_ptimera.reset(ptimera OBJ_REF_DBG_COMMA_THIS_FUNCTION_LINE);

   if (m_ptimera)
   {

      m_ptimera->m_map[uiTimer] = this;

   }

   m_bHandling = false;

   m_uEvent = uiTimer;

   m_pfnTimer = pfnTimer;

   m_pvoidData = pvoidData;

   return estatus;

}


bool timer_task::start(const ::duration& duration, bool bPeriodic)
{

   sync_lock sl(mutex());

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

      auto pparent = m_ptimera->m_pobjectContext;

      if (pparent)
      {

         auto pcontextobjectParent = pparent.cast < ::context_object>();

         if (pcontextobjectParent)
         {

            auto playeredContainer = pcontextobjectParent->m_pobjectContext;

            string strFormat;

            strFormat.Format(",container: [% s", typeid(*playeredContainer).name());

            m_strDebugNote += strFormat;

            auto pcontextobjectContainer = playeredContainer.cast < ::context_object> ();

            if (pcontextobjectContainer)
            {

               strFormat.Format(", id = % s]", __str(pcontextobjectContainer->m_id).c_str());
               
               m_strDebugNote += strFormat;

            }
            else
            {

               m_strDebugNote += "]";

            }

         }

      }

      m_id = m_strDebugNote;

      if (!begin_task())
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


::estatus timer_task::on_task()
{

   ::i64 iSleepMs = m_duration.u32_millis();

   ::i64 c100Ms = iSleepMs / 100;

   ::i64 r100Ms = iSleepMs % 100;

   while (true)
   {

      for (::index i = 0; i < c100Ms; i++)
      {

         Sleep(100);

         if (!thread_get_run())
         {

            break;

         }

      }

      Sleep((::u32) r100Ms);

      if (!thread_get_run())
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



void timer_task::finalize()
{

   {

      sync_lock sl(mutex());

      try
      {

         if (m_ptimera)
         {

            m_ptimera->remove_timer(this);

            m_ptimera.release(OBJ_REF_DBG_THIS);

         }

      }
      catch (...)
      {

      }

   }

   ::timer::finalize();

   ::task::finalize();

}



