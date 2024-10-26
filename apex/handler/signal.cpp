// Extrapolation from merge with control_"topic" by camilo on day after ThomasBirthday2021 10:30!!
#include "framework.h"
#include "signal.h"
#include "manager.h"
#include "manager_room.h"
#include "context.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"


namespace handler
{

   signal::signal(const ::atom & atom, ::manager * pmanager) :
      m_pmanager(pmanager),
      ::topic(atom),
      ::extended_topic(atom)
   {

   }


   signal::~signal()
   {


   }


#ifdef _DEBUG


   i64 signal::increment_reference_count()
   {

      return ::topic::increment_reference_count();

   }


   i64 signal::decrement_reference_count()
   {

      return ::topic::decrement_reference_count();

   }


   i64 signal::release()
   {

      return ::topic::release();

   }


#endif




   //void signal::step()
   //{
   //
   //   auto ptask = ::get_task();
   //
   //   if (::manager::s_bDestroyAll || !ptask->task_get_run())
   //   {
   //
   //      return ::error_failed;
   //
   //   }
   //
   //   m_pmanager->signal(this);
   //
   //   return ::success;
   //
   //}


   //bool signal::is_modified()
   //{
   //
   //   return false;
   //
   //}


   void signal::run()
   {

      while (true)
      {

         bool bModified = is_modified();

         if (!bModified)
         {

            // fetch updated polling time
            auto iPollMillis = poll_time();

            if (!should_poll(iPollMillis))
            {

               break;

            }

            if (system()->manager_room()->may_run_signal_handling())
            {

               break;

            }

            ::preempt(iPollMillis);

            continue;

         }

         clear_modified();

         notify();

      }

      //return ::success;

   }


   void signal::notify()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for (auto & pair : m_signalhandlercontext)
      {

         auto & signalhandler = pair.m_element1;

         auto & pcontext = pair.m_element2;

         if (!pcontext)
         {

            pcontext = __allocate ::context();

         }

         //      if (pcontext->m_bFork)
         //      {
         //
         //         branch_element(pmatter);
         //
         //      }
         //      else
         //      {

         signalhandler(this, pcontext);

         //      }

      }

   }


   ::context * signal::listener_context(const ::signal_handler & signalhandler)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto & pcontext = m_signalhandlercontext[signalhandler];

      if (!pcontext)
      {

         pcontext = __allocate ::context();

      }

      return pcontext;

   }


   void signal::start_task()
   {

      //return ::success_none;

   }


   //void topic::reset_update(const ::atom & atom)
   //{
   //
   //
   //}
   //

   bool signal::is_up_to_date(const ::context * pcontext) const
   {

      if (::is_null(m_pmanager))
      {

         return false;

      }

      if (m_iUpdateSerial < 0)
      {

         return false;

      }

      return pcontext->is_up_to_date(this);

   }


   void signal::set_up_to_date(::context * pcontext)
   {

      pcontext->set_up_to_date(this);

   }


   void signal::add_handler(::matter * pmatter)
   {

      pmatter->destroying() += [this, pmatter]()
      {

         erase_signal_handler(::signal_handler(pmatter));

      };

      add_signal_handler(::signal_handler(pmatter));

   }


   void signal::add_signal_handler(const ::signal_handler & signalhandler)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      //bool bShouldFork = false;

      //if (m_matterchange.is_empty())
      //{

      //   if (should_poll(poll_millis()))
      //   {

      //      bShouldFork = true;

      //   }

      //}

      //if(m_iUpdateSerial < || >>= 0)
      //{

      //   bShouldFork = true;

      //}

      auto & pcontext = m_signalhandlercontext[signalhandler];

      if (!pcontext)
      {

         pcontext = __allocate ::context();

      }

      //pcontext->m_bFork = bForkWhenNotify;

      //pmatter->on_subject(this, pcontext);

   }


   void signal::erase_signal_handler(const ::signal_handler & signalhandler)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_signalhandlercontext.erase_item(signalhandler);

   }


   //void signal::erase_signal_handlers(::particle * pparticle)
   //{
   //
   //   _synchronous_lock synchronouslock(this->synchronization());
   //
   //   while(true)
   //   {
   //      
   //      auto p = m_signalhandlercontext.predicate_find(
   //                                                     [pparticle](auto & pair)
   //                                                     {
   //                                                        
   //                                                        return pair.m_element2.m_pbase == pparticle;
   //                                                        
   //                                                     });
   //    if(!p)
   //    {
   //       
   //       break;
   //       
   //    }
   //      
   //      m_signalhandlercontext.erase(p);
   //    
   //   }
   //
   //}


   void signal::set_modified()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_bModified = true;

      m_iUpdateSerial++;

      if (!should_poll(poll_time()))
      {

         fork([this]() {call(); });

      }

   }

   void signal::clear_modified()
   {

      m_bModified = false;

   }


   bool signal::is_modified() const
   {

      return m_bModified;

   }


   void signal::post_destroy_all()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_signalhandlercontext.erase_all();

   }


   class ::time signal::poll_time()
   {

      return system()->get_update_poll_time(m_atom);

   }


} // namespace handler





