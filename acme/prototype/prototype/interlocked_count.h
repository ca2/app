#pragma once


#include "atomic.h"


#if OSBIT == 64

// memory must be aligned
class INLINE_CLASS_DECL_ACME interlocked_huge_integer
{
protected:


   //char                 m_sz[16];
   //huge_integer *              m_plong;
   huge_integer                   m_hi;


public:



   inline interlocked_huge_integer(huge_integer i = 0);


   inline interlocked_huge_integer& operator = (huge_integer i);


   inline operator huge_integer() const;


   inline huge_integer operator++();
   inline huge_integer operator--();
   inline huge_integer operator++(int);
   inline huge_integer operator--(int);

   inline interlocked_huge_integer& operator+=(huge_integer l);
   inline interlocked_huge_integer& operator-=(huge_integer l);


   inline huge_integer as_integer() const { return m_hi;}
   
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


   inline interlocked_int & operator++();
   inline interlocked_int & operator--();
   inline int operator++(int);
   inline int operator--(int);


   inline interlocked_int& operator+=(int l);
   inline interlocked_int& operator-=(int l);


   inline int as_integer() const { return m_i;}


};


#if OSBIT == 32

using interlocked_count = ::interlocked_int;

#else

using interlocked_count = ::interlocked_huge_integer;

#endif


#if OSBIT == 64


inline interlocked_huge_integer::interlocked_huge_integer(huge_integer i) :
   m_hi(i)
{

}


inline interlocked_huge_integer& interlocked_huge_integer::operator = (huge_integer i)
{

   atomic_assign64(&m_hi, i);

   return *this;

}


inline interlocked_huge_integer::operator huge_integer() const
{

   return m_hi;

}


inline huge_integer interlocked_huge_integer::operator++()
{

   return atomic_increment64(&m_hi);

}


inline huge_integer interlocked_huge_integer::operator--()
{

   return atomic_decrement64(&m_hi);

}


inline huge_integer interlocked_huge_integer::operator++(int)
{

   auto i = m_hi;

   atomic_increment64(&m_hi);

   return i;

}


inline huge_integer interlocked_huge_integer::operator--(int)
{

   auto i = m_hi;

   atomic_decrement64(&m_hi);

   return i;

}


inline interlocked_huge_integer& interlocked_huge_integer::operator+=(huge_integer i)
{

   atomic_add64(&m_hi, i);

   return *this;

}


inline interlocked_huge_integer& interlocked_huge_integer::operator-=(huge_integer i)
{

   atomic_subtract64(&m_hi, i);

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


inline interlocked_int& interlocked_int::operator++()
{

   atomic_increment32(&m_i);

   return *this;

}


inline interlocked_int& interlocked_int::operator--()
{

   atomic_decrement32(&m_i);

   return *this;

}


inline int interlocked_int::operator++(int)
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


inline interlocked_int& interlocked_int::operator+=(int i)
{

   atomic_add32(&m_i, i);

   return *this;

}


inline interlocked_int& interlocked_int::operator-=(int l)
{

   atomic_subtract32(&m_i, l);

   return *this;

}



