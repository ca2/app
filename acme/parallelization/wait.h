// Created by camilo on 2021-10-04 04:57 BRT <3ThomasBorregaardSørensen!!
#pragma once


#ifdef wait
#undef wait
#endif // wait


class CLASS_DECL_ACME wait :
   public INTEGRAL_MILLISECOND
{
public:


   wait() : INTEGRAL_MILLISECOND{} {}
   wait(enum_zero) : INTEGRAL_MILLISECOND(e_zero){}
   wait(const INTEGRAL_NANOSECOND & integralnanosecond) :INTEGRAL_MILLISECOND(integralnanosecond.m_i / 1'000'000) { }
   wait(const INTEGRAL_MICROSECOND & integralmicrosecond):INTEGRAL_MILLISECOND(integralmicrosecond.m_i / 1'000) { }
   wait(const INTEGRAL_MILLISECOND & integralmillisecond) :INTEGRAL_MILLISECOND(integralmillisecond) { }
   wait(const INTEGRAL_SECOND & integralsecond) :INTEGRAL_MILLISECOND(integralsecond.m_i * 1'000) { }
   wait(const INTEGRAL_MINUTE & integralminute) :INTEGRAL_MILLISECOND(integralminute.m_i * 60'000) { }
   wait(const INTEGRAL_HOUR & integralhour) :INTEGRAL_MILLISECOND(integralhour.m_i * 3'600'000) { }
   wait(const INTEGRAL_DAY & integralday) :INTEGRAL_MILLISECOND(integralday.m_i * 86'400'000) { }
   wait(const DURATION & duration) :INTEGRAL_MILLISECOND(duration.m_iSecond * 1'000 + duration.m_iNanosecond / 1'000'000) {}

   static inline ::i64 __infinite() { return 0xffffffffu ; }

   static inline INTEGRAL_MILLISECOND _infinite() { return INTEGRAL_MILLISECOND{ __infinite() }; }

   static inline class ::wait infinite() { return _infinite(); }

   inline operator ::u32() const { return (::u32) ::minimum_maximum(m_i, 0, __infinite()); }

   inline bool is_infinite() const { return m_i >= __infinite(); }

   inline bool is_null() const { return m_i <= 0; }

   static inline class ::wait now();

   inline class ::wait elapsed(const class ::wait & waitSample = now()) { return INTEGRAL_MILLISECOND(waitSample.m_i - m_i); }

   //inline class ::wait operator +(const class ::wait & wait) const { return INTEGRAL_MILLISECOND(m_i + wait.m_i); }
   //inline class ::wait operator -(const class ::wait & wait) const { return INTEGRAL_MILLISECOND(m_i - wait.m_i); }

};
