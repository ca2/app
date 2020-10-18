#include "framework.h"
#include "apex/const/id.h"


#define THREADED_TIMER


timer::timer(::apex::timer_array * ptimera, uptr uiTimer, PFN_TIMER pfnTimer, void * pvoidData, class sync * pmutex) :
   ::object(ptimera)
{

   m_bRunning = false;

   initialize(ptimera);

   __refer(m_ptimera, ptimera);

   if(m_ptimera)
   {

      m_ptimera->m_map[uiTimer] = this;

      //impl_init();

   }

   m_bHandling = false;

   m_nIDEvent = uiTimer;

   m_pfnTimer = pfnTimer;

   m_pvoidData = pvoidData;

   m_pcallback = nullptr;

   m_puserinteraction = nullptr;

}


timer::~timer()
{

}


i64 timer::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return thread::add_ref(OBJ_REF_DBG_ARGS);

}


i64 timer::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return thread::dec_ref(OBJ_REF_DBG_ARGS);

}


i64 timer::release(OBJ_REF_DBG_PARAMS_DEF)
{

   return thread::release(OBJ_REF_DBG_ARGS);

}


bool timer::start(const ::duration & duration, bool bPeriodic)
{

   sync_lock sl(mutex());

   if (::is_set(m_pcallback) && !m_pcallback->timer_is_ok())
   {

      return false;

   }

   set_ok();

   m_bPeriodic = bPeriodic;

   m_duration = duration;

   try
   {

      m_bRunning = true;

      if (!begin())
      {

         return false;

      }

      m_strDebugNote.Format("nIDEvent=%d,container:[%s,id=%s])", m_nIDEvent, typeid(*m_ptimera->get_context_object()->get_context_object()).name(), __str(m_ptimera->get_context_object()->get_context_object()->m_id).c_str());

      //if(!impl_start())
      //{

      //   return false;

      //}

   }
   catch(...)
   {

      m_bRunning = false;

      return false;

   }

   return true;

}


//void timer::call_on_timer()
//{
//
//   sync_lock sl(mutex());
//
//   __keep_true(m_bHandling);
//
//   if (!is_timer_ok())
//   {
//
//      return;
//
//   }
//
//   m_bDupHandle = false;
//
//   set_current_handles();
//
//   ::set_thread(this);
//
//   bool bRepeat = true;
//
//   ::thread_set(id_thread_is_timer);
//
//   try
//   {
//
//      if(!thread_get_run())
//      {
//
//         bRepeat = false;
//
//      }
//
//   }
//   catch(...)
//   {
//
//      bRepeat = false;
//
//   }
//
//   if(bRepeat)
//   {
//
//      m_bTemporary = true;
//
//      sl.unlock();
//
//      try
//      {
//
//         if(!on_timer())
//         {
//
//            bRepeat = false;
//
//         }
//
//      }
//      catch(...)
//      {
//
//      }
//
//      sl.lock();
//
//   }
//
//   if(bRepeat)
//   {
//
//      try
//      {
//
//         if (m_bPeriodic)
//         {
//
//            if(!impl_restart())
//            {
//
//               bRepeat = false;
//
//            }
//
//         }
//         else
//         {
//
//             bRepeat = false;
//
//         }
//
//      }
//      catch (...)
//      {
//
//         bRepeat = false;
//
//      }
//
//   }
//
//   if(!bRepeat)
//   {
//
//      try
//      {
//
//         m_bRunning = false;
//
//      }
//      catch (...)
//      {
//
//      }
//
//   }
//
//}


bool timer::on_timer()
{

   m_bRet = false;

   if (m_pfnTimer != nullptr)
   {

      m_pfnTimer(this);

      return true;

   }

   if (m_pcallback != nullptr)
   {

      return m_pcallback->on_timer(this);

   }

   return true;

}


void timer::term_thread()
{

   {

      sync_lock sl(mutex());

      try
      {

         m_ptimera->remove_timer(this);

      }
      catch (...)
      {

      }

   }

   ::thread::term_thread();

}


bool timer::thread_active() const
{

   return m_bRunning && ::thread::thread_active();

}


#ifdef THREADED_TIMER


//void timer::impl_init()
//{
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
//   begin();
//
//   return true;
//
//}


//void timer::impl_term()
//{
//
//   if (m_bInit)
//   {
//
//      m_bInit = false;
//
//   }
//
//}


//void timer::impl_stop()
//{
//
//   set_finish();
//
//}

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
//
//   return true;
//
//}


::estatus timer::run()
{

   while (thread_sleep(m_duration))
   {

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


const char* timer::debug_note() const
{

   return m_strDebugNote;

}



#endif // THREADED_TIMER



