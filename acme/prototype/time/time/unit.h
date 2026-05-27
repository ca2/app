//
//  _unit.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 15/10/21 08:54 BRT
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


// nanosecond unit ηs - greek eta - greek etha
constexpr class time operator""_ηs(::u64 u) { return nanosecond_time(u); }


// microsecond unit μs - greek mu
constexpr class time operator""_μs(::u64 u) { return microsecond_time(u); }


constexpr class time operator""_ms(::u64 u) { return millisecond_time(u); }


constexpr class time operator""_s(::u64 u) { return second_time(u); }


constexpr class time operator""_min(::u64 u) { return minute_time(u); }
constexpr class time operator""_minute(::u64 u) { return minute_time(u); }
constexpr class time operator""_minutes(::u64 u) { return minute_time(u); }


constexpr class time operator""_h(::u64 u) { return hour_time(u); }
constexpr class time operator""_hour(::u64 u) { return hour_time(u); }
constexpr class time operator""_hours(::u64 u) { return hour_time(u); }


constexpr class time operator""_day(::u64 u) { return day_time(u); }
constexpr class time operator""_days(::u64 u) { return day_time(u); }




// unit _nanosecond
constexpr class time operator""_ηs(::f128 d) { return nanosecond_time(d); }


// unit _microsecond
constexpr class time operator""_μs(::f128 d) { return microsecond_time(d); }


constexpr class time operator""_ms(::f128 d) { return millisecond_time(d); }


constexpr class time operator""_s(::f128 d) { return second_time(d); }


constexpr class time operator""_min(::f128 d) { return minute_time(d); }
constexpr class time operator""_minute(::f128 d) { return minute_time(d); }
constexpr class time operator""_minutes(::f128 d) { return minute_time(d); }


constexpr class time operator""_h(::f128 d) { return hour_time(d); }
constexpr class time operator""_hour(::f128 d) { return hour_time(d); }
constexpr class time operator""_hours(::f128 d) { return hour_time(d); }


constexpr class time operator""_day(::f128 d) { return day_time(d); }
constexpr class time operator""_days(::f128 d) { return day_time(d); }



