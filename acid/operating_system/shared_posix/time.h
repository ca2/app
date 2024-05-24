//
// Created by camilo on 2020-12-05. <3tbs!!
//
#pragma once


#include "acid/primitive/datetime/earth_time_shift.h"
#include <time.h>



inline timespec __timespec(const class time & time)
{

   timespec timespec;

   timespec.tv_sec = time.m_iSecond;

   timespec.tv_nsec = (long)time.m_iNanosecond;

   return timespec;

}


CLASS_DECL_ACID struct ::tm * tm_struct(struct ::tm * ptm, const ::posix_time & posixtime, const class ::time & timeshift = {});


CLASS_DECL_ACID void copy(::earth::gregorian_time * ptime, const struct ::tm * ptm, ::i64 iNanosecond = 0);


CLASS_DECL_ACID void copy(struct ::tm * ptm, const ::earth::gregorian_time * ptime);


CLASS_DECL_ACID struct tm * GetZoneTm(struct tm * ptm, const ::earth::zone_time & zonetime);




