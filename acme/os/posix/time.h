//
// Created by camilo on 2020-12-05. <3tbs!!
//
#pragma once


#include <time.h>


inline timespec __timespec(const ::millis & millis)
{
   timespec time;
   time.tv_sec = millis.m_iMilliseconds / 1'000;
   time.tv_nsec = (millis.m_iMilliseconds % 1'000) * 1'000'000;
   return time;
}



