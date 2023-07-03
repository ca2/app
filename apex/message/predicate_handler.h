#pragma once



//#include "acme/primitive/primitive/pointer.h"


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


      virtual void handle(::message::message * pmessage) override
      {

         m_predicate(pmessage);

      }


   };


   template < typename PREDICATE >
   ::pointer < ::particle > __handler(PREDICATE predicate) 
   {

      return __new(predicate_handler<PREDICATE>(predicate));

   }


} // namespace message



