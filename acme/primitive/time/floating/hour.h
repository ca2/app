// Created by camilo on 2021-10-05 12:45 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME floating_hour_t :
   public FLOATING_HOUR
{
public:


   using BASE_TYPE = FLOATING_HOUR;


   constexpr floating_hour_t(FLOATING_HOUR hour = {}) : FLOATING_HOUR(hour) {}


   INTEGRAL_SECOND integral_seconds() const { return INTEGRAL_SECOND((::i64)(m_d * 3'600.0)); }
   INTEGRAL_NANOSECOND integral_nanoseconds() const { return INTEGRAL_NANOSECOND((::i64)(fmod(m_d * 3'600.0, 1.0) * 1'000'000'000.0)); }


};


using floating_hour = floating_time < floating_hour_t >;

//
//constexpr FLOATING_HOUR operator "" _h(long double d) { return (FLOATING_HOUR)d; }
//constexpr FLOATING_HOUR operator "" _hour(long double d) { return (FLOATING_HOUR)d; }
//constexpr FLOATING_HOUR operator "" _hours(long double d) { return (FLOATING_HOUR)d; }


inline floating_hour get_floating_hour() { return FLOATING_HOUR(get_floating_nanosecond().m_d / 3'600'000'000'000.0); }


template <  >
inline floating_hour now<floating_hour>()
{

   return get_floating_hour();

}



