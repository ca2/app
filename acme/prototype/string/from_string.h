// Created by camilo on 2022-06-06 20:11 BRT <3ThomasBorregaardSorensen!!
#pragma once


inline  void           from_string(::ansi_character & ch, const ::ansi_character * psz);
inline  void           from_string(::wide_character & ch, const ::ansi_character * psz);

inline  void           from_string(char & i, const ::ansi_character * psz);
inline  void           from_string(short & i, const ::ansi_character * psz);
inline  void           from_string(int & i, const ::ansi_character * psz);
inline  void           from_string(i64 & i, const ::ansi_character * psz);
inline  void           from_string(int & i, int iBase, const ::ansi_character * psz);
inline  void           from_string(i64 & i, int iBase, const ::ansi_character * psz);
inline  void           from_string(unsigned char & i, const ::ansi_character * psz);
inline  void           from_string(unsigned short & i, const ::ansi_character * psz);
inline  void           from_string(unsigned int & i, const ::ansi_character * psz);
inline  void           from_string(u64 & i, const ::ansi_character * psz);
inline  void           from_string(unsigned int & i, int iBase, const ::ansi_character * psz);
inline  void           from_string(u64 & i, int iBase, const ::ansi_character * psz);

#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)
inline  void           from_string(long & l, const ::ansi_character * psz);
inline  void           from_string(long & l, int iBase, const ::ansi_character * psz);
#endif

inline  void           from_string(float & f, const ::ansi_character * psz);
inline  void           from_string(double & d, const ::ansi_character * psz);


inline  void           from_string(::ansi_character * sz, const ::ansi_character * psz);
inline  void           from_string(::wd16_character * sz, const ::ansi_character * psz);
inline  void           from_string(::wd32_character * sz, const ::ansi_character * psz);

template < size_t n >
inline  void           from_string(::ansi_character sz[n], const ::ansi_character * psz);
template < size_t n >
inline  void           from_string(::wd16_character sz[n], const ::ansi_character * psz);
template < size_t n >
inline  void           from_string(::wd32_character sz[n], const ::ansi_character * psz);


inline  void           from_string(::atom & atom, const ::ansi_character * psz);

inline void from_string(::particle & element, const ::ansi_character * psz);



