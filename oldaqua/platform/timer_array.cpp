#include "framework.h" // previously aqua/user/user.h


namespace aqua
{


   timer_array::timer_array()
   {

      m_bOk = true;

      defer_create_mutex();

   }


   timer_array::~timer_array()
   {

      m_bOk = false;

      delete_all_timers(); // besides virtual

   }


   bool timer_array::create_timer(uptr nIDEvent,UINT nEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      if(nEllapse < 800)
      {

//         string str;
//
//         str.Format("creating fast timer: %d\n", nEllapse);
//
//         ::output_debug_string(str);

      }

      sync_lock sl(mutex());

      if (!m_bOk)
      {

         return false;

      }

      delete_timer(nIDEvent);

      auto ptimer = __new(timer(this, nIDEvent, pfnTimer, pvoidData, mutex()));

      ptimer->set_context_thread(get_context_thread());

      ptimer->m_pcallback = this;

      m_map.set_at(nIDEvent, ptimer);

      //sl.unlock();

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

         delete_timer(nIDEvent);

      }

      return bOk;

   }


   bool timer_array::set_timer(uptr nIDEvent, UINT nEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      if (!create_timer(nIDEvent, nEllapse, pfnTimer, bPeriodic, pvoidData))
      {

         return false;

      }

      return true;

   }


   bool timer_array::delete_timer(uptr nIDEvent)
   {

      sync_lock sl(mutex());

      auto * ppair = m_map.plookup(nIDEvent);

      if (ppair == nullptr)
      {

         return true;

      }

      auto ptimer = ppair->element2();

      m_map.remove_key(nIDEvent);

      ptimer->finalize();

      return true;

   }


   bool timer_array::remove_timer(::timer * ptimer)
   {

      sync_lock sl(mutex());

      try
      {

         uptr nIDEvent = ptimer->m_nIDEvent;

         auto * ppair = m_map.plookup(nIDEvent);

         if (ppair == nullptr)
         {

            return true;

         }

         auto ptimerMapped = ppair->element2();

         if(ptimerMapped == ptimer)
         {

            m_map.remove_key(nIDEvent);

         }

      }
      catch(...)
      {

      }

      return true;

   }


   bool timer_array::timer_is_ok()
   {

      return m_bOk;

   }


   bool timer_array::on_timer(timer * ptimer)
   {

      if (!m_bOk)
      {

         delete_timer(ptimer->m_nIDEvent);

         return false;

      }

      _001OnTimer(ptimer);

      if(!ptimer->m_bPeriodic)
      {

         delete_timer(ptimer->m_nIDEvent);

         return false;

      }

      return true;

   }


   void timer_array::_001OnTimer(::timer * ptimer)
   {

      if (m_pcallback != nullptr)
      {

         m_pcallback->on_timer(ptimer);

      }

   }


   void timer_array::finalize()
   {

      m_bOk = false;

      delete_all_timers();

      ::timer_callback::finalize();

   }


   void timer_array::delete_all_timers()
   {

      {

         sync_lock sl(mutex());

         __keep(m_bOk, false);

         auto map = m_map;

         for (auto & pair : map)
         {

            auto ptimer = pair.element2();

            try
            {

               sync_lock sl(ptimer->mutex());

               ptimer->m_eobject -= e_object_success;

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

      //finalize();

      {

         sync_lock sl(mutex());

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


} // namespace user



