// Created by camilo on 2021-10-05 12:36 BRT <3ThomasBorregaardSørensen!![ THE ONE GOD ]
#pragma once


class CLASS_DECL_ACME floating_millisecond_t :
   public FLOATING_MILLISECOND
{
public:


   using BASE_TYPE = FLOATING_MILLISECOND;


   constexpr floating_millisecond_t(FLOATING_MILLISECOND millisecond = {}) : FLOATING_MILLISECOND(millisecond) {}


   constexpr operator INTEGRAL_SECOND() const { return { (::i64)(m_d / 1'000.0) }; }
   constexpr operator INTEGRAL_NANOSECOND() const { return { (::i64)(fmod(m_d, 1'000.0) * 1'000'000.0) }; }


   constexpr operator FLOATING_SECOND() const { return { m_d / 1'000.0 }; }

};


using floating_millisecond = floating_duration < floating_millisecond_t >; 


inline floating_millisecond get_floating_millisecond() { return FLOATING_MILLISECOND(get_floating_nanosecond().m_d / 1'000'000.0); }


template <  >
inline floating_millisecond now<floating_millisecond>()
{

   return get_floating_millisecond();

}



