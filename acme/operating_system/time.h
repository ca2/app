#pragma once


#include "acme/prototype/datetime/file_time.h"
#include "acme/prototype/datetime/system_time.h"
#ifdef WINDOWS
#include "acme/operating_system/windows/time.h"
#else
#include "acme/operating_system/ansi/windows_time.h"
#endif


struct system_time_t;
class file_time;

CLASS_DECL_ACME long long __first_tick(void);
CLASS_DECL_ACME long long __get_tick(void);


class time;


#define ISDST_DAYLIGHT_SAVINGS 1
#define ISDST_NO_DAYLIGHT_SAVINGS 0
#define ISDST_DONT_KNOW -1


void copy(system_time * psystemtimeUTC, const struct tm * ptmUTC);
void copy(struct tm * ptmUTC, const system_time * psystemtimeUTC);


//CLASS_DECL_ACME system_time as_system_time(const tm * ptm);
/// class ::time constructor accepts const ::file_time &
///CLASS_DECL_ACME class ::time as_time(const ::file_time & filetime);




CLASS_DECL_ACME bool is_valid_file_time(const ::file_time & filetime);
//CLASS_DECL_ACME void system_time_to_tm(tm * ptm, const system_time & systemtime);











