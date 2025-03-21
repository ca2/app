#pragma once



//#include "acme/prototype/prototype/pointer.h"


namespace message
{


   template < typename PREDICATE >
   class predicate_handler :
      virtual public ::particle
   {
   public:


      PREDICATE m_predicate;


      predicate_handler(PREDICATE predicate) : m_predicate(predicate) { }
      ~predicate_handler() override{}


      virtual void handle_message(::message::message * pmessage) override
      {

         m_predicate(pmessage);

      }


   };


   template < typename PREDICATE >
   ::particle_pointer __handler(PREDICATE predicate) 
   {

      return __allocate predicate_handler<PREDICATE> (predicate);

   }


} // namespace message



