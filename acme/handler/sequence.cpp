#include "framework.h"
//#include s.h"
#include "sequence.h"
#include "acme/parallelization/synchronous_lock.h"

//
//::critical_section g_criticalsectionSequence;
//
//
//critical_section * get_sequence_critical_section()
//{
//
//
//   return &g_criticalsectionSequence;
//
//}
//

//void initialize_sequence_critical_section()
//{
//
//   if (!g_pcriticalsectionSequence)
//   {
//
//      g_pcriticalsectionSequence = ___new critical_section();
//
//   }
//
//}
//
//
//void finalize_sequence_critical_section()
//{
//
//   if (g_pcriticalsectionSequence)
//   {
//
//      delete g_pcriticalsectionSequence;
//
//      g_pcriticalsectionSequence = nullptr;
//
//   }
//
//}
//




//#include "acme/parallelization/synchronization.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/critical_section.h"
//#include "acme/user/user/conversation.h"
#include "acme/platform/application.h"
//#include "acme/handler/step_function.h"

//template < typename SEQUENCE >
//using sequence_step = ::function < void(SEQUENCE *) >;

#include "acme/prototype/collection/list.h"

//
////template < typename SEQUENCE >
//class sequencer :
//   virtual public ::list < ::pointer < step > >
//{
//public:


   //::payload                        m_payload;
   //::pointer< ::step >              m_pstepLast;
   //::pointer< ::step >              m_pstep;
   ////::collection::index              m_iStep;

//sequencer_payload::sequencer_payload(::sequencer & sequencer) :
//   m_sequencer(sequencer)
//
//{
//   //  m_iStep = 0;
//
//}
//
//sequencer_payload::~sequencer_payload()
//{
//
//
//
//}
//
//
//void sequencer_payload::on_initialize_particle()
//{
//
//   ::list < ::sequencer_step >::on_initialize_particle();
//
//   defer_create_synchronization();
//
//}
//
//
/////void set_object(const TYPE & result, const ::e_status & estatus = ::success);
////void set_status(const ::e_status & estatus = ::success);
//void sequencer_payload::run()
//{
//
//   m_estatus = ::success;
//
//   _synchronous_lock synchronouslock(this->synchronization());
//
//   do
//   {
//
//      if (!m_iterator)
//      {
//
//         m_iterator = this->begin();
//
//      }
//      else
//      {
//
//         m_iterator++;
//
//      }
//
//      if (!m_iterator || m_iterator == this->end())
//      {
//
//         break;
//
//      }
//
//      synchronouslock.unlock();
//
//      sequence_step();
//
//      synchronouslock._lock();
//
//   } while (m_estatus.ok());
//
//}
//
//
//::e_status sequencer_payload::do_step()
//{
//
//
//   try
//   {
//
//      _synchronous_lock synchronouslock(this->synchronization());
//
//      auto aggregator = *m_iterator;
//
//      synchronouslock.unlock();
//
//      aggregator(m_sequencer);
//
//   }
//   catch (const ::exception & e)
//   {
//
//      return e.m_estatus;
//
//   }
//   catch (...)
//   {
//
//      return error_exception;
//
//   }
//
//   return ::success;
//
//}
//
//void sequencer_payload::sequence_step()
//{
//
//   m_estatus = do_step();
//
//   //if (m_estatus.succeeded())
//   //{
//
//   //   m_iStep++;
//
//   //}
//
//}
//
////sequencer<SEQUENCE> * topic(const class time & timeWait = ::time::infinity());
//
//
////virtual ::payload run_with_timeout(const class time & timeWait = ::time::infinity()) override;
//void sequencer_payload::add_step(const ::sequencer_step & step)
//{
//
//   _synchronous_lock synchronouslock(synchronization());
//
//   add_tail(step);
//
//}
//
//
//
//
//
//void sequencer_payload::add_result(const ::payload & payload)
//{
//
//   _synchronous_lock synchronouslock(synchronization());
//   m_payload.payload_array_reference().add(payload);
//
//}
//
//::payload sequencer_payload::last_result()
//{
//   _synchronous_lock synchronouslock(synchronization());
//
//   if (m_payload.get_type() == e_type_payload_array)
//   {
//
//      if (m_payload.payload_array_reference().has_element())
//      {
//
//         return m_payload.payload_array_reference().last();
//
//      }
//
//   }
//
//   return m_payload;
//
//}

sequence::sequence() 
{

}
sequence::~sequence()
{


}

//
//::sequencer & sequencer::operator <<(const ::sequencer_step & step)
//{
//
//   m_p->add_step(step);
//
//   return *this;
//
//}
//
//
//void sequencer::add_result(const ::payload & payload)
//{
//
//   m_p->add_result(payload);
//
//}
//
//
//::payload sequencer::last_result()
//{
//   return m_p->last_result();
//
//}
//::sequencer & sequencer::then(enum_as, ::sequencer_step::base * psequenceaggregatorbase)
//{

//   add_tail({ transfer_t{}, psequenceaggregatorbase });

//   return *this;

//}


//::sequencer & sequencer::then(const ::sequencer_step & step)
//{

//   add_tail(step);

//   return *this;

//}



//sequencer<SEQUENCE> * then(const class time & time, const sequence_step < SEQUENCE > & step);


//::payload sequencer::do_synchronously(const class time & timeWait = ::time::infinity())
//{

//   call_run();

//   return m_payload;

//}


//virtual void do_asynchronously()
//{

//   m_psequence->do_asynchronously();

//}


//};




//sequencer * sequencer::then(const function & function)
//{
//
//   m_psequencer->then(function);
//
//   return this;
//
//}
//
//sequencer * sequencer::then(const class time & time, const function & function);
//{
//
//   m_psequencer->then(time, function);
//   return this;
//
//}

//CLASS_DECL_ACME critical_section* ::platform::get()->sequence_critical_section();

//CLASS_DECL_ACME void initialize_sequence_critical_section();
//
//CLASS_DECL_ACME void finalize_sequence_critical_section();


//template < typename TYPE /*, typename TRANSPORT = ::transport < TYPE >, typename SEQUENCE = ::sequencer < TYPE, TRANSPORT >*/ >
//class asynchronous :
//   virtual public matter
//{
//public:
//
//
//   ::pointer<TYPE>         m_p;
//
//
//   //TYPE * ();
//
//
//};




//template < typename SEQUENCE >
//sequencer < SEQUENCE > ::sequencer()
//{
//
//   //m_ptask = ::get_task();
//
//   m_phappening = nullptr;
//
//}


//template < typename TYPE >
//void future < RESULT > ::set_object(const RESULT& result, const ::e_status & estatus)
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   if (m_p.m_estatus == error_not_initialized)
//   {
//
//      m_p.m_estatus = estatus;
//
//      m_p.m_result = result;
//
//      if (m_phappening)
//      {
//
//         m_phappening->set_happening();
//
//      }
//
//      if (m_preceptor)
//      {
//
//         m_preceptor->get(this);
//
//      }
//
//   }
//
//}

//
//template < typename SEQUENCE >
//void sequencer < SEQUENCE > ::fork()
//{
//
//   fork(this, [this]()
//   {
//
//      on_sequence();
//
//   });
//
//}

//
//template < typename SEQUENCE >
//void sequencer < SEQUENCE > ::on_sequence()
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   if (m_phappening)
//   {
//
//      m_phappening->set_happening();
//
//   }
//
//   if(m_stepa.has_element())
//   {
//      
//      ::pointer < sequencer < SEQUENCE > > psequencer(this);
//
//      auto step = m_stepa.pop_first();
//
//      lock.unlock();
//
//      auto λ = [this, step, psequencer]
//      {
//
//         step(m_psequence);
//
//         psequencer->on_sequence();
//
//      };
//      
//      m_papplication->post_procedure(λ);
//
//   }
//   else 
//   {
//      
//      m_psequence.release();
//      
//   }
//
//}
//

//template < typename SEQUENCE >
//void sequencer < SEQUENCE > ::set_status(const ::e_status & estatus)
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   m_p.m_estatus = estatus;
//
//   if (m_phappening)
//   {
//
//      m_phappening->set_happening();
//
//   }
//
//   increment_reference_count();
//
//   system()->fork(__routine([this]()
//      {
//
//         auto pHold = ::pointer_transfer(this);
//
//         critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//         while (m_stepa.has_element())
//         {
//
//            auto pfunction = m_stepa.pop_first();
//
//            lock.unlock();
//
//            pfunction->process(*this);
//
//            lock.lock();
//
//         }
//
//      }));
//
//}


//
//template < typename SEQUENCE >
//sequencer < SEQUENCE > * sequencer < SEQUENCE > ::then(const sequence_step < SEQUENCE > & step)
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   if (m_psequence.is_set())
//   {
//
//      m_stepa.add(step);
//
//   }
//   else
//   {
//
//      lock.unlock();
//
//      step(m_psequence);
//
//   }
//
//   return m_psequence;
//
//}
//
//
//template < typename SEQUENCE >
//sequencer < SEQUENCE > * sequencer < SEQUENCE > ::then(const class time & timeWait, const sequence_step < SEQUENCE > & step)
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   if (m_psequence.m_estatus == error_not_initialized)
//   {
//
//      m_stepa.add(step);
//
//      m_phappening = __allocate manual_reset_happening();
//
//      lock.unlock();
//
//      if (!m_phappening->wait(timeWait))
//      {
//
//         lock.lock();
//
//         if (m_psequence.m_estatus == error_not_initialized)
//         {
//
//            m_psequence.m_estatus = error_timeout;
//
//         }
//
//         lock.unlock();
//
//         if (m_psequence.m_estatus == error_timeout)
//         {
//
//            step(m_psequence);
//
//         }
//
//      }
//
//   }
//   else
//   {
//
//      lock.unlock();
//
//      step(m_psequence);
//
//   }
//
//   return m_psequence;
//
//}
//
//
//template < typename SEQUENCE >
//sequencer < SEQUENCE > * sequencer < SEQUENCE > ::topic(const class time & timeWait)
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   if (m_psequence.m_estatus == error_not_initialized)
//   {
//
//      m_phappening = __allocate manual_reset_happening();
//
//      if (!m_phappening->wait(timeWait))
//      {
//
//         lock.lock();
//
//         if (m_psequence.m_estatus == error_not_initialized)
//         {
//
//            m_psequence.m_estatus = error_timeout;
//
//         }
//
//         lock.unlock();
//
//      }
//
//   }
//
//   return this->m_p;
//
//}
//
//
//template < typename SEQUENCE >
//::e_status sequencer < SEQUENCE > ::wait(const class time & timeWait)
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   if (m_psequence.m_estatus == error_not_initialized)
//   {
//
//      m_phappening = __allocate manual_reset_happening();
//
//      lock.unlock();
//
//      if (!m_phappening->wait(timeWait))
//      {
//
//         lock.lock();
//
//         if (m_psequence.m_estatus == error_not_initialized)
//         {
//
//            m_psequence.m_estatus = error_wait_timeout;
//
//         }
//
//         lock.unlock();
//
//      }
//
//   }
//
//   return m_psequence.m_estatus;
//
//}
//



//sequence * sequence::current()
//{
//
//   return dynamic_cast <sequence *>(task_context<sequence>::current());
//}
////inline [[noreturn]] static void cancel()
////{
////
////   throw ::cancel_exception<sequence>();
////
////}


void sequence::run()
{

   //stack_task_context_base stack(this);

   //procedure_array_with_context<sequence>::run();
   
   this->first()->call();
   
}


//void sequence::on_end_procedure()
//{
//   
//   m_pparticleLast = m_pparticle;
//
//}

void sequence::destroy()
{

   
   subparticle_array::destroy();
   
   
//   task_context<sequence>::destroy();
//   procedure_array_with_context<sequence>::destroy();
//   property_object::destroy();
   
}


//::payload sequence::get_last_result()
//{
//
//   if (!m_pparticleLast)
//   {
//      return {};
//
//   }
//   return m_pparticleLast->get_result_payload();
//}
//
//::payload get_last_result();


#if defined(DEBUG)

::huge_integer sequence::increment_reference_count()
{

   return ::subparticle_array::increment_reference_count();

}


::huge_integer sequence::decrement_reference_count()
{

   return ::subparticle_array::decrement_reference_count();

}

#endif

void sequence::on_subparticle_sequence(::subparticle * psubparticle)
{
 
   auto iFind = this->find_first(psubparticle);
   
   if(iFind < 0)
   {
    
      throw ::exception(error_wrong_state);
      
   }
   
   auto iNext = iFind + 1;
   
   if(iNext >= this->size())
   {
      
      on_end_of_sequence();
      
      return;
      
   }
   
   //m_payloadaResult.add(payload);
   
   auto p = this->element_at(iNext);
   
   if(p->m_psequence != this)
   {
      
      throw ::exception(error_wrong_state);
      
   }
   
   p->call();
   
}


void sequence::on_end_of_sequence()
{

   if (m_pmanualresethappeningOnEndOfSequence)
   {

      m_pmanualresethappeningOnEndOfSequence->set_happening();

   }

   ::subparticle_array::clear();
 
   release();
   
}


