#pragma once


#ifdef LINUX

typedef unsigned long HCURSOR;
#define hcursor_null ((HCURSOR) 0)

#else

#if !defined(WINDOWS)
typedef void* HCURSOR;
#endif

//#define hcursor_null ((hcursor) nullptr)

#endif



