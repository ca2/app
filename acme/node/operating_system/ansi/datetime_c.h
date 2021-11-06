#pragma once


#if defined(WINDOWS)

extern "C"
CLASS_DECL_ACME struct tm *gmtime_r(const time_t *timep,struct tm *result);

extern "C"
CLASS_DECL_ACME int gettimeofday(struct timeval* tp, void* tz);

#endif

