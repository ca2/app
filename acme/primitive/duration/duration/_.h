// Created by camilo on 2021-10-05 12:54 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


#include "duration.h"


#include "nanosecond.h"
#include "microsecond.h"
#include "millisecond.h"


#include "second.h"


#include "minute.h"
#include "hour.h"
#include "day.h"


inline bool operator < (const ::INTEGRAL_MILLISECOND & integralmillisecond, const ::duration & duration)
{

   return integralmillisecond < duration.integral_millisecond();

}



