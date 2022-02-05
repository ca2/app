#pragma once


namespace str
{

   template < typename T >
   inline string  from_int(const T & t);

   template < typename T >
   inline string  from_u(const T & t);


} // namespace str


inline CLASS_DECL_ACME string string_from_strdup(const ansichar * psz);


template < typename T >
inline string __string(const T& t);

template < typename T >
inline string __string(const T * & p);


inline string __string(const ansichar* psz);


inline string __string(ansichar* psz);


inline string __string(const widechar * pwsz);


inline string __string(widechar * pwsz);


template < >
inline string __string(const ansistring * & p);


template < >
inline string __string(const widestring *& p);


template < >
inline string __string(const natural_ansistring & naturalansistr);


template < >
inline string __string(const natural_widestring & naturalwidestr);


#define __cstr(t) (__string(t).c_str())


// namespace str
// {


template < typename TYPE >
inline void to_string(string & str, const TYPE & t);

template < typename TYPE >
inline void to_string(string & str, const ::matter & t);

//#ifdef _UWP
//inline void to_string(string& str, Platform::String^ strSource);
//#endif

inline void to_string(string& str, const bool & b);

inline void to_string(string& str, const ansichar & ansich);
inline void to_string(string& str, const widechar & widech);

inline void to_string(string& str, const char * psz);
inline void to_string(string& str, char * const psz);

inline void to_string(string& str, const wd16char * psz);
inline void to_string(string& str, wd16char * const psz);

inline void to_string(string& str, const wd32char * psz);
inline void to_string(string& str, wd32char * const psz);

inline void to_string(string& str, const signed char & ch);


inline void to_string(string& str, const ansichar& ch);
inline void to_string(string& str, const uchar& uch);


inline void to_string(string& str, const i16& i);
inline void to_string(string& str, const u16& i);
inline void to_string(string& str, const i32& i);
inline void to_string(string& str, const u32& u);
inline void to_string(string& str, const i64& i);
inline void to_string(string& str, const u64& u);
inline void to_string(string& str, const unsigned long& ul);
CLASS_DECL_ACME void to_string(string& str, const float& f);
CLASS_DECL_ACME void to_string(string& str, const double& d);


#if defined(ANDROID) || defined(RASPBIAN)

CLASS_DECL_ACME void to_string(string& str, long int i);

#endif


#ifdef WINDOWS

inline void to_string(string& str, const long& i);
inline void to_string(string& str, const ::i32& i);
inline void to_string(string& str, const ::u32& i);

#endif

#ifdef __APPLE__

inline void to_string(string& str, const long& l);

#endif

inline void to_string(string& str, const string& strSrc);

inline void to_string(string & str, const ::atom & atom);

inline void to_string(string & str, const ::wd16string & wd16str);

inline void to_string(string & str, const ::wd32string & wd16str);


// } // namespace str



