//
// Created by camilo on 2021-10-05 12:41 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
//
//
//
//class CLASS_DECL_ACME floating_second_t :
//   public floating_second
//{
//public:
//
//
//   using BASE_TYPE = floating_second;
//
//
//   constexpr floating_second_t(floating_second second = {}) : floating_second(second) {}
//   floating_second_t(const class time & time);
//
//   integral_second integral_seconds() const { return (integral_second)((::i64) m_d); }
//   integral_nanosecond integral_nanoseconds() const { return (integral_nanosecond)((::i64) (fmod(m_d, 1.0) * 1'000'000'000.0)); }
//
//
//};
//
//
//using floating_second = floating_time < floating_second_t >; 

//
//constexpr floating_second operator "" _s(long double d) { return (floating_second)d; }


inline floating_second get_floating_second() { return floating_second(get_floating_nanosecond().m_d / 1'000'000'000.0); }



template <  >
inline floating_second now<floating_second>()
{

   return get_floating_second();

}






