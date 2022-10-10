#pragma once

//#pragma once


//template < typename T >
//inline string __string(const T & t)
//{
//
//   string str;
//
//   ::to_string(str, t);
//
//   return str;
//
//}
//
//
//template < >
//CLASS_DECL_ACME string __string(const ::enum_status & estatus);
//

//
//template < typename T >
//inline string __string(const T *& p)
//{
//
//   string str;
//
//   ::to_string(str, *p);
//
//   return str;
//
//}
//
//
//inline string __string(const ansichar* psz)
//{
//
//   return string(psz);
//
//}
//
//
//inline string __string(ansichar* psz)
//{
//
//   return string((const ansichar *) psz);
//
//}
//
//
//inline string __string(const widechar * pwsz)
//{
//
//   return string(pwsz);
//
//}
//
//
//inline string __string(widechar * pwsz)
//{
//
//   return string(pwsz);
//
//}
//
//
//template < >
//inline string __string(const ansistring * & p)
//{
//
//   return *p;
//
//}
//
//
//template < >
//inline string __string(const widestring *& p)
//{
//
//   return string(*p);
//
//}
//
//
//template < >
//inline string __string(const natural_ansistring & naturalansistr)
//{
//
//   return naturalansistr.m_pdata;
//
//}
//
//
//template < >
//inline string __string(const natural_widestring & naturalwidestr)
//{
//
//   return string(naturalwidestr);
//
//}
//
//

   //inline ::string __string(const char * psz)
   //{

   //   str = psz;

   //}

   //inline ::string __string(char * const psz)
   //{

   //   str = psz;

   //}


   //inline ::string __string(const wd16char * psz)
   //{

   //   str = psz;

   //}

   //inline ::string __string(wd16char * const psz)
   //{

   //   str = psz;

   //}


   //inline ::string __string(const wd32char * psz)
   //{

   //   str = psz;

   //}

   //inline ::string __string(wd32char * const psz)
   //{

   //   str = psz;

   //}


   //   inline ::string __string(const signed char & ch)
   //{

   //   str = (ansichar) ch;

   //}


   //inline void to_string(string& str, const ansichar& ch)
   //{

   //   str = ch;

   //}


   //inline void to_string(string& str, const widechar& wch)
   //{

   //   str = wch;

   //}


   //inline void to_string(string& str, const uchar& uch)
   //{

   //   str = (const ansichar&)uch;

   //}


   //inline void to_string(string& str, const string& strSrc)
   //{

   //   str.assign(strSrc);

   //}


// } // namespace str


//#endif // __cplusplus_winrt


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
//   ::str().assign(*this, t);
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


//#ifndef __cplusplus_winrt



template < typename TYPE_CHAR >
template < typename TYPE >
inline string_base < TYPE_CHAR > & string_base < TYPE_CHAR >::operator+=(const TYPE & t)
{

   string_base < TYPE_CHAR > str(t);

   return append(str);

}


template < typename TYPE_CHAR >
template < typename TYPE >
inline string_base < TYPE_CHAR > string_base < TYPE_CHAR >::operator +(const TYPE & t) const
{

   string_base < TYPE_CHAR > strConcatenation(*this);

   string_base < TYPE_CHAR > str(t);

   strConcatenation += str;

   return strConcatenation;

}



//template < typename STRINGABLE >
//inline void __exchange_as_string(stream & s, STRINGABLE & stringable)
//{
//
//   string str;
//
//   if (s.is_storing())
//   {
//
//      ::to_string(str, (const STRINGABLE &)stringable);
//
//      s.exchange(atom::e_type_empty, str);
//
//   }
//   else
//   {
//
//      s.exchange(atom::e_type_empty, str);
//
//      ::from_string(stringable, (const string &)str);
//
//   }
//
//}


//template < typename TYPE_CHAR >
//template < non_pointer NONPOINTER >
//inline string_base < TYPE_CHAR >::string_base(const NONPOINTER & nonpointer) :
//   string_base(__string(nonpointer))
//{
//
//
//}



