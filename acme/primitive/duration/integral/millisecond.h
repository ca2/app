// Recreated by camilo on 2021-10-05 13:08 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
// Refactored/Merged by camilo on 2021-10-04 06:45 BRT <3ThomasBorregaardS�rensen!![ THE ONE GOD ]
#pragma once


class integral_millisecond_t :
   public INTEGRAL_MILLISECOND
{
public:


   using BASE_TYPE = INTEGRAL_MILLISECOND;


   integral_millisecond_t(INTEGRAL_MILLISECOND millisecond = {}) : INTEGRAL_MILLISECOND(millisecond) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i / 1'000); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND((m_i % 1'000) * 1'000'000); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i); }


};


using integral_millisecond = integral_duration < integral_millisecond_t >;


template <  >
inline integral_millisecond now<integral_millisecond>()
{

   return get_integral_millisecond();

}





