//
// Recreated by camilo on 2021-10-05 13:01 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Refactored/Merged by camilo on 2021-10-04 06:45 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
// Created by camilo on 2020-11-16. <3ThomasBS_ [ THE ONE GOD ]
//


class CLASS_DECL_ACME integral_nanosecond_t :
   public INTEGRAL_NANOSECOND
{
public:


   using BASE_TYPE = INTEGRAL_NANOSECOND;


   constexpr integral_nanosecond_t(INTEGRAL_NANOSECOND nanosecond = {}): INTEGRAL_NANOSECOND(nanosecond) {}


   INTEGRAL_SECOND seconds() const { return INTEGRAL_SECOND(m_i / 1'000'000'000); }
   INTEGRAL_NANOSECOND nanoseconds() const { return INTEGRAL_NANOSECOND(m_i % 1'000'000'000); }
   INTEGRAL_MILLISECOND total_milliseconds() const { return INTEGRAL_MILLISECOND(m_i / 1'000'000); }


};


using integral_nanosecond = integral_duration < integral_nanosecond_t >;




template <  >
inline integral_nanosecond now<integral_nanosecond>()
{

   return get_integral_nanosecond();

}




