#pragma once

#include "_conv_ansi_impl.h"


//template < typename TYPE >
//inline string::string(const tostring < TYPE > & tostring) { ::from(*this, tostring); }

//template < typename TYPE >
//inline wstring::wstring(const tostring < TYPE > & tostring) { ::from(*this, tostring); }


//template < typename TYPE_CHAR >
//template < typename TYPE >
//inline string & string_base < TYPE_CHAR >::operator =(const tostring < TYPE > & tostring) { tostring.to_string(*this); return *this; }


//template < typename TYPE_CHAR >
//template < typename TYPE >
//inline wstring & wstring::operator =(const tostring < TYPE > & tostring) { ::from(*this, tostring); return *this; }


//template < typename TYPE_CHAR >
//template < typename TYPE >
//inline string & string_base < TYPE_CHAR >::operator +=(const tostring < TYPE > & tostring) { return operator +=(::__string(tostring)); }


//template < typename TYPE_CHAR >
//template < typename TYPE >
//inline wstring & wstring::operator +=(const tostring < TYPE > & tostring) { return operator +=(::__string(tostring)); }


//template < typename TYPE1, typename TYPE2 >
//inline CLASS_DECL_ACME string operator + (const tostring < TYPE1 > & tostring1, const tostring < TYPE2 > & tostring2) { return __string(tostring1) + __string(tostring2); }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const ::string & str, const tostring < TYPE > & tostring) { return str + __string(tostring); }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const tostring < TYPE > & tostring, const ::string & str) { return __string(tostring) + str; }


//template < typename TYPE >
//inline CLASS_DECL_ACME wstring operator + (const wstring & wstr, const tostring < TYPE > & o) { return wstr + wstring(o); }


//template < typename TYPE >
//inline CLASS_DECL_ACME wstring operator + (const tostring < TYPE > & o, const wstring & wstr) { return wstring(o) + wstr; }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const tostring < TYPE > & tostring, const char * p) { return __string(tostring) + p; }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const char * p, const tostring < TYPE > & tostring) { return p + __string(tostring); }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const tostring < TYPE > & tostring, const wchar_t * p) { return __string(tostring) + string(p); }


//template < typename TYPE >
//inline CLASS_DECL_ACME wstring operator + (const wchar_t * p, const tostring < TYPE > & tostring) { return wstring(p) + wstring(__string(tostring)); }



namespace hex
{


   inline CLASS_DECL_ACME i32 to(char ch)
   {

      if (ch >= '0' && ch <= '9')
      {

         return ch - '0';

      }
      else if (ch >= 'a' && ch <= 'f')
      {

         return ch - 'a' + 10;

      }
      else if (ch >= 'A' && ch <= 'F')
      {

         return ch - 'A' + 10;

      }
      else
      {

         throw "not hexadecimal digit";

      }

   }


} // namespace hex


//template < typename TYPE_CHAR >
//template < typename TYPE >
//inline string_base < TYPE_CHAR >::string_base(const TYPE & t) :
//   string_base(nullptr)
//{
//
//   ::str::assign(*this, t);
//
//}


//template < typename TYPE_CHAR >
//template < typename TYPE >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const TYPE & t)
//{
//
//   return operator = (__string(t));
//
//}


//template < typename TYPE_CHAR >
//template < typename TYPE >
//inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const TYPE & t)
//{
//
//   return operator += (__string(t));
//
//}


#ifndef __cplusplus_winrt


template < typename TYPE_CHAR >
template < typename TYPE >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const TYPE & t) const
{

   return this->operator + (__string(t));

}


template < typename STRINGABLE >
inline void __exchange_as_string(stream & s, STRINGABLE & stringable)
{

   string str;

   if (s.is_storing())
   {

      ::str::from(str, (const STRINGABLE &) stringable);

      s.exchange(id::e_type_empty, str);

   }
   else
   {

      s.exchange(id::e_type_empty, str);

      ::from_string(stringable, (const string &) str);

   }

}


#endif



