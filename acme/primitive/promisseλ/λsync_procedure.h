#pragma once


template < typename PRED >
class λsync_procedure :
   virtual public ::matter
{
public:


   PRED                       m_pred;
   manual_reset_event         m_ev;


   λsync_procedure(PRED pred) : m_pred(pred) { }
   virtual ~λsync_procedure() {}


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
procedure ＿＿sync_procedure(PRED pred)
{

   return ＿＿new(λsync_procedure<PRED>(pred));

}
