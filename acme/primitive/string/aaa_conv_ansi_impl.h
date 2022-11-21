#pragma once


template < typename T >
inline string as_string(const T& t)
{

   string str;

   ::to_string(str, t);

   return str;

}

//
//template < >
//CLASS_DECL_ACME string as_string(const ::enum_status & estatus);
//


template < typename T >
inline string as_string(const T * & p)
{

   string str;

   ::to_string(str, *p);

   return str;

}

//
//inline string as_string(const ansichar* psz)
//{
//
//   return string(psz);
//
//}
//
//
//inline string as_string(ansichar* psz)
//{
//
//   return string((const ansichar *) psz);
//
//}
//
//
//inline string as_string(const widechar * pwsz)
//{
//
//   return string(pwsz);
//
//}
//
//
//inline string as_string(widechar * pwsz)
//{
//
//   return string(pwsz);
//
//}
//
//
//template < >
//inline string as_string(const ansistring * & p)
//{
//
//   return *p;
//
//}
//
//
//template < >
//inline string as_string(const widestring *& p)
//{
//
//   return string(*p);
//
//}
//
//
//template < >
//inline string as_string(const natural_ansistring & naturalansistr)
//{
//
//   return naturalansistr.m_pdata;
//
//}
//
//
//template < >
//inline string as_string(const natural_widestring & naturalwidestr)
//{
//
//   return string(naturalwidestr);
//
//}
//
//

   //inline ::string as_string(const char * psz)
   //{

   //   str = psz;

   //}

   //inline ::string as_string(char * const psz)
   //{

   //   str = psz;

   //}


   //inline ::string as_string(const wd16char * psz)
   //{

   //   str = psz;

   //}

   //inline ::string as_string(wd16char * const psz)
   //{

   //   str = psz;

   //}


   //inline ::string as_string(const wd32char * psz)
   //{

   //   str = psz;

   //}

   //inline ::string as_string(wd32char * const psz)
   //{

   //   str = psz;

   //}


   //   inline ::string as_string(const signed char & ch)
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


#endif // __cplusplus_winrt
