// Created by camilo on 2021-09-06 14:41 BRT <3ThomasBS_!!
#pragma once


template < primitive_integral INTEGRAL >
class set_bit
{
public:
   

   INTEGRAL &      m_field;
   INTEGRAL        m_mask;


   set_bit(INTEGRAL & field, INTEGRAL mask) :
      m_field(field), m_mask(mask) { }

   bool is_set() const { return (m_field & m_mask) == m_mask; }

   void set(bool bSet)
   {

      if (bSet)
      {

         set();

      }
      else
      {

         unset();

      }

   }

   void set()
   {

      if (is_set())
      {

         return;

      }

      m_field = (INTEGRAL) (((::u64) m_field) | ((::u64)m_mask));

   }

   void unset()
   {

      if (is_set())
      {

         return;

      }

      m_field = (INTEGRAL) (((::u64)m_field) & (~((::u64)m_mask)));

   }

};



