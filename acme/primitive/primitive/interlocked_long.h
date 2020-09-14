#pragma once


template < typename INTERLOCKED_LONG >
class interlocked
{
public:


   INTERLOCKED_LONG * m_plong;


   interlocked(INTERLOCKED_LONG l = 0);
   virtual ~interlocked();


   void add(INTERLOCKED_LONG l);
   void subtract(INTERLOCKED_LONG l);


   inline operator INTERLOCKED_LONG() { return *m_plong; }

   interlocked & operator = (INTERLOCKED_LONG i);
   //bool operator == (long i) const;
   //bool operator > (long i) const;
   //bool operator >= (long i) const;
   //bool operator < (long i) const;
   //bool operator <= (long i) const;
   //bool operator != (long i) const;


   interlocked & operator++();
   interlocked & operator--();
   INTERLOCKED_LONG operator++(int);
   INTERLOCKED_LONG operator--(int);

   interlocked & operator+=(INTERLOCKED_LONG l) { add(l); return *this; }
   interlocked & operator-=(INTERLOCKED_LONG l) { subtract(l); return *this; }


};


using interlocked_long = ::interlocked < long >;


#if defined(WINDOWS) && OSBIT == 32

using interlocked_count = ::interlocked < long >;

#else

using interlocked_count = ::interlocked < ::count >;

#endif



template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG >::interlocked(INTERLOCKED_LONG l)
{
#if defined(WINDOWS) || defined(APPLEOS)
   m_plong = (INTERLOCKED_LONG *)aligned_memory_alloc(sizeof(INTERLOCKED_LONG));
#else
   m_plong = (INTERLOCKED_LONG *)malloc(sizeof(INTERLOCKED_LONG));
#endif
   * m_plong = l;
}

template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG >::~interlocked()
{
   if (m_plong != nullptr)
   {
#if defined(WINDOWS) || defined(APPLEOS)
      memory_free(m_plong);
#else
      free(m_plong);
#endif
   }
}

template < typename TYPENAME >
inline void interlocked_exchange_add(TYPENAME * p, TYPENAME l)
{
#ifdef WINDOWS
   InterlockedExchangeAdd(p, l);
#else
   __sync_fetch_and_add(p, l);
#endif

}

inline void interlocked_exchange_add(long long * p, long long l)
{
   interlocked_exchange_add((unsigned long long *) p, (unsigned long long) l);
}

template < typename TYPENAME >
inline void interlocked_exchange(TYPENAME * p, TYPENAME l)
{
#ifdef WINDOWS
   InterlockedExchange(p, l);
#else
   __sync_synchronize();
   *p = l;
#endif
}

inline void interlocked_exchange(long long * p, long long l)
{
   interlocked_exchange((unsigned long long *) p, (unsigned long long) l);
}

template < typename INTERLOCKED_LONG >
inline void interlocked < INTERLOCKED_LONG >::add(INTERLOCKED_LONG l)
{
   interlocked_exchange_add(m_plong, l);
}


template < typename INTERLOCKED_LONG >
inline void interlocked < INTERLOCKED_LONG >::subtract(INTERLOCKED_LONG l)
{
   interlocked_exchange_add(m_plong, -l);
}


template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG > & interlocked < INTERLOCKED_LONG >::operator = (INTERLOCKED_LONG l)
{
   interlocked_exchange(m_plong, l);
   return *this;
}

//bool interlocked_long::operator == (long i) const
//{
//   return *m_plong == i;
//}
//
//bool interlocked_long::operator > (long i) const
//{
//   return *m_plong > i;
//}
//
//bool interlocked_long::operator >= (long i) const
//{
//   return *m_plong >= i;
//}
//
//bool interlocked_long::operator < (long i) const
//{
//   return *m_plong < i;
//}
//
//bool interlocked_long::operator <= (long i) const
//{
//   return *m_plong <= i;
//}
//
//bool interlocked_long::operator != (long i) const
//{
//   return *m_plong != i;
//}


template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG > & interlocked < INTERLOCKED_LONG >::operator++()
{

   add(1);

   return *this;

}


template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG > & interlocked < INTERLOCKED_LONG >::operator--()
{

   subtract(1);

   return *this;

}


template < typename INTERLOCKED_LONG >
inline INTERLOCKED_LONG interlocked < INTERLOCKED_LONG >::operator++(int)
{

   INTERLOCKED_LONG l = *m_plong;

   add(1);

   return l;

}


template < typename INTERLOCKED_LONG >
inline INTERLOCKED_LONG interlocked < INTERLOCKED_LONG >::operator--(int)
{

   INTERLOCKED_LONG l = *m_plong;

   subtract(1);

   return l;

}




