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

    timespec.tv_nsec = time.m_iNanosecond;
   
   return timespec;
   
}


CLASS_DECL_ACME struct ::tm *tm_struct(struct ::tm *ptm, const ::posix_time & posixtime, const ::earth::time_shift &timeshift = ::earth::time_shift::none());




inline void copy(::earth::gregorian::time * ptime, const struct ::tm *ptm, ::i64 iNanosecond = 0)
{

    ptime->m_iNanoSecond = iNanosecond;
    ptime->m_iSecond = ptm->tm_sec;
    ptime->m_iMinute = ptm->tm_min;
    ptime->m_iHour = ptm->tm_hour;
    ptime->m_iDay = ptm->tm_mday;
    ptime->m_iMonth = ptm->tm_mon;
    ptime->m_iYear = ptm->tm_year + 1900;
    ptime->m_iDayOfWeek = ptm->tm_wday;

}



inline void copy(struct ::tm *ptm, const ::earth::gregorian::time * ptime)
{

    ptm->tm_sec = ptime->m_iSecond;
    ptm->tm_min = ptime->m_iMinute;
    ptm->tm_hour = ptime->m_iHour;
    ptm->tm_mday = ptime->m_iDay;
    ptm->tm_mon = ptime->m_iMonth;
    ptm->tm_year = ptime->m_iYear - 1900;
    ptm->tm_wday = ptime->m_iDayOfWeek;

}


CLASS_DECL_ACME struct tm* GetZoneTm(struct tm* ptm, const ::earth::zonetime & zonetime);




