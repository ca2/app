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

   operator u32hash() const { return NODE::operator u32hash(); }

   //set_node(ARG_TYPE1 element1) :
   //   pair(element1)
   //{

   //}


   //set_node(ARG_TYPE1 element1, ARG_TYPE2 element2):
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
inline typename PAIR::TYPE2& payload_of(const set_node<PAIR>& pair)
{

   return (typename PAIR::TYPE2 &) pair.element2();

}



template <  typename TYPE >
inline ::pointer<TYPE>& payload_of(const ::pointer<TYPE> & p)
{

   return (::pointer<TYPE>&) p;

}


namespace std
{


   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_size< ::set_node < PAIR > > : integral_constant<size_t, 2> {};

   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_element< 0, set_node < PAIR > >
   {
      using type = typename ::set_node < PAIR >::TYPE1;
   };

   template < typename PAIR >
   ALIENATED_ANDROID_ANARCHY tuple_element< 1, set_node < PAIR > >
   {
      using type = typename ::set_node < PAIR >::TYPE2;
   };


} // namespace std



template < typename TYPE >
::index an_index_of(const set_node < TYPE > * p)
{

   return p->index();

}



template < typename TYPE >
TYPE * next_as_of_iterator(const set_node < TYPE > * p)
{

   return p->m_pnext;

}





