#pragma once


class counter64 :
   public manual_reset_event
{
public:


   interlocked_i64      m_interlocked;


   counter64(::i64 lCount) : m_interlocked(lCount) {}


   ::i64 operator ++()
   {

      ::i64 i = --m_interlocked;

      if (i <= 0)
      {

         SetEvent();

      }

      return i;

   }


   ::i64 operator ++(int)
   {

      ::i64 i = m_interlocked;

      ++(*this);

      return i;

   }

};


class counter32 :
   public manual_reset_event
{
public:


   interlocked_i32      m_interlocked;


   counter32(::i32 lCount) : m_interlocked(lCount) {}


   ::i32 operator ++()
   {

      ::i32 i = --m_interlocked;

      if (i <= 0)
      {

         SetEvent();

      }

      return i;

   }


   ::i32 operator ++(int)
   {

      ::i32 i = m_interlocked;

      ++(*this);

      return i;

   }

};



