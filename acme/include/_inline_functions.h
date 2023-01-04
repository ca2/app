// Created by camilo on 2022-11-08 23:10 <3ThomasBorregaardSorensen!!
#pragma once


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



inline bool is_empty(const ::ansi_character * p) { return is_string_empty(p); }
inline bool is_empty(const ::wd16_character * p) { return is_string_empty(p); }
inline bool is_empty(const ::wd32_character * p) { return is_string_empty(p); }


inline bool has_char(const ::ansi_character * p) { return !is_empty(p); }
inline bool has_char(const ::wd16_character * p) { return !is_empty(p); }
inline bool has_char(const ::wd32_character * p) { return !is_empty(p); }



inline ::u64 make64_from32(::u32 l, ::u32 h)
{

   return ((::u64)l) | (((::u64)h) << 32);

}


inline bool __is_valid_address(const void* p, memsize size, bool bReadWrite)
{

#ifdef DEEP_DEBUG

   byte* pbyte = (byte*)p;

   if (bReadWrite)
   {

      for (::index i = 0; i < size; i++)
      {

         ::byte& b = *pbyte;

         b++; // tests read/write of byte b

         b--; // restablish it

      }

   }
   else
   {

      ::i32 sum = 0;

      for (::index i = 0; i < size; i++)
      {

         ::byte& b = *pbyte;

         sum += b; // tests read of byte b

      }

   }

#endif // DEEP_DEBUG

   return ::is_set(p);

}


inline bool __is_valid_string(const ::wide_character* pwsz, memsize nMaxLength)
{

   return ::__is_valid_address(pwsz, nMaxLength);

}


inline bool __is_valid_string(const char * psz, memsize nMaxLength)
{

   return ::__is_valid_address(psz, nMaxLength);

}


inline int_bool address_overlaps(const void * pszDst, const void * pszSrc, strsize srclen)
{

   return (((byte*)pszSrc) <= ((byte*)pszDst) && ((byte*)pszSrc) + srclen > ((byte*)pszDst))
      || (((byte*)pszDst) <= ((byte*)pszSrc) && ((byte*)pszDst) + srclen > ((byte*)pszSrc));

}


//template < typename TYPE > inline TYPE*& __defer_new(TYPE*& p)
//{
//
//   if (!p) p = memory_new TYPE;
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


inline bool failed(const ::payload& payload) { return !::succeeded(payload); }


inline int read_char(u8*& pdata, memsize& s, char* pch)
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


inline bool is_impact_group(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 1000; }


inline bool is_impact_subgroup(::u64 u, ::u64 uGroup) { return u >= uGroup && u < uGroup + 100; }


inline bool is_file_or_folder(const ::file::enum_type& etype)
{

   return (etype & ::file::e_type_file_or_folder) > ::file::e_type_exists;

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


inline i64 ansi_to_i64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
{

   return strtoll(psz, (::ansi_character **) ppszEnd, iBase);

}


inline u64 ansi_to_u64(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
{

   return strtoull(psz, (::ansi_character **) ppszEnd, iBase);

}


inline i32 ansi_to_i32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
{

#ifdef WINDOWS

   return strtol(psz, (::ansi_character **) ppszEnd, iBase);

#else

   long l = strtol(psz, (::ansi_character **) ppszEnd, iBase);

   if(l > INT_MAX)
   {

      errno = ERANGE;

      return INT_MAX;

   }
   else if(l < INT_MIN)
   {

      errno = ERANGE;

      return INT_MIN;

   }

   return (::i32) l;

#endif

}


inline u32 ansi_to_u32(const ::ansi_character * psz, const ::ansi_character ** ppszEnd, i32 iBase)
{

#ifdef WINDOWS

   return strtoul(psz, (::ansi_character **) ppszEnd, iBase);

#else

   unsigned long ul = strtoul(psz, (::ansi_character **) ppszEnd, iBase);

   if(ul > UINT_MAX)
   {

      errno = ERANGE;

      return UINT_MAX;

   }

   return (::u32) ul;

#endif

}



//template < primitive_integral SECOND, primitive_integral NANOSECOND >
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
//template < primitive_integral SECOND1, primitive_integral NANOSECOND1, primitive_integral SECOND2, primitive_integral NANOSECOND2 >
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
//template < primitive_integral SECOND1, primitive_integral NANOSECOND1, primitive_integral SECOND2, primitive_integral NANOSECOND2 >
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



