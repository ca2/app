// printf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#pragma once

CLASS_DECL_ACME int printf_dup(const_char_pointer format, ...);
CLASS_DECL_ACME int wprintf_dup(const ::wide_character *format, ...);
CLASS_DECL_ACME int vprintf_dup(const_char_pointer format, va_list args);
CLASS_DECL_ACME int vwprintf_dup(const ::wide_character *format, va_list args);

#ifdef __APPLE__
int ecvt_r(double, int, int *__restrict, int *__restrict, char * sz, size_t size); /* LEGACY */
int fcvt_r(double, int, int *__restrict, int *__restrict, char * sz, size_t size); /* LEGACY */
#endif



