#pragma once


#include "pair.h"
#include "list_iterator.h"


template < typename ITEM >
class set_node :
   public ITEM
{
public:


   using BASE_NODE = ::set_node < ITEM >;


   using BASE_ITEM = ITEM;


   using KEY = typename BASE_ITEM::KEY;
   using ARG_KEY = typename BASE_ITEM::ARG_KEY;
   using PAYLOAD = typename BASE_ITEM::PAYLOAD;
   using ARG_PAYLOAD = typename BASE_ITEM::ARG_PAYLOAD;


   BASE_NODE *          m_back;
   BASE_NODE *          m_next;
   BASE_NODE *          m_nextHash;
   BASE_NODE **         m_pbackHash;


   using BASE_ITEM::BASE_ITEM;


   void defer_set_payload(ARG_PAYLOAD payload)
   {

      BASE_ITEM::defer_set_payload(payload);

   }


   auto & back() { return m_back; }
   auto & back() const { return m_back; }

   auto & next() { return m_next; }
   auto & next() const { return m_next; }

   auto & item() { return *(BASE_ITEM *)this; }
   auto & item() const { return *(BASE_ITEM *)this; }

   auto & node() { return *this; }
   auto & node() const { return *this; }

   ::collection::index index() const
   {

      ::collection::index i = 0;

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
inline typename PAIR::TYPE2& payload_of(const set_node<PAIR>& pair)
{

   return (typename PAIR::TYPE2 &) pair.element2();

}



template <  typename TYPE >
inline ::pointer<TYPE>& payload_of(const ::pointer<TYPE> & p)
{

   return (::pointer<TYPE>&) p;

}




template < typename TYPE >
::collection::index an_index_of(const set_node < TYPE > * p)
{

   return p->index();

}



template < typename TYPE >
TYPE * next_as_of_iterator(const set_node < TYPE > * p)
{

   return p->m_pnext;

}





