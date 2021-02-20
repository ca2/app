#pragma once


namespace promise
{


   template<typename PRED>
   class predicate_sync_routine :
           virtual public ::matter
   {
   public:


      PRED                 m_predicate;
      manual_reset_event   m_ev;


      predicate_sync_routine(PRED pred) : m_predicate(pred) {}
      virtual ~predicate_sync_routine() {}


      virtual ::e_status run() override
      {

         m_predicate();

         m_ev.SetEvent();

         return ::success;

      }


      void sync_wait() override
      {

         m_ev.wait();

      }


      void sync_wait(const ::duration &duration) override
      {

         m_ev.wait();

      }


   };


} // namespace promise


template < typename PRED >
::promise::routine __sync_routine(PRED pred)
{

   return __new(::promise::predicate_sync_routine<PRED>(pred));

}
