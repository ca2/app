//
// Created by camilo on 2024-10-25 00:28 <3ThomasBorregaardSorensen!!
//
#pragma once



template < typename TYPE >
class cast
{
public:

   TYPE * m_p;

   template < typename TYPE2 >
   cast(const TYPE2 * p2)
   {

      m_p = dynamic_cast < TYPE  *>((TYPE2 *)(p2));

   }


   operator TYPE *()
   {

      return m_p;

   }

   TYPE * operator ->()
   {

      return m_p;

   }

   TYPE & operator *()
   {

      return *m_p;

   }

};

