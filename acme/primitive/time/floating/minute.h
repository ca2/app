// Created by camilo on 2021-10-05 12:35 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once

//
//class CLASS_DECL_ACME floating_minute_t :
//   public floating_minute
//{
//public:
//
//
//   using BASE_TYPE = floating_minute;
//
//
//   constexpr floating_minute_t(floating_minute minute = {}) : floating_minute(minute) {}
//
//
//   integral_second integral_seconds() const { return integral_second((::i64)(m_d * 60.0)); }
//   integral_nanosecond integral_nanoseconds() const { return integral_nanosecond((::i64)(fmod(m_d * 60.0, 1.0) * 1'000'000'000.0)); }
//
//
//};
//
//
//using floating_minute = floating_time < floating_minute_t >;


//constexpr floating_minute operator "" _min(long double d) { return (floating_minute)d; }
//constexpr floating_minute operator "" _minute(long double d) { return (floating_minute)d; }
//constexpr floating_minute operator "" _minutes(long double d) { return (floating_minute)d; }


inline floating_minute get_floating_minute() { return floating_minute(get_floating_nanosecond().m_d / 60'000'000'000.0); }
       

template <  >
inline floating_minute now<floating_minute>()
{

   return get_floating_minute();

}



