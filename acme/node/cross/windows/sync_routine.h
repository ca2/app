#pragma once


namespace promise
{


   class sync_routine;


   inline __pointer(sync_routine) ___sync_routine(const ::routine & routine);


   class CLASS_DECL_ACME sync_routine :
           public ::synchronization_object
   {
   protected:

      friend __pointer(sync_routine) ___sync_routine(const ::routine &routine);


      sync_routine(const ::routine & routine) :
         m_routine(routine)
      {

         __defer_construct(m_peventCompletion);

      }


   public:


      routine                          m_routine;
      __pointer(manual_reset_event)    m_peventCompletion;
      ::duration                       m_duration;
      ::e_status                        m_estatus;


      virtual ~sync_routine() {}


      inline virtual ::e_status operator()() override
      {

         m_estatus = m_routine();

         m_peventCompletion->SetEvent();

         return m_estatus;

      }


      virtual synchronization_result wait(const duration &durationTimeout) override
      {

         return m_peventCompletion->wait(durationTimeout);

      }


   };


   inline __pointer(sync_routine) ___sync_routine(const ::routine & routine)
   {

      return __new(sync_routine(routine));

   }


} // namespace promise



