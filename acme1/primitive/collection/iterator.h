#pragma once


template < typename TYPE >
class random_access_iterator
{
public:

   typedef TYPE BASE_TYPE;

   TYPE *         m_p;


   random_access_iterator(TYPE * point)
   {
      m_p = point;
   }

   random_access_iterator(const random_access_iterator & it)
   {
      operator = (it);
   }


   random_access_iterator & operator = (const random_access_iterator & it)
   {
      m_p = it.m_p;
      return *this;
   }

   bool operator == (const random_access_iterator & it)
   {
      return m_p == it.m_p;
   }

   bool operator != (const random_access_iterator & it)
   {
      return !operator==(it);
   }

   random_access_iterator operator ++(int)
   {
      random_access_iterator it = *this;
      operator ++();
      return it;
   }

   random_access_iterator operator --(int)
   {
      random_access_iterator it = *this;
      operator --();
      return it;
   }

   random_access_iterator & operator ++()
   {
      m_p++;
      return *this;
   }

   random_access_iterator & operator +(iptr i)
   {
      m_p += i;
      return *this;
   }

   random_access_iterator & operator --()
   {
      m_p--;
      return *this;
   }

   random_access_iterator & operator -(iptr c)
   {
      m_p -= c;
      return *this;
   }

   bool operator < (const random_access_iterator & i) const
   {
      return m_p < i.m_p;
   }

   TYPE & operator * ()
   {
      return *m_p;
   }

   const TYPE & operator * () const
   {
      return (const TYPE &)*m_p;
   }


};


template < typename TYPE >
class const_random_access_iterator
{
public:


   const TYPE *            m_p;

   const_random_access_iterator(const TYPE * point)
   {
      m_p = point;
   }

   const_random_access_iterator(const random_access_iterator < TYPE > & it)
   {
      operator = (it);
   }

   const_random_access_iterator(const const_random_access_iterator & it)
   {
      operator = (it);
   }

   const_random_access_iterator & operator = (const random_access_iterator < TYPE > & it)
   {
      m_p = it.m_p;
      return *this;
   }

   const_random_access_iterator & operator = (const const_random_access_iterator & it)
   {
      m_p = it.m_p;
      return *this;
   }

   bool operator == (const const_random_access_iterator & it)
   {
      return m_p == it.m_p;
   }

   bool operator != (const const_random_access_iterator & it)
   {
      return !operator==(it);
   }

   const_random_access_iterator operator ++(int)
   {
      const_random_access_iterator it = *this;
      operator ++();
      return it;
   }

   const_random_access_iterator operator --(int)
   {
      const_random_access_iterator it = *this;
      operator --();
      return it;
   }

   const_random_access_iterator & operator ++()
   {
      m_p++;
      return *this;
   }

   const_random_access_iterator & operator +(iptr i)
   {
      m_p += i;
      return *this;
   }

   const_random_access_iterator & operator --()
   {
      m_p--;
      return *this;
   }

   const_random_access_iterator & operator -(iptr i)
   {
      m_p -= i;
      return *this;
   }


   bool operator < (const const_random_access_iterator & i) const
   {

      return m_p < i.m_p;

   }

   const TYPE & operator * ()
   {
      return *((const TYPE*)m_p);
   }

};

//
//
//template < class ITERATOR >
//struct iterator_info
//{
//   typedef typename ITERATOR::ITERATOR_CATEGORY    ITERATOR_CATEGORY;
//   typedef typename ITERATOR::VALUE_TYPE           VALUE_TYPE;
//   typedef typename ITERATOR::DIFFERENCE_TYPE      DIFFERENCE_TYPE;
//   typedef DIFFERENCE_TYPE                         DISTANCE_TYPE;	// retained
//   typedef typename ITERATOR::POINTER              POINTER;
//   typedef typename ITERATOR::REFERENCE            REFERENCE;
//};
//
//
//template < class TYPE >
//struct iterator_info < TYPE * >
//{
//   typedef random_access_iterator < TYPE * >       ITERATOR_CATEGORY;
//   typedef TYPE                                    VALUE_TYPE;
//   typedef ptrdiff_t                               DIFFERENCE_TYPE;
//   typedef ptrdiff_t                               DISTANCE_TYPE;	// retained
//   typedef TYPE *                                  POINTER;
//   typedef TYPE &                                  REFERENCE;
//};
//
//
//template < class TYPE >
//struct iterator_info < const TYPE * >
//{
//   typedef random_access_iterator < TYPE * >       ITERATOR_CATEGORY;
//   typedef TYPE                                    VALUE_TYPE;
//   typedef ptrdiff_t                               DIFFERENCE_TYPE;
//   typedef ptrdiff_t                               DISTANCE_TYPE;	// retained
//   typedef const TYPE *                            POINTER;
//   typedef const TYPE &                            REFERENCE;
//};
//
//

