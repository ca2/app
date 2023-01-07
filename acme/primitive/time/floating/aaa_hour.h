// Created by camilo on 2021-10-05 12:45 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once

//
//class CLASS_DECL_ACME floating_hour_t :
//   public floating_hour
//{
//public:
//
//
//   using BASE_TYPE = floating_hour;
//
//
//   constexpr floating_hour_t(floating_hour hour = {}) : floating_hour(hour) {}
//
//
//   integral_second integral_seconds() const { return integral_second((::i64)(m_d * 3'600.0)); }
//   integral_nanosecond integral_nanoseconds() const { return integral_nanosecond((::i64)(fmod(m_d * 3'600.0, 1.0) * 1'000'000'000.0)); }
//
//
//};
//
//
//using floating_hour = floating_time < floating_hour_t >;
//
////
//constexpr floating_hour operator "" _h(long double d) { return (floating_hour)d; }
//constexpr floating_hour operator "" _hour(long double d) { return (floating_hour)d; }
//constexpr floating_hour operator "" _hours(long double d) { return (floating_hour)d; }


inline floating_hour get_floating_hour() { return floating_hour(get_floating_nanosecond().m_d / 3'600'000'000'000.0); }


template <  >
inline floating_hour now<floating_hour>()
{

   return get_floating_hour();

}



