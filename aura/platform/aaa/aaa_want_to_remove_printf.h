// printf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#pragma once

CLASS_DECL_AURA int printf_dup(const ::string &format, ...);
CLASS_DECL_AURA int wprintf_dup(const ::wide_character *format, ...);
CLASS_DECL_AURA int vprintf_dup(const ::string &format, va_list args);
CLASS_DECL_AURA int vwprintf_dup(const ::wide_character *format, va_list args);

#ifdef APPLEOS
int ecvt_r(double, int, int *__restrict, int *__restrict, char * sz, size_t size); /* LEGACY */
int fcvt_r(double, int, int *__restrict, int *__restrict, char * sz, size_t size); /* LEGACY */
#endif



