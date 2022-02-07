#pragma once


extern "C"
CLASS_DECL_CORE struct tm *gmtime_r(const time_t *timep,struct tm *result);


#if defined(WINDOWS)

extern "C"
CLASS_DECL_CORE int gettimeofday(struct timeval* tp, void* tz);

#endif

