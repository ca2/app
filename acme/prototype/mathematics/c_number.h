#pragma once


template < typename T >
class c_number
{
public:

   typedef T TYPE;

   T  m_number;

   inline c_number()
   {
      m_number = (T) 0;
   }

   inline c_number(T number)
   {
      m_number = number;
   }

   inline c_number(const ::string & str)
   {
      from(str);
   }

   inline operator T &()
   {
      return m_number;
   }

   inline operator const T &() const
   {
      return m_number;
   }

   inline c_number < T > & from(const ::string & str);

   /*   bool operator == (const c_number & n) const;
      bool operator > (const c_number & n) const;
      bool operator < (const c_number & n) const;
      bool operator >= (const c_number & n) const;
      bool operator <= (const c_number & n) const;
      bool operator != (const c_number & n) const;

      c_number & operator = (const c_number & n);
      c_number & operator += (const c_number & n);
      c_number & operator -= (const c_number & n);*/


   inline static T max_value()
   {
      return ::numeric_info< T >::maximum();
   }

   inline static T min_value()
   {
      return ::numeric_info< T >::minimum();
   }

   inline static T allset_value()
   {
      return ::numeric_info< T >::allset();
   }

   inline void set_maximum()
   {
      m_number = max_value();
   }


   template < typename TYPE >
   inline TYPE * cast() const
   {
      return (TYPE *) m_number;
   }

   template < typename TYPE >
   inline TYPE scast() const
   {
      return (TYPE)m_number;
   }


};


/*template < typename T >
inline bool c_number<T> ::operator == (const c_number < T > & n) const
{
   return m_number == n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator > (const c_number < T > & n) const
{
   return m_number > n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator < (const c_number < T > & n) const
{
   return m_number < n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator >= (const c_number < T > & n) const
{
   return m_number >= n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator <= (const c_number < T > & n) const
{
   return m_number <= n.m_number;
}

template < typename T >
inline bool c_number<T> ::operator != (const c_number < T > & n) const
{
   return m_number != n.m_number;
}

template < typename T >
inline c_number<T> & c_number<T> ::operator = (const c_number < T > & n)
{
   m_number = n.m_number;
   return *this;
}

template < typename T >
inline c_number<T> & c_number<T> ::operator += (const c_number<T> & n)
{
   m_number += n.m_number;
   return *this;
}

template < typename T >
inline c_number<T> & c_number<T> ::operator -= (const c_number<T> & n)
{
   m_number -= n.m_number;
   return *this;
}

template < typename T >
inline c_number<T> operator + (const c_number<T> & n1, const c_number<T> & n2)
{
   return n1.m_number + n2.m_number;
}

template < typename T >
inline c_number<T> operator - (const c_number<T> & n1, const c_number<T> & n2)
{
   return n1.m_number - n2.m_number;
}

*/











#define DEFINE_UNIT(e, ca, T) \
   class e ca : \
      public c_number < T > \
   { \
   public: \
      ca() \
      { \
      } \
      \
      ca(const T & ca) : \
         c_number < T > ((const c_number < T > &) ca) \
      { \
      } \
      \
   };


class time;


//class microsecond;


//class nanosecond;


class time;




//class CLASS_DECL_ACME class ::time
//{
//public:
//
//
//   long long       m_i;
//
//
//   class ::time() { m_i = 0; }
//   class ::time(long long i) { m_i = i; }
//
//
//   class ::time & operator = (const second & second) { m_i = second.m_i * 1'000; return *this; }
//   class ::time & operator = (const class time & time) { m_i = class ::time.m_i; return *this; }
//   class ::time & operator = (const microsecond & microsecond);
//   class ::time & operator = (const nanosecond & nanosecond);
//   class ::time & operator = (const class time & time);
//   class ::time & operator = (long long i) { m_i = i; return *this; }
//
//
//};









////#ifdef WINDOWS
//DEFINE_UNIT(CLASS_DECL_ACME, lock_time, unsigned int)
//DEFINE_UNIT(CLASS_DECL_ACME, tick_time, unsigned int)
////#endif

//DEFINE_C_NUMBER(CLASS_DECL_ACME, filesize        , unsigned long long)
//DEFINE_C_NUMBER(CLASS_DECL_ACME, filesize    , unsigned long long)
//DEFINE_C_NUMBER(CLASS_DECL_ACME, filesize      ,  long long)


/*namespace numeric_info
{


   template <>
   inline filesize get_maximum_value < filesize > ()
   {
      return static_cast < filesize > (0xffffffffffffffff);
   }

   template <>
   inline filesize get_minimum_value < filesize > ()
   {
      return static_cast < unsigned long long > (0);
   }

   template <>
   inline filesize get_allset_value < filesize > ()
   {
      return static_cast < filesize > (0xffffffffffffffff);
   }

   template <>
   inline filesize get_null_value < filesize > ()
   {
      return 0;
   }

   template <>
   inline filesize get_unitary_value < filesize >()
   {
      return 1;
   }


} // namespace numeric_info



*/


namespace numeric_info_internal
{


   template < typename T >
   class CLASS_DECL_ACME numeric_info < ::c_number < T > > :
      public numeric_info < T >
   {
   public:


   };


} // namespace numeric_info_internal


//template < typename T >
//inline stream &  operator >>(stream & istream, c_number < T > & t)
//{
//
//   return istream >> t.m_number;
//
//}
//
//template < typename T >
//inline stream &  operator <<(stream & ostream, const c_number < T > & t)
//{
//
//   return ostream << t.m_number;
//
//}
