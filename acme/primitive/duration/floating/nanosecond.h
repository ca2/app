//
// Created by camilo on 2021-10-05. <3ThomasBS_ [ THE ONE GOD ]
//


class CLASS_DECL_ACME floating_nanosecond_t :
   public FLOATING_NANOSECOND
{
public:


   using BASE_TYPE = FLOATING_NANOSECOND;


   constexpr floating_nanosecond_t(FLOATING_NANOSECOND nanosecond = {}) : FLOATING_NANOSECOND(nanosecond) {}


   operator INTEGRAL_SECOND() const { return INTEGRAL_SECOND((::i64) (m_d / 1'000'000'000.0)); }
   operator INTEGRAL_NANOSECOND() const { return INTEGRAL_NANOSECOND((::i64)fmod(m_d, 1'000'000'000.0)); }

   operator FLOATING_SECOND() const { return FLOATING_SECOND(m_d / 1'000'000'000.0); }



};


using floating_nanosecond = floating_duration < floating_nanosecond_t >;


inline floating_nanosecond get_floating_nanosecond() { return FLOATING_NANOSECOND((::f64)get_integral_nanosecond().m_i); }


template <  >
inline floating_nanosecond now<floating_nanosecond>()
{

   return get_floating_nanosecond();

}



