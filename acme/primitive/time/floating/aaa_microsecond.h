//
// Created by camilo on 2021-10-0512:35 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
//
#pragma once

//
//class CLASS_DECL_ACME floating_microsecond_t :
//   public floating_microsecond
//{
//public:
//
//
//   using BASE_TYPE = floating_microsecond;
//
//
//   constexpr floating_microsecond_t(floating_microsecond microsecond = {}) : floating_microsecond(microsecond) {}
//
//
//   integral_second integral_seconds() const { return integral_second((::i64)(m_d / 1'000'000.0)); }
//   integral_nanosecond integral_nanoseconds() const { return integral_nanosecond((::i64)(fmod(m_d, 1'000'000.0) * 1'000.0)); }
//
//
//};
//
//
//using floating_microsecond = floating_time < floating_microsecond_t >;

//
//constexpr floating_microsecond operator "" _us(long double d) { return (floating_microsecond)d; }
//constexpr floating_microsecond operator "" _μs(long double d) { return (floating_microsecond)d; }


inline floating_microsecond get_floating_microsecond() { return floating_microsecond(get_floating_nanosecond().m_d / 1'000.0); }


template <  >
inline floating_microsecond now<floating_microsecond>()
{

   return get_floating_microsecond();

}



