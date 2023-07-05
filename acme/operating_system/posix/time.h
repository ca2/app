//
// Created by camilo on 2020-12-05. <3tbs!!
//
#pragma once


#include "acme/primitive/datetime/earth_time_shift.h"
#include <time.h>



inline timespec __timespec(const class time & time)
{

   timespec timespec;

   timespec.tv_sec = time.m_iSecond;

   timespec.tv_nsec = (long)time.m_iNanosecond;

   return timespec;

}


CLASS_DECL_ACME struct ::tm * tm_struct(struct ::tm * ptm, const ::posix_time & posixtime, const ::earth::time_shift & timeshift = ::earth::time_shift::none());


CLASS_DECL_ACME void copy(::earth::gregorian::time * ptime, const struct ::tm * ptm, ::i64 iNanosecond = 0);


CLASS_DECL_ACME void copy(struct ::tm * ptm, const ::earth::gregorian::time * ptime);


CLASS_DECL_ACME struct tm * GetZoneTm(struct tm * ptm, const ::earth::zone_time & zonetime);




