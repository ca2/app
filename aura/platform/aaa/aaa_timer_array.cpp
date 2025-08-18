#include "framework.h" // previously aura/user/user.h


namespace aura
{


   timer_array::timer_array()
   {

      m_bOk = true;

      defer_create_synchronization();

   }


   timer_array::~timer_array()
   {

      m_bOk = false;

      delete_all_timers(); // besides virtual

   }


   bool timer_array::create_timer(uptr uEvent,unsigned int nEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      if(nEllapse < 800)
      {

//         string str;
//
//         str.formatf("creating fast timer: %d\n", nEllapse);
//
//         ::information(str);

      }

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_bOk)
      {

         return false;

      }

      delete_timer(uEvent);

      auto ptimer = øallocate timer(this, uEvent, pfnTimer, pvoidData, mutex());

      ptimer->set_context_thread(get_context_thread());

      ptimer->m_pcallback = this;

      m_map.set_at(uEvent, ptimer);

      //synchronouslock.unlock();

      bool bOk = true;

      try
      {

         if(!ptimer->start(nEllapse,bPeriodic))
         {

            bOk = false;

         }

      }
      catch(...)
      {

         bOk = false;

      }

      if(!bOk)
      {

         delete_timer(uEvent);

      }

      return bOk;

   }


   bool timer_array::set_timer(uptr uEvent, unsigned int nEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      if (!create_timer(uEvent, nEllapse, pfnTimer, bPeriodic, pvoidData))
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

      ptimer->set_finish();

      return true;

   }


   bool timer_array::erase_timer(::timer * ptimer)
   {

      synchronous_lock synchronouslock(this->synchronization());

      try
      {

         uptr uEvent = ptimer->m_uTimer;

         auto * ppair = m_map.plookup(uEvent);

         if (ppair == nullptr)
         {

            return true;

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

      return true;

   }


   bool timer_array::e_timer_is_ok()
   {

      return m_bOk;

   }


   bool timer_array::on_timer(timer * ptimer)
   {

      if (!m_bOk)
      {

         delete_timer(ptimer->m_uTimer);

         return false;

      }

      on_timer(ptimer);

      if(!ptimer->m_bPeriodic)
      {

         delete_timer(ptimer->m_uTimer);

         return false;

      }

      return true;

   }


   void timer_array::on_timer(::timer * ptimer)
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

   }


   void timer_array::delete_all_timers()
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         KEEP(m_bOk, false);

         auto map = m_map;

         for (auto & pair : map)
         {

            auto ptimer = pair.element2();

            try
            {

               synchronous_lock synchronouslock(ptimer->mutex());

               ptimer->clear(e_flag_success);

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

      //destroy();

      {

         synchronous_lock synchronouslock(this->synchronization());

         KEEP(m_bOk, false);

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


} // namespace user



