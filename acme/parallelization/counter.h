#pragma once


class counter :
   public manual_reset_event
{
public:


   interlocked_count      m_interlocked;


   counter(::count c) : m_interlocked(c) {}


   ::count operator ++()
   {

      ::count c = --m_interlocked;

      if (c <= 0)
      {

         SetEvent();

      }

      return c;

   }


   ::count operator ++(int)
   {

      ::count c = m_interlocked;

      ++(*this);

      return c;

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
