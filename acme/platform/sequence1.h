#pragma once


template < typename SEQUENCE >
using sequence_step = ::function < void(SEQUENCE *) >;


template < typename SEQUENCE >
class sequence :
   virtual public ::element
{
public:


   __pointer(sequencer < SEQUENCE >)      m_psequencer;
   ::payload                              m_payloadResult;


   virtual ::payload do_synchronously(const class ::wait & wait = ::wait::infinite())
   {

      return {};

   }


   virtual void do_asynchronously()
   {


   }


   //inline SEQUENCE * get() { return this; }
   //inline const SEQUENCE * get() const { return this; }

   //sequence * then(const sequence_step < SEQUENCE > & function);

   //sequence * then(const ::duration & duration, const sequence_step < SEQUENCE > & function);



};
