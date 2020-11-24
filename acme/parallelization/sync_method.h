#pragma once


class sync_procedure;


inline ＿＿pointer(sync_procedure) ___sync_procedure(const procedure & procedure);


class CLASS_DECL_ACME sync_procedure :
   public ::sync
{
protected:


   friend ＿＿pointer(sync_procedure) ___sync_procedure(const procedure & procedure);


   sync_procedure(const procedure & procedure) :
      m_procedure(procedure)
   {

      ＿＿defer_construct(m_peventCompletion);

   }


public:


   procedure                              m_procedure;
   ＿＿pointer(manual_reset_event)          m_peventCompletion;
   ::duration                             m_duration;
   ::estatus                              m_estatus;


   virtual ~sync_procedure() {}
   

   inline virtual ::estatus operator()() override
   {

      m_estatus = m_procedure();

      m_peventCompletion->SetEvent();

      return m_estatus;

   }


   virtual sync_result wait(const duration& durationTimeout)
   {

      return m_peventCompletion->wait(durationTimeout);

   }


};



inline ＿＿pointer(sync_procedure) ___sync_procedure(const procedure & procedure)
{

   return ＿＿new(sync_procedure(procedure));

}