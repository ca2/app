#pragma once


#ifdef LINUX

typedef ulong HCURSOR;
#define hcursor_null ((HCURSOR) 0)

#else

#if !defined(WINDOWS)
typedef void* HCURSOR;
#endif

//#define hcursor_null ((hcursor) nullptr)

#endif



