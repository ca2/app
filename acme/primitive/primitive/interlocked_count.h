#pragma once


#include "atomic.h"


#if OSBIT == 64


class INLINE_CLASS_DECL_ACME interlocked_i64
{
protected:


   char                 m_sz[16];
   ::i64 *              m_plong;


public:


   inline void construct(::i64 l = 0);


   inline interlocked_i64(::i64 l = 0);


   inline interlocked_i64& operator = (::i64 i);


   inline operator ::i64() const;


   inline ::i64 operator++();
   inline ::i64 operator--();
   inline ::i64 operator++(int);
   inline ::i64 operator--(int);

   inline interlocked_i64& operator+=(::i64 l);
   inline interlocked_i64& operator-=(::i64 l);

   
};


#endif


class INLINE_CLASS_DECL_ACME interlocked_i32
{
protected:


   char                 m_sz[8];
   ::i32 *              m_plong;


public:


   inline void construct(::i32 l = 0);

   inline interlocked_i32(::i32 l = 0);

   inline interlocked_i32& operator = (::i32 i);
   
   inline operator ::i32() const;


   inline interlocked_i32 & operator++();
   inline interlocked_i32 & operator--();
   inline ::i32 operator++(int);
   inline ::i32 operator--(int);


   inline interlocked_i32& operator+=(::i32 l);
   inline interlocked_i32& operator-=(::i32 l);


};


#if OSBIT == 32

using interlocked_count = ::interlocked_i32;

#else

using interlocked_count = ::interlocked_i64;

#endif


#if OSBIT == 64


inline void interlocked_i64::construct(::i64 l)
{

   m_plong = (::i64*)(((::iptr)this + 7) & ~7);

   *m_plong = l;

}


inline interlocked_i64::interlocked_i64(::i64 l)
{

   construct(l);

}


inline interlocked_i64& interlocked_i64::operator = (::i64 i)
{

   *m_plong = i;

   return *this;

}


inline interlocked_i64::operator ::i64() const
{

   return *m_plong;

}


inline ::i64 interlocked_i64::operator++()
{

   return atomic_increment64(m_plong);

}


inline ::i64 interlocked_i64::operator--()
{

   return atomic_decrement64(m_plong);

}


inline ::i64 interlocked_i64::operator++(int)
{

   auto l = *m_plong;

   atomic_increment64(m_plong);

   return l;

}


inline ::i64 interlocked_i64::operator--(int)
{

   auto l = *m_plong;

   atomic_decrement64(m_plong);

   return l;

}


inline interlocked_i64& interlocked_i64::operator+=(::i64 l)
{

   atomic_add64(m_plong, l);

   return *this;

}


inline interlocked_i64& interlocked_i64::operator-=(::i64 l)
{

   atomic_subtract64(m_plong, l);

   return *this;

}



#endif



inline void interlocked_i32::construct(::i32 l)
{

   m_plong = (::i32*)(((iptr)this + 7) & ~7);

   *m_plong = l;

}


inline interlocked_i32::interlocked_i32(::i32 l)
{

   construct(l);

}


inline interlocked_i32& interlocked_i32::operator = (::i32 i)
{

   *m_plong = i;

   return *this;

}


inline interlocked_i32::operator ::i32() const
{

   return *m_plong;

}


inline interlocked_i32& interlocked_i32::operator++()
{

   atomic_increment32(m_plong);

   return *this;

}


inline interlocked_i32& interlocked_i32::operator--()
{

   atomic_decrement32(m_plong);

   return *this;

}


inline ::i32 interlocked_i32::operator++(int)
{

   auto l = *m_plong;

   atomic_increment32(m_plong);

   return l;

}


inline ::i32 interlocked_i32::operator--(int)
{

   auto l = *m_plong;

   atomic_decrement32(m_plong);

   return l;

}


inline interlocked_i32& interlocked_i32::operator+=(::i32 l)
{

   atomic_add32(m_plong, l);

   return *this;

}


inline interlocked_i32& interlocked_i32::operator-=(::i32 l)
{

   atomic_subtract32(m_plong, l);

   return *this;

}



