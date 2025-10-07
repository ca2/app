// Created by camilo on 2022-06-06 20:11 BRT <3ThomasBorregaardSorensen!!
#pragma once


inline  void           from_string(::ansi_character & ch, const_char_pointer psz);
inline  void           from_string(::wide_character & ch, const_char_pointer psz);

inline  void           from_string(char & i, const_char_pointer psz);
inline  void           from_string(short & i, const_char_pointer psz);
inline  void           from_string(int & i, const_char_pointer psz);
inline  void           from_string(long long & i, const_char_pointer psz);
inline  void           from_string(int & i, int iBase, const_char_pointer psz);
inline  void           from_string(long long & i, int iBase, const_char_pointer psz);
inline  void           from_string(unsigned char & i, const_char_pointer psz);
inline  void           from_string(unsigned short & i, const_char_pointer psz);
inline  void           from_string(unsigned int & i, const_char_pointer psz);
inline  void           from_string(unsigned long long & i, const_char_pointer psz);
inline  void           from_string(unsigned int & i, int iBase, const_char_pointer psz);
inline  void           from_string(unsigned long long & i, int iBase, const_char_pointer psz);

#if defined(__APPLE__) || defined(__ANDROID__) || defined(RASPBERRYPIOS) || defined(WINDOWS)
inline  void           from_string(long & l, const_char_pointer psz);
inline  void           from_string(long & l, int iBase, const_char_pointer psz);
#endif

inline  void           from_string(float & f, const_char_pointer psz);
inline  void           from_string(double & d, const_char_pointer psz);


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



