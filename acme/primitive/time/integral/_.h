#pragma once





CLASS_DECL_ACME integral_nanosecond get_integral_nanosecond();

inline integral_microsecond get_integral_microsecond() { return integral_microsecond{(::i64) (get_integral_nanosecond().m_i / 1'000)}; }

inline integral_millisecond get_integral_millisecond() { return integral_millisecond{(::i64)(get_integral_nanosecond().m_i / 1'000'000)}; }

inline integral_second get_integral_second() { return integral_second{(::i64) (get_integral_nanosecond().m_i / 1'000'000'000)}; }

inline integral_minute get_integral_minute() { return integral_minute{(::i64) (get_integral_nanosecond().m_i / 60'000'000'000)}; }

inline integral_hour get_integral_hour() { return integral_hour{(::i64)(get_integral_nanosecond().m_i / 3'600'000'000'000)}; }

inline integral_day get_integral_day() { return integral_day{(::i64) (get_integral_nanosecond().m_i / 86'400'000'000'000)}; }



#include "acme/primitive/time/integral/time.h"


#include "nanosecond.h"
#include "microsecond.h"
#include "millisecond.h"


#include "second.h"


#include "minute.h"
#include "hour.h"
#include "day.h"







