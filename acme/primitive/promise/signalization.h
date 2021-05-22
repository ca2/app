//
// Created by camilo on 25/04/2021. ~08:00 <3Thomas Borregaard Sørensen
//
#pragma once


namespace promise
{


   class CLASS_DECL_ACME signalization :
      virtual public ::material_object
   {
      public:


      manual_reset_event m_evReady;


   //synchronization(PRED pred) : m_predicate(pred) {}

#ifdef _DEBUG
      signalization();
      virtual ~signalization();
#else
      signalization() {}
      virtual ~signalization() {}
#endif

   //
   //      virtual ::e_status run() override
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


   //      virtual ::e_status run() override
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



