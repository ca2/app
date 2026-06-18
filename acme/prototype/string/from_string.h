// Created by camilo on 2022-06-06 20:11 BRT <3ThomasBorregaardSorensen!!
#pragma once


inline  void           from_string(::ansi_character & ch, const_char_pointer psz);
inline  void           from_string(::wide_character & ch, const_char_pointer psz);

inline  void           from_string(::i8 & i, const_char_pointer psz);
inline  void           from_string(::i16 & i, const_char_pointer psz);
inline  void           from_string(::i32 & i, const_char_pointer psz);
inline  void           from_string(::i64 & i, const_char_pointer psz);
inline  void           from_string(::i32 & i, ::i32 iBase, const_char_pointer psz);
inline  void           from_string(::i64 & i, ::i32 iBase, const_char_pointer psz);
inline  void           from_string(::u8 & i, const_char_pointer psz);
inline  void           from_string(::u16 & i, const_char_pointer psz);
inline  void           from_string(::u32 & i, const_char_pointer psz);
inline  void           from_string(::u64 & i, const_char_pointer psz);
inline  void           from_string(::u32 & i, ::i32 iBase, const_char_pointer psz);
inline  void           from_string(::u64 & i, ::i32 iBase, const_char_pointer psz);

#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS) || defined(WINDOWS)
inline  void           from_string(long & l, const_char_pointer psz);
inline  void           from_string(long & l, ::i32 iBase, const_char_pointer psz);
#endif

inline  void           from_string(::f32 & f, const_char_pointer psz);
inline  void           from_string(::f64 & d, const_char_pointer psz);


inline  void           from_string(::ansi_character * sz, const_char_pointer psz);
inline  void           from_string(::wd16_character * sz, const_char_pointer psz);
inline  void           from_string(::wd32_character * sz, const_char_pointer psz);

template < size_t n >
inline  void           from_string(::ansi_character sz[n], const_char_pointer psz);
template < size_t n >
inline  void           from_string(::wd16_character sz[n], const_char_pointer psz);
template < size_t n >
inline  void           from_string(::wd32_character sz[n], const_char_pointer psz);


inline  void           from_string(::atom & atom, const_char_pointer psz);

inline void from_string(::particle & element, const_char_pointer psz);



