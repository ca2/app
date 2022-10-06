// Created by camilo on 2022-04-24 04:50 <3ThomasBorregaardSørensen!!
#pragma once


template < typename TYPE >
void to_string(string & str, const TYPE & t);

template < typename TYPE >
void to_string(string & str, const ::matter & t);


CLASS_DECL_ACME void to_string(string & str, const bool & b);


CLASS_DECL_ACME void to_string(string & str, const ansichar & ansich);
CLASS_DECL_ACME void to_string(string & str, const widechar & widech);


CLASS_DECL_ACME void to_string(string & str, const char * psz);
CLASS_DECL_ACME void to_string(string & str, char * const psz);


CLASS_DECL_ACME void to_string(string & str, const wd16char * psz);
CLASS_DECL_ACME void to_string(string & str, wd16char * const psz);


CLASS_DECL_ACME void to_string(string & str, const wd32char * psz);
CLASS_DECL_ACME void to_string(string & str, wd32char * const psz);


CLASS_DECL_ACME void to_string(string & str, const signed char & ch);


CLASS_DECL_ACME void to_string(string & str, const ansichar & ch);
CLASS_DECL_ACME void to_string(string & str, const uchar & uch);


CLASS_DECL_ACME void to_string(string & str, const i16 & i);
CLASS_DECL_ACME void to_string(string & str, const u16 & i);
CLASS_DECL_ACME void to_string(string & str, const i32 & i);
CLASS_DECL_ACME void to_string(string & str, const u32 & u);
CLASS_DECL_ACME void to_string(string & str, const i64 & i);
CLASS_DECL_ACME void to_string(string & str, const u64 & u);


CLASS_DECL_ACME void to_string(string & str, const float & f);
CLASS_DECL_ACME void to_string(string & str, const double & d);


CLASS_DECL_ACME void to_string(string & str, const unsigned long int & ul);
CLASS_DECL_ACME void to_string(string & str, const long int & i);


CLASS_DECL_ACME void to_string(string & str, const ::string & strSrc);
CLASS_DECL_ACME void to_string(string & str, const ::atom & atom);
CLASS_DECL_ACME void to_string(string & str, const ::wd16string & wd16str);
CLASS_DECL_ACME void to_string(string & str, const ::wd32string & wd16str);



