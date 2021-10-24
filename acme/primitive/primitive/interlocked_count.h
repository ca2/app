#pragma once


#include "acme/primitive/primitive/atomic.h"


class CLASS_DECL_ACME interlocked_i64
{
protected:


   char                         m_sz[(sizeof(::i64) + 7) & ~7];
   ::i64 *                      m_plong;


public:


   interlocked_i64(::i64 l = 0)
   {  

      m_plong = (::i64 *) (((::iptr)this + 7) & ~7);

      *m_plong = l;


   }


   interlocked_i64 & operator = (::i64 i);

   operator ::i64() const { return *m_plong; }


   ::i64 operator++();
   ::i64 operator--();
   ::i64 operator++(int);
   ::i64 operator--(int);

   interlocked_i64 & operator+=(::i64 l);
   interlocked_i64 & operator-=(::i64 l);

   
};


class CLASS_DECL_ACME interlocked_i32
{
protected:


   char                       m_sz[(sizeof(::i32) + 7) & ~7];
   ::i32 *         m_plong;


public:


   interlocked_i32(::i32 l = 0)
   {

      m_plong = (::i32 *) (((iptr)this + 7) & ~7);

      *m_plong = l;


   }


   interlocked_i32 & operator = (::i32 i);

   operator ::i32() const { return *m_plong; }


   interlocked_i32 & operator++();
   interlocked_i32 & operator--();
   ::i32 operator++(int);
   ::i32 operator--(int);

   interlocked_i32 & operator+=(::i32 l);
   interlocked_i32 & operator-=(::i32 l);

   
};



#if defined(WINDOWS) && OSBIT == 32

using interlocked_count = ::interlocked_i32;

#else

using interlocked_count = ::interlocked_i64;

#endif





inline interlocked_i32 & interlocked_i32::operator++()
{

   atomic_increment(m_plong);

   return *this;

}


inline interlocked_i32 & interlocked_i32::operator--()
{

   atomic_decrement(m_plong);

   return *this;

}


inline ::i32 interlocked_i32::operator++(int)
{

  auto l = *m_plong;

  atomic_increment(m_plong);

  return l;

}


inline ::i32 interlocked_i32::operator--(int)
{

  auto l = *m_plong;

  atomic_decrement(m_plong);

  return l;

}





inline ::i64 interlocked_i64::operator++()
{

   return atomic_increment(m_plong);

}


inline ::i64 interlocked_i64::operator--()
{

   return atomic_decrement(m_plong);

}


inline ::i64 interlocked_i64::operator++(int)
{

  auto l = *m_plong;

  atomic_increment(m_plong);

  return l;

}


inline ::i64 interlocked_i64::operator--(int)
{

  auto l = *m_plong;

  atomic_decrement(m_plong);

  return l;

}



