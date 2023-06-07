// From list by camilo on 2022-09-12 20:10 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/particle.h"
//#include "list_iterator.h"


template < class TYPE >
class list_node
{
public:


   using ITEM = TYPE;
   using ARG_ITEM = argument_of < TYPE >;

   using this_iterator = ::list_iterator < list_node < TYPE > * >;


   this_iterator     m_next;
   this_iterator     m_back;
   TYPE              m_element;


   list_node(ARG_ITEM t) :
      m_element(t)
   {

   }

   list_node(ITEM && t) :
      m_element(::transfer(t))
   {

   }

   operator TYPE & () { return m_element; }
   operator const TYPE & () const { return (const TYPE & ) m_element; }


   auto & back() { return m_back; }
   auto & back()const { return m_back; }

   auto & next() { return m_next; }
   auto & next()const { return m_next; }


   auto & item() { return m_element; }
   auto & item() const { return m_element; }

    
   auto & topic() { return m_element; }
   auto & topic() const { return m_element; }


   auto transfer_topic() { return ::transfer(m_element); }


   auto transfer() { return ::transfer(*this); }


};



