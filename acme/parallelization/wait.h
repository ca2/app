// Created by camilo on 2021-10-04 04:57 BRT <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME wait
{
public:


   ::i64       m_iMillisecond;


#if CPP20

   template < primitive_integral INTEGRAL >
   wait(INTEGRAL integral) { m_iMillisecond = (::i64)integral; }

#else

   wait(::i64 i) { m_iMillisecond = i; }

#endif


   wait(const ::wait & wait) : m_iMillisecond(wait.m_iMillisecond) {}
   inline wait(const ::duration & duration);

   static inline ::i64 _infinite() { return 0xffffffffu; }

   static inline class ::wait infinite() { return _infinite(); }

   inline operator ::u32() const { return (::u32) ::minimum_maximum(m_iMillisecond, 0, _infinite()); }

   inline bool is_infinite() const { return m_iMillisecond >= infinite(); }

   static inline class ::wait now();

   inline class ::wait elapsed(const class ::wait & waitSample = now()) { return waitSample.m_iMillisecond - m_iMillisecond; }

};
