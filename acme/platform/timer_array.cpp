#include "framework.h"
#include "timer_task.h"
#include "acme/parallelization/synchronous_lock.h"


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


   bool timer_array::create_timer(::particle * pparticle, uptr uEvent, const class ::time& millisEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_bOk)
      {

         return false;

      }

      delete_timer(uEvent);

      auto ptimer = __new(timer_task);

      ptimer->initialize_timer(pparticle, this, uEvent, pfnTimer, pvoidData, synchronization());

      ptimer->m_ptimercallback = this;

      //m_pcallback->add_composite(ptimer OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      bool bOk = true;

      //try
      //{

         ptimer->start(millisEllapse, bPeriodic);

         //if(!)
         //{

         //   bOk = false;

         //}

      //}
      //catch(...)
      //{

        // bOk = false;

      //}

      //if(!bOk)
      //{

      //   delete_timer(uEvent);

      //}

      return bOk;

   }


   bool timer_array::set_timer(::particle * pparticle, uptr uEvent, const class ::time& millisEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      if (!create_timer(pparticle, uEvent, millisEllapse, pfnTimer, bPeriodic, pvoidData))
      {

         return false;

      }

      return true;

   }


   bool timer_array::delete_timer(uptr uEvent)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto * ppair = m_map.plookup(uEvent);

      if (ppair == nullptr)
      {

         return true;

      }

      auto ptimer = ppair->element2();

      m_map.erase_key(uEvent);

      ptimer->destroy();

      return true;

   }


   void timer_array::erase_timer(::timer * ptimer)
   {

      synchronous_lock synchronouslock(this->synchronization());

      try
      {

         uptr uEvent = ptimer->m_uEvent;

         auto * ppair = m_map.plookup(uEvent);

         if (ppair == nullptr)
         {

            return;

         }

         auto ptimerMapped = ppair->element2();

         if(ptimerMapped == ptimer)
         {

            m_map.erase_key(uEvent);

         }

      }
      catch(...)
      {

      }

      //return true;

   }


   bool timer_array::e_timer_is_ok()
   {

      return m_bOk;

   }


   void timer_array::on_timer(timer * ptimer)
   {

      if (!m_bOk)
      {

         delete_timer(ptimer->m_uEvent);

         return;

      }

      _001OnTimer(ptimer);

      if(!ptimer->m_bPeriodic)
      {

         delete_timer(ptimer->m_uEvent);

         return;

      }

      //return true;

   }


   void timer_array::_001OnTimer(::timer * ptimer)
   {

      if (m_pcallback != nullptr)
      {

         m_pcallback->on_timer(ptimer);

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

         synchronous_lock synchronouslock(this->synchronization());

         __keep(m_bOk, false);

         auto map = m_map;

         for (auto & pair : map)
         {

            auto ptimer = pair.element2();

            try
            {

               synchronous_lock synchronouslock(ptimer->synchronization());

               ptimer->clear_flag(e_flag_success);

               if(!ptimer->m_bHandling)
               {

                  delete_timer(pair.element1());

               }

            }
            catch(...)
            {

            }

         }

      }

      {

         synchronous_lock synchronouslock(this->synchronization());

         __keep(m_bOk, false);

         auto map = m_map;

         for (auto & pair : map)
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



