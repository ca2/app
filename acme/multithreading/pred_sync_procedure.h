#pragma once


template < typename PRED >
class pred_sync_procedure :
   virtual public ::matter
{
public:


   PRED                       m_pred;
   manual_reset_event         m_ev;


   pred_sync_procedure(PRED pred) : m_pred(pred) { }
   virtual ~pred_sync_procedure() {}


   virtual ::estatus run() override
   {

      m_pred();

      m_ev.SetEvent();

      return ::success;

   }


   void sync_wait() override
   {

      m_ev.wait();

   }


   void sync_wait(const ::duration & duration) override
   {

      m_ev.wait();

   }


};




template < typename PRED >
procedure __sync_procedure(PRED pred)
{

   return __new(pred_sync_procedure<PRED>(pred));

}
