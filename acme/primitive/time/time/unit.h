//
//  _unit.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 08:54 BRT
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#pragma once


constexpr integral_nanosecond operator "" _ns(unsigned long long int u) { return integral_nanosecond(u); }


constexpr integral_microsecond operator "" _us(unsigned long long int u) { return integral_microsecond(u); }
constexpr integral_microsecond operator "" _µs(unsigned long long int u) { return integral_microsecond(u); }


constexpr integral_millisecond operator "" _ms(unsigned long long int u) { return integral_millisecond(u); }


constexpr integral_second operator "" _s(unsigned long long int u) { return integral_second(u); }


constexpr integral_minute operator "" _min(unsigned long long int u) { return integral_minute(u); }
constexpr integral_minute operator "" _minute(unsigned long long int u) { return integral_minute(u); }
constexpr integral_minute operator "" _minutes(unsigned long long int u) { return integral_minute(u); }


constexpr integral_hour operator "" _h(unsigned long long int u) { return integral_hour(u); }
constexpr integral_hour operator "" _hour(unsigned long long int u) { return integral_hour(u); }
constexpr integral_hour operator "" _hours(unsigned long long int u) { return integral_hour(u); }


constexpr integral_day operator "" _day(unsigned long long int u) { return integral_day(u); }
constexpr integral_day operator "" _days(unsigned long long int u) { return integral_day(u); }





constexpr floating_nanosecond operator "" _ns(long double d) { return floating_nanosecond(d); }


constexpr floating_microsecond operator "" _us(long double d) { return floating_microsecond(d); }
constexpr floating_microsecond operator "" _µs(long double d) { return floating_microsecond(d); }


constexpr floating_millisecond operator "" _ms(long double d) { return floating_millisecond(d); }


constexpr floating_second operator "" _s(long double d) { return floating_second(d); }


constexpr floating_minute operator "" _min(long double d) { return floating_minute(d); }
constexpr floating_minute operator "" _minute(long double d) { return floating_minute(d); }
constexpr floating_minute operator "" _minutes(long double d) { return floating_minute(d); }


constexpr floating_hour operator "" _h(long double d) { return floating_hour(d); }
constexpr floating_hour operator "" _hour(long double d) { return floating_hour(d); }
constexpr floating_hour operator "" _hours(long double d) { return floating_hour(d); }


constexpr floating_day operator "" _day(long double d) { return floating_day(d); }
constexpr floating_day operator "" _days(long double d) { return floating_day(d); }



