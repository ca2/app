#pragma once


#include "atomic.h"


#if OSBIT == 64

// memory must be aligned
class INLINE_CLASS_DECL_ACME interlocked_long_long
{
protected:


   //char               m_sz[16];
   //::i64 *        m_plong;
   ::i64            m_i64;


public:



   inline interlocked_long_long(::i64 i = 0);


   inline interlocked_long_long(const interlocked_long_long& ll);


   inline interlocked_long_long(interlocked_long_long && ll);


   inline interlocked_long_long& operator = (::i64 i);


   inline operator ::i64() const;


   inline ::i64 operator ++();
   inline ::i64 operator--();
   inline ::i64 operator ++(int);
   inline ::i64 operator--(int);

   inline interlocked_long_long& operator +=(::i64 l);
   inline interlocked_long_long& operator-=(::i64 l);


   inline ::i64 as_integer() const { return m_i64;}
   
};


#endif


// memory must be aligned
class INLINE_CLASS_DECL_ACME interlocked_int
{
protected:


   //char                 m_sz[8];
   //int *              m_plong;
   int                   m_i32;


public:


   inline interlocked_int(int i = 0);

   inline interlocked_int& operator = (int i);
   
   inline operator int() const;


   inline interlocked_int & operator ++();
   inline interlocked_int & operator--();
   inline int operator ++(int);
   inline int operator--(int);


   inline interlocked_int& operator +=(int l);
   inline interlocked_int& operator-=(int l);


   inline int as_integer() const { return m_i32;}


};


#if OSBIT == 32

using interlocked_count = ::interlocked_int;

#else

using interlocked_count = ::interlocked_long_long;

#endif


#if OSBIT == 64


inline interlocked_long_long::interlocked_long_long(::i64 i) :
   m_i64(i)
{

}


inline interlocked_long_long::interlocked_long_long(const interlocked_long_long & ll) :
   m_i64(ll.m_i64)
{

}


inline interlocked_long_long::interlocked_long_long(interlocked_long_long && ll) :
   m_i64(ll.m_i64)
{
   ll.m_i64 = 0;
}


inline interlocked_long_long& interlocked_long_long::operator = (::i64 i)
{

   atomic_assign64(&m_i64, i);

   return *this;

}


inline interlocked_long_long::operator ::i64() const
{

   return m_i64;

}


inline ::i64 interlocked_long_long::operator ++()
{

   return atomic_increment64(&m_i64);

}


inline ::i64 interlocked_long_long::operator--()
{

   return atomic_decrement64(&m_i64);

}


inline ::i64 interlocked_long_long::operator ++(int)
{

   auto ll = m_i64;

   atomic_increment64(&m_i64);

   return ll;

}


inline ::i64 interlocked_long_long::operator--(int)
{

   auto ll = m_i64;

   atomic_decrement64(&m_i64);

   return ll;

}


inline interlocked_long_long& interlocked_long_long::operator +=(::i64 ll)
{

   atomic_add64(&m_i64, ll);

   return *this;

}


inline interlocked_long_long& interlocked_long_long::operator-=(::i64 ll)
{

   atomic_subtract64(&m_i64, ll);

   return *this;

}



#endif



//inline void interlocked_int::construct(int l)
//{
//
//   m_plong = (int*)(((iptr)m_sz + 7) & ~7);
//
//   *m_plong = l;
//
//}


inline interlocked_int::interlocked_int(int i) :
   m_i32(i)
{

   //construct(l);

}


inline interlocked_int& interlocked_int::operator = (int i)
{

   atomic_assign32(&m_i32, i);

   return *this;

}


inline interlocked_int::operator int() const
{

   return m_i32;

}


inline interlocked_int& interlocked_int::operator ++()
{

   atomic_increment32(&m_i32);

   return *this;

}


inline interlocked_int& interlocked_int::operator--()
{

   atomic_decrement32(&m_i32);

   return *this;

}


inline int interlocked_int::operator ++(int)
{

   auto i = m_i32;

   atomic_increment32(&m_i32);

   return i;

}


inline int interlocked_int::operator--(int)
{

   auto i = m_i32;

   atomic_decrement32(&m_i32);

   return i;

}


inline interlocked_int& interlocked_int::operator +=(int i)
{

   atomic_add32(&m_i32, i);

   return *this;

}


inline interlocked_int& interlocked_int::operator-=(int l)
{

   atomic_subtract32(&m_i32, l);

   return *this;

}



