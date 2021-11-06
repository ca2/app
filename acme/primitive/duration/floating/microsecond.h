//
// Created by camilo on 2021-10-0512:35 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
//
#pragma once


class CLASS_DECL_ACME floating_microsecond_t :
   public FLOATING_MICROSECOND
{
public:


   using BASE_TYPE = FLOATING_MICROSECOND;


   floating_microsecond_t(FLOATING_MICROSECOND microsecond = {}) : FLOATING_MICROSECOND(microsecond) {}


   INTEGRAL_SECOND integral_seconds() const { return INTEGRAL_SECOND((::i64)(m_d / 1'000'000.0)); }
   INTEGRAL_NANOSECOND integral_nanoseconds() const { return INTEGRAL_NANOSECOND((::i64)(fmod(m_d, 1'000'000.0) * 1'000.0)); }


};


using floating_microsecond = floating_duration < floating_microsecond_t >;


constexpr FLOATING_MICROSECOND operator "" _us(long double d) { return (FLOATING_MICROSECOND)d; }
constexpr FLOATING_MICROSECOND operator "" _μs(long double d) { return (FLOATING_MICROSECOND)d; }


inline floating_microsecond get_floating_microsecond() { return FLOATING_MICROSECOND(get_floating_nanosecond().m_d / 1'000.0); }


template <  >
inline floating_microsecond now<floating_microsecond>()
{

   return get_floating_microsecond();

}



