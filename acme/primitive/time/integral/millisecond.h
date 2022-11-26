// Recreated by camilo on 2021-10-05 13:08 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Refactored/Merged by camilo on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


class integral_millisecond_t :
   public INTEGRAL_MILLISECOND
{
public:


   using BASE_TYPE = INTEGRAL_MILLISECOND;


   constexpr integral_millisecond_t(INTEGRAL_MILLISECOND millisecond = {}) : INTEGRAL_MILLISECOND(millisecond) {}


   constexpr operator INTEGRAL_SECOND() const { return { m_i / 1'000 }; }
   constexpr operator INTEGRAL_NANOSECOND() const { return { (m_i % 1'000) * 1'000'000 }; }


   constexpr operator FLOATING_SECOND() const { return { m_i / 1'000.0 }; }

};


using integral_millisecond = integral_time < integral_millisecond_t >;


template <  >
inline integral_millisecond now<integral_millisecond>()
{

   return get_integral_millisecond();

}





