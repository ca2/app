// sprintf.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
//#include <stdarg.h>

#define EOF     (-1)


int sprintf_dup(char *buffer, const char *format, ...)
{
    int retValue;
    va_list argptr;

    va_start(argptr, format);
    retValue = vsprintf(buffer, format, argptr);
    va_end(argptr);

    return retValue;
}

int snprintf_dup(char *dest, size_t n, const char *fmt, ...)
{
	__UNREFERENCED_PARAMETER(n);

	va_list args;
	va_start(args, fmt);
	int retValue = vsprintf(dest, fmt, args);
	va_end(args);
	return retValue;
}

int vsnprintf_dup(char *dest, size_t n, const char *fmt, va_list args)
{
	__UNREFERENCED_PARAMETER(n);
	return vsprintf(dest, fmt, args);
}

int vsprintf_dup(char *dest, const char *fmt, va_list args)
{
   #ifdef WINDOWS_DESKTOP
	int retValue = wvsprintfA(dest, fmt, args);
   #elif defined(UNIVERSAL_WINDOWS)
	int retValue = vsprintf(dest, fmt, args);
	#else
	int retValue = vsprintf(dest, fmt, args);
	#endif
   return retValue;
}













int swnprintf_dup(::wide_character *dest, size_t n, const ::wide_character *fmt, ...)
{

	va_list args;
	va_start(args, fmt);
	int retValue = vswprintf(dest, n, fmt, args);
	va_end(args);
	return retValue;

}


int vswprintf_dup(::wide_character *dest, size_t n, const ::wide_character *fmt, va_list args)
{

#ifdef WINDOWS_DESKTOP
	int retValue = wvsprintfW(dest, fmt, args);
#elif defined(UNIVERSAL_WINDOWS)
   int retValue = vswprintf_s(dest, n, fmt, args);
#else
	int retValue = vswprintf(dest, n, fmt, args);
#endif
   return retValue;

}
