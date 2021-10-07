// Recreated by camilo on 2021-10-05 13:11 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME integral_minute_t :
   public INTEGRAL_MINUTE
{
public:


   using BASE_TYPE = INTEGRAL_MINUTE;


   integral_minute_t(INTEGRAL_MINUTE minute = {}) : INTEGRAL_MINUTE(minute) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i * 60); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND(0); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i * 60'000); }


};


using integral_minute = integral_duration < integral_minute_t >;


inline integral_minute operator "" _min(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }
inline integral_minute operator "" _minute(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }
inline integral_minute operator "" _minutes(unsigned long long int u) { return (INTEGRAL_MINUTE)u; }


template <  >
inline integral_minute now<integral_minute>()
{

   return get_integral_minute();

}





