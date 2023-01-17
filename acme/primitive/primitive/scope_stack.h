//
// Created by camilo on 2022-10-23 09:24 <3ThomasBorregaardSørensen!!
//
#pragma once


template < typename T >
class scope_stack
{
public:


   T & m_reference;
   T m_tPrevious;


   scope_stack(T& reference, const T& tStack) :
      m_reference(reference)
   {

      m_tPrevious = reference;

      reference = tStack;

   }


   ~scope_stack()
   {

      m_reference = m_tPrevious;

   }


};


#define __scope_stack(xxxx, aaaa) auto stack_at_line ## LINE_NUMBER = ::scope_stack < ::erase_reference< decltype(xxxx) >::TYPE > (xxxx, aaaa);



