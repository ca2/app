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

   inline c_number(const string & str)
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

   inline c_number < T > & from(const string & str);

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


class millis;


class micros;


class nanos;


class duration;


class CLASS_DECL_ACME millis
{
public:


   ::i64       m_iMilliseconds;


   millis() { m_iMilliseconds = 0; }
   millis(::i64 i) { m_iMilliseconds = i; }


   millis & operator = (const millis & millis) { m_iMilliseconds = millis.m_iMilliseconds; return *this; }
   millis & operator = (const micros & micros);
   millis & operator = (const nanos & nanos);
   millis & operator = (const duration & duration);
   millis & operator = (::i64 i) { m_iMilliseconds = i; return *this; }


};


class CLASS_DECL_ACME micros
{
public:


   ::i64       m_iMicroseconds;


   micros() { m_iMicroseconds = 0; }
   micros(::i64 i) { m_iMicroseconds = i; }


   micros & operator = (const millis & millis) { m_iMicroseconds = millis.m_iMilliseconds; return *this; }
   micros & operator = (const micros & micros) { m_iMicroseconds = micros.m_iMicroseconds; return *this; }
   micros & operator = (const nanos & nanos);
   micros & operator = (const duration & duration);
   micros & operator = (::i64 i) { m_iMicroseconds = i; return *this; }


};


class CLASS_DECL_ACME nanos
{
public:


   ::i16    m_iNanoseconds;


   nanos() { m_iNanoseconds = 0; }
   nanos(::i64 i) { m_iNanoseconds = i; }


   nanos & operator = (const millis & millis) { m_iNanoseconds = millis.m_iMilliseconds * 1'000'000; return *this; }
   nanos & operator = (const micros & micros) { m_iNanoseconds = micros.m_iMicroseconds * 1'000; return *this; }
   nanos & operator = (const nanos & nanos) { m_iNanoseconds = nanos.m_iNanoseconds; return *this; }
   nanos & operator = (const duration & duration);
   nanos & operator = (::i64 i) { m_iNanoseconds = i; return *this; }


};


inline millis & millis::operator = (const nanos & nanos) { m_iMilliseconds = nanos.m_iNanoseconds / 1'000'000; return *this; }
inline micros & micros::operator = (const nanos & nanos) { m_iMicroseconds = nanos.m_iNanoseconds / 1'000; return *this; }
inline millis & millis::operator = (const micros & micros) { m_iMilliseconds = micros.m_iMicroseconds / 1'000; return *this; }


////#ifdef WINDOWS
//DEFINE_UNIT(CLASS_DECL_ACME, lock_duration, u32)
//DEFINE_UNIT(CLASS_DECL_ACME, tick_duration, u32)
////#endif

//DEFINE_C_NUMBER(CLASS_DECL_ACME, filesize        , u64)
//DEFINE_C_NUMBER(CLASS_DECL_ACME, filesize    , u64)
//DEFINE_C_NUMBER(CLASS_DECL_ACME, filesize      ,  i64)


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
      return static_cast < u64 > (0);
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

}


template < typename T >
inline stream &  operator >>(stream & istream, c_number < T > & t)
{

   return istream >> t.m_number;

}

template < typename T >
inline stream &  operator <<(stream & ostream, const c_number < T > & t)
{

   return ostream << t.m_number;

}
