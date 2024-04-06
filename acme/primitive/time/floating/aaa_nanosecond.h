//
// Created by camilo on 2021-10-05. <3ThomasBS_ [ THE ONE GOD ]
//
//
//
//class CLASS_DECL_ACME floating_nanosecond_t :
//   public floating_nanosecond
//{
//public:
//
//
//   using BASE_TYPE = floating_nanosecond;
//
//
//   constexpr floating_nanosecond_t(floating_nanosecond nanosecond = {}) : floating_nanosecond(nanosecond) {}
//
//
//   operator integral_second() const { return integral_second((::i64) (m_d / 1'000'000'000.0)); }
//   operator integral_nanosecond() const { return integral_nanosecond((::i64)fmod(m_d, 1'000'000'000.0)); }
//
//   operator floating_second() const { return floating_second(m_d / 1'000'000'000.0); }
//
//
//
//};
//
//
//using floating_nanosecond = floating_time < floating_nanosecond_t >;


// inline floating_nanosecond get_floating_nanosecond() { return floating_nanosecond((::f64)get_integral_nanosecond().m_i); }


// template <  >
// inline floating_nanosecond now<floating_nanosecond>()
// {

//    return get_floating_nanosecond();

// }



