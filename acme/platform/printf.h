// printf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#pragma once

CLASS_DECL_ACME ::i32 printf_dup(const_char_pointer format, ...);
CLASS_DECL_ACME ::i32 wprintf_dup(const ::wide_character *format, ...);
CLASS_DECL_ACME ::i32 vprintf_dup(const_char_pointer format, va_list args);
CLASS_DECL_ACME ::i32 vwprintf_dup(const ::wide_character *format, va_list args);

#ifdef __APPLE__
::i32 ecvt_r(::f64, ::i32, ::i32 *__restrict, ::i32 *__restrict, char_pointer sz, size_t size); /* LEGACY */
::i32 fcvt_r(::f64, ::i32, ::i32 *__restrict, ::i32 *__restrict, char_pointer sz, size_t size); /* LEGACY */
#endif



