//
// Created by camilo on 2020-12-05. <3tbs!!
//
#pragma once


#include "acme/prototype/datetime/earth_time_shift.h"
#include <time.h>



inline timespec __timespec(const class time & time)
{

   timespec timespec;

   timespec.tv_sec = time.m_iSecond;

   timespec.tv_nsec = (long)time.m_iNanosecond;

   return timespec;

}


CLASS_DECL_ACME struct ::tm * tm_struct(struct ::tm * ptm, const ::posix_time & posixtime, const class ::time & timeshift = {});


CLASS_DECL_ACME void copy(::earth::gregorian_time * ptime, const struct ::tm * ptm, long long iNanosecond = 0);


CLASS_DECL_ACME void copy(struct ::tm * ptm, const ::earth::gregorian_time * ptime);


CLASS_DECL_ACME struct tm * GetZoneTm(struct tm * ptm, const ::earth::zone_time & zonetime);


CLASS_DECL_ACME void copy(struct timespec * ptimespec, const class ::time * ptime);


CLASS_DECL_ACME void copy(class ::time * ptime, const struct timespec * ptimespec);


CLASS_DECL_ACME time_t portable_timegm_threadsafe(const struct tm *tm);



