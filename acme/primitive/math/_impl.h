#pragma once




template < typename TYPE >
inline number_cast<TYPE>::number_cast(__int64 i)
{

   if (i > (__int64)::numeric_info < TYPE >::maximum() || i < (__int64)::numeric_info < TYPE >::minimum())
   {

      __throw(invalid_type("not valid \"<" __STRING(TYPE) ">\""));

   }

   m_number = (TYPE)i;

}


template < typename TYPE >
inline number_cast<TYPE>::number_cast(int i)
{

   if (i > (int)::numeric_info < TYPE >::maximum() || i < (int)::numeric_info < TYPE >::minimum())
   {

      __throw(invalid_type("not valid \"<" __STRING(TYPE) ">\""));

   }

   m_number = (TYPE)i;

}


inline iptr_cast::iptr_cast(::i64 i)
{

#if OSBIT == 32

   if (i > INT_MAX || i < INT_MIN)
   {

      __throw(invalid_type("not valid \"<" __STRING(NUMBER) ">\""));

   }

#endif

   m_number = (iptr)i;

}

inline i32_cast::i32_cast(::i64 i)
{

   if (i > INT_MAX || i < INT_MIN)
   {

      __throw(invalid_type("not valid \"<" __STRING(NUMBER) ">\""));

   }

   m_number = (i32)i;

}

inline i32_cast::i32_cast(unsigned int u)
{

   if (u > INT_MAX)
   {

      __throw(invalid_type("not valid \"<" __STRING(NUMBER) ">\""));

   }

   m_number = (i32)u;

}

inline u32_cast::u32_cast(::i64 i)
{

   if (i > UINT_MAX || i < 0)
   {

      __throw(invalid_type("not valid \"<" __STRING(NUMBER) ">\""));

   }

   m_number = (u32)i;

}


inline u32_cast::u32_cast(int i)
{

   if (i < 0)
   {

      __throw(invalid_type("not valid \"<" __STRING(NUMBER) ">\""));

   }

   m_number = (u32)i;

}



using index_cast = iptr_cast;
using count_cast = iptr_cast;


using memsize_cast = iptr_cast;
using strsize_cast = iptr_cast;


using LONG_cast = i32_cast;


template < typename T >
inline c_number < T > & c_number < T >::from(const string & str)
{

   ::str::to(m_number, str);

   return *this;

}


