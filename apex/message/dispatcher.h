#pragma once


CLASS_DECL_APEX int get_member_function_offset();
CLASS_DECL_APEX int get_member_function_size();


namespace message
{


   class CLASS_DECL_APEX dispatcher :
      public ::function_pointer
   {
   public:


      ::matter_pointer           m_phandlerTarget;
      chunk                      m_chunkMemberFunction;


      dispatcher() { }

      dispatcher(::matter * phandlerTarget, ::matter * phandlerFunction) :
         m_phandlerTarget(phandlerTarget),
         ::function_pointer(phandlerFunction)
      {

      }
      

      template < typename T1, typename T2 >
      dispatcher(T1 * p, void (T2:: * pfn)(::message::message * pmessage))
      {

         //auto s = sizeof(pfn);

         auto ptrptr = (byte*)&pfn;

         m_chunkMemberFunction.assign(ptrptr + get_member_function_offset(), get_member_function_size());

         ::function_pointer::operator = (::message::__handler([p, pfn](::message::message * pmessage)
            {

               (p->*pfn)(pmessage);

            }));

         m_phandlerTarget = p;

      }


      template < typename PREDICATE >
      dispatcher(PREDICATE predicate)
      {

         ::function_pointer::operator = (__new(predicate_handler < PREDICATE >(predicate)));

         m_phandlerTarget = m_p;

      }


      dispatcher(const dispatcher & dispatcher) :
         m_phandlerTarget(dispatcher.m_phandlerTarget),
         ::function_pointer(dispatcher),
         m_chunkMemberFunction(dispatcher.m_chunkMemberFunction)
      {

      }


      dispatcher & operator = (const dispatcher & dispatcher)
      {

         if (this != &dispatcher)
         {
          
            m_phandlerTarget = dispatcher.m_phandlerTarget;

            ::function_pointer::operator=(dispatcher.m_p);

            m_chunkMemberFunction = dispatcher.m_chunkMemberFunction;

         }

         return *this;

      }


      bool operator == (const dispatcher & dispatcher) const
      {

         if (this == &dispatcher)
         {

            return true;

         }

         bool bSameHandler = m_phandlerTarget == dispatcher.m_phandlerTarget;

         bool bExactlySamePredicateHolder = m_p == dispatcher.m_p;

         bool bSameMemberIfSet = m_chunkMemberFunction.size() > 0 && m_chunkMemberFunction == dispatcher.m_chunkMemberFunction;

         return bSameHandler && (bExactlySamePredicateHolder || bSameMemberIfSet);

      }


   };


   using dispatcher_array = ::array < dispatcher >;


   using dispatcher_map = ::id_map < dispatcher_array >;

   
} // namespace message



