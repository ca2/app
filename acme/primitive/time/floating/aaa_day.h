// Created by camilo on 2021-10-05 12:45 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once
//
//
//class CLASS_DECL_ACME floating_day_t :
//   public floating_day
//{
//public:
//
//
//   using BASE_TYPE = floating_day;
//
//
//   constexpr floating_day_t(floating_day day = {}) : floating_day(day) {}
//
//
//   integral_second integral_seconds() const { return integral_second((::i64)(m_d * 86'400.0)); }
//   integral_nanosecond integral_nanoseconds() const { return integral_nanosecond((::i64)(fmod(m_d * 86'400.0, 1.0) * 1'000'000'000.0)); }
//
//
//};
//
//
//using floating_day = floating_time < floating_day_t >; 

//
//constexpr floating_day operator "" _day(long double d) { return (floating_day)d; }
//constexpr floating_day operator "" _days(long double d) { return (floating_day)d; }


inline floating_day get_floating_day() { return floating_day(get_floating_nanosecond().m_d / 86'400'000'000'000.0); }


template <  >
inline floating_day now<floating_day>()
{

   return get_floating_day();

}



