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


      ::collection::count operator ++(::i32)
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
//         set_happening();
//
//      }
//
//      return i;
//
//   }
//
//
//   ::i32 operator ++(::i32)
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
