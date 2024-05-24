// Recreated by camilo on 2021-10-05 13:08 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
// Refactored/Merged by camilo on 2021-10-04 06:45 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once


//class integral_millisecond_t :
//   public integral_millisecond
//{
//public:
//
//
//   using BASE_TYPE = integral_millisecond;
//
//
//   constexpr integral_millisecond_t(integral_millisecond millisecond = {}) : integral_millisecond(millisecond) {}
//
//
//   constexpr operator integral_second() const { return { m_i / 1'000 }; }
//   constexpr operator integral_nanosecond() const { return { (m_i % 1'000) * 1'000'000 }; }
//
//
//   constexpr operator floating_second() const { return { m_i / 1'000.0 }; }
//
//};
//
//
//using integral_millisecond = integral_time < integral_millisecond_t >;
//

template <  >
inline integral_millisecond now<integral_millisecond>()
{

   return get_integral_millisecond();

}





