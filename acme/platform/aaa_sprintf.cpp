// sprintf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
//#include <stdarg.h>

#define EOF     (-1)


i32 sprintf_dup(char *buffer, const char *format, ...)
{
    i32 retValue;
    va_list argptr;

    va_start(argptr, format);
    retValue = vsprintf(buffer, format, argptr);
    va_end(argptr);

    return retValue;
}

i32 snprintf_dup(char *dest, size_t n, const char *fmt, ...)
{
	__UNREFERENCED_PARAMETER(n);

	va_list args;
	va_start(args, fmt);
	i32 retValue = vsprintf(dest, fmt, args);
	va_end(args);
	return retValue;
}

i32 vsnprintf_dup(char *dest, size_t n, const char *fmt, va_list args)
{
	__UNREFERENCED_PARAMETER(n);
	return vsprintf(dest, fmt, args);
}

i32 vsprintf_dup(char *dest, const char *fmt, va_list args)
{
   #ifdef WINDOWS_DESKTOP
	i32 retValue = wvsprintfA(dest, fmt, args);
   #elif defined(_UWP)
	i32 retValue = vsprintf(dest, fmt, args);
	#else
	i32 retValue = vsprintf(dest, fmt, args);
	#endif
   return retValue;
}













i32 swnprintf_dup(::wide_character *dest, size_t n, const ::wide_character *fmt, ...)
{

	va_list args;
	va_start(args, fmt);
	i32 retValue = vswprintf(dest, n, fmt, args);
	va_end(args);
	return retValue;

}


i32 vswprintf_dup(::wide_character *dest, size_t n, const ::wide_character *fmt, va_list args)
{

#ifdef WINDOWS_DESKTOP
	i32 retValue = wvsprintfW(dest, fmt, args);
#elif defined(_UWP)
   i32 retValue = vswprintf_s(dest, n, fmt, args);
#else
	i32 retValue = vswprintf(dest, n, fmt, args);
#endif
   return retValue;

}
