// Recreated by camilo on 2021-10-05 13:17 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]  
// Refactored/Merged by camilon on 2021-10-04 07:00 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once

//
//class CLASS_DECL_ACME integral_day_t :
//   public integral_day
//{
//public:
//
//
//   using BASE_TYPE = integral_day;
//
//
//   constexpr integral_day_t(integral_day day = {}) : integral_day(day) {}
//
//
//   integral_second seconds() const { return integral_second(m_i * 86'400); }
//   integral_nanosecond nanoseconds() const { return integral_nanosecond(0); }
//   integral_millisecond total_milliseconds() const { return integral_millisecond(m_i *86'400'000); }
//
//   
//};
//
//
//using integral_day = integral_time < integral_day_t >;


template <  >
inline integral_day now<integral_day>()
{

   return get_integral_day();

}




