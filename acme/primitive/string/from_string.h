// Created by camilo on 2022-06-06 20:11 BRT <3ThomasBorregaardSørensen!!
#pragma once


inline  void           from_string(ansichar & ch, const ansichar * psz);
inline  void           from_string(widechar & ch, const ansichar * psz);

inline  void           from_string(i8 & i, const ansichar * psz);
inline  void           from_string(i16 & i, const ansichar * psz);
inline  void           from_string(i32 & i, const ansichar * psz);
inline  void           from_string(i64 & i, const ansichar * psz);
inline  void           from_string(i32 & i, i32 iBase, const ansichar * psz);
inline  void           from_string(i64 & i, i32 iBase, const ansichar * psz);
inline  void           from_string(u8 & i, const ansichar * psz);
inline  void           from_string(u16 & i, const ansichar * psz);
inline  void           from_string(u32 & i, const ansichar * psz);
inline  void           from_string(u64 & i, const ansichar * psz);
inline  void           from_string(u32 & i, i32 iBase, const ansichar * psz);
inline  void           from_string(u64 & i, i32 iBase, const ansichar * psz);

#if defined(__APPLE__) || defined(ANDROID) || defined(RASPBIAN) || defined(WINDOWS)
inline  void           from_string(long & l, const ansichar * psz);
inline  void           from_string(long & l, i32 iBase, const ansichar * psz);
#endif

inline  void           from_string(float & f, const ansichar * psz);
inline  void           from_string(double & d, const ansichar * psz);


inline  void           from_string(ansichar * sz, const ansichar * psz);
inline  void           from_string(wd16char * sz, const ansichar * psz);
inline  void           from_string(wd32char * sz, const ansichar * psz);

template < size_t n >
inline  void           from_string(ansichar sz[n], const ansichar * psz);
template < size_t n >
inline  void           from_string(wd16char sz[n], const ansichar * psz);
template < size_t n >
inline  void           from_string(wd32char sz[n], const ansichar * psz);


inline  void           from_string(::atom & atom, const ansichar * psz);

inline void from_string(::particle & element, const ansichar * psz);



