// Created based on ca2 sequence theoric classed by
//     camilo on 2024-1007 17:40 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/handler/step.h"
class sequencer;
using sequencer_step =
::function < void(::sequencer & sequencer) >;

//class step_function :
//   virtual public step
//{
//public:
//
//
//   ::aggregate      m_aggregate;
//
//
//
//   step_function(const ::aggregate & aggregate) :
//      m_aggregate(aggregate)
//   {
//   }
//
//   
//   void aggregate(::sequence * psequence) override
//   {
//      m_aggregate(psequence);
//   }
//
////
////   virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity())
////   {
////
////      try
////      {
////
////         m_procedure();
////
////      }
////      catch (const ::exception & e)
////      {
////
////         return e.m_estatus;
////
////      }
////      catch (...)
////      {
////
////         return error_exception;
////
////      }
////
////      return ::success;
////
////   }
////
////
////   virtual void do_asynchronously()
////   {
////
////      ::platform::get()->system()->post_procedure([this]()
////         {
////
////            m_payloadResult = do_synchronously(5_s);
////            
////});
////
////   }
////
//
//   //inline SEQUENCE * get() { return this; }
//   //inline const SEQUENCE * get() const { return this; }
//
//   //sequence * then(const sequence_step < SEQUENCE > & function);
//
//   //sequence * then(const class time & time, const sequence_step < SEQUENCE > & function);
//
//
//
//};
//
//
//
//
//
//
////template < typename OBJECT, typename TRANSPORT , typename SEQUENCE >
////SEQUENCE * asynchronous < OBJECT, TRANSPORT, SEQUENCE >::sequence()
////{
////
////   if (!m_pfuture)
////   {
////
////      system()->__construct_new(m_pfuture);
////       
////      m_pfuture->system() = system();
////
////      m_pfuture->m_p = this;
////
////   }
////
////   return m_pfuture;
////
////}
//
//
//
//
////template < typename TYPE >
////inline ::pointer<TYPE>property_object::__create_new()
////{
////
////   auto p = __new TYPE();
////
////   p->initialize_matter(this);
////
////   return p;
////
////}
//
//
////#endif // __cplusplus_winrt
