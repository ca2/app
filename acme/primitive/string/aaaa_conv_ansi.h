#pragma once


namespace str
{

   template < typename T >
   inline string  from_int(const T & t);

   template < typename T >
   inline string  from_u(const T & t);


} // namespace str


inline CLASS_DECL_ACME string string_from_strdup(const ::ansi_character * psz);


template < typename T >
inline string as_string(const T& t);

template < typename T >
inline string as_string(const T * & p);


inline string as_string(const ::ansi_character* psz);


inline string as_string(::ansi_character* psz);


inline string as_string(const ::wide_character * pwsz);


inline string as_string(::wide_character * pwsz);


template < >
inline string as_string(const ansi_string * & p);


template < >
inline string as_string(const wide_string *& p);


template < >
inline string as_string(const natural_ansistring & naturalansistr);


template < >
inline string as_string(const natural_widestring & naturalwidestr);


template < typename TYPE >
inline ::string as_string(const TYPE & t);

template < typename TYPE >
inline ::string as_string(const ::matter & t);

inline void to_string(string& str, const bool & b);

inline void to_string(string& str, const ::ansi_character & ansich);
inline void to_string(string& str, const ::wide_character & widech);

inline void to_string(string& str, const ::scoped_string & scopedstr);
inline void to_string(string& str, char * const psz);

inline void to_string(string& str, const ::wd16_character * psz);
inline void to_string(string& str, ::wd16_character * const psz);

inline void to_string(string& str, const ::wd32_character * psz);
inline void to_string(string& str, ::wd32_character * const psz);

inline void to_string(string& str, const signed char & ch);


inline void to_string(string& str, const ::ansi_character& ch);
inline void to_string(string& str, const uchar& uch);


inline void to_string(string& str, const i16& i);
inline void to_string(string& str, const u16& i);
inline void to_string(string& str, const i32& i);
inline void to_string(string& str, const u32& u);
inline void to_string(string& str, const i64& i);
inline void to_string(string& str, const u64& u);


CLASS_DECL_ACME void to_string(string& str, const float& f);
CLASS_DECL_ACME void to_string(string& str, const double& d);


CLASS_DECL_ACME void to_string(string& str, const unsigned long & ul);
CLASS_DECL_ACME void to_string(string& str, const long int & i);


inline void to_string(string& str, const string& strSrc);

inline ::string as_string(const ::atom & atom);

inline ::string as_string(const ::wd16_string & wd16str);

inline ::string as_string(const ::wd32_string & wd16str);



