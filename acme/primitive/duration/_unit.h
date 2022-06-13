//
//  _unit.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 08:54 BRT
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


constexpr integral_nanosecond operator "" _ns(unsigned long long int u) { return INTEGRAL_NANOSECOND(u); }


constexpr integral_microsecond operator "" _us(unsigned long long int u) { return INTEGRAL_MICROSECOND(u); }
constexpr integral_microsecond operator "" _µs(unsigned long long int u) { return INTEGRAL_MICROSECOND(u); }


constexpr integral_millisecond operator "" _ms(unsigned long long int u) { return INTEGRAL_MILLISECOND(u); }


constexpr integral_second operator "" _s(unsigned long long int u) { return INTEGRAL_SECOND(u); }


constexpr integral_minute operator "" _min(unsigned long long int u) { return INTEGRAL_MINUTE(u); }
constexpr integral_minute operator "" _minute(unsigned long long int u) { return INTEGRAL_MINUTE(u); }
constexpr integral_minute operator "" _minutes(unsigned long long int u) { return INTEGRAL_MINUTE(u); }


constexpr integral_hour operator "" _h(unsigned long long int u) { return INTEGRAL_HOUR(u); }
constexpr integral_hour operator "" _hour(unsigned long long int u) { return INTEGRAL_HOUR(u); }
constexpr integral_hour operator "" _hours(unsigned long long int u) { return INTEGRAL_HOUR(u); }


constexpr integral_day operator "" _day(unsigned long long int u) { return INTEGRAL_DAY(u); }
constexpr integral_day operator "" _days(unsigned long long int u) { return INTEGRAL_DAY(u); }





constexpr floating_nanosecond operator "" _ns(long double d) { return FLOATING_NANOSECOND(d); }


constexpr floating_microsecond operator "" _us(long double d) { return FLOATING_MICROSECOND(d); }
constexpr floating_microsecond operator "" _µs(long double d) { return FLOATING_MICROSECOND(d); }


constexpr floating_millisecond operator "" _ms(long double d) { return FLOATING_MILLISECOND(d); }


constexpr floating_second operator "" _s(long double d) { return FLOATING_SECOND(d); }


constexpr floating_minute operator "" _min(long double d) { return FLOATING_MINUTE(d); }
constexpr floating_minute operator "" _minute(long double d) { return FLOATING_MINUTE(d); }
constexpr floating_minute operator "" _minutes(long double d) { return FLOATING_MINUTE(d); }


constexpr floating_hour operator "" _h(long double d) { return FLOATING_HOUR(d); }
constexpr floating_hour operator "" _hour(long double d) { return FLOATING_HOUR(d); }
constexpr floating_hour operator "" _hours(long double d) { return FLOATING_HOUR(d); }


constexpr floating_day operator "" _day(long double d) { return FLOATING_DAY(d); }
constexpr floating_day operator "" _days(long double d) { return FLOATING_DAY(d); }



