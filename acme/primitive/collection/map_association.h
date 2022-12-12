#pragma once


#include "pair.h"
#include "list_iterator.h"


template < typename PAYLOAD >
class map_association :
   public PAYLOAD
{
public:


   using ITEM = map_association;
   using ITEM_POINTER = ITEM *;

   using iterator = ::list_iterator < ITEM_POINTER >;
   using const_iterator = ::const_list_iterator < ITEM_POINTER >;

   using payload = PAYLOAD;


   ITEM_POINTER         m_back;
   ITEM_POINTER         m_next;
   ITEM_POINTER         m_nextHash;
   ITEM_POINTER *       m_pbackHash;


   using PAYLOAD::PAYLOAD;

   //map_association()
   //{

   //}

   auto back() { return m_back; }
   auto back()const { return m_back; }

   auto next() { return m_next; }
   auto next()const { return m_next; }

   auto item() { return this; }
   auto item() const { return this; }

   //map_association(ARG_TYPE1 element1) :
   //   pair(element1)
   //{

   //}


   //map_association(ARG_TYPE1 element1, ARG_TYPE2 element2):
   //   pair(element1, element2)
   //{

   //}


   ::index index() const
   {

      ::index i = 0;

      auto p = m_back;

      while (*p)
      {

         i++;

         p++;

      }

      return i;

   }


};


template <  typename PAIR >
inline typename PAIR::TYPE2& __value(const map_association<PAIR>& pair)
{

   return (typename PAIR::TYPE2 &) pair.element2();

}



template <  typename TYPE >
inline ::pointer<TYPE>& __value(const ::pointer<TYPE> & p)
{

   return (::pointer<TYPE>&) p;

}


namespace std
{


   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::map_association < PAIR > > : integral_constant<size_t, 2> {};

   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_element< 0, map_association < PAIR > >
   {
      using type = typename ::map_association < PAIR >::TYPE1;
   };

   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_element< 1, map_association < PAIR > >
   {
      using type = typename ::map_association < PAIR >::TYPE2;
   };


} // namespace std



template < typename TYPE >
::index an_index_of(const map_association < TYPE > * p)
{

   return p->index();

}



template < typename TYPE >
TYPE * next_as_of_iterator(const map_association < TYPE > * p)
{

   return p->m_pnext;

}





