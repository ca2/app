// Created by camilo on 2022-06-06 20:11 BRT <3ThomasBorregaardSørensen!!
#pragma once


inline  void           from_string(::ansi_character & ch, const ::ansi_character * psz);
inline  void           from_string(::wide_character & ch, const ::ansi_character * psz);

inline  void           from_string(i8 & i, const ::ansi_character * psz);
inline  void           from_string(i16 & i, const ::ansi_character * psz);
inline  void           from_string(i32 & i, const ::ansi_character * psz);
inline  void           from_string(i64 & i, const ::ansi_character * psz);
inline  void           from_string(i32 & i, i32 iBase, const ::ansi_character * psz);
inline  void           from_string(i64 & i, i32 iBase, const ::ansi_character * psz);
inline  void           from_string(u8 & i, const ::ansi_character * psz);
inline  void           from_string(u16 & i, const ::ansi_character * psz);
inline  void           from_string(u32 & i, const ::ansi_character * psz);
inline  void           from_string(u64 & i, const ::ansi_character * psz);
inline  void           from_string(u32 & i, i32 iBase, const ::ansi_character * psz);
inline  void           from_string(u64 & i, i32 iBase, const ::ansi_character * psz);

#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBERRYPIOS) || defined(WINDOWS)
inline  void           from_string(long & l, const ::ansi_character * psz);
inline  void           from_string(long & l, i32 iBase, const ::ansi_character * psz);
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



