// Recreated by camilo on 2021-10-05 13:15 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]  Thomas Likes number 5
// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME integral_hour_t :
   public INTEGRAL_HOUR
{
public:


   using BASE_TYPE = INTEGRAL_HOUR;


   integral_hour_t(INTEGRAL_HOUR hour = {}) : INTEGRAL_HOUR(hour) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i * 3'600); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND(0); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i * 3'600'000); }


};


using integral_hour = integral_duration < integral_hour_t >;


inline integral_hour operator "" _h(unsigned long long int u) { return (INTEGRAL_HOUR)u; }
inline integral_hour operator "" _hour(unsigned long long int u) { return (INTEGRAL_HOUR)u; }
inline integral_hour operator "" _hours(unsigned long long int u) { return (INTEGRAL_HOUR)u; }


template <  >
inline integral_hour now<integral_hour>()
{

   return get_integral_hour();

}





