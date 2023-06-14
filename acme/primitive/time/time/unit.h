//
//  _unit.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 15/10/21 08:54 BRT
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


// nanosecond unit greekethas
constexpr class time operator "" _greekethas(unsigned long long int u) { return integral_nanosecond(u); }


// microsecond unit greekmus
constexpr class time operator "" _greekmus(unsigned long long int u) { return integral_microsecond(u); }


constexpr class time operator "" _ms(unsigned long long int u) { return integral_millisecond(u); }


constexpr class time operator "" _s(unsigned long long int u) { return integral_second(u); }


constexpr class time operator "" _min(unsigned long long int u) { return integral_minute(u); }
constexpr class time operator "" _minute(unsigned long long int u) { return integral_minute(u); }
constexpr class time operator "" _minutes(unsigned long long int u) { return integral_minute(u); }


constexpr class time operator "" _h(unsigned long long int u) { return integral_hour(u); }
constexpr class time operator "" _hour(unsigned long long int u) { return integral_hour(u); }
constexpr class time operator "" _hours(unsigned long long int u) { return integral_hour(u); }


constexpr class time operator "" _day(unsigned long long int u) { return integral_day(u); }
constexpr class time operator "" _days(unsigned long long int u) { return integral_day(u); }




// unit _nanosecond
constexpr class time operator "" _greekethas(long double d) { return floating_nanosecond(d); }


// unit _microsecond
constexpr class time operator "" _greekmus(long double d) { return floating_microsecond(d); }


constexpr class time operator "" _ms(long double d) { return floating_millisecond(d); }


constexpr class time operator "" _s(long double d) { return floating_second(d); }


constexpr class time operator "" _min(long double d) { return floating_minute(d); }
constexpr class time operator "" _minute(long double d) { return floating_minute(d); }
constexpr class time operator "" _minutes(long double d) { return floating_minute(d); }


constexpr class time operator "" _h(long double d) { return floating_hour(d); }
constexpr class time operator "" _hour(long double d) { return floating_hour(d); }
constexpr class time operator "" _hours(long double d) { return floating_hour(d); }


constexpr class time operator "" _day(long double d) { return floating_day(d); }
constexpr class time operator "" _days(long double d) { return floating_day(d); }



