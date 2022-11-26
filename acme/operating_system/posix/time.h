//
// Created by camilo on 2020-12-05. <3tbs!!
//
#pragma once


#include <time.h>


inline timespec __timespec(const class time & time)
{
   
   timespec time;
   
   time.tv_sec = time.m_iSecond;
   
   time.tv_nsec = time.m_iNanosecond;
   
   return time;
   
}



