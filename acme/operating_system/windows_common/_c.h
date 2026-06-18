
#pragma once


extern "C"
CLASS_DECL_ACME struct tm * gmtime_r(const time_t * timep, struct tm * result);

extern "C"
CLASS_DECL_ACME ::i32 gettimeofday(struct timeval * tp, void * tz);



