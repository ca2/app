#pragma once


#include "acme/primitive/primitive/memory_c.h"


//class wstring;
//class string;
//class wstring;




#ifdef WINDOWS
#define unilen wcslen
#else
#define unilen wide_length
#endif

using u16string = string_base < wd16char >;

using u32string = string_base < wd32char >;

#if WCHAR_T_SIZE == 16

using wstring = u16string;

#else

using wstring = u32string;

#endif

//inline wstring operator + (const wstring & wstr1, const wstring & wstr2);
//inline wstring operator + (const wstring & str, const unichar * psz);
//inline wstring operator + (const unichar * psz, const wstring & str);


CLASS_DECL_ACME wstring gen_utf8_to_16(const char * psz);



//class CLASS_DECL_ACME wstring :
//   public wstring
//{
//public:
//
//
//   static const unichar * g_pszWindowsBBQBUNC;
//   static const unichar * g_pszWindowsBBQB;
//   static const unichar * g_pszWindowsBB;
//
//
//   using wstring::string_base;
//   wstring() {}
//   wstring(for_moving) {};
//   inline wstring(const ::string & str);
//   inline wstring(const ::string & str);
//   inline wstring(const char * pszSrc);
//   inline wstring(const char * pszSrc, strsize len);
//   inline wstring(const char ch);
//   inline wstring(strsize repeat, const char ch);
//   inline wstring(const u8 * pszSrc);
//   inline wstring(const u8 * pszSrc, strsize nLength);
//   template < typename TYPE >
//   inline wstring(const tostring < TYPE > & o);
//   ~wstring();
//
//
//   void construct();
//
//   void reserve(strsize n) { __UNREFERENCED_PARAMETER(n); } // wstring does not prereserve
//
//
//   using wstring::operator =;
//   wstring & operator = (const char * psz);
//   wstring & operator = (const ::string & str);
//
//   template < typename TYPE >
//   inline wstring & operator =(const tostring < TYPE > & o);
//
//
//   using string_base < CHAR_TYPE >::operator+=;
//   wstring & operator+=(const char * pszSrc);
//   wstring & operator+=(uchar ch);
//   wstring & operator+=(unichar ch);
//
//   template < typename TYPE >
//   inline wstring & operator +=(const tostring < TYPE > & o);
//
//
//   inline const unichar * c_str() const { return this->operator const unichar *();  }
//
//
//#if defined(_UWP) && defined(__cplusplus_winrt)
//   inline operator String ^ () const { return ref memory_new String(operator const unichar *()); }
//   inline operator String ^ () { return ref memory_new String(operator const unichar *()); }
//#endif
//
//
//   inline unichar operator [] (index iIndex) const
//   {
//
//      return m_psz[iIndex];
//
//   }
//
//
//   inline unichar & operator [] (index iIndex)
//   {
//
//      return m_psz[iIndex];
//
//   }
//
//
//
//   inline i32 Compare(const unichar * psz) const
//   {
//      return wide_compare(m_psz, psz);
//   }
//
//   inline i32 Compare(const wstring &str) const
//   {
//      return wide_compare(m_psz, str);
//   }
//
//   inline i32 CompareNoCase(const unichar * psz) const
//   {
//      return wide_compare_case_insensitive(m_psz, psz);
//   }
//
//   inline i32 CompareNoCase(const wstring &str) const
//   {
//      return wide_compare_case_insensitive(m_psz, str);
//   }
//
//
//   inline bool is_empty() const
//   {
//      return get_length() <= 0 || *m_psz == L'\0';
//   }
//
//
//   inline static wstring empty_string()
//   {
//      unichar push[]= {0};
//      return push;
//   }
//
//
//
//
//   wstring substr(::index iStart, ::count c = -1);
//   wstring & replace(::index iStart,::count c, const unichar * psz);
//
//
//
//   void assign(const unichar* psz);
//   void assign(const char * psz);
//
//
//   strsize find(unichar ch,strsize start = 0,strsize count = -1) const RELEASENOTHROW;
//   strsize find(const unichar * pszSub,strsize start = 0,strsize count = -1,const unichar ** pszTail = nullptr) const RELEASENOTHROW;
//
//   bool empty() const { return is_empty();  }
//
//   using string_base < CHAR_TYPE > ::operator ==;
//   bool operator==(const char * psz2) const;
//   bool operator==(char psz2) const;
//
//   using string_base < CHAR_TYPE > ::operator >;
//   bool operator>(const char * psz2) const;
//   bool operator>(char psz2) const;
//
//   using string_base < CHAR_TYPE > ::operator <;
//   bool operator<(const char * psz2) const;
//   bool operator<(char psz2) const;
//
//
//   using string_base < CHAR_TYPE > ::operator !=;
//   inline bool operator!=(const char * psz) const { return !operator ==(psz); }
//   inline bool operator!=(char ch) const { return !operator ==(ch); }
//
//   using string_base < CHAR_TYPE > ::operator >=;
//   inline bool operator>=(const char * psz) const { return !operator <(psz); }
//   inline bool operator>=(char ch) const { return !operator <(ch); }
//
//   using string_base < CHAR_TYPE > ::operator <=;
//   inline bool operator<=(const char * psz) const { return !operator >(psz); }
//   inline bool operator<=(char ch) const { return !operator >(ch); }
//
//
//};















//template < >
//inline uptr uptr_hash < const wstring & > (const wstring & str)
//{
//
//   return uptr_hash < const wstring & > (str);
//
//}










//inline bool wstring::operator==(const char * psz) const { return operator == (wstring(psz)); }
//inline bool wstring::operator==(char ch) const { return operator==(wstring(ch)); }
//
//inline bool wstring::operator<(const char * psz) const { return operator < (wstring(psz)); }
//inline bool wstring::operator<(char ch) const { return operator < (wstring(ch)); }
//
//inline bool wstring::operator>(const char * psz) const { return operator > (wstring(psz)); }
//inline bool wstring::operator>(char ch) const { return operator>(wstring(ch)); }




inline wstring operator + (const wstring & str1, const wstring & str2)
{

   wstring str;

   return string_concatenate(str, str1, str1.length(), str2, str2.length());

}

template < typename TYPE >
inline CLASS_DECL_ACME wstring operator + (const wstring & wstr, const tostring < TYPE > & o);

template < typename TYPE >
inline CLASS_DECL_ACME wstring operator + (const tostring < TYPE > & o, const wstring & wstr);



//inline wstring operator+(const wstring & wstr1, const wstring & wstr2)
//{
//
//   wstring wstr;
//
//   return string_concatenate(wstr, wstr1, wstr1.get_length(), wstr2, wstr2.get_length());
//
//}
//
//
//inline wstring operator+(const wstring & wstr1, const unichar * pwsz2)
//{
//
//   wstring wstr;
//
//   return string_concatenate(wstr, wstr1, wstr1.get_length(), pwsz2, wstring::string_safe_length(pwsz2));
//
//}
//
//
//inline wstring  operator+(const unichar * pwsz1, const wstring & wstr2)
//{
//
//   wstring wstr;
//
//   return string_concatenate(wstr, pwsz1, wstring::string_safe_length(pwsz1), wstr2, wstr2.get_length());
//
//}
