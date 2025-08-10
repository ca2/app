#pragma once


#include "atomic.h"


#if OSBIT == 64

// memory must be aligned
class INLINE_CLASS_DECL_ACME interlocked_long_long
{
protected:


   //char               m_sz[16];
   //long long *        m_plong;
   long long            m_ll;


public:



   inline interlocked_long_long(long long i = 0);


   inline interlocked_long_long& operator = (long long i);


   inline operator long long() const;


   inline long long operator ++();
   inline long long operator--();
   inline long long operator ++(int);
   inline long long operator--(int);

   inline interlocked_long_long& operator +=(long long l);
   inline interlocked_long_long& operator-=(long long l);


   inline long long as_integer() const { return m_ll;}
   
};


#endif


// memory must be aligned
class INLINE_CLASS_DECL_ACME interlocked_int
{
protected:


   //char                 m_sz[8];
   //int *              m_plong;
   int                   m_i;


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


   inline int as_integer() const { return m_i;}


};


#if OSBIT == 32

using interlocked_count = ::interlocked_int;

#else

using interlocked_count = ::interlocked_long_long;

#endif


#if OSBIT == 64


inline interlocked_long_long::interlocked_long_long(long long i) :
   m_ll(i)
{

}


inline interlocked_long_long& interlocked_long_long::operator = (long long i)
{

   atomic_assign64(&m_ll, i);

   return *this;

}


inline interlocked_long_long::operator long long() const
{

   return m_ll;

}


inline long long interlocked_long_long::operator ++()
{

   return atomic_increment64(&m_ll);

}


inline long long interlocked_long_long::operator--()
{

   return atomic_decrement64(&m_ll);

}


inline long long interlocked_long_long::operator ++(int)
{

   auto ll = m_ll;

   atomic_increment64(&m_ll);

   return ll;

}


inline long long interlocked_long_long::operator--(int)
{

   auto ll = m_ll;

   atomic_decrement64(&m_ll);

   return ll;

}


inline interlocked_long_long& interlocked_long_long::operator +=(long long ll)
{

   atomic_add64(&m_ll, ll);

   return *this;

}


inline interlocked_long_long& interlocked_long_long::operator-=(long long ll)
{

   atomic_subtract64(&m_ll, ll);

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
   m_i(i)
{

   //construct(l);

}


inline interlocked_int& interlocked_int::operator = (int i)
{

   atomic_assign32(&m_i, i);

   return *this;

}


inline interlocked_int::operator int() const
{

   return m_i;

}


inline interlocked_int& interlocked_int::operator ++()
{

   atomic_increment32(&m_i);

   return *this;

}


inline interlocked_int& interlocked_int::operator--()
{

   atomic_decrement32(&m_i);

   return *this;

}


inline int interlocked_int::operator ++(int)
{

   auto i = m_i;

   atomic_increment32(&m_i);

   return i;

}


inline int interlocked_int::operator--(int)
{

   auto i = m_i;

   atomic_decrement32(&m_i);

   return i;

}


inline interlocked_int& interlocked_int::operator +=(int i)
{

   atomic_add32(&m_i, i);

   return *this;

}


inline interlocked_int& interlocked_int::operator-=(int l)
{

   atomic_subtract32(&m_i, l);

   return *this;

}



