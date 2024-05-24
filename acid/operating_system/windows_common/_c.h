
#pragma once


extern "C"
CLASS_DECL_ACID struct tm * gmtime_r(const time_t * timep, struct tm * result);

extern "C"
CLASS_DECL_ACID int gettimeofday(struct timeval * tp, void * tz);



