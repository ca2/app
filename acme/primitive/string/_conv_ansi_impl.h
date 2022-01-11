#pragma once


#ifndef __cplusplus_winrt


template < typename T >
inline string __string(const T& t)
{

   string str;

   ::to_string(str, t);

   return str;

}


template < >
CLASS_DECL_ACME string __string(const ::enum_status & estatus);


template < >
inline string __string(const void & estatus)
{

   return __string(estatus.m_estatus);

}


template < typename T >
inline string __string(const T * & p)
{

   string str;

   ::to_string(str, *p);

   return str;

}


inline string __string(const ansichar* psz)
{

   return string(psz);

}


inline string __string(ansichar* psz)
{

   return string((const ansichar *) psz);

}


inline string __string(const widechar * pwsz)
{

   return string(pwsz);

}


inline string __string(widechar * pwsz)
{

   return string(pwsz);

}


template < >
inline string __string(const ansistring * & p)
{

   return *p;

}


template < >
inline string __string(const widestring *& p)
{

   return string(*p);

}


template < >
inline string __string(const natural_ansistring & naturalansistr)
{

   return naturalansistr.m_pdata;

}


template < >
inline string __string(const natural_widestring & naturalwidestr)
{

   return string(naturalwidestr);

}



   inline void to_string(string & str, const char * psz)
   {

      str = psz;

   }

   inline void to_string(string & str, char * const psz)
   {

      str = psz;

   }


   inline void to_string(string & str, const wd16char * psz)
   {

      str = psz;

   }

   inline void to_string(string & str, wd16char * const psz)
   {

      str = psz;

   }


   inline void to_string(string & str, const wd32char * psz)
   {

      str = psz;

   }

   inline void to_string(string & str, wd32char * const psz)
   {

      str = psz;

   }


      inline void to_string(string & str, const signed char & ch)
   {

      str = (ansichar) ch;

   }


   inline void to_string(string& str, const ansichar& ch)
   {

      str = ch;

   }


   inline void to_string(string& str, const widechar& wch)
   {

      str = wch;

   }


   inline void to_string(string& str, const uchar& uch)
   {

      str = (const ansichar&)uch;

   }


   inline void to_string(string& str, const string& strSrc)
   {

      str.assign(strSrc);

   }


// } // namespace str


#endif // __cplusplus_winrt
