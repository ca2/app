// Created by camilo on 2022-04-24 04:50 <3ThomasBorregaardSørensen!!
#pragma once


template < typename TYPE >
inline void to_string(string & str, const TYPE & t);

template < typename TYPE >
inline void to_string(string & str, const ::matter & t);


inline void to_string(string & str, const bool & b);


inline void to_string(string & str, const ansichar & ansich);
inline void to_string(string & str, const widechar & widech);


inline void to_string(string & str, const char * psz);
inline void to_string(string & str, char * const psz);


inline void to_string(string & str, const wd16char * psz);
inline void to_string(string & str, wd16char * const psz);


inline void to_string(string & str, const wd32char * psz);
inline void to_string(string & str, wd32char * const psz);


inline void to_string(string & str, const signed char & ch);


inline void to_string(string & str, const ansichar & ch);
inline void to_string(string & str, const uchar & uch);


inline void to_string(string & str, const i16 & i);
inline void to_string(string & str, const u16 & i);
inline void to_string(string & str, const i32 & i);
inline void to_string(string & str, const u32 & u);
inline void to_string(string & str, const i64 & i);
inline void to_string(string & str, const u64 & u);


CLASS_DECL_ACME void to_string(string & str, const float & f);
CLASS_DECL_ACME void to_string(string & str, const double & d);


CLASS_DECL_ACME void to_string(string & str, const unsigned long int & ul);
CLASS_DECL_ACME void to_string(string & str, const long int & i);


inline void to_string(string & str, const ::string & strSrc);
inline void to_string(string & str, const ::atom & atom);
inline void to_string(string & str, const ::wd16string & wd16str);
inline void to_string(string & str, const ::wd32string & wd16str);



