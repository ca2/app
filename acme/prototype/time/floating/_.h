// Created by camilo on 2021-10-05 12:55 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once


//#include "acme/prototype/time/floating/time.h"


inline double f64_nanosecond() { return (double)::i64_nanosecond(); }

inline double f64_microsecond() { return f64_nanosecond() / 1'000.0; }

inline double f64_millisecond() { return f64_nanosecond() / 1'000'000.0; }

inline double f64_second() { return f64_nanosecond() / 1'000'000'000.0; }

inline double f64_minute() { return f64_nanosecond() / 60'000'000'000.0; }

inline double f64_hour() { return f64_nanosecond() / 3'600'000'000'000.0; }

inline double f64_day() { return f64_nanosecond() / 86'400'000'000'000.0; }



//inline float f32_nanosecond() { return (float)::i64_nanosecond(); }
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
