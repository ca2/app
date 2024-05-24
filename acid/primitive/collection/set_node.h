#pragma once


#include "pair.h"
#include "list_iterator.h"


template < typename NODE >
class set_node :
   public NODE
{
public:


   using ITEM = typename NODE::ITEM;
   using ARG_ITEM = typename NODE::ARG_ITEM;


   using node = NODE;


   set_node *        m_back;
   set_node *        m_next;
   set_node *        m_nextHash;
   set_node **       m_pbackHash;


   using NODE::NODE;


   auto & back() { return m_back; }
   auto & back() const { return m_back; }

   auto & next() { return m_next; }
   auto & next() const { return m_next; }

   auto & item() { return NODE::item(); }
   auto & item() const { return NODE::item(); }

   auto & topic() { return *this; }
   auto & topic() const { return *this; }

   //operator ::u32() const { return NODE::operator u32(); }

   //set_node(ARG_TYPE1 element1) :
   //   pair(element1)
   //{

   //}


   //set_node(ARG_TYPE1 element1, ARG_TYPE2 element2):
   //   pair(element1, element2)
   //{

   //}


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





