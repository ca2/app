// Recreated by camilo on 2021-10-05 13:17 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]  
// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME integral_day_t :
   public INTEGRAL_DAY
{
public:


   using BASE_TYPE = INTEGRAL_DAY;


   integral_day_t(INTEGRAL_DAY day = {}) : INTEGRAL_DAY(day) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i * 86'400); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND(0); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i *86'400'000); }

   
};


using integral_day = integral_duration < integral_day_t >;


constexpr INTEGRAL_DAY operator "" _day(unsigned long long int u) { return (INTEGRAL_DAY)u; }
constexpr INTEGRAL_DAY operator "" _days(unsigned long long int u) { return (INTEGRAL_DAY)u; }


template <  >
inline integral_day now<integral_day>()
{

   return get_integral_day();

}




