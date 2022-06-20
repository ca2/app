#pragma once


#include "acme/parallelization/synchronization_object.h"


template < typename TYPE >
class sequence :
   virtual public ::synchronization_object
{
public:


   class step :
      virtual public matter
   {
   public:


      virtual void process(class sequence& sequence) {}


   };


   template < typename OPERATION >
   class step_operation :
      virtual public step
   {
   public:


      OPERATION   m_operation;


      step_operation(OPERATION operation) :
         m_operation(operation)
      {

      }


      virtual void process(class sequence & sequence) override
      {

         m_operation(sequence);

      }

   };


   __pointer(TYPE)                        m_p;
   __pointer(manual_reset_event)          m_pevent;
   __pointer_array(step)                  m_stepa;

   
   sequence();
   ~sequence()
   {



   }


   ///void set_object(const TYPE & result, const ::e_status & estatus = ::success);
   //void set_status(const ::e_status & estatus = ::success);
   void on_sequence() override;
   void fork();


   TYPE & topic(const ::duration & duration = ::duration::infinite());


   ::e_status wait(const class ::wait & wait = ::wait::infinite()) override;


   template < typename OPERATION >
   sequence & then(OPERATION v);

   template < typename OPERATION >
   sequence& then(const ::duration& duration, OPERATION operation);

   auto operator ->() { return m_p.operator ->(); }
   auto operator ->() const { return m_p.operator ->(); }
   
   
//   virtual ::atom do_synchronously()
//   {
//      
//      return m_p->do_synchronously();
//      
//   }
   

};


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



