#pragma once


extern "C"
CLASS_DECL_APEX struct tm *gmtime_r(const time_t *timep,struct tm *result);


#if defined(WINDOWS)

extern "C"
CLASS_DECL_APEX int gettimeofday(struct timeval* tp, void* tz);

#endif

