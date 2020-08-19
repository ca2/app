#pragma once


namespace str
{

   template < typename T >
   inline string  from_int(const T & t);

   template < typename T >
   inline string  from_uint(const T & t);

   inline CLASS_DECL_AURA string from_strdup(const ansichar * psz);

} // namespace str


template < typename T >
inline string __str(const T& t);

template < typename T >
inline string __str(const T * & p);


inline string __str(const ansichar* psz);


inline string __str(ansichar* psz);


inline string __str(const widechar * pwsz);


inline string __str(widechar * pwsz);


template < >
inline string __str(const ansistring * & p);


template < >
inline string __str(const widestring *& p);


template < >
inline string __str(const natural_ansistring & naturalansistr);


template < >
inline string __str(const natural_widestring & naturalwidestr);


#define __cstr(t) (__str(t).c_str())


namespace str
{


   template < typename TYPE >
   inline void from(string & str, const TYPE & t);

   template < typename TYPE >
   inline void from(string & str, const ::generic_object & t);


   inline void from(string& str, const bool & b);

   inline void from(string& str, const ansichar & ansich);
   inline void from(string& str, const widechar & widech);

   inline void from(string& str, const char * psz);
   inline void from(string& str, char * const psz);

   inline void from(string& str, const wd16char * psz);
   inline void from(string& str, wd16char * const psz);

   inline void from(string& str, const wd32char * psz);
   inline void from(string& str, wd32char * const psz);

   inline void from(string& str, const signed char & ch);


   inline void from(string& str, const ansichar& ch);
   inline void from(string& str, const uchar& uch);


   inline void from(string& str, const i16& i);
   inline void from(string& str, const u16& i);
   inline void from(string& str, const i32& i);
   inline void from(string& str, const u32& ui);
   inline void from(string& str, const i64& i);
   inline void from(string& str, const u64& ui);
   inline void from(string& str, const unsigned long& ul);
   CLASS_DECL_AURA void from(string& str, const float& f);
   CLASS_DECL_AURA void from(string& str, const double& d);


   #if defined(ANDROID) || defined(RASPBIAN)

   CLASS_DECL_AURA void from(string& str, long int i);

   #endif


   #ifdef WINDOWS

   inline void from(string& str, const long& i);
   inline void from(string& str, const LONG& i);
   inline void from(string& str, const DWORD& i);

   #endif

   #ifdef __APPLE__

   inline void from(string& str, const long& l);

   #endif

   inline void from(string& str, const string& strSrc);

   inline void from(string & str, const ::id & id);

   inline void from(string & str, const ::wd16string & wd16str);

   inline void from(string & str, const ::wd32string & wd16str);


} // namespace str



