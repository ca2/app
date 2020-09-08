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
//inline string & string_base < TYPE_CHAR >::operator +=(const tostring < TYPE > & tostring) { return operator +=(::__str(tostring)); }


//template < typename TYPE_CHAR >
//template < typename TYPE >
//inline wstring & wstring::operator +=(const tostring < TYPE > & tostring) { return operator +=(::__str(tostring)); }


//template < typename TYPE1, typename TYPE2 >
//inline CLASS_DECL_ACME string operator + (const tostring < TYPE1 > & tostring1, const tostring < TYPE2 > & tostring2) { return __str(tostring1) + __str(tostring2); }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const string & str, const tostring < TYPE > & tostring) { return str + __str(tostring); }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const tostring < TYPE > & tostring, const string & str) { return __str(tostring) + str; }


//template < typename TYPE >
//inline CLASS_DECL_ACME wstring operator + (const wstring & wstr, const tostring < TYPE > & o) { return wstr + wstring(o); }


//template < typename TYPE >
//inline CLASS_DECL_ACME wstring operator + (const tostring < TYPE > & o, const wstring & wstr) { return wstring(o) + wstr; }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const tostring < TYPE > & tostring, const char * p) { return __str(tostring) + p; }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const char * p, const tostring < TYPE > & tostring) { return p + __str(tostring); }


//template < typename TYPE >
//inline CLASS_DECL_ACME string operator + (const tostring < TYPE > & tostring, const wchar_t * p) { return __str(tostring) + string(p); }


//template < typename TYPE >
//inline CLASS_DECL_ACME wstring operator + (const wchar_t * p, const tostring < TYPE > & tostring) { return wstring(p) + wstring(__str(tostring)); }





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

         __throw(invalid_argument_exception("not hexadecimal digit"));

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


template < typename TYPE_CHAR >
template < typename TYPE >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator=(const TYPE & t)
{

   return operator = (__str(t));

}


template < typename TYPE_CHAR >
template < typename TYPE >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const TYPE & t)
{

   return operator += (__str(t));

}


template < typename TYPE_CHAR, typename TYPE >
inline string_base < TYPE_CHAR > operator +(const string_base < TYPE_CHAR > & str, const TYPE & t)
{

   return str.operator + (__str(t));

}






template < typename STRINGABLE >
inline void __exchange_as_string(stream & s, STRINGABLE & stringable)
{

   string str;

   if (s.is_storing())
   {

      ::str::from(str, stringable);

      s.exchange(id::type_empty, str);

   }
   else
   {

      s.exchange(id::type_empty, str);

      ::str::to(stringable, str);

   }

}
