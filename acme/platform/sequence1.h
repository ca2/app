#pragma once


//#include "acme/primitive/primitive/payload.h"


template < typename SEQUENCE >
class sequence :
   virtual public ::particle
{
public:


   pointer< sequencer < SEQUENCE > >      m_psequencer;
   ::payload                              m_payloadResult;


   virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity())
   {

      return {};

   }


   virtual void do_asynchronously()
   {


   }


   //inline SEQUENCE * get() { return this; }
   //inline const SEQUENCE * get() const { return this; }

   //sequence * then(const sequence_step < SEQUENCE > & function);

   //sequence * then(const class time & time, const sequence_step < SEQUENCE > & function);



};






//template < typename OBJECT, typename TRANSPORT , typename SEQUENCE >
//SEQUENCE * asynchronous < OBJECT, TRANSPORT, SEQUENCE >::sequence()
//{
//
//   if (!m_pfuture)
//   {
//
//      system()->__construct_new(m_pfuture);
//       
//      m_pfuture->system() = system();
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
//   auto p = ::place(new TYPE());
//
//   p->initialize_matter(this);
//
//   return p;
//
//}


//#endif // __cplusplus_winrt
