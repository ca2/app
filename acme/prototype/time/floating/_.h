// Created by camilo on 2021-10-05 12:55 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once


//#include "acme/prototype/time/floating/time.h"


inline double double_nanosecond() { return (double)::long_long_nanosecond(); }

inline double double_microsecond() { return double_nanosecond() / 1'000.0; }

inline double double_millisecond() { return double_nanosecond() / 1'000'000.0; }

inline double double_second() { return double_nanosecond() / 1'000'000'000.0; }

inline double double_minute() { return double_nanosecond() / 60'000'000'000.0; }

inline double double_hour() { return double_nanosecond() / 3'600'000'000'000.0; }

inline double double_day() { return double_nanosecond() / 86'400'000'000'000.0; }



//inline float f32_nanosecond() { return (float)::long_long_nanosecond(); }
//
//inline float f32_microsecond() { return f32_nanosecond() / 1'000.0f; }
//
//inline float f32_millisecond() { return f32_nanosecond() / 1'000'000.0f; }
//
//inline float f32_second() { return f32_nanosecond() / 1'000'000'000.0f; }
//
//inline float f32_minute() { return f32_nanosecond() / 60'000'000'000.0f; }
//
//inline float f32_hour() { return f32_nanosecond() / 3'600'000'000'000.0f; }
//
//inline float f32_day() { return f32_nanosecond() / 86'400'000'000'000.0f; }
//
//
//#include "nanosecond.h"
//#include "microsecond.h"
//#include "millisecond.h"
//
//
//#include "second.h"
//
//
//#include "minute.h"
//#include "hour.h"
//#include "day.h"
//
//
//
