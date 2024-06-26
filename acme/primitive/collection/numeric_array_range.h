#pragma once


template < typename A >
class numeric_array_each
{
public:

   A & a;
   inline numeric_array_each(A & array):a(array){}
   inline numeric_array_each & operator += (const typename A::BASE_TYPE & t)
   {
      for(::collection::index i = 0; i < a.get_count(); i++)
      {
         a[i] += t;
      }
      return *this;
   }
   inline numeric_array_each & operator -= (const typename A::BASE_TYPE & t)
   {
      for(::collection::index i = 0; i < a.get_count(); i++)
      {
         a[i] -= t;
      }
      return *this;
   }

};


template < typename A >
class numeric_array_range
{
public:

   A & a;
   ::collection::index m_iBeg;
   ::collection::index m_iEnd;

   inline numeric_array_range(numeric_array_range && r):a(r.a),m_iBeg(a.m_iBeg),m_iEnd(a.m_iEnd) {}

   inline numeric_array_range(A & array, ::collection::index iStart, ::collection::index iCount = -1):a(array)
   {

      if(iCount == 0)
         return ;

      ::collection::index iEnd;

      if(iCount < 0)
      {

         iEnd = iCount + a.get_size();

      }
      else
      {

         iEnd = iCount - 1;

      }

      if(iStart < 0)
      {

         iStart += a.get_size();

      }

      if(iStart < 0)
      {

         iEnd += iStart;

         iStart = 0;

      }

      if(iStart < 0)
         throw_exception(error_bad_argument);

      if(iStart >= a.get_count())
         throw_exception(error_bad_argument);

      if(iEnd < 0)
         throw_exception(error_bad_argument);

      if(iEnd >= a.get_count())
         throw_exception(error_bad_argument);

      m_iBeg = iStart;

      m_iEnd = iEnd;

   }

   inline numeric_array_range & operator += (const typename A::BASE_TYPE & t)
   {
      for(::collection::index i = m_iBeg; i <= m_iEnd; i++)
      {
         a[i] += t;
      }
      return *this;
   }

   inline numeric_array_range & operator -= (const typename A::BASE_TYPE & t)
   {
      for(::collection::index i = m_iBeg; i <= m_iEnd; i++)
      {
         a[i] -= t;
      }
      return *this;
   }

};


