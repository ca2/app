#pragma once


#include "acme/primitive/primitive/payload.h"


template < typename SEQUENCE >
class sequence :
   virtual public ::element
{
public:


   pointer< sequencer < SEQUENCE > >      m_psequencer;
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






//template < typename OBJECT, typename TRANSPORT , typename SEQUENCE >
//SEQUENCE * asynchronous < OBJECT, TRANSPORT, SEQUENCE >::sequence()
//{
//
//   if (!m_pfuture)
//   {
//
//      acmesystem()->__construct_new(m_pfuture);
//       
//      m_pfuture->acmesystem() = acmesystem();
//
//      m_pfuture->m_p = this;
//
//   }
//
//   return m_pfuture;
//
//}




//template < typename TYPE >
//inline ::pointer<TYPE>property_object::__create_new()
//{
//
//   auto p = __new(TYPE);
//
//   p->initialize_matter(this);
//
//   return p;
//
//}


//#endif // __cplusplus_winrt
