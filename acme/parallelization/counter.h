#pragma once


#include "acme/platform/procedure.h"


class counter :
   virtual public ::element
{
protected:

   
   ::procedure             m_procedureCompleted;


public:


   interlocked_count       m_interlocked;


   counter(::count c, const ::procedure & procedureCompleted) : 
      m_interlocked(c),
      m_procedureCompleted(procedureCompleted)
   {
   
   
   }


   ::count operator ++()
   {

      ::count c = --m_interlocked;

      if (has_completed())
      {

         m_procedureCompleted();

      }

      return c;

   }


   ::count operator ++(int)
   {

      ::count c = m_interlocked;

      ++(*this);

      return c;

   }


   bool has_completed() const
   {

      return m_interlocked <= 0;

   }


};


//class counter32 :
//   public manual_reset_event
//{
//public:
//
//
//   interlocked_i32      m_interlocked;
//
//
//   counter32(::i32 lCount) : m_interlocked(lCount) {}
//
//
//   ::i32 operator ++()
//   {
//
//      ::i32 i = --m_interlocked;
//
//      if (i <= 0)
//      {
//
//         SetEvent();
//
//      }
//
//      return i;
//
//   }
//
//
//   ::i32 operator ++(int)
//   {
//
//      ::i32 i = m_interlocked;
//
//      ++(*this);
//
//      return i;
//
//   }
//
//};
//
//
//
