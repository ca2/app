#pragma once

//
////namespace promise
////{
//
//
//   class sync_routine;
//
//
//   inline ::pointer<sync_routine>___sync_routine(const ::procedure & procedure);
//
//
//   class CLASS_DECL_ACME sync_routine :
//           public ::synchronization//   {
//   protected:
//
//      friend ::pointer<sync_routine>___sync_routine(const ::procedure &routine);
//
//
//      sync_routine(const ::procedure & procedure) :
//         m_procedure(routine)
//      {
//
//         __defer_construct(m_phappeningCompletion);
//
//      }
//
//
//   public:
//
//
//      routine                          m_procedure;
//      ::pointer<manual_reset_happening>   m_phappeningCompletion;
//      ::duration                       m_duration;
//      void                       m_estatus;
//
//
//      virtual ~sync_routine() {}
//
//
//      inline virtual void operator()() override
//      {
//
//         m_estatus = m_procedure();
//
//         m_phappeningCompletion->SetEvent();
//
//         return m_estatus;
//
//      }
//
//
//      virtual synchronization_result wait(const duration &durationTimeout) override
//      {
//
//         return m_phappeningCompletion->wait(durationTimeout);
//
//      }
//
//
//   };
//
//
//   inline ::pointer<sync_routine>___sync_routine(const ::procedure & procedure)
//   {
//
//      return __allocate sync_routine(routine);
//
//   }
//
//
////} // namespace promise
//
//
//
