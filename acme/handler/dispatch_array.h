// Created based on ca2 sequence theoric classed by
//     camilo on 2024-1007 17:40 <3ThomasBorregaardSorensen!!
#pragma once
#include "prototype/collection/procedure_array.h"


class sequence;

#include "acme/prototype/prototype/function.h"

//
//
////#include "acme/handler/step.h"
//class sequencer;
//using sequencer_step =
//::function < void(::sequencer & sequencer) >;
//
////class step_function :
////   virtual public step
////{
////public:
////
////
////   ::aggregate      m_aggregate;
////
////
////
////   step_function(const ::aggregate & aggregate) :
////      m_aggregate(aggregate)
////   {
////   }
////
////   
////   void aggregate(::sequence * psequence) override
////   {
////      m_aggregate(psequence);
////   }
////
//////
//////   virtual ::payload do_synchronously(const class time & timeWait = ::time::infinity())
//////   {
//////
//////      try
//////      {
//////
//////         m_procedure();
//////
//////      }
//////      catch (const ::exception & e)
//////      {
//////
//////         return e.m_estatus;
//////
//////      }
//////      catch (...)
//////      {
//////
//////         return error_exception;
//////
//////      }
//////
//////      return ::success;
//////
//////   }
//////
//////
//////   virtual void do_asynchronously()
//////   {
//////
//////      system()->post_procedure([this]()
//////         {
//////
//////            m_payloadResult = do_synchronously(5_s);
//////            
//////});
//////
//////   }
//////
////
////   //inline SEQUENCE * get() { return this; }
////   //inline const SEQUENCE * get() const { return this; }
////
////   //sequence * then(const sequence_step < SEQUENCE > & function);
////
////   //sequence * then(const class time & time, const sequence_step < SEQUENCE > & function);
////
////
////
////};
////
////
////
////
////
////
//////template < typename OBJECT, typename TRANSPORT , typename SEQUENCE >
//////SEQUENCE * asynchronous < OBJECT, TRANSPORT, SEQUENCE >::sequence()
//////{
//////
//////   if (!m_pfuture)
//////   {
//////
//////      system()->construct_newø(m_pfuture);
//////       
//////      m_pfuture->system() = system();
//////
//////      m_pfuture->m_p = this;
//////
//////   }
//////
//////   return m_pfuture;
//////
//////}
////
////
////
////
//////template < typename TYPE >
//////inline ::pointer<TYPE>property_object::øcreate_new()
//////{
//////
//////   auto p = allocateø TYPE();
//////
//////   p->initialize_matter(this);
//////
//////   return p;
//////
//////}
////
////
//////#endif // __cplusplus_winrt


using particle_pointer = ::pointer <  ::particle  >;



class CLASS_DECL_ACME dispatch_array2 :
   virtual public ::procedure_array
{
public:


   
   //::procedure                                  m_procedure;
   //::pointer < sequence >                       m_psequence;
   ::cast < ::particle >                        m_pparticleDispatcher;
   enum_dispatch                                m_edispatch;
   

   //dispatch_array2(::particle * pparticleDispatcher, enum_dispatch edispatch);
   dispatch_array2(::particle * pparticleDispatcher, enum_dispatch edispatch);
   //sequence_continuation(::particle * pparticleTarget, enum_dispatch edispatch, const ::procedure & procedure, bool bCreateSequence = false);
   dispatch_array2(::particle * pparticleDispatcher, enum_dispatch edispatch, const ::procedure &procedure);
   dispatch_array2(const dispatch_array2 & dispatcha);



   dispatch_array2 & operator << (const ::procedure & procedure);


   ~dispatch_array2();


   void run() override;


   void dispatch_this();


};




class CLASS_DECL_ACME dispatch_arrayø :
   virtual public ::dispatch_array2
{
public:


   using  dispatch_array2::dispatch_array2;


   ~dispatch_arrayø()
   {

      try
      {

         dispatch_this();

      }
      catch (...)
      {

      }

   }


};





// class CLASS_DECL_ACME post_dispatch_array :
//    public dispatch_arrayø
// {
// public:
//
//
//    post_dispatch_array(::particle * pparticleDispatcher) : dispatch_arrayø(pparticleDispatcher, e_dispatch_post) {}
//    post_dispatch_array(::particle * pparticleDispatcher, const::procedure & procedure) : dispatch_arrayø(pparticleDispatcher, e_dispatch_post, procedure) {}
//    post_dispatch_array & operator << (const ::procedure & procedure)
//    {
//       dispatch_arrayø::operator <<(procedure);
//       return *this;
//    }
//
// };
//
//
// class CLASS_DECL_ACME send_dispatch_array :
//    public dispatch_arrayø
// {
// public:
//
//
//    send_dispatch_array(::particle * pparticleDispatcher) : dispatch_arrayø(pparticleDispatcher, e_dispatch_send) {}
//    send_dispatch_array(::particle * pparticleDispatcher, const::procedure & procedure) : dispatch_arrayø(pparticleDispatcher, e_dispatch_send, procedure) {}
//    send_dispatch_array & operator << (const ::procedure & procedure)
//    {
//       dispatch_arrayø::operator <<(procedure);
//       return *this;
//    }
//
// };