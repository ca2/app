#pragma once



CLASS_DECL_ACME i64 strtoi(const char * psz);
CLASS_DECL_ACME i64 strtoi(const widechar * psz);



const ansistring __string_base(const ansichar * psz)
{

   return psz;

}

const wd16string __string_base(const wd16char * psz)
{

   return psz;

}

const wd32string __string_base(const wd32char * psz)
{

   return psz;

}

namespace file
{

   class str;

} // namespace file


#if defined(__APPLE)

#define noexcept

#endif


template <typename T>
inline T FormatArgument(T value) noexcept
{

   return value;

}

#ifdef WINDOWS
inline ::u32 _gen_GetConversionACP()
{

   return CP_UTF8;

}
#endif

class fixed_alloc_array;



template < >
inline uptr uptr_hash < const ansistring & >(const ansistring & ansistr)
{

   return uptr_hash < const ansichar * >(ansistr.c_str());

}


template < >
inline uptr uptr_hash < const widestring & >(const widestring & widestr)
{

   return uptr_hash < const widechar * >(widestr.c_str());

}



template < >
inline uptr uptr_hash < ansistring >(ansistring ansistr)
{

   return uptr_hash < const ansistring & >(ansistr);

}


template < >
inline uptr uptr_hash < widestring >(widestring widestr)
{

   return uptr_hash < const widestring & >(widestr);

}


inline const char * FormatArgument(const string & value) noexcept { return value.c_str(); }


template < typename TYPE_CHAR >
inline string_base < TYPE_CHAR > operator+(const string_base < TYPE_CHAR > & str1, const string_base < TYPE_CHAR > & str2)
{

   string_base < TYPE_CHAR > str;

   return string_concatenate(str, str1, str1.get_length(), str2, str2.get_length());

}


inline ::string operator+(const char * psz, const ::string & str) { return string(psz) + str; }
inline ::string operator+(const char * psz, const ::atom & atom) { return string(psz) + string(atom); }
inline ::string operator+(const char * psz, const ::payload & payload) { return string(psz) + string(payload); }
inline ::string operator+(const char * psz, const ::property& property) { return string(psz) + string(property); }


//inline ::ansistring CLASS_DECL_ACME operator + (ansichar ansich, const ::ansistring & str2)
//{
//
//   ::ansistring str;
//
//   return string_concatenate < ::ansistring >(str, &ansich, sizeof(ansich), str2, str2.get_length());
//
//}
//
//
//inline ::ansistring CLASS_DECL_ACME operator + (wd16char wd16ch, const ::ansistring & str)
//{
//
//   ::ansistring str1(wd16ch);
//
//   return str1 + str;
//
//}
//
//
//inline ::ansistring CLASS_DECL_ACME operator + (wd32char wd32ch, const ::ansistring & str)
//{
//
//   ::ansistring str1(wd32ch);
//
//   return str1 + str;
//
//}


inline ::wstring operator+(const widechar* pszLeft, const ::wstring & wstringableRight)
{

   ::wstring wstrLeft(pszLeft);

   ::wstring wstrRight(wstringableRight);

   return wstrLeft + wstrRight;

}


//inline wstring operator+(const widechar * pwsz1, const wstring & wstr2)
//{
//
//   wstring wstr;
//
//   return string_concatenate < wstring >(wstr, pwsz1, ::str().string_safe_length(pwsz1), wstr2, wstr2.get_length());
//
//}


//template < >
//inline string __string(const ::payload & payload) { return payload; }


//template < >
//inline string __string(const ::file::path & path) { return path.c_str(); }


//template < >
//inline string __string(const ::property & property) { return property; }


#include "___ch_impl.h"
#include "__c_wd16_impl.h"


#ifndef NO_TEMPLATE


inline ::string atom::string() const
{

   if (m_etype == e_type_null)
   {

      return "(null)";

   }
   else if (m_etype == e_type_empty)
   {

      return "(empty)";

   }
   else if (is_text())
   {

      return m_str;

   }
   else if (is_integer())
   {

      return __string(m_i);

   }
   else
   {

      return ::string("(atom : type:") + __string(m_etype) + ",body:" + __string(m_u) + ")";

   }

}


template < >
inline uptr uptr_hash< const atom & >(const atom & key)
{

   return (((uptr)key.m_etype) << 24) ^ (key.is_text() ? uptr_hash(key.m_str.c_str()) : ((((::u32)(uptr)key.m_u) >> 8) & 0xffffffffu));

}


template < >
inline uptr uptr_hash< atom>(atom key)
{

   return uptr_hash<const atom & >((const atom &)key);

}


#endif
