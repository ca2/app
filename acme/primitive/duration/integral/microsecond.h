//
// Recreated by camilo on 2021-10-05 13:07 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Refactored/Merged by camilon on 2021-10-04 0:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Created by camilo on 2020-11-16. <3TBS_ [ THE ONLY ] [ THE GOD ] [ THE MAN ]
//
#pragma once


class CLASS_DECL_ACME integral_microsecond_t :
   public INTEGRAL_MICROSECOND
{
public:


   using BASE_TYPE = INTEGRAL_MICROSECOND;


   integral_microsecond_t(INTEGRAL_MICROSECOND microsecond = {}) : INTEGRAL_MICROSECOND(microsecond) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i / 1'000'000); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND((m_i % 1'000'000) * 1'000); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i / 1'000); }


   operator class ::wait const () { return total_milliseconds(); }


};


using integral_microsecond = integral_duration < integral_microsecond_t >;


inline integral_microsecond operator "" _us(unsigned long long int u) { return (INTEGRAL_MICROSECOND)u; }
inline integral_microsecond operator "" _μs(unsigned long long int u) { return (INTEGRAL_MICROSECOND)u; }


template <  >
inline integral_microsecond now<integral_microsecond>()
{

   return get_integral_microsecond();

}









