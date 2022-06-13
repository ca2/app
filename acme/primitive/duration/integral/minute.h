// Recreated by camilo on 2021-10-05 13:11 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME integral_minute_t :
   public INTEGRAL_MINUTE
{
public:


   using BASE_TYPE = INTEGRAL_MINUTE;


   constexpr integral_minute_t(INTEGRAL_MINUTE minute = {}) : INTEGRAL_MINUTE(minute) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i * 60); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND(0); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i * 60'000); }


};


using integral_minute = integral_duration < integral_minute_t >;




template <  >
inline integral_minute now<integral_minute>()
{

   return get_integral_minute();

}





