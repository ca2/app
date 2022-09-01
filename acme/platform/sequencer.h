#pragma once


#include "acme/parallelization/synchronization_object.h"


template < typename SEQUENCE >
class sequencer :
   virtual public synchronization_object
{
public:


   __pointer(SEQUENCE)                             m_psequence;
   __pointer(manual_reset_event)                   m_pevent;
   array < sequence_step < SEQUENCE > >            m_stepa;

   
   sequencer();
   ~sequencer()
   {



   }


   ///void set_object(const TYPE & result, const ::e_status & estatus = ::success);
   //void set_status(const ::e_status & estatus = ::success);
   void on_sequence() override;
   void fork();


   sequence<SEQUENCE> * topic(const ::duration & duration = ::duration::infinite());


   virtual ::e_status wait(const class ::wait & wait = ::wait::infinite()) override;


   sequence<SEQUENCE> * then(const sequence_step < SEQUENCE > & step);

   sequence<SEQUENCE> * then(const ::duration& duration, const sequence_step < SEQUENCE > & step);

   
   virtual ::atom do_synchronously(const class ::wait & wait = ::wait::infinite())
   {
      
      return m_psequence->do_synchronously(wait);
      
   }


   virtual void do_asynchronously()
   {

      m_psequence->do_asynchronously();

   }


};



//sequence * sequence::then(const function & function)
//{
//
//   m_psequencer->then(function);
//
//   return this;
//
//}
//
//sequence * sequence::then(const ::duration & duration, const function & function);
//{
//
//   m_psequencer->then(duration, function);
//   return this;
//
//}

CLASS_DECL_ACME critical_section* get_sequence_critical_section();

CLASS_DECL_ACME void initialize_sequence_critical_section();

CLASS_DECL_ACME void finalize_sequence_critical_section();


//template < typename TYPE /*, typename TRANSPORT = ::transport < TYPE >, typename SEQUENCE = ::sequence < TYPE, TRANSPORT >*/ >
//class asynchronous :
//   virtual public matter
//{
//public:
//
//
//   __pointer(TYPE)          m_p;
//
//
//   //TYPE * ();
//
//
//};



