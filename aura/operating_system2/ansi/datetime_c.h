#pragma once


extern "C"
CLASS_DECL_AURA struct tm *gmtime_r(const posix_time *timep,struct tm *result);


#if defined(WINDOWS)

extern "C"
CLASS_DECL_AURA int gettimeofday(struct timeval* tp, void* tz);

#endif

