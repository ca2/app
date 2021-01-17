#pragma once


template < typename T >
inline string __str(const T& t)
{

   string str;

   ::str::from(str, t);

   return str;

}


template < typename T >
inline string __str(const T * & p)
{

   string str;

   ::str::from(str, *p);

   return str;

}


inline string __str(const ansichar* psz)
{

   return string(psz);

}


inline string __str(ansichar* psz)
{

   return string((const ansichar *) psz);

}


inline string __str(const widechar * pwsz)
{

   return string(pwsz);

}


inline string __str(widechar * pwsz)
{

   return string(pwsz);

}


template < >
inline string __str(const ansistring * & p)
{

   return *p;

}


template < >
inline string __str(const widestring *& p)
{

   return string(*p);

}


template < >
inline string __str(const natural_ansistring & naturalansistr)
{

   return naturalansistr.m_pdata;

}


template < >
inline string __str(const natural_widestring & naturalwidestr)
{

   return string(naturalwidestr);

}


namespace str
{


   inline void from(string & str, const char * psz)
   {

      str = psz;

   }

   inline void from(string & str, char * const psz)
   {

      str = psz;

   }


   inline void from(string & str, const wd16char * psz)
   {

      str = psz;

   }

   inline void from(string & str, wd16char * const psz)
   {

      str = psz;

   }


   inline void from(string & str, const wd32char * psz)
   {

      str = psz;

   }

   inline void from(string & str, wd32char * const psz)
   {

      str = psz;

   }


      inline void from(string & str, const signed char & ch)
   {

      str = (ansichar) ch;

   }


   inline void from(string& str, const ansichar& ch)
   {

      str = ch;

   }


   inline void from(string& str, const widechar& wch)
   {

      str = wch;

   }


   inline void from(string& str, const uchar& uch)
   {

      str = (const ansichar&)uch;

   }


   inline void from(string& str, const string& strSrc)
   {

      str.assign(strSrc);

   }


} // namespace str



