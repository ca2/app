// Created by camilo on 2022-11-08 23:10 <3ThomasBorregaardSorensen!!
#pragma once




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


inline bool __is_valid_string(const widechar* pwsz, memsize nMaxLength)
{

   return ::__is_valid_address(pwsz, nMaxLength);

}


inline bool __is_valid_string(const char* psz, memsize nMaxLength)
{

   return ::__is_valid_address(psz, nMaxLength);

}



inline int_bool address_overlaps(const void* pszDst, const void* pszSrc, strsize srclen)
{

   return (((byte*)pszSrc) <= ((byte*)pszDst) && ((byte*)pszSrc) + srclen > ((byte*)pszDst))
      || (((byte*)pszDst) <= ((byte*)pszSrc) && ((byte*)pszDst) + srclen > ((byte*)pszSrc));

}



template < typename TYPE > inline TYPE*& __defer_new(TYPE*& p)
{

   if (!p) p = memory_new TYPE;

   return p;

}


inline const ::particle * context_trace_object() { return general_trace_object(); }


#ifdef CPP17

template <typename PRED, typename ... Args >
inline bool _returns_true(PRED pred, const true_type& predicate_returns_void, bool bOnVoid, Args... args)
{
   pred(args...);
   return bOnVoid;
}

template <typename PRED, typename ... Args >
inline bool _returns_true(PRED pred, const false_type& predicate_returns_void, bool, Args... args)
{
   return (bool)pred(args...);
}

template <typename PRED, typename ... Args >
inline bool returns_true(PRED pred, bool bOnVoid, Args... args)
{

   return _returns_true(pred, is_void<decltype(pred(args...))>, bOnVoid, args...);

}

template <typename PRED, typename ... Args >
inline bool _returns_false(PRED pred, const true_type& predicate_returns_void, bool bOnVoid, Args... args)
{
   pred(args...);
   return bOnVoid;
}

template <typename PRED, typename ... Args >
inline bool _returns_false(PRED pred, const false_type& predicate_returns_void, bool, Args... args)
{
   return !(bool)pred(args...);
}

template <typename PRED, typename ... Args >
inline bool returns_false(PRED pred, bool bOnVoid, Args... args)
{

   return _returns_false(pred, is_void < decltype(pred(args...)) >, bOnVoid, args...);

}

#endif



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





template < typename TYPE >
inline bool is_reference_null(const TYPE& t)
{

   return is_null(&t);

}


template < typename TYPE >
inline bool is_reference_set(const TYPE& t)
{

   return is_set(&t);

}



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


template < class T >
inline void __dynamic_cast(T*& ptarget, T* psource)
{

   ptarget = psource;

}


template < class T , typename T2 >
inline void __dynamic_cast(T * & ptarget, T2 * psource)
{

   ptarget = dynamic_cast < T * >(psource);

}



