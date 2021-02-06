#pragma once


template < typename INTERLOCKED_LONG >
class interlocked
{
public:


   char sz[(sizeof(INTERLOCKED_LONG) + 7) & ~7];


   interlocked(INTERLOCKED_LONG l = 0);
   ~interlocked();


   //void add(INTERLOCKED_LONG l);
   //void subtract(INTERLOCKED_LONG l);


   inline operator INTERLOCKED_LONG &() { return *(INTERLOCKED_LONG*)(((iptr) this + 7) & ~7); }
   inline operator INTERLOCKED_LONG () const { return *(INTERLOCKED_LONG *)(((iptr) this + 7) & ~7); }

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


using interlocked_i32 = ::interlocked < ::i32 >;


#if defined(WINDOWS) && OSBIT == 32

using interlocked_count = ::interlocked < ::i32 >;

#else

using interlocked_count = ::interlocked < ::i64 >;

#endif



template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG >::interlocked(INTERLOCKED_LONG l)
{
//#if defined(WINDOWS) || defined(APPLEOS)
  //&operator INTERLOCKED_LONG &() = (INTERLOCKED_LONG *)aligned_memory_alloc(sizeof(INTERLOCKED_LONG));
//#else
  //&operator INTERLOCKED_LONG &() = (INTERLOCKED_LONG *)malloc(sizeof(INTERLOCKED_LONG));
//#endif
  //* &operator INTERLOCKED_LONG &() = l;
}

template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG >::~interlocked()
{
//  if (&operator INTERLOCKED_LONG &() != nullptr)
//  {
//#if defined(WINDOWS) || defined(APPLEOS)
//     memory_free(&operator INTERLOCKED_LONG &());
//#else
//     free(&operator INTERLOCKED_LONG &());
//#endif
//  }
}

//template < typename INTERLOCKED_LONG >
//inline void interlocked < INTERLOCKED_LONG >::add(INTERLOCKED_LONG l)
//{
//  interlocked_exchange_add(&operator INTERLOCKED_LONG &(), l);
//}
//
//
//template < typename INTERLOCKED_LONG >
//inline void interlocked < INTERLOCKED_LONG >::subtract(INTERLOCKED_LONG l)
//{
//  interlocked_exchange_add(&operator INTERLOCKED_LONG &(), -l);
//}


//template < typename INTERLOCKED_LONG >
//inline interlocked < INTERLOCKED_LONG > & interlocked < INTERLOCKED_LONG >::operator = (INTERLOCKED_LONG l)
//{
//  interlocked_exchange(&operator INTERLOCKED_LONG &(), l);
//  return *this;
//}

//bool interlocked_long::operator == (long i) const
//{
//   return *&operator INTERLOCKED_LONG &() == i;
//}
//
//bool interlocked_long::operator > (long i) const
//{
//   return *&operator INTERLOCKED_LONG &() > i;
//}
//
//bool interlocked_long::operator >= (long i) const
//{
//   return *&operator INTERLOCKED_LONG &() >= i;
//}
//
//bool interlocked_long::operator < (long i) const
//{
//   return *&operator INTERLOCKED_LONG &() < i;
//}
//
//bool interlocked_long::operator <= (long i) const
//{
//   return *&operator INTERLOCKED_LONG &() <= i;
//}
//
//bool interlocked_long::operator != (long i) const
//{
//   return *&operator INTERLOCKED_LONG &() != i;
//}


template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG > & interlocked < INTERLOCKED_LONG >::operator++()
{

   atomic_increment(&operator INTERLOCKED_LONG &());

   return *this;

}


template < typename INTERLOCKED_LONG >
inline interlocked < INTERLOCKED_LONG > & interlocked < INTERLOCKED_LONG >::operator--()
{

   atomic_decrement(&operator INTERLOCKED_LONG &());

   return *this;

}


template < typename INTERLOCKED_LONG >
inline INTERLOCKED_LONG interlocked < INTERLOCKED_LONG >::operator++(int)
{

  auto l = *&operator INTERLOCKED_LONG &();

  atomic_increment(&operator INTERLOCKED_LONG &());

  return l;

}


template < typename INTERLOCKED_LONG >
inline INTERLOCKED_LONG interlocked < INTERLOCKED_LONG >::operator--(int)
{

  auto l = *&operator INTERLOCKED_LONG &();

  atomic_decrement(&operator INTERLOCKED_LONG &());

  return l;

}



