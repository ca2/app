//
//  _unit.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21 08:54 BRT
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


constexpr INTEGRAL_NANOSECOND operator "" _ns(unsigned long long int u) { return INTEGRAL_NANOSECOND(u); }


constexpr INTEGRAL_MICROSECOND operator "" _us(unsigned long long int u) { return INTEGRAL_MICROSECOND(u); }
constexpr INTEGRAL_MICROSECOND operator "" _µs(unsigned long long int u) { return INTEGRAL_MICROSECOND(u); }


constexpr INTEGRAL_MILLISECOND operator "" _ms(unsigned long long int u) { return INTEGRAL_MILLISECOND(u); }


constexpr INTEGRAL_SECOND operator "" _s(unsigned long long int u) { return INTEGRAL_SECOND(u); }


constexpr INTEGRAL_MINUTE operator "" _min(unsigned long long int u) { return INTEGRAL_MINUTE(u); }
constexpr INTEGRAL_MINUTE operator "" _minute(unsigned long long int u) { return INTEGRAL_MINUTE(u); }
constexpr INTEGRAL_MINUTE operator "" _minutes(unsigned long long int u) { return INTEGRAL_MINUTE(u); }


constexpr INTEGRAL_HOUR operator "" _h(unsigned long long int u) { return INTEGRAL_HOUR(u); }
constexpr INTEGRAL_HOUR operator "" _hour(unsigned long long int u) { return INTEGRAL_HOUR(u); }
constexpr INTEGRAL_HOUR operator "" _hours(unsigned long long int u) { return INTEGRAL_HOUR(u); }


constexpr INTEGRAL_DAY operator "" _day(unsigned long long int u) { return INTEGRAL_DAY(u); }
constexpr INTEGRAL_DAY operator "" _days(unsigned long long int u) { return INTEGRAL_DAY(u); }

