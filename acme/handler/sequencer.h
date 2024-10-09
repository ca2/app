// Deeply refactored by camilo on 2024-10-07 07:24 <3ThomasBorregaardSorensen!!
#pragma once

//enum enum_as
//{
//   as
//};

//#include "acme/parallelization/synchronization.h"
//#include "acme/parallelization/manual_reset_event.h"
//#include "acme/parallelization/critical_section.h"
//#include "acme/user/user/conversation.h"
//#include "acme/platform/context.h"
//#include "acme/handler/step_function.h"
//#include "acme/handler/aggregate.h"
//template < typename SEQUENCE >
//using sequence_step = ::function < void(SEQUENCE *) >;

#include "acme/prototype/collection/list.h"


class sequencer_payload :
   virtual public ::list < ::sequencer_step >
{
public:


   ::payload                                    m_payload;
   ::list < ::sequencer_step >::iterator        m_iterator;
   ::sequencer &                                m_sequencer;
   //::pointer< ::particle >          m_pparticleLast;
   //::pointer< ::particle >          m_pparticle;
   //::collection::index              m_iStep;
   
   sequencer_payload(::sequencer & sequencer);

   ~sequencer_payload();


   void on_initialize_particle();


   virtual void add_result(const ::payload & payload);


   ///void set_object(const TYPE & result, const ::e_status & estatus = ::success);
   //void set_status(const ::e_status & estatus = ::success);
   void run() override;
   ::e_status do_step();

   virtual void sequence_step();

   void add_step(const ::sequencer_step & step);

   //::sequencer & operator << (enum_as, ::sequence_aggregator::base * psequenceaggregatorbase);
   
   //::sequence & then(const ::sequence_aggregator & step);

   //::sequencer & then(enum_as, ::sequence_aggregator::base * psequenceaggregatorbase);

   //::sequencer & then(const ::sequence_aggregator & step);

   //virtual void do_asynchronously()
   //{

   //   m_psequence->do_asynchronously();

   //}
   virtual ::payload last_result();

};

class sequencer :
   public ::pointer < sequencer_payload >
{
public:

   sequencer(::particle * pparticle);


   ::sequencer & operator << (const ::sequencer_step & step);

   
   ::payload last_result();

   void add_result(const ::payload & payload);

};

//sequence * sequence::then(const function & function)
//{
//
//   m_psequencer->then(function);
//
//   return this;
//
//}
//
//sequence * sequence::then(const class time & time, const function & function);
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


//template < typename TYPE /*, typename TRANSPORT = ::transport < TYPE >, typename SEQUENCE = ::sequence < TYPE, TRANSPORT >*/ >
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
//   m_pevent = nullptr;
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
//      if (m_pevent)
//      {
//
//         m_pevent->SetEvent();
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
//   if (m_pevent)
//   {
//
//      m_pevent->SetEvent();
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
//      m_pcontext->post_procedure(λ);
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
//   if (m_pevent)
//   {
//
//      m_pevent->SetEvent();
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
//sequence < SEQUENCE > * sequencer < SEQUENCE > ::then(const sequence_step < SEQUENCE > & step)
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
//sequence < SEQUENCE > * sequencer < SEQUENCE > ::then(const class time & timeWait, const sequence_step < SEQUENCE > & step)
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   if (m_psequence.m_estatus == error_not_initialized)
//   {
//
//      m_stepa.add(step);
//
//      m_pevent = __new manual_reset_event();
//
//      lock.unlock();
//
//      if (!m_pevent->wait(timeWait))
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
//sequence < SEQUENCE > * sequencer < SEQUENCE > ::topic(const class time & timeWait)
//{
//
//   critical_section_lock lock(::platform::get()->sequence_critical_section());
//
//   if (m_psequence.m_estatus == error_not_initialized)
//   {
//
//      m_pevent = __new manual_reset_event();
//
//      if (!m_pevent->wait(timeWait))
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
//      m_pevent = __new manual_reset_event();
//
//      lock.unlock();
//
//      if (!m_pevent->wait(timeWait))
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
