// Recreated by camilo on 2021-10-05 13:11 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Refactored/Merged by camilon on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once

//
//class CLASS_DECL_ACME integral_minute_t :
//   public integral_minute
//{
//public:
//
//
//   using BASE_TYPE = integral_minute;
//
//
//   constexpr integral_minute_t(integral_minute minute = {}) : integral_minute(minute) {}
//
//
//   integral_second seconds() const { return integral_second(m_i * 60); }
//   integral_nanosecond nanoseconds() const { return integral_nanosecond(0); }
//   integral_millisecond total_milliseconds() const { return integral_millisecond(m_i * 60'000); }
//
//
////};
//
//
//using integral_minute = integral_time < integral_minute_t >;
//



template <  >
inline integral_minute now<integral_minute>()
{

   return get_integral_minute();

}





