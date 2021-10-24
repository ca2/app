//
// Created by camilo on 2021-10-05 12:41 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
//


class CLASS_DECL_ACME floating_second_t :
   public FLOATING_SECOND
{
public:


   using BASE_TYPE = FLOATING_SECOND;


   floating_second_t(FLOATING_SECOND second = {}) : FLOATING_SECOND(second) {}


   INTEGRAL_SECOND integral_seconds() const { return (INTEGRAL_SECOND)((::i64) m_d); }
   INTEGRAL_NANOSECOND integral_nanoseconds() const { return (INTEGRAL_NANOSECOND)((::i64) (fmod(m_d, 1.0) * 1'000'000'000.0)); }


};


using floating_second = floating_duration < floating_second_t >; 


constexpr FLOATING_SECOND operator "" _s(long double d) { return (FLOATING_SECOND)d; }


inline floating_second get_floating_second() { return FLOATING_SECOND(get_floating_nanosecond().m_d / 1'000'000'000.0); }



template <  >
inline floating_second now<floating_second>()
{

   return get_floating_second();

}






