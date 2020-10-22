#include "framework.h"
#include "apex/const/id.h"


threaded_timer::threaded_timer()
{

}


threaded_timer::~threaded_timer()
{

}



i64 threaded_timer::add_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return thread::add_ref(OBJ_REF_DBG_ARGS);

}


i64 threaded_timer::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
{

   return thread::dec_ref(OBJ_REF_DBG_ARGS);

}


i64 threaded_timer::release(OBJ_REF_DBG_PARAMS_DEF)
{

   return thread::release(OBJ_REF_DBG_ARGS);

}


::estatus threaded_timer::initialize_timer(::apex::timer_array* ptimera, uptr uiTimer, PFN_TIMER pfnTimer, void* pvoidData, class sync* pmutex)
{

   auto estatus = initialize(ptimera);

   if (!estatus)
   {

      return estatus;

   }

   m_bRunning = false;

   initialize(ptimera);

   __refer(m_ptimera, ptimera);

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


bool threaded_timer::start(const ::duration& duration, bool bPeriodic)
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

      if (!begin())
      {

         return false;

      }

      m_strDebugNote.Format("uEvent=%d,container:[%s,id=%s])", m_uEvent, typeid(*m_ptimera->get_context_object()->get_context_object()).name(), __str(m_ptimera->get_context_object()->get_context_object()->m_id).c_str());

      //if(!impl_start())
      //{

      //   return false;

      //}

   }
   catch (...)
   {

      m_bRunning = false;

      return false;

   }

   return true;

}


//void threaded_timer::call_on_timer()
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


bool threaded_timer::on_timer()
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


void threaded_timer::term_thread()
{

   ::thread::term_thread();

}


bool threaded_timer::thread_active() const
{

   return m_bRunning && ::thread::thread_active();

}


::estatus threaded_timer::run()
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



void threaded_timer::finalize()
{

   {

      sync_lock sl(mutex());

      try
      {

         if (m_ptimera)
         {

            m_ptimera->remove_timer(this);

            __release(m_ptimera OBJ_REF_DBG_COMMA_THIS);

         }

      }
      catch (...)
      {

      }

   }

   ::timer::finalize();

   ::thread::finalize();

}



