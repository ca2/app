#pragma once


#include "acme/platform/procedure.h"


namespace parallelization
{


   class counter :
      virtual public ::particle
   {
   protected:


      ::procedure             m_procedureCompleted;


   public:


      interlocked_count       m_interlocked;


      counter(::collection::count c, const ::procedure & procedureCompleted) :
         m_interlocked(c),
         m_procedureCompleted(procedureCompleted)
      {


      }


      ::collection::count operator ++()
      {

         ::collection::count c = --m_interlocked;

         if (has_completed())
         {

            m_procedureCompleted();

         }

         return c;

      }


      ::collection::count operator ++(int)
      {

         ::collection::count c = m_interlocked;

         ++(*this);

         return c;

      }


      bool has_completed() const
      {

         return m_interlocked <= 0;

      }


   };


} // namespace parallelization



//class counter32 :
//   public manual_reset_happening
//{
//public:
//
//
//   interlocked_int      m_interlocked;
//
//
//   counter32(int lCount) : m_interlocked(lCount) {}
//
//
//   int operator ++()
//   {
//
//      int i = --m_interlocked;
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
//   int operator ++(int)
//   {
//
//      int i = m_interlocked;
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
