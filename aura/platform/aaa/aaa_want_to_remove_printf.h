// printf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#pragma once

CLASS_DECL_AURA i32 printf_dup(const ::string &format, ...);
CLASS_DECL_AURA i32 wprintf_dup(const widechar *format, ...);
CLASS_DECL_AURA i32 vprintf_dup(const ::string &format, va_list args);
CLASS_DECL_AURA i32 vwprintf_dup(const widechar *format, va_list args);

#ifdef APPLEOS
i32 ecvt_r(double, int, int *__restrict, int *__restrict, char * sz, size_t size); /* LEGACY */
i32 fcvt_r(double, int, int *__restrict, int *__restrict, char * sz, size_t size); /* LEGACY */
#endif



