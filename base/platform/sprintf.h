#pragma once



CLASS_DECL_AURA i32 sprintf_dup(char *buffer, const char *format, ...);
CLASS_DECL_AURA i32 _snprintf_dup(char *dest, size_t n, const char *fmt, ...);
CLASS_DECL_AURA i32 vsnprintf_dup(char *dest, size_t n, const char *fmt, va_list args);
CLASS_DECL_AURA i32 vsprintf_dup(char *dest, const char *fmt, va_list args);

CLASS_DECL_AURA i32 swnprintf_dup(widechar *dest, size_t n, const widechar *fmt, ...);
CLASS_DECL_AURA i32 vswprintf_dup(widechar *dest, size_t n, const widechar *fmt, va_list args);
