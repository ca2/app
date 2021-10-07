//
// Created by camilo on 2020-12-05. <3tbs!!
//
#pragma once


#include <time.h>


inline timespec __timespec(const ::duration & duration)
{
   timespec time;
   time.tv_sec = ::duration.m_i / 1'000;
   time.tv_nsec = (::duration.m_i % 1'000) * 1'000'000;
   return time;
}



