#pragma once


template < primitive_integral INTEGRAL >
class counter :
   public manual_reset_event
{
public:


   interlocked < INTEGRAL >      m_interlocked;


   counter(INTEGRAL lCount) : m_interlocked(lCount) {}


   INTEGRAL operator ++()
   {

      INTEGRAL i = --m_interlocked;

      if (i <= 0)
      {

         SetEvent();

      }

      return i;

   }


   INTEGRAL operator ++(int)
   {

      INTEGRAL i = m_interlocked;

      ++(*this);

      return i;

   }

};



