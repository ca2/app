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
//inline string as_string(const ::ansi_character* psz)
//{
//
//   return string(psz);
//
//}
//
//
//inline string as_string(::ansi_character* psz)
//{
//
//   return string((const ::ansi_character *) psz);
//
//}
//
//
//inline string as_string(const ::wide_character * pwsz)
//{
//
//   return string(pwsz);
//
//}
//
//
//inline string as_string(::wide_character * pwsz)
//{
//
//   return string(pwsz);
//
//}
//
//
//template < >
//inline string as_string(const ansi_string * & p)
//{
//
//   return *p;
//
//}
//
//
//template < >
//inline string as_string(const wide_string *& p)
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


   //inline ::string as_string(const ::wd16_character * psz)
   //{

   //   str = psz;

   //}

   //inline ::string as_string(::wd16_character * const psz)
   //{

   //   str = psz;

   //}


   //inline ::string as_string(const ::wd32_character * psz)
   //{

   //   str = psz;

   //}

   //inline ::string as_string(::wd32_character * const psz)
   //{

   //   str = psz;

   //}


   //   inline ::string as_string(const signed char & ch)
   //{

   //   str = (::ansi_character) ch;

   //}


   //inline void to_string(string& str, const ::ansi_character& ch)
   //{

   //   str = ch;

   //}


   //inline void to_string(string& str, const ::wide_character& wch)
   //{

   //   str = wch;

   //}


   //inline void to_string(string& str, const uchar& uch)
   //{

   //   str = (const ::ansi_character&)uch;

   //}


   //inline void to_string(string& str, const string& strSrc)
   //{

   //   str.assign(strSrc);

   //}


// } // namespace str


#endif // __cplusplus_winrt
