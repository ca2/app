// Recreated by camilo on 2021-10-05 13:15 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]  Thomas Likes number 5
// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once

//
//class CLASS_DECL_ACME integral_hour_t :
//   public integral_hour
//{
//public:
//
//
//   using BASE_TYPE = integral_hour;
//
//
//   constexpr integral_hour_t(integral_hour hour = {}) : integral_hour(hour) {}
//
//
//   integral_second seconds() const { return integral_second(m_i * 3'600); }
//   integral_nanosecond nanoseconds() const { return integral_nanosecond(0); }
//   integral_millisecond total_milliseconds() const { return integral_millisecond(m_i * 3'600'000); }
//
//
//};
//
//
//using integral_hour = integral_time < integral_hour_t >;
//

template <  >
inline integral_hour now<integral_hour>()
{

   return get_integral_hour();

}





