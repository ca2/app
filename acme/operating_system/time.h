#pragma once


//#include "acme/primitive/datetime/system_time.h"
//#include "acme/primitive/datetime/filetime_span.h"
//#include "acme/primitive/datetime/filetime.h"

struct system_time_t;
class filetime;

CLASS_DECL_ACME i64 __first_tick(void);
CLASS_DECL_ACME i64 __get_tick(void);


class duration;


#define ISDST_DAYLIGHT_SAVINGS 1
#define ISDST_NO_DAYLIGHT_SAVINGS 0
#define ISDST_DONT_KNOW -1


void copy(system_time_t* psystemtimeUTC, const struct tm* ptmUTC);
void copy(struct tm* ptmUTC, const system_time_t* psystemtimeUTC);


CLASS_DECL_ACME void get_system_time(system_time_t* psystemtime);
CLASS_DECL_ACME void file_time_to_time(time_t* ptime, const filetime_t* pfiletime, i32 nDST = -1);
CLASS_DECL_ACME void system_time_to_time(time_t* ptime, const system_time_t* psystemtime, i32 nDST = -1);
CLASS_DECL_ACME void system_time_to_file_time(filetime_t* pfiletime, const system_time_t* psystemtime);
CLASS_DECL_ACME void time_to_system_time(system_time_t* psystem_time, const time_t* ptime);
CLASS_DECL_ACME void time_to_file_time(filetime_t* pfiletime, const time_t* ptime);
CLASS_DECL_ACME void get_system_time_as_file_time(filetime_t* pfiletime);
CLASS_DECL_ACME void file_time_to_system_time(system_time_t* psystemtime, const filetime_t* pfiletime);
CLASS_DECL_ACME void file_time_to_local_file_time(filetime_t* pfiletimeLocal, const filetime_t* pfiletime);
CLASS_DECL_ACME void is_valid_filetime(const filetime_t* pfiletime);
CLASS_DECL_ACME void system_time_to_tm(tm * ptm, const system_time_t * psystemtime);
CLASS_DECL_ACME void tm_to_system_time(system_time_t * psystemtime, const tm * ptm);
CLASS_DECL_ACME filetime get_filetime_now();


