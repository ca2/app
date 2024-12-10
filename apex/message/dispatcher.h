#pragma once


#include "predicate_handler.h"
#include "acme/memory/chunk.h"
#include "acme/prototype/collection/atom_map.h"
//#include "acme/prototype/prototype/function.h"

//#include "acme/prototype/prototype/pointer.h"


CLASS_DECL_APEX int get_member_function_offset();
CLASS_DECL_APEX int get_member_function_size();




namespace message
{


   class CLASS_DECL_APEX dispatcher :
      virtual public ::particle
   {
   public:


      ::cast < ::particle >                        m_pparticleHandlerTarget;
      ::function < void(::message::message *) >    m_functionHandler;
      chunk                                        m_chunkMemberFunction;


      dispatcher();

      //dispatcher(::particle* pparticleHandleTarget, const ::function < void(::message::message *) > & functionHandler);

      template < typename T1, typename T2 >
      dispatcher(T1 * pparticleHandlerTarget, void (T2:: * pfnHandlerFunction)(::message::message * pmessage))
      {

         auto ptrptr = (unsigned char*)&pfnHandlerFunction;

         m_chunkMemberFunction.assign(ptrptr + get_member_function_offset(), get_member_function_size());

         m_functionHandler = 
            [pparticleHandlerTarget, pfnHandlerFunction](::message::message* pmessage)
            {

               (pparticleHandlerTarget->*pfnHandlerFunction)(pmessage);

            };

         m_pparticleHandlerTarget = pparticleHandlerTarget;

      }

      template < typename FUNCTION >
      dispatcher(FUNCTION function)
      {

         m_functionHandler = function;

      }


      dispatcher(const dispatcher& dispatcher);
      ~dispatcher() override;


      dispatcher& operator = (const dispatcher& dispatcher);
      bool operator == (const dispatcher& dispatcher) const;

   };


   using dispatcher_array = ::array < dispatcher >;


   using dispatcher_map = ::atom_map < dispatcher_array >;

   
} // namespace message



