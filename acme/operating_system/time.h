#pragma once


//#include "acme/primitive/datetime/system_time.h"
//#include "acme/primitive/datetime/file_time_span.h"
#include "acme/primitive/datetime/file_time.h"

struct system_time_t;
class file_time;

CLASS_DECL_ACME i64 __first_tick(void);
CLASS_DECL_ACME i64 __get_tick(void);


class time;


#define ISDST_DAYLIGHT_SAVINGS 1
#define ISDST_NO_DAYLIGHT_SAVINGS 0
#define ISDST_DONT_KNOW -1


void copy(system_time * psystemtimeUTC, const struct tm * ptmUTC);
void copy(struct tm * ptmUTC, const system_time * psystemtimeUTC);


//CLASS_DECL_ACME system_time as_system_time(const tm * ptm);
CLASS_DECL_ACME class ::time as_time(const ::file_time & filetime);


CLASS_DECL_ACME bool is_valid_file_time(const ::file_time & filetime);
//CLASS_DECL_ACME void system_time_to_tm(tm * ptm, const system_time & systemtime);

