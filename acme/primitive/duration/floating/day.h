// Created by camilo on 2021-10-05 12:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME floating_day_t :
   public FLOATING_DAY
{
public:


   using BASE_TYPE = FLOATING_DAY;


   floating_day_t(FLOATING_DAY day = {}) : FLOATING_DAY(day) {}


   INTEGRAL_SECOND integral_seconds() const { return INTEGRAL_SECOND((::i64)(m_d * 86'400.0)); }
   INTEGRAL_NANOSECOND integral_nanoseconds() const { return INTEGRAL_NANOSECOND((::i64)(fmod(m_d * 86'400.0, 1.0) * 1'000'000'000.0)); }


};


using floating_day = floating_duration < floating_day_t >; 


inline floating_day operator "" _day(long double d) { return (FLOATING_DAY)d; }
inline floating_day operator "" _days(long double d) { return (FLOATING_DAY)d; }


inline floating_day get_floating_day() { return FLOATING_DAY(get_floating_nanosecond().m_d / 86'400'000'000'000.0); }


template <  >
inline floating_day now<floating_day>()
{

   return get_floating_day();

}



