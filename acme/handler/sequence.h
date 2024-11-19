// Deeply refactored by camilo on 2024-10-07 07:24 <3ThomasBorregaardSorensen!!
// More deep refactoring merging post_procedure_continuation by
//   camilo on 2024-10-09 11:31 <3ThomasBorregaardSorensen!!
// post_procedure_continuation
//  camilo on 2024-10-08 08:45 <3ThomasBorregaardSorensen!!
#pragma once


//struct continuation_t {};

using particle_pointer = ::pointer <  ::particle  >;
//template < typename CONTEXT_TYPE >
//class procedure_array_with_context;

class sequence;
// Deeply refactored by camilo on 2024-10-07 07:24 <3ThomasBorregaardSorensen!!
// More deep refactoring merging post_procedure_continuation by
//   camilo on 2024-10-09 11:31 <3ThomasBorregaardSorensen!!
// post_procedure_continuation
//  camilo on 2024-10-08 08:45 <3ThomasBorregaardSorensen!!
#pragma once


using particle_pointer = ::pointer <  ::particle  >;
template < typename CONTEXT_TYPE >
class procedure_array_with_context;
//struct continuation_t {};
#include "acme/parallelization/task_context.h"

//class task_context_base :
//   virtual public ::particle
//{
//public:
//
//   ::pointer <task_context_base> m_pParent;
//
//   inline static thread_local ::pointer <task_context_base> t_pRoot;
//   static task_context_base * current() { return t_pRoot; }
//   void push()
//   {
//
//      auto pNewParent = t_pRoot;
//
//      t_pRoot = this;
//
//      t_pRoot->m_pParent = pNewParent;
//
//   }
//
//
//   void pop()
//   {
//
//      auto pParent = t_pRoot->m_pParent;
//
//      t_pRoot = pParent;
//
//   }
//
//};
//
//class stack_task_context_base
//{
//public:
//   task_context_base * m_p;
//
//   stack_task_context_base(task_context_base * p) :
//      m_p(p)
//   {
//      m_p->push();
//
//   }
//
//   ~stack_task_context_base()
//   {
//
//      m_p->pop();
//
//      m_p = nullptr;
//   }
//
//};
//
//template < typename CONTEXT_TYPE >
//class task_context :
//   virtual public ::task_context_base
//{
//public:
//
//   task_context()
//   {
//
//   }
//   ~task_context() override
//   {
//
//   }
//
//};

class CLASS_DECL_ACME sequence :
   virtual public ::subparticle_array
   //virtual public procedure_array_with_context<sequence>,
   //virtual public property_object
{
public:

   //::particle_pointer m_pparticleLast;
   //::particle_pointer m_pparticle;
   ::pointer < manual_reset_happening > m_pmanualresethappeningOnEndOfSequence;
   
   sequence();
   ~sequence() override;
   

#if defined(DEBUG)

   ::huge_integer increment_reference_count() override;
   ::huge_integer decrement_reference_count() override;

#endif


   virtual void on_subparticle_sequence(::subparticle * psubparticle);
   
//   static sequence * current();
//   [[noreturn]] inline static void cancel()
//   {
//
//      throw ::cancel_exception<sequence>();
//
//   }
   void run() override;
//   ::payload get_last_result();
//   void on_end_procedure() override;
   void destroy() override;
   
   
   virtual void on_end_of_sequence();
   
   
};
//
//
//template < typename TARGET_TYPE >
//class CLASS_DECL_ACME sequence_continuation
//{
//public:
//
//   ::procedure                m_procedure;
//   ::pointer < sequence >                       m_psequence;
//   ::pointer < TARGET_TYPE >                    m_ptarget;
//   void (TARGET_TYPE:: *)(const ::procedure &)  m_pfnSequencer;
//
//
//   sequence_continuation(TARGET_TYPE * pparticleTarget, void (TARGET_TYPE:: *)(const ::procedure &) pfn);
//   sequence_continuation(::particle * pparticleTarget, const ::procedure & procedure);
//   sequence_continuation & operator << (const ::procedure & procedure);
//   ~sequence_continuation();
//
//};

//#pragma once

//enum enum_as
//{
//   as
//};

//#include "acme/parallelization/synchronization.h"
//#include "acme/parallelization/manual_reset_happening.h"
//#include "acme/parallelization/critical_section.h"
//#include "acme/user/user/conversation.h"
//#include "acme/platform/application.h"
//#include "acme/handler/step_function.h"
//#include "acme/handler/aggregate.h"
//template < typename SEQUENCE >
//using sequence_step = ::function < void(SEQUENCE *) >;
//
//#include "acme/prototype/collection/list.h"

//
//class sequencer_payload :
//   virtual public ::list < ::sequencer_step >
//{
//public:
//
//
//   ::payload                                    m_payload;
//   ::list < ::sequencer_step >::iterator        m_iterator;
//   ::sequencer & m_sequencer;
//   //::pointer< ::particle >          m_pparticleLast;
//   //::pointer< ::particle >          m_pparticle;
//   //::collection::index              m_iStep;
//
//   sequencer_payload(::sequencer & sequencer);
//
//   ~sequencer_payload();
//
//
//   void on_initialize_particle();
//
//
//   virtual void add_result(const ::payload & payload);
//
//
//   ///void set_object(const TYPE & result, const ::e_status & estatus = ::success);
//   //void set_status(const ::e_status & estatus = ::success);
//   void run() override;
//   ::e_status do_step();
//
//   virtual void sequence_step();
//
//   void add_step(const ::sequencer_step & step);
//
//   //::sequencer & operator << (enum_as, ::sequence_aggregator::base * psequenceaggregatorbase);
//
//   //::sequence & then(const ::sequence_aggregator & step);
//
//   //::sequencer & then(enum_as, ::sequence_aggregator::base * psequenceaggregatorbase);
//
//   //::sequencer & then(const ::sequence_aggregator & step);
//
//   //virtual void do_asynchronously()
//   //{
//
//   //   m_psequence->do_asynchronously();
//
//   //}
//   virtual ::payload last_result();
//
//};

//class sequencer :
//   public ::pointer < sequencer_payload >
//{
//public:
//
//   sequencer(::particle * pparticle);
//
//
//   ::sequencer & operator << (const ::sequencer_step & step);
//
//
//   ::payload last_result();
//
//   void add_result(const ::payload & payload);
//
//};

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
//sequence < SEQUENCE > * sequencer < SEQUENCE > ::topic(const class time & timeWait)
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



//#pragma once

//enum enum_as
//{
//   as
//};

//#include "acme/parallelization/synchronization.h"
//#include "acme/parallelization/manual_reset_happening.h"
//#include "acme/parallelization/critical_section.h"
//#include "acme/user/user/conversation.h"
//#include "acme/platform/application.h"
//#include "acme/handler/step_function.h"
//#include "acme/handler/aggregate.h"
//template < typename SEQUENCE >
//using sequence_step = ::function < void(SEQUENCE *) >;

//#include "acme/prototype/collection/list.h"
//
//
//class sequencer_payload :
//   virtual public ::list < ::sequencer_step >
//{
//public:
//
//
//   ::payload                                    m_payload;
//   ::list < ::sequencer_step >::iterator        m_iterator;
//   ::sequencer &                                m_sequencer;
//   //::pointer< ::particle >          m_pparticleLast;
//   //::pointer< ::particle >          m_pparticle;
//   //::collection::index              m_iStep;
//   
//   sequencer_payload(::sequencer & sequencer);
//
//   ~sequencer_payload();
//
//
//   void on_initialize_particle();
//
//
//   virtual void add_result(const ::payload & payload);
//
//
//   ///void set_object(const TYPE & result, const ::e_status & estatus = ::success);
//   //void set_status(const ::e_status & estatus = ::success);
//   void run() override;
//   ::e_status do_step();
//
//   virtual void sequence_step();
//
//   void add_step(const ::sequencer_step & step);
//
//   //::sequencer & operator << (enum_as, ::sequence_aggregator::base * psequenceaggregatorbase);
//   
//   //::sequence & then(const ::sequence_aggregator & step);
//
//   //::sequencer & then(enum_as, ::sequence_aggregator::base * psequenceaggregatorbase);
//
//   //::sequencer & then(const ::sequence_aggregator & step);
//
//   //virtual void do_asynchronously()
//   //{
//
//   //   m_psequence->do_asynchronously();
//
//   //}
//   virtual ::payload last_result();
//
//};
//
//class sequencer :
//   public ::pointer < sequencer_payload >
//{
//public:
//
//   sequencer(::particle * pparticle);
//
//
//   ::sequencer & operator << (const ::sequencer_step & step);
//
//   
//   ::payload last_result();
//
//   void add_result(const ::payload & payload);
//
//};

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
//sequence < SEQUENCE > * sequencer < SEQUENCE > ::topic(const class time & timeWait)
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

