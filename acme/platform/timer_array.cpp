#include "framework.h"
#include "timer_task.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/keep.h"


namespace acme
{


   timer_array::timer_array()
   {

      m_bOk = true;

      defer_create_synchronization();

   }


   timer_array::~timer_array()
   {

      m_bOk = false;

      delete_all_timers();

   }


   bool timer_array::create_timer(::particle * pparticle, uptr uEvent, const class ::time& millisEllapse, const ::procedure& procedure, bool bPeriodic)
   {

      delete_timer(uEvent);

      ::pointer < ::timer_task > ptimer;
      
      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (!m_bOk)
         {

            return false;

         }

         ptimer = __allocate timer_task();

         ptimer->m_ptimercallback = this;

         m_timermap[uEvent] = ptimer;

      }

      ptimer->initialize_timer(pparticle, this, uEvent, procedure, synchronization());

      bool bOk = true;

      ptimer->start_timer_task(millisEllapse, bPeriodic);

      return bOk;

   }


   bool timer_array::set_timer(::particle * pparticle, uptr uEvent, const class ::time& millisEllapse, const ::procedure& procedure, bool bPeriodic)
   {

      if (!create_timer(pparticle, uEvent, millisEllapse, procedure, bPeriodic))
      {

         return false;

      }

      return true;

   }


   bool timer_array::delete_timer(uptr uEvent)
   {

      ::pointer<::timer_task > ptimer;

      {

         _synchronous_lock synchronouslock(this->synchronization());

         auto iterator = m_timermap.find(uEvent);

         if (!iterator)
         {

            return true;

         }

         ptimer = iterator->payload();

         m_timermap.erase(iterator);

      }

      ptimer->stop_timer_task();

      return true;

   }


   void timer_array::erase_timer(::timer * ptimer)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      try
      {

         uptr uTimer = ptimer->m_uTimer;

         auto iterator = m_timermap.find(uTimer);

         if (!iterator)
         {

            return;

         }

         auto ptimerMapped = iterator->payload();

         if(ptimerMapped == ptimer)
         {

            m_timermap.erase(iterator);

         }

      }
      catch(...)
      {

      }

   }


   bool timer_array::e_timer_is_ok()
   {

      return m_bOk;

   }


   void timer_array::call_on_timer(timer * ptimer)
   {

      if (!m_bOk)
      {

         delete_timer(ptimer->m_uTimer);

         return;

      }

      on_timer(ptimer);

      if(!ptimer->m_bPeriodic)
      {

         delete_timer(ptimer->m_uTimer);

         return;

      }

      //return true;

   }


   void timer_array::on_timer(::timer * ptimer)
   {

      if (m_pcallback != nullptr)
      {

         m_pcallback->call_on_timer(ptimer);

      }

   }


   void timer_array::destroy()
   {

      m_bOk = false;

      delete_all_timers();

      ::timer_callback::destroy();

      //return ::success;

   }


   void timer_array::delete_all_timers()
   {

      {

         KEEP(m_bOk, false);

         decltype(m_timermap) map_base;

         {

            _synchronous_lock synchronouslock(this->synchronization());

            map_base = m_timermap;

         }

         for (auto & pair : map_base)
         {

            auto ptimer = pair.element2();

            try
            {

               _synchronous_lock _synchronouslockTimer(ptimer->synchronization());

               ptimer->clear_flag(e_flag_success);

               if(!ptimer->m_bHandling)
               {

                  _synchronouslockTimer.unlock();

                  delete_timer(pair.element1());

               }

            }
            catch(...)
            {

            }

         }

      }

      {

         KEEP(m_bOk, false);

         decltype(m_timermap) map_base;

         {

            _synchronous_lock synchronouslock(this->synchronization());

            map_base = m_timermap;

         }

         for (auto & pair : map_base)
         {

            try
            {

               delete_timer(pair.element1());

            }
            catch(...)
            {

            }

         }

      }

   }


} // namespace acme



