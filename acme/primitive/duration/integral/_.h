// Created by camilo on 2021-10-05 12:54 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once





CLASS_DECL_ACME INTEGRAL_NANOSECOND get_integral_nanosecond();

inline INTEGRAL_MICROSECOND get_integral_microsecond() { return INTEGRAL_MICROSECOND{(::i64) (get_integral_nanosecond().m_i / 1'000)}; }

inline INTEGRAL_MILLISECOND get_integral_millisecond() { return INTEGRAL_MILLISECOND{(::i64)(get_integral_nanosecond().m_i / 1'000'000)}; }

inline INTEGRAL_SECOND get_integral_second() { return INTEGRAL_SECOND{(::i64) (get_integral_nanosecond().m_i / 1'000'000'000)}; }

inline INTEGRAL_MINUTE get_integral_minute() { return INTEGRAL_MINUTE{(::i64) (get_integral_nanosecond().m_i / 60'000'000'000)}; }

inline INTEGRAL_HOUR get_integral_hour() { return INTEGRAL_HOUR{(::i64)(get_integral_nanosecond().m_i / 3'600'000'000'000)}; }

inline INTEGRAL_DAY get_integral_day() { return INTEGRAL_DAY{(::i64) (get_integral_nanosecond().m_i / 86'400'000'000'000)}; }






#include "duration.h"


#include "nanosecond.h"
#include "microsecond.h"
#include "millisecond.h"


#include "second.h"


#include "minute.h"
#include "hour.h"
#include "day.h"







