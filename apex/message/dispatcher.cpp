// Created by camilo on 2021-09-20 20:17 BRT 
#include "framework.h"
#include "dispatcher.h"


namespace message
{


   dispatcher::dispatcher()
   {

   }


   //dispatcher::dispatcher(::particle* pparticleHandleTarget, const ::function < void(::message::message *) > & functionHandler) :
   //   m_pparticleHandlerTarget(pparticleHandleTarget),
   //   m_functionHandler(functionHandler)
   //{

   //}


   //template < typename T1, typename T2 >
   //dispatcher(T1* p, void (T2::* pfn)(::message::message* pmessage))
   //{
   //
   //   //auto s = sizeof(pfn);
   //
   //   auto ptrptr = (byte*)&pfn;
   //
   //   m_chunkMemberFunction.assign(ptrptr + get_member_function_offset(), get_member_function_size());
   //
   //   ::function_pointer::operator = (::message::__handler([p, pfn](::message::message* pmessage)
   //      {
   //
   //         (p->*pfn)(pmessage);
   //
   //      }));
   //
   //   m_pparticleHandlerTarget = p;
   //
   //}
   //
   //
   //template < typename PREDICATE >
   //dispatcher(PREDICATE predicate)
   //{
   //
   //   ::pointer < ::particle >::operator = (__new(predicate_handler < PREDICATE >(predicate)));
   //
   //   m_pparticleHandlerTarget = m_p;
   //
   //}
   //

   dispatcher::dispatcher(const dispatcher& dispatcher) :
      m_pparticleHandlerTarget(dispatcher.m_pparticleHandlerTarget),
      m_functionHandler(dispatcher.m_functionHandler),
      m_chunkMemberFunction(dispatcher.m_chunkMemberFunction)
   {

   }


   dispatcher& dispatcher::operator = (const dispatcher& dispatcher)
   {

      if (this != &dispatcher)
      {

         m_pparticleHandlerTarget = dispatcher.m_pparticleHandlerTarget;

         m_functionHandler = dispatcher.m_functionHandler;

         m_chunkMemberFunction = dispatcher.m_chunkMemberFunction;

      }

      return *this;

   }


   bool dispatcher::operator == (const dispatcher& dispatcher) const
   {

      if (this == &dispatcher)
      {

         return true;

      }

      bool bSameHandler = m_pparticleHandlerTarget == dispatcher.m_pparticleHandlerTarget;

      bool bExactlySamePredicateHolder = m_functionHandler == dispatcher.m_functionHandler;

      bool bSameMemberIfSet = m_chunkMemberFunction.size() > 0 && m_chunkMemberFunction == dispatcher.m_chunkMemberFunction;

      return bSameHandler && (bExactlySamePredicateHolder || bSameMemberIfSet);

   }


} // namespace message


CLASS_DECL_APEX int get_member_function_size()
{

   return sizeof(void*);

}



CLASS_DECL_APEX int get_member_function_offset()
{

   return 0;

}

