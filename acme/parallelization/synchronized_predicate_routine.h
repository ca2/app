#pragma once


#include "acme/primitive/promise/signalization.h"


namespace parallelization
{



   class CLASS_DECL_ACME synchronizer :
      virtual public signalization
   {
   public:


      manual_reset_event   m_evGoingToWrite;
      manual_reset_event   m_evResponse;


      //synchronization(PRED pred) : m_predicate(pred) {}
      synchronization()  { }
      virtual ~synchronization() {}

//
//      virtual void run() override
//      {
//
//         m_predicate();
//
//         m_ev.SetEvent();
//
//         return ::success;
//
//      }
//


//      virtual void run() override
//      {
//
//         m_evWriting.SetEvent();
//
//         return ::success;
//
//      }


//      synchronization_result sync_wait() override
//      {
//
//         auto result = m_ev.wait();
//
//         return result;
//
//      }
//
//
//      synchronization_result sync_wait(const ::duration &duration) override
//      {
//
//         auto result = m_ev.wait();
//
//         return result;
//
//      }
//

   };




} // namespace promise

//
//template < typename PRED >
//auto __sync_routine(PRED pred)
//{
//
//   return __new(::promise::predicate_sync_routine<PRED>(pred));
//
//}

//
//template < typename PRED >
//::procedure __sync_payload_routine(::matter * pmatter, PRED pred)
//{
//
//   auto proutine = __new(::promise::predicate_sync_routine<PRED>(pred));
//
//   return {pmatter, proutine};
//
//}
