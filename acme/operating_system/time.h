#pragma once


//#include "acme/primitive/datetime/system_time.h"
//#include "acme/primitive/datetime/file_time_span.h"
////#include "acme/primitive/datetime/file_time.h"

struct system_time_t;
class file_time;

CLASS_DECL_ACME i64 __first_tick(void);
CLASS_DECL_ACME i64 __get_tick(void);


class time;


#define ISDST_DAYLIGHT_SAVINGS 1
#define ISDST_NO_DAYLIGHT_SAVINGS 0
#define ISDST_DONT_KNOW -1


void copy(system_time_t & systemtimeUTC, const struct tm & tmUTC);
void copy(struct tm & tmUTC, const system_time_t & systemtimeUTC);


CLASS_DECL_ACME void get_system_time(system_time_t * psystemtime);
CLASS_DECL_ACME void file_time_to_earth_time(posix_time * ptime, const file_time_t* pfile_time, i32 nDST = -1);
CLASS_DECL_ACME void file_time_to_time(class ::time* ptime, const file_time_t* pfiletime);
CLASS_DECL_ACME void system_time_to_earth_time(posix_time * ptime, const system_time_t* psystemtime, i32 nDST = -1);
CLASS_DECL_ACME void system_time_to_file_time(file_time_t * pfile_time, const system_time_t* psystemtime);
CLASS_DECL_ACME void earth_time_to_system_time(system_time_t * psystem_time, const posix_time* ptime);
CLASS_DECL_ACME void earth_time_to_file_time(file_time_t * pfile_time, const posix_time* ptime);
CLASS_DECL_ACME void time_to_file_time(file_time_t* pfiletime, const class ::time* ptime);
CLASS_DECL_ACME void get_system_time_as_file_time(file_time_t* pfile_time);
CLASS_DECL_ACME void file_time_to_system_time(system_time_t* psystemtime, const file_time_t* pfile_time);
CLASS_DECL_ACME void file_time_to_local_file_time(file_time_t* pfile_timeLocal, const file_time_t* pfile_time);
CLASS_DECL_ACME void is_valid_file_time(const file_time_t* pfile_time);
CLASS_DECL_ACME void system_time_to_tm(tm * ptm, const system_time_t * psystemtime);
CLASS_DECL_ACME void tm_to_system_time(system_time_t * psystemtime, const tm * ptm);
CLASS_DECL_ACME void datetime_to_filetime(::file_time_t * pfiletime, const ::earth::time & time);
CLASS_DECL_ACME file_time get_file_time_now();


