//
//  _unit.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 15/10/21 08:54 BRT
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


// nanosecond unit ηs - greek eta - greek etha
constexpr class time operator "" _ηs(unsigned long long int u) { return nanosecond_time(u); }


// microsecond unit μs - greek mu
constexpr class time operator "" _μs(unsigned long long int u) { return microsecond_time(u); }


constexpr class time operator "" _ms(unsigned long long int u) { return millisecond_time(u); }


constexpr class time operator "" _s(unsigned long long int u) { return second_time(u); }


constexpr class time operator "" _min(unsigned long long int u) { return minute_time(u); }
constexpr class time operator "" _minute(unsigned long long int u) { return minute_time(u); }
constexpr class time operator "" _minutes(unsigned long long int u) { return minute_time(u); }


constexpr class time operator "" _h(unsigned long long int u) { return hour_time(u); }
constexpr class time operator "" _hour(unsigned long long int u) { return hour_time(u); }
constexpr class time operator "" _hours(unsigned long long int u) { return hour_time(u); }


constexpr class time operator "" _day(unsigned long long int u) { return day_time(u); }
constexpr class time operator "" _days(unsigned long long int u) { return day_time(u); }




// unit _nanosecond
constexpr class time operator "" _ηs(long double d) { return nanosecond_time(d); }


// unit _microsecond
constexpr class time operator "" _μs(long double d) { return microsecond_time(d); }


constexpr class time operator "" _ms(long double d) { return millisecond_time(d); }


constexpr class time operator "" _s(long double d) { return second_time(d); }


constexpr class time operator "" _min(long double d) { return minute_time(d); }
constexpr class time operator "" _minute(long double d) { return minute_time(d); }
constexpr class time operator "" _minutes(long double d) { return minute_time(d); }


constexpr class time operator "" _h(long double d) { return hour_time(d); }
constexpr class time operator "" _hour(long double d) { return hour_time(d); }
constexpr class time operator "" _hours(long double d) { return hour_time(d); }


constexpr class time operator "" _day(long double d) { return day_time(d); }
constexpr class time operator "" _days(long double d) { return day_time(d); }



