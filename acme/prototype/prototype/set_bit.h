// Created by camilo on 2021-09-06 14:41 BRT <3ThomasBS_!!
#pragma once


template < typename ENUM >
class set_bit
{
public:


   using TYPE = raw_enum_of<ENUM>;
   

   TYPE &         m_field;
   huge_natural          m_mask;


   set_bit(TYPE & field, huge_natural mask) :
      m_field(field), m_mask(mask) { }

   bool is_set() const { return ((huge_natural)m_field & m_mask) == m_mask; }

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

      m_field = (TYPE) (((huge_natural) m_field) | ((huge_natural)m_mask));

   }

   void unset()
   {

      if (is_set())
      {

         return;

      }

      m_field = (TYPE) (((huge_natural)m_field) & (~((huge_natural)m_mask)));

   }

};



