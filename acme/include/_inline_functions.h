// Created by camilo on 2022-11-08 23:10 <3ThomasBorregaardSorensen!!
#pragma once


#include <math.h>
#include <limits>


template < typename T >
T default_epsilon()
{

   return {};

}


template < prototype_integral INTEGRAL >
constexpr INTEGRAL default_epsilon()
{

   return 0;

}


template < prototype_floating FLOATING >
constexpr FLOATING default_epsilon()
{

   return ::std::numeric_limits<FLOATING>::epsilon();

}


//template < typename A, typename B >
//inline void swap(A & a, B & b)
//{
//
//   auto t = a;
//
//   a = b;
//
//   b = t;
//
//}



inline bool is_empty(const_char_pointer p) { return is_string_empty(p); }
inline bool is_empty(const ::wd16_character * p) { return is_string_empty(p); }
inline bool is_empty(const ::wd32_character * p) { return is_string_empty(p); }


inline bool has_character(const_char_pointer p) { return !is_empty(p); }
inline bool has_character(const ::wd16_character * p) { return !is_empty(p); }
inline bool has_character(const ::wd32_character * p) { return !is_empty(p); }



inline unsigned long long make64_from32(unsigned int l, unsigned int h)
{

   return ((unsigned long long)l) | (((unsigned long long)h) << 32);

}

CLASS_DECL_ACME void this_is_a_debugging_consumer(int & i);

inline bool is_memory_segment_ok(const void * pMemory, memsize s)
{

   auto p = (const unsigned char *)pMemory;

   auto e = p + s;

   try
   {

#ifdef DEEP_MEMORY_SEGMENT_CHECK

      int sum = 0;

      while (p < e)
      {

         sum += *b; // tests read of unsigned char *p

         p++;

      }

#else // DEEP_MEMORY_SEGMENT_CHECK
//      __pragma(clang)
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wunused-but-set-variable"

      if (s >= 1)
      {

         int sum = 0;

         sum += p[0]; // tests read of unsigned char p[0]

         if (s >= 2)
         {

            sum += *(e-1); // tests read of unsigned char e[-1]

         }

         this_is_a_debugging_consumer(sum);

      }

//#pragma clang diagnostic pop

#endif // else DEEP_MEMORY_SEGMENT_CHECK

      return true;

   }
   catch (...)
   {

   }

   return false;

}


inline bool is_memory_segment_ok(void * pMemory, memsize s)
{

   auto p = (unsigned char *)pMemory;

   auto e = p + s;

   try
   {

#ifdef DEEP_MEMORY_SEGMENT_CHECK

      while (p < e)
      {

         unsigned char & b = *p;

         b++; // tests read/write of unsigned char b

         b--; // restablish it

         p++;

      }


#else // DEEP_MEMORY_SEGMENT_CHECK

      if (s >= 1)
      {

         unsigned char & b = p[0];

         b++; // tests read/write of unsigned char p[0]

         b--; // restablish it

         if (s >= 2)
         {

            unsigned char & b = e[-1];

            b++; // tests read/write of unsigned char e[-1]

            b--; // restablish it


         }

      }

#endif // else DEEP_MEMORY_SEGMENT_CHECK

      return true;

   }
   catch (...)
   {

   }

   return false;

}


template < typename TYPE >
inline bool is_array_ok(TYPE * p, ::collection::count c)
{

   return is_memory_segment_ok(p, c * sizeof(TYPE));

}


template < typename TYPE >
inline bool is_array_ok(const TYPE * p, ::collection::count c)
{

   return is_memory_segment_ok(p, c * sizeof(TYPE));

}


inline bool is_string_ok(::wide_character * p, character_count s)
{

   return ::is_array_ok(p, s);

}


inline bool is_string_ok(const ::wide_character * p, character_count s)
{

   return ::is_array_ok(p, s);

}


inline bool is_string_ok(::ansi_character * p, character_count s)
{

   return ::is_array_ok(p, s);

}


inline bool is_string_ok(const_char_pointer p, character_count s)
{

   return ::is_array_ok(p, s);

}


template < typename TYPE >
inline bool is_null_terminated_primitive_array_ok(TYPE * p)
{

   try
   {

      while (*p)
      {

         auto & item = *p;

         item++; // tests read/write of unsigned char b

         item--; // restablish it

         p++;

      }

      return true;

   }
   catch (...)
   {

   }

   return false;

}


template < typename TYPE >
inline bool is_null_terminated_primitive_array_ok(const TYPE * p)
{

   try
   {

      TYPE t{};

      while (*p)
      {

         t ^= *p;

         p++;

      }

      return true;

   }
   catch (...)
   {

   }

   return false;

}


inline bool is_string_ok(::wide_character * p)
{

   return is_null_terminated_primitive_array_ok(p);

}


inline bool is_string_ok(const ::wide_character * p)
{

   return is_null_terminated_primitive_array_ok(p);

}


inline bool is_string_ok(::ansi_character * p)
{

   return is_null_terminated_primitive_array_ok(p);

}


inline bool is_string_ok(const_char_pointer p)
{

   return is_null_terminated_primitive_array_ok(p);

}


inline int_bool address_overlaps(const void * p1, const void * p2, character_count len)
{

   return (((unsigned char*)p1) <= (((unsigned char*)p2) + len))
       && (((unsigned char*)p2) <= (((unsigned char*)p1) + len));

}


//template < typename TYPE > inline TYPE*& __defer_new(TYPE*& p)
//{
//
//   if (!p) p = øallocate TYPE();
//
//   return p;
//
//}
//
//
//inline const ::particle * context_trace_object() { return general_trace_object(); }
//
//
//#ifdef CPP17
//
//template <typename PRED, typename ... Args >
//inline bool _returns_true(PRED pred, const true_type& predicate_returns_void, bool bOnVoid, Args... args)
//{
//   pred(args...);
//   return bOnVoid;
//}
//
//template <typename PRED, typename ... Args >
//inline bool _returns_true(PRED pred, const false_type& predicate_returns_void, bool, Args... args)
//{
//   return (bool)pred(args...);
//}
//
//template <typename PRED, typename ... Args >
//inline bool returns_true(PRED pred, bool bOnVoid, Args... args)
//{
//
//   return _returns_true(pred, is_void<decltype(pred(args...))>, bOnVoid, args...);
//
//}
//
//template <typename PRED, typename ... Args >
//inline bool _returns_false(PRED pred, const true_type& predicate_returns_void, bool bOnVoid, Args... args)
//{
//   pred(args...);
//   return bOnVoid;
//}
//
//template <typename PRED, typename ... Args >
//inline bool _returns_false(PRED pred, const false_type& predicate_returns_void, bool, Args... args)
//{
//   return !(bool)pred(args...);
//}
//
//template <typename PRED, typename ... Args >
//inline bool returns_false(PRED pred, bool bOnVoid, Args... args)
//{
//
//   return _returns_false(pred, is_void < decltype(pred(args...)) >, bOnVoid, args...);
//
//}
//
//#endif
//


inline const ::particle* trace_object(const ::particle* pparticle) { return pparticle; }


//inline bool failed(const ::payload& payload) { return !::succeeded(payload); }


inline int read_char(unsigned char*& pdata, memsize& s, char* pch)
{

   if (s < 1)
   {

      return 0;

   }

   *pch = (char)*pdata;

   pdata++;

   s--;

   return 1;

}


//
//
//template < typename TYPE >
//inline bool is_reference_null(const TYPE& t)
//{
//
//   return is_null(&t);
//
//}
//
//
//template < typename TYPE >
//inline bool is_reference_set(const TYPE& t)
//{
//
//   return is_set(&t);
//
//}
//


inline bool is_impact_group(unsigned long long u, unsigned long long uGroup) { return u >= uGroup && u < uGroup + 1000; }


inline bool is_impact_subgroup(unsigned long long u, unsigned long long uGroup) { return u >= uGroup && u < uGroup + 100; }


inline bool is_file_or_folder2(const ::file::enum_type& etype)
{

   return (etype & ::file::e_type_file_or_folder2);

}


inline bool is_existing_file_or_folder(const ::file::enum_type& etype)
{

   return (etype & ::file::e_type_file_or_folder2) > ::file::e_type_exists;

}


inline bool exists(const ::file::enum_type& etype)
{

   return etype & ::file::e_type_exists;

}


//
//template < class T >
//inline void __dynamic_cast(T*& ptarget, T* psource)
//{
//
//   ptarget = psource;
//
//}
//
//
//template < class T , typename T2 >
//inline void __dynamic_cast(T * & ptarget, T2 * psource)
//{
//
//   ptarget = dynamic_cast < T * >(psource);
//
//}
//
//
//template < typename T1, typename T2 >
//inline bool __sort(T1& t1, T2& t2)
//{
//
//   if (t2 >= t1)
//   {
//
//      return false;
//
//   }
//
//   auto t = t2;
//
//   t2 = t1;
//
//   t1 = t;
//
//   return true;
//
//}
//
//




//template < prototype_integral SECOND, prototype_integral NANOSECOND >
//constexpr void normalize_second_nanosecond(SECOND & second, NANOSECOND & nanosecond)
//{
//
//   auto extrasecond = nanosecond > 0 ? (nanosecond / 1'000'000'000) : ((nanosecond / 1'000'000'000) - 1);
//
//   second += extrasecond;
//
//   nanosecond -= extrasecond * 1'000'000'000;
//
//}
//
//
//
//template < prototype_integral SECOND1, prototype_integral NANOSECOND1, prototype_integral SECOND2, prototype_integral NANOSECOND2 >
//constexpr void add_second_nanosecond(SECOND1 & second1, NANOSECOND1 & nanosecond1, const SECOND2 & second2, const NANOSECOND2 & nanosecond2)
//{
//
//   auto nanos = nanosecond1 + nanosecond2;
//
//   auto extrasecond = nanos > 0 ? (nanos / 1'000'000'000) : ((nanos / 1'000'000'000) - 1);
//
//   second1 = second1 + second2 + extrasecond;
//
//   nanosecond1 = nanos - extrasecond * 1'000'000'000;
//
//}
//
//
//
//template < prototype_integral SECOND1, prototype_integral NANOSECOND1, prototype_integral SECOND2, prototype_integral NANOSECOND2 >
//constexpr void subtract_second_nanosecond(SECOND1 & second1, NANOSECOND1 & nanosecond1, const SECOND2 & second2, const NANOSECOND2 & nanosecond2)
//{
//
//   auto nanos = nanosecond1 - nanosecond2;
//
//   auto extrasecond = nanos > 0 ? (nanos / 1'000'000'000) : ((nanos / 1'000'000'000) - 1);
//
//   second1 = second1 - second2 + extrasecond;
//
//   nanosecond1 = nanos - extrasecond * 1'000'000'000;
//
//}


CLASS_DECL_ACME void throw_exception(enum_status estatus);


constexpr ::std::strong_ordering negation(const ::std::strong_ordering & ordering)
{

   if(ordering < 0)
   {

      return ::std::strong_ordering::greater;

   }
   else if (ordering > 0)
   {

      return ::std::strong_ordering::less;

   }
   else
   {

      return ::std::strong_ordering::equal;

   }

}


template < prototype_floating NUMBER1, prototype_floating NUMBER2 >
bool is_equal(const NUMBER1 & n1, const NUMBER2 & n2, largest_number < NUMBER2, NUMBER2 > epsilon = default_epsilon < largest_number < NUMBER2, NUMBER2 > >())
{

   return ::std::abs(n1 - n2) < epsilon;

}


template < prototype_floating NUMBER1, prototype_integral NUMBER2 >
bool is_equal(const NUMBER1 & n1, const NUMBER2 & n2, largest_number < NUMBER2, NUMBER2 > epsilon = default_epsilon < largest_number < NUMBER2, NUMBER2 > >())
{

   return ::std::abs(n1 - n2) < epsilon;

}


template < prototype_integral NUMBER1, prototype_floating NUMBER2 >
bool is_equal(const NUMBER1 & n1, const NUMBER2 & n2, largest_number < NUMBER2, NUMBER2 > epsilon = default_epsilon < largest_number < NUMBER2, NUMBER2 > >())
{

   return ::std::abs(n1 - n2) < epsilon;

}


template < prototype_integral NUMBER1, prototype_integral NUMBER2 >
bool is_equal(const NUMBER1 & n1, const NUMBER2 & n2, largest_number < NUMBER2, NUMBER2 > epsilon = 0)
{

   return n1 == n2;

}


/// this function assumes minimum and maximum already have some valid value and that minimum is greater or equal maximum.
template < prototype_number NUMBER1, prototype_number NUMBER2 >
constexpr void _expand_minimum_maximum(NUMBER1 & minimum, NUMBER1 & maximum, NUMBER2 n)
{

   if (n < minimum)
   {

      minimum = (NUMBER1) n;

   }
   else if (n > maximum)
   {

      maximum = (NUMBER1) n;

   }

}


/// this function assumes minimum and maximum already have some valid value and that minimum is greater or equal maximum.
template < prototype_integral NUMBER1, prototype_integral NUMBER2 >
constexpr void expand_minimum_maximum(NUMBER1 & minimum, NUMBER1 & maximum, NUMBER2 n)
{

   _expand_minimum_maximum(minimum, maximum, n);

}


/// this function assumes minimum and maximum already have some valid value and that minimum is greater or equal maximum.
template < prototype_floating NUMBER1, prototype_floating NUMBER2 >
constexpr void expand_minimum_maximum(NUMBER1 & minimum, NUMBER1 & maximum, NUMBER2 n)
{

   _expand_minimum_maximum(minimum, maximum, n);

}


/// this function assumes minimum and maximum already have some valid value and that minimum is greater or equal maximum.
template < prototype_floating NUMBER1, prototype_integral NUMBER2 >
constexpr void expand_minimum_maximum(NUMBER1 & minimum, NUMBER1 & maximum, NUMBER2 n)
{

   _expand_minimum_maximum(minimum, maximum, n);

}


/// this function assumes minimum and maximum already have some valid value and that minimum is greater or equal maximum.
template < prototype_integral NUMBER1, prototype_floating NUMBER2 >
constexpr void expand_minimum_maximum(NUMBER1 & minimum, NUMBER1 & maximum, NUMBER2 n)
{

   if (n < minimum)
   {

      minimum = (NUMBER1) floor(n);

   }
   else if (n > maximum)
   {

      maximum = (NUMBER1) ceil(n);

   }

}



