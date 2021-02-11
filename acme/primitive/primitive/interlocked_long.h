#pragma once


template < typename INTERLOCKED_LONG >
class interlocked
{
protected:


   char                       m_sz[(sizeof(INTERLOCKED_LONG) + 7) & ~7];
   INTERLOCKED_LONG *         m_plong;


public:


   interlocked(INTERLOCKED_LONG l = 0)
   {  

      m_plong = (INTERLOCKED_LONG *) (((iptr)this + 7) & ~7);

   }


   interlocked & operator = (INTERLOCKED_LONG i);

   operator INTERLOCKED_LONG() const { return *m_plong; }


   interlocked & operator++();
   interlocked & operator--();
   INTERLOCKED_LONG operator++(int);
   INTERLOCKED_LONG operator--(int);

   interlocked & operator+=(INTERLOCKED_LONG l);
   interlocked & operator-=(INTERLOCKED_LONG l);

   
};


using interlocked_i32 = ::interlocked < ::i32 >;


#if defined(WINDOWS) && OSBIT == 32

using interlocked_count = ::interlocked < ::i32 >;

#else

using interlocked_count = ::interlocked < ::i64 >;

#endif





template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG > & interlocked < INTERLOCKED_LONG >::operator++()
{

   atomic_increment(m_plong);

   return *this;

}


template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG > & interlocked < INTERLOCKED_LONG >::operator--()
{

   atomic_decrement(m_plong);

   return *this;

}


template < typename INTERLOCKED_LONG >
inline INTERLOCKED_LONG interlocked < INTERLOCKED_LONG >::operator++(int)
{

  auto l = *m_plong;

  atomic_increment(m_plong);

  return l;

}


template < typename INTERLOCKED_LONG >
inline INTERLOCKED_LONG interlocked < INTERLOCKED_LONG >::operator--(int)
{

  auto l = *m_plong;

  atomic_decrement(m_plong);

  return l;

}



