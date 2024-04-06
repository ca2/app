// Created by camilo on 2021-10-05 12:36 BRT <3ThomasBorregaardSorensen!![ THE ONE GOD ]
#pragma once

//
//class CLASS_DECL_ACME floating_millisecond_t :
//   public floating_millisecond
//{
//public:
//
//
//   using BASE_TYPE = floating_millisecond;
//
//
//   constexpr floating_millisecond_t(floating_millisecond millisecond = {}) : floating_millisecond(millisecond) {}
//
//
//   constexpr operator integral_second() const { return { (::i64)(m_d / 1'000.0) }; }
//   constexpr operator integral_nanosecond() const { return { (::i64)(fmod(m_d, 1'000.0) * 1'000'000.0) }; }
//
//
//   constexpr operator floating_second() const { return { m_d / 1'000.0 }; }
//
//};
//
//
//using floating_millisecond = floating_time < floating_millisecond_t >; 
//

inline floating_millisecond get_floating_millisecond() { return floating_millisecond(get_floating_nanosecond().m_d / 1'000'000.0); }


template <  >
inline floating_millisecond now<floating_millisecond>()
{

   return get_floating_millisecond();

}



