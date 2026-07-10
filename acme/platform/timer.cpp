// Deep Refactoring timer_handler by camilo on 2026-05-28 10:33 <3ThomasBorregaardSørensen!! Mummi!! Bilbo
#include "framework.h"
#include "timer.h"
#include "acme/constant/id.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/session.h"



timer_handler::timer_handler()
{

   // m_pTimerTask = this;
   m_timeResolution = 200_ms;

}


timer_handler::~timer_handler() {}


//void timer_handler::on_initialize_particle()
//{

  // ::task::on_initialize_particle();

   //defer_create_synchronization();
//}


::timer * timer_handler::add_timer(::timer_dispatch * ptimerdispatch, const ::e_timer & etimer, const class ::time &time,
                                                   const ::timer_callback &callback)
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto &ptimer = m_timermap[ptimerdispatch][etimer];

   defer_construct_newø(ptimer);

   ptimer->m_ptimerhandler = this;
   ptimer->m_ptimerdispatch = ptimerdispatch;
   ptimer->m_etimer = etimer;
   ptimer->m_time = time;
   ptimer->m_callback = callback;
   ptimer->restart();

   m_timeResolution = minimum(minimum(m_timeResolution, time), ::system()->m_timeProcedureTimerMinimumResolution);

   on_start_timers_handling_hint();

    //   if (!is_task_set2())
  // {
//branch();
   //}



   return ptimer;

}


void timer_handler::erase_timer(::timer_dispatch * ptimerdispatch, const ::e_timer & etimer)
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   m_timermap[ptimerdispatch].erase(etimer);

    on_stop_timers_handling_hint();

   //if (is_empty())
   //{

     // set_finish();
   //}
}


void timer_handler::erase_timer_dispatch(::timer_dispatch * ptimerdispatch)
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

    m_timermap.erase(ptimerdispatch);
//   bool bFound;

  // do
 //  {

   //   bFound = false;

   //   for (auto &ptimer: this->payloads())
   //   {
     //    if (ptimer->m_callback == callback)
     //    {
     //       erase(ptimer->m_etimer);
     //       bFound = true;
     //       break;
     //    }
     // }
   // }
   // while (bFound);
}


//
// void procedure_timer::initialize_timer(::particle * pparticle, ::acme::timer_array * ptimera, uptr uiTimer,
// const::procedure& procedure, ::particle * pparticleSynchronization)
//{
//
//   ::task::initialize(pparticle);
//
//   clear_flag(e_flag_running);
//
//   m_bHandling = false;
//
//   m_uTimer = uiTimer;
//
//   m_procedure = procedure;
//
//}


// void procedure_timer::start_procedure_timer(const class time & timeWait, bool bPeriodic)
//{
//
//    _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//    if (::is_set(m_ptimercallback) && !m_ptimercallback->e_timer_is_ok())
//    {
//
//       return;
//
//    }
//
//    set_ok_flag();
//
//    m_bPeriodic = bPeriodic;
//
//    m_timeWait = timeWait;
//
//    //try
//    //{
//
//       m_strDebugNote.formatf("uTimer-%d", m_uTimer);
//
//       //auto pparent = m_ptimera->m_pobject;
//
//       //if (pparent)
//       //{
//
//       //   auto pcontextobjectParent = pparent.cast < ::object>();
//
//       //   if (pcontextobjectParent)
//       //   {
//
//       //      auto playeredContainer = pcontextobjectParent->m_pobject;
//
//       //      string strFormat;
//
//       //      strFormat.formatf(",container: [% s", typeid(*playeredContainer).name());
//
//       //      m_strDebugNote += strFormat;
//
//       //      auto pcontextobjectContainer = playeredContainer.cast < ::object> ();
//
//       //      if (pcontextobjectContainer)
//       //      {
//
//       //         strFormat.formatf(", atom = % s]", as_string(pcontextobjectContainer->id()).c_str());
//       //
//       //         m_strDebugNote += strFormat;
//
//       //      }
//       //      else
//       //      {
//
//       //         m_strDebugNote += "]";
//
//       //      }
//
//       //   }
//
//       //}
//
//       id() = m_strDebugNote;
//
//       set_flag(e_flag_running);
//
//       branch();
//
//       ///if (!branch())
//       //{
//
//         // return false;
//
//       //}
//
//
//
//    //}
//    //catch (...)
//    //{
//
//    //   return false;
//
//    //}
//
//    //return true;
//
// }


// void procedure_timer::on_timer()
//{
//
//    m_bRet = false;
//
//    if (m_procedure)
//    {
//
//       m_procedure();
//
//       return;
//       //return true;
//
//    }
//
//    if (m_ptimercallback != nullptr)
//    {
//
//       m_ptimercallback->call_on_timer(this);
//
//       return;
//
//    }
//
//    //return true;
//
// }


// void procedure_timer::term_task()
//{
//
//    ::task::term_task();
//
// }


// bool procedure_timer::is_task_set() const
//{
//
//    return ::task::is_task_set();
//
// }

   void timer_handler::on_start_timers_handling_hint() {

}
   void timer_handler::on_stop_timers_handling_hint() {

}

void timer_handler::handle_timers()
{

   auto itNext = m_timermap.begin();

   decltype(itNext) it;

   ::timer_map * ptimermap = nullptr;

   while (task_get_run())
   {

     // task_run(m_timeResolution);

      it = itNext;

      if (m_timermap.is_empty())
      {

         break;

      }

      {

         _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         if (it == m_timermap.end())
         {

            break;

         }

         ptimermap = &it->m_element2;

         itNext = it + 1;

      }

      if (ptimermap->count() > 0)
      {

          _handle_timers(ptimermap);
          //(*ptimer)(ptimer);
      }

      //if (ptimermap->count() <= 0)
      //{

      //  _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //   if (ptimermap->count() <= 0)
      //   {
      //      
      //      m_timermap.erase(it);

      //   }

      //}
         //else
         //{

           // ptimer->restart();

         //}

      //}

   }

   // auto waitSleep = m_timeWait;

   // const auto intervalTime = 100_ms;

   // auto [countDecisecondSleep, remainderDecisecondSleep] = waitSleep.count_and_remainder(intervalTime);

   // while (true)
   //{

   //   task_iteration();

   //   for (::collection::index i = 0; i < countDecisecondSleep; i++)
   //   {

   //      ::preempt(100_ms);

   //      if (!task_get_run())
   //      {

   //         break;

   //      }

   //   }

   //   ::preempt(remainderDecisecondSleep);

   //   if (!task_get_run())
   //   {

   //      break;

   //   }

   //   try
   //   {

   //      on_timer();

   //   }
   //   catch (...)
   //   {

   //   }

   //   if (!m_bPeriodic)
   //   {

   //      break;

   //   }

   //}

   ////m_bRunning = false;

   // clear_flag(e_flag_running);
}


void timer_handler::_handle_timers(::timer_map * ptimermap)
{

   auto itNext = ptimermap->begin();

   decltype(itNext) it; 

   ::pointer < ::timer > ptimer;
   ::e_timer etimer;

   while (task_get_run())
   {

     // task_run(m_timeResolution);

      it = itNext;

      if (ptimermap->is_empty())
      {

         break;

      }

      {

         _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

         if (it == ptimermap->end())
         {

            break;

         }

         ptimer = it->m_element2;
         etimer = it->m_element1;

         itNext = it + 1;

      }

      if (ptimer->should_call())
      {

         (*ptimer)(ptimer);

         {

            _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            auto itCurrent = ptimermap->find(etimer);

            if (itCurrent && itCurrent->element2() == ptimer)
            {

               if (ptimer->m_bRet)
               {

                  ptimermap->erase(itCurrent);

               }
               else
               {

                  ptimer->restart();

               }

            }

            // A callback can reenter the task loop and mutate the timer map.
            itNext = ptimermap->begin();

         }

      }

   }

   // auto waitSleep = m_timeWait;

   // const auto intervalTime = 100_ms;

   // auto [countDecisecondSleep, remainderDecisecondSleep] = waitSleep.count_and_remainder(intervalTime);

   // while (true)
   //{

   //   task_iteration();

   //   for (::collection::index i = 0; i < countDecisecondSleep; i++)
   //   {

   //      ::preempt(100_ms);

   //      if (!task_get_run())
   //      {

   //         break;

   //      }

   //   }

   //   ::preempt(remainderDecisecondSleep);

   //   if (!task_get_run())
   //   {

   //      break;

   //   }

   //   try
   //   {

   //      on_timer();

   //   }
   //   catch (...)
   //   {

   //   }

   //   if (!m_bPeriodic)
   //   {

   //      break;

   //   }

   //}

   ////m_bRunning = false;

   // clear_flag(e_flag_running);
}


// void procedure_timer::stop_procedure_timer()
//{
//
//    {
//
//       _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       if (is_task_set2())
//       {
//
//          set_finish();
//
//       }
//       else
//       {
//
//          destroy();
//
//       }
//
//    }
//
// }
//
//
// void procedure_timer::destroy()
//{
//
//    {
//
//       _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//       try
//       {
//
//          if (m_ptimera)
//          {
//
//             synchronouslock.unlock();
//
//             m_ptimera->erase_timer(this);
//
//             synchronouslock._lock();
//
//             m_ptimera.release();
//
//          }
//
//       }
//       catch (...)
//       {
//
//       }
//
//    }
//
//    ::timer::destroy();
//
//    ::task::destroy();
//
// }
//
//
//


timer_dispatch::timer_dispatch()
{


}


timer_dispatch::~timer_dispatch() {}


class ::timer_handler * timer_dispatch::get_timer_handler(const class ::time &time)
{

//   if (m_timer)
//   {

//      return m_ptimerhandlerDefault;

//   }

   auto ptimerhandler = session()->get_timer_handler(time);

   return ptimerhandler;

}


::timer_map *timer_dispatch::get_timer_map()
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   if (!m_ptimermap)
   {

      construct_newø(m_ptimermap);
   }

   return m_ptimermap;

}


::timer * timer_dispatch::set_timer(const ::e_timer & etimer, const class ::time &time,
                                            const ::timer_callback &callbackOptional, ::timer_handler *ptimerhandler)
{

   if (::is_null(ptimerhandler))
   {

      ptimerhandler = this->get_timer_handler(time);

   }

   ::timer_callback callback;

   if (!callbackOptional)
   {
      
      callback = this;

   }
   else
   {

      callback = callbackOptional;

   }  

   auto ptimer = ptimerhandler->add_timer(this, etimer, time, callback);

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   get_timer_map()->set_at(etimer, ptimer);

   return ptimer;

}


void timer_dispatch::kill_timer(const ::e_timer & etimer)
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   if (!m_ptimermap)
   {

      return;

   }

   auto it = m_ptimermap->find(etimer);

   if (!it)
   {

      return;

   }

   auto ptimer = it->element2();

   ptimer->cancel();

   m_ptimermap->erase(it);

}


::comparable_array_base < ::e_timer > timer_dispatch::all_timers_ids()
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   if (!m_ptimermap)
   {

      return {};

   }

   ::comparable_array_base < ::e_timer > etimera;

   for (auto & it : *m_ptimermap)
   {

      etimera.add(it.m_element1);

   }

   return etimera;

}


void timer_dispatch::erase_all_timers()
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto etimera = all_timers_ids();

   erase_timers(etimera);

}

void timer_dispatch::erase_timers(const ::comparable_array_base < ::e_timer > & etimera)
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   for (auto etimer : etimera)
   {

      kill_timer(etimer);

   }

}
