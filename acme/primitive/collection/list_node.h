// From list by camilo on 2022-09-12 20:10 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/particle.h"
#include "list_iterator.h"


template < class TYPE, class ARG_TYPE >
class list_node
{
public:


   using ITEM = TYPE;

   using iterator = ::list_iterator < list_node < TYPE, ARG_TYPE > * >;


   iterator          m_next;
   iterator          m_back;
   TYPE              m_element;


   list_node(ARG_TYPE t, iterator back, iterator next) :
      m_element(t), m_back(back), m_next(next)
   {

   }


   auto & back() { return m_back; }
   auto & back()const { return m_back; }

   auto & next() { return m_next; }
   auto & next()const { return m_next; }


   auto item() { return &m_element; }
   auto item() const { return &m_element; }

    
   auto & element() { return m_element; }
   auto & element() const { return m_element; }

};



