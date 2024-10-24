#pragma once


#include "atomic.h"


#if OSBIT == 64

// memory must be aligned
class INLINE_CLASS_DECL_ACME interlocked_i64
{
protected:


   //char                 m_sz[16];
   //::i64 *              m_plong;
   ::i64                   m_i64;


public:



   inline interlocked_i64(::i64 i = 0);


   inline interlocked_i64& operator = (::i64 i);


   inline operator ::i64() const;


   inline ::i64 operator++();
   inline ::i64 operator--();
   inline ::i64 operator++(int);
   inline ::i64 operator--(int);

   inline interlocked_i64& operator+=(::i64 l);
   inline interlocked_i64& operator-=(::i64 l);


   inline ::i64 as_integer() const { return m_i64;}
   
};


#endif


// memory must be aligned
class INLINE_CLASS_DECL_ACME interlocked_i32
{
protected:


   //char                 m_sz[8];
   //::i32 *              m_plong;
   ::i32                   m_i32;


public:


   inline interlocked_i32(::i32 i = 0);

   inline interlocked_i32& operator = (::i32 i);
   
   inline operator ::i32() const;


   inline interlocked_i32 & operator++();
   inline interlocked_i32 & operator--();
   inline ::i32 operator++(int);
   inline ::i32 operator--(int);


   inline interlocked_i32& operator+=(::i32 l);
   inline interlocked_i32& operator-=(::i32 l);


   inline ::i32 as_integer() const { return m_i32;}


};


#if OSBIT == 32

using interlocked_count = ::interlocked_i32;

#else

using interlocked_count = ::interlocked_i64;

#endif


#if OSBIT == 64


inline interlocked_i64::interlocked_i64(::i64 i) :
   m_i64(i)
{

}


inline interlocked_i64& interlocked_i64::operator = (::i64 i)
{

   atomic_assign64(&m_i64, i);

   return *this;

}


inline interlocked_i64::operator ::i64() const
{

   return m_i64;

}


inline ::i64 interlocked_i64::operator++()
{

   return atomic_increment64(&m_i64);

}


inline ::i64 interlocked_i64::operator--()
{

   return atomic_decrement64(&m_i64);

}


inline ::i64 interlocked_i64::operator++(int)
{

   auto i = m_i64;

   atomic_increment64(&m_i64);

   return i;

}


inline ::i64 interlocked_i64::operator--(int)
{

   auto i = m_i64;

   atomic_decrement64(&m_i64);

   return i;

}


inline interlocked_i64& interlocked_i64::operator+=(::i64 i)
{

   atomic_add64(&m_i64, i);

   return *this;

}


inline interlocked_i64& interlocked_i64::operator-=(::i64 i)
{

   atomic_subtract64(&m_i64, i);

   return *this;

}



#endif



//inline void interlocked_i32::construct(::i32 l)
//{
//
//   m_plong = (::i32*)(((iptr)m_sz + 7) & ~7);
//
//   *m_plong = l;
//
//}


inline interlocked_i32::interlocked_i32(::i32 i) :
   m_i32(i)
{

   //construct(l);

}


inline interlocked_i32& interlocked_i32::operator = (::i32 i)
{

   atomic_assign32(&m_i32, i);

   return *this;

}


inline interlocked_i32::operator ::i32() const
{

   return m_i32;

}


inline interlocked_i32& interlocked_i32::operator++()
{

   atomic_increment32(&m_i32);

   return *this;

}


inline interlocked_i32& interlocked_i32::operator--()
{

   atomic_decrement32(&m_i32);

   return *this;

}


inline ::i32 interlocked_i32::operator++(int)
{

   auto i = m_i32;

   atomic_increment32(&m_i32);

   return i;

}


inline ::i32 interlocked_i32::operator--(int)
{

   auto i = m_i32;

   atomic_decrement32(&m_i32);

   return i;

}


inline interlocked_i32& interlocked_i32::operator+=(::i32 i)
{

   atomic_add32(&m_i32, i);

   return *this;

}


inline interlocked_i32& interlocked_i32::operator-=(::i32 l)
{

   atomic_subtract32(&m_i32, l);

   return *this;

}



