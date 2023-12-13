// Created by camilo on 2023-11-22 12:47 <3ThomasBorregaardSorensen
#pragma once


#include "acme/memory/::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate.h"


// currently simple_array doesn't call any constructors/destructors on elements
template < typename T >
class simple_array
{
public:

   T* m_p;
   int m_c;
   int m_cAlloc;


   simple_array() { m_p = nullptr; m_c = 0; m_cAlloc = 0; }
   ~simple_array() { if (m_p) ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(m_p); m_p = nullptr; m_c = 0; m_cAlloc = 0; }

   void allocate_for_size(int s)
   {

      if (s > m_cAlloc)
      {

         m_cAlloc = s + 8;

         auto pNew = (T*)::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->allocate(m_cAlloc * sizeof(T));

         memory_copy(pNew, m_p, m_c * sizeof(T));

         ::acme::get()->m_pheapmanagement->memory(::heap::e_memory_main)->free(m_p);

         m_p = pNew;

      }

   }

   void add(const T& t)
   {

      allocate_for_size(m_c + 1);

      ::new (m_p + m_c) T(t);

      m_c++;

   }

   void erase_at(::index i)
   {

      memory_transfer(m_p + i, m_p + i + 1, (m_c - i - 1) * sizeof(T));

      m_c--;

   }

};


template < typename T >
bool erase_first(simple_array < T >& a, const T& t)
{

   for (::index i = 0; i < a.m_c; i++)
   {

      if (a.m_p[i] == t)
      {

         a.erase_at(i);

         return true;

      }

   }

   return false;

}




