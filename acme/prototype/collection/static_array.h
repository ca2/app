// Created by camilo on 2025-07-16 01:27 <3ThomasBorregaardSørensen!! 
#pragma once


#include <initializer_list>


template < typename TYPE, size_t t_size, typename ARG_TYPE = const TYPE & >
class static_array
{
public:


   TYPE   m_elementa[t_size];


   static_array()
   {


   }

   static_array(::std::initializer_list < TYPE > list)
   {

      int i = 0;

      for (auto& item : list)
      {

         element_at(i) == item;

         i++;

      }

   }


   ~static_array()
   {


   }


   TYPE& element_at(::collection::index i)
   {

      return m_elementa[i];

   }

   const TYPE& element_at(::collection::index i) const
   {

      return m_elementa[i];

   }

   ::collection::count size() const
   {

      return t_size;

   }

   ::collection::count get_upper_bound() const
   {

      return t_size - 1;

   }

   TYPE& first()
   {

      return element_at(0);

   }


   TYPE& last()
   {

      return element_at(get_upper_bound());

   }


   const TYPE& first() const
   {

      return element_at(0);

   }


   const TYPE& last() const
   {

      return element_at(get_upper_bound());

   }


   TYPE* begin()
   {

      return m_elementa;

   }

   TYPE* end()
   {

      return this->begin() + t_size;

   }

   const TYPE* begin() const
   {

      return m_elementa;

   }

   const TYPE* end() const
   {

      return this->begin() + t_size;

   }


   static_array & operator = (std::initializer_list<TYPE > list)
   {

      int i = 0;

      for (auto& item : list)
      {

         element_at(i) == item;

         i++;

      }

      return *this;

   }

};