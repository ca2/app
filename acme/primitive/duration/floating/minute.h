// Created by camilo on 2021-10-05 12:35 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME floating_minute_t :
   public FLOATING_MINUTE
{
public:


   using BASE_TYPE = FLOATING_MINUTE;


   floating_minute_t(FLOATING_MINUTE minute = {}) : FLOATING_MINUTE(minute) {}


   INTEGRAL_SECOND integral_seconds() const { return INTEGRAL_SECOND((::i64)(m_d * 60.0)); }
   INTEGRAL_NANOSECOND integral_nanoseconds() const { return INTEGRAL_NANOSECOND((::i64)(fmod(m_d * 60.0, 1.0) * 1'000'000'000.0)); }


};


using floating_minute = floating_duration < floating_minute_t >;


inline floating_minute operator "" _min(long double d) { return (FLOATING_MINUTE)d; }
inline floating_minute operator "" _minute(long double d) { return (FLOATING_MINUTE)d; }
inline floating_minute operator "" _minutes(long double d) { return (FLOATING_MINUTE)d; }


inline floating_minute get_floating_minute() { return FLOATING_MINUTE(get_floating_nanosecond().m_d / 60'000'000'000.0); }
       

template <  >
inline floating_minute now<floating_minute>()
{

   return get_floating_minute();

}



